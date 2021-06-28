
#include <Ethernet.h>

char server[] = "toni-develops.com";    // name address for Google (using DNS)
char serverName[] = "toni-develops.com";
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);
EthernetClient client;

// Variables to measure the speed
unsigned long byteCount = 0;


void setupEthernetWebClient() {
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 8061)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /thermostat-services/get-data?data=[] HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

unsigned char dataBuffer[500] = {0};
unsigned int dataBufferLen = 0;
short int ethernetMode = 0;


/**
 * 
 */
 
bool readDataFromServer(char serverData[], int serverDataLen) {
  if(ethernetMode == 3)
    return 1;

  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = client.available();
  
  if (len > 0) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    byteCount = byteCount + len;
    
    for(int i = 0; i < len; i ++) {
      if(buffer[i] == '[') {
        // body data started
        ethernetMode = 2;        
      }
      if(ethernetMode == 2) {
        serverData[dataBufferLen] = (char)buffer[i];
        dataBufferLen ++;
      }
    }
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    //Serial.write(dataBuffer, dataBufferLen);
    client.stop();
    //Serial.println();

    ethernetMode = 3;
    return 1;
  }  
  return 0;
}
