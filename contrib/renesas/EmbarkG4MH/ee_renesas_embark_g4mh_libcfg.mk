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

## \file	ee_renesas_embark_g4mh_libcfg.mk
## \brief	Renesas Embark G4MH Software Libraries Configuration.
##
## This makefile contains the rules to integrate Renesas Embark Ex2 Software
## in Erika Enterprise as a stand-alone libraries.
##
## \author	Errico Guidieri
## \date	2018

## Check the Renesas Embark G4MH Software

ifeq	($(call islibopt, OSEE_LIB_EMBARK_G4MH), yes)

include	$(OS_EE_MK_BASE_DIR)/ee_renesas_embark_g4mh_linkcfg.mk

ifeq	($(and										\
		$(call iseeopt, OSEE_ARCH_RH850),			\
		$(call iseeopt, OSEE_ARCH_RH850_G4MH)	\
	), yes)

#Prepare the Multi-Line Variables to be called to handle each driver
define lib_embark_g4mh_drv

OSEE_SRCS_EMBARK_G4MH_$(1)_$(OSEE_RH850_MCU) += $$(subst $$(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/$(OSEE_RH850_MCU)/,, $$(wildcard $$(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/$(OSEE_RH850_MCU)/*.wr.asm))
OSEE_SRCS_EMBARK_G4MH_$(1)_$(OSEE_RH850_MCU) += $$(subst $$(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/$(OSEE_RH850_MCU)/,, $$(wildcard $$(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/$(OSEE_RH850_MCU)/*.c))

OSEE_SRCS_EMBARK_G4MH_$(1) += $$(subst $(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/,, $$(wildcard $(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/*.wr.asm))
OSEE_SRCS_EMBARK_G4MH_$(1) += $$(subst $(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/,, $$(wildcard $(OSEE_EMBARK_G4MH_FILES)/Drivers/$(1)/*.c))

OSEE_SRCS_EMBARK_G4MH_$(1) := $$(filter-out $$(OSEE_SRCS_EMBARK_G4MH_$(1)_$(OSEE_RH850_MCU)), $$(OSEE_SRCS_EMBARK_G4MH_$(1)))

OSEE_SRCS_EMBARK_G4MH += $$(addprefix Drivers/$(1)/$(OSEE_RH850_MCU)/, $$(OSEE_SRCS_EMBARK_G4MH_$(1)_$(OSEE_RH850_MCU)))
OSEE_SRCS_EMBARK_G4MH += $$(addprefix Drivers/$(1)/, $$(OSEE_SRCS_EMBARK_G4MH_$(1)))

endef # lib_embark_g4mh_drv

# Prepare the list of drivers of EMBARK G4MH to be built
OSEE_SRCS_DIRS_EMBARK_G4MH := RH850 $(OSEE_SRCS_DIRS_EMBARK_G4MH)

# Generate the list of files of all drivers to be built
$(foreach drv,$(OSEE_SRCS_DIRS_EMBARK_G4MH),$(eval $(call lib_embark_g4mh_drv,$(drv))))

ifeq	($(call islibopt, OSEE_LIB_EMBARK_G4MH_SA), yes)

ALL_LIBS += $(OS_EE_LIB_DIR)/$(EMBARK_G4MH_LIB)

OSEE_OBJS_EMBARK_G4MH := 										\
	$(addprefix $(OS_EE_OBJ_DIR)/,								\
		$(patsubst %.c,%.c.o,									\
			$(patsubst %.asm,%.asm.o,							\
				$(patsubst %.S,%.S.o,$(OSEE_SRCS_EMBARK_G4MH))	\
			)													\
		)														\
	)

$(OS_EE_LIB_DIR)/$(EMBARK_G4MH_LIB): $(OSEE_OBJS_EMBARK_G4MH)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^
	@echo "******************************************"
	@echo "* Embark G4MH Library built successfully! *"
	@echo "******************************************"

else	# OSEE_LIB_EMBARK_G4MH

EE_SRCS += $(OSEE_SRCS_EMBARK_G4MH)

endif	# OSEE_LIB_EMBARK_G4MH

endif	# OSEE_LIB_EMBARK_G4MH && OSEE_ARCH_RH850_G4MH

endif	# OSEE_LIB_EMBARK_G4MH
