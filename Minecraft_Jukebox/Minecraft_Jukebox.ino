#include <SPI.h>
#include<MFRC522.h>

#define RST_PIN 5
#define SS_PIN 10

byte readCard[4];
String music_disc[2] = {"7A667D89","405D2EA5?"};
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SPI.begin(); // SPI bus
  mfrc522.PCD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(getID())
  {
   if(tagID == music_disc[0]){
    Serial.println("traveco?");
   }
   if(tagID == music_disc[1]){
    Serial.println("sexo?");
   }
  }
}


//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
