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

## \file	ee_arduino_linkcfg.mk
## \brief	Arduino SDK Link Configuration.
##
## This makefile contains the rules to integrate Arduino SDK stand-alone library
## in an Erika Enterprise Application.
##
## \author	Giuseppe Serano
## \date	2016

## Check the Arduino library selection
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)

ifeq	($(and	\
		$(call iseeopt, OS_EE_ARCH_AVR8),	\
		$(call iseeopt, OS_EE_ARCH_AVR8_ATMEGA)	\
	), yes)

ifndef	ARDUINO_SDK_FILES
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_8_5), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.8.5
else	# OS_EE_LIB_ARDUINO_SDK_CC_1_8_5
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_6_10), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.6.10
else	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_10
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_6_9), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.6.9
else	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_9
export	ARDUINO_SDK_FILES = C:/arduino-1.6.8
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_9
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_10
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_8_5
else	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.7.10
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.7.9
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
export	ARDUINO_SDK_FILES = C:/arduino-1.7.8
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
else	# OS_EE_LIB_ARDUINO_SDK_ORG
export	ARDUINO_SDK_FILES = C:/arduino-1.0.5-r2
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_CC
endif	# ARDUINO_SDK_FILES

ARDUINO_SDK_ROOT := $(call short_native_path, $(ARDUINO_SDK_FILES))

EE_VPATH += $(ARDUINO_SDK_ROOT)

ifeq	($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_8_5), yes)
#OS_EE_OPT += ARDUINO=10805
OS_EE_DEFS_AS	+= -DARDUINO=10805
OS_EE_DEFS_CC	+= -DARDUINO=10805
OS_EE_DEFS_CXX	+= -DARDUINO=10805
else	# OS_EE_LIB_ARDUINO_SDK_CC_1_8_5
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_6_10), yes)
#OS_EE_OPT += ARDUINO=10610
OS_EE_DEFS_AS	+= -DARDUINO=10610
OS_EE_DEFS_CC	+= -DARDUINO=10610
OS_EE_DEFS_CXX	+= -DARDUINO=10610
else	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_10
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC_1_6_9), yes)
#OS_EE_OPT += ARDUINO=10609
OS_EE_DEFS_AS	+= -DARDUINO=10609
OS_EE_DEFS_CC	+= -DARDUINO=10609
OS_EE_DEFS_CXX	+= -DARDUINO=10609
else	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_9
#OS_EE_OPT += ARDUINO=10608
OS_EE_DEFS_AS	+= -DARDUINO=10608
OS_EE_DEFS_CC	+= -DARDUINO=10608
OS_EE_DEFS_CXX	+= -DARDUINO=10608
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_9
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_6_10
endif	# OS_EE_LIB_ARDUINO_SDK_CC_1_8_5
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
#OS_EE_OPT += ARDUINO=10710
OS_EE_DEFS_AS	+= -DARDUINO=10710
OS_EE_DEFS_CC	+= -DARDUINO=10710
OS_EE_DEFS_CXX	+= -DARDUINO=10710
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
#OS_EE_OPT += ARDUINO=10709
OS_EE_DEFS_AS	+= -DARDUINO=10709
OS_EE_DEFS_CC	+= -DARDUINO=10709
OS_EE_DEFS_CXX	+= -DARDUINO=10709
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
#OS_EE_OPT += ARDUINO=10708
OS_EE_DEFS_AS	+= -DARDUINO=10708
OS_EE_DEFS_CC	+= -DARDUINO=10708
OS_EE_DEFS_CXX	+= -DARDUINO=10708
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_UNO_328),yes)
#OS_EE_OPT += ARDUINO_AVR_UNO
OS_EE_DEFS_AS	+= -DARDUINO_AVR_UNO
OS_EE_DEFS_CC	+= -DARDUINO_AVR_UNO
OS_EE_DEFS_CXX	+= -DARDUINO_AVR_UNO
endif	# OS_EE_LIB_ARDUINO_UNO_328
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_NANO_328),yes)
#OS_EE_OPT += ARDUINO_AVR_NANO
OS_EE_DEFS_AS	+= -DARDUINO_AVR_NANO
OS_EE_DEFS_CC	+= -DARDUINO_AVR_NANO
OS_EE_DEFS_CXX	+= -DARDUINO_AVR_NANO
endif	# OS_EE_LIB_ARDUINO_NANO_328
#OS_EE_OPT += ARDUINO_ARCH_AVR
OS_EE_DEFS_AS	+= -DARDUINO_ARCH_AVR
OS_EE_DEFS_CC	+= -DARDUINO_ARCH_AVR
OS_EE_DEFS_CXX	+= -DARDUINO_ARCH_AVR
endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG

##
## Add the inc path to the include pathlist
## New include mechanism

ifeq	($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/cores/arduino	\
		$(INCLUDE_PATH)
else	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/cores/arduino	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_UNO_328), yes)
ifeq	($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/variants/standard	\
		$(INCLUDE_PATH)
else	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/variants/standard	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_UNO_328

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_NANO_328), yes)
ifeq ($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)
INCLUDE_PATH :=	\
	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/variants/eightanaloginputs	\
	$(INCLUDE_PATH)
else	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
INCLUDE_PATH :=	\
	$(ARDUINO_SDK_ROOT)/hardware/arduino/variants/eightanaloginputs	\
	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_NANO_328

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_SIMUL), yes)
#OS_EE_OPT += F_CPU=1000000UL
OS_EE_DEFS_AS	+= -DF_CPU=1000000UL
OS_EE_DEFS_CC		+= -DF_CPU=1000000UL
OS_EE_DEFS_CXX	+= -DF_CPU=1000000UL
else
#OS_EE_OPT += F_CPU=16000000UL
OS_EE_DEFS_AS	+= -DF_CPU=16000000UL
OS_EE_DEFS_CC		+= -DF_CPU=16000000UL
OS_EE_DEFS_CXX	+= -DF_CPU=16000000UL
endif

