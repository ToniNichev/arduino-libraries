#include <Ethernet.h>
#include "EthernetWebClient.h"
#include "string_to_float.h"

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

    float *r = parseToValues(serverData);  

    
    Serial.println(sizeof(r) );
    Serial.println("##############");
    Serial.println(r[0],4);
    Serial.println(r[1],4);
    Serial.println(r[2],4);
    Serial.println(r[3],4);
    Serial.println(r[4],4);
    Serial.println(r[5],4);
    Serial.println(r[6],4);
    Serial.println(r[7],4);

    //Serial.write(serverData, 800);   
  }
  delay(300);
}
