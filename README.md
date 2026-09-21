# Smart-irrigation-System
This is IoT based project for Monitor plants health and Control control irrigation process 

Welcome to the Smart Irrigation System project! This repository contains the code and documentation for building a smart irrigation system using NodeMCU, Relay module, DHT11 sensor, Moisture sensor, and an air water valve to control water flow.

**Complete Report of this project** : https://drive.google.com/file/d/1sqiVt4n40g6_vmeh06R-Bm4rwvRZe_ns/view?usp=sharing

**Demo Video** : https://youtu.be/WtQtlA_PUv8

**NOTE**: This Repository contains two different project sources (both are nearly same)
          
          1. Smart Irrigation System using Blynk IOT (Shown in Demo Video and aboves report)
          2. Garden System Project (Contains following information)

**Project Overview :**
The Smart Irrigation System is designed to automate the process of watering plants by monitoring soil moisture levels and environmental conditions. This project aims to conserve water and ensure that plants receive the right amount of water, enhancing their growth and health.

**Components**
NodeMCU: A low-cost open-source IoT platform. It includes firmware that runs on the ESP8266 Wi-Fi SoC from Espressif Systems, and hardware which is based on the ESP-12 module.
Relay Module: Used to control the water valve. It acts as a switch that opens or closes the circuit based on the signals received from the NodeMCU.
DHT11 Sensor: A basic, low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air.
Moisture Sensor: Measures the volumetric content of water in the soil and provides an analog output that can be read by the NodeMCU.
Air Water Valve: Controls the flow of water to the irrigation system. It is operated by the relay module based on the moisture sensor's readings.

**Features**
Automated Irrigation: Automatically waters plants when soil moisture levels drop below a predefined threshold.
Environmental Monitoring: Monitors temperature and humidity levels using the DHT11 sensor.
Water Conservation: Ensures optimal use of water resources by only watering when necessary.
Remote Control and Monitoring: Can be integrated with IoT platforms for remote monitoring and control.

**How It Works**
Initialization: The NodeMCU initializes the sensors and the relay module.
Data Collection: The DHT11 sensor collects temperature and humidity data, and the moisture sensor measures the soil moisture level.
Decision Making: The NodeMCU processes the sensor data and decides whether the soil moisture level is below the threshold.
Irrigation Control: If the soil moisture is below the threshold, the NodeMCU activates the relay, opening the air water valve to irrigate the plants. Once the desired moisture level is reached, the relay deactivates, closing the valve.
Monitoring and Logging: Sensor data can be logged and monitored remotely if integrated with an IoT platform.

**Getting Started**
Prerequisites
NodeMCU (ESP8266)
Relay Module
DHT11 Sensor
Moisture Sensor
Air Water Valve
Jumper wires
Breadboard or PCB
Installation
Clone the Repository

bash
Copy code
git clone https://github.com/TejasVarute/smart-irrigation-System.git
cd smart-irrigation-system
Install Required Libraries
Ensure you have the following libraries installed in your Arduino IDE:

ESP8266WiFi
DHT sensor library
Adafruit Unified Sensor library
Upload the Code
Connect your NodeMCU to your computer and upload the code from src/main.ino using the Arduino IDE.

Wiring Diagram
Follow the wiring diagram provided in the docs/wiring_diagram.png file to connect your components correctly.

Configuration
Modify the configuration settings in the src/config.h file to set your Wi-Fi credentials and other parameters such as the soil moisture threshold.

Usage
Once the code is uploaded and the system is powered on, the Smart Irrigation System will start monitoring the soil moisture levels and environmental conditions, and control the water flow accordingly.

Contributing
Contributions are welcome! Please read the CONTRIBUTING.md file for guidelines on how to contribute to this project.

License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgements
Special thanks to the open-source community and the developers of the libraries used in this project.
