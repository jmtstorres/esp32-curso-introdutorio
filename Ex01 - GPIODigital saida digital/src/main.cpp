#include <Arduino.h>

void setup() {  
  //Configurando GPIO 0 como saída
  pinMode(GPIO_NUM_2, OUTPUT);  
} 

void loop() {
  //Alterando estado para alto (HIGH)  
  digitalWrite(GPIO_NUM_2, HIGH);  
  //Aguardando 1 segundo  
  delay(1000);  
  //Alterando estado para alto (HIGH)  
  digitalWrite(GPIO_NUM_2, LOW);  
  //Aguardando 1 segundo  
  delay(1000); 
}