#ifndef NTP_ESP_H
#define NTP_ESP_H

#include <WiFi.h>
#include <NTPClient.h>

void init_ntp();
String ntpGetTimeStr();

#endif