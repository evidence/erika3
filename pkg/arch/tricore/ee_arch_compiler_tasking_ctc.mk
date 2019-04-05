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

## \file    ee_arch_compiler_tasking_ctc.mk
## \brief   Architecture TASKING CTC Compiler.
##
## This makefile contains the list of TASKING CTC Compiler variables for a
## specific Architecture in Erika Enterprise.
##
## \author  Errico Guidieri
## \date    2019

##
## Compiler related options
##

# CCTCBIN variable, (if not empty), must end with separator
ifneq ($(CCTCBIN),)
#Assure the existence of the trailing slash eventually remove it with realpath
#and adding it back
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
CCTCBINLOC := $(realpath $(shell cygpath `cygpath -ms '$(CCTCBIN)'`))/
else
CCTCBINLOC := $(realpath $(CCTCBIN))/
endif # OS_EE_RTD_BUILD_ENV_CYGWIN
endif # CCTCBIN

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
ALLINCPATH += $(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

EE_OBJDUMP ?= $(CCTCBINLOC)hldumptc

EE_LINK ?= $(CCTCBINLOC)cctc

OS_EE_AS ?= $(CCTCBINLOC)cctc

EE_CC ?= $(CCTCBINLOC)cctc

EE_CXX ?= $(CCTCBINLOC)cctc

OS_EE_AR ?= $(CCTCBINLOC)artc

EE_SIZE ?= $(CCTCBINLOC)elfsize

## OPT_CC are the options for TASKING CTC TriCore C compiler invocation
# -t keep temporary files
# --source mix assembly and source code (too distracting)
OPT_CC += -c -C$(OSEE_TRICORE_MCU) -t -D__CPU__=$(OSEE_TRICORE_MCU)\
 -D__CPU_$(OSEE_TRICORE_MCU_UC)__ --no-preprocessing-only -E+comments,-noline\
 --iso=99 --language=+gcc,-volatile,+strings --fp-model=3
ifneq ($(call iseeopt, OSEE_TASKING_CTC_MINIMAL_OPTS), yes)
OPT_CC += -Wa-Hsfr/reg$(OSEE_TRICORE_MCU).def
endif	# !OSEE_TASKING_CTC_MINIMAL_OPTS
ifeq ($(or\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),\
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))\
), yes)
OPT_CC += -g -O1
else
OPT_CC += -g -O2
endif

# Specific option from the application makefile
OPT_CC += $(CFLAGS)

ifeq ($(call iseeopt,  OSEE_TC_2G), yes)
# N.B. abs18 addressing support is broken for AURIX 2G,
# assure to turn it off
OPT_CC += --default-near-size=0
endif # OSEE_TC_2G

# Move the preprocessed file in output dir
CCEXTRASTUFF = && mv $(subst .c.o,.pre,$(notdir $@)) $(subst .c.o,.c.i,$@)

## OPT_CXX are the options for TriCore C++ compiler invocation
# --source mix assembly and source code (too distracting)
OPT_CXX += -c -C$(OSEE_TRICORE_MCU) -t -D__CPU__=$(OSEE_TRICORE_MCU)\
 -D__CPU_$(OSEE_TRICORE_MCU_UC)__ --no-preprocessing-only -E+comments,-noline\
 --c++03 --language=+gcc,-volatile,+strings --fp-model=3\
 --io-streams
ifneq	($(call iseeopt, OSEE_TASKING_CTC_MINIMAL_OPTS), yes)
OPT_CXX += --default-near-size=8 -Wa-Hsfr/reg$(OSEE_TRICORE_MCU).def\
 --instantiate=used
endif	# !OSEE_TASKING_CTC_MINIMAL_OPTS
ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)), \
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG)) \
), yes)
OPT_CXX += -g -O1
else
OPT_CXX += -g -O2
endif

# Specific option from the application makefile
OPT_CXX += $(CFLAGS) $(CXXFLAGS)

ifeq ($(call iseeopt,  OSEE_TC_2G), yes)
# N.B. abs18 addressing support is broken for AURIX 2G,
# assure to turn it off
OPT_CXX += --default-near-size=0
endif # OSEE_TC_2G

# Move the preprocessed file in output dir
CXXEXTRASTUFF =\
 && mv $(subst .cpp.o,.pre,$(notdir $@)) $(subst .cpp.o,.cpp\.i,$@)

