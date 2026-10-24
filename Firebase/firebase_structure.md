# Firebase Data Structure

## Overview

The Smart Irrigation System is designed to use Firebase
for remote monitoring of irrigation parameters.

## Database Structure

```text
SmartIrrigation
│
├── sensorValue
├── moisturePercentage
├── pumpStatus
└── systemStatus



| Parameter          | Description                         |
| ------------------ | ----------------------------------- |
| sensorValue        | Raw soil moisture sensor reading    |
| moisturePercentage | Calculated soil moisture percentage |
| pumpStatus         | Current pump state                  |
| systemStatus       | Current irrigation condition        |
