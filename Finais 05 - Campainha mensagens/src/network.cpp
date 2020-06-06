#include <network.h>

int connect()
{
    WiFi.begin("NET_2GDC570B", "4BDC570B");
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