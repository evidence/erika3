# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2017  Evidence Srl
#
# <License>
# ###*E*###

## \file	makefile
## \brief	Jailhouse x86_64 Inmates Makefile.
##
## Makefile for Jailhouse x86_64 inmates in Erika Enterprise.
##
## \author	Michele Pes
## \date	2017
# ###*E*###

# Destination directories
export OUTPUT_DIR = out
export ERIKA_DIR = erika

ifndef  JAILHOUSE_DIR
export JAILHOUSE_DIR = $(HOME)/jailhouse
endif

ifndef	ERIKA_FILES
export ERIKA_FILES = $(abspath ../../ee3)
endif

ifndef	RTDRUID_ECLIPSE_HOME
ifeq	($(shell uname), Linux)
export RTDRUID_ECLIPSE_HOME = $(HOME)/Evidence/eclipse
else
export RTDRUID_ECLIPSE_HOME = C:/Evidence/eclipse
endif
endif

ifndef	RTDRUID_SCRIPT_DIR
RTDRUID_SCRIPT_DIR = $(RTDRUID_ECLIPSE_HOME)/evidence
endif

RTDRUID_OS_OUTPUTS = $(ERIKA_DIR)

RTDRUID_APP_OUTPUTS = $(OUTPUT_DIR)

ifdef V
OS_EE_OPT += OS_EE_VERBOSE
export OS_EE_OPT
endif

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

ifeq ($(RUN_RTDRUID),1)
ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

# Run RT-Druid
$(ERIKA_DIR): os.oil
	@echo "Running RT-Druid for os..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ; \
	export ECLIPSE_HOME ; \
	exec sh $(RTDRUID_SCRIPT_DIR)/generate_code.sh \
	$(RTDRUID_ECLIPSE_HOME) os.oil $@

$(OUTPUT_DIR): appl.oil
	@echo "Running RT-Druid for application..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ; \
	export ECLIPSE_HOME ; \
	exec sh $(RTDRUID_SCRIPT_DIR)/generate_code.sh \
	$(RTDRUID_ECLIPSE_HOME) appl.oil $@

else	# RT-Druid

# Simulate RT-Druid

$(ERIKA_DIR): ./%: fake_druid/%
	@echo "Substituing RT-Druid in generating os..."
	@cp -r $< .

$(OUTPUT_DIR): ./%: fake_druid/%
	@echo "Substituing RT-Druid in generating application..."
	@cp -r $< .

endif	# RT-Druid
