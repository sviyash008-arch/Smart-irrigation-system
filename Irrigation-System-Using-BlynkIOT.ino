#define BLYNK_TEMPLATE_ID "TMPLqR3R9azi"
#define BLYNK_DEVICE_NAME "Smart Irrigration System"
#define BLYNK_AUTH_TOKEN "AyuD8HMbvWyypMI7NqeEFtZaGHccEg_K"

#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2
OneWireoneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BlynkTimer timer;

char auth[] = "AyuD8HMbvWyypMI7NqeEFtZaGHccEg_K";
char ssid[] = "V2029";
char pass[] = "Wifi-Pass";

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) 
    {
      return;
    }
Blynk.virtualWrite(V5, h); //V5 is for Humidity
Blynk.virtualWrite(V6, t); //V6 is for Temperature
}

void Motor()
{
Serial.begin(9600);
pinMode(D2,OUTPUT);
}

void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
timer.setInterval(1000L, sendSensor);
dht.begin();

Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
sensors.begin();
}
  int sensor=0;
  int output=0;

void sendTemps()
{
  sensor=analogRead(A0);
  output=(100-map(sensor,0,1023,0,100)); //in place 100 there is 145 depending upon Moisture sensor
delay(1000);

sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

Serial.println(temp);
Serial.print(output);

Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,output);
delay(1000);
}

void loop()
{
Blynk.run();
timer.run();
sendTemps();
}
