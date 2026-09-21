# Smart Irrigation System 🌿💧

This is an IoT-based system designed to monitor plant health and automatically control the irrigation process using environmental sensors, automated water valves, and a custom **Node-RED Web Dashboard**.

Welcome to the Smart Irrigation System repository! This documentation provides a comprehensive overview of the system architecture, hardware requirements, and circuit configurations.

### 📌 Project Overview

The Smart Irrigation System automates plant watering by continuously reading soil moisture levels and surrounding climate parameters. The system minimizes water wastage while ensuring optimal soil hydration levels for plant growth.

#### Key Features
* 🤖 **Automated Irrigation:** Triggers water flow via relay when soil moisture drops below threshold.
* 🌡️ **Environmental Monitoring:** Real-time temperature and humidity tracking using the DHT11 sensor.
* 💧 **Water Conservation:** Prevents overwatering through real-time threshold control.
* 🖥️ **Node-RED Web Dashboard:** Real-time web visualization with gauges, graphs, and manual valve controls via MQTT protocol.

---

### 🛠️ Hardware Components Required

| Component | Description |
| :--- | :--- |
| **NodeMCU (ESP8266)** | Wi-Fi-enabled microcontroller running system logic and MQTT communication. |
| **Relay Module** | Electronic switch controlling power to the water valve/solenoid. |
| **DHT11 Sensor** | Digital sensor measuring ambient temperature and air humidity. |
| **Moisture Sensor** | Analog sensor monitoring volumetric soil moisture. |
| **Air / Water Valve** | Solenoid / mini water pump controlling irrigation flow. |
| **Power Supply & Wiring** | Breadboard / PCB, jumper wires, and 5V power adapter. |

---

### ⚙️ How It Works

1. **Initialization:** NodeMCU initializes Wi-Fi connection, pin states, and connects to the Node-RED MQTT Broker.
2. **Data Collection:** DHT11 reads temperature and humidity; the moisture sensor samples soil hydration.
3. **Telemetry & Dashboard:** Sensor readings are published as JSON payloads to Node-RED for live web dashboard updates.
4. **Irrigation Control:**
   * **Automatic Mode:** Logic processing compares moisture levels against predefined thresholds to control the relay.
   * **Manual Mode:** Commands sent directly from the Node-RED Web UI override valve state.
5. **Feedback Loop:** Hardware status is confirmed back to Node-RED in real-time.

---

### 🔒 Strictly Controlled Source Code Access

This repository contains public documentation, system specifications, and hardware architecture diagrams. **The core firmware source code and Node-RED flows are proprietary, closed-source, and strictly private.**


