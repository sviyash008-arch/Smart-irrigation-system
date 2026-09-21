#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long lastPublishTime = 0;
const long PUBLISH_INTERVAL = 5000; 

void setupWifi();
void reconnectMqtt();
void mqttCallback(char* topic, byte* payload, unsigned int length);
void publishAndDisplayData();

void setup() {
  Serial.begin(115200);


  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 


  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Smart Gardening");
  lcd.setCursor(5, 1);
  lcd.print("System");


  dht.begin();

 
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  delay(2000);
  lcd.clear();
}

void loop() {
 
  if (!mqttClient.connected()) {
    reconnectMqtt();
  }
  mqttClient.loop(); 

  unsigned long now = millis();
  if (now - lastPublishTime >= PUBLISH_INTERVAL) {
    lastPublishTime = now;
    publishAndDisplayData();
  }
}


void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Connected!");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());
}


void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message arrived on [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (String(topic) == TOPIC_RELAY_COMMAND) {
    if (message == "ON" || message == "1") {
      digitalWrite(RELAY_PIN, LOW); 
      mqttClient.publish(TOPIC_RELAY_STATUS, "ON");
      Serial.println("Action: Relay Turned ON");
    } 
    else if (message == "OFF" || message == "0") {
      digitalWrite(RELAY_PIN, HIGH); 
      mqttClient.publish(TOPIC_RELAY_STATUS, "OFF");
      Serial.println("Action: Relay Turned OFF");
    }
  }
}


void reconnectMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT Broker at ");
    Serial.print(MQTT_SERVER);
    Serial.print("...");

    String clientId = "ESP8266-SmartIrrigation-" + String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println(" Connected!");
      mqttClient.subscribe(TOPIC_RELAY_COMMAND);
      Serial.print("Subscribed to: ");
      Serial.println(TOPIC_RELAY_COMMAND);
    } else {
      Serial.print(" Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}


void publishAndDisplayData() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int rawSoil = analogRead(SOIL_PIN);

  int soilMoisturePercent = map(rawSoil, 1024, 300, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("No record is");
    lcd.setCursor(3, 1);
    lcd.print("collected");
    return;
  }


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print((int)temp);
  lcd.print((char)223); 
  lcd.print("C Hum:");
  lcd.print((int)humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Soil Moist: ");
  lcd.print(soilMoisturePercent);
  lcd.print("%");


  StaticJsonDocument<200> doc;
  doc["temperature"]   = temp;
  doc["humidity"]      = humidity;
  doc["soil_moisture"] = soilMoisturePercent;
  doc["raw_soil"]      = rawSoil;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

 
  mqttClient.publish(TOPIC_TELEMETRY, jsonBuffer);

  Serial.print("Published to Node-RED: ");
  Serial.println(jsonBuffer);
}
