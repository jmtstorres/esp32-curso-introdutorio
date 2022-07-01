#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <display_esp.h>

const char* ssid       = "SSID_REDE";
const char* password   = "SENHA_REDE";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -3*3600;
const int   daylightOffset_sec = 0;

void updateLocalTime();

void setup()
{
  Serial.begin(9600);
  initialize_display();
  setFooterLeft("desconectado");
  setFooterRight("-");
  updateDisplay();
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  setFooterLeft("rede:");
  setFooterRight(ssid);
  updateDisplay();
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  updateLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  updateLocalTime();
}

void updateLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    setBody("--:--:--");
    setHeaderRight("--/--/--");
    return;
  }else{
    char datestr[16];
    char timestr[16];
    sprintf(timestr, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    sprintf(datestr, "%02d/%02d/%02d", timeinfo.tm_mday, timeinfo.tm_mon, timeinfo.tm_year-100);
    setBody(timestr);
    setHeaderRight(datestr);
  }
  updateDisplay();
}