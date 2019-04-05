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

## \file	ee_fatfs_libcfg.mk
## \brief	FatFs Library Configuration.
##
## This makefile contains the rules to integrate the FatFs stack in Erika
## Enterprise as a stand-alone library.
##
## \author	Luca Cuomo
## \date	2019

ifeq	($(call islibopt, OS_EE_LIB_FATFS), yes)

include	$(OS_EE_MK_BASE_DIR)/ee_fatfs_linkcfg.mk

EE_SRCS_FATFS += source/ff.c
EE_SRCS_FATFS += source/ffsystem.c
EE_SRCS_FATFS += source/ffunicode.c

ifeq	($(call islibopt, OS_EE_LIB_FATFS_DISKIO_MEMORY), yes)
EE_SRCS_FATFS += ffmem.c
endif

EE_OBJS_FATFS := 							       \
	$(addprefix $(OS_EE_OBJ_DIR)/,					       \
		$(patsubst %.c,%.c.o,				       \
			$(patsubst %.c,%.c.o,				       \
				$(patsubst %.S,%.S.o,$(EE_SRCS_FATFS))   \
			)						       \
		)							       \
	)

LIBSRCS += $(EE_SRCS_FATFS)

FATFSLIB = fatfs
FATFS_LIB := lib$(FATFSLIB).a

$(OS_EE_LIB_DIR)/$(FATFS_LIB): $(EE_OBJS_FATFS)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^
	@echo "****************************************"
	@echo "* FatFs library built successfully! *"
	@echo "****************************************"

OPT_LIBS += $(OS_EE_LIB_DIR)/$(FATFS_LIB)
ALL_LIBS += $(OS_EE_LIB_DIR)/$(FATFS_LIB)

endif	# OS_EE_LIB_FATFS
