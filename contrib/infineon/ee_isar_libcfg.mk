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

## \file	ee_isar_libcfg.mk
## \brief	Infineon AUTOSAR MCAL Library Configuration.
##
## This makefile contains the rules to integrate Infineon AUTOSAR MCAL Library
## in Erika Enterprise as a stand-alone libraries.
##
## \author	Giuseppe Serano
## \date	2018

## Check the Infineon AUTOSAR MCAL Library

##
## ISAR MCAL
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL), yes)

include	$(OS_EE_MK_BASE_DIR)/ee_isar_linkcfg.mk

ifeq	($(call iseeopt, OSEE_ARCH_TRICORE), yes)

ifeq	($(findstring tc27x, $(OSEE_TRICORE_MCU)), tc27x)

##
## Tricore General
##
#EE_SRCS_ISAR_MCAL += tricore_general/ssc/src/Mcal.c
EE_SRCS_ISAR_MCAL += tricore_general/ssc/src/Mcal_TcLib.c
EE_SRCS_ISAR_MCAL += tricore_general/ssc/src/Mcal_WdgLib.c

##
## IRQ Infineon Tricore
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Irq.c
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Adc_Irq.c
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GTM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Gtm_Irq.c
endif	# OS_EE_LIB_ISAR_MCAL_GTM_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ERU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Eru_Irq.c
endif	# OS_EE_LIB_ISAR_MCAL_ERU_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Fls_Irq.c
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER
endif	# OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER

##
## Integration General
##
#EE_SRCS_ISAR_MCAL += integration_general/src/Test_Print.c
#EE_SRCS_ISAR_MCAL += integration_general/src/Test_Time.c

##
## EcuM
##
#EE_SRCS_ISAR_MCAL += ecum_infineon_tricore/ssc/src/EcuM.c

##
## EcuM Configuration
##
#EE_SRCS_ISAR_MCAL += src/EcuM_LCfg.c
#EE_SRCS_ISAR_MCAL += src/EcuM_PBCfg.c

##
## PORT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_USE_DET), yes)
EE_SRCS_ISAR_MCAL += Det.c
endif	# OS_EE_LIB_ISAR_MCAL_USE_DET

##
## MCU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GTM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Gtm.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Gtm_Platform.c
endif	# OS_EE_LIB_ISAR_MCAL_GTM_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_MCU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Crc.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Dma.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Platform.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_MCU_DRIVER

##
## MCU Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GTM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Gtm_LCfg.c
EE_SRCS_ISAR_MCAL += src/Gtm_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_GTM_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_MCU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Mcu_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_MCU_DRIVER

##
## PORT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PORT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += port_infineon_tricore/ssc/src/Port.c
endif	# OS_EE_LIB_ISAR_MCAL_PORT_DRIVER

##
## PORT Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PORT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Port_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_PORT_DRIVER

##
## DIO Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_DIO_DRIVER), yes)
EE_SRCS_ISAR_MCAL += dio_infineon_tricore/ssc/src/Dio.c
EE_SRCS_ISAR_MCAL += dio_infineon_tricore/ssc/src/Dio_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_DIO_DRIVER

##
## DIO Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_DIO_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Dio_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_DIO_DRIVER

##
## GPT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GPT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += gpt_infineon_tricore/ssc/src/Gpt.c
EE_SRCS_ISAR_MCAL += gpt_infineon_tricore/ssc/src/Gpt_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_GPT_DRIVER

##
## GPT Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GPT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Gpt_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_GPT_DRIVER

##
## ICU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ICU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += icu_17_gtmccu6_infineon_tricore/ssc/src/Icu_17_GtmCcu6.c
EE_SRCS_ISAR_MCAL += icu_17_gtmccu6_infineon_tricore/ssc/src/Icu_17_GtmCcu6_Safe.c
EE_SRCS_ISAR_MCAL += icu_17_gtmccu6_infineon_tricore/ssc/src/Icu_17_GtmCcu6_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_ICU_DRIVER

##
## ICU Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ICU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Icu_17_GtmCcu6_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_ICU_DRIVER

##
## PWM Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PWM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += pwm_17_gtm_infineon_tricore/ssc/src/Pwm_17_Gtm.c
EE_SRCS_ISAR_MCAL += pwm_17_gtm_infineon_tricore/ssc/src/Pwm_17_Gtm_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_PWM_DRIVER

##
## PWM Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PWM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Pwm_17_Gtm_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_PWM_DRIVER

##
## ADC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_Calibration.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_ConvHandle.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_HwHandle.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER

##
## ADC Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Adc_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER

##
## SPI Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SPI_DRIVER), yes)
EE_SRCS_ISAR_MCAL += spi_infineon_tricore/ssc/src/Spi.c
EE_SRCS_ISAR_MCAL += spi_infineon_tricore/ssc/src/Spi_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_SPI_DRIVER

