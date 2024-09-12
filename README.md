# Angle of Attack Detection System for Race Boats

## Overview

This project is designed to detect the **angle of attack** (AOA) of a race boat in real-time using an Arduino microcontroller. By measuring the AOA, the system helps optimize the boat's performance, providing valuable data for racers and engineers. This system can be mounted on the boat and uses sensors (e.g., accelerometers, gyroscopes) to measure the boat's pitch and calculate the angle of attack.

## Features

- **Real-Time AOA Measurement**: Continuously monitors the boat's pitch and calculates the angle of attack in real-time.
- **Arduino-Based**: Implemented on an Arduino board, making it lightweight and suitable for race boat integration.
- **Sensor Input**: Designed to work with commonly available sensors like MPU6050 (accelerometer and gyroscope).
- **Data Output**: Can be configured to display AOA readings on an LCD screen or sent to a data logger.

## Project Structure

- **AngleBoat/AngleBoat.ino**: The main Arduino sketch that reads sensor data, processes it, and calculates the angle of attack.
- **AngleTest/**: Contains testing scripts or supplementary code for validating the system.
  
## Hardware Requirements

To set up the AOA detection system, you'll need the following hardware components:
- **Arduino**: Compatible with Arduino Uno, Nano, or similar boards.
- **MPU6050 Sensor**: A 6-axis accelerometer and gyroscope to measure the boat's orientation.
- **Display**: Optional (LCD screen or other output methods to display the AOA in real time).
- **Power Supply**: Battery pack or USB power for the Arduino.
- **Cables and Mounting**: For connecting and securing the Arduino and sensors to the boat.

## Installation

1. **Connect the MPU6050 Sensor**:
   - Connect the sensor to the Arduino board using the following pin configuration:
     - VCC → 5V
     - GND → GND
     - SCL → A5 (Arduino Uno)
     - SDA → A4 (Arduino Uno)
   
2. **Upload the Code**:
   - Open the `AngleBoat.ino` file in the Arduino IDE.
   - Select the correct board and port from the **Tools** menu.
   - Upload the code to the Arduino.

3. **Configure the Display (Optional)**:
   - If you're using an LCD screen or another display method, connect it to the Arduino and modify the code to send output to the display.

4. **Mount the System**:
   - Securely mount the Arduino and sensor to your race boat. Ensure the sensor is properly oriented to measure the boat's pitch correctly.

## Usage

1. Once the system is mounted and powered on, the sensor will begin reading data and calculating the boat's angle of attack.
2. The angle of attack will either be displayed on the connected LCD screen (if configured) or sent to a serial monitor or data logger for analysis.
3. Use the data to optimize the boat's performance based on the angle of attack readings.

## Code Overview

The main logic for detecting the angle of attack is found in the `AngleBoat.ino` file, where the sensor data is processed to calculate the boat's orientation. Here's a brief overview of the code structure:

- **Sensor Initialization**: The MPU6050 sensor is initialized to start reading accelerometer and gyroscope data.
- **Data Processing**: The pitch (angle of attack) is calculated from the sensor readings using basic trigonometric functions.
- **Output**: The calculated angle of attack is output to either an LCD screen or via the serial interface.

## Future Improvements

- **Data Logging**: Implement a data logging feature to store angle of attack data for post-race analysis.
- **Wireless Communication**: Add wireless modules (e.g., Bluetooth, Wi-Fi) to send real-time data to a remote display or monitoring system.
- **Enhanced Calibration**: Improve the calibration process to make the system more accurate under various conditions.
