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

## \file	ee_arch_compiler_gcc.mk
## \brief	Architecture GCC Compiler.
##
## This makefile contains the list of GCC Compiler Rules for a specific
## Architecture in Erika Enterprise.
##
## \author	Errico Guidieri
## \date	2016

##
## Compiler related options
##

ERIKALIB = $(ERIKALIB_NAME).a

# Output directory for Kalray makefile
O ?= ${OS_EE_APP_OUT_DIR}
export K1_OUTPTDIR ?= $(if ${O},${O},output)

# Toolchain directory for kalray mafile
K1_TOOLCHAIN_DIR ?= $(shell echo $${K1_TOOLCHAIN_DIR:-/usr/local/k1tools/})

#board can be tc2, emb01 or developer
board ?= developer

# emb01 is always a remote target
# tc2 and developer can be both local or remote (local by default)
ifeq (${board}, emb01)
remote := true
else
remote := false
endif

#arch have to be k1b (Bostan)
arch ?= k1b

# ALLINCPATH is a colon separated list of directories for source file searching
# -I = adds directories to the source file search path (for both gcc and gas)
# we consider the ee pkg directory and the application dir
# we also consider the current directory because the app could be compiled
# from the config files generated from eclipse...
#ALLINCPATH += \
#$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$(call native_path,$d)))
ALLINCPATH += \
$(foreach d,$(INCLUDE_PATH),$(addprefix -I,$d))

# Add needed flags to CFLAGS
# 

CFLAGS_LOCAL = -mhypervisor -std=c99 -Wall -save-temps=obj -g3 -O\
  -Winit-self -Wswitch-default -Wfloat-equal -Wundef -Wshadow\
  -Wuninitialized -Wno-unused-function\
  -I. ${ALLINCPATH} ${CFLAGS}

#OS_EE_DEFS_AS = $(addprefix -D,$(EEOPT))
#OS_EE_DEFS_CC  = $(addprefix -D,$(EEOPT))
#OS_EE_DEFS_CXX  = $(addprefix -D,$(EEOPT))
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
OS_EE_DEFS_AS	+= -DOS_EE_BUILD
OS_EE_DEFS_CC	+= -DOS_EE_BUILD
OS_EE_DEFS_CXX	+= -DOS_EE_BUILD
endif


ifeq ($(call iseeopt, OS_EE_BUILD), yes)

# BINDIR is the directory of assembler, linker, ... distributed with AVR Tools
K1_BINDIR := $(call native_path,$(K1_TOOLCHAIN_DIR))/bin

ifndef	K1_GCCPREFIX
K1_GCCPREFIX = k1
endif

ifndef	EE_OBJDUMP
EE_OBJDUMP = $(K1_BINDIR)/$(K1_GCCPREFIX)-objdump
endif

# GNUPro compilers
ifndef	EE_LINK
EE_LINK = $(K1_BINDIR)/$(K1_GCCPREFIX)-gcc
endif

ifndef	OS_EE_AS
OS_EE_AS = $(K1_BINDIR)/$(K1_GCCPREFIX)-gcc
endif

ifndef	EE_CC
EE_CC = $(K1_BINDIR)/$(K1_GCCPREFIX)-gcc
endif

ifndef	EE_CXX
EE_CXX = $(K1_BINDIR)/$(K1_GCCPREFIX)-g++
endif

ifndef	OS_EE_AR
OS_EE_AR = $(K1_BINDIR)/$(K1_GCCPREFIX)-ar
endif

ifndef	EE_NM
EE_NM = $(K1_BINDIR)/$(K1_GCCPREFIX)-nm
endif

ifndef	EE_OBJCOPY
EE_OBJCOPY = $(K1_BINDIR)/$(K1_GCCPREFIX)-objcopy
endif

ifndef	EE_SIZE
EE_SIZE = $(K1_BINDIR)/$(K1_GCCPREFIX)-size
endif

# Defining EEOPT Macros
# Each identifier that is listed in EEOPT is also inserted as a 
# command-line macro in the compiler...

OPT_CC := -c -mcluster=node -mboard=${board} -march=${arch} -mos=bare
OPT_CC += ${CFLAGS_LOCAL}

OS_EE_AS_OPT += ${OPT_CC}
# Specific option from the application makefile
OS_EE_AS_OPT += $(ASFLAGS)

# OS_EE_AR_OPT represents the options for avr linker invocation
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
OS_EE_AR_OPT = $(subst $(OS_EE_SPACE),,csv $(subst v,,$(ARFLAGS)))
else	# OS_EE_VERBOSE
OS_EE_AR_OPT = $(subst v,,$(subst $(OS_EE_SPACE),,cs $(ARFLAGS)))
endif	# OS_EE_VERBOSE

