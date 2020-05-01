/*
 * SAMD11 Simple Data Logger
 * 
 * Requires these two libraries: 
 * https://github.com/cmaglie/FlashStorage
 * https://github.com/arduino-libraries/RTCZero
 * 
 * Was testing this on a SAMD11 Feather, may need to be tweaked once a board variant
 * for the cap is finished.
 * 
 * Copyright (c) 2020 Joey Castillo
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include <RTCZero.h>
#include <FlashAsEEPROM.h>

RTCZero rtc;
bool usbMode = false;
bool shouldLog = false;

#define RECORD_SIZE 6

void setup() {
  Serial.begin(9600);
  
  rtc.begin();

  // log once per minute, 1024 bytes stores just under 3 hours of data
  rtc.setAlarmSeconds(0);
  rtc.enableAlarm(rtc.MATCH_SS);

  // Or log once per hour, 1024 bytes stores ~1 week of data
//  rtc.setAlarmMinutes(0);
//  rtc.enableAlarm(rtc.MATCH_MMSS);

  analogReadResolution(8);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);
  if(Serial) {
    usbMode = true;
  }
  digitalWrite(LED_BUILTIN, usbMode);

  if (usbMode) {
    dumpData();
    while(1);
  } 

  // disable USB in hopes of lowering power usage
  USB->DEVICE.CTRLA.bit.ENABLE = 0;

  if (!rtc.getYear()) {
    rtc.setDate(4, 25, 20);
    rtc.setTime(2, 24, 50);
  }

  rtc.attachInterrupt(alarmMatch);
}

void loop() {
  rtc.standbyMode();
  if (shouldLog) {
    shouldLog = false;
    uint8_t i = EEPROM.read(0);
    EEPROM.write(0, i + 1);
    size_t loc = i * RECORD_SIZE + 2;
    EEPROM.write(loc + 0, rtc.getYear());
    EEPROM.write(loc + 1, rtc.getMonth());
    EEPROM.write(loc + 2, rtc.getDay());
    EEPROM.write(loc + 3, rtc.getHours());
    EEPROM.write(loc + 4, analogRead(A0));
    EEPROM.write(loc + 5, analogRead(A1));
    EEPROM.write(loc + 6, analogRead(A2));
    EEPROM.write(loc + 7, analogRead(A3));
    EEPROM.commit();
    delay(100);
  }
}

void alarmMatch() {
  shouldLog = true;
}

void dumpData() {
  Serial.println("timestamp,A0,A1,A2,A3");
  for(int i = 0; i < EEPROM.read(0); i++) {
    size_t loc = i * RECORD_SIZE + 2;
    Serial.print("20");
    Serial.print(EEPROM.read(loc + 0));
    Serial.print('-');
    Serial.print(EEPROM.read(loc + 1));
    Serial.print('-');
    Serial.print(EEPROM.read(loc + 2));
    Serial.print(' ');
    Serial.print(EEPROM.read(loc + 3));
    Serial.print(":00:00,");
    Serial.print(EEPROM.read(loc + 4));
    Serial.print(',');
    Serial.print(EEPROM.read(loc + 5));
    Serial.print(',');
    Serial.print(EEPROM.read(loc + 6));
    Serial.print(',');
    Serial.print(EEPROM.read(loc + 7));
    Serial.println();
  }
}
