#ifndef CLIMA_H
#define CLIMA_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

String getClima(String cidade, int hour);

#endif