#include <Arduino.h>

int entrada = GPIO_NUM_4;
int saida = GPIO_NUM_2;

void setup() {
  Serial.begin(9600);
  pinMode(entrada, INPUT_PULLDOWN);
  pinMode(saida, OUTPUT);
}

void loop() {
  int read = digitalRead(entrada);
  Serial.println("Read: " + String(read, DEC));
  digitalWrite(saida, read);
  if(read == HIGH){
    delay(10000);
  }
  delay(100);
}