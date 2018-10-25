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

/** \file   ee_tc_csfr.h
 *  \brief  Compiler independent CPU register IDs header file.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#ifndef OSEE_TC_CSFR_H
#define OSEE_TC_CSFR_H

/* Program Control 0 */
#define OSEE_CSFR_PCON0      (0x920CU)
/* Program Control 1 */
#define OSEE_CSFR_PCON1      (0x9204U)
/* Data Memory Control Register */
#define OSEE_CSFR_DCON0      (0x9040U)
/* Compatibility Control Register */
#define OSEE_CSFR_COMPAT     (0x9400U)

/* Counter Control */
#define OSEE_CSFR_CCTRL      (0xFC00U)
/* CPU Clock Cycle Count */
#define OSEE_CSFR_CCNT       (0xFC04U)
/* Previous Context Information Register */
#define OSEE_CSFR_PCXI       (0xFE00U)
/* Program Status Word */
#define OSEE_CSFR_PSW        (0xFE04U)
/* Program Counter */
#define OSEE_CSFR_PC         (0xFE08U)
/* System Configuration Register */
#define OSEE_CSFR_SYSCON     (0xFE14U)

/* Moved in ee_hal.h since these registers are accessible
   from user space, so they belong to the public API */
#if 0
/* CPUn Identification Register TC1.6P */
#define OSEE_CSFR_CPU_ID     (0xFE18U)
/* CPUn Core Identification Register */
#define OSEE_CSFR_CORE_ID    (0xFE1CU)
#endif /* 0 */
/* Base Interrupt Vector Table Pointer */
#define OSEE_CSFR_BIV        (0xFE20U)
/* Base Trap Vector Table Pointer */
#define OSEE_CSFR_BTV        (0xFE24U)
/* Interrupt Stack Pointer */
#define OSEE_CSFR_ISP        (0xFE28U)
/* Interrupt Control Register */
#define OSEE_CSFR_ICR        (0xFE2CU)
/* Free CSA List Head Pointer */
#define OSEE_CSFR_FCX        (0xFE38U)
/* Free CSA List Limit Pointer */
#define OSEE_CSFR_LCX        (0xFE3CU)

/* CPUn Data Protection Range 0, Lower Bound Register */
#define OSEE_CSFR_DPR0_L     (0xC000U)
/* CPUn Data Protection Range 1, Lower Bound Register */
#define OSEE_CSFR_DPR1_L     (0xC008U)
/* CPUn Data Protection Range 2, Lower Bound Register */
#define OSEE_CSFR_DPR2_L     (0xC010U)
/* CPUn Data Protection Range 3, Lower Bound Register */
#define OSEE_CSFR_DPR3_L     (0xC018U)
/* CPUn Data Protection Range 4, Lower Bound Register */
#define OSEE_CSFR_DPR4_L     (0xC020U)
/* CPUn Data Protection Range 5, Lower Bound Register */
#define OSEE_CSFR_DPR5_L     (0xC028U)
/* CPUn Data Protection Range 6, Lower Bound Register */
#define OSEE_CSFR_DPR6_L     (0xC030U)
/* CPUn Data Protection Range 7, Lower Bound Register */
#define OSEE_CSFR_DPR7_L     (0xC038U)
/* CPUn Data Protection Range 8, Lower Bound Register */
#define OSEE_CSFR_DPR8_L     (0xC040U)
/* CPUn Data Protection Range 9, Lower Bound Register */
#define OSEE_CSFR_DPR9_L     (0xC048U)
/* CPUn Data Protection Range 10, Lower Bound Register */
#define OSEE_CSFR_DPR10_L    (0xC050U)
/* CPUn Data Protection Range 11, Lower Bound Register */
#define OSEE_CSFR_DPR11_L    (0xC058U)
/* CPUn Data Protection Range 12, Lower Bound Register */
#define OSEE_CSFR_DPR12_L    (0xC060U)
/* CPUn Data Protection Range 13, Lower Bound Register */
#define OSEE_CSFR_DPR13_L    (0xC068U)
/* CPUn Data Protection Range 14, Lower Bound Register */
#define OSEE_CSFR_DPR14_L    (0xC070U)
/* CPUn Data Protection Range 15, Lower Bound Register */
#define OSEE_CSFR_DPR15_L    (0xC078U)
/* CPUn Data Protection Range 0, Upper Bound Register */
#define OSEE_CSFR_DPR0_U     (0xC004U)
/* CPUn Data Protection Range 1, Upper Bound Register */
#define OSEE_CSFR_DPR1_U     (0xC00CU)
/* CPUn Data Protection Range 2, Upper Bound Register */
#define OSEE_CSFR_DPR2_U     (0xC014U)
/* CPUn Data Protection Range 3, Upper Bound Register */
#define OSEE_CSFR_DPR3_U     (0xC01CU)
/* CPUn Data Protection Range 4, Upper Bound Register */
#define OSEE_CSFR_DPR4_U     (0xC024U)
/* CPUn Data Protection Range 5, Upper Bound Register */
#define OSEE_CSFR_DPR5_U     (0xC02CU)
/* CPUn Data Protection Range 6, Upper Bound Register */
#define OSEE_CSFR_DPR6_U     (0xC034U)
/* CPUn Data Protection Range 7, Upper Bound Register */
#define OSEE_CSFR_DPR7_U     (0xC03CU)
/* CPUn Data Protection Range 8, Upper Bound Register */
#define OSEE_CSFR_DPR8_U     (0xC044U)
/* CPUn Data Protection Range 9, Upper Bound Register */
#define OSEE_CSFR_DPR9_U     (0xC04CU)
/* CPUn Data Protection Range 10, Upper Bound Register */
#define OSEE_CSFR_DPR10_U    (0xC054U)
/* CPUn Data Protection Range 11, Upper Bound Register */
#define OSEE_CSFR_DPR11_U    (0xC05CU)
/* CPUn Data Protection Range 12, Upper Bound Register */
#define OSEE_CSFR_DPR12_U    (0xC064U)
/* CPUn Data Protection Range 13, Upper Bound Register */
#define OSEE_CSFR_DPR13_U    (0xC06CU)
/* CPUn Data Protection Range 14, Upper Bound Register */
#define OSEE_CSFR_DPR14_U    (0xC074U)
/* CPUn Data Protection Range 15, Upper Bound Register */
#define OSEE_CSFR_DPR15_U    (0xC07CU)

