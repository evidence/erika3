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

## \file    ee_arch_compiler_ti_cgt_arm.mk
## \brief   ARM Architecture TI Code Generator Tool ARM Compiler.
##
## This makefile contains the list of TI Code Generator Tool ARM Compiler
## variables for TI AWR16XX
##
## \author  Errico Guidieri
## \date    2019

##
## Compiler related options
##

ti_path = $(shell cygpath -ml '$(strip $1)')

# Erika Library.
ERIKALIB = $(ERIKALIB_NAME).a

# Define the TARGET
TARGET_NAME ?= erika3app

# TI_ARM_C_DIR variable
ifneq ($(TI_ARM_C_DIR),)
#Assure the existence of the trailing slash eventually remove it with realpath
#and adding it back
TI_ARM_C_DIR_LOC := $(call ti_path, $(realpath $(TI_ARM_C_DIR)))
endif # TI_ARM_C_DIR

# TI_MMWAVE_SDK_PATH
ifneq ($(TI_MMWAVE_SDK_PATH),)
#Assure the existence of the trailing slash eventually remove it with realpath
#and adding it back
TI_MMWAVE_SDK_PATH_LOC := $(call ti_path, $(realpath $(TI_MMWAVE_SDK_PATH)))
else
$(error TI_MMWAVE_SDK_PATH must be provided)
endif # TI_MMWAVE_SDK_PATH

# ALLINCPATH is a colon separated list of directories for source file searching
# --include_path= adds directories to the source file search path
# System libraries include files
SYSTEM_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)"
SYSTEM_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages"
ifneq ($(TI_ARM_C_DIR),)
SYSTEM_PATH += "$(TI_ARM_C_DIR_LOC)/include"
endif

ALLINCPATH += $(foreach d, $(SYSTEM_PATH),$(addprefix --include_path=,$d))
ALLINCPATH += $(foreach d,$(INCLUDE_PATH),$(addprefix --include_path=,"$(call ti_path, $d)"))

EE_OBJDUMP ?= $(TI_ARM_C_DIR_LOC)/bin/armdis

# GNUPro compilers
EE_LINK ?= $(TI_ARM_C_DIR_LOC)/bin/armcl

OS_EE_AS ?= $(TI_ARM_C_DIR_LOC)/bin/armcl

EE_CC ?= $(TI_ARM_C_DIR_LOC)/bin/armcl

EE_CXX ?= $(TI_ARM_C_DIR_LOC)/bin/armcl

OS_EE_AR ?= $(TI_ARM_C_DIR_LOC)/bin/armar

## OPT_CC are the options for TI CGT ARM C compiler invocation
# Useful options:
#
# -mv7R4                   ARMv7r Cortex-R4
# --code_state=16          Thumb16 Instruction Set
# --float_support=VFPv3D16 Co-processor VFPv3, hardware float support
# -me                      Little Endianness (Default endianness is Big)
# -On                      Optimization level
# -g                       Debug Synbols
# --c99                    Conformance to C 99
# --enum_type=int          Force all the enums to be 32-bit integers underlying
#                          In contrast of the default "packet" where each enum
#                          is "packet" in the smallest type that can contains it
#                          (Actually I prefer the default behavior, but i need
#                           to use enum as integer to have the same ABI of
#                           mmWave SDK libraries)
# --diag_suppress=190      #190-D enumerated type mixed with another type
#                          This diagnostic seams bugged. It is triggered
#                          where enums are not involved!!!

OPT_CC = --preproc_with_compile -mv7R4 --code_state=16\
 --float_support=VFPv3D16  -me --abi=eabi --display_error_number --keep_asm\
 --gen_func_subsections=on --define=_LITTLE_ENDIAN --enum_type=int\
 --diag_suppress=190
ifneq ($(call iseeopt, OSEE_TI_CGT_ARM_MINIMAL_OPTS), yes)
OPT_CC += --define=SOC_XWR16XX --define=SUBSYS_MSS --define=DOWNLOAD_FROM_CCS\
 --define=MMWAVE_L3RAM_SIZE=0xC0000 --define=DebugP_ASSERT_ENABLED\
 --diag_warning=225
