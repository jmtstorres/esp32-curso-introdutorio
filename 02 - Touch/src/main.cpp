#include <Arduino.h>

int ledPin = GPIO_NUM_32;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int read = touchRead(T4);
  String wr = String(read) + "\n";
  Serial.write(wr.c_str());
  if(read == 1){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
}