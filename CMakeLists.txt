cmake_minimum_required( VERSION 3.24 )
project( WT32-ETH01_demo )

set( CMAKE_CXX_STANDARD 17 )

add_executable( WT32-ETH01_demo
		WT32-ETH01_demo.ino
		WT32-ETH01_demo.h
		Network.ino
		Network.h
		privateInfo.h
		PubSubClient.cpp
		PubSubClient.h )

set_target_properties( WT32-ETH01_demo PROPERTIES LINKER_LANGUAGE CXX )
