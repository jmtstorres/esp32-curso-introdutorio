#include <display_esp.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String headerRight = "--";
String headerLeft = "--";
String body = "--";
String footerLeft = "--";
String footerRight = "--";

void initialize_display()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
}

void setHeaderRight(String headerStr){
    headerRight = headerStr;
}

void setHeaderLeft(String headerStr){
    headerLeft = headerStr;
}

void setBody(String bodyStr){
    body = bodyStr;
}

void setFooterRight(String footerStr){
    footerRight = footerStr;
}

void setFooterLeft(String footerStr){
    footerLeft = footerStr;
}

void writeText(String text)
{
    display.clearDisplay();

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(F(text.c_str()));
    display.display(); // Show initial text
}

void drawline(int x, int y, int xe, int ye){
    display.clearDisplay();
    display.drawRoundRect(0, 0, 128, 64, 3, WHITE);
    display.drawLine(x, y, xe, ye, WHITE);
    display.display();
}

void updateDisplay(){
    display.clearDisplay();

    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(F(headerLeft.c_str()));

    display.setCursor(128-(headerRight.length()*6), 0);
    display.println(F(headerRight.c_str()));

    int scale = 2;
    display.setTextSize(scale); // Draw 2X-scale text
    display.setCursor((64-((body.length()*6*scale)/2)), 32-(scale*4));
    display.println(F(body.c_str()));

    display.setTextSize(1);
    display.setCursor(0, 57);
    display.println(F(footerLeft.c_str()));

    display.setCursor(128-(footerRight.length()*6), 57);
    display.println(F(footerRight.c_str()));

    display.display(); // Show initial text
}

void clearDisplay(){
    display.clearDisplay();
    display.display(); 
}