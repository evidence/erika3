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

## \file	ee_arch_compiler_gcc.mk
## \brief	Architecture GCC Compiler.
##
## This makefile contains the list of GCC Compiler Rules for a specific
## Architecture in Erika Enterprise.
##
## \author	Giuseppe Serano
## \date	2016

##
## Compiler related options
##


## AVR Tools GNU GCC compiler

# BINDIR is the directory of assembler, linker, ... distributed with AVR Tools
BINDIR := $(call native_path,$(AVR_TOOLS))/bin

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
#ALLINCPATH += \
#$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call native_path,$d)))
ALLINCPATH += \
$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

ifndef	AVR_GCCPREFIX
AVR_GCCPREFIX = avr
endif

ifndef	EE_OBJDUMP
EE_OBJDUMP = $(BINDIR)/$(AVR_GCCPREFIX)-objdump
endif

# GNUPro compilers
ifndef	EE_LINK
EE_LINK = $(BINDIR)/$(AVR_GCCPREFIX)-gcc
endif

ifndef	OS_EE_AS
OS_EE_AS = $(BINDIR)/$(AVR_GCCPREFIX)-gcc
endif

ifndef	EE_CC
EE_CC = $(BINDIR)/$(AVR_GCCPREFIX)-gcc
endif

ifndef	EE_CXX
EE_CXX = $(BINDIR)/$(AVR_GCCPREFIX)-g++
endif

ifndef	OS_EE_AR
OS_EE_AR := $(BINDIR)/$(AVR_GCCPREFIX)-ar
endif

ifndef	EE_NM
EE_NM = $(BINDIR)/$(AVR_GCCPREFIX)-nm
endif

ifndef	EE_OBJCOPY
EE_OBJCOPY = $(BINDIR)/$(AVR_GCCPREFIX)-objcopy
endif

ifndef	EE_SIZE
EE_SIZE = $(BINDIR)/$(AVR_GCCPREFIX)-size
endif

################################################################################
## OPT_CC are the options for arm compiler invocation			      ##
# -mmcu=atmega128    = generate optimized code for AVR atmega128 processor     #
# -Os                 = select the optimization level			       #
#                     NOTE that -O0 can NOT be used because it not expands     #
#                     inline functions!!!!				       #
# -c                 = compile only (do not link)			       #
# -Wall		   = all compiling warning				       #
# -Winline	         = warn if a function does not expand inline           #
# -finline-functions = make all simple functions inline			       #
##-Wl                =Pass option to the linker avr-ld   		      ##
################################################################################

## OPT_CC are the options for avr compiler invocation
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)
OPT_CC += -c -save-temps=obj
ifeq ($(or	\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),	       \
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))      \
), yes)
OPT_CC += -g
endif
OPT_CC += -Os
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
OPT_CC += -std=gnu11
else	# OS_EE_LIB_ARDUINO_SDK_CC
OPT_CC += -w
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq ($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)
OPT_CC += -ffunction-sections -fdata-sections
else	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
OPT_CC += -fdata-sections -ffunction-sections
endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
ifneq ($(OS_EE_AVR8_MCU),)
OPT_CC += -mmcu=$(OS_EE_AVR8_MCU)
endif	# OS_EE_AVR8_MCU
else	# OS_EE_LIB_ARDUINO_SDK
OPT_CC = -Wall -Winline -w -c
ifeq ($(call iseeopt, __AVR8_GCC_C99__), yes)
OPT_CC += -std=gnu99
else
OPT_CC += -std=c89
endif
ifeq ($(findstring atxmega, $(OS_EE_AVR8_MCU)), atxmega)
OPT_CC += -gdwarf-2 -Os -save-temps=obj
else	# ATXMEGA
#ifeq ($(call iseeopt, DEBUG), yes)
ifeq ($(or	\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),	       \
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))      \
), yes)
OPT_CC += -gdwarf-2
endif
endif	# ATXMEGA
ifneq ($(OS_EE_AVR8_MCU),)
OPT_CC += -fdata-sections -ffunction-sections
OPT_CC += -Werror-implicit-function-declaration -Wmissing-prototypes
OPT_CC += -Wpointer-arith -Wstrict-prototypes -mrelax
OPT_CC += -mmcu=$(OS_EE_AVR8_MCU)
endif	# OS_EE_AVR8_MCU
endif	# OS_EE_LIB_ARDUINO_SDK
# Specific option from the application makefile
OPT_CC += $(CFLAGS)

