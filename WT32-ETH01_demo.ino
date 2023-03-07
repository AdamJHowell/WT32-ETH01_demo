#include "WT32-ETH01_demo.h"


void setup()
{
	pinMode( RX_LED, OUTPUT );
	pinMode( TX_LED, OUTPUT );
	Serial.begin( 115200 );
	//	snprintf( macAddress, 18, "%s", EthernetClient.macAddress().c_str() );
	//	snprintf( ipAddress, 16, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );

	byte mac[]                     = { 0xC4, 0xDE, 0xE2, 0xB2, 0xC5, 0xD0 };
	int status = Ethernet.begin( mac );
	if( status == 0 )
	{
		Serial.println( "Failed to configure Ethernet using DHCP!" );
		// Check for Ethernet hardware present
		if( Ethernet.hardwareStatus() == EthernetNoHardware )
			Serial.println( "Ethernet shield was not found." );
		else if( Ethernet.linkStatus() == LinkOFF )
			Serial.println( "Ethernet cable is not connected." );
	}
	else if( status == 1 )
	{
		Serial.println( "Ethernet connection succeeded using DHCP." );
	}
	else
	{
		Serial.print( "Unknown status code: " );
		Serial.println( status );
	}

	//	if( !Ethernet.begin( mac ) )
	//	{
	//		// If DHCP fails, log a warning that we should try it with a hard-coded address.
	//		Serial.println( "\n\n" );
	//		Serial.println( "-------------------------------------------------------------" );
	//		Serial.println( "Unable to initialize the Ethernet module." );
	//		Serial.println( "It is possible that it may work with a hard-coded IP address." );
	//		Serial.println( "-------------------------------------------------------------" );
	//		Serial.println( "\n\n" );
	//		IPAddress ip( 10, 250, 250, 212 );
	//		Ethernet.begin( mac, ip );
	//	}

	Serial.print( "ethClient.status(): " );
	Serial.println( ethClient.status() );
	Serial.print( "ethClient.available(): " );
	Serial.println( ethClient.available() );
	Serial.print( "ethClient.connected(): " );
	Serial.println( ethClient.connected() );
	Serial.print( "ethClient.getSocketNumber(): " );
	Serial.println( ethClient.getSocketNumber() );
	Serial.print( "ethClient.localPort(): " );
	Serial.println( ethClient.localPort() );
	Serial.print( "ethClient.remoteIP(): " );
	Serial.println( ethClient.remoteIP() );
	Serial.print( "ethClient.remotePort(): " );
	Serial.println( ethClient.remotePort() );

	configureOTA();
}


void deviceRestart()
{
	Serial.println( "Restarting the device..." );
	ESP.restart();
}


void loop()
{
	if( !mqttClient.connected() )
		mqttConnect( "adamh-dt-2019.west.faircom.com" );
	mqttClient.loop();

	digitalWrite( RX_LED, LED_ON );
	digitalWrite( TX_LED, LED_OFF );
	Serial.println( "LED on" );
	delay( 1000 );
	digitalWrite( RX_LED, LED_OFF );
	digitalWrite( TX_LED, LED_ON );
	Serial.println( "LED off" );
	delay( 1000 );
}
