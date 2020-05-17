#include <Arduino.h>

int entrada = GPIO_NUM_4;
int saida = GPIO_NUM_2;

void setup() {
  //Inicializando GPIO4 como saída  
  pinMode(saida, OUTPUT);  
  //Inicializando GPIO5 como entrada  
  pinMode(entrada, INPUT_PULLDOWN);  
}   
  
void loop() {  
  //Lendo valor da entrada no GPIO5  
  int valor = digitalRead(entrada);  
  //Atribuindo o valor para a saída (HIGH ou LOW)  
  digitalWrite(saida, valor);  
  //Delay impedindo que a alteração seja  
  //rápida demais para ser visualizada  
  delay(100);
}  
