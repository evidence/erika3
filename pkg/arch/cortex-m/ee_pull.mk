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

## \file	ee_pull.mk
## \brief	Pull file for ARM Cortex-M Architecture Module.
##
## This makefile contains the list of files to be pulled into Erika Enterprise
## project to support ARM Cortex-M Architecture Module.
##
## \author	Giuseppe Serano
## \date	2018

ifeq	($(call iseeopt, OS_EE_ARCH_CORTEX_M), yes)

OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_arch_rules.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_arch_cfg.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_arch_compiler_gcc.mk

OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_conf.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_arch_compiler_gcc.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_platform_types.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_get_kernel_and_core.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_hal.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_hal_internal_types.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_mcu_irq.h

OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_irq.h
ifeq	($(call iseeopt, OSEE_HAS_SYSTEM_TIMER), yes)
OS_EE_PULL_INC_FILES += \
		$(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_system_timer.h
endif	# OSEE_HAS_SYSTEM_TIMER
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_utils.h

ifeq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_S32K1XX), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_s32k1xx_irq.h
endif	# OS_EE_ARCH_CORTEX_M_S32K1XX

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_hal_internal.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_internal.h

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_nvic.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_irqstub.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_system.h

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_asm.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_irq_asm.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_irqstub.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_system.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_change_context.c
ifeq	($(call iseeopt, OSEE_HAS_SYSTEM_TIMER), yes)
OS_EE_PULL_SRC_FILES += \
		$(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_systick.h
OS_EE_PULL_SRC_FILES += \
		$(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_system_timer.c
endif	# OSEE_HAS_SYSTEM_TIMER
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_cortex_m_utils.c

ifeq	($(call iseeopt, OS_EE_ARCH_CORTEX_M_S32K1XX), yes)
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_s32k1xx_internal.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_s32k1xx_intvect.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/cortex-m/ee_s32k1xx_mcu.h
endif	# OS_EE_ARCH_CORTEX_M_S32K1XX

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/std/arch/ee_std_hal_init.c

endif	# OS_EE_ARCH_CORTEX_M
