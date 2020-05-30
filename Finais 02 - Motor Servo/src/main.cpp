#include <Arduino.h>
#include <Servo.h>

int j_y = GPIO_NUM_2;
int j_x = GPIO_NUM_15;
int btn = GPIO_NUM_15;

int servoXpin = GPIO_NUM_0;
int servoYpin = GPIO_NUM_5;

Servo servo_x;
Servo servo_y;

void setup() {
  Serial.begin(9600);
  servo_x.attach(servoXpin);
  servo_y.attach(servoYpin);
  pinMode(btn, INPUT_PULLDOWN);
  pinMode(j_y, INPUT_PULLUP);
  pinMode(j_x, INPUT_PULLUP);
}

void loop() {
  int angle_y = analogRead(j_y);
  int angle_x = analogRead(j_x);
  servo_x.write(angle_x*180/4096);
  servo_y.write(angle_y*180/4096);
  delay(10);
}