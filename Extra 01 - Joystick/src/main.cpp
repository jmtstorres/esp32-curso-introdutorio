#include <Arduino.h>

int j_y = GPIO_NUM_2;
int j_x = GPIO_NUM_4;

int led_amarelo = GPIO_NUM_16;
int led_vermelho = GPIO_NUM_5;

int valor = 0;

void setup() {
  Serial.begin(9600);

  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  
  pinMode(j_x, INPUT_PULLUP);
  pinMode(j_y, INPUT_PULLUP);

  //Ligando GPIO ao canal 0
  ledcAttachPin(led_amarelo, 0);
  //Configurando canal 0 com frequencia de 1khz e 10 bits
  ledcSetup(0, 1000, 12); 

  //Ligando GPIO ao canal 0
  ledcAttachPin(led_vermelho, 1);
  //Configurando canal 0 com frequencia de 1khz e 10 bits
  ledcSetup(1, 1000, 12); 
}

void loop() {
  int readx = analogRead(j_x);
  ledcWrite(0, readx);//Escrevemos o valor no canal configurado
  
  int ready = analogRead(j_y);
  ledcWrite(1, ready);//Escrevemos o valor no canal configurado

  Serial.println("|X:" + String(readx) + "|Y:" + String(ready));
  delay(100);
}