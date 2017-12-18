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

# Makefile for Erika Enterprise documentation
# Author: 2016,  Giuseppe Serano


# Output directories
OUTPUT_DIRS	= html latex rtf

# Picture directory
PIC_DIR		= html

DOXYGEN	:= $(shell which doxygen 2>/dev/null)

# Pictures
PICTURES	= LogoEvidence-new-1.jpg	\
		  LogoEvidence-new-2.jpg

# OS Configuration
include ../mk/ee_oscfg.mk

.PHONY: clean pdfdoc Doxyfile htmldoc all docs

docs:	all
ifeq ($(DOXYGEN),)
	@echo "***********************************************"
	@echo "* Doxygen required to generate documentation! *"
	@echo "***********************************************"
else
	@echo "**********************************************************"
	@echo "* Erika Enterprise Documentation Generated successfully! *"
	@echo "**********************************************************"
endif

all:	htmldoc

htmldoc: Doxyfile

Doxyfile: Doxyfile.in
ifeq ($(DOXYGEN),)
else
	@echo "************************************************"
	@echo "* Erika Enterprise Documentation Generation... *"
	@echo "************************************************"
	@sed -e 's/@OS_EE_OPT@/$(OS_EE_OPT)/g' < $< > $@
	@doxygen > output.log 2>&1
	@cp $(PICTURES) $(PIC_DIR)
endif

pdfdoc: htmldoc
	cd latex; make refman.pdf && mv refman.pdf ../ee3-refman.pdf

clean:
	@echo Cleaning Documentation...
	@-$(RM) -f -r *.log $(OUTPUT_DIRS) ee3-refman.pdf
