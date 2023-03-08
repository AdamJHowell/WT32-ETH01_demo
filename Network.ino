#include "Network.h"


/**
 * @brief lookupMQTTCode() will return the string for an integer state code.
 * The string values are taken from PubSubClient.h
 */
void lookupMQTTCode( const int code, String buffer )
{
	switch( code )
	{
		case -4:
			buffer = "Connection timeout";
			break;
		case -3:
			buffer = "Connection lost";
			break;
		case -2:
			buffer = "Connect failed";
			break;
		case -1:
			buffer = "Disconnected";
			break;
		case 0:
			buffer = "Connected";
			break;
		case 1:
			buffer = "Bad protocol";
			break;
		case 2:
			buffer = "Bad client ID";
			break;
		case 3:
			buffer = "Unavailable";
			break;
		case 4:
			buffer = "Bad credentials";
			break;
		case 5:
			buffer = "Unauthorized";
			break;
		default:
			buffer = "Unknown MQTT state code";
	}
} // End of the lookupMQTTCode() function.

/**
 * @brief configureOTA() will configure and initiate Over The Air (OTA) updates for this device.
 */
void configureOTA()
{
#ifdef ESP8266
	Serial.println( "Configuring OTA for the ESP8266" );
	// Port defaults to 8266
	// ArduinoOTA.setPort(8266);

	// Hostname defaults to esp8266-[ChipID]
	ArduinoOTA.setHostname( hostName );

	// No authentication by default
	ArduinoOTA.setPassword( otaPass );

	// Password can be set with it's md5 value as well
	// MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
	// ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

	ArduinoOTA.onStart( []() {
		String type;
		if( ArduinoOTA.getCommand() == U_FLASH )
			type = "sketch";
		else // U_SPIFFS
			type = "filesystem";

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.println( "Start updating " + type );
	} );
	ArduinoOTA.onEnd( []() {
		Serial.println( "\nEnd" );
	} );
	ArduinoOTA.onProgress( []( unsigned int progress, unsigned int total ) {
		Serial.printf( "Progress: %u%%\r", ( progress / ( total / 100 ) ) );
	} );
	ArduinoOTA.onError( []( ota_error_t error ) {
		Serial.printf( "Error[%u]: ", error );
		if( error == OTA_AUTH_ERROR ) Serial.println( "Auth Failed" );
		else if( error == OTA_BEGIN_ERROR )
			Serial.println( "Begin Failed" );
		else if( error == OTA_CONNECT_ERROR )
			Serial.println( "Connect Failed" );
		else if( error == OTA_RECEIVE_ERROR )
			Serial.println( "Receive Failed" );
		else if( error == OTA_END_ERROR )
			Serial.println( "End Failed" );
	} );
#else
	Serial.println( "Configuring OTA for the ESP32" );
	// The ESP32 port defaults to 3232
	// ArduinoOTA.setPort( 3232 );
	// The ESP32 hostname defaults to esp32-[MAC]
	//	ArduinoOTA.setHostname( hostName );  // I'm deliberately using the default.
	// Authentication is disabled by default.
	ArduinoOTA.setPassword( otaPass );
	// Password can be set with it's md5 value as well
	// MD5( admin ) = 21232f297a57a5a743894a0e4a801fc3
	// ArduinoOTA.setPasswordHash( "21232f297a57a5a743894a0e4a801fc3" );
	//	Serial.printf( "Using hostname '%s'\n", hostName );

	String type = "filesystem"; // SPIFFS
	if( ArduinoOTA.getCommand() == U_FLASH )
		type = "sketch";

	// Configure the OTA callbacks.
	ArduinoOTA.onStart( []() {
		String type = "flash"; // U_FLASH
		if( ArduinoOTA.getCommand() == U_SPIFFS )
			type = "filesystem";
		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.print( "OTA is updating the " );
		Serial.println( type );
	} );
	ArduinoOTA.onEnd( []() { Serial.println( "\nTerminating OTA communication." ); } );
	ArduinoOTA.onProgress( []( unsigned int progress, unsigned int total ) { Serial.printf( "OTA progress: %u%%\r", ( progress / ( total / 100 ) ) ); } );
	ArduinoOTA.onError( []( ota_error_t error ) {
		Serial.printf( "Error[%u]: ", error );
		if( error == OTA_AUTH_ERROR ) Serial.println( "OTA authentication failed!" );
		else if( error == OTA_BEGIN_ERROR ) Serial.println( "OTA transmission failed to initiate properly!" );
		else if( error == OTA_CONNECT_ERROR ) Serial.println( "OTA connection failed!" );
		else if( error == OTA_RECEIVE_ERROR ) Serial.println( "OTA client was unable to properly receive data!" );
		else if( error == OTA_END_ERROR ) Serial.println( "OTA transmission failed to terminate properly!" ); } );
#endif

	// Start listening for OTA commands.
	ArduinoOTA.begin();

	Serial.println( "OTA is configured and ready." );
} // End of the configureOTA() function.

/**
 * @brief mqttConnect() will connect to the MQTT broker.
 */
