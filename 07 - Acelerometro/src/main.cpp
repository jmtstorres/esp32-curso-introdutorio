/*
  ADXL3xx

  Reads an Analog Devices ADXL3xx accelerometer and communicates the
  acceleration to the computer. The pins used are designed to be easily
  compatible with the breakout boards from SparkFun, available from:
  http://www.sparkfun.com/commerce/categories.php?c=80

  The circuit:
  - analog 0: accelerometer self test
  - analog 1: z-axis
  - analog 2: y-axis
  - analog 3: x-axis
  - analog 4: ground
  - analog 5: vcc

  created 2 Jul 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ADXL3xx
*/
#include <Arduino.h>

const int xpin = GPIO_NUM_25;                  // x-axis of the accelerometer
const int ypin = GPIO_NUM_26;                  // y-axis
const int zpin = GPIO_NUM_27;                  // z-axis (only on 3-axis models)

void setup() {
  analogReadResolution(10);
  // initialize the serial communications:
  Serial.begin(9600);
}

float toAngle(int read){
  float volts = read*3.3/1024;
  return (volts - 1.2)*(180/0.68);
}

void loop() {
  // print the sensor values:
  Serial.print(toAngle(analogRead(xpin)));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(toAngle(analogRead(ypin)));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(toAngle(analogRead(zpin)));
  Serial.println();
  // delay before next reading:
  delay(100);
}