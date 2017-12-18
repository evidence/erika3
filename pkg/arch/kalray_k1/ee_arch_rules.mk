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
## \author	Errico Guidieri
## \author	Giuseppe Serano
## \date	2016

ifeq ($(call iseeopt, OS_EE_BUILD), yes)

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

all: make_directories $(TARGET)
	@echo "**************************************************"
	@echo "* Erika Enterprise Libraries built successfully! *"
	@echo "**************************************************"

clean::
	@-rm -rf *.a *.map *.elf $(OS_EE_OBJ_DIR) $(OS_EE_LIB_DIR)
	@echo "**************************************************"
	@echo "* Erika Enterprise Libraries clean successfully! *"
	@echo "**************************************************"

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

$(OS_EE_LIB_DIR)/$(ERIKALIB): $(LIBEEOBJS)
	$(OS_EE_VERBOSE_PRINTAR) $(OS_EE_AR) $(OS_EE_COMP_AR_OPT) $@ $^

else	# (OS_EE_BUILD = yes)

# Products Prefix
TARGETNAME ?= mppa


# Add basic include paths
# [GS]: TO BE REMOVED!!!
#INCLUDE_PATH += $(call short_native_path, $(OS_EE_INC_BASE_DIR))
#INCLUDE_PATH += $(call short_native_path, $(abspath $(OS_EE_APP_BASE_DIR)))
#INCLUDE_PATH += $(call short_native_path, $(abspath $(OS_EE_APP_OUT_DIR)))

#EE_VPATH +=	$(call short_native_path,$(abspath $(OS_EE_APP_BASE_DIR))) \
		$(call short_native_path,$(abspath $(OS_EE_APP_OUT_DIR)))

#SRCS += $(sort $(OS_EE_APP_CFG_SRCS))

#vpath %.c	$(EE_VPATH)
#vpath %.S	$(EE_VPATH)
#vpath %.cpp	$(EE_VPATH)

.PHONY: clean-build
# [GS]: TO BE REMOVED!!!
#$(OBJDIRS):
#	@echo "MAKE_DIRECTORIES"
#	$(QUIET)mkdir -p $(OBJDIRS)

clean-build::
	@printf "CLEAN BUILD\n";
	@-rm -rf *.a *.map *.elf $(OBJDIR) $(LIBDIR)

#$(LIBBASE)/$(ERIKALIB):
#	$(MAKE) -C $(OS_EE_BASE_DIR) all

# Include compiler options and paths
#include $(MKBASE)/ee_compiler.mk
#include $(wildcard $(MKBASE)/ee_arch_compiler_*.mk)

TARGETNAME ?= mppa

# Multibin extension
MULTIBIN_SUFFIX ?= .mpk
# IO ELF suffix
IO_SUFFIX ?= _io.elf
# CLUSTER ELF suffix
ERIKA_SUFFIX ?= _erika.elf

# Products names
K1_MULTIBIN_NAME  ?= ${TARGETNAME}${MULTIBIN_SUFFIX}
K1_ERIKA_APP_NAME ?= ${TARGETNAME}${ERIKA_SUFFIX}
#K1_IO_APP_NAME    ?= ${TARGETNAME}${IO_SUFFIX} # Have to be provided outside

# Needed for Ubuntu/Debian since sh points to dash instead of bash...
SHELL := /bin/bash

platforms := hardware simulator

# Define weither we are using OSes or not. can be os/rtems/nodeos/bare
# If not present, default to os
system-name := os
## EG: Used to plug ERIKA
cluster-system := bare

# Common cflags and lflags (for all targets)
# These flags will be propagated through the hierarchy
# I cannot use -Werror for open mp unkown pragmas
# -Wbad-function-cast it bother too much with optimized preemption point.
cflags += ${CFLAGS_LOCAL}
lflags += -mhypervisor -lm

# The mppa-bin target is used to generate multibinary for specified target
mppa-bin := K1_MULTIBIN
K1_MULTIBIN-name := ${K1_MULTIBIN_APP_NAME}
# Define which binaries will composed multibin1
# Note that the first binary in the list defines the boot binary
K1_MULTIBIN-objs := ${K1_ERIKA_APP_NAME} ${K1_IO_APP_NAME}

# You can pass additionnal flags to "k1-create-multibinary" using the
# following command.
# for example, '-w ".*"' will active all tracepoints
#K1_MULTIBIN-flags := -w ".*"

################################################################################
#                          Cluster binaries
################################################################################
cluster-bin += ${K1_ERIKA_APP_NAME}

# Each *-srcs variable describe sources for the binaries
${K1_ERIKA_APP_NAME}-srcs += ${SRCS}

${K1_ERIKA_APP_NAME}-deps += ${OS_EE_LIB_BASE_DIR}/${ERIKALIB}

# Flags can be specified per binary
# FIX this better
${K1_ERIKA_APP_NAME}-cflags += ${OS_EE_DEFS_CC}


${K1_ERIKA_APP_NAME}-lflags += -g\
  -Wl,-Map="${K1_OUTPTDIR}/build/${K1_ERIKA_APP_NAME}.map"\
  -Wl,--defsym=USER_STACK_SIZE=0x2000 -Wl,--defsym=KSTACK_SIZE=0x1000\
  -L${OS_EE_LIB_BASE_DIR} -L${K1_OUTPTDIR}\
  -lvbsp -l${EELIB} -lmppaipc

################################################################################
#                          IO binaries
################################################################################
${K1_IO_APP_NAME}-lflags += -mcluster=ioddr -march=${arch} -mboard=${board}
  -mos=rtems\
  -lm  -lmppapower -lmppanoc -lmpparouting -lpcie_queue -lmppaipc\
  -Wl,-Map="${K1_OUTPTDIR}/build/${K1_IO_APP_NAME}.map

# Special hooks for user makefile

# Hooks specified in help-hooks are rules which will be called after displaying
# the default help
help-hooks +=
# Pre build hooks will be called before build
pre-build-hooks +=
# Post build hooks will be called after build
post-build-hooks +=
# Clean Hooks
clean-hooks += clean-build

# Finally, include the Kalray Makefile which will instantiate the rules
# and do the work
include ${K1_TOOLCHAIN_DIR}/share/make/Makefile.kalray

endif # (OS_EE_BUILD = yes)

