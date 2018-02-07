# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
#
# Copyright (C) 2002-2017 Evidence Srl
#
# This file is part of ERIKA Enterprise.
#
# See LICENSE file.
# ###*E*###

## \file  ee_pull.mk
## \brief Pull file for AArch64 Architecture Module.
##
## This makefile contains the list of files to be pulled into Erika Enterprise
## project to support AArch64 Architecture Module.
##
## \author  Errico Guidieri
## \date    2017

ifeq	($(call iseeopt, OSEE_ARCH_AARCH64), yes)

ifeq	($(call iseeopt, OSEE_PLATFORM_JAILHOUSE), yes)
OSEE_PLATFORM := jailhouse
endif

ifeq	($(call iseeopt, OSEE_PLATFORM_VIBRANTE), yes)
OSEE_PLATFORM := vibrante
endif

ifndef OSEE_PLATFORM
$(error "Not valid platform provided!")
endif

OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/$(OSEE_PLATFORM)/ee_arch_cfg.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/$(OSEE_PLATFORM)/ee_arch_compiler_gcc.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/$(OSEE_PLATFORM)/ee_aarch64.lds
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_arch_rules.mk

OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_conf.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_arch_compiler_gcc.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_platform_types.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_get_kernel_and_core.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_hal.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_hal_internal_types.h

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_aarch64_boot.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_aarch64_header.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_aarch64_int.c
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_aarch64_ctx.S
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_aarch64_gtimer.c

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_hal_internal.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/ee_internal.h

ifneq ($(OSEE_AARCH64_SOC),)
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/aarch64/soc/$(OSEE_AARCH64_SOC)/ee_aarch64_gic.h
endif # OSEE_AARCH64_SOC

OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/std/arch/ee_std_hal_init.c

endif	# OSEE_ARCH_AARCH64