endif # !OSEE_TI_CGT_ARM_MINIMAL_OPTS
ifeq ($(or\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),\
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))\
), yes)
OPT_CC += -g -O1
else
OPT_CC += -g -O3
endif
# Specific option from the application makefile
OPT_CC += $(CFLAGS)

# COMPUTED_OPT_CC_PREP Used for file preprocessed file generation:
COMPUTED_OPT_CC_PREP :=  --preproc_with_comment $(filter-out --preproc_with_compile , $(OPT_CC))

## OPT_CXX are the options for TI CGT ARM C++ compiler invocation
OPT_CXX += --preproc_with_compile -mv7R4 --code_state=16\
 --float_support=VFPv3D16 -me --abi=eabi --display_error_number --keep_asm\
 --gen_func_subsections=on --define=_LITTLE_ENDIAN --enum_type=int\
 --diag_suppress=190
ifneq ($(call iseeopt, OSEE_TI_CGT_ARM_MINIMAL_OPTS), yes)
OPT_CXX +=--define=SOC_XWR16XX --define=SUBSYS_MSS --define=DOWNLOAD_FROM_CCS\
 --define=MMWAVE_L3RAM_SIZE=0xC0000 --define=DebugP_ASSERT_ENABLED\
 --diag_warning=225
endif # !OSEE_TI_CGT_ARM_MINIMAL_OPTS
ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)), \
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG)) \
), yes)
OPT_CXX += -g -O1
else
OPT_CXX += -g -O3
endif

# Specific option from the application makefile
OPT_CXX += $(CFLAGS) $(CXXFLAGS)

## OS_EE_AS_OPT are the options for TI CGT ARM assembler invocation
OS_EE_AS_OPT =  --preproc_with_compile -mv7R4 --code_state=16\
 --float_support=VFPv3D16 -me --abi=eabi --display_error_number\
 --gen_func_subsections=on --define=_LITTLE_ENDIAN --enum_type=int\
 --diag_suppress=190
ifneq ($(call iseeopt, OSEE_TI_CGT_ARM_MINIMAL_OPTS), yes)
OS_EE_AS_OPT +=--define=SOC_XWR16XX --define=SUBSYS_MSS --define=DOWNLOAD_FROM_CCS\
 --define=MMWAVE_L3RAM_SIZE=0xC0000 --define=DebugP_ASSERT_ENABLED\
 --diag_warning=225
endif # !OSEE_TI_CGT_ARM_MINIMAL_OPTS

ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),\
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))\
), yes)
OS_EE_AS_OPT += -g
else
OS_EE_AS_OPT += -g
endif

OS_EE_AS_OPT += $(ASFLAGS)

# COMPUTED_OPT_AS_PREP   Used for assembly file
COMPUTED_OPT_AS_PREP = --preproc_only\
 $(filter-out --preproc_with_compile, $(OS_EE_AS_OPT))

