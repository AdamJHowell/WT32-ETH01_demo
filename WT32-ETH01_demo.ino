#include "WT32-ETH01_demo.h"


void setup()
{
	pinMode( RX_LED, OUTPUT );
	pinMode( TX_LED, OUTPUT );
	Serial.begin( 115200 );
}


void loop()
{
	digitalWrite( RX_LED, LED_ON );
	digitalWrite( TX_LED, LED_OFF );
	Serial.println( "LED on" );
	delay( 1000 );
	digitalWrite( RX_LED, LED_OFF );
	digitalWrite( TX_LED, LED_ON );
	Serial.println( "LED off" );
	delay( 1000 );
}