## OPT_CXX are the options for avr compiler invocation
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)
OPT_CXX += -c -save-temps=obj
ifeq ($(or	\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),	       \
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))      \
), yes)
OPT_CXX += -g
endif
OPT_CXX += -Os
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC), yes)
OPT_CXX += -std=gnu++11
else	# OS_EE_LIB_ARDUINO_SDK_CC
OPT_CXX += -w
endif	# OS_EE_LIB_ARDUINO_SDK_CC
ifeq ($(or	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_CC),	\
		$(call islibopt, OS_EE_LIB_ARDUINO_SDK_ORG)	\
	), yes)
OPT_CXX += -fno-exceptions -ffunction-sections -fdata-sections
OPT_CXX += -fno-threadsafe-statics
else	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
OPT_CXX += -fdata-sections -ffunction-sections -fno-exceptions
endif	# OS_EE_LIB_ARDUINO_SDK_CC && OS_EE_LIB_ARDUINO_SDK_ORG
ifneq ($(OS_EE_AVR8_MCU),)
OPT_CXX += -mmcu=$(OS_EE_AVR8_MCU)
endif	# OS_EE_AVR8_MCU
else	# OS_EE_LIB_ARDUINO_SDK
OPT_CXX = -Wall -Winline -w -c
ifeq ($(call iseeopt, __AVR8_GCC_C99__), yes)
OPT_CXX += -std=gnu99
else
OPT_CXX += -std=c89
endif
#ifeq ($(call iseeopt, DEBUG), yes)
ifeq ($(or	\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),	       \
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))      \
), yes)
OPT_CXX += -gdwarf-2
endif
OPT_CXX += -fdata-sections -ffunction-sections
OPT_CXX += -Werror-implicit-function-declaration
OPT_CXX += -Wpointer-arith -mrelax
OPT_CXX += -mmcu=$(OS_EE_AVR8_MCU)
endif	# OS_EE_LIB_ARDUINO_SDK
# Specific option from the application makefile
OPT_CXX += $(CFLAGS) $(CXXFLAGS)

## OS_EE_AS_OPT are the options for avr assembler invocation
# --gdwarf2     = generate dwarf2 debbugging information for each assembler line
## -x assembler-with-cpp -gdwarf2
OS_EE_AS_OPT = -c -x assembler-with-cpp -save-temps=obj
ifneq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)
ifeq ($(call iseeopt, __AVR8_GCC_C99__), yes)
OS_EE_AS_OPT += -std=gnu99
else
OS_EE_AS_OPT += -std=c89
endif
endif	# !OS_EE_LIB_ARDUINO_SDK
ifneq ($(OS_EE_AVR8_MCU),)
OS_EE_AS_OPT += -mrelax
ifeq ($(findstring atxmega, $(OS_EE_AVR8_MCU)), atxmega)
OS_EE_AS_OPT += -Wa,-gdwarf2
else	# ATXMEGA
#ifeq ($(call iseeopt, DEBUG), yes)
ifeq ($(or	\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),	       \
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))      \
), yes)
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)
OS_EE_AS_OPT += -g
else	# OS_EE_LIB_ARDUINO_SDK
OS_EE_AS_OPT += -Wa,-gdwarf2
endif	# OS_EE_LIB_ARDUINO_SDK
endif	# DEBUG
endif	# ATXMEGA
OS_EE_AS_OPT += -mmcu=$(OS_EE_AVR8_MCU)
endif	# OS_EE_AVR8_MCU
# Specific option from the application makefile
OS_EE_AS_OPT += $(ASFLAGS)

# OS_EE_AR_OPT represents the options for avr linker invocation
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_AR_OPT = $(subst $(OS_EE_SPACE),,csv $(subst v,,$(ARFLAGS)))
else	# OS_EE_VERBOSE
OS_EE_AR_OPT = $(subst v,,$(subst $(OS_EE_SPACE),,cs $(ARFLAGS)))
endif	# OS_EE_VERBOSE

