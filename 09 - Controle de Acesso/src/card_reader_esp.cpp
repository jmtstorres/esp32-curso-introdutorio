#include <card_reader_esp.h>

MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
MFRC522 mfrc522(SS_PIN, RST_PIN);

void initCardReader()
{
    SPI.begin();
    mfrc522.PCD_Init();
}

boolean cardPresent(){
    return mfrc522.PICC_IsNewCardPresent();
}

boolean cardRead(){
    return mfrc522.PICC_ReadCardSerial();
}