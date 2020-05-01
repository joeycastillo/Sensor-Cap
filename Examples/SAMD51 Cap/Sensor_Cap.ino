
/*
 * Based on Adafruit's ADT7410 breakout demo code.
 * 
 * Required sensor board: https://oshpark.com/shared_projects/sPoSvHVT
 * 
 * You'll need my fork of the ADT7410 library that adds interrupt support:
 * https://github.com/joeycastillo/Adafruit_ADT7410
 * 
 * Also this was working on an earlier prototype with a hacked up Trinket 
 * board variant, hence the wacky pin numbering. Will update this when I
 * do the M4 variant proper like.
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_ADT7410.h"

Adafruit_ADT7410 tempsensor = Adafruit_ADT7410();
Adafruit_NeoPixel led(1, 19, NEO_GRB + NEO_KHZ800);

unsigned int lastBuzz = 0;

void setup() {
  ////////////
  // Serial //
  ////////////
  Serial.begin(115200);

  ////////////////////////
  // Temperature Sensor //
  ////////////////////////
  pinMode(7, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  if (!tempsensor.begin()) {
    Serial.println("Couldn't find ADT7410!");
    while (1);
  }

  // Normal forehead temperature is: 
  // 31.7° in a cold place (15°)
  // 35.2° in a normal room (27°)
  // 31.7° in a hot place (47°)
  // This sketch assumes normal room temperature for now.

  tempsensor.setInterruptC(ADT7410_SETPOINT_LOW, 31.0); // <31° means hat is off of head
  tempsensor.setInterruptC(ADT7410_SETPOINT_HIGH, 36.0); // >36° is higher than the expected 35°
  tempsensor.setInterruptC(ADT7410_SETPOINT_CRITICAL, 37.0); // >37°, alert me!
  tempsensor.setHysteresisC(2); // interrupt lines should toggle immediately on crossing the boundary temperature.
  tempsensor.setComparatorMode(true);

  // sensor takes 250 ms to get first readings
  delay(250);

  led.begin();
}

void loop() {
  // Read and print out the temperature, then convert to *F
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  bool tempGood = digitalRead(12);
  bool tempCrit = !digitalRead(7);

  led.clear();
  if(tempCrit) {
    led.setPixelColor(0, led.Color(150, 0, 0));
    Serial.println("10,0,0");
    if (millis() - lastBuzz > 10000) {
      digitalWrite(3, HIGH);
      for (int i = 0; i < 2; i++) {
        delay(25);
        tone(A0, 329.63, 100);
        delay(150);
        tone(A0, 261.63, 100);
        delay(150);
      }
      lastBuzz = millis();
      digitalWrite(3, LOW);
    }
  } else if (!tempGood) {
    if (c < 32) led.setPixelColor(0, led.Color(0, 32, 128));
    else led.setPixelColor(0, led.Color(128, 128, 0));
    Serial.println("0,0,10");
  } else {
    led.setPixelColor(0, led.Color(0, 160, 0));    
    Serial.println("0,10,0");
  }

  led.show();

  delay(500);
}