# OPT_LINK represents the options for avr linker invocation
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)
OPT_LINK += -Os -Wl,--gc-sections
ifneq ($(OS_EE_AVR8_MCU),)
OPT_LINK += -mmcu=$(OS_EE_AVR8_MCU)
endif	# OS_EE_AVR8_MCU
else	# OS_EE_LIB_ARDUINO_SDK
OPT_LINK = $(LDFLAGS)
ifneq ($(OS_EE_AVR8_MCU),)
OPT_LINK += -Wl,--start-group -Wl,--end-group -Wl,--gc-sections
OPT_LINK += -mrelax -Wl,--relax
ifeq ($(findstring atxmega, $(OS_EE_AVR8_MCU)), atxmega)
OPT_LINK += -Wl,--section-start=.BOOT=0x4000
endif	# ATXMEGA
OPT_LINK += -mmcu=$(OS_EE_AVR8_MCU)
endif	# OS_EE_AVR8_MCU
endif	# OS_EE_LIB_ARDUINO_SDK

# Defining OS_EE_OPT Macros
# Each identifier that is listed in OS_EE_OPT is also inserted as a 
# command-line macro in the compiler...

#OS_EE_DEFS_AS = $(addprefix -D,$(OS_EE_OPT))
#OS_EE_DEFS_CC  = $(addprefix -D,$(OS_EE_OPT))
#OS_EE_DEFS_CXX  = $(addprefix -D,$(OS_EE_OPT))
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_DEFS_AS	+= -DOS_EE_BUILD
OS_EE_DEFS_CC	+= -DOS_EE_BUILD
OS_EE_DEFS_CXX	+= -DOS_EE_BUILD
endif

# Automatic dependency generation
ifeq ($(call iseeopt, OS_EE_NO_DEPS), yes)
OS_EE_DEP_OPT =
OS_EE_MK_DEPS =
else	# OS_EE_NO_DEPS
# Create dependency for all headers, and add a target for each header
OS_EE_DEP_OPT = -MP -MMD -MF $(call native_path,$(subst .o,.d_tmp,$(@)))
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
# Dependencies on Windows need path translation and quote remotion
OS_EE_MK_DEPS = sed -e 's_\\\(.\)\(.\)_/\1\2_g' \
	-e 's_\<\([a-zA-Z]\):/_/cygdrive/\l\1/_g' < $1_tmp > $1 && rm $1_tmp
else	# OS_EE_RTD_BUILD_ENV_CYGWIN
OS_EE_MK_DEPS = mv $1_tmp $1
endif	# OS_EE_RTD_BUILD_ENV_CYGWIN
endif	# OS_EE_NO_DEPS

# Erika Library.
ERIKALIB = $(ERIKALIB_NAME).a

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
# the EE library is built in the current directory
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OPT_LIBS += -l$(EELIB) -L .
LIBDEP += lib/$(ERIKALIB)
else	# OS_EE_BUILD
OS_EE_OPT_LIBS = -L $(call short_native_path,$(abspath $(OS_EE_LIB_BASE_DIR))) \
-L . -Wl,--start-group $(OPT_LIBS) -l$(EELIB) -Wl,--end-group
LIBDEP += $(OS_EE_LIB_BASE_DIR)/lib$(EELIB).a
endif	# OS_EE_BUILD

# Define the TARGET
ifeq ($(findstring atxmega, $(OS_EE_AVR8_MCU)), atxmega)
TARGET_NAME := $(OS_EE_AVR8_MCU)
else	# ATXMEGA
ifeq ($(call islibopt, OS_EE_LIB_ARDUINO_SDK), yes)
TARGET_NAME := arduino
else	# OS_EE_LIB_ARDUINO_SDK
TARGET_NAME := avr
endif	# OS_EE_LIB_ARDUINO_SDK
endif	# ATXMEGA

# Add application file to dependencies
ifneq ($(call iseeopt, OS_EE_BUILD), yes)
export APP_TARGETS := 	$(TARGET_NAME).eep \
			$(TARGET_NAME).hex \
			$(TARGET_NAME).lss \
			$(TARGET_NAME).srec
$(info APP_TARGETS=$(APP_TARGETS))
endif	# !OS_EE_BUILD
