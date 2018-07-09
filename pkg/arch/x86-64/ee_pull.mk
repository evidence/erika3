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
## \brief	Pull file for x86-64 Architecture Module.
##
## This makefile contains the list of files to be pulled into Erika Enterprise
## project to support x86-64 Architecture Module.
##
## \author	Michele Pes
## \date	2017

ifeq ($(call iseeopt, OSEE_ARCH_X86_64), yes)

ifeq ($(call iseeopt, OSEE_PLATFORM_JAILHOUSE), yes)
OSEE_PLATFORM := jailhouse
endif

ifndef OSEE_PLATFORM
$(error "Not valid platform provided!")
endif

OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_arch_rules.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/$(OSEE_PLATFORM)/ee_arch_cfg.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/$(OSEE_PLATFORM)/ee_arch_compiler_gcc.mk

OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_conf.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_arch_override.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_arch_compiler_gcc.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_platform_types.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_get_kernel_and_core.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_hal.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_hal_internal_types.h

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/$(OSEE_PLATFORM)/ee_x86_64_boot.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/std/arch/ee_std_hal_init.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_x86_64_int.c

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_x86_64_ctx.S

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_hal_internal.h

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/ee_internal.h

ifneq ($(OSEE_X86_64_BOARD),)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/$(OSEE_X86_64_BOARD)/ee_board.h
endif # OSEE_X86_64_BOARD

ifeq ($(call iseeopt, OSEE_HAS_SYSTEM_TIMER), yes)
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/x86-64/$(OSEE_PLATFORM)/ee_x86_64_apic_timer.c
endif # OSEE_HAS_SYSTEM_TIMER

endif # OSEE_ARCH_X86_64
