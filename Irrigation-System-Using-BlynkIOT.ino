#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "config.h"

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long lastPublishTime = 0;
const long PUBLISH_INTERVAL = 5000; 

void setupWifi();
void reconnectMqtt();
void mqttCallback(char* topic, byte* payload, unsigned int length);
void publishSensorData();

void setup() {
  Serial.begin(115200);
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  dht.begin();
  
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnectMqtt();
  }
  mqttClient.loop();
  
  unsigned long now = millis();
  if (now - lastPublishTime >= PUBLISH_INTERVAL) {
    lastPublishTime = now;
    publishSensorData();
  }
}

void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to Wi-Fi Network: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Successfully Connected!");
  Serial.print("ESP8266 Local IP Address: ");
  Serial.println(WiFi.localIP());
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Command received on [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  if (String(topic) == TOPIC_RELAY_COMMAND) {
    if (message == "ON" || message == "1") {
      digitalWrite(RELAY_PIN, LOW); 
      mqttClient.publish(TOPIC_RELAY_STATUS, "ON");
      Serial.println("Action: Relay Turned ON (Water Valve Open)");
    } 
    else if (message == "OFF" || message == "0") {
      digitalWrite(RELAY_PIN, HIGH); 
      mqttClient.publish(TOPIC_RELAY_STATUS, "OFF");
      Serial.println("Action: Relay Turned OFF (Water Valve Closed)");
    }
  }
}


void reconnectMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(MQTT_SERVER);
    Serial.print("...");

    String clientId = "ESP8266-SmartIrrigation-" + String(random(0xffff), HEX);
    
    if (mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT Broker!");
      mqttClient.subscribe(TOPIC_RELAY_COMMAND);
      Serial.print("Subscribed to topic: ");
      Serial.println(TOPIC_RELAY_COMMAND);
    } else {
      Serial.print("Failed to connect, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}


void publishSensorData() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int rawSoil = analogRead(SOIL_PIN);
  

  int soilMoisturePercent = map(rawSoil, 1024, 300, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Warning: Failed to read from DHT sensor!");
    return;
  }


  StaticJsonDocument<200> doc;
  doc["temperature"]   = temp;
  doc["humidity"]      = humidity;
  doc["soil_moisture"] = soilMoisturePercent;
  doc["raw_soil"]      = rawSoil;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

 
  mqttClient.publish(TOPIC_TELEMETRY, jsonBuffer);
  
  Serial.print("Published payload to Node-RED: ");
  Serial.println(jsonBuffer);
}
