/******************************************************************************
lis3dh-motion-detection.h
LIS3DH Arduino
Leonardo Bispo
Mar 03, 2019
https://github.com/ldab/lis3dh-motion-detection
Resources:
Uses Wire.h for i2c operation

Inspired by https://github.com/sparkfun/SparkFun_LIS3DH_Arduino_Library

Distributed as-is; no warranty is given.
******************************************************************************/

// Accelerometer provides different Power modes by changing output bit resolution
#define LOW_POWER
//#define NORMAL_MODE
//#define HIGH_RESOLUTION

// Enable Serial debbug on Serial UART to see registers wrote
#define LIS3DH_DEBUG Serial

#include "lis3dh-motion-detection.h"
#include "Wire.h"

uint16_t sampleRate = 1;  // HZ - Samples per second - 1, 10, 25, 50, 100, 200, 400, 1600, 5000
uint8_t accelRange = 2;   // Accelerometer range = 2, 4, 8, 16g

LIS3DH myIMU(0x18);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  
  myIMU.begin(sampleRate, 1, 1, 1, accelRange);
  
  uint8_t readData = 0;

  // Confirm configuration:
  myIMU.readRegister(&readData, LIS3DH_INT1_CFG);
  Serial.println(readData, HEX);
  myIMU.readRegister(&readData, LIS3DH_INT2_CFG);
  Serial.println(readData, HEX);

  // Get the ID:
  myIMU.readRegister(&readData, LIS3DH_WHO_AM_I);
  Serial.println(readData, HEX);
}


void loop() {
  int16_t dataHighres = 0;

  myIMU.readRegisterInt16( &dataHighres, LIS3DH_OUT_X_L );
  Serial.print('x');
  Serial.println(dataHighres);

  myIMU.readRegisterInt16( &dataHighres, LIS3DH_OUT_Z_L );
  Serial.print('z');
  Serial.println(dataHighres);

  delay(1000);
}
