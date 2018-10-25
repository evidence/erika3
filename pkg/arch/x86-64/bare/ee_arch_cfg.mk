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

## \file	ee_arch_cfg.mk
## \brief	Architecture Module Configuration.
##
## This makefile contains the list of file for a specific Architecture to be
## compiled in Erika Enterprise library.
##
## \author	Ida Savino
## \date	2018

ifeq	($(call iseeopt, OSEE_ARCH_X86_64), yes)

EE_SRCS += ee_x86_64_startup.S
EE_SRCS += ee_x86_64_boot.c
EE_SRCS += ee_x86_64_ctx.S
EE_SRCS += ee_x86_64_libc_syscall.c

EE_SRCS += ee_x86_64_memory_mgmt.c

EE_SRCS += ee_x86_64_int.c
EE_SRCS += ee_x86_64_apic.c
EE_SRCS += ee_x86_64_ioapic.c

EE_SRCS += src/ee_uart.c
EE_SRCS += src/ee_pci.c
ifeq ($(call iseeopt, OSEE_API_DYNAMIC), yes)
	EE_SRCS += ee_std_hal_init.c
endif # OSEE_DYNAMIC_API

ifeq ($(call iseeopt, OSEE_HAS_SYSTEM_TIMER), yes)
EE_SRCS += ee_x86_64_system_timer.c
endif # OSEE_DYNAMIC_API

endif	# OSEE_ARCH_X86_64