# Automatic dependency generation
ifeq ($(call iseeopt, OS_EE_NO_DEPS), yes)
OS_EE_DEP_OPT =
OS_EE_MK_DEPS =
else	# OS_EE_NO_DEPS
# Create dependency for all headers, and add a target for each header
OS_EE_DEP_OPT = -MP -MMD -MF $(call native_path,$(subst .o,.d_tmp,$(@)))
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
# Dependencies on Windows need path translation and quote remotion
OS_EE_MK_DEPS = sed -e 's_\\\(.\)_/\1_g' \
	-e 's_\<\([a-zA-Z]\):/_/cygdrive/\l\1/_g' < $1_tmp > $1 && rm $1_tmp
else	# OS_EE_RTD_BUILD_ENV_CYGWIN
OS_EE_MK_DEPS = mv $1_tmp $1
endif	# OS_EE_RTD_BUILD_ENV_CYGWIN
endif	# OS_EE_NO_DEPS

# [GS]: TO BE REMOVED!!!
#else
#TARGETNAME ?= mppa

# Multibin extension
#MULTIBIN_SUFFIX ?= .mpk
# IO ELF suffix
#IO_SUFFIX ?= _io.elf
# CLUSTER ELF suffix
#ERIKA_SUFFIX ?= _erika.elf

# Products names
#K1_MULTIBIN_NAME  ?= ${TARGETNAME}${MULTIBIN_SUFFIX}
#K1_ERIKA_APP_NAME ?= ${TARGETNAME}${ERIKA_SUFFIX}
#K1_IO_APP_NAME    ?= ${TARGETNAME}${IO_SUFFIX} # Have to be provided outside

# Needed for Ubuntu/Debian since sh points to dash instead of bash...
#SHELL := /bin/bash

#platforms := hardware simulator

# Define weither we are using OSes or not. can be os/rtems/nodeos/bare
# If not present, default to os
#system-name := os
## EG: Used to plug ERIKA
#cluster-system := bare

# Common cflags and lflags (for all targets)
# These flags will be propagated through the hierarchy
# I cannot use -Werror for open mp unkown pragmas
# -Wbad-function-cast it bother too much with optimized preemption point.
#cflags += ${CFLAGS}
#lflags += -mhypervisor -lm

# The mppa-bin target is used to generate multibinary for specified target
#mppa-bin := K1_MULTIBIN
#K1_MULTIBIN-name := ${K1_MULTIBIN_APP_NAME}
# Define which binaries will composed multibin1
# Note that the first binary in the list defines the boot binary
#K1_MULTIBIN-objs := ${K1_ERIKA_APP_NAME} ${K1_IO_APP_NAME}

# You can pass additionnal flags to "k1-create-multibinary" using the
# following command.
# for example, '-w ".*"' will active all tracepoints
#K1_MULTIBIN-flags := -w ".*"

################################################################################
#                          Cluster binaries
################################################################################
#cluster-bin += ${K1_ERIKA_APP_NAME}

# Each *-srcs variable describe sources for the binaries
#${K1_ERIKA_APP_NAME}-srcs += ${SRCS}

#${K1_ERIKA_APP_NAME}-deps += ${OS_EE_LIB_BASE_DIR}/${ERIKALIB}

# Flags can be specified per binary
# FIX this better
#${K1_ERIKA_APP_NAME}-cflags += ${OS_EE_DEFS_CC}


#${K1_ERIKA_APP_NAME}-lflags += -g\
#  -Wl,-Map="${K1_OUTPTDIR}/build/${K1_ERIKA_APP_NAME}.map"\
#  -Wl,--defsym=USER_STACK_SIZE=0x2000 -Wl,--defsym=KSTACK_SIZE=0x1000\
#  -L${OS_EE_LIB_BASE_DIR} -L${K1_OUTPTDIR}\
#  -lvbsp -l${EELIB} -lmppaipc

################################################################################
#                          IO binaries
################################################################################
#${K1_IO_APP_NAME}-lflags += -mcluster=ioddr -march=${arch} -mboard=${board}
#  -mos=rtems\
#  -lm  -lmppapower -lmppanoc -lmpparouting -lpcie_queue -lmppaipc\
-Wl,-Map="${K1_OUTPTDIR}/build/${K1_IO_APP_NAME}.map

# Special hooks for user makefile

# Hooks specified in help-hooks are rules which will be called after displaying
# the default help
#help-hooks +=
# Pre build hooks will be called before build
#pre-build-hooks +=
# Post build hooks will be called after build
#post-build-hooks +=
# Clean Hooks
#clean-hooks += clean-build

# Finally, include the Kalray Makefile which will instantiate the rules
# and do the work
#include ${K1_TOOLCHAIN_DIR}/share/make/Makefile.kalray
endif

