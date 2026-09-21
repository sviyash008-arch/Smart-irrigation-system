#ifndef CONFIG_H
#define CONFIG_H

const char* WIFI_SSID     = "SmartHome_IoT_Network"; 
const char* WIFI_PASSWORD = "Password1234!";        

const char* MQTT_SERVER   = "192.168.1.150";        
const int   MQTT_PORT     = 1883;                   

const char* MQTT_USER     = "irrigation_admin";     
const char* MQTT_PASSWORD = "MqttSecurePass2026!";   

const char* TOPIC_TELEMETRY    = "irrigation/telemetry";    
const char* TOPIC_RELAY_COMMAND = "irrigation/relay/command";
const char* TOPIC_RELAY_STATUS  = "irrigation/relay/status";

#define DHTPIN          D2  
#define DHTTYPE         DHT11
#define SOIL_PIN        A0   
#define RELAY_PIN       D1   

#endif 
