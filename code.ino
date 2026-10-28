#include <WiFi.h>
#include <ThingSpeak.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ================ WIFI ==================
const char* WIFI_SSID = "IoT Project";
const char* WIFI_PASSWORD = "35958712";

// ============== THINGSPEAK ==============
unsigned long CHANNEL_ID = 3521931;
const char* WRITE_API_KEY = "IAQDUGJOXID3C66H";

WiFiClient client;

// ============== SENSOR PINS =============
#define PH_PIN 34
#define TURBIDITY_PIN 35
#define ONE_WIRE_BUS 4

// ============== TEMPERATURE =============
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temperatureSensor(&oneWire);

// ============== VARIABLES ===============
float temperatureC = 0.0;
float pHValue = 0.0;
float turbidityValue = 0.0;

unsigned long lastUpdate = 0;

// ThingSpeak update interval
const unsigned long updateInterval = 20000;

// ============== SETUP ===================
void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(12);

  // Start temperature sensor
  temperatureSensor.begin();

  // Connect to Wi-Fi
  Serial.println();
  Serial.println("Water Quality Monitoring System");
  Serial.print("Connecting to Wi-Fi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttempt = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startAttempt < 20000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    ThingSpeak.begin(client);
    Serial.println("ThingSpeak started.");
  } else {
    Serial.println("\nWi-Fi connection failed.");
    Serial.println("Check your Wi-Fi credentials.");
  }
}

// ============== MAIN LOOP ===============
void loop() {
  readSensors();

  Serial.println("-------------------------------");

  Serial.print("pH estimate: ");
  Serial.println(pHValue, 2);

  Serial.print("Turbidity sensor voltage: ");
  Serial.println(turbidityValue, 3);

  Serial.print("Temperature: ");
  Serial.print(temperatureC, 2);
  Serial.println(" C");

  if (WiFi.status() == WL_CONNECTED &&
      millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    sendToThingSpeak();
  }

  delay(1000);
}

// ============== READ SENSORS =============
void readSensors() {
  // pH sensor
  int phRaw = analogRead(PH_PIN);
  float phVoltage = (phRaw / 4095.0) * 3.3;

  // Temporary estimate: calibrate with your pH sensor
  pHValue = 7.0 + ((2.5 - phVoltage) / 0.18);

  // Turbidity sensor
  int turbidityRaw = analogRead(TURBIDITY_PIN);

  float turbidityVoltage =
      (turbidityRaw / 4095.0) * 3.3;

  // Report voltage until sensor calibration is performed
  turbidityValue = turbidityVoltage;

  // DS18B20 temperature sensor
  temperatureSensor.requestTemperatures();

  float measuredTemperature =
      temperatureSensor.getTempCByIndex(0);

  if (measuredTemperature != DEVICE_DISCONNECTED_C &&
      measuredTemperature >= -55.0 &&
      measuredTemperature <= 125.0) {
    temperatureC = measuredTemperature;
  } else {
    Serial.println("Warning: DS18B20 not detected.");
  }
}

// ============== SEND TO CLOUD ============
void sendToThingSpeak() {
  Serial.println("Sending data to ThingSpeak...");

  ThingSpeak.setField(1, pHValue);
  ThingSpeak.setField(2, turbidityValue);
  ThingSpeak.setField(3, temperatureC);

  int response =
      ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

  if (response == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.print("ThingSpeak error code: ");
    Serial.println(response);
  }
}