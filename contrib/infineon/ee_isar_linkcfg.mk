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

## \file	ee_isar_linkcfg.mk
## \brief	Infineon AUTOSAR MCAL Library Configuration.
##
## This makefile contains the rules to integrate Infineon AUTOSAR MCAL
## stand-alone library in an Erika Enterprise Application.
##
## \author	Giuseppe Serano
## \date	2018

## Check the Infineon AUTOSAR MCAL Library selection

##
## ISAR MCAL
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL), yes)

ifeq	($(call iseeopt, OSEE_ARCH_TRICORE), yes)

ifeq	($(findstring tc27x, $(OSEE_TRICORE_MCU)), tc27x)

ifndef	ISAR_MCAL_BASE_FILES
$(error ISAR_MCAL_BASE_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_BASE_FILES=$(ISAR_MCAL_BASE_FILES))
ISAR_MCAL_BASE_ROOT := $(call short_native_path, $(ISAR_MCAL_BASE_FILES))
EE_VPATH += $(ISAR_MCAL_BASE_ROOT)
endif

ifndef	ISAR_MCAL_CFG_FILES
$(error ISAR_MCAL_CFG_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_CFG_FILES=$(ISAR_MCAL_CFG_FILES))
ISAR_MCAL_CFG_ROOT := $(call short_native_path, $(ISAR_MCAL_CFG_FILES))
EE_VPATH += $(ISAR_MCAL_CFG_ROOT)
endif

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CRC_DRIVER), yes)
ifndef	ISAR_MCAL_LIB_FILES
$(error ISAR_MCAL_LIB_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_LIB_FILES=$(ISAR_MCAL_LIB_FILES))
ISAR_MCAL_LIB_ROOT := $(call short_native_path, $(ISAR_MCAL_LIB_FILES))
EE_VPATH += $(ISAR_MCAL_LIB_ROOT)
endif
endif	# OS_EE_LIB_ISAR_MCAL_CRC_DRIVER

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
ifndef	ISAR_MCAL_MEM_FILES
$(error ISAR_MCAL_MEM_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_MEM_FILES=$(ISAR_MCAL_MEM_FILES))
ISAR_MCAL_MEM_ROOT := $(call short_native_path, $(ISAR_MCAL_MEM_FILES))
EE_VPATH += $(ISAR_MCAL_MEM_ROOT)
endif
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CAN_DRIVER), yes)
ifndef	ISAR_MCAL_COM_BASIC_FILES
$(error ISAR_MCAL_COM_BASIC_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_COM_BASIC_FILES=$(ISAR_MCAL_COM_BASIC_FILES))
ISAR_MCAL_COM_BASIC_ROOT := $(call short_native_path, $(ISAR_MCAL_COM_BASIC_FILES))
EE_VPATH += $(ISAR_MCAL_COM_BASIC_ROOT)
endif
endif	# OS_EE_LIB_ISAR_MCAL_CAN_DRIVER

##
## Compiler Selection.
##
OS_EE_DEFS_AS	+=-D_GNU_C_TRICORE_=1 -DOS_KERNEL_TYPE
OS_EE_DEFS_CC	+=-D_GNU_C_TRICORE_=1 -DOS_KERNEL_TYPE
OS_EE_DEFS_CXX	+=-D_GNU_C_TRICORE_=1 -DOS_KERNEL_TYPE

##
## MCU Selection.
##

#ifeq	($(findstring S32K144, $(OS_EE_CORTEX_M_MCU)), S32K144)
#OS_EE_DEFS_AS	+= -DCPU_S32K144HFT0VLLT
#OS_EE_DEFS_CC	+= -DCPU_S32K144HFT0VLLT
#OS_EE_DEFS_CXX	+= -DCPU_S32K144HFT0VLLT
#endif	# OS_EE_CORTEX_M_MCU == S32K144

##
## Add the inc path to the include pathlist
## New include mechanism

##
## MemMap.h
##
ifneq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_BSW), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/demoapp/tricore/compiler	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_BSW

##
## General
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_6_0_0), yes)
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_BSW), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc		\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc/TC27xD	\
$(INCLUDE_PATH)
else
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/general/inc			\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc		\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc/TC27xD	\
$(INCLUDE_PATH)
endif
endif

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_3_0_0), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/general/inc			\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc		\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc/TC29x	\
$(INCLUDE_PATH)
endif

##
## Tricore General
##
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/tricore_general/ssc/inc	\
$(ISAR_MCAL_CFG_ROOT)/inc			\
$(INCLUDE_PATH)

