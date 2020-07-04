#ifndef DISPLAY_ESP_H
#define DISPLAY_ESP_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

void initialize_display();
void writeText(String text);
void setHeaderRight(String headerStr);
void setHeaderLeft(String headerStr);
void setBody(String bodyStr);
void setFooterRight(String footerStr);
void setFooterLeft(String footerStr);
void clearDisplay();
void updateDisplay();
void drawline(int x, int y, int xe, int ye);

#endif
