# ###*B*###
# Erika Enterprise, version 3
# 
# Copyright (C) 2017 - 2018 Evidence s.r.l.
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
# < www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
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

## \file    ee_arch_compiler_gcc.mk
## \brief   Architecture GCC Compiler.
##
## This makefile contains the list of GCC Compiler varialiables for a specific
## Architecture in Erika Enterprise.
##
## \author  Errico Guidieri
## \date    2017

##
## Compiler related options
##

# BINDIR variable, (if not empty), must end with separator
BINDIR ?=

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
ALLINCPATH += $(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

TRICORE_GCCPREFIX ?= tricore-

EE_OBJDUMP ?= $(BINDIR)$(TRICORE_GCCPREFIX)objdump

# GNUPro compilers
EE_LINK ?= $(BINDIR)$(TRICORE_GCCPREFIX)gcc

OS_EE_AS ?= $(BINDIR)$(TRICORE_GCCPREFIX)gcc

EE_CC ?= $(BINDIR)$(TRICORE_GCCPREFIX)gcc

EE_CXX ?= $(BINDIR)$(TRICORE_GCCPREFIX)g++

OS_EE_AR ?= $(BINDIR)$(TRICORE_GCCPREFIX)ar

EE_NM ?= $(BINDIR)$(TRICORE_GCCPREFIX)nm

EE_OBJCOPY ?= $(BINDIR)$(TRICORE_GCCPREFIX)objcopy

EE_SIZE ?= $(BINDIR)$(TRICORE_GCCPREFIX)size

## OPT_CC are the options for TriCore C compiler invocation
#-ffunction-sections -fdata-sections
# -fno-strict-aliasing
ifeq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_CC += -c -Wall -Wextra $(OPT_CPU)
else	# OS_EE_GCC_MINIMAL_OPTS
OPT_CC += -c -Wall -Wextra $(OPT_CPU) -Wstrict-prototypes\
 -Wtype-limits -Wmissing-declarations -Wmissing-prototypes\
 -Wdiv-by-zero -Wdouble-promotion -Wcast-align -Wformat-security\
 -Wignored-qualifiers\
 -fno-common -fshort-enums -fstrict-volatile-bitfields -finline-functions\
 -fzero-initialized-in-bss
endif	# OS_EE_GCC_MINIMAL_OPTS

ifeq ($(or\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),\
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))\
), yes)
OPT_CC += -g -O1 -save-temps=obj
else
#-fomit-frame-pointer
OPT_CC += -g -Os -save-temps=obj
endif

# Specific option from the application makefile
OPT_CC += $(CFLAGS)

## OPT_CXX are the options for TriCore C++ compiler invocation
ifeq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_CXX += -c -Wall -Wextra $(OPT_CPU)
else	# OS_EE_GCC_MINIMAL_OPTS
OPT_CXX += -c -Wall -Wextra $(OPT_CPU) -Wstrict-prototypes\
 -Wtype-limits -Wmissing-declarations -Wmissing-prototypes\
 -Wdiv-by-zero -Wdouble-promotion -Wcast-align -Wformat-security\
 -Wignored-qualifiers\
 -fno-common -fshort-enums -fstrict-volatile-bitfields -finline-functions\
 -fzero-initialized-in-bss
endif	# OS_EE_GCC_MINIMAL_OPTS

ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)), \
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG)) \
), yes)
OPT_CXX += -g -O1 -save-temps=obj
else
#-fomit-frame-pointer
OPT_CXX += -g -Os -save-temps=obj
endif

# Specific option from the application makefile
OPT_CXX += $(CFLAGS) $(CXXFLAGS)

## OS_EE_AS_OPT are the options for TriCore assembler invocation
OS_EE_AS_OPT = -Wall -Wextra $(OPT_CPU)

ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)), \
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG)) \
), yes)
OS_EE_AS_OPT += -g -O1 -save-temps=obj -Wa,--gdwarf2
else
OS_EE_AS_OPT += -g -Os -save-temps=obj -Wa,--gdwarf2
endif

OS_EE_AS_OPT += $(ASFLAGS)