##
## IRQ Infineon Tricore
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/irq_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER


##
## Demo AURIX
##
#INCLUDE_PATH :=	\
#$(ISAR_MCAL_CFG_ROOT)/Demo_Aurix		\
#$(INCLUDE_PATH)

##
## Integration General
##
#INCLUDE_PATH :=	\
#$(ISAR_MCAL_BASE_ROOT)/integration_general/inc	\
#$(INCLUDE_PATH)

##
## EcuM
##
#INCLUDE_PATH :=	\
#$(ISAR_MCAL_BASE_ROOT)/ecum_infineon_tricore/ssc/inc	\
#$(INCLUDE_PATH)

##
## Drivers Configuration
##
INCLUDE_PATH :=	\
$(ISAR_MCAL_CFG_ROOT)/inc			\
$(INCLUDE_PATH)

##
## MCU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_MCU_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/mcu_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_MCU_DRIVER

##
## PORT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PORT_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/port_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_PORT_DRIVER

##
## DIO Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_DIO_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/dio_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_DIO_DRIVER

##
## GPT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GPT_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/gpt_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_GPT_DRIVER

##
## ICU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ICU_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/icu_17_gtmccu6_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_ICU_DRIVER

##
## PWM Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PWM_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/pwm_17_gtm_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_PWM_DRIVER

##
## ADC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/adc_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER

##
## SPI Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SPI_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/spi_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_SPI_DRIVER

##
## CRC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CRC_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_LIB_ROOT)/crc_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_CRC_DRIVER

##
## FLS Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_MEM_ROOT)/fls_17_pmu_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FEE Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FEE_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_MEM_ROOT)/fee_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_FEE_DRIVER

##
## CAN Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CAN_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_COM_BASIC_ROOT)/can_17_mcanp_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_CAN_DRIVER

##
## CAN Transciever 
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CAN_TRCV_6250GV33), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_COM_BASIC_ROOT)/cantrcv_17_6250gv33_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_CAN_TRCV_6250GV33

ifneq	($(if $(filter OS_EE_BUILD,$(OS_EE_OPT)),yes,), yes)
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SA), yes)
ISARMCAL = isarmcal
ISAR_MCAL := lib$(ISARMCAL).a

OPT_LIBS += -l$(ISARMCAL)
ALL_LIBS += $(OS_EE_LIB_BASE_DIR)/$(ISAR_MCAL)
endif	# OS_EE_LIB_ISAR_MCAL_SA
endif	# !OS_EE_BUILD

endif	# OSEE_TRICORE_MCU == tc27x

ifeq	($(findstring tc29x, $(OSEE_TRICORE_MCU)), tc29x)

ifndef	ISAR_MCAL_BASE_FILES
$(error ISAR_MCAL_BASE_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_BASE_FILES=$(ISAR_MCAL_BASE_FILES))
ISAR_MCAL_BASE_ROOT := $(call short_native_path, $(ISAR_MCAL_BASE_FILES))
EE_VPATH += $(ISAR_MCAL_BASE_ROOT)
endif

ifndef	ISAR_MCAL_CFG_FILES
$(error ISAR_MCAL_CFG_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_CFG_FILES=$(ISAR_MCAL_CFG_FILES))
ISAR_MCAL_CFG_ROOT := $(call short_native_path, $(ISAR_MCAL_CFG_FILES))
EE_VPATH += $(ISAR_MCAL_CFG_ROOT)
endif

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CRC_DRIVER), yes)
ifndef	ISAR_MCAL_LIB_FILES
$(error ISAR_MCAL_LIB_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_LIB_FILES=$(ISAR_MCAL_LIB_FILES))
ISAR_MCAL_LIB_ROOT := $(call short_native_path, $(ISAR_MCAL_LIB_FILES))
EE_VPATH += $(ISAR_MCAL_LIB_ROOT)
endif
endif	# OS_EE_LIB_ISAR_MCAL_CRC_DRIVER

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
ifndef	ISAR_MCAL_MEM_FILES
$(error ISAR_MCAL_MEM_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_MEM_FILES=$(ISAR_MCAL_MEM_FILES))
ISAR_MCAL_MEM_ROOT := $(call short_native_path, $(ISAR_MCAL_MEM_FILES))
EE_VPATH += $(ISAR_MCAL_MEM_ROOT)
endif
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CAN_DRIVER), yes)
ifndef	ISAR_MCAL_COM_BASIC_FILES
$(error ISAR_MCAL_COM_BASIC_FILES NOT DEFINED!!!)
else
$(info ISAR_MCAL_COM_BASIC_FILES=$(ISAR_MCAL_COM_BASIC_FILES))
ISAR_MCAL_COM_BASIC_ROOT := $(call short_native_path, $(ISAR_MCAL_COM_BASIC_FILES))
EE_VPATH += $(ISAR_MCAL_COM_BASIC_ROOT)
endif
endif	# OS_EE_LIB_ISAR_CAN_MCAL__DRIVER

