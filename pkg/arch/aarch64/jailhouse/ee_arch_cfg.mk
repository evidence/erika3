# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
#
# Copyright (C) 2002-2017 Evidence Srl
#
# This file is part of ERIKA Enterprise.
#
# See LICENSE file.
# ###*E*###

## \file  ee_arch_cfg.mk
## \brief Architecture Build Configuration.
##
## This makefile contains the list of file for a specific Architecture to be
## compiled in Erika Enterprise library.
##
## \author  Errico Guidieri
## \date    2017

ifeq ($(call iseeopt, OSEE_PLATFORM_JAILHOUSE), yes)

EE_SRCS += ee_aarch64_header.S
EE_SRCS += ee_aarch64_boot.c
EE_SRCS += ee_aarch64_int.c
EE_SRCS += ee_aarch64_ctx.S
EE_SRCS += ee_aarch64_gtimer.c

ifeq ($(call iseeopt, OSEE_API_DYNAMIC), yes)
EE_SRCS += ee_std_hal_init.c
endif # OSEE_DYNAMIC_API

endif # OSEE_PLATFORM_JAILHOUSE
