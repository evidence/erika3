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

## \file    ee_arch_compiler_wr_diab.mk
## \brief   RH850 Architecture Wind River Diab Compiler.
##
## This makefile contains the list of Wind River Diab Compiler variables for 
## RH850 Architecture in Erika Enterprise.
##
## \author  Errico Guidieri
## \date    2018

##
## Compiler related options
##

# WIND_DIAB_PATH variable
ifneq ($(WIND_DIAB_PATH),)
#Assure the existence of the trailing slash eventually remove it with realpath
#and adding it back
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
WIND_DIAB_PATH_LOC := $(realpath $(shell cygpath `cygpath -ms '$(WIND_DIAB_PATH)'`))/WIN32/bin/
else
# TODO: check if exist a 64 bit version for Linux
WIND_DIAB_PATH_LOC := $(realpath $(WIND_DIAB_PATH))/LINUX386/bin/
endif # OS_EE_RTD_BUILD_ENV_CYGWIN
endif # WIND_DIAB_PATH

#EG: Force OS_EE_INC_BASE_DIR to be on top of the INCLUDE_PATH LIST.
#    So I can provide override header files.
OSEE_ERIKA_INC := $(call short_native_path, $(OS_EE_INC_BASE_DIR))
INCLUDE_PATH := $(OSEE_ERIKA_INC) $(filter-out $(OSEE_ERIKA_INC), $(INCLUDE_PATH))
# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
ALLINCPATH += $(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

EE_OBJDUMP ?= $(WIND_DIAB_PATH_LOC)windiss
EE_OBJCOPY ?= $(WIND_DIAB_PATH_LOC)ddump

# GNUPro compilers
EE_LINK ?= $(WIND_DIAB_PATH_LOC)dld

OS_EE_AS ?= $(WIND_DIAB_PATH_LOC)das

EE_CC ?= $(WIND_DIAB_PATH_LOC)dcc

EE_CXX ?= $(WIND_DIAB_PATH_LOC)dplus

OS_EE_AR ?= $(WIND_DIAB_PATH_LOC)dar

## OPT_CC are the options for Wind River Diab RH850 C compiler invocation
# Useful options:
#
# -XO     : Enable extra optimizations.
# -Xkeywords=4 : enable inline keyword.
# -Xforce-prototypes: Seems to have problems with main.
# -Xbss-common-off : Turn off DIAB COMMON handlig (when turned off Diab
#                    compiler well behave for .bss variables)
# -Xmacro-in-pragma: Expand macros in pragma
# -Xsize-opt: Optimize for size instead of speed
# -Xdialect-xxx: specify the C dialect
# -Xdebug-inline-on: Generate debugging information for all inlined functions.
#                    Works with DWARF 2 and DWARF 3 only. Can result in very
#                    large executables. This option is disabled by default.
# -Xpass-source: Imply -Xkeep-assembly-file + source code as comment
# -Xstruct-arg-warning: Not implemented yet
# -Wa,-Xsimd: Not documented, but used by Renesas in Embark, I suppose it means
#  Enable Integer Single instruction Multiple Data in assembly
# -Wa,l: Tell the 
# -Xuse-fpsimd: Enable Use floating single instruction multiple data intrinsics
# -Xlint: Enable lint checker
# Suppresed Warnings:
# -ei4188\
# warning (etoa:4188): enumerated type mixed with another type
# Seems to be bugged since it points to line where no enum types are used.

OPT_CC = -c -tRH850GH:simple -Xkeywords=4 -Xsemi-is-comment -Xuse-fpsimd\
 -ei4188\
 -Wa,-Xsimd -Wa,-l
ifneq ($(call iseeopt, OSEE_WR_DIAB_MINIMAL_OPTS), yes)
OPT_CC += -Xdialect-c99 -Xbss-common-off -Xunroll=8 -Xunroll-size=100\
 -Xsmall-data=8 -Xsmall-const=8 -Xenum-is-best -Xinline=50
#-Xlint
endif # !OSEE_WR_DIAB_MINIMAL_OPTS
ifeq ($(or\
    $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)),\
    $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG))\
), yes)

#OPT_CC += -g -XO -#
# Seems that we need g3 option for inlining, see Note 1 pag 69 of
# Wind River Diab Compiler User's Guide for rh850
#-Xpass-source -Xkeep-assembly-file
OPT_CC += -g3 -XO
else
#-Xpass-source -Xkeep-assembly-file
OPT_CC += -g3 -XO
endif
# Specific option from the application makefile
OPT_CC += $(CFLAGS)

# COMPUTED_OPT_CC_PREP Used for file preprocessed file generation:
COMPUTED_OPT_CC_PREP :=  -P $(filter-out -c, $(OPT_CC))
# COMPUTED_OPT_CC_AS   Used for assembly file
COMPUTED_OPT_CC_AS   :=  -S $(filter-out -c, $(OPT_CC)) -Xpass-source

