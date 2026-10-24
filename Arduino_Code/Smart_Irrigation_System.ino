/*
  Smart Irrigation System
  -----------------------
  IoT-based automatic irrigation system using
  NodeMCU ESP8266 and a soil moisture sensor.

  Features:
  - Soil moisture monitoring
  - Moisture percentage calculation
  - Automatic pump control
  - Relay-based switching
  - Wi-Fi connectivity
  - Firebase integration structure

  Board: NodeMCU ESP8266
*/

#include <ESP8266WiFi.h>

// -------------------------
// Wi-Fi Configuration
// -------------------------

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// -------------------------
// Pin Configuration
// -------------------------

const int soilMoisturePin = A0;
const int relayPin = D1;

// -------------------------
// Sensor Calibration
// -------------------------

const int dryValue = 850;
const int wetValue = 350;

// -------------------------
// Moisture Thresholds
// -------------------------

const int pumpOnThreshold = 35;
const int pumpOffThreshold = 55;

bool pumpState = false;


// -------------------------
// Setup
// -------------------------

void setup() {

  Serial.begin(115200);

  pinMode(soilMoisturePin, INPUT);
  pinMode(relayPin, OUTPUT);

  // Pump OFF at startup.
  // Active-LOW relay.
  digitalWrite(relayPin, HIGH);

  Serial.println();
  Serial.println("==============================");
  Serial.println(" Smart Irrigation System");
  Serial.println("==============================");

  // Connect to Wi-Fi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}


// -------------------------
// Main Loop
// -------------------------

void loop() {

  // Read raw soil moisture value.
  int sensorValue = analogRead(soilMoisturePin);

  // Convert raw reading into percentage.
  int moisturePercentage = map(
    sensorValue,
    dryValue,
    wetValue,
    0,
    100
  );

  // Keep percentage between 0 and 100.
  moisturePercentage = constrain(
    moisturePercentage,
    0,
    100
  );


  // -------------------------
  // Automatic Pump Control
  // -------------------------

  if (!pumpState && moisturePercentage < pumpOnThreshold) {

    pumpState = true;

    // Active-LOW relay
    digitalWrite(relayPin, LOW);

    Serial.println("Soil is DRY");
    Serial.println("Pump: ON");
  }

  else if (pumpState && moisturePercentage >= pumpOffThreshold) {

    pumpState = false;

    // Pump OFF
    digitalWrite(relayPin, HIGH);

    Serial.println("Soil moisture sufficient");
    Serial.println("Pump: OFF");
  }


  // -------------------------
  // Display System Data
  // -------------------------

  Serial.println("------------------------------");

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  Serial.print("Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  Serial.print("Pump Status: ");

  if (pumpState) {
    Serial.println("ON");
  }
  else {
    Serial.println("OFF");
  }

  Serial.print("Wi-Fi Status: ");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected");
  }
  else {
    Serial.println("Disconnected");
  }

  Serial.println("------------------------------");

  delay(2000);
}
