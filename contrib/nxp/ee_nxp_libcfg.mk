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

## \file	ee_nxp_libcfg.mk
## \brief	NXP Libraries Configuration.
##
## This makefile contains the rules to integrate NXP Libraries
## in Erika Enterprise as a stand-alone libraries.
##
## \author	Giuseppe Serano
## \date	2018

## Check the NXP Libraries selection

##
## S32 SDK
##
ifeq	($(call islibopt, OS_EE_LIB_S32_SDK), yes)

include	$(OS_EE_MK_BASE_DIR)/ee_nxp_linkcfg.mk

ifeq	($(and	\
		$(call iseeopt, OS_EE_ARCH_CORTEX_M),		\
		$(call iseeopt, OS_EE_ARCH_CORTEX_M_S32K1XX)	\
	), yes)

##
## Drivers
##
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/drivers/src/adc		\
$(S32_SDK_ROOT)/platform/drivers/src/clock/S32K1xx	\
$(S32_SDK_ROOT)/platform/drivers/src/cmp		\
$(S32_SDK_ROOT)/platform/drivers/src/crc		\
$(S32_SDK_ROOT)/platform/drivers/src/csec		\
$(S32_SDK_ROOT)/platform/drivers/src/edma		\
$(S32_SDK_ROOT)/platform/drivers/src/eim		\
$(S32_SDK_ROOT)/platform/drivers/src/erm		\
$(S32_SDK_ROOT)/platform/drivers/src/ewm		\
$(S32_SDK_ROOT)/platform/drivers/src/flexcan		\
$(S32_SDK_ROOT)/platform/drivers/src/flexio		\
$(S32_SDK_ROOT)/platform/drivers/src/ftm		\
$(S32_SDK_ROOT)/platform/drivers/src/lpi2c		\
$(S32_SDK_ROOT)/platform/drivers/src/lpit		\
$(S32_SDK_ROOT)/platform/drivers/src/lpspi		\
$(S32_SDK_ROOT)/platform/drivers/src/lptmr		\
$(S32_SDK_ROOT)/platform/drivers/src/lpuart		\
$(S32_SDK_ROOT)/platform/drivers/src/mpu		\
$(S32_SDK_ROOT)/platform/drivers/src/pdb		\
$(S32_SDK_ROOT)/platform/drivers/src/pins		\
$(S32_SDK_ROOT)/platform/drivers/src/power/S32K1xx	\
$(S32_SDK_ROOT)/platform/drivers/src/rtc		\
$(S32_SDK_ROOT)/platform/drivers/src/trgmux		\
$(S32_SDK_ROOT)/platform/drivers/src/wdog		\
$(S32_SDK_ROOT)/rtos/osif				\
$(INCLUDE_PATH)

ifeq	($(findstring S32K148, $(OS_EE_CORTEX_M_MCU)), S32K148)
INCLUDE_PATH :=	\
$(S32_SDK_ROOT)/platform/drivers/src/enet		\
$(S32_SDK_ROOT)/platform/drivers/src/quadspi		\
$(S32_SDK_ROOT)/platform/drivers/src/sai		\
$(INCLUDE_PATH)
endif	# OS_EE_CORTEX_M_MCU == S32K148