##
## Compiler Selection.
##
OS_EE_DEFS_AS	+=-D_GNU_C_TRICORE_=1 -DOS_KERNEL_TYPE
OS_EE_DEFS_CC	+=-D_GNU_C_TRICORE_=1 -DOS_KERNEL_TYPE
OS_EE_DEFS_CXX	+=-D_GNU_C_TRICORE_=1 -DOS_KERNEL_TYPE

##
## MCU Selection.
##

#ifeq	($(findstring S32K144, $(OS_EE_CORTEX_M_MCU)), S32K144)
#OS_EE_DEFS_AS	+= -DCPU_S32K144HFT0VLLT
#OS_EE_DEFS_CC	+= -DCPU_S32K144HFT0VLLT
#OS_EE_DEFS_CXX	+= -DCPU_S32K144HFT0VLLT
#endif	# OS_EE_CORTEX_M_MCU == S32K144

##
## Add the inc path to the include pathlist
## New include mechanism

##
## MemMap.h
##
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/demoapp/tricore/compiler	\
$(INCLUDE_PATH)

##
## General
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_6_0_0), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/general/inc			\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc		\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc/TC27xD	\
$(INCLUDE_PATH)
endif

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_3_0_0), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/general/inc			\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc		\
$(ISAR_MCAL_BASE_ROOT)/general/tricore/inc/TC29x	\
$(INCLUDE_PATH)
endif

##
## Tricore General
##
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/tricore_general/ssc/inc	\
$(ISAR_MCAL_CFG_ROOT)/inc			\
$(INCLUDE_PATH)

##
## IRQ Infineon Tricore
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/irq_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER


##
## Demo AURIX
##
#INCLUDE_PATH :=	\
#$(ISAR_MCAL_CFG_ROOT)/Demo_Aurix		\
#$(INCLUDE_PATH)

##
## Integration General
##
#INCLUDE_PATH :=	\
#$(ISAR_MCAL_BASE_ROOT)/integration_general/inc	\
#$(INCLUDE_PATH)

##
## EcuM
##
#INCLUDE_PATH :=	\
#$(ISAR_MCAL_BASE_ROOT)/ecum_infineon_tricore/ssc/inc	\
#$(INCLUDE_PATH)

##
## Drivers Configuration
##
INCLUDE_PATH :=	\
$(ISAR_MCAL_CFG_ROOT)/inc			\
$(INCLUDE_PATH)

##
## MCU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_MCU_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/mcu_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_MCU_DRIVER

##
## PORT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PORT_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/port_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_PORT_DRIVER

##
## DIO Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_DIO_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/dio_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_DIO_DRIVER

##
## GPT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GPT_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/gpt_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_GPT_DRIVER

##
## ICU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ICU_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/icu_17_gtmccu6_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_ICU_DRIVER

##
## PWM Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PWM_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/pwm_17_gtm_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_PWM_DRIVER

##
## ADC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/adc_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER

##
## SPI Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SPI_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_BASE_ROOT)/spi_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_SPI_DRIVER

##
## CRC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CRC_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_LIB_ROOT)/crc_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_CRC_DRIVER

##
## FLS Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_MEM_ROOT)/fls_17_pmu_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FEE Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FEE_DRIVER), yes)
INCLUDE_PATH :=	\
$(ISAR_MCAL_MEM_ROOT)/fee_infineon_tricore/ssc/inc	\
$(INCLUDE_PATH)
endif	# OS_EE_LIB_ISAR_MCAL_FEE_DRIVER

ifneq	($(if $(filter OS_EE_BUILD,$(OS_EE_OPT)),yes,), yes)
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SA), yes)
ISARMCAL = isarmcal
ISAR_MCAL := lib$(ISARMCAL).a

OPT_LIBS += -l$(ISARMCAL)
ALL_LIBS += $(OS_EE_LIB_BASE_DIR)/$(ISAR_MCAL)
endif	# OS_EE_LIB_ISAR_MCAL_SA
endif	# !OS_EE_BUILD

endif	# OSEE_TRICORE_MCU == tc29x


endif	# OSEE_ARCH_TRICORE

endif	# OS_EE_LIB_ISAR_MCAL
