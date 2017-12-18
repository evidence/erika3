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

## \file	ee_path_helper.mk
## \brief	Verbose Macros.
##
## This makefile contains the list of macros used in the buils process.
##
## \note	To be merged in ee_common.mk
##
## \author	Giuseppe Serano
## \date	2016


############################################################################
#
# Workaround to remove cygwin warning messages about the usage of DOS-like paths
# that is produced the first time a DOS-like path is used:
#  - run as soon as possible a shell command that uses a path and drop 
#    the error message.
# Here is an example, using 'test' command
#  es:  $(shell test -d "c:\\dummy\\path" 2>/dev/null)
#
# Usually, check_and_set_xxx_compiler_path is called in first stages of makefile
# and it contains a test command that already drop the error message, than there
# is no need to explicitly invoke a shell command to drop the message.
#
# Note: CYGWIN=nodosfilewarning option has to be set before the first execution
#       of cygwin programs, than it cannot be set here
#
############################################################################
#$(shell test -d "c:\\dummy\\path" 2>/dev/null)


############################################################################
#
# Compiler checks
#
############################################################################

#
# Checks if a path exists and then sets the variable required by Erika
# makefiles.
# The resulted path is transformed using cygwin functions
#
# 1-> container name (es. PIC30_GCC). Cannot be empty.
# 2-> native compiler path (es c:/Program Files). Can be empty.
#
# Example:
# $(eval $(call check_and_set_cygwin_compiler_path,PIC30_GCC,C:\\Program Files))
#
define check_and_set_cygwin_compiler_path

ifndef $(1)

ifeq ($$(strip $(2)),)
# usually this happens if RT-Druid was not able to find the default value.
# Even if is deprecated, for some cases it is possible to search the compiler
# using the PATH.

# list here all special cases (es. a b c)
ifneq (,$$(findstring $$(strip $(1)),PPC_DIAB_BASEDIR))
$$(warning The environment variable $(1) is unset.)
$$(warning The compiler will be searched using the PATH)
else
$$(error Please set the compiler path into $(1) variable before run the makefile)
endif
else
CHECK_COMPILER_PATH := $$(shell test -d "$(2)" 2>/dev/null && echo "0")
ifneq ($$(CHECK_COMPILER_PATH),0)
$$(error Compiler not found. Provided path is '$(2)')
endif
CHECK_COMPILER_PATH :=
$(1) := $$(shell cygpath `cygpath -ms '$(2)'`)
endif

else
CHECK_COMPILER_PATH := $$(shell test -d "$$($(1))" 2>/dev/null && echo "0")
ifneq ($$(CHECK_COMPILER_PATH),0)
$$(error Compiler not found. Provided path is '$$($(1))')
endif
CHECK_COMPILER_PATH :=
endif

endef # check_and_set_cygwin_compiler_path

#
# Checks if a path exists and then sets the variable required by Erika
# makefiles.
#
# 1-> container name (es. PIC30_GCC). Cannot be empty
# 2-> native compiler path (es /opt/Program Files). Can be empty.
#
# Example:
# $(eval $(call check_and_set_linux_compiler_path,PIC30_GCC,/opt/Program Files))
#
define check_and_set_linux_compiler_path

ifndef $(1)

ifeq ($$(strip $(2)),)
# usually this happens if RT-Druid was not able to find the default value.
# Even if is deprecated, for some cases it is possible to search the compiler
# using the PATH.

# list here all special cases (es. a b c)
ifneq (,$$(findstring $$(strip $(1)),PPC_DIAB_BASEDIR))
$$(warning The environment variable $(1) is unset.)
$$(warning The compiler will be searched using the PATH)
else
$$(error Please set the compiler path into $(1) variable before run the makefile)
endif
else
CHECK_COMPILER_PATH := $$(shell test -d "$(2)" 2>/dev/null && echo "0")
ifneq ($$(CHECK_COMPILER_PATH),0)
$$(error Compiler not found. Provided path is '$(2)')
endif
CHECK_COMPILER_PATH :=
$(1) := $(2)
endif

else
CHECK_COMPILER_PATH := $$(shell test -d "$$($(1))" 2>/dev/null && echo "0")
ifneq ($$(CHECK_COMPILER_PATH),0)
$$(error Compiler not found. Provided path is '$$($(1))')
endif
CHECK_COMPILER_PATH :=
endif

endef # check_and_set_linux_compiler_path

#
# Empty var.
#
OS_EE_EMPTY :=

#
# Space var.
#
OS_EE_SPACE := $(OS_EE_EMPTY) $(OS_EE_EMPTY)


# Functions to test OS_EE_OPT and LIB_OPT, useful in conditionals and in
# or/and expressions
#
# Examples:
# ifeq ($(call iseeopt,__MULTI__), yes)
# ifeq (
#   $(and $(call iseeopt,__MULTI__), $(call iseeopt,__IRQ_STACK_NEEDED__)), yes
# )
# ifneq ($(call iseeopt,__MULTI__), yes)
iseeopt = $(if $(filter $1,$(OS_EE_OPT)),yes,)

islibopt = $(if $(filter $1,$(OS_EE_LIB_OPT)),yes,)

# `native_path' is used to convert Unix-style names to native names
ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
# Sed is used to remove trailing backslash and to double internal backslashes
native_path = \
"$(shell cygpath -w '$(strip $1)' | sed -e 's/\\$$//' -e 's/\\/\\\\/g')"
else

# native_path is supposed to return a path string; `strip' removes leading or
# trailing white chars
native_path = $(strip $1)

endif

ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
#unix_path = $(shell cygpath -u -a '$1' | sed -e 's/ /\\ /g')
unix_path = $(shell cygpath -u -a '$1')
else
unix_path = $1
endif

ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
unix_relpath = $(shell cygpath -u '$1')
else
unix_relpath = $1
endif

ifeq ($(call iseeopt, OS_EE_RTD_BUILD_ENV_CYGWIN), yes)
short_native_path =	\
$(shell cygpath -w -s '$(strip $1)' | sed -e 's/\\$$//' -e 's/\\/\\\\/g')
else
short_native_path = $(strip $1)
endif