## OPT_CXX are the options for Wind River Diab RH850 C++ compiler invocation
OPT_CXX += -c -tRH850GH:simple -Xkeywords=4 -Xsemi-is-comment -Xuse-fpsimd\
 -Wa,-Xsimd\
#-Wa,-l
ifneq ($(call iseeopt, OSEE_WR_DIAB_MINIMAL_OPTS), yes)
OPT_CXX += -Xbss-common-off -Xunroll=8 -Xunroll-size=100\
 -Xsmall-data=8 -Xsmall-const=8 -Xenum-is-best -Xinline=50
# -Xsyntax-warning-on
endif # !OSEE_WR_DIAB_MINIMAL_OPTS
ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)), \
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG)) \
), yes)
OPT_CXX += -g3 -XO -Xkeep-assembly-file -Xpass-source
else
OPT_CXX += -g3 -XO -Xkeep-assembly-file -Xpass-source
endif

# Specific option from the application makefile
OPT_CXX += $(CFLAGS) $(CXXFLAGS)

## OS_EE_AS_OPT are the options for Wind River Diab RH850 assembler invocation
OS_EE_AS_OPT = -tRH850GH:simple -Xsimd -l

ifeq ($(or\
  $(and $(call iseeopt, OS_EE_BUILD), $(call iseeopt, OS_EE_BUILD_DEBUG)), \
  $(and $(call iseeopt, OS_EE_APP_BUILD), $(call iseeopt, OS_EE_APP_BUILD_DEBUG)) \
), yes)
OS_EE_AS_OPT += -g
else
OS_EE_AS_OPT += -g
endif

OS_EE_AS_OPT += $(ASFLAGS)

# OS_EE_AR_OPT represents the options for archiver invocation
ifeq ($(call iseeopt, OS_EE_VERBOSE), yes)
#OPT_CC  += -v
#OPT_CXX += -v
OS_EE_AR_OPT = $(subst $(OS_EE_SPACE),,csv $(subst v,,$(ARFLAGS)))
else # OS_EE_VERBOSE
OS_EE_AR_OPT = $(subst v,,$(subst $(OS_EE_SPACE),,cs $(ARFLAGS)))
endif # OS_EE_VERBOSE

# OPT_LINK represents the options for avr linker invocation
OSEE_LINKER_SCRIPT ?= $(call short_native_path,$(abspath $(OS_EE_MK_BASE_DIR)/ee_$(OSEE_RH850_MCU).wr.ld))
## OPT_LINK are the options for Diab RH850 dld
# Useful options:
# -Xrescan-libraries: defualt rescan between libararies to satisfy references
OPT_LINK += $(OSEE_LINKER_SCRIPT) -tRH850GH:simple -Xelf -m63
ifneq ($(call iseeopt, OS_EE_GCC_MINIMAL_OPTS), yes)
OPT_LINK +=  -Xcombine-readonly-sections  -Xcheck-overlapping\
 -Xremove-unused-sections
endif # !OS_EE_GCC_MINIMAL_OPTS

OPT_LINK += $(LDFLAGS)

## OPT_LIBS is used to link additional libraries (e.g., for C++ support)
# the EE library is built in the current directory
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
LIBDEP += lib/$(ERIKALIB)
else # OS_EE_BUILD
OPT_LIBS := -L $(call short_native_path,$(abspath $(OS_EE_LIB_BASE_DIR)))\
 -l:crt0.o -l$(EELIB) -lc -limpl $(OPT_LIBS)
LIBDEP += $(OS_EE_LIB_BASE_DIR)/$(ERIKALIB)
endif # OS_EE_BUILD

# Redirect Linker Output to create map file
LINK_REDIRECT = > "$(@D)/$(basename $(notdir $@)).map"

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_DEFS_AS   += -DOS_EE_BUILD
OS_EE_DEFS_CC   += -DOS_EE_BUILD
OS_EE_DEFS_CXX  += -DOS_EE_BUILD
endif

# Automatic dependency generation
ifeq ($(call iseeopt, OS_EE_NO_DEPS), yes)
OS_EE_DEP_OPT =
OS_EE_MK_DEPS =
else	# OS_EE_NO_DEPS
# Create dependency for all headers, and add a target for each header
OS_EE_DEP_OPT = -Xmake-dependency=d -Xmake-dependency-target=$@ -Xmake-dependency-savefile=$(call native_path,$(subst $(suffix $@),.d_tmp,$@))
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
# Dependencies on Windows need path translation and quote remotion
OS_EE_MK_DEPS = sed -e 's_\\\(.\)\(.\)_/\1\2_g' \
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
APP_TARGETS := $(TARGET_NAME).dump $(TARGET_NAME).s19
endif	# !OS_EE_BUILD