## OS_EE_AS_OPT are the options for TriCore assembler invocation
#-t keep temporary files
OS_EE_AS_OPT = -c -C$(OSEE_TRICORE_MCU) -t -D__CPU__=$(OSEE_TRICORE_MCU)\
 -D__CPU_$(OSEE_TRICORE_MCU_UC)__ -Wa-Hsfr/reg$(OSEE_TRICORE_MCU).def\
 -Wa-gAHLs --emit-locals=-equs,-symbols\
 -Wa-Ogs -Wa--error-limit=42
ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)), \
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG)) \
), yes)
OS_EE_AS_OPT += -g -O1 -Wa--debug-info=+smart
else
OS_EE_AS_OPT += -g -O2 -Wa-gAHLs
endif

OS_EE_AS_OPT += $(ASFLAGS)

# OS_EE_AR_OPT represents the options for archiver invocation
OS_EE_AR_OPT = -r -c
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_AR_OPT += -v
endif	# OS_EE_VERBOSE

# OSEE_DUMP_OPT represents the options for disassembler invocation
# --dump-format=3 means everything
OSEE_DUMP_OPT = --dump-format=3

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_DEFS_AS   += -DOS_EE_BUILD
OS_EE_DEFS_CC   += -DOS_EE_BUILD
OS_EE_DEFS_CXX  += -DOS_EE_BUILD
endif

ifeq ($(call iseeopt,  OSEE_TC_LINK_BMHD), yes)
OSEE_TRICORE_LINK_BMHD := -Wl-DOSEE_TC_LINK_BMHD
endif #OSEE_T C_LINK_BMHD

# OPT_LINK represents the options for TASKING CTC linker invocation
# --munch To add information about initialization and termination routines
# (e.g. C++ global constructors and destructors)
OSEE_LINKER_SCRIPT ?= $(call short_native_path,$(abspath $(OS_EE_MK_BASE_DIR)/ee_tc_tasking_flash.lsl))
OPT_LINK += -C$(OSEE_TRICORE_MCU) --lsl-core=vtc --lsl-file=$(OSEE_LINKER_SCRIPT)\
 -D__CPU__=$(OSEE_TRICORE_MCU) -Wl-D__PROC_$(OSEE_TRICORE_MCU_UC)__ $(OSEE_TRICORE_LINK_BMHD)\
 -Wl-OtxycL -Wl--map-file=$(TARGET_NAME).xml:XML -Wl-mcdfiklmnoqrsu --munch
#OPT_LINK += $(OPT_UNDEFINED) $(OPT_LINK_EXTRA)

OPT_LINK += $(LDFLAGS)

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
# the EE library is built in the current directory
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
LIBDEP += lib/$(ERIKALIB)
else	# OS_EE_BUILD
OPT_LIBS += -L$(call short_native_path,$(abspath $(OS_EE_LIB_BASE_DIR)))
#libee.a and user libs must be the first of the list to be the first picked to
#get symbols
OPT_LIBS += -l$(EELIB) $(LIBS)
OPT_LIBS +=-lstlsx_fpu -lcpsx_fpu -lcs_fpu -lfp_fpu -lrt
LIBDEP += $(OS_EE_LIB_BASE_DIR)/$(ERIKALIB)
endif	# OS_EE_BUILD

# Automatic dependency generation
ifeq ($(call iseeopt, OS_EE_NO_DEPS), yes)
OS_EE_DEP_OPT =
OS_EE_MK_DEPS =
else	# OS_EE_NO_DEPS
# Create dependency for all headers, and add a target for each header
OS_EE_DEP_OPT = --dep-file=$(call native_path,$(subst .o,.d_tmp,$(@))) -Wc--make-target=$(@)
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
# Dependencies on Windows need path translation and quote remotion
OS_EE_MK_DEPS = sed -e 's_"__g' -e 's_\\\(.\)\(.\)_/\1\2_g' \
	-e 's_\<\([a-zA-Z]\):/_/cygdrive/\l\1/_g' < $1_tmp > $1 && rm $1_tmp
else	# OS_EE_RTD_BUILD_ENV_CYGWIN
OS_EE_MK_DEPS = mv $1_tmp $1
endif	# OS_EE_RTD_BUILD_ENV_CYGWIN
endif	# OS_EE_NO_DEPS

# Erika Library.
ERIKALIB = $(ERIKALIB_NAME).a

# Define the TARGET
TARGET_NAME ?= erika3app

# Add application file to dependencies
ifneq ($(call iseeopt, OS_EE_BUILD), yes)
export APP_TARGETS := $(TARGET_NAME).dump
$(info APP_TARGETS=$(APP_TARGETS))
endif	# !OS_EE_BUILD