/* CPUn Code Protection Range 0 Lower Bound Register */
#define OSEE_CSFR_CPR0_L     (0xD000U)
/* CPUn Code Protection Range 1 Lower Bound Register */
#define OSEE_CSFR_CPR1_L     (0xD008U)
/* CPUn Code Protection Range 2 Lower Bound Register */
#define OSEE_CSFR_CPR2_L     (0xD010U)
/* CPUn Code Protection Range 3 Lower Bound Register */
#define OSEE_CSFR_CPR3_L     (0xD018U)
/* CPUn Code Protection Range 4 Lower Bound Register */
#define OSEE_CSFR_CPR4_L     (0xD020U)
/* CPUn Code Protection Range 5 Lower Bound Register */
#define OSEE_CSFR_CPR5_L     (0xD028U)
/* CPUn Code Protection Range 6 Lower Bound Register */
#define OSEE_CSFR_CPR6_L     (0xD030U)
/* CPUn Code Protection Range 7 Lower Bound Register */
#define OSEE_CSFR_CPR7_L     (0xD038U)
/* CPUn Code Protection Range 0 Upper Bound Register */
#define OSEE_CSFR_CPR0_U     (0xD004U)
/* CPUn Code Protection Range 1 Upper Bound Register */
#define OSEE_CSFR_CPR1_U     (0xD00CU)
/* CPUn Code Protection Range 2 Upper Bound Register */
#define OSEE_CSFR_CPR2_U     (0xD014U)
/* CPUn Code Protection Range 3 Upper Bound Register */
#define OSEE_CSFR_CPR3_U     (0xD01CU)
/* CPUn Code Protection Range 4 Upper Bound Register */
#define OSEE_CSFR_CPR4_U     (0xD024U)
/* CPUn Code Protection Range 5 Upper Bound Register */
#define OSEE_CSFR_CPR5_U     (0xD02CU)
/* CPUn Code Protection Range 6 Upper Bound Register */
#define OSEE_CSFR_CPR6_U     (0xD034U)
/* CPUn Code Protection Range 7 Upper Bound Register */
#define OSEE_CSFR_CPR7_U     (0xD03CU)

/* CPUn Data Protection Read Enable Register Set 0 */
#define OSEE_CSFR_DPRE_0     (0xE010U)
/* CPUn Data Protection Read Enable Register Set 1 */
#define OSEE_CSFR_DPRE_1     (0xE014U)
/* CPUn Data Protection Read Enable Register Set 2 */
#define OSEE_CSFR_DPRE_2     (0xE018U)
/* CPUn Data Protection Read Enable Register Set 3 */
#define OSEE_CSFR_DPRE_3     (0xE01CU)

/* CPUn Data Protection Write Enable Register Set 0 */
#define OSEE_CSFR_DPWE_0     (0xE020U)
/* CPUn Data Protection Write Enable Register Set 1 */
#define OSEE_CSFR_DPWE_1     (0xE024U)
/* CPUn Data Protection Write Enable Register Set 2 */
#define OSEE_CSFR_DPWE_2     (0xE028U)
/* CPUn Data Protection Write Enable Register Set 3 */
#define OSEE_CSFR_DPWE_3     (0xE02CU)

/* CPUn Code Protection Execute Enable Register Set 0 */
#define OSEE_CSFR_CPXE_0     (0xE000U)
/* CPUn Code Protection Execute Enable Register Set 1 */
#define OSEE_CSFR_CPXE_1     (0xE004U)
/* CPUn Code Protection Execute Enable Register Set 2 */
#define OSEE_CSFR_CPXE_2     (0xE008U)
/* CPUn Code Protection Execute Enable Register Set 3 */
#define OSEE_CSFR_CPXE_3     (0xE00CU)

/* CPUn Temporal Protection System Timer Register 0 */
#define OSEE_CSFR_TPS_TIMER0 (0xE404U)
/* CPUn Temporal Protection System Timer Register 0 */
#define OSEE_CSFR_TPS_TIMER1 (0xE408U)
/* CPUn Temporal Protection System Timer Register 0 */
#define OSEE_CSFR_TPS_TIMER2 (0xE40CU)
/* CPUn Temporal Protection System Control Register */
#define OSEE_CSFR_TPS_CON    (0xE400U)

#endif /* OSEE_TC_CSFR_H */
