/*
  Smart Irrigation System
  -----------------------
  Arduino-based automatic irrigation controller.

  Features:
  - Reads soil moisture using an analog sensor
  - Converts sensor reading into moisture percentage
  - Automatically controls a water pump through a relay
  - Uses separate ON/OFF thresholds to reduce rapid relay switching
  - Displays system status through Serial Monitor

  Board: Arduino Uno
*/

const int soilMoisturePin = A0;
const int relayPin = 7;

// Sensor calibration values.
// These should be adjusted according to the actual sensor.
const int dryValue = 850;
const int wetValue = 350;

// Pump starts when moisture falls below this value.
const int pumpOnThreshold = 35;

// Pump stops when moisture reaches this value.
const int pumpOffThreshold = 55;

bool pumpState = false;

void setup() {

  Serial.begin(9600);

  pinMode(soilMoisturePin, INPUT);
  pinMode(relayPin, OUTPUT);

  // Keep pump OFF when the system starts.
  digitalWrite(relayPin, HIGH);

  Serial.println("================================");
  Serial.println(" Smart Irrigation System");
  Serial.println("================================");
  Serial.println("System Started");
  Serial.println();
}

void loop() {

  // Read raw sensor value.
  int sensorValue = analogRead(soilMoisturePin);

  // Convert sensor value into moisture percentage.
  int moisturePercentage = map(
    sensorValue,
    dryValue,
    wetValue,
    0,
    100
  );

  // Keep percentage within 0-100 range.
  moisturePercentage = constrain(
    moisturePercentage,
    0,
    100
  );

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);

  Serial.print(" | Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");


  // Start pump when soil becomes too dry.
  if (!pumpState && moisturePercentage < pumpOnThreshold) {

    pumpState = true;

    // Active-LOW relay
    digitalWrite(relayPin, LOW);

    Serial.println("Status: DRY");
    Serial.println("Action: Pump ON");
  }


  // Stop pump when soil has enough moisture.
  else if (pumpState && moisturePercentage >= pumpOffThreshold) {

    pumpState = false;

    // Active-LOW relay
    digitalWrite(relayPin, HIGH);

    Serial.println("Status: MOIST");
    Serial.println("Action: Pump OFF");
  }


  // Display normal operating status.
  else {

    if (moisturePercentage < pumpOffThreshold) {
      Serial.println("Status: Moisture being monitored");
    }
    else {
      Serial.println("Status: Moisture sufficient");
    }

    Serial.print("Pump: ");

    if (pumpState) {
      Serial.println("ON");
    }
    else {
      Serial.println("OFF");
    }
  }

  Serial.println("--------------------------------");

  // Read sensor every 2 seconds.
  delay(2000);
}
