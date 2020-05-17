#include <Arduino.h>
#include "BluetoothSerial.h"

//Definições de código para habilitar a função bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; //Classe com as funcionalidades bluetooth

int saida = GPIO_NUM_2;

//Callback para registro de eventos de estado
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){ //Caso o estado recebido seja conectado
    Serial.println("Client Connected");
  }

  if(event == ESP_SPP_CLOSE_EVT ){ //Caso o estado recebido seja desconectado
    Serial.println("Client disconnected");
  }
}

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32Dev");        //Iniciando com nome ESP32Dev
  SerialBT.register_callback(callback);
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(saida, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    int read = SerialBT.read();
    Serial.write(read);
    if(read == 0x30){
      Serial.println("ON!!!");
      digitalWrite(saida, LOW);
    }

    if(read == 0x31){
      Serial.println("OFF!!");
      digitalWrite(saida, HIGH);
    }
  }
  delay(20);
}