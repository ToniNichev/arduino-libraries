#include "RFCommunicator.h"

RF24 RFCommunicatorRadio(9, 8);  // CE, CSN
//address through which two modules communicate.
const byte RFCommunicatorAddress[6] = "00001";
const byte RFCommunicatorAddressNewDevice[6] = "00002";
short int RFCommunicatorMode = 0;

void RFCommunicatorSetup() {
  //create an RF24 object``
  //RF24 radio(9, 8);  // CE, CSN
  Serial.println("!@!@!@!@");
}

short int RFCommunicatorLoop(char data[]) {
  if (RFCommunicatorRadio.available())
  {
    char text[128] = {0};
    RFCommunicatorRadio.read(&text, sizeof(text));
    //Serial.println(text);
    RFCommunicatorMode = 1;
   }
   return RFCommunicatorMode;
}

void RFCommunicatorListen() {
  RFCommunicatorRadio.begin();
  RFCommunicatorRadio.openReadingPipe(0, RFCommunicatorAddress);
  RFCommunicatorRadio.startListening();   
  Serial.println("Listening ...");
}

void RFCommunicatorSend(char sendText[]) {
  RFCommunicatorRadio.begin();
  RFCommunicatorRadio.openWritingPipe(RFCommunicatorAddress);
  RFCommunicatorRadio.stopListening();  
  delay(100);

  //const char text[] = "Test 123";
  const char text[150] = {0};
  strcpy(text,sendText);
  RFCommunicatorRadio.write(&text, sizeof(text));
}
