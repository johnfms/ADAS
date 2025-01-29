# ATmega32-based ADAS Project

## Overview
This project implements a miniature Advanced Driver Assistance Systems (ADAS) platform using the ATmega32 microcontroller. The system demonstrates key ADAS features including Adaptive Cruise Control (ACC), Lane Departure Warning (LDW), Automated Emergency Braking (AEB), and Lane Keeping Support (LKS).

## Features
- **Adaptive Cruise Control (ACC)**
  - Automatically adjusts vehicle speed based on distance from obstacles
  - Uses ultrasonic sensor for distance measurement
  - Linear speed control implementation

- **Lane Departure Warning (LDW) & Lane Keeping Support (LKS)**
  - IR sensors for lane detection
  - Automatic steering correction
  - Visual indicators for lane departure

- **Automated Emergency Braking (AEB)**
  - Emergency stop when obstacles are too close
  - Configurable minimum safe distance
  - Audio-visual warnings during emergency stops

## Hardware Requirements
- ATmega32 Microcontroller
- LCD Display
- Ultrasonic Sensor
- 2x IR Sensors
- H-Bridge Motor Driver
- DC Motors
- LED Indicators:
  - Green (Forward)
  - Yellow (Left/Right Turn)
  - Red (Emergency Stop)
- Buzzer
- Power Supply

## Pin Configuration
### LCD Connection
- Data Port: PORTA
- Control Pins: PC0 (RS), PC1 (RW), PC2 (E)

### Ultrasonic Sensor
- TRIG: PC3
- ECHO: PC4

### IR Sensors
- Left Sensor: PD2
- Right Sensor: PD3

### Motor Control (H-Bridge)
- IN1: PB0
- IN2: PD4
- IN3: PD5
- IN4: PD6
- ENA (Left Motor PWM): PB3
- ENB (Right Motor PWM): PD7

### LED Indicators
- Red LED: PB4
- Yellow LED Left: PB5
- Yellow LED Right: PB6
- Green LED: PB7
- Buzzer: PB2

## Software Implementation
The project is organized into several modules:
- `ADAS.c`: Main program file
- `ultrasonic.h`: Distance measurement functionality
- `ir.h`: Lane detection system
- `Hbridge.h`: Motor control functions
- `lcd.h`: Display interface
- `leds.h`: LED and buzzer control

### Key Features
1. **Distance-based Speed Control**
   - Linear speed adjustment based on obstacle distance
   - Configurable minimum and maximum distances
   - Smooth acceleration and deceleration

2. **Lane Detection System**
   - Interrupt-driven IR sensor monitoring
   - Real-time lane departure detection
   - Automatic steering correction

3. **Status Display**
   - Real-time distance measurement
   - Current speed indication
   - Operating mode display

4. **Visual Feedback System**
   - Color-coded LED indicators
   - Emergency warning buzzer
   - Intuitive status indication

## Getting Started
1. Clone the repository
2. Configure your ATmega32 with the specified pin connections
3. Compile the project using your preferred AVR toolchain
4. Flash the compiled binary to your ATmega32
5. Power up the system and verify all connections

## Configuration
Key parameters can be adjusted in the main header files:
```c
#define MIN_DISTANCE 10  // Minimum safe distance
#define MAX_DISTANCE 50  // Maximum control distance
```

## Contributing
Feel free to submit issues, fork the repository, and create pull requests for any improvements.

## Author
- johnfms
