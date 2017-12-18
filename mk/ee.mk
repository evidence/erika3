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

## \file	ee.mk
## \brief	ERIKA Enterprise Rules.
##
## This makefile contains the list of rules to build Erika Enterprise libraries
## and applications
##
## \author	Giuseppe Serano
## \date	2016

############################################################################
#
# Erika base directory
#
############################################################################

ifndef	OS_EE_BASE_DIR

ifeq ($(if $(filter OS_EE_RTD_BUILD_ENV_NATIVE,$(OS_EE_OPT)),yes,), yes)
OS_EE_BASE_DIR := $(strip $(abspath $(OS_EE_APP_BASE_DIR)/erika))
else	# OS_EE_OPT OS_EE_RTD_BUILD_ENV_NATIVE
OS_EE_BASE_DIR := $(shell cygpath `cygpath -ms '$(abspath $(OS_EE_APP_BASE_DIR)/erika)'`)
endif	# OS_EE_OPT OS_EE_RTD_BUILD_ENV_NATIVE

endif	# !OS_EE_BASE_DIR

# Include directory paths
include $(OS_EE_BASE_DIR)/mk/ee_dir.mk

# include OS configuration
include $(OS_EE_MK_BASE_DIR)/ee_oscfg.mk

# Include templates and functions to handle paths
include $(OS_EE_MK_BASE_DIR)/ee_path_helper.mk

# Include verbose macros
include $(OS_EE_MK_BASE_DIR)/ee_verbose.mk

# OS_EE_OPT is used to appropriately configure and compile the particular
# application. Symbols specified in OS_EE_OPT are implicitly defined when
# compiling the application using the -D compiler option

# The simbol OS_EE_BUILD in OS_EE_OPT is used to check the OS against the application.
ifeq ($(call iseeopt,OS_EE_BUILD), yes)

