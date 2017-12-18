# ###*B*###
# Erika Enterprise, version 3
# 
# Copyright (C) 2017 Evidence s.r.l.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or (at
# your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License, version 2, for more details.
# 
# You should have received a copy of the GNU General Public License,
# version 2, along with this program; if not, see
# <https://www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
# 
# This program is distributed to you subject to the following
# clarifications and special exceptions to the GNU General Public
# License, version 2.
# 
# THIRD PARTIES' MATERIALS
# 
# Certain materials included in this library are provided by third
# parties under licenses other than the GNU General Public License. You
# may only use, copy, link to, modify and redistribute this library
# following the terms of license indicated below for third parties'
# materials.
# 
# In case you make modified versions of this library which still include
# said third parties' materials, you are obligated to grant this special
# exception.
# 
# The complete list of Third party materials allowed with ERIKA
# Enterprise version 3, together with the terms and conditions of each
# license, is present in the file THIRDPARTY.TXT in the root of the
# project.
# ###*E*###

## \file	ee_arduino_libcfg.mk
## \brief	Arduino SDK Library Configuration.
##
## This makefile contains the rules to integrate Arduino SDK in Erika Enterprise
## as a stand-alone library.
##
## \author	Giuseppe Serano
## \date	2016

## Check the Arduino library selection
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)

include	$(OS_EE_MK_BASE_DIR)/ee_arduino_linkcfg.mk

ifeq	($(and	\
		$(call iseeopt, OS_EE_ARCH_AVR8),	\
		$(call iseeopt, OS_EE_ARCH_AVR8_ATMEGA)	\
	), yes)

