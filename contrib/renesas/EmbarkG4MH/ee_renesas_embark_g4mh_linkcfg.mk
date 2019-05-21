# ###*B*###
# Erika Enterprise, version 3
# 
# Copyright (C) 2017 - 2019 Evidence s.r.l.
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

## \file	ee_renesas_embark_g4mh_linkcfg.mk
## \brief	Renesas Embark G4MH Software Libraries Link Configuration.
##
## This makefile contains the rules to integrate Renesas Embark G4MH Software
## stand-alone libraries in an Erika Enterprise Application.
##
## \author	Errico Guidieri
## \date	2018

## Check the Renesas Embark G4MH Software
ifeq	($(call islibopt, OSEE_LIB_EMBARK_G4MH), yes)

ifeq	($(and	\
		$(call iseeopt, OSEE_ARCH_RH850),	\
		$(call iseeopt, OSEE_ARCH_RH850_G4MH)	\
	), yes)

ifndef	OSEE_EMBARK_G4MH_FILES
$(error OSEE_EMBARK_G4MH_FILES not specified)
endif	# OSEE_EMBARK_G4MH_FILES

# THIS IS A MUST !!! Under Cygwin OSEE_EMBARK_G4MH_FILES have to be provided as
# cygwin path to make happy other ERIKA's makefiles (I have no idea why,
# the build system is too complicated for me), but INCLUDE_PATH
# have to be native, since is used by native compilers.
OSEE_EMBARK_G4MH_FILES := $(call short_native_path, $(OSEE_EMBARK_G4MH_FILES))

EE_VPATH += $(OSEE_EMBARK_G4MH_FILES)

##
## Embark G4MH Drivers Include Paths for application
##
INCLUDE_PATH += $(call short_native_path, $(OSEE_EMBARK_G4MH_FILES)/Drivers/RH850/$(OSEE_RH850_MCU))
INCLUDE_PATH += $(call short_native_path, $(OSEE_EMBARK_G4MH_FILES)/Drivers/RH850)

ifneq ($(OSEE_SRCS_DIRS_EMBARK_G4MH),)
OSEE_SRCS_DIRS_EMBARK_G4MH_COMPLETED_AND_FILTERED += $(foreach dir, $(OSEE_SRCS_DIRS_EMBARK_G4MH), $(wildcard $(OSEE_EMBARK_G4MH_FILES)/Drivers/$(dir)/$(OSEE_RH850_MCU)) $(wildcard $(OSEE_EMBARK_G4MH_FILES)/Drivers/$(dir)))

INCLUDE_PATH += $(foreach dir, $(OSEE_SRCS_DIRS_EMBARK_G4MH_COMPLETED_AND_FILTERED), $(call short_native_path, $(dir)))
endif

##
## Start-Up Code
##
ifneq	($(if $(filter OS_EE_BUILD,$(OS_EE_OPT)),yes,), yes)
OPT_LINK += -e _g_g4mh_DirVec
endif	# !OS_EE_BUILD

ifeq	($(call islibopt, OSEE_LIB_EMBARK_G4MH_SA), yes)

EMBARK_G4MH = embark_g4mh
EMBARK_G4MH_LIB := lib$(EMBARK_G4MH).a

ifneq	($(if $(filter OS_EE_BUILD,$(OS_EE_OPT)),yes,), yes)
OPT_LIBS += -l$(EMBARK_G4MH)
endif	# !OS_EE_BUILD
endif	# OS_EE_LIB_S32_SDK_SA

endif	# OSEE_ARCH_RH850 && OSEE_ARCH_RH850_G4MH

endif	# OSEE_LIB_EMBARK_G4MH
