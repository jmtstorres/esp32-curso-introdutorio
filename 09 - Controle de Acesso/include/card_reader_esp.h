#ifndef CARD_READER_ESP
#define CARD_READER_ESP

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN    GPIO_NUM_4
#define RST_PIN   GPIO_NUM_5
#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16

void initCardReader();
boolean cardPresent();
boolean cardRead();

#endif