ifeq	($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/hooks.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_digital.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_analog.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_pulse.c

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_pulse.S
endif	# OS_EE_LIB_ARDUINO_SDK_CC

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_shift.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/WInterrupts.c

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_PCINT), yes)
EE_SRCS += hardware/arduino/avr/cores/arduino/WPCInterrupts.c
endif	# OS_EE_LIB_ARDUINO_SDK_PCINT

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/abi.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/CDC.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial0.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial1.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial2.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial3.cpp

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HID.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/IPAddress.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/new.cpp

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/PluggableUSB.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/Print.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/Stream.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/Tone.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/USBCore.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/WMath.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/WString.cpp

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ARDUINO_WIFI), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/ArduinoWiFi.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/crc16.c
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/espduino.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/FP.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/rest.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/ringbuf.c
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/SC16IS750.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ARDUINO_WIFI

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_BRACCIO), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/Braccio.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_BRACCIO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_BRIDGE), yes)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/Bridge.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/Console.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/FileIO.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/HttpClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/MailBox.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/Process.cpp
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeUdp.cpp
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_6_9), yes)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeSSLClient.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_9
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/YunClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/YunServer.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_BRIDGE

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_CIAO), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/Ciao.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/crc16.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/espduino.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/FP.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/rest.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/ringbuf.c
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/SC16IS750.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/wifi.cpp
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/Ciao.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/crc16.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/espduino.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/FP.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/rest.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/ringbuf.c
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/SC16IS750.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/UnowifiCiao.cpp
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
EE_SRCS += libraries/Braccio/src/Ciao.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_CIAO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_EEPROM), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/EEPROM/EEPROM.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_EEPROM

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ESPLORA), yes)
EE_SRCS_ARDUINO_SDK += libraries/Esplora/src/Esplora.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ESPLORA

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET), yes)
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/Dhcp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/Dns.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/Ethernet.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/EthernetClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/EthernetServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/EthernetUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/utility/socket.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/utility/w5100.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET2), yes)
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Dhcp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Dns.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Ethernet2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/EthernetClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/EthernetServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/EthernetUdp2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Twitter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/utility/socket.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/utility/w5500.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET2

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_FIRMATA), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Firmata/Firmata.cpp
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/EthernetClientStream.cpp
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/SerialFirmata.cpp
ifeq	$(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_6_10),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_8_5)	\
	)
	, yes
)
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/BLEStream.cpp
else	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_10 || OS_EE_LIB_ARDUINO_SDK_CC_1_8_5
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/WiFi101Stream.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_10 || OS_EE_LIB_ARDUINO_SDK_CC_1_8_5
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/WiFiStream.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
EE_SRCS += libraries/Firmata/utility/BLEStream.cpp
EE_SRCS += libraries/Firmata/utility/EthernetClientStream.cpp
EE_SRCS += libraries/Firmata/utility/SerialFirmata.cpp
EE_SRCS += libraries/Firmata/utility/WiFi101Stream.cpp
EE_SRCS += libraries/Firmata/utility/WiFiStream.cpp
EE_SRCS += libraries/Firmata/Firmata.cpp
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
EE_SRCS_ARDUINO_SDK += libraries/Firmata/src/Firmata.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_FIRMATA

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_GSM), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3CircularBuffer.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileAccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileCellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileDataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileMockupProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkRegistry.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileSMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileVoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1AccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BandManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BaseProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1CellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DirectModemProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemCore.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemVerification.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1PinManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ScanNetworks.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1SMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1VoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SMSService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SoftSerial.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3VoiceCallService.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3CircularBuffer.cpp
EE_SRCS_ARDUINO_SDK += 	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileAccessProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileCellManagement.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileClientProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileClientService.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileDataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileMockupProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileNetworkRegistry.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileServerProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileServerService.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileSMSProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3MobileVoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1AccessProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1BandManagement.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1BaseProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1CellManagement.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ClientProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1DataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1DirectModemProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ModemCore.cpp
EE_SRCS_ARDUINO_SDK +=	\
hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ModemVerification.cpp
EE_SRCS_ARDUINO_SDK +=	\
hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1MultiClientProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1MultiServerProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1PinManagement.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ScanNetworks.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ServerProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1SMSProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1VoiceProvider.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV2.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3SMSService.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3SoftSerial.cpp
EE_SRCS_ARDUINO_SDK +=	\
	hardware/arduino/avr/libraries/GSM/src/GSM3VoiceCallService.cpp
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3CircularBuffer.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileAccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileCellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileDataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileMockupProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkRegistry.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileSMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileVoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1AccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BandManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BaseProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1CellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DirectModemProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemCore.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemVerification.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1PinManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ScanNetworks.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1SMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1VoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV2.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SMSService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SoftSerial.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3VoiceCallService.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_GSM

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_HID), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/HID/src/HID.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_HID

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_KEYBOARD), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Keyboard/src/Keyboard.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_KEYBOARD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_LIQUID_CRYSTAL), yes)
EE_SRCS_ARDUINO_SDK += libraries/LiquidCrystal/src/LiquidCrystal.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_LIQUID_CRYSTAL

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_LUCKY_SHIELD), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/Adafruit_SSD1306.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/BME280.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/CAT9555.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/glcdfont.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/MAG3110.c
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/MMA8491Q.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_LUCKY_SHIELD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_MOUSE), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Keyboard/src/Mouse.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_MOUSE

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_N_AXES_MOTION), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += libraries/NAxesMotion/NAxesMotion.cpp
EE_SRCS_ARDUINO_SDK += libraries/NAxesMotion/utility/BNO055.c
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_N_AXES_MOTION

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_REST), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifneq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
EE_SRCS_ARDUINO_SDK += libraries/Rest/src/rest.cpp
endif	# !OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_REST

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_CONTROL), yes)
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Arduino_LCD.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/ArduinoRobot.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/communication.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Compass.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/EasyTransfer2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/EEPROM_I2C.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Fat16.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/glcdfont.c
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/helper.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/information.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/keyboard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/lcd.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Melody.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Motors.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Multiplexer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/RobotSdCard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/SdCard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Sensors.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Squawk.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/SquawkSD.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/utility/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/utility/RobotTextManager.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/utility/VirtualKeyboard.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_CONTROL

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_MOTOR), yes)
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/ArduinoRobotMotorBoard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/EasyTransfer2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/lineFellow.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/Multiplexer.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_MOTOR

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_IREMOTE), yes)
EE_SRCS_ARDUINO_SDK += libraries/RobotIRemote/src/IRemote.cpp
EE_SRCS_ARDUINO_SDK += libraries/RobotIRemote/src/IRemoteTools.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_IREMOTE

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_RTC), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += libraries/RTC/src/RTCInt.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_RTC

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SCHEDULER), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += libraries/Scheduler/src/Scheduler.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_SCHEDULER

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SD), yes)
EE_SRCS_ARDUINO_SDK += libraries/SD/src/File.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/SD.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/utility/Sd2Card.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/utility/SdFile.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/utility/SdVolume.cpp
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_SD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SERVO), yes)
EE_SRCS_ARDUINO_SDK += libraries/Servo/src/avr/Servo.cpp
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_SERVO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SOFTWARE_SERIAL), yes)
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SoftwareSerial/src/SoftwareSerial.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SoftwareSerial/SoftwareSerial.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_SOFTWARE_SERIAL

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SPI), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SPI/src/SPI.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SPI/SPI.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_SPI

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SPACEBREW_YUN), yes)
EE_SRCS_ARDUINO_SDK += libraries/SpacebrewYun/src/SpacebrewYun.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_SPACEBREW_YUN

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_STEPPER), yes)
EE_SRCS_ARDUINO_SDK += libraries/Stepper/src/Stepper.cpp
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_STEPPER

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TEMBOO), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/Temboo.cpp
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/TembooCoAPEdgeDevice.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/TembooMQTTEdgeDevice.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/BaseFormatter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoInput.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoInputFormatter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoInputSet.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoOutput.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoOutputFormatter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoOutputSet.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoPreset.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoPresetFormatter.cpp
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/CoapMessageLayer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/CoapMsg.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/CoapRRLayer.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/DataFormatter.cpp
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTConnectClient.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTConnectServer.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTDeserializePublish.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTFormat.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTPacket.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTSerializePublish.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTSubscribeClient.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTSubscribeServer.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTUnsubscribeClient.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTUnsubscribeServer.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooCoAPSession.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooGlobal.c
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooMQTTSession.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_CC
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooSession.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/tmbhmac.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/tmbmd5.cpp
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TEMBOO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TFT), yes)
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/TFT.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/utility/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/utility/ST7735.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/utility/glcdfont.c
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TFT

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Timer1/Timer1.cpp
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1_CTC), yes)
#EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Timer1CTC/Timer1CTC.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Timer1CTC/Timer1CTC.c
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1_CTC

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_USB_HOST), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/adk.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/hid2.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/KeyboardController.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/MouseController.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/parsetools.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/Usb.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_USB_HOST

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_WIFI), yes)
ifneq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFi.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFiClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFiServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFiUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/utility/server_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/utility/spi_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/utility/wifi_drv.cpp
endif	# !OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_WIFI

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_WIFI_SHIELD), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFi.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFiClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFiServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFiUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/utility/server_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/utility/spi_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/utility/wifi_drv.cpp
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_WIFI_SHIELD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_WIRE), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/src/Wire.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/src/utility/twi.c
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/Wire.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/utility/twi.c
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_WIRE

endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_SA), yes)

EE_OBJS_ARDUINO_SDK := 							       \
	$(addprefix $(OS_EE_OBJ_DIR)/,					       \
		$(patsubst %.cpp,%.cpp.o,				       \
			$(patsubst %.c,%.c.o,				       \
				$(patsubst %.S,%.S.o,$(EE_SRCS_ARDUINO_SDK))   \
			)						       \
		)							       \
	)

LIBSRCS += $(EE_SRCS_ARDUINO_SDK)

ARDUINO_SDK_LIB := libarduinosdk.a

$(OS_EE_LIB_DIR)/$(ARDUINO_SDK_LIB): $(EE_OBJS_ARDUINO_SDK)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^
	@echo "*******************************************"
	@echo "* Arduino SDK library built successfully! *"
	@echo "*******************************************"

OPT_LIBS += $(OS_EE_LIB_DIR)/$(ARDUINO_SDK_LIB)
ALL_LIBS += $(OS_EE_LIB_DIR)/$(ARDUINO_SDK_LIB)

else	# OS_EE_LIB_ARDUINO_SDK_SA

EE_SRCS += $(EE_SRCS_ARDUINO_SDK)

endif	# OS_EE_LIB_ARDUINO_SDK_SA

endif	# OS_EE_ARCH_AVR8 && OS_EE_ARCH_AVR8_ATMEGA

endif	# OS_EE_LIB_ARDUINO_SDK
