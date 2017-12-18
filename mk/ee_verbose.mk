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

## \file	ee_verbose.mk
## \brief	Verbose Macros.
##
## This makefile contains the list of macros to let the build process verbose.
##
## \note	To be merged in ee_common.mk
##
## \author	Giuseppe Serano
## \date	2016

# Enable verbose output from OS_EE_OPT
ifeq	($(call iseeopt, OS_EE_VERBOSE), yes)
QUIET=
VERBOSE_DEVNULL=
else	# EE_OPT VERBOSE
QUIET=@
VERBOSE_DEVNULL=>/dev/null
endif	# EE_OPT VERBOSE

VERBOSE_PRINTDEP=$(QUIET)printf "DEP  $(notdir $<)\\n";
VERBOSE_PRINTCC= $(QUIET)printf "CC   $(notdir $<)\\n";
VERBOSE_PRINTTCC=$(QUIET)printf "TCC  $(notdir $<)\\n";
VERBOSE_PRINTCPP=$(QUIET)printf "CPP  $(notdir $<)\\n";
OS_EE_VERBOSE_PRINTAS	=	$(QUIET)printf "AS   $(notdir $<)\\n";
VERBOSE_PRINTPRE=$(QUIET)printf "PRE  $(notdir $<)\\n";

VERBOSE_PRINTCXX=$(QUIET)printf "CXX  $(notdir $<)\\n";
VERBOSE_PRINTLD= $(QUIET)printf "LD   $(notdir $@)\\n";
OS_EE_VERBOSE_PRINTAR= $(QUIET)printf "AR   $(notdir $@)\\n";

VERBOSE_PRINTEEP= $(QUIET)printf "EEP  $(notdir $<)\\n";
VERBOSE_PRINTHEX= $(QUIET)printf "HEX  $(notdir $<)\\n";
VERBOSE_PRINTLSS= $(QUIET)printf "LSS  $(notdir $<)\\n";
VERBOSE_PRINTSREC=$(QUIET)printf "SREC $(notdir $<)\\n";
