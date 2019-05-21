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
 * ###*E*###
 */

/**
 * \file  ee_rh850_ei_ref_table_wr_diab.S
 * \brief EI Reference Table for PE0. Moreover if embark will let do this,
 *        this file could override _g_g4mh_RefTbl Embark Software
 *        Symbol for EI Table Reference.
 *
 * \author  Errico Guidieri
 * \date    2018
 */
 
#include "ee_cfg.h"
/* Include wrapper context macros */
#include "ee_rh850_ei_wrapper_ctx_wr_diab.hs"

  #----------------------------------------------------------------------------
  #-- Description : Reference Table for EI exceptions
  #-- Notes       : - This vector must start at 512 byte boundary (see
  #--                 information about INTBP register in
  #--                 "RH850G4MH U/M Software")
  #--             : - Size should match index of the highest EIINT exception
  #--                 channel in the system plus 1
  #--             : - INTBP register is initialized with this address on
  #--                 startup to change INTBP during execution use API
  #--                 R_G4MH_SetVectorTable
  #----------------------------------------------------------------------------
  .section ".g4mh_int"
#if (defined(OSEE_RH850_OVERRIDE_G4MH_REF_TABLE))
#define OSEE_RH850_REF_TABLE _g_g4mh_RefTbl
  .org 0x200
#else
#define OSEE_RH850_REF_TABLE _osEE_rh850_core0_reftabl_ei
  /*.align for RH850 use Power of 2 expression by default. So 2^9 = 512*/
  .align 9
#endif /* OSEE_RH850_OVERRIDE_G4MH_REF_TABLE */
  .global OSEE_RH850_REF_TABLE
OSEE_RH850_REF_TABLE:
#if (defined(OSEE_RH850_CORE0_0_ISR_CAT)) || (!defined(OSEE_SINGLECORE))
  .word _osEE_rh850_core0_ei0         #-- Core0 EIINT0
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT0
#endif /* OSEE_RH850_CORE0_0_ISR_CAT || !OSEE_SINGLECORE */
#if (defined(OSEE_RH850_CORE0_1_ISR_CAT))
  .word _osEE_rh850_core0_ei1         #-- Core0 EIINT1
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT1
#endif /* OSEE_RH850_CORE0_1_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_2_ISR_CAT))
  .word _osEE_rh850_core0_ei2         #-- Core0 EIINT2
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT2
#endif /* OSEE_RH850_CORE0_2_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_3_ISR_CAT))
  .word _osEE_rh850_core0_ei3         #-- Core0 EIINT3
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT3
#endif /* OSEE_RH850_CORE0_3_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_4_ISR_CAT))
  .word _osEE_rh850_core0_ei4         #-- Core0 EIINT4
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT4
#endif /* OSEE_RH850_CORE0_4_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_5_ISR_CAT))
  .word _osEE_rh850_core0_ei5         #-- Core0 EIINT5
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT5
#endif /* OSEE_RH850_CORE0_5_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_6_ISR_CAT))
  .word _osEE_rh850_core0_ei6         #-- Core0 EIINT6
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT6
#endif /* OSEE_RH850_CORE0_6_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_7_ISR_CAT))
  .word _osEE_rh850_core0_ei7         #-- Core0 EIINT7
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT7
#endif /* OSEE_RH850_CORE0_7_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_8_ISR_CAT))
  .word _osEE_rh850_core0_ei8         #-- Core0 EIINT8
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT8
#endif /* OSEE_RH850_CORE0_8_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_9_ISR_CAT))
  .word _osEE_rh850_core0_ei9         #-- Core0 EIINT9
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT9
#endif /* OSEE_RH850_CORE0_9_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_10_ISR_CAT))
  .word _osEE_rh850_core0_ei10        #-- Core0 EIINT10
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT10
#endif /* OSEE_RH850_CORE0_10_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_11_ISR_CAT))
  .word _osEE_rh850_core0_ei11        #-- Core0 EIINT11
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT11
#endif /* OSEE_RH850_CORE0_11_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_12_ISR_CAT))
  .word _osEE_rh850_core0_ei12        #-- Core0 EIINT12
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT12
#endif /* OSEE_RH850_CORE0_12_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_13_ISR_CAT))
  .word _osEE_rh850_core0_ei13        #-- Core0 EIINT13
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT13
#endif /* OSEE_RH850_CORE0_13_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_14_ISR_CAT))
  .word _osEE_rh850_core0_ei14        #-- Core0 EIINT14
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT14
#endif /* OSEE_RH850_CORE0_14_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_15_ISR_CAT))
  .word _osEE_rh850_core0_ei15        #-- Core0 EIINT15
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT15
#endif /* OSEE_RH850_CORE0_15_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_16_ISR_CAT))
  .word _osEE_rh850_core0_ei16        #-- Core0 EIINT16
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT16
#endif /* OSEE_RH850_CORE0_16_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_17_ISR_CAT))
  .word _osEE_rh850_core0_ei17        #-- Core0 EIINT17
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT17
#endif /* OSEE_RH850_CORE0_17_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_18_ISR_CAT))
  .word _osEE_rh850_core0_ei18        #-- Core0 EIINT18
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT18
#endif /* OSEE_RH850_CORE0_18_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_19_ISR_CAT))
  .word _osEE_rh850_core0_ei19        #-- Core0 EIINT19
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT19
#endif /* OSEE_RH850_CORE0_19_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_20_ISR_CAT))
  .word _osEE_rh850_core0_ei20        #-- Core0 EIINT20
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT20
#endif /* OSEE_RH850_CORE0_20_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_21_ISR_CAT))
  .word _osEE_rh850_core0_ei21        #-- Core0 EIINT21
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT21
#endif /* OSEE_RH850_CORE0_21_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_22_ISR_CAT))
  .word _osEE_rh850_core0_ei22        #-- Core0 EIINT22
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT22
#endif /* OSEE_RH850_CORE0_22_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_23_ISR_CAT))
  .word _osEE_rh850_core0_ei23        #-- Core0 EIINT23
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT23
#endif /* OSEE_RH850_CORE0_23_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_24_ISR_CAT))
  .word _osEE_rh850_core0_ei24        #-- Core0 EIINT24
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT24
#endif /* OSEE_RH850_CORE0_24_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_25_ISR_CAT))
  .word _osEE_rh850_core0_ei25        #-- Core0 EIINT25
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT25
#endif /* OSEE_RH850_CORE0_25_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_26_ISR_CAT))
  .word _osEE_rh850_core0_ei26        #-- Core0 EIINT26
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT26
#endif /* OSEE_RH850_CORE0_26_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_27_ISR_CAT))
  .word _osEE_rh850_core0_ei27        #-- Core0 EIINT27
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT27
#endif /* OSEE_RH850_CORE0_27_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_28_ISR_CAT))
  .word _osEE_rh850_core0_ei28        #-- Core0 EIINT28
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT28
#endif /* OSEE_RH850_CORE0_28_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_29_ISR_CAT))
  .word _osEE_rh850_core0_ei29        #-- Core0 EIINT29
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT29
#endif /* OSEE_RH850_CORE0_29_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_30_ISR_CAT))
  .word _osEE_rh850_core0_ei30        #-- Core0 EIINT30
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT30
#endif /* OSEE_RH850_CORE0_30_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_31_ISR_CAT))
  .word _osEE_rh850_core0_ei31        #-- Core0 EIINT31
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT31
#endif /* OSEE_RH850_CORE0_31_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_32_ISR_CAT))
  .word _osEE_rh850_core0_ei32        #-- Core0 EIINT32
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT32
#endif /* OSEE_RH850_CORE0_32_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_33_ISR_CAT))
  .word _osEE_rh850_core0_ei33        #-- Core0 EIINT33
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT33
#endif /* OSEE_RH850_CORE0_33_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_34_ISR_CAT))
  .word _osEE_rh850_core0_ei34        #-- Core0 EIINT34
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT34
#endif /* OSEE_RH850_CORE0_34_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_35_ISR_CAT))
  .word _osEE_rh850_core0_ei35        #-- Core0 EIINT35
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT35
#endif /* OSEE_RH850_CORE0_35_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_36_ISR_CAT))
  .word _osEE_rh850_core0_ei36        #-- Core0 EIINT36
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT36
#endif /* OSEE_RH850_CORE0_36_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_37_ISR_CAT))
  .word _osEE_rh850_core0_ei37        #-- Core0 EIINT37
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT37
#endif /* OSEE_RH850_CORE0_37_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_38_ISR_CAT))
  .word _osEE_rh850_core0_ei38        #-- Core0 EIINT38
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT38
#endif /* OSEE_RH850_CORE0_38_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_39_ISR_CAT))
  .word _osEE_rh850_core0_ei39        #-- Core0 EIINT39
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT39
#endif /* OSEE_RH850_CORE0_39_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_40_ISR_CAT))
  .word _osEE_rh850_core0_ei40        #-- Core0 EIINT40
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT40
#endif /* OSEE_RH850_CORE0_40_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_41_ISR_CAT))
  .word _osEE_rh850_core0_ei41        #-- Core0 EIINT41
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT41
#endif /* OSEE_RH850_CORE0_41_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_42_ISR_CAT))
  .word _osEE_rh850_core0_ei42        #-- Core0 EIINT42
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT42
#endif /* OSEE_RH850_CORE0_42_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_43_ISR_CAT))
  .word _osEE_rh850_core0_ei43        #-- Core0 EIINT43
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT43
#endif /* OSEE_RH850_CORE0_43_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_44_ISR_CAT))
  .word _osEE_rh850_core0_ei44        #-- Core0 EIINT44
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT44
#endif /* OSEE_RH850_CORE0_44_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_45_ISR_CAT))
  .word _osEE_rh850_core0_ei45        #-- Core0 EIINT45
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT45
#endif /* OSEE_RH850_CORE0_45_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_46_ISR_CAT))
  .word _osEE_rh850_core0_ei46        #-- Core0 EIINT46
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT46
#endif /* OSEE_RH850_CORE0_46_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_47_ISR_CAT))
  .word _osEE_rh850_core0_ei47        #-- Core0 EIINT47
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT47
#endif /* OSEE_RH850_CORE0_47_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_48_ISR_CAT))
  .word _osEE_rh850_core0_ei48        #-- Core0 EIINT48
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT48
#endif /* OSEE_RH850_CORE0_48_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_49_ISR_CAT))
  .word _osEE_rh850_core0_ei49        #-- Core0 EIINT49
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT49
#endif /* OSEE_RH850_CORE0_49_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_50_ISR_CAT))
  .word _osEE_rh850_core0_ei50        #-- Core0 EIINT50
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT50
#endif /* OSEE_RH850_CORE0_50_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_51_ISR_CAT))
  .word _osEE_rh850_core0_ei51        #-- Core0 EIINT51
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT51
#endif /* OSEE_RH850_CORE0_51_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_52_ISR_CAT))
  .word _osEE_rh850_core0_ei52        #-- Core0 EIINT52
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT52
#endif /* OSEE_RH850_CORE0_52_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_53_ISR_CAT))
  .word _osEE_rh850_core0_ei53        #-- Core0 EIINT53
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT53
#endif /* OSEE_RH850_CORE0_53_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_54_ISR_CAT))
  .word _osEE_rh850_core0_ei54        #-- Core0 EIINT54
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT54
#endif /* OSEE_RH850_CORE0_54_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_55_ISR_CAT))
  .word _osEE_rh850_core0_ei55        #-- Core0 EIINT55
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT55
#endif /* OSEE_RH850_CORE0_55_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_56_ISR_CAT))
  .word _osEE_rh850_core0_ei56        #-- Core0 EIINT56
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT56
#endif /* OSEE_RH850_CORE0_56_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_57_ISR_CAT))
  .word _osEE_rh850_core0_ei57        #-- Core0 EIINT57
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT57
#endif /* OSEE_RH850_CORE0_57_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_58_ISR_CAT))
  .word _osEE_rh850_core0_ei58        #-- Core0 EIINT58
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT58
#endif /* OSEE_RH850_CORE0_58_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_59_ISR_CAT))
  .word _osEE_rh850_core0_ei59        #-- Core0 EIINT59
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT59
#endif /* OSEE_RH850_CORE0_59_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_60_ISR_CAT))
  .word _osEE_rh850_core0_ei60        #-- Core0 EIINT60
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT60
#endif /* OSEE_RH850_CORE0_60_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_61_ISR_CAT))
  .word _osEE_rh850_core0_ei61        #-- Core0 EIINT61
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT61
#endif /* OSEE_RH850_CORE0_61_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_62_ISR_CAT))
  .word _osEE_rh850_core0_ei62        #-- Core0 EIINT62
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT62
#endif /* OSEE_RH850_CORE0_62_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_63_ISR_CAT))
  .word _osEE_rh850_core0_ei63        #-- Core0 EIINT63
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT63
#endif /* OSEE_RH850_CORE0_63_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_64_ISR_CAT))
  .word _osEE_rh850_core0_ei64        #-- Core0 EIINT64
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT64
#endif /* OSEE_RH850_CORE0_64_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_65_ISR_CAT))
  .word _osEE_rh850_core0_ei65        #-- Core0 EIINT65
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT65
#endif /* OSEE_RH850_CORE0_65_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_66_ISR_CAT))
  .word _osEE_rh850_core0_ei66        #-- Core0 EIINT66
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT66
#endif /* OSEE_RH850_CORE0_66_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_67_ISR_CAT))
  .word _osEE_rh850_core0_ei67        #-- Core0 EIINT67
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT67
#endif /* OSEE_RH850_CORE0_67_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_68_ISR_CAT))
  .word _osEE_rh850_core0_ei68        #-- Core0 EIINT68
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT68
#endif /* OSEE_RH850_CORE0_68_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_69_ISR_CAT))
  .word _osEE_rh850_core0_ei69        #-- Core0 EIINT69
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT69
#endif /* OSEE_RH850_CORE0_69_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_70_ISR_CAT))
  .word _osEE_rh850_core0_ei70        #-- Core0 EIINT70
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT70
#endif /* OSEE_RH850_CORE0_70_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_71_ISR_CAT))
  .word _osEE_rh850_core0_ei71        #-- Core0 EIINT71
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT71
#endif /* OSEE_RH850_CORE0_71_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_72_ISR_CAT))
  .word _osEE_rh850_core0_ei72        #-- Core0 EIINT72
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT72
#endif /* OSEE_RH850_CORE0_72_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_73_ISR_CAT))
  .word _osEE_rh850_core0_ei73        #-- Core0 EIINT73
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT73
#endif /* OSEE_RH850_CORE0_73_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_74_ISR_CAT))
  .word _osEE_rh850_core0_ei74        #-- Core0 EIINT74
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT74
#endif /* OSEE_RH850_CORE0_74_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_75_ISR_CAT))
  .word _osEE_rh850_core0_ei75        #-- Core0 EIINT75
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT75
#endif /* OSEE_RH850_CORE0_75_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_76_ISR_CAT))
  .word _osEE_rh850_core0_ei76        #-- Core0 EIINT76
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT76
#endif /* OSEE_RH850_CORE0_76_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_77_ISR_CAT))
  .word _osEE_rh850_core0_ei77        #-- Core0 EIINT77
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT77
#endif /* OSEE_RH850_CORE0_77_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_78_ISR_CAT))
  .word _osEE_rh850_core0_ei78        #-- Core0 EIINT78
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT78
#endif /* OSEE_RH850_CORE0_78_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_79_ISR_CAT))
  .word _osEE_rh850_core0_ei79        #-- Core0 EIINT79
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT79
#endif /* OSEE_RH850_CORE0_79_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_80_ISR_CAT))
  .word _osEE_rh850_core0_ei80        #-- Core0 EIINT80
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT80
#endif /* OSEE_RH850_CORE0_80_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_81_ISR_CAT))
  .word _osEE_rh850_core0_ei81        #-- Core0 EIINT81
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT81
#endif /* OSEE_RH850_CORE0_81_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_82_ISR_CAT))
  .word _osEE_rh850_core0_ei82        #-- Core0 EIINT82
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT82
#endif /* OSEE_RH850_CORE0_82_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_83_ISR_CAT))
  .word _osEE_rh850_core0_ei83        #-- Core0 EIINT83
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT83
#endif /* OSEE_RH850_CORE0_83_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_84_ISR_CAT))
  .word _osEE_rh850_core0_ei84        #-- Core0 EIINT84
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT84
#endif /* OSEE_RH850_CORE0_84_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_85_ISR_CAT))
  .word _osEE_rh850_core0_ei85        #-- Core0 EIINT85
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT85
#endif /* OSEE_RH850_CORE0_85_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_86_ISR_CAT))
  .word _osEE_rh850_core0_ei86        #-- Core0 EIINT86
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT86
#endif /* OSEE_RH850_CORE0_86_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_87_ISR_CAT))
  .word _osEE_rh850_core0_ei87        #-- Core0 EIINT87
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT87
#endif /* OSEE_RH850_CORE0_87_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_88_ISR_CAT))
  .word _osEE_rh850_core0_ei88        #-- Core0 EIINT88
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT88
#endif /* OSEE_RH850_CORE0_88_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_89_ISR_CAT))
  .word _osEE_rh850_core0_ei89        #-- Core0 EIINT89
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT89
#endif /* OSEE_RH850_CORE0_89_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_90_ISR_CAT))
  .word _osEE_rh850_core0_ei90        #-- Core0 EIINT90
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT90
#endif /* OSEE_RH850_CORE0_90_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_91_ISR_CAT))
  .word _osEE_rh850_core0_ei91        #-- Core0 EIINT91
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT91
#endif /* OSEE_RH850_CORE0_91_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_92_ISR_CAT))
  .word _osEE_rh850_core0_ei92        #-- Core0 EIINT92
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT92
#endif /* OSEE_RH850_CORE0_92_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_93_ISR_CAT))
  .word _osEE_rh850_core0_ei93        #-- Core0 EIINT93
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT93
#endif /* OSEE_RH850_CORE0_93_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_94_ISR_CAT))
  .word _osEE_rh850_core0_ei94        #-- Core0 EIINT94
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT94
#endif /* OSEE_RH850_CORE0_94_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_95_ISR_CAT))
  .word _osEE_rh850_core0_ei95        #-- Core0 EIINT95
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT95
#endif /* OSEE_RH850_CORE0_95_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_96_ISR_CAT))
  .word _osEE_rh850_core0_ei96        #-- Core0 EIINT96
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT96
#endif /* OSEE_RH850_CORE0_96_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_97_ISR_CAT))
  .word _osEE_rh850_core0_ei97        #-- Core0 EIINT97
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT97
#endif /* OSEE_RH850_CORE0_97_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_98_ISR_CAT))
  .word _osEE_rh850_core0_ei98        #-- Core0 EIINT98
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT98
#endif /* OSEE_RH850_CORE0_98_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_99_ISR_CAT))
  .word _osEE_rh850_core0_ei99        #-- Core0 EIINT99
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT99
#endif /* OSEE_RH850_CORE0_99_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_100_ISR_CAT))
  .word _osEE_rh850_core0_ei100       #-- Core0 EIINT100
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT100
#endif /* OSEE_RH850_CORE0_100_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_101_ISR_CAT))
  .word _osEE_rh850_core0_ei101       #-- Core0 EIINT101
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT101
#endif /* OSEE_RH850_CORE0_101_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_102_ISR_CAT))
  .word _osEE_rh850_core0_ei102       #-- Core0 EIINT102
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT102
#endif /* OSEE_RH850_CORE0_102_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_103_ISR_CAT))
  .word _osEE_rh850_core0_ei103       #-- Core0 EIINT103
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT103
#endif /* OSEE_RH850_CORE0_103_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_104_ISR_CAT))
  .word _osEE_rh850_core0_ei104       #-- Core0 EIINT104
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT104
#endif /* OSEE_RH850_CORE0_104_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_105_ISR_CAT))
  .word _osEE_rh850_core0_ei105       #-- Core0 EIINT105
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT105
#endif /* OSEE_RH850_CORE0_105_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_106_ISR_CAT))
  .word _osEE_rh850_core0_ei106       #-- Core0 EIINT106
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT106
#endif /* OSEE_RH850_CORE0_106_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_107_ISR_CAT))
  .word _osEE_rh850_core0_ei107       #-- Core0 EIINT107
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT107
#endif /* OSEE_RH850_CORE0_107_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_108_ISR_CAT))
  .word _osEE_rh850_core0_ei108       #-- Core0 EIINT108
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT108
#endif /* OSEE_RH850_CORE0_108_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_109_ISR_CAT))
  .word _osEE_rh850_core0_ei109       #-- Core0 EIINT109
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT109
#endif /* OSEE_RH850_CORE0_109_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_110_ISR_CAT))
  .word _osEE_rh850_core0_ei110       #-- Core0 EIINT110
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT110
#endif /* OSEE_RH850_CORE0_110_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_111_ISR_CAT))
  .word _osEE_rh850_core0_ei111       #-- Core0 EIINT111
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT111
#endif /* OSEE_RH850_CORE0_111_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_112_ISR_CAT))
  .word _osEE_rh850_core0_ei112       #-- Core0 EIINT112
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT112
#endif /* OSEE_RH850_CORE0_112_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_113_ISR_CAT))
  .word _osEE_rh850_core0_ei113       #-- Core0 EIINT113
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT113
#endif /* OSEE_RH850_CORE0_113_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_114_ISR_CAT))
  .word _osEE_rh850_core0_ei114       #-- Core0 EIINT114
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT114
#endif /* OSEE_RH850_CORE0_114_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_115_ISR_CAT))
  .word _osEE_rh850_core0_ei115       #-- Core0 EIINT115
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT115
#endif /* OSEE_RH850_CORE0_115_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_116_ISR_CAT))
  .word _osEE_rh850_core0_ei116       #-- Core0 EIINT116
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT116
#endif /* OSEE_RH850_CORE0_116_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_117_ISR_CAT))
  .word _osEE_rh850_core0_ei117       #-- Core0 EIINT117
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT117
#endif /* OSEE_RH850_CORE0_117_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_118_ISR_CAT))
  .word _osEE_rh850_core0_ei118       #-- Core0 EIINT118
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT118
#endif /* OSEE_RH850_CORE0_118_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_119_ISR_CAT))
  .word _osEE_rh850_core0_ei119       #-- Core0 EIINT119
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT119
#endif /* OSEE_RH850_CORE0_119_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_120_ISR_CAT))
  .word _osEE_rh850_core0_ei120       #-- Core0 EIINT120
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT120
#endif /* OSEE_RH850_CORE0_120_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_121_ISR_CAT))
  .word _osEE_rh850_core0_ei121       #-- Core0 EIINT121
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT121
#endif /* OSEE_RH850_CORE0_121_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_122_ISR_CAT))
  .word _osEE_rh850_core0_ei122       #-- Core0 EIINT122
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT122
#endif /* OSEE_RH850_CORE0_122_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_123_ISR_CAT))
  .word _osEE_rh850_core0_ei123       #-- Core0 EIINT123
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT123
#endif /* OSEE_RH850_CORE0_123_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_124_ISR_CAT))
  .word _osEE_rh850_core0_ei124       #-- Core0 EIINT124
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT124
#endif /* OSEE_RH850_CORE0_124_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_125_ISR_CAT))
  .word _osEE_rh850_core0_ei125       #-- Core0 EIINT125
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT125
#endif /* OSEE_RH850_CORE0_125_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_126_ISR_CAT))
  .word _osEE_rh850_core0_ei126       #-- Core0 EIINT126
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT126
#endif /* OSEE_RH850_CORE0_126_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_127_ISR_CAT))
  .word _osEE_rh850_core0_ei127       #-- Core0 EIINT127
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT127
#endif /* OSEE_RH850_CORE0_127_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_128_ISR_CAT))
  .word _osEE_rh850_core0_ei128       #-- Core0 EIINT128
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT128
#endif /* OSEE_RH850_CORE0_128_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_129_ISR_CAT))
  .word _osEE_rh850_core0_ei129       #-- Core0 EIINT129
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT129
#endif /* OSEE_RH850_CORE0_129_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_130_ISR_CAT))
  .word _osEE_rh850_core0_ei130       #-- Core0 EIINT130
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT130
#endif /* OSEE_RH850_CORE0_130_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_131_ISR_CAT))
  .word _osEE_rh850_core0_ei131       #-- Core0 EIINT131
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT131
#endif /* OSEE_RH850_CORE0_131_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_132_ISR_CAT))
  .word _osEE_rh850_core0_ei132       #-- Core0 EIINT132
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT132
#endif /* OSEE_RH850_CORE0_132_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_133_ISR_CAT))
  .word _osEE_rh850_core0_ei133       #-- Core0 EIINT133
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT133
#endif /* OSEE_RH850_CORE0_133_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_134_ISR_CAT))
  .word _osEE_rh850_core0_ei134       #-- Core0 EIINT134
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT134
#endif /* OSEE_RH850_CORE0_134_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_135_ISR_CAT))
  .word _osEE_rh850_core0_ei135       #-- Core0 EIINT135
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT135
#endif /* OSEE_RH850_CORE0_135_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_136_ISR_CAT))
  .word _osEE_rh850_core0_ei136       #-- Core0 EIINT136
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT136
#endif /* OSEE_RH850_CORE0_136_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_137_ISR_CAT))
  .word _osEE_rh850_core0_ei137       #-- Core0 EIINT137
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT137
#endif /* OSEE_RH850_CORE0_137_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_138_ISR_CAT))
  .word _osEE_rh850_core0_ei138       #-- Core0 EIINT138
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT138
#endif /* OSEE_RH850_CORE0_138_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_139_ISR_CAT))
  .word _osEE_rh850_core0_ei139       #-- Core0 EIINT139
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT139
#endif /* OSEE_RH850_CORE0_139_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_140_ISR_CAT))
  .word _osEE_rh850_core0_ei140       #-- Core0 EIINT140
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT140
#endif /* OSEE_RH850_CORE0_140_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_141_ISR_CAT))
  .word _osEE_rh850_core0_ei141       #-- Core0 EIINT141
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT141
#endif /* OSEE_RH850_CORE0_141_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_142_ISR_CAT))
  .word _osEE_rh850_core0_ei142       #-- Core0 EIINT142
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT142
#endif /* OSEE_RH850_CORE0_142_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_143_ISR_CAT))
  .word _osEE_rh850_core0_ei143       #-- Core0 EIINT143
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT143
#endif /* OSEE_RH850_CORE0_143_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_144_ISR_CAT))
  .word _osEE_rh850_core0_ei144       #-- Core0 EIINT144
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT144
#endif /* OSEE_RH850_CORE0_144_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_145_ISR_CAT))
  .word _osEE_rh850_core0_ei145       #-- Core0 EIINT145
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT145
#endif /* OSEE_RH850_CORE0_145_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_146_ISR_CAT))
  .word _osEE_rh850_core0_ei146       #-- Core0 EIINT146
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT146
#endif /* OSEE_RH850_CORE0_146_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_147_ISR_CAT))
  .word _osEE_rh850_core0_ei147       #-- Core0 EIINT147
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT147
#endif /* OSEE_RH850_CORE0_147_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_148_ISR_CAT))
  .word _osEE_rh850_core0_ei148       #-- Core0 EIINT148
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT148
#endif /* OSEE_RH850_CORE0_148_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_149_ISR_CAT))
  .word _osEE_rh850_core0_ei149       #-- Core0 EIINT149
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT149
#endif /* OSEE_RH850_CORE0_149_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_150_ISR_CAT))
  .word _osEE_rh850_core0_ei150       #-- Core0 EIINT150
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT150
#endif /* OSEE_RH850_CORE0_150_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_151_ISR_CAT))
  .word _osEE_rh850_core0_ei151       #-- Core0 EIINT151
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT151
#endif /* OSEE_RH850_CORE0_151_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_152_ISR_CAT))
  .word _osEE_rh850_core0_ei152       #-- Core0 EIINT152
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT152
#endif /* OSEE_RH850_CORE0_152_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_153_ISR_CAT))
  .word _osEE_rh850_core0_ei153       #-- Core0 EIINT153
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT153
#endif /* OSEE_RH850_CORE0_153_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_154_ISR_CAT))
  .word _osEE_rh850_core0_ei154       #-- Core0 EIINT154
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT154
#endif /* OSEE_RH850_CORE0_154_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_155_ISR_CAT))
  .word _osEE_rh850_core0_ei155       #-- Core0 EIINT155
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT155
#endif /* OSEE_RH850_CORE0_155_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_156_ISR_CAT))
  .word _osEE_rh850_core0_ei156       #-- Core0 EIINT156
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT156
#endif /* OSEE_RH850_CORE0_156_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_157_ISR_CAT))
  .word _osEE_rh850_core0_ei157       #-- Core0 EIINT157
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT157
#endif /* OSEE_RH850_CORE0_157_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_158_ISR_CAT))
  .word _osEE_rh850_core0_ei158       #-- Core0 EIINT158
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT158
#endif /* OSEE_RH850_CORE0_158_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_159_ISR_CAT))
  .word _osEE_rh850_core0_ei159       #-- Core0 EIINT159
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT159
#endif /* OSEE_RH850_CORE0_159_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_160_ISR_CAT))
  .word _osEE_rh850_core0_ei160       #-- Core0 EIINT160
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT160
#endif /* OSEE_RH850_CORE0_160_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_161_ISR_CAT))
  .word _osEE_rh850_core0_ei161       #-- Core0 EIINT161
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT161
#endif /* OSEE_RH850_CORE0_161_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_162_ISR_CAT))
  .word _osEE_rh850_core0_ei162       #-- Core0 EIINT162
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT162
#endif /* OSEE_RH850_CORE0_162_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_163_ISR_CAT))
  .word _osEE_rh850_core0_ei163       #-- Core0 EIINT163
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT163
#endif /* OSEE_RH850_CORE0_163_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_164_ISR_CAT))
  .word _osEE_rh850_core0_ei164       #-- Core0 EIINT164
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT164
#endif /* OSEE_RH850_CORE0_164_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_165_ISR_CAT))
  .word _osEE_rh850_core0_ei165       #-- Core0 EIINT165
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT165
#endif /* OSEE_RH850_CORE0_165_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_166_ISR_CAT))
  .word _osEE_rh850_core0_ei166       #-- Core0 EIINT166
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT166
#endif /* OSEE_RH850_CORE0_166_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_167_ISR_CAT))
  .word _osEE_rh850_core0_ei167       #-- Core0 EIINT167
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT167
#endif /* OSEE_RH850_CORE0_167_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_168_ISR_CAT))
  .word _osEE_rh850_core0_ei168       #-- Core0 EIINT168
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT168
#endif /* OSEE_RH850_CORE0_168_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_169_ISR_CAT))
  .word _osEE_rh850_core0_ei169       #-- Core0 EIINT169
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT169
#endif /* OSEE_RH850_CORE0_169_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_170_ISR_CAT))
  .word _osEE_rh850_core0_ei170       #-- Core0 EIINT170
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT170
#endif /* OSEE_RH850_CORE0_170_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_171_ISR_CAT))
  .word _osEE_rh850_core0_ei171       #-- Core0 EIINT171
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT171
#endif /* OSEE_RH850_CORE0_171_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_172_ISR_CAT))
  .word _osEE_rh850_core0_ei172       #-- Core0 EIINT172
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT172
#endif /* OSEE_RH850_CORE0_172_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_173_ISR_CAT))
  .word _osEE_rh850_core0_ei173       #-- Core0 EIINT173
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT173
#endif /* OSEE_RH850_CORE0_173_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_174_ISR_CAT))
  .word _osEE_rh850_core0_ei174       #-- Core0 EIINT174
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT174
#endif /* OSEE_RH850_CORE0_174_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_175_ISR_CAT))
  .word _osEE_rh850_core0_ei175       #-- Core0 EIINT175
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT175
#endif /* OSEE_RH850_CORE0_175_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_176_ISR_CAT))
  .word _osEE_rh850_core0_ei176       #-- Core0 EIINT176
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT176
#endif /* OSEE_RH850_CORE0_176_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_177_ISR_CAT))
  .word _osEE_rh850_core0_ei177       #-- Core0 EIINT177
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT177
#endif /* OSEE_RH850_CORE0_177_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_178_ISR_CAT))
  .word _osEE_rh850_core0_ei178       #-- Core0 EIINT178
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT178
#endif /* OSEE_RH850_CORE0_178_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_179_ISR_CAT))
  .word _osEE_rh850_core0_ei179       #-- Core0 EIINT179
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT179
#endif /* OSEE_RH850_CORE0_179_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_180_ISR_CAT))
  .word _osEE_rh850_core0_ei180       #-- Core0 EIINT180
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT180
#endif /* OSEE_RH850_CORE0_180_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_181_ISR_CAT))
  .word _osEE_rh850_core0_ei181       #-- Core0 EIINT181
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT181
#endif /* OSEE_RH850_CORE0_181_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_182_ISR_CAT))
  .word _osEE_rh850_core0_ei182       #-- Core0 EIINT182
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT182
#endif /* OSEE_RH850_CORE0_182_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_183_ISR_CAT))
  .word _osEE_rh850_core0_ei183       #-- Core0 EIINT183
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT183
#endif /* OSEE_RH850_CORE0_183_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_184_ISR_CAT))
  .word _osEE_rh850_core0_ei184       #-- Core0 EIINT184
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT184
#endif /* OSEE_RH850_CORE0_184_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_185_ISR_CAT))
  .word _osEE_rh850_core0_ei185       #-- Core0 EIINT185
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT185
#endif /* OSEE_RH850_CORE0_185_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_186_ISR_CAT))
  .word _osEE_rh850_core0_ei186       #-- Core0 EIINT186
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT186
#endif /* OSEE_RH850_CORE0_186_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_187_ISR_CAT))
  .word _osEE_rh850_core0_ei187       #-- Core0 EIINT187
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT187
#endif /* OSEE_RH850_CORE0_187_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_188_ISR_CAT))
  .word _osEE_rh850_core0_ei188       #-- Core0 EIINT188
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT188
#endif /* OSEE_RH850_CORE0_188_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_189_ISR_CAT))
  .word _osEE_rh850_core0_ei189       #-- Core0 EIINT189
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT189
#endif /* OSEE_RH850_CORE0_189_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_190_ISR_CAT))
  .word _osEE_rh850_core0_ei190       #-- Core0 EIINT190
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT190
#endif /* OSEE_RH850_CORE0_190_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_191_ISR_CAT))
  .word _osEE_rh850_core0_ei191       #-- Core0 EIINT191
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT191
#endif /* OSEE_RH850_CORE0_191_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_192_ISR_CAT))
  .word _osEE_rh850_core0_ei192       #-- Core0 EIINT192
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT192
#endif /* OSEE_RH850_CORE0_192_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_193_ISR_CAT))
  .word _osEE_rh850_core0_ei193       #-- Core0 EIINT193
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT193
#endif /* OSEE_RH850_CORE0_193_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_194_ISR_CAT))
  .word _osEE_rh850_core0_ei194       #-- Core0 EIINT194
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT194
#endif /* OSEE_RH850_CORE0_194_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_195_ISR_CAT))
  .word _osEE_rh850_core0_ei195       #-- Core0 EIINT195
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT195
#endif /* OSEE_RH850_CORE0_195_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_196_ISR_CAT))
  .word _osEE_rh850_core0_ei196       #-- Core0 EIINT196
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT196
#endif /* OSEE_RH850_CORE0_196_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_197_ISR_CAT))
  .word _osEE_rh850_core0_ei197       #-- Core0 EIINT197
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT197
#endif /* OSEE_RH850_CORE0_197_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_198_ISR_CAT))
  .word _osEE_rh850_core0_ei198       #-- Core0 EIINT198
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT198
#endif /* OSEE_RH850_CORE0_198_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_199_ISR_CAT))
  .word _osEE_rh850_core0_ei199       #-- Core0 EIINT199
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT199
#endif /* OSEE_RH850_CORE0_199_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_200_ISR_CAT))
  .word _osEE_rh850_core0_ei200       #-- Core0 EIINT200
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT200
#endif /* OSEE_RH850_CORE0_200_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_201_ISR_CAT))
  .word _osEE_rh850_core0_ei201       #-- Core0 EIINT201
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT201
#endif /* OSEE_RH850_CORE0_201_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_202_ISR_CAT))
  .word _osEE_rh850_core0_ei202       #-- Core0 EIINT202
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT202
#endif /* OSEE_RH850_CORE0_202_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_203_ISR_CAT))
  .word _osEE_rh850_core0_ei203       #-- Core0 EIINT203
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT203
#endif /* OSEE_RH850_CORE0_203_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_204_ISR_CAT))
  .word _osEE_rh850_core0_ei204       #-- Core0 EIINT204
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT204
#endif /* OSEE_RH850_CORE0_204_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_205_ISR_CAT))
  .word _osEE_rh850_core0_ei205       #-- Core0 EIINT205
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT205
#endif /* OSEE_RH850_CORE0_205_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_206_ISR_CAT))
  .word _osEE_rh850_core0_ei206       #-- Core0 EIINT206
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT206
#endif /* OSEE_RH850_CORE0_206_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_207_ISR_CAT))
  .word _osEE_rh850_core0_ei207       #-- Core0 EIINT207
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT207
#endif /* OSEE_RH850_CORE0_207_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_208_ISR_CAT))
  .word _osEE_rh850_core0_ei208       #-- Core0 EIINT208
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT208
#endif /* OSEE_RH850_CORE0_208_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_209_ISR_CAT))
  .word _osEE_rh850_core0_ei209       #-- Core0 EIINT209
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT209
#endif /* OSEE_RH850_CORE0_209_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_210_ISR_CAT))
  .word _osEE_rh850_core0_ei210       #-- Core0 EIINT210
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT210
#endif /* OSEE_RH850_CORE0_210_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_211_ISR_CAT))
  .word _osEE_rh850_core0_ei211       #-- Core0 EIINT211
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT211
#endif /* OSEE_RH850_CORE0_211_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_212_ISR_CAT))
  .word _osEE_rh850_core0_ei212       #-- Core0 EIINT212
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT212
#endif /* OSEE_RH850_CORE0_212_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_213_ISR_CAT))
  .word _osEE_rh850_core0_ei213       #-- Core0 EIINT213
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT213
#endif /* OSEE_RH850_CORE0_213_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_214_ISR_CAT))
  .word _osEE_rh850_core0_ei214       #-- Core0 EIINT214
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT214
#endif /* OSEE_RH850_CORE0_214_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_215_ISR_CAT))
  .word _osEE_rh850_core0_ei215       #-- Core0 EIINT215
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT215
#endif /* OSEE_RH850_CORE0_215_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_216_ISR_CAT))
  .word _osEE_rh850_core0_ei216       #-- Core0 EIINT216
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT216
#endif /* OSEE_RH850_CORE0_216_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_217_ISR_CAT))
  .word _osEE_rh850_core0_ei217       #-- Core0 EIINT217
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT217
#endif /* OSEE_RH850_CORE0_217_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_218_ISR_CAT))
  .word _osEE_rh850_core0_ei218       #-- Core0 EIINT218
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT218
#endif /* OSEE_RH850_CORE0_218_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_219_ISR_CAT))
  .word _osEE_rh850_core0_ei219       #-- Core0 EIINT219
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT219
#endif /* OSEE_RH850_CORE0_219_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_220_ISR_CAT))
  .word _osEE_rh850_core0_ei220       #-- Core0 EIINT220
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT220
#endif /* OSEE_RH850_CORE0_220_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_221_ISR_CAT))
  .word _osEE_rh850_core0_ei221       #-- Core0 EIINT221
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT221
#endif /* OSEE_RH850_CORE0_221_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_222_ISR_CAT))
  .word _osEE_rh850_core0_ei222       #-- Core0 EIINT222
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT222
#endif /* OSEE_RH850_CORE0_222_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_223_ISR_CAT))
  .word _osEE_rh850_core0_ei223       #-- Core0 EIINT223
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT223
#endif /* OSEE_RH850_CORE0_223_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_224_ISR_CAT))
  .word _osEE_rh850_core0_ei224       #-- Core0 EIINT224
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT224
#endif /* OSEE_RH850_CORE0_224_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_225_ISR_CAT))
  .word _osEE_rh850_core0_ei225       #-- Core0 EIINT225
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT225
#endif /* OSEE_RH850_CORE0_225_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_226_ISR_CAT))
  .word _osEE_rh850_core0_ei226       #-- Core0 EIINT226
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT226
#endif /* OSEE_RH850_CORE0_226_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_227_ISR_CAT))
  .word _osEE_rh850_core0_ei227       #-- Core0 EIINT227
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT227
#endif /* OSEE_RH850_CORE0_227_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_228_ISR_CAT))
  .word _osEE_rh850_core0_ei228       #-- Core0 EIINT228
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT228
#endif /* OSEE_RH850_CORE0_228_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_229_ISR_CAT))
  .word _osEE_rh850_core0_ei229       #-- Core0 EIINT229
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT229
#endif /* OSEE_RH850_CORE0_229_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_230_ISR_CAT))
  .word _osEE_rh850_core0_ei230       #-- Core0 EIINT230
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT230
#endif /* OSEE_RH850_CORE0_230_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_231_ISR_CAT))
  .word _osEE_rh850_core0_ei231       #-- Core0 EIINT231
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT231
#endif /* OSEE_RH850_CORE0_231_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_232_ISR_CAT))
  .word _osEE_rh850_core0_ei232       #-- Core0 EIINT232
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT232
#endif /* OSEE_RH850_CORE0_232_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_233_ISR_CAT))
  .word _osEE_rh850_core0_ei233       #-- Core0 EIINT233
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT233
#endif /* OSEE_RH850_CORE0_233_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_234_ISR_CAT))
  .word _osEE_rh850_core0_ei234       #-- Core0 EIINT234
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT234
#endif /* OSEE_RH850_CORE0_234_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_235_ISR_CAT))
  .word _osEE_rh850_core0_ei235       #-- Core0 EIINT235
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT235
#endif /* OSEE_RH850_CORE0_235_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_236_ISR_CAT))
  .word _osEE_rh850_core0_ei236       #-- Core0 EIINT236
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT236
#endif /* OSEE_RH850_CORE0_236_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_237_ISR_CAT))
  .word _osEE_rh850_core0_ei237       #-- Core0 EIINT237
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT237
#endif /* OSEE_RH850_CORE0_237_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_238_ISR_CAT))
  .word _osEE_rh850_core0_ei238       #-- Core0 EIINT238
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT238
#endif /* OSEE_RH850_CORE0_238_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_239_ISR_CAT))
  .word _osEE_rh850_core0_ei239       #-- Core0 EIINT239
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT239
#endif /* OSEE_RH850_CORE0_239_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_240_ISR_CAT))
  .word _osEE_rh850_core0_ei240       #-- Core0 EIINT240
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT240
#endif /* OSEE_RH850_CORE0_240_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_241_ISR_CAT))
  .word _osEE_rh850_core0_ei241       #-- Core0 EIINT241
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT241
#endif /* OSEE_RH850_CORE0_241_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_242_ISR_CAT))
  .word _osEE_rh850_core0_ei242       #-- Core0 EIINT242
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT242
#endif /* OSEE_RH850_CORE0_242_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_243_ISR_CAT))
  .word _osEE_rh850_core0_ei243       #-- Core0 EIINT243
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT243
#endif /* OSEE_RH850_CORE0_243_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_244_ISR_CAT))
  .word _osEE_rh850_core0_ei244       #-- Core0 EIINT244
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT244
#endif /* OSEE_RH850_CORE0_244_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_245_ISR_CAT))
  .word _osEE_rh850_core0_ei245       #-- Core0 EIINT245
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT245
#endif /* OSEE_RH850_CORE0_245_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_246_ISR_CAT))
  .word _osEE_rh850_core0_ei246       #-- Core0 EIINT246
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT246
#endif /* OSEE_RH850_CORE0_246_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_247_ISR_CAT))
  .word _osEE_rh850_core0_ei247       #-- Core0 EIINT247
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT247
#endif /* OSEE_RH850_CORE0_247_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_248_ISR_CAT))
  .word _osEE_rh850_core0_ei248       #-- Core0 EIINT248
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT248
#endif /* OSEE_RH850_CORE0_248_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_249_ISR_CAT))
  .word _osEE_rh850_core0_ei249       #-- Core0 EIINT249
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT249
#endif /* OSEE_RH850_CORE0_249_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_250_ISR_CAT))
  .word _osEE_rh850_core0_ei250       #-- Core0 EIINT250
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT250
#endif /* OSEE_RH850_CORE0_250_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_251_ISR_CAT))
  .word _osEE_rh850_core0_ei251       #-- Core0 EIINT251
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT251
#endif /* OSEE_RH850_CORE0_251_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_252_ISR_CAT))
  .word _osEE_rh850_core0_ei252       #-- Core0 EIINT252
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT252
#endif /* OSEE_RH850_CORE0_252_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_253_ISR_CAT))
  .word _osEE_rh850_core0_ei253       #-- Core0 EIINT253
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT253
#endif /* OSEE_RH850_CORE0_253_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_254_ISR_CAT))
  .word _osEE_rh850_core0_ei254       #-- Core0 EIINT254
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT254
#endif /* OSEE_RH850_CORE0_254_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_255_ISR_CAT))
  .word _osEE_rh850_core0_ei255       #-- Core0 EIINT255
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT255
#endif /* OSEE_RH850_CORE0_255_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_256_ISR_CAT))
  .word _osEE_rh850_core0_ei256       #-- Core0 EIINT256
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT256
#endif /* OSEE_RH850_CORE0_256_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_257_ISR_CAT))
  .word _osEE_rh850_core0_ei257       #-- Core0 EIINT257
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT257
#endif /* OSEE_RH850_CORE0_257_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_258_ISR_CAT))
  .word _osEE_rh850_core0_ei258       #-- Core0 EIINT258
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT258
#endif /* OSEE_RH850_CORE0_258_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_259_ISR_CAT))
  .word _osEE_rh850_core0_ei259       #-- Core0 EIINT259
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT259
#endif /* OSEE_RH850_CORE0_259_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_260_ISR_CAT))
  .word _osEE_rh850_core0_ei260       #-- Core0 EIINT260
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT260
#endif /* OSEE_RH850_CORE0_260_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_261_ISR_CAT))
  .word _osEE_rh850_core0_ei261       #-- Core0 EIINT261
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT261
#endif /* OSEE_RH850_CORE0_261_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_262_ISR_CAT))
  .word _osEE_rh850_core0_ei262       #-- Core0 EIINT262
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT262
#endif /* OSEE_RH850_CORE0_262_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_263_ISR_CAT))
  .word _osEE_rh850_core0_ei263       #-- Core0 EIINT263
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT263
#endif /* OSEE_RH850_CORE0_263_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_264_ISR_CAT))
  .word _osEE_rh850_core0_ei264       #-- Core0 EIINT264
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT264
#endif /* OSEE_RH850_CORE0_264_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_265_ISR_CAT))
  .word _osEE_rh850_core0_ei265       #-- Core0 EIINT265
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT265
#endif /* OSEE_RH850_CORE0_265_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_266_ISR_CAT))
  .word _osEE_rh850_core0_ei266       #-- Core0 EIINT266
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT266
#endif /* OSEE_RH850_CORE0_266_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_267_ISR_CAT))
  .word _osEE_rh850_core0_ei267       #-- Core0 EIINT267
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT267
#endif /* OSEE_RH850_CORE0_267_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_268_ISR_CAT))
  .word _osEE_rh850_core0_ei268       #-- Core0 EIINT268
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT268
#endif /* OSEE_RH850_CORE0_268_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_269_ISR_CAT))
  .word _osEE_rh850_core0_ei269       #-- Core0 EIINT269
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT269
#endif /* OSEE_RH850_CORE0_269_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_270_ISR_CAT))
  .word _osEE_rh850_core0_ei270       #-- Core0 EIINT270
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT270
#endif /* OSEE_RH850_CORE0_270_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_271_ISR_CAT))
  .word _osEE_rh850_core0_ei271       #-- Core0 EIINT271
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT271
#endif /* OSEE_RH850_CORE0_271_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_272_ISR_CAT))
  .word _osEE_rh850_core0_ei272       #-- Core0 EIINT272
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT272
#endif /* OSEE_RH850_CORE0_272_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_273_ISR_CAT))
  .word _osEE_rh850_core0_ei273       #-- Core0 EIINT273
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT273
#endif /* OSEE_RH850_CORE0_273_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_274_ISR_CAT))
  .word _osEE_rh850_core0_ei274       #-- Core0 EIINT274
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT274
#endif /* OSEE_RH850_CORE0_274_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_275_ISR_CAT))
  .word _osEE_rh850_core0_ei275       #-- Core0 EIINT275
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT275
#endif /* OSEE_RH850_CORE0_275_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_276_ISR_CAT))
  .word _osEE_rh850_core0_ei276       #-- Core0 EIINT276
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT276
#endif /* OSEE_RH850_CORE0_276_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_277_ISR_CAT))
  .word _osEE_rh850_core0_ei277       #-- Core0 EIINT277
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT277
#endif /* OSEE_RH850_CORE0_277_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_278_ISR_CAT))
  .word _osEE_rh850_core0_ei278       #-- Core0 EIINT278
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT278
#endif /* OSEE_RH850_CORE0_278_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_279_ISR_CAT))
  .word _osEE_rh850_core0_ei279       #-- Core0 EIINT279
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT279
#endif /* OSEE_RH850_CORE0_279_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_280_ISR_CAT))
  .word _osEE_rh850_core0_ei280       #-- Core0 EIINT280
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT280
#endif /* OSEE_RH850_CORE0_280_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_281_ISR_CAT))
  .word _osEE_rh850_core0_ei281       #-- Core0 EIINT281
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT281
#endif /* OSEE_RH850_CORE0_281_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_282_ISR_CAT))
  .word _osEE_rh850_core0_ei282       #-- Core0 EIINT282
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT282
#endif /* OSEE_RH850_CORE0_282_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_283_ISR_CAT))
  .word _osEE_rh850_core0_ei283       #-- Core0 EIINT283
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT283
#endif /* OSEE_RH850_CORE0_283_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_284_ISR_CAT))
  .word _osEE_rh850_core0_ei284       #-- Core0 EIINT284
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT284
#endif /* OSEE_RH850_CORE0_284_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_285_ISR_CAT))
  .word _osEE_rh850_core0_ei285       #-- Core0 EIINT285
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT285
#endif /* OSEE_RH850_CORE0_285_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_286_ISR_CAT))
  .word _osEE_rh850_core0_ei286       #-- Core0 EIINT286
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT286
#endif /* OSEE_RH850_CORE0_286_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_287_ISR_CAT))
  .word _osEE_rh850_core0_ei287       #-- Core0 EIINT287
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT287
#endif /* OSEE_RH850_CORE0_287_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_288_ISR_CAT))
  .word _osEE_rh850_core0_ei288       #-- Core0 EIINT288
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT288
#endif /* OSEE_RH850_CORE0_288_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_289_ISR_CAT))
  .word _osEE_rh850_core0_ei289       #-- Core0 EIINT289
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT289
#endif /* OSEE_RH850_CORE0_289_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_290_ISR_CAT))
  .word _osEE_rh850_core0_ei290       #-- Core0 EIINT290
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT290
#endif /* OSEE_RH850_CORE0_290_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_291_ISR_CAT))
  .word _osEE_rh850_core0_ei291       #-- Core0 EIINT291
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT291
#endif /* OSEE_RH850_CORE0_291_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_292_ISR_CAT))
  .word _osEE_rh850_core0_ei292       #-- Core0 EIINT292
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT292
#endif /* OSEE_RH850_CORE0_292_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_293_ISR_CAT))
  .word _osEE_rh850_core0_ei293       #-- Core0 EIINT293
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT293
#endif /* OSEE_RH850_CORE0_293_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_294_ISR_CAT))
  .word _osEE_rh850_core0_ei294       #-- Core0 EIINT294
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT294
#endif /* OSEE_RH850_CORE0_294_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_295_ISR_CAT))
  .word _osEE_rh850_core0_ei295       #-- Core0 EIINT295
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT295
#endif /* OSEE_RH850_CORE0_295_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_296_ISR_CAT))
  .word _osEE_rh850_core0_ei296       #-- Core0 EIINT296
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT296
#endif /* OSEE_RH850_CORE0_296_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_297_ISR_CAT))
  .word _osEE_rh850_core0_ei297       #-- Core0 EIINT297
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT297
#endif /* OSEE_RH850_CORE0_297_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_298_ISR_CAT))
  .word _osEE_rh850_core0_ei298       #-- Core0 EIINT298
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT298
#endif /* OSEE_RH850_CORE0_298_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_299_ISR_CAT))
  .word _osEE_rh850_core0_ei299       #-- Core0 EIINT299
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT299
#endif /* OSEE_RH850_CORE0_299_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_300_ISR_CAT))
  .word _osEE_rh850_core0_ei300       #-- Core0 EIINT300
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT300
#endif /* OSEE_RH850_CORE0_300_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_301_ISR_CAT))
  .word _osEE_rh850_core0_ei301       #-- Core0 EIINT301
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT301
#endif /* OSEE_RH850_CORE0_301_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_302_ISR_CAT))
  .word _osEE_rh850_core0_ei302       #-- Core0 EIINT302
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT302
#endif /* OSEE_RH850_CORE0_302_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_303_ISR_CAT))
  .word _osEE_rh850_core0_ei303       #-- Core0 EIINT303
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT303
#endif /* OSEE_RH850_CORE0_303_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_304_ISR_CAT))
  .word _osEE_rh850_core0_ei304       #-- Core0 EIINT304
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT304
#endif /* OSEE_RH850_CORE0_304_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_305_ISR_CAT))
  .word _osEE_rh850_core0_ei305       #-- Core0 EIINT305
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT305
#endif /* OSEE_RH850_CORE0_305_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_306_ISR_CAT))
  .word _osEE_rh850_core0_ei306       #-- Core0 EIINT306
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT306
#endif /* OSEE_RH850_CORE0_306_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_307_ISR_CAT))
  .word _osEE_rh850_core0_ei307       #-- Core0 EIINT307
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT307
#endif /* OSEE_RH850_CORE0_307_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_308_ISR_CAT))
  .word _osEE_rh850_core0_ei308       #-- Core0 EIINT308
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT308
#endif /* OSEE_RH850_CORE0_308_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_309_ISR_CAT))
  .word _osEE_rh850_core0_ei309       #-- Core0 EIINT309
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT309
#endif /* OSEE_RH850_CORE0_309_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_310_ISR_CAT))
  .word _osEE_rh850_core0_ei310       #-- Core0 EIINT310
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT310
#endif /* OSEE_RH850_CORE0_310_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_311_ISR_CAT))
  .word _osEE_rh850_core0_ei311       #-- Core0 EIINT311
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT311
#endif /* OSEE_RH850_CORE0_311_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_312_ISR_CAT))
  .word _osEE_rh850_core0_ei312       #-- Core0 EIINT312
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT312
#endif /* OSEE_RH850_CORE0_312_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_313_ISR_CAT))
  .word _osEE_rh850_core0_ei313       #-- Core0 EIINT313
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT313
#endif /* OSEE_RH850_CORE0_313_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_314_ISR_CAT))
  .word _osEE_rh850_core0_ei314       #-- Core0 EIINT314
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT314
#endif /* OSEE_RH850_CORE0_314_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_315_ISR_CAT))
  .word _osEE_rh850_core0_ei315       #-- Core0 EIINT315
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT315
#endif /* OSEE_RH850_CORE0_315_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_316_ISR_CAT))
  .word _osEE_rh850_core0_ei316       #-- Core0 EIINT316
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT316
#endif /* OSEE_RH850_CORE0_316_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_317_ISR_CAT))
  .word _osEE_rh850_core0_ei317       #-- Core0 EIINT317
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT317
#endif /* OSEE_RH850_CORE0_317_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_318_ISR_CAT))
  .word _osEE_rh850_core0_ei318       #-- Core0 EIINT318
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT318
#endif /* OSEE_RH850_CORE0_318_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_319_ISR_CAT))
  .word _osEE_rh850_core0_ei319       #-- Core0 EIINT319
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT319
#endif /* OSEE_RH850_CORE0_319_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_320_ISR_CAT))
  .word _osEE_rh850_core0_ei320       #-- Core0 EIINT320
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT320
#endif /* OSEE_RH850_CORE0_320_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_321_ISR_CAT))
  .word _osEE_rh850_core0_ei321       #-- Core0 EIINT321
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT321
#endif /* OSEE_RH850_CORE0_321_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_322_ISR_CAT))
  .word _osEE_rh850_core0_ei322       #-- Core0 EIINT322
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT322
#endif /* OSEE_RH850_CORE0_322_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_323_ISR_CAT))
  .word _osEE_rh850_core0_ei323       #-- Core0 EIINT323
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT323
#endif /* OSEE_RH850_CORE0_323_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_324_ISR_CAT))
  .word _osEE_rh850_core0_ei324       #-- Core0 EIINT324
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT324
#endif /* OSEE_RH850_CORE0_324_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_325_ISR_CAT))
  .word _osEE_rh850_core0_ei325       #-- Core0 EIINT325
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT325
#endif /* OSEE_RH850_CORE0_325_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_326_ISR_CAT))
  .word _osEE_rh850_core0_ei326       #-- Core0 EIINT326
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT326
#endif /* OSEE_RH850_CORE0_326_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_327_ISR_CAT))
  .word _osEE_rh850_core0_ei327       #-- Core0 EIINT327
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT327
#endif /* OSEE_RH850_CORE0_327_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_328_ISR_CAT))
  .word _osEE_rh850_core0_ei328       #-- Core0 EIINT328
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT328
#endif /* OSEE_RH850_CORE0_328_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_329_ISR_CAT))
  .word _osEE_rh850_core0_ei329       #-- Core0 EIINT329
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT329
#endif /* OSEE_RH850_CORE0_329_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_330_ISR_CAT))
  .word _osEE_rh850_core0_ei330       #-- Core0 EIINT330
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT330
#endif /* OSEE_RH850_CORE0_330_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_331_ISR_CAT))
  .word _osEE_rh850_core0_ei331       #-- Core0 EIINT331
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT331
#endif /* OSEE_RH850_CORE0_331_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_332_ISR_CAT))
  .word _osEE_rh850_core0_ei332       #-- Core0 EIINT332
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT332
#endif /* OSEE_RH850_CORE0_332_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_333_ISR_CAT))
  .word _osEE_rh850_core0_ei333       #-- Core0 EIINT333
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT333
#endif /* OSEE_RH850_CORE0_333_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_334_ISR_CAT))
  .word _osEE_rh850_core0_ei334       #-- Core0 EIINT334
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT334
#endif /* OSEE_RH850_CORE0_334_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_335_ISR_CAT))
  .word _osEE_rh850_core0_ei335       #-- Core0 EIINT335
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT335
#endif /* OSEE_RH850_CORE0_335_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_336_ISR_CAT))
  .word _osEE_rh850_core0_ei336       #-- Core0 EIINT336
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT336
#endif /* OSEE_RH850_CORE0_336_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_337_ISR_CAT))
  .word _osEE_rh850_core0_ei337       #-- Core0 EIINT337
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT337
#endif /* OSEE_RH850_CORE0_337_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_338_ISR_CAT))
  .word _osEE_rh850_core0_ei338       #-- Core0 EIINT338
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT338
#endif /* OSEE_RH850_CORE0_338_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_339_ISR_CAT))
  .word _osEE_rh850_core0_ei339       #-- Core0 EIINT339
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT339
#endif /* OSEE_RH850_CORE0_339_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_340_ISR_CAT))
  .word _osEE_rh850_core0_ei340       #-- Core0 EIINT340
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT340
#endif /* OSEE_RH850_CORE0_340_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_341_ISR_CAT))
  .word _osEE_rh850_core0_ei341       #-- Core0 EIINT341
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT341
#endif /* OSEE_RH850_CORE0_341_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_342_ISR_CAT))
  .word _osEE_rh850_core0_ei342       #-- Core0 EIINT342
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT342
#endif /* OSEE_RH850_CORE0_342_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_343_ISR_CAT))
  .word _osEE_rh850_core0_ei343       #-- Core0 EIINT343
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT343
#endif /* OSEE_RH850_CORE0_343_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_344_ISR_CAT))
  .word _osEE_rh850_core0_ei344       #-- Core0 EIINT344
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT344
#endif /* OSEE_RH850_CORE0_344_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_345_ISR_CAT))
  .word _osEE_rh850_core0_ei345       #-- Core0 EIINT345
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT345
#endif /* OSEE_RH850_CORE0_345_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_346_ISR_CAT))
  .word _osEE_rh850_core0_ei346       #-- Core0 EIINT346
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT346
#endif /* OSEE_RH850_CORE0_346_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_347_ISR_CAT))
  .word _osEE_rh850_core0_ei347       #-- Core0 EIINT347
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT347
#endif /* OSEE_RH850_CORE0_347_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_348_ISR_CAT))
  .word _osEE_rh850_core0_ei348       #-- Core0 EIINT348
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT348
#endif /* OSEE_RH850_CORE0_348_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_349_ISR_CAT))
  .word _osEE_rh850_core0_ei349       #-- Core0 EIINT349
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT349
#endif /* OSEE_RH850_CORE0_349_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_350_ISR_CAT))
  .word _osEE_rh850_core0_ei350       #-- Core0 EIINT350
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT350
#endif /* OSEE_RH850_CORE0_350_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_351_ISR_CAT))
  .word _osEE_rh850_core0_ei351       #-- Core0 EIINT351
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT351
#endif /* OSEE_RH850_CORE0_351_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_352_ISR_CAT))
  .word _osEE_rh850_core0_ei352       #-- Core0 EIINT352
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT352
#endif /* OSEE_RH850_CORE0_352_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_353_ISR_CAT))
  .word _osEE_rh850_core0_ei353       #-- Core0 EIINT353
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT353
#endif /* OSEE_RH850_CORE0_353_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_354_ISR_CAT))
  .word _osEE_rh850_core0_ei354       #-- Core0 EIINT354
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT354
#endif /* OSEE_RH850_CORE0_354_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_355_ISR_CAT))
  .word _osEE_rh850_core0_ei355       #-- Core0 EIINT355
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT355
#endif /* OSEE_RH850_CORE0_355_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_356_ISR_CAT))
  .word _osEE_rh850_core0_ei356       #-- Core0 EIINT356
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT356
#endif /* OSEE_RH850_CORE0_356_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_357_ISR_CAT))
  .word _osEE_rh850_core0_ei357       #-- Core0 EIINT357
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT357
#endif /* OSEE_RH850_CORE0_357_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_358_ISR_CAT))
  .word _osEE_rh850_core0_ei358       #-- Core0 EIINT358
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT358
#endif /* OSEE_RH850_CORE0_358_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_359_ISR_CAT))
  .word _osEE_rh850_core0_ei359       #-- Core0 EIINT359
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT359
#endif /* OSEE_RH850_CORE0_359_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_360_ISR_CAT))
  .word _osEE_rh850_core0_ei360       #-- Core0 EIINT360
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT360
#endif /* OSEE_RH850_CORE0_360_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_361_ISR_CAT))
  .word _osEE_rh850_core0_ei361       #-- Core0 EIINT361
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT361
#endif /* OSEE_RH850_CORE0_361_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_362_ISR_CAT))
  .word _osEE_rh850_core0_ei362       #-- Core0 EIINT362
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT362
#endif /* OSEE_RH850_CORE0_362_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_363_ISR_CAT))
  .word _osEE_rh850_core0_ei363       #-- Core0 EIINT363
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT363
#endif /* OSEE_RH850_CORE0_363_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_364_ISR_CAT))
  .word _osEE_rh850_core0_ei364       #-- Core0 EIINT364
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT364
#endif /* OSEE_RH850_CORE0_364_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_365_ISR_CAT))
  .word _osEE_rh850_core0_ei365       #-- Core0 EIINT365
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT365
#endif /* OSEE_RH850_CORE0_365_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_366_ISR_CAT))
  .word _osEE_rh850_core0_ei366       #-- Core0 EIINT366
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT366
#endif /* OSEE_RH850_CORE0_366_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_367_ISR_CAT))
  .word _osEE_rh850_core0_ei367       #-- Core0 EIINT367
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT367
#endif /* OSEE_RH850_CORE0_367_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_368_ISR_CAT))
  .word _osEE_rh850_core0_ei368       #-- Core0 EIINT368
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT368
#endif /* OSEE_RH850_CORE0_368_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_369_ISR_CAT))
  .word _osEE_rh850_core0_ei369       #-- Core0 EIINT369
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT369
#endif /* OSEE_RH850_CORE0_369_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_370_ISR_CAT))
  .word _osEE_rh850_core0_ei370       #-- Core0 EIINT370
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT370
#endif /* OSEE_RH850_CORE0_370_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_371_ISR_CAT))
  .word _osEE_rh850_core0_ei371       #-- Core0 EIINT371
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT371
#endif /* OSEE_RH850_CORE0_371_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_372_ISR_CAT))
  .word _osEE_rh850_core0_ei372       #-- Core0 EIINT372
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT372
#endif /* OSEE_RH850_CORE0_372_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_373_ISR_CAT))
  .word _osEE_rh850_core0_ei373       #-- Core0 EIINT373
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT373
#endif /* OSEE_RH850_CORE0_373_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_374_ISR_CAT))
  .word _osEE_rh850_core0_ei374       #-- Core0 EIINT374
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT374
#endif /* OSEE_RH850_CORE0_374_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_375_ISR_CAT))
  .word _osEE_rh850_core0_ei375       #-- Core0 EIINT375
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT375
#endif /* OSEE_RH850_CORE0_375_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_376_ISR_CAT))
  .word _osEE_rh850_core0_ei376       #-- Core0 EIINT376
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT376
#endif /* OSEE_RH850_CORE0_376_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_377_ISR_CAT))
  .word _osEE_rh850_core0_ei377       #-- Core0 EIINT377
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT377
#endif /* OSEE_RH850_CORE0_377_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_378_ISR_CAT))
  .word _osEE_rh850_core0_ei378       #-- Core0 EIINT378
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT378
#endif /* OSEE_RH850_CORE0_378_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_379_ISR_CAT))
  .word _osEE_rh850_core0_ei379       #-- Core0 EIINT379
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT379
#endif /* OSEE_RH850_CORE0_379_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_380_ISR_CAT))
  .word _osEE_rh850_core0_ei380       #-- Core0 EIINT380
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT380
#endif /* OSEE_RH850_CORE0_380_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_381_ISR_CAT))
  .word _osEE_rh850_core0_ei381       #-- Core0 EIINT381
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT381
#endif /* OSEE_RH850_CORE0_381_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_382_ISR_CAT))
  .word _osEE_rh850_core0_ei382       #-- Core0 EIINT382
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT382
#endif /* OSEE_RH850_CORE0_382_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_383_ISR_CAT))
  .word _osEE_rh850_core0_ei383       #-- Core0 EIINT383
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT383
#endif /* OSEE_RH850_CORE0_383_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_384_ISR_CAT))
  .word _osEE_rh850_core0_ei384       #-- Core0 EIINT384
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT384
#endif /* OSEE_RH850_CORE0_384_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_385_ISR_CAT))
  .word _osEE_rh850_core0_ei385       #-- Core0 EIINT385
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT385
#endif /* OSEE_RH850_CORE0_385_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_386_ISR_CAT))
  .word _osEE_rh850_core0_ei386       #-- Core0 EIINT386
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT386
#endif /* OSEE_RH850_CORE0_386_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_387_ISR_CAT))
  .word _osEE_rh850_core0_ei387       #-- Core0 EIINT387
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT387
#endif /* OSEE_RH850_CORE0_387_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_388_ISR_CAT))
  .word _osEE_rh850_core0_ei388       #-- Core0 EIINT388
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT388
#endif /* OSEE_RH850_CORE0_388_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_389_ISR_CAT))
  .word _osEE_rh850_core0_ei389       #-- Core0 EIINT389
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT389
#endif /* OSEE_RH850_CORE0_389_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_390_ISR_CAT))
  .word _osEE_rh850_core0_ei390       #-- Core0 EIINT390
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT390
#endif /* OSEE_RH850_CORE0_390_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_391_ISR_CAT))
  .word _osEE_rh850_core0_ei391       #-- Core0 EIINT391
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT391
#endif /* OSEE_RH850_CORE0_391_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_392_ISR_CAT))
  .word _osEE_rh850_core0_ei392       #-- Core0 EIINT392
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT392
#endif /* OSEE_RH850_CORE0_392_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_393_ISR_CAT))
  .word _osEE_rh850_core0_ei393       #-- Core0 EIINT393
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT393
#endif /* OSEE_RH850_CORE0_393_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_394_ISR_CAT))
  .word _osEE_rh850_core0_ei394       #-- Core0 EIINT394
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT394
#endif /* OSEE_RH850_CORE0_394_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_395_ISR_CAT))
  .word _osEE_rh850_core0_ei395       #-- Core0 EIINT395
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT395
#endif /* OSEE_RH850_CORE0_395_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_396_ISR_CAT))
  .word _osEE_rh850_core0_ei396       #-- Core0 EIINT396
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT396
#endif /* OSEE_RH850_CORE0_396_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_397_ISR_CAT))
  .word _osEE_rh850_core0_ei397       #-- Core0 EIINT397
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT397
#endif /* OSEE_RH850_CORE0_397_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_398_ISR_CAT))
  .word _osEE_rh850_core0_ei398       #-- Core0 EIINT398
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT398
#endif /* OSEE_RH850_CORE0_398_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_399_ISR_CAT))
  .word _osEE_rh850_core0_ei399       #-- Core0 EIINT399
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT399
#endif /* OSEE_RH850_CORE0_399_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_400_ISR_CAT))
  .word _osEE_rh850_core0_ei400       #-- Core0 EIINT400
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT400
#endif /* OSEE_RH850_CORE0_400_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_401_ISR_CAT))
  .word _osEE_rh850_core0_ei401       #-- Core0 EIINT401
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT401
#endif /* OSEE_RH850_CORE0_401_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_402_ISR_CAT))
  .word _osEE_rh850_core0_ei402       #-- Core0 EIINT402
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT402
#endif /* OSEE_RH850_CORE0_402_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_403_ISR_CAT))
  .word _osEE_rh850_core0_ei403       #-- Core0 EIINT403
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT403
#endif /* OSEE_RH850_CORE0_403_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_404_ISR_CAT))
  .word _osEE_rh850_core0_ei404       #-- Core0 EIINT404
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT404
#endif /* OSEE_RH850_CORE0_404_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_405_ISR_CAT))
  .word _osEE_rh850_core0_ei405       #-- Core0 EIINT405
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT405
#endif /* OSEE_RH850_CORE0_405_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_406_ISR_CAT))
  .word _osEE_rh850_core0_ei406       #-- Core0 EIINT406
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT406
#endif /* OSEE_RH850_CORE0_406_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_407_ISR_CAT))
  .word _osEE_rh850_core0_ei407       #-- Core0 EIINT407
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT407
#endif /* OSEE_RH850_CORE0_407_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_408_ISR_CAT))
  .word _osEE_rh850_core0_ei408       #-- Core0 EIINT408
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT408
#endif /* OSEE_RH850_CORE0_408_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_409_ISR_CAT))
  .word _osEE_rh850_core0_ei409       #-- Core0 EIINT409
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT409
#endif /* OSEE_RH850_CORE0_409_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_410_ISR_CAT))
  .word _osEE_rh850_core0_ei410       #-- Core0 EIINT410
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT410
#endif /* OSEE_RH850_CORE0_410_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_411_ISR_CAT))
  .word _osEE_rh850_core0_ei411       #-- Core0 EIINT411
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT411
#endif /* OSEE_RH850_CORE0_411_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_412_ISR_CAT))
  .word _osEE_rh850_core0_ei412       #-- Core0 EIINT412
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT412
#endif /* OSEE_RH850_CORE0_412_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_413_ISR_CAT))
  .word _osEE_rh850_core0_ei413       #-- Core0 EIINT413
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT413
#endif /* OSEE_RH850_CORE0_413_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_414_ISR_CAT))
  .word _osEE_rh850_core0_ei414       #-- Core0 EIINT414
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT414
#endif /* OSEE_RH850_CORE0_414_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_415_ISR_CAT))
  .word _osEE_rh850_core0_ei415       #-- Core0 EIINT415
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT415
#endif /* OSEE_RH850_CORE0_415_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_416_ISR_CAT))
  .word _osEE_rh850_core0_ei416       #-- Core0 EIINT416
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT416
#endif /* OSEE_RH850_CORE0_416_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_417_ISR_CAT))
  .word _osEE_rh850_core0_ei417       #-- Core0 EIINT417
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT417
#endif /* OSEE_RH850_CORE0_417_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_418_ISR_CAT))
  .word _osEE_rh850_core0_ei418       #-- Core0 EIINT418
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT418
#endif /* OSEE_RH850_CORE0_418_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_419_ISR_CAT))
  .word _osEE_rh850_core0_ei419       #-- Core0 EIINT419
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT419
#endif /* OSEE_RH850_CORE0_419_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_420_ISR_CAT))
  .word _osEE_rh850_core0_ei420       #-- Core0 EIINT420
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT420
#endif /* OSEE_RH850_CORE0_420_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_421_ISR_CAT))
  .word _osEE_rh850_core0_ei421       #-- Core0 EIINT421
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT421
#endif /* OSEE_RH850_CORE0_421_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_422_ISR_CAT))
  .word _osEE_rh850_core0_ei422       #-- Core0 EIINT422
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT422
#endif /* OSEE_RH850_CORE0_422_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_423_ISR_CAT))
  .word _osEE_rh850_core0_ei423       #-- Core0 EIINT423
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT423
#endif /* OSEE_RH850_CORE0_423_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_424_ISR_CAT))
  .word _osEE_rh850_core0_ei424       #-- Core0 EIINT424
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT424
#endif /* OSEE_RH850_CORE0_424_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_425_ISR_CAT))
  .word _osEE_rh850_core0_ei425       #-- Core0 EIINT425
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT425
#endif /* OSEE_RH850_CORE0_425_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_426_ISR_CAT))
  .word _osEE_rh850_core0_ei426       #-- Core0 EIINT426
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT426
#endif /* OSEE_RH850_CORE0_426_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_427_ISR_CAT))
  .word _osEE_rh850_core0_ei427       #-- Core0 EIINT427
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT427
#endif /* OSEE_RH850_CORE0_427_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_428_ISR_CAT))
  .word _osEE_rh850_core0_ei428       #-- Core0 EIINT428
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT428
#endif /* OSEE_RH850_CORE0_428_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_429_ISR_CAT))
  .word _osEE_rh850_core0_ei429       #-- Core0 EIINT429
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT429
#endif /* OSEE_RH850_CORE0_429_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_430_ISR_CAT))
  .word _osEE_rh850_core0_ei430       #-- Core0 EIINT430
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT430
#endif /* OSEE_RH850_CORE0_430_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_431_ISR_CAT))
  .word _osEE_rh850_core0_ei431       #-- Core0 EIINT431
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT431
#endif /* OSEE_RH850_CORE0_431_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_432_ISR_CAT))
  .word _osEE_rh850_core0_ei432       #-- Core0 EIINT432
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT432
#endif /* OSEE_RH850_CORE0_432_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_433_ISR_CAT))
  .word _osEE_rh850_core0_ei433       #-- Core0 EIINT433
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT433
#endif /* OSEE_RH850_CORE0_433_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_434_ISR_CAT))
  .word _osEE_rh850_core0_ei434       #-- Core0 EIINT434
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT434
#endif /* OSEE_RH850_CORE0_434_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_435_ISR_CAT))
  .word _osEE_rh850_core0_ei435       #-- Core0 EIINT435
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT435
#endif /* OSEE_RH850_CORE0_435_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_436_ISR_CAT))
  .word _osEE_rh850_core0_ei436       #-- Core0 EIINT436
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT436
#endif /* OSEE_RH850_CORE0_436_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_437_ISR_CAT))
  .word _osEE_rh850_core0_ei437       #-- Core0 EIINT437
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT437
#endif /* OSEE_RH850_CORE0_437_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_438_ISR_CAT))
  .word _osEE_rh850_core0_ei438       #-- Core0 EIINT438
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT438
#endif /* OSEE_RH850_CORE0_438_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_439_ISR_CAT))
  .word _osEE_rh850_core0_ei439       #-- Core0 EIINT439
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT439
#endif /* OSEE_RH850_CORE0_439_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_440_ISR_CAT))
  .word _osEE_rh850_core0_ei440       #-- Core0 EIINT440
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT440
#endif /* OSEE_RH850_CORE0_440_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_441_ISR_CAT))
  .word _osEE_rh850_core0_ei441       #-- Core0 EIINT441
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT441
#endif /* OSEE_RH850_CORE0_441_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_442_ISR_CAT))
  .word _osEE_rh850_core0_ei442       #-- Core0 EIINT442
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT442
#endif /* OSEE_RH850_CORE0_442_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_443_ISR_CAT))
  .word _osEE_rh850_core0_ei443       #-- Core0 EIINT443
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT443
#endif /* OSEE_RH850_CORE0_443_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_444_ISR_CAT))
  .word _osEE_rh850_core0_ei444       #-- Core0 EIINT444
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT444
#endif /* OSEE_RH850_CORE0_444_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_445_ISR_CAT))
  .word _osEE_rh850_core0_ei445       #-- Core0 EIINT445
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT445
#endif /* OSEE_RH850_CORE0_445_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_446_ISR_CAT))
  .word _osEE_rh850_core0_ei446       #-- Core0 EIINT446
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT446
#endif /* OSEE_RH850_CORE0_446_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_447_ISR_CAT))
  .word _osEE_rh850_core0_ei447       #-- Core0 EIINT447
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT447
#endif /* OSEE_RH850_CORE0_447_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_448_ISR_CAT))
  .word _osEE_rh850_core0_ei448       #-- Core0 EIINT448
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT448
#endif /* OSEE_RH850_CORE0_448_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_449_ISR_CAT))
  .word _osEE_rh850_core0_ei449       #-- Core0 EIINT449
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT449
#endif /* OSEE_RH850_CORE0_449_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_450_ISR_CAT))
  .word _osEE_rh850_core0_ei450       #-- Core0 EIINT450
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT450
#endif /* OSEE_RH850_CORE0_450_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_451_ISR_CAT))
  .word _osEE_rh850_core0_ei451       #-- Core0 EIINT451
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT451
#endif /* OSEE_RH850_CORE0_451_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_452_ISR_CAT))
  .word _osEE_rh850_core0_ei452       #-- Core0 EIINT452
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT452
#endif /* OSEE_RH850_CORE0_452_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_453_ISR_CAT))
  .word _osEE_rh850_core0_ei453       #-- Core0 EIINT453
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT453
#endif /* OSEE_RH850_CORE0_453_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_454_ISR_CAT))
  .word _osEE_rh850_core0_ei454       #-- Core0 EIINT454
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT454
#endif /* OSEE_RH850_CORE0_454_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_455_ISR_CAT))
  .word _osEE_rh850_core0_ei455       #-- Core0 EIINT455
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT455
#endif /* OSEE_RH850_CORE0_455_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_456_ISR_CAT))
  .word _osEE_rh850_core0_ei456       #-- Core0 EIINT456
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT456
#endif /* OSEE_RH850_CORE0_456_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_457_ISR_CAT))
  .word _osEE_rh850_core0_ei457       #-- Core0 EIINT457
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT457
#endif /* OSEE_RH850_CORE0_457_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_458_ISR_CAT))
  .word _osEE_rh850_core0_ei458       #-- Core0 EIINT458
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT458
#endif /* OSEE_RH850_CORE0_458_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_459_ISR_CAT))
  .word _osEE_rh850_core0_ei459       #-- Core0 EIINT459
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT459
#endif /* OSEE_RH850_CORE0_459_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_460_ISR_CAT))
  .word _osEE_rh850_core0_ei460       #-- Core0 EIINT460
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT460
#endif /* OSEE_RH850_CORE0_460_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_461_ISR_CAT))
  .word _osEE_rh850_core0_ei461       #-- Core0 EIINT461
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT461
#endif /* OSEE_RH850_CORE0_461_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_462_ISR_CAT))
  .word _osEE_rh850_core0_ei462       #-- Core0 EIINT462
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT462
#endif /* OSEE_RH850_CORE0_462_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_463_ISR_CAT))
  .word _osEE_rh850_core0_ei463       #-- Core0 EIINT463
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT463
#endif /* OSEE_RH850_CORE0_463_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_464_ISR_CAT))
  .word _osEE_rh850_core0_ei464       #-- Core0 EIINT464
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT464
#endif /* OSEE_RH850_CORE0_464_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_465_ISR_CAT))
  .word _osEE_rh850_core0_ei465       #-- Core0 EIINT465
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT465
#endif /* OSEE_RH850_CORE0_465_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_466_ISR_CAT))
  .word _osEE_rh850_core0_ei466       #-- Core0 EIINT466
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT466
#endif /* OSEE_RH850_CORE0_466_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_467_ISR_CAT))
  .word _osEE_rh850_core0_ei467       #-- Core0 EIINT467
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT467
#endif /* OSEE_RH850_CORE0_467_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_468_ISR_CAT))
  .word _osEE_rh850_core0_ei468       #-- Core0 EIINT468
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT468
#endif /* OSEE_RH850_CORE0_468_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_469_ISR_CAT))
  .word _osEE_rh850_core0_ei469       #-- Core0 EIINT469
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT469
#endif /* OSEE_RH850_CORE0_469_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_470_ISR_CAT))
  .word _osEE_rh850_core0_ei470       #-- Core0 EIINT470
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT470
#endif /* OSEE_RH850_CORE0_470_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_471_ISR_CAT))
  .word _osEE_rh850_core0_ei471       #-- Core0 EIINT471
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT471
#endif /* OSEE_RH850_CORE0_471_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_472_ISR_CAT))
  .word _osEE_rh850_core0_ei472       #-- Core0 EIINT472
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT472
#endif /* OSEE_RH850_CORE0_472_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_473_ISR_CAT))
  .word _osEE_rh850_core0_ei473       #-- Core0 EIINT473
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT473
#endif /* OSEE_RH850_CORE0_473_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_474_ISR_CAT))
  .word _osEE_rh850_core0_ei474       #-- Core0 EIINT474
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT474
#endif /* OSEE_RH850_CORE0_474_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_475_ISR_CAT))
  .word _osEE_rh850_core0_ei475       #-- Core0 EIINT475
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT475
#endif /* OSEE_RH850_CORE0_475_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_476_ISR_CAT))
  .word _osEE_rh850_core0_ei476       #-- Core0 EIINT476
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT476
#endif /* OSEE_RH850_CORE0_476_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_477_ISR_CAT))
  .word _osEE_rh850_core0_ei477       #-- Core0 EIINT477
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT477
#endif /* OSEE_RH850_CORE0_477_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_478_ISR_CAT))
  .word _osEE_rh850_core0_ei478       #-- Core0 EIINT478
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT478
#endif /* OSEE_RH850_CORE0_478_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_479_ISR_CAT))
  .word _osEE_rh850_core0_ei479       #-- Core0 EIINT479
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT479
#endif /* OSEE_RH850_CORE0_479_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_480_ISR_CAT))
  .word _osEE_rh850_core0_ei480       #-- Core0 EIINT480
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT480
#endif /* OSEE_RH850_CORE0_480_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_481_ISR_CAT))
  .word _osEE_rh850_core0_ei481       #-- Core0 EIINT481
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT481
#endif /* OSEE_RH850_CORE0_481_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_482_ISR_CAT))
  .word _osEE_rh850_core0_ei482       #-- Core0 EIINT482
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT482
#endif /* OSEE_RH850_CORE0_482_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_483_ISR_CAT))
  .word _osEE_rh850_core0_ei483       #-- Core0 EIINT483
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT483
#endif /* OSEE_RH850_CORE0_483_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_484_ISR_CAT))
  .word _osEE_rh850_core0_ei484       #-- Core0 EIINT484
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT484
#endif /* OSEE_RH850_CORE0_484_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_485_ISR_CAT))
  .word _osEE_rh850_core0_ei485       #-- Core0 EIINT485
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT485
#endif /* OSEE_RH850_CORE0_485_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_486_ISR_CAT))
  .word _osEE_rh850_core0_ei486       #-- Core0 EIINT486
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT486
#endif /* OSEE_RH850_CORE0_486_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_487_ISR_CAT))
  .word _osEE_rh850_core0_ei487       #-- Core0 EIINT487
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT487
#endif /* OSEE_RH850_CORE0_487_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_488_ISR_CAT))
  .word _osEE_rh850_core0_ei488       #-- Core0 EIINT488
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT488
#endif /* OSEE_RH850_CORE0_488_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_489_ISR_CAT))
  .word _osEE_rh850_core0_ei489       #-- Core0 EIINT489
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT489
#endif /* OSEE_RH850_CORE0_489_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_490_ISR_CAT))
  .word _osEE_rh850_core0_ei490       #-- Core0 EIINT490
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT490
#endif /* OSEE_RH850_CORE0_490_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_491_ISR_CAT))
  .word _osEE_rh850_core0_ei491       #-- Core0 EIINT491
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT491
#endif /* OSEE_RH850_CORE0_491_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_492_ISR_CAT))
  .word _osEE_rh850_core0_ei492       #-- Core0 EIINT492
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT492
#endif /* OSEE_RH850_CORE0_492_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_493_ISR_CAT))
  .word _osEE_rh850_core0_ei493       #-- Core0 EIINT493
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT493
#endif /* OSEE_RH850_CORE0_493_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_494_ISR_CAT))
  .word _osEE_rh850_core0_ei494       #-- Core0 EIINT494
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT494
#endif /* OSEE_RH850_CORE0_494_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_495_ISR_CAT))
  .word _osEE_rh850_core0_ei495       #-- Core0 EIINT495
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT495
#endif /* OSEE_RH850_CORE0_495_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_496_ISR_CAT))
  .word _osEE_rh850_core0_ei496       #-- Core0 EIINT496
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT496
#endif /* OSEE_RH850_CORE0_496_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_497_ISR_CAT))
  .word _osEE_rh850_core0_ei497       #-- Core0 EIINT497
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT497
#endif /* OSEE_RH850_CORE0_497_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_498_ISR_CAT))
  .word _osEE_rh850_core0_ei498       #-- Core0 EIINT498
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT498
#endif /* OSEE_RH850_CORE0_498_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_499_ISR_CAT))
  .word _osEE_rh850_core0_ei499       #-- Core0 EIINT499
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT499
#endif /* OSEE_RH850_CORE0_499_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_500_ISR_CAT))
  .word _osEE_rh850_core0_ei500       #-- Core0 EIINT500
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT500
#endif /* OSEE_RH850_CORE0_500_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_501_ISR_CAT))
  .word _osEE_rh850_core0_ei501       #-- Core0 EIINT501
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT501
#endif /* OSEE_RH850_CORE0_501_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_502_ISR_CAT))
  .word _osEE_rh850_core0_ei502       #-- Core0 EIINT502
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT502
#endif /* OSEE_RH850_CORE0_502_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_503_ISR_CAT))
  .word _osEE_rh850_core0_ei503       #-- Core0 EIINT503
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT503
#endif /* OSEE_RH850_CORE0_503_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_504_ISR_CAT))
  .word _osEE_rh850_core0_ei504       #-- Core0 EIINT504
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT504
#endif /* OSEE_RH850_CORE0_504_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_505_ISR_CAT))
  .word _osEE_rh850_core0_ei505       #-- Core0 EIINT505
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT505
#endif /* OSEE_RH850_CORE0_505_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_506_ISR_CAT))
  .word _osEE_rh850_core0_ei506       #-- Core0 EIINT506
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT506
#endif /* OSEE_RH850_CORE0_506_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_507_ISR_CAT))
  .word _osEE_rh850_core0_ei507       #-- Core0 EIINT507
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT507
#endif /* OSEE_RH850_CORE0_507_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_508_ISR_CAT))
  .word _osEE_rh850_core0_ei508       #-- Core0 EIINT508
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT508
#endif /* OSEE_RH850_CORE0_508_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_509_ISR_CAT))
  .word _osEE_rh850_core0_ei509       #-- Core0 EIINT509
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT509
#endif /* OSEE_RH850_CORE0_509_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_510_ISR_CAT))
  .word _osEE_rh850_core0_ei510       #-- Core0 EIINT510
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT510
#endif /* OSEE_RH850_CORE0_510_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_511_ISR_CAT))
  .word _osEE_rh850_core0_ei511       #-- Core0 EIINT511
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT511
#endif /* OSEE_RH850_CORE0_511_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_512_ISR_CAT))
  .word _osEE_rh850_core0_ei512       #-- Core0 EIINT512
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT512
#endif /* OSEE_RH850_CORE0_512_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_513_ISR_CAT))
  .word _osEE_rh850_core0_ei513       #-- Core0 EIINT513
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT513
#endif /* OSEE_RH850_CORE0_513_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_514_ISR_CAT))
  .word _osEE_rh850_core0_ei514       #-- Core0 EIINT514
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT514
#endif /* OSEE_RH850_CORE0_514_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_515_ISR_CAT))
  .word _osEE_rh850_core0_ei515       #-- Core0 EIINT515
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT515
#endif /* OSEE_RH850_CORE0_515_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_516_ISR_CAT))
  .word _osEE_rh850_core0_ei516       #-- Core0 EIINT516
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT516
#endif /* OSEE_RH850_CORE0_516_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_517_ISR_CAT))
  .word _osEE_rh850_core0_ei517       #-- Core0 EIINT517
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT517
#endif /* OSEE_RH850_CORE0_517_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_518_ISR_CAT))
  .word _osEE_rh850_core0_ei518       #-- Core0 EIINT518
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT518
#endif /* OSEE_RH850_CORE0_518_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_519_ISR_CAT))
  .word _osEE_rh850_core0_ei519       #-- Core0 EIINT519
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT519
#endif /* OSEE_RH850_CORE0_519_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_520_ISR_CAT))
  .word _osEE_rh850_core0_ei520       #-- Core0 EIINT520
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT520
#endif /* OSEE_RH850_CORE0_520_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_521_ISR_CAT))
  .word _osEE_rh850_core0_ei521       #-- Core0 EIINT521
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT521
#endif /* OSEE_RH850_CORE0_521_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_522_ISR_CAT))
  .word _osEE_rh850_core0_ei522       #-- Core0 EIINT522
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT522
#endif /* OSEE_RH850_CORE0_522_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_523_ISR_CAT))
  .word _osEE_rh850_core0_ei523       #-- Core0 EIINT523
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT523
#endif /* OSEE_RH850_CORE0_523_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_524_ISR_CAT))
  .word _osEE_rh850_core0_ei524       #-- Core0 EIINT524
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT524
#endif /* OSEE_RH850_CORE0_524_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_525_ISR_CAT))
  .word _osEE_rh850_core0_ei525       #-- Core0 EIINT525
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT525
#endif /* OSEE_RH850_CORE0_525_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_526_ISR_CAT))
  .word _osEE_rh850_core0_ei526       #-- Core0 EIINT526
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT526
#endif /* OSEE_RH850_CORE0_526_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_527_ISR_CAT))
  .word _osEE_rh850_core0_ei527       #-- Core0 EIINT527
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT527
#endif /* OSEE_RH850_CORE0_527_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_528_ISR_CAT))
  .word _osEE_rh850_core0_ei528       #-- Core0 EIINT528
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT528
#endif /* OSEE_RH850_CORE0_528_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_529_ISR_CAT))
  .word _osEE_rh850_core0_ei529       #-- Core0 EIINT529
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT529
#endif /* OSEE_RH850_CORE0_529_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_530_ISR_CAT))
  .word _osEE_rh850_core0_ei530       #-- Core0 EIINT530
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT530
#endif /* OSEE_RH850_CORE0_530_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_531_ISR_CAT))
  .word _osEE_rh850_core0_ei531       #-- Core0 EIINT531
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT531
#endif /* OSEE_RH850_CORE0_531_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_532_ISR_CAT))
  .word _osEE_rh850_core0_ei532       #-- Core0 EIINT532
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT532
#endif /* OSEE_RH850_CORE0_532_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_533_ISR_CAT))
  .word _osEE_rh850_core0_ei533       #-- Core0 EIINT533
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT533
#endif /* OSEE_RH850_CORE0_533_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_534_ISR_CAT))
  .word _osEE_rh850_core0_ei534       #-- Core0 EIINT534
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT534
#endif /* OSEE_RH850_CORE0_534_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_535_ISR_CAT))
  .word _osEE_rh850_core0_ei535       #-- Core0 EIINT535
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT535
#endif /* OSEE_RH850_CORE0_535_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_536_ISR_CAT))
  .word _osEE_rh850_core0_ei536       #-- Core0 EIINT536
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT536
#endif /* OSEE_RH850_CORE0_536_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_537_ISR_CAT))
  .word _osEE_rh850_core0_ei537       #-- Core0 EIINT537
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT537
#endif /* OSEE_RH850_CORE0_537_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_538_ISR_CAT))
  .word _osEE_rh850_core0_ei538       #-- Core0 EIINT538
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT538
#endif /* OSEE_RH850_CORE0_538_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_539_ISR_CAT))
  .word _osEE_rh850_core0_ei539       #-- Core0 EIINT539
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT539
#endif /* OSEE_RH850_CORE0_539_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_540_ISR_CAT))
  .word _osEE_rh850_core0_ei540       #-- Core0 EIINT540
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT540
#endif /* OSEE_RH850_CORE0_540_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_541_ISR_CAT))
  .word _osEE_rh850_core0_ei541       #-- Core0 EIINT541
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT541
#endif /* OSEE_RH850_CORE0_541_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_542_ISR_CAT))
  .word _osEE_rh850_core0_ei542       #-- Core0 EIINT542
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT542
#endif /* OSEE_RH850_CORE0_542_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_543_ISR_CAT))
  .word _osEE_rh850_core0_ei543       #-- Core0 EIINT543
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT543
#endif /* OSEE_RH850_CORE0_543_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_544_ISR_CAT))
  .word _osEE_rh850_core0_ei544       #-- Core0 EIINT544
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT544
#endif /* OSEE_RH850_CORE0_544_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_545_ISR_CAT))
  .word _osEE_rh850_core0_ei545       #-- Core0 EIINT545
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT545
#endif /* OSEE_RH850_CORE0_545_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_546_ISR_CAT))
  .word _osEE_rh850_core0_ei546       #-- Core0 EIINT546
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT546
#endif /* OSEE_RH850_CORE0_546_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_547_ISR_CAT))
  .word _osEE_rh850_core0_ei547       #-- Core0 EIINT547
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT547
#endif /* OSEE_RH850_CORE0_547_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_548_ISR_CAT))
  .word _osEE_rh850_core0_ei548       #-- Core0 EIINT548
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT548
#endif /* OSEE_RH850_CORE0_548_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_549_ISR_CAT))
  .word _osEE_rh850_core0_ei549       #-- Core0 EIINT549
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT549
#endif /* OSEE_RH850_CORE0_549_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_550_ISR_CAT))
  .word _osEE_rh850_core0_ei550       #-- Core0 EIINT550
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT550
#endif /* OSEE_RH850_CORE0_550_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_551_ISR_CAT))
  .word _osEE_rh850_core0_ei551       #-- Core0 EIINT551
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT551
#endif /* OSEE_RH850_CORE0_551_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_552_ISR_CAT))
  .word _osEE_rh850_core0_ei552       #-- Core0 EIINT552
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT552
#endif /* OSEE_RH850_CORE0_552_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_553_ISR_CAT))
  .word _osEE_rh850_core0_ei553       #-- Core0 EIINT553
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT553
#endif /* OSEE_RH850_CORE0_553_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_554_ISR_CAT))
  .word _osEE_rh850_core0_ei554       #-- Core0 EIINT554
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT554
#endif /* OSEE_RH850_CORE0_554_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_555_ISR_CAT))
  .word _osEE_rh850_core0_ei555       #-- Core0 EIINT555
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT555
#endif /* OSEE_RH850_CORE0_555_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_556_ISR_CAT))
  .word _osEE_rh850_core0_ei556       #-- Core0 EIINT556
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT556
#endif /* OSEE_RH850_CORE0_556_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_557_ISR_CAT))
  .word _osEE_rh850_core0_ei557       #-- Core0 EIINT557
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT557
#endif /* OSEE_RH850_CORE0_557_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_558_ISR_CAT))
  .word _osEE_rh850_core0_ei558       #-- Core0 EIINT558
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT558
#endif /* OSEE_RH850_CORE0_558_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_559_ISR_CAT))
  .word _osEE_rh850_core0_ei559       #-- Core0 EIINT559
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT559
#endif /* OSEE_RH850_CORE0_559_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_560_ISR_CAT))
  .word _osEE_rh850_core0_ei560       #-- Core0 EIINT560
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT560
#endif /* OSEE_RH850_CORE0_560_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_561_ISR_CAT))
  .word _osEE_rh850_core0_ei561       #-- Core0 EIINT561
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT561
#endif /* OSEE_RH850_CORE0_561_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_562_ISR_CAT))
  .word _osEE_rh850_core0_ei562       #-- Core0 EIINT562
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT562
#endif /* OSEE_RH850_CORE0_562_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_563_ISR_CAT))
  .word _osEE_rh850_core0_ei563       #-- Core0 EIINT563
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT563
#endif /* OSEE_RH850_CORE0_563_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_564_ISR_CAT))
  .word _osEE_rh850_core0_ei564       #-- Core0 EIINT564
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT564
#endif /* OSEE_RH850_CORE0_564_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_565_ISR_CAT))
  .word _osEE_rh850_core0_ei565       #-- Core0 EIINT565
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT565
#endif /* OSEE_RH850_CORE0_565_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_566_ISR_CAT))
  .word _osEE_rh850_core0_ei566       #-- Core0 EIINT566
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT566
#endif /* OSEE_RH850_CORE0_566_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_567_ISR_CAT))
  .word _osEE_rh850_core0_ei567       #-- Core0 EIINT567
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT567
#endif /* OSEE_RH850_CORE0_567_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_568_ISR_CAT))
  .word _osEE_rh850_core0_ei568       #-- Core0 EIINT568
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT568
#endif /* OSEE_RH850_CORE0_568_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_569_ISR_CAT))
  .word _osEE_rh850_core0_ei569       #-- Core0 EIINT569
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT569
#endif /* OSEE_RH850_CORE0_569_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_570_ISR_CAT))
  .word _osEE_rh850_core0_ei570       #-- Core0 EIINT570
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT570
#endif /* OSEE_RH850_CORE0_570_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_571_ISR_CAT))
  .word _osEE_rh850_core0_ei571       #-- Core0 EIINT571
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT571
#endif /* OSEE_RH850_CORE0_571_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_572_ISR_CAT))
  .word _osEE_rh850_core0_ei572       #-- Core0 EIINT572
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT572
#endif /* OSEE_RH850_CORE0_572_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_573_ISR_CAT))
  .word _osEE_rh850_core0_ei573       #-- Core0 EIINT573
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT573
#endif /* OSEE_RH850_CORE0_573_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_574_ISR_CAT))
  .word _osEE_rh850_core0_ei574       #-- Core0 EIINT574
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT574
#endif /* OSEE_RH850_CORE0_574_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_575_ISR_CAT))
  .word _osEE_rh850_core0_ei575       #-- Core0 EIINT575
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT575
#endif /* OSEE_RH850_CORE0_575_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_576_ISR_CAT))
  .word _osEE_rh850_core0_ei576       #-- Core0 EIINT576
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT576
#endif /* OSEE_RH850_CORE0_576_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_577_ISR_CAT))
  .word _osEE_rh850_core0_ei577       #-- Core0 EIINT577
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT577
#endif /* OSEE_RH850_CORE0_577_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_578_ISR_CAT))
  .word _osEE_rh850_core0_ei578       #-- Core0 EIINT578
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT578
#endif /* OSEE_RH850_CORE0_578_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_579_ISR_CAT))
  .word _osEE_rh850_core0_ei579       #-- Core0 EIINT579
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT579
#endif /* OSEE_RH850_CORE0_579_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_580_ISR_CAT))
  .word _osEE_rh850_core0_ei580       #-- Core0 EIINT580
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT580
#endif /* OSEE_RH850_CORE0_580_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_581_ISR_CAT))
  .word _osEE_rh850_core0_ei581       #-- Core0 EIINT581
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT581
#endif /* OSEE_RH850_CORE0_581_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_582_ISR_CAT))
  .word _osEE_rh850_core0_ei582       #-- Core0 EIINT582
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT582
#endif /* OSEE_RH850_CORE0_582_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_583_ISR_CAT))
  .word _osEE_rh850_core0_ei583       #-- Core0 EIINT583
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT583
#endif /* OSEE_RH850_CORE0_583_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_584_ISR_CAT))
  .word _osEE_rh850_core0_ei584       #-- Core0 EIINT584
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT584
#endif /* OSEE_RH850_CORE0_584_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_585_ISR_CAT))
  .word _osEE_rh850_core0_ei585       #-- Core0 EIINT585
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT585
#endif /* OSEE_RH850_CORE0_585_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_586_ISR_CAT))
  .word _osEE_rh850_core0_ei586       #-- Core0 EIINT586
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT586
#endif /* OSEE_RH850_CORE0_586_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_587_ISR_CAT))
  .word _osEE_rh850_core0_ei587       #-- Core0 EIINT587
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT587
#endif /* OSEE_RH850_CORE0_587_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_588_ISR_CAT))
  .word _osEE_rh850_core0_ei588       #-- Core0 EIINT588
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT588
#endif /* OSEE_RH850_CORE0_588_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_589_ISR_CAT))
  .word _osEE_rh850_core0_ei589       #-- Core0 EIINT589
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT589
#endif /* OSEE_RH850_CORE0_589_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_590_ISR_CAT))
  .word _osEE_rh850_core0_ei590       #-- Core0 EIINT590
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT590
#endif /* OSEE_RH850_CORE0_590_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_591_ISR_CAT))
  .word _osEE_rh850_core0_ei591       #-- Core0 EIINT591
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT591
#endif /* OSEE_RH850_CORE0_591_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_592_ISR_CAT))
  .word _osEE_rh850_core0_ei592       #-- Core0 EIINT592
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT592
#endif /* OSEE_RH850_CORE0_592_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_593_ISR_CAT))
  .word _osEE_rh850_core0_ei593       #-- Core0 EIINT593
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT593
#endif /* OSEE_RH850_CORE0_593_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_594_ISR_CAT))
  .word _osEE_rh850_core0_ei594       #-- Core0 EIINT594
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT594
#endif /* OSEE_RH850_CORE0_594_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_595_ISR_CAT))
  .word _osEE_rh850_core0_ei595       #-- Core0 EIINT595
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT595
#endif /* OSEE_RH850_CORE0_595_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_596_ISR_CAT))
  .word _osEE_rh850_core0_ei596       #-- Core0 EIINT596
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT596
#endif /* OSEE_RH850_CORE0_596_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_597_ISR_CAT))
  .word _osEE_rh850_core0_ei597       #-- Core0 EIINT597
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT597
#endif /* OSEE_RH850_CORE0_597_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_598_ISR_CAT))
  .word _osEE_rh850_core0_ei598       #-- Core0 EIINT598
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT598
#endif /* OSEE_RH850_CORE0_598_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_599_ISR_CAT))
  .word _osEE_rh850_core0_ei599       #-- Core0 EIINT599
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT599
#endif /* OSEE_RH850_CORE0_599_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_600_ISR_CAT))
  .word _osEE_rh850_core0_ei600       #-- Core0 EIINT600
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT600
#endif /* OSEE_RH850_CORE0_600_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_601_ISR_CAT))
  .word _osEE_rh850_core0_ei601       #-- Core0 EIINT601
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT601
#endif /* OSEE_RH850_CORE0_601_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_602_ISR_CAT))
  .word _osEE_rh850_core0_ei602       #-- Core0 EIINT602
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT602
#endif /* OSEE_RH850_CORE0_602_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_603_ISR_CAT))
  .word _osEE_rh850_core0_ei603       #-- Core0 EIINT603
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT603
#endif /* OSEE_RH850_CORE0_603_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_604_ISR_CAT))
  .word _osEE_rh850_core0_ei604       #-- Core0 EIINT604
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT604
#endif /* OSEE_RH850_CORE0_604_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_605_ISR_CAT))
  .word _osEE_rh850_core0_ei605       #-- Core0 EIINT605
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT605
#endif /* OSEE_RH850_CORE0_605_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_606_ISR_CAT))
  .word _osEE_rh850_core0_ei606       #-- Core0 EIINT606
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT606
#endif /* OSEE_RH850_CORE0_606_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_607_ISR_CAT))
  .word _osEE_rh850_core0_ei607       #-- Core0 EIINT607
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT607
#endif /* OSEE_RH850_CORE0_607_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_608_ISR_CAT))
  .word _osEE_rh850_core0_ei608       #-- Core0 EIINT608
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT608
#endif /* OSEE_RH850_CORE0_608_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_609_ISR_CAT))
  .word _osEE_rh850_core0_ei609       #-- Core0 EIINT609
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT609
#endif /* OSEE_RH850_CORE0_609_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_610_ISR_CAT))
  .word _osEE_rh850_core0_ei610       #-- Core0 EIINT610
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT610
#endif /* OSEE_RH850_CORE0_610_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_611_ISR_CAT))
  .word _osEE_rh850_core0_ei611       #-- Core0 EIINT611
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT611
#endif /* OSEE_RH850_CORE0_611_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_612_ISR_CAT))
  .word _osEE_rh850_core0_ei612       #-- Core0 EIINT612
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT612
#endif /* OSEE_RH850_CORE0_612_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_613_ISR_CAT))
  .word _osEE_rh850_core0_ei613       #-- Core0 EIINT613
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT613
#endif /* OSEE_RH850_CORE0_613_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_614_ISR_CAT))
  .word _osEE_rh850_core0_ei614       #-- Core0 EIINT614
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT614
#endif /* OSEE_RH850_CORE0_614_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_615_ISR_CAT))
  .word _osEE_rh850_core0_ei615       #-- Core0 EIINT615
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT615
#endif /* OSEE_RH850_CORE0_615_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_616_ISR_CAT))
  .word _osEE_rh850_core0_ei616       #-- Core0 EIINT616
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT616
#endif /* OSEE_RH850_CORE0_616_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_617_ISR_CAT))
  .word _osEE_rh850_core0_ei617       #-- Core0 EIINT617
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT617
#endif /* OSEE_RH850_CORE0_617_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_618_ISR_CAT))
  .word _osEE_rh850_core0_ei618       #-- Core0 EIINT618
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT618
#endif /* OSEE_RH850_CORE0_618_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_619_ISR_CAT))
  .word _osEE_rh850_core0_ei619       #-- Core0 EIINT619
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT619
#endif /* OSEE_RH850_CORE0_619_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_620_ISR_CAT))
  .word _osEE_rh850_core0_ei620       #-- Core0 EIINT620
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT620
#endif /* OSEE_RH850_CORE0_620_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_621_ISR_CAT))
  .word _osEE_rh850_core0_ei621       #-- Core0 EIINT621
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT621
#endif /* OSEE_RH850_CORE0_621_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_622_ISR_CAT))
  .word _osEE_rh850_core0_ei622       #-- Core0 EIINT622
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT622
#endif /* OSEE_RH850_CORE0_622_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_623_ISR_CAT))
  .word _osEE_rh850_core0_ei623       #-- Core0 EIINT623
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT623
#endif /* OSEE_RH850_CORE0_623_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_624_ISR_CAT))
  .word _osEE_rh850_core0_ei624       #-- Core0 EIINT624
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT624
#endif /* OSEE_RH850_CORE0_624_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_625_ISR_CAT))
  .word _osEE_rh850_core0_ei625       #-- Core0 EIINT625
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT625
#endif /* OSEE_RH850_CORE0_625_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_626_ISR_CAT))
  .word _osEE_rh850_core0_ei626       #-- Core0 EIINT626
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT626
#endif /* OSEE_RH850_CORE0_626_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_627_ISR_CAT))
  .word _osEE_rh850_core0_ei627       #-- Core0 EIINT627
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT627
#endif /* OSEE_RH850_CORE0_627_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_628_ISR_CAT))
  .word _osEE_rh850_core0_ei628       #-- Core0 EIINT628
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT628
#endif /* OSEE_RH850_CORE0_628_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_629_ISR_CAT))
  .word _osEE_rh850_core0_ei629       #-- Core0 EIINT629
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT629
#endif /* OSEE_RH850_CORE0_629_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_630_ISR_CAT))
  .word _osEE_rh850_core0_ei630       #-- Core0 EIINT630
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT630
#endif /* OSEE_RH850_CORE0_630_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_631_ISR_CAT))
  .word _osEE_rh850_core0_ei631       #-- Core0 EIINT631
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT631
#endif /* OSEE_RH850_CORE0_631_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_632_ISR_CAT))
  .word _osEE_rh850_core0_ei632       #-- Core0 EIINT632
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT632
#endif /* OSEE_RH850_CORE0_632_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_633_ISR_CAT))
  .word _osEE_rh850_core0_ei633       #-- Core0 EIINT633
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT633
#endif /* OSEE_RH850_CORE0_633_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_634_ISR_CAT))
  .word _osEE_rh850_core0_ei634       #-- Core0 EIINT634
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT634
#endif /* OSEE_RH850_CORE0_634_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_635_ISR_CAT))
  .word _osEE_rh850_core0_ei635       #-- Core0 EIINT635
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT635
#endif /* OSEE_RH850_CORE0_635_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_636_ISR_CAT))
  .word _osEE_rh850_core0_ei636       #-- Core0 EIINT636
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT636
#endif /* OSEE_RH850_CORE0_636_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_637_ISR_CAT))
  .word _osEE_rh850_core0_ei637       #-- Core0 EIINT637
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT637
#endif /* OSEE_RH850_CORE0_637_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_638_ISR_CAT))
  .word _osEE_rh850_core0_ei638       #-- Core0 EIINT638
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT638
#endif /* OSEE_RH850_CORE0_638_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_639_ISR_CAT))
  .word _osEE_rh850_core0_ei639       #-- Core0 EIINT639
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT639
#endif /* OSEE_RH850_CORE0_639_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_640_ISR_CAT))
  .word _osEE_rh850_core0_ei640       #-- Core0 EIINT640
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT640
#endif /* OSEE_RH850_CORE0_640_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_641_ISR_CAT))
  .word _osEE_rh850_core0_ei641       #-- Core0 EIINT641
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT641
#endif /* OSEE_RH850_CORE0_641_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_642_ISR_CAT))
  .word _osEE_rh850_core0_ei642       #-- Core0 EIINT642
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT642
#endif /* OSEE_RH850_CORE0_642_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_643_ISR_CAT))
  .word _osEE_rh850_core0_ei643       #-- Core0 EIINT643
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT643
#endif /* OSEE_RH850_CORE0_643_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_644_ISR_CAT))
  .word _osEE_rh850_core0_ei644       #-- Core0 EIINT644
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT644
#endif /* OSEE_RH850_CORE0_644_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_645_ISR_CAT))
  .word _osEE_rh850_core0_ei645       #-- Core0 EIINT645
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT645
#endif /* OSEE_RH850_CORE0_645_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_646_ISR_CAT))
  .word _osEE_rh850_core0_ei646       #-- Core0 EIINT646
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT646
#endif /* OSEE_RH850_CORE0_646_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_647_ISR_CAT))
  .word _osEE_rh850_core0_ei647       #-- Core0 EIINT647
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT647
#endif /* OSEE_RH850_CORE0_647_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_648_ISR_CAT))
  .word _osEE_rh850_core0_ei648       #-- Core0 EIINT648
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT648
#endif /* OSEE_RH850_CORE0_648_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_649_ISR_CAT))
  .word _osEE_rh850_core0_ei649       #-- Core0 EIINT649
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT649
#endif /* OSEE_RH850_CORE0_649_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_650_ISR_CAT))
  .word _osEE_rh850_core0_ei650       #-- Core0 EIINT650
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT650
#endif /* OSEE_RH850_CORE0_650_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_651_ISR_CAT))
  .word _osEE_rh850_core0_ei651       #-- Core0 EIINT651
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT651
#endif /* OSEE_RH850_CORE0_651_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_652_ISR_CAT))
  .word _osEE_rh850_core0_ei652       #-- Core0 EIINT652
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT652
#endif /* OSEE_RH850_CORE0_652_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_653_ISR_CAT))
  .word _osEE_rh850_core0_ei653       #-- Core0 EIINT653
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT653
#endif /* OSEE_RH850_CORE0_653_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_654_ISR_CAT))
  .word _osEE_rh850_core0_ei654       #-- Core0 EIINT654
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT654
#endif /* OSEE_RH850_CORE0_654_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_655_ISR_CAT))
  .word _osEE_rh850_core0_ei655       #-- Core0 EIINT655
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT655
#endif /* OSEE_RH850_CORE0_655_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_656_ISR_CAT))
  .word _osEE_rh850_core0_ei656       #-- Core0 EIINT656
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT656
#endif /* OSEE_RH850_CORE0_656_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_657_ISR_CAT))
  .word _osEE_rh850_core0_ei657       #-- Core0 EIINT657
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT657
#endif /* OSEE_RH850_CORE0_657_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_658_ISR_CAT))
  .word _osEE_rh850_core0_ei658       #-- Core0 EIINT658
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT658
#endif /* OSEE_RH850_CORE0_658_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_659_ISR_CAT))
  .word _osEE_rh850_core0_ei659       #-- Core0 EIINT659
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT659
#endif /* OSEE_RH850_CORE0_659_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_660_ISR_CAT))
  .word _osEE_rh850_core0_ei660       #-- Core0 EIINT660
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT660
#endif /* OSEE_RH850_CORE0_660_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_661_ISR_CAT))
  .word _osEE_rh850_core0_ei661       #-- Core0 EIINT661
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT661
#endif /* OSEE_RH850_CORE0_661_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_662_ISR_CAT))
  .word _osEE_rh850_core0_ei662       #-- Core0 EIINT662
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT662
#endif /* OSEE_RH850_CORE0_662_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_663_ISR_CAT))
  .word _osEE_rh850_core0_ei663       #-- Core0 EIINT663
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT663
#endif /* OSEE_RH850_CORE0_663_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_664_ISR_CAT))
  .word _osEE_rh850_core0_ei664       #-- Core0 EIINT664
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT664
#endif /* OSEE_RH850_CORE0_664_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_665_ISR_CAT))
  .word _osEE_rh850_core0_ei665       #-- Core0 EIINT665
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT665
#endif /* OSEE_RH850_CORE0_665_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_666_ISR_CAT))
  .word _osEE_rh850_core0_ei666       #-- Core0 EIINT666
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT666
#endif /* OSEE_RH850_CORE0_666_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_667_ISR_CAT))
  .word _osEE_rh850_core0_ei667       #-- Core0 EIINT667
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT667
#endif /* OSEE_RH850_CORE0_667_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_668_ISR_CAT))
  .word _osEE_rh850_core0_ei668       #-- Core0 EIINT668
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT668
#endif /* OSEE_RH850_CORE0_668_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_669_ISR_CAT))
  .word _osEE_rh850_core0_ei669       #-- Core0 EIINT669
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT669
#endif /* OSEE_RH850_CORE0_669_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_670_ISR_CAT))
  .word _osEE_rh850_core0_ei670       #-- Core0 EIINT670
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT670
#endif /* OSEE_RH850_CORE0_670_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_671_ISR_CAT))
  .word _osEE_rh850_core0_ei671       #-- Core0 EIINT671
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT671
#endif /* OSEE_RH850_CORE0_671_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_672_ISR_CAT))
  .word _osEE_rh850_core0_ei672       #-- Core0 EIINT672
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT672
#endif /* OSEE_RH850_CORE0_672_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_673_ISR_CAT))
  .word _osEE_rh850_core0_ei673       #-- Core0 EIINT673
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT673
#endif /* OSEE_RH850_CORE0_673_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_674_ISR_CAT))
  .word _osEE_rh850_core0_ei674       #-- Core0 EIINT674
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT674
#endif /* OSEE_RH850_CORE0_674_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_675_ISR_CAT))
  .word _osEE_rh850_core0_ei675       #-- Core0 EIINT675
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT675
#endif /* OSEE_RH850_CORE0_675_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_676_ISR_CAT))
  .word _osEE_rh850_core0_ei676       #-- Core0 EIINT676
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT676
#endif /* OSEE_RH850_CORE0_676_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_677_ISR_CAT))
  .word _osEE_rh850_core0_ei677       #-- Core0 EIINT677
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT677
#endif /* OSEE_RH850_CORE0_677_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_678_ISR_CAT))
  .word _osEE_rh850_core0_ei678       #-- Core0 EIINT678
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT678
#endif /* OSEE_RH850_CORE0_678_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_679_ISR_CAT))
  .word _osEE_rh850_core0_ei679       #-- Core0 EIINT679
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT679
#endif /* OSEE_RH850_CORE0_679_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_680_ISR_CAT))
  .word _osEE_rh850_core0_ei680       #-- Core0 EIINT680
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT680
#endif /* OSEE_RH850_CORE0_680_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_681_ISR_CAT))
  .word _osEE_rh850_core0_ei681       #-- Core0 EIINT681
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT681
#endif /* OSEE_RH850_CORE0_681_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_682_ISR_CAT))
  .word _osEE_rh850_core0_ei682       #-- Core0 EIINT682
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT682
#endif /* OSEE_RH850_CORE0_682_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_683_ISR_CAT))
  .word _osEE_rh850_core0_ei683       #-- Core0 EIINT683
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT683
#endif /* OSEE_RH850_CORE0_683_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_684_ISR_CAT))
  .word _osEE_rh850_core0_ei684       #-- Core0 EIINT684
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT684
#endif /* OSEE_RH850_CORE0_684_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_685_ISR_CAT))
  .word _osEE_rh850_core0_ei685       #-- Core0 EIINT685
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT685
#endif /* OSEE_RH850_CORE0_685_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_686_ISR_CAT))
  .word _osEE_rh850_core0_ei686       #-- Core0 EIINT686
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT686
#endif /* OSEE_RH850_CORE0_686_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_687_ISR_CAT))
  .word _osEE_rh850_core0_ei687       #-- Core0 EIINT687
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT687
#endif /* OSEE_RH850_CORE0_687_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_688_ISR_CAT))
  .word _osEE_rh850_core0_ei688       #-- Core0 EIINT688
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT688
#endif /* OSEE_RH850_CORE0_688_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_689_ISR_CAT))
  .word _osEE_rh850_core0_ei689       #-- Core0 EIINT689
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT689
#endif /* OSEE_RH850_CORE0_689_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_690_ISR_CAT))
  .word _osEE_rh850_core0_ei690       #-- Core0 EIINT690
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT690
#endif /* OSEE_RH850_CORE0_690_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_691_ISR_CAT))
  .word _osEE_rh850_core0_ei691       #-- Core0 EIINT691
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT691
#endif /* OSEE_RH850_CORE0_691_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_692_ISR_CAT))
  .word _osEE_rh850_core0_ei692       #-- Core0 EIINT692
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT692
#endif /* OSEE_RH850_CORE0_692_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_693_ISR_CAT))
  .word _osEE_rh850_core0_ei693       #-- Core0 EIINT693
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT693
#endif /* OSEE_RH850_CORE0_693_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_694_ISR_CAT))
  .word _osEE_rh850_core0_ei694       #-- Core0 EIINT694
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT694
#endif /* OSEE_RH850_CORE0_694_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_695_ISR_CAT))
  .word _osEE_rh850_core0_ei695       #-- Core0 EIINT695
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core0 EIINT695
#endif /* OSEE_RH850_CORE0_695_ISR_CAT */
#.size _g_g4mh_RefTbl, .-_g_g4mh_RefTbl
.size OSEE_RH850_REF_TABLE, .-OSEE_RH850_REF_TABLE

  #----------------------------------------------------------------------------
  #-- Description : Unused EI ISR Wrapper
  #----------------------------------------------------------------------------

  .section ".text"

  .global   _osEE_rh850_call_IsrEiUnused
#if (defined(OSEE_LIB_EMBARK_G4MH))
  .import   _R_G4MH_IsrEiUnused
_osEE_rh850_call_IsrEiUnused:
  #-- Save ISR Context
  pushsp  r1-r19
  osEE_rh850_save_isr_ctx_m

  #-- Call _R_G4MH_IsrEiUnused
  jarl  _R_G4MH_IsrEiUnused, r31
  
  #-- Disable interrupts (Just in case)
  di

  #-- Restore ISR Context
  osEE_rh850_restore_isr_ctx_m

  #-- synchronize pipeline
  #--
  #-- IMPORTANT: required for 
  #--  - External Interrupt Processing Flow
  #--  - Software Interrupt Processing Flow
  #--  - Peripheral Interrupt Processing Flow
  #--
  #-- redundant for other types of EI interrupts
  syncp

  #-- return from EI exception
  eiret

  .size _osEE_rh850_call_IsrEiUnused, .-_osEE_rh850_call_IsrEiUnused
#else
  .import   osEE_rh850_isr_ei_unused

_osEE_rh850_call_IsrEiUnused:
  #-- Save ISR Context
  pushsp  r1-r19
  osEE_rh850_save_isr_ctx_m

  #-- Call osEE_rh850_isr_ei_unused (Passing EIIC, already saved in r10)
  mov   r10, r6
  jarl  osEE_rh850_isr_ei_unused, r31

  #-- Disable interrupts (Just in case)
  di

  #-- Restore ISR Context
  osEE_rh850_restore_isr_ctx_m

  #-- synchronize pipeline
  #--
  #-- IMPORTANT: required for 
  #--  - External Interrupt Processing Flow
  #--  - Software Interrupt Processing Flow
  #--  - Peripheral Interrupt Processing Flow
  #--
  #-- redundant for other types of EI interrupts
  syncp

  #-- return from EI exception
  eiret
  .size _osEE_rh850_call_IsrEiUnused, .-_osEE_rh850_call_IsrEiUnused
#endif

  #----------------------------------------------------------------------------
  #-- Description : ISR1 Wrapper
  #----------------------------------------------------------------------------
  .global   _osEE_rh850_call_isr1
_osEE_rh850_call_isr1:
  #-- Save ISR Context
  osEE_rh850_save_isr_ctx_m

  #-- Enable Interrupts for ISR1
  ei

  #-- Call ISR1 Function
  jarl  [r6], r31

  #-- Disable Interrupts
  di

  #-- Restore ISR Context
  osEE_rh850_restore_isr_ctx_m

  #-- synchronize pipeline
  syncp

  #-- return from EI exception
  eiret
  .size _osEE_rh850_call_isr1, .-_osEE_rh850_call_isr1

  #----------------------------------------------------------------------------
  #-- Description : ISR2 Wrapper
  #----------------------------------------------------------------------------
  .import   _osEE_rh850_isr2_wrapper

  .global   _osEE_rh850_call_isr2
_osEE_rh850_call_isr2:
  #-- Save ISR Context
  osEE_rh850_save_isr_ctx_m

  #-- Call _osEE_rh850_isr2_wrapper (after storing sp as second call parameter) 
  mov   sp, r7
  jarl  _osEE_rh850_isr2_wrapper, r31

  #-- Restore ISR Context
  osEE_rh850_restore_isr_ctx_m

  #-- synchronize pipeline
  syncp

  #-- return from EI exception
  eiret
  .size _osEE_rh850_call_isr2, .-_osEE_rh850_call_isr2

  #----------------------------------------------------------------------------
  #-- Description : ISR Refence Table Entries (The select the right wrapper)
  #----------------------------------------------------------------------------
#if (!defined(OSEE_SINGLECORE))
  .import _osEE_rh850_handle_ipir
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_RH850_CORE0_0_ISR_CAT)) || (!defined(OSEE_SINGLECORE))
#if (defined(OSEE_RH850_CORE0_0_ISR_CAT)) && (OSEE_RH850_CORE0_0_ISR_CAT == 1)
_osEE_rh850_core0_ei0:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_0_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei0, .-_osEE_rh850_core0_ei0
#elif (defined(OSEE_RH850_CORE0_0_ISR_CAT)) && (OSEE_RH850_CORE0_0_ISR_CAT == 2)
_osEE_rh850_core0_ei0:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_0_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei0, .-_osEE_rh850_core0_ei0
#else
_osEE_rh850_core0_ei0:
  #-- Save ISR Context
  pushsp  r1-r19
  osEE_rh850_save_isr_ctx_m

  #-- Call _R_G4MH_IsrEiUnused
  jarl  _osEE_rh850_handle_ipir, r31

  #-- Restore ISR Context
  osEE_rh850_restore_isr_ctx_m

  #-- Synchronize pipeline needed for Software Interrupt Processing Flow
  syncp

  #-- return from EI exception
  eiret

  .size  _osEE_rh850_core0_ei0, .-_osEE_rh850_core0_ei0
#endif
#endif /* OSEE_RH850_CORE0_0_ISR_CAT || !OSEE_SINGLECORE */
#if (defined(OSEE_RH850_CORE0_1_ISR_CAT))
#if (OSEE_RH850_CORE0_1_ISR_CAT == 1)
_osEE_rh850_core0_ei1:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_1_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei1, .-_osEE_rh850_core0_ei1
#else
_osEE_rh850_core0_ei1:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_1_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei1, .-_osEE_rh850_core0_ei1
#endif
#endif /* OSEE_RH850_CORE0_1_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_2_ISR_CAT))
#if (OSEE_RH850_CORE0_2_ISR_CAT == 1)
_osEE_rh850_core0_ei2:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_2_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei2, .-_osEE_rh850_core0_ei2
#else
_osEE_rh850_core0_ei2:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_2_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei2, .-_osEE_rh850_core0_ei2
#endif
#endif /* OSEE_RH850_CORE0_2_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_3_ISR_CAT))
#if (OSEE_RH850_CORE0_3_ISR_CAT == 1)
_osEE_rh850_core0_ei3:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_3_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei3, .-_osEE_rh850_core0_ei3
#else
_osEE_rh850_core0_ei3:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_3_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei3, .-_osEE_rh850_core0_ei3
#endif
#endif /* OSEE_RH850_CORE0_3_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_4_ISR_CAT))
#if (OSEE_RH850_CORE0_4_ISR_CAT == 1)
_osEE_rh850_core0_ei4:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_4_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei4, .-_osEE_rh850_core0_ei4
#else
_osEE_rh850_core0_ei4:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_4_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei4, .-_osEE_rh850_core0_ei4
#endif
#endif /* OSEE_RH850_CORE0_4_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_5_ISR_CAT))
#if (OSEE_RH850_CORE0_5_ISR_CAT == 1)
_osEE_rh850_core0_ei5:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_5_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei5, .-_osEE_rh850_core0_ei5
#else
_osEE_rh850_core0_ei5:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_5_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei5, .-_osEE_rh850_core0_ei5
#endif
#endif /* OSEE_RH850_CORE0_5_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_6_ISR_CAT))
#if (OSEE_RH850_CORE0_6_ISR_CAT == 1)
_osEE_rh850_core0_ei6:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_6_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei6, .-_osEE_rh850_core0_ei6
#else
_osEE_rh850_core0_ei6:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_6_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei6, .-_osEE_rh850_core0_ei6
#endif
#endif /* OSEE_RH850_CORE0_6_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_7_ISR_CAT))
#if (OSEE_RH850_CORE0_7_ISR_CAT == 1)
_osEE_rh850_core0_ei7:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_7_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei7, .-_osEE_rh850_core0_ei7
#else
_osEE_rh850_core0_ei7:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_7_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei7, .-_osEE_rh850_core0_ei7
#endif
#endif /* OSEE_RH850_CORE0_7_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_8_ISR_CAT))
#if (OSEE_RH850_CORE0_8_ISR_CAT == 1)
_osEE_rh850_core0_ei8:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_8_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei8, .-_osEE_rh850_core0_ei8
#else
_osEE_rh850_core0_ei8:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_8_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei8, .-_osEE_rh850_core0_ei8
#endif
#endif /* OSEE_RH850_CORE0_8_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_9_ISR_CAT))
#if (OSEE_RH850_CORE0_9_ISR_CAT == 1)
_osEE_rh850_core0_ei9:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_9_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei9, .-_osEE_rh850_core0_ei9
#else
_osEE_rh850_core0_ei9:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_9_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei9, .-_osEE_rh850_core0_ei9
#endif
#endif /* OSEE_RH850_CORE0_9_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_10_ISR_CAT))
#if (OSEE_RH850_CORE0_10_ISR_CAT == 1)
_osEE_rh850_core0_ei10:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_10_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei10, .-_osEE_rh850_core0_ei10
#else
_osEE_rh850_core0_ei10:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_10_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei10, .-_osEE_rh850_core0_ei10
#endif
#endif /* OSEE_RH850_CORE0_10_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_11_ISR_CAT))
#if (OSEE_RH850_CORE0_11_ISR_CAT == 1)
_osEE_rh850_core0_ei11:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_11_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei11, .-_osEE_rh850_core0_ei11
#else
_osEE_rh850_core0_ei11:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_11_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei11, .-_osEE_rh850_core0_ei11
#endif
#endif /* OSEE_RH850_CORE0_11_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_12_ISR_CAT))
#if (OSEE_RH850_CORE0_12_ISR_CAT == 1)
_osEE_rh850_core0_ei12:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_12_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei12, .-_osEE_rh850_core0_ei12
#else
_osEE_rh850_core0_ei12:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_12_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei12, .-_osEE_rh850_core0_ei12
#endif
#endif /* OSEE_RH850_CORE0_12_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_13_ISR_CAT))
#if (OSEE_RH850_CORE0_13_ISR_CAT == 1)
_osEE_rh850_core0_ei13:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_13_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei13, .-_osEE_rh850_core0_ei13
#else
_osEE_rh850_core0_ei13:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_13_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei13, .-_osEE_rh850_core0_ei13
#endif
#endif /* OSEE_RH850_CORE0_13_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_14_ISR_CAT))
#if (OSEE_RH850_CORE0_14_ISR_CAT == 1)
_osEE_rh850_core0_ei14:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_14_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei14, .-_osEE_rh850_core0_ei14
#else
_osEE_rh850_core0_ei14:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_14_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei14, .-_osEE_rh850_core0_ei14
#endif
#endif /* OSEE_RH850_CORE0_14_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_15_ISR_CAT))
#if (OSEE_RH850_CORE0_15_ISR_CAT == 1)
_osEE_rh850_core0_ei15:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_15_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei15, .-_osEE_rh850_core0_ei15
#else
_osEE_rh850_core0_ei15:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_15_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei15, .-_osEE_rh850_core0_ei15
#endif
#endif /* OSEE_RH850_CORE0_15_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_16_ISR_CAT))
#if (OSEE_RH850_CORE0_16_ISR_CAT == 1)
_osEE_rh850_core0_ei16:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_16_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei16, .-_osEE_rh850_core0_ei16
#else
_osEE_rh850_core0_ei16:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_16_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei16, .-_osEE_rh850_core0_ei16
#endif
#endif /* OSEE_RH850_CORE0_16_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_17_ISR_CAT))
#if (OSEE_RH850_CORE0_17_ISR_CAT == 1)
_osEE_rh850_core0_ei17:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_17_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei17, .-_osEE_rh850_core0_ei17
#else
_osEE_rh850_core0_ei17:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_17_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei17, .-_osEE_rh850_core0_ei17
#endif
#endif /* OSEE_RH850_CORE0_17_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_18_ISR_CAT))
#if (OSEE_RH850_CORE0_18_ISR_CAT == 1)
_osEE_rh850_core0_ei18:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_18_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei18, .-_osEE_rh850_core0_ei18
#else
_osEE_rh850_core0_ei18:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_18_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei18, .-_osEE_rh850_core0_ei18
#endif
#endif /* OSEE_RH850_CORE0_18_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_19_ISR_CAT))
#if (OSEE_RH850_CORE0_19_ISR_CAT == 1)
_osEE_rh850_core0_ei19:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_19_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei19, .-_osEE_rh850_core0_ei19
#else
_osEE_rh850_core0_ei19:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_19_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei19, .-_osEE_rh850_core0_ei19
#endif
#endif /* OSEE_RH850_CORE0_19_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_20_ISR_CAT))
#if (OSEE_RH850_CORE0_20_ISR_CAT == 1)
_osEE_rh850_core0_ei20:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_20_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei20, .-_osEE_rh850_core0_ei20
#else
_osEE_rh850_core0_ei20:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_20_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei20, .-_osEE_rh850_core0_ei20
#endif
#endif /* OSEE_RH850_CORE0_20_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_21_ISR_CAT))
#if (OSEE_RH850_CORE0_21_ISR_CAT == 1)
_osEE_rh850_core0_ei21:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_21_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei21, .-_osEE_rh850_core0_ei21
#else
_osEE_rh850_core0_ei21:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_21_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei21, .-_osEE_rh850_core0_ei21
#endif
#endif /* OSEE_RH850_CORE0_21_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_22_ISR_CAT))
#if (OSEE_RH850_CORE0_22_ISR_CAT == 1)
_osEE_rh850_core0_ei22:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_22_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei22, .-_osEE_rh850_core0_ei22
#else
_osEE_rh850_core0_ei22:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_22_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei22, .-_osEE_rh850_core0_ei22
#endif
#endif /* OSEE_RH850_CORE0_22_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_23_ISR_CAT))
#if (OSEE_RH850_CORE0_23_ISR_CAT == 1)
_osEE_rh850_core0_ei23:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_23_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei23, .-_osEE_rh850_core0_ei23
#else
_osEE_rh850_core0_ei23:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_23_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei23, .-_osEE_rh850_core0_ei23
#endif
#endif /* OSEE_RH850_CORE0_23_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_24_ISR_CAT))
#if (OSEE_RH850_CORE0_24_ISR_CAT == 1)
_osEE_rh850_core0_ei24:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_24_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei24, .-_osEE_rh850_core0_ei24
#else
_osEE_rh850_core0_ei24:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_24_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei24, .-_osEE_rh850_core0_ei24
#endif
#endif /* OSEE_RH850_CORE0_24_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_25_ISR_CAT))
#if (OSEE_RH850_CORE0_25_ISR_CAT == 1)
_osEE_rh850_core0_ei25:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_25_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei25, .-_osEE_rh850_core0_ei25
#else
_osEE_rh850_core0_ei25:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_25_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei25, .-_osEE_rh850_core0_ei25
#endif
#endif /* OSEE_RH850_CORE0_25_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_26_ISR_CAT))
#if (OSEE_RH850_CORE0_26_ISR_CAT == 1)
_osEE_rh850_core0_ei26:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_26_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei26, .-_osEE_rh850_core0_ei26
#else
_osEE_rh850_core0_ei26:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_26_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei26, .-_osEE_rh850_core0_ei26
#endif
#endif /* OSEE_RH850_CORE0_26_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_27_ISR_CAT))
#if (OSEE_RH850_CORE0_27_ISR_CAT == 1)
_osEE_rh850_core0_ei27:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_27_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei27, .-_osEE_rh850_core0_ei27
#else
_osEE_rh850_core0_ei27:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_27_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei27, .-_osEE_rh850_core0_ei27
#endif
#endif /* OSEE_RH850_CORE0_27_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_28_ISR_CAT))
#if (OSEE_RH850_CORE0_28_ISR_CAT == 1)
_osEE_rh850_core0_ei28:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_28_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei28, .-_osEE_rh850_core0_ei28
#else
_osEE_rh850_core0_ei28:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_28_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei28, .-_osEE_rh850_core0_ei28
#endif
#endif /* OSEE_RH850_CORE0_28_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_29_ISR_CAT))
#if (OSEE_RH850_CORE0_29_ISR_CAT == 1)
_osEE_rh850_core0_ei29:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_29_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei29, .-_osEE_rh850_core0_ei29
#else
_osEE_rh850_core0_ei29:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_29_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei29, .-_osEE_rh850_core0_ei29
#endif
#endif /* OSEE_RH850_CORE0_29_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_30_ISR_CAT))
#if (OSEE_RH850_CORE0_30_ISR_CAT == 1)
_osEE_rh850_core0_ei30:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_30_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei30, .-_osEE_rh850_core0_ei30
#else
_osEE_rh850_core0_ei30:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_30_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei30, .-_osEE_rh850_core0_ei30
#endif
#endif /* OSEE_RH850_CORE0_30_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_31_ISR_CAT))
#if (OSEE_RH850_CORE0_31_ISR_CAT == 1)
_osEE_rh850_core0_ei31:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_31_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei31, .-_osEE_rh850_core0_ei31
#else
_osEE_rh850_core0_ei31:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_31_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei31, .-_osEE_rh850_core0_ei31
#endif
#endif /* OSEE_RH850_CORE0_31_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_32_ISR_CAT))
#if (OSEE_RH850_CORE0_32_ISR_CAT == 1)
_osEE_rh850_core0_ei32:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_32_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei32, .-_osEE_rh850_core0_ei32
#else
_osEE_rh850_core0_ei32:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_32_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei32, .-_osEE_rh850_core0_ei32
#endif
#endif /* OSEE_RH850_CORE0_32_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_33_ISR_CAT))
#if (OSEE_RH850_CORE0_33_ISR_CAT == 1)
_osEE_rh850_core0_ei33:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_33_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei33, .-_osEE_rh850_core0_ei33
#else
_osEE_rh850_core0_ei33:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_33_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei33, .-_osEE_rh850_core0_ei33
#endif
#endif /* OSEE_RH850_CORE0_33_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_34_ISR_CAT))
#if (OSEE_RH850_CORE0_34_ISR_CAT == 1)
_osEE_rh850_core0_ei34:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_34_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei34, .-_osEE_rh850_core0_ei34
#else
_osEE_rh850_core0_ei34:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_34_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei34, .-_osEE_rh850_core0_ei34
#endif
#endif /* OSEE_RH850_CORE0_34_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_35_ISR_CAT))
#if (OSEE_RH850_CORE0_35_ISR_CAT == 1)
_osEE_rh850_core0_ei35:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_35_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei35, .-_osEE_rh850_core0_ei35
#else
_osEE_rh850_core0_ei35:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_35_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei35, .-_osEE_rh850_core0_ei35
#endif
#endif /* OSEE_RH850_CORE0_35_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_36_ISR_CAT))
#if (OSEE_RH850_CORE0_36_ISR_CAT == 1)
_osEE_rh850_core0_ei36:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_36_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei36, .-_osEE_rh850_core0_ei36
#else
_osEE_rh850_core0_ei36:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_36_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei36, .-_osEE_rh850_core0_ei36
#endif
#endif /* OSEE_RH850_CORE0_36_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_37_ISR_CAT))
#if (OSEE_RH850_CORE0_37_ISR_CAT == 1)
_osEE_rh850_core0_ei37:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_37_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei37, .-_osEE_rh850_core0_ei37
#else
_osEE_rh850_core0_ei37:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_37_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei37, .-_osEE_rh850_core0_ei37
#endif
#endif /* OSEE_RH850_CORE0_37_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_38_ISR_CAT))
#if (OSEE_RH850_CORE0_38_ISR_CAT == 1)
_osEE_rh850_core0_ei38:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_38_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei38, .-_osEE_rh850_core0_ei38
#else
_osEE_rh850_core0_ei38:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_38_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei38, .-_osEE_rh850_core0_ei38
#endif
#endif /* OSEE_RH850_CORE0_38_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_39_ISR_CAT))
#if (OSEE_RH850_CORE0_39_ISR_CAT == 1)
_osEE_rh850_core0_ei39:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_39_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei39, .-_osEE_rh850_core0_ei39
#else
_osEE_rh850_core0_ei39:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_39_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei39, .-_osEE_rh850_core0_ei39
#endif
#endif /* OSEE_RH850_CORE0_39_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_40_ISR_CAT))
#if (OSEE_RH850_CORE0_40_ISR_CAT == 1)
_osEE_rh850_core0_ei40:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_40_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei40, .-_osEE_rh850_core0_ei40
#else
_osEE_rh850_core0_ei40:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_40_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei40, .-_osEE_rh850_core0_ei40
#endif
#endif /* OSEE_RH850_CORE0_40_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_41_ISR_CAT))
#if (OSEE_RH850_CORE0_41_ISR_CAT == 1)
_osEE_rh850_core0_ei41:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_41_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei41, .-_osEE_rh850_core0_ei41
#else
_osEE_rh850_core0_ei41:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_41_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei41, .-_osEE_rh850_core0_ei41
#endif
#endif /* OSEE_RH850_CORE0_41_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_42_ISR_CAT))
#if (OSEE_RH850_CORE0_42_ISR_CAT == 1)
_osEE_rh850_core0_ei42:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_42_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei42, .-_osEE_rh850_core0_ei42
#else
_osEE_rh850_core0_ei42:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_42_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei42, .-_osEE_rh850_core0_ei42
#endif
#endif /* OSEE_RH850_CORE0_42_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_43_ISR_CAT))
#if (OSEE_RH850_CORE0_43_ISR_CAT == 1)
_osEE_rh850_core0_ei43:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_43_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei43, .-_osEE_rh850_core0_ei43
#else
_osEE_rh850_core0_ei43:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_43_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei43, .-_osEE_rh850_core0_ei43
#endif
#endif /* OSEE_RH850_CORE0_43_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_44_ISR_CAT))
#if (OSEE_RH850_CORE0_44_ISR_CAT == 1)
_osEE_rh850_core0_ei44:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_44_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei44, .-_osEE_rh850_core0_ei44
#else
_osEE_rh850_core0_ei44:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_44_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei44, .-_osEE_rh850_core0_ei44
#endif
#endif /* OSEE_RH850_CORE0_44_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_45_ISR_CAT))
#if (OSEE_RH850_CORE0_45_ISR_CAT == 1)
_osEE_rh850_core0_ei45:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_45_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei45, .-_osEE_rh850_core0_ei45
#else
_osEE_rh850_core0_ei45:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_45_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei45, .-_osEE_rh850_core0_ei45
#endif
#endif /* OSEE_RH850_CORE0_45_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_46_ISR_CAT))
#if (OSEE_RH850_CORE0_46_ISR_CAT == 1)
_osEE_rh850_core0_ei46:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_46_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei46, .-_osEE_rh850_core0_ei46
#else
_osEE_rh850_core0_ei46:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_46_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei46, .-_osEE_rh850_core0_ei46
#endif
#endif /* OSEE_RH850_CORE0_46_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_47_ISR_CAT))
#if (OSEE_RH850_CORE0_47_ISR_CAT == 1)
_osEE_rh850_core0_ei47:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_47_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei47, .-_osEE_rh850_core0_ei47
#else
_osEE_rh850_core0_ei47:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_47_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei47, .-_osEE_rh850_core0_ei47
#endif
#endif /* OSEE_RH850_CORE0_47_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_48_ISR_CAT))
#if (OSEE_RH850_CORE0_48_ISR_CAT == 1)
_osEE_rh850_core0_ei48:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_48_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei48, .-_osEE_rh850_core0_ei48
#else
_osEE_rh850_core0_ei48:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_48_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei48, .-_osEE_rh850_core0_ei48
#endif
#endif /* OSEE_RH850_CORE0_48_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_49_ISR_CAT))
#if (OSEE_RH850_CORE0_49_ISR_CAT == 1)
_osEE_rh850_core0_ei49:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_49_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei49, .-_osEE_rh850_core0_ei49
#else
_osEE_rh850_core0_ei49:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_49_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei49, .-_osEE_rh850_core0_ei49
#endif
#endif /* OSEE_RH850_CORE0_49_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_50_ISR_CAT))
#if (OSEE_RH850_CORE0_50_ISR_CAT == 1)
_osEE_rh850_core0_ei50:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_50_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei50, .-_osEE_rh850_core0_ei50
#else
_osEE_rh850_core0_ei50:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_50_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei50, .-_osEE_rh850_core0_ei50
#endif
#endif /* OSEE_RH850_CORE0_50_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_51_ISR_CAT))
#if (OSEE_RH850_CORE0_51_ISR_CAT == 1)
_osEE_rh850_core0_ei51:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_51_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei51, .-_osEE_rh850_core0_ei51
#else
_osEE_rh850_core0_ei51:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_51_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei51, .-_osEE_rh850_core0_ei51
#endif
#endif /* OSEE_RH850_CORE0_51_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_52_ISR_CAT))
#if (OSEE_RH850_CORE0_52_ISR_CAT == 1)
_osEE_rh850_core0_ei52:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_52_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei52, .-_osEE_rh850_core0_ei52
#else
_osEE_rh850_core0_ei52:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_52_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei52, .-_osEE_rh850_core0_ei52
#endif
#endif /* OSEE_RH850_CORE0_52_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_53_ISR_CAT))
#if (OSEE_RH850_CORE0_53_ISR_CAT == 1)
_osEE_rh850_core0_ei53:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_53_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei53, .-_osEE_rh850_core0_ei53
#else
_osEE_rh850_core0_ei53:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_53_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei53, .-_osEE_rh850_core0_ei53
#endif
#endif /* OSEE_RH850_CORE0_53_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_54_ISR_CAT))
#if (OSEE_RH850_CORE0_54_ISR_CAT == 1)
_osEE_rh850_core0_ei54:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_54_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei54, .-_osEE_rh850_core0_ei54
#else
_osEE_rh850_core0_ei54:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_54_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei54, .-_osEE_rh850_core0_ei54
#endif
#endif /* OSEE_RH850_CORE0_54_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_55_ISR_CAT))
#if (OSEE_RH850_CORE0_55_ISR_CAT == 1)
_osEE_rh850_core0_ei55:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_55_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei55, .-_osEE_rh850_core0_ei55
#else
_osEE_rh850_core0_ei55:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_55_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei55, .-_osEE_rh850_core0_ei55
#endif
#endif /* OSEE_RH850_CORE0_55_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_56_ISR_CAT))
#if (OSEE_RH850_CORE0_56_ISR_CAT == 1)
_osEE_rh850_core0_ei56:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_56_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei56, .-_osEE_rh850_core0_ei56
#else
_osEE_rh850_core0_ei56:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_56_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei56, .-_osEE_rh850_core0_ei56
#endif
#endif /* OSEE_RH850_CORE0_56_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_57_ISR_CAT))
#if (OSEE_RH850_CORE0_57_ISR_CAT == 1)
_osEE_rh850_core0_ei57:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_57_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei57, .-_osEE_rh850_core0_ei57
#else
_osEE_rh850_core0_ei57:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_57_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei57, .-_osEE_rh850_core0_ei57
#endif
#endif /* OSEE_RH850_CORE0_57_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_58_ISR_CAT))
#if (OSEE_RH850_CORE0_58_ISR_CAT == 1)
_osEE_rh850_core0_ei58:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_58_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei58, .-_osEE_rh850_core0_ei58
#else
_osEE_rh850_core0_ei58:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_58_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei58, .-_osEE_rh850_core0_ei58
#endif
#endif /* OSEE_RH850_CORE0_58_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_59_ISR_CAT))
#if (OSEE_RH850_CORE0_59_ISR_CAT == 1)
_osEE_rh850_core0_ei59:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_59_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei59, .-_osEE_rh850_core0_ei59
#else
_osEE_rh850_core0_ei59:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_59_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei59, .-_osEE_rh850_core0_ei59
#endif
#endif /* OSEE_RH850_CORE0_59_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_60_ISR_CAT))
#if (OSEE_RH850_CORE0_60_ISR_CAT == 1)
_osEE_rh850_core0_ei60:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_60_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei60, .-_osEE_rh850_core0_ei60
#else
_osEE_rh850_core0_ei60:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_60_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei60, .-_osEE_rh850_core0_ei60
#endif
#endif /* OSEE_RH850_CORE0_60_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_61_ISR_CAT))
#if (OSEE_RH850_CORE0_61_ISR_CAT == 1)
_osEE_rh850_core0_ei61:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_61_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei61, .-_osEE_rh850_core0_ei61
#else
_osEE_rh850_core0_ei61:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_61_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei61, .-_osEE_rh850_core0_ei61
#endif
#endif /* OSEE_RH850_CORE0_61_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_62_ISR_CAT))
#if (OSEE_RH850_CORE0_62_ISR_CAT == 1)
_osEE_rh850_core0_ei62:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_62_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei62, .-_osEE_rh850_core0_ei62
#else
_osEE_rh850_core0_ei62:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_62_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei62, .-_osEE_rh850_core0_ei62
#endif
#endif /* OSEE_RH850_CORE0_62_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_63_ISR_CAT))
#if (OSEE_RH850_CORE0_63_ISR_CAT == 1)
_osEE_rh850_core0_ei63:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_63_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei63, .-_osEE_rh850_core0_ei63
#else
_osEE_rh850_core0_ei63:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_63_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei63, .-_osEE_rh850_core0_ei63
#endif
#endif /* OSEE_RH850_CORE0_63_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_64_ISR_CAT))
#if (OSEE_RH850_CORE0_64_ISR_CAT == 1)
_osEE_rh850_core0_ei64:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_64_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei64, .-_osEE_rh850_core0_ei64
#else
_osEE_rh850_core0_ei64:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_64_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei64, .-_osEE_rh850_core0_ei64
#endif
#endif /* OSEE_RH850_CORE0_64_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_65_ISR_CAT))
#if (OSEE_RH850_CORE0_65_ISR_CAT == 1)
_osEE_rh850_core0_ei65:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_65_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei65, .-_osEE_rh850_core0_ei65
#else
_osEE_rh850_core0_ei65:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_65_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei65, .-_osEE_rh850_core0_ei65
#endif
#endif /* OSEE_RH850_CORE0_65_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_66_ISR_CAT))
#if (OSEE_RH850_CORE0_66_ISR_CAT == 1)
_osEE_rh850_core0_ei66:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_66_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei66, .-_osEE_rh850_core0_ei66
#else
_osEE_rh850_core0_ei66:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_66_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei66, .-_osEE_rh850_core0_ei66
#endif
#endif /* OSEE_RH850_CORE0_66_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_67_ISR_CAT))
#if (OSEE_RH850_CORE0_67_ISR_CAT == 1)
_osEE_rh850_core0_ei67:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_67_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei67, .-_osEE_rh850_core0_ei67
#else
_osEE_rh850_core0_ei67:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_67_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei67, .-_osEE_rh850_core0_ei67
#endif
#endif /* OSEE_RH850_CORE0_67_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_68_ISR_CAT))
#if (OSEE_RH850_CORE0_68_ISR_CAT == 1)
_osEE_rh850_core0_ei68:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_68_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei68, .-_osEE_rh850_core0_ei68
#else
_osEE_rh850_core0_ei68:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_68_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei68, .-_osEE_rh850_core0_ei68
#endif
#endif /* OSEE_RH850_CORE0_68_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_69_ISR_CAT))
#if (OSEE_RH850_CORE0_69_ISR_CAT == 1)
_osEE_rh850_core0_ei69:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_69_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei69, .-_osEE_rh850_core0_ei69
#else
_osEE_rh850_core0_ei69:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_69_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei69, .-_osEE_rh850_core0_ei69
#endif
#endif /* OSEE_RH850_CORE0_69_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_70_ISR_CAT))
#if (OSEE_RH850_CORE0_70_ISR_CAT == 1)
_osEE_rh850_core0_ei70:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_70_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei70, .-_osEE_rh850_core0_ei70
#else
_osEE_rh850_core0_ei70:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_70_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei70, .-_osEE_rh850_core0_ei70
#endif
#endif /* OSEE_RH850_CORE0_70_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_71_ISR_CAT))
#if (OSEE_RH850_CORE0_71_ISR_CAT == 1)
_osEE_rh850_core0_ei71:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_71_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei71, .-_osEE_rh850_core0_ei71
#else
_osEE_rh850_core0_ei71:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_71_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei71, .-_osEE_rh850_core0_ei71
#endif
#endif /* OSEE_RH850_CORE0_71_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_72_ISR_CAT))
#if (OSEE_RH850_CORE0_72_ISR_CAT == 1)
_osEE_rh850_core0_ei72:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_72_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei72, .-_osEE_rh850_core0_ei72
#else
_osEE_rh850_core0_ei72:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_72_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei72, .-_osEE_rh850_core0_ei72
#endif
#endif /* OSEE_RH850_CORE0_72_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_73_ISR_CAT))
#if (OSEE_RH850_CORE0_73_ISR_CAT == 1)
_osEE_rh850_core0_ei73:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_73_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei73, .-_osEE_rh850_core0_ei73
#else
_osEE_rh850_core0_ei73:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_73_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei73, .-_osEE_rh850_core0_ei73
#endif
#endif /* OSEE_RH850_CORE0_73_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_74_ISR_CAT))
#if (OSEE_RH850_CORE0_74_ISR_CAT == 1)
_osEE_rh850_core0_ei74:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_74_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei74, .-_osEE_rh850_core0_ei74
#else
_osEE_rh850_core0_ei74:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_74_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei74, .-_osEE_rh850_core0_ei74
#endif
#endif /* OSEE_RH850_CORE0_74_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_75_ISR_CAT))
#if (OSEE_RH850_CORE0_75_ISR_CAT == 1)
_osEE_rh850_core0_ei75:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_75_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei75, .-_osEE_rh850_core0_ei75
#else
_osEE_rh850_core0_ei75:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_75_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei75, .-_osEE_rh850_core0_ei75
#endif
#endif /* OSEE_RH850_CORE0_75_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_76_ISR_CAT))
#if (OSEE_RH850_CORE0_76_ISR_CAT == 1)
_osEE_rh850_core0_ei76:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_76_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei76, .-_osEE_rh850_core0_ei76
#else
_osEE_rh850_core0_ei76:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_76_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei76, .-_osEE_rh850_core0_ei76
#endif
#endif /* OSEE_RH850_CORE0_76_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_77_ISR_CAT))
#if (OSEE_RH850_CORE0_77_ISR_CAT == 1)
_osEE_rh850_core0_ei77:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_77_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei77, .-_osEE_rh850_core0_ei77
#else
_osEE_rh850_core0_ei77:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_77_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei77, .-_osEE_rh850_core0_ei77
#endif
#endif /* OSEE_RH850_CORE0_77_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_78_ISR_CAT))
#if (OSEE_RH850_CORE0_78_ISR_CAT == 1)
_osEE_rh850_core0_ei78:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_78_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei78, .-_osEE_rh850_core0_ei78
#else
_osEE_rh850_core0_ei78:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_78_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei78, .-_osEE_rh850_core0_ei78
#endif
#endif /* OSEE_RH850_CORE0_78_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_79_ISR_CAT))
#if (OSEE_RH850_CORE0_79_ISR_CAT == 1)
_osEE_rh850_core0_ei79:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_79_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei79, .-_osEE_rh850_core0_ei79
#else
_osEE_rh850_core0_ei79:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_79_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei79, .-_osEE_rh850_core0_ei79
#endif
#endif /* OSEE_RH850_CORE0_79_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_80_ISR_CAT))
#if (OSEE_RH850_CORE0_80_ISR_CAT == 1)
_osEE_rh850_core0_ei80:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_80_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei80, .-_osEE_rh850_core0_ei80
#else
_osEE_rh850_core0_ei80:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_80_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei80, .-_osEE_rh850_core0_ei80
#endif
#endif /* OSEE_RH850_CORE0_80_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_81_ISR_CAT))
#if (OSEE_RH850_CORE0_81_ISR_CAT == 1)
_osEE_rh850_core0_ei81:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_81_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei81, .-_osEE_rh850_core0_ei81
#else
_osEE_rh850_core0_ei81:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_81_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei81, .-_osEE_rh850_core0_ei81
#endif
#endif /* OSEE_RH850_CORE0_81_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_82_ISR_CAT))
#if (OSEE_RH850_CORE0_82_ISR_CAT == 1)
_osEE_rh850_core0_ei82:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_82_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei82, .-_osEE_rh850_core0_ei82
#else
_osEE_rh850_core0_ei82:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_82_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei82, .-_osEE_rh850_core0_ei82
#endif
#endif /* OSEE_RH850_CORE0_82_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_83_ISR_CAT))
#if (OSEE_RH850_CORE0_83_ISR_CAT == 1)
_osEE_rh850_core0_ei83:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_83_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei83, .-_osEE_rh850_core0_ei83
#else
_osEE_rh850_core0_ei83:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_83_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei83, .-_osEE_rh850_core0_ei83
#endif
#endif /* OSEE_RH850_CORE0_83_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_84_ISR_CAT))
#if (OSEE_RH850_CORE0_84_ISR_CAT == 1)
_osEE_rh850_core0_ei84:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_84_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei84, .-_osEE_rh850_core0_ei84
#else
_osEE_rh850_core0_ei84:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_84_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei84, .-_osEE_rh850_core0_ei84
#endif
#endif /* OSEE_RH850_CORE0_84_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_85_ISR_CAT))
#if (OSEE_RH850_CORE0_85_ISR_CAT == 1)
_osEE_rh850_core0_ei85:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_85_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei85, .-_osEE_rh850_core0_ei85
#else
_osEE_rh850_core0_ei85:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_85_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei85, .-_osEE_rh850_core0_ei85
#endif
#endif /* OSEE_RH850_CORE0_85_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_86_ISR_CAT))
#if (OSEE_RH850_CORE0_86_ISR_CAT == 1)
_osEE_rh850_core0_ei86:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_86_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei86, .-_osEE_rh850_core0_ei86
#else
_osEE_rh850_core0_ei86:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_86_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei86, .-_osEE_rh850_core0_ei86
#endif
#endif /* OSEE_RH850_CORE0_86_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_87_ISR_CAT))
#if (OSEE_RH850_CORE0_87_ISR_CAT == 1)
_osEE_rh850_core0_ei87:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_87_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei87, .-_osEE_rh850_core0_ei87
#else
_osEE_rh850_core0_ei87:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_87_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei87, .-_osEE_rh850_core0_ei87
#endif
#endif /* OSEE_RH850_CORE0_87_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_88_ISR_CAT))
#if (OSEE_RH850_CORE0_88_ISR_CAT == 1)
_osEE_rh850_core0_ei88:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_88_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei88, .-_osEE_rh850_core0_ei88
#else
_osEE_rh850_core0_ei88:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_88_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei88, .-_osEE_rh850_core0_ei88
#endif
#endif /* OSEE_RH850_CORE0_88_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_89_ISR_CAT))
#if (OSEE_RH850_CORE0_89_ISR_CAT == 1)
_osEE_rh850_core0_ei89:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_89_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei89, .-_osEE_rh850_core0_ei89
#else
_osEE_rh850_core0_ei89:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_89_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei89, .-_osEE_rh850_core0_ei89
#endif
#endif /* OSEE_RH850_CORE0_89_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_90_ISR_CAT))
#if (OSEE_RH850_CORE0_90_ISR_CAT == 1)
_osEE_rh850_core0_ei90:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_90_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei90, .-_osEE_rh850_core0_ei90
#else
_osEE_rh850_core0_ei90:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_90_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei90, .-_osEE_rh850_core0_ei90
#endif
#endif /* OSEE_RH850_CORE0_90_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_91_ISR_CAT))
#if (OSEE_RH850_CORE0_91_ISR_CAT == 1)
_osEE_rh850_core0_ei91:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_91_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei91, .-_osEE_rh850_core0_ei91
#else
_osEE_rh850_core0_ei91:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_91_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei91, .-_osEE_rh850_core0_ei91
#endif
#endif /* OSEE_RH850_CORE0_91_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_92_ISR_CAT))
#if (OSEE_RH850_CORE0_92_ISR_CAT == 1)
_osEE_rh850_core0_ei92:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_92_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei92, .-_osEE_rh850_core0_ei92
#else
_osEE_rh850_core0_ei92:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_92_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei92, .-_osEE_rh850_core0_ei92
#endif
#endif /* OSEE_RH850_CORE0_92_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_93_ISR_CAT))
#if (OSEE_RH850_CORE0_93_ISR_CAT == 1)
_osEE_rh850_core0_ei93:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_93_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei93, .-_osEE_rh850_core0_ei93
#else
_osEE_rh850_core0_ei93:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_93_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei93, .-_osEE_rh850_core0_ei93
#endif
#endif /* OSEE_RH850_CORE0_93_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_94_ISR_CAT))
#if (OSEE_RH850_CORE0_94_ISR_CAT == 1)
_osEE_rh850_core0_ei94:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_94_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei94, .-_osEE_rh850_core0_ei94
#else
_osEE_rh850_core0_ei94:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_94_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei94, .-_osEE_rh850_core0_ei94
#endif
#endif /* OSEE_RH850_CORE0_94_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_95_ISR_CAT))
#if (OSEE_RH850_CORE0_95_ISR_CAT == 1)
_osEE_rh850_core0_ei95:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_95_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei95, .-_osEE_rh850_core0_ei95
#else
_osEE_rh850_core0_ei95:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_95_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei95, .-_osEE_rh850_core0_ei95
#endif
#endif /* OSEE_RH850_CORE0_95_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_96_ISR_CAT))
#if (OSEE_RH850_CORE0_96_ISR_CAT == 1)
_osEE_rh850_core0_ei96:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_96_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei96, .-_osEE_rh850_core0_ei96
#else
_osEE_rh850_core0_ei96:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_96_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei96, .-_osEE_rh850_core0_ei96
#endif
#endif /* OSEE_RH850_CORE0_96_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_97_ISR_CAT))
#if (OSEE_RH850_CORE0_97_ISR_CAT == 1)
_osEE_rh850_core0_ei97:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_97_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei97, .-_osEE_rh850_core0_ei97
#else
_osEE_rh850_core0_ei97:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_97_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei97, .-_osEE_rh850_core0_ei97
#endif
#endif /* OSEE_RH850_CORE0_97_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_98_ISR_CAT))
#if (OSEE_RH850_CORE0_98_ISR_CAT == 1)
_osEE_rh850_core0_ei98:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_98_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei98, .-_osEE_rh850_core0_ei98
#else
_osEE_rh850_core0_ei98:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_98_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei98, .-_osEE_rh850_core0_ei98
#endif
#endif /* OSEE_RH850_CORE0_98_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_99_ISR_CAT))
#if (OSEE_RH850_CORE0_99_ISR_CAT == 1)
_osEE_rh850_core0_ei99:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_99_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei99, .-_osEE_rh850_core0_ei99
#else
_osEE_rh850_core0_ei99:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_99_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei99, .-_osEE_rh850_core0_ei99
#endif
#endif /* OSEE_RH850_CORE0_99_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_100_ISR_CAT))
#if (OSEE_RH850_CORE0_100_ISR_CAT == 1)
_osEE_rh850_core0_ei100:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_100_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei100, .-_osEE_rh850_core0_ei100
#else
_osEE_rh850_core0_ei100:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_100_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei100, .-_osEE_rh850_core0_ei100
#endif
#endif /* OSEE_RH850_CORE0_100_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_101_ISR_CAT))
#if (OSEE_RH850_CORE0_101_ISR_CAT == 1)
_osEE_rh850_core0_ei101:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_101_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei101, .-_osEE_rh850_core0_ei101
#else
_osEE_rh850_core0_ei101:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_101_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei101, .-_osEE_rh850_core0_ei101
#endif
#endif /* OSEE_RH850_CORE0_101_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_102_ISR_CAT))
#if (OSEE_RH850_CORE0_102_ISR_CAT == 1)
_osEE_rh850_core0_ei102:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_102_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei102, .-_osEE_rh850_core0_ei102
#else
_osEE_rh850_core0_ei102:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_102_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei102, .-_osEE_rh850_core0_ei102
#endif
#endif /* OSEE_RH850_CORE0_102_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_103_ISR_CAT))
#if (OSEE_RH850_CORE0_103_ISR_CAT == 1)
_osEE_rh850_core0_ei103:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_103_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei103, .-_osEE_rh850_core0_ei103
#else
_osEE_rh850_core0_ei103:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_103_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei103, .-_osEE_rh850_core0_ei103
#endif
#endif /* OSEE_RH850_CORE0_103_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_104_ISR_CAT))
#if (OSEE_RH850_CORE0_104_ISR_CAT == 1)
_osEE_rh850_core0_ei104:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_104_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei104, .-_osEE_rh850_core0_ei104
#else
_osEE_rh850_core0_ei104:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_104_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei104, .-_osEE_rh850_core0_ei104
#endif
#endif /* OSEE_RH850_CORE0_104_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_105_ISR_CAT))
#if (OSEE_RH850_CORE0_105_ISR_CAT == 1)
_osEE_rh850_core0_ei105:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_105_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei105, .-_osEE_rh850_core0_ei105
#else
_osEE_rh850_core0_ei105:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_105_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei105, .-_osEE_rh850_core0_ei105
#endif
#endif /* OSEE_RH850_CORE0_105_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_106_ISR_CAT))
#if (OSEE_RH850_CORE0_106_ISR_CAT == 1)
_osEE_rh850_core0_ei106:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_106_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei106, .-_osEE_rh850_core0_ei106
#else
_osEE_rh850_core0_ei106:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_106_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei106, .-_osEE_rh850_core0_ei106
#endif
#endif /* OSEE_RH850_CORE0_106_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_107_ISR_CAT))
#if (OSEE_RH850_CORE0_107_ISR_CAT == 1)
_osEE_rh850_core0_ei107:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_107_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei107, .-_osEE_rh850_core0_ei107
#else
_osEE_rh850_core0_ei107:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_107_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei107, .-_osEE_rh850_core0_ei107
#endif
#endif /* OSEE_RH850_CORE0_107_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_108_ISR_CAT))
#if (OSEE_RH850_CORE0_108_ISR_CAT == 1)
_osEE_rh850_core0_ei108:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_108_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei108, .-_osEE_rh850_core0_ei108
#else
_osEE_rh850_core0_ei108:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_108_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei108, .-_osEE_rh850_core0_ei108
#endif
#endif /* OSEE_RH850_CORE0_108_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_109_ISR_CAT))
#if (OSEE_RH850_CORE0_109_ISR_CAT == 1)
_osEE_rh850_core0_ei109:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_109_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei109, .-_osEE_rh850_core0_ei109
#else
_osEE_rh850_core0_ei109:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_109_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei109, .-_osEE_rh850_core0_ei109
#endif
#endif /* OSEE_RH850_CORE0_109_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_110_ISR_CAT))
#if (OSEE_RH850_CORE0_110_ISR_CAT == 1)
_osEE_rh850_core0_ei110:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_110_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei110, .-_osEE_rh850_core0_ei110
#else
_osEE_rh850_core0_ei110:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_110_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei110, .-_osEE_rh850_core0_ei110
#endif
#endif /* OSEE_RH850_CORE0_110_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_111_ISR_CAT))
#if (OSEE_RH850_CORE0_111_ISR_CAT == 1)
_osEE_rh850_core0_ei111:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_111_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei111, .-_osEE_rh850_core0_ei111
#else
_osEE_rh850_core0_ei111:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_111_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei111, .-_osEE_rh850_core0_ei111
#endif
#endif /* OSEE_RH850_CORE0_111_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_112_ISR_CAT))
#if (OSEE_RH850_CORE0_112_ISR_CAT == 1)
_osEE_rh850_core0_ei112:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_112_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei112, .-_osEE_rh850_core0_ei112
#else
_osEE_rh850_core0_ei112:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_112_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei112, .-_osEE_rh850_core0_ei112
#endif
#endif /* OSEE_RH850_CORE0_112_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_113_ISR_CAT))
#if (OSEE_RH850_CORE0_113_ISR_CAT == 1)
_osEE_rh850_core0_ei113:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_113_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei113, .-_osEE_rh850_core0_ei113
#else
_osEE_rh850_core0_ei113:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_113_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei113, .-_osEE_rh850_core0_ei113
#endif
#endif /* OSEE_RH850_CORE0_113_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_114_ISR_CAT))
#if (OSEE_RH850_CORE0_114_ISR_CAT == 1)
_osEE_rh850_core0_ei114:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_114_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei114, .-_osEE_rh850_core0_ei114
#else
_osEE_rh850_core0_ei114:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_114_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei114, .-_osEE_rh850_core0_ei114
#endif
#endif /* OSEE_RH850_CORE0_114_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_115_ISR_CAT))
#if (OSEE_RH850_CORE0_115_ISR_CAT == 1)
_osEE_rh850_core0_ei115:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_115_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei115, .-_osEE_rh850_core0_ei115
#else
_osEE_rh850_core0_ei115:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_115_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei115, .-_osEE_rh850_core0_ei115
#endif
#endif /* OSEE_RH850_CORE0_115_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_116_ISR_CAT))
#if (OSEE_RH850_CORE0_116_ISR_CAT == 1)
_osEE_rh850_core0_ei116:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_116_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei116, .-_osEE_rh850_core0_ei116
#else
_osEE_rh850_core0_ei116:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_116_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei116, .-_osEE_rh850_core0_ei116
#endif
#endif /* OSEE_RH850_CORE0_116_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_117_ISR_CAT))
#if (OSEE_RH850_CORE0_117_ISR_CAT == 1)
_osEE_rh850_core0_ei117:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_117_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei117, .-_osEE_rh850_core0_ei117
#else
_osEE_rh850_core0_ei117:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_117_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei117, .-_osEE_rh850_core0_ei117
#endif
#endif /* OSEE_RH850_CORE0_117_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_118_ISR_CAT))
#if (OSEE_RH850_CORE0_118_ISR_CAT == 1)
_osEE_rh850_core0_ei118:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_118_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei118, .-_osEE_rh850_core0_ei118
#else
_osEE_rh850_core0_ei118:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_118_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei118, .-_osEE_rh850_core0_ei118
#endif
#endif /* OSEE_RH850_CORE0_118_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_119_ISR_CAT))
#if (OSEE_RH850_CORE0_119_ISR_CAT == 1)
_osEE_rh850_core0_ei119:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_119_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei119, .-_osEE_rh850_core0_ei119
#else
_osEE_rh850_core0_ei119:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_119_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei119, .-_osEE_rh850_core0_ei119
#endif
#endif /* OSEE_RH850_CORE0_119_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_120_ISR_CAT))
#if (OSEE_RH850_CORE0_120_ISR_CAT == 1)
_osEE_rh850_core0_ei120:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_120_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei120, .-_osEE_rh850_core0_ei120
#else
_osEE_rh850_core0_ei120:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_120_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei120, .-_osEE_rh850_core0_ei120
#endif
#endif /* OSEE_RH850_CORE0_120_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_121_ISR_CAT))
#if (OSEE_RH850_CORE0_121_ISR_CAT == 1)
_osEE_rh850_core0_ei121:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_121_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei121, .-_osEE_rh850_core0_ei121
#else
_osEE_rh850_core0_ei121:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_121_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei121, .-_osEE_rh850_core0_ei121
#endif
#endif /* OSEE_RH850_CORE0_121_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_122_ISR_CAT))
#if (OSEE_RH850_CORE0_122_ISR_CAT == 1)
_osEE_rh850_core0_ei122:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_122_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei122, .-_osEE_rh850_core0_ei122
#else
_osEE_rh850_core0_ei122:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_122_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei122, .-_osEE_rh850_core0_ei122
#endif
#endif /* OSEE_RH850_CORE0_122_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_123_ISR_CAT))
#if (OSEE_RH850_CORE0_123_ISR_CAT == 1)
_osEE_rh850_core0_ei123:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_123_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei123, .-_osEE_rh850_core0_ei123
#else
_osEE_rh850_core0_ei123:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_123_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei123, .-_osEE_rh850_core0_ei123
#endif
#endif /* OSEE_RH850_CORE0_123_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_124_ISR_CAT))
#if (OSEE_RH850_CORE0_124_ISR_CAT == 1)
_osEE_rh850_core0_ei124:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_124_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei124, .-_osEE_rh850_core0_ei124
#else
_osEE_rh850_core0_ei124:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_124_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei124, .-_osEE_rh850_core0_ei124
#endif
#endif /* OSEE_RH850_CORE0_124_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_125_ISR_CAT))
#if (OSEE_RH850_CORE0_125_ISR_CAT == 1)
_osEE_rh850_core0_ei125:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_125_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei125, .-_osEE_rh850_core0_ei125
#else
_osEE_rh850_core0_ei125:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_125_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei125, .-_osEE_rh850_core0_ei125
#endif
#endif /* OSEE_RH850_CORE0_125_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_126_ISR_CAT))
#if (OSEE_RH850_CORE0_126_ISR_CAT == 1)
_osEE_rh850_core0_ei126:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_126_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei126, .-_osEE_rh850_core0_ei126
#else
_osEE_rh850_core0_ei126:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_126_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei126, .-_osEE_rh850_core0_ei126
#endif
#endif /* OSEE_RH850_CORE0_126_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_127_ISR_CAT))
#if (OSEE_RH850_CORE0_127_ISR_CAT == 1)
_osEE_rh850_core0_ei127:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_127_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei127, .-_osEE_rh850_core0_ei127
#else
_osEE_rh850_core0_ei127:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_127_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei127, .-_osEE_rh850_core0_ei127
#endif
#endif /* OSEE_RH850_CORE0_127_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_128_ISR_CAT))
#if (OSEE_RH850_CORE0_128_ISR_CAT == 1)
_osEE_rh850_core0_ei128:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_128_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei128, .-_osEE_rh850_core0_ei128
#else
_osEE_rh850_core0_ei128:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_128_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei128, .-_osEE_rh850_core0_ei128
#endif
#endif /* OSEE_RH850_CORE0_128_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_129_ISR_CAT))
#if (OSEE_RH850_CORE0_129_ISR_CAT == 1)
_osEE_rh850_core0_ei129:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_129_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei129, .-_osEE_rh850_core0_ei129
#else
_osEE_rh850_core0_ei129:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_129_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei129, .-_osEE_rh850_core0_ei129
#endif
#endif /* OSEE_RH850_CORE0_129_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_130_ISR_CAT))
#if (OSEE_RH850_CORE0_130_ISR_CAT == 1)
_osEE_rh850_core0_ei130:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_130_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei130, .-_osEE_rh850_core0_ei130
#else
_osEE_rh850_core0_ei130:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_130_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei130, .-_osEE_rh850_core0_ei130
#endif
#endif /* OSEE_RH850_CORE0_130_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_131_ISR_CAT))
#if (OSEE_RH850_CORE0_131_ISR_CAT == 1)
_osEE_rh850_core0_ei131:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_131_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei131, .-_osEE_rh850_core0_ei131
#else
_osEE_rh850_core0_ei131:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_131_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei131, .-_osEE_rh850_core0_ei131
#endif
#endif /* OSEE_RH850_CORE0_131_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_132_ISR_CAT))
#if (OSEE_RH850_CORE0_132_ISR_CAT == 1)
_osEE_rh850_core0_ei132:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_132_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei132, .-_osEE_rh850_core0_ei132
#else
_osEE_rh850_core0_ei132:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_132_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei132, .-_osEE_rh850_core0_ei132
#endif
#endif /* OSEE_RH850_CORE0_132_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_133_ISR_CAT))
#if (OSEE_RH850_CORE0_133_ISR_CAT == 1)
_osEE_rh850_core0_ei133:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_133_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei133, .-_osEE_rh850_core0_ei133
#else
_osEE_rh850_core0_ei133:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_133_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei133, .-_osEE_rh850_core0_ei133
#endif
#endif /* OSEE_RH850_CORE0_133_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_134_ISR_CAT))
#if (OSEE_RH850_CORE0_134_ISR_CAT == 1)
_osEE_rh850_core0_ei134:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_134_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei134, .-_osEE_rh850_core0_ei134
#else
_osEE_rh850_core0_ei134:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_134_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei134, .-_osEE_rh850_core0_ei134
#endif
#endif /* OSEE_RH850_CORE0_134_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_135_ISR_CAT))
#if (OSEE_RH850_CORE0_135_ISR_CAT == 1)
_osEE_rh850_core0_ei135:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_135_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei135, .-_osEE_rh850_core0_ei135
#else
_osEE_rh850_core0_ei135:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_135_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei135, .-_osEE_rh850_core0_ei135
#endif
#endif /* OSEE_RH850_CORE0_135_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_136_ISR_CAT))
#if (OSEE_RH850_CORE0_136_ISR_CAT == 1)
_osEE_rh850_core0_ei136:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_136_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei136, .-_osEE_rh850_core0_ei136
#else
_osEE_rh850_core0_ei136:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_136_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei136, .-_osEE_rh850_core0_ei136
#endif
#endif /* OSEE_RH850_CORE0_136_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_137_ISR_CAT))
#if (OSEE_RH850_CORE0_137_ISR_CAT == 1)
_osEE_rh850_core0_ei137:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_137_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei137, .-_osEE_rh850_core0_ei137
#else
_osEE_rh850_core0_ei137:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_137_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei137, .-_osEE_rh850_core0_ei137
#endif
#endif /* OSEE_RH850_CORE0_137_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_138_ISR_CAT))
#if (OSEE_RH850_CORE0_138_ISR_CAT == 1)
_osEE_rh850_core0_ei138:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_138_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei138, .-_osEE_rh850_core0_ei138
#else
_osEE_rh850_core0_ei138:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_138_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei138, .-_osEE_rh850_core0_ei138
#endif
#endif /* OSEE_RH850_CORE0_138_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_139_ISR_CAT))
#if (OSEE_RH850_CORE0_139_ISR_CAT == 1)
_osEE_rh850_core0_ei139:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_139_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei139, .-_osEE_rh850_core0_ei139
#else
_osEE_rh850_core0_ei139:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_139_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei139, .-_osEE_rh850_core0_ei139
#endif
#endif /* OSEE_RH850_CORE0_139_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_140_ISR_CAT))
#if (OSEE_RH850_CORE0_140_ISR_CAT == 1)
_osEE_rh850_core0_ei140:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_140_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei140, .-_osEE_rh850_core0_ei140
#else
_osEE_rh850_core0_ei140:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_140_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei140, .-_osEE_rh850_core0_ei140
#endif
#endif /* OSEE_RH850_CORE0_140_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_141_ISR_CAT))
#if (OSEE_RH850_CORE0_141_ISR_CAT == 1)
_osEE_rh850_core0_ei141:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_141_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei141, .-_osEE_rh850_core0_ei141
#else
_osEE_rh850_core0_ei141:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_141_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei141, .-_osEE_rh850_core0_ei141
#endif
#endif /* OSEE_RH850_CORE0_141_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_142_ISR_CAT))
#if (OSEE_RH850_CORE0_142_ISR_CAT == 1)
_osEE_rh850_core0_ei142:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_142_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei142, .-_osEE_rh850_core0_ei142
#else
_osEE_rh850_core0_ei142:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_142_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei142, .-_osEE_rh850_core0_ei142
#endif
#endif /* OSEE_RH850_CORE0_142_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_143_ISR_CAT))
#if (OSEE_RH850_CORE0_143_ISR_CAT == 1)
_osEE_rh850_core0_ei143:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_143_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei143, .-_osEE_rh850_core0_ei143
#else
_osEE_rh850_core0_ei143:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_143_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei143, .-_osEE_rh850_core0_ei143
#endif
#endif /* OSEE_RH850_CORE0_143_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_144_ISR_CAT))
#if (OSEE_RH850_CORE0_144_ISR_CAT == 1)
_osEE_rh850_core0_ei144:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_144_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei144, .-_osEE_rh850_core0_ei144
#else
_osEE_rh850_core0_ei144:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_144_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei144, .-_osEE_rh850_core0_ei144
#endif
#endif /* OSEE_RH850_CORE0_144_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_145_ISR_CAT))
#if (OSEE_RH850_CORE0_145_ISR_CAT == 1)
_osEE_rh850_core0_ei145:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_145_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei145, .-_osEE_rh850_core0_ei145
#else
_osEE_rh850_core0_ei145:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_145_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei145, .-_osEE_rh850_core0_ei145
#endif
#endif /* OSEE_RH850_CORE0_145_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_146_ISR_CAT))
#if (OSEE_RH850_CORE0_146_ISR_CAT == 1)
_osEE_rh850_core0_ei146:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_146_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei146, .-_osEE_rh850_core0_ei146
#else
_osEE_rh850_core0_ei146:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_146_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei146, .-_osEE_rh850_core0_ei146
#endif
#endif /* OSEE_RH850_CORE0_146_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_147_ISR_CAT))
#if (OSEE_RH850_CORE0_147_ISR_CAT == 1)
_osEE_rh850_core0_ei147:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_147_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei147, .-_osEE_rh850_core0_ei147
#else
_osEE_rh850_core0_ei147:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_147_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei147, .-_osEE_rh850_core0_ei147
#endif
#endif /* OSEE_RH850_CORE0_147_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_148_ISR_CAT))
#if (OSEE_RH850_CORE0_148_ISR_CAT == 1)
_osEE_rh850_core0_ei148:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_148_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei148, .-_osEE_rh850_core0_ei148
#else
_osEE_rh850_core0_ei148:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_148_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei148, .-_osEE_rh850_core0_ei148
#endif
#endif /* OSEE_RH850_CORE0_148_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_149_ISR_CAT))
#if (OSEE_RH850_CORE0_149_ISR_CAT == 1)
_osEE_rh850_core0_ei149:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_149_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei149, .-_osEE_rh850_core0_ei149
#else
_osEE_rh850_core0_ei149:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_149_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei149, .-_osEE_rh850_core0_ei149
#endif
#endif /* OSEE_RH850_CORE0_149_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_150_ISR_CAT))
#if (OSEE_RH850_CORE0_150_ISR_CAT == 1)
_osEE_rh850_core0_ei150:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_150_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei150, .-_osEE_rh850_core0_ei150
#else
_osEE_rh850_core0_ei150:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_150_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei150, .-_osEE_rh850_core0_ei150
#endif
#endif /* OSEE_RH850_CORE0_150_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_151_ISR_CAT))
#if (OSEE_RH850_CORE0_151_ISR_CAT == 1)
_osEE_rh850_core0_ei151:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_151_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei151, .-_osEE_rh850_core0_ei151
#else
_osEE_rh850_core0_ei151:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_151_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei151, .-_osEE_rh850_core0_ei151
#endif
#endif /* OSEE_RH850_CORE0_151_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_152_ISR_CAT))
#if (OSEE_RH850_CORE0_152_ISR_CAT == 1)
_osEE_rh850_core0_ei152:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_152_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei152, .-_osEE_rh850_core0_ei152
#else
_osEE_rh850_core0_ei152:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_152_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei152, .-_osEE_rh850_core0_ei152
#endif
#endif /* OSEE_RH850_CORE0_152_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_153_ISR_CAT))
#if (OSEE_RH850_CORE0_153_ISR_CAT == 1)
_osEE_rh850_core0_ei153:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_153_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei153, .-_osEE_rh850_core0_ei153
#else
_osEE_rh850_core0_ei153:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_153_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei153, .-_osEE_rh850_core0_ei153
#endif
#endif /* OSEE_RH850_CORE0_153_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_154_ISR_CAT))
#if (OSEE_RH850_CORE0_154_ISR_CAT == 1)
_osEE_rh850_core0_ei154:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_154_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei154, .-_osEE_rh850_core0_ei154
#else
_osEE_rh850_core0_ei154:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_154_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei154, .-_osEE_rh850_core0_ei154
#endif
#endif /* OSEE_RH850_CORE0_154_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_155_ISR_CAT))
#if (OSEE_RH850_CORE0_155_ISR_CAT == 1)
_osEE_rh850_core0_ei155:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_155_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei155, .-_osEE_rh850_core0_ei155
#else
_osEE_rh850_core0_ei155:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_155_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei155, .-_osEE_rh850_core0_ei155
#endif
#endif /* OSEE_RH850_CORE0_155_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_156_ISR_CAT))
#if (OSEE_RH850_CORE0_156_ISR_CAT == 1)
_osEE_rh850_core0_ei156:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_156_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei156, .-_osEE_rh850_core0_ei156
#else
_osEE_rh850_core0_ei156:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_156_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei156, .-_osEE_rh850_core0_ei156
#endif
#endif /* OSEE_RH850_CORE0_156_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_157_ISR_CAT))
#if (OSEE_RH850_CORE0_157_ISR_CAT == 1)
_osEE_rh850_core0_ei157:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_157_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei157, .-_osEE_rh850_core0_ei157
#else
_osEE_rh850_core0_ei157:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_157_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei157, .-_osEE_rh850_core0_ei157
#endif
#endif /* OSEE_RH850_CORE0_157_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_158_ISR_CAT))
#if (OSEE_RH850_CORE0_158_ISR_CAT == 1)
_osEE_rh850_core0_ei158:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_158_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei158, .-_osEE_rh850_core0_ei158
#else
_osEE_rh850_core0_ei158:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_158_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei158, .-_osEE_rh850_core0_ei158
#endif
#endif /* OSEE_RH850_CORE0_158_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_159_ISR_CAT))
#if (OSEE_RH850_CORE0_159_ISR_CAT == 1)
_osEE_rh850_core0_ei159:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_159_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei159, .-_osEE_rh850_core0_ei159
#else
_osEE_rh850_core0_ei159:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_159_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei159, .-_osEE_rh850_core0_ei159
#endif
#endif /* OSEE_RH850_CORE0_159_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_160_ISR_CAT))
#if (OSEE_RH850_CORE0_160_ISR_CAT == 1)
_osEE_rh850_core0_ei160:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_160_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei160, .-_osEE_rh850_core0_ei160
#else
_osEE_rh850_core0_ei160:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_160_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei160, .-_osEE_rh850_core0_ei160
#endif
#endif /* OSEE_RH850_CORE0_160_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_161_ISR_CAT))
#if (OSEE_RH850_CORE0_161_ISR_CAT == 1)
_osEE_rh850_core0_ei161:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_161_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei161, .-_osEE_rh850_core0_ei161
#else
_osEE_rh850_core0_ei161:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_161_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei161, .-_osEE_rh850_core0_ei161
#endif
#endif /* OSEE_RH850_CORE0_161_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_162_ISR_CAT))
#if (OSEE_RH850_CORE0_162_ISR_CAT == 1)
_osEE_rh850_core0_ei162:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_162_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei162, .-_osEE_rh850_core0_ei162
#else
_osEE_rh850_core0_ei162:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_162_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei162, .-_osEE_rh850_core0_ei162
#endif
#endif /* OSEE_RH850_CORE0_162_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_163_ISR_CAT))
#if (OSEE_RH850_CORE0_163_ISR_CAT == 1)
_osEE_rh850_core0_ei163:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_163_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei163, .-_osEE_rh850_core0_ei163
#else
_osEE_rh850_core0_ei163:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_163_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei163, .-_osEE_rh850_core0_ei163
#endif
#endif /* OSEE_RH850_CORE0_163_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_164_ISR_CAT))
#if (OSEE_RH850_CORE0_164_ISR_CAT == 1)
_osEE_rh850_core0_ei164:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_164_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei164, .-_osEE_rh850_core0_ei164
#else
_osEE_rh850_core0_ei164:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_164_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei164, .-_osEE_rh850_core0_ei164
#endif
#endif /* OSEE_RH850_CORE0_164_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_165_ISR_CAT))
#if (OSEE_RH850_CORE0_165_ISR_CAT == 1)
_osEE_rh850_core0_ei165:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_165_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei165, .-_osEE_rh850_core0_ei165
#else
_osEE_rh850_core0_ei165:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_165_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei165, .-_osEE_rh850_core0_ei165
#endif
#endif /* OSEE_RH850_CORE0_165_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_166_ISR_CAT))
#if (OSEE_RH850_CORE0_166_ISR_CAT == 1)
_osEE_rh850_core0_ei166:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_166_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei166, .-_osEE_rh850_core0_ei166
#else
_osEE_rh850_core0_ei166:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_166_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei166, .-_osEE_rh850_core0_ei166
#endif
#endif /* OSEE_RH850_CORE0_166_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_167_ISR_CAT))
#if (OSEE_RH850_CORE0_167_ISR_CAT == 1)
_osEE_rh850_core0_ei167:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_167_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei167, .-_osEE_rh850_core0_ei167
#else
_osEE_rh850_core0_ei167:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_167_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei167, .-_osEE_rh850_core0_ei167
#endif
#endif /* OSEE_RH850_CORE0_167_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_168_ISR_CAT))
#if (OSEE_RH850_CORE0_168_ISR_CAT == 1)
_osEE_rh850_core0_ei168:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_168_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei168, .-_osEE_rh850_core0_ei168
#else
_osEE_rh850_core0_ei168:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_168_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei168, .-_osEE_rh850_core0_ei168
#endif
#endif /* OSEE_RH850_CORE0_168_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_169_ISR_CAT))
#if (OSEE_RH850_CORE0_169_ISR_CAT == 1)
_osEE_rh850_core0_ei169:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_169_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei169, .-_osEE_rh850_core0_ei169
#else
_osEE_rh850_core0_ei169:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_169_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei169, .-_osEE_rh850_core0_ei169
#endif
#endif /* OSEE_RH850_CORE0_169_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_170_ISR_CAT))
#if (OSEE_RH850_CORE0_170_ISR_CAT == 1)
_osEE_rh850_core0_ei170:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_170_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei170, .-_osEE_rh850_core0_ei170
#else
_osEE_rh850_core0_ei170:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_170_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei170, .-_osEE_rh850_core0_ei170
#endif
#endif /* OSEE_RH850_CORE0_170_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_171_ISR_CAT))
#if (OSEE_RH850_CORE0_171_ISR_CAT == 1)
_osEE_rh850_core0_ei171:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_171_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei171, .-_osEE_rh850_core0_ei171
#else
_osEE_rh850_core0_ei171:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_171_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei171, .-_osEE_rh850_core0_ei171
#endif
#endif /* OSEE_RH850_CORE0_171_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_172_ISR_CAT))
#if (OSEE_RH850_CORE0_172_ISR_CAT == 1)
_osEE_rh850_core0_ei172:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_172_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei172, .-_osEE_rh850_core0_ei172
#else
_osEE_rh850_core0_ei172:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_172_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei172, .-_osEE_rh850_core0_ei172
#endif
#endif /* OSEE_RH850_CORE0_172_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_173_ISR_CAT))
#if (OSEE_RH850_CORE0_173_ISR_CAT == 1)
_osEE_rh850_core0_ei173:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_173_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei173, .-_osEE_rh850_core0_ei173
#else
_osEE_rh850_core0_ei173:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_173_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei173, .-_osEE_rh850_core0_ei173
#endif
#endif /* OSEE_RH850_CORE0_173_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_174_ISR_CAT))
#if (OSEE_RH850_CORE0_174_ISR_CAT == 1)
_osEE_rh850_core0_ei174:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_174_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei174, .-_osEE_rh850_core0_ei174
#else
_osEE_rh850_core0_ei174:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_174_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei174, .-_osEE_rh850_core0_ei174
#endif
#endif /* OSEE_RH850_CORE0_174_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_175_ISR_CAT))
#if (OSEE_RH850_CORE0_175_ISR_CAT == 1)
_osEE_rh850_core0_ei175:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_175_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei175, .-_osEE_rh850_core0_ei175
#else
_osEE_rh850_core0_ei175:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_175_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei175, .-_osEE_rh850_core0_ei175
#endif
#endif /* OSEE_RH850_CORE0_175_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_176_ISR_CAT))
#if (OSEE_RH850_CORE0_176_ISR_CAT == 1)
_osEE_rh850_core0_ei176:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_176_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei176, .-_osEE_rh850_core0_ei176
#else
_osEE_rh850_core0_ei176:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_176_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei176, .-_osEE_rh850_core0_ei176
#endif
#endif /* OSEE_RH850_CORE0_176_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_177_ISR_CAT))
#if (OSEE_RH850_CORE0_177_ISR_CAT == 1)
_osEE_rh850_core0_ei177:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_177_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei177, .-_osEE_rh850_core0_ei177
#else
_osEE_rh850_core0_ei177:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_177_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei177, .-_osEE_rh850_core0_ei177
#endif
#endif /* OSEE_RH850_CORE0_177_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_178_ISR_CAT))
#if (OSEE_RH850_CORE0_178_ISR_CAT == 1)
_osEE_rh850_core0_ei178:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_178_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei178, .-_osEE_rh850_core0_ei178
#else
_osEE_rh850_core0_ei178:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_178_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei178, .-_osEE_rh850_core0_ei178
#endif
#endif /* OSEE_RH850_CORE0_178_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_179_ISR_CAT))
#if (OSEE_RH850_CORE0_179_ISR_CAT == 1)
_osEE_rh850_core0_ei179:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_179_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei179, .-_osEE_rh850_core0_ei179
#else
_osEE_rh850_core0_ei179:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_179_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei179, .-_osEE_rh850_core0_ei179
#endif
#endif /* OSEE_RH850_CORE0_179_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_180_ISR_CAT))
#if (OSEE_RH850_CORE0_180_ISR_CAT == 1)
_osEE_rh850_core0_ei180:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_180_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei180, .-_osEE_rh850_core0_ei180
#else
_osEE_rh850_core0_ei180:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_180_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei180, .-_osEE_rh850_core0_ei180
#endif
#endif /* OSEE_RH850_CORE0_180_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_181_ISR_CAT))
#if (OSEE_RH850_CORE0_181_ISR_CAT == 1)
_osEE_rh850_core0_ei181:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_181_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei181, .-_osEE_rh850_core0_ei181
#else
_osEE_rh850_core0_ei181:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_181_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei181, .-_osEE_rh850_core0_ei181
#endif
#endif /* OSEE_RH850_CORE0_181_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_182_ISR_CAT))
#if (OSEE_RH850_CORE0_182_ISR_CAT == 1)
_osEE_rh850_core0_ei182:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_182_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei182, .-_osEE_rh850_core0_ei182
#else
_osEE_rh850_core0_ei182:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_182_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei182, .-_osEE_rh850_core0_ei182
#endif
#endif /* OSEE_RH850_CORE0_182_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_183_ISR_CAT))
#if (OSEE_RH850_CORE0_183_ISR_CAT == 1)
_osEE_rh850_core0_ei183:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_183_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei183, .-_osEE_rh850_core0_ei183
#else
_osEE_rh850_core0_ei183:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_183_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei183, .-_osEE_rh850_core0_ei183
#endif
#endif /* OSEE_RH850_CORE0_183_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_184_ISR_CAT))
#if (OSEE_RH850_CORE0_184_ISR_CAT == 1)
_osEE_rh850_core0_ei184:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_184_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei184, .-_osEE_rh850_core0_ei184
#else
_osEE_rh850_core0_ei184:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_184_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei184, .-_osEE_rh850_core0_ei184
#endif
#endif /* OSEE_RH850_CORE0_184_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_185_ISR_CAT))
#if (OSEE_RH850_CORE0_185_ISR_CAT == 1)
_osEE_rh850_core0_ei185:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_185_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei185, .-_osEE_rh850_core0_ei185
#else
_osEE_rh850_core0_ei185:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_185_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei185, .-_osEE_rh850_core0_ei185
#endif
#endif /* OSEE_RH850_CORE0_185_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_186_ISR_CAT))
#if (OSEE_RH850_CORE0_186_ISR_CAT == 1)
_osEE_rh850_core0_ei186:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_186_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei186, .-_osEE_rh850_core0_ei186
#else
_osEE_rh850_core0_ei186:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_186_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei186, .-_osEE_rh850_core0_ei186
#endif
#endif /* OSEE_RH850_CORE0_186_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_187_ISR_CAT))
#if (OSEE_RH850_CORE0_187_ISR_CAT == 1)
_osEE_rh850_core0_ei187:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_187_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei187, .-_osEE_rh850_core0_ei187
#else
_osEE_rh850_core0_ei187:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_187_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei187, .-_osEE_rh850_core0_ei187
#endif
#endif /* OSEE_RH850_CORE0_187_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_188_ISR_CAT))
#if (OSEE_RH850_CORE0_188_ISR_CAT == 1)
_osEE_rh850_core0_ei188:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_188_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei188, .-_osEE_rh850_core0_ei188
#else
_osEE_rh850_core0_ei188:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_188_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei188, .-_osEE_rh850_core0_ei188
#endif
#endif /* OSEE_RH850_CORE0_188_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_189_ISR_CAT))
#if (OSEE_RH850_CORE0_189_ISR_CAT == 1)
_osEE_rh850_core0_ei189:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_189_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei189, .-_osEE_rh850_core0_ei189
#else
_osEE_rh850_core0_ei189:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_189_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei189, .-_osEE_rh850_core0_ei189
#endif
#endif /* OSEE_RH850_CORE0_189_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_190_ISR_CAT))
#if (OSEE_RH850_CORE0_190_ISR_CAT == 1)
_osEE_rh850_core0_ei190:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_190_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei190, .-_osEE_rh850_core0_ei190
#else
_osEE_rh850_core0_ei190:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_190_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei190, .-_osEE_rh850_core0_ei190
#endif
#endif /* OSEE_RH850_CORE0_190_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_191_ISR_CAT))
#if (OSEE_RH850_CORE0_191_ISR_CAT == 1)
_osEE_rh850_core0_ei191:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_191_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei191, .-_osEE_rh850_core0_ei191
#else
_osEE_rh850_core0_ei191:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_191_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei191, .-_osEE_rh850_core0_ei191
#endif
#endif /* OSEE_RH850_CORE0_191_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_192_ISR_CAT))
#if (OSEE_RH850_CORE0_192_ISR_CAT == 1)
_osEE_rh850_core0_ei192:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_192_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei192, .-_osEE_rh850_core0_ei192
#else
_osEE_rh850_core0_ei192:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_192_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei192, .-_osEE_rh850_core0_ei192
#endif
#endif /* OSEE_RH850_CORE0_192_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_193_ISR_CAT))
#if (OSEE_RH850_CORE0_193_ISR_CAT == 1)
_osEE_rh850_core0_ei193:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_193_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei193, .-_osEE_rh850_core0_ei193
#else
_osEE_rh850_core0_ei193:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_193_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei193, .-_osEE_rh850_core0_ei193
#endif
#endif /* OSEE_RH850_CORE0_193_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_194_ISR_CAT))
#if (OSEE_RH850_CORE0_194_ISR_CAT == 1)
_osEE_rh850_core0_ei194:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_194_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei194, .-_osEE_rh850_core0_ei194
#else
_osEE_rh850_core0_ei194:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_194_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei194, .-_osEE_rh850_core0_ei194
#endif
#endif /* OSEE_RH850_CORE0_194_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_195_ISR_CAT))
#if (OSEE_RH850_CORE0_195_ISR_CAT == 1)
_osEE_rh850_core0_ei195:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_195_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei195, .-_osEE_rh850_core0_ei195
#else
_osEE_rh850_core0_ei195:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_195_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei195, .-_osEE_rh850_core0_ei195
#endif
#endif /* OSEE_RH850_CORE0_195_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_196_ISR_CAT))
#if (OSEE_RH850_CORE0_196_ISR_CAT == 1)
_osEE_rh850_core0_ei196:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_196_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei196, .-_osEE_rh850_core0_ei196
#else
_osEE_rh850_core0_ei196:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_196_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei196, .-_osEE_rh850_core0_ei196
#endif
#endif /* OSEE_RH850_CORE0_196_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_197_ISR_CAT))
#if (OSEE_RH850_CORE0_197_ISR_CAT == 1)
_osEE_rh850_core0_ei197:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_197_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei197, .-_osEE_rh850_core0_ei197
#else
_osEE_rh850_core0_ei197:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_197_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei197, .-_osEE_rh850_core0_ei197
#endif
#endif /* OSEE_RH850_CORE0_197_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_198_ISR_CAT))
#if (OSEE_RH850_CORE0_198_ISR_CAT == 1)
_osEE_rh850_core0_ei198:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_198_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei198, .-_osEE_rh850_core0_ei198
#else
_osEE_rh850_core0_ei198:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_198_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei198, .-_osEE_rh850_core0_ei198
#endif
#endif /* OSEE_RH850_CORE0_198_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_199_ISR_CAT))
#if (OSEE_RH850_CORE0_199_ISR_CAT == 1)
_osEE_rh850_core0_ei199:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_199_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei199, .-_osEE_rh850_core0_ei199
#else
_osEE_rh850_core0_ei199:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_199_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei199, .-_osEE_rh850_core0_ei199
#endif
#endif /* OSEE_RH850_CORE0_199_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_200_ISR_CAT))
#if (OSEE_RH850_CORE0_200_ISR_CAT == 1)
_osEE_rh850_core0_ei200:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_200_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei200, .-_osEE_rh850_core0_ei200
#else
_osEE_rh850_core0_ei200:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_200_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei200, .-_osEE_rh850_core0_ei200
#endif
#endif /* OSEE_RH850_CORE0_200_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_201_ISR_CAT))
#if (OSEE_RH850_CORE0_201_ISR_CAT == 1)
_osEE_rh850_core0_ei201:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_201_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei201, .-_osEE_rh850_core0_ei201
#else
_osEE_rh850_core0_ei201:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_201_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei201, .-_osEE_rh850_core0_ei201
#endif
#endif /* OSEE_RH850_CORE0_201_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_202_ISR_CAT))
#if (OSEE_RH850_CORE0_202_ISR_CAT == 1)
_osEE_rh850_core0_ei202:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_202_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei202, .-_osEE_rh850_core0_ei202
#else
_osEE_rh850_core0_ei202:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_202_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei202, .-_osEE_rh850_core0_ei202
#endif
#endif /* OSEE_RH850_CORE0_202_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_203_ISR_CAT))
#if (OSEE_RH850_CORE0_203_ISR_CAT == 1)
_osEE_rh850_core0_ei203:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_203_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei203, .-_osEE_rh850_core0_ei203
#else
_osEE_rh850_core0_ei203:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_203_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei203, .-_osEE_rh850_core0_ei203
#endif
#endif /* OSEE_RH850_CORE0_203_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_204_ISR_CAT))
#if (OSEE_RH850_CORE0_204_ISR_CAT == 1)
_osEE_rh850_core0_ei204:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_204_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei204, .-_osEE_rh850_core0_ei204
#else
_osEE_rh850_core0_ei204:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_204_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei204, .-_osEE_rh850_core0_ei204
#endif
#endif /* OSEE_RH850_CORE0_204_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_205_ISR_CAT))
#if (OSEE_RH850_CORE0_205_ISR_CAT == 1)
_osEE_rh850_core0_ei205:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_205_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei205, .-_osEE_rh850_core0_ei205
#else
_osEE_rh850_core0_ei205:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_205_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei205, .-_osEE_rh850_core0_ei205
#endif
#endif /* OSEE_RH850_CORE0_205_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_206_ISR_CAT))
#if (OSEE_RH850_CORE0_206_ISR_CAT == 1)
_osEE_rh850_core0_ei206:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_206_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei206, .-_osEE_rh850_core0_ei206
#else
_osEE_rh850_core0_ei206:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_206_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei206, .-_osEE_rh850_core0_ei206
#endif
#endif /* OSEE_RH850_CORE0_206_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_207_ISR_CAT))
#if (OSEE_RH850_CORE0_207_ISR_CAT == 1)
_osEE_rh850_core0_ei207:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_207_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei207, .-_osEE_rh850_core0_ei207
#else
_osEE_rh850_core0_ei207:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_207_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei207, .-_osEE_rh850_core0_ei207
#endif
#endif /* OSEE_RH850_CORE0_207_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_208_ISR_CAT))
#if (OSEE_RH850_CORE0_208_ISR_CAT == 1)
_osEE_rh850_core0_ei208:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_208_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei208, .-_osEE_rh850_core0_ei208
#else
_osEE_rh850_core0_ei208:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_208_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei208, .-_osEE_rh850_core0_ei208
#endif
#endif /* OSEE_RH850_CORE0_208_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_209_ISR_CAT))
#if (OSEE_RH850_CORE0_209_ISR_CAT == 1)
_osEE_rh850_core0_ei209:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_209_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei209, .-_osEE_rh850_core0_ei209
#else
_osEE_rh850_core0_ei209:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_209_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei209, .-_osEE_rh850_core0_ei209
#endif
#endif /* OSEE_RH850_CORE0_209_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_210_ISR_CAT))
#if (OSEE_RH850_CORE0_210_ISR_CAT == 1)
_osEE_rh850_core0_ei210:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_210_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei210, .-_osEE_rh850_core0_ei210
#else
_osEE_rh850_core0_ei210:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_210_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei210, .-_osEE_rh850_core0_ei210
#endif
#endif /* OSEE_RH850_CORE0_210_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_211_ISR_CAT))
#if (OSEE_RH850_CORE0_211_ISR_CAT == 1)
_osEE_rh850_core0_ei211:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_211_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei211, .-_osEE_rh850_core0_ei211
#else
_osEE_rh850_core0_ei211:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_211_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei211, .-_osEE_rh850_core0_ei211
#endif
#endif /* OSEE_RH850_CORE0_211_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_212_ISR_CAT))
#if (OSEE_RH850_CORE0_212_ISR_CAT == 1)
_osEE_rh850_core0_ei212:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_212_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei212, .-_osEE_rh850_core0_ei212
#else
_osEE_rh850_core0_ei212:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_212_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei212, .-_osEE_rh850_core0_ei212
#endif
#endif /* OSEE_RH850_CORE0_212_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_213_ISR_CAT))
#if (OSEE_RH850_CORE0_213_ISR_CAT == 1)
_osEE_rh850_core0_ei213:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_213_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei213, .-_osEE_rh850_core0_ei213
#else
_osEE_rh850_core0_ei213:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_213_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei213, .-_osEE_rh850_core0_ei213
#endif
#endif /* OSEE_RH850_CORE0_213_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_214_ISR_CAT))
#if (OSEE_RH850_CORE0_214_ISR_CAT == 1)
_osEE_rh850_core0_ei214:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_214_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei214, .-_osEE_rh850_core0_ei214
#else
_osEE_rh850_core0_ei214:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_214_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei214, .-_osEE_rh850_core0_ei214
#endif
#endif /* OSEE_RH850_CORE0_214_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_215_ISR_CAT))
#if (OSEE_RH850_CORE0_215_ISR_CAT == 1)
_osEE_rh850_core0_ei215:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_215_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei215, .-_osEE_rh850_core0_ei215
#else
_osEE_rh850_core0_ei215:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_215_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei215, .-_osEE_rh850_core0_ei215
#endif
#endif /* OSEE_RH850_CORE0_215_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_216_ISR_CAT))
#if (OSEE_RH850_CORE0_216_ISR_CAT == 1)
_osEE_rh850_core0_ei216:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_216_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei216, .-_osEE_rh850_core0_ei216
#else
_osEE_rh850_core0_ei216:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_216_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei216, .-_osEE_rh850_core0_ei216
#endif
#endif /* OSEE_RH850_CORE0_216_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_217_ISR_CAT))
#if (OSEE_RH850_CORE0_217_ISR_CAT == 1)
_osEE_rh850_core0_ei217:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_217_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei217, .-_osEE_rh850_core0_ei217
#else
_osEE_rh850_core0_ei217:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_217_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei217, .-_osEE_rh850_core0_ei217
#endif
#endif /* OSEE_RH850_CORE0_217_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_218_ISR_CAT))
#if (OSEE_RH850_CORE0_218_ISR_CAT == 1)
_osEE_rh850_core0_ei218:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_218_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei218, .-_osEE_rh850_core0_ei218
#else
_osEE_rh850_core0_ei218:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_218_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei218, .-_osEE_rh850_core0_ei218
#endif
#endif /* OSEE_RH850_CORE0_218_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_219_ISR_CAT))
#if (OSEE_RH850_CORE0_219_ISR_CAT == 1)
_osEE_rh850_core0_ei219:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_219_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei219, .-_osEE_rh850_core0_ei219
#else
_osEE_rh850_core0_ei219:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_219_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei219, .-_osEE_rh850_core0_ei219
#endif
#endif /* OSEE_RH850_CORE0_219_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_220_ISR_CAT))
#if (OSEE_RH850_CORE0_220_ISR_CAT == 1)
_osEE_rh850_core0_ei220:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_220_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei220, .-_osEE_rh850_core0_ei220
#else
_osEE_rh850_core0_ei220:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_220_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei220, .-_osEE_rh850_core0_ei220
#endif
#endif /* OSEE_RH850_CORE0_220_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_221_ISR_CAT))
#if (OSEE_RH850_CORE0_221_ISR_CAT == 1)
_osEE_rh850_core0_ei221:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_221_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei221, .-_osEE_rh850_core0_ei221
#else
_osEE_rh850_core0_ei221:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_221_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei221, .-_osEE_rh850_core0_ei221
#endif
#endif /* OSEE_RH850_CORE0_221_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_222_ISR_CAT))
#if (OSEE_RH850_CORE0_222_ISR_CAT == 1)
_osEE_rh850_core0_ei222:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_222_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei222, .-_osEE_rh850_core0_ei222
#else
_osEE_rh850_core0_ei222:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_222_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei222, .-_osEE_rh850_core0_ei222
#endif
#endif /* OSEE_RH850_CORE0_222_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_223_ISR_CAT))
#if (OSEE_RH850_CORE0_223_ISR_CAT == 1)
_osEE_rh850_core0_ei223:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_223_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei223, .-_osEE_rh850_core0_ei223
#else
_osEE_rh850_core0_ei223:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_223_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei223, .-_osEE_rh850_core0_ei223
#endif
#endif /* OSEE_RH850_CORE0_223_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_224_ISR_CAT))
#if (OSEE_RH850_CORE0_224_ISR_CAT == 1)
_osEE_rh850_core0_ei224:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_224_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei224, .-_osEE_rh850_core0_ei224
#else
_osEE_rh850_core0_ei224:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_224_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei224, .-_osEE_rh850_core0_ei224
#endif
#endif /* OSEE_RH850_CORE0_224_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_225_ISR_CAT))
#if (OSEE_RH850_CORE0_225_ISR_CAT == 1)
_osEE_rh850_core0_ei225:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_225_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei225, .-_osEE_rh850_core0_ei225
#else
_osEE_rh850_core0_ei225:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_225_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei225, .-_osEE_rh850_core0_ei225
#endif
#endif /* OSEE_RH850_CORE0_225_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_226_ISR_CAT))
#if (OSEE_RH850_CORE0_226_ISR_CAT == 1)
_osEE_rh850_core0_ei226:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_226_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei226, .-_osEE_rh850_core0_ei226
#else
_osEE_rh850_core0_ei226:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_226_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei226, .-_osEE_rh850_core0_ei226
#endif
#endif /* OSEE_RH850_CORE0_226_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_227_ISR_CAT))
#if (OSEE_RH850_CORE0_227_ISR_CAT == 1)
_osEE_rh850_core0_ei227:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_227_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei227, .-_osEE_rh850_core0_ei227
#else
_osEE_rh850_core0_ei227:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_227_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei227, .-_osEE_rh850_core0_ei227
#endif
#endif /* OSEE_RH850_CORE0_227_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_228_ISR_CAT))
#if (OSEE_RH850_CORE0_228_ISR_CAT == 1)
_osEE_rh850_core0_ei228:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_228_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei228, .-_osEE_rh850_core0_ei228
#else
_osEE_rh850_core0_ei228:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_228_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei228, .-_osEE_rh850_core0_ei228
#endif
#endif /* OSEE_RH850_CORE0_228_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_229_ISR_CAT))
#if (OSEE_RH850_CORE0_229_ISR_CAT == 1)
_osEE_rh850_core0_ei229:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_229_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei229, .-_osEE_rh850_core0_ei229
#else
_osEE_rh850_core0_ei229:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_229_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei229, .-_osEE_rh850_core0_ei229
#endif
#endif /* OSEE_RH850_CORE0_229_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_230_ISR_CAT))
#if (OSEE_RH850_CORE0_230_ISR_CAT == 1)
_osEE_rh850_core0_ei230:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_230_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei230, .-_osEE_rh850_core0_ei230
#else
_osEE_rh850_core0_ei230:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_230_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei230, .-_osEE_rh850_core0_ei230
#endif
#endif /* OSEE_RH850_CORE0_230_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_231_ISR_CAT))
#if (OSEE_RH850_CORE0_231_ISR_CAT == 1)
_osEE_rh850_core0_ei231:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_231_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei231, .-_osEE_rh850_core0_ei231
#else
_osEE_rh850_core0_ei231:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_231_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei231, .-_osEE_rh850_core0_ei231
#endif
#endif /* OSEE_RH850_CORE0_231_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_232_ISR_CAT))
#if (OSEE_RH850_CORE0_232_ISR_CAT == 1)
_osEE_rh850_core0_ei232:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_232_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei232, .-_osEE_rh850_core0_ei232
#else
_osEE_rh850_core0_ei232:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_232_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei232, .-_osEE_rh850_core0_ei232
#endif
#endif /* OSEE_RH850_CORE0_232_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_233_ISR_CAT))
#if (OSEE_RH850_CORE0_233_ISR_CAT == 1)
_osEE_rh850_core0_ei233:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_233_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei233, .-_osEE_rh850_core0_ei233
#else
_osEE_rh850_core0_ei233:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_233_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei233, .-_osEE_rh850_core0_ei233
#endif
#endif /* OSEE_RH850_CORE0_233_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_234_ISR_CAT))
#if (OSEE_RH850_CORE0_234_ISR_CAT == 1)
_osEE_rh850_core0_ei234:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_234_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei234, .-_osEE_rh850_core0_ei234
#else
_osEE_rh850_core0_ei234:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_234_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei234, .-_osEE_rh850_core0_ei234
#endif
#endif /* OSEE_RH850_CORE0_234_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_235_ISR_CAT))
#if (OSEE_RH850_CORE0_235_ISR_CAT == 1)
_osEE_rh850_core0_ei235:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_235_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei235, .-_osEE_rh850_core0_ei235
#else
_osEE_rh850_core0_ei235:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_235_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei235, .-_osEE_rh850_core0_ei235
#endif
#endif /* OSEE_RH850_CORE0_235_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_236_ISR_CAT))
#if (OSEE_RH850_CORE0_236_ISR_CAT == 1)
_osEE_rh850_core0_ei236:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_236_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei236, .-_osEE_rh850_core0_ei236
#else
_osEE_rh850_core0_ei236:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_236_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei236, .-_osEE_rh850_core0_ei236
#endif
#endif /* OSEE_RH850_CORE0_236_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_237_ISR_CAT))
#if (OSEE_RH850_CORE0_237_ISR_CAT == 1)
_osEE_rh850_core0_ei237:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_237_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei237, .-_osEE_rh850_core0_ei237
#else
_osEE_rh850_core0_ei237:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_237_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei237, .-_osEE_rh850_core0_ei237
#endif
#endif /* OSEE_RH850_CORE0_237_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_238_ISR_CAT))
#if (OSEE_RH850_CORE0_238_ISR_CAT == 1)
_osEE_rh850_core0_ei238:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_238_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei238, .-_osEE_rh850_core0_ei238
#else
_osEE_rh850_core0_ei238:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_238_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei238, .-_osEE_rh850_core0_ei238
#endif
#endif /* OSEE_RH850_CORE0_238_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_239_ISR_CAT))
#if (OSEE_RH850_CORE0_239_ISR_CAT == 1)
_osEE_rh850_core0_ei239:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_239_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei239, .-_osEE_rh850_core0_ei239
#else
_osEE_rh850_core0_ei239:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_239_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei239, .-_osEE_rh850_core0_ei239
#endif
#endif /* OSEE_RH850_CORE0_239_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_240_ISR_CAT))
#if (OSEE_RH850_CORE0_240_ISR_CAT == 1)
_osEE_rh850_core0_ei240:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_240_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei240, .-_osEE_rh850_core0_ei240
#else
_osEE_rh850_core0_ei240:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_240_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei240, .-_osEE_rh850_core0_ei240
#endif
#endif /* OSEE_RH850_CORE0_240_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_241_ISR_CAT))
#if (OSEE_RH850_CORE0_241_ISR_CAT == 1)
_osEE_rh850_core0_ei241:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_241_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei241, .-_osEE_rh850_core0_ei241
#else
_osEE_rh850_core0_ei241:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_241_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei241, .-_osEE_rh850_core0_ei241
#endif
#endif /* OSEE_RH850_CORE0_241_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_242_ISR_CAT))
#if (OSEE_RH850_CORE0_242_ISR_CAT == 1)
_osEE_rh850_core0_ei242:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_242_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei242, .-_osEE_rh850_core0_ei242
#else
_osEE_rh850_core0_ei242:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_242_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei242, .-_osEE_rh850_core0_ei242
#endif
#endif /* OSEE_RH850_CORE0_242_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_243_ISR_CAT))
#if (OSEE_RH850_CORE0_243_ISR_CAT == 1)
_osEE_rh850_core0_ei243:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_243_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei243, .-_osEE_rh850_core0_ei243
#else
_osEE_rh850_core0_ei243:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_243_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei243, .-_osEE_rh850_core0_ei243
#endif
#endif /* OSEE_RH850_CORE0_243_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_244_ISR_CAT))
#if (OSEE_RH850_CORE0_244_ISR_CAT == 1)
_osEE_rh850_core0_ei244:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_244_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei244, .-_osEE_rh850_core0_ei244
#else
_osEE_rh850_core0_ei244:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_244_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei244, .-_osEE_rh850_core0_ei244
#endif
#endif /* OSEE_RH850_CORE0_244_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_245_ISR_CAT))
#if (OSEE_RH850_CORE0_245_ISR_CAT == 1)
_osEE_rh850_core0_ei245:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_245_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei245, .-_osEE_rh850_core0_ei245
#else
_osEE_rh850_core0_ei245:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_245_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei245, .-_osEE_rh850_core0_ei245
#endif
#endif /* OSEE_RH850_CORE0_245_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_246_ISR_CAT))
#if (OSEE_RH850_CORE0_246_ISR_CAT == 1)
_osEE_rh850_core0_ei246:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_246_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei246, .-_osEE_rh850_core0_ei246
#else
_osEE_rh850_core0_ei246:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_246_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei246, .-_osEE_rh850_core0_ei246
#endif
#endif /* OSEE_RH850_CORE0_246_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_247_ISR_CAT))
#if (OSEE_RH850_CORE0_247_ISR_CAT == 1)
_osEE_rh850_core0_ei247:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_247_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei247, .-_osEE_rh850_core0_ei247
#else
_osEE_rh850_core0_ei247:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_247_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei247, .-_osEE_rh850_core0_ei247
#endif
#endif /* OSEE_RH850_CORE0_247_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_248_ISR_CAT))
#if (OSEE_RH850_CORE0_248_ISR_CAT == 1)
_osEE_rh850_core0_ei248:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_248_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei248, .-_osEE_rh850_core0_ei248
#else
_osEE_rh850_core0_ei248:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_248_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei248, .-_osEE_rh850_core0_ei248
#endif
#endif /* OSEE_RH850_CORE0_248_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_249_ISR_CAT))
#if (OSEE_RH850_CORE0_249_ISR_CAT == 1)
_osEE_rh850_core0_ei249:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_249_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei249, .-_osEE_rh850_core0_ei249
#else
_osEE_rh850_core0_ei249:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_249_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei249, .-_osEE_rh850_core0_ei249
#endif
#endif /* OSEE_RH850_CORE0_249_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_250_ISR_CAT))
#if (OSEE_RH850_CORE0_250_ISR_CAT == 1)
_osEE_rh850_core0_ei250:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_250_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei250, .-_osEE_rh850_core0_ei250
#else
_osEE_rh850_core0_ei250:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_250_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei250, .-_osEE_rh850_core0_ei250
#endif
#endif /* OSEE_RH850_CORE0_250_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_251_ISR_CAT))
#if (OSEE_RH850_CORE0_251_ISR_CAT == 1)
_osEE_rh850_core0_ei251:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_251_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei251, .-_osEE_rh850_core0_ei251
#else
_osEE_rh850_core0_ei251:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_251_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei251, .-_osEE_rh850_core0_ei251
#endif
#endif /* OSEE_RH850_CORE0_251_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_252_ISR_CAT))
#if (OSEE_RH850_CORE0_252_ISR_CAT == 1)
_osEE_rh850_core0_ei252:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_252_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei252, .-_osEE_rh850_core0_ei252
#else
_osEE_rh850_core0_ei252:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_252_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei252, .-_osEE_rh850_core0_ei252
#endif
#endif /* OSEE_RH850_CORE0_252_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_253_ISR_CAT))
#if (OSEE_RH850_CORE0_253_ISR_CAT == 1)
_osEE_rh850_core0_ei253:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_253_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei253, .-_osEE_rh850_core0_ei253
#else
_osEE_rh850_core0_ei253:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_253_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei253, .-_osEE_rh850_core0_ei253
#endif
#endif /* OSEE_RH850_CORE0_253_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_254_ISR_CAT))
#if (OSEE_RH850_CORE0_254_ISR_CAT == 1)
_osEE_rh850_core0_ei254:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_254_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei254, .-_osEE_rh850_core0_ei254
#else
_osEE_rh850_core0_ei254:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_254_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei254, .-_osEE_rh850_core0_ei254
#endif
#endif /* OSEE_RH850_CORE0_254_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_255_ISR_CAT))
#if (OSEE_RH850_CORE0_255_ISR_CAT == 1)
_osEE_rh850_core0_ei255:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_255_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei255, .-_osEE_rh850_core0_ei255
#else
_osEE_rh850_core0_ei255:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_255_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei255, .-_osEE_rh850_core0_ei255
#endif
#endif /* OSEE_RH850_CORE0_255_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_256_ISR_CAT))
#if (OSEE_RH850_CORE0_256_ISR_CAT == 1)
_osEE_rh850_core0_ei256:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_256_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei256, .-_osEE_rh850_core0_ei256
#else
_osEE_rh850_core0_ei256:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_256_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei256, .-_osEE_rh850_core0_ei256
#endif
#endif /* OSEE_RH850_CORE0_256_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_257_ISR_CAT))
#if (OSEE_RH850_CORE0_257_ISR_CAT == 1)
_osEE_rh850_core0_ei257:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_257_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei257, .-_osEE_rh850_core0_ei257
#else
_osEE_rh850_core0_ei257:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_257_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei257, .-_osEE_rh850_core0_ei257
#endif
#endif /* OSEE_RH850_CORE0_257_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_258_ISR_CAT))
#if (OSEE_RH850_CORE0_258_ISR_CAT == 1)
_osEE_rh850_core0_ei258:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_258_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei258, .-_osEE_rh850_core0_ei258
#else
_osEE_rh850_core0_ei258:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_258_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei258, .-_osEE_rh850_core0_ei258
#endif
#endif /* OSEE_RH850_CORE0_258_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_259_ISR_CAT))
#if (OSEE_RH850_CORE0_259_ISR_CAT == 1)
_osEE_rh850_core0_ei259:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_259_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei259, .-_osEE_rh850_core0_ei259
#else
_osEE_rh850_core0_ei259:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_259_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei259, .-_osEE_rh850_core0_ei259
#endif
#endif /* OSEE_RH850_CORE0_259_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_260_ISR_CAT))
#if (OSEE_RH850_CORE0_260_ISR_CAT == 1)
_osEE_rh850_core0_ei260:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_260_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei260, .-_osEE_rh850_core0_ei260
#else
_osEE_rh850_core0_ei260:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_260_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei260, .-_osEE_rh850_core0_ei260
#endif
#endif /* OSEE_RH850_CORE0_260_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_261_ISR_CAT))
#if (OSEE_RH850_CORE0_261_ISR_CAT == 1)
_osEE_rh850_core0_ei261:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_261_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei261, .-_osEE_rh850_core0_ei261
#else
_osEE_rh850_core0_ei261:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_261_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei261, .-_osEE_rh850_core0_ei261
#endif
#endif /* OSEE_RH850_CORE0_261_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_262_ISR_CAT))
#if (OSEE_RH850_CORE0_262_ISR_CAT == 1)
_osEE_rh850_core0_ei262:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_262_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei262, .-_osEE_rh850_core0_ei262
#else
_osEE_rh850_core0_ei262:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_262_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei262, .-_osEE_rh850_core0_ei262
#endif
#endif /* OSEE_RH850_CORE0_262_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_263_ISR_CAT))
#if (OSEE_RH850_CORE0_263_ISR_CAT == 1)
_osEE_rh850_core0_ei263:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_263_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei263, .-_osEE_rh850_core0_ei263
#else
_osEE_rh850_core0_ei263:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_263_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei263, .-_osEE_rh850_core0_ei263
#endif
#endif /* OSEE_RH850_CORE0_263_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_264_ISR_CAT))
#if (OSEE_RH850_CORE0_264_ISR_CAT == 1)
_osEE_rh850_core0_ei264:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_264_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei264, .-_osEE_rh850_core0_ei264
#else
_osEE_rh850_core0_ei264:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_264_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei264, .-_osEE_rh850_core0_ei264
#endif
#endif /* OSEE_RH850_CORE0_264_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_265_ISR_CAT))
#if (OSEE_RH850_CORE0_265_ISR_CAT == 1)
_osEE_rh850_core0_ei265:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_265_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei265, .-_osEE_rh850_core0_ei265
#else
_osEE_rh850_core0_ei265:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_265_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei265, .-_osEE_rh850_core0_ei265
#endif
#endif /* OSEE_RH850_CORE0_265_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_266_ISR_CAT))
#if (OSEE_RH850_CORE0_266_ISR_CAT == 1)
_osEE_rh850_core0_ei266:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_266_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei266, .-_osEE_rh850_core0_ei266
#else
_osEE_rh850_core0_ei266:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_266_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei266, .-_osEE_rh850_core0_ei266
#endif
#endif /* OSEE_RH850_CORE0_266_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_267_ISR_CAT))
#if (OSEE_RH850_CORE0_267_ISR_CAT == 1)
_osEE_rh850_core0_ei267:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_267_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei267, .-_osEE_rh850_core0_ei267
#else
_osEE_rh850_core0_ei267:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_267_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei267, .-_osEE_rh850_core0_ei267
#endif
#endif /* OSEE_RH850_CORE0_267_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_268_ISR_CAT))
#if (OSEE_RH850_CORE0_268_ISR_CAT == 1)
_osEE_rh850_core0_ei268:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_268_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei268, .-_osEE_rh850_core0_ei268
#else
_osEE_rh850_core0_ei268:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_268_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei268, .-_osEE_rh850_core0_ei268
#endif
#endif /* OSEE_RH850_CORE0_268_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_269_ISR_CAT))
#if (OSEE_RH850_CORE0_269_ISR_CAT == 1)
_osEE_rh850_core0_ei269:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_269_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei269, .-_osEE_rh850_core0_ei269
#else
_osEE_rh850_core0_ei269:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_269_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei269, .-_osEE_rh850_core0_ei269
#endif
#endif /* OSEE_RH850_CORE0_269_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_270_ISR_CAT))
#if (OSEE_RH850_CORE0_270_ISR_CAT == 1)
_osEE_rh850_core0_ei270:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_270_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei270, .-_osEE_rh850_core0_ei270
#else
_osEE_rh850_core0_ei270:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_270_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei270, .-_osEE_rh850_core0_ei270
#endif
#endif /* OSEE_RH850_CORE0_270_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_271_ISR_CAT))
#if (OSEE_RH850_CORE0_271_ISR_CAT == 1)
_osEE_rh850_core0_ei271:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_271_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei271, .-_osEE_rh850_core0_ei271
#else
_osEE_rh850_core0_ei271:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_271_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei271, .-_osEE_rh850_core0_ei271
#endif
#endif /* OSEE_RH850_CORE0_271_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_272_ISR_CAT))
#if (OSEE_RH850_CORE0_272_ISR_CAT == 1)
_osEE_rh850_core0_ei272:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_272_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei272, .-_osEE_rh850_core0_ei272
#else
_osEE_rh850_core0_ei272:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_272_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei272, .-_osEE_rh850_core0_ei272
#endif
#endif /* OSEE_RH850_CORE0_272_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_273_ISR_CAT))
#if (OSEE_RH850_CORE0_273_ISR_CAT == 1)
_osEE_rh850_core0_ei273:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_273_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei273, .-_osEE_rh850_core0_ei273
#else
_osEE_rh850_core0_ei273:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_273_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei273, .-_osEE_rh850_core0_ei273
#endif
#endif /* OSEE_RH850_CORE0_273_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_274_ISR_CAT))
#if (OSEE_RH850_CORE0_274_ISR_CAT == 1)
_osEE_rh850_core0_ei274:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_274_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei274, .-_osEE_rh850_core0_ei274
#else
_osEE_rh850_core0_ei274:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_274_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei274, .-_osEE_rh850_core0_ei274
#endif
#endif /* OSEE_RH850_CORE0_274_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_275_ISR_CAT))
#if (OSEE_RH850_CORE0_275_ISR_CAT == 1)
_osEE_rh850_core0_ei275:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_275_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei275, .-_osEE_rh850_core0_ei275
#else
_osEE_rh850_core0_ei275:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_275_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei275, .-_osEE_rh850_core0_ei275
#endif
#endif /* OSEE_RH850_CORE0_275_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_276_ISR_CAT))
#if (OSEE_RH850_CORE0_276_ISR_CAT == 1)
_osEE_rh850_core0_ei276:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_276_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei276, .-_osEE_rh850_core0_ei276
#else
_osEE_rh850_core0_ei276:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_276_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei276, .-_osEE_rh850_core0_ei276
#endif
#endif /* OSEE_RH850_CORE0_276_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_277_ISR_CAT))
#if (OSEE_RH850_CORE0_277_ISR_CAT == 1)
_osEE_rh850_core0_ei277:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_277_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei277, .-_osEE_rh850_core0_ei277
#else
_osEE_rh850_core0_ei277:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_277_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei277, .-_osEE_rh850_core0_ei277
#endif
#endif /* OSEE_RH850_CORE0_277_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_278_ISR_CAT))
#if (OSEE_RH850_CORE0_278_ISR_CAT == 1)
_osEE_rh850_core0_ei278:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_278_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei278, .-_osEE_rh850_core0_ei278
#else
_osEE_rh850_core0_ei278:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_278_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei278, .-_osEE_rh850_core0_ei278
#endif
#endif /* OSEE_RH850_CORE0_278_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_279_ISR_CAT))
#if (OSEE_RH850_CORE0_279_ISR_CAT == 1)
_osEE_rh850_core0_ei279:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_279_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei279, .-_osEE_rh850_core0_ei279
#else
_osEE_rh850_core0_ei279:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_279_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei279, .-_osEE_rh850_core0_ei279
#endif
#endif /* OSEE_RH850_CORE0_279_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_280_ISR_CAT))
#if (OSEE_RH850_CORE0_280_ISR_CAT == 1)
_osEE_rh850_core0_ei280:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_280_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei280, .-_osEE_rh850_core0_ei280
#else
_osEE_rh850_core0_ei280:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_280_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei280, .-_osEE_rh850_core0_ei280
#endif
#endif /* OSEE_RH850_CORE0_280_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_281_ISR_CAT))
#if (OSEE_RH850_CORE0_281_ISR_CAT == 1)
_osEE_rh850_core0_ei281:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_281_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei281, .-_osEE_rh850_core0_ei281
#else
_osEE_rh850_core0_ei281:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_281_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei281, .-_osEE_rh850_core0_ei281
#endif
#endif /* OSEE_RH850_CORE0_281_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_282_ISR_CAT))
#if (OSEE_RH850_CORE0_282_ISR_CAT == 1)
_osEE_rh850_core0_ei282:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_282_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei282, .-_osEE_rh850_core0_ei282
#else
_osEE_rh850_core0_ei282:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_282_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei282, .-_osEE_rh850_core0_ei282
#endif
#endif /* OSEE_RH850_CORE0_282_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_283_ISR_CAT))
#if (OSEE_RH850_CORE0_283_ISR_CAT == 1)
_osEE_rh850_core0_ei283:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_283_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei283, .-_osEE_rh850_core0_ei283
#else
_osEE_rh850_core0_ei283:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_283_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei283, .-_osEE_rh850_core0_ei283
#endif
#endif /* OSEE_RH850_CORE0_283_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_284_ISR_CAT))
#if (OSEE_RH850_CORE0_284_ISR_CAT == 1)
_osEE_rh850_core0_ei284:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_284_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei284, .-_osEE_rh850_core0_ei284
#else
_osEE_rh850_core0_ei284:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_284_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei284, .-_osEE_rh850_core0_ei284
#endif
#endif /* OSEE_RH850_CORE0_284_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_285_ISR_CAT))
#if (OSEE_RH850_CORE0_285_ISR_CAT == 1)
_osEE_rh850_core0_ei285:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_285_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei285, .-_osEE_rh850_core0_ei285
#else
_osEE_rh850_core0_ei285:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_285_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei285, .-_osEE_rh850_core0_ei285
#endif
#endif /* OSEE_RH850_CORE0_285_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_286_ISR_CAT))
#if (OSEE_RH850_CORE0_286_ISR_CAT == 1)
_osEE_rh850_core0_ei286:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_286_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei286, .-_osEE_rh850_core0_ei286
#else
_osEE_rh850_core0_ei286:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_286_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei286, .-_osEE_rh850_core0_ei286
#endif
#endif /* OSEE_RH850_CORE0_286_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_287_ISR_CAT))
#if (OSEE_RH850_CORE0_287_ISR_CAT == 1)
_osEE_rh850_core0_ei287:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_287_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei287, .-_osEE_rh850_core0_ei287
#else
_osEE_rh850_core0_ei287:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_287_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei287, .-_osEE_rh850_core0_ei287
#endif
#endif /* OSEE_RH850_CORE0_287_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_288_ISR_CAT))
#if (OSEE_RH850_CORE0_288_ISR_CAT == 1)
_osEE_rh850_core0_ei288:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_288_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei288, .-_osEE_rh850_core0_ei288
#else
_osEE_rh850_core0_ei288:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_288_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei288, .-_osEE_rh850_core0_ei288
#endif
#endif /* OSEE_RH850_CORE0_288_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_289_ISR_CAT))
#if (OSEE_RH850_CORE0_289_ISR_CAT == 1)
_osEE_rh850_core0_ei289:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_289_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei289, .-_osEE_rh850_core0_ei289
#else
_osEE_rh850_core0_ei289:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_289_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei289, .-_osEE_rh850_core0_ei289
#endif
#endif /* OSEE_RH850_CORE0_289_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_290_ISR_CAT))
#if (OSEE_RH850_CORE0_290_ISR_CAT == 1)
_osEE_rh850_core0_ei290:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_290_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei290, .-_osEE_rh850_core0_ei290
#else
_osEE_rh850_core0_ei290:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_290_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei290, .-_osEE_rh850_core0_ei290
#endif
#endif /* OSEE_RH850_CORE0_290_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_291_ISR_CAT))
#if (OSEE_RH850_CORE0_291_ISR_CAT == 1)
_osEE_rh850_core0_ei291:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_291_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei291, .-_osEE_rh850_core0_ei291
#else
_osEE_rh850_core0_ei291:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_291_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei291, .-_osEE_rh850_core0_ei291
#endif
#endif /* OSEE_RH850_CORE0_291_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_292_ISR_CAT))
#if (OSEE_RH850_CORE0_292_ISR_CAT == 1)
_osEE_rh850_core0_ei292:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_292_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei292, .-_osEE_rh850_core0_ei292
#else
_osEE_rh850_core0_ei292:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_292_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei292, .-_osEE_rh850_core0_ei292
#endif
#endif /* OSEE_RH850_CORE0_292_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_293_ISR_CAT))
#if (OSEE_RH850_CORE0_293_ISR_CAT == 1)
_osEE_rh850_core0_ei293:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_293_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei293, .-_osEE_rh850_core0_ei293
#else
_osEE_rh850_core0_ei293:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_293_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei293, .-_osEE_rh850_core0_ei293
#endif
#endif /* OSEE_RH850_CORE0_293_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_294_ISR_CAT))
#if (OSEE_RH850_CORE0_294_ISR_CAT == 1)
_osEE_rh850_core0_ei294:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_294_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei294, .-_osEE_rh850_core0_ei294
#else
_osEE_rh850_core0_ei294:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_294_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei294, .-_osEE_rh850_core0_ei294
#endif
#endif /* OSEE_RH850_CORE0_294_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_295_ISR_CAT))
#if (OSEE_RH850_CORE0_295_ISR_CAT == 1)
_osEE_rh850_core0_ei295:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_295_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei295, .-_osEE_rh850_core0_ei295
#else
_osEE_rh850_core0_ei295:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_295_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei295, .-_osEE_rh850_core0_ei295
#endif
#endif /* OSEE_RH850_CORE0_295_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_296_ISR_CAT))
#if (OSEE_RH850_CORE0_296_ISR_CAT == 1)
_osEE_rh850_core0_ei296:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_296_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei296, .-_osEE_rh850_core0_ei296
#else
_osEE_rh850_core0_ei296:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_296_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei296, .-_osEE_rh850_core0_ei296
#endif
#endif /* OSEE_RH850_CORE0_296_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_297_ISR_CAT))
#if (OSEE_RH850_CORE0_297_ISR_CAT == 1)
_osEE_rh850_core0_ei297:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_297_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei297, .-_osEE_rh850_core0_ei297
#else
_osEE_rh850_core0_ei297:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_297_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei297, .-_osEE_rh850_core0_ei297
#endif
#endif /* OSEE_RH850_CORE0_297_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_298_ISR_CAT))
#if (OSEE_RH850_CORE0_298_ISR_CAT == 1)
_osEE_rh850_core0_ei298:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_298_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei298, .-_osEE_rh850_core0_ei298
#else
_osEE_rh850_core0_ei298:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_298_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei298, .-_osEE_rh850_core0_ei298
#endif
#endif /* OSEE_RH850_CORE0_298_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_299_ISR_CAT))
#if (OSEE_RH850_CORE0_299_ISR_CAT == 1)
_osEE_rh850_core0_ei299:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_299_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei299, .-_osEE_rh850_core0_ei299
#else
_osEE_rh850_core0_ei299:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_299_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei299, .-_osEE_rh850_core0_ei299
#endif
#endif /* OSEE_RH850_CORE0_299_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_300_ISR_CAT))
#if (OSEE_RH850_CORE0_300_ISR_CAT == 1)
_osEE_rh850_core0_ei300:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_300_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei300, .-_osEE_rh850_core0_ei300
#else
_osEE_rh850_core0_ei300:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_300_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei300, .-_osEE_rh850_core0_ei300
#endif
#endif /* OSEE_RH850_CORE0_300_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_301_ISR_CAT))
#if (OSEE_RH850_CORE0_301_ISR_CAT == 1)
_osEE_rh850_core0_ei301:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_301_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei301, .-_osEE_rh850_core0_ei301
#else
_osEE_rh850_core0_ei301:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_301_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei301, .-_osEE_rh850_core0_ei301
#endif
#endif /* OSEE_RH850_CORE0_301_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_302_ISR_CAT))
#if (OSEE_RH850_CORE0_302_ISR_CAT == 1)
_osEE_rh850_core0_ei302:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_302_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei302, .-_osEE_rh850_core0_ei302
#else
_osEE_rh850_core0_ei302:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_302_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei302, .-_osEE_rh850_core0_ei302
#endif
#endif /* OSEE_RH850_CORE0_302_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_303_ISR_CAT))
#if (OSEE_RH850_CORE0_303_ISR_CAT == 1)
_osEE_rh850_core0_ei303:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_303_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei303, .-_osEE_rh850_core0_ei303
#else
_osEE_rh850_core0_ei303:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_303_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei303, .-_osEE_rh850_core0_ei303
#endif
#endif /* OSEE_RH850_CORE0_303_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_304_ISR_CAT))
#if (OSEE_RH850_CORE0_304_ISR_CAT == 1)
_osEE_rh850_core0_ei304:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_304_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei304, .-_osEE_rh850_core0_ei304
#else
_osEE_rh850_core0_ei304:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_304_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei304, .-_osEE_rh850_core0_ei304
#endif
#endif /* OSEE_RH850_CORE0_304_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_305_ISR_CAT))
#if (OSEE_RH850_CORE0_305_ISR_CAT == 1)
_osEE_rh850_core0_ei305:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_305_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei305, .-_osEE_rh850_core0_ei305
#else
_osEE_rh850_core0_ei305:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_305_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei305, .-_osEE_rh850_core0_ei305
#endif
#endif /* OSEE_RH850_CORE0_305_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_306_ISR_CAT))
#if (OSEE_RH850_CORE0_306_ISR_CAT == 1)
_osEE_rh850_core0_ei306:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_306_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei306, .-_osEE_rh850_core0_ei306
#else
_osEE_rh850_core0_ei306:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_306_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei306, .-_osEE_rh850_core0_ei306
#endif
#endif /* OSEE_RH850_CORE0_306_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_307_ISR_CAT))
#if (OSEE_RH850_CORE0_307_ISR_CAT == 1)
_osEE_rh850_core0_ei307:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_307_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei307, .-_osEE_rh850_core0_ei307
#else
_osEE_rh850_core0_ei307:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_307_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei307, .-_osEE_rh850_core0_ei307
#endif
#endif /* OSEE_RH850_CORE0_307_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_308_ISR_CAT))
#if (OSEE_RH850_CORE0_308_ISR_CAT == 1)
_osEE_rh850_core0_ei308:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_308_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei308, .-_osEE_rh850_core0_ei308
#else
_osEE_rh850_core0_ei308:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_308_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei308, .-_osEE_rh850_core0_ei308
#endif
#endif /* OSEE_RH850_CORE0_308_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_309_ISR_CAT))
#if (OSEE_RH850_CORE0_309_ISR_CAT == 1)
_osEE_rh850_core0_ei309:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_309_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei309, .-_osEE_rh850_core0_ei309
#else
_osEE_rh850_core0_ei309:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_309_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei309, .-_osEE_rh850_core0_ei309
#endif
#endif /* OSEE_RH850_CORE0_309_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_310_ISR_CAT))
#if (OSEE_RH850_CORE0_310_ISR_CAT == 1)
_osEE_rh850_core0_ei310:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_310_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei310, .-_osEE_rh850_core0_ei310
#else
_osEE_rh850_core0_ei310:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_310_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei310, .-_osEE_rh850_core0_ei310
#endif
#endif /* OSEE_RH850_CORE0_310_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_311_ISR_CAT))
#if (OSEE_RH850_CORE0_311_ISR_CAT == 1)
_osEE_rh850_core0_ei311:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_311_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei311, .-_osEE_rh850_core0_ei311
#else
_osEE_rh850_core0_ei311:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_311_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei311, .-_osEE_rh850_core0_ei311
#endif
#endif /* OSEE_RH850_CORE0_311_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_312_ISR_CAT))
#if (OSEE_RH850_CORE0_312_ISR_CAT == 1)
_osEE_rh850_core0_ei312:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_312_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei312, .-_osEE_rh850_core0_ei312
#else
_osEE_rh850_core0_ei312:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_312_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei312, .-_osEE_rh850_core0_ei312
#endif
#endif /* OSEE_RH850_CORE0_312_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_313_ISR_CAT))
#if (OSEE_RH850_CORE0_313_ISR_CAT == 1)
_osEE_rh850_core0_ei313:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_313_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei313, .-_osEE_rh850_core0_ei313
#else
_osEE_rh850_core0_ei313:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_313_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei313, .-_osEE_rh850_core0_ei313
#endif
#endif /* OSEE_RH850_CORE0_313_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_314_ISR_CAT))
#if (OSEE_RH850_CORE0_314_ISR_CAT == 1)
_osEE_rh850_core0_ei314:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_314_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei314, .-_osEE_rh850_core0_ei314
#else
_osEE_rh850_core0_ei314:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_314_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei314, .-_osEE_rh850_core0_ei314
#endif
#endif /* OSEE_RH850_CORE0_314_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_315_ISR_CAT))
#if (OSEE_RH850_CORE0_315_ISR_CAT == 1)
_osEE_rh850_core0_ei315:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_315_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei315, .-_osEE_rh850_core0_ei315
#else
_osEE_rh850_core0_ei315:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_315_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei315, .-_osEE_rh850_core0_ei315
#endif
#endif /* OSEE_RH850_CORE0_315_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_316_ISR_CAT))
#if (OSEE_RH850_CORE0_316_ISR_CAT == 1)
_osEE_rh850_core0_ei316:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_316_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei316, .-_osEE_rh850_core0_ei316
#else
_osEE_rh850_core0_ei316:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_316_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei316, .-_osEE_rh850_core0_ei316
#endif
#endif /* OSEE_RH850_CORE0_316_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_317_ISR_CAT))
#if (OSEE_RH850_CORE0_317_ISR_CAT == 1)
_osEE_rh850_core0_ei317:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_317_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei317, .-_osEE_rh850_core0_ei317
#else
_osEE_rh850_core0_ei317:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_317_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei317, .-_osEE_rh850_core0_ei317
#endif
#endif /* OSEE_RH850_CORE0_317_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_318_ISR_CAT))
#if (OSEE_RH850_CORE0_318_ISR_CAT == 1)
_osEE_rh850_core0_ei318:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_318_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei318, .-_osEE_rh850_core0_ei318
#else
_osEE_rh850_core0_ei318:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_318_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei318, .-_osEE_rh850_core0_ei318
#endif
#endif /* OSEE_RH850_CORE0_318_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_319_ISR_CAT))
#if (OSEE_RH850_CORE0_319_ISR_CAT == 1)
_osEE_rh850_core0_ei319:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_319_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei319, .-_osEE_rh850_core0_ei319
#else
_osEE_rh850_core0_ei319:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_319_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei319, .-_osEE_rh850_core0_ei319
#endif
#endif /* OSEE_RH850_CORE0_319_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_320_ISR_CAT))
#if (OSEE_RH850_CORE0_320_ISR_CAT == 1)
_osEE_rh850_core0_ei320:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_320_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei320, .-_osEE_rh850_core0_ei320
#else
_osEE_rh850_core0_ei320:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_320_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei320, .-_osEE_rh850_core0_ei320
#endif
#endif /* OSEE_RH850_CORE0_320_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_321_ISR_CAT))
#if (OSEE_RH850_CORE0_321_ISR_CAT == 1)
_osEE_rh850_core0_ei321:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_321_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei321, .-_osEE_rh850_core0_ei321
#else
_osEE_rh850_core0_ei321:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_321_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei321, .-_osEE_rh850_core0_ei321
#endif
#endif /* OSEE_RH850_CORE0_321_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_322_ISR_CAT))
#if (OSEE_RH850_CORE0_322_ISR_CAT == 1)
_osEE_rh850_core0_ei322:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_322_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei322, .-_osEE_rh850_core0_ei322
#else
_osEE_rh850_core0_ei322:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_322_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei322, .-_osEE_rh850_core0_ei322
#endif
#endif /* OSEE_RH850_CORE0_322_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_323_ISR_CAT))
#if (OSEE_RH850_CORE0_323_ISR_CAT == 1)
_osEE_rh850_core0_ei323:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_323_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei323, .-_osEE_rh850_core0_ei323
#else
_osEE_rh850_core0_ei323:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_323_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei323, .-_osEE_rh850_core0_ei323
#endif
#endif /* OSEE_RH850_CORE0_323_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_324_ISR_CAT))
#if (OSEE_RH850_CORE0_324_ISR_CAT == 1)
_osEE_rh850_core0_ei324:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_324_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei324, .-_osEE_rh850_core0_ei324
#else
_osEE_rh850_core0_ei324:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_324_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei324, .-_osEE_rh850_core0_ei324
#endif
#endif /* OSEE_RH850_CORE0_324_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_325_ISR_CAT))
#if (OSEE_RH850_CORE0_325_ISR_CAT == 1)
_osEE_rh850_core0_ei325:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_325_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei325, .-_osEE_rh850_core0_ei325
#else
_osEE_rh850_core0_ei325:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_325_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei325, .-_osEE_rh850_core0_ei325
#endif
#endif /* OSEE_RH850_CORE0_325_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_326_ISR_CAT))
#if (OSEE_RH850_CORE0_326_ISR_CAT == 1)
_osEE_rh850_core0_ei326:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_326_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei326, .-_osEE_rh850_core0_ei326
#else
_osEE_rh850_core0_ei326:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_326_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei326, .-_osEE_rh850_core0_ei326
#endif
#endif /* OSEE_RH850_CORE0_326_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_327_ISR_CAT))
#if (OSEE_RH850_CORE0_327_ISR_CAT == 1)
_osEE_rh850_core0_ei327:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_327_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei327, .-_osEE_rh850_core0_ei327
#else
_osEE_rh850_core0_ei327:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_327_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei327, .-_osEE_rh850_core0_ei327
#endif
#endif /* OSEE_RH850_CORE0_327_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_328_ISR_CAT))
#if (OSEE_RH850_CORE0_328_ISR_CAT == 1)
_osEE_rh850_core0_ei328:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_328_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei328, .-_osEE_rh850_core0_ei328
#else
_osEE_rh850_core0_ei328:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_328_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei328, .-_osEE_rh850_core0_ei328
#endif
#endif /* OSEE_RH850_CORE0_328_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_329_ISR_CAT))
#if (OSEE_RH850_CORE0_329_ISR_CAT == 1)
_osEE_rh850_core0_ei329:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_329_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei329, .-_osEE_rh850_core0_ei329
#else
_osEE_rh850_core0_ei329:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_329_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei329, .-_osEE_rh850_core0_ei329
#endif
#endif /* OSEE_RH850_CORE0_329_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_330_ISR_CAT))
#if (OSEE_RH850_CORE0_330_ISR_CAT == 1)
_osEE_rh850_core0_ei330:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_330_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei330, .-_osEE_rh850_core0_ei330
#else
_osEE_rh850_core0_ei330:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_330_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei330, .-_osEE_rh850_core0_ei330
#endif
#endif /* OSEE_RH850_CORE0_330_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_331_ISR_CAT))
#if (OSEE_RH850_CORE0_331_ISR_CAT == 1)
_osEE_rh850_core0_ei331:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_331_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei331, .-_osEE_rh850_core0_ei331
#else
_osEE_rh850_core0_ei331:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_331_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei331, .-_osEE_rh850_core0_ei331
#endif
#endif /* OSEE_RH850_CORE0_331_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_332_ISR_CAT))
#if (OSEE_RH850_CORE0_332_ISR_CAT == 1)
_osEE_rh850_core0_ei332:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_332_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei332, .-_osEE_rh850_core0_ei332
#else
_osEE_rh850_core0_ei332:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_332_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei332, .-_osEE_rh850_core0_ei332
#endif
#endif /* OSEE_RH850_CORE0_332_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_333_ISR_CAT))
#if (OSEE_RH850_CORE0_333_ISR_CAT == 1)
_osEE_rh850_core0_ei333:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_333_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei333, .-_osEE_rh850_core0_ei333
#else
_osEE_rh850_core0_ei333:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_333_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei333, .-_osEE_rh850_core0_ei333
#endif
#endif /* OSEE_RH850_CORE0_333_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_334_ISR_CAT))
#if (OSEE_RH850_CORE0_334_ISR_CAT == 1)
_osEE_rh850_core0_ei334:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_334_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei334, .-_osEE_rh850_core0_ei334
#else
_osEE_rh850_core0_ei334:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_334_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei334, .-_osEE_rh850_core0_ei334
#endif
#endif /* OSEE_RH850_CORE0_334_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_335_ISR_CAT))
#if (OSEE_RH850_CORE0_335_ISR_CAT == 1)
_osEE_rh850_core0_ei335:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_335_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei335, .-_osEE_rh850_core0_ei335
#else
_osEE_rh850_core0_ei335:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_335_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei335, .-_osEE_rh850_core0_ei335
#endif
#endif /* OSEE_RH850_CORE0_335_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_336_ISR_CAT))
#if (OSEE_RH850_CORE0_336_ISR_CAT == 1)
_osEE_rh850_core0_ei336:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_336_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei336, .-_osEE_rh850_core0_ei336
#else
_osEE_rh850_core0_ei336:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_336_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei336, .-_osEE_rh850_core0_ei336
#endif
#endif /* OSEE_RH850_CORE0_336_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_337_ISR_CAT))
#if (OSEE_RH850_CORE0_337_ISR_CAT == 1)
_osEE_rh850_core0_ei337:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_337_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei337, .-_osEE_rh850_core0_ei337
#else
_osEE_rh850_core0_ei337:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_337_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei337, .-_osEE_rh850_core0_ei337
#endif
#endif /* OSEE_RH850_CORE0_337_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_338_ISR_CAT))
#if (OSEE_RH850_CORE0_338_ISR_CAT == 1)
_osEE_rh850_core0_ei338:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_338_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei338, .-_osEE_rh850_core0_ei338
#else
_osEE_rh850_core0_ei338:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_338_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei338, .-_osEE_rh850_core0_ei338
#endif
#endif /* OSEE_RH850_CORE0_338_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_339_ISR_CAT))
#if (OSEE_RH850_CORE0_339_ISR_CAT == 1)
_osEE_rh850_core0_ei339:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_339_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei339, .-_osEE_rh850_core0_ei339
#else
_osEE_rh850_core0_ei339:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_339_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei339, .-_osEE_rh850_core0_ei339
#endif
#endif /* OSEE_RH850_CORE0_339_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_340_ISR_CAT))
#if (OSEE_RH850_CORE0_340_ISR_CAT == 1)
_osEE_rh850_core0_ei340:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_340_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei340, .-_osEE_rh850_core0_ei340
#else
_osEE_rh850_core0_ei340:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_340_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei340, .-_osEE_rh850_core0_ei340
#endif
#endif /* OSEE_RH850_CORE0_340_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_341_ISR_CAT))
#if (OSEE_RH850_CORE0_341_ISR_CAT == 1)
_osEE_rh850_core0_ei341:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_341_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei341, .-_osEE_rh850_core0_ei341
#else
_osEE_rh850_core0_ei341:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_341_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei341, .-_osEE_rh850_core0_ei341
#endif
#endif /* OSEE_RH850_CORE0_341_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_342_ISR_CAT))
#if (OSEE_RH850_CORE0_342_ISR_CAT == 1)
_osEE_rh850_core0_ei342:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_342_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei342, .-_osEE_rh850_core0_ei342
#else
_osEE_rh850_core0_ei342:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_342_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei342, .-_osEE_rh850_core0_ei342
#endif
#endif /* OSEE_RH850_CORE0_342_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_343_ISR_CAT))
#if (OSEE_RH850_CORE0_343_ISR_CAT == 1)
_osEE_rh850_core0_ei343:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_343_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei343, .-_osEE_rh850_core0_ei343
#else
_osEE_rh850_core0_ei343:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_343_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei343, .-_osEE_rh850_core0_ei343
#endif
#endif /* OSEE_RH850_CORE0_343_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_344_ISR_CAT))
#if (OSEE_RH850_CORE0_344_ISR_CAT == 1)
_osEE_rh850_core0_ei344:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_344_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei344, .-_osEE_rh850_core0_ei344
#else
_osEE_rh850_core0_ei344:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_344_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei344, .-_osEE_rh850_core0_ei344
#endif
#endif /* OSEE_RH850_CORE0_344_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_345_ISR_CAT))
#if (OSEE_RH850_CORE0_345_ISR_CAT == 1)
_osEE_rh850_core0_ei345:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_345_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei345, .-_osEE_rh850_core0_ei345
#else
_osEE_rh850_core0_ei345:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_345_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei345, .-_osEE_rh850_core0_ei345
#endif
#endif /* OSEE_RH850_CORE0_345_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_346_ISR_CAT))
#if (OSEE_RH850_CORE0_346_ISR_CAT == 1)
_osEE_rh850_core0_ei346:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_346_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei346, .-_osEE_rh850_core0_ei346
#else
_osEE_rh850_core0_ei346:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_346_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei346, .-_osEE_rh850_core0_ei346
#endif
#endif /* OSEE_RH850_CORE0_346_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_347_ISR_CAT))
#if (OSEE_RH850_CORE0_347_ISR_CAT == 1)
_osEE_rh850_core0_ei347:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_347_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei347, .-_osEE_rh850_core0_ei347
#else
_osEE_rh850_core0_ei347:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_347_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei347, .-_osEE_rh850_core0_ei347
#endif
#endif /* OSEE_RH850_CORE0_347_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_348_ISR_CAT))
#if (OSEE_RH850_CORE0_348_ISR_CAT == 1)
_osEE_rh850_core0_ei348:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_348_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei348, .-_osEE_rh850_core0_ei348
#else
_osEE_rh850_core0_ei348:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_348_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei348, .-_osEE_rh850_core0_ei348
#endif
#endif /* OSEE_RH850_CORE0_348_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_349_ISR_CAT))
#if (OSEE_RH850_CORE0_349_ISR_CAT == 1)
_osEE_rh850_core0_ei349:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_349_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei349, .-_osEE_rh850_core0_ei349
#else
_osEE_rh850_core0_ei349:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_349_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei349, .-_osEE_rh850_core0_ei349
#endif
#endif /* OSEE_RH850_CORE0_349_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_350_ISR_CAT))
#if (OSEE_RH850_CORE0_350_ISR_CAT == 1)
_osEE_rh850_core0_ei350:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_350_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei350, .-_osEE_rh850_core0_ei350
#else
_osEE_rh850_core0_ei350:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_350_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei350, .-_osEE_rh850_core0_ei350
#endif
#endif /* OSEE_RH850_CORE0_350_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_351_ISR_CAT))
#if (OSEE_RH850_CORE0_351_ISR_CAT == 1)
_osEE_rh850_core0_ei351:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_351_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei351, .-_osEE_rh850_core0_ei351
#else
_osEE_rh850_core0_ei351:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_351_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei351, .-_osEE_rh850_core0_ei351
#endif
#endif /* OSEE_RH850_CORE0_351_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_352_ISR_CAT))
#if (OSEE_RH850_CORE0_352_ISR_CAT == 1)
_osEE_rh850_core0_ei352:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_352_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei352, .-_osEE_rh850_core0_ei352
#else
_osEE_rh850_core0_ei352:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_352_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei352, .-_osEE_rh850_core0_ei352
#endif
#endif /* OSEE_RH850_CORE0_352_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_353_ISR_CAT))
#if (OSEE_RH850_CORE0_353_ISR_CAT == 1)
_osEE_rh850_core0_ei353:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_353_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei353, .-_osEE_rh850_core0_ei353
#else
_osEE_rh850_core0_ei353:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_353_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei353, .-_osEE_rh850_core0_ei353
#endif
#endif /* OSEE_RH850_CORE0_353_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_354_ISR_CAT))
#if (OSEE_RH850_CORE0_354_ISR_CAT == 1)
_osEE_rh850_core0_ei354:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_354_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei354, .-_osEE_rh850_core0_ei354
#else
_osEE_rh850_core0_ei354:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_354_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei354, .-_osEE_rh850_core0_ei354
#endif
#endif /* OSEE_RH850_CORE0_354_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_355_ISR_CAT))
#if (OSEE_RH850_CORE0_355_ISR_CAT == 1)
_osEE_rh850_core0_ei355:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_355_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei355, .-_osEE_rh850_core0_ei355
#else
_osEE_rh850_core0_ei355:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_355_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei355, .-_osEE_rh850_core0_ei355
#endif
#endif /* OSEE_RH850_CORE0_355_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_356_ISR_CAT))
#if (OSEE_RH850_CORE0_356_ISR_CAT == 1)
_osEE_rh850_core0_ei356:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_356_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei356, .-_osEE_rh850_core0_ei356
#else
_osEE_rh850_core0_ei356:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_356_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei356, .-_osEE_rh850_core0_ei356
#endif
#endif /* OSEE_RH850_CORE0_356_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_357_ISR_CAT))
#if (OSEE_RH850_CORE0_357_ISR_CAT == 1)
_osEE_rh850_core0_ei357:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_357_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei357, .-_osEE_rh850_core0_ei357
#else
_osEE_rh850_core0_ei357:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_357_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei357, .-_osEE_rh850_core0_ei357
#endif
#endif /* OSEE_RH850_CORE0_357_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_358_ISR_CAT))
#if (OSEE_RH850_CORE0_358_ISR_CAT == 1)
_osEE_rh850_core0_ei358:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_358_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei358, .-_osEE_rh850_core0_ei358
#else
_osEE_rh850_core0_ei358:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_358_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei358, .-_osEE_rh850_core0_ei358
#endif
#endif /* OSEE_RH850_CORE0_358_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_359_ISR_CAT))
#if (OSEE_RH850_CORE0_359_ISR_CAT == 1)
_osEE_rh850_core0_ei359:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_359_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei359, .-_osEE_rh850_core0_ei359
#else
_osEE_rh850_core0_ei359:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_359_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei359, .-_osEE_rh850_core0_ei359
#endif
#endif /* OSEE_RH850_CORE0_359_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_360_ISR_CAT))
#if (OSEE_RH850_CORE0_360_ISR_CAT == 1)
_osEE_rh850_core0_ei360:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_360_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei360, .-_osEE_rh850_core0_ei360
#else
_osEE_rh850_core0_ei360:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_360_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei360, .-_osEE_rh850_core0_ei360
#endif
#endif /* OSEE_RH850_CORE0_360_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_361_ISR_CAT))
#if (OSEE_RH850_CORE0_361_ISR_CAT == 1)
_osEE_rh850_core0_ei361:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_361_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei361, .-_osEE_rh850_core0_ei361
#else
_osEE_rh850_core0_ei361:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_361_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei361, .-_osEE_rh850_core0_ei361
#endif
#endif /* OSEE_RH850_CORE0_361_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_362_ISR_CAT))
#if (OSEE_RH850_CORE0_362_ISR_CAT == 1)
_osEE_rh850_core0_ei362:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_362_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei362, .-_osEE_rh850_core0_ei362
#else
_osEE_rh850_core0_ei362:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_362_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei362, .-_osEE_rh850_core0_ei362
#endif
#endif /* OSEE_RH850_CORE0_362_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_363_ISR_CAT))
#if (OSEE_RH850_CORE0_363_ISR_CAT == 1)
_osEE_rh850_core0_ei363:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_363_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei363, .-_osEE_rh850_core0_ei363
#else
_osEE_rh850_core0_ei363:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_363_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei363, .-_osEE_rh850_core0_ei363
#endif
#endif /* OSEE_RH850_CORE0_363_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_364_ISR_CAT))
#if (OSEE_RH850_CORE0_364_ISR_CAT == 1)
_osEE_rh850_core0_ei364:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_364_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei364, .-_osEE_rh850_core0_ei364
#else
_osEE_rh850_core0_ei364:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_364_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei364, .-_osEE_rh850_core0_ei364
#endif
#endif /* OSEE_RH850_CORE0_364_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_365_ISR_CAT))
#if (OSEE_RH850_CORE0_365_ISR_CAT == 1)
_osEE_rh850_core0_ei365:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_365_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei365, .-_osEE_rh850_core0_ei365
#else
_osEE_rh850_core0_ei365:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_365_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei365, .-_osEE_rh850_core0_ei365
#endif
#endif /* OSEE_RH850_CORE0_365_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_366_ISR_CAT))
#if (OSEE_RH850_CORE0_366_ISR_CAT == 1)
_osEE_rh850_core0_ei366:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_366_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei366, .-_osEE_rh850_core0_ei366
#else
_osEE_rh850_core0_ei366:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_366_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei366, .-_osEE_rh850_core0_ei366
#endif
#endif /* OSEE_RH850_CORE0_366_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_367_ISR_CAT))
#if (OSEE_RH850_CORE0_367_ISR_CAT == 1)
_osEE_rh850_core0_ei367:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_367_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei367, .-_osEE_rh850_core0_ei367
#else
_osEE_rh850_core0_ei367:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_367_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei367, .-_osEE_rh850_core0_ei367
#endif
#endif /* OSEE_RH850_CORE0_367_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_368_ISR_CAT))
#if (OSEE_RH850_CORE0_368_ISR_CAT == 1)
_osEE_rh850_core0_ei368:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_368_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei368, .-_osEE_rh850_core0_ei368
#else
_osEE_rh850_core0_ei368:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_368_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei368, .-_osEE_rh850_core0_ei368
#endif
#endif /* OSEE_RH850_CORE0_368_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_369_ISR_CAT))
#if (OSEE_RH850_CORE0_369_ISR_CAT == 1)
_osEE_rh850_core0_ei369:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_369_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei369, .-_osEE_rh850_core0_ei369
#else
_osEE_rh850_core0_ei369:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_369_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei369, .-_osEE_rh850_core0_ei369
#endif
#endif /* OSEE_RH850_CORE0_369_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_370_ISR_CAT))
#if (OSEE_RH850_CORE0_370_ISR_CAT == 1)
_osEE_rh850_core0_ei370:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_370_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei370, .-_osEE_rh850_core0_ei370
#else
_osEE_rh850_core0_ei370:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_370_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei370, .-_osEE_rh850_core0_ei370
#endif
#endif /* OSEE_RH850_CORE0_370_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_371_ISR_CAT))
#if (OSEE_RH850_CORE0_371_ISR_CAT == 1)
_osEE_rh850_core0_ei371:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_371_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei371, .-_osEE_rh850_core0_ei371
#else
_osEE_rh850_core0_ei371:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_371_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei371, .-_osEE_rh850_core0_ei371
#endif
#endif /* OSEE_RH850_CORE0_371_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_372_ISR_CAT))
#if (OSEE_RH850_CORE0_372_ISR_CAT == 1)
_osEE_rh850_core0_ei372:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_372_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei372, .-_osEE_rh850_core0_ei372
#else
_osEE_rh850_core0_ei372:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_372_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei372, .-_osEE_rh850_core0_ei372
#endif
#endif /* OSEE_RH850_CORE0_372_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_373_ISR_CAT))
#if (OSEE_RH850_CORE0_373_ISR_CAT == 1)
_osEE_rh850_core0_ei373:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_373_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei373, .-_osEE_rh850_core0_ei373
#else
_osEE_rh850_core0_ei373:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_373_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei373, .-_osEE_rh850_core0_ei373
#endif
#endif /* OSEE_RH850_CORE0_373_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_374_ISR_CAT))
#if (OSEE_RH850_CORE0_374_ISR_CAT == 1)
_osEE_rh850_core0_ei374:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_374_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei374, .-_osEE_rh850_core0_ei374
#else
_osEE_rh850_core0_ei374:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_374_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei374, .-_osEE_rh850_core0_ei374
#endif
#endif /* OSEE_RH850_CORE0_374_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_375_ISR_CAT))
#if (OSEE_RH850_CORE0_375_ISR_CAT == 1)
_osEE_rh850_core0_ei375:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_375_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei375, .-_osEE_rh850_core0_ei375
#else
_osEE_rh850_core0_ei375:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_375_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei375, .-_osEE_rh850_core0_ei375
#endif
#endif /* OSEE_RH850_CORE0_375_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_376_ISR_CAT))
#if (OSEE_RH850_CORE0_376_ISR_CAT == 1)
_osEE_rh850_core0_ei376:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_376_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei376, .-_osEE_rh850_core0_ei376
#else
_osEE_rh850_core0_ei376:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_376_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei376, .-_osEE_rh850_core0_ei376
#endif
#endif /* OSEE_RH850_CORE0_376_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_377_ISR_CAT))
#if (OSEE_RH850_CORE0_377_ISR_CAT == 1)
_osEE_rh850_core0_ei377:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_377_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei377, .-_osEE_rh850_core0_ei377
#else
_osEE_rh850_core0_ei377:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_377_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei377, .-_osEE_rh850_core0_ei377
#endif
#endif /* OSEE_RH850_CORE0_377_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_378_ISR_CAT))
#if (OSEE_RH850_CORE0_378_ISR_CAT == 1)
_osEE_rh850_core0_ei378:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_378_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei378, .-_osEE_rh850_core0_ei378
#else
_osEE_rh850_core0_ei378:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_378_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei378, .-_osEE_rh850_core0_ei378
#endif
#endif /* OSEE_RH850_CORE0_378_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_379_ISR_CAT))
#if (OSEE_RH850_CORE0_379_ISR_CAT == 1)
_osEE_rh850_core0_ei379:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_379_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei379, .-_osEE_rh850_core0_ei379
#else
_osEE_rh850_core0_ei379:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_379_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei379, .-_osEE_rh850_core0_ei379
#endif
#endif /* OSEE_RH850_CORE0_379_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_380_ISR_CAT))
#if (OSEE_RH850_CORE0_380_ISR_CAT == 1)
_osEE_rh850_core0_ei380:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_380_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei380, .-_osEE_rh850_core0_ei380
#else
_osEE_rh850_core0_ei380:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_380_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei380, .-_osEE_rh850_core0_ei380
#endif
#endif /* OSEE_RH850_CORE0_380_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_381_ISR_CAT))
#if (OSEE_RH850_CORE0_381_ISR_CAT == 1)
_osEE_rh850_core0_ei381:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_381_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei381, .-_osEE_rh850_core0_ei381
#else
_osEE_rh850_core0_ei381:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_381_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei381, .-_osEE_rh850_core0_ei381
#endif
#endif /* OSEE_RH850_CORE0_381_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_382_ISR_CAT))
#if (OSEE_RH850_CORE0_382_ISR_CAT == 1)
_osEE_rh850_core0_ei382:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_382_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei382, .-_osEE_rh850_core0_ei382
#else
_osEE_rh850_core0_ei382:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_382_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei382, .-_osEE_rh850_core0_ei382
#endif
#endif /* OSEE_RH850_CORE0_382_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_383_ISR_CAT))
#if (OSEE_RH850_CORE0_383_ISR_CAT == 1)
_osEE_rh850_core0_ei383:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_383_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei383, .-_osEE_rh850_core0_ei383
#else
_osEE_rh850_core0_ei383:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_383_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei383, .-_osEE_rh850_core0_ei383
#endif
#endif /* OSEE_RH850_CORE0_383_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_384_ISR_CAT))
#if (OSEE_RH850_CORE0_384_ISR_CAT == 1)
_osEE_rh850_core0_ei384:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_384_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei384, .-_osEE_rh850_core0_ei384
#else
_osEE_rh850_core0_ei384:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_384_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei384, .-_osEE_rh850_core0_ei384
#endif
#endif /* OSEE_RH850_CORE0_384_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_385_ISR_CAT))
#if (OSEE_RH850_CORE0_385_ISR_CAT == 1)
_osEE_rh850_core0_ei385:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_385_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei385, .-_osEE_rh850_core0_ei385
#else
_osEE_rh850_core0_ei385:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_385_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei385, .-_osEE_rh850_core0_ei385
#endif
#endif /* OSEE_RH850_CORE0_385_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_386_ISR_CAT))
#if (OSEE_RH850_CORE0_386_ISR_CAT == 1)
_osEE_rh850_core0_ei386:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_386_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei386, .-_osEE_rh850_core0_ei386
#else
_osEE_rh850_core0_ei386:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_386_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei386, .-_osEE_rh850_core0_ei386
#endif
#endif /* OSEE_RH850_CORE0_386_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_387_ISR_CAT))
#if (OSEE_RH850_CORE0_387_ISR_CAT == 1)
_osEE_rh850_core0_ei387:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_387_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei387, .-_osEE_rh850_core0_ei387
#else
_osEE_rh850_core0_ei387:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_387_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei387, .-_osEE_rh850_core0_ei387
#endif
#endif /* OSEE_RH850_CORE0_387_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_388_ISR_CAT))
#if (OSEE_RH850_CORE0_388_ISR_CAT == 1)
_osEE_rh850_core0_ei388:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_388_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei388, .-_osEE_rh850_core0_ei388
#else
_osEE_rh850_core0_ei388:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_388_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei388, .-_osEE_rh850_core0_ei388
#endif
#endif /* OSEE_RH850_CORE0_388_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_389_ISR_CAT))
#if (OSEE_RH850_CORE0_389_ISR_CAT == 1)
_osEE_rh850_core0_ei389:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_389_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei389, .-_osEE_rh850_core0_ei389
#else
_osEE_rh850_core0_ei389:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_389_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei389, .-_osEE_rh850_core0_ei389
#endif
#endif /* OSEE_RH850_CORE0_389_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_390_ISR_CAT))
#if (OSEE_RH850_CORE0_390_ISR_CAT == 1)
_osEE_rh850_core0_ei390:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_390_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei390, .-_osEE_rh850_core0_ei390
#else
_osEE_rh850_core0_ei390:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_390_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei390, .-_osEE_rh850_core0_ei390
#endif
#endif /* OSEE_RH850_CORE0_390_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_391_ISR_CAT))
#if (OSEE_RH850_CORE0_391_ISR_CAT == 1)
_osEE_rh850_core0_ei391:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_391_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei391, .-_osEE_rh850_core0_ei391
#else
_osEE_rh850_core0_ei391:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_391_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei391, .-_osEE_rh850_core0_ei391
#endif
#endif /* OSEE_RH850_CORE0_391_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_392_ISR_CAT))
#if (OSEE_RH850_CORE0_392_ISR_CAT == 1)
_osEE_rh850_core0_ei392:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_392_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei392, .-_osEE_rh850_core0_ei392
#else
_osEE_rh850_core0_ei392:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_392_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei392, .-_osEE_rh850_core0_ei392
#endif
#endif /* OSEE_RH850_CORE0_392_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_393_ISR_CAT))
#if (OSEE_RH850_CORE0_393_ISR_CAT == 1)
_osEE_rh850_core0_ei393:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_393_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei393, .-_osEE_rh850_core0_ei393
#else
_osEE_rh850_core0_ei393:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_393_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei393, .-_osEE_rh850_core0_ei393
#endif
#endif /* OSEE_RH850_CORE0_393_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_394_ISR_CAT))
#if (OSEE_RH850_CORE0_394_ISR_CAT == 1)
_osEE_rh850_core0_ei394:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_394_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei394, .-_osEE_rh850_core0_ei394
#else
_osEE_rh850_core0_ei394:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_394_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei394, .-_osEE_rh850_core0_ei394
#endif
#endif /* OSEE_RH850_CORE0_394_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_395_ISR_CAT))
#if (OSEE_RH850_CORE0_395_ISR_CAT == 1)
_osEE_rh850_core0_ei395:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_395_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei395, .-_osEE_rh850_core0_ei395
#else
_osEE_rh850_core0_ei395:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_395_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei395, .-_osEE_rh850_core0_ei395
#endif
#endif /* OSEE_RH850_CORE0_395_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_396_ISR_CAT))
#if (OSEE_RH850_CORE0_396_ISR_CAT == 1)
_osEE_rh850_core0_ei396:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_396_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei396, .-_osEE_rh850_core0_ei396
#else
_osEE_rh850_core0_ei396:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_396_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei396, .-_osEE_rh850_core0_ei396
#endif
#endif /* OSEE_RH850_CORE0_396_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_397_ISR_CAT))
#if (OSEE_RH850_CORE0_397_ISR_CAT == 1)
_osEE_rh850_core0_ei397:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_397_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei397, .-_osEE_rh850_core0_ei397
#else
_osEE_rh850_core0_ei397:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_397_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei397, .-_osEE_rh850_core0_ei397
#endif
#endif /* OSEE_RH850_CORE0_397_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_398_ISR_CAT))
#if (OSEE_RH850_CORE0_398_ISR_CAT == 1)
_osEE_rh850_core0_ei398:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_398_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei398, .-_osEE_rh850_core0_ei398
#else
_osEE_rh850_core0_ei398:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_398_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei398, .-_osEE_rh850_core0_ei398
#endif
#endif /* OSEE_RH850_CORE0_398_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_399_ISR_CAT))
#if (OSEE_RH850_CORE0_399_ISR_CAT == 1)
_osEE_rh850_core0_ei399:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_399_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei399, .-_osEE_rh850_core0_ei399
#else
_osEE_rh850_core0_ei399:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_399_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei399, .-_osEE_rh850_core0_ei399
#endif
#endif /* OSEE_RH850_CORE0_399_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_400_ISR_CAT))
#if (OSEE_RH850_CORE0_400_ISR_CAT == 1)
_osEE_rh850_core0_ei400:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_400_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei400, .-_osEE_rh850_core0_ei400
#else
_osEE_rh850_core0_ei400:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_400_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei400, .-_osEE_rh850_core0_ei400
#endif
#endif /* OSEE_RH850_CORE0_400_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_401_ISR_CAT))
#if (OSEE_RH850_CORE0_401_ISR_CAT == 1)
_osEE_rh850_core0_ei401:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_401_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei401, .-_osEE_rh850_core0_ei401
#else
_osEE_rh850_core0_ei401:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_401_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei401, .-_osEE_rh850_core0_ei401
#endif
#endif /* OSEE_RH850_CORE0_401_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_402_ISR_CAT))
#if (OSEE_RH850_CORE0_402_ISR_CAT == 1)
_osEE_rh850_core0_ei402:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_402_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei402, .-_osEE_rh850_core0_ei402
#else
_osEE_rh850_core0_ei402:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_402_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei402, .-_osEE_rh850_core0_ei402
#endif
#endif /* OSEE_RH850_CORE0_402_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_403_ISR_CAT))
#if (OSEE_RH850_CORE0_403_ISR_CAT == 1)
_osEE_rh850_core0_ei403:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_403_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei403, .-_osEE_rh850_core0_ei403
#else
_osEE_rh850_core0_ei403:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_403_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei403, .-_osEE_rh850_core0_ei403
#endif
#endif /* OSEE_RH850_CORE0_403_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_404_ISR_CAT))
#if (OSEE_RH850_CORE0_404_ISR_CAT == 1)
_osEE_rh850_core0_ei404:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_404_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei404, .-_osEE_rh850_core0_ei404
#else
_osEE_rh850_core0_ei404:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_404_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei404, .-_osEE_rh850_core0_ei404
#endif
#endif /* OSEE_RH850_CORE0_404_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_405_ISR_CAT))
#if (OSEE_RH850_CORE0_405_ISR_CAT == 1)
_osEE_rh850_core0_ei405:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_405_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei405, .-_osEE_rh850_core0_ei405
#else
_osEE_rh850_core0_ei405:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_405_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei405, .-_osEE_rh850_core0_ei405
#endif
#endif /* OSEE_RH850_CORE0_405_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_406_ISR_CAT))
#if (OSEE_RH850_CORE0_406_ISR_CAT == 1)
_osEE_rh850_core0_ei406:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_406_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei406, .-_osEE_rh850_core0_ei406
#else
_osEE_rh850_core0_ei406:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_406_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei406, .-_osEE_rh850_core0_ei406
#endif
#endif /* OSEE_RH850_CORE0_406_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_407_ISR_CAT))
#if (OSEE_RH850_CORE0_407_ISR_CAT == 1)
_osEE_rh850_core0_ei407:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_407_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei407, .-_osEE_rh850_core0_ei407
#else
_osEE_rh850_core0_ei407:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_407_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei407, .-_osEE_rh850_core0_ei407
#endif
#endif /* OSEE_RH850_CORE0_407_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_408_ISR_CAT))
#if (OSEE_RH850_CORE0_408_ISR_CAT == 1)
_osEE_rh850_core0_ei408:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_408_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei408, .-_osEE_rh850_core0_ei408
#else
_osEE_rh850_core0_ei408:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_408_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei408, .-_osEE_rh850_core0_ei408
#endif
#endif /* OSEE_RH850_CORE0_408_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_409_ISR_CAT))
#if (OSEE_RH850_CORE0_409_ISR_CAT == 1)
_osEE_rh850_core0_ei409:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_409_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei409, .-_osEE_rh850_core0_ei409
#else
_osEE_rh850_core0_ei409:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_409_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei409, .-_osEE_rh850_core0_ei409
#endif
#endif /* OSEE_RH850_CORE0_409_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_410_ISR_CAT))
#if (OSEE_RH850_CORE0_410_ISR_CAT == 1)
_osEE_rh850_core0_ei410:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_410_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei410, .-_osEE_rh850_core0_ei410
#else
_osEE_rh850_core0_ei410:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_410_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei410, .-_osEE_rh850_core0_ei410
#endif
#endif /* OSEE_RH850_CORE0_410_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_411_ISR_CAT))
#if (OSEE_RH850_CORE0_411_ISR_CAT == 1)
_osEE_rh850_core0_ei411:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_411_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei411, .-_osEE_rh850_core0_ei411
#else
_osEE_rh850_core0_ei411:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_411_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei411, .-_osEE_rh850_core0_ei411
#endif
#endif /* OSEE_RH850_CORE0_411_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_412_ISR_CAT))
#if (OSEE_RH850_CORE0_412_ISR_CAT == 1)
_osEE_rh850_core0_ei412:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_412_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei412, .-_osEE_rh850_core0_ei412
#else
_osEE_rh850_core0_ei412:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_412_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei412, .-_osEE_rh850_core0_ei412
#endif
#endif /* OSEE_RH850_CORE0_412_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_413_ISR_CAT))
#if (OSEE_RH850_CORE0_413_ISR_CAT == 1)
_osEE_rh850_core0_ei413:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_413_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei413, .-_osEE_rh850_core0_ei413
#else
_osEE_rh850_core0_ei413:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_413_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei413, .-_osEE_rh850_core0_ei413
#endif
#endif /* OSEE_RH850_CORE0_413_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_414_ISR_CAT))
#if (OSEE_RH850_CORE0_414_ISR_CAT == 1)
_osEE_rh850_core0_ei414:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_414_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei414, .-_osEE_rh850_core0_ei414
#else
_osEE_rh850_core0_ei414:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_414_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei414, .-_osEE_rh850_core0_ei414
#endif
#endif /* OSEE_RH850_CORE0_414_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_415_ISR_CAT))
#if (OSEE_RH850_CORE0_415_ISR_CAT == 1)
_osEE_rh850_core0_ei415:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_415_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei415, .-_osEE_rh850_core0_ei415
#else
_osEE_rh850_core0_ei415:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_415_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei415, .-_osEE_rh850_core0_ei415
#endif
#endif /* OSEE_RH850_CORE0_415_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_416_ISR_CAT))
#if (OSEE_RH850_CORE0_416_ISR_CAT == 1)
_osEE_rh850_core0_ei416:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_416_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei416, .-_osEE_rh850_core0_ei416
#else
_osEE_rh850_core0_ei416:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_416_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei416, .-_osEE_rh850_core0_ei416
#endif
#endif /* OSEE_RH850_CORE0_416_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_417_ISR_CAT))
#if (OSEE_RH850_CORE0_417_ISR_CAT == 1)
_osEE_rh850_core0_ei417:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_417_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei417, .-_osEE_rh850_core0_ei417
#else
_osEE_rh850_core0_ei417:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_417_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei417, .-_osEE_rh850_core0_ei417
#endif
#endif /* OSEE_RH850_CORE0_417_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_418_ISR_CAT))
#if (OSEE_RH850_CORE0_418_ISR_CAT == 1)
_osEE_rh850_core0_ei418:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_418_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei418, .-_osEE_rh850_core0_ei418
#else
_osEE_rh850_core0_ei418:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_418_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei418, .-_osEE_rh850_core0_ei418
#endif
#endif /* OSEE_RH850_CORE0_418_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_419_ISR_CAT))
#if (OSEE_RH850_CORE0_419_ISR_CAT == 1)
_osEE_rh850_core0_ei419:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_419_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei419, .-_osEE_rh850_core0_ei419
#else
_osEE_rh850_core0_ei419:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_419_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei419, .-_osEE_rh850_core0_ei419
#endif
#endif /* OSEE_RH850_CORE0_419_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_420_ISR_CAT))
#if (OSEE_RH850_CORE0_420_ISR_CAT == 1)
_osEE_rh850_core0_ei420:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_420_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei420, .-_osEE_rh850_core0_ei420
#else
_osEE_rh850_core0_ei420:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_420_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei420, .-_osEE_rh850_core0_ei420
#endif
#endif /* OSEE_RH850_CORE0_420_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_421_ISR_CAT))
#if (OSEE_RH850_CORE0_421_ISR_CAT == 1)
_osEE_rh850_core0_ei421:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_421_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei421, .-_osEE_rh850_core0_ei421
#else
_osEE_rh850_core0_ei421:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_421_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei421, .-_osEE_rh850_core0_ei421
#endif
#endif /* OSEE_RH850_CORE0_421_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_422_ISR_CAT))
#if (OSEE_RH850_CORE0_422_ISR_CAT == 1)
_osEE_rh850_core0_ei422:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_422_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei422, .-_osEE_rh850_core0_ei422
#else
_osEE_rh850_core0_ei422:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_422_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei422, .-_osEE_rh850_core0_ei422
#endif
#endif /* OSEE_RH850_CORE0_422_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_423_ISR_CAT))
#if (OSEE_RH850_CORE0_423_ISR_CAT == 1)
_osEE_rh850_core0_ei423:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_423_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei423, .-_osEE_rh850_core0_ei423
#else
_osEE_rh850_core0_ei423:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_423_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei423, .-_osEE_rh850_core0_ei423
#endif
#endif /* OSEE_RH850_CORE0_423_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_424_ISR_CAT))
#if (OSEE_RH850_CORE0_424_ISR_CAT == 1)
_osEE_rh850_core0_ei424:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_424_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei424, .-_osEE_rh850_core0_ei424
#else
_osEE_rh850_core0_ei424:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_424_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei424, .-_osEE_rh850_core0_ei424
#endif
#endif /* OSEE_RH850_CORE0_424_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_425_ISR_CAT))
#if (OSEE_RH850_CORE0_425_ISR_CAT == 1)
_osEE_rh850_core0_ei425:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_425_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei425, .-_osEE_rh850_core0_ei425
#else
_osEE_rh850_core0_ei425:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_425_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei425, .-_osEE_rh850_core0_ei425
#endif
#endif /* OSEE_RH850_CORE0_425_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_426_ISR_CAT))
#if (OSEE_RH850_CORE0_426_ISR_CAT == 1)
_osEE_rh850_core0_ei426:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_426_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei426, .-_osEE_rh850_core0_ei426
#else
_osEE_rh850_core0_ei426:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_426_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei426, .-_osEE_rh850_core0_ei426
#endif
#endif /* OSEE_RH850_CORE0_426_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_427_ISR_CAT))
#if (OSEE_RH850_CORE0_427_ISR_CAT == 1)
_osEE_rh850_core0_ei427:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_427_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei427, .-_osEE_rh850_core0_ei427
#else
_osEE_rh850_core0_ei427:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_427_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei427, .-_osEE_rh850_core0_ei427
#endif
#endif /* OSEE_RH850_CORE0_427_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_428_ISR_CAT))
#if (OSEE_RH850_CORE0_428_ISR_CAT == 1)
_osEE_rh850_core0_ei428:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_428_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei428, .-_osEE_rh850_core0_ei428
#else
_osEE_rh850_core0_ei428:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_428_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei428, .-_osEE_rh850_core0_ei428
#endif
#endif /* OSEE_RH850_CORE0_428_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_429_ISR_CAT))
#if (OSEE_RH850_CORE0_429_ISR_CAT == 1)
_osEE_rh850_core0_ei429:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_429_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei429, .-_osEE_rh850_core0_ei429
#else
_osEE_rh850_core0_ei429:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_429_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei429, .-_osEE_rh850_core0_ei429
#endif
#endif /* OSEE_RH850_CORE0_429_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_430_ISR_CAT))
#if (OSEE_RH850_CORE0_430_ISR_CAT == 1)
_osEE_rh850_core0_ei430:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_430_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei430, .-_osEE_rh850_core0_ei430
#else
_osEE_rh850_core0_ei430:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_430_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei430, .-_osEE_rh850_core0_ei430
#endif
#endif /* OSEE_RH850_CORE0_430_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_431_ISR_CAT))
#if (OSEE_RH850_CORE0_431_ISR_CAT == 1)
_osEE_rh850_core0_ei431:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_431_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei431, .-_osEE_rh850_core0_ei431
#else
_osEE_rh850_core0_ei431:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_431_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei431, .-_osEE_rh850_core0_ei431
#endif
#endif /* OSEE_RH850_CORE0_431_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_432_ISR_CAT))
#if (OSEE_RH850_CORE0_432_ISR_CAT == 1)
_osEE_rh850_core0_ei432:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_432_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei432, .-_osEE_rh850_core0_ei432
#else
_osEE_rh850_core0_ei432:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_432_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei432, .-_osEE_rh850_core0_ei432
#endif
#endif /* OSEE_RH850_CORE0_432_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_433_ISR_CAT))
#if (OSEE_RH850_CORE0_433_ISR_CAT == 1)
_osEE_rh850_core0_ei433:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_433_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei433, .-_osEE_rh850_core0_ei433
#else
_osEE_rh850_core0_ei433:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_433_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei433, .-_osEE_rh850_core0_ei433
#endif
#endif /* OSEE_RH850_CORE0_433_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_434_ISR_CAT))
#if (OSEE_RH850_CORE0_434_ISR_CAT == 1)
_osEE_rh850_core0_ei434:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_434_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei434, .-_osEE_rh850_core0_ei434
#else
_osEE_rh850_core0_ei434:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_434_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei434, .-_osEE_rh850_core0_ei434
#endif
#endif /* OSEE_RH850_CORE0_434_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_435_ISR_CAT))
#if (OSEE_RH850_CORE0_435_ISR_CAT == 1)
_osEE_rh850_core0_ei435:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_435_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei435, .-_osEE_rh850_core0_ei435
#else
_osEE_rh850_core0_ei435:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_435_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei435, .-_osEE_rh850_core0_ei435
#endif
#endif /* OSEE_RH850_CORE0_435_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_436_ISR_CAT))
#if (OSEE_RH850_CORE0_436_ISR_CAT == 1)
_osEE_rh850_core0_ei436:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_436_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei436, .-_osEE_rh850_core0_ei436
#else
_osEE_rh850_core0_ei436:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_436_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei436, .-_osEE_rh850_core0_ei436
#endif
#endif /* OSEE_RH850_CORE0_436_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_437_ISR_CAT))
#if (OSEE_RH850_CORE0_437_ISR_CAT == 1)
_osEE_rh850_core0_ei437:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_437_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei437, .-_osEE_rh850_core0_ei437
#else
_osEE_rh850_core0_ei437:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_437_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei437, .-_osEE_rh850_core0_ei437
#endif
#endif /* OSEE_RH850_CORE0_437_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_438_ISR_CAT))
#if (OSEE_RH850_CORE0_438_ISR_CAT == 1)
_osEE_rh850_core0_ei438:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_438_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei438, .-_osEE_rh850_core0_ei438
#else
_osEE_rh850_core0_ei438:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_438_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei438, .-_osEE_rh850_core0_ei438
#endif
#endif /* OSEE_RH850_CORE0_438_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_439_ISR_CAT))
#if (OSEE_RH850_CORE0_439_ISR_CAT == 1)
_osEE_rh850_core0_ei439:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_439_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei439, .-_osEE_rh850_core0_ei439
#else
_osEE_rh850_core0_ei439:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_439_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei439, .-_osEE_rh850_core0_ei439
#endif
#endif /* OSEE_RH850_CORE0_439_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_440_ISR_CAT))
#if (OSEE_RH850_CORE0_440_ISR_CAT == 1)
_osEE_rh850_core0_ei440:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_440_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei440, .-_osEE_rh850_core0_ei440
#else
_osEE_rh850_core0_ei440:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_440_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei440, .-_osEE_rh850_core0_ei440
#endif
#endif /* OSEE_RH850_CORE0_440_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_441_ISR_CAT))
#if (OSEE_RH850_CORE0_441_ISR_CAT == 1)
_osEE_rh850_core0_ei441:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_441_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei441, .-_osEE_rh850_core0_ei441
#else
_osEE_rh850_core0_ei441:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_441_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei441, .-_osEE_rh850_core0_ei441
#endif
#endif /* OSEE_RH850_CORE0_441_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_442_ISR_CAT))
#if (OSEE_RH850_CORE0_442_ISR_CAT == 1)
_osEE_rh850_core0_ei442:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_442_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei442, .-_osEE_rh850_core0_ei442
#else
_osEE_rh850_core0_ei442:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_442_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei442, .-_osEE_rh850_core0_ei442
#endif
#endif /* OSEE_RH850_CORE0_442_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_443_ISR_CAT))
#if (OSEE_RH850_CORE0_443_ISR_CAT == 1)
_osEE_rh850_core0_ei443:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_443_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei443, .-_osEE_rh850_core0_ei443
#else
_osEE_rh850_core0_ei443:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_443_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei443, .-_osEE_rh850_core0_ei443
#endif
#endif /* OSEE_RH850_CORE0_443_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_444_ISR_CAT))
#if (OSEE_RH850_CORE0_444_ISR_CAT == 1)
_osEE_rh850_core0_ei444:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_444_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei444, .-_osEE_rh850_core0_ei444
#else
_osEE_rh850_core0_ei444:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_444_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei444, .-_osEE_rh850_core0_ei444
#endif
#endif /* OSEE_RH850_CORE0_444_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_445_ISR_CAT))
#if (OSEE_RH850_CORE0_445_ISR_CAT == 1)
_osEE_rh850_core0_ei445:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_445_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei445, .-_osEE_rh850_core0_ei445
#else
_osEE_rh850_core0_ei445:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_445_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei445, .-_osEE_rh850_core0_ei445
#endif
#endif /* OSEE_RH850_CORE0_445_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_446_ISR_CAT))
#if (OSEE_RH850_CORE0_446_ISR_CAT == 1)
_osEE_rh850_core0_ei446:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_446_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei446, .-_osEE_rh850_core0_ei446
#else
_osEE_rh850_core0_ei446:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_446_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei446, .-_osEE_rh850_core0_ei446
#endif
#endif /* OSEE_RH850_CORE0_446_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_447_ISR_CAT))
#if (OSEE_RH850_CORE0_447_ISR_CAT == 1)
_osEE_rh850_core0_ei447:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_447_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei447, .-_osEE_rh850_core0_ei447
#else
_osEE_rh850_core0_ei447:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_447_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei447, .-_osEE_rh850_core0_ei447
#endif
#endif /* OSEE_RH850_CORE0_447_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_448_ISR_CAT))
#if (OSEE_RH850_CORE0_448_ISR_CAT == 1)
_osEE_rh850_core0_ei448:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_448_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei448, .-_osEE_rh850_core0_ei448
#else
_osEE_rh850_core0_ei448:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_448_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei448, .-_osEE_rh850_core0_ei448
#endif
#endif /* OSEE_RH850_CORE0_448_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_449_ISR_CAT))
#if (OSEE_RH850_CORE0_449_ISR_CAT == 1)
_osEE_rh850_core0_ei449:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_449_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei449, .-_osEE_rh850_core0_ei449
#else
_osEE_rh850_core0_ei449:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_449_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei449, .-_osEE_rh850_core0_ei449
#endif
#endif /* OSEE_RH850_CORE0_449_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_450_ISR_CAT))
#if (OSEE_RH850_CORE0_450_ISR_CAT == 1)
_osEE_rh850_core0_ei450:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_450_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei450, .-_osEE_rh850_core0_ei450
#else
_osEE_rh850_core0_ei450:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_450_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei450, .-_osEE_rh850_core0_ei450
#endif
#endif /* OSEE_RH850_CORE0_450_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_451_ISR_CAT))
#if (OSEE_RH850_CORE0_451_ISR_CAT == 1)
_osEE_rh850_core0_ei451:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_451_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei451, .-_osEE_rh850_core0_ei451
#else
_osEE_rh850_core0_ei451:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_451_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei451, .-_osEE_rh850_core0_ei451
#endif
#endif /* OSEE_RH850_CORE0_451_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_452_ISR_CAT))
#if (OSEE_RH850_CORE0_452_ISR_CAT == 1)
_osEE_rh850_core0_ei452:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_452_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei452, .-_osEE_rh850_core0_ei452
#else
_osEE_rh850_core0_ei452:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_452_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei452, .-_osEE_rh850_core0_ei452
#endif
#endif /* OSEE_RH850_CORE0_452_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_453_ISR_CAT))
#if (OSEE_RH850_CORE0_453_ISR_CAT == 1)
_osEE_rh850_core0_ei453:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_453_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei453, .-_osEE_rh850_core0_ei453
#else
_osEE_rh850_core0_ei453:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_453_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei453, .-_osEE_rh850_core0_ei453
#endif
#endif /* OSEE_RH850_CORE0_453_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_454_ISR_CAT))
#if (OSEE_RH850_CORE0_454_ISR_CAT == 1)
_osEE_rh850_core0_ei454:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_454_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei454, .-_osEE_rh850_core0_ei454
#else
_osEE_rh850_core0_ei454:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_454_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei454, .-_osEE_rh850_core0_ei454
#endif
#endif /* OSEE_RH850_CORE0_454_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_455_ISR_CAT))
#if (OSEE_RH850_CORE0_455_ISR_CAT == 1)
_osEE_rh850_core0_ei455:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_455_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei455, .-_osEE_rh850_core0_ei455
#else
_osEE_rh850_core0_ei455:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_455_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei455, .-_osEE_rh850_core0_ei455
#endif
#endif /* OSEE_RH850_CORE0_455_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_456_ISR_CAT))
#if (OSEE_RH850_CORE0_456_ISR_CAT == 1)
_osEE_rh850_core0_ei456:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_456_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei456, .-_osEE_rh850_core0_ei456
#else
_osEE_rh850_core0_ei456:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_456_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei456, .-_osEE_rh850_core0_ei456
#endif
#endif /* OSEE_RH850_CORE0_456_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_457_ISR_CAT))
#if (OSEE_RH850_CORE0_457_ISR_CAT == 1)
_osEE_rh850_core0_ei457:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_457_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei457, .-_osEE_rh850_core0_ei457
#else
_osEE_rh850_core0_ei457:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_457_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei457, .-_osEE_rh850_core0_ei457
#endif
#endif /* OSEE_RH850_CORE0_457_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_458_ISR_CAT))
#if (OSEE_RH850_CORE0_458_ISR_CAT == 1)
_osEE_rh850_core0_ei458:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_458_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei458, .-_osEE_rh850_core0_ei458
#else
_osEE_rh850_core0_ei458:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_458_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei458, .-_osEE_rh850_core0_ei458
#endif
#endif /* OSEE_RH850_CORE0_458_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_459_ISR_CAT))
#if (OSEE_RH850_CORE0_459_ISR_CAT == 1)
_osEE_rh850_core0_ei459:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_459_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei459, .-_osEE_rh850_core0_ei459
#else
_osEE_rh850_core0_ei459:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_459_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei459, .-_osEE_rh850_core0_ei459
#endif
#endif /* OSEE_RH850_CORE0_459_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_460_ISR_CAT))
#if (OSEE_RH850_CORE0_460_ISR_CAT == 1)
_osEE_rh850_core0_ei460:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_460_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei460, .-_osEE_rh850_core0_ei460
#else
_osEE_rh850_core0_ei460:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_460_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei460, .-_osEE_rh850_core0_ei460
#endif
#endif /* OSEE_RH850_CORE0_460_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_461_ISR_CAT))
#if (OSEE_RH850_CORE0_461_ISR_CAT == 1)
_osEE_rh850_core0_ei461:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_461_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei461, .-_osEE_rh850_core0_ei461
#else
_osEE_rh850_core0_ei461:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_461_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei461, .-_osEE_rh850_core0_ei461
#endif
#endif /* OSEE_RH850_CORE0_461_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_462_ISR_CAT))
#if (OSEE_RH850_CORE0_462_ISR_CAT == 1)
_osEE_rh850_core0_ei462:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_462_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei462, .-_osEE_rh850_core0_ei462
#else
_osEE_rh850_core0_ei462:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_462_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei462, .-_osEE_rh850_core0_ei462
#endif
#endif /* OSEE_RH850_CORE0_462_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_463_ISR_CAT))
#if (OSEE_RH850_CORE0_463_ISR_CAT == 1)
_osEE_rh850_core0_ei463:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_463_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei463, .-_osEE_rh850_core0_ei463
#else
_osEE_rh850_core0_ei463:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_463_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei463, .-_osEE_rh850_core0_ei463
#endif
#endif /* OSEE_RH850_CORE0_463_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_464_ISR_CAT))
#if (OSEE_RH850_CORE0_464_ISR_CAT == 1)
_osEE_rh850_core0_ei464:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_464_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei464, .-_osEE_rh850_core0_ei464
#else
_osEE_rh850_core0_ei464:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_464_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei464, .-_osEE_rh850_core0_ei464
#endif
#endif /* OSEE_RH850_CORE0_464_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_465_ISR_CAT))
#if (OSEE_RH850_CORE0_465_ISR_CAT == 1)
_osEE_rh850_core0_ei465:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_465_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei465, .-_osEE_rh850_core0_ei465
#else
_osEE_rh850_core0_ei465:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_465_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei465, .-_osEE_rh850_core0_ei465
#endif
#endif /* OSEE_RH850_CORE0_465_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_466_ISR_CAT))
#if (OSEE_RH850_CORE0_466_ISR_CAT == 1)
_osEE_rh850_core0_ei466:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_466_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei466, .-_osEE_rh850_core0_ei466
#else
_osEE_rh850_core0_ei466:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_466_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei466, .-_osEE_rh850_core0_ei466
#endif
#endif /* OSEE_RH850_CORE0_466_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_467_ISR_CAT))
#if (OSEE_RH850_CORE0_467_ISR_CAT == 1)
_osEE_rh850_core0_ei467:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_467_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei467, .-_osEE_rh850_core0_ei467
#else
_osEE_rh850_core0_ei467:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_467_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei467, .-_osEE_rh850_core0_ei467
#endif
#endif /* OSEE_RH850_CORE0_467_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_468_ISR_CAT))
#if (OSEE_RH850_CORE0_468_ISR_CAT == 1)
_osEE_rh850_core0_ei468:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_468_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei468, .-_osEE_rh850_core0_ei468
#else
_osEE_rh850_core0_ei468:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_468_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei468, .-_osEE_rh850_core0_ei468
#endif
#endif /* OSEE_RH850_CORE0_468_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_469_ISR_CAT))
#if (OSEE_RH850_CORE0_469_ISR_CAT == 1)
_osEE_rh850_core0_ei469:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_469_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei469, .-_osEE_rh850_core0_ei469
#else
_osEE_rh850_core0_ei469:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_469_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei469, .-_osEE_rh850_core0_ei469
#endif
#endif /* OSEE_RH850_CORE0_469_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_470_ISR_CAT))
#if (OSEE_RH850_CORE0_470_ISR_CAT == 1)
_osEE_rh850_core0_ei470:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_470_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei470, .-_osEE_rh850_core0_ei470
#else
_osEE_rh850_core0_ei470:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_470_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei470, .-_osEE_rh850_core0_ei470
#endif
#endif /* OSEE_RH850_CORE0_470_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_471_ISR_CAT))
#if (OSEE_RH850_CORE0_471_ISR_CAT == 1)
_osEE_rh850_core0_ei471:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_471_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei471, .-_osEE_rh850_core0_ei471
#else
_osEE_rh850_core0_ei471:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_471_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei471, .-_osEE_rh850_core0_ei471
#endif
#endif /* OSEE_RH850_CORE0_471_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_472_ISR_CAT))
#if (OSEE_RH850_CORE0_472_ISR_CAT == 1)
_osEE_rh850_core0_ei472:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_472_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei472, .-_osEE_rh850_core0_ei472
#else
_osEE_rh850_core0_ei472:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_472_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei472, .-_osEE_rh850_core0_ei472
#endif
#endif /* OSEE_RH850_CORE0_472_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_473_ISR_CAT))
#if (OSEE_RH850_CORE0_473_ISR_CAT == 1)
_osEE_rh850_core0_ei473:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_473_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei473, .-_osEE_rh850_core0_ei473
#else
_osEE_rh850_core0_ei473:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_473_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei473, .-_osEE_rh850_core0_ei473
#endif
#endif /* OSEE_RH850_CORE0_473_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_474_ISR_CAT))
#if (OSEE_RH850_CORE0_474_ISR_CAT == 1)
_osEE_rh850_core0_ei474:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_474_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei474, .-_osEE_rh850_core0_ei474
#else
_osEE_rh850_core0_ei474:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_474_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei474, .-_osEE_rh850_core0_ei474
#endif
#endif /* OSEE_RH850_CORE0_474_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_475_ISR_CAT))
#if (OSEE_RH850_CORE0_475_ISR_CAT == 1)
_osEE_rh850_core0_ei475:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_475_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei475, .-_osEE_rh850_core0_ei475
#else
_osEE_rh850_core0_ei475:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_475_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei475, .-_osEE_rh850_core0_ei475
#endif
#endif /* OSEE_RH850_CORE0_475_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_476_ISR_CAT))
#if (OSEE_RH850_CORE0_476_ISR_CAT == 1)
_osEE_rh850_core0_ei476:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_476_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei476, .-_osEE_rh850_core0_ei476
#else
_osEE_rh850_core0_ei476:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_476_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei476, .-_osEE_rh850_core0_ei476
#endif
#endif /* OSEE_RH850_CORE0_476_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_477_ISR_CAT))
#if (OSEE_RH850_CORE0_477_ISR_CAT == 1)
_osEE_rh850_core0_ei477:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_477_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei477, .-_osEE_rh850_core0_ei477
#else
_osEE_rh850_core0_ei477:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_477_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei477, .-_osEE_rh850_core0_ei477
#endif
#endif /* OSEE_RH850_CORE0_477_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_478_ISR_CAT))
#if (OSEE_RH850_CORE0_478_ISR_CAT == 1)
_osEE_rh850_core0_ei478:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_478_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei478, .-_osEE_rh850_core0_ei478
#else
_osEE_rh850_core0_ei478:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_478_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei478, .-_osEE_rh850_core0_ei478
#endif
#endif /* OSEE_RH850_CORE0_478_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_479_ISR_CAT))
#if (OSEE_RH850_CORE0_479_ISR_CAT == 1)
_osEE_rh850_core0_ei479:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_479_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei479, .-_osEE_rh850_core0_ei479
#else
_osEE_rh850_core0_ei479:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_479_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei479, .-_osEE_rh850_core0_ei479
#endif
#endif /* OSEE_RH850_CORE0_479_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_480_ISR_CAT))
#if (OSEE_RH850_CORE0_480_ISR_CAT == 1)
_osEE_rh850_core0_ei480:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_480_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei480, .-_osEE_rh850_core0_ei480
#else
_osEE_rh850_core0_ei480:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_480_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei480, .-_osEE_rh850_core0_ei480
#endif
#endif /* OSEE_RH850_CORE0_480_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_481_ISR_CAT))
#if (OSEE_RH850_CORE0_481_ISR_CAT == 1)
_osEE_rh850_core0_ei481:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_481_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei481, .-_osEE_rh850_core0_ei481
#else
_osEE_rh850_core0_ei481:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_481_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei481, .-_osEE_rh850_core0_ei481
#endif
#endif /* OSEE_RH850_CORE0_481_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_482_ISR_CAT))
#if (OSEE_RH850_CORE0_482_ISR_CAT == 1)
_osEE_rh850_core0_ei482:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_482_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei482, .-_osEE_rh850_core0_ei482
#else
_osEE_rh850_core0_ei482:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_482_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei482, .-_osEE_rh850_core0_ei482
#endif
#endif /* OSEE_RH850_CORE0_482_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_483_ISR_CAT))
#if (OSEE_RH850_CORE0_483_ISR_CAT == 1)
_osEE_rh850_core0_ei483:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_483_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei483, .-_osEE_rh850_core0_ei483
#else
_osEE_rh850_core0_ei483:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_483_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei483, .-_osEE_rh850_core0_ei483
#endif
#endif /* OSEE_RH850_CORE0_483_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_484_ISR_CAT))
#if (OSEE_RH850_CORE0_484_ISR_CAT == 1)
_osEE_rh850_core0_ei484:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_484_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei484, .-_osEE_rh850_core0_ei484
#else
_osEE_rh850_core0_ei484:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_484_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei484, .-_osEE_rh850_core0_ei484
#endif
#endif /* OSEE_RH850_CORE0_484_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_485_ISR_CAT))
#if (OSEE_RH850_CORE0_485_ISR_CAT == 1)
_osEE_rh850_core0_ei485:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_485_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei485, .-_osEE_rh850_core0_ei485
#else
_osEE_rh850_core0_ei485:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_485_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei485, .-_osEE_rh850_core0_ei485
#endif
#endif /* OSEE_RH850_CORE0_485_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_486_ISR_CAT))
#if (OSEE_RH850_CORE0_486_ISR_CAT == 1)
_osEE_rh850_core0_ei486:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_486_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei486, .-_osEE_rh850_core0_ei486
#else
_osEE_rh850_core0_ei486:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_486_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei486, .-_osEE_rh850_core0_ei486
#endif
#endif /* OSEE_RH850_CORE0_486_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_487_ISR_CAT))
#if (OSEE_RH850_CORE0_487_ISR_CAT == 1)
_osEE_rh850_core0_ei487:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_487_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei487, .-_osEE_rh850_core0_ei487
#else
_osEE_rh850_core0_ei487:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_487_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei487, .-_osEE_rh850_core0_ei487
#endif
#endif /* OSEE_RH850_CORE0_487_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_488_ISR_CAT))
#if (OSEE_RH850_CORE0_488_ISR_CAT == 1)
_osEE_rh850_core0_ei488:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_488_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei488, .-_osEE_rh850_core0_ei488
#else
_osEE_rh850_core0_ei488:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_488_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei488, .-_osEE_rh850_core0_ei488
#endif
#endif /* OSEE_RH850_CORE0_488_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_489_ISR_CAT))
#if (OSEE_RH850_CORE0_489_ISR_CAT == 1)
_osEE_rh850_core0_ei489:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_489_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei489, .-_osEE_rh850_core0_ei489
#else
_osEE_rh850_core0_ei489:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_489_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei489, .-_osEE_rh850_core0_ei489
#endif
#endif /* OSEE_RH850_CORE0_489_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_490_ISR_CAT))
#if (OSEE_RH850_CORE0_490_ISR_CAT == 1)
_osEE_rh850_core0_ei490:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_490_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei490, .-_osEE_rh850_core0_ei490
#else
_osEE_rh850_core0_ei490:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_490_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei490, .-_osEE_rh850_core0_ei490
#endif
#endif /* OSEE_RH850_CORE0_490_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_491_ISR_CAT))
#if (OSEE_RH850_CORE0_491_ISR_CAT == 1)
_osEE_rh850_core0_ei491:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_491_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei491, .-_osEE_rh850_core0_ei491
#else
_osEE_rh850_core0_ei491:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_491_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei491, .-_osEE_rh850_core0_ei491
#endif
#endif /* OSEE_RH850_CORE0_491_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_492_ISR_CAT))
#if (OSEE_RH850_CORE0_492_ISR_CAT == 1)
_osEE_rh850_core0_ei492:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_492_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei492, .-_osEE_rh850_core0_ei492
#else
_osEE_rh850_core0_ei492:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_492_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei492, .-_osEE_rh850_core0_ei492
#endif
#endif /* OSEE_RH850_CORE0_492_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_493_ISR_CAT))
#if (OSEE_RH850_CORE0_493_ISR_CAT == 1)
_osEE_rh850_core0_ei493:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_493_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei493, .-_osEE_rh850_core0_ei493
#else
_osEE_rh850_core0_ei493:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_493_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei493, .-_osEE_rh850_core0_ei493
#endif
#endif /* OSEE_RH850_CORE0_493_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_494_ISR_CAT))
#if (OSEE_RH850_CORE0_494_ISR_CAT == 1)
_osEE_rh850_core0_ei494:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_494_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei494, .-_osEE_rh850_core0_ei494
#else
_osEE_rh850_core0_ei494:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_494_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei494, .-_osEE_rh850_core0_ei494
#endif
#endif /* OSEE_RH850_CORE0_494_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_495_ISR_CAT))
#if (OSEE_RH850_CORE0_495_ISR_CAT == 1)
_osEE_rh850_core0_ei495:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_495_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei495, .-_osEE_rh850_core0_ei495
#else
_osEE_rh850_core0_ei495:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_495_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei495, .-_osEE_rh850_core0_ei495
#endif
#endif /* OSEE_RH850_CORE0_495_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_496_ISR_CAT))
#if (OSEE_RH850_CORE0_496_ISR_CAT == 1)
_osEE_rh850_core0_ei496:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_496_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei496, .-_osEE_rh850_core0_ei496
#else
_osEE_rh850_core0_ei496:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_496_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei496, .-_osEE_rh850_core0_ei496
#endif
#endif /* OSEE_RH850_CORE0_496_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_497_ISR_CAT))
#if (OSEE_RH850_CORE0_497_ISR_CAT == 1)
_osEE_rh850_core0_ei497:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_497_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei497, .-_osEE_rh850_core0_ei497
#else
_osEE_rh850_core0_ei497:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_497_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei497, .-_osEE_rh850_core0_ei497
#endif
#endif /* OSEE_RH850_CORE0_497_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_498_ISR_CAT))
#if (OSEE_RH850_CORE0_498_ISR_CAT == 1)
_osEE_rh850_core0_ei498:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_498_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei498, .-_osEE_rh850_core0_ei498
#else
_osEE_rh850_core0_ei498:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_498_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei498, .-_osEE_rh850_core0_ei498
#endif
#endif /* OSEE_RH850_CORE0_498_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_499_ISR_CAT))
#if (OSEE_RH850_CORE0_499_ISR_CAT == 1)
_osEE_rh850_core0_ei499:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_499_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei499, .-_osEE_rh850_core0_ei499
#else
_osEE_rh850_core0_ei499:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_499_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei499, .-_osEE_rh850_core0_ei499
#endif
#endif /* OSEE_RH850_CORE0_499_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_500_ISR_CAT))
#if (OSEE_RH850_CORE0_500_ISR_CAT == 1)
_osEE_rh850_core0_ei500:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_500_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei500, .-_osEE_rh850_core0_ei500
#else
_osEE_rh850_core0_ei500:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_500_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei500, .-_osEE_rh850_core0_ei500
#endif
#endif /* OSEE_RH850_CORE0_500_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_501_ISR_CAT))
#if (OSEE_RH850_CORE0_501_ISR_CAT == 1)
_osEE_rh850_core0_ei501:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_501_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei501, .-_osEE_rh850_core0_ei501
#else
_osEE_rh850_core0_ei501:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_501_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei501, .-_osEE_rh850_core0_ei501
#endif
#endif /* OSEE_RH850_CORE0_501_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_502_ISR_CAT))
#if (OSEE_RH850_CORE0_502_ISR_CAT == 1)
_osEE_rh850_core0_ei502:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_502_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei502, .-_osEE_rh850_core0_ei502
#else
_osEE_rh850_core0_ei502:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_502_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei502, .-_osEE_rh850_core0_ei502
#endif
#endif /* OSEE_RH850_CORE0_502_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_503_ISR_CAT))
#if (OSEE_RH850_CORE0_503_ISR_CAT == 1)
_osEE_rh850_core0_ei503:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_503_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei503, .-_osEE_rh850_core0_ei503
#else
_osEE_rh850_core0_ei503:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_503_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei503, .-_osEE_rh850_core0_ei503
#endif
#endif /* OSEE_RH850_CORE0_503_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_504_ISR_CAT))
#if (OSEE_RH850_CORE0_504_ISR_CAT == 1)
_osEE_rh850_core0_ei504:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_504_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei504, .-_osEE_rh850_core0_ei504
#else
_osEE_rh850_core0_ei504:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_504_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei504, .-_osEE_rh850_core0_ei504
#endif
#endif /* OSEE_RH850_CORE0_504_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_505_ISR_CAT))
#if (OSEE_RH850_CORE0_505_ISR_CAT == 1)
_osEE_rh850_core0_ei505:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_505_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei505, .-_osEE_rh850_core0_ei505
#else
_osEE_rh850_core0_ei505:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_505_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei505, .-_osEE_rh850_core0_ei505
#endif
#endif /* OSEE_RH850_CORE0_505_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_506_ISR_CAT))
#if (OSEE_RH850_CORE0_506_ISR_CAT == 1)
_osEE_rh850_core0_ei506:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_506_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei506, .-_osEE_rh850_core0_ei506
#else
_osEE_rh850_core0_ei506:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_506_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei506, .-_osEE_rh850_core0_ei506
#endif
#endif /* OSEE_RH850_CORE0_506_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_507_ISR_CAT))
#if (OSEE_RH850_CORE0_507_ISR_CAT == 1)
_osEE_rh850_core0_ei507:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_507_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei507, .-_osEE_rh850_core0_ei507
#else
_osEE_rh850_core0_ei507:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_507_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei507, .-_osEE_rh850_core0_ei507
#endif
#endif /* OSEE_RH850_CORE0_507_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_508_ISR_CAT))
#if (OSEE_RH850_CORE0_508_ISR_CAT == 1)
_osEE_rh850_core0_ei508:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_508_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei508, .-_osEE_rh850_core0_ei508
#else
_osEE_rh850_core0_ei508:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_508_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei508, .-_osEE_rh850_core0_ei508
#endif
#endif /* OSEE_RH850_CORE0_508_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_509_ISR_CAT))
#if (OSEE_RH850_CORE0_509_ISR_CAT == 1)
_osEE_rh850_core0_ei509:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_509_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei509, .-_osEE_rh850_core0_ei509
#else
_osEE_rh850_core0_ei509:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_509_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei509, .-_osEE_rh850_core0_ei509
#endif
#endif /* OSEE_RH850_CORE0_509_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_510_ISR_CAT))
#if (OSEE_RH850_CORE0_510_ISR_CAT == 1)
_osEE_rh850_core0_ei510:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_510_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei510, .-_osEE_rh850_core0_ei510
#else
_osEE_rh850_core0_ei510:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_510_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei510, .-_osEE_rh850_core0_ei510
#endif
#endif /* OSEE_RH850_CORE0_510_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_511_ISR_CAT))
#if (OSEE_RH850_CORE0_511_ISR_CAT == 1)
_osEE_rh850_core0_ei511:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_511_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei511, .-_osEE_rh850_core0_ei511
#else
_osEE_rh850_core0_ei511:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_511_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei511, .-_osEE_rh850_core0_ei511
#endif
#endif /* OSEE_RH850_CORE0_511_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_512_ISR_CAT))
#if (OSEE_RH850_CORE0_512_ISR_CAT == 1)
_osEE_rh850_core0_ei512:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_512_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei512, .-_osEE_rh850_core0_ei512
#else
_osEE_rh850_core0_ei512:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_512_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei512, .-_osEE_rh850_core0_ei512
#endif
#endif /* OSEE_RH850_CORE0_512_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_513_ISR_CAT))
#if (OSEE_RH850_CORE0_513_ISR_CAT == 1)
_osEE_rh850_core0_ei513:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_513_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei513, .-_osEE_rh850_core0_ei513
#else
_osEE_rh850_core0_ei513:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_513_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei513, .-_osEE_rh850_core0_ei513
#endif
#endif /* OSEE_RH850_CORE0_513_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_514_ISR_CAT))
#if (OSEE_RH850_CORE0_514_ISR_CAT == 1)
_osEE_rh850_core0_ei514:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_514_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei514, .-_osEE_rh850_core0_ei514
#else
_osEE_rh850_core0_ei514:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_514_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei514, .-_osEE_rh850_core0_ei514
#endif
#endif /* OSEE_RH850_CORE0_514_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_515_ISR_CAT))
#if (OSEE_RH850_CORE0_515_ISR_CAT == 1)
_osEE_rh850_core0_ei515:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_515_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei515, .-_osEE_rh850_core0_ei515
#else
_osEE_rh850_core0_ei515:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_515_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei515, .-_osEE_rh850_core0_ei515
#endif
#endif /* OSEE_RH850_CORE0_515_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_516_ISR_CAT))
#if (OSEE_RH850_CORE0_516_ISR_CAT == 1)
_osEE_rh850_core0_ei516:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_516_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei516, .-_osEE_rh850_core0_ei516
#else
_osEE_rh850_core0_ei516:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_516_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei516, .-_osEE_rh850_core0_ei516
#endif
#endif /* OSEE_RH850_CORE0_516_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_517_ISR_CAT))
#if (OSEE_RH850_CORE0_517_ISR_CAT == 1)
_osEE_rh850_core0_ei517:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_517_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei517, .-_osEE_rh850_core0_ei517
#else
_osEE_rh850_core0_ei517:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_517_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei517, .-_osEE_rh850_core0_ei517
#endif
#endif /* OSEE_RH850_CORE0_517_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_518_ISR_CAT))
#if (OSEE_RH850_CORE0_518_ISR_CAT == 1)
_osEE_rh850_core0_ei518:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_518_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei518, .-_osEE_rh850_core0_ei518
#else
_osEE_rh850_core0_ei518:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_518_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei518, .-_osEE_rh850_core0_ei518
#endif
#endif /* OSEE_RH850_CORE0_518_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_519_ISR_CAT))
#if (OSEE_RH850_CORE0_519_ISR_CAT == 1)
_osEE_rh850_core0_ei519:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_519_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei519, .-_osEE_rh850_core0_ei519
#else
_osEE_rh850_core0_ei519:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_519_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei519, .-_osEE_rh850_core0_ei519
#endif
#endif /* OSEE_RH850_CORE0_519_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_520_ISR_CAT))
#if (OSEE_RH850_CORE0_520_ISR_CAT == 1)
_osEE_rh850_core0_ei520:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_520_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei520, .-_osEE_rh850_core0_ei520
#else
_osEE_rh850_core0_ei520:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_520_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei520, .-_osEE_rh850_core0_ei520
#endif
#endif /* OSEE_RH850_CORE0_520_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_521_ISR_CAT))
#if (OSEE_RH850_CORE0_521_ISR_CAT == 1)
_osEE_rh850_core0_ei521:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_521_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei521, .-_osEE_rh850_core0_ei521
#else
_osEE_rh850_core0_ei521:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_521_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei521, .-_osEE_rh850_core0_ei521
#endif
#endif /* OSEE_RH850_CORE0_521_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_522_ISR_CAT))
#if (OSEE_RH850_CORE0_522_ISR_CAT == 1)
_osEE_rh850_core0_ei522:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_522_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei522, .-_osEE_rh850_core0_ei522
#else
_osEE_rh850_core0_ei522:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_522_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei522, .-_osEE_rh850_core0_ei522
#endif
#endif /* OSEE_RH850_CORE0_522_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_523_ISR_CAT))
#if (OSEE_RH850_CORE0_523_ISR_CAT == 1)
_osEE_rh850_core0_ei523:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_523_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei523, .-_osEE_rh850_core0_ei523
#else
_osEE_rh850_core0_ei523:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_523_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei523, .-_osEE_rh850_core0_ei523
#endif
#endif /* OSEE_RH850_CORE0_523_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_524_ISR_CAT))
#if (OSEE_RH850_CORE0_524_ISR_CAT == 1)
_osEE_rh850_core0_ei524:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_524_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei524, .-_osEE_rh850_core0_ei524
#else
_osEE_rh850_core0_ei524:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_524_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei524, .-_osEE_rh850_core0_ei524
#endif
#endif /* OSEE_RH850_CORE0_524_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_525_ISR_CAT))
#if (OSEE_RH850_CORE0_525_ISR_CAT == 1)
_osEE_rh850_core0_ei525:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_525_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei525, .-_osEE_rh850_core0_ei525
#else
_osEE_rh850_core0_ei525:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_525_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei525, .-_osEE_rh850_core0_ei525
#endif
#endif /* OSEE_RH850_CORE0_525_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_526_ISR_CAT))
#if (OSEE_RH850_CORE0_526_ISR_CAT == 1)
_osEE_rh850_core0_ei526:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_526_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei526, .-_osEE_rh850_core0_ei526
#else
_osEE_rh850_core0_ei526:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_526_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei526, .-_osEE_rh850_core0_ei526
#endif
#endif /* OSEE_RH850_CORE0_526_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_527_ISR_CAT))
#if (OSEE_RH850_CORE0_527_ISR_CAT == 1)
_osEE_rh850_core0_ei527:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_527_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei527, .-_osEE_rh850_core0_ei527
#else
_osEE_rh850_core0_ei527:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_527_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei527, .-_osEE_rh850_core0_ei527
#endif
#endif /* OSEE_RH850_CORE0_527_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_528_ISR_CAT))
#if (OSEE_RH850_CORE0_528_ISR_CAT == 1)
_osEE_rh850_core0_ei528:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_528_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei528, .-_osEE_rh850_core0_ei528
#else
_osEE_rh850_core0_ei528:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_528_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei528, .-_osEE_rh850_core0_ei528
#endif
#endif /* OSEE_RH850_CORE0_528_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_529_ISR_CAT))
#if (OSEE_RH850_CORE0_529_ISR_CAT == 1)
_osEE_rh850_core0_ei529:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_529_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei529, .-_osEE_rh850_core0_ei529
#else
_osEE_rh850_core0_ei529:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_529_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei529, .-_osEE_rh850_core0_ei529
#endif
#endif /* OSEE_RH850_CORE0_529_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_530_ISR_CAT))
#if (OSEE_RH850_CORE0_530_ISR_CAT == 1)
_osEE_rh850_core0_ei530:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_530_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei530, .-_osEE_rh850_core0_ei530
#else
_osEE_rh850_core0_ei530:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_530_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei530, .-_osEE_rh850_core0_ei530
#endif
#endif /* OSEE_RH850_CORE0_530_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_531_ISR_CAT))
#if (OSEE_RH850_CORE0_531_ISR_CAT == 1)
_osEE_rh850_core0_ei531:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_531_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei531, .-_osEE_rh850_core0_ei531
#else
_osEE_rh850_core0_ei531:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_531_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei531, .-_osEE_rh850_core0_ei531
#endif
#endif /* OSEE_RH850_CORE0_531_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_532_ISR_CAT))
#if (OSEE_RH850_CORE0_532_ISR_CAT == 1)
_osEE_rh850_core0_ei532:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_532_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei532, .-_osEE_rh850_core0_ei532
#else
_osEE_rh850_core0_ei532:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_532_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei532, .-_osEE_rh850_core0_ei532
#endif
#endif /* OSEE_RH850_CORE0_532_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_533_ISR_CAT))
#if (OSEE_RH850_CORE0_533_ISR_CAT == 1)
_osEE_rh850_core0_ei533:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_533_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei533, .-_osEE_rh850_core0_ei533
#else
_osEE_rh850_core0_ei533:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_533_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei533, .-_osEE_rh850_core0_ei533
#endif
#endif /* OSEE_RH850_CORE0_533_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_534_ISR_CAT))
#if (OSEE_RH850_CORE0_534_ISR_CAT == 1)
_osEE_rh850_core0_ei534:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_534_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei534, .-_osEE_rh850_core0_ei534
#else
_osEE_rh850_core0_ei534:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_534_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei534, .-_osEE_rh850_core0_ei534
#endif
#endif /* OSEE_RH850_CORE0_534_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_535_ISR_CAT))
#if (OSEE_RH850_CORE0_535_ISR_CAT == 1)
_osEE_rh850_core0_ei535:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_535_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei535, .-_osEE_rh850_core0_ei535
#else
_osEE_rh850_core0_ei535:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_535_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei535, .-_osEE_rh850_core0_ei535
#endif
#endif /* OSEE_RH850_CORE0_535_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_536_ISR_CAT))
#if (OSEE_RH850_CORE0_536_ISR_CAT == 1)
_osEE_rh850_core0_ei536:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_536_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei536, .-_osEE_rh850_core0_ei536
#else
_osEE_rh850_core0_ei536:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_536_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei536, .-_osEE_rh850_core0_ei536
#endif
#endif /* OSEE_RH850_CORE0_536_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_537_ISR_CAT))
#if (OSEE_RH850_CORE0_537_ISR_CAT == 1)
_osEE_rh850_core0_ei537:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_537_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei537, .-_osEE_rh850_core0_ei537
#else
_osEE_rh850_core0_ei537:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_537_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei537, .-_osEE_rh850_core0_ei537
#endif
#endif /* OSEE_RH850_CORE0_537_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_538_ISR_CAT))
#if (OSEE_RH850_CORE0_538_ISR_CAT == 1)
_osEE_rh850_core0_ei538:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_538_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei538, .-_osEE_rh850_core0_ei538
#else
_osEE_rh850_core0_ei538:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_538_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei538, .-_osEE_rh850_core0_ei538
#endif
#endif /* OSEE_RH850_CORE0_538_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_539_ISR_CAT))
#if (OSEE_RH850_CORE0_539_ISR_CAT == 1)
_osEE_rh850_core0_ei539:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_539_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei539, .-_osEE_rh850_core0_ei539
#else
_osEE_rh850_core0_ei539:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_539_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei539, .-_osEE_rh850_core0_ei539
#endif
#endif /* OSEE_RH850_CORE0_539_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_540_ISR_CAT))
#if (OSEE_RH850_CORE0_540_ISR_CAT == 1)
_osEE_rh850_core0_ei540:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_540_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei540, .-_osEE_rh850_core0_ei540
#else
_osEE_rh850_core0_ei540:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_540_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei540, .-_osEE_rh850_core0_ei540
#endif
#endif /* OSEE_RH850_CORE0_540_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_541_ISR_CAT))
#if (OSEE_RH850_CORE0_541_ISR_CAT == 1)
_osEE_rh850_core0_ei541:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_541_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei541, .-_osEE_rh850_core0_ei541
#else
_osEE_rh850_core0_ei541:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_541_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei541, .-_osEE_rh850_core0_ei541
#endif
#endif /* OSEE_RH850_CORE0_541_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_542_ISR_CAT))
#if (OSEE_RH850_CORE0_542_ISR_CAT == 1)
_osEE_rh850_core0_ei542:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_542_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei542, .-_osEE_rh850_core0_ei542
#else
_osEE_rh850_core0_ei542:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_542_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei542, .-_osEE_rh850_core0_ei542
#endif
#endif /* OSEE_RH850_CORE0_542_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_543_ISR_CAT))
#if (OSEE_RH850_CORE0_543_ISR_CAT == 1)
_osEE_rh850_core0_ei543:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_543_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei543, .-_osEE_rh850_core0_ei543
#else
_osEE_rh850_core0_ei543:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_543_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei543, .-_osEE_rh850_core0_ei543
#endif
#endif /* OSEE_RH850_CORE0_543_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_544_ISR_CAT))
#if (OSEE_RH850_CORE0_544_ISR_CAT == 1)
_osEE_rh850_core0_ei544:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_544_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei544, .-_osEE_rh850_core0_ei544
#else
_osEE_rh850_core0_ei544:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_544_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei544, .-_osEE_rh850_core0_ei544
#endif
#endif /* OSEE_RH850_CORE0_544_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_545_ISR_CAT))
#if (OSEE_RH850_CORE0_545_ISR_CAT == 1)
_osEE_rh850_core0_ei545:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_545_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei545, .-_osEE_rh850_core0_ei545
#else
_osEE_rh850_core0_ei545:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_545_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei545, .-_osEE_rh850_core0_ei545
#endif
#endif /* OSEE_RH850_CORE0_545_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_546_ISR_CAT))
#if (OSEE_RH850_CORE0_546_ISR_CAT == 1)
_osEE_rh850_core0_ei546:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_546_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei546, .-_osEE_rh850_core0_ei546
#else
_osEE_rh850_core0_ei546:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_546_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei546, .-_osEE_rh850_core0_ei546
#endif
#endif /* OSEE_RH850_CORE0_546_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_547_ISR_CAT))
#if (OSEE_RH850_CORE0_547_ISR_CAT == 1)
_osEE_rh850_core0_ei547:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_547_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei547, .-_osEE_rh850_core0_ei547
#else
_osEE_rh850_core0_ei547:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_547_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei547, .-_osEE_rh850_core0_ei547
#endif
#endif /* OSEE_RH850_CORE0_547_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_548_ISR_CAT))
#if (OSEE_RH850_CORE0_548_ISR_CAT == 1)
_osEE_rh850_core0_ei548:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_548_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei548, .-_osEE_rh850_core0_ei548
#else
_osEE_rh850_core0_ei548:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_548_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei548, .-_osEE_rh850_core0_ei548
#endif
#endif /* OSEE_RH850_CORE0_548_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_549_ISR_CAT))
#if (OSEE_RH850_CORE0_549_ISR_CAT == 1)
_osEE_rh850_core0_ei549:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_549_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei549, .-_osEE_rh850_core0_ei549
#else
_osEE_rh850_core0_ei549:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_549_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei549, .-_osEE_rh850_core0_ei549
#endif
#endif /* OSEE_RH850_CORE0_549_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_550_ISR_CAT))
#if (OSEE_RH850_CORE0_550_ISR_CAT == 1)
_osEE_rh850_core0_ei550:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_550_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei550, .-_osEE_rh850_core0_ei550
#else
_osEE_rh850_core0_ei550:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_550_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei550, .-_osEE_rh850_core0_ei550
#endif
#endif /* OSEE_RH850_CORE0_550_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_551_ISR_CAT))
#if (OSEE_RH850_CORE0_551_ISR_CAT == 1)
_osEE_rh850_core0_ei551:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_551_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei551, .-_osEE_rh850_core0_ei551
#else
_osEE_rh850_core0_ei551:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_551_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei551, .-_osEE_rh850_core0_ei551
#endif
#endif /* OSEE_RH850_CORE0_551_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_552_ISR_CAT))
#if (OSEE_RH850_CORE0_552_ISR_CAT == 1)
_osEE_rh850_core0_ei552:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_552_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei552, .-_osEE_rh850_core0_ei552
#else
_osEE_rh850_core0_ei552:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_552_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei552, .-_osEE_rh850_core0_ei552
#endif
#endif /* OSEE_RH850_CORE0_552_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_553_ISR_CAT))
#if (OSEE_RH850_CORE0_553_ISR_CAT == 1)
_osEE_rh850_core0_ei553:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_553_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei553, .-_osEE_rh850_core0_ei553
#else
_osEE_rh850_core0_ei553:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_553_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei553, .-_osEE_rh850_core0_ei553
#endif
#endif /* OSEE_RH850_CORE0_553_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_554_ISR_CAT))
#if (OSEE_RH850_CORE0_554_ISR_CAT == 1)
_osEE_rh850_core0_ei554:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_554_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei554, .-_osEE_rh850_core0_ei554
#else
_osEE_rh850_core0_ei554:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_554_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei554, .-_osEE_rh850_core0_ei554
#endif
#endif /* OSEE_RH850_CORE0_554_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_555_ISR_CAT))
#if (OSEE_RH850_CORE0_555_ISR_CAT == 1)
_osEE_rh850_core0_ei555:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_555_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei555, .-_osEE_rh850_core0_ei555
#else
_osEE_rh850_core0_ei555:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_555_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei555, .-_osEE_rh850_core0_ei555
#endif
#endif /* OSEE_RH850_CORE0_555_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_556_ISR_CAT))
#if (OSEE_RH850_CORE0_556_ISR_CAT == 1)
_osEE_rh850_core0_ei556:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_556_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei556, .-_osEE_rh850_core0_ei556
#else
_osEE_rh850_core0_ei556:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_556_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei556, .-_osEE_rh850_core0_ei556
#endif
#endif /* OSEE_RH850_CORE0_556_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_557_ISR_CAT))
#if (OSEE_RH850_CORE0_557_ISR_CAT == 1)
_osEE_rh850_core0_ei557:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_557_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei557, .-_osEE_rh850_core0_ei557
#else
_osEE_rh850_core0_ei557:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_557_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei557, .-_osEE_rh850_core0_ei557
#endif
#endif /* OSEE_RH850_CORE0_557_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_558_ISR_CAT))
#if (OSEE_RH850_CORE0_558_ISR_CAT == 1)
_osEE_rh850_core0_ei558:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_558_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei558, .-_osEE_rh850_core0_ei558
#else
_osEE_rh850_core0_ei558:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_558_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei558, .-_osEE_rh850_core0_ei558
#endif
#endif /* OSEE_RH850_CORE0_558_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_559_ISR_CAT))
#if (OSEE_RH850_CORE0_559_ISR_CAT == 1)
_osEE_rh850_core0_ei559:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_559_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei559, .-_osEE_rh850_core0_ei559
#else
_osEE_rh850_core0_ei559:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_559_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei559, .-_osEE_rh850_core0_ei559
#endif
#endif /* OSEE_RH850_CORE0_559_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_560_ISR_CAT))
#if (OSEE_RH850_CORE0_560_ISR_CAT == 1)
_osEE_rh850_core0_ei560:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_560_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei560, .-_osEE_rh850_core0_ei560
#else
_osEE_rh850_core0_ei560:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_560_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei560, .-_osEE_rh850_core0_ei560
#endif
#endif /* OSEE_RH850_CORE0_560_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_561_ISR_CAT))
#if (OSEE_RH850_CORE0_561_ISR_CAT == 1)
_osEE_rh850_core0_ei561:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_561_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei561, .-_osEE_rh850_core0_ei561
#else
_osEE_rh850_core0_ei561:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_561_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei561, .-_osEE_rh850_core0_ei561
#endif
#endif /* OSEE_RH850_CORE0_561_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_562_ISR_CAT))
#if (OSEE_RH850_CORE0_562_ISR_CAT == 1)
_osEE_rh850_core0_ei562:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_562_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei562, .-_osEE_rh850_core0_ei562
#else
_osEE_rh850_core0_ei562:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_562_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei562, .-_osEE_rh850_core0_ei562
#endif
#endif /* OSEE_RH850_CORE0_562_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_563_ISR_CAT))
#if (OSEE_RH850_CORE0_563_ISR_CAT == 1)
_osEE_rh850_core0_ei563:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_563_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei563, .-_osEE_rh850_core0_ei563
#else
_osEE_rh850_core0_ei563:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_563_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei563, .-_osEE_rh850_core0_ei563
#endif
#endif /* OSEE_RH850_CORE0_563_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_564_ISR_CAT))
#if (OSEE_RH850_CORE0_564_ISR_CAT == 1)
_osEE_rh850_core0_ei564:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_564_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei564, .-_osEE_rh850_core0_ei564
#else
_osEE_rh850_core0_ei564:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_564_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei564, .-_osEE_rh850_core0_ei564
#endif
#endif /* OSEE_RH850_CORE0_564_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_565_ISR_CAT))
#if (OSEE_RH850_CORE0_565_ISR_CAT == 1)
_osEE_rh850_core0_ei565:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_565_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei565, .-_osEE_rh850_core0_ei565
#else
_osEE_rh850_core0_ei565:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_565_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei565, .-_osEE_rh850_core0_ei565
#endif
#endif /* OSEE_RH850_CORE0_565_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_566_ISR_CAT))
#if (OSEE_RH850_CORE0_566_ISR_CAT == 1)
_osEE_rh850_core0_ei566:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_566_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei566, .-_osEE_rh850_core0_ei566
#else
_osEE_rh850_core0_ei566:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_566_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei566, .-_osEE_rh850_core0_ei566
#endif
#endif /* OSEE_RH850_CORE0_566_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_567_ISR_CAT))
#if (OSEE_RH850_CORE0_567_ISR_CAT == 1)
_osEE_rh850_core0_ei567:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_567_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei567, .-_osEE_rh850_core0_ei567
#else
_osEE_rh850_core0_ei567:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_567_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei567, .-_osEE_rh850_core0_ei567
#endif
#endif /* OSEE_RH850_CORE0_567_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_568_ISR_CAT))
#if (OSEE_RH850_CORE0_568_ISR_CAT == 1)
_osEE_rh850_core0_ei568:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_568_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei568, .-_osEE_rh850_core0_ei568
#else
_osEE_rh850_core0_ei568:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_568_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei568, .-_osEE_rh850_core0_ei568
#endif
#endif /* OSEE_RH850_CORE0_568_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_569_ISR_CAT))
#if (OSEE_RH850_CORE0_569_ISR_CAT == 1)
_osEE_rh850_core0_ei569:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_569_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei569, .-_osEE_rh850_core0_ei569
#else
_osEE_rh850_core0_ei569:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_569_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei569, .-_osEE_rh850_core0_ei569
#endif
#endif /* OSEE_RH850_CORE0_569_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_570_ISR_CAT))
#if (OSEE_RH850_CORE0_570_ISR_CAT == 1)
_osEE_rh850_core0_ei570:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_570_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei570, .-_osEE_rh850_core0_ei570
#else
_osEE_rh850_core0_ei570:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_570_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei570, .-_osEE_rh850_core0_ei570
#endif
#endif /* OSEE_RH850_CORE0_570_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_571_ISR_CAT))
#if (OSEE_RH850_CORE0_571_ISR_CAT == 1)
_osEE_rh850_core0_ei571:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_571_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei571, .-_osEE_rh850_core0_ei571
#else
_osEE_rh850_core0_ei571:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_571_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei571, .-_osEE_rh850_core0_ei571
#endif
#endif /* OSEE_RH850_CORE0_571_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_572_ISR_CAT))
#if (OSEE_RH850_CORE0_572_ISR_CAT == 1)
_osEE_rh850_core0_ei572:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_572_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei572, .-_osEE_rh850_core0_ei572
#else
_osEE_rh850_core0_ei572:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_572_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei572, .-_osEE_rh850_core0_ei572
#endif
#endif /* OSEE_RH850_CORE0_572_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_573_ISR_CAT))
#if (OSEE_RH850_CORE0_573_ISR_CAT == 1)
_osEE_rh850_core0_ei573:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_573_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei573, .-_osEE_rh850_core0_ei573
#else
_osEE_rh850_core0_ei573:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_573_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei573, .-_osEE_rh850_core0_ei573
#endif
#endif /* OSEE_RH850_CORE0_573_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_574_ISR_CAT))
#if (OSEE_RH850_CORE0_574_ISR_CAT == 1)
_osEE_rh850_core0_ei574:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_574_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei574, .-_osEE_rh850_core0_ei574
#else
_osEE_rh850_core0_ei574:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_574_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei574, .-_osEE_rh850_core0_ei574
#endif
#endif /* OSEE_RH850_CORE0_574_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_575_ISR_CAT))
#if (OSEE_RH850_CORE0_575_ISR_CAT == 1)
_osEE_rh850_core0_ei575:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_575_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei575, .-_osEE_rh850_core0_ei575
#else
_osEE_rh850_core0_ei575:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_575_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei575, .-_osEE_rh850_core0_ei575
#endif
#endif /* OSEE_RH850_CORE0_575_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_576_ISR_CAT))
#if (OSEE_RH850_CORE0_576_ISR_CAT == 1)
_osEE_rh850_core0_ei576:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_576_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei576, .-_osEE_rh850_core0_ei576
#else
_osEE_rh850_core0_ei576:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_576_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei576, .-_osEE_rh850_core0_ei576
#endif
#endif /* OSEE_RH850_CORE0_576_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_577_ISR_CAT))
#if (OSEE_RH850_CORE0_577_ISR_CAT == 1)
_osEE_rh850_core0_ei577:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_577_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei577, .-_osEE_rh850_core0_ei577
#else
_osEE_rh850_core0_ei577:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_577_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei577, .-_osEE_rh850_core0_ei577
#endif
#endif /* OSEE_RH850_CORE0_577_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_578_ISR_CAT))
#if (OSEE_RH850_CORE0_578_ISR_CAT == 1)
_osEE_rh850_core0_ei578:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_578_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei578, .-_osEE_rh850_core0_ei578
#else
_osEE_rh850_core0_ei578:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_578_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei578, .-_osEE_rh850_core0_ei578
#endif
#endif /* OSEE_RH850_CORE0_578_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_579_ISR_CAT))
#if (OSEE_RH850_CORE0_579_ISR_CAT == 1)
_osEE_rh850_core0_ei579:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_579_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei579, .-_osEE_rh850_core0_ei579
#else
_osEE_rh850_core0_ei579:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_579_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei579, .-_osEE_rh850_core0_ei579
#endif
#endif /* OSEE_RH850_CORE0_579_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_580_ISR_CAT))
#if (OSEE_RH850_CORE0_580_ISR_CAT == 1)
_osEE_rh850_core0_ei580:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_580_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei580, .-_osEE_rh850_core0_ei580
#else
_osEE_rh850_core0_ei580:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_580_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei580, .-_osEE_rh850_core0_ei580
#endif
#endif /* OSEE_RH850_CORE0_580_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_581_ISR_CAT))
#if (OSEE_RH850_CORE0_581_ISR_CAT == 1)
_osEE_rh850_core0_ei581:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_581_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei581, .-_osEE_rh850_core0_ei581
#else
_osEE_rh850_core0_ei581:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_581_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei581, .-_osEE_rh850_core0_ei581
#endif
#endif /* OSEE_RH850_CORE0_581_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_582_ISR_CAT))
#if (OSEE_RH850_CORE0_582_ISR_CAT == 1)
_osEE_rh850_core0_ei582:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_582_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei582, .-_osEE_rh850_core0_ei582
#else
_osEE_rh850_core0_ei582:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_582_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei582, .-_osEE_rh850_core0_ei582
#endif
#endif /* OSEE_RH850_CORE0_582_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_583_ISR_CAT))
#if (OSEE_RH850_CORE0_583_ISR_CAT == 1)
_osEE_rh850_core0_ei583:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_583_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei583, .-_osEE_rh850_core0_ei583
#else
_osEE_rh850_core0_ei583:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_583_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei583, .-_osEE_rh850_core0_ei583
#endif
#endif /* OSEE_RH850_CORE0_583_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_584_ISR_CAT))
#if (OSEE_RH850_CORE0_584_ISR_CAT == 1)
_osEE_rh850_core0_ei584:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_584_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei584, .-_osEE_rh850_core0_ei584
#else
_osEE_rh850_core0_ei584:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_584_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei584, .-_osEE_rh850_core0_ei584
#endif
#endif /* OSEE_RH850_CORE0_584_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_585_ISR_CAT))
#if (OSEE_RH850_CORE0_585_ISR_CAT == 1)
_osEE_rh850_core0_ei585:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_585_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei585, .-_osEE_rh850_core0_ei585
#else
_osEE_rh850_core0_ei585:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_585_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei585, .-_osEE_rh850_core0_ei585
#endif
#endif /* OSEE_RH850_CORE0_585_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_586_ISR_CAT))
#if (OSEE_RH850_CORE0_586_ISR_CAT == 1)
_osEE_rh850_core0_ei586:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_586_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei586, .-_osEE_rh850_core0_ei586
#else
_osEE_rh850_core0_ei586:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_586_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei586, .-_osEE_rh850_core0_ei586
#endif
#endif /* OSEE_RH850_CORE0_586_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_587_ISR_CAT))
#if (OSEE_RH850_CORE0_587_ISR_CAT == 1)
_osEE_rh850_core0_ei587:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_587_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei587, .-_osEE_rh850_core0_ei587
#else
_osEE_rh850_core0_ei587:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_587_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei587, .-_osEE_rh850_core0_ei587
#endif
#endif /* OSEE_RH850_CORE0_587_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_588_ISR_CAT))
#if (OSEE_RH850_CORE0_588_ISR_CAT == 1)
_osEE_rh850_core0_ei588:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_588_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei588, .-_osEE_rh850_core0_ei588
#else
_osEE_rh850_core0_ei588:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_588_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei588, .-_osEE_rh850_core0_ei588
#endif
#endif /* OSEE_RH850_CORE0_588_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_589_ISR_CAT))
#if (OSEE_RH850_CORE0_589_ISR_CAT == 1)
_osEE_rh850_core0_ei589:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_589_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei589, .-_osEE_rh850_core0_ei589
#else
_osEE_rh850_core0_ei589:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_589_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei589, .-_osEE_rh850_core0_ei589
#endif
#endif /* OSEE_RH850_CORE0_589_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_590_ISR_CAT))
#if (OSEE_RH850_CORE0_590_ISR_CAT == 1)
_osEE_rh850_core0_ei590:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_590_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei590, .-_osEE_rh850_core0_ei590
#else
_osEE_rh850_core0_ei590:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_590_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei590, .-_osEE_rh850_core0_ei590
#endif
#endif /* OSEE_RH850_CORE0_590_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_591_ISR_CAT))
#if (OSEE_RH850_CORE0_591_ISR_CAT == 1)
_osEE_rh850_core0_ei591:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_591_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei591, .-_osEE_rh850_core0_ei591
#else
_osEE_rh850_core0_ei591:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_591_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei591, .-_osEE_rh850_core0_ei591
#endif
#endif /* OSEE_RH850_CORE0_591_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_592_ISR_CAT))
#if (OSEE_RH850_CORE0_592_ISR_CAT == 1)
_osEE_rh850_core0_ei592:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_592_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei592, .-_osEE_rh850_core0_ei592
#else
_osEE_rh850_core0_ei592:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_592_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei592, .-_osEE_rh850_core0_ei592
#endif
#endif /* OSEE_RH850_CORE0_592_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_593_ISR_CAT))
#if (OSEE_RH850_CORE0_593_ISR_CAT == 1)
_osEE_rh850_core0_ei593:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_593_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei593, .-_osEE_rh850_core0_ei593
#else
_osEE_rh850_core0_ei593:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_593_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei593, .-_osEE_rh850_core0_ei593
#endif
#endif /* OSEE_RH850_CORE0_593_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_594_ISR_CAT))
#if (OSEE_RH850_CORE0_594_ISR_CAT == 1)
_osEE_rh850_core0_ei594:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_594_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei594, .-_osEE_rh850_core0_ei594
#else
_osEE_rh850_core0_ei594:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_594_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei594, .-_osEE_rh850_core0_ei594
#endif
#endif /* OSEE_RH850_CORE0_594_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_595_ISR_CAT))
#if (OSEE_RH850_CORE0_595_ISR_CAT == 1)
_osEE_rh850_core0_ei595:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_595_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei595, .-_osEE_rh850_core0_ei595
#else
_osEE_rh850_core0_ei595:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_595_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei595, .-_osEE_rh850_core0_ei595
#endif
#endif /* OSEE_RH850_CORE0_595_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_596_ISR_CAT))
#if (OSEE_RH850_CORE0_596_ISR_CAT == 1)
_osEE_rh850_core0_ei596:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_596_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei596, .-_osEE_rh850_core0_ei596
#else
_osEE_rh850_core0_ei596:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_596_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei596, .-_osEE_rh850_core0_ei596
#endif
#endif /* OSEE_RH850_CORE0_596_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_597_ISR_CAT))
#if (OSEE_RH850_CORE0_597_ISR_CAT == 1)
_osEE_rh850_core0_ei597:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_597_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei597, .-_osEE_rh850_core0_ei597
#else
_osEE_rh850_core0_ei597:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_597_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei597, .-_osEE_rh850_core0_ei597
#endif
#endif /* OSEE_RH850_CORE0_597_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_598_ISR_CAT))
#if (OSEE_RH850_CORE0_598_ISR_CAT == 1)
_osEE_rh850_core0_ei598:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_598_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei598, .-_osEE_rh850_core0_ei598
#else
_osEE_rh850_core0_ei598:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_598_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei598, .-_osEE_rh850_core0_ei598
#endif
#endif /* OSEE_RH850_CORE0_598_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_599_ISR_CAT))
#if (OSEE_RH850_CORE0_599_ISR_CAT == 1)
_osEE_rh850_core0_ei599:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_599_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei599, .-_osEE_rh850_core0_ei599
#else
_osEE_rh850_core0_ei599:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_599_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei599, .-_osEE_rh850_core0_ei599
#endif
#endif /* OSEE_RH850_CORE0_599_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_600_ISR_CAT))
#if (OSEE_RH850_CORE0_600_ISR_CAT == 1)
_osEE_rh850_core0_ei600:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_600_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei600, .-_osEE_rh850_core0_ei600
#else
_osEE_rh850_core0_ei600:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_600_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei600, .-_osEE_rh850_core0_ei600
#endif
#endif /* OSEE_RH850_CORE0_600_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_601_ISR_CAT))
#if (OSEE_RH850_CORE0_601_ISR_CAT == 1)
_osEE_rh850_core0_ei601:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_601_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei601, .-_osEE_rh850_core0_ei601
#else
_osEE_rh850_core0_ei601:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_601_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei601, .-_osEE_rh850_core0_ei601
#endif
#endif /* OSEE_RH850_CORE0_601_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_602_ISR_CAT))
#if (OSEE_RH850_CORE0_602_ISR_CAT == 1)
_osEE_rh850_core0_ei602:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_602_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei602, .-_osEE_rh850_core0_ei602
#else
_osEE_rh850_core0_ei602:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_602_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei602, .-_osEE_rh850_core0_ei602
#endif
#endif /* OSEE_RH850_CORE0_602_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_603_ISR_CAT))
#if (OSEE_RH850_CORE0_603_ISR_CAT == 1)
_osEE_rh850_core0_ei603:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_603_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei603, .-_osEE_rh850_core0_ei603
#else
_osEE_rh850_core0_ei603:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_603_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei603, .-_osEE_rh850_core0_ei603
#endif
#endif /* OSEE_RH850_CORE0_603_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_604_ISR_CAT))
#if (OSEE_RH850_CORE0_604_ISR_CAT == 1)
_osEE_rh850_core0_ei604:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_604_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei604, .-_osEE_rh850_core0_ei604
#else
_osEE_rh850_core0_ei604:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_604_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei604, .-_osEE_rh850_core0_ei604
#endif
#endif /* OSEE_RH850_CORE0_604_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_605_ISR_CAT))
#if (OSEE_RH850_CORE0_605_ISR_CAT == 1)
_osEE_rh850_core0_ei605:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_605_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei605, .-_osEE_rh850_core0_ei605
#else
_osEE_rh850_core0_ei605:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_605_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei605, .-_osEE_rh850_core0_ei605
#endif
#endif /* OSEE_RH850_CORE0_605_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_606_ISR_CAT))
#if (OSEE_RH850_CORE0_606_ISR_CAT == 1)
_osEE_rh850_core0_ei606:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_606_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei606, .-_osEE_rh850_core0_ei606
#else
_osEE_rh850_core0_ei606:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_606_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei606, .-_osEE_rh850_core0_ei606
#endif
#endif /* OSEE_RH850_CORE0_606_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_607_ISR_CAT))
#if (OSEE_RH850_CORE0_607_ISR_CAT == 1)
_osEE_rh850_core0_ei607:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_607_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei607, .-_osEE_rh850_core0_ei607
#else
_osEE_rh850_core0_ei607:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_607_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei607, .-_osEE_rh850_core0_ei607
#endif
#endif /* OSEE_RH850_CORE0_607_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_608_ISR_CAT))
#if (OSEE_RH850_CORE0_608_ISR_CAT == 1)
_osEE_rh850_core0_ei608:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_608_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei608, .-_osEE_rh850_core0_ei608
#else
_osEE_rh850_core0_ei608:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_608_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei608, .-_osEE_rh850_core0_ei608
#endif
#endif /* OSEE_RH850_CORE0_608_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_609_ISR_CAT))
#if (OSEE_RH850_CORE0_609_ISR_CAT == 1)
_osEE_rh850_core0_ei609:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_609_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei609, .-_osEE_rh850_core0_ei609
#else
_osEE_rh850_core0_ei609:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_609_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei609, .-_osEE_rh850_core0_ei609
#endif
#endif /* OSEE_RH850_CORE0_609_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_610_ISR_CAT))
#if (OSEE_RH850_CORE0_610_ISR_CAT == 1)
_osEE_rh850_core0_ei610:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_610_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei610, .-_osEE_rh850_core0_ei610
#else
_osEE_rh850_core0_ei610:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_610_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei610, .-_osEE_rh850_core0_ei610
#endif
#endif /* OSEE_RH850_CORE0_610_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_611_ISR_CAT))
#if (OSEE_RH850_CORE0_611_ISR_CAT == 1)
_osEE_rh850_core0_ei611:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_611_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei611, .-_osEE_rh850_core0_ei611
#else
_osEE_rh850_core0_ei611:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_611_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei611, .-_osEE_rh850_core0_ei611
#endif
#endif /* OSEE_RH850_CORE0_611_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_612_ISR_CAT))
#if (OSEE_RH850_CORE0_612_ISR_CAT == 1)
_osEE_rh850_core0_ei612:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_612_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei612, .-_osEE_rh850_core0_ei612
#else
_osEE_rh850_core0_ei612:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_612_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei612, .-_osEE_rh850_core0_ei612
#endif
#endif /* OSEE_RH850_CORE0_612_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_613_ISR_CAT))
#if (OSEE_RH850_CORE0_613_ISR_CAT == 1)
_osEE_rh850_core0_ei613:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_613_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei613, .-_osEE_rh850_core0_ei613
#else
_osEE_rh850_core0_ei613:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_613_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei613, .-_osEE_rh850_core0_ei613
#endif
#endif /* OSEE_RH850_CORE0_613_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_614_ISR_CAT))
#if (OSEE_RH850_CORE0_614_ISR_CAT == 1)
_osEE_rh850_core0_ei614:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_614_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei614, .-_osEE_rh850_core0_ei614
#else
_osEE_rh850_core0_ei614:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_614_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei614, .-_osEE_rh850_core0_ei614
#endif
#endif /* OSEE_RH850_CORE0_614_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_615_ISR_CAT))
#if (OSEE_RH850_CORE0_615_ISR_CAT == 1)
_osEE_rh850_core0_ei615:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_615_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei615, .-_osEE_rh850_core0_ei615
#else
_osEE_rh850_core0_ei615:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_615_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei615, .-_osEE_rh850_core0_ei615
#endif
#endif /* OSEE_RH850_CORE0_615_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_616_ISR_CAT))
#if (OSEE_RH850_CORE0_616_ISR_CAT == 1)
_osEE_rh850_core0_ei616:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_616_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei616, .-_osEE_rh850_core0_ei616
#else
_osEE_rh850_core0_ei616:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_616_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei616, .-_osEE_rh850_core0_ei616
#endif
#endif /* OSEE_RH850_CORE0_616_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_617_ISR_CAT))
#if (OSEE_RH850_CORE0_617_ISR_CAT == 1)
_osEE_rh850_core0_ei617:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_617_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei617, .-_osEE_rh850_core0_ei617
#else
_osEE_rh850_core0_ei617:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_617_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei617, .-_osEE_rh850_core0_ei617
#endif
#endif /* OSEE_RH850_CORE0_617_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_618_ISR_CAT))
#if (OSEE_RH850_CORE0_618_ISR_CAT == 1)
_osEE_rh850_core0_ei618:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_618_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei618, .-_osEE_rh850_core0_ei618
#else
_osEE_rh850_core0_ei618:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_618_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei618, .-_osEE_rh850_core0_ei618
#endif
#endif /* OSEE_RH850_CORE0_618_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_619_ISR_CAT))
#if (OSEE_RH850_CORE0_619_ISR_CAT == 1)
_osEE_rh850_core0_ei619:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_619_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei619, .-_osEE_rh850_core0_ei619
#else
_osEE_rh850_core0_ei619:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_619_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei619, .-_osEE_rh850_core0_ei619
#endif
#endif /* OSEE_RH850_CORE0_619_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_620_ISR_CAT))
#if (OSEE_RH850_CORE0_620_ISR_CAT == 1)
_osEE_rh850_core0_ei620:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_620_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei620, .-_osEE_rh850_core0_ei620
#else
_osEE_rh850_core0_ei620:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_620_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei620, .-_osEE_rh850_core0_ei620
#endif
#endif /* OSEE_RH850_CORE0_620_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_621_ISR_CAT))
#if (OSEE_RH850_CORE0_621_ISR_CAT == 1)
_osEE_rh850_core0_ei621:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_621_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei621, .-_osEE_rh850_core0_ei621
#else
_osEE_rh850_core0_ei621:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_621_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei621, .-_osEE_rh850_core0_ei621
#endif
#endif /* OSEE_RH850_CORE0_621_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_622_ISR_CAT))
#if (OSEE_RH850_CORE0_622_ISR_CAT == 1)
_osEE_rh850_core0_ei622:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_622_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei622, .-_osEE_rh850_core0_ei622
#else
_osEE_rh850_core0_ei622:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_622_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei622, .-_osEE_rh850_core0_ei622
#endif
#endif /* OSEE_RH850_CORE0_622_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_623_ISR_CAT))
#if (OSEE_RH850_CORE0_623_ISR_CAT == 1)
_osEE_rh850_core0_ei623:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_623_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei623, .-_osEE_rh850_core0_ei623
#else
_osEE_rh850_core0_ei623:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_623_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei623, .-_osEE_rh850_core0_ei623
#endif
#endif /* OSEE_RH850_CORE0_623_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_624_ISR_CAT))
#if (OSEE_RH850_CORE0_624_ISR_CAT == 1)
_osEE_rh850_core0_ei624:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_624_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei624, .-_osEE_rh850_core0_ei624
#else
_osEE_rh850_core0_ei624:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_624_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei624, .-_osEE_rh850_core0_ei624
#endif
#endif /* OSEE_RH850_CORE0_624_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_625_ISR_CAT))
#if (OSEE_RH850_CORE0_625_ISR_CAT == 1)
_osEE_rh850_core0_ei625:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_625_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei625, .-_osEE_rh850_core0_ei625
#else
_osEE_rh850_core0_ei625:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_625_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei625, .-_osEE_rh850_core0_ei625
#endif
#endif /* OSEE_RH850_CORE0_625_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_626_ISR_CAT))
#if (OSEE_RH850_CORE0_626_ISR_CAT == 1)
_osEE_rh850_core0_ei626:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_626_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei626, .-_osEE_rh850_core0_ei626
#else
_osEE_rh850_core0_ei626:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_626_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei626, .-_osEE_rh850_core0_ei626
#endif
#endif /* OSEE_RH850_CORE0_626_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_627_ISR_CAT))
#if (OSEE_RH850_CORE0_627_ISR_CAT == 1)
_osEE_rh850_core0_ei627:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_627_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei627, .-_osEE_rh850_core0_ei627
#else
_osEE_rh850_core0_ei627:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_627_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei627, .-_osEE_rh850_core0_ei627
#endif
#endif /* OSEE_RH850_CORE0_627_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_628_ISR_CAT))
#if (OSEE_RH850_CORE0_628_ISR_CAT == 1)
_osEE_rh850_core0_ei628:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_628_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei628, .-_osEE_rh850_core0_ei628
#else
_osEE_rh850_core0_ei628:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_628_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei628, .-_osEE_rh850_core0_ei628
#endif
#endif /* OSEE_RH850_CORE0_628_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_629_ISR_CAT))
#if (OSEE_RH850_CORE0_629_ISR_CAT == 1)
_osEE_rh850_core0_ei629:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_629_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei629, .-_osEE_rh850_core0_ei629
#else
_osEE_rh850_core0_ei629:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_629_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei629, .-_osEE_rh850_core0_ei629
#endif
#endif /* OSEE_RH850_CORE0_629_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_630_ISR_CAT))
#if (OSEE_RH850_CORE0_630_ISR_CAT == 1)
_osEE_rh850_core0_ei630:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_630_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei630, .-_osEE_rh850_core0_ei630
#else
_osEE_rh850_core0_ei630:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_630_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei630, .-_osEE_rh850_core0_ei630
#endif
#endif /* OSEE_RH850_CORE0_630_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_631_ISR_CAT))
#if (OSEE_RH850_CORE0_631_ISR_CAT == 1)
_osEE_rh850_core0_ei631:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_631_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei631, .-_osEE_rh850_core0_ei631
#else
_osEE_rh850_core0_ei631:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_631_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei631, .-_osEE_rh850_core0_ei631
#endif
#endif /* OSEE_RH850_CORE0_631_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_632_ISR_CAT))
#if (OSEE_RH850_CORE0_632_ISR_CAT == 1)
_osEE_rh850_core0_ei632:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_632_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei632, .-_osEE_rh850_core0_ei632
#else
_osEE_rh850_core0_ei632:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_632_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei632, .-_osEE_rh850_core0_ei632
#endif
#endif /* OSEE_RH850_CORE0_632_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_633_ISR_CAT))
#if (OSEE_RH850_CORE0_633_ISR_CAT == 1)
_osEE_rh850_core0_ei633:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_633_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei633, .-_osEE_rh850_core0_ei633
#else
_osEE_rh850_core0_ei633:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_633_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei633, .-_osEE_rh850_core0_ei633
#endif
#endif /* OSEE_RH850_CORE0_633_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_634_ISR_CAT))
#if (OSEE_RH850_CORE0_634_ISR_CAT == 1)
_osEE_rh850_core0_ei634:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_634_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei634, .-_osEE_rh850_core0_ei634
#else
_osEE_rh850_core0_ei634:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_634_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei634, .-_osEE_rh850_core0_ei634
#endif
#endif /* OSEE_RH850_CORE0_634_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_635_ISR_CAT))
#if (OSEE_RH850_CORE0_635_ISR_CAT == 1)
_osEE_rh850_core0_ei635:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_635_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei635, .-_osEE_rh850_core0_ei635
#else
_osEE_rh850_core0_ei635:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_635_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei635, .-_osEE_rh850_core0_ei635
#endif
#endif /* OSEE_RH850_CORE0_635_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_636_ISR_CAT))
#if (OSEE_RH850_CORE0_636_ISR_CAT == 1)
_osEE_rh850_core0_ei636:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_636_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei636, .-_osEE_rh850_core0_ei636
#else
_osEE_rh850_core0_ei636:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_636_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei636, .-_osEE_rh850_core0_ei636
#endif
#endif /* OSEE_RH850_CORE0_636_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_637_ISR_CAT))
#if (OSEE_RH850_CORE0_637_ISR_CAT == 1)
_osEE_rh850_core0_ei637:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_637_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei637, .-_osEE_rh850_core0_ei637
#else
_osEE_rh850_core0_ei637:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_637_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei637, .-_osEE_rh850_core0_ei637
#endif
#endif /* OSEE_RH850_CORE0_637_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_638_ISR_CAT))
#if (OSEE_RH850_CORE0_638_ISR_CAT == 1)
_osEE_rh850_core0_ei638:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_638_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei638, .-_osEE_rh850_core0_ei638
#else
_osEE_rh850_core0_ei638:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_638_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei638, .-_osEE_rh850_core0_ei638
#endif
#endif /* OSEE_RH850_CORE0_638_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_639_ISR_CAT))
#if (OSEE_RH850_CORE0_639_ISR_CAT == 1)
_osEE_rh850_core0_ei639:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_639_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei639, .-_osEE_rh850_core0_ei639
#else
_osEE_rh850_core0_ei639:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_639_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei639, .-_osEE_rh850_core0_ei639
#endif
#endif /* OSEE_RH850_CORE0_639_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_640_ISR_CAT))
#if (OSEE_RH850_CORE0_640_ISR_CAT == 1)
_osEE_rh850_core0_ei640:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_640_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei640, .-_osEE_rh850_core0_ei640
#else
_osEE_rh850_core0_ei640:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_640_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei640, .-_osEE_rh850_core0_ei640
#endif
#endif /* OSEE_RH850_CORE0_640_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_641_ISR_CAT))
#if (OSEE_RH850_CORE0_641_ISR_CAT == 1)
_osEE_rh850_core0_ei641:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_641_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei641, .-_osEE_rh850_core0_ei641
#else
_osEE_rh850_core0_ei641:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_641_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei641, .-_osEE_rh850_core0_ei641
#endif
#endif /* OSEE_RH850_CORE0_641_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_642_ISR_CAT))
#if (OSEE_RH850_CORE0_642_ISR_CAT == 1)
_osEE_rh850_core0_ei642:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_642_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei642, .-_osEE_rh850_core0_ei642
#else
_osEE_rh850_core0_ei642:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_642_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei642, .-_osEE_rh850_core0_ei642
#endif
#endif /* OSEE_RH850_CORE0_642_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_643_ISR_CAT))
#if (OSEE_RH850_CORE0_643_ISR_CAT == 1)
_osEE_rh850_core0_ei643:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_643_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei643, .-_osEE_rh850_core0_ei643
#else
_osEE_rh850_core0_ei643:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_643_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei643, .-_osEE_rh850_core0_ei643
#endif
#endif /* OSEE_RH850_CORE0_643_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_644_ISR_CAT))
#if (OSEE_RH850_CORE0_644_ISR_CAT == 1)
_osEE_rh850_core0_ei644:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_644_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei644, .-_osEE_rh850_core0_ei644
#else
_osEE_rh850_core0_ei644:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_644_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei644, .-_osEE_rh850_core0_ei644
#endif
#endif /* OSEE_RH850_CORE0_644_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_645_ISR_CAT))
#if (OSEE_RH850_CORE0_645_ISR_CAT == 1)
_osEE_rh850_core0_ei645:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_645_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei645, .-_osEE_rh850_core0_ei645
#else
_osEE_rh850_core0_ei645:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_645_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei645, .-_osEE_rh850_core0_ei645
#endif
#endif /* OSEE_RH850_CORE0_645_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_646_ISR_CAT))
#if (OSEE_RH850_CORE0_646_ISR_CAT == 1)
_osEE_rh850_core0_ei646:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_646_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei646, .-_osEE_rh850_core0_ei646
#else
_osEE_rh850_core0_ei646:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_646_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei646, .-_osEE_rh850_core0_ei646
#endif
#endif /* OSEE_RH850_CORE0_646_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_647_ISR_CAT))
#if (OSEE_RH850_CORE0_647_ISR_CAT == 1)
_osEE_rh850_core0_ei647:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_647_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei647, .-_osEE_rh850_core0_ei647
#else
_osEE_rh850_core0_ei647:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_647_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei647, .-_osEE_rh850_core0_ei647
#endif
#endif /* OSEE_RH850_CORE0_647_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_648_ISR_CAT))
#if (OSEE_RH850_CORE0_648_ISR_CAT == 1)
_osEE_rh850_core0_ei648:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_648_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei648, .-_osEE_rh850_core0_ei648
#else
_osEE_rh850_core0_ei648:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_648_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei648, .-_osEE_rh850_core0_ei648
#endif
#endif /* OSEE_RH850_CORE0_648_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_649_ISR_CAT))
#if (OSEE_RH850_CORE0_649_ISR_CAT == 1)
_osEE_rh850_core0_ei649:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_649_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei649, .-_osEE_rh850_core0_ei649
#else
_osEE_rh850_core0_ei649:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_649_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei649, .-_osEE_rh850_core0_ei649
#endif
#endif /* OSEE_RH850_CORE0_649_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_650_ISR_CAT))
#if (OSEE_RH850_CORE0_650_ISR_CAT == 1)
_osEE_rh850_core0_ei650:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_650_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei650, .-_osEE_rh850_core0_ei650
#else
_osEE_rh850_core0_ei650:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_650_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei650, .-_osEE_rh850_core0_ei650
#endif
#endif /* OSEE_RH850_CORE0_650_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_651_ISR_CAT))
#if (OSEE_RH850_CORE0_651_ISR_CAT == 1)
_osEE_rh850_core0_ei651:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_651_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei651, .-_osEE_rh850_core0_ei651
#else
_osEE_rh850_core0_ei651:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_651_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei651, .-_osEE_rh850_core0_ei651
#endif
#endif /* OSEE_RH850_CORE0_651_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_652_ISR_CAT))
#if (OSEE_RH850_CORE0_652_ISR_CAT == 1)
_osEE_rh850_core0_ei652:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_652_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei652, .-_osEE_rh850_core0_ei652
#else
_osEE_rh850_core0_ei652:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_652_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei652, .-_osEE_rh850_core0_ei652
#endif
#endif /* OSEE_RH850_CORE0_652_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_653_ISR_CAT))
#if (OSEE_RH850_CORE0_653_ISR_CAT == 1)
_osEE_rh850_core0_ei653:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_653_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei653, .-_osEE_rh850_core0_ei653
#else
_osEE_rh850_core0_ei653:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_653_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei653, .-_osEE_rh850_core0_ei653
#endif
#endif /* OSEE_RH850_CORE0_653_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_654_ISR_CAT))
#if (OSEE_RH850_CORE0_654_ISR_CAT == 1)
_osEE_rh850_core0_ei654:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_654_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei654, .-_osEE_rh850_core0_ei654
#else
_osEE_rh850_core0_ei654:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_654_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei654, .-_osEE_rh850_core0_ei654
#endif
#endif /* OSEE_RH850_CORE0_654_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_655_ISR_CAT))
#if (OSEE_RH850_CORE0_655_ISR_CAT == 1)
_osEE_rh850_core0_ei655:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_655_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei655, .-_osEE_rh850_core0_ei655
#else
_osEE_rh850_core0_ei655:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_655_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei655, .-_osEE_rh850_core0_ei655
#endif
#endif /* OSEE_RH850_CORE0_655_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_656_ISR_CAT))
#if (OSEE_RH850_CORE0_656_ISR_CAT == 1)
_osEE_rh850_core0_ei656:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_656_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei656, .-_osEE_rh850_core0_ei656
#else
_osEE_rh850_core0_ei656:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_656_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei656, .-_osEE_rh850_core0_ei656
#endif
#endif /* OSEE_RH850_CORE0_656_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_657_ISR_CAT))
#if (OSEE_RH850_CORE0_657_ISR_CAT == 1)
_osEE_rh850_core0_ei657:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_657_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei657, .-_osEE_rh850_core0_ei657
#else
_osEE_rh850_core0_ei657:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_657_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei657, .-_osEE_rh850_core0_ei657
#endif
#endif /* OSEE_RH850_CORE0_657_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_658_ISR_CAT))
#if (OSEE_RH850_CORE0_658_ISR_CAT == 1)
_osEE_rh850_core0_ei658:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_658_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei658, .-_osEE_rh850_core0_ei658
#else
_osEE_rh850_core0_ei658:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_658_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei658, .-_osEE_rh850_core0_ei658
#endif
#endif /* OSEE_RH850_CORE0_658_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_659_ISR_CAT))
#if (OSEE_RH850_CORE0_659_ISR_CAT == 1)
_osEE_rh850_core0_ei659:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_659_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei659, .-_osEE_rh850_core0_ei659
#else
_osEE_rh850_core0_ei659:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_659_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei659, .-_osEE_rh850_core0_ei659
#endif
#endif /* OSEE_RH850_CORE0_659_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_660_ISR_CAT))
#if (OSEE_RH850_CORE0_660_ISR_CAT == 1)
_osEE_rh850_core0_ei660:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_660_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei660, .-_osEE_rh850_core0_ei660
#else
_osEE_rh850_core0_ei660:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_660_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei660, .-_osEE_rh850_core0_ei660
#endif
#endif /* OSEE_RH850_CORE0_660_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_661_ISR_CAT))
#if (OSEE_RH850_CORE0_661_ISR_CAT == 1)
_osEE_rh850_core0_ei661:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_661_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei661, .-_osEE_rh850_core0_ei661
#else
_osEE_rh850_core0_ei661:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_661_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei661, .-_osEE_rh850_core0_ei661
#endif
#endif /* OSEE_RH850_CORE0_661_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_662_ISR_CAT))
#if (OSEE_RH850_CORE0_662_ISR_CAT == 1)
_osEE_rh850_core0_ei662:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_662_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei662, .-_osEE_rh850_core0_ei662
#else
_osEE_rh850_core0_ei662:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_662_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei662, .-_osEE_rh850_core0_ei662
#endif
#endif /* OSEE_RH850_CORE0_662_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_663_ISR_CAT))
#if (OSEE_RH850_CORE0_663_ISR_CAT == 1)
_osEE_rh850_core0_ei663:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_663_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei663, .-_osEE_rh850_core0_ei663
#else
_osEE_rh850_core0_ei663:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_663_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei663, .-_osEE_rh850_core0_ei663
#endif
#endif /* OSEE_RH850_CORE0_663_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_664_ISR_CAT))
#if (OSEE_RH850_CORE0_664_ISR_CAT == 1)
_osEE_rh850_core0_ei664:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_664_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei664, .-_osEE_rh850_core0_ei664
#else
_osEE_rh850_core0_ei664:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_664_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei664, .-_osEE_rh850_core0_ei664
#endif
#endif /* OSEE_RH850_CORE0_664_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_665_ISR_CAT))
#if (OSEE_RH850_CORE0_665_ISR_CAT == 1)
_osEE_rh850_core0_ei665:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_665_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei665, .-_osEE_rh850_core0_ei665
#else
_osEE_rh850_core0_ei665:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_665_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei665, .-_osEE_rh850_core0_ei665
#endif
#endif /* OSEE_RH850_CORE0_665_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_666_ISR_CAT))
#if (OSEE_RH850_CORE0_666_ISR_CAT == 1)
_osEE_rh850_core0_ei666:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_666_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei666, .-_osEE_rh850_core0_ei666
#else
_osEE_rh850_core0_ei666:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_666_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei666, .-_osEE_rh850_core0_ei666
#endif
#endif /* OSEE_RH850_CORE0_666_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_667_ISR_CAT))
#if (OSEE_RH850_CORE0_667_ISR_CAT == 1)
_osEE_rh850_core0_ei667:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_667_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei667, .-_osEE_rh850_core0_ei667
#else
_osEE_rh850_core0_ei667:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_667_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei667, .-_osEE_rh850_core0_ei667
#endif
#endif /* OSEE_RH850_CORE0_667_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_668_ISR_CAT))
#if (OSEE_RH850_CORE0_668_ISR_CAT == 1)
_osEE_rh850_core0_ei668:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_668_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei668, .-_osEE_rh850_core0_ei668
#else
_osEE_rh850_core0_ei668:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_668_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei668, .-_osEE_rh850_core0_ei668
#endif
#endif /* OSEE_RH850_CORE0_668_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_669_ISR_CAT))
#if (OSEE_RH850_CORE0_669_ISR_CAT == 1)
_osEE_rh850_core0_ei669:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_669_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei669, .-_osEE_rh850_core0_ei669
#else
_osEE_rh850_core0_ei669:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_669_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei669, .-_osEE_rh850_core0_ei669
#endif
#endif /* OSEE_RH850_CORE0_669_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_670_ISR_CAT))
#if (OSEE_RH850_CORE0_670_ISR_CAT == 1)
_osEE_rh850_core0_ei670:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_670_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei670, .-_osEE_rh850_core0_ei670
#else
_osEE_rh850_core0_ei670:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_670_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei670, .-_osEE_rh850_core0_ei670
#endif
#endif /* OSEE_RH850_CORE0_670_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_671_ISR_CAT))
#if (OSEE_RH850_CORE0_671_ISR_CAT == 1)
_osEE_rh850_core0_ei671:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_671_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei671, .-_osEE_rh850_core0_ei671
#else
_osEE_rh850_core0_ei671:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_671_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei671, .-_osEE_rh850_core0_ei671
#endif
#endif /* OSEE_RH850_CORE0_671_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_672_ISR_CAT))
#if (OSEE_RH850_CORE0_672_ISR_CAT == 1)
_osEE_rh850_core0_ei672:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_672_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei672, .-_osEE_rh850_core0_ei672
#else
_osEE_rh850_core0_ei672:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_672_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei672, .-_osEE_rh850_core0_ei672
#endif
#endif /* OSEE_RH850_CORE0_672_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_673_ISR_CAT))
#if (OSEE_RH850_CORE0_673_ISR_CAT == 1)
_osEE_rh850_core0_ei673:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_673_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei673, .-_osEE_rh850_core0_ei673
#else
_osEE_rh850_core0_ei673:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_673_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei673, .-_osEE_rh850_core0_ei673
#endif
#endif /* OSEE_RH850_CORE0_673_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_674_ISR_CAT))
#if (OSEE_RH850_CORE0_674_ISR_CAT == 1)
_osEE_rh850_core0_ei674:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_674_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei674, .-_osEE_rh850_core0_ei674
#else
_osEE_rh850_core0_ei674:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_674_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei674, .-_osEE_rh850_core0_ei674
#endif
#endif /* OSEE_RH850_CORE0_674_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_675_ISR_CAT))
#if (OSEE_RH850_CORE0_675_ISR_CAT == 1)
_osEE_rh850_core0_ei675:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_675_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei675, .-_osEE_rh850_core0_ei675
#else
_osEE_rh850_core0_ei675:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_675_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei675, .-_osEE_rh850_core0_ei675
#endif
#endif /* OSEE_RH850_CORE0_675_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_676_ISR_CAT))
#if (OSEE_RH850_CORE0_676_ISR_CAT == 1)
_osEE_rh850_core0_ei676:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_676_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei676, .-_osEE_rh850_core0_ei676
#else
_osEE_rh850_core0_ei676:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_676_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei676, .-_osEE_rh850_core0_ei676
#endif
#endif /* OSEE_RH850_CORE0_676_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_677_ISR_CAT))
#if (OSEE_RH850_CORE0_677_ISR_CAT == 1)
_osEE_rh850_core0_ei677:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_677_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei677, .-_osEE_rh850_core0_ei677
#else
_osEE_rh850_core0_ei677:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_677_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei677, .-_osEE_rh850_core0_ei677
#endif
#endif /* OSEE_RH850_CORE0_677_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_678_ISR_CAT))
#if (OSEE_RH850_CORE0_678_ISR_CAT == 1)
_osEE_rh850_core0_ei678:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_678_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei678, .-_osEE_rh850_core0_ei678
#else
_osEE_rh850_core0_ei678:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_678_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei678, .-_osEE_rh850_core0_ei678
#endif
#endif /* OSEE_RH850_CORE0_678_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_679_ISR_CAT))
#if (OSEE_RH850_CORE0_679_ISR_CAT == 1)
_osEE_rh850_core0_ei679:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_679_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei679, .-_osEE_rh850_core0_ei679
#else
_osEE_rh850_core0_ei679:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_679_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei679, .-_osEE_rh850_core0_ei679
#endif
#endif /* OSEE_RH850_CORE0_679_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_680_ISR_CAT))
#if (OSEE_RH850_CORE0_680_ISR_CAT == 1)
_osEE_rh850_core0_ei680:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_680_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei680, .-_osEE_rh850_core0_ei680
#else
_osEE_rh850_core0_ei680:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_680_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei680, .-_osEE_rh850_core0_ei680
#endif
#endif /* OSEE_RH850_CORE0_680_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_681_ISR_CAT))
#if (OSEE_RH850_CORE0_681_ISR_CAT == 1)
_osEE_rh850_core0_ei681:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_681_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei681, .-_osEE_rh850_core0_ei681
#else
_osEE_rh850_core0_ei681:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_681_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei681, .-_osEE_rh850_core0_ei681
#endif
#endif /* OSEE_RH850_CORE0_681_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_682_ISR_CAT))
#if (OSEE_RH850_CORE0_682_ISR_CAT == 1)
_osEE_rh850_core0_ei682:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_682_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei682, .-_osEE_rh850_core0_ei682
#else
_osEE_rh850_core0_ei682:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_682_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei682, .-_osEE_rh850_core0_ei682
#endif
#endif /* OSEE_RH850_CORE0_682_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_683_ISR_CAT))
#if (OSEE_RH850_CORE0_683_ISR_CAT == 1)
_osEE_rh850_core0_ei683:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_683_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei683, .-_osEE_rh850_core0_ei683
#else
_osEE_rh850_core0_ei683:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_683_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei683, .-_osEE_rh850_core0_ei683
#endif
#endif /* OSEE_RH850_CORE0_683_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_684_ISR_CAT))
#if (OSEE_RH850_CORE0_684_ISR_CAT == 1)
_osEE_rh850_core0_ei684:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_684_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei684, .-_osEE_rh850_core0_ei684
#else
_osEE_rh850_core0_ei684:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_684_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei684, .-_osEE_rh850_core0_ei684
#endif
#endif /* OSEE_RH850_CORE0_684_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_685_ISR_CAT))
#if (OSEE_RH850_CORE0_685_ISR_CAT == 1)
_osEE_rh850_core0_ei685:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_685_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei685, .-_osEE_rh850_core0_ei685
#else
_osEE_rh850_core0_ei685:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_685_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei685, .-_osEE_rh850_core0_ei685
#endif
#endif /* OSEE_RH850_CORE0_685_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_686_ISR_CAT))
#if (OSEE_RH850_CORE0_686_ISR_CAT == 1)
_osEE_rh850_core0_ei686:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_686_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei686, .-_osEE_rh850_core0_ei686
#else
_osEE_rh850_core0_ei686:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_686_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei686, .-_osEE_rh850_core0_ei686
#endif
#endif /* OSEE_RH850_CORE0_686_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_687_ISR_CAT))
#if (OSEE_RH850_CORE0_687_ISR_CAT == 1)
_osEE_rh850_core0_ei687:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_687_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei687, .-_osEE_rh850_core0_ei687
#else
_osEE_rh850_core0_ei687:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_687_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei687, .-_osEE_rh850_core0_ei687
#endif
#endif /* OSEE_RH850_CORE0_687_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_688_ISR_CAT))
#if (OSEE_RH850_CORE0_688_ISR_CAT == 1)
_osEE_rh850_core0_ei688:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_688_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei688, .-_osEE_rh850_core0_ei688
#else
_osEE_rh850_core0_ei688:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_688_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei688, .-_osEE_rh850_core0_ei688
#endif
#endif /* OSEE_RH850_CORE0_688_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_689_ISR_CAT))
#if (OSEE_RH850_CORE0_689_ISR_CAT == 1)
_osEE_rh850_core0_ei689:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_689_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei689, .-_osEE_rh850_core0_ei689
#else
_osEE_rh850_core0_ei689:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_689_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei689, .-_osEE_rh850_core0_ei689
#endif
#endif /* OSEE_RH850_CORE0_689_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_690_ISR_CAT))
#if (OSEE_RH850_CORE0_690_ISR_CAT == 1)
_osEE_rh850_core0_ei690:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_690_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei690, .-_osEE_rh850_core0_ei690
#else
_osEE_rh850_core0_ei690:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_690_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei690, .-_osEE_rh850_core0_ei690
#endif
#endif /* OSEE_RH850_CORE0_690_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_691_ISR_CAT))
#if (OSEE_RH850_CORE0_691_ISR_CAT == 1)
_osEE_rh850_core0_ei691:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_691_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei691, .-_osEE_rh850_core0_ei691
#else
_osEE_rh850_core0_ei691:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_691_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei691, .-_osEE_rh850_core0_ei691
#endif
#endif /* OSEE_RH850_CORE0_691_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_692_ISR_CAT))
#if (OSEE_RH850_CORE0_692_ISR_CAT == 1)
_osEE_rh850_core0_ei692:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_692_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei692, .-_osEE_rh850_core0_ei692
#else
_osEE_rh850_core0_ei692:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_692_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei692, .-_osEE_rh850_core0_ei692
#endif
#endif /* OSEE_RH850_CORE0_692_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_693_ISR_CAT))
#if (OSEE_RH850_CORE0_693_ISR_CAT == 1)
_osEE_rh850_core0_ei693:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_693_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei693, .-_osEE_rh850_core0_ei693
#else
_osEE_rh850_core0_ei693:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_693_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei693, .-_osEE_rh850_core0_ei693
#endif
#endif /* OSEE_RH850_CORE0_693_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_694_ISR_CAT))
#if (OSEE_RH850_CORE0_694_ISR_CAT == 1)
_osEE_rh850_core0_ei694:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_694_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei694, .-_osEE_rh850_core0_ei694
#else
_osEE_rh850_core0_ei694:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_694_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei694, .-_osEE_rh850_core0_ei694
#endif
#endif /* OSEE_RH850_CORE0_694_ISR_CAT */
#if (defined(OSEE_RH850_CORE0_695_ISR_CAT))
#if (OSEE_RH850_CORE0_695_ISR_CAT == 1)
_osEE_rh850_core0_ei695:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_695_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core0_ei695, .-_osEE_rh850_core0_ei695
#else
_osEE_rh850_core0_ei695:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE0_695_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core0_ei695, .-_osEE_rh850_core0_ei695
#endif
#endif /* OSEE_RH850_CORE0_695_ISR_CAT */

