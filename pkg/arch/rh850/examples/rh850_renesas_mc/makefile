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

## \file	makefile
## \brief	RH850 demos makefile.
##
## Makefile for RH850 demos in Erika Enterprise.
##
## \author	Errico Guidieri
## \date	2018
# ###*E*###

# Destination directories

ifneq (${micro},)
  MCU_DERIVATIVE = $(micro)
else
# Default target $(MCU_DERIVATIVE) = r7f702z04
  MCU_DERIVATIVE = r7f702z04
endif

export OUTPUT_DIR = out
export ERIKA_DIR  = erika
CONF_OIL          = conf_$(MCU_DERIVATIVE).oil
WS               ?= workspace

ifndef	RTDRUID_ECLIPSE_HOME
ifeq	($(shell uname), Linux)
export RTDRUID_ECLIPSE_HOME = ${HOME}/evidence/eclipse_ee3/eclipse
else
export RTDRUID_ECLIPSE_HOME = C:/Evidence/eclipse_ee3/eclipse
endif
endif

ifndef	RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR = $(RTDRUID_ECLIPSE_HOME)/evidence
endif

ifdef V
OS_EE_OPT += OS_EE_VERBOSE
export OS_EE_OPT
endif

.PHONY:	all pull config os appl \
	clean os-clean appl-clean \
	dist-clean os-dist-clean appl-dist-clean \
	upload

all: os appl

pull: config
	$(MAKE) -C $(ERIKA_DIR) mk

os: pull
	$(MAKE) -C $(ERIKA_DIR) all

appl: pull os
	$(MAKE) -C $(OUTPUT_DIR) all

clean: os-clean appl-clean

os-clean: config
	@echo os cleaning...
	$(MAKE) -C $(ERIKA_DIR) clean

appl-clean: config
	@echo application cleaning...
	$(MAKE) -C $(OUTPUT_DIR) clean

dist-clean: os-dist-clean appl-dist-clean

os-dist-clean:
	@echo os distribution cleaning...
	@$(RM) -r $(ERIKA_DIR) $(WS)

appl-dist-clean:
	@echo application distribution cleaning...
	@$(RM) -r $(OUTPUT_DIR) cfg/$(MCU_DERIVATIVE)

doc:	pull
	$(MAKE) -C $(ERIKA_DIR)/doc

pdfdoc:	pull
	$(MAKE) -C $(ERIKA_DIR)/doc $@

upload:	all
	$(MAKE) -C $(OUTPUT_DIR) upload

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
config: $(CONF_OIL)
#	@echo "Generating configuration with RT-Druid"
#	@java -jar ${RTDRUID_ECLIPSE_HOME}/plugins/org.eclipse.equinox.launcher_*.jar\
#			-data $(WS)\
#			-application com.eu.evidence.rtdruid3.oil.ee.core.generator\
#				--inputFile conf.oil\
#				--outputDir .
	@${RTDRUID_ECLIPSE_HOME}/evidence/generate_code.sh ${RTDRUID_ECLIPSE_HOME} $< .
