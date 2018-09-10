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

## \file  ee_arch_rules.mk
## \brief Architecture Build Rules.
##
## This makefile contains the list of rules to build Erika Enterprise libraries
## and applications for a specific Architecture.
##
## \author  Errico Guidieri
## \date    2017

##
## Compute common variables
##

COMPUTED_ALLINCPATH := $(ALLINCPATH)
COMPUTED_OPT_LINK := $(OPT_LINK)
OS_EE_COMP_AS_OPT := $(OS_EE_AS_OPT)
OS_EE_COMP_AR_OPT := $(OS_EE_AR_OPT)
COMPUTED_OPT_CC := $(OPT_CC)
COMPUTED_OPT_CXX := $(OPT_CXX)

SOURCEFILE = $(call native_path,$<)
TARGETFILE = $(call native_path,$@)

##
## Main rules: all clean
##

.PHONY: all clean

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
all:: make_directories $(TARGET)
	@echo "**************************************************"
	@echo "* Erika Enterprise Libraries built successfully! *"
	@echo "**************************************************"

clean::
	@-rm -rf *.a *.map *.elf *.bin $(OS_EE_OBJ_DIR) $(OS_EE_LIB_DIR)
	@echo "**************************************************"
	@echo "* Erika Enterprise Libraries clean successfully! *"
	@echo "**************************************************"
else	# OS_EE_BUILD
all:: make_directories $(TARGET)
	@echo "****************************************************"
	@echo "* Erika Enterprise Application built successfully! *"
	@echo "****************************************************"

clean::
	@-rm -rf *.a *.map *.elf *.bin $(OS_EE_OBJ_DIR) $(OS_EE_LIB_DIR)
	@echo "****************************************************"
	@echo "* Erika Enterprise Application clean successfully! *"
	@echo "****************************************************"
endif	# OS_EE_BUILD

#
# --------------------------------------------------------------------------
#


##
## ELF file creation
##

$(TARGET_NAME).elf: $(OBJS) $(LIBDEP)
	$(VERBOSE_PRINTLD) $(EE_LINK) $(COMPUTED_OPT_LINK) $(OBJS) \
	-o $(TARGETFILE) $(OPT_LIBS)
	$(QUIET)$(EE_SIZE) $(TARGETFILE)

##
## BIN file creation
##

$(TARGET_NAME).bin: $(TARGET_NAME).elf
	$(EE_OBJCOPY) -O binary $< $@

$(TARGET_NAME).dump: $(TARGET_NAME).elf
	$(EE_OBJDUMP) -C -t -x -S $< > $@

##
## OBJ files creation
##

$(OS_EE_OBJ_DIR)/%.S.o: %.S
	$(OS_EE_VERBOSE_PRINTAS) $(OS_EE_AS) $(OS_EE_DEFS_AS) $(COMPUTED_ALLINCPATH) \
	$(OS_EE_COMP_AS_OPT) $(OS_EE_DEP_OPT) -o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call OS_EE_MK_DEPS, $(subst .o,.d,$(@)))

$(OS_EE_OBJ_DIR)/%.c.o: %.c
	$(VERBOSE_PRINTCC) $(EE_CC) $(OS_EE_DEFS_CC) $(COMPUTED_ALLINCPATH) \
	$(COMPUTED_OPT_CC) $(OS_EE_DEP_OPT) -o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call OS_EE_MK_DEPS, $(subst .o,.d,$(@)))

$(OS_EE_OBJ_DIR)/%.cpp.o: %.cpp
	$(VERBOSE_PRINTCXX) $(EE_CXX) $(OS_EE_DEFS_CXX) $(COMPUTED_ALLINCPATH) \
	$(COMPUTED_OPT_CXX) $(OS_EE_DEP_OPT) -o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call OS_EE_MK_DEPS, $(subst .o,.d,$(@)))

##
## EE Library
##

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
$(OS_EE_LIB_DIR)/$(ERIKALIB): $(LIBEEOBJS)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^
else	# OS_EE_BUILD
$(OS_EE_LIB_BASE_DIR)/$(ERIKALIB):
	@$(MAKE) -C $(OS_EE_BASE_DIR) all
endif	# OS_EE_BUILD
