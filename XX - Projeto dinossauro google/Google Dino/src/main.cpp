#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int read = analogRead(A1);
  delay(10);
  Serial.write(read);
  if(read < 700){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}