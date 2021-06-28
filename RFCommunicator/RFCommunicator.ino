#include <nRF24L01.h>
#include <RF24.h>
#include "RFCommunicator.h"


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }   
  

  //RFCommunicatorSetup();
  //delay(2000);
  //RFCommunicatorSend("this is my text 123 555");
  //RFCommunicatorListen();
}

int mode = 0;
char data[100] = {0};

void loop() {
  switch(mode) {
    case 0:
      RFCommunicatorSend("Send message 1");
      mode = 1;
      break;
    case 1:
      if(RFCommunicatorLoop(data) == true) {
        // data available
        mode = 2;
      }
      delay(2000);
      mode = 2;
      break;
    case 2:
      RFCommunicatorSend("Send message 2");
      delay(2000);
      mode = 0;
      break;
  }

}