#include only if one library configuration file exists
ifneq ($(strip $(wildcard $(OS_EE_MK_BASE_DIR)/*_libcfg.mk)),)
include $(wildcard $(OS_EE_MK_BASE_DIR)/*_libcfg.mk)
endif

#include only if one configuration file exists
ifneq ($(strip $(wildcard $(OS_EE_MK_BASE_DIR)/*_cfg.mk)),)
include $(wildcard $(OS_EE_MK_BASE_DIR)/*_cfg.mk)
endif

else	# OS_EE_BUILD

## include only if one libreary linking configuration file exists
ifneq ($(strip $(wildcard $(OS_EE_MK_BASE_DIR)/*_linkcfg.mk)),)
include $(wildcard $(OS_EE_MK_BASE_DIR)/*_linkcfg.mk)
endif

endif	# OS_EE_BUILD

# Erika LIB name
EELIB = ee
ERIKALIB_NAME = lib$(EELIB)

## include only if one architecture compiler makefile exists
include $(wildcard $(OS_EE_MK_BASE_DIR)/ee_arch_compiler_*.mk)

# Explicit the default target
.DEFAULT_GOAL := all

# Add application file to dependencies
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
#TARGET := 	$(TARGET_NAME).eep \
#		$(TARGET_NAME).hex \
#		$(TARGET_NAME).lss \
#		$(TARGET_NAME).srec
TARGET :=	$(ALL_LIBS) \
		$(OS_EE_LIB_DIR)/$(ERIKALIB)
else	# OS_EE_BUILD
TARGET := 	$(APP_TARGETS)
endif	# OS_EE_BUILD

# Specific option from the libs dependencies
LIBDEP += $(ALL_LIBS)
# Specific option from the application makefile
LIBDEP += $(LDDEPS)

#
# --------------------------------------------------------------------------
#

##
## Source files and paths
##


# Boot code containing _start should stay outside of the library in
# case of normal compilation

LIBEESRCS	+= $(EE_SRCS) $(OS_EE_CFG_SRCS)
LIBEEOBJS	:=							\
	$(addprefix $(OS_EE_OBJ_DIR)/,					\
		$(patsubst %.cpp,%.cpp.o,				\
			$(patsubst %.c,%.c.o,				\
				$(patsubst %.S,%.S.o,$(LIBEESRCS))	\
			)						\
		)							\
	)

LIBSRCS		+= $(LIB_SRCS)
LIBOBJS		:=							\
	$(addprefix $(OS_EE_OBJ_DIR)/,					\
		$(patsubst %.cpp,%.cpp.o,				\
			$(patsubst %.c,%.c.o,				\
				$(patsubst %.S,%.S.o,$(LIBSRCS))	\
			)						\
		)							\
	)

SRCS		+= $(sort $(OS_EE_APP_CFG_SRCS))
OBJS		:=							\
	$(addprefix $(OS_EE_OBJ_DIR)/,					\
		$(patsubst %.cpp,%.cpp.o,				\
			$(patsubst %.c,%.c.o,				\
				$(patsubst %.S,%.S.o,$(SRCS))		\
			)						\
		)							\
	)

# Variable used to import dependencies
#ALLOBJS = $(LIBEEOBJS) $(LIBOBJS) $(OBJS)
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
ALLOBJS = $(LIBEEOBJS) $(LIBOBJS)
else	# OS_EE_BUILD
ALLOBJS = $(OBJS)
endif	# OS_EE_BUILD

OS_EE_OBJ_DIRS = $(sort $(dir $(ALLOBJS)))

# Add basic include paths
INCLUDE_PATH += $(call short_native_path, $(OS_EE_INC_BASE_DIR))
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
INCLUDE_PATH += $(call short_native_path, $(OS_EE_SRC_BASE_DIR))
else	# OS_EE_BUILD
INCLUDE_PATH += $(call short_native_path, $(abspath $(OS_EE_APP_BASE_DIR)))
INCLUDE_PATH += $(call short_native_path, $(abspath $(OS_EE_APP_OUT_DIR)))
endif	# OS_EE_BUILD

EE_VPATH += $(OS_EE_BASE_DIR)

ifeq ($(call iseeopt, OS_EE_BUILD), yes)
EE_VPATH +=	$(OS_EE_SRC_BASE_DIR)
else	# OS_EE_BUILD
EE_VPATH +=	$(call short_native_path,$(abspath $(OS_EE_APP_BASE_DIR))) \
		$(call short_native_path,$(abspath $(OS_EE_APP_OUT_DIR)))
endif	# OS_EE_BUILD

vpath %.c	$(EE_VPATH)
vpath %.S	$(EE_VPATH)
vpath %.cpp	$(EE_VPATH)

##
## Directories
##

.PHONY: make_directories

## Objects depend on directories, but they are not remade if directories change
$(ALLOBJS): | make_directories

make_directories: $(OS_EE_OBJ_DIRS)

## Directories are (re)created only when some of them don't exist already
ifeq ($(call iseeopt, OS_EE_BUILD), yes)
$(OS_EE_OBJ_DIRS):
	@echo "***************************************"
	@echo "* Erika Enterprise Libraries build... *"
	@echo "***************************************"
	$(QUIET)mkdir -p $(OS_EE_LIB_DIR)
	$(QUIET)mkdir -p $(OS_EE_OBJ_DIRS)
else	# OS_EE_BUILD
$(OS_EE_OBJ_DIRS):
	@echo "*****************************************"
	@echo "* Erika Enterprise Application build... *"
	@echo "*****************************************"
	$(QUIET)mkdir -p $(OS_EE_OBJ_DIRS)
endif	# OS_EE_BUILD

##
## Automatic Generation of dependencies
##

dependencies=$(subst .o,.d,$(ALLOBJS))
ifneq ($(call iseeopt, OS_EE_NO_DEPS), yes) 
ifneq ($(MAKECMDGOALS),clean)
-include $(dependencies)
endif
endif

##
## Architecture Rules
##########################################################################
include $(OS_EE_MK_BASE_DIR)/ee_arch_rules.mk
