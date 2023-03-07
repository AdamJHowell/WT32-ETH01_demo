//
// Created by Adam Howell on 2023-03-07.
//

#ifndef WT32_ETH01_DEMO_WT32_ETH01_DEMO_H
#define WT32_ETH01_DEMO_WT32_ETH01_DEMO_H


#include "Network.h"


const unsigned int RX_LED        = 5;  // The GPIO that the RX LED uses.
const unsigned int TX_LED        = 17; // The GPIO that the TX LED uses.
const unsigned int LED_ON        = 1;  // Defining this gives flexibility for devices that use inverted logic.
const unsigned int LED_OFF       = 0;  // Defining this gives flexibility for devices that use inverted logic.
const unsigned int JSON_DOC_SIZE = 1024;
const char *macAddress           = "";
const char *ipAddress            = "";

#endif //WT32_ETH01_DEMO_WT32_ETH01_DEMO_H
