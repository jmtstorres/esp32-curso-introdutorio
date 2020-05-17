#include <Arduino.h>

int saida = GPIO_NUM_0;
int entrada = GPIO_NUM_32;

void setup() { 
  Serial.begin(9600);     
  //Inicializando GPIO4 como saída    
  pinMode(saida, OUTPUT);
  //Inicializando GPIO4 como saída    
  pinMode(entrada, INPUT_PULLDOWN);
}

void loop() {    
  int valor = analogRead(entrada);//Lendo valor no pino de entrada
  Serial.println("Valor: " + String(valor));
  int tensao = (valor*3.3)/4095;
  if(tensao > 1.4){//Se o valor lido indicar tensão maior do que 1,5V
     digitalWrite(saida, HIGH);//Coloca a saida em HIGH
  } else {
     digitalWrite(saida, LOW);//Caso contrário coloca a saída em LOW
  }
  delay(100);
} 