ifeq	($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ARDUINO_WIFI), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/ArduinoWiFi/src		\
		$(ARDUINO_SDK_ROOT)/libraries/ArduinoWiFi/src/lib	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ARDUINO_WIFI

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_BRACCIO), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Braccio/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_BRACCIO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_BRIDGE), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Bridge/src \
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_BRIDGE

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_CIAO), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ciao/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ciao/src/lib	\
		$(INCLUDE_PATH)
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ciao/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ciao/src/lib	\
		$(INCLUDE_PATH)
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ciao/src		\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_CIAO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_EEPROM), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/EEPROM/src \
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/EEPROM \
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_EEPROM

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ESPLORA), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Esplora/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ESPLORA

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ethernet/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ethernet/src/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET2), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ethernet2/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ethernet2/src/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ETHERNET2

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_FIRMATA), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Firmata		\
		$(ARDUINO_SDK_ROOT)/libraries/Firmata/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Firmata		\
		$(ARDUINO_SDK_ROOT)/libraries/Firmata/utility	\
		$(INCLUDE_PATH)
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Firmata/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_FIRMATA

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_GSM), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/GSM/src		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/GSM/src \
		$(INCLUDE_PATH)
else	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/GSM/src \
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_GSM

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_HID), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/HID/src \
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_HID

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_KEYBOARD), yes)
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Keyboard/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_KEYBOARD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_LIQUID_CRYSTAL), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/LiquidCrystal/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_LIQUID_CRYSTAL

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_LUCKY_SHIELD), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/LuckyShield/src		\
		$(ARDUINO_SDK_ROOT)/libraries/LuckyShield/src/lib	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_9
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_LUCKY_SHIELD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_MOUSE), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Mouse/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_MOUSE

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_N_AXES_MOTION), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/NAxesMotion/		\
		$(ARDUINO_SDK_ROOT)/libraries/NAxesMotion/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_N_AXES_MOTION

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_REST), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
ifneq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Rest/src		$(INCLUDE_PATH)
endif	# !OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_REST

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_CONTROL), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Robot_Control/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Robot_Control/src/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_CONTROL

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_MOTOR), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Robot_Motor/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_MOTOR

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_IREMOTE), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/RobotIRemote/src	$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_ROBOT_IREMOTE

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_RTC), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/RTC/src		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_RTC

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SCHEDULER), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Scheduler/src		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_SCHEDULER

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SD), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/SD/src		\
		$(ARDUINO_SDK_ROOT)/libraries/SD/src/utility	\
		$(INCLUDE_PATH)
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_SD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SERVO), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Servo/src \
		$(ARDUINO_SDK_ROOT)/libraries/Servo/src/avr \
		$(INCLUDE_PATH)
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_SERVO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SOFTWARE_SERIAL), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SoftwareSerial/src	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SoftwareSerial	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_SOFTWARE_SERIAL
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SPI), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SPI/src	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SPI	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_SPI

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_SPACEBREW_YUN), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/SpacebrewYun/src	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_SPACEBREW_YUN

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_STEPPER), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Stepper/src	$(INCLUDE_PATH)
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_STEPPER
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TEMBOO), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Temboo/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Temboo/src/utility	\
		$(INCLUDE_PATH)
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TEMBOO

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TFT), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/TFT/src		\
		$(ARDUINO_SDK_ROOT)/libraries/TFT/src/utility	\
		$(INCLUDE_PATH)
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TFT

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Timer1 \
		$(INCLUDE_PATH)
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1_CTC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Timer1CTC \
		$(INCLUDE_PATH)
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_TIMER1_CTC

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_USB_HOST), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/USBHost/src	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	#OS_EE_LIB_ARDUINO_SDK_LIB_USB_HOST

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_WIFI), yes)
ifneq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/WiFi/src		\
		$(ARDUINO_SDK_ROOT)/libraries/WiFi/src/utility	\
		$(INCLUDE_PATH)
endif	# !OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_WIFI

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_WIFI_SHIELD), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/WiFiShield/src		\
		$(ARDUINO_SDK_ROOT)/libraries/WiFiShiled/src/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG_1_7_10
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_WIFI_SHIELD

ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_LIB_WIRE), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire/src		\
		$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire/src/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire		\
		$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire/utility	\
		$(INCLUDE_PATH)
endif	# OS_EE_LIB_ARDUINO_SDK_ORG
endif	# OS_EE_LIB_ARDUINO_SDK_LIB_WIRE

endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG

ifneq	($(if $(filter OS_EE_BUILD,$(OS_EE_OPT)),yes,), yes)
ifeq	($(call islibopt, OS_EE_LIB_ARDUINO_SDK_SA), yes)
ARDUINOSDKLIB = arduinosdk
ARDUINO_SDK_LIB := lib$(ARDUINOSDKLIB).a

OPT_LIBS += -l$(ARDUINOSDKLIB)
ALL_LIBS += $(OS_EE_LIB_BASE_DIR)/$(ARDUINO_SDK_LIB)
endif	# OS_EE_LIB_ARDUINO_SDK_SA
endif	# !OS_EE_BUILD

endif	# OS_EE_ARCH_AVR8 && OS_EE_ARCH_AVR8_ATMEGA

endif	# OS_EE_LIB_ARDUINO_SDK
