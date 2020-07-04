#include <Arduino.h>
#include <music.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");
  initializeBuzzer();
  Serial.println("Tocando...");
  playInitSong();
  Serial.println("Finalizado.");
}

void loop() {
  // put your main code here, to run repeatedly:
}