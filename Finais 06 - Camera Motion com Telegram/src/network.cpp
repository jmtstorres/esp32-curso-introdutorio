#include <network.h>

int connect()
{
    WiFi.begin("SSID_REDE", "SENHA_REDE");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    return WL_CONNECTED;
}

String getIP(){
    return WiFi.localIP().toString();
}