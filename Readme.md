
💧 IoT-Based Water Quality Monitoring System Using ESP32

📌 Project Overview

The IoT-Based Water Quality Monitoring System is an electronics and IoT project designed to monitor important water quality parameters using sensors and an ESP32 microcontroller.

The system measures three parameters:

- pH: Estimates how acidic or alkaline the water is.
- Turbidity: Indicates the cloudiness of water caused by suspended particles.
- Temperature: Measures the temperature of the water.

The ESP32 collects sensor readings and sends the data to the ThingSpeak IoT cloud platform over Wi-Fi. Users can view the recorded measurements through the ThingSpeak dashboard. An optional OLED display can also be added to show readings locally.

This project demonstrates how IoT technology can be used for water quality monitoring and remote data visualization.

---

🎯 Objectives

- Monitor water pH, turbidity, and temperature.
- Collect sensor readings using an ESP32.
- Transmit sensor data over Wi-Fi.
- Display and visualize data using ThingSpeak.
- Provide the option to display readings on an OLED screen.
- Develop a low-cost prototype for water quality monitoring.

---

🛠️ Hardware Requirements

No.| Component| Purpose
1| ESP32 Development Board| Microcontroller and Wi-Fi connectivity
2| pH Sensor Module| Measures water pH
3| Turbidity Sensor Module| Measures water cloudiness
4| DS18B20 Temperature Sensor| Measures water temperature
5| OLED Display (SSD1306, optional)| Displays readings locally
6| Breadboard| Circuit prototyping
7| Jumper Wires| Electrical connections
8| USB Data Cable| Programming and powering the ESP32
9| Suitable Power Supply| Powers the system when required

Note: The OLED display is optional. The basic software sends data to ThingSpeak and prints readings to the Serial Monitor.

---

💻 Software Requirements

- Arduino IDE
- ESP32 board package for Arduino IDE
- ThingSpeak account
- Wi-Fi connection
- Required Arduino libraries:
  - "WiFi.h"
  - "ThingSpeak.h"
  - "OneWire.h"
  - "DallasTemperature.h"

For the optional OLED display, install:

- Adafruit SSD1306
- Adafruit GFX Library

The ESP32 board package supplies the ESP32-specific Wi-Fi library. The other libraries can be installed through the Arduino IDE Library Manager.

---

⚙️ System Architecture

        Water Sample
             |
     +-------+-------+
     |       |       |
    pH   Turbidity  DS18B20
  Sensor   Sensor   Temperature
     |       |       |
     +-------+-------+
             |
            ESP32
             |
          Wi-Fi
             |
        ThingSpeak
        IoT Platform
             |
       Web Dashboard

Optional local display:

The ESP32 can also send readings to an SSD1306 OLED display over I²C.

---

🔌 Sensor Pin Connections

The following connections match the pin definitions in the current Arduino sketch.

Component| Sensor Pin| ESP32 Pin
pH Sensor| Analog Output| GPIO 34
Turbidity Sensor| Analog Output| GPIO 35
DS18B20| Data| GPIO 4
DS18B20| VCC| Suitable supply voltage for the sensor
DS18B20| GND| GND
ESP32| USB| Computer

Important:

- Connect all sensor grounds to the ESP32 ground.
- Check each sensor module's operating voltage and output voltage before connecting it.
- ESP32 GPIO inputs are not 5 V tolerant. Do not apply a 5 V analog output directly to GPIO 34 or GPIO 35.
- A typical bare DS18B20 requires a pull-up resistor, commonly 4.7 kΩ, between its data line and the appropriate logic supply. Follow your module's wiring requirements.
- The OLED wiring will depend on the selected display module.

---

📡 ThingSpeak Configuration

Create a ThingSpeak channel and enable the following fields:

Field| Parameter
Field 1| pH
Field 2| Turbidity
Field 3| Temperature

Save the channel and copy its Channel ID and Write API Key.

In the Arduino sketch, update the configuration:

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

unsigned long CHANNEL_ID = 3521931;
const char* WRITE_API_KEY = "YOUR_WRITE_API_KEY";

Replace the example Channel ID if you use a different channel.

Security: Never publish your real Wi-Fi password or ThingSpeak Write API Key in a public GitHub repository. Use placeholders in committed code.

---

🚀 Installation and Setup

Step 1: Install Arduino IDE

