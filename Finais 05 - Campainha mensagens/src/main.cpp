#include <Arduino.h>
#include <music.h>
#include <network.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

int btnPin = GPIO_NUM_4;
int ledPin = GPIO_NUM_16;

#define BOTtoken "1235018938:AAFcKaibsOmJ8FsmO0H_C-wccB8H4Vuh3PI"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

String id = "1103920585";

void setup()
{
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLDOWN);
  pinMode(ledPin, OUTPUT);
  if(connect()){
    digitalWrite(ledPin, HIGH);
  }
  initializeBuzzer(GPIO_NUM_2);
  playInitSong();
}

void loop()
{
  /*
  int newmsg = bot.getUpdates(bot.last_message_received + 1);
  for (int i = 0; i < newmsg; i++)
  {
    //Tratar comandos!
    String idChat = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    Serial.println("Recebido: " + idChat + " - " + text);
  }
  */

  if (digitalRead(btnPin) == HIGH)
  {
    digitalWrite(ledPin, LOW);
    playInitSong();
    bot.sendSimpleMessage(id, "Campainha tocou!!!", "");
    digitalWrite(ledPin, HIGH);
  }
}