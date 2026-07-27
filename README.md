# Smart Home Control System using ESP32 & DWIN DGUS Touchscreen

## Overview

This project demonstrates a touchscreen-based Smart Home Control System developed using an ESP32 microcontroller and a DWIN DGUS HMI display.

The primary objective of the project was to establish UART communication between the DWIN touchscreen and the ESP32, using LED control as proof of successful hardware–software integration. A Smart Home interface was developed to provide an intuitive way of interacting with the system, where LEDs represent different room lighting zones.

---

## Features

- Interactive touchscreen-based Human–Machine Interface (HMI)
- Individual room control:
  - Living Room
  - Bedroom
  - Kitchen
  - Study Room
- ALL ON functionality
- ALL OFF functionality
- UART communication between DWIN DGUS and ESP32
- Real-time LED control

---

## Hardware Used

- ESP32 Development Board
- DWIN DGUS Touchscreen Display
- Breadboard
- LEDs
- Jumper Wires
- 5V Power Supply

---

## Software Used

- Arduino IDE
- DWIN DGUS Tool

---

## How It Works

1. The user interacts with the DWIN touchscreen.
2. The touchscreen sends the corresponding UART command to the ESP32.
3. The ESP32 processes the received command.
4. The appropriate LED is switched ON or OFF.
5. The ALL ON and ALL OFF buttons control all LEDs simultaneously.

---

## Repository Contents

- smart_home.ino
- README.md
- Front.jpeg
- Back.jpeg

---

## Future Improvements

- Relay-based appliance control
- Wi-Fi connectivity
- IoT integration
- Mobile application support
- Sensor monitoring

---

## Demonstration

A demonstration video of the project is available.


## License

This project is shared for educational and portfolio purposes.