##
## SPI Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SPI_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Spi_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_SPI_DRIVER

##
## CRC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CRC_DRIVER), yes)
EE_SRCS_ISAR_MCAL += crc_infineon_tricore/ssc/src/Crc.c
endif	# OS_EE_LIB_ISAR_MCAL_CRC_DRIVER

##
## FLS Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
EE_SRCS_ISAR_MCAL += fls_17_pmu_infineon_tricore/ssc/src/Fls_17_Pmu.c
EE_SRCS_ISAR_MCAL += fls_17_pmu_infineon_tricore/ssc/src/Fls_17_Pmu_ac.c
EE_SRCS_ISAR_MCAL += fls_17_pmu_infineon_tricore/ssc/src/Fls_17_Pmu_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FLS Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Fls_17_Pmu_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FEE Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FEE_DRIVER), yes)
EE_SRCS_ISAR_MCAL += fee_infineon_tricore/ssc/src/Fee.c
EE_SRCS_ISAR_MCAL += fee_infineon_tricore/ssc/src/Fee_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_FEE_DRIVER

##
## FEE Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FEE_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Fee_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_FEE_DRIVER

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SA), yes)

EE_OBJS_ISAR_MCAL := 						   \
	$(addprefix $(OS_EE_OBJ_DIR)/,				   \
		$(patsubst %.c,%.c.o,				   \
			$(patsubst %.S,%.S.o,$(EE_SRCS_ISAR_MCAL)) \
		)						   \
	)

LIBSRCS += $(EE_SRCS_ISAR_MCAL)

ISAR_MCAL_LIB := libisarmcal.a

$(OS_EE_LIB_DIR)/$(ISAR_MCAL_LIB): $(EE_OBJS_ISAR_MCAL)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^
	@echo "*****************************************"
	@echo "* ISAR MCAL Library built successfully! *"
	@echo "*****************************************"

OPT_LIBS += $(OS_EE_LIB_DIR)/$(ISAR_MCAL_LIB)
ALL_LIBS += $(OS_EE_LIB_DIR)/$(ISAR_MCAL_LIB)

else	# OS_EE_LIB_ISAR_MCAL_SA

EE_SRCS += $(EE_SRCS_ISAR_MCAL)

endif	# OS_EE_LIB_ISAR_MCAL_SA

endif	# OSEE_TRICORE_MCU == tc27x

ifeq	($(findstring tc29x, $(OSEE_TRICORE_MCU)), tc29x)

##
## Tricore General
##
#EE_SRCS_ISAR_MCAL += tricore_general/ssc/src/Mcal.c
EE_SRCS_ISAR_MCAL += tricore_general/ssc/src/Mcal_TcLib.c
EE_SRCS_ISAR_MCAL += tricore_general/ssc/src/Mcal_WdgLib.c

##
## IRQ Infineon Tricore
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Irq.c
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GTM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Gtm_Irq.c
endif	# OS_EE_LIB_ISAR_MCAL_GTM_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ERU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Eru_Irq.c
endif	# OS_EE_LIB_ISAR_MCAL_ERU_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
EE_SRCS_ISAR_MCAL += irq_infineon_tricore/ssc/src/Fls_Irq.c
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER
endif	# OS_EE_LIB_ISAR_MCAL_IRQ_DRIVER

##
## Integration General
##
#EE_SRCS_ISAR_MCAL += integration_general/src/Test_Print.c
#EE_SRCS_ISAR_MCAL += integration_general/src/Test_Time.c

##
## EcuM
##
#EE_SRCS_ISAR_MCAL += ecum_infineon_tricore/ssc/src/EcuM.c

##
## EcuM Configuration
##
#EE_SRCS_ISAR_MCAL += src/EcuM_LCfg.c
#EE_SRCS_ISAR_MCAL += src/EcuM_PBCfg.c

##
## PORT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_USE_DET), yes)
EE_SRCS_ISAR_MCAL += Det.c
endif	# OS_EE_LIB_ISAR_MCAL_USE_DET

##
## MCU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GTM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Gtm.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Gtm_Platform.c
endif	# OS_EE_LIB_ISAR_MCAL_GTM_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_MCU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Crc.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Dma.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Platform.c
EE_SRCS_ISAR_MCAL += mcu_infineon_tricore/ssc/src/Mcu_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_MCU_DRIVER

##
## MCU Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GTM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Gtm_LCfg.c
EE_SRCS_ISAR_MCAL += src/Gtm_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_GTM_DRIVER
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_MCU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Mcu_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_MCU_DRIVER

##
## PORT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PORT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += port_infineon_tricore/ssc/src/Port.c
endif	# OS_EE_LIB_ISAR_MCAL_PORT_DRIVER

##
## PORT Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PORT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Port_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_PORT_DRIVER

