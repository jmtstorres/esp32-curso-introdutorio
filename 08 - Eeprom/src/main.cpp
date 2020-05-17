#include <Arduino.h>
#include <EEPROM.h>

//Endereço para gravação dos dados
#define ADDR_COUNT 0

void setup() {
  EEPROM.begin(1);    //Inicializando a Memória (tamanho de 1 byte)
  Serial.begin(9600); //Inicializando a porta serial
}

void loop() {
  int vezes = EEPROM.read(ADDR_COUNT); //Efetuando leitura dos dados no endereço
  vezes += 1;                          //Somamos 1 a esse valor
  
  EEPROM.write(ADDR_COUNT, vezes);     //Gravando valor incrementado
  EEPROM.commit();                     //Salvando os dados em memória
  
  //Mostrando dados salvos
  Serial.println("Contagem: " + String(vezes, DEC));
  
  delay(2000);  //Aguardando 2 segundos
}