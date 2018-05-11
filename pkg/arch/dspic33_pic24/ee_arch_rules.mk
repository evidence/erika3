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

## \file	ee_arch_rules.mk
## \brief	Architecture Build Rules.
##
## This makefile contains the list of rules to build Erika Enterprise libraries
## and applications for a specific Architecture.
##
## \author	Giuseppe Serano
## \date	2018

##
## Compute common variables
##

OS_EE_COMP_ALLINCPATH	:= $(ALLINCPATH)
OS_EE_COMP_OPT_LINK	:= $(OS_EE_OPT_LINK)
OS_EE_COMP_OPT_AR	:= $(OS_EE_OPT_AR)
OS_EE_COMP_OPT_AS	:= $(OS_EE_OPT_AS)
OS_EE_COMP_OPT_CC	:= $(OS_EE_OPT_CC)
OS_EE_COMP_OPT_BIN2HEX	:= $(OS_EE_OPT_BIN2HEX)

##
## Target and Source file.
##

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
	@-rm -rf *.a *.map *.elf $(OS_EE_OBJ_DIR) $(OS_EE_LIB_DIR)
	@-rm -rf *.eep *.hex *.lss *.srec
	@echo "**************************************************"
	@echo "* Erika Enterprise Libraries clean successfully! *"
	@echo "**************************************************"
else	# OS_EE_BUILD
all:: make_directories $(TARGET) dbg
	@echo "****************************************************"
	@echo "* Erika Enterprise Application built successfully! *"
	@echo "****************************************************"

clean::
	@-rm -rf *.a *.map *.elf $(OS_EE_OBJ_DIR) $(OS_EE_LIB_DIR)
	@-rm -rf *.eep *.hex *.lss *.srec
	@echo "****************************************************"
	@echo "* Erika Enterprise Application clean successfully! *"
	@echo "****************************************************"
endif	# OS_EE_BUILD

##
## Debugger targets
##
ifneq ($(call iseeopt, OS_EE_BUILD), yes)

DBG_TARGETS := ee_dspic33_pic24_mdb.cmd

.PHONY: all clean

dbg: $(DBG_TARGETS)

ee_dspic33_pic24_mdb.cmd: $(OS_EE_DBG_BASE_DIR)/ee_dspic33_pic24_mdb.cmd
	@echo "GEN $@ from $<"
	$(QUIET)sed	\
	-e 's:#OS_EE_DSPIC33_PIC24_MCU#:$(OS_EE_DSPIC33_PIC24_MCU):g'	\
	-e 's:#OS_EE_DSPIC33_PIC24_DBG#:$(OS_EE_DSPIC33_PIC24_DBG):g'	\
	-e 's:#OS_EE_DSPIC33_PIC24_TARGET_NAME#:$(TARGET_NAME):g'	\
	$< > $@

endif	# OS_EE_BUILD

#
# --------------------------------------------------------------------------
#

##
## HEX file creation
##

$(TARGET_NAME).hex: $(TARGET_NAME).elf
	$(VERBOSE_PRINTHEX) $(OS_EE_BIN2HEX) $(SOURCEFILE) \
	$(OS_EE_COMP_OPT_BIN2HEX)

##
## ELF file creation
##

$(TARGET_NAME).elf: $(OBJS) $(LIBDEP)
	$(VERBOSE_PRINTLD) $(OS_EE_LINK) $(OS_EE_COMP_OPT_LINK) $(OBJS) \
	-o $(TARGETFILE) $(OS_EE_OPT_LIBS)

##
## OBJ files creation
##

$(OS_EE_OBJ_DIR)/%.s.o: %.s
	$(OS_EE_VERBOSE_PRINTAS) $(OS_EE_AS) $(OS_EE_DEFS_AS) \
	$(OS_EE_COMP_ALLINCPATH) $(OS_EE_COMP_OPT_AS) $(OS_EE_DEP_OPT) \
	-o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call OS_EE_MK_DEPS, $(subst .o,.d,$(@)))

$(OS_EE_OBJ_DIR)/%.S.o: %.S
	$(OS_EE_VERBOSE_PRINTAS) $(OS_EE_AS) $(OS_EE_DEFS_AS) \
	$(OS_EE_COMP_ALLINCPATH) $(OS_EE_COMP_OPT_AS) $(OS_EE_DEP_OPT) \
	-o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call OS_EE_MK_DEPS, $(subst .o,.d,$(@)))

$(OS_EE_OBJ_DIR)/%.c.o: %.c
	$(VERBOSE_PRINTCC) $(OS_EE_CC) $(OS_EE_DEFS_CC) \
	$(OS_EE_COMP_ALLINCPATH) $(OS_EE_COMP_OPT_CC) $(OS_EE_DEP_OPT) \
	-o $(TARGETFILE) $(SOURCEFILE)
	$(QUIET)$(call OS_EE_MK_DEPS, $(subst .o,.d,$(@)))

##
## EE Library
##

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
$(OS_EE_LIB_DIR)/$(ERIKALIB): $(LIBEEOBJS)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_OPT_AR) $@ $^
else	# OS_EE_BUILD
$(OS_EE_LIB_BASE_DIR)/$(ERIKALIB):
	@$(MAKE) -C $(OS_EE_BASE_DIR) all
endif	# OS_EE_BUILD
