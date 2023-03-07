//
// Created by Adam Howell on 2023-03-07.
//

#ifndef WT32_ETH01_DEMO_WT32_ETH01_DEMO_H
#define WT32_ETH01_DEMO_WT32_ETH01_DEMO_H


#include "Network.h"
#include "privateInfo.h"


const unsigned int RX_LED             = 5;    // The GPIO that the RX LED uses.
const unsigned int TX_LED             = 17;   // The GPIO that the TX LED uses.
const unsigned int LED_ON             = 1;    // Defining this gives flexibility for devices that use inverted logic.
const unsigned int LED_OFF            = 0;    // Defining this gives flexibility for devices that use inverted logic.
const unsigned int MILLIS_IN_SEC      = 1000; // The number of milliseconds in one second.
const unsigned int LED_BLINK_INTERVAL = 200;  // The time between LED blinks.
unsigned long lastLedBlinkTime        = 0;    // The time of the last LED state change.
char macAddress[18];                          // The MAC address of the WiFi NIC.
char ipAddress[16];                           // The IP address given to the device.

void deviceRestart();

#endif //WT32_ETH01_DEMO_WT32_ETH01_DEMO_H
