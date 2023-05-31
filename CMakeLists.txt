cmake_minimum_required( VERSION 3.24 )
project( WT32-ETH01_demo )

set( CMAKE_CXX_STANDARD 17 )


include_directories( .
		C:/Code/Arduino/libraries/ArduinoJson/
		"C:/Users/Adam Howell/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32s3/include/lwip/lwip/src/include/netif"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/cores/esp32"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/variants/wt32-eth01"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/libraries/ArduinoOTA/src/"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/libraries/WiFi/src/"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/esp_event/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/freertos/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/freertos/include/esp_additions/freertos"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/dio_qspi/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/freertos/port/xtensa/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/xtensa/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/xtensa/esp32/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/esp_rom/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/esp_rom/include/linux"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/esp_hw_support/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/tools/sdk/esp32/include/hal/include/"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/cores/esp32"
		"C:/Users/Adam/.espressif/tools/xtensa-esp32-elf/esp-2021r2-patch3-8.4.0/xtensa-esp32-elf/xtensa-esp32-elf/include"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/libraries/Update/src"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/libraries/ESPmDNS/src"
		"C:/Users/Adam/Documents/Arduino/libraries/"
		"C:/Users/Adam/AppData/Local/Arduino15/libraries/Ethernet/src"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp32/hardware/esp32/2.0.7/cores/esp32"
		"C:/Users/Adam/AppData/Local/Arduino15/packages/esp8266/hardware/esp8266/3.1.1/libraries/ESP8266mDNS/src" )


add_executable( WT32-ETH01_demo
		WT32-ETH01_demo.ino
		WT32-ETH01_demo.h
		Network.ino
		Network.h
		privateInfo.h
		PubSubClient.cpp
		PubSubClient.h )

set_target_properties( WT32-ETH01_demo PROPERTIES LINKER_LANGUAGE CXX )