##
## DIO Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_DIO_DRIVER), yes)
EE_SRCS_ISAR_MCAL += dio_infineon_tricore/ssc/src/Dio.c
EE_SRCS_ISAR_MCAL += dio_infineon_tricore/ssc/src/Dio_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_DIO_DRIVER

##
## DIO Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_DIO_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Dio_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_DIO_DRIVER

##
## GPT Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GPT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += gpt_infineon_tricore/ssc/src/Gpt.c
EE_SRCS_ISAR_MCAL += gpt_infineon_tricore/ssc/src/Gpt_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_GPT_DRIVER

##
## GPT Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_GPT_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Gpt_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_GPT_DRIVER

##
## ICU Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ICU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += icu_17_gtmccu6_infineon_tricore/ssc/src/Icu_17_GtmCcu6.c
EE_SRCS_ISAR_MCAL += icu_17_gtmccu6_infineon_tricore/ssc/src/Icu_17_GtmCcu6_Safe.c
EE_SRCS_ISAR_MCAL += icu_17_gtmccu6_infineon_tricore/ssc/src/Icu_17_GtmCcu6_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_ICU_DRIVER

##
## ICU Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ICU_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Icu_17_GtmCcu6_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_ICU_DRIVER

##
## PWM Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PWM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += pwm_17_gtm_infineon_tricore/ssc/src/Pwm_17_Gtm.c
EE_SRCS_ISAR_MCAL += pwm_17_gtm_infineon_tricore/ssc/src/Pwm_17_Gtm_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_PWM_DRIVER

##
## PWM Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PWM_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Pwm_17_Gtm_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_PWM_DRIVER

##
## ADC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_Calibration.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_ConvHandle.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_HwHandle.c
EE_SRCS_ISAR_MCAL += adc_infineon_tricore/ssc/src/Adc_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER

##
## ADC Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Adc_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER

##
## SPI Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SPI_DRIVER), yes)
EE_SRCS_ISAR_MCAL += spi_infineon_tricore/ssc/src/Spi.c
EE_SRCS_ISAR_MCAL += spi_infineon_tricore/ssc/src/Spi_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_SPI_DRIVER

##
## SPI Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SPI_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Spi_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_SPI_DRIVER

##
## CRC Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_CRC_DRIVER), yes)
EE_SRCS_ISAR_MCAL += crc_infineon_tricore/ssc/src/Crc.c
endif	# OS_EE_LIB_ISAR_MCAL_CRC_DRIVER

##
## FLS Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
EE_SRCS_ISAR_MCAL += fls_17_pmu_infineon_tricore/ssc/src/Fls_17_Pmu.c
EE_SRCS_ISAR_MCAL += fls_17_pmu_infineon_tricore/ssc/src/Fls_17_Pmu_ac.c
EE_SRCS_ISAR_MCAL += fls_17_pmu_infineon_tricore/ssc/src/Fls_17_Pmu_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FLS Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Fls_17_Pmu_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FEE Driver
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FEE_DRIVER), yes)
EE_SRCS_ISAR_MCAL += fee_infineon_tricore/ssc/src/Fee.c
EE_SRCS_ISAR_MCAL += fee_infineon_tricore/ssc/src/Fee_Ver.c
endif	# OS_EE_LIB_ISAR_MCAL_FEE_DRIVER

##
## FEE Driver Configuration
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FEE_DRIVER), yes)
EE_SRCS_ISAR_MCAL += src/Fee_PBCfg.c
endif	# OS_EE_LIB_ISAR_MCAL_FEE_DRIVER

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SA), yes)

EE_OBJS_ISAR_MCAL := 						   \
	$(addprefix $(OS_EE_OBJ_DIR)/,				   \
		$(patsubst %.c,%.c.o,				   \
			$(patsubst %.S,%.S.o,$(EE_SRCS_ISAR_MCAL)) \
		)						   \
	)

LIBSRCS += $(EE_SRCS_ISAR_MCAL)

ISAR_MCAL_LIB := libisarmcal.a

$(OS_EE_LIB_DIR)/$(ISAR_MCAL_LIB): $(EE_OBJS_ISAR_MCAL)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^
	@echo "*****************************************"
	@echo "* ISAR MCAL Library built successfully! *"
	@echo "*****************************************"

OPT_LIBS += $(OS_EE_LIB_DIR)/$(ISAR_MCAL_LIB)
ALL_LIBS += $(OS_EE_LIB_DIR)/$(ISAR_MCAL_LIB)

else	# OS_EE_LIB_ISAR_MCAL_SA

EE_SRCS += $(EE_SRCS_ISAR_MCAL)

endif	# OS_EE_LIB_ISAR_MCAL_SA

endif	# OSEE_TRICORE_MCU == tc29x


endif	# OSEE_ARCH_TRICORE

endif	# OS_EE_LIB_ISAR_MCAL
