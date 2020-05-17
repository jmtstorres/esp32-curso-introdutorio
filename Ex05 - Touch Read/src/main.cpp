#include <Arduino.h>

int ledPin = GPIO_NUM_2;
int touchPin = GPIO_NUM_4;
  
void setup() {
  Serial.begin(9600);
  Serial.println("Iniciado...");
  pinMode(ledPin, OUTPUT);//Configurando pino para saída do LED
}  
  
void loop() {  
  int read = touchRead(touchPin);//Lendo a entrada do Touch 4  
  Serial.println("Read: " + String(read, DEC));
  //No modelo do Shield Arduino, os valores  
  //são 1 para toque detectado e 0 ao contrário  
  if(read == 1){  
    digitalWrite(ledPin, HIGH);//Aciona saída do LED  
  }else{  
    digitalWrite(ledPin, LOW);//Desaciona saída do LED  
  }  
}
