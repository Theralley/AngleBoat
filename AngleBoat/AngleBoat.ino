#include <SPI.h>
#include<Wire.h>
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 8
#define DIO 9

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1500

const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

TM1637Display display(CLK, DIO);

    static const float k_throttle = 0.96f;
    float OldGyX;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
Serial.begin(9600);

  pinMode(10, OUTPUT);
}
void loop() {
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers

    AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    //Serial.print("AcX = "); Serial.print(AcX / (180 / 3.141592));
    //Serial.print(" | AcY = "); Serial.print(AcY / (180 / 3.141592));
    //Serial.print(" | AcZ = "); Serial.print(AcZ / (180 / 3.141592));
    //Serial.print(" | Temp = "); Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
    Serial.print(" | GyX = "); Serial.println(GyX);
    //Serial.print(" | GyY = "); Serial.print(GyY / (180 / 3.141592));
    //Serial.print(" | GyZ = "); Serial.println(GyZ / (180 / 3.141592));
    //GyX = (((1-k_throttle)*OldGyX) + (k_throttle*GyX));
    //GyX = OldGyX;
    Serial.print(" Current Y: "); Serial.print(GyY/ (180 / 3.141592));
    Serial.print(" Current X: "); Serial.print(GyX/ (180 / 3.141592));
    Serial.print(" Current Z: "); Serial.print(GyZ/ (180 / 3.141592));
  display.setBrightness(0x0f);

  //display.setSegments(data);
  //display.showNumberDec(GyX, false, 2,1);
  
  display.setSegments(data);
  display.showNumberDec(9999, false, 4, 1);
  delay(TEST_DELAY);

  display.setSegments(data);
  /**for(int i=0; i<=10; i++)
  {
    display.showNumberDec(i);
  }*/
    
    //delay(100);
}