Download and install the Arduino IDE from the official website:

https://www.arduino.cc/en/software

Step 2: Install ESP32 Board Support

Install the ESP32 board package through Arduino IDE's Boards Manager.

Select the appropriate ESP32 development board.

Step 3: Install Libraries

Open Tools → Manage Libraries and install:

- ThingSpeak
- OneWire
- DallasTemperature

For OLED functionality, also install Adafruit SSD1306 and Adafruit GFX Library.

Step 4: Configure ThingSpeak

Create a channel, enable Fields 1–3, and save the Channel ID and Write API Key.

Step 5: Configure the Arduino Sketch

Enter the appropriate Wi-Fi credentials and ThingSpeak configuration locally.

Step 6: Verify and Upload

1. Connect the ESP32 to your computer using a data-capable USB cable.
2. Select the correct board and COM port.
3. Click Verify to compile the sketch.
4. Click Upload to program the ESP32.
5. Open Serial Monitor at 115200 baud.
6. Check the sensor readings and Wi-Fi connection messages.

Step 7: View the Results

Open your ThingSpeak channel dashboard and check whether new readings are being recorded.

---

📊 Expected Output

The system is designed to report the following measurements:

Parameter| Output
pH| Estimated acidity or alkalinity
Turbidity| Sensor-derived turbidity measurement
Temperature| Water temperature in °C

The readings are printed in the Serial Monitor and uploaded to ThingSpeak every 15 seconds in the current sketch.

Actual measurements depend on sensor calibration, installation, and water conditions.

Note: The current turbidity calculation returns sensor voltage, not calibrated NTU. The pH formula is also a temporary approximation. Both require calibration before their readings can be treated as reliable measurements.

---

🧪 Calibration and Testing

Before using the system for meaningful measurements:

1. Calibrate the pH sensor with appropriate standard buffer solutions.
2. Calibrate the turbidity sensor using suitable reference samples and the manufacturer's instructions.
3. Verify the DS18B20 reading against a suitable temperature reference.
4. Confirm that sensor output voltages remain within the ESP32's input limits.
5. Test Wi-Fi connectivity and verify that ThingSpeak accepts updates.
6. Compare the recorded readings with reference measurements where possible.

This prototype should not be considered a certified water safety testing device.

---

🌍 Applications

- Educational IoT and electronics projects
- Water quality observation and data logging
- Laboratory demonstrations
- Aquaculture monitoring prototypes
- Environmental monitoring experiments
- Remote sensor monitoring demonstrations

---

🔮 Future Improvements

- Add OLED display support for local readings.
- Calibrate pH and turbidity measurements.
- Add alerts when readings exceed selected thresholds.
- Create a mobile-friendly monitoring dashboard.
- Store historical readings for analysis.
- Add additional sensors, such as electrical conductivity or dissolved oxygen sensors.
- Improve power efficiency and enclosure design.

---

📁 Suggested Repository Structure

IoT-Water-Quality-Monitoring/
│
├── README.md
├── src/
│   └── water_quality_monitor.ino
├── docs/
│   ├── circuit_diagram.png
│   └── project_architecture.png
├── images/
│   └── project_setup.jpg
└── LICENSE

Add only files and images that you actually have. The OLED-enabled program can be stored separately if it is maintained as a separate version.

---

👨‍💻 Project Status

Current stage: Software preparation and verification.

The Arduino sketch has successfully compiled in Arduino IDE. Hardware testing, sensor calibration, OLED integration, and live ThingSpeak data verification remain dependent on completing the hardware setup.

---

📜 License

This project can be shared and adapted for educational purposes. Add an appropriate open-source license, such as the MIT License, if you want to permit others to reuse and modify your code under its terms.

---

🙌 Acknowledgements

- Arduino community
- Espressif ESP32 ecosystem
- ThingSpeak IoT platform
- Adafruit libraries and documentation
- Open-source electronics and IoT communityHow to add this to GitHub

1. Open your repository on GitHub.


2. Click Add file → Create new file.


3. Enter README.md as the filename.


4. Copy and paste the README content above.


5. Click Commit changes to save it.



GitHub will automatically display the README on your repository's main page.

Important: Before publishing your Arduino sketch, replace all real Wi-Fi credentials and API keys with placeholders. This keeps your network and ThingSpeak channel secure.
