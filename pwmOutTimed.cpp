#include <Arduino.h>

int pin = GPIO_NUM_32;
int valor = 0;

void setup() {      
  //Inicializando GPIO4 como saída    
  pinMode(pin, OUTPUT);
  ledcAttachPin(pin, 0);
  ledcSetup(0, 1000, 10); 
}     
    
void loop() {    
  valor++; //Soma valor de 1 a cada loop  
  if(valor == 255){//Se valor passa do limite de 255, voltamos para zero  
    valor = 0;  
  }  
  ledcWrite(0, valor);//Escrevemos valor no pino de saída  
  delay(10);  
} 
