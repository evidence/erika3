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

## \file  ee_pull.mk
## \brief Pull file for Renesas RH850 Architecture Module.
##
## This makefile contains the list of files to be pulled into Erika Enterprise
## project to support Renesas RH850 Architecture Module.
##
## \author  Errico Guidieri
## \date    2018

ifeq ($(call iseeopt, OSEE_ARCH_RH850), yes)

OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_arch_rules.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_arch_cfg.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_arch_compiler_wr_diab.mk

OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_arch_override.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_conf.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_arch_compiler_wr_diab.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_platform_types.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_get_kernel_and_core.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_hal.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_hal_irq.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_hal_internal_types.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_hal_mc.h

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_hal_internal.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_internal.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_rh850_ctx_wr_diab.S
ifeq ($(call iseeopt, OSEE_ARCH_RH850_G4MH), yes)
ifneq ($(OSEE_RH850_MCU),)
# wildcard filters unsupported derivatives
OS_EE_PULL_MK_FILES += $(wildcard $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/$(OSEE_RH850_MCU)/ee_$(OSEE_RH850_MCU).wr.ld)
endif
ifneq ($(call islibopt, OSEE_LIB_EMBARK_G4MH), yes)
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/ee_rh850_ei_ref_table_wr_diab.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/ee_rh850_ei_ref_table_pe1_wr_diab.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/ee_rh850_ei_ref_table_pe2_wr_diab.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/ee_rh850_ei_ref_table_pe3_wr_diab.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/ee_rh850_ei_ref_table_pe4_wr_diab.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/ee_rh850_ei_ref_table_pe5_wr_diab.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/mcu/g4mh/ee_rh850_ei_wrapper_ctx_wr_diab.hs
endif # !OSEE_LIB_EMBARK_G4MH
endif # OSEE_ARCH_RH850_G4MH

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_hal_mc_internal.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_rh850_hal.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_rh850_hal_mc.c
ifeq ($(call iseeopt, OSEE_WR_DIAB), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/ee_os_mem_map_wr_diab.h
endif # OSEE_WR_DIAB
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/Os_MemMap.h

ifeq ($(call iseeopt, OSEE_API_DYNAMIC), yes)
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/std/arch/ee_std_hal_init.c
endif # OSEE_DYNAMIC_API
ifeq	($(call islibopt, OSEE_LIB_EMBARK_G4MH), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/embark_g4mh/ee_rh850_embark_g4mh.h
OS_EE_PULL_INC_FILES += $(OS_EE_BASE_DIR)/$(OS_EE_PULL_DIR)/r_g4mh_cfg.inc

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/rh850/embark_g4mh/ee_rh850_embark_g4mh.c
endif

endif # OSEE_ARCH_RH850