# OS_EE_AR_OPT represents the options for archiver invocation
ifeq ($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_AR_OPT = $(subst $(OS_EE_SPACE),,ruv $(subst v,,$(ARFLAGS)))
else # OS_EE_VERBOSE
OS_EE_AR_OPT = $(subst v,,$(subst $(OS_EE_SPACE),,ru $(ARFLAGS)))
endif # OS_EE_VERBOSE

LIB_PATH += "$(TI_ARM_C_DIR_LOC)/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/control/mmwavelink/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/crc/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/esm/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/gpio/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/soc/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/pinmux/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/mailbox/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/dma/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/drivers/uart/lib"
LIB_PATH += "$(TI_MMWAVE_SDK_PATH_LOC)/packages/ti/utils/cli/lib"
LIB_PATH += "$(call ti_path, $(OS_EE_LIB_BASE_DIR))"

LIB_PATH_OPT := $(foreach d, $(LIB_PATH),$(addprefix -i,$d))

# Stack and heap default sizes
OSEE_SYS_STACK_SIZE ?= 0x800
# mmWave SDK require the heap
OSEE_SYS_HEAP_SIZE  ?= 0x800

# OPT_LINK represents the options for avr linker invocation
OSEE_LINKER_SCRIPT ?= $(call ti_path,$(abspath $(OS_EE_MK_BASE_DIR)/mss_mmw_linker.cmd))
## OPT_LINK are the options for Diab RH850 dld
# Useful options:
# -z is an alias for --run_linker only after this option we can specify
# linking options
# --reread_libs      Re-read previous linked libraries fro dependencies
# --disable_auto_rts   Disable automatic selection for runtime

OPT_LINK = -mv7R4 --code_state=16 --float_support=VFPv3D16\
 -me --abi=eabi --display_error_number --gen_func_subsections=on\
 --define=_LITTLE_ENDIAN -g --enum_type=int\
# --diag_suppress=190
ifneq ($(call iseeopt, OSEE_TI_CGT_ARM_MINIMAL_OPTS), yes)
OPT_LINK +=--define=SOC_XWR16XX --define=SUBSYS_MSS --define=DOWNLOAD_FROM_CCS\
 --define=MMWAVE_L3RAM_SIZE=0xC0000 --define=DebugP_ASSERT_ENABLED\
 --diag_warning=225
endif # !OSEE_TI_CGT_ARM_MINIMAL_OPTS
# -z is an alias for --run_linker only after this option we can specify
# linking options
OPT_LINK += -z --rom_model -m"$(TARGET_NAME).map"\
 --heap_size=$(OSEE_SYS_HEAP_SIZE)\
 --stack_size=$(OSEE_SYS_STACK_SIZE) --reread_libs --disable_auto_rts\
 --warn_sections --xml_link_info="$(TARGET_NAME).xml"\
 --unused_section_elimination=on $(LIB_PATH_OPT)

OPT_LINK += $(LDFLAGS)

SYSTEM_LIB += libesm_xwr16xx.aer4f
SYSTEM_LIB += libgpio_xwr16xx.aer4f
SYSTEM_LIB += libsoc_xwr16xx.aer4f
SYSTEM_LIB += libmailbox_xwr16xx.aer4f
SYSTEM_LIB += libpinmux_xwr16xx.aer4f
SYSTEM_LIB += libcrc_xwr16xx.aer4f
SYSTEM_LIB += libDMA_xwr16xx.aer4f
SYSTEM_LIB += libuart_xwr16xx.aer4f
SYSTEM_LIB += libmmwavelink_xwr16xx.aer4f
SYSTEM_LIB += libcli_xwr16xx.aer4f
SYSTEM_LIB += rtsv7R4_T_le_v3D16_eabi.lib
SYSTEM_LIB += libc.a
SYSTEM_LIB += $(ERIKALIB)

OPT_LIBS := $(foreach d, $(SYSTEM_LIB),$(addprefix -l,$d))

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
# the EE library is built in the current directory
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
LIBDEP += lib/$(ERIKALIB)
else # OS_EE_BUILD
LIBDEP += $(OS_EE_LIB_BASE_DIR)/$(ERIKALIB)
endif # OS_EE_BUILD

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_DEFS_AS   += --define=OS_EE_BUILD
OS_EE_DEFS_CC   += --define=OS_EE_BUILD
OS_EE_DEFS_CXX  += --define=OS_EE_BUILD
endif

# Automatic dependency generation
ifeq ($(call iseeopt, OS_EE_NO_DEPS), yes)
OS_EE_DEP_OPT =
OS_EE_MK_DEPS =
else	# OS_EE_NO_DEPS
# Create dependency for all headers, and add a target for each header
OS_EE_DEP_OPT =  --preproc_dependency=$(call native_path,$(subst $(suffix $(notdir $@)),.d_tmp,$@))\
 --obj_directory="$(dir $@)"
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
# Dependencies on Windows need path translation and quote remotion
OS_EE_MK_DEPS = sed -e 's_\\\(.\)\(.\)_/\1\2_g' \
	-e 's_.obj_$(suffix $@).o_g' < $1_tmp > $1 && rm $1_tmp
else	# OS_EE_RTD_BUILD_ENV_CYGWIN
OS_EE_MK_DEPS = mv $1_tmp $1
endif	# OS_EE_RTD_BUILD_ENV_CYGWIN
endif	# OS_EE_NO_DEPS

# Add application file to dependencies
ifneq ($(call iseeopt, OS_EE_BUILD), yes)
APP_TARGETS := $(TARGET_NAME).dump
endif	# !OS_EE_BUILD
