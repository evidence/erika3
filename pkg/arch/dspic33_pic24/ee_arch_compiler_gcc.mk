# ###*B*###
# Erika Enterprise, version 3
# 
# Copyright (C) 2018 Evidence s.r.l.
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
## \brief	MPLAB XC16 C Compiler.
##
## This makefile contains the list of MPLAB XC16 C Compiler Rules for a specific
## Architecture in Erika Enterprise.
##
## \author	Giuseppe Serano
## \date	2018

##
## Compiler related options
##


## MPLAB XC16 Tools C compiler

# BINDIR is the directory of assembler, linker, ... distributed with MPLAB XC16
# C compiler.
BINDIR := $(call native_path,$(XC16_TOOLS))/bin

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
#ALLINCPATH += \
#$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call native_path,$d)))
ALLINCPATH += \
$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

##
## Toolchain Commands
##

ifndef	XC16_PREFIX
XC16_PREFIX = xc16
endif

ifndef	OS_EE_CC
OS_EE_CC = $(BINDIR)/$(XC16_PREFIX)-gcc
endif

ifndef	OS_EE_AS
OS_EE_AS = $(BINDIR)/$(XC16_PREFIX)-gcc
endif

ifndef	OS_EE_AR
OS_EE_AR := $(BINDIR)/$(XC16_PREFIX)-ar
endif

ifndef	OS_EE_LINK
OS_EE_LINK = $(BINDIR)/$(XC16_PREFIX)-gcc
endif

ifndef	OS_EE_BIN2HEX
OS_EE_BIN2HEX = $(BINDIR)/$(XC16_PREFIX)-bin2hex
endif

# OS_EE_APPL_BUILD work-around!
ifneq ($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_OPT += OS_EE_APPL_BUILD
endif

################################################################################
## OS_EE_OPT_CC are the options for C compiler invocation			      ##
################################################################################
OS_EE_OPT_CC = -c

ifeq ($(call iseeopt, OS_EE_ARCH_DSPIC33_PIC24), yes)
OS_EE_OPT_CC += -mcpu=$(OS_EE_DSPIC33_PIC24_MCU)
endif	# OS_EE_ARCH_DSPIC33_PIC24

ifneq ($(call iseeopt, OS_EE_GCC_XC16_MINIMAL_OPTS), yes)
OS_EE_OPT_CC += -Wall -Wextra -save-temps=obj
OS_EE_OPT_CC += -ffunction-sections
#[GS]: -fdata-sections disabled (T.B.C.)
#OS_EE_OPT_CC += -fdata-sections
endif	# OS_EE_GCC_XC16_MINIMAL_OPTS

ifeq ($(or	\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),     \
  $(and 								       \
	$(call iseeopt, OS_EE_APPL_BUILD),				       \
	$(call iseeopt, OS_EE_APPL_BUILD_DEBUG)				       \
  )									       \
), yes)
OS_EE_OPT_CC += -g -O0
else
OS_EE_OPT_CC += -O1
endif

# Specific option from the application makefile
OS_EE_OPT_CC += $(CFLAGS)

################################################################################
## OS_EE_OPT_AS are the options for assembler invocation		      ##
################################################################################
OS_EE_OPT_AS = -c -x assembler-with-cpp

ifeq ($(call iseeopt, OS_EE_ARCH_DSPIC33_PIC24), yes)
OS_EE_OPT_AS += -mcpu=$(OS_EE_DSPIC33_PIC24_MCU)
endif	# OS_EE_ARCH_DSPIC33_PIC24

ifneq ($(call iseeopt, OS_EE_GCC_XC16_MINIMAL_OPTS), yes)
OS_EE_OPT_AS += -save-temps=obj
OS_EE_OPT_AS += -ffunction-sections
#[GS]: -fdata-sections disabled (T.B.C.)
#OS_EE_OPT_AS += -fdata-sections
endif	# OS_EE_GCC_XC16_MINIMAL_OPTS

ifeq ($(or	\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),     \
  $(and 								       \
	$(call iseeopt, OS_EE_APPL_BUILD),				       \
	$(call iseeopt, OS_EE_APPL_BUILD_DEBUG)				       \
  )									       \
), yes)
OS_EE_OPT_AS += -Wa,-g -O0
else
OS_EE_OPT_AS += -O1
endif

# Specific option from the application makefile
OS_EE_OPT_AS += $(ASFLAGS)

################################################################################
## OS_EE_OPT_AR are the options for librarian invocation		      ##
################################################################################
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_OPT_AR = $(subst $(OS_EE_SPACE),,csv $(subst v,,$(ARFLAGS)))
else	# OS_EE_VERBOSE
OS_EE_OPT_AR = $(subst v,,$(subst $(OS_EE_SPACE),,cs $(ARFLAGS)))
endif	# OS_EE_VERBOSE

################################################################################
## OS_EE_OPT_LINK are the options for linker invocation			      ##
################################################################################
OS_EE_OPT_LINK = -omf=elf

ifneq ($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OS_EE_OPT_LINK += -Wl,--gc-sections
endif	# OS_EE_GCC_MINIMAL_OPTS
OS_EE_OPT_LINK += -Wl,--script=p$(OS_EE_DSPIC33_PIC24_MCU).gld
OS_EE_OPT_LINK += -Wl,--Map="$(OS_EE_DSPIC33_PIC24_MCU).map"
OS_EE_OPT_LINK += -Wl,--cref
OS_EE_OPT_LINK += -Wl,--stackguard=2
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_OPT_LINK += -Wl,--report-mem
endif	# OS_EE_VERBOSE

# Specific option from the application makefile
OS_EE_OPT_LINK += $(LDFLAGS)

################################################################################
## OS_EE_OPT_BIN2HEX are the options for binarian invocation		      ##
################################################################################
OS_EE_OPT_BIN2HEX = -a -omf=elf

# Defining OS_EE_OPT Macros
# Each identifier that is listed in OS_EE_OPT is also inserted as a 
# command-line macro in the compiler...

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
## the EE library is built in the current directory
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OPT_LIBS += -l$(EELIB) -L .
LIBDEP += lib/$(ERIKALIB)
else	# OS_EE_BUILD
OS_EE_OPT_LIBS = -L"$(call short_native_path,$(abspath $(OS_EE_LIB_BASE_DIR)))"
OS_EE_OPT_LIBS += -L. -Wl,--start-group $(OPT_LIBS) -l$(EELIB) -Wl,--end-group
LIBDEP += $(OS_EE_LIB_BASE_DIR)/lib$(EELIB).a
endif	# OS_EE_BUILD

# Define the TARGET
TARGET_NAME := erika3app

# Add application file to dependencies
ifneq ($(call iseeopt, OS_EE_BUILD), yes)
export APP_TARGETS := 	$(TARGET_NAME).hex
endif	# !OS_EE_BUILD
