#include <Arduino.h>

int pin = GPIO_NUM_32;
int pinin = GPIO_NUM_25;

void setup() {      
  //Inicializando GPIO4 como saída    
  pinMode(pin, OUTPUT);
  pinMode(pinin, INPUT_PULLDOWN);
  ledcAttachPin(pin, 0);
  ledcSetup(0, 1000, 10); 
}     
    
void loop() {    
  int valor = analogRead(pinin);
  ledcWrite(0, valor);//Escrevemos valor no pino de saída  
  delay(20);
} 
