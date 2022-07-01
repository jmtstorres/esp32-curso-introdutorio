#include <Arduino.h>
#include <music.h>
#include <display_esp.h>
#include <card_reader_esp.h>
#include <ntp_esp.h>
#include <connection_wifi.h>

int btnPin = GPIO_NUM_17;
int redPin = GPIO_NUM_17;
int grePin = GPIO_NUM_17;

void setup() {
  initialize_display();
  setFooterLeft("desconectado");
  setFooterRight("-");
  updateDisplay();

  bool conectado = connectWifi();
  if(conectado){
    setFooterLeft("rede:");
    setFooterRight(SSID_REDE);
  }
  updateDisplay();

  Serial.begin(9600);
  init_ntp();
  initializeBuzzer();
  initCardReader();

  pinMode(btnPin, INPUT_PULLDOWN);
  
  playInitSong();
}

void loop() {

  setHeaderLeft(ntpGetTimeStr());

  int valor = digitalRead(btnPin);
  if(valor == 1){
    setBody("Apertou!");
    updateDisplay();
    playDeniedSong();
    delay(1000);
  }
  
  if (cardPresent()) 
  {
    if(cardRead()){
      setBody("Cartao!");
      updateDisplay();
      playAcessSong();
      delay(1000);
    }
  }

  setBody("Aguardando");
  updateDisplay();
  delay(100);
}