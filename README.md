# Joystick-Controlled Stepper Motor System

A C++ embedded system running on an Arduino UNO R3 to control a 28BYJ-48 stepper motor using an analog joystick module, featuring non-blocking speed control and real-time RPM telemetry.

## System Components
- **Microcontroller:** Arduino UNO R3
- **Motor & Driver:** 28BYJ-48 Stepper Motor + ULN2003 Driver Board
- **Input:** 2-Axis Analog Joystick Module

## Hardware Pinout
| Component | Arduino Pin | Description |
| :--- | :--- | :--- |
| Joystick VRx | A0 | Speed & Direction Control |
| Motor IN1 - IN4 | Pins 8, 9, 10, 11 | Coil Phase Control Signals |

## Key Features
- **Dynamic Speed Regulation:** Maps analog deflection to coil step delay (2ms–20ms).
- **Non-Blocking Serial Telemetry:** Calculates real-time output RPM based on motor gear ratio (2048 steps/rev).
- **Deadzone Calibration:** Eliminates resting jitter with a ±50 center margin.
