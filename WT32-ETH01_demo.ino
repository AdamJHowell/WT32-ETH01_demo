#define RX_LED 5
#define TX_LED 17


void setup()
{
	pinMode( RX_LED, OUTPUT );
	pinMode( TX_LED, OUTPUT );
	Serial.begin( 115200 );
}


void loop()
{
	digitalWrite( RX_LED, HIGH );
	digitalWrite( TX_LED, LOW );
	Serial.println( "LED on" );
	delay( 1000 );
	digitalWrite( RX_LED, LOW );
	digitalWrite( TX_LED, HIGH );
	Serial.println( "LED off" );
	delay( 1000 );
}