void mqttConnect( const char *mqttBroker )
{
	long time = millis();
	// Connect the first time.  Avoid subtraction overflow.  Connect after cool down.
	if( lastMqttConnectionTime == 0 || ( time > mqttCoolDownInterval && ( time - mqttCoolDownInterval ) > lastMqttConnectionTime ) )
	{
		mqttConnectCount++;
		digitalWrite( RX_LED, LED_OFF );
		Serial.println( "Connecting to the MQTT broker." );

		mqttClient.setServer( mqttBroker, mqttPort );
		mqttClient.setCallback( mqttCallback );

		// Connect to the broker, using the MAC address as the client ID.
		if( mqttClient.connect( macAddress ) )
		{
			Serial.println( "Connected to the broker." );
			mqttClient.subscribe( COMMAND_TOPIC );
			digitalWrite( RX_LED, LED_ON );
		}
		else
		{
			int mqttStateCode = mqttClient.state();
			String buffer;
			lookupMQTTCode( mqttStateCode, buffer );
			Serial.printf( "MQTT state: %s\n", buffer );
			Serial.printf( "MQTT state code: %d\n", mqttStateCode );

			// This block increments the broker connection "cooldown" time by 10 seconds after every failed connection, and resets it once it is over 2 minutes.
			if( mqttCoolDownInterval > 120000 )
				mqttCoolDownInterval = 0;
			mqttCoolDownInterval += 10000;
		}

		lastMqttConnectionTime = millis();
	}
} // End of the mqttConnect() function.


/**
 * @brief publishTelemetry() will process incoming messages on subscribed topics.
 */
void publishTelemetry()
{
	publishCount++;
	char topicBuffer[256] = "";
	char valueBuffer[25]  = "";

	snprintf( topicBuffer, 256, "%s%s%s%s", TOPIC_PREFIX, macAddress, "/", MAC_TOPIC );
	snprintf( valueBuffer, 25, "%s", macAddress );
	if( mqttClient.publish( topicBuffer, valueBuffer ) )
		Serial.printf( "Publishing '%s' to '%s'\n", valueBuffer, topicBuffer );

	snprintf( topicBuffer, 256, "%s%s%s%s", TOPIC_PREFIX, macAddress, "/", IP_TOPIC );
	snprintf( valueBuffer, 25, "%s", ipAddress );
	if( mqttClient.publish( topicBuffer, valueBuffer ) )
		Serial.printf( "Publishing '%s' to '%s'\n", valueBuffer, topicBuffer );

	snprintf( topicBuffer, 256, "%s%s%s%s", TOPIC_PREFIX, macAddress, "/", MQTT_COUNT_TOPIC );
	snprintf( valueBuffer, 25, "%u", mqttConnectCount );
	if( mqttClient.publish( topicBuffer, valueBuffer ) )
		Serial.printf( "Publishing '%s' to '%s'\n", valueBuffer, topicBuffer );

	snprintf( topicBuffer, 256, "%s%s%s%s", TOPIC_PREFIX, macAddress, "/", MQTT_COOLDOWN_TOPIC );
	snprintf( valueBuffer, 25, "%lu", mqttCoolDownInterval );
	if( mqttClient.publish( topicBuffer, valueBuffer ) )
		Serial.printf( "Publishing '%s' to '%s'\n", valueBuffer, topicBuffer );

	snprintf( topicBuffer, 256, "%s%s%s%s", TOPIC_PREFIX, macAddress, "/", PUBLISH_COUNT_TOPIC );
	snprintf( valueBuffer, 25, "%lu", publishCount );
	if( mqttClient.publish( topicBuffer, valueBuffer ) )
		Serial.printf( "Publishing '%s' to '%s'\n", valueBuffer, topicBuffer );
} // End of the publishTelemetry() function.


/**
 * @brief mqttCallback() will process incoming messages on subscribed topics.
 * { "command": "publishTelemetry" }
 * { "command": "changeTelemetryInterval", "value": 10000 }
 */
void mqttCallback( char *topic, byte *payload, unsigned int length )
{
	callbackCount++;
	Serial.printf( "\nMessage arrived on Topic: '%s'\n", topic );

	StaticJsonDocument<JSON_DOC_SIZE> callbackJsonDoc;
	Serial.println( "JSON document (static) was created." );
	deserializeJson( callbackJsonDoc, payload, length );
	Serial.println( "JSON document was deserialized." );

	const char *command = callbackJsonDoc["command"];
	Serial.printf( "Processing command '%s'.\n", command );
	if( strcmp( command, "publishTelemetry" ) == 0 )
	{
		// Set publishNow to 1, to indicate that a telemetry read and publish should happen immediately.
		publishNow = true;
	}
	else if( strcmp( command, "changeTelemetryInterval" ) == 0 )
	{
		unsigned long tempValue = callbackJsonDoc["value"];
		// Only update the value if it is greater than 4 seconds.  This prevents a seconds vs. milliseconds confusion.
		if( tempValue > 4000 )
			publishInterval = tempValue;
		Serial.printf( "MQTT publish interval has been updated to %u\n", publishInterval );
		lastPublishTime = 0;
	}
	else if( strcmp( command, "deviceRestart" ) == 0 )
	{
		Serial.printf( "Restarting this device...\n" );
		deviceRestart();
	}
	else
		Serial.printf( "Unknown command '%s'\n", command );
} // End of the mqttCallback() function.
