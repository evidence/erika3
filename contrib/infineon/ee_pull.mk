# ###*B*###
# Erika Enterprise, version 3
# 
# Copyright (C) 2018 Evidence s.r.l.
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
## \brief	Pull file for Infineon Libraries.
##
## This makefile contains the list of files to be pulled into Erika Enterprise
## project to support Infineon Libraries.
##
## \author	Giuseppe Serano
## \date	2018

## Check the NXP Libraries selection

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL), yes)

OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/contrib/infineon/ee_isar_libcfg.mk
OS_EE_PULL_MK_FILES += $(ERIKA_FILES)/contrib/infineon/ee_isar_linkcfg.mk

##
## ERIKA3 Integration header files.
##
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/Compiler.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/intrinsics.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/McalOsConfig.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/SchM_17_McalCfg.h

ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_3_0_0), yes)
	OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/Std_Types.h
	OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/MemMap.h
endif

##
## DET header file
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_USE_DET), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/Det.h
OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/src/Det.c
endif	# OS_EE_LIB_ISAR_MCAL_USE_DET


##
## ADC Driver Schedule Manager header file.
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ADC_DRIVER), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/SchM_Adc.h
endif	# OS_EE_LIB_ISAR_MCAL_ADC_DRIVER

##
## ICU Driver Schedule Manager header file.
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_ICU_DRIVER), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/SchM_Icu_17_GtmCcu6.h
endif	# OS_EE_LIB_ISAR_MCAL_ICU_DRIVER

##
## PWM Driver Schedule Manager header file.
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_PWM_DRIVER), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/SchM_Pwm_17_Gtm.h
endif	# OS_EE_LIB_ISAR_MCAL_PWM_DRIVER

##
## SPI Driver Schedule Manager header file.
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_SPI_DRIVER), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/SchM_Spi.h
endif	# OS_EE_LIB_ISAR_MCAL_SPI_DRIVER

##
## Memory Interface header file.
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/MemIf_Types.h
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FLS Driver Diegnaostic Event Manager and Schedule Manager header files.
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FLS_DRIVER), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/Dem.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/Dem_Types.h
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/SchM_Fls_17_Pmu.h
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_3_0_0), yes)
	OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/Dem_PBcfg.h
endif
endif	# OS_EE_LIB_ISAR_MCAL_FLS_DRIVER

##
## FEE Driver NVM Callbacks header file.
##
ifeq	($(call islibopt, OS_EE_LIB_ISAR_MCAL_FEE_DRIVER), yes)
OS_EE_PULL_INC_FILES += $(ERIKA_FILES)/contrib/infineon/ISAR/inc/NvM_Cbk.h
endif	# OS_EE_LIB_ISAR_MCAL_FEE_DRIVER

endif	# OS_EE_LIB_ISAR_MCAL
