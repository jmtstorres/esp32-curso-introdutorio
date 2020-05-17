#include <Arduino.h>
#include <WiFi.h>
#include <page.h>

WiFiServer server(80);
int LED = GPIO_NUM_32;

void setup(){

  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  WiFi.begin("NET-VIRTUA-JOAO", "92437775ta");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  String ip = WiFi.localIP().toString();
  String ipStr = "Connected to the WiFi network: " + ip;
  Serial.println(ipStr);
  page.replace("X-X-X", ip);
  Serial.print(page);

  server.begin();
}

void loop(){
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.print(page);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}