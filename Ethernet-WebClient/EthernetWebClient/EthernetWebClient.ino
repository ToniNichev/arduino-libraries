#include <Ethernet.h>
#include "EthernetWebClient.h"

char serverData[100] = {0};
int serverDataLen;

void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
  Serial.println("================== PROGRAM STARTED ======================");
  
  setupEthernetWebClient();
  delay(200); 

}

short int programMode = 0;

void loop() {
  
  if(programMode == 0 && readDataFromServer(serverData, serverDataLen) == 1) {
    programMode = 1;
    Serial.write(serverData, 800);   
  }
  delay(300);
}
