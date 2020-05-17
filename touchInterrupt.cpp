#include <Arduino.h>

void callback();

int ledPin = GPIO_NUM_32;
bool acionado = false;

void setup() {
  pinMode(ledPin, OUTPUT);//Configurando pino para saída do LED
  //Configurando a interrupção para que quando o valor da entrada T4
  //for abaixo de 1 a função callback seja chamada
  touchAttachInterrupt(T4, callback, 1);
}

void callback(){
  acionado = true;
}

void loop() {
  if(acionado){
    digitalWrite(ledPin, LOW);
    acionado = false;
  }else{
    digitalWrite(ledPin, HIGH);
  }
  delay(100);
}