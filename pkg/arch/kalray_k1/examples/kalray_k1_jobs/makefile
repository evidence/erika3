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

## \file	makefile
## \brief	Kalra1 K1 Demos Makefile.
##
## Makefile for K1 demos in Erika Enterprise.
##
## \author	Errico Guidieri
## \date	2016
# ###*E*###

# Destination directories
export OUTPUT_DIR = out
export ERIKA_DIR = erika

# Toolchain directory for kalray mafile
K1_TOOLCHAIN_DIR ?= $(shell echo $${K1_TOOLCHAIN_DIR:-/usr/local/k1tools/})

ifndef	ERIKA_FILES
export ERIKA_FILES = $(abspath ../../ee3)
endif

#export VERBOSE=1

ifndef	RTDRUID_ECLIPSE_HOME
ifeq	($(shell uname), Linux)
export RTDRUID_ECLIPSE_HOME = $(HOME)/evidence/eclipse_ee3/eclipse
else
export RTDRUID_ECLIPSE_HOME = C:/Evidence/eclipse_ee3/eclipse
endif
endif

ifndef	RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR = $(RTDRUID_ECLIPSE_HOME)/evidence
endif

ifndef	RTDRUID_JAVA_HOME
RTDRUID_JAVA_HOME := ${abspath $(RTDRUID_ECLIPSE_HOME)/../java}
endif

RTDRUID_OS_OUTPUTS = $(ERIKA_DIR)

RTDRUID_APP_OUTPUTS = $(OUTPUT_DIR)

.PHONY:	all pull os appl \
	clean os-clean appl-clean \
	dist-clean os-dist-clean appl-dist-clean \
	upload

all: os appl

pull: $(ERIKA_DIR)
	$(MAKE) -C $< mk

os: $(ERIKA_DIR)
	$(MAKE) -C $< all

appl: $(OUTPUT_DIR) $(ERIKA_DIR)
	$(MAKE) -C $< all

clean: os-clean appl-clean

os-clean: $(ERIKA_DIR)
	@echo os cleaning...
	$(MAKE) -C $(ERIKA_DIR) clean

appl-clean: $(OUTPUT_DIR) $(ERIKA_DIR)
	@echo application cleaning...
	$(MAKE) -C $(OUTPUT_DIR) clean

dist-clean: os-dist-clean appl-dist-clean

os-dist-clean:
	@echo os distribution cleaning...
	@$(RM) -r $(ERIKA_DIR)

appl-dist-clean:
	@echo application distribution cleaning...
	@$(RM) -r $(OUTPUT_DIR)

doc:	pull
	$(MAKE) -C $(ERIKA_DIR)/doc

pdfdoc:	pull
	$(MAKE) -C $(ERIKA_DIR)/doc $@

ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

## TO BE Restored
## Run RT-Druid
#$(ERIKA_DIR): os.oil
#	@echo "Running RT-Druid for os..."
#	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ; \
#	export ECLIPSE_HOME ; \
#	exec sh $(RTDRUID_SCRIPT_DIR)/generate_code.sh \
#	$(RTDRUID_ECLIPSE_HOME) $< $@
#
#$(OUTPUT_DIR): appl.oil
#	@echo "Running RT-Druid for application..."
#	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ; \
#	export ECLIPSE_HOME ; \
#	exec sh $(RTDRUID_SCRIPT_DIR)/generate_code.sh \
#	$(RTDRUID_ECLIPSE_HOME) appl.oil $@

# More Command Options
#  --generateOS
#                   enable the generation of OS configuration files
#  --generateAppl
#                   enable the generation of Application
#                   configuration files
$(ERIKA_DIR) $(OUTPUT_DIR): conf.oil
	${RTDRUID_JAVA_HOME}/bin/java\
		-jar ${RTDRUID_ECLIPSE_HOME}/plugins/org.eclipse.equinox.launcher_1.3.201.v20161025-1711.jar\
			-application com.eu.evidence.rtdruid3.oil.ee.core.generator\
				--preferenceFile rtd.properties\
				--inputFile conf.oil\
				--outputDir .

