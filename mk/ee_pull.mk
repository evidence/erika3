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

## \file	ee_pull.mk
## \brief	Pull Rules.
##
## This makefile contains the list of rules to pull source files in
## Erika Enterprise project.
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
include $(ERIKA_FILES)/mk/ee_dir.mk

# include configuration
include $(OS_EE_BASE_DIR)/$(OS_EE_PULL_DIR)/ee_oscfg_mk.txt

# Include templates and functions to handle paths
include $(ERIKA_FILES)/$(OS_EE_MK_DIR)/ee_path_helper.mk

# Include verbose macros
include $(ERIKA_FILES)/$(OS_EE_MK_DIR)/ee_verbose.mk

# OS_EE_OPT is used to appropriately configure and compile the particular
# application. Symbols specified in OS_EE_OPT are implicitly defined when
# compiling the application using the -D compiler option

# The simbol OS_EE_BUILD in EE_OPT is used to check the OS in the contrib
# libraries.

OS_EE_OPT += OS_EE_BUILD

# EEALLOPT is deprecated (binary distributions have not been around for a while)
# This definition should raise an error if its value is ever used
# EEALLOPT=$(error ERROR: use of EEPULLALLOPT)

#include only if not empty
ifneq ($(strip $(wildcard $(ERIKA_FILES)/pkg/*/*/ee_pull.mk)),)
include $(wildcard $(ERIKA_FILES)/pkg/*/*/ee_pull.mk)
endif

#include only if not empty
ifneq ($(strip $(wildcard $(ERIKA_FILES)/contrib/*/ee_pull.mk)),)
include $(wildcard $(ERIKA_FILES)/contrib/*/ee_pull.mk)
endif

##
## Files
##########################################################################

OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/$(OS_EE_MK_DIR)/ee.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/$(OS_EE_MK_DIR)/ee_dir.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/$(OS_EE_MK_DIR)/ee_path_helper.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/$(OS_EE_MK_DIR)/ee_verbose.mk

OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/makefile
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/Doxyfile.in
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/doxygen.sty
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/evman.sty
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/header.tex
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/header.html
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/footer.html
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/footer.tex
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/stylesheet.css
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/erika3.png
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/LogoEvidence-new-1.jpg
OS_EE_PULL_DOC_FILES += $(ERIKA_FILES)/$(OS_EE_DOC_DIR)/LogoEvidence-new-2.jpg

##
## Directories
##########################################################################

ifndef	OS_EE_INC_DIR
OS_EE_PULL_INC_DEST_DIR := inc
else
OS_EE_PULL_INC_DEST_DIR = $(OS_EE_INC_DIR)
endif

ifndef	OS_EE_SRC_DIR
OS_EE_PULL_SRC_DEST_DIR := src
else
OS_EE_PULL_SRC_DEST_DIR = $(OS_EE_SRC_DIR)
endif

ifndef	OS_EE_MK_DIR
OS_EE_PULL_MK_DEST_DIR := mk
else
OS_EE_PULL_MK_DEST_DIR = $(OS_EE_MK_DIR)
endif

ifndef	OS_EE_DBG_DIR
OS_EE_PULL_DBG_DEST_DIR := dbg
else
OS_EE_PULL_DBG_DEST_DIR = $(OS_EE_DBG_DIR)
endif

ifndef	OS_EE_DOC_DIR
OS_EE_PULL_DOC_DEST_DIR := doc
else
OS_EE_PULL_DOC_DEST_DIR = $(OS_EE_DOC_DIR)
endif

OS_EE_PULL_DEST_DIRS :=	$(OS_EE_PULL_INC_DEST_DIR)	\
			$(OS_EE_PULL_SRC_DEST_DIR)	\
			$(OS_EE_PULL_MK_DEST_DIR)	\
			$(OS_EE_PULL_DBG_DEST_DIR)	\
			$(OS_EE_PULL_DOC_DEST_DIR)

##
## Main rules: all clean
##########################################################################

.PHONY: all clean make_directories

all:: make_directories
	@echo "*****************************************"
	@echo "* Erika Enterprise Pulled successfully! *"
	@echo "*****************************************"

clean::
	$(QUIET)-$(RM) -f $(OS_EE_PULL_DEST_DIRS)
	@echo "******************************************"
	@echo "* Erika Enterprise Removed successfully! *"
	@echo "******************************************"

make_directories: $(OS_EE_PULL_DEST_DIRS)

## Directories are (re)created only when some of them don't exist already
$(OS_EE_PULL_DEST_DIRS):
	$(QUIET)mkdir -p $(OS_EE_PULL_DEST_DIRS)
	$(QUIET)cp	$(OS_EE_PULL_MK_FILES) $(OS_EE_PULL_MK_DEST_DIR)
	$(QUIET)cp	$(OS_EE_BASE_DIR)/$(OS_EE_PULL_DIR)/ee_oscfg_mk.txt	\
			$(OS_EE_PULL_MK_DEST_DIR)/ee_oscfg.mk
	$(QUIET)cp	$(OS_EE_PULL_INC_FILES) $(OS_EE_PULL_INC_DEST_DIR)
	$(QUIET)cp	$(OS_EE_BASE_DIR)/$(OS_EE_PULL_DIR)/ee_oscfg_h.txt	\
			$(OS_EE_PULL_INC_DEST_DIR)/ee_oscfg.h
	$(QUIET)cp	$(OS_EE_PULL_SRC_FILES) $(OS_EE_PULL_SRC_DEST_DIR)
	$(QUIET)cp	$(OS_EE_BASE_DIR)/$(OS_EE_PULL_DIR)/ee_oscfg_c.txt	\
			$(OS_EE_PULL_SRC_DEST_DIR)/ee_oscfg.c
ifdef	OS_EE_PULL_DBG_FILES
	$(QUIET)cp	$(OS_EE_PULL_DBG_FILES) $(OS_EE_PULL_DBG_DEST_DIR)
endif
	$(QUIET)cp	$(OS_EE_PULL_DOC_FILES) $(OS_EE_PULL_DOC_DEST_DIR)
