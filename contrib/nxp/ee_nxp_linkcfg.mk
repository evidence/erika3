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

## \file	ee_nxp_linkcfg.mk
## \brief	NXP Libraries Link Configuration.
##
## This makefile contains the rules to integrate NXP stand-alone
## libraries in an Erika Enterprise Application.
##
## \author	Giuseppe Serano
## \date	2018

## Check the NXP Libraries selection

##
## S32 SDK
##
ifeq	($(call islibopt, OS_EE_LIB_S32_SDK), yes)

ifeq	($(and	\
		$(call iseeopt, OS_EE_ARCH_CORTEX_M),	\
		$(call iseeopt, OS_EE_ARCH_CORTEX_M_S32K1XX)	\
	), yes)

ifndef	S32_SDK_FILES
ifeq	($(call islibopt, OS_EE_LIB_S32_SDK_0_8_4_EAR), yes)
export	S32_SDK_FILES = C:/NXP/S32DS_ARM_v2.0/S32DS/S32SDK_S32K14x_EAR_0.8.4
else	# OS_EE_LIB_S32_SDK_0_8_4_EAR
export	S32_SDK_FILES = C:/NXP/S32DS_ARM_v2.0/S32DS/S32SDK_S32K14x_EAR_0.8.4
endif	# OS_EE_LIB_S32_SDK_0_8_4_EAR
endif	# S32_SDK_FILES

S32_SDK_ROOT := $(call short_native_path, $(S32_SDK_FILES))

EE_VPATH += $(S32_SDK_ROOT)

##
## MCU Selection.
##

ifeq	($(findstring S32K144, $(OS_EE_CORTEX_M_MCU)), S32K144)
OS_EE_DEFS_AS	+= -DCPU_S32K144HFT0VLLT
OS_EE_DEFS_CC	+= -DCPU_S32K144HFT0VLLT
OS_EE_DEFS_CXX	+= -DCPU_S32K144HFT0VLLT
endif	# OS_EE_CORTEX_M_MCU == S32K144

ifeq	($(findstring S32K148, $(OS_EE_CORTEX_M_MCU)), S32K148)
OS_EE_DEFS_AS	+= -DCPU_S32K148
OS_EE_DEFS_CC	+= -DCPU_S32K148
OS_EE_DEFS_CXX	+= -DCPU_S32K148
endif	# OS_EE_CORTEX_M_MCU == S32K148

##
## HAL Enabling.
##
#OS_EE_OPT += USE_HAL_DRIVER
#OS_EE_DEFS_AS	+= -DUSE_HAL_DRIVER
#OS_EE_DEFS_CC	+= -DUSE_HAL_DRIVER
#OS_EE_DEFS_CXX	+= -DUSE_HAL_DRIVER

##
## Add the inc path to the include pathlist
## New include mechanism

##
## Drivers
##
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/drivers/inc		\
$(S32_SDK_ROOT)/platform/drivers/src/ftm	\
$(INCLUDE_PATH)

##
## Device
##
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/devices	\
$(S32_SDK_ROOT)/platform/devices/common	\
$(INCLUDE_PATH)

ifeq	($(findstring S32K144, $(OS_EE_CORTEX_M_MCU)), S32K144)
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/devices/S32K144/include	\
$(INCLUDE_PATH)
endif	# OS_EE_CORTEX_M_MCU == S32K144

ifeq	($(findstring S32K148, $(OS_EE_CORTEX_M_MCU)), S32K148)
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/devices/S32K148/include	\
$(INCLUDE_PATH)
endif	# OS_EE_CORTEX_M_MCU == S32K148

##
## Start-Up Code
##

ifeq	($(findstring S32K144, $(OS_EE_CORTEX_M_MCU)), S32K144)
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/devices/S32K144/startup	\
$(INCLUDE_PATH)
OS_EE_APP_CFG_SRCS += platform/devices/S32K144/startup/gcc/startup_S32K144.S
endif	# OS_EE_CORTEX_M_MCU == S32K144

ifeq	($(findstring S32K148, $(OS_EE_CORTEX_M_MCU)), S32K148)
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/devices/S32K148/startup	\
$(INCLUDE_PATH)
OS_EE_APP_CFG_SRCS += platform/devices/S32K148/startup/gcc/startup_S32K148.S
endif	# OS_EE_CORTEX_M_MCU == S32K148

##
## Linker Script
##

ifeq	($(findstring S32K144, $(OS_EE_CORTEX_M_MCU)), S32K144)
ifeq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_RAM), yes)
OS_EE_LINKER_SCRIPT := \
$(S32_SDK_ROOT)/platform/devices/S32K144/linker/gcc/S32K144_64_ram.ld
else
OS_EE_LINKER_SCRIPT := \
$(S32_SDK_ROOT)/platform/devices/S32K144/linker/gcc/S32K144_64_flash.ld
endif
endif	# OS_EE_CORTEX_M_MCU == S32K144

ifeq	($(findstring S32K148, $(OS_EE_CORTEX_M_MCU)), S32K148)
ifeq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_RAM), yes)
OS_EE_LINKER_SCRIPT := \
$(S32_SDK_ROOT)/platform/devices/S32K148/linker/gcc/S32K148_256_ram.ld
else
OS_EE_LINKER_SCRIPT := \
$(S32_SDK_ROOT)/platform/devices/S32K148/linker/gcc/S32K148_256_flash.ld
endif
endif	# OS_EE_CORTEX_M_MCU == S32K148

ifneq	($(if $(filter OS_EE_BUILD,$(OS_EE_OPT)),yes,), yes)
ifeq	($(call islibopt, OS_EE_LIB_S32_SDK_SA), yes)
S32SDK = s32sdk
S32_SDK := lib$(S32SDK).a

OPT_LIBS += -l$(S32SDK)
#OPT_LINK += $(S32_SDK_ROOT)/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a
ALL_LIBS += $(OS_EE_LIB_BASE_DIR)/$(S32_SDK)
endif	# OS_EE_LIB_S32_SDK_SA
endif	# !OS_EE_BUILD

endif	# OS_EE_ARCH_CORTEX_M && OS_EE_ARCH_CORTEX_M_S32K1XX

endif	# OS_EE_LIB_S32_SDK
