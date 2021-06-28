
#ifndef ETHERNET_WEB_CLIENT_H
#define ETHERNET_WEB_CLIENT_H
#include <Arduino.h>
#include "EthernetWebClient.h"

void setupEthernetWebClient();
bool readDataFromServer(char serverData[], int serverDataLen);

#endif
