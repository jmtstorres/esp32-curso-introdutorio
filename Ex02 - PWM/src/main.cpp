#include <Arduino.h>

int saida = GPIO_NUM_2;
int valor = 0;
  
void setup() {      
  //Inicializando GPIO como saída    
  pinMode(saida, OUTPUT);
  //Ligando GPIO ao canal 0
  ledcAttachPin(saida, 0);
  //Configurando canal 0 com frequencia de 1khz e 10 bits
  ledcSetup(0, 1000, 10); 
}     
    
void loop() {    
  valor++; //Soma valor de 1 a cada loop  
  if(valor == 255){//Se valor passa do limite de 255, voltamos para zero  
    valor = 0;  
  }  
  ledcWrite(0, valor);//Escrevemos o valor no canal configurado
  delay(10);  
}  
