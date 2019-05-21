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

/** \file   r_peid4_cfg.c
 *  \brief  project configuration for PEID4  (core 4)
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#include <r_prj.h>

/*##############################################################################
 # global configurations
 ##############################################################################*/

/*******************************************************************************
 * Name        : g_peid4_SysCallPrjCfg
 * Description : SYSCALL vector table
 * Note        : size of this table can be up to 256 elements (0-255)
 *******************************************************************************/
const g4mh_syscall_t g_peid4_SysCallPrjCfg[] =
{
  /* Vector 0 */ R_G4MH_SysCallUnused,
  /* Vector 1 */ R_G4MH_SysCallUnused,
  /* Vector 2 */ R_G4MH_SysCallUnused,
  /* Vector 3 */ R_G4MH_SysCallUnused,
};

/*******************************************************************************
 * Name        : g_peid4_FePrjCfg
 * Description : array of User functions for FE exceptions
 * Note        : do not remove, this name is referenced in r_boot.asm. When
 *             : changed must also be changed in r_boot.asm.
 * Note        : Size of this array must match number of FE exceptions (16)
 *******************************************************************************/
const g4mh_isr_t g_peid4_FePrjCfg[] =
{
  /* 0: RESET    */ R_BOOT_IsrReset,
  /* 1: SYSERR   */ R_G4MH_IsrFeUnused,
  /* 2: HVTRAP   */ R_G4MH_IsrFeUnused,
  /* 3: FETRAP   */ R_G4MH_IsrFeUnused,
  /* 4: TRAP0    */ R_G4MH_IsrFeUnused,
  /* 5: TRAP1    */ R_G4MH_IsrFeUnused,
  /* 6: RIE      */ R_G4MH_IsrFeUnused,
  /* 7: FPP/FPI  */ R_G4MH_IsrFeUnused,
  /* 8: UCPOP    */ R_G4MH_IsrFeUnused,
  /* 9: MIP/MDP  */ R_G4MH_IsrFeUnused,
  /* 10: PIE     */ R_G4MH_IsrFeUnused,
  /* 11: DEBUG   */ R_G4MH_IsrFeUnused,
  /* 12: MAE     */ R_G4MH_IsrFeUnused,
  /* 13: (R.F.U) */ R_G4MH_IsrFeUnused,
  /* 14: FENMI   */ R_G4MH_IsrFeUnused,
  /* 15: FEINT   */ R_G4MH_IsrFeUnused
};

/*******************************************************************************
 * Name        : g_peid4_DirVecEiPrjCfg
 * Description : array of User functions for EI exceptions using Direct Vector
 * Note        : Size of this array must match number of FE exceptions (16)
 *******************************************************************************/
const g4mh_isr_t g_peid4_DirVecEiPrjCfg[] =
{
  /* EI PRIO=0 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=1 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=2 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=3 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=4 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=5 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=6 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=7 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=8 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=9 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=10 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=11 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=12 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=13 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=14 */ R_G4MH_IsrEiDvUnused,
  /* EI PRIO=15 */ R_G4MH_IsrEiDvUnused
};

