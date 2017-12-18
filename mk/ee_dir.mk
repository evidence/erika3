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

## \file	ee_dir.mk
## \brief	Standard Directories.
##
## This makefile contains the list of standard directories used in an
## Erika Enterprise project.
##
## \note	To be merged in ee_common.mk
##
## \author	Giuseppe Serano
## \date	2016

# OS_EE_BASE_DIR is the base directory of the kernel.

# OS_EE_DBG_DIR is the directory used to generate debugger script files
OS_EE_DBG_DIR := dbg

# OS_EE_DOC_DIR is the directory used to generate documentation files
OS_EE_DOC_DIR := doc

# OS_EE_INC_DIR is the directory used to generate include files
OS_EE_INC_DIR := inc

# OS_EE_INC_BASE_DIR is the base directory for header files
OS_EE_INC_BASE_DIR := $(OS_EE_BASE_DIR)/$(OS_EE_INC_DIR)

# OS_EE_LIB_DIR is the directory used to generate library files
OS_EE_LIB_DIR := lib

# OS_EE_LIB_BASE_DIR is the base directory for library f
OS_EE_LIB_BASE_DIR := $(OS_EE_BASE_DIR)/$(OS_EE_LIB_DIR)

# OS_EE_MK_DIR is the directory used to generate make files
OS_EE_MK_DIR := mk

# OS_EE_MK_BASE_DIR is the base directory for make files
OS_EE_MK_BASE_DIR := $(OS_EE_BASE_DIR)/$(OS_EE_MK_DIR)

# OS_EE_OBJ_DIR is the directory used to generate object files
OS_EE_OBJ_DIR := obj

# OS_EE_PULL_DIR is the directory used to generate pull make files
OS_EE_PULL_DIR := pull

# OS_EE_SRC_DIR is the directory used to generate source files
OS_EE_SRC_DIR := src

# OS_EE_SRC_BASE_DIR is the base directory for sources files
OS_EE_SRC_BASE_DIR := $(OS_EE_BASE_DIR)/$(OS_EE_SRC_DIR)
