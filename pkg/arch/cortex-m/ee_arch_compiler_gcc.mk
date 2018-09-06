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

## \file	ee_arch_compiler_gcc.mk
## \brief	ARM GNU GCC Compiler.
##
## This makefile contains the list of ARM GNU GCC Compiler Rules for a specific
## Architecture in Erika Enterprise.
##
## \author	Giuseppe Serano
## \date	2018

##
## Compiler related options
##


## ARM Tools GNU GCC compiler

# BINDIR is the directory of assembler, linker, ... distributed with ARM Tools
BINDIR := $(call native_path,$(ARM_TOOLS))/bin

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
ALLINCPATH += \
$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

ifndef	ARM_GCCPREFIX
ARM_GCCPREFIX = arm-none-eabi
endif

ifndef	EE_OBJDUMP
EE_OBJDUMP = $(BINDIR)/$(ARM_GCCPREFIX)-objdump
endif

# GNUPro compilers
ifndef	EE_LINK
EE_LINK = $(BINDIR)/$(ARM_GCCPREFIX)-gcc
endif

ifndef	OS_EE_AS
OS_EE_AS = $(BINDIR)/$(ARM_GCCPREFIX)-gcc
endif

ifndef	EE_CC
EE_CC = $(BINDIR)/$(ARM_GCCPREFIX)-gcc
endif

ifndef	EE_CXX
EE_CXX = $(BINDIR)/$(ARM_GCCPREFIX)-g++
endif

ifndef	OS_EE_AR
OS_EE_AR := $(BINDIR)/$(ARM_GCCPREFIX)-ar
endif

ifndef	EE_NM
EE_NM = $(BINDIR)/$(ARM_GCCPREFIX)-nm
endif

ifndef	EE_OBJCOPY
EE_OBJCOPY = $(BINDIR)/$(ARM_GCCPREFIX)-objcopy
endif

ifndef	EE_SIZE
EE_SIZE = $(BINDIR)/$(ARM_GCCPREFIX)-size
endif

# OS_EE_APPL_BUILD work-around!
ifneq	($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_OPT += OS_EE_APPL_BUILD
endif

################################################################################
## OPT_CC are the options for arm C compiler invocation			      ##
################################################################################
OPT_CC = -c -mthumb -mthumb-interwork
OPT_CC += -mapcs -fno-common -ffreestanding -fno-builtin -fno-exceptions
# GS: FPU Support
ifneq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU), yes)
OPT_CC += -mfloat-abi=soft
else	# OS_EE_ARCH_CORTEX_M_M4F_FPU
OPT_CC += -mfloat-abi=hard -mfpu=fpv4-sp-d16
endif	# OS_EE_ARCH_CORTEX_M_M4F_FPU

ifeq	($(or							\
  $(call iseeopt, OS_EE_ARCH_CORTEX_M_M4),			\
  $(or								\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F),		\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU)		\
  )								\
), yes)
OPT_CC += -mcpu=cortex-m4
endif	#
	# OS_EE_ARCH_CORTEX_M_M4	||
	# OS_EE_ARCH_CORTEX_M_M4F	||
	# OS_EE_ARCH_CORTEX_M_M4F_FPU
	#

ifneq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_CC += -Wextra -save-temps=obj -std=gnu99
endif	# OS_EE_GCC_MINIMAL_OPTS

ifeq	($(or	\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),     \
  $(and 								       \
	$(call iseeopt, OS_EE_APPL_BUILD),				       \
	$(call iseeopt, OS_EE_APPL_BUILD_DEBUG)				       \
  )									       \
), yes)
OPT_CC += -ggdb -Og
endif

ifneq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_CC += -fdata-sections -ffunction-sections
endif	# OS_EE_CORTEX_M_MCU

# Specific option from the application makefile
OPT_CC += $(CFLAGS)

################################################################################
## OPT_CXX are the options for arm C++ compiler invocation		      ##
################################################################################
OPT_CXX = -c -mthumb -mthumb-interwork

# GS: FPU Support
ifneq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU), yes)
OPT_CXX += -mfloat-abi=soft
else	# OS_EE_ARCH_CORTEX_M_M4F_FPU
OPT_CXX += -mfloat-abi=hard -mfpu=fpv4-sp-d16
endif	# OS_EE_ARCH_CORTEX_M_M4F_FPU

ifeq	($(or							\
  $(call iseeopt, OS_EE_ARCH_CORTEX_M_M4),			\
  $(or								\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F),		\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU)		\
  )								\
), yes)
OPT_CXX += -mcpu=cortex-m4
endif	#
	# OS_EE_ARCH_CORTEX_M_M4	||
	# OS_EE_ARCH_CORTEX_M_M4F	||
	# OS_EE_ARCH_CORTEX_M_M4F_FPU
	#

ifneq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_CXX += -Wextra -save-temps=obj -std=gnu++11
endif	# OS_EE_GCC_MINIMAL_OPTS

