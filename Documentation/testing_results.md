# Testing and Results

## Testing Objective

The system was tested to verify soil moisture monitoring
and automatic pump-control logic.

## Dry Soil Condition

When the calculated soil moisture falls below the configured
lower threshold:

- The system identifies the soil as dry.
- The pump is switched ON.
- The pump status is displayed by the system.

## Moist Soil Condition

When the calculated soil moisture reaches the upper threshold:

- The system identifies sufficient moisture.
- The pump is switched OFF.
- The pump status is updated.

## Control Logic

| Moisture Level | Pump Action |
|---|---|
| Below 35% | ON |
| 35–54% | Maintain previous state |
| 55% or above | OFF |

## Calibration

The values used for dry and wet conditions may need to be
adjusted according to the actual soil moisture sensor.

## Relay Configuration

The program assumes an active-LOW relay module.
