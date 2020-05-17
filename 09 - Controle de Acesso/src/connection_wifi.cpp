#include <connection_wifi.h>

String ssid = SSID_JOAO;
String passwd = PASSWD_JOAO;

boolean connectWifi(){
  int wStatus = WL_DISCONNECTED;
  int limit = 60;
  WiFi.begin(ssid.c_str(), passwd.c_str());
  while (wStatus != WL_CONNECTED &&
         wStatus != WL_CONNECT_FAILED)
  {
    Serial.println("Tentando conexão...");
    delay(1000);
    wStatus = WiFi.status();
    if (limit-- <= 0)
    {
      wStatus = WL_CONNECT_FAILED;
      break;
    }
  }

  if (wStatus == WL_CONNECTED)
  {
    String ip = WiFi.localIP().toString();
    String ipStr = "Connected to the WiFi network: " + ip;
    Serial.println(ipStr);
    return true;
  }
  else
  {
    Serial.println("Falha ao conectar.");
  }
  return false;
}