ifeq	($(or	\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),     \
  $(and 								       \
	$(call iseeopt, OS_EE_APPL_BUILD),				       \
	$(call iseeopt, OS_EE_APPL_BUILD_DEBUG)				       \
  )									       \
), yes)
OPT_CXX += -ggdb -Og
endif

ifneq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_CXX += -fdata-sections -ffunction-sections
endif	# OS_EE_CORTEX_M_MCU

OPT_CXX += $(CFLAGS) $(CXXFLAGS)

################################################################################
## OS_EE_AS_OPT are the options for arm assembler invocation		      ##
################################################################################
OS_EE_AS_OPT = -c -x assembler-with-cpp -mthumb -mthumb-interwork

# GS: FPU Support
ifneq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU), yes)
OS_EE_AS_OPT += -mfloat-abi=soft
else	# OS_EE_ARCH_CORTEX_M_M4F_FPU
OS_EE_AS_OPT += -mfloat-abi=hard -mfpu=fpv4-sp-d16
endif	# OS_EE_ARCH_CORTEX_M_M4F_FPU

ifeq	($(or							\
  $(call iseeopt, OS_EE_ARCH_CORTEX_M_M4),			\
  $(or								\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F),		\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU)		\
  )								\
), yes)
OS_EE_AS_OPT += -mcpu=cortex-m4
endif	#
	# OS_EE_ARCH_CORTEX_M_M4	||
	# OS_EE_ARCH_CORTEX_M_M4F	||
	# OS_EE_ARCH_CORTEX_M_M4F_FPU
	#

ifneq	($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OS_EE_AS_OPT += -save-temps=obj
endif	# OS_EE_GCC_MINIMAL_OPTS

ifeq	($(or	\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),     \
  $(and 								       \
	$(call iseeopt, OS_EE_APPL_BUILD),				       \
	$(call iseeopt, OS_EE_APPL_BUILD_DEBUG)				       \
  )									       \
), yes)
OS_EE_AS_OPT += -Wa,-ggdb
endif

# Specific option from the application makefile
OS_EE_AS_OPT += $(ASFLAGS)

################################################################################
## OS_EE_AR_OPT are the options for arm librarian invocation		      ##
################################################################################
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_AR_OPT = $(subst $(OS_EE_SPACE),,csv $(subst v,,$(ARFLAGS)))
else	# OS_EE_VERBOSE
OS_EE_AR_OPT = $(subst v,,$(subst $(OS_EE_SPACE),,cs $(ARFLAGS)))
endif	# OS_EE_VERBOSE

################################################################################
## OS_EE_AR_OPT are the options for arm linker invocation		      ##
################################################################################
OPT_LINK = -mthumb -mthumb-interwork

# GS: FPU Support
ifneq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU), yes)
OPT_LINK += -mfloat-abi=soft
else	# OS_EE_ARCH_CORTEX_M_M4F_FPU
OPT_LINK += -mfloat-abi=hard -mfpu=fpv4-sp-d16
endif	# OS_EE_ARCH_CORTEX_M_M4F_FPU

ifeq	($(or							\
  $(call iseeopt, OS_EE_ARCH_CORTEX_M_M4),			\
  $(or								\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F),		\
	$(call iseeopt, OS_EE_ARCH_CORTEX_M_M4F_FPU)		\
  )								\
), yes)
OPT_LINK += -mcpu=cortex-m4
endif	#
	# OS_EE_ARCH_CORTEX_M_M4	||
	# OS_EE_ARCH_CORTEX_M_M4F	||
	# OS_EE_ARCH_CORTEX_M_M4F_FPU
	#



ifneq ($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_LINK += -Wl,--gc-sections
endif	# OS_EE_GCC_MINIMAL_OPTS

# Specific option from the application makefile
OPT_LINK += $(LDFLAGS)

# Defining OS_EE_OPT Macros
# Each identifier that is listed in OS_EE_OPT is also inserted as a 
# command-line macro in the compiler...
ifeq	($(call iseeopt, OS_EE_BUILD), yes)
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
ifeq	($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
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
ifeq	($(call iseeopt, OS_EE_BUILD), yes)
OPT_LIBS += -l$(EELIB) -L .
LIBDEP += lib/$(ERIKALIB)
else	# OS_EE_BUILD
OS_EE_OPT_LIBS = -L $(call short_native_path,$(abspath $(OS_EE_LIB_BASE_DIR))) \
-L . -Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc \
$(OPT_LIBS) -l$(EELIB) -Wl,--end-group
LIBDEP += $(OS_EE_LIB_BASE_DIR)/lib$(EELIB).a
endif	# OS_EE_BUILD

# Define the TARGET
TARGET_NAME := erika3app

# Add application file to dependencies
ifneq	($(call iseeopt, OS_EE_BUILD), yes)
export APP_TARGETS :=	$(TARGET_NAME).eep \
			$(TARGET_NAME).hex \
			$(TARGET_NAME).lss \
			$(TARGET_NAME).srec
endif	# !OS_EE_BUILD