# OS_EE_AR_OPT represents the options for archiver invocation
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_AR_OPT = $(subst $(OS_EE_SPACE),,csv $(subst v,,$(ARFLAGS)))
else	# OS_EE_VERBOSE
OS_EE_AR_OPT = $(subst v,,$(subst $(OS_EE_SPACE),,cs $(ARFLAGS)))
endif	# OS_EE_VERBOSE

# Handle special case of TC39X family A-Step revision
ifeq ($(OSEE_TRICORE_MCU), tc39x)
ifeq (${OSEE_TRICORE_STEP}, AA)
OPT_LINK_EXTRA=-Wl,--defsym=__DSPR0_SIZE=96k -Wl,--defsym=__DSPR1_SIZE=96k
endif #OSEE_TRICORE_STEP AA
endif #OSEE_TRICORE_MCU tc39x

ifeq ($(call iseeopt, OSEE_TC_LINK_BMHD), yes)
ifneq ($(call iseeopt, OSEE_TC_2G), yes)
SYMBOLS_FORCED_TO_BE_LINK += osEE_tc_bmhd_0 osEE_tc_bmhd_1
else
SYMBOLS_FORCED_TO_BE_LINK += osEE_tc_bmhd_0_orig osEE_tc_bmhd_1_orig\
 osEE_tc_bmhd_2_orig osEE_tc_bmhd_3_orig osEE_tc_bmhd_4_orig
SYMBOLS_FORCED_TO_BE_LINK += osEE_tc_bmhd_0_copy osEE_tc_bmhd_1_copy\
 osEE_tc_bmhd_2_copy osEE_tc_bmhd_3_copy osEE_tc_bmhd_4_copy
endif #!OSEE_TC_2G
endif #OSEE_TC_LINK_BMHD
# Added EXTERN directive to all linker scripts for this
#SYMBOLS_FORCED_TO_BE_LINK += __TRICORE_DERIVATE_NAME__
ifneq ($(SYMBOLS_FORCED_TO_BE_LINK),)
# Used in the following addprefix, without this variable the prefix will be
# split because the comma
COMMA=,
OPT_UNDEFINED := $(addprefix -Wl$(COMMA)--undefined=, $(SYMBOLS_FORCED_TO_BE_LINK))
endif

# OPT_LINK represents the options for HighTec GCC linker invocation
OSEE_LINKER_SCRIPT ?= $(call short_native_path,$(abspath $(OS_EE_MK_BASE_DIR)/ee_tc_gcc_flash.ld))
ifeq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_LINK += $(OPT_CPU) -T $(OSEE_LINKER_SCRIPT) -nostartfiles -Wl,-Map=$(TARGET_NAME).map $(OPT_UNDEFINED) $(OPT_LINK_EXTRA)
else	# OS_EE_GCC_MINIMAL_OPTS
OPT_LINK += $(OPT_CPU) -T $(OSEE_LINKER_SCRIPT) -nostartfiles -Wl,--gc-sections -Wl,-Map=$(TARGET_NAME).map $(OPT_UNDEFINED) $(OPT_LINK_EXTRA)
endif	# OS_EE_GCC_MINIMAL_OPTS

OPT_LINK += $(LDFLAGS)

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
# the EE library is built in the current directory
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OPT_LIBS += -l$(EELIB) -L .
LIBDEP += lib/$(ERIKALIB)
else	# OS_EE_BUILD
OPT_LIBS += -L $(call short_native_path,$(abspath $(OS_EE_LIB_BASE_DIR)))
#OPT_LIBS += --start-group -l$(EELIB) -l:lib.a --end-group
OPT_LIBS += -l$(EELIB)
LIBDEP += $(OS_EE_LIB_BASE_DIR)/$(ERIKALIB)
endif	# OS_EE_BUILD

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_DEFS_AS   += -DOS_EE_BUILD
OS_EE_DEFS_CC   += -DOS_EE_BUILD
OS_EE_DEFS_CXX  += -DOS_EE_BUILD
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

# Define the TARGET
TARGET_NAME ?= erika3app

# Add application file to dependencies
ifneq ($(call iseeopt, OS_EE_BUILD), yes)
#export APP_TARGETS := $(TARGET_NAME).bin $(TARGET_NAME).dump
export APP_TARGETS := $(TARGET_NAME).dump
$(info APP_TARGETS=$(APP_TARGETS))
endif	# !OS_EE_BUILD
