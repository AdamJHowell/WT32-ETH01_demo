#ifndef ESPSHT30BMP280MQTT_NETWORK_H
#define ESPSHT30BMP280MQTT_NETWORK_H


#include "PubSubClient.h" // MQTT client by Nick O'Leary: https://github.com/knolleary/pubsubclient
#include "WT32-ETH01_demo.h"
#include <ArduinoOTA.h> // Arduino Over-The-Air updates.


#ifdef ESP8266
#include <ESP8266mDNS.h>
// These two defines accommodate a devkit I have, which powers the onboard LED backwards from what is traditional.
#else
#include <ESPmDNS.h> // Library for multicast DNS, needed for Over-The-Air updates.
#endif               // ESP8266
#include <ArduinoJson.h>
#include <Ethernet.h>


const char *COMMAND_TOPIC            = "Outdoors/commands";    // The topic used to subscribe to update commands.  Commands: publishTelemetry, changeTelemetryInterval, changeSeaLevelPressure.
const char *TOPIC_PREFIX             = "Outdoors/";            // The MQTT topic prefix, which will have suffixes appended to.
const char *MAC_TOPIC                = "mac";                  // The MAC address topic suffix.
const char *IP_TOPIC                 = "ip";                   // The IP address topic suffix.
const char *MQTT_COUNT_TOPIC         = "mqttCount";            // The MQTT count topic suffix.
const char *MQTT_COOLDOWN_TOPIC      = "mqttCoolDownInterval"; // The MQTT cooldown count topic suffix.
const char *PUBLISH_COUNT_TOPIC      = "publishCount";         // The publishCount topic suffix.
const unsigned int JSON_DOC_SIZE     = 1024;
unsigned int mqttConnectCount        = 0;
unsigned int publishCount            = 0;
unsigned int callbackCount           = 0;
unsigned long lastMqttConnectionTime = 0;
unsigned long mqttCoolDownInterval   = 10000;
unsigned long publishInterval        = 20000;
unsigned long lastPublishTime        = 0;
bool publishNow                      = false;
const int mqttPort = 1883;

EthernetClient ethClient;
PubSubClient mqttClient( ethClient );


void lookupMQTTCode( int code, String buffer );
void configureOTA();
void publishTelemetry();
void mqttCallback( char *topic, byte *payload, unsigned int length );
void mqttConnect( const char *mqttBroker );


#endif //ESPSHT30BMP280MQTT_NETWORK_H
