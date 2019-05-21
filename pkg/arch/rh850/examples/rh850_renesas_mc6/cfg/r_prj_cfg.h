/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License, version 2, for more details.
 * 
 * You should have received a copy of the GNU General Public License,
 * version 2, along with this program; if not, see
 * < www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 * 
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 * 
 * THIRD PARTIES' MATERIALS
 * 
 * Certain materials included in this library are provided by third
 * parties under licenses other than the GNU General Public License. You
 * may only use, copy, link to, modify and redistribute this library
 * following the terms of license indicated below for third parties'
 * materials.
 * 
 * In case you make modified versions of this library which still include
 * said third parties' materials, you are obligated to grant this special
 * exception.
 * 
 * The complete list of Third party materials allowed with ERIKA
 * Enterprise version 3, together with the terms and conditions of each
 * license, is present in the file THIRDPARTY.TXT in the root of the
 * project.
 * ###*E*### */

/** \file   r_prj_cfg.h
 *  \brief  project configuration defines
 *
 *  \author Errico Gudieri
 *  \date   2018
 */

#ifndef R_PRJ_CFG_H
#define R_PRJ_CFG_H


/*##############################################################################
 # global configurations
 ##############################################################################*/

/*******************************************************************************
 * PORT configuration
 ******************************************************************************/
extern const port_cfg_t g_port_PrjCfg[];
extern const uint32     g_port_PrjCfgCnt;

/*******************************************************************************
 * PEID0 (core 0) configurations
 *******************************************************************************/
extern const g4mh_isr_t     g_peid0_RefTblEiPrjCfg[];
extern const g4mh_isr_t     g_peid0_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid0_FePrjCfg[];
extern const g4mh_syscall_t g_peid0_SysCallPrjCfg[];

/*******************************************************************************
 * PEID1 (core 1) configurations
 *******************************************************************************/
extern const g4mh_isr_t     g_peid1_RefTblEiPrjCfg[];
extern const g4mh_isr_t     g_peid1_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid1_FePrjCfg[];
extern const g4mh_syscall_t g_peid1_SysCallPrjCfg[];

/*******************************************************************************
 * PEID2 (core 2) configurations
 *******************************************************************************/
extern const g4mh_isr_t     g_peid2_RefTblEiPrjCfg[];
extern const g4mh_isr_t     g_peid2_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid2_FePrjCfg[];
extern const g4mh_syscall_t g_peid2_SysCallPrjCfg[];

/*******************************************************************************
 * PEID3 (core 3) configurations
 *******************************************************************************/
extern const g4mh_isr_t     g_peid3_RefTblEiPrjCfg[];
extern const g4mh_isr_t     g_peid3_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid3_FePrjCfg[];
extern const g4mh_syscall_t g_peid3_SysCallPrjCfg[];

/*******************************************************************************
 * PEID4 (core 4) configurations
 *******************************************************************************/
extern const g4mh_isr_t     g_peid4_RefTblEiPrjCfg[];
extern const g4mh_isr_t     g_peid4_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid4_FePrjCfg[];
extern const g4mh_syscall_t g_peid4_SysCallPrjCfg[];

/*******************************************************************************
 * PEID5 (core 5) configurations
 *******************************************************************************/
extern const g4mh_isr_t     g_peid5_RefTblEiPrjCfg[];
extern const g4mh_isr_t     g_peid5_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid5_FePrjCfg[];
extern const g4mh_syscall_t g_peid5_SysCallPrjCfg[];

/*******************************************************************************
 * BOOT configuration
 *******************************************************************************/
extern const boot_cfg_t     g_boot_PrjCfg;

/*******************************************************************************
 * configuration of user functions to execute in case of FE, EI and SYSCALL
 * exceptions on PEID0
 ******************************************************************************/
extern const g4mh_syscall_t g_peid0_SysCallPrjCfg[];
extern const g4mh_isr_t     g_peid0_FePrjCfg[];
extern const g4mh_isr_t     g_peid0_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid0_RefTblEiPrjCfg[];

/*******************************************************************************
 * configuration of user functions to execute in case of FE, EI and SYSCALL
 * exceptions on PEID1
 ******************************************************************************/
extern const g4mh_syscall_t g_peid1_SysCallPrjCfg[];
extern const g4mh_isr_t     g_peid1_FePrjCfg[];
extern const g4mh_isr_t     g_peid1_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid1_RefTblEiPrjCfg[];

/*******************************************************************************
 * configuration of user functions to execute in case of FE, EI and SYSCALL
 * exceptions on PEID2
 ******************************************************************************/
extern const g4mh_syscall_t g_peid2_SysCallPrjCfg[];
extern const g4mh_isr_t     g_peid2_FePrjCfg[];
extern const g4mh_isr_t     g_peid2_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid2_RefTblEiPrjCfg[];

/*******************************************************************************
 * configuration of user functions to execute in case of FE, EI and SYSCALL
 * exceptions on PEID3
 ******************************************************************************/
extern const g4mh_syscall_t g_peid3_SysCallPrjCfg[];
extern const g4mh_isr_t     g_peid3_FePrjCfg[];
extern const g4mh_isr_t     g_peid3_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid3_RefTblEiPrjCfg[];

/*******************************************************************************
 * configuration of user functions to execute in case of FE, EI and SYSCALL
 * exceptions on PEID4
 ******************************************************************************/
extern const g4mh_syscall_t g_peid4_SysCallPrjCfg[];
extern const g4mh_isr_t     g_peid4_FePrjCfg[];
extern const g4mh_isr_t     g_peid4_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid4_RefTblEiPrjCfg[];

/*******************************************************************************
 * configuration of user functions to execute in case of FE, EI and SYSCALL
 * exceptions on PEID5
 ******************************************************************************/
extern const g4mh_syscall_t g_peid5_SysCallPrjCfg[];
extern const g4mh_isr_t     g_peid5_FePrjCfg[];
extern const g4mh_isr_t     g_peid5_DirVecEiPrjCfg[];
extern const g4mh_isr_t     g_peid5_RefTblEiPrjCfg[];

#endif /* R_PRJ_CFG_H */