EE_SRCS_S32_SDK += platform/drivers/src/adc/adc_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/clock/clock_manager.c
EE_SRCS_S32_SDK += platform/drivers/src/clock/S32K1xx/clock_S32K1xx.c
EE_SRCS_S32_SDK += platform/drivers/src/cmp/cmp_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/cmp/cmp_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/crc/crc_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/crc/crc_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/csec/csec_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/csec/csec_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/edma/edma_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/edma/edma_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/edma/edma_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/eim/eim_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/eim/eim_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/erm/erm_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/erm/erm_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/ewm/ewm_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/flash/flash_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/flexcan/flexcan_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/flexcan/flexcan_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/flexcan/flexcan_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/flexio/flexio_common.c
EE_SRCS_S32_SDK += platform/drivers/src/flexio/flexio_i2c_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/flexio/flexio_i2s_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/flexio/flexio_spi_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/flexio/flexio_uart_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/ftm/ftm_common.c
EE_SRCS_S32_SDK += platform/drivers/src/ftm/ftm_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/ftm/ftm_ic_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/ftm/ftm_mc_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/ftm/ftm_oc_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/ftm/ftm_pwm_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/ftm/ftm_qd_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/interrupt/interrupt_manager.c
EE_SRCS_S32_SDK += platform/drivers/src/lin/lin_common.c
EE_SRCS_S32_SDK += platform/drivers/src/lin/lin_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lin/lin_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/lpi2c/lpi2c_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lpi2c/lpi2c_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/lpi2c/lpi2c_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/lpit/lpit_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lpit/lpit_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/lpspi/lpspi_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/lpspi/lpspi_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/lpspi/lpspi_master_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lpspi/lpspi_shared_function.c
EE_SRCS_S32_SDK += platform/drivers/src/lpspi/lpspi_slave_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lptmr/lptmr_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lptmr/lptmr_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/lpuart/lin_lpuart_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lpuart/lpuart_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/lpuart/lpuart_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/lpuart/lpuart_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/mpu/mpu_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/mpu/mpu_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/pdb/pdb_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/pdb/pdb_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/pins/pins_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/pins/pins_port_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/power/power_manager.c
EE_SRCS_S32_SDK += platform/drivers/src/power/S32K1xx/power_manager_S32K1xx.c
EE_SRCS_S32_SDK += platform/drivers/src/power/S32K1xx/power_pmc_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/power/S32K1xx/power_rcm_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/power/S32K1xx/power_smc_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/rtc/rtc_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/rtc/rtc_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/rtc/rtc_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/trgmux/trgmux_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/trgmux/trgmux_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/wdog/wdog_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/wdog/wdog_hw_access.c

ifeq	($(findstring S32K148, $(OS_EE_CORTEX_M_MCU)), S32K148)
EE_SRCS_S32_SDK += platform/drivers/src/enet/enet_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/enet/enet_hw_access.c
EE_SRCS_S32_SDK += platform/drivers/src/enet/enet_irq.c
EE_SRCS_S32_SDK += platform/drivers/src/flash_mx25l6433f/flash_mx25l6433f_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/quadspi/quadspi_driver.c
EE_SRCS_S32_SDK += platform/drivers/src/sai/sai_driver.c
endif	# OS_EE_CORTEX_M_MCU == S32K148

##
## Start-Up Code
##
EE_SRCS_S32_SDK += platform/devices/startup.c

ifeq	($(findstring S32K144, $(OS_EE_CORTEX_M_MCU)), S32K144)
EE_SRCS_S32_SDK += platform/devices/S32K144/startup/system_S32K144.c
endif	# OS_EE_CORTEX_M_MCU == S32K144

ifeq	($(findstring S32K148, $(OS_EE_CORTEX_M_MCU)), S32K148)
EE_SRCS_S32_SDK += platform/devices/S32K148/startup/system_S32K148.c
endif	# OS_EE_CORTEX_M_MCU == S32K148

ifeq	($(call islibopt, OS_EE_LIB_S32_SDK_SA), yes)

EE_OBJS_S32_SDK := 						       \
	$(addprefix $(OS_EE_OBJ_DIR)/,				       \
		$(patsubst %.c,%.c.o,				       \
			$(patsubst %.S,%.S.o,$(EE_SRCS_S32_SDK))       \
		)						       \
	)

LIBSRCS += $(EE_SRCS_S32_SDK)

S32_SDK_LIB := libs32sdk.a

$(OS_EE_LIB_DIR)/$(S32_SDK_LIB): $(EE_OBJS_S32_SDK)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^
	@echo "**************************************"
	@echo "* S32 SDK Library built successfully! *"
	@echo "**************************************"

OPT_LIBS += $(OS_EE_LIB_DIR)/$(S32_SDK_LIB)
ALL_LIBS += $(OS_EE_LIB_DIR)/$(S32_SDK_LIB)

else	# OS_EE_LIB_S32_SDK_SA

EE_SRCS += $(EE_SRCS_S32_SDK)

endif	# OS_EE_LIB_S32_SDK_SA

endif	# OS_EE_ARCH_CORTEX_M && OS_EE_ARCH_CORTEX_M_S32K1XX

endif	# OS_EE_LIB_S32_SDK
