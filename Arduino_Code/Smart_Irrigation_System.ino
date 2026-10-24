/*
  Smart Irrigation System
  -----------------------
  Arduino-based automatic irrigation system.

  Working:
  - Reads soil moisture using an analog sensor.
  - If the soil is dry, the water pump is switched ON.
  - If sufficient moisture is detected, the pump is switched OFF.

  Board: Arduino Uno
*/

const int soilMoisturePin = A0;
const int relayPin = 7;

// Adjust this value after calibrating your soil moisture sensor.
const int moistureThreshold = 600;

void setup() {
  Serial.begin(9600);

  pinMode(soilMoisturePin, INPUT);
  pinMode(relayPin, OUTPUT);

  // Pump OFF at startup.
  digitalWrite(relayPin, HIGH);

  Serial.println("Smart Irrigation System Started");
}

void loop() {

  int moistureValue = analogRead(soilMoisturePin);

  Serial.print("Soil Moisture Value: ");
  Serial.println(moistureValue);

  if (moistureValue > moistureThreshold) {

    // Soil is relatively dry.
    digitalWrite(relayPin, LOW);

    Serial.println("Soil is dry -> Pump ON");

  } else {

    // Soil has sufficient moisture.
    digitalWrite(relayPin, HIGH);

    Serial.println("Soil has sufficient moisture -> Pump OFF");
  }

  delay(2000);
}
