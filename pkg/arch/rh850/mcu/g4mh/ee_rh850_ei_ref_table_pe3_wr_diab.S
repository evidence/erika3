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
 * \file  ee_rh850_ei_ref_table_pe3_wr_diab.S
 * \brief EI Reference Table for PE3.
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

  .import _osEE_rh850_call_IsrEiUnused
  .import _osEE_rh850_call_isr1
  .import _osEE_rh850_call_isr2

  .section ".g4mh_int"
  /*.align for RH850 use Power of 2 expression by default. So 2^9 = 512*/
  .align 9
  .global _osEE_rh850_core3_reftabl_ei
_osEE_rh850_core3_reftabl_ei:
  .word _osEE_rh850_core3_ei0         #-- Core3 EIINT0
#if (defined(OSEE_RH850_CORE3_1_ISR_CAT))
  .word _osEE_rh850_core3_ei1         #-- Core3 EIINT1
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT1
#endif /* OSEE_RH850_CORE3_1_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_2_ISR_CAT))
  .word _osEE_rh850_core3_ei2         #-- Core3 EIINT2
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT2
#endif /* OSEE_RH850_CORE3_2_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_3_ISR_CAT))
  .word _osEE_rh850_core3_ei3         #-- Core3 EIINT3
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT3
#endif /* OSEE_RH850_CORE3_3_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_4_ISR_CAT))
  .word _osEE_rh850_core3_ei4         #-- Core3 EIINT4
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT4
#endif /* OSEE_RH850_CORE3_4_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_5_ISR_CAT))
  .word _osEE_rh850_core3_ei5         #-- Core3 EIINT5
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT5
#endif /* OSEE_RH850_CORE3_5_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_6_ISR_CAT))
  .word _osEE_rh850_core3_ei6         #-- Core3 EIINT6
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT6
#endif /* OSEE_RH850_CORE3_6_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_7_ISR_CAT))
  .word _osEE_rh850_core3_ei7         #-- Core3 EIINT7
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT7
#endif /* OSEE_RH850_CORE3_7_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_8_ISR_CAT))
  .word _osEE_rh850_core3_ei8         #-- Core3 EIINT8
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT8
#endif /* OSEE_RH850_CORE3_8_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_9_ISR_CAT))
  .word _osEE_rh850_core3_ei9         #-- Core3 EIINT9
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT9
#endif /* OSEE_RH850_CORE3_9_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_10_ISR_CAT))
  .word _osEE_rh850_core3_ei10        #-- Core3 EIINT10
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT10
#endif /* OSEE_RH850_CORE3_10_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_11_ISR_CAT))
  .word _osEE_rh850_core3_ei11        #-- Core3 EIINT11
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT11
#endif /* OSEE_RH850_CORE3_11_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_12_ISR_CAT))
  .word _osEE_rh850_core3_ei12        #-- Core3 EIINT12
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT12
#endif /* OSEE_RH850_CORE3_12_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_13_ISR_CAT))
  .word _osEE_rh850_core3_ei13        #-- Core3 EIINT13
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT13
#endif /* OSEE_RH850_CORE3_13_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_14_ISR_CAT))
  .word _osEE_rh850_core3_ei14        #-- Core3 EIINT14
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT14
#endif /* OSEE_RH850_CORE3_14_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_15_ISR_CAT))
  .word _osEE_rh850_core3_ei15        #-- Core3 EIINT15
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT15
#endif /* OSEE_RH850_CORE3_15_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_16_ISR_CAT))
  .word _osEE_rh850_core3_ei16        #-- Core3 EIINT16
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT16
#endif /* OSEE_RH850_CORE3_16_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_17_ISR_CAT))
  .word _osEE_rh850_core3_ei17        #-- Core3 EIINT17
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT17
#endif /* OSEE_RH850_CORE3_17_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_18_ISR_CAT))
  .word _osEE_rh850_core3_ei18        #-- Core3 EIINT18
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT18
#endif /* OSEE_RH850_CORE3_18_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_19_ISR_CAT))
  .word _osEE_rh850_core3_ei19        #-- Core3 EIINT19
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT19
#endif /* OSEE_RH850_CORE3_19_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_20_ISR_CAT))
  .word _osEE_rh850_core3_ei20        #-- Core3 EIINT20
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT20
#endif /* OSEE_RH850_CORE3_20_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_21_ISR_CAT))
  .word _osEE_rh850_core3_ei21        #-- Core3 EIINT21
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT21
#endif /* OSEE_RH850_CORE3_21_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_22_ISR_CAT))
  .word _osEE_rh850_core3_ei22        #-- Core3 EIINT22
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT22
#endif /* OSEE_RH850_CORE3_22_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_23_ISR_CAT))
  .word _osEE_rh850_core3_ei23        #-- Core3 EIINT23
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT23
#endif /* OSEE_RH850_CORE3_23_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_24_ISR_CAT))
  .word _osEE_rh850_core3_ei24        #-- Core3 EIINT24
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT24
#endif /* OSEE_RH850_CORE3_24_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_25_ISR_CAT))
  .word _osEE_rh850_core3_ei25        #-- Core3 EIINT25
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT25
#endif /* OSEE_RH850_CORE3_25_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_26_ISR_CAT))
  .word _osEE_rh850_core3_ei26        #-- Core3 EIINT26
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT26
#endif /* OSEE_RH850_CORE3_26_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_27_ISR_CAT))
  .word _osEE_rh850_core3_ei27        #-- Core3 EIINT27
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT27
#endif /* OSEE_RH850_CORE3_27_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_28_ISR_CAT))
  .word _osEE_rh850_core3_ei28        #-- Core3 EIINT28
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT28
#endif /* OSEE_RH850_CORE3_28_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_29_ISR_CAT))
  .word _osEE_rh850_core3_ei29        #-- Core3 EIINT29
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT29
#endif /* OSEE_RH850_CORE3_29_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_30_ISR_CAT))
  .word _osEE_rh850_core3_ei30        #-- Core3 EIINT30
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT30
#endif /* OSEE_RH850_CORE3_30_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_31_ISR_CAT))
  .word _osEE_rh850_core3_ei31        #-- Core3 EIINT31
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT31
#endif /* OSEE_RH850_CORE3_31_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_32_ISR_CAT))
  .word _osEE_rh850_core3_ei32        #-- Core3 EIINT32
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT32
#endif /* OSEE_RH850_CORE3_32_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_33_ISR_CAT))
  .word _osEE_rh850_core3_ei33        #-- Core3 EIINT33
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT33
#endif /* OSEE_RH850_CORE3_33_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_34_ISR_CAT))
  .word _osEE_rh850_core3_ei34        #-- Core3 EIINT34
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT34
#endif /* OSEE_RH850_CORE3_34_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_35_ISR_CAT))
  .word _osEE_rh850_core3_ei35        #-- Core3 EIINT35
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT35
#endif /* OSEE_RH850_CORE3_35_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_36_ISR_CAT))
  .word _osEE_rh850_core3_ei36        #-- Core3 EIINT36
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT36
#endif /* OSEE_RH850_CORE3_36_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_37_ISR_CAT))
  .word _osEE_rh850_core3_ei37        #-- Core3 EIINT37
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT37
#endif /* OSEE_RH850_CORE3_37_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_38_ISR_CAT))
  .word _osEE_rh850_core3_ei38        #-- Core3 EIINT38
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT38
#endif /* OSEE_RH850_CORE3_38_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_39_ISR_CAT))
  .word _osEE_rh850_core3_ei39        #-- Core3 EIINT39
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT39
#endif /* OSEE_RH850_CORE3_39_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_40_ISR_CAT))
  .word _osEE_rh850_core3_ei40        #-- Core3 EIINT40
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT40
#endif /* OSEE_RH850_CORE3_40_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_41_ISR_CAT))
  .word _osEE_rh850_core3_ei41        #-- Core3 EIINT41
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT41
#endif /* OSEE_RH850_CORE3_41_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_42_ISR_CAT))
  .word _osEE_rh850_core3_ei42        #-- Core3 EIINT42
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT42
#endif /* OSEE_RH850_CORE3_42_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_43_ISR_CAT))
  .word _osEE_rh850_core3_ei43        #-- Core3 EIINT43
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT43
#endif /* OSEE_RH850_CORE3_43_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_44_ISR_CAT))
  .word _osEE_rh850_core3_ei44        #-- Core3 EIINT44
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT44
#endif /* OSEE_RH850_CORE3_44_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_45_ISR_CAT))
  .word _osEE_rh850_core3_ei45        #-- Core3 EIINT45
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT45
#endif /* OSEE_RH850_CORE3_45_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_46_ISR_CAT))
  .word _osEE_rh850_core3_ei46        #-- Core3 EIINT46
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT46
#endif /* OSEE_RH850_CORE3_46_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_47_ISR_CAT))
  .word _osEE_rh850_core3_ei47        #-- Core3 EIINT47
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT47
#endif /* OSEE_RH850_CORE3_47_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_48_ISR_CAT))
  .word _osEE_rh850_core3_ei48        #-- Core3 EIINT48
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT48
#endif /* OSEE_RH850_CORE3_48_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_49_ISR_CAT))
  .word _osEE_rh850_core3_ei49        #-- Core3 EIINT49
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT49
#endif /* OSEE_RH850_CORE3_49_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_50_ISR_CAT))
  .word _osEE_rh850_core3_ei50        #-- Core3 EIINT50
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT50
#endif /* OSEE_RH850_CORE3_50_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_51_ISR_CAT))
  .word _osEE_rh850_core3_ei51        #-- Core3 EIINT51
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT51
#endif /* OSEE_RH850_CORE3_51_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_52_ISR_CAT))
  .word _osEE_rh850_core3_ei52        #-- Core3 EIINT52
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT52
#endif /* OSEE_RH850_CORE3_52_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_53_ISR_CAT))
  .word _osEE_rh850_core3_ei53        #-- Core3 EIINT53
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT53
#endif /* OSEE_RH850_CORE3_53_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_54_ISR_CAT))
  .word _osEE_rh850_core3_ei54        #-- Core3 EIINT54
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT54
#endif /* OSEE_RH850_CORE3_54_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_55_ISR_CAT))
  .word _osEE_rh850_core3_ei55        #-- Core3 EIINT55
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT55
#endif /* OSEE_RH850_CORE3_55_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_56_ISR_CAT))
  .word _osEE_rh850_core3_ei56        #-- Core3 EIINT56
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT56
#endif /* OSEE_RH850_CORE3_56_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_57_ISR_CAT))
  .word _osEE_rh850_core3_ei57        #-- Core3 EIINT57
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT57
#endif /* OSEE_RH850_CORE3_57_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_58_ISR_CAT))
  .word _osEE_rh850_core3_ei58        #-- Core3 EIINT58
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT58
#endif /* OSEE_RH850_CORE3_58_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_59_ISR_CAT))
  .word _osEE_rh850_core3_ei59        #-- Core3 EIINT59
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT59
#endif /* OSEE_RH850_CORE3_59_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_60_ISR_CAT))
  .word _osEE_rh850_core3_ei60        #-- Core3 EIINT60
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT60
#endif /* OSEE_RH850_CORE3_60_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_61_ISR_CAT))
  .word _osEE_rh850_core3_ei61        #-- Core3 EIINT61
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT61
#endif /* OSEE_RH850_CORE3_61_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_62_ISR_CAT))
  .word _osEE_rh850_core3_ei62        #-- Core3 EIINT62
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT62
#endif /* OSEE_RH850_CORE3_62_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_63_ISR_CAT))
  .word _osEE_rh850_core3_ei63        #-- Core3 EIINT63
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT63
#endif /* OSEE_RH850_CORE3_63_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_64_ISR_CAT))
  .word _osEE_rh850_core3_ei64        #-- Core3 EIINT64
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT64
#endif /* OSEE_RH850_CORE3_64_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_65_ISR_CAT))
  .word _osEE_rh850_core3_ei65        #-- Core3 EIINT65
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT65
#endif /* OSEE_RH850_CORE3_65_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_66_ISR_CAT))
  .word _osEE_rh850_core3_ei66        #-- Core3 EIINT66
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT66
#endif /* OSEE_RH850_CORE3_66_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_67_ISR_CAT))
  .word _osEE_rh850_core3_ei67        #-- Core3 EIINT67
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT67
#endif /* OSEE_RH850_CORE3_67_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_68_ISR_CAT))
  .word _osEE_rh850_core3_ei68        #-- Core3 EIINT68
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT68
#endif /* OSEE_RH850_CORE3_68_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_69_ISR_CAT))
  .word _osEE_rh850_core3_ei69        #-- Core3 EIINT69
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT69
#endif /* OSEE_RH850_CORE3_69_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_70_ISR_CAT))
  .word _osEE_rh850_core3_ei70        #-- Core3 EIINT70
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT70
#endif /* OSEE_RH850_CORE3_70_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_71_ISR_CAT))
  .word _osEE_rh850_core3_ei71        #-- Core3 EIINT71
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT71
#endif /* OSEE_RH850_CORE3_71_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_72_ISR_CAT))
  .word _osEE_rh850_core3_ei72        #-- Core3 EIINT72
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT72
#endif /* OSEE_RH850_CORE3_72_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_73_ISR_CAT))
  .word _osEE_rh850_core3_ei73        #-- Core3 EIINT73
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT73
#endif /* OSEE_RH850_CORE3_73_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_74_ISR_CAT))
  .word _osEE_rh850_core3_ei74        #-- Core3 EIINT74
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT74
#endif /* OSEE_RH850_CORE3_74_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_75_ISR_CAT))
  .word _osEE_rh850_core3_ei75        #-- Core3 EIINT75
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT75
#endif /* OSEE_RH850_CORE3_75_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_76_ISR_CAT))
  .word _osEE_rh850_core3_ei76        #-- Core3 EIINT76
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT76
#endif /* OSEE_RH850_CORE3_76_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_77_ISR_CAT))
  .word _osEE_rh850_core3_ei77        #-- Core3 EIINT77
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT77
#endif /* OSEE_RH850_CORE3_77_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_78_ISR_CAT))
  .word _osEE_rh850_core3_ei78        #-- Core3 EIINT78
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT78
#endif /* OSEE_RH850_CORE3_78_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_79_ISR_CAT))
  .word _osEE_rh850_core3_ei79        #-- Core3 EIINT79
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT79
#endif /* OSEE_RH850_CORE3_79_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_80_ISR_CAT))
  .word _osEE_rh850_core3_ei80        #-- Core3 EIINT80
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT80
#endif /* OSEE_RH850_CORE3_80_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_81_ISR_CAT))
  .word _osEE_rh850_core3_ei81        #-- Core3 EIINT81
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT81
#endif /* OSEE_RH850_CORE3_81_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_82_ISR_CAT))
  .word _osEE_rh850_core3_ei82        #-- Core3 EIINT82
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT82
#endif /* OSEE_RH850_CORE3_82_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_83_ISR_CAT))
  .word _osEE_rh850_core3_ei83        #-- Core3 EIINT83
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT83
#endif /* OSEE_RH850_CORE3_83_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_84_ISR_CAT))
  .word _osEE_rh850_core3_ei84        #-- Core3 EIINT84
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT84
#endif /* OSEE_RH850_CORE3_84_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_85_ISR_CAT))
  .word _osEE_rh850_core3_ei85        #-- Core3 EIINT85
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT85
#endif /* OSEE_RH850_CORE3_85_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_86_ISR_CAT))
  .word _osEE_rh850_core3_ei86        #-- Core3 EIINT86
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT86
#endif /* OSEE_RH850_CORE3_86_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_87_ISR_CAT))
  .word _osEE_rh850_core3_ei87        #-- Core3 EIINT87
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT87
#endif /* OSEE_RH850_CORE3_87_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_88_ISR_CAT))
  .word _osEE_rh850_core3_ei88        #-- Core3 EIINT88
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT88
#endif /* OSEE_RH850_CORE3_88_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_89_ISR_CAT))
  .word _osEE_rh850_core3_ei89        #-- Core3 EIINT89
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT89
#endif /* OSEE_RH850_CORE3_89_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_90_ISR_CAT))
  .word _osEE_rh850_core3_ei90        #-- Core3 EIINT90
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT90
#endif /* OSEE_RH850_CORE3_90_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_91_ISR_CAT))
  .word _osEE_rh850_core3_ei91        #-- Core3 EIINT91
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT91
#endif /* OSEE_RH850_CORE3_91_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_92_ISR_CAT))
  .word _osEE_rh850_core3_ei92        #-- Core3 EIINT92
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT92
#endif /* OSEE_RH850_CORE3_92_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_93_ISR_CAT))
  .word _osEE_rh850_core3_ei93        #-- Core3 EIINT93
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT93
#endif /* OSEE_RH850_CORE3_93_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_94_ISR_CAT))
  .word _osEE_rh850_core3_ei94        #-- Core3 EIINT94
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT94
#endif /* OSEE_RH850_CORE3_94_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_95_ISR_CAT))
  .word _osEE_rh850_core3_ei95        #-- Core3 EIINT95
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT95
#endif /* OSEE_RH850_CORE3_95_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_96_ISR_CAT))
  .word _osEE_rh850_core3_ei96        #-- Core3 EIINT96
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT96
#endif /* OSEE_RH850_CORE3_96_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_97_ISR_CAT))
  .word _osEE_rh850_core3_ei97        #-- Core3 EIINT97
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT97
#endif /* OSEE_RH850_CORE3_97_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_98_ISR_CAT))
  .word _osEE_rh850_core3_ei98        #-- Core3 EIINT98
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT98
#endif /* OSEE_RH850_CORE3_98_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_99_ISR_CAT))
  .word _osEE_rh850_core3_ei99        #-- Core3 EIINT99
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT99
#endif /* OSEE_RH850_CORE3_99_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_100_ISR_CAT))
  .word _osEE_rh850_core3_ei100       #-- Core3 EIINT100
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT100
#endif /* OSEE_RH850_CORE3_100_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_101_ISR_CAT))
  .word _osEE_rh850_core3_ei101       #-- Core3 EIINT101
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT101
#endif /* OSEE_RH850_CORE3_101_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_102_ISR_CAT))
  .word _osEE_rh850_core3_ei102       #-- Core3 EIINT102
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT102
#endif /* OSEE_RH850_CORE3_102_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_103_ISR_CAT))
  .word _osEE_rh850_core3_ei103       #-- Core3 EIINT103
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT103
#endif /* OSEE_RH850_CORE3_103_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_104_ISR_CAT))
  .word _osEE_rh850_core3_ei104       #-- Core3 EIINT104
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT104
#endif /* OSEE_RH850_CORE3_104_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_105_ISR_CAT))
  .word _osEE_rh850_core3_ei105       #-- Core3 EIINT105
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT105
#endif /* OSEE_RH850_CORE3_105_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_106_ISR_CAT))
  .word _osEE_rh850_core3_ei106       #-- Core3 EIINT106
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT106
#endif /* OSEE_RH850_CORE3_106_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_107_ISR_CAT))
  .word _osEE_rh850_core3_ei107       #-- Core3 EIINT107
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT107
#endif /* OSEE_RH850_CORE3_107_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_108_ISR_CAT))
  .word _osEE_rh850_core3_ei108       #-- Core3 EIINT108
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT108
#endif /* OSEE_RH850_CORE3_108_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_109_ISR_CAT))
  .word _osEE_rh850_core3_ei109       #-- Core3 EIINT109
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT109
#endif /* OSEE_RH850_CORE3_109_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_110_ISR_CAT))
  .word _osEE_rh850_core3_ei110       #-- Core3 EIINT110
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT110
#endif /* OSEE_RH850_CORE3_110_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_111_ISR_CAT))
  .word _osEE_rh850_core3_ei111       #-- Core3 EIINT111
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT111
#endif /* OSEE_RH850_CORE3_111_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_112_ISR_CAT))
  .word _osEE_rh850_core3_ei112       #-- Core3 EIINT112
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT112
#endif /* OSEE_RH850_CORE3_112_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_113_ISR_CAT))
  .word _osEE_rh850_core3_ei113       #-- Core3 EIINT113
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT113
#endif /* OSEE_RH850_CORE3_113_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_114_ISR_CAT))
  .word _osEE_rh850_core3_ei114       #-- Core3 EIINT114
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT114
#endif /* OSEE_RH850_CORE3_114_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_115_ISR_CAT))
  .word _osEE_rh850_core3_ei115       #-- Core3 EIINT115
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT115
#endif /* OSEE_RH850_CORE3_115_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_116_ISR_CAT))
  .word _osEE_rh850_core3_ei116       #-- Core3 EIINT116
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT116
#endif /* OSEE_RH850_CORE3_116_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_117_ISR_CAT))
  .word _osEE_rh850_core3_ei117       #-- Core3 EIINT117
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT117
#endif /* OSEE_RH850_CORE3_117_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_118_ISR_CAT))
  .word _osEE_rh850_core3_ei118       #-- Core3 EIINT118
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT118
#endif /* OSEE_RH850_CORE3_118_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_119_ISR_CAT))
  .word _osEE_rh850_core3_ei119       #-- Core3 EIINT119
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT119
#endif /* OSEE_RH850_CORE3_119_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_120_ISR_CAT))
  .word _osEE_rh850_core3_ei120       #-- Core3 EIINT120
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT120
#endif /* OSEE_RH850_CORE3_120_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_121_ISR_CAT))
  .word _osEE_rh850_core3_ei121       #-- Core3 EIINT121
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT121
#endif /* OSEE_RH850_CORE3_121_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_122_ISR_CAT))
  .word _osEE_rh850_core3_ei122       #-- Core3 EIINT122
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT122
#endif /* OSEE_RH850_CORE3_122_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_123_ISR_CAT))
  .word _osEE_rh850_core3_ei123       #-- Core3 EIINT123
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT123
#endif /* OSEE_RH850_CORE3_123_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_124_ISR_CAT))
  .word _osEE_rh850_core3_ei124       #-- Core3 EIINT124
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT124
#endif /* OSEE_RH850_CORE3_124_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_125_ISR_CAT))
  .word _osEE_rh850_core3_ei125       #-- Core3 EIINT125
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT125
#endif /* OSEE_RH850_CORE3_125_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_126_ISR_CAT))
  .word _osEE_rh850_core3_ei126       #-- Core3 EIINT126
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT126
#endif /* OSEE_RH850_CORE3_126_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_127_ISR_CAT))
  .word _osEE_rh850_core3_ei127       #-- Core3 EIINT127
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT127
#endif /* OSEE_RH850_CORE3_127_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_128_ISR_CAT))
  .word _osEE_rh850_core3_ei128       #-- Core3 EIINT128
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT128
#endif /* OSEE_RH850_CORE3_128_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_129_ISR_CAT))
  .word _osEE_rh850_core3_ei129       #-- Core3 EIINT129
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT129
#endif /* OSEE_RH850_CORE3_129_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_130_ISR_CAT))
  .word _osEE_rh850_core3_ei130       #-- Core3 EIINT130
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT130
#endif /* OSEE_RH850_CORE3_130_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_131_ISR_CAT))
  .word _osEE_rh850_core3_ei131       #-- Core3 EIINT131
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT131
#endif /* OSEE_RH850_CORE3_131_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_132_ISR_CAT))
  .word _osEE_rh850_core3_ei132       #-- Core3 EIINT132
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT132
#endif /* OSEE_RH850_CORE3_132_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_133_ISR_CAT))
  .word _osEE_rh850_core3_ei133       #-- Core3 EIINT133
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT133
#endif /* OSEE_RH850_CORE3_133_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_134_ISR_CAT))
  .word _osEE_rh850_core3_ei134       #-- Core3 EIINT134
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT134
#endif /* OSEE_RH850_CORE3_134_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_135_ISR_CAT))
  .word _osEE_rh850_core3_ei135       #-- Core3 EIINT135
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT135
#endif /* OSEE_RH850_CORE3_135_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_136_ISR_CAT))
  .word _osEE_rh850_core3_ei136       #-- Core3 EIINT136
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT136
#endif /* OSEE_RH850_CORE3_136_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_137_ISR_CAT))
  .word _osEE_rh850_core3_ei137       #-- Core3 EIINT137
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT137
#endif /* OSEE_RH850_CORE3_137_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_138_ISR_CAT))
  .word _osEE_rh850_core3_ei138       #-- Core3 EIINT138
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT138
#endif /* OSEE_RH850_CORE3_138_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_139_ISR_CAT))
  .word _osEE_rh850_core3_ei139       #-- Core3 EIINT139
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT139
#endif /* OSEE_RH850_CORE3_139_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_140_ISR_CAT))
  .word _osEE_rh850_core3_ei140       #-- Core3 EIINT140
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT140
#endif /* OSEE_RH850_CORE3_140_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_141_ISR_CAT))
  .word _osEE_rh850_core3_ei141       #-- Core3 EIINT141
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT141
#endif /* OSEE_RH850_CORE3_141_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_142_ISR_CAT))
  .word _osEE_rh850_core3_ei142       #-- Core3 EIINT142
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT142
#endif /* OSEE_RH850_CORE3_142_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_143_ISR_CAT))
  .word _osEE_rh850_core3_ei143       #-- Core3 EIINT143
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT143
#endif /* OSEE_RH850_CORE3_143_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_144_ISR_CAT))
  .word _osEE_rh850_core3_ei144       #-- Core3 EIINT144
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT144
#endif /* OSEE_RH850_CORE3_144_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_145_ISR_CAT))
  .word _osEE_rh850_core3_ei145       #-- Core3 EIINT145
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT145
#endif /* OSEE_RH850_CORE3_145_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_146_ISR_CAT))
  .word _osEE_rh850_core3_ei146       #-- Core3 EIINT146
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT146
#endif /* OSEE_RH850_CORE3_146_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_147_ISR_CAT))
  .word _osEE_rh850_core3_ei147       #-- Core3 EIINT147
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT147
#endif /* OSEE_RH850_CORE3_147_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_148_ISR_CAT))
  .word _osEE_rh850_core3_ei148       #-- Core3 EIINT148
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT148
#endif /* OSEE_RH850_CORE3_148_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_149_ISR_CAT))
  .word _osEE_rh850_core3_ei149       #-- Core3 EIINT149
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT149
#endif /* OSEE_RH850_CORE3_149_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_150_ISR_CAT))
  .word _osEE_rh850_core3_ei150       #-- Core3 EIINT150
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT150
#endif /* OSEE_RH850_CORE3_150_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_151_ISR_CAT))
  .word _osEE_rh850_core3_ei151       #-- Core3 EIINT151
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT151
#endif /* OSEE_RH850_CORE3_151_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_152_ISR_CAT))
  .word _osEE_rh850_core3_ei152       #-- Core3 EIINT152
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT152
#endif /* OSEE_RH850_CORE3_152_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_153_ISR_CAT))
  .word _osEE_rh850_core3_ei153       #-- Core3 EIINT153
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT153
#endif /* OSEE_RH850_CORE3_153_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_154_ISR_CAT))
  .word _osEE_rh850_core3_ei154       #-- Core3 EIINT154
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT154
#endif /* OSEE_RH850_CORE3_154_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_155_ISR_CAT))
  .word _osEE_rh850_core3_ei155       #-- Core3 EIINT155
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT155
#endif /* OSEE_RH850_CORE3_155_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_156_ISR_CAT))
  .word _osEE_rh850_core3_ei156       #-- Core3 EIINT156
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT156
#endif /* OSEE_RH850_CORE3_156_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_157_ISR_CAT))
  .word _osEE_rh850_core3_ei157       #-- Core3 EIINT157
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT157
#endif /* OSEE_RH850_CORE3_157_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_158_ISR_CAT))
  .word _osEE_rh850_core3_ei158       #-- Core3 EIINT158
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT158
#endif /* OSEE_RH850_CORE3_158_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_159_ISR_CAT))
  .word _osEE_rh850_core3_ei159       #-- Core3 EIINT159
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT159
#endif /* OSEE_RH850_CORE3_159_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_160_ISR_CAT))
  .word _osEE_rh850_core3_ei160       #-- Core3 EIINT160
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT160
#endif /* OSEE_RH850_CORE3_160_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_161_ISR_CAT))
  .word _osEE_rh850_core3_ei161       #-- Core3 EIINT161
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT161
#endif /* OSEE_RH850_CORE3_161_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_162_ISR_CAT))
  .word _osEE_rh850_core3_ei162       #-- Core3 EIINT162
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT162
#endif /* OSEE_RH850_CORE3_162_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_163_ISR_CAT))
  .word _osEE_rh850_core3_ei163       #-- Core3 EIINT163
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT163
#endif /* OSEE_RH850_CORE3_163_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_164_ISR_CAT))
  .word _osEE_rh850_core3_ei164       #-- Core3 EIINT164
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT164
#endif /* OSEE_RH850_CORE3_164_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_165_ISR_CAT))
  .word _osEE_rh850_core3_ei165       #-- Core3 EIINT165
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT165
#endif /* OSEE_RH850_CORE3_165_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_166_ISR_CAT))
  .word _osEE_rh850_core3_ei166       #-- Core3 EIINT166
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT166
#endif /* OSEE_RH850_CORE3_166_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_167_ISR_CAT))
  .word _osEE_rh850_core3_ei167       #-- Core3 EIINT167
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT167
#endif /* OSEE_RH850_CORE3_167_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_168_ISR_CAT))
  .word _osEE_rh850_core3_ei168       #-- Core3 EIINT168
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT168
#endif /* OSEE_RH850_CORE3_168_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_169_ISR_CAT))
  .word _osEE_rh850_core3_ei169       #-- Core3 EIINT169
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT169
#endif /* OSEE_RH850_CORE3_169_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_170_ISR_CAT))
  .word _osEE_rh850_core3_ei170       #-- Core3 EIINT170
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT170
#endif /* OSEE_RH850_CORE3_170_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_171_ISR_CAT))
  .word _osEE_rh850_core3_ei171       #-- Core3 EIINT171
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT171
#endif /* OSEE_RH850_CORE3_171_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_172_ISR_CAT))
  .word _osEE_rh850_core3_ei172       #-- Core3 EIINT172
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT172
#endif /* OSEE_RH850_CORE3_172_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_173_ISR_CAT))
  .word _osEE_rh850_core3_ei173       #-- Core3 EIINT173
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT173
#endif /* OSEE_RH850_CORE3_173_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_174_ISR_CAT))
  .word _osEE_rh850_core3_ei174       #-- Core3 EIINT174
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT174
#endif /* OSEE_RH850_CORE3_174_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_175_ISR_CAT))
  .word _osEE_rh850_core3_ei175       #-- Core3 EIINT175
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT175
#endif /* OSEE_RH850_CORE3_175_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_176_ISR_CAT))
  .word _osEE_rh850_core3_ei176       #-- Core3 EIINT176
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT176
#endif /* OSEE_RH850_CORE3_176_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_177_ISR_CAT))
  .word _osEE_rh850_core3_ei177       #-- Core3 EIINT177
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT177
#endif /* OSEE_RH850_CORE3_177_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_178_ISR_CAT))
  .word _osEE_rh850_core3_ei178       #-- Core3 EIINT178
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT178
#endif /* OSEE_RH850_CORE3_178_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_179_ISR_CAT))
  .word _osEE_rh850_core3_ei179       #-- Core3 EIINT179
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT179
#endif /* OSEE_RH850_CORE3_179_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_180_ISR_CAT))
  .word _osEE_rh850_core3_ei180       #-- Core3 EIINT180
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT180
#endif /* OSEE_RH850_CORE3_180_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_181_ISR_CAT))
  .word _osEE_rh850_core3_ei181       #-- Core3 EIINT181
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT181
#endif /* OSEE_RH850_CORE3_181_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_182_ISR_CAT))
  .word _osEE_rh850_core3_ei182       #-- Core3 EIINT182
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT182
#endif /* OSEE_RH850_CORE3_182_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_183_ISR_CAT))
  .word _osEE_rh850_core3_ei183       #-- Core3 EIINT183
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT183
#endif /* OSEE_RH850_CORE3_183_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_184_ISR_CAT))
  .word _osEE_rh850_core3_ei184       #-- Core3 EIINT184
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT184
#endif /* OSEE_RH850_CORE3_184_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_185_ISR_CAT))
  .word _osEE_rh850_core3_ei185       #-- Core3 EIINT185
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT185
#endif /* OSEE_RH850_CORE3_185_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_186_ISR_CAT))
  .word _osEE_rh850_core3_ei186       #-- Core3 EIINT186
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT186
#endif /* OSEE_RH850_CORE3_186_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_187_ISR_CAT))
  .word _osEE_rh850_core3_ei187       #-- Core3 EIINT187
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT187
#endif /* OSEE_RH850_CORE3_187_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_188_ISR_CAT))
  .word _osEE_rh850_core3_ei188       #-- Core3 EIINT188
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT188
#endif /* OSEE_RH850_CORE3_188_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_189_ISR_CAT))
  .word _osEE_rh850_core3_ei189       #-- Core3 EIINT189
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT189
#endif /* OSEE_RH850_CORE3_189_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_190_ISR_CAT))
  .word _osEE_rh850_core3_ei190       #-- Core3 EIINT190
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT190
#endif /* OSEE_RH850_CORE3_190_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_191_ISR_CAT))
  .word _osEE_rh850_core3_ei191       #-- Core3 EIINT191
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT191
#endif /* OSEE_RH850_CORE3_191_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_192_ISR_CAT))
  .word _osEE_rh850_core3_ei192       #-- Core3 EIINT192
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT192
#endif /* OSEE_RH850_CORE3_192_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_193_ISR_CAT))
  .word _osEE_rh850_core3_ei193       #-- Core3 EIINT193
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT193
#endif /* OSEE_RH850_CORE3_193_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_194_ISR_CAT))
  .word _osEE_rh850_core3_ei194       #-- Core3 EIINT194
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT194
#endif /* OSEE_RH850_CORE3_194_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_195_ISR_CAT))
  .word _osEE_rh850_core3_ei195       #-- Core3 EIINT195
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT195
#endif /* OSEE_RH850_CORE3_195_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_196_ISR_CAT))
  .word _osEE_rh850_core3_ei196       #-- Core3 EIINT196
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT196
#endif /* OSEE_RH850_CORE3_196_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_197_ISR_CAT))
  .word _osEE_rh850_core3_ei197       #-- Core3 EIINT197
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT197
#endif /* OSEE_RH850_CORE3_197_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_198_ISR_CAT))
  .word _osEE_rh850_core3_ei198       #-- Core3 EIINT198
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT198
#endif /* OSEE_RH850_CORE3_198_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_199_ISR_CAT))
  .word _osEE_rh850_core3_ei199       #-- Core3 EIINT199
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT199
#endif /* OSEE_RH850_CORE3_199_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_200_ISR_CAT))
  .word _osEE_rh850_core3_ei200       #-- Core3 EIINT200
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT200
#endif /* OSEE_RH850_CORE3_200_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_201_ISR_CAT))
  .word _osEE_rh850_core3_ei201       #-- Core3 EIINT201
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT201
#endif /* OSEE_RH850_CORE3_201_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_202_ISR_CAT))
  .word _osEE_rh850_core3_ei202       #-- Core3 EIINT202
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT202
#endif /* OSEE_RH850_CORE3_202_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_203_ISR_CAT))
  .word _osEE_rh850_core3_ei203       #-- Core3 EIINT203
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT203
#endif /* OSEE_RH850_CORE3_203_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_204_ISR_CAT))
  .word _osEE_rh850_core3_ei204       #-- Core3 EIINT204
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT204
#endif /* OSEE_RH850_CORE3_204_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_205_ISR_CAT))
  .word _osEE_rh850_core3_ei205       #-- Core3 EIINT205
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT205
#endif /* OSEE_RH850_CORE3_205_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_206_ISR_CAT))
  .word _osEE_rh850_core3_ei206       #-- Core3 EIINT206
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT206
#endif /* OSEE_RH850_CORE3_206_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_207_ISR_CAT))
  .word _osEE_rh850_core3_ei207       #-- Core3 EIINT207
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT207
#endif /* OSEE_RH850_CORE3_207_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_208_ISR_CAT))
  .word _osEE_rh850_core3_ei208       #-- Core3 EIINT208
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT208
#endif /* OSEE_RH850_CORE3_208_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_209_ISR_CAT))
  .word _osEE_rh850_core3_ei209       #-- Core3 EIINT209
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT209
#endif /* OSEE_RH850_CORE3_209_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_210_ISR_CAT))
  .word _osEE_rh850_core3_ei210       #-- Core3 EIINT210
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT210
#endif /* OSEE_RH850_CORE3_210_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_211_ISR_CAT))
  .word _osEE_rh850_core3_ei211       #-- Core3 EIINT211
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT211
#endif /* OSEE_RH850_CORE3_211_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_212_ISR_CAT))
  .word _osEE_rh850_core3_ei212       #-- Core3 EIINT212
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT212
#endif /* OSEE_RH850_CORE3_212_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_213_ISR_CAT))
  .word _osEE_rh850_core3_ei213       #-- Core3 EIINT213
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT213
#endif /* OSEE_RH850_CORE3_213_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_214_ISR_CAT))
  .word _osEE_rh850_core3_ei214       #-- Core3 EIINT214
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT214
#endif /* OSEE_RH850_CORE3_214_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_215_ISR_CAT))
  .word _osEE_rh850_core3_ei215       #-- Core3 EIINT215
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT215
#endif /* OSEE_RH850_CORE3_215_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_216_ISR_CAT))
  .word _osEE_rh850_core3_ei216       #-- Core3 EIINT216
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT216
#endif /* OSEE_RH850_CORE3_216_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_217_ISR_CAT))
  .word _osEE_rh850_core3_ei217       #-- Core3 EIINT217
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT217
#endif /* OSEE_RH850_CORE3_217_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_218_ISR_CAT))
  .word _osEE_rh850_core3_ei218       #-- Core3 EIINT218
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT218
#endif /* OSEE_RH850_CORE3_218_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_219_ISR_CAT))
  .word _osEE_rh850_core3_ei219       #-- Core3 EIINT219
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT219
#endif /* OSEE_RH850_CORE3_219_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_220_ISR_CAT))
  .word _osEE_rh850_core3_ei220       #-- Core3 EIINT220
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT220
#endif /* OSEE_RH850_CORE3_220_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_221_ISR_CAT))
  .word _osEE_rh850_core3_ei221       #-- Core3 EIINT221
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT221
#endif /* OSEE_RH850_CORE3_221_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_222_ISR_CAT))
  .word _osEE_rh850_core3_ei222       #-- Core3 EIINT222
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT222
#endif /* OSEE_RH850_CORE3_222_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_223_ISR_CAT))
  .word _osEE_rh850_core3_ei223       #-- Core3 EIINT223
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT223
#endif /* OSEE_RH850_CORE3_223_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_224_ISR_CAT))
  .word _osEE_rh850_core3_ei224       #-- Core3 EIINT224
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT224
#endif /* OSEE_RH850_CORE3_224_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_225_ISR_CAT))
  .word _osEE_rh850_core3_ei225       #-- Core3 EIINT225
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT225
#endif /* OSEE_RH850_CORE3_225_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_226_ISR_CAT))
  .word _osEE_rh850_core3_ei226       #-- Core3 EIINT226
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT226
#endif /* OSEE_RH850_CORE3_226_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_227_ISR_CAT))
  .word _osEE_rh850_core3_ei227       #-- Core3 EIINT227
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT227
#endif /* OSEE_RH850_CORE3_227_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_228_ISR_CAT))
  .word _osEE_rh850_core3_ei228       #-- Core3 EIINT228
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT228
#endif /* OSEE_RH850_CORE3_228_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_229_ISR_CAT))
  .word _osEE_rh850_core3_ei229       #-- Core3 EIINT229
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT229
#endif /* OSEE_RH850_CORE3_229_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_230_ISR_CAT))
  .word _osEE_rh850_core3_ei230       #-- Core3 EIINT230
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT230
#endif /* OSEE_RH850_CORE3_230_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_231_ISR_CAT))
  .word _osEE_rh850_core3_ei231       #-- Core3 EIINT231
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT231
#endif /* OSEE_RH850_CORE3_231_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_232_ISR_CAT))
  .word _osEE_rh850_core3_ei232       #-- Core3 EIINT232
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT232
#endif /* OSEE_RH850_CORE3_232_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_233_ISR_CAT))
  .word _osEE_rh850_core3_ei233       #-- Core3 EIINT233
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT233
#endif /* OSEE_RH850_CORE3_233_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_234_ISR_CAT))
  .word _osEE_rh850_core3_ei234       #-- Core3 EIINT234
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT234
#endif /* OSEE_RH850_CORE3_234_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_235_ISR_CAT))
  .word _osEE_rh850_core3_ei235       #-- Core3 EIINT235
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT235
#endif /* OSEE_RH850_CORE3_235_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_236_ISR_CAT))
  .word _osEE_rh850_core3_ei236       #-- Core3 EIINT236
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT236
#endif /* OSEE_RH850_CORE3_236_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_237_ISR_CAT))
  .word _osEE_rh850_core3_ei237       #-- Core3 EIINT237
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT237
#endif /* OSEE_RH850_CORE3_237_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_238_ISR_CAT))
  .word _osEE_rh850_core3_ei238       #-- Core3 EIINT238
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT238
#endif /* OSEE_RH850_CORE3_238_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_239_ISR_CAT))
  .word _osEE_rh850_core3_ei239       #-- Core3 EIINT239
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT239
#endif /* OSEE_RH850_CORE3_239_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_240_ISR_CAT))
  .word _osEE_rh850_core3_ei240       #-- Core3 EIINT240
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT240
#endif /* OSEE_RH850_CORE3_240_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_241_ISR_CAT))
  .word _osEE_rh850_core3_ei241       #-- Core3 EIINT241
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT241
#endif /* OSEE_RH850_CORE3_241_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_242_ISR_CAT))
  .word _osEE_rh850_core3_ei242       #-- Core3 EIINT242
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT242
#endif /* OSEE_RH850_CORE3_242_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_243_ISR_CAT))
  .word _osEE_rh850_core3_ei243       #-- Core3 EIINT243
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT243
#endif /* OSEE_RH850_CORE3_243_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_244_ISR_CAT))
  .word _osEE_rh850_core3_ei244       #-- Core3 EIINT244
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT244
#endif /* OSEE_RH850_CORE3_244_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_245_ISR_CAT))
  .word _osEE_rh850_core3_ei245       #-- Core3 EIINT245
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT245
#endif /* OSEE_RH850_CORE3_245_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_246_ISR_CAT))
  .word _osEE_rh850_core3_ei246       #-- Core3 EIINT246
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT246
#endif /* OSEE_RH850_CORE3_246_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_247_ISR_CAT))
  .word _osEE_rh850_core3_ei247       #-- Core3 EIINT247
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT247
#endif /* OSEE_RH850_CORE3_247_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_248_ISR_CAT))
  .word _osEE_rh850_core3_ei248       #-- Core3 EIINT248
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT248
#endif /* OSEE_RH850_CORE3_248_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_249_ISR_CAT))
  .word _osEE_rh850_core3_ei249       #-- Core3 EIINT249
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT249
#endif /* OSEE_RH850_CORE3_249_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_250_ISR_CAT))
  .word _osEE_rh850_core3_ei250       #-- Core3 EIINT250
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT250
#endif /* OSEE_RH850_CORE3_250_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_251_ISR_CAT))
  .word _osEE_rh850_core3_ei251       #-- Core3 EIINT251
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT251
#endif /* OSEE_RH850_CORE3_251_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_252_ISR_CAT))
  .word _osEE_rh850_core3_ei252       #-- Core3 EIINT252
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT252
#endif /* OSEE_RH850_CORE3_252_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_253_ISR_CAT))
  .word _osEE_rh850_core3_ei253       #-- Core3 EIINT253
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT253
#endif /* OSEE_RH850_CORE3_253_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_254_ISR_CAT))
  .word _osEE_rh850_core3_ei254       #-- Core3 EIINT254
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT254
#endif /* OSEE_RH850_CORE3_254_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_255_ISR_CAT))
  .word _osEE_rh850_core3_ei255       #-- Core3 EIINT255
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT255
#endif /* OSEE_RH850_CORE3_255_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_256_ISR_CAT))
  .word _osEE_rh850_core3_ei256       #-- Core3 EIINT256
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT256
#endif /* OSEE_RH850_CORE3_256_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_257_ISR_CAT))
  .word _osEE_rh850_core3_ei257       #-- Core3 EIINT257
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT257
#endif /* OSEE_RH850_CORE3_257_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_258_ISR_CAT))
  .word _osEE_rh850_core3_ei258       #-- Core3 EIINT258
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT258
#endif /* OSEE_RH850_CORE3_258_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_259_ISR_CAT))
  .word _osEE_rh850_core3_ei259       #-- Core3 EIINT259
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT259
#endif /* OSEE_RH850_CORE3_259_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_260_ISR_CAT))
  .word _osEE_rh850_core3_ei260       #-- Core3 EIINT260
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT260
#endif /* OSEE_RH850_CORE3_260_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_261_ISR_CAT))
  .word _osEE_rh850_core3_ei261       #-- Core3 EIINT261
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT261
#endif /* OSEE_RH850_CORE3_261_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_262_ISR_CAT))
  .word _osEE_rh850_core3_ei262       #-- Core3 EIINT262
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT262
#endif /* OSEE_RH850_CORE3_262_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_263_ISR_CAT))
  .word _osEE_rh850_core3_ei263       #-- Core3 EIINT263
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT263
#endif /* OSEE_RH850_CORE3_263_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_264_ISR_CAT))
  .word _osEE_rh850_core3_ei264       #-- Core3 EIINT264
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT264
#endif /* OSEE_RH850_CORE3_264_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_265_ISR_CAT))
  .word _osEE_rh850_core3_ei265       #-- Core3 EIINT265
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT265
#endif /* OSEE_RH850_CORE3_265_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_266_ISR_CAT))
  .word _osEE_rh850_core3_ei266       #-- Core3 EIINT266
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT266
#endif /* OSEE_RH850_CORE3_266_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_267_ISR_CAT))
  .word _osEE_rh850_core3_ei267       #-- Core3 EIINT267
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT267
#endif /* OSEE_RH850_CORE3_267_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_268_ISR_CAT))
  .word _osEE_rh850_core3_ei268       #-- Core3 EIINT268
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT268
#endif /* OSEE_RH850_CORE3_268_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_269_ISR_CAT))
  .word _osEE_rh850_core3_ei269       #-- Core3 EIINT269
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT269
#endif /* OSEE_RH850_CORE3_269_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_270_ISR_CAT))
  .word _osEE_rh850_core3_ei270       #-- Core3 EIINT270
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT270
#endif /* OSEE_RH850_CORE3_270_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_271_ISR_CAT))
  .word _osEE_rh850_core3_ei271       #-- Core3 EIINT271
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT271
#endif /* OSEE_RH850_CORE3_271_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_272_ISR_CAT))
  .word _osEE_rh850_core3_ei272       #-- Core3 EIINT272
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT272
#endif /* OSEE_RH850_CORE3_272_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_273_ISR_CAT))
  .word _osEE_rh850_core3_ei273       #-- Core3 EIINT273
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT273
#endif /* OSEE_RH850_CORE3_273_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_274_ISR_CAT))
  .word _osEE_rh850_core3_ei274       #-- Core3 EIINT274
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT274
#endif /* OSEE_RH850_CORE3_274_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_275_ISR_CAT))
  .word _osEE_rh850_core3_ei275       #-- Core3 EIINT275
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT275
#endif /* OSEE_RH850_CORE3_275_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_276_ISR_CAT))
  .word _osEE_rh850_core3_ei276       #-- Core3 EIINT276
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT276
#endif /* OSEE_RH850_CORE3_276_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_277_ISR_CAT))
  .word _osEE_rh850_core3_ei277       #-- Core3 EIINT277
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT277
#endif /* OSEE_RH850_CORE3_277_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_278_ISR_CAT))
  .word _osEE_rh850_core3_ei278       #-- Core3 EIINT278
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT278
#endif /* OSEE_RH850_CORE3_278_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_279_ISR_CAT))
  .word _osEE_rh850_core3_ei279       #-- Core3 EIINT279
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT279
#endif /* OSEE_RH850_CORE3_279_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_280_ISR_CAT))
  .word _osEE_rh850_core3_ei280       #-- Core3 EIINT280
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT280
#endif /* OSEE_RH850_CORE3_280_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_281_ISR_CAT))
  .word _osEE_rh850_core3_ei281       #-- Core3 EIINT281
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT281
#endif /* OSEE_RH850_CORE3_281_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_282_ISR_CAT))
  .word _osEE_rh850_core3_ei282       #-- Core3 EIINT282
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT282
#endif /* OSEE_RH850_CORE3_282_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_283_ISR_CAT))
  .word _osEE_rh850_core3_ei283       #-- Core3 EIINT283
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT283
#endif /* OSEE_RH850_CORE3_283_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_284_ISR_CAT))
  .word _osEE_rh850_core3_ei284       #-- Core3 EIINT284
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT284
#endif /* OSEE_RH850_CORE3_284_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_285_ISR_CAT))
  .word _osEE_rh850_core3_ei285       #-- Core3 EIINT285
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT285
#endif /* OSEE_RH850_CORE3_285_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_286_ISR_CAT))
  .word _osEE_rh850_core3_ei286       #-- Core3 EIINT286
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT286
#endif /* OSEE_RH850_CORE3_286_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_287_ISR_CAT))
  .word _osEE_rh850_core3_ei287       #-- Core3 EIINT287
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT287
#endif /* OSEE_RH850_CORE3_287_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_288_ISR_CAT))
  .word _osEE_rh850_core3_ei288       #-- Core3 EIINT288
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT288
#endif /* OSEE_RH850_CORE3_288_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_289_ISR_CAT))
  .word _osEE_rh850_core3_ei289       #-- Core3 EIINT289
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT289
#endif /* OSEE_RH850_CORE3_289_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_290_ISR_CAT))
  .word _osEE_rh850_core3_ei290       #-- Core3 EIINT290
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT290
#endif /* OSEE_RH850_CORE3_290_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_291_ISR_CAT))
  .word _osEE_rh850_core3_ei291       #-- Core3 EIINT291
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT291
#endif /* OSEE_RH850_CORE3_291_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_292_ISR_CAT))
  .word _osEE_rh850_core3_ei292       #-- Core3 EIINT292
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT292
#endif /* OSEE_RH850_CORE3_292_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_293_ISR_CAT))
  .word _osEE_rh850_core3_ei293       #-- Core3 EIINT293
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT293
#endif /* OSEE_RH850_CORE3_293_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_294_ISR_CAT))
  .word _osEE_rh850_core3_ei294       #-- Core3 EIINT294
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT294
#endif /* OSEE_RH850_CORE3_294_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_295_ISR_CAT))
  .word _osEE_rh850_core3_ei295       #-- Core3 EIINT295
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT295
#endif /* OSEE_RH850_CORE3_295_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_296_ISR_CAT))
  .word _osEE_rh850_core3_ei296       #-- Core3 EIINT296
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT296
#endif /* OSEE_RH850_CORE3_296_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_297_ISR_CAT))
  .word _osEE_rh850_core3_ei297       #-- Core3 EIINT297
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT297
#endif /* OSEE_RH850_CORE3_297_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_298_ISR_CAT))
  .word _osEE_rh850_core3_ei298       #-- Core3 EIINT298
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT298
#endif /* OSEE_RH850_CORE3_298_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_299_ISR_CAT))
  .word _osEE_rh850_core3_ei299       #-- Core3 EIINT299
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT299
#endif /* OSEE_RH850_CORE3_299_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_300_ISR_CAT))
  .word _osEE_rh850_core3_ei300       #-- Core3 EIINT300
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT300
#endif /* OSEE_RH850_CORE3_300_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_301_ISR_CAT))
  .word _osEE_rh850_core3_ei301       #-- Core3 EIINT301
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT301
#endif /* OSEE_RH850_CORE3_301_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_302_ISR_CAT))
  .word _osEE_rh850_core3_ei302       #-- Core3 EIINT302
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT302
#endif /* OSEE_RH850_CORE3_302_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_303_ISR_CAT))
  .word _osEE_rh850_core3_ei303       #-- Core3 EIINT303
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT303
#endif /* OSEE_RH850_CORE3_303_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_304_ISR_CAT))
  .word _osEE_rh850_core3_ei304       #-- Core3 EIINT304
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT304
#endif /* OSEE_RH850_CORE3_304_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_305_ISR_CAT))
  .word _osEE_rh850_core3_ei305       #-- Core3 EIINT305
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT305
#endif /* OSEE_RH850_CORE3_305_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_306_ISR_CAT))
  .word _osEE_rh850_core3_ei306       #-- Core3 EIINT306
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT306
#endif /* OSEE_RH850_CORE3_306_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_307_ISR_CAT))
  .word _osEE_rh850_core3_ei307       #-- Core3 EIINT307
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT307
#endif /* OSEE_RH850_CORE3_307_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_308_ISR_CAT))
  .word _osEE_rh850_core3_ei308       #-- Core3 EIINT308
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT308
#endif /* OSEE_RH850_CORE3_308_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_309_ISR_CAT))
  .word _osEE_rh850_core3_ei309       #-- Core3 EIINT309
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT309
#endif /* OSEE_RH850_CORE3_309_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_310_ISR_CAT))
  .word _osEE_rh850_core3_ei310       #-- Core3 EIINT310
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT310
#endif /* OSEE_RH850_CORE3_310_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_311_ISR_CAT))
  .word _osEE_rh850_core3_ei311       #-- Core3 EIINT311
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT311
#endif /* OSEE_RH850_CORE3_311_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_312_ISR_CAT))
  .word _osEE_rh850_core3_ei312       #-- Core3 EIINT312
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT312
#endif /* OSEE_RH850_CORE3_312_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_313_ISR_CAT))
  .word _osEE_rh850_core3_ei313       #-- Core3 EIINT313
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT313
#endif /* OSEE_RH850_CORE3_313_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_314_ISR_CAT))
  .word _osEE_rh850_core3_ei314       #-- Core3 EIINT314
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT314
#endif /* OSEE_RH850_CORE3_314_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_315_ISR_CAT))
  .word _osEE_rh850_core3_ei315       #-- Core3 EIINT315
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT315
#endif /* OSEE_RH850_CORE3_315_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_316_ISR_CAT))
  .word _osEE_rh850_core3_ei316       #-- Core3 EIINT316
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT316
#endif /* OSEE_RH850_CORE3_316_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_317_ISR_CAT))
  .word _osEE_rh850_core3_ei317       #-- Core3 EIINT317
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT317
#endif /* OSEE_RH850_CORE3_317_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_318_ISR_CAT))
  .word _osEE_rh850_core3_ei318       #-- Core3 EIINT318
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT318
#endif /* OSEE_RH850_CORE3_318_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_319_ISR_CAT))
  .word _osEE_rh850_core3_ei319       #-- Core3 EIINT319
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT319
#endif /* OSEE_RH850_CORE3_319_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_320_ISR_CAT))
  .word _osEE_rh850_core3_ei320       #-- Core3 EIINT320
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT320
#endif /* OSEE_RH850_CORE3_320_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_321_ISR_CAT))
  .word _osEE_rh850_core3_ei321       #-- Core3 EIINT321
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT321
#endif /* OSEE_RH850_CORE3_321_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_322_ISR_CAT))
  .word _osEE_rh850_core3_ei322       #-- Core3 EIINT322
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT322
#endif /* OSEE_RH850_CORE3_322_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_323_ISR_CAT))
  .word _osEE_rh850_core3_ei323       #-- Core3 EIINT323
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT323
#endif /* OSEE_RH850_CORE3_323_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_324_ISR_CAT))
  .word _osEE_rh850_core3_ei324       #-- Core3 EIINT324
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT324
#endif /* OSEE_RH850_CORE3_324_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_325_ISR_CAT))
  .word _osEE_rh850_core3_ei325       #-- Core3 EIINT325
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT325
#endif /* OSEE_RH850_CORE3_325_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_326_ISR_CAT))
  .word _osEE_rh850_core3_ei326       #-- Core3 EIINT326
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT326
#endif /* OSEE_RH850_CORE3_326_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_327_ISR_CAT))
  .word _osEE_rh850_core3_ei327       #-- Core3 EIINT327
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT327
#endif /* OSEE_RH850_CORE3_327_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_328_ISR_CAT))
  .word _osEE_rh850_core3_ei328       #-- Core3 EIINT328
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT328
#endif /* OSEE_RH850_CORE3_328_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_329_ISR_CAT))
  .word _osEE_rh850_core3_ei329       #-- Core3 EIINT329
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT329
#endif /* OSEE_RH850_CORE3_329_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_330_ISR_CAT))
  .word _osEE_rh850_core3_ei330       #-- Core3 EIINT330
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT330
#endif /* OSEE_RH850_CORE3_330_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_331_ISR_CAT))
  .word _osEE_rh850_core3_ei331       #-- Core3 EIINT331
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT331
#endif /* OSEE_RH850_CORE3_331_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_332_ISR_CAT))
  .word _osEE_rh850_core3_ei332       #-- Core3 EIINT332
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT332
#endif /* OSEE_RH850_CORE3_332_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_333_ISR_CAT))
  .word _osEE_rh850_core3_ei333       #-- Core3 EIINT333
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT333
#endif /* OSEE_RH850_CORE3_333_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_334_ISR_CAT))
  .word _osEE_rh850_core3_ei334       #-- Core3 EIINT334
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT334
#endif /* OSEE_RH850_CORE3_334_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_335_ISR_CAT))
  .word _osEE_rh850_core3_ei335       #-- Core3 EIINT335
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT335
#endif /* OSEE_RH850_CORE3_335_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_336_ISR_CAT))
  .word _osEE_rh850_core3_ei336       #-- Core3 EIINT336
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT336
#endif /* OSEE_RH850_CORE3_336_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_337_ISR_CAT))
  .word _osEE_rh850_core3_ei337       #-- Core3 EIINT337
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT337
#endif /* OSEE_RH850_CORE3_337_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_338_ISR_CAT))
  .word _osEE_rh850_core3_ei338       #-- Core3 EIINT338
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT338
#endif /* OSEE_RH850_CORE3_338_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_339_ISR_CAT))
  .word _osEE_rh850_core3_ei339       #-- Core3 EIINT339
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT339
#endif /* OSEE_RH850_CORE3_339_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_340_ISR_CAT))
  .word _osEE_rh850_core3_ei340       #-- Core3 EIINT340
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT340
#endif /* OSEE_RH850_CORE3_340_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_341_ISR_CAT))
  .word _osEE_rh850_core3_ei341       #-- Core3 EIINT341
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT341
#endif /* OSEE_RH850_CORE3_341_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_342_ISR_CAT))
  .word _osEE_rh850_core3_ei342       #-- Core3 EIINT342
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT342
#endif /* OSEE_RH850_CORE3_342_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_343_ISR_CAT))
  .word _osEE_rh850_core3_ei343       #-- Core3 EIINT343
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT343
#endif /* OSEE_RH850_CORE3_343_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_344_ISR_CAT))
  .word _osEE_rh850_core3_ei344       #-- Core3 EIINT344
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT344
#endif /* OSEE_RH850_CORE3_344_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_345_ISR_CAT))
  .word _osEE_rh850_core3_ei345       #-- Core3 EIINT345
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT345
#endif /* OSEE_RH850_CORE3_345_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_346_ISR_CAT))
  .word _osEE_rh850_core3_ei346       #-- Core3 EIINT346
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT346
#endif /* OSEE_RH850_CORE3_346_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_347_ISR_CAT))
  .word _osEE_rh850_core3_ei347       #-- Core3 EIINT347
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT347
#endif /* OSEE_RH850_CORE3_347_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_348_ISR_CAT))
  .word _osEE_rh850_core3_ei348       #-- Core3 EIINT348
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT348
#endif /* OSEE_RH850_CORE3_348_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_349_ISR_CAT))
  .word _osEE_rh850_core3_ei349       #-- Core3 EIINT349
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT349
#endif /* OSEE_RH850_CORE3_349_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_350_ISR_CAT))
  .word _osEE_rh850_core3_ei350       #-- Core3 EIINT350
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT350
#endif /* OSEE_RH850_CORE3_350_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_351_ISR_CAT))
  .word _osEE_rh850_core3_ei351       #-- Core3 EIINT351
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT351
#endif /* OSEE_RH850_CORE3_351_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_352_ISR_CAT))
  .word _osEE_rh850_core3_ei352       #-- Core3 EIINT352
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT352
#endif /* OSEE_RH850_CORE3_352_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_353_ISR_CAT))
  .word _osEE_rh850_core3_ei353       #-- Core3 EIINT353
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT353
#endif /* OSEE_RH850_CORE3_353_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_354_ISR_CAT))
  .word _osEE_rh850_core3_ei354       #-- Core3 EIINT354
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT354
#endif /* OSEE_RH850_CORE3_354_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_355_ISR_CAT))
  .word _osEE_rh850_core3_ei355       #-- Core3 EIINT355
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT355
#endif /* OSEE_RH850_CORE3_355_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_356_ISR_CAT))
  .word _osEE_rh850_core3_ei356       #-- Core3 EIINT356
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT356
#endif /* OSEE_RH850_CORE3_356_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_357_ISR_CAT))
  .word _osEE_rh850_core3_ei357       #-- Core3 EIINT357
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT357
#endif /* OSEE_RH850_CORE3_357_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_358_ISR_CAT))
  .word _osEE_rh850_core3_ei358       #-- Core3 EIINT358
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT358
#endif /* OSEE_RH850_CORE3_358_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_359_ISR_CAT))
  .word _osEE_rh850_core3_ei359       #-- Core3 EIINT359
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT359
#endif /* OSEE_RH850_CORE3_359_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_360_ISR_CAT))
  .word _osEE_rh850_core3_ei360       #-- Core3 EIINT360
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT360
#endif /* OSEE_RH850_CORE3_360_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_361_ISR_CAT))
  .word _osEE_rh850_core3_ei361       #-- Core3 EIINT361
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT361
#endif /* OSEE_RH850_CORE3_361_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_362_ISR_CAT))
  .word _osEE_rh850_core3_ei362       #-- Core3 EIINT362
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT362
#endif /* OSEE_RH850_CORE3_362_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_363_ISR_CAT))
  .word _osEE_rh850_core3_ei363       #-- Core3 EIINT363
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT363
#endif /* OSEE_RH850_CORE3_363_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_364_ISR_CAT))
  .word _osEE_rh850_core3_ei364       #-- Core3 EIINT364
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT364
#endif /* OSEE_RH850_CORE3_364_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_365_ISR_CAT))
  .word _osEE_rh850_core3_ei365       #-- Core3 EIINT365
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT365
#endif /* OSEE_RH850_CORE3_365_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_366_ISR_CAT))
  .word _osEE_rh850_core3_ei366       #-- Core3 EIINT366
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT366
#endif /* OSEE_RH850_CORE3_366_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_367_ISR_CAT))
  .word _osEE_rh850_core3_ei367       #-- Core3 EIINT367
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT367
#endif /* OSEE_RH850_CORE3_367_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_368_ISR_CAT))
  .word _osEE_rh850_core3_ei368       #-- Core3 EIINT368
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT368
#endif /* OSEE_RH850_CORE3_368_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_369_ISR_CAT))
  .word _osEE_rh850_core3_ei369       #-- Core3 EIINT369
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT369
#endif /* OSEE_RH850_CORE3_369_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_370_ISR_CAT))
  .word _osEE_rh850_core3_ei370       #-- Core3 EIINT370
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT370
#endif /* OSEE_RH850_CORE3_370_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_371_ISR_CAT))
  .word _osEE_rh850_core3_ei371       #-- Core3 EIINT371
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT371
#endif /* OSEE_RH850_CORE3_371_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_372_ISR_CAT))
  .word _osEE_rh850_core3_ei372       #-- Core3 EIINT372
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT372
#endif /* OSEE_RH850_CORE3_372_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_373_ISR_CAT))
  .word _osEE_rh850_core3_ei373       #-- Core3 EIINT373
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT373
#endif /* OSEE_RH850_CORE3_373_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_374_ISR_CAT))
  .word _osEE_rh850_core3_ei374       #-- Core3 EIINT374
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT374
#endif /* OSEE_RH850_CORE3_374_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_375_ISR_CAT))
  .word _osEE_rh850_core3_ei375       #-- Core3 EIINT375
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT375
#endif /* OSEE_RH850_CORE3_375_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_376_ISR_CAT))
  .word _osEE_rh850_core3_ei376       #-- Core3 EIINT376
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT376
#endif /* OSEE_RH850_CORE3_376_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_377_ISR_CAT))
  .word _osEE_rh850_core3_ei377       #-- Core3 EIINT377
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT377
#endif /* OSEE_RH850_CORE3_377_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_378_ISR_CAT))
  .word _osEE_rh850_core3_ei378       #-- Core3 EIINT378
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT378
#endif /* OSEE_RH850_CORE3_378_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_379_ISR_CAT))
  .word _osEE_rh850_core3_ei379       #-- Core3 EIINT379
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT379
#endif /* OSEE_RH850_CORE3_379_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_380_ISR_CAT))
  .word _osEE_rh850_core3_ei380       #-- Core3 EIINT380
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT380
#endif /* OSEE_RH850_CORE3_380_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_381_ISR_CAT))
  .word _osEE_rh850_core3_ei381       #-- Core3 EIINT381
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT381
#endif /* OSEE_RH850_CORE3_381_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_382_ISR_CAT))
  .word _osEE_rh850_core3_ei382       #-- Core3 EIINT382
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT382
#endif /* OSEE_RH850_CORE3_382_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_383_ISR_CAT))
  .word _osEE_rh850_core3_ei383       #-- Core3 EIINT383
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT383
#endif /* OSEE_RH850_CORE3_383_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_384_ISR_CAT))
  .word _osEE_rh850_core3_ei384       #-- Core3 EIINT384
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT384
#endif /* OSEE_RH850_CORE3_384_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_385_ISR_CAT))
  .word _osEE_rh850_core3_ei385       #-- Core3 EIINT385
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT385
#endif /* OSEE_RH850_CORE3_385_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_386_ISR_CAT))
  .word _osEE_rh850_core3_ei386       #-- Core3 EIINT386
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT386
#endif /* OSEE_RH850_CORE3_386_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_387_ISR_CAT))
  .word _osEE_rh850_core3_ei387       #-- Core3 EIINT387
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT387
#endif /* OSEE_RH850_CORE3_387_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_388_ISR_CAT))
  .word _osEE_rh850_core3_ei388       #-- Core3 EIINT388
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT388
#endif /* OSEE_RH850_CORE3_388_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_389_ISR_CAT))
  .word _osEE_rh850_core3_ei389       #-- Core3 EIINT389
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT389
#endif /* OSEE_RH850_CORE3_389_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_390_ISR_CAT))
  .word _osEE_rh850_core3_ei390       #-- Core3 EIINT390
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT390
#endif /* OSEE_RH850_CORE3_390_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_391_ISR_CAT))
  .word _osEE_rh850_core3_ei391       #-- Core3 EIINT391
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT391
#endif /* OSEE_RH850_CORE3_391_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_392_ISR_CAT))
  .word _osEE_rh850_core3_ei392       #-- Core3 EIINT392
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT392
#endif /* OSEE_RH850_CORE3_392_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_393_ISR_CAT))
  .word _osEE_rh850_core3_ei393       #-- Core3 EIINT393
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT393
#endif /* OSEE_RH850_CORE3_393_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_394_ISR_CAT))
  .word _osEE_rh850_core3_ei394       #-- Core3 EIINT394
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT394
#endif /* OSEE_RH850_CORE3_394_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_395_ISR_CAT))
  .word _osEE_rh850_core3_ei395       #-- Core3 EIINT395
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT395
#endif /* OSEE_RH850_CORE3_395_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_396_ISR_CAT))
  .word _osEE_rh850_core3_ei396       #-- Core3 EIINT396
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT396
#endif /* OSEE_RH850_CORE3_396_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_397_ISR_CAT))
  .word _osEE_rh850_core3_ei397       #-- Core3 EIINT397
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT397
#endif /* OSEE_RH850_CORE3_397_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_398_ISR_CAT))
  .word _osEE_rh850_core3_ei398       #-- Core3 EIINT398
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT398
#endif /* OSEE_RH850_CORE3_398_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_399_ISR_CAT))
  .word _osEE_rh850_core3_ei399       #-- Core3 EIINT399
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT399
#endif /* OSEE_RH850_CORE3_399_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_400_ISR_CAT))
  .word _osEE_rh850_core3_ei400       #-- Core3 EIINT400
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT400
#endif /* OSEE_RH850_CORE3_400_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_401_ISR_CAT))
  .word _osEE_rh850_core3_ei401       #-- Core3 EIINT401
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT401
#endif /* OSEE_RH850_CORE3_401_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_402_ISR_CAT))
  .word _osEE_rh850_core3_ei402       #-- Core3 EIINT402
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT402
#endif /* OSEE_RH850_CORE3_402_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_403_ISR_CAT))
  .word _osEE_rh850_core3_ei403       #-- Core3 EIINT403
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT403
#endif /* OSEE_RH850_CORE3_403_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_404_ISR_CAT))
  .word _osEE_rh850_core3_ei404       #-- Core3 EIINT404
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT404
#endif /* OSEE_RH850_CORE3_404_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_405_ISR_CAT))
  .word _osEE_rh850_core3_ei405       #-- Core3 EIINT405
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT405
#endif /* OSEE_RH850_CORE3_405_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_406_ISR_CAT))
  .word _osEE_rh850_core3_ei406       #-- Core3 EIINT406
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT406
#endif /* OSEE_RH850_CORE3_406_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_407_ISR_CAT))
  .word _osEE_rh850_core3_ei407       #-- Core3 EIINT407
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT407
#endif /* OSEE_RH850_CORE3_407_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_408_ISR_CAT))
  .word _osEE_rh850_core3_ei408       #-- Core3 EIINT408
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT408
#endif /* OSEE_RH850_CORE3_408_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_409_ISR_CAT))
  .word _osEE_rh850_core3_ei409       #-- Core3 EIINT409
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT409
#endif /* OSEE_RH850_CORE3_409_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_410_ISR_CAT))
  .word _osEE_rh850_core3_ei410       #-- Core3 EIINT410
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT410
#endif /* OSEE_RH850_CORE3_410_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_411_ISR_CAT))
  .word _osEE_rh850_core3_ei411       #-- Core3 EIINT411
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT411
#endif /* OSEE_RH850_CORE3_411_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_412_ISR_CAT))
  .word _osEE_rh850_core3_ei412       #-- Core3 EIINT412
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT412
#endif /* OSEE_RH850_CORE3_412_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_413_ISR_CAT))
  .word _osEE_rh850_core3_ei413       #-- Core3 EIINT413
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT413
#endif /* OSEE_RH850_CORE3_413_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_414_ISR_CAT))
  .word _osEE_rh850_core3_ei414       #-- Core3 EIINT414
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT414
#endif /* OSEE_RH850_CORE3_414_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_415_ISR_CAT))
  .word _osEE_rh850_core3_ei415       #-- Core3 EIINT415
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT415
#endif /* OSEE_RH850_CORE3_415_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_416_ISR_CAT))
  .word _osEE_rh850_core3_ei416       #-- Core3 EIINT416
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT416
#endif /* OSEE_RH850_CORE3_416_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_417_ISR_CAT))
  .word _osEE_rh850_core3_ei417       #-- Core3 EIINT417
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT417
#endif /* OSEE_RH850_CORE3_417_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_418_ISR_CAT))
  .word _osEE_rh850_core3_ei418       #-- Core3 EIINT418
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT418
#endif /* OSEE_RH850_CORE3_418_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_419_ISR_CAT))
  .word _osEE_rh850_core3_ei419       #-- Core3 EIINT419
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT419
#endif /* OSEE_RH850_CORE3_419_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_420_ISR_CAT))
  .word _osEE_rh850_core3_ei420       #-- Core3 EIINT420
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT420
#endif /* OSEE_RH850_CORE3_420_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_421_ISR_CAT))
  .word _osEE_rh850_core3_ei421       #-- Core3 EIINT421
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT421
#endif /* OSEE_RH850_CORE3_421_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_422_ISR_CAT))
  .word _osEE_rh850_core3_ei422       #-- Core3 EIINT422
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT422
#endif /* OSEE_RH850_CORE3_422_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_423_ISR_CAT))
  .word _osEE_rh850_core3_ei423       #-- Core3 EIINT423
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT423
#endif /* OSEE_RH850_CORE3_423_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_424_ISR_CAT))
  .word _osEE_rh850_core3_ei424       #-- Core3 EIINT424
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT424
#endif /* OSEE_RH850_CORE3_424_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_425_ISR_CAT))
  .word _osEE_rh850_core3_ei425       #-- Core3 EIINT425
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT425
#endif /* OSEE_RH850_CORE3_425_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_426_ISR_CAT))
  .word _osEE_rh850_core3_ei426       #-- Core3 EIINT426
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT426
#endif /* OSEE_RH850_CORE3_426_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_427_ISR_CAT))
  .word _osEE_rh850_core3_ei427       #-- Core3 EIINT427
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT427
#endif /* OSEE_RH850_CORE3_427_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_428_ISR_CAT))
  .word _osEE_rh850_core3_ei428       #-- Core3 EIINT428
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT428
#endif /* OSEE_RH850_CORE3_428_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_429_ISR_CAT))
  .word _osEE_rh850_core3_ei429       #-- Core3 EIINT429
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT429
#endif /* OSEE_RH850_CORE3_429_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_430_ISR_CAT))
  .word _osEE_rh850_core3_ei430       #-- Core3 EIINT430
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT430
#endif /* OSEE_RH850_CORE3_430_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_431_ISR_CAT))
  .word _osEE_rh850_core3_ei431       #-- Core3 EIINT431
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT431
#endif /* OSEE_RH850_CORE3_431_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_432_ISR_CAT))
  .word _osEE_rh850_core3_ei432       #-- Core3 EIINT432
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT432
#endif /* OSEE_RH850_CORE3_432_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_433_ISR_CAT))
  .word _osEE_rh850_core3_ei433       #-- Core3 EIINT433
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT433
#endif /* OSEE_RH850_CORE3_433_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_434_ISR_CAT))
  .word _osEE_rh850_core3_ei434       #-- Core3 EIINT434
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT434
#endif /* OSEE_RH850_CORE3_434_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_435_ISR_CAT))
  .word _osEE_rh850_core3_ei435       #-- Core3 EIINT435
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT435
#endif /* OSEE_RH850_CORE3_435_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_436_ISR_CAT))
  .word _osEE_rh850_core3_ei436       #-- Core3 EIINT436
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT436
#endif /* OSEE_RH850_CORE3_436_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_437_ISR_CAT))
  .word _osEE_rh850_core3_ei437       #-- Core3 EIINT437
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT437
#endif /* OSEE_RH850_CORE3_437_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_438_ISR_CAT))
  .word _osEE_rh850_core3_ei438       #-- Core3 EIINT438
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT438
#endif /* OSEE_RH850_CORE3_438_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_439_ISR_CAT))
  .word _osEE_rh850_core3_ei439       #-- Core3 EIINT439
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT439
#endif /* OSEE_RH850_CORE3_439_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_440_ISR_CAT))
  .word _osEE_rh850_core3_ei440       #-- Core3 EIINT440
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT440
#endif /* OSEE_RH850_CORE3_440_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_441_ISR_CAT))
  .word _osEE_rh850_core3_ei441       #-- Core3 EIINT441
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT441
#endif /* OSEE_RH850_CORE3_441_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_442_ISR_CAT))
  .word _osEE_rh850_core3_ei442       #-- Core3 EIINT442
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT442
#endif /* OSEE_RH850_CORE3_442_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_443_ISR_CAT))
  .word _osEE_rh850_core3_ei443       #-- Core3 EIINT443
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT443
#endif /* OSEE_RH850_CORE3_443_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_444_ISR_CAT))
  .word _osEE_rh850_core3_ei444       #-- Core3 EIINT444
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT444
#endif /* OSEE_RH850_CORE3_444_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_445_ISR_CAT))
  .word _osEE_rh850_core3_ei445       #-- Core3 EIINT445
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT445
#endif /* OSEE_RH850_CORE3_445_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_446_ISR_CAT))
  .word _osEE_rh850_core3_ei446       #-- Core3 EIINT446
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT446
#endif /* OSEE_RH850_CORE3_446_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_447_ISR_CAT))
  .word _osEE_rh850_core3_ei447       #-- Core3 EIINT447
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT447
#endif /* OSEE_RH850_CORE3_447_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_448_ISR_CAT))
  .word _osEE_rh850_core3_ei448       #-- Core3 EIINT448
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT448
#endif /* OSEE_RH850_CORE3_448_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_449_ISR_CAT))
  .word _osEE_rh850_core3_ei449       #-- Core3 EIINT449
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT449
#endif /* OSEE_RH850_CORE3_449_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_450_ISR_CAT))
  .word _osEE_rh850_core3_ei450       #-- Core3 EIINT450
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT450
#endif /* OSEE_RH850_CORE3_450_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_451_ISR_CAT))
  .word _osEE_rh850_core3_ei451       #-- Core3 EIINT451
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT451
#endif /* OSEE_RH850_CORE3_451_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_452_ISR_CAT))
  .word _osEE_rh850_core3_ei452       #-- Core3 EIINT452
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT452
#endif /* OSEE_RH850_CORE3_452_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_453_ISR_CAT))
  .word _osEE_rh850_core3_ei453       #-- Core3 EIINT453
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT453
#endif /* OSEE_RH850_CORE3_453_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_454_ISR_CAT))
  .word _osEE_rh850_core3_ei454       #-- Core3 EIINT454
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT454
#endif /* OSEE_RH850_CORE3_454_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_455_ISR_CAT))
  .word _osEE_rh850_core3_ei455       #-- Core3 EIINT455
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT455
#endif /* OSEE_RH850_CORE3_455_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_456_ISR_CAT))
  .word _osEE_rh850_core3_ei456       #-- Core3 EIINT456
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT456
#endif /* OSEE_RH850_CORE3_456_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_457_ISR_CAT))
  .word _osEE_rh850_core3_ei457       #-- Core3 EIINT457
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT457
#endif /* OSEE_RH850_CORE3_457_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_458_ISR_CAT))
  .word _osEE_rh850_core3_ei458       #-- Core3 EIINT458
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT458
#endif /* OSEE_RH850_CORE3_458_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_459_ISR_CAT))
  .word _osEE_rh850_core3_ei459       #-- Core3 EIINT459
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT459
#endif /* OSEE_RH850_CORE3_459_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_460_ISR_CAT))
  .word _osEE_rh850_core3_ei460       #-- Core3 EIINT460
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT460
#endif /* OSEE_RH850_CORE3_460_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_461_ISR_CAT))
  .word _osEE_rh850_core3_ei461       #-- Core3 EIINT461
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT461
#endif /* OSEE_RH850_CORE3_461_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_462_ISR_CAT))
  .word _osEE_rh850_core3_ei462       #-- Core3 EIINT462
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT462
#endif /* OSEE_RH850_CORE3_462_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_463_ISR_CAT))
  .word _osEE_rh850_core3_ei463       #-- Core3 EIINT463
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT463
#endif /* OSEE_RH850_CORE3_463_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_464_ISR_CAT))
  .word _osEE_rh850_core3_ei464       #-- Core3 EIINT464
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT464
#endif /* OSEE_RH850_CORE3_464_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_465_ISR_CAT))
  .word _osEE_rh850_core3_ei465       #-- Core3 EIINT465
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT465
#endif /* OSEE_RH850_CORE3_465_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_466_ISR_CAT))
  .word _osEE_rh850_core3_ei466       #-- Core3 EIINT466
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT466
#endif /* OSEE_RH850_CORE3_466_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_467_ISR_CAT))
  .word _osEE_rh850_core3_ei467       #-- Core3 EIINT467
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT467
#endif /* OSEE_RH850_CORE3_467_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_468_ISR_CAT))
  .word _osEE_rh850_core3_ei468       #-- Core3 EIINT468
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT468
#endif /* OSEE_RH850_CORE3_468_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_469_ISR_CAT))
  .word _osEE_rh850_core3_ei469       #-- Core3 EIINT469
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT469
#endif /* OSEE_RH850_CORE3_469_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_470_ISR_CAT))
  .word _osEE_rh850_core3_ei470       #-- Core3 EIINT470
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT470
#endif /* OSEE_RH850_CORE3_470_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_471_ISR_CAT))
  .word _osEE_rh850_core3_ei471       #-- Core3 EIINT471
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT471
#endif /* OSEE_RH850_CORE3_471_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_472_ISR_CAT))
  .word _osEE_rh850_core3_ei472       #-- Core3 EIINT472
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT472
#endif /* OSEE_RH850_CORE3_472_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_473_ISR_CAT))
  .word _osEE_rh850_core3_ei473       #-- Core3 EIINT473
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT473
#endif /* OSEE_RH850_CORE3_473_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_474_ISR_CAT))
  .word _osEE_rh850_core3_ei474       #-- Core3 EIINT474
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT474
#endif /* OSEE_RH850_CORE3_474_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_475_ISR_CAT))
  .word _osEE_rh850_core3_ei475       #-- Core3 EIINT475
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT475
#endif /* OSEE_RH850_CORE3_475_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_476_ISR_CAT))
  .word _osEE_rh850_core3_ei476       #-- Core3 EIINT476
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT476
#endif /* OSEE_RH850_CORE3_476_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_477_ISR_CAT))
  .word _osEE_rh850_core3_ei477       #-- Core3 EIINT477
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT477
#endif /* OSEE_RH850_CORE3_477_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_478_ISR_CAT))
  .word _osEE_rh850_core3_ei478       #-- Core3 EIINT478
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT478
#endif /* OSEE_RH850_CORE3_478_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_479_ISR_CAT))
  .word _osEE_rh850_core3_ei479       #-- Core3 EIINT479
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT479
#endif /* OSEE_RH850_CORE3_479_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_480_ISR_CAT))
  .word _osEE_rh850_core3_ei480       #-- Core3 EIINT480
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT480
#endif /* OSEE_RH850_CORE3_480_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_481_ISR_CAT))
  .word _osEE_rh850_core3_ei481       #-- Core3 EIINT481
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT481
#endif /* OSEE_RH850_CORE3_481_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_482_ISR_CAT))
  .word _osEE_rh850_core3_ei482       #-- Core3 EIINT482
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT482
#endif /* OSEE_RH850_CORE3_482_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_483_ISR_CAT))
  .word _osEE_rh850_core3_ei483       #-- Core3 EIINT483
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT483
#endif /* OSEE_RH850_CORE3_483_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_484_ISR_CAT))
  .word _osEE_rh850_core3_ei484       #-- Core3 EIINT484
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT484
#endif /* OSEE_RH850_CORE3_484_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_485_ISR_CAT))
  .word _osEE_rh850_core3_ei485       #-- Core3 EIINT485
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT485
#endif /* OSEE_RH850_CORE3_485_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_486_ISR_CAT))
  .word _osEE_rh850_core3_ei486       #-- Core3 EIINT486
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT486
#endif /* OSEE_RH850_CORE3_486_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_487_ISR_CAT))
  .word _osEE_rh850_core3_ei487       #-- Core3 EIINT487
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT487
#endif /* OSEE_RH850_CORE3_487_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_488_ISR_CAT))
  .word _osEE_rh850_core3_ei488       #-- Core3 EIINT488
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT488
#endif /* OSEE_RH850_CORE3_488_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_489_ISR_CAT))
  .word _osEE_rh850_core3_ei489       #-- Core3 EIINT489
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT489
#endif /* OSEE_RH850_CORE3_489_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_490_ISR_CAT))
  .word _osEE_rh850_core3_ei490       #-- Core3 EIINT490
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT490
#endif /* OSEE_RH850_CORE3_490_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_491_ISR_CAT))
  .word _osEE_rh850_core3_ei491       #-- Core3 EIINT491
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT491
#endif /* OSEE_RH850_CORE3_491_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_492_ISR_CAT))
  .word _osEE_rh850_core3_ei492       #-- Core3 EIINT492
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT492
#endif /* OSEE_RH850_CORE3_492_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_493_ISR_CAT))
  .word _osEE_rh850_core3_ei493       #-- Core3 EIINT493
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT493
#endif /* OSEE_RH850_CORE3_493_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_494_ISR_CAT))
  .word _osEE_rh850_core3_ei494       #-- Core3 EIINT494
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT494
#endif /* OSEE_RH850_CORE3_494_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_495_ISR_CAT))
  .word _osEE_rh850_core3_ei495       #-- Core3 EIINT495
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT495
#endif /* OSEE_RH850_CORE3_495_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_496_ISR_CAT))
  .word _osEE_rh850_core3_ei496       #-- Core3 EIINT496
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT496
#endif /* OSEE_RH850_CORE3_496_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_497_ISR_CAT))
  .word _osEE_rh850_core3_ei497       #-- Core3 EIINT497
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT497
#endif /* OSEE_RH850_CORE3_497_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_498_ISR_CAT))
  .word _osEE_rh850_core3_ei498       #-- Core3 EIINT498
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT498
#endif /* OSEE_RH850_CORE3_498_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_499_ISR_CAT))
  .word _osEE_rh850_core3_ei499       #-- Core3 EIINT499
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT499
#endif /* OSEE_RH850_CORE3_499_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_500_ISR_CAT))
  .word _osEE_rh850_core3_ei500       #-- Core3 EIINT500
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT500
#endif /* OSEE_RH850_CORE3_500_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_501_ISR_CAT))
  .word _osEE_rh850_core3_ei501       #-- Core3 EIINT501
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT501
#endif /* OSEE_RH850_CORE3_501_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_502_ISR_CAT))
  .word _osEE_rh850_core3_ei502       #-- Core3 EIINT502
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT502
#endif /* OSEE_RH850_CORE3_502_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_503_ISR_CAT))
  .word _osEE_rh850_core3_ei503       #-- Core3 EIINT503
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT503
#endif /* OSEE_RH850_CORE3_503_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_504_ISR_CAT))
  .word _osEE_rh850_core3_ei504       #-- Core3 EIINT504
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT504
#endif /* OSEE_RH850_CORE3_504_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_505_ISR_CAT))
  .word _osEE_rh850_core3_ei505       #-- Core3 EIINT505
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT505
#endif /* OSEE_RH850_CORE3_505_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_506_ISR_CAT))
  .word _osEE_rh850_core3_ei506       #-- Core3 EIINT506
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT506
#endif /* OSEE_RH850_CORE3_506_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_507_ISR_CAT))
  .word _osEE_rh850_core3_ei507       #-- Core3 EIINT507
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT507
#endif /* OSEE_RH850_CORE3_507_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_508_ISR_CAT))
  .word _osEE_rh850_core3_ei508       #-- Core3 EIINT508
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT508
#endif /* OSEE_RH850_CORE3_508_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_509_ISR_CAT))
  .word _osEE_rh850_core3_ei509       #-- Core3 EIINT509
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT509
#endif /* OSEE_RH850_CORE3_509_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_510_ISR_CAT))
  .word _osEE_rh850_core3_ei510       #-- Core3 EIINT510
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT510
#endif /* OSEE_RH850_CORE3_510_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_511_ISR_CAT))
  .word _osEE_rh850_core3_ei511       #-- Core3 EIINT511
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT511
#endif /* OSEE_RH850_CORE3_511_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_512_ISR_CAT))
  .word _osEE_rh850_core3_ei512       #-- Core3 EIINT512
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT512
#endif /* OSEE_RH850_CORE3_512_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_513_ISR_CAT))
  .word _osEE_rh850_core3_ei513       #-- Core3 EIINT513
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT513
#endif /* OSEE_RH850_CORE3_513_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_514_ISR_CAT))
  .word _osEE_rh850_core3_ei514       #-- Core3 EIINT514
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT514
#endif /* OSEE_RH850_CORE3_514_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_515_ISR_CAT))
  .word _osEE_rh850_core3_ei515       #-- Core3 EIINT515
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT515
#endif /* OSEE_RH850_CORE3_515_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_516_ISR_CAT))
  .word _osEE_rh850_core3_ei516       #-- Core3 EIINT516
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT516
#endif /* OSEE_RH850_CORE3_516_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_517_ISR_CAT))
  .word _osEE_rh850_core3_ei517       #-- Core3 EIINT517
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT517
#endif /* OSEE_RH850_CORE3_517_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_518_ISR_CAT))
  .word _osEE_rh850_core3_ei518       #-- Core3 EIINT518
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT518
#endif /* OSEE_RH850_CORE3_518_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_519_ISR_CAT))
  .word _osEE_rh850_core3_ei519       #-- Core3 EIINT519
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT519
#endif /* OSEE_RH850_CORE3_519_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_520_ISR_CAT))
  .word _osEE_rh850_core3_ei520       #-- Core3 EIINT520
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT520
#endif /* OSEE_RH850_CORE3_520_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_521_ISR_CAT))
  .word _osEE_rh850_core3_ei521       #-- Core3 EIINT521
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT521
#endif /* OSEE_RH850_CORE3_521_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_522_ISR_CAT))
  .word _osEE_rh850_core3_ei522       #-- Core3 EIINT522
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT522
#endif /* OSEE_RH850_CORE3_522_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_523_ISR_CAT))
  .word _osEE_rh850_core3_ei523       #-- Core3 EIINT523
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT523
#endif /* OSEE_RH850_CORE3_523_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_524_ISR_CAT))
  .word _osEE_rh850_core3_ei524       #-- Core3 EIINT524
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT524
#endif /* OSEE_RH850_CORE3_524_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_525_ISR_CAT))
  .word _osEE_rh850_core3_ei525       #-- Core3 EIINT525
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT525
#endif /* OSEE_RH850_CORE3_525_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_526_ISR_CAT))
  .word _osEE_rh850_core3_ei526       #-- Core3 EIINT526
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT526
#endif /* OSEE_RH850_CORE3_526_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_527_ISR_CAT))
  .word _osEE_rh850_core3_ei527       #-- Core3 EIINT527
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT527
#endif /* OSEE_RH850_CORE3_527_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_528_ISR_CAT))
  .word _osEE_rh850_core3_ei528       #-- Core3 EIINT528
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT528
#endif /* OSEE_RH850_CORE3_528_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_529_ISR_CAT))
  .word _osEE_rh850_core3_ei529       #-- Core3 EIINT529
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT529
#endif /* OSEE_RH850_CORE3_529_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_530_ISR_CAT))
  .word _osEE_rh850_core3_ei530       #-- Core3 EIINT530
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT530
#endif /* OSEE_RH850_CORE3_530_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_531_ISR_CAT))
  .word _osEE_rh850_core3_ei531       #-- Core3 EIINT531
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT531
#endif /* OSEE_RH850_CORE3_531_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_532_ISR_CAT))
  .word _osEE_rh850_core3_ei532       #-- Core3 EIINT532
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT532
#endif /* OSEE_RH850_CORE3_532_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_533_ISR_CAT))
  .word _osEE_rh850_core3_ei533       #-- Core3 EIINT533
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT533
#endif /* OSEE_RH850_CORE3_533_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_534_ISR_CAT))
  .word _osEE_rh850_core3_ei534       #-- Core3 EIINT534
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT534
#endif /* OSEE_RH850_CORE3_534_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_535_ISR_CAT))
  .word _osEE_rh850_core3_ei535       #-- Core3 EIINT535
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT535
#endif /* OSEE_RH850_CORE3_535_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_536_ISR_CAT))
  .word _osEE_rh850_core3_ei536       #-- Core3 EIINT536
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT536
#endif /* OSEE_RH850_CORE3_536_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_537_ISR_CAT))
  .word _osEE_rh850_core3_ei537       #-- Core3 EIINT537
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT537
#endif /* OSEE_RH850_CORE3_537_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_538_ISR_CAT))
  .word _osEE_rh850_core3_ei538       #-- Core3 EIINT538
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT538
#endif /* OSEE_RH850_CORE3_538_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_539_ISR_CAT))
  .word _osEE_rh850_core3_ei539       #-- Core3 EIINT539
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT539
#endif /* OSEE_RH850_CORE3_539_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_540_ISR_CAT))
  .word _osEE_rh850_core3_ei540       #-- Core3 EIINT540
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT540
#endif /* OSEE_RH850_CORE3_540_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_541_ISR_CAT))
  .word _osEE_rh850_core3_ei541       #-- Core3 EIINT541
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT541
#endif /* OSEE_RH850_CORE3_541_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_542_ISR_CAT))
  .word _osEE_rh850_core3_ei542       #-- Core3 EIINT542
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT542
#endif /* OSEE_RH850_CORE3_542_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_543_ISR_CAT))
  .word _osEE_rh850_core3_ei543       #-- Core3 EIINT543
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT543
#endif /* OSEE_RH850_CORE3_543_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_544_ISR_CAT))
  .word _osEE_rh850_core3_ei544       #-- Core3 EIINT544
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT544
#endif /* OSEE_RH850_CORE3_544_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_545_ISR_CAT))
  .word _osEE_rh850_core3_ei545       #-- Core3 EIINT545
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT545
#endif /* OSEE_RH850_CORE3_545_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_546_ISR_CAT))
  .word _osEE_rh850_core3_ei546       #-- Core3 EIINT546
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT546
#endif /* OSEE_RH850_CORE3_546_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_547_ISR_CAT))
  .word _osEE_rh850_core3_ei547       #-- Core3 EIINT547
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT547
#endif /* OSEE_RH850_CORE3_547_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_548_ISR_CAT))
  .word _osEE_rh850_core3_ei548       #-- Core3 EIINT548
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT548
#endif /* OSEE_RH850_CORE3_548_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_549_ISR_CAT))
  .word _osEE_rh850_core3_ei549       #-- Core3 EIINT549
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT549
#endif /* OSEE_RH850_CORE3_549_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_550_ISR_CAT))
  .word _osEE_rh850_core3_ei550       #-- Core3 EIINT550
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT550
#endif /* OSEE_RH850_CORE3_550_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_551_ISR_CAT))
  .word _osEE_rh850_core3_ei551       #-- Core3 EIINT551
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT551
#endif /* OSEE_RH850_CORE3_551_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_552_ISR_CAT))
  .word _osEE_rh850_core3_ei552       #-- Core3 EIINT552
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT552
#endif /* OSEE_RH850_CORE3_552_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_553_ISR_CAT))
  .word _osEE_rh850_core3_ei553       #-- Core3 EIINT553
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT553
#endif /* OSEE_RH850_CORE3_553_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_554_ISR_CAT))
  .word _osEE_rh850_core3_ei554       #-- Core3 EIINT554
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT554
#endif /* OSEE_RH850_CORE3_554_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_555_ISR_CAT))
  .word _osEE_rh850_core3_ei555       #-- Core3 EIINT555
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT555
#endif /* OSEE_RH850_CORE3_555_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_556_ISR_CAT))
  .word _osEE_rh850_core3_ei556       #-- Core3 EIINT556
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT556
#endif /* OSEE_RH850_CORE3_556_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_557_ISR_CAT))
  .word _osEE_rh850_core3_ei557       #-- Core3 EIINT557
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT557
#endif /* OSEE_RH850_CORE3_557_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_558_ISR_CAT))
  .word _osEE_rh850_core3_ei558       #-- Core3 EIINT558
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT558
#endif /* OSEE_RH850_CORE3_558_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_559_ISR_CAT))
  .word _osEE_rh850_core3_ei559       #-- Core3 EIINT559
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT559
#endif /* OSEE_RH850_CORE3_559_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_560_ISR_CAT))
  .word _osEE_rh850_core3_ei560       #-- Core3 EIINT560
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT560
#endif /* OSEE_RH850_CORE3_560_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_561_ISR_CAT))
  .word _osEE_rh850_core3_ei561       #-- Core3 EIINT561
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT561
#endif /* OSEE_RH850_CORE3_561_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_562_ISR_CAT))
  .word _osEE_rh850_core3_ei562       #-- Core3 EIINT562
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT562
#endif /* OSEE_RH850_CORE3_562_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_563_ISR_CAT))
  .word _osEE_rh850_core3_ei563       #-- Core3 EIINT563
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT563
#endif /* OSEE_RH850_CORE3_563_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_564_ISR_CAT))
  .word _osEE_rh850_core3_ei564       #-- Core3 EIINT564
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT564
#endif /* OSEE_RH850_CORE3_564_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_565_ISR_CAT))
  .word _osEE_rh850_core3_ei565       #-- Core3 EIINT565
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT565
#endif /* OSEE_RH850_CORE3_565_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_566_ISR_CAT))
  .word _osEE_rh850_core3_ei566       #-- Core3 EIINT566
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT566
#endif /* OSEE_RH850_CORE3_566_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_567_ISR_CAT))
  .word _osEE_rh850_core3_ei567       #-- Core3 EIINT567
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT567
#endif /* OSEE_RH850_CORE3_567_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_568_ISR_CAT))
  .word _osEE_rh850_core3_ei568       #-- Core3 EIINT568
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT568
#endif /* OSEE_RH850_CORE3_568_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_569_ISR_CAT))
  .word _osEE_rh850_core3_ei569       #-- Core3 EIINT569
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT569
#endif /* OSEE_RH850_CORE3_569_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_570_ISR_CAT))
  .word _osEE_rh850_core3_ei570       #-- Core3 EIINT570
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT570
#endif /* OSEE_RH850_CORE3_570_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_571_ISR_CAT))
  .word _osEE_rh850_core3_ei571       #-- Core3 EIINT571
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT571
#endif /* OSEE_RH850_CORE3_571_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_572_ISR_CAT))
  .word _osEE_rh850_core3_ei572       #-- Core3 EIINT572
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT572
#endif /* OSEE_RH850_CORE3_572_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_573_ISR_CAT))
  .word _osEE_rh850_core3_ei573       #-- Core3 EIINT573
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT573
#endif /* OSEE_RH850_CORE3_573_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_574_ISR_CAT))
  .word _osEE_rh850_core3_ei574       #-- Core3 EIINT574
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT574
#endif /* OSEE_RH850_CORE3_574_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_575_ISR_CAT))
  .word _osEE_rh850_core3_ei575       #-- Core3 EIINT575
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT575
#endif /* OSEE_RH850_CORE3_575_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_576_ISR_CAT))
  .word _osEE_rh850_core3_ei576       #-- Core3 EIINT576
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT576
#endif /* OSEE_RH850_CORE3_576_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_577_ISR_CAT))
  .word _osEE_rh850_core3_ei577       #-- Core3 EIINT577
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT577
#endif /* OSEE_RH850_CORE3_577_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_578_ISR_CAT))
  .word _osEE_rh850_core3_ei578       #-- Core3 EIINT578
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT578
#endif /* OSEE_RH850_CORE3_578_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_579_ISR_CAT))
  .word _osEE_rh850_core3_ei579       #-- Core3 EIINT579
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT579
#endif /* OSEE_RH850_CORE3_579_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_580_ISR_CAT))
  .word _osEE_rh850_core3_ei580       #-- Core3 EIINT580
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT580
#endif /* OSEE_RH850_CORE3_580_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_581_ISR_CAT))
  .word _osEE_rh850_core3_ei581       #-- Core3 EIINT581
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT581
#endif /* OSEE_RH850_CORE3_581_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_582_ISR_CAT))
  .word _osEE_rh850_core3_ei582       #-- Core3 EIINT582
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT582
#endif /* OSEE_RH850_CORE3_582_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_583_ISR_CAT))
  .word _osEE_rh850_core3_ei583       #-- Core3 EIINT583
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT583
#endif /* OSEE_RH850_CORE3_583_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_584_ISR_CAT))
  .word _osEE_rh850_core3_ei584       #-- Core3 EIINT584
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT584
#endif /* OSEE_RH850_CORE3_584_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_585_ISR_CAT))
  .word _osEE_rh850_core3_ei585       #-- Core3 EIINT585
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT585
#endif /* OSEE_RH850_CORE3_585_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_586_ISR_CAT))
  .word _osEE_rh850_core3_ei586       #-- Core3 EIINT586
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT586
#endif /* OSEE_RH850_CORE3_586_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_587_ISR_CAT))
  .word _osEE_rh850_core3_ei587       #-- Core3 EIINT587
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT587
#endif /* OSEE_RH850_CORE3_587_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_588_ISR_CAT))
  .word _osEE_rh850_core3_ei588       #-- Core3 EIINT588
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT588
#endif /* OSEE_RH850_CORE3_588_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_589_ISR_CAT))
  .word _osEE_rh850_core3_ei589       #-- Core3 EIINT589
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT589
#endif /* OSEE_RH850_CORE3_589_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_590_ISR_CAT))
  .word _osEE_rh850_core3_ei590       #-- Core3 EIINT590
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT590
#endif /* OSEE_RH850_CORE3_590_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_591_ISR_CAT))
  .word _osEE_rh850_core3_ei591       #-- Core3 EIINT591
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT591
#endif /* OSEE_RH850_CORE3_591_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_592_ISR_CAT))
  .word _osEE_rh850_core3_ei592       #-- Core3 EIINT592
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT592
#endif /* OSEE_RH850_CORE3_592_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_593_ISR_CAT))
  .word _osEE_rh850_core3_ei593       #-- Core3 EIINT593
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT593
#endif /* OSEE_RH850_CORE3_593_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_594_ISR_CAT))
  .word _osEE_rh850_core3_ei594       #-- Core3 EIINT594
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT594
#endif /* OSEE_RH850_CORE3_594_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_595_ISR_CAT))
  .word _osEE_rh850_core3_ei595       #-- Core3 EIINT595
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT595
#endif /* OSEE_RH850_CORE3_595_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_596_ISR_CAT))
  .word _osEE_rh850_core3_ei596       #-- Core3 EIINT596
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT596
#endif /* OSEE_RH850_CORE3_596_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_597_ISR_CAT))
  .word _osEE_rh850_core3_ei597       #-- Core3 EIINT597
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT597
#endif /* OSEE_RH850_CORE3_597_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_598_ISR_CAT))
  .word _osEE_rh850_core3_ei598       #-- Core3 EIINT598
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT598
#endif /* OSEE_RH850_CORE3_598_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_599_ISR_CAT))
  .word _osEE_rh850_core3_ei599       #-- Core3 EIINT599
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT599
#endif /* OSEE_RH850_CORE3_599_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_600_ISR_CAT))
  .word _osEE_rh850_core3_ei600       #-- Core3 EIINT600
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT600
#endif /* OSEE_RH850_CORE3_600_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_601_ISR_CAT))
  .word _osEE_rh850_core3_ei601       #-- Core3 EIINT601
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT601
#endif /* OSEE_RH850_CORE3_601_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_602_ISR_CAT))
  .word _osEE_rh850_core3_ei602       #-- Core3 EIINT602
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT602
#endif /* OSEE_RH850_CORE3_602_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_603_ISR_CAT))
  .word _osEE_rh850_core3_ei603       #-- Core3 EIINT603
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT603
#endif /* OSEE_RH850_CORE3_603_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_604_ISR_CAT))
  .word _osEE_rh850_core3_ei604       #-- Core3 EIINT604
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT604
#endif /* OSEE_RH850_CORE3_604_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_605_ISR_CAT))
  .word _osEE_rh850_core3_ei605       #-- Core3 EIINT605
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT605
#endif /* OSEE_RH850_CORE3_605_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_606_ISR_CAT))
  .word _osEE_rh850_core3_ei606       #-- Core3 EIINT606
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT606
#endif /* OSEE_RH850_CORE3_606_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_607_ISR_CAT))
  .word _osEE_rh850_core3_ei607       #-- Core3 EIINT607
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT607
#endif /* OSEE_RH850_CORE3_607_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_608_ISR_CAT))
  .word _osEE_rh850_core3_ei608       #-- Core3 EIINT608
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT608
#endif /* OSEE_RH850_CORE3_608_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_609_ISR_CAT))
  .word _osEE_rh850_core3_ei609       #-- Core3 EIINT609
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT609
#endif /* OSEE_RH850_CORE3_609_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_610_ISR_CAT))
  .word _osEE_rh850_core3_ei610       #-- Core3 EIINT610
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT610
#endif /* OSEE_RH850_CORE3_610_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_611_ISR_CAT))
  .word _osEE_rh850_core3_ei611       #-- Core3 EIINT611
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT611
#endif /* OSEE_RH850_CORE3_611_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_612_ISR_CAT))
  .word _osEE_rh850_core3_ei612       #-- Core3 EIINT612
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT612
#endif /* OSEE_RH850_CORE3_612_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_613_ISR_CAT))
  .word _osEE_rh850_core3_ei613       #-- Core3 EIINT613
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT613
#endif /* OSEE_RH850_CORE3_613_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_614_ISR_CAT))
  .word _osEE_rh850_core3_ei614       #-- Core3 EIINT614
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT614
#endif /* OSEE_RH850_CORE3_614_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_615_ISR_CAT))
  .word _osEE_rh850_core3_ei615       #-- Core3 EIINT615
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT615
#endif /* OSEE_RH850_CORE3_615_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_616_ISR_CAT))
  .word _osEE_rh850_core3_ei616       #-- Core3 EIINT616
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT616
#endif /* OSEE_RH850_CORE3_616_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_617_ISR_CAT))
  .word _osEE_rh850_core3_ei617       #-- Core3 EIINT617
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT617
#endif /* OSEE_RH850_CORE3_617_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_618_ISR_CAT))
  .word _osEE_rh850_core3_ei618       #-- Core3 EIINT618
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT618
#endif /* OSEE_RH850_CORE3_618_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_619_ISR_CAT))
  .word _osEE_rh850_core3_ei619       #-- Core3 EIINT619
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT619
#endif /* OSEE_RH850_CORE3_619_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_620_ISR_CAT))
  .word _osEE_rh850_core3_ei620       #-- Core3 EIINT620
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT620
#endif /* OSEE_RH850_CORE3_620_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_621_ISR_CAT))
  .word _osEE_rh850_core3_ei621       #-- Core3 EIINT621
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT621
#endif /* OSEE_RH850_CORE3_621_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_622_ISR_CAT))
  .word _osEE_rh850_core3_ei622       #-- Core3 EIINT622
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT622
#endif /* OSEE_RH850_CORE3_622_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_623_ISR_CAT))
  .word _osEE_rh850_core3_ei623       #-- Core3 EIINT623
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT623
#endif /* OSEE_RH850_CORE3_623_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_624_ISR_CAT))
  .word _osEE_rh850_core3_ei624       #-- Core3 EIINT624
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT624
#endif /* OSEE_RH850_CORE3_624_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_625_ISR_CAT))
  .word _osEE_rh850_core3_ei625       #-- Core3 EIINT625
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT625
#endif /* OSEE_RH850_CORE3_625_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_626_ISR_CAT))
  .word _osEE_rh850_core3_ei626       #-- Core3 EIINT626
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT626
#endif /* OSEE_RH850_CORE3_626_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_627_ISR_CAT))
  .word _osEE_rh850_core3_ei627       #-- Core3 EIINT627
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT627
#endif /* OSEE_RH850_CORE3_627_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_628_ISR_CAT))
  .word _osEE_rh850_core3_ei628       #-- Core3 EIINT628
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT628
#endif /* OSEE_RH850_CORE3_628_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_629_ISR_CAT))
  .word _osEE_rh850_core3_ei629       #-- Core3 EIINT629
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT629
#endif /* OSEE_RH850_CORE3_629_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_630_ISR_CAT))
  .word _osEE_rh850_core3_ei630       #-- Core3 EIINT630
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT630
#endif /* OSEE_RH850_CORE3_630_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_631_ISR_CAT))
  .word _osEE_rh850_core3_ei631       #-- Core3 EIINT631
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT631
#endif /* OSEE_RH850_CORE3_631_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_632_ISR_CAT))
  .word _osEE_rh850_core3_ei632       #-- Core3 EIINT632
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT632
#endif /* OSEE_RH850_CORE3_632_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_633_ISR_CAT))
  .word _osEE_rh850_core3_ei633       #-- Core3 EIINT633
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT633
#endif /* OSEE_RH850_CORE3_633_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_634_ISR_CAT))
  .word _osEE_rh850_core3_ei634       #-- Core3 EIINT634
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT634
#endif /* OSEE_RH850_CORE3_634_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_635_ISR_CAT))
  .word _osEE_rh850_core3_ei635       #-- Core3 EIINT635
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT635
#endif /* OSEE_RH850_CORE3_635_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_636_ISR_CAT))
  .word _osEE_rh850_core3_ei636       #-- Core3 EIINT636
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT636
#endif /* OSEE_RH850_CORE3_636_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_637_ISR_CAT))
  .word _osEE_rh850_core3_ei637       #-- Core3 EIINT637
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT637
#endif /* OSEE_RH850_CORE3_637_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_638_ISR_CAT))
  .word _osEE_rh850_core3_ei638       #-- Core3 EIINT638
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT638
#endif /* OSEE_RH850_CORE3_638_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_639_ISR_CAT))
  .word _osEE_rh850_core3_ei639       #-- Core3 EIINT639
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT639
#endif /* OSEE_RH850_CORE3_639_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_640_ISR_CAT))
  .word _osEE_rh850_core3_ei640       #-- Core3 EIINT640
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT640
#endif /* OSEE_RH850_CORE3_640_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_641_ISR_CAT))
  .word _osEE_rh850_core3_ei641       #-- Core3 EIINT641
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT641
#endif /* OSEE_RH850_CORE3_641_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_642_ISR_CAT))
  .word _osEE_rh850_core3_ei642       #-- Core3 EIINT642
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT642
#endif /* OSEE_RH850_CORE3_642_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_643_ISR_CAT))
  .word _osEE_rh850_core3_ei643       #-- Core3 EIINT643
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT643
#endif /* OSEE_RH850_CORE3_643_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_644_ISR_CAT))
  .word _osEE_rh850_core3_ei644       #-- Core3 EIINT644
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT644
#endif /* OSEE_RH850_CORE3_644_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_645_ISR_CAT))
  .word _osEE_rh850_core3_ei645       #-- Core3 EIINT645
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT645
#endif /* OSEE_RH850_CORE3_645_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_646_ISR_CAT))
  .word _osEE_rh850_core3_ei646       #-- Core3 EIINT646
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT646
#endif /* OSEE_RH850_CORE3_646_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_647_ISR_CAT))
  .word _osEE_rh850_core3_ei647       #-- Core3 EIINT647
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT647
#endif /* OSEE_RH850_CORE3_647_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_648_ISR_CAT))
  .word _osEE_rh850_core3_ei648       #-- Core3 EIINT648
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT648
#endif /* OSEE_RH850_CORE3_648_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_649_ISR_CAT))
  .word _osEE_rh850_core3_ei649       #-- Core3 EIINT649
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT649
#endif /* OSEE_RH850_CORE3_649_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_650_ISR_CAT))
  .word _osEE_rh850_core3_ei650       #-- Core3 EIINT650
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT650
#endif /* OSEE_RH850_CORE3_650_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_651_ISR_CAT))
  .word _osEE_rh850_core3_ei651       #-- Core3 EIINT651
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT651
#endif /* OSEE_RH850_CORE3_651_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_652_ISR_CAT))
  .word _osEE_rh850_core3_ei652       #-- Core3 EIINT652
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT652
#endif /* OSEE_RH850_CORE3_652_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_653_ISR_CAT))
  .word _osEE_rh850_core3_ei653       #-- Core3 EIINT653
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT653
#endif /* OSEE_RH850_CORE3_653_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_654_ISR_CAT))
  .word _osEE_rh850_core3_ei654       #-- Core3 EIINT654
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT654
#endif /* OSEE_RH850_CORE3_654_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_655_ISR_CAT))
  .word _osEE_rh850_core3_ei655       #-- Core3 EIINT655
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT655
#endif /* OSEE_RH850_CORE3_655_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_656_ISR_CAT))
  .word _osEE_rh850_core3_ei656       #-- Core3 EIINT656
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT656
#endif /* OSEE_RH850_CORE3_656_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_657_ISR_CAT))
  .word _osEE_rh850_core3_ei657       #-- Core3 EIINT657
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT657
#endif /* OSEE_RH850_CORE3_657_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_658_ISR_CAT))
  .word _osEE_rh850_core3_ei658       #-- Core3 EIINT658
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT658
#endif /* OSEE_RH850_CORE3_658_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_659_ISR_CAT))
  .word _osEE_rh850_core3_ei659       #-- Core3 EIINT659
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT659
#endif /* OSEE_RH850_CORE3_659_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_660_ISR_CAT))
  .word _osEE_rh850_core3_ei660       #-- Core3 EIINT660
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT660
#endif /* OSEE_RH850_CORE3_660_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_661_ISR_CAT))
  .word _osEE_rh850_core3_ei661       #-- Core3 EIINT661
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT661
#endif /* OSEE_RH850_CORE3_661_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_662_ISR_CAT))
  .word _osEE_rh850_core3_ei662       #-- Core3 EIINT662
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT662
#endif /* OSEE_RH850_CORE3_662_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_663_ISR_CAT))
  .word _osEE_rh850_core3_ei663       #-- Core3 EIINT663
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT663
#endif /* OSEE_RH850_CORE3_663_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_664_ISR_CAT))
  .word _osEE_rh850_core3_ei664       #-- Core3 EIINT664
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT664
#endif /* OSEE_RH850_CORE3_664_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_665_ISR_CAT))
  .word _osEE_rh850_core3_ei665       #-- Core3 EIINT665
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT665
#endif /* OSEE_RH850_CORE3_665_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_666_ISR_CAT))
  .word _osEE_rh850_core3_ei666       #-- Core3 EIINT666
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT666
#endif /* OSEE_RH850_CORE3_666_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_667_ISR_CAT))
  .word _osEE_rh850_core3_ei667       #-- Core3 EIINT667
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT667
#endif /* OSEE_RH850_CORE3_667_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_668_ISR_CAT))
  .word _osEE_rh850_core3_ei668       #-- Core3 EIINT668
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT668
#endif /* OSEE_RH850_CORE3_668_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_669_ISR_CAT))
  .word _osEE_rh850_core3_ei669       #-- Core3 EIINT669
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT669
#endif /* OSEE_RH850_CORE3_669_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_670_ISR_CAT))
  .word _osEE_rh850_core3_ei670       #-- Core3 EIINT670
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT670
#endif /* OSEE_RH850_CORE3_670_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_671_ISR_CAT))
  .word _osEE_rh850_core3_ei671       #-- Core3 EIINT671
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT671
#endif /* OSEE_RH850_CORE3_671_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_672_ISR_CAT))
  .word _osEE_rh850_core3_ei672       #-- Core3 EIINT672
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT672
#endif /* OSEE_RH850_CORE3_672_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_673_ISR_CAT))
  .word _osEE_rh850_core3_ei673       #-- Core3 EIINT673
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT673
#endif /* OSEE_RH850_CORE3_673_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_674_ISR_CAT))
  .word _osEE_rh850_core3_ei674       #-- Core3 EIINT674
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT674
#endif /* OSEE_RH850_CORE3_674_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_675_ISR_CAT))
  .word _osEE_rh850_core3_ei675       #-- Core3 EIINT675
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT675
#endif /* OSEE_RH850_CORE3_675_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_676_ISR_CAT))
  .word _osEE_rh850_core3_ei676       #-- Core3 EIINT676
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT676
#endif /* OSEE_RH850_CORE3_676_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_677_ISR_CAT))
  .word _osEE_rh850_core3_ei677       #-- Core3 EIINT677
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT677
#endif /* OSEE_RH850_CORE3_677_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_678_ISR_CAT))
  .word _osEE_rh850_core3_ei678       #-- Core3 EIINT678
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT678
#endif /* OSEE_RH850_CORE3_678_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_679_ISR_CAT))
  .word _osEE_rh850_core3_ei679       #-- Core3 EIINT679
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT679
#endif /* OSEE_RH850_CORE3_679_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_680_ISR_CAT))
  .word _osEE_rh850_core3_ei680       #-- Core3 EIINT680
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT680
#endif /* OSEE_RH850_CORE3_680_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_681_ISR_CAT))
  .word _osEE_rh850_core3_ei681       #-- Core3 EIINT681
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT681
#endif /* OSEE_RH850_CORE3_681_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_682_ISR_CAT))
  .word _osEE_rh850_core3_ei682       #-- Core3 EIINT682
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT682
#endif /* OSEE_RH850_CORE3_682_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_683_ISR_CAT))
  .word _osEE_rh850_core3_ei683       #-- Core3 EIINT683
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT683
#endif /* OSEE_RH850_CORE3_683_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_684_ISR_CAT))
  .word _osEE_rh850_core3_ei684       #-- Core3 EIINT684
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT684
#endif /* OSEE_RH850_CORE3_684_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_685_ISR_CAT))
  .word _osEE_rh850_core3_ei685       #-- Core3 EIINT685
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT685
#endif /* OSEE_RH850_CORE3_685_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_686_ISR_CAT))
  .word _osEE_rh850_core3_ei686       #-- Core3 EIINT686
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT686
#endif /* OSEE_RH850_CORE3_686_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_687_ISR_CAT))
  .word _osEE_rh850_core3_ei687       #-- Core3 EIINT687
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT687
#endif /* OSEE_RH850_CORE3_687_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_688_ISR_CAT))
  .word _osEE_rh850_core3_ei688       #-- Core3 EIINT688
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT688
#endif /* OSEE_RH850_CORE3_688_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_689_ISR_CAT))
  .word _osEE_rh850_core3_ei689       #-- Core3 EIINT689
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT689
#endif /* OSEE_RH850_CORE3_689_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_690_ISR_CAT))
  .word _osEE_rh850_core3_ei690       #-- Core3 EIINT690
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT690
#endif /* OSEE_RH850_CORE3_690_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_691_ISR_CAT))
  .word _osEE_rh850_core3_ei691       #-- Core3 EIINT691
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT691
#endif /* OSEE_RH850_CORE3_691_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_692_ISR_CAT))
  .word _osEE_rh850_core3_ei692       #-- Core3 EIINT692
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT692
#endif /* OSEE_RH850_CORE3_692_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_693_ISR_CAT))
  .word _osEE_rh850_core3_ei693       #-- Core3 EIINT693
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT693
#endif /* OSEE_RH850_CORE3_693_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_694_ISR_CAT))
  .word _osEE_rh850_core3_ei694       #-- Core3 EIINT694
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT694
#endif /* OSEE_RH850_CORE3_694_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_695_ISR_CAT))
  .word _osEE_rh850_core3_ei695       #-- Core3 EIINT695
#else
  .word _osEE_rh850_call_IsrEiUnused  #-- Core3 EIINT695
#endif /* OSEE_RH850_CORE3_695_ISR_CAT */
#.size _g_g4mh_RefTbl, .-_g_g4mh_RefTbl
.size _osEE_rh850_core3_reftabl_ei, .-_osEE_rh850_core3_reftabl_ei

  #----------------------------------------------------------------------------
  #-- Description : ISR Refence Table Entries (The select the right wrapper)
  #----------------------------------------------------------------------------

  .section ".text"

  .import _osEE_rh850_handle_ipir
_osEE_rh850_core3_ei0:
  #-- Save ISR Context
  pushsp  r1-r19
  osEE_rh850_save_isr_ctx_m

  #-- Call _osEE_rh850_handle_ipir
  jarl  _osEE_rh850_handle_ipir, r31

  #-- Restore ISR Context
  osEE_rh850_restore_isr_ctx_m

  #-- Synchronize pipeline needed for Software Interrupt Processing Flow
  syncp

  #-- return from EI exception
  eiret

  .size  _osEE_rh850_core3_ei0, .-_osEE_rh850_core3_ei0
#if (defined(OSEE_RH850_CORE3_1_ISR_CAT))
#if (OSEE_RH850_CORE3_1_ISR_CAT == 1)
_osEE_rh850_core3_ei1:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_1_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei1, .-_osEE_rh850_core3_ei1
#else
_osEE_rh850_core3_ei1:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_1_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei1, .-_osEE_rh850_core3_ei1
#endif
#endif /* OSEE_RH850_CORE3_1_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_2_ISR_CAT))
#if (OSEE_RH850_CORE3_2_ISR_CAT == 1)
_osEE_rh850_core3_ei2:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_2_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei2, .-_osEE_rh850_core3_ei2
#else
_osEE_rh850_core3_ei2:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_2_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei2, .-_osEE_rh850_core3_ei2
#endif
#endif /* OSEE_RH850_CORE3_2_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_3_ISR_CAT))
#if (OSEE_RH850_CORE3_3_ISR_CAT == 1)
_osEE_rh850_core3_ei3:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_3_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei3, .-_osEE_rh850_core3_ei3
#else
_osEE_rh850_core3_ei3:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_3_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei3, .-_osEE_rh850_core3_ei3
#endif
#endif /* OSEE_RH850_CORE3_3_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_4_ISR_CAT))
#if (OSEE_RH850_CORE3_4_ISR_CAT == 1)
_osEE_rh850_core3_ei4:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_4_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei4, .-_osEE_rh850_core3_ei4
#else
_osEE_rh850_core3_ei4:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_4_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei4, .-_osEE_rh850_core3_ei4
#endif
#endif /* OSEE_RH850_CORE3_4_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_5_ISR_CAT))
#if (OSEE_RH850_CORE3_5_ISR_CAT == 1)
_osEE_rh850_core3_ei5:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_5_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei5, .-_osEE_rh850_core3_ei5
#else
_osEE_rh850_core3_ei5:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_5_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei5, .-_osEE_rh850_core3_ei5
#endif
#endif /* OSEE_RH850_CORE3_5_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_6_ISR_CAT))
#if (OSEE_RH850_CORE3_6_ISR_CAT == 1)
_osEE_rh850_core3_ei6:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_6_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei6, .-_osEE_rh850_core3_ei6
#else
_osEE_rh850_core3_ei6:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_6_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei6, .-_osEE_rh850_core3_ei6
#endif
#endif /* OSEE_RH850_CORE3_6_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_7_ISR_CAT))
#if (OSEE_RH850_CORE3_7_ISR_CAT == 1)
_osEE_rh850_core3_ei7:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_7_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei7, .-_osEE_rh850_core3_ei7
#else
_osEE_rh850_core3_ei7:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_7_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei7, .-_osEE_rh850_core3_ei7
#endif
#endif /* OSEE_RH850_CORE3_7_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_8_ISR_CAT))
#if (OSEE_RH850_CORE3_8_ISR_CAT == 1)
_osEE_rh850_core3_ei8:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_8_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei8, .-_osEE_rh850_core3_ei8
#else
_osEE_rh850_core3_ei8:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_8_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei8, .-_osEE_rh850_core3_ei8
#endif
#endif /* OSEE_RH850_CORE3_8_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_9_ISR_CAT))
#if (OSEE_RH850_CORE3_9_ISR_CAT == 1)
_osEE_rh850_core3_ei9:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_9_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei9, .-_osEE_rh850_core3_ei9
#else
_osEE_rh850_core3_ei9:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_9_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei9, .-_osEE_rh850_core3_ei9
#endif
#endif /* OSEE_RH850_CORE3_9_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_10_ISR_CAT))
#if (OSEE_RH850_CORE3_10_ISR_CAT == 1)
_osEE_rh850_core3_ei10:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_10_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei10, .-_osEE_rh850_core3_ei10
#else
_osEE_rh850_core3_ei10:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_10_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei10, .-_osEE_rh850_core3_ei10
#endif
#endif /* OSEE_RH850_CORE3_10_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_11_ISR_CAT))
#if (OSEE_RH850_CORE3_11_ISR_CAT == 1)
_osEE_rh850_core3_ei11:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_11_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei11, .-_osEE_rh850_core3_ei11
#else
_osEE_rh850_core3_ei11:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_11_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei11, .-_osEE_rh850_core3_ei11
#endif
#endif /* OSEE_RH850_CORE3_11_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_12_ISR_CAT))
#if (OSEE_RH850_CORE3_12_ISR_CAT == 1)
_osEE_rh850_core3_ei12:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_12_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei12, .-_osEE_rh850_core3_ei12
#else
_osEE_rh850_core3_ei12:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_12_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei12, .-_osEE_rh850_core3_ei12
#endif
#endif /* OSEE_RH850_CORE3_12_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_13_ISR_CAT))
#if (OSEE_RH850_CORE3_13_ISR_CAT == 1)
_osEE_rh850_core3_ei13:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_13_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei13, .-_osEE_rh850_core3_ei13
#else
_osEE_rh850_core3_ei13:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_13_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei13, .-_osEE_rh850_core3_ei13
#endif
#endif /* OSEE_RH850_CORE3_13_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_14_ISR_CAT))
#if (OSEE_RH850_CORE3_14_ISR_CAT == 1)
_osEE_rh850_core3_ei14:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_14_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei14, .-_osEE_rh850_core3_ei14
#else
_osEE_rh850_core3_ei14:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_14_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei14, .-_osEE_rh850_core3_ei14
#endif
#endif /* OSEE_RH850_CORE3_14_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_15_ISR_CAT))
#if (OSEE_RH850_CORE3_15_ISR_CAT == 1)
_osEE_rh850_core3_ei15:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_15_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei15, .-_osEE_rh850_core3_ei15
#else
_osEE_rh850_core3_ei15:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_15_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei15, .-_osEE_rh850_core3_ei15
#endif
#endif /* OSEE_RH850_CORE3_15_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_16_ISR_CAT))
#if (OSEE_RH850_CORE3_16_ISR_CAT == 1)
_osEE_rh850_core3_ei16:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_16_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei16, .-_osEE_rh850_core3_ei16
#else
_osEE_rh850_core3_ei16:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_16_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei16, .-_osEE_rh850_core3_ei16
#endif
#endif /* OSEE_RH850_CORE3_16_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_17_ISR_CAT))
#if (OSEE_RH850_CORE3_17_ISR_CAT == 1)
_osEE_rh850_core3_ei17:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_17_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei17, .-_osEE_rh850_core3_ei17
#else
_osEE_rh850_core3_ei17:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_17_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei17, .-_osEE_rh850_core3_ei17
#endif
#endif /* OSEE_RH850_CORE3_17_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_18_ISR_CAT))
#if (OSEE_RH850_CORE3_18_ISR_CAT == 1)
_osEE_rh850_core3_ei18:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_18_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei18, .-_osEE_rh850_core3_ei18
#else
_osEE_rh850_core3_ei18:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_18_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei18, .-_osEE_rh850_core3_ei18
#endif
#endif /* OSEE_RH850_CORE3_18_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_19_ISR_CAT))
#if (OSEE_RH850_CORE3_19_ISR_CAT == 1)
_osEE_rh850_core3_ei19:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_19_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei19, .-_osEE_rh850_core3_ei19
#else
_osEE_rh850_core3_ei19:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_19_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei19, .-_osEE_rh850_core3_ei19
#endif
#endif /* OSEE_RH850_CORE3_19_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_20_ISR_CAT))
#if (OSEE_RH850_CORE3_20_ISR_CAT == 1)
_osEE_rh850_core3_ei20:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_20_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei20, .-_osEE_rh850_core3_ei20
#else
_osEE_rh850_core3_ei20:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_20_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei20, .-_osEE_rh850_core3_ei20
#endif
#endif /* OSEE_RH850_CORE3_20_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_21_ISR_CAT))
#if (OSEE_RH850_CORE3_21_ISR_CAT == 1)
_osEE_rh850_core3_ei21:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_21_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei21, .-_osEE_rh850_core3_ei21
#else
_osEE_rh850_core3_ei21:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_21_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei21, .-_osEE_rh850_core3_ei21
#endif
#endif /* OSEE_RH850_CORE3_21_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_22_ISR_CAT))
#if (OSEE_RH850_CORE3_22_ISR_CAT == 1)
_osEE_rh850_core3_ei22:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_22_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei22, .-_osEE_rh850_core3_ei22
#else
_osEE_rh850_core3_ei22:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_22_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei22, .-_osEE_rh850_core3_ei22
#endif
#endif /* OSEE_RH850_CORE3_22_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_23_ISR_CAT))
#if (OSEE_RH850_CORE3_23_ISR_CAT == 1)
_osEE_rh850_core3_ei23:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_23_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei23, .-_osEE_rh850_core3_ei23
#else
_osEE_rh850_core3_ei23:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_23_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei23, .-_osEE_rh850_core3_ei23
#endif
#endif /* OSEE_RH850_CORE3_23_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_24_ISR_CAT))
#if (OSEE_RH850_CORE3_24_ISR_CAT == 1)
_osEE_rh850_core3_ei24:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_24_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei24, .-_osEE_rh850_core3_ei24
#else
_osEE_rh850_core3_ei24:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_24_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei24, .-_osEE_rh850_core3_ei24
#endif
#endif /* OSEE_RH850_CORE3_24_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_25_ISR_CAT))
#if (OSEE_RH850_CORE3_25_ISR_CAT == 1)
_osEE_rh850_core3_ei25:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_25_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei25, .-_osEE_rh850_core3_ei25
#else
_osEE_rh850_core3_ei25:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_25_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei25, .-_osEE_rh850_core3_ei25
#endif
#endif /* OSEE_RH850_CORE3_25_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_26_ISR_CAT))
#if (OSEE_RH850_CORE3_26_ISR_CAT == 1)
_osEE_rh850_core3_ei26:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_26_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei26, .-_osEE_rh850_core3_ei26
#else
_osEE_rh850_core3_ei26:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_26_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei26, .-_osEE_rh850_core3_ei26
#endif
#endif /* OSEE_RH850_CORE3_26_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_27_ISR_CAT))
#if (OSEE_RH850_CORE3_27_ISR_CAT == 1)
_osEE_rh850_core3_ei27:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_27_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei27, .-_osEE_rh850_core3_ei27
#else
_osEE_rh850_core3_ei27:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_27_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei27, .-_osEE_rh850_core3_ei27
#endif
#endif /* OSEE_RH850_CORE3_27_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_28_ISR_CAT))
#if (OSEE_RH850_CORE3_28_ISR_CAT == 1)
_osEE_rh850_core3_ei28:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_28_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei28, .-_osEE_rh850_core3_ei28
#else
_osEE_rh850_core3_ei28:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_28_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei28, .-_osEE_rh850_core3_ei28
#endif
#endif /* OSEE_RH850_CORE3_28_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_29_ISR_CAT))
#if (OSEE_RH850_CORE3_29_ISR_CAT == 1)
_osEE_rh850_core3_ei29:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_29_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei29, .-_osEE_rh850_core3_ei29
#else
_osEE_rh850_core3_ei29:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_29_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei29, .-_osEE_rh850_core3_ei29
#endif
#endif /* OSEE_RH850_CORE3_29_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_30_ISR_CAT))
#if (OSEE_RH850_CORE3_30_ISR_CAT == 1)
_osEE_rh850_core3_ei30:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_30_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei30, .-_osEE_rh850_core3_ei30
#else
_osEE_rh850_core3_ei30:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_30_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei30, .-_osEE_rh850_core3_ei30
#endif
#endif /* OSEE_RH850_CORE3_30_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_31_ISR_CAT))
#if (OSEE_RH850_CORE3_31_ISR_CAT == 1)
_osEE_rh850_core3_ei31:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_31_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei31, .-_osEE_rh850_core3_ei31
#else
_osEE_rh850_core3_ei31:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_31_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei31, .-_osEE_rh850_core3_ei31
#endif
#endif /* OSEE_RH850_CORE3_31_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_32_ISR_CAT))
#if (OSEE_RH850_CORE3_32_ISR_CAT == 1)
_osEE_rh850_core3_ei32:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_32_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei32, .-_osEE_rh850_core3_ei32
#else
_osEE_rh850_core3_ei32:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_32_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei32, .-_osEE_rh850_core3_ei32
#endif
#endif /* OSEE_RH850_CORE3_32_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_33_ISR_CAT))
#if (OSEE_RH850_CORE3_33_ISR_CAT == 1)
_osEE_rh850_core3_ei33:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_33_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei33, .-_osEE_rh850_core3_ei33
#else
_osEE_rh850_core3_ei33:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_33_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei33, .-_osEE_rh850_core3_ei33
#endif
#endif /* OSEE_RH850_CORE3_33_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_34_ISR_CAT))
#if (OSEE_RH850_CORE3_34_ISR_CAT == 1)
_osEE_rh850_core3_ei34:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_34_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei34, .-_osEE_rh850_core3_ei34
#else
_osEE_rh850_core3_ei34:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_34_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei34, .-_osEE_rh850_core3_ei34
#endif
#endif /* OSEE_RH850_CORE3_34_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_35_ISR_CAT))
#if (OSEE_RH850_CORE3_35_ISR_CAT == 1)
_osEE_rh850_core3_ei35:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_35_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei35, .-_osEE_rh850_core3_ei35
#else
_osEE_rh850_core3_ei35:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_35_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei35, .-_osEE_rh850_core3_ei35
#endif
#endif /* OSEE_RH850_CORE3_35_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_36_ISR_CAT))
#if (OSEE_RH850_CORE3_36_ISR_CAT == 1)
_osEE_rh850_core3_ei36:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_36_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei36, .-_osEE_rh850_core3_ei36
#else
_osEE_rh850_core3_ei36:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_36_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei36, .-_osEE_rh850_core3_ei36
#endif
#endif /* OSEE_RH850_CORE3_36_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_37_ISR_CAT))
#if (OSEE_RH850_CORE3_37_ISR_CAT == 1)
_osEE_rh850_core3_ei37:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_37_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei37, .-_osEE_rh850_core3_ei37
#else
_osEE_rh850_core3_ei37:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_37_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei37, .-_osEE_rh850_core3_ei37
#endif
#endif /* OSEE_RH850_CORE3_37_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_38_ISR_CAT))
#if (OSEE_RH850_CORE3_38_ISR_CAT == 1)
_osEE_rh850_core3_ei38:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_38_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei38, .-_osEE_rh850_core3_ei38
#else
_osEE_rh850_core3_ei38:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_38_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei38, .-_osEE_rh850_core3_ei38
#endif
#endif /* OSEE_RH850_CORE3_38_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_39_ISR_CAT))
#if (OSEE_RH850_CORE3_39_ISR_CAT == 1)
_osEE_rh850_core3_ei39:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_39_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei39, .-_osEE_rh850_core3_ei39
#else
_osEE_rh850_core3_ei39:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_39_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei39, .-_osEE_rh850_core3_ei39
#endif
#endif /* OSEE_RH850_CORE3_39_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_40_ISR_CAT))
#if (OSEE_RH850_CORE3_40_ISR_CAT == 1)
_osEE_rh850_core3_ei40:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_40_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei40, .-_osEE_rh850_core3_ei40
#else
_osEE_rh850_core3_ei40:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_40_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei40, .-_osEE_rh850_core3_ei40
#endif
#endif /* OSEE_RH850_CORE3_40_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_41_ISR_CAT))
#if (OSEE_RH850_CORE3_41_ISR_CAT == 1)
_osEE_rh850_core3_ei41:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_41_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei41, .-_osEE_rh850_core3_ei41
#else
_osEE_rh850_core3_ei41:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_41_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei41, .-_osEE_rh850_core3_ei41
#endif
#endif /* OSEE_RH850_CORE3_41_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_42_ISR_CAT))
#if (OSEE_RH850_CORE3_42_ISR_CAT == 1)
_osEE_rh850_core3_ei42:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_42_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei42, .-_osEE_rh850_core3_ei42
#else
_osEE_rh850_core3_ei42:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_42_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei42, .-_osEE_rh850_core3_ei42
#endif
#endif /* OSEE_RH850_CORE3_42_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_43_ISR_CAT))
#if (OSEE_RH850_CORE3_43_ISR_CAT == 1)
_osEE_rh850_core3_ei43:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_43_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei43, .-_osEE_rh850_core3_ei43
#else
_osEE_rh850_core3_ei43:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_43_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei43, .-_osEE_rh850_core3_ei43
#endif
#endif /* OSEE_RH850_CORE3_43_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_44_ISR_CAT))
#if (OSEE_RH850_CORE3_44_ISR_CAT == 1)
_osEE_rh850_core3_ei44:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_44_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei44, .-_osEE_rh850_core3_ei44
#else
_osEE_rh850_core3_ei44:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_44_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei44, .-_osEE_rh850_core3_ei44
#endif
#endif /* OSEE_RH850_CORE3_44_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_45_ISR_CAT))
#if (OSEE_RH850_CORE3_45_ISR_CAT == 1)
_osEE_rh850_core3_ei45:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_45_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei45, .-_osEE_rh850_core3_ei45
#else
_osEE_rh850_core3_ei45:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_45_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei45, .-_osEE_rh850_core3_ei45
#endif
#endif /* OSEE_RH850_CORE3_45_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_46_ISR_CAT))
#if (OSEE_RH850_CORE3_46_ISR_CAT == 1)
_osEE_rh850_core3_ei46:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_46_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei46, .-_osEE_rh850_core3_ei46
#else
_osEE_rh850_core3_ei46:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_46_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei46, .-_osEE_rh850_core3_ei46
#endif
#endif /* OSEE_RH850_CORE3_46_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_47_ISR_CAT))
#if (OSEE_RH850_CORE3_47_ISR_CAT == 1)
_osEE_rh850_core3_ei47:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_47_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei47, .-_osEE_rh850_core3_ei47
#else
_osEE_rh850_core3_ei47:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_47_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei47, .-_osEE_rh850_core3_ei47
#endif
#endif /* OSEE_RH850_CORE3_47_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_48_ISR_CAT))
#if (OSEE_RH850_CORE3_48_ISR_CAT == 1)
_osEE_rh850_core3_ei48:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_48_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei48, .-_osEE_rh850_core3_ei48
#else
_osEE_rh850_core3_ei48:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_48_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei48, .-_osEE_rh850_core3_ei48
#endif
#endif /* OSEE_RH850_CORE3_48_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_49_ISR_CAT))
#if (OSEE_RH850_CORE3_49_ISR_CAT == 1)
_osEE_rh850_core3_ei49:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_49_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei49, .-_osEE_rh850_core3_ei49
#else
_osEE_rh850_core3_ei49:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_49_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei49, .-_osEE_rh850_core3_ei49
#endif
#endif /* OSEE_RH850_CORE3_49_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_50_ISR_CAT))
#if (OSEE_RH850_CORE3_50_ISR_CAT == 1)
_osEE_rh850_core3_ei50:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_50_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei50, .-_osEE_rh850_core3_ei50
#else
_osEE_rh850_core3_ei50:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_50_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei50, .-_osEE_rh850_core3_ei50
#endif
#endif /* OSEE_RH850_CORE3_50_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_51_ISR_CAT))
#if (OSEE_RH850_CORE3_51_ISR_CAT == 1)
_osEE_rh850_core3_ei51:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_51_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei51, .-_osEE_rh850_core3_ei51
#else
_osEE_rh850_core3_ei51:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_51_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei51, .-_osEE_rh850_core3_ei51
#endif
#endif /* OSEE_RH850_CORE3_51_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_52_ISR_CAT))
#if (OSEE_RH850_CORE3_52_ISR_CAT == 1)
_osEE_rh850_core3_ei52:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_52_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei52, .-_osEE_rh850_core3_ei52
#else
_osEE_rh850_core3_ei52:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_52_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei52, .-_osEE_rh850_core3_ei52
#endif
#endif /* OSEE_RH850_CORE3_52_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_53_ISR_CAT))
#if (OSEE_RH850_CORE3_53_ISR_CAT == 1)
_osEE_rh850_core3_ei53:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_53_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei53, .-_osEE_rh850_core3_ei53
#else
_osEE_rh850_core3_ei53:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_53_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei53, .-_osEE_rh850_core3_ei53
#endif
#endif /* OSEE_RH850_CORE3_53_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_54_ISR_CAT))
#if (OSEE_RH850_CORE3_54_ISR_CAT == 1)
_osEE_rh850_core3_ei54:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_54_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei54, .-_osEE_rh850_core3_ei54
#else
_osEE_rh850_core3_ei54:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_54_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei54, .-_osEE_rh850_core3_ei54
#endif
#endif /* OSEE_RH850_CORE3_54_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_55_ISR_CAT))
#if (OSEE_RH850_CORE3_55_ISR_CAT == 1)
_osEE_rh850_core3_ei55:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_55_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei55, .-_osEE_rh850_core3_ei55
#else
_osEE_rh850_core3_ei55:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_55_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei55, .-_osEE_rh850_core3_ei55
#endif
#endif /* OSEE_RH850_CORE3_55_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_56_ISR_CAT))
#if (OSEE_RH850_CORE3_56_ISR_CAT == 1)
_osEE_rh850_core3_ei56:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_56_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei56, .-_osEE_rh850_core3_ei56
#else
_osEE_rh850_core3_ei56:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_56_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei56, .-_osEE_rh850_core3_ei56
#endif
#endif /* OSEE_RH850_CORE3_56_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_57_ISR_CAT))
#if (OSEE_RH850_CORE3_57_ISR_CAT == 1)
_osEE_rh850_core3_ei57:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_57_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei57, .-_osEE_rh850_core3_ei57
#else
_osEE_rh850_core3_ei57:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_57_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei57, .-_osEE_rh850_core3_ei57
#endif
#endif /* OSEE_RH850_CORE3_57_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_58_ISR_CAT))
#if (OSEE_RH850_CORE3_58_ISR_CAT == 1)
_osEE_rh850_core3_ei58:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_58_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei58, .-_osEE_rh850_core3_ei58
#else
_osEE_rh850_core3_ei58:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_58_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei58, .-_osEE_rh850_core3_ei58
#endif
#endif /* OSEE_RH850_CORE3_58_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_59_ISR_CAT))
#if (OSEE_RH850_CORE3_59_ISR_CAT == 1)
_osEE_rh850_core3_ei59:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_59_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei59, .-_osEE_rh850_core3_ei59
#else
_osEE_rh850_core3_ei59:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_59_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei59, .-_osEE_rh850_core3_ei59
#endif
#endif /* OSEE_RH850_CORE3_59_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_60_ISR_CAT))
#if (OSEE_RH850_CORE3_60_ISR_CAT == 1)
_osEE_rh850_core3_ei60:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_60_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei60, .-_osEE_rh850_core3_ei60
#else
_osEE_rh850_core3_ei60:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_60_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei60, .-_osEE_rh850_core3_ei60
#endif
#endif /* OSEE_RH850_CORE3_60_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_61_ISR_CAT))
#if (OSEE_RH850_CORE3_61_ISR_CAT == 1)
_osEE_rh850_core3_ei61:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_61_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei61, .-_osEE_rh850_core3_ei61
#else
_osEE_rh850_core3_ei61:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_61_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei61, .-_osEE_rh850_core3_ei61
#endif
#endif /* OSEE_RH850_CORE3_61_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_62_ISR_CAT))
#if (OSEE_RH850_CORE3_62_ISR_CAT == 1)
_osEE_rh850_core3_ei62:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_62_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei62, .-_osEE_rh850_core3_ei62
#else
_osEE_rh850_core3_ei62:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_62_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei62, .-_osEE_rh850_core3_ei62
#endif
#endif /* OSEE_RH850_CORE3_62_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_63_ISR_CAT))
#if (OSEE_RH850_CORE3_63_ISR_CAT == 1)
_osEE_rh850_core3_ei63:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_63_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei63, .-_osEE_rh850_core3_ei63
#else
_osEE_rh850_core3_ei63:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_63_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei63, .-_osEE_rh850_core3_ei63
#endif
#endif /* OSEE_RH850_CORE3_63_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_64_ISR_CAT))
#if (OSEE_RH850_CORE3_64_ISR_CAT == 1)
_osEE_rh850_core3_ei64:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_64_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei64, .-_osEE_rh850_core3_ei64
#else
_osEE_rh850_core3_ei64:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_64_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei64, .-_osEE_rh850_core3_ei64
#endif
#endif /* OSEE_RH850_CORE3_64_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_65_ISR_CAT))
#if (OSEE_RH850_CORE3_65_ISR_CAT == 1)
_osEE_rh850_core3_ei65:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_65_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei65, .-_osEE_rh850_core3_ei65
#else
_osEE_rh850_core3_ei65:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_65_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei65, .-_osEE_rh850_core3_ei65
#endif
#endif /* OSEE_RH850_CORE3_65_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_66_ISR_CAT))
#if (OSEE_RH850_CORE3_66_ISR_CAT == 1)
_osEE_rh850_core3_ei66:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_66_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei66, .-_osEE_rh850_core3_ei66
#else
_osEE_rh850_core3_ei66:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_66_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei66, .-_osEE_rh850_core3_ei66
#endif
#endif /* OSEE_RH850_CORE3_66_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_67_ISR_CAT))
#if (OSEE_RH850_CORE3_67_ISR_CAT == 1)
_osEE_rh850_core3_ei67:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_67_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei67, .-_osEE_rh850_core3_ei67
#else
_osEE_rh850_core3_ei67:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_67_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei67, .-_osEE_rh850_core3_ei67
#endif
#endif /* OSEE_RH850_CORE3_67_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_68_ISR_CAT))
#if (OSEE_RH850_CORE3_68_ISR_CAT == 1)
_osEE_rh850_core3_ei68:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_68_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei68, .-_osEE_rh850_core3_ei68
#else
_osEE_rh850_core3_ei68:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_68_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei68, .-_osEE_rh850_core3_ei68
#endif
#endif /* OSEE_RH850_CORE3_68_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_69_ISR_CAT))
#if (OSEE_RH850_CORE3_69_ISR_CAT == 1)
_osEE_rh850_core3_ei69:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_69_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei69, .-_osEE_rh850_core3_ei69
#else
_osEE_rh850_core3_ei69:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_69_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei69, .-_osEE_rh850_core3_ei69
#endif
#endif /* OSEE_RH850_CORE3_69_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_70_ISR_CAT))
#if (OSEE_RH850_CORE3_70_ISR_CAT == 1)
_osEE_rh850_core3_ei70:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_70_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei70, .-_osEE_rh850_core3_ei70
#else
_osEE_rh850_core3_ei70:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_70_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei70, .-_osEE_rh850_core3_ei70
#endif
#endif /* OSEE_RH850_CORE3_70_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_71_ISR_CAT))
#if (OSEE_RH850_CORE3_71_ISR_CAT == 1)
_osEE_rh850_core3_ei71:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_71_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei71, .-_osEE_rh850_core3_ei71
#else
_osEE_rh850_core3_ei71:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_71_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei71, .-_osEE_rh850_core3_ei71
#endif
#endif /* OSEE_RH850_CORE3_71_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_72_ISR_CAT))
#if (OSEE_RH850_CORE3_72_ISR_CAT == 1)
_osEE_rh850_core3_ei72:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_72_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei72, .-_osEE_rh850_core3_ei72
#else
_osEE_rh850_core3_ei72:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_72_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei72, .-_osEE_rh850_core3_ei72
#endif
#endif /* OSEE_RH850_CORE3_72_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_73_ISR_CAT))
#if (OSEE_RH850_CORE3_73_ISR_CAT == 1)
_osEE_rh850_core3_ei73:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_73_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei73, .-_osEE_rh850_core3_ei73
#else
_osEE_rh850_core3_ei73:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_73_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei73, .-_osEE_rh850_core3_ei73
#endif
#endif /* OSEE_RH850_CORE3_73_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_74_ISR_CAT))
#if (OSEE_RH850_CORE3_74_ISR_CAT == 1)
_osEE_rh850_core3_ei74:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_74_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei74, .-_osEE_rh850_core3_ei74
#else
_osEE_rh850_core3_ei74:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_74_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei74, .-_osEE_rh850_core3_ei74
#endif
#endif /* OSEE_RH850_CORE3_74_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_75_ISR_CAT))
#if (OSEE_RH850_CORE3_75_ISR_CAT == 1)
_osEE_rh850_core3_ei75:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_75_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei75, .-_osEE_rh850_core3_ei75
#else
_osEE_rh850_core3_ei75:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_75_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei75, .-_osEE_rh850_core3_ei75
#endif
#endif /* OSEE_RH850_CORE3_75_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_76_ISR_CAT))
#if (OSEE_RH850_CORE3_76_ISR_CAT == 1)
_osEE_rh850_core3_ei76:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_76_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei76, .-_osEE_rh850_core3_ei76
#else
_osEE_rh850_core3_ei76:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_76_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei76, .-_osEE_rh850_core3_ei76
#endif
#endif /* OSEE_RH850_CORE3_76_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_77_ISR_CAT))
#if (OSEE_RH850_CORE3_77_ISR_CAT == 1)
_osEE_rh850_core3_ei77:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_77_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei77, .-_osEE_rh850_core3_ei77
#else
_osEE_rh850_core3_ei77:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_77_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei77, .-_osEE_rh850_core3_ei77
#endif
#endif /* OSEE_RH850_CORE3_77_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_78_ISR_CAT))
#if (OSEE_RH850_CORE3_78_ISR_CAT == 1)
_osEE_rh850_core3_ei78:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_78_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei78, .-_osEE_rh850_core3_ei78
#else
_osEE_rh850_core3_ei78:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_78_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei78, .-_osEE_rh850_core3_ei78
#endif
#endif /* OSEE_RH850_CORE3_78_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_79_ISR_CAT))
#if (OSEE_RH850_CORE3_79_ISR_CAT == 1)
_osEE_rh850_core3_ei79:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_79_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei79, .-_osEE_rh850_core3_ei79
#else
_osEE_rh850_core3_ei79:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_79_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei79, .-_osEE_rh850_core3_ei79
#endif
#endif /* OSEE_RH850_CORE3_79_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_80_ISR_CAT))
#if (OSEE_RH850_CORE3_80_ISR_CAT == 1)
_osEE_rh850_core3_ei80:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_80_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei80, .-_osEE_rh850_core3_ei80
#else
_osEE_rh850_core3_ei80:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_80_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei80, .-_osEE_rh850_core3_ei80
#endif
#endif /* OSEE_RH850_CORE3_80_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_81_ISR_CAT))
#if (OSEE_RH850_CORE3_81_ISR_CAT == 1)
_osEE_rh850_core3_ei81:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_81_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei81, .-_osEE_rh850_core3_ei81
#else
_osEE_rh850_core3_ei81:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_81_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei81, .-_osEE_rh850_core3_ei81
#endif
#endif /* OSEE_RH850_CORE3_81_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_82_ISR_CAT))
#if (OSEE_RH850_CORE3_82_ISR_CAT == 1)
_osEE_rh850_core3_ei82:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_82_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei82, .-_osEE_rh850_core3_ei82
#else
_osEE_rh850_core3_ei82:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_82_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei82, .-_osEE_rh850_core3_ei82
#endif
#endif /* OSEE_RH850_CORE3_82_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_83_ISR_CAT))
#if (OSEE_RH850_CORE3_83_ISR_CAT == 1)
_osEE_rh850_core3_ei83:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_83_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei83, .-_osEE_rh850_core3_ei83
#else
_osEE_rh850_core3_ei83:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_83_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei83, .-_osEE_rh850_core3_ei83
#endif
#endif /* OSEE_RH850_CORE3_83_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_84_ISR_CAT))
#if (OSEE_RH850_CORE3_84_ISR_CAT == 1)
_osEE_rh850_core3_ei84:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_84_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei84, .-_osEE_rh850_core3_ei84
#else
_osEE_rh850_core3_ei84:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_84_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei84, .-_osEE_rh850_core3_ei84
#endif
#endif /* OSEE_RH850_CORE3_84_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_85_ISR_CAT))
#if (OSEE_RH850_CORE3_85_ISR_CAT == 1)
_osEE_rh850_core3_ei85:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_85_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei85, .-_osEE_rh850_core3_ei85
#else
_osEE_rh850_core3_ei85:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_85_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei85, .-_osEE_rh850_core3_ei85
#endif
#endif /* OSEE_RH850_CORE3_85_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_86_ISR_CAT))
#if (OSEE_RH850_CORE3_86_ISR_CAT == 1)
_osEE_rh850_core3_ei86:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_86_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei86, .-_osEE_rh850_core3_ei86
#else
_osEE_rh850_core3_ei86:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_86_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei86, .-_osEE_rh850_core3_ei86
#endif
#endif /* OSEE_RH850_CORE3_86_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_87_ISR_CAT))
#if (OSEE_RH850_CORE3_87_ISR_CAT == 1)
_osEE_rh850_core3_ei87:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_87_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei87, .-_osEE_rh850_core3_ei87
#else
_osEE_rh850_core3_ei87:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_87_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei87, .-_osEE_rh850_core3_ei87
#endif
#endif /* OSEE_RH850_CORE3_87_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_88_ISR_CAT))
#if (OSEE_RH850_CORE3_88_ISR_CAT == 1)
_osEE_rh850_core3_ei88:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_88_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei88, .-_osEE_rh850_core3_ei88
#else
_osEE_rh850_core3_ei88:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_88_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei88, .-_osEE_rh850_core3_ei88
#endif
#endif /* OSEE_RH850_CORE3_88_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_89_ISR_CAT))
#if (OSEE_RH850_CORE3_89_ISR_CAT == 1)
_osEE_rh850_core3_ei89:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_89_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei89, .-_osEE_rh850_core3_ei89
#else
_osEE_rh850_core3_ei89:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_89_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei89, .-_osEE_rh850_core3_ei89
#endif
#endif /* OSEE_RH850_CORE3_89_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_90_ISR_CAT))
#if (OSEE_RH850_CORE3_90_ISR_CAT == 1)
_osEE_rh850_core3_ei90:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_90_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei90, .-_osEE_rh850_core3_ei90
#else
_osEE_rh850_core3_ei90:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_90_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei90, .-_osEE_rh850_core3_ei90
#endif
#endif /* OSEE_RH850_CORE3_90_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_91_ISR_CAT))
#if (OSEE_RH850_CORE3_91_ISR_CAT == 1)
_osEE_rh850_core3_ei91:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_91_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei91, .-_osEE_rh850_core3_ei91
#else
_osEE_rh850_core3_ei91:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_91_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei91, .-_osEE_rh850_core3_ei91
#endif
#endif /* OSEE_RH850_CORE3_91_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_92_ISR_CAT))
#if (OSEE_RH850_CORE3_92_ISR_CAT == 1)
_osEE_rh850_core3_ei92:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_92_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei92, .-_osEE_rh850_core3_ei92
#else
_osEE_rh850_core3_ei92:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_92_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei92, .-_osEE_rh850_core3_ei92
#endif
#endif /* OSEE_RH850_CORE3_92_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_93_ISR_CAT))
#if (OSEE_RH850_CORE3_93_ISR_CAT == 1)
_osEE_rh850_core3_ei93:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_93_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei93, .-_osEE_rh850_core3_ei93
#else
_osEE_rh850_core3_ei93:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_93_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei93, .-_osEE_rh850_core3_ei93
#endif
#endif /* OSEE_RH850_CORE3_93_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_94_ISR_CAT))
#if (OSEE_RH850_CORE3_94_ISR_CAT == 1)
_osEE_rh850_core3_ei94:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_94_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei94, .-_osEE_rh850_core3_ei94
#else
_osEE_rh850_core3_ei94:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_94_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei94, .-_osEE_rh850_core3_ei94
#endif
#endif /* OSEE_RH850_CORE3_94_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_95_ISR_CAT))
#if (OSEE_RH850_CORE3_95_ISR_CAT == 1)
_osEE_rh850_core3_ei95:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_95_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei95, .-_osEE_rh850_core3_ei95
#else
_osEE_rh850_core3_ei95:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_95_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei95, .-_osEE_rh850_core3_ei95
#endif
#endif /* OSEE_RH850_CORE3_95_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_96_ISR_CAT))
#if (OSEE_RH850_CORE3_96_ISR_CAT == 1)
_osEE_rh850_core3_ei96:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_96_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei96, .-_osEE_rh850_core3_ei96
#else
_osEE_rh850_core3_ei96:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_96_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei96, .-_osEE_rh850_core3_ei96
#endif
#endif /* OSEE_RH850_CORE3_96_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_97_ISR_CAT))
#if (OSEE_RH850_CORE3_97_ISR_CAT == 1)
_osEE_rh850_core3_ei97:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_97_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei97, .-_osEE_rh850_core3_ei97
#else
_osEE_rh850_core3_ei97:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_97_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei97, .-_osEE_rh850_core3_ei97
#endif
#endif /* OSEE_RH850_CORE3_97_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_98_ISR_CAT))
#if (OSEE_RH850_CORE3_98_ISR_CAT == 1)
_osEE_rh850_core3_ei98:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_98_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei98, .-_osEE_rh850_core3_ei98
#else
_osEE_rh850_core3_ei98:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_98_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei98, .-_osEE_rh850_core3_ei98
#endif
#endif /* OSEE_RH850_CORE3_98_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_99_ISR_CAT))
#if (OSEE_RH850_CORE3_99_ISR_CAT == 1)
_osEE_rh850_core3_ei99:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_99_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei99, .-_osEE_rh850_core3_ei99
#else
_osEE_rh850_core3_ei99:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_99_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei99, .-_osEE_rh850_core3_ei99
#endif
#endif /* OSEE_RH850_CORE3_99_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_100_ISR_CAT))
#if (OSEE_RH850_CORE3_100_ISR_CAT == 1)
_osEE_rh850_core3_ei100:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_100_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei100, .-_osEE_rh850_core3_ei100
#else
_osEE_rh850_core3_ei100:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_100_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei100, .-_osEE_rh850_core3_ei100
#endif
#endif /* OSEE_RH850_CORE3_100_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_101_ISR_CAT))
#if (OSEE_RH850_CORE3_101_ISR_CAT == 1)
_osEE_rh850_core3_ei101:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_101_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei101, .-_osEE_rh850_core3_ei101
#else
_osEE_rh850_core3_ei101:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_101_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei101, .-_osEE_rh850_core3_ei101
#endif
#endif /* OSEE_RH850_CORE3_101_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_102_ISR_CAT))
#if (OSEE_RH850_CORE3_102_ISR_CAT == 1)
_osEE_rh850_core3_ei102:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_102_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei102, .-_osEE_rh850_core3_ei102
#else
_osEE_rh850_core3_ei102:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_102_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei102, .-_osEE_rh850_core3_ei102
#endif
#endif /* OSEE_RH850_CORE3_102_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_103_ISR_CAT))
#if (OSEE_RH850_CORE3_103_ISR_CAT == 1)
_osEE_rh850_core3_ei103:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_103_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei103, .-_osEE_rh850_core3_ei103
#else
_osEE_rh850_core3_ei103:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_103_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei103, .-_osEE_rh850_core3_ei103
#endif
#endif /* OSEE_RH850_CORE3_103_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_104_ISR_CAT))
#if (OSEE_RH850_CORE3_104_ISR_CAT == 1)
_osEE_rh850_core3_ei104:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_104_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei104, .-_osEE_rh850_core3_ei104
#else
_osEE_rh850_core3_ei104:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_104_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei104, .-_osEE_rh850_core3_ei104
#endif
#endif /* OSEE_RH850_CORE3_104_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_105_ISR_CAT))
#if (OSEE_RH850_CORE3_105_ISR_CAT == 1)
_osEE_rh850_core3_ei105:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_105_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei105, .-_osEE_rh850_core3_ei105
#else
_osEE_rh850_core3_ei105:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_105_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei105, .-_osEE_rh850_core3_ei105
#endif
#endif /* OSEE_RH850_CORE3_105_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_106_ISR_CAT))
#if (OSEE_RH850_CORE3_106_ISR_CAT == 1)
_osEE_rh850_core3_ei106:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_106_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei106, .-_osEE_rh850_core3_ei106
#else
_osEE_rh850_core3_ei106:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_106_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei106, .-_osEE_rh850_core3_ei106
#endif
#endif /* OSEE_RH850_CORE3_106_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_107_ISR_CAT))
#if (OSEE_RH850_CORE3_107_ISR_CAT == 1)
_osEE_rh850_core3_ei107:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_107_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei107, .-_osEE_rh850_core3_ei107
#else
_osEE_rh850_core3_ei107:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_107_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei107, .-_osEE_rh850_core3_ei107
#endif
#endif /* OSEE_RH850_CORE3_107_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_108_ISR_CAT))
#if (OSEE_RH850_CORE3_108_ISR_CAT == 1)
_osEE_rh850_core3_ei108:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_108_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei108, .-_osEE_rh850_core3_ei108
#else
_osEE_rh850_core3_ei108:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_108_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei108, .-_osEE_rh850_core3_ei108
#endif
#endif /* OSEE_RH850_CORE3_108_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_109_ISR_CAT))
#if (OSEE_RH850_CORE3_109_ISR_CAT == 1)
_osEE_rh850_core3_ei109:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_109_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei109, .-_osEE_rh850_core3_ei109
#else
_osEE_rh850_core3_ei109:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_109_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei109, .-_osEE_rh850_core3_ei109
#endif
#endif /* OSEE_RH850_CORE3_109_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_110_ISR_CAT))
#if (OSEE_RH850_CORE3_110_ISR_CAT == 1)
_osEE_rh850_core3_ei110:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_110_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei110, .-_osEE_rh850_core3_ei110
#else
_osEE_rh850_core3_ei110:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_110_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei110, .-_osEE_rh850_core3_ei110
#endif
#endif /* OSEE_RH850_CORE3_110_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_111_ISR_CAT))
#if (OSEE_RH850_CORE3_111_ISR_CAT == 1)
_osEE_rh850_core3_ei111:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_111_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei111, .-_osEE_rh850_core3_ei111
#else
_osEE_rh850_core3_ei111:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_111_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei111, .-_osEE_rh850_core3_ei111
#endif
#endif /* OSEE_RH850_CORE3_111_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_112_ISR_CAT))
#if (OSEE_RH850_CORE3_112_ISR_CAT == 1)
_osEE_rh850_core3_ei112:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_112_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei112, .-_osEE_rh850_core3_ei112
#else
_osEE_rh850_core3_ei112:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_112_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei112, .-_osEE_rh850_core3_ei112
#endif
#endif /* OSEE_RH850_CORE3_112_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_113_ISR_CAT))
#if (OSEE_RH850_CORE3_113_ISR_CAT == 1)
_osEE_rh850_core3_ei113:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_113_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei113, .-_osEE_rh850_core3_ei113
#else
_osEE_rh850_core3_ei113:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_113_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei113, .-_osEE_rh850_core3_ei113
#endif
#endif /* OSEE_RH850_CORE3_113_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_114_ISR_CAT))
#if (OSEE_RH850_CORE3_114_ISR_CAT == 1)
_osEE_rh850_core3_ei114:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_114_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei114, .-_osEE_rh850_core3_ei114
#else
_osEE_rh850_core3_ei114:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_114_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei114, .-_osEE_rh850_core3_ei114
#endif
#endif /* OSEE_RH850_CORE3_114_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_115_ISR_CAT))
#if (OSEE_RH850_CORE3_115_ISR_CAT == 1)
_osEE_rh850_core3_ei115:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_115_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei115, .-_osEE_rh850_core3_ei115
#else
_osEE_rh850_core3_ei115:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_115_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei115, .-_osEE_rh850_core3_ei115
#endif
#endif /* OSEE_RH850_CORE3_115_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_116_ISR_CAT))
#if (OSEE_RH850_CORE3_116_ISR_CAT == 1)
_osEE_rh850_core3_ei116:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_116_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei116, .-_osEE_rh850_core3_ei116
#else
_osEE_rh850_core3_ei116:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_116_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei116, .-_osEE_rh850_core3_ei116
#endif
#endif /* OSEE_RH850_CORE3_116_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_117_ISR_CAT))
#if (OSEE_RH850_CORE3_117_ISR_CAT == 1)
_osEE_rh850_core3_ei117:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_117_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei117, .-_osEE_rh850_core3_ei117
#else
_osEE_rh850_core3_ei117:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_117_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei117, .-_osEE_rh850_core3_ei117
#endif
#endif /* OSEE_RH850_CORE3_117_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_118_ISR_CAT))
#if (OSEE_RH850_CORE3_118_ISR_CAT == 1)
_osEE_rh850_core3_ei118:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_118_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei118, .-_osEE_rh850_core3_ei118
#else
_osEE_rh850_core3_ei118:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_118_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei118, .-_osEE_rh850_core3_ei118
#endif
#endif /* OSEE_RH850_CORE3_118_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_119_ISR_CAT))
#if (OSEE_RH850_CORE3_119_ISR_CAT == 1)
_osEE_rh850_core3_ei119:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_119_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei119, .-_osEE_rh850_core3_ei119
#else
_osEE_rh850_core3_ei119:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_119_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei119, .-_osEE_rh850_core3_ei119
#endif
#endif /* OSEE_RH850_CORE3_119_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_120_ISR_CAT))
#if (OSEE_RH850_CORE3_120_ISR_CAT == 1)
_osEE_rh850_core3_ei120:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_120_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei120, .-_osEE_rh850_core3_ei120
#else
_osEE_rh850_core3_ei120:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_120_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei120, .-_osEE_rh850_core3_ei120
#endif
#endif /* OSEE_RH850_CORE3_120_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_121_ISR_CAT))
#if (OSEE_RH850_CORE3_121_ISR_CAT == 1)
_osEE_rh850_core3_ei121:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_121_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei121, .-_osEE_rh850_core3_ei121
#else
_osEE_rh850_core3_ei121:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_121_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei121, .-_osEE_rh850_core3_ei121
#endif
#endif /* OSEE_RH850_CORE3_121_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_122_ISR_CAT))
#if (OSEE_RH850_CORE3_122_ISR_CAT == 1)
_osEE_rh850_core3_ei122:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_122_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei122, .-_osEE_rh850_core3_ei122
#else
_osEE_rh850_core3_ei122:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_122_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei122, .-_osEE_rh850_core3_ei122
#endif
#endif /* OSEE_RH850_CORE3_122_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_123_ISR_CAT))
#if (OSEE_RH850_CORE3_123_ISR_CAT == 1)
_osEE_rh850_core3_ei123:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_123_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei123, .-_osEE_rh850_core3_ei123
#else
_osEE_rh850_core3_ei123:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_123_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei123, .-_osEE_rh850_core3_ei123
#endif
#endif /* OSEE_RH850_CORE3_123_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_124_ISR_CAT))
#if (OSEE_RH850_CORE3_124_ISR_CAT == 1)
_osEE_rh850_core3_ei124:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_124_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei124, .-_osEE_rh850_core3_ei124
#else
_osEE_rh850_core3_ei124:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_124_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei124, .-_osEE_rh850_core3_ei124
#endif
#endif /* OSEE_RH850_CORE3_124_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_125_ISR_CAT))
#if (OSEE_RH850_CORE3_125_ISR_CAT == 1)
_osEE_rh850_core3_ei125:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_125_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei125, .-_osEE_rh850_core3_ei125
#else
_osEE_rh850_core3_ei125:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_125_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei125, .-_osEE_rh850_core3_ei125
#endif
#endif /* OSEE_RH850_CORE3_125_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_126_ISR_CAT))
#if (OSEE_RH850_CORE3_126_ISR_CAT == 1)
_osEE_rh850_core3_ei126:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_126_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei126, .-_osEE_rh850_core3_ei126
#else
_osEE_rh850_core3_ei126:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_126_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei126, .-_osEE_rh850_core3_ei126
#endif
#endif /* OSEE_RH850_CORE3_126_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_127_ISR_CAT))
#if (OSEE_RH850_CORE3_127_ISR_CAT == 1)
_osEE_rh850_core3_ei127:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_127_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei127, .-_osEE_rh850_core3_ei127
#else
_osEE_rh850_core3_ei127:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_127_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei127, .-_osEE_rh850_core3_ei127
#endif
#endif /* OSEE_RH850_CORE3_127_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_128_ISR_CAT))
#if (OSEE_RH850_CORE3_128_ISR_CAT == 1)
_osEE_rh850_core3_ei128:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_128_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei128, .-_osEE_rh850_core3_ei128
#else
_osEE_rh850_core3_ei128:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_128_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei128, .-_osEE_rh850_core3_ei128
#endif
#endif /* OSEE_RH850_CORE3_128_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_129_ISR_CAT))
#if (OSEE_RH850_CORE3_129_ISR_CAT == 1)
_osEE_rh850_core3_ei129:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_129_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei129, .-_osEE_rh850_core3_ei129
#else
_osEE_rh850_core3_ei129:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_129_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei129, .-_osEE_rh850_core3_ei129
#endif
#endif /* OSEE_RH850_CORE3_129_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_130_ISR_CAT))
#if (OSEE_RH850_CORE3_130_ISR_CAT == 1)
_osEE_rh850_core3_ei130:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_130_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei130, .-_osEE_rh850_core3_ei130
#else
_osEE_rh850_core3_ei130:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_130_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei130, .-_osEE_rh850_core3_ei130
#endif
#endif /* OSEE_RH850_CORE3_130_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_131_ISR_CAT))
#if (OSEE_RH850_CORE3_131_ISR_CAT == 1)
_osEE_rh850_core3_ei131:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_131_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei131, .-_osEE_rh850_core3_ei131
#else
_osEE_rh850_core3_ei131:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_131_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei131, .-_osEE_rh850_core3_ei131
#endif
#endif /* OSEE_RH850_CORE3_131_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_132_ISR_CAT))
#if (OSEE_RH850_CORE3_132_ISR_CAT == 1)
_osEE_rh850_core3_ei132:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_132_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei132, .-_osEE_rh850_core3_ei132
#else
_osEE_rh850_core3_ei132:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_132_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei132, .-_osEE_rh850_core3_ei132
#endif
#endif /* OSEE_RH850_CORE3_132_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_133_ISR_CAT))
#if (OSEE_RH850_CORE3_133_ISR_CAT == 1)
_osEE_rh850_core3_ei133:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_133_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei133, .-_osEE_rh850_core3_ei133
#else
_osEE_rh850_core3_ei133:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_133_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei133, .-_osEE_rh850_core3_ei133
#endif
#endif /* OSEE_RH850_CORE3_133_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_134_ISR_CAT))
#if (OSEE_RH850_CORE3_134_ISR_CAT == 1)
_osEE_rh850_core3_ei134:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_134_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei134, .-_osEE_rh850_core3_ei134
#else
_osEE_rh850_core3_ei134:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_134_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei134, .-_osEE_rh850_core3_ei134
#endif
#endif /* OSEE_RH850_CORE3_134_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_135_ISR_CAT))
#if (OSEE_RH850_CORE3_135_ISR_CAT == 1)
_osEE_rh850_core3_ei135:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_135_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei135, .-_osEE_rh850_core3_ei135
#else
_osEE_rh850_core3_ei135:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_135_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei135, .-_osEE_rh850_core3_ei135
#endif
#endif /* OSEE_RH850_CORE3_135_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_136_ISR_CAT))
#if (OSEE_RH850_CORE3_136_ISR_CAT == 1)
_osEE_rh850_core3_ei136:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_136_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei136, .-_osEE_rh850_core3_ei136
#else
_osEE_rh850_core3_ei136:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_136_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei136, .-_osEE_rh850_core3_ei136
#endif
#endif /* OSEE_RH850_CORE3_136_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_137_ISR_CAT))
#if (OSEE_RH850_CORE3_137_ISR_CAT == 1)
_osEE_rh850_core3_ei137:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_137_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei137, .-_osEE_rh850_core3_ei137
#else
_osEE_rh850_core3_ei137:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_137_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei137, .-_osEE_rh850_core3_ei137
#endif
#endif /* OSEE_RH850_CORE3_137_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_138_ISR_CAT))
#if (OSEE_RH850_CORE3_138_ISR_CAT == 1)
_osEE_rh850_core3_ei138:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_138_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei138, .-_osEE_rh850_core3_ei138
#else
_osEE_rh850_core3_ei138:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_138_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei138, .-_osEE_rh850_core3_ei138
#endif
#endif /* OSEE_RH850_CORE3_138_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_139_ISR_CAT))
#if (OSEE_RH850_CORE3_139_ISR_CAT == 1)
_osEE_rh850_core3_ei139:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_139_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei139, .-_osEE_rh850_core3_ei139
#else
_osEE_rh850_core3_ei139:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_139_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei139, .-_osEE_rh850_core3_ei139
#endif
#endif /* OSEE_RH850_CORE3_139_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_140_ISR_CAT))
#if (OSEE_RH850_CORE3_140_ISR_CAT == 1)
_osEE_rh850_core3_ei140:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_140_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei140, .-_osEE_rh850_core3_ei140
#else
_osEE_rh850_core3_ei140:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_140_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei140, .-_osEE_rh850_core3_ei140
#endif
#endif /* OSEE_RH850_CORE3_140_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_141_ISR_CAT))
#if (OSEE_RH850_CORE3_141_ISR_CAT == 1)
_osEE_rh850_core3_ei141:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_141_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei141, .-_osEE_rh850_core3_ei141
#else
_osEE_rh850_core3_ei141:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_141_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei141, .-_osEE_rh850_core3_ei141
#endif
#endif /* OSEE_RH850_CORE3_141_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_142_ISR_CAT))
#if (OSEE_RH850_CORE3_142_ISR_CAT == 1)
_osEE_rh850_core3_ei142:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_142_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei142, .-_osEE_rh850_core3_ei142
#else
_osEE_rh850_core3_ei142:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_142_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei142, .-_osEE_rh850_core3_ei142
#endif
#endif /* OSEE_RH850_CORE3_142_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_143_ISR_CAT))
#if (OSEE_RH850_CORE3_143_ISR_CAT == 1)
_osEE_rh850_core3_ei143:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_143_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei143, .-_osEE_rh850_core3_ei143
#else
_osEE_rh850_core3_ei143:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_143_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei143, .-_osEE_rh850_core3_ei143
#endif
#endif /* OSEE_RH850_CORE3_143_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_144_ISR_CAT))
#if (OSEE_RH850_CORE3_144_ISR_CAT == 1)
_osEE_rh850_core3_ei144:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_144_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei144, .-_osEE_rh850_core3_ei144
#else
_osEE_rh850_core3_ei144:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_144_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei144, .-_osEE_rh850_core3_ei144
#endif
#endif /* OSEE_RH850_CORE3_144_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_145_ISR_CAT))
#if (OSEE_RH850_CORE3_145_ISR_CAT == 1)
_osEE_rh850_core3_ei145:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_145_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei145, .-_osEE_rh850_core3_ei145
#else
_osEE_rh850_core3_ei145:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_145_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei145, .-_osEE_rh850_core3_ei145
#endif
#endif /* OSEE_RH850_CORE3_145_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_146_ISR_CAT))
#if (OSEE_RH850_CORE3_146_ISR_CAT == 1)
_osEE_rh850_core3_ei146:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_146_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei146, .-_osEE_rh850_core3_ei146
#else
_osEE_rh850_core3_ei146:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_146_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei146, .-_osEE_rh850_core3_ei146
#endif
#endif /* OSEE_RH850_CORE3_146_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_147_ISR_CAT))
#if (OSEE_RH850_CORE3_147_ISR_CAT == 1)
_osEE_rh850_core3_ei147:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_147_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei147, .-_osEE_rh850_core3_ei147
#else
_osEE_rh850_core3_ei147:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_147_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei147, .-_osEE_rh850_core3_ei147
#endif
#endif /* OSEE_RH850_CORE3_147_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_148_ISR_CAT))
#if (OSEE_RH850_CORE3_148_ISR_CAT == 1)
_osEE_rh850_core3_ei148:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_148_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei148, .-_osEE_rh850_core3_ei148
#else
_osEE_rh850_core3_ei148:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_148_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei148, .-_osEE_rh850_core3_ei148
#endif
#endif /* OSEE_RH850_CORE3_148_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_149_ISR_CAT))
#if (OSEE_RH850_CORE3_149_ISR_CAT == 1)
_osEE_rh850_core3_ei149:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_149_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei149, .-_osEE_rh850_core3_ei149
#else
_osEE_rh850_core3_ei149:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_149_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei149, .-_osEE_rh850_core3_ei149
#endif
#endif /* OSEE_RH850_CORE3_149_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_150_ISR_CAT))
#if (OSEE_RH850_CORE3_150_ISR_CAT == 1)
_osEE_rh850_core3_ei150:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_150_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei150, .-_osEE_rh850_core3_ei150
#else
_osEE_rh850_core3_ei150:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_150_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei150, .-_osEE_rh850_core3_ei150
#endif
#endif /* OSEE_RH850_CORE3_150_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_151_ISR_CAT))
#if (OSEE_RH850_CORE3_151_ISR_CAT == 1)
_osEE_rh850_core3_ei151:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_151_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei151, .-_osEE_rh850_core3_ei151
#else
_osEE_rh850_core3_ei151:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_151_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei151, .-_osEE_rh850_core3_ei151
#endif
#endif /* OSEE_RH850_CORE3_151_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_152_ISR_CAT))
#if (OSEE_RH850_CORE3_152_ISR_CAT == 1)
_osEE_rh850_core3_ei152:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_152_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei152, .-_osEE_rh850_core3_ei152
#else
_osEE_rh850_core3_ei152:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_152_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei152, .-_osEE_rh850_core3_ei152
#endif
#endif /* OSEE_RH850_CORE3_152_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_153_ISR_CAT))
#if (OSEE_RH850_CORE3_153_ISR_CAT == 1)
_osEE_rh850_core3_ei153:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_153_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei153, .-_osEE_rh850_core3_ei153
#else
_osEE_rh850_core3_ei153:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_153_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei153, .-_osEE_rh850_core3_ei153
#endif
#endif /* OSEE_RH850_CORE3_153_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_154_ISR_CAT))
#if (OSEE_RH850_CORE3_154_ISR_CAT == 1)
_osEE_rh850_core3_ei154:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_154_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei154, .-_osEE_rh850_core3_ei154
#else
_osEE_rh850_core3_ei154:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_154_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei154, .-_osEE_rh850_core3_ei154
#endif
#endif /* OSEE_RH850_CORE3_154_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_155_ISR_CAT))
#if (OSEE_RH850_CORE3_155_ISR_CAT == 1)
_osEE_rh850_core3_ei155:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_155_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei155, .-_osEE_rh850_core3_ei155
#else
_osEE_rh850_core3_ei155:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_155_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei155, .-_osEE_rh850_core3_ei155
#endif
#endif /* OSEE_RH850_CORE3_155_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_156_ISR_CAT))
#if (OSEE_RH850_CORE3_156_ISR_CAT == 1)
_osEE_rh850_core3_ei156:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_156_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei156, .-_osEE_rh850_core3_ei156
#else
_osEE_rh850_core3_ei156:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_156_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei156, .-_osEE_rh850_core3_ei156
#endif
#endif /* OSEE_RH850_CORE3_156_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_157_ISR_CAT))
#if (OSEE_RH850_CORE3_157_ISR_CAT == 1)
_osEE_rh850_core3_ei157:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_157_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei157, .-_osEE_rh850_core3_ei157
#else
_osEE_rh850_core3_ei157:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_157_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei157, .-_osEE_rh850_core3_ei157
#endif
#endif /* OSEE_RH850_CORE3_157_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_158_ISR_CAT))
#if (OSEE_RH850_CORE3_158_ISR_CAT == 1)
_osEE_rh850_core3_ei158:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_158_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei158, .-_osEE_rh850_core3_ei158
#else
_osEE_rh850_core3_ei158:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_158_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei158, .-_osEE_rh850_core3_ei158
#endif
#endif /* OSEE_RH850_CORE3_158_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_159_ISR_CAT))
#if (OSEE_RH850_CORE3_159_ISR_CAT == 1)
_osEE_rh850_core3_ei159:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_159_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei159, .-_osEE_rh850_core3_ei159
#else
_osEE_rh850_core3_ei159:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_159_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei159, .-_osEE_rh850_core3_ei159
#endif
#endif /* OSEE_RH850_CORE3_159_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_160_ISR_CAT))
#if (OSEE_RH850_CORE3_160_ISR_CAT == 1)
_osEE_rh850_core3_ei160:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_160_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei160, .-_osEE_rh850_core3_ei160
#else
_osEE_rh850_core3_ei160:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_160_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei160, .-_osEE_rh850_core3_ei160
#endif
#endif /* OSEE_RH850_CORE3_160_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_161_ISR_CAT))
#if (OSEE_RH850_CORE3_161_ISR_CAT == 1)
_osEE_rh850_core3_ei161:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_161_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei161, .-_osEE_rh850_core3_ei161
#else
_osEE_rh850_core3_ei161:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_161_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei161, .-_osEE_rh850_core3_ei161
#endif
#endif /* OSEE_RH850_CORE3_161_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_162_ISR_CAT))
#if (OSEE_RH850_CORE3_162_ISR_CAT == 1)
_osEE_rh850_core3_ei162:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_162_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei162, .-_osEE_rh850_core3_ei162
#else
_osEE_rh850_core3_ei162:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_162_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei162, .-_osEE_rh850_core3_ei162
#endif
#endif /* OSEE_RH850_CORE3_162_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_163_ISR_CAT))
#if (OSEE_RH850_CORE3_163_ISR_CAT == 1)
_osEE_rh850_core3_ei163:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_163_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei163, .-_osEE_rh850_core3_ei163
#else
_osEE_rh850_core3_ei163:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_163_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei163, .-_osEE_rh850_core3_ei163
#endif
#endif /* OSEE_RH850_CORE3_163_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_164_ISR_CAT))
#if (OSEE_RH850_CORE3_164_ISR_CAT == 1)
_osEE_rh850_core3_ei164:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_164_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei164, .-_osEE_rh850_core3_ei164
#else
_osEE_rh850_core3_ei164:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_164_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei164, .-_osEE_rh850_core3_ei164
#endif
#endif /* OSEE_RH850_CORE3_164_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_165_ISR_CAT))
#if (OSEE_RH850_CORE3_165_ISR_CAT == 1)
_osEE_rh850_core3_ei165:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_165_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei165, .-_osEE_rh850_core3_ei165
#else
_osEE_rh850_core3_ei165:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_165_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei165, .-_osEE_rh850_core3_ei165
#endif
#endif /* OSEE_RH850_CORE3_165_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_166_ISR_CAT))
#if (OSEE_RH850_CORE3_166_ISR_CAT == 1)
_osEE_rh850_core3_ei166:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_166_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei166, .-_osEE_rh850_core3_ei166
#else
_osEE_rh850_core3_ei166:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_166_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei166, .-_osEE_rh850_core3_ei166
#endif
#endif /* OSEE_RH850_CORE3_166_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_167_ISR_CAT))
#if (OSEE_RH850_CORE3_167_ISR_CAT == 1)
_osEE_rh850_core3_ei167:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_167_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei167, .-_osEE_rh850_core3_ei167
#else
_osEE_rh850_core3_ei167:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_167_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei167, .-_osEE_rh850_core3_ei167
#endif
#endif /* OSEE_RH850_CORE3_167_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_168_ISR_CAT))
#if (OSEE_RH850_CORE3_168_ISR_CAT == 1)
_osEE_rh850_core3_ei168:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_168_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei168, .-_osEE_rh850_core3_ei168
#else
_osEE_rh850_core3_ei168:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_168_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei168, .-_osEE_rh850_core3_ei168
#endif
#endif /* OSEE_RH850_CORE3_168_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_169_ISR_CAT))
#if (OSEE_RH850_CORE3_169_ISR_CAT == 1)
_osEE_rh850_core3_ei169:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_169_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei169, .-_osEE_rh850_core3_ei169
#else
_osEE_rh850_core3_ei169:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_169_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei169, .-_osEE_rh850_core3_ei169
#endif
#endif /* OSEE_RH850_CORE3_169_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_170_ISR_CAT))
#if (OSEE_RH850_CORE3_170_ISR_CAT == 1)
_osEE_rh850_core3_ei170:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_170_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei170, .-_osEE_rh850_core3_ei170
#else
_osEE_rh850_core3_ei170:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_170_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei170, .-_osEE_rh850_core3_ei170
#endif
#endif /* OSEE_RH850_CORE3_170_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_171_ISR_CAT))
#if (OSEE_RH850_CORE3_171_ISR_CAT == 1)
_osEE_rh850_core3_ei171:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_171_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei171, .-_osEE_rh850_core3_ei171
#else
_osEE_rh850_core3_ei171:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_171_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei171, .-_osEE_rh850_core3_ei171
#endif
#endif /* OSEE_RH850_CORE3_171_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_172_ISR_CAT))
#if (OSEE_RH850_CORE3_172_ISR_CAT == 1)
_osEE_rh850_core3_ei172:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_172_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei172, .-_osEE_rh850_core3_ei172
#else
_osEE_rh850_core3_ei172:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_172_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei172, .-_osEE_rh850_core3_ei172
#endif
#endif /* OSEE_RH850_CORE3_172_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_173_ISR_CAT))
#if (OSEE_RH850_CORE3_173_ISR_CAT == 1)
_osEE_rh850_core3_ei173:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_173_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei173, .-_osEE_rh850_core3_ei173
#else
_osEE_rh850_core3_ei173:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_173_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei173, .-_osEE_rh850_core3_ei173
#endif
#endif /* OSEE_RH850_CORE3_173_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_174_ISR_CAT))
#if (OSEE_RH850_CORE3_174_ISR_CAT == 1)
_osEE_rh850_core3_ei174:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_174_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei174, .-_osEE_rh850_core3_ei174
#else
_osEE_rh850_core3_ei174:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_174_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei174, .-_osEE_rh850_core3_ei174
#endif
#endif /* OSEE_RH850_CORE3_174_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_175_ISR_CAT))
#if (OSEE_RH850_CORE3_175_ISR_CAT == 1)
_osEE_rh850_core3_ei175:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_175_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei175, .-_osEE_rh850_core3_ei175
#else
_osEE_rh850_core3_ei175:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_175_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei175, .-_osEE_rh850_core3_ei175
#endif
#endif /* OSEE_RH850_CORE3_175_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_176_ISR_CAT))
#if (OSEE_RH850_CORE3_176_ISR_CAT == 1)
_osEE_rh850_core3_ei176:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_176_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei176, .-_osEE_rh850_core3_ei176
#else
_osEE_rh850_core3_ei176:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_176_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei176, .-_osEE_rh850_core3_ei176
#endif
#endif /* OSEE_RH850_CORE3_176_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_177_ISR_CAT))
#if (OSEE_RH850_CORE3_177_ISR_CAT == 1)
_osEE_rh850_core3_ei177:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_177_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei177, .-_osEE_rh850_core3_ei177
#else
_osEE_rh850_core3_ei177:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_177_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei177, .-_osEE_rh850_core3_ei177
#endif
#endif /* OSEE_RH850_CORE3_177_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_178_ISR_CAT))
#if (OSEE_RH850_CORE3_178_ISR_CAT == 1)
_osEE_rh850_core3_ei178:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_178_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei178, .-_osEE_rh850_core3_ei178
#else
_osEE_rh850_core3_ei178:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_178_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei178, .-_osEE_rh850_core3_ei178
#endif
#endif /* OSEE_RH850_CORE3_178_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_179_ISR_CAT))
#if (OSEE_RH850_CORE3_179_ISR_CAT == 1)
_osEE_rh850_core3_ei179:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_179_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei179, .-_osEE_rh850_core3_ei179
#else
_osEE_rh850_core3_ei179:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_179_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei179, .-_osEE_rh850_core3_ei179
#endif
#endif /* OSEE_RH850_CORE3_179_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_180_ISR_CAT))
#if (OSEE_RH850_CORE3_180_ISR_CAT == 1)
_osEE_rh850_core3_ei180:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_180_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei180, .-_osEE_rh850_core3_ei180
#else
_osEE_rh850_core3_ei180:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_180_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei180, .-_osEE_rh850_core3_ei180
#endif
#endif /* OSEE_RH850_CORE3_180_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_181_ISR_CAT))
#if (OSEE_RH850_CORE3_181_ISR_CAT == 1)
_osEE_rh850_core3_ei181:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_181_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei181, .-_osEE_rh850_core3_ei181
#else
_osEE_rh850_core3_ei181:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_181_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei181, .-_osEE_rh850_core3_ei181
#endif
#endif /* OSEE_RH850_CORE3_181_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_182_ISR_CAT))
#if (OSEE_RH850_CORE3_182_ISR_CAT == 1)
_osEE_rh850_core3_ei182:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_182_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei182, .-_osEE_rh850_core3_ei182
#else
_osEE_rh850_core3_ei182:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_182_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei182, .-_osEE_rh850_core3_ei182
#endif
#endif /* OSEE_RH850_CORE3_182_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_183_ISR_CAT))
#if (OSEE_RH850_CORE3_183_ISR_CAT == 1)
_osEE_rh850_core3_ei183:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_183_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei183, .-_osEE_rh850_core3_ei183
#else
_osEE_rh850_core3_ei183:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_183_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei183, .-_osEE_rh850_core3_ei183
#endif
#endif /* OSEE_RH850_CORE3_183_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_184_ISR_CAT))
#if (OSEE_RH850_CORE3_184_ISR_CAT == 1)
_osEE_rh850_core3_ei184:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_184_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei184, .-_osEE_rh850_core3_ei184
#else
_osEE_rh850_core3_ei184:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_184_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei184, .-_osEE_rh850_core3_ei184
#endif
#endif /* OSEE_RH850_CORE3_184_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_185_ISR_CAT))
#if (OSEE_RH850_CORE3_185_ISR_CAT == 1)
_osEE_rh850_core3_ei185:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_185_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei185, .-_osEE_rh850_core3_ei185
#else
_osEE_rh850_core3_ei185:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_185_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei185, .-_osEE_rh850_core3_ei185
#endif
#endif /* OSEE_RH850_CORE3_185_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_186_ISR_CAT))
#if (OSEE_RH850_CORE3_186_ISR_CAT == 1)
_osEE_rh850_core3_ei186:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_186_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei186, .-_osEE_rh850_core3_ei186
#else
_osEE_rh850_core3_ei186:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_186_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei186, .-_osEE_rh850_core3_ei186
#endif
#endif /* OSEE_RH850_CORE3_186_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_187_ISR_CAT))
#if (OSEE_RH850_CORE3_187_ISR_CAT == 1)
_osEE_rh850_core3_ei187:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_187_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei187, .-_osEE_rh850_core3_ei187
#else
_osEE_rh850_core3_ei187:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_187_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei187, .-_osEE_rh850_core3_ei187
#endif
#endif /* OSEE_RH850_CORE3_187_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_188_ISR_CAT))
#if (OSEE_RH850_CORE3_188_ISR_CAT == 1)
_osEE_rh850_core3_ei188:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_188_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei188, .-_osEE_rh850_core3_ei188
#else
_osEE_rh850_core3_ei188:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_188_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei188, .-_osEE_rh850_core3_ei188
#endif
#endif /* OSEE_RH850_CORE3_188_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_189_ISR_CAT))
#if (OSEE_RH850_CORE3_189_ISR_CAT == 1)
_osEE_rh850_core3_ei189:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_189_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei189, .-_osEE_rh850_core3_ei189
#else
_osEE_rh850_core3_ei189:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_189_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei189, .-_osEE_rh850_core3_ei189
#endif
#endif /* OSEE_RH850_CORE3_189_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_190_ISR_CAT))
#if (OSEE_RH850_CORE3_190_ISR_CAT == 1)
_osEE_rh850_core3_ei190:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_190_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei190, .-_osEE_rh850_core3_ei190
#else
_osEE_rh850_core3_ei190:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_190_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei190, .-_osEE_rh850_core3_ei190
#endif
#endif /* OSEE_RH850_CORE3_190_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_191_ISR_CAT))
#if (OSEE_RH850_CORE3_191_ISR_CAT == 1)
_osEE_rh850_core3_ei191:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_191_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei191, .-_osEE_rh850_core3_ei191
#else
_osEE_rh850_core3_ei191:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_191_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei191, .-_osEE_rh850_core3_ei191
#endif
#endif /* OSEE_RH850_CORE3_191_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_192_ISR_CAT))
#if (OSEE_RH850_CORE3_192_ISR_CAT == 1)
_osEE_rh850_core3_ei192:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_192_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei192, .-_osEE_rh850_core3_ei192
#else
_osEE_rh850_core3_ei192:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_192_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei192, .-_osEE_rh850_core3_ei192
#endif
#endif /* OSEE_RH850_CORE3_192_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_193_ISR_CAT))
#if (OSEE_RH850_CORE3_193_ISR_CAT == 1)
_osEE_rh850_core3_ei193:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_193_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei193, .-_osEE_rh850_core3_ei193
#else
_osEE_rh850_core3_ei193:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_193_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei193, .-_osEE_rh850_core3_ei193
#endif
#endif /* OSEE_RH850_CORE3_193_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_194_ISR_CAT))
#if (OSEE_RH850_CORE3_194_ISR_CAT == 1)
_osEE_rh850_core3_ei194:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_194_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei194, .-_osEE_rh850_core3_ei194
#else
_osEE_rh850_core3_ei194:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_194_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei194, .-_osEE_rh850_core3_ei194
#endif
#endif /* OSEE_RH850_CORE3_194_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_195_ISR_CAT))
#if (OSEE_RH850_CORE3_195_ISR_CAT == 1)
_osEE_rh850_core3_ei195:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_195_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei195, .-_osEE_rh850_core3_ei195
#else
_osEE_rh850_core3_ei195:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_195_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei195, .-_osEE_rh850_core3_ei195
#endif
#endif /* OSEE_RH850_CORE3_195_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_196_ISR_CAT))
#if (OSEE_RH850_CORE3_196_ISR_CAT == 1)
_osEE_rh850_core3_ei196:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_196_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei196, .-_osEE_rh850_core3_ei196
#else
_osEE_rh850_core3_ei196:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_196_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei196, .-_osEE_rh850_core3_ei196
#endif
#endif /* OSEE_RH850_CORE3_196_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_197_ISR_CAT))
#if (OSEE_RH850_CORE3_197_ISR_CAT == 1)
_osEE_rh850_core3_ei197:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_197_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei197, .-_osEE_rh850_core3_ei197
#else
_osEE_rh850_core3_ei197:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_197_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei197, .-_osEE_rh850_core3_ei197
#endif
#endif /* OSEE_RH850_CORE3_197_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_198_ISR_CAT))
#if (OSEE_RH850_CORE3_198_ISR_CAT == 1)
_osEE_rh850_core3_ei198:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_198_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei198, .-_osEE_rh850_core3_ei198
#else
_osEE_rh850_core3_ei198:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_198_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei198, .-_osEE_rh850_core3_ei198
#endif
#endif /* OSEE_RH850_CORE3_198_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_199_ISR_CAT))
#if (OSEE_RH850_CORE3_199_ISR_CAT == 1)
_osEE_rh850_core3_ei199:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_199_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei199, .-_osEE_rh850_core3_ei199
#else
_osEE_rh850_core3_ei199:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_199_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei199, .-_osEE_rh850_core3_ei199
#endif
#endif /* OSEE_RH850_CORE3_199_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_200_ISR_CAT))
#if (OSEE_RH850_CORE3_200_ISR_CAT == 1)
_osEE_rh850_core3_ei200:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_200_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei200, .-_osEE_rh850_core3_ei200
#else
_osEE_rh850_core3_ei200:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_200_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei200, .-_osEE_rh850_core3_ei200
#endif
#endif /* OSEE_RH850_CORE3_200_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_201_ISR_CAT))
#if (OSEE_RH850_CORE3_201_ISR_CAT == 1)
_osEE_rh850_core3_ei201:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_201_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei201, .-_osEE_rh850_core3_ei201
#else
_osEE_rh850_core3_ei201:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_201_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei201, .-_osEE_rh850_core3_ei201
#endif
#endif /* OSEE_RH850_CORE3_201_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_202_ISR_CAT))
#if (OSEE_RH850_CORE3_202_ISR_CAT == 1)
_osEE_rh850_core3_ei202:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_202_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei202, .-_osEE_rh850_core3_ei202
#else
_osEE_rh850_core3_ei202:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_202_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei202, .-_osEE_rh850_core3_ei202
#endif
#endif /* OSEE_RH850_CORE3_202_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_203_ISR_CAT))
#if (OSEE_RH850_CORE3_203_ISR_CAT == 1)
_osEE_rh850_core3_ei203:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_203_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei203, .-_osEE_rh850_core3_ei203
#else
_osEE_rh850_core3_ei203:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_203_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei203, .-_osEE_rh850_core3_ei203
#endif
#endif /* OSEE_RH850_CORE3_203_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_204_ISR_CAT))
#if (OSEE_RH850_CORE3_204_ISR_CAT == 1)
_osEE_rh850_core3_ei204:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_204_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei204, .-_osEE_rh850_core3_ei204
#else
_osEE_rh850_core3_ei204:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_204_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei204, .-_osEE_rh850_core3_ei204
#endif
#endif /* OSEE_RH850_CORE3_204_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_205_ISR_CAT))
#if (OSEE_RH850_CORE3_205_ISR_CAT == 1)
_osEE_rh850_core3_ei205:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_205_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei205, .-_osEE_rh850_core3_ei205
#else
_osEE_rh850_core3_ei205:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_205_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei205, .-_osEE_rh850_core3_ei205
#endif
#endif /* OSEE_RH850_CORE3_205_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_206_ISR_CAT))
#if (OSEE_RH850_CORE3_206_ISR_CAT == 1)
_osEE_rh850_core3_ei206:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_206_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei206, .-_osEE_rh850_core3_ei206
#else
_osEE_rh850_core3_ei206:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_206_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei206, .-_osEE_rh850_core3_ei206
#endif
#endif /* OSEE_RH850_CORE3_206_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_207_ISR_CAT))
#if (OSEE_RH850_CORE3_207_ISR_CAT == 1)
_osEE_rh850_core3_ei207:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_207_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei207, .-_osEE_rh850_core3_ei207
#else
_osEE_rh850_core3_ei207:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_207_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei207, .-_osEE_rh850_core3_ei207
#endif
#endif /* OSEE_RH850_CORE3_207_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_208_ISR_CAT))
#if (OSEE_RH850_CORE3_208_ISR_CAT == 1)
_osEE_rh850_core3_ei208:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_208_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei208, .-_osEE_rh850_core3_ei208
#else
_osEE_rh850_core3_ei208:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_208_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei208, .-_osEE_rh850_core3_ei208
#endif
#endif /* OSEE_RH850_CORE3_208_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_209_ISR_CAT))
#if (OSEE_RH850_CORE3_209_ISR_CAT == 1)
_osEE_rh850_core3_ei209:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_209_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei209, .-_osEE_rh850_core3_ei209
#else
_osEE_rh850_core3_ei209:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_209_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei209, .-_osEE_rh850_core3_ei209
#endif
#endif /* OSEE_RH850_CORE3_209_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_210_ISR_CAT))
#if (OSEE_RH850_CORE3_210_ISR_CAT == 1)
_osEE_rh850_core3_ei210:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_210_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei210, .-_osEE_rh850_core3_ei210
#else
_osEE_rh850_core3_ei210:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_210_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei210, .-_osEE_rh850_core3_ei210
#endif
#endif /* OSEE_RH850_CORE3_210_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_211_ISR_CAT))
#if (OSEE_RH850_CORE3_211_ISR_CAT == 1)
_osEE_rh850_core3_ei211:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_211_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei211, .-_osEE_rh850_core3_ei211
#else
_osEE_rh850_core3_ei211:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_211_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei211, .-_osEE_rh850_core3_ei211
#endif
#endif /* OSEE_RH850_CORE3_211_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_212_ISR_CAT))
#if (OSEE_RH850_CORE3_212_ISR_CAT == 1)
_osEE_rh850_core3_ei212:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_212_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei212, .-_osEE_rh850_core3_ei212
#else
_osEE_rh850_core3_ei212:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_212_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei212, .-_osEE_rh850_core3_ei212
#endif
#endif /* OSEE_RH850_CORE3_212_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_213_ISR_CAT))
#if (OSEE_RH850_CORE3_213_ISR_CAT == 1)
_osEE_rh850_core3_ei213:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_213_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei213, .-_osEE_rh850_core3_ei213
#else
_osEE_rh850_core3_ei213:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_213_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei213, .-_osEE_rh850_core3_ei213
#endif
#endif /* OSEE_RH850_CORE3_213_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_214_ISR_CAT))
#if (OSEE_RH850_CORE3_214_ISR_CAT == 1)
_osEE_rh850_core3_ei214:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_214_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei214, .-_osEE_rh850_core3_ei214
#else
_osEE_rh850_core3_ei214:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_214_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei214, .-_osEE_rh850_core3_ei214
#endif
#endif /* OSEE_RH850_CORE3_214_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_215_ISR_CAT))
#if (OSEE_RH850_CORE3_215_ISR_CAT == 1)
_osEE_rh850_core3_ei215:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_215_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei215, .-_osEE_rh850_core3_ei215
#else
_osEE_rh850_core3_ei215:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_215_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei215, .-_osEE_rh850_core3_ei215
#endif
#endif /* OSEE_RH850_CORE3_215_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_216_ISR_CAT))
#if (OSEE_RH850_CORE3_216_ISR_CAT == 1)
_osEE_rh850_core3_ei216:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_216_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei216, .-_osEE_rh850_core3_ei216
#else
_osEE_rh850_core3_ei216:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_216_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei216, .-_osEE_rh850_core3_ei216
#endif
#endif /* OSEE_RH850_CORE3_216_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_217_ISR_CAT))
#if (OSEE_RH850_CORE3_217_ISR_CAT == 1)
_osEE_rh850_core3_ei217:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_217_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei217, .-_osEE_rh850_core3_ei217
#else
_osEE_rh850_core3_ei217:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_217_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei217, .-_osEE_rh850_core3_ei217
#endif
#endif /* OSEE_RH850_CORE3_217_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_218_ISR_CAT))
#if (OSEE_RH850_CORE3_218_ISR_CAT == 1)
_osEE_rh850_core3_ei218:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_218_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei218, .-_osEE_rh850_core3_ei218
#else
_osEE_rh850_core3_ei218:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_218_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei218, .-_osEE_rh850_core3_ei218
#endif
#endif /* OSEE_RH850_CORE3_218_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_219_ISR_CAT))
#if (OSEE_RH850_CORE3_219_ISR_CAT == 1)
_osEE_rh850_core3_ei219:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_219_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei219, .-_osEE_rh850_core3_ei219
#else
_osEE_rh850_core3_ei219:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_219_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei219, .-_osEE_rh850_core3_ei219
#endif
#endif /* OSEE_RH850_CORE3_219_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_220_ISR_CAT))
#if (OSEE_RH850_CORE3_220_ISR_CAT == 1)
_osEE_rh850_core3_ei220:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_220_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei220, .-_osEE_rh850_core3_ei220
#else
_osEE_rh850_core3_ei220:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_220_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei220, .-_osEE_rh850_core3_ei220
#endif
#endif /* OSEE_RH850_CORE3_220_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_221_ISR_CAT))
#if (OSEE_RH850_CORE3_221_ISR_CAT == 1)
_osEE_rh850_core3_ei221:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_221_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei221, .-_osEE_rh850_core3_ei221
#else
_osEE_rh850_core3_ei221:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_221_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei221, .-_osEE_rh850_core3_ei221
#endif
#endif /* OSEE_RH850_CORE3_221_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_222_ISR_CAT))
#if (OSEE_RH850_CORE3_222_ISR_CAT == 1)
_osEE_rh850_core3_ei222:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_222_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei222, .-_osEE_rh850_core3_ei222
#else
_osEE_rh850_core3_ei222:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_222_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei222, .-_osEE_rh850_core3_ei222
#endif
#endif /* OSEE_RH850_CORE3_222_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_223_ISR_CAT))
#if (OSEE_RH850_CORE3_223_ISR_CAT == 1)
_osEE_rh850_core3_ei223:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_223_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei223, .-_osEE_rh850_core3_ei223
#else
_osEE_rh850_core3_ei223:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_223_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei223, .-_osEE_rh850_core3_ei223
#endif
#endif /* OSEE_RH850_CORE3_223_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_224_ISR_CAT))
#if (OSEE_RH850_CORE3_224_ISR_CAT == 1)
_osEE_rh850_core3_ei224:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_224_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei224, .-_osEE_rh850_core3_ei224
#else
_osEE_rh850_core3_ei224:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_224_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei224, .-_osEE_rh850_core3_ei224
#endif
#endif /* OSEE_RH850_CORE3_224_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_225_ISR_CAT))
#if (OSEE_RH850_CORE3_225_ISR_CAT == 1)
_osEE_rh850_core3_ei225:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_225_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei225, .-_osEE_rh850_core3_ei225
#else
_osEE_rh850_core3_ei225:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_225_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei225, .-_osEE_rh850_core3_ei225
#endif
#endif /* OSEE_RH850_CORE3_225_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_226_ISR_CAT))
#if (OSEE_RH850_CORE3_226_ISR_CAT == 1)
_osEE_rh850_core3_ei226:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_226_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei226, .-_osEE_rh850_core3_ei226
#else
_osEE_rh850_core3_ei226:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_226_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei226, .-_osEE_rh850_core3_ei226
#endif
#endif /* OSEE_RH850_CORE3_226_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_227_ISR_CAT))
#if (OSEE_RH850_CORE3_227_ISR_CAT == 1)
_osEE_rh850_core3_ei227:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_227_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei227, .-_osEE_rh850_core3_ei227
#else
_osEE_rh850_core3_ei227:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_227_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei227, .-_osEE_rh850_core3_ei227
#endif
#endif /* OSEE_RH850_CORE3_227_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_228_ISR_CAT))
#if (OSEE_RH850_CORE3_228_ISR_CAT == 1)
_osEE_rh850_core3_ei228:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_228_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei228, .-_osEE_rh850_core3_ei228
#else
_osEE_rh850_core3_ei228:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_228_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei228, .-_osEE_rh850_core3_ei228
#endif
#endif /* OSEE_RH850_CORE3_228_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_229_ISR_CAT))
#if (OSEE_RH850_CORE3_229_ISR_CAT == 1)
_osEE_rh850_core3_ei229:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_229_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei229, .-_osEE_rh850_core3_ei229
#else
_osEE_rh850_core3_ei229:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_229_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei229, .-_osEE_rh850_core3_ei229
#endif
#endif /* OSEE_RH850_CORE3_229_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_230_ISR_CAT))
#if (OSEE_RH850_CORE3_230_ISR_CAT == 1)
_osEE_rh850_core3_ei230:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_230_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei230, .-_osEE_rh850_core3_ei230
#else
_osEE_rh850_core3_ei230:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_230_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei230, .-_osEE_rh850_core3_ei230
#endif
#endif /* OSEE_RH850_CORE3_230_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_231_ISR_CAT))
#if (OSEE_RH850_CORE3_231_ISR_CAT == 1)
_osEE_rh850_core3_ei231:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_231_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei231, .-_osEE_rh850_core3_ei231
#else
_osEE_rh850_core3_ei231:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_231_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei231, .-_osEE_rh850_core3_ei231
#endif
#endif /* OSEE_RH850_CORE3_231_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_232_ISR_CAT))
#if (OSEE_RH850_CORE3_232_ISR_CAT == 1)
_osEE_rh850_core3_ei232:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_232_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei232, .-_osEE_rh850_core3_ei232
#else
_osEE_rh850_core3_ei232:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_232_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei232, .-_osEE_rh850_core3_ei232
#endif
#endif /* OSEE_RH850_CORE3_232_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_233_ISR_CAT))
#if (OSEE_RH850_CORE3_233_ISR_CAT == 1)
_osEE_rh850_core3_ei233:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_233_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei233, .-_osEE_rh850_core3_ei233
#else
_osEE_rh850_core3_ei233:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_233_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei233, .-_osEE_rh850_core3_ei233
#endif
#endif /* OSEE_RH850_CORE3_233_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_234_ISR_CAT))
#if (OSEE_RH850_CORE3_234_ISR_CAT == 1)
_osEE_rh850_core3_ei234:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_234_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei234, .-_osEE_rh850_core3_ei234
#else
_osEE_rh850_core3_ei234:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_234_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei234, .-_osEE_rh850_core3_ei234
#endif
#endif /* OSEE_RH850_CORE3_234_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_235_ISR_CAT))
#if (OSEE_RH850_CORE3_235_ISR_CAT == 1)
_osEE_rh850_core3_ei235:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_235_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei235, .-_osEE_rh850_core3_ei235
#else
_osEE_rh850_core3_ei235:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_235_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei235, .-_osEE_rh850_core3_ei235
#endif
#endif /* OSEE_RH850_CORE3_235_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_236_ISR_CAT))
#if (OSEE_RH850_CORE3_236_ISR_CAT == 1)
_osEE_rh850_core3_ei236:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_236_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei236, .-_osEE_rh850_core3_ei236
#else
_osEE_rh850_core3_ei236:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_236_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei236, .-_osEE_rh850_core3_ei236
#endif
#endif /* OSEE_RH850_CORE3_236_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_237_ISR_CAT))
#if (OSEE_RH850_CORE3_237_ISR_CAT == 1)
_osEE_rh850_core3_ei237:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_237_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei237, .-_osEE_rh850_core3_ei237
#else
_osEE_rh850_core3_ei237:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_237_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei237, .-_osEE_rh850_core3_ei237
#endif
#endif /* OSEE_RH850_CORE3_237_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_238_ISR_CAT))
#if (OSEE_RH850_CORE3_238_ISR_CAT == 1)
_osEE_rh850_core3_ei238:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_238_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei238, .-_osEE_rh850_core3_ei238
#else
_osEE_rh850_core3_ei238:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_238_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei238, .-_osEE_rh850_core3_ei238
#endif
#endif /* OSEE_RH850_CORE3_238_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_239_ISR_CAT))
#if (OSEE_RH850_CORE3_239_ISR_CAT == 1)
_osEE_rh850_core3_ei239:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_239_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei239, .-_osEE_rh850_core3_ei239
#else
_osEE_rh850_core3_ei239:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_239_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei239, .-_osEE_rh850_core3_ei239
#endif
#endif /* OSEE_RH850_CORE3_239_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_240_ISR_CAT))
#if (OSEE_RH850_CORE3_240_ISR_CAT == 1)
_osEE_rh850_core3_ei240:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_240_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei240, .-_osEE_rh850_core3_ei240
#else
_osEE_rh850_core3_ei240:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_240_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei240, .-_osEE_rh850_core3_ei240
#endif
#endif /* OSEE_RH850_CORE3_240_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_241_ISR_CAT))
#if (OSEE_RH850_CORE3_241_ISR_CAT == 1)
_osEE_rh850_core3_ei241:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_241_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei241, .-_osEE_rh850_core3_ei241
#else
_osEE_rh850_core3_ei241:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_241_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei241, .-_osEE_rh850_core3_ei241
#endif
#endif /* OSEE_RH850_CORE3_241_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_242_ISR_CAT))
#if (OSEE_RH850_CORE3_242_ISR_CAT == 1)
_osEE_rh850_core3_ei242:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_242_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei242, .-_osEE_rh850_core3_ei242
#else
_osEE_rh850_core3_ei242:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_242_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei242, .-_osEE_rh850_core3_ei242
#endif
#endif /* OSEE_RH850_CORE3_242_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_243_ISR_CAT))
#if (OSEE_RH850_CORE3_243_ISR_CAT == 1)
_osEE_rh850_core3_ei243:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_243_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei243, .-_osEE_rh850_core3_ei243
#else
_osEE_rh850_core3_ei243:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_243_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei243, .-_osEE_rh850_core3_ei243
#endif
#endif /* OSEE_RH850_CORE3_243_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_244_ISR_CAT))
#if (OSEE_RH850_CORE3_244_ISR_CAT == 1)
_osEE_rh850_core3_ei244:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_244_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei244, .-_osEE_rh850_core3_ei244
#else
_osEE_rh850_core3_ei244:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_244_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei244, .-_osEE_rh850_core3_ei244
#endif
#endif /* OSEE_RH850_CORE3_244_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_245_ISR_CAT))
#if (OSEE_RH850_CORE3_245_ISR_CAT == 1)
_osEE_rh850_core3_ei245:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_245_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei245, .-_osEE_rh850_core3_ei245
#else
_osEE_rh850_core3_ei245:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_245_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei245, .-_osEE_rh850_core3_ei245
#endif
#endif /* OSEE_RH850_CORE3_245_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_246_ISR_CAT))
#if (OSEE_RH850_CORE3_246_ISR_CAT == 1)
_osEE_rh850_core3_ei246:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_246_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei246, .-_osEE_rh850_core3_ei246
#else
_osEE_rh850_core3_ei246:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_246_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei246, .-_osEE_rh850_core3_ei246
#endif
#endif /* OSEE_RH850_CORE3_246_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_247_ISR_CAT))
#if (OSEE_RH850_CORE3_247_ISR_CAT == 1)
_osEE_rh850_core3_ei247:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_247_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei247, .-_osEE_rh850_core3_ei247
#else
_osEE_rh850_core3_ei247:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_247_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei247, .-_osEE_rh850_core3_ei247
#endif
#endif /* OSEE_RH850_CORE3_247_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_248_ISR_CAT))
#if (OSEE_RH850_CORE3_248_ISR_CAT == 1)
_osEE_rh850_core3_ei248:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_248_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei248, .-_osEE_rh850_core3_ei248
#else
_osEE_rh850_core3_ei248:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_248_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei248, .-_osEE_rh850_core3_ei248
#endif
#endif /* OSEE_RH850_CORE3_248_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_249_ISR_CAT))
#if (OSEE_RH850_CORE3_249_ISR_CAT == 1)
_osEE_rh850_core3_ei249:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_249_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei249, .-_osEE_rh850_core3_ei249
#else
_osEE_rh850_core3_ei249:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_249_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei249, .-_osEE_rh850_core3_ei249
#endif
#endif /* OSEE_RH850_CORE3_249_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_250_ISR_CAT))
#if (OSEE_RH850_CORE3_250_ISR_CAT == 1)
_osEE_rh850_core3_ei250:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_250_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei250, .-_osEE_rh850_core3_ei250
#else
_osEE_rh850_core3_ei250:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_250_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei250, .-_osEE_rh850_core3_ei250
#endif
#endif /* OSEE_RH850_CORE3_250_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_251_ISR_CAT))
#if (OSEE_RH850_CORE3_251_ISR_CAT == 1)
_osEE_rh850_core3_ei251:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_251_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei251, .-_osEE_rh850_core3_ei251
#else
_osEE_rh850_core3_ei251:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_251_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei251, .-_osEE_rh850_core3_ei251
#endif
#endif /* OSEE_RH850_CORE3_251_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_252_ISR_CAT))
#if (OSEE_RH850_CORE3_252_ISR_CAT == 1)
_osEE_rh850_core3_ei252:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_252_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei252, .-_osEE_rh850_core3_ei252
#else
_osEE_rh850_core3_ei252:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_252_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei252, .-_osEE_rh850_core3_ei252
#endif
#endif /* OSEE_RH850_CORE3_252_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_253_ISR_CAT))
#if (OSEE_RH850_CORE3_253_ISR_CAT == 1)
_osEE_rh850_core3_ei253:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_253_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei253, .-_osEE_rh850_core3_ei253
#else
_osEE_rh850_core3_ei253:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_253_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei253, .-_osEE_rh850_core3_ei253
#endif
#endif /* OSEE_RH850_CORE3_253_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_254_ISR_CAT))
#if (OSEE_RH850_CORE3_254_ISR_CAT == 1)
_osEE_rh850_core3_ei254:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_254_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei254, .-_osEE_rh850_core3_ei254
#else
_osEE_rh850_core3_ei254:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_254_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei254, .-_osEE_rh850_core3_ei254
#endif
#endif /* OSEE_RH850_CORE3_254_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_255_ISR_CAT))
#if (OSEE_RH850_CORE3_255_ISR_CAT == 1)
_osEE_rh850_core3_ei255:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_255_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei255, .-_osEE_rh850_core3_ei255
#else
_osEE_rh850_core3_ei255:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_255_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei255, .-_osEE_rh850_core3_ei255
#endif
#endif /* OSEE_RH850_CORE3_255_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_256_ISR_CAT))
#if (OSEE_RH850_CORE3_256_ISR_CAT == 1)
_osEE_rh850_core3_ei256:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_256_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei256, .-_osEE_rh850_core3_ei256
#else
_osEE_rh850_core3_ei256:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_256_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei256, .-_osEE_rh850_core3_ei256
#endif
#endif /* OSEE_RH850_CORE3_256_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_257_ISR_CAT))
#if (OSEE_RH850_CORE3_257_ISR_CAT == 1)
_osEE_rh850_core3_ei257:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_257_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei257, .-_osEE_rh850_core3_ei257
#else
_osEE_rh850_core3_ei257:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_257_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei257, .-_osEE_rh850_core3_ei257
#endif
#endif /* OSEE_RH850_CORE3_257_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_258_ISR_CAT))
#if (OSEE_RH850_CORE3_258_ISR_CAT == 1)
_osEE_rh850_core3_ei258:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_258_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei258, .-_osEE_rh850_core3_ei258
#else
_osEE_rh850_core3_ei258:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_258_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei258, .-_osEE_rh850_core3_ei258
#endif
#endif /* OSEE_RH850_CORE3_258_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_259_ISR_CAT))
#if (OSEE_RH850_CORE3_259_ISR_CAT == 1)
_osEE_rh850_core3_ei259:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_259_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei259, .-_osEE_rh850_core3_ei259
#else
_osEE_rh850_core3_ei259:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_259_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei259, .-_osEE_rh850_core3_ei259
#endif
#endif /* OSEE_RH850_CORE3_259_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_260_ISR_CAT))
#if (OSEE_RH850_CORE3_260_ISR_CAT == 1)
_osEE_rh850_core3_ei260:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_260_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei260, .-_osEE_rh850_core3_ei260
#else
_osEE_rh850_core3_ei260:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_260_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei260, .-_osEE_rh850_core3_ei260
#endif
#endif /* OSEE_RH850_CORE3_260_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_261_ISR_CAT))
#if (OSEE_RH850_CORE3_261_ISR_CAT == 1)
_osEE_rh850_core3_ei261:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_261_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei261, .-_osEE_rh850_core3_ei261
#else
_osEE_rh850_core3_ei261:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_261_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei261, .-_osEE_rh850_core3_ei261
#endif
#endif /* OSEE_RH850_CORE3_261_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_262_ISR_CAT))
#if (OSEE_RH850_CORE3_262_ISR_CAT == 1)
_osEE_rh850_core3_ei262:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_262_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei262, .-_osEE_rh850_core3_ei262
#else
_osEE_rh850_core3_ei262:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_262_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei262, .-_osEE_rh850_core3_ei262
#endif
#endif /* OSEE_RH850_CORE3_262_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_263_ISR_CAT))
#if (OSEE_RH850_CORE3_263_ISR_CAT == 1)
_osEE_rh850_core3_ei263:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_263_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei263, .-_osEE_rh850_core3_ei263
#else
_osEE_rh850_core3_ei263:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_263_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei263, .-_osEE_rh850_core3_ei263
#endif
#endif /* OSEE_RH850_CORE3_263_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_264_ISR_CAT))
#if (OSEE_RH850_CORE3_264_ISR_CAT == 1)
_osEE_rh850_core3_ei264:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_264_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei264, .-_osEE_rh850_core3_ei264
#else
_osEE_rh850_core3_ei264:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_264_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei264, .-_osEE_rh850_core3_ei264
#endif
#endif /* OSEE_RH850_CORE3_264_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_265_ISR_CAT))
#if (OSEE_RH850_CORE3_265_ISR_CAT == 1)
_osEE_rh850_core3_ei265:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_265_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei265, .-_osEE_rh850_core3_ei265
#else
_osEE_rh850_core3_ei265:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_265_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei265, .-_osEE_rh850_core3_ei265
#endif
#endif /* OSEE_RH850_CORE3_265_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_266_ISR_CAT))
#if (OSEE_RH850_CORE3_266_ISR_CAT == 1)
_osEE_rh850_core3_ei266:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_266_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei266, .-_osEE_rh850_core3_ei266
#else
_osEE_rh850_core3_ei266:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_266_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei266, .-_osEE_rh850_core3_ei266
#endif
#endif /* OSEE_RH850_CORE3_266_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_267_ISR_CAT))
#if (OSEE_RH850_CORE3_267_ISR_CAT == 1)
_osEE_rh850_core3_ei267:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_267_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei267, .-_osEE_rh850_core3_ei267
#else
_osEE_rh850_core3_ei267:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_267_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei267, .-_osEE_rh850_core3_ei267
#endif
#endif /* OSEE_RH850_CORE3_267_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_268_ISR_CAT))
#if (OSEE_RH850_CORE3_268_ISR_CAT == 1)
_osEE_rh850_core3_ei268:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_268_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei268, .-_osEE_rh850_core3_ei268
#else
_osEE_rh850_core3_ei268:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_268_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei268, .-_osEE_rh850_core3_ei268
#endif
#endif /* OSEE_RH850_CORE3_268_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_269_ISR_CAT))
#if (OSEE_RH850_CORE3_269_ISR_CAT == 1)
_osEE_rh850_core3_ei269:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_269_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei269, .-_osEE_rh850_core3_ei269
#else
_osEE_rh850_core3_ei269:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_269_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei269, .-_osEE_rh850_core3_ei269
#endif
#endif /* OSEE_RH850_CORE3_269_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_270_ISR_CAT))
#if (OSEE_RH850_CORE3_270_ISR_CAT == 1)
_osEE_rh850_core3_ei270:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_270_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei270, .-_osEE_rh850_core3_ei270
#else
_osEE_rh850_core3_ei270:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_270_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei270, .-_osEE_rh850_core3_ei270
#endif
#endif /* OSEE_RH850_CORE3_270_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_271_ISR_CAT))
#if (OSEE_RH850_CORE3_271_ISR_CAT == 1)
_osEE_rh850_core3_ei271:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_271_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei271, .-_osEE_rh850_core3_ei271
#else
_osEE_rh850_core3_ei271:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_271_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei271, .-_osEE_rh850_core3_ei271
#endif
#endif /* OSEE_RH850_CORE3_271_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_272_ISR_CAT))
#if (OSEE_RH850_CORE3_272_ISR_CAT == 1)
_osEE_rh850_core3_ei272:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_272_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei272, .-_osEE_rh850_core3_ei272
#else
_osEE_rh850_core3_ei272:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_272_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei272, .-_osEE_rh850_core3_ei272
#endif
#endif /* OSEE_RH850_CORE3_272_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_273_ISR_CAT))
#if (OSEE_RH850_CORE3_273_ISR_CAT == 1)
_osEE_rh850_core3_ei273:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_273_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei273, .-_osEE_rh850_core3_ei273
#else
_osEE_rh850_core3_ei273:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_273_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei273, .-_osEE_rh850_core3_ei273
#endif
#endif /* OSEE_RH850_CORE3_273_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_274_ISR_CAT))
#if (OSEE_RH850_CORE3_274_ISR_CAT == 1)
_osEE_rh850_core3_ei274:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_274_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei274, .-_osEE_rh850_core3_ei274
#else
_osEE_rh850_core3_ei274:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_274_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei274, .-_osEE_rh850_core3_ei274
#endif
#endif /* OSEE_RH850_CORE3_274_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_275_ISR_CAT))
#if (OSEE_RH850_CORE3_275_ISR_CAT == 1)
_osEE_rh850_core3_ei275:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_275_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei275, .-_osEE_rh850_core3_ei275
#else
_osEE_rh850_core3_ei275:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_275_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei275, .-_osEE_rh850_core3_ei275
#endif
#endif /* OSEE_RH850_CORE3_275_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_276_ISR_CAT))
#if (OSEE_RH850_CORE3_276_ISR_CAT == 1)
_osEE_rh850_core3_ei276:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_276_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei276, .-_osEE_rh850_core3_ei276
#else
_osEE_rh850_core3_ei276:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_276_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei276, .-_osEE_rh850_core3_ei276
#endif
#endif /* OSEE_RH850_CORE3_276_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_277_ISR_CAT))
#if (OSEE_RH850_CORE3_277_ISR_CAT == 1)
_osEE_rh850_core3_ei277:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_277_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei277, .-_osEE_rh850_core3_ei277
#else
_osEE_rh850_core3_ei277:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_277_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei277, .-_osEE_rh850_core3_ei277
#endif
#endif /* OSEE_RH850_CORE3_277_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_278_ISR_CAT))
#if (OSEE_RH850_CORE3_278_ISR_CAT == 1)
_osEE_rh850_core3_ei278:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_278_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei278, .-_osEE_rh850_core3_ei278
#else
_osEE_rh850_core3_ei278:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_278_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei278, .-_osEE_rh850_core3_ei278
#endif
#endif /* OSEE_RH850_CORE3_278_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_279_ISR_CAT))
#if (OSEE_RH850_CORE3_279_ISR_CAT == 1)
_osEE_rh850_core3_ei279:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_279_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei279, .-_osEE_rh850_core3_ei279
#else
_osEE_rh850_core3_ei279:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_279_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei279, .-_osEE_rh850_core3_ei279
#endif
#endif /* OSEE_RH850_CORE3_279_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_280_ISR_CAT))
#if (OSEE_RH850_CORE3_280_ISR_CAT == 1)
_osEE_rh850_core3_ei280:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_280_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei280, .-_osEE_rh850_core3_ei280
#else
_osEE_rh850_core3_ei280:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_280_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei280, .-_osEE_rh850_core3_ei280
#endif
#endif /* OSEE_RH850_CORE3_280_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_281_ISR_CAT))
#if (OSEE_RH850_CORE3_281_ISR_CAT == 1)
_osEE_rh850_core3_ei281:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_281_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei281, .-_osEE_rh850_core3_ei281
#else
_osEE_rh850_core3_ei281:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_281_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei281, .-_osEE_rh850_core3_ei281
#endif
#endif /* OSEE_RH850_CORE3_281_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_282_ISR_CAT))
#if (OSEE_RH850_CORE3_282_ISR_CAT == 1)
_osEE_rh850_core3_ei282:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_282_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei282, .-_osEE_rh850_core3_ei282
#else
_osEE_rh850_core3_ei282:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_282_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei282, .-_osEE_rh850_core3_ei282
#endif
#endif /* OSEE_RH850_CORE3_282_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_283_ISR_CAT))
#if (OSEE_RH850_CORE3_283_ISR_CAT == 1)
_osEE_rh850_core3_ei283:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_283_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei283, .-_osEE_rh850_core3_ei283
#else
_osEE_rh850_core3_ei283:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_283_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei283, .-_osEE_rh850_core3_ei283
#endif
#endif /* OSEE_RH850_CORE3_283_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_284_ISR_CAT))
#if (OSEE_RH850_CORE3_284_ISR_CAT == 1)
_osEE_rh850_core3_ei284:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_284_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei284, .-_osEE_rh850_core3_ei284
#else
_osEE_rh850_core3_ei284:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_284_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei284, .-_osEE_rh850_core3_ei284
#endif
#endif /* OSEE_RH850_CORE3_284_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_285_ISR_CAT))
#if (OSEE_RH850_CORE3_285_ISR_CAT == 1)
_osEE_rh850_core3_ei285:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_285_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei285, .-_osEE_rh850_core3_ei285
#else
_osEE_rh850_core3_ei285:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_285_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei285, .-_osEE_rh850_core3_ei285
#endif
#endif /* OSEE_RH850_CORE3_285_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_286_ISR_CAT))
#if (OSEE_RH850_CORE3_286_ISR_CAT == 1)
_osEE_rh850_core3_ei286:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_286_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei286, .-_osEE_rh850_core3_ei286
#else
_osEE_rh850_core3_ei286:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_286_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei286, .-_osEE_rh850_core3_ei286
#endif
#endif /* OSEE_RH850_CORE3_286_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_287_ISR_CAT))
#if (OSEE_RH850_CORE3_287_ISR_CAT == 1)
_osEE_rh850_core3_ei287:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_287_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei287, .-_osEE_rh850_core3_ei287
#else
_osEE_rh850_core3_ei287:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_287_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei287, .-_osEE_rh850_core3_ei287
#endif
#endif /* OSEE_RH850_CORE3_287_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_288_ISR_CAT))
#if (OSEE_RH850_CORE3_288_ISR_CAT == 1)
_osEE_rh850_core3_ei288:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_288_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei288, .-_osEE_rh850_core3_ei288
#else
_osEE_rh850_core3_ei288:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_288_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei288, .-_osEE_rh850_core3_ei288
#endif
#endif /* OSEE_RH850_CORE3_288_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_289_ISR_CAT))
#if (OSEE_RH850_CORE3_289_ISR_CAT == 1)
_osEE_rh850_core3_ei289:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_289_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei289, .-_osEE_rh850_core3_ei289
#else
_osEE_rh850_core3_ei289:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_289_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei289, .-_osEE_rh850_core3_ei289
#endif
#endif /* OSEE_RH850_CORE3_289_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_290_ISR_CAT))
#if (OSEE_RH850_CORE3_290_ISR_CAT == 1)
_osEE_rh850_core3_ei290:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_290_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei290, .-_osEE_rh850_core3_ei290
#else
_osEE_rh850_core3_ei290:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_290_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei290, .-_osEE_rh850_core3_ei290
#endif
#endif /* OSEE_RH850_CORE3_290_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_291_ISR_CAT))
#if (OSEE_RH850_CORE3_291_ISR_CAT == 1)
_osEE_rh850_core3_ei291:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_291_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei291, .-_osEE_rh850_core3_ei291
#else
_osEE_rh850_core3_ei291:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_291_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei291, .-_osEE_rh850_core3_ei291
#endif
#endif /* OSEE_RH850_CORE3_291_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_292_ISR_CAT))
#if (OSEE_RH850_CORE3_292_ISR_CAT == 1)
_osEE_rh850_core3_ei292:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_292_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei292, .-_osEE_rh850_core3_ei292
#else
_osEE_rh850_core3_ei292:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_292_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei292, .-_osEE_rh850_core3_ei292
#endif
#endif /* OSEE_RH850_CORE3_292_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_293_ISR_CAT))
#if (OSEE_RH850_CORE3_293_ISR_CAT == 1)
_osEE_rh850_core3_ei293:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_293_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei293, .-_osEE_rh850_core3_ei293
#else
_osEE_rh850_core3_ei293:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_293_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei293, .-_osEE_rh850_core3_ei293
#endif
#endif /* OSEE_RH850_CORE3_293_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_294_ISR_CAT))
#if (OSEE_RH850_CORE3_294_ISR_CAT == 1)
_osEE_rh850_core3_ei294:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_294_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei294, .-_osEE_rh850_core3_ei294
#else
_osEE_rh850_core3_ei294:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_294_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei294, .-_osEE_rh850_core3_ei294
#endif
#endif /* OSEE_RH850_CORE3_294_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_295_ISR_CAT))
#if (OSEE_RH850_CORE3_295_ISR_CAT == 1)
_osEE_rh850_core3_ei295:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_295_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei295, .-_osEE_rh850_core3_ei295
#else
_osEE_rh850_core3_ei295:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_295_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei295, .-_osEE_rh850_core3_ei295
#endif
#endif /* OSEE_RH850_CORE3_295_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_296_ISR_CAT))
#if (OSEE_RH850_CORE3_296_ISR_CAT == 1)
_osEE_rh850_core3_ei296:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_296_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei296, .-_osEE_rh850_core3_ei296
#else
_osEE_rh850_core3_ei296:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_296_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei296, .-_osEE_rh850_core3_ei296
#endif
#endif /* OSEE_RH850_CORE3_296_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_297_ISR_CAT))
#if (OSEE_RH850_CORE3_297_ISR_CAT == 1)
_osEE_rh850_core3_ei297:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_297_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei297, .-_osEE_rh850_core3_ei297
#else
_osEE_rh850_core3_ei297:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_297_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei297, .-_osEE_rh850_core3_ei297
#endif
#endif /* OSEE_RH850_CORE3_297_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_298_ISR_CAT))
#if (OSEE_RH850_CORE3_298_ISR_CAT == 1)
_osEE_rh850_core3_ei298:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_298_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei298, .-_osEE_rh850_core3_ei298
#else
_osEE_rh850_core3_ei298:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_298_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei298, .-_osEE_rh850_core3_ei298
#endif
#endif /* OSEE_RH850_CORE3_298_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_299_ISR_CAT))
#if (OSEE_RH850_CORE3_299_ISR_CAT == 1)
_osEE_rh850_core3_ei299:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_299_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei299, .-_osEE_rh850_core3_ei299
#else
_osEE_rh850_core3_ei299:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_299_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei299, .-_osEE_rh850_core3_ei299
#endif
#endif /* OSEE_RH850_CORE3_299_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_300_ISR_CAT))
#if (OSEE_RH850_CORE3_300_ISR_CAT == 1)
_osEE_rh850_core3_ei300:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_300_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei300, .-_osEE_rh850_core3_ei300
#else
_osEE_rh850_core3_ei300:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_300_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei300, .-_osEE_rh850_core3_ei300
#endif
#endif /* OSEE_RH850_CORE3_300_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_301_ISR_CAT))
#if (OSEE_RH850_CORE3_301_ISR_CAT == 1)
_osEE_rh850_core3_ei301:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_301_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei301, .-_osEE_rh850_core3_ei301
#else
_osEE_rh850_core3_ei301:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_301_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei301, .-_osEE_rh850_core3_ei301
#endif
#endif /* OSEE_RH850_CORE3_301_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_302_ISR_CAT))
#if (OSEE_RH850_CORE3_302_ISR_CAT == 1)
_osEE_rh850_core3_ei302:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_302_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei302, .-_osEE_rh850_core3_ei302
#else
_osEE_rh850_core3_ei302:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_302_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei302, .-_osEE_rh850_core3_ei302
#endif
#endif /* OSEE_RH850_CORE3_302_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_303_ISR_CAT))
#if (OSEE_RH850_CORE3_303_ISR_CAT == 1)
_osEE_rh850_core3_ei303:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_303_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei303, .-_osEE_rh850_core3_ei303
#else
_osEE_rh850_core3_ei303:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_303_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei303, .-_osEE_rh850_core3_ei303
#endif
#endif /* OSEE_RH850_CORE3_303_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_304_ISR_CAT))
#if (OSEE_RH850_CORE3_304_ISR_CAT == 1)
_osEE_rh850_core3_ei304:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_304_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei304, .-_osEE_rh850_core3_ei304
#else
_osEE_rh850_core3_ei304:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_304_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei304, .-_osEE_rh850_core3_ei304
#endif
#endif /* OSEE_RH850_CORE3_304_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_305_ISR_CAT))
#if (OSEE_RH850_CORE3_305_ISR_CAT == 1)
_osEE_rh850_core3_ei305:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_305_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei305, .-_osEE_rh850_core3_ei305
#else
_osEE_rh850_core3_ei305:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_305_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei305, .-_osEE_rh850_core3_ei305
#endif
#endif /* OSEE_RH850_CORE3_305_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_306_ISR_CAT))
#if (OSEE_RH850_CORE3_306_ISR_CAT == 1)
_osEE_rh850_core3_ei306:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_306_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei306, .-_osEE_rh850_core3_ei306
#else
_osEE_rh850_core3_ei306:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_306_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei306, .-_osEE_rh850_core3_ei306
#endif
#endif /* OSEE_RH850_CORE3_306_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_307_ISR_CAT))
#if (OSEE_RH850_CORE3_307_ISR_CAT == 1)
_osEE_rh850_core3_ei307:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_307_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei307, .-_osEE_rh850_core3_ei307
#else
_osEE_rh850_core3_ei307:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_307_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei307, .-_osEE_rh850_core3_ei307
#endif
#endif /* OSEE_RH850_CORE3_307_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_308_ISR_CAT))
#if (OSEE_RH850_CORE3_308_ISR_CAT == 1)
_osEE_rh850_core3_ei308:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_308_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei308, .-_osEE_rh850_core3_ei308
#else
_osEE_rh850_core3_ei308:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_308_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei308, .-_osEE_rh850_core3_ei308
#endif
#endif /* OSEE_RH850_CORE3_308_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_309_ISR_CAT))
#if (OSEE_RH850_CORE3_309_ISR_CAT == 1)
_osEE_rh850_core3_ei309:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_309_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei309, .-_osEE_rh850_core3_ei309
#else
_osEE_rh850_core3_ei309:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_309_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei309, .-_osEE_rh850_core3_ei309
#endif
#endif /* OSEE_RH850_CORE3_309_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_310_ISR_CAT))
#if (OSEE_RH850_CORE3_310_ISR_CAT == 1)
_osEE_rh850_core3_ei310:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_310_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei310, .-_osEE_rh850_core3_ei310
#else
_osEE_rh850_core3_ei310:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_310_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei310, .-_osEE_rh850_core3_ei310
#endif
#endif /* OSEE_RH850_CORE3_310_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_311_ISR_CAT))
#if (OSEE_RH850_CORE3_311_ISR_CAT == 1)
_osEE_rh850_core3_ei311:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_311_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei311, .-_osEE_rh850_core3_ei311
#else
_osEE_rh850_core3_ei311:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_311_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei311, .-_osEE_rh850_core3_ei311
#endif
#endif /* OSEE_RH850_CORE3_311_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_312_ISR_CAT))
#if (OSEE_RH850_CORE3_312_ISR_CAT == 1)
_osEE_rh850_core3_ei312:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_312_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei312, .-_osEE_rh850_core3_ei312
#else
_osEE_rh850_core3_ei312:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_312_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei312, .-_osEE_rh850_core3_ei312
#endif
#endif /* OSEE_RH850_CORE3_312_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_313_ISR_CAT))
#if (OSEE_RH850_CORE3_313_ISR_CAT == 1)
_osEE_rh850_core3_ei313:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_313_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei313, .-_osEE_rh850_core3_ei313
#else
_osEE_rh850_core3_ei313:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_313_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei313, .-_osEE_rh850_core3_ei313
#endif
#endif /* OSEE_RH850_CORE3_313_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_314_ISR_CAT))
#if (OSEE_RH850_CORE3_314_ISR_CAT == 1)
_osEE_rh850_core3_ei314:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_314_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei314, .-_osEE_rh850_core3_ei314
#else
_osEE_rh850_core3_ei314:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_314_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei314, .-_osEE_rh850_core3_ei314
#endif
#endif /* OSEE_RH850_CORE3_314_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_315_ISR_CAT))
#if (OSEE_RH850_CORE3_315_ISR_CAT == 1)
_osEE_rh850_core3_ei315:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_315_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei315, .-_osEE_rh850_core3_ei315
#else
_osEE_rh850_core3_ei315:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_315_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei315, .-_osEE_rh850_core3_ei315
#endif
#endif /* OSEE_RH850_CORE3_315_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_316_ISR_CAT))
#if (OSEE_RH850_CORE3_316_ISR_CAT == 1)
_osEE_rh850_core3_ei316:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_316_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei316, .-_osEE_rh850_core3_ei316
#else
_osEE_rh850_core3_ei316:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_316_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei316, .-_osEE_rh850_core3_ei316
#endif
#endif /* OSEE_RH850_CORE3_316_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_317_ISR_CAT))
#if (OSEE_RH850_CORE3_317_ISR_CAT == 1)
_osEE_rh850_core3_ei317:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_317_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei317, .-_osEE_rh850_core3_ei317
#else
_osEE_rh850_core3_ei317:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_317_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei317, .-_osEE_rh850_core3_ei317
#endif
#endif /* OSEE_RH850_CORE3_317_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_318_ISR_CAT))
#if (OSEE_RH850_CORE3_318_ISR_CAT == 1)
_osEE_rh850_core3_ei318:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_318_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei318, .-_osEE_rh850_core3_ei318
#else
_osEE_rh850_core3_ei318:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_318_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei318, .-_osEE_rh850_core3_ei318
#endif
#endif /* OSEE_RH850_CORE3_318_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_319_ISR_CAT))
#if (OSEE_RH850_CORE3_319_ISR_CAT == 1)
_osEE_rh850_core3_ei319:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_319_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei319, .-_osEE_rh850_core3_ei319
#else
_osEE_rh850_core3_ei319:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_319_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei319, .-_osEE_rh850_core3_ei319
#endif
#endif /* OSEE_RH850_CORE3_319_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_320_ISR_CAT))
#if (OSEE_RH850_CORE3_320_ISR_CAT == 1)
_osEE_rh850_core3_ei320:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_320_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei320, .-_osEE_rh850_core3_ei320
#else
_osEE_rh850_core3_ei320:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_320_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei320, .-_osEE_rh850_core3_ei320
#endif
#endif /* OSEE_RH850_CORE3_320_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_321_ISR_CAT))
#if (OSEE_RH850_CORE3_321_ISR_CAT == 1)
_osEE_rh850_core3_ei321:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_321_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei321, .-_osEE_rh850_core3_ei321
#else
_osEE_rh850_core3_ei321:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_321_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei321, .-_osEE_rh850_core3_ei321
#endif
#endif /* OSEE_RH850_CORE3_321_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_322_ISR_CAT))
#if (OSEE_RH850_CORE3_322_ISR_CAT == 1)
_osEE_rh850_core3_ei322:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_322_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei322, .-_osEE_rh850_core3_ei322
#else
_osEE_rh850_core3_ei322:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_322_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei322, .-_osEE_rh850_core3_ei322
#endif
#endif /* OSEE_RH850_CORE3_322_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_323_ISR_CAT))
#if (OSEE_RH850_CORE3_323_ISR_CAT == 1)
_osEE_rh850_core3_ei323:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_323_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei323, .-_osEE_rh850_core3_ei323
#else
_osEE_rh850_core3_ei323:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_323_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei323, .-_osEE_rh850_core3_ei323
#endif
#endif /* OSEE_RH850_CORE3_323_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_324_ISR_CAT))
#if (OSEE_RH850_CORE3_324_ISR_CAT == 1)
_osEE_rh850_core3_ei324:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_324_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei324, .-_osEE_rh850_core3_ei324
#else
_osEE_rh850_core3_ei324:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_324_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei324, .-_osEE_rh850_core3_ei324
#endif
#endif /* OSEE_RH850_CORE3_324_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_325_ISR_CAT))
#if (OSEE_RH850_CORE3_325_ISR_CAT == 1)
_osEE_rh850_core3_ei325:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_325_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei325, .-_osEE_rh850_core3_ei325
#else
_osEE_rh850_core3_ei325:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_325_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei325, .-_osEE_rh850_core3_ei325
#endif
#endif /* OSEE_RH850_CORE3_325_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_326_ISR_CAT))
#if (OSEE_RH850_CORE3_326_ISR_CAT == 1)
_osEE_rh850_core3_ei326:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_326_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei326, .-_osEE_rh850_core3_ei326
#else
_osEE_rh850_core3_ei326:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_326_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei326, .-_osEE_rh850_core3_ei326
#endif
#endif /* OSEE_RH850_CORE3_326_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_327_ISR_CAT))
#if (OSEE_RH850_CORE3_327_ISR_CAT == 1)
_osEE_rh850_core3_ei327:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_327_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei327, .-_osEE_rh850_core3_ei327
#else
_osEE_rh850_core3_ei327:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_327_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei327, .-_osEE_rh850_core3_ei327
#endif
#endif /* OSEE_RH850_CORE3_327_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_328_ISR_CAT))
#if (OSEE_RH850_CORE3_328_ISR_CAT == 1)
_osEE_rh850_core3_ei328:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_328_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei328, .-_osEE_rh850_core3_ei328
#else
_osEE_rh850_core3_ei328:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_328_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei328, .-_osEE_rh850_core3_ei328
#endif
#endif /* OSEE_RH850_CORE3_328_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_329_ISR_CAT))
#if (OSEE_RH850_CORE3_329_ISR_CAT == 1)
_osEE_rh850_core3_ei329:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_329_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei329, .-_osEE_rh850_core3_ei329
#else
_osEE_rh850_core3_ei329:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_329_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei329, .-_osEE_rh850_core3_ei329
#endif
#endif /* OSEE_RH850_CORE3_329_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_330_ISR_CAT))
#if (OSEE_RH850_CORE3_330_ISR_CAT == 1)
_osEE_rh850_core3_ei330:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_330_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei330, .-_osEE_rh850_core3_ei330
#else
_osEE_rh850_core3_ei330:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_330_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei330, .-_osEE_rh850_core3_ei330
#endif
#endif /* OSEE_RH850_CORE3_330_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_331_ISR_CAT))
#if (OSEE_RH850_CORE3_331_ISR_CAT == 1)
_osEE_rh850_core3_ei331:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_331_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei331, .-_osEE_rh850_core3_ei331
#else
_osEE_rh850_core3_ei331:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_331_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei331, .-_osEE_rh850_core3_ei331
#endif
#endif /* OSEE_RH850_CORE3_331_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_332_ISR_CAT))
#if (OSEE_RH850_CORE3_332_ISR_CAT == 1)
_osEE_rh850_core3_ei332:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_332_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei332, .-_osEE_rh850_core3_ei332
#else
_osEE_rh850_core3_ei332:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_332_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei332, .-_osEE_rh850_core3_ei332
#endif
#endif /* OSEE_RH850_CORE3_332_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_333_ISR_CAT))
#if (OSEE_RH850_CORE3_333_ISR_CAT == 1)
_osEE_rh850_core3_ei333:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_333_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei333, .-_osEE_rh850_core3_ei333
#else
_osEE_rh850_core3_ei333:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_333_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei333, .-_osEE_rh850_core3_ei333
#endif
#endif /* OSEE_RH850_CORE3_333_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_334_ISR_CAT))
#if (OSEE_RH850_CORE3_334_ISR_CAT == 1)
_osEE_rh850_core3_ei334:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_334_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei334, .-_osEE_rh850_core3_ei334
#else
_osEE_rh850_core3_ei334:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_334_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei334, .-_osEE_rh850_core3_ei334
#endif
#endif /* OSEE_RH850_CORE3_334_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_335_ISR_CAT))
#if (OSEE_RH850_CORE3_335_ISR_CAT == 1)
_osEE_rh850_core3_ei335:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_335_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei335, .-_osEE_rh850_core3_ei335
#else
_osEE_rh850_core3_ei335:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_335_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei335, .-_osEE_rh850_core3_ei335
#endif
#endif /* OSEE_RH850_CORE3_335_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_336_ISR_CAT))
#if (OSEE_RH850_CORE3_336_ISR_CAT == 1)
_osEE_rh850_core3_ei336:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_336_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei336, .-_osEE_rh850_core3_ei336
#else
_osEE_rh850_core3_ei336:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_336_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei336, .-_osEE_rh850_core3_ei336
#endif
#endif /* OSEE_RH850_CORE3_336_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_337_ISR_CAT))
#if (OSEE_RH850_CORE3_337_ISR_CAT == 1)
_osEE_rh850_core3_ei337:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_337_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei337, .-_osEE_rh850_core3_ei337
#else
_osEE_rh850_core3_ei337:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_337_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei337, .-_osEE_rh850_core3_ei337
#endif
#endif /* OSEE_RH850_CORE3_337_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_338_ISR_CAT))
#if (OSEE_RH850_CORE3_338_ISR_CAT == 1)
_osEE_rh850_core3_ei338:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_338_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei338, .-_osEE_rh850_core3_ei338
#else
_osEE_rh850_core3_ei338:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_338_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei338, .-_osEE_rh850_core3_ei338
#endif
#endif /* OSEE_RH850_CORE3_338_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_339_ISR_CAT))
#if (OSEE_RH850_CORE3_339_ISR_CAT == 1)
_osEE_rh850_core3_ei339:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_339_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei339, .-_osEE_rh850_core3_ei339
#else
_osEE_rh850_core3_ei339:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_339_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei339, .-_osEE_rh850_core3_ei339
#endif
#endif /* OSEE_RH850_CORE3_339_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_340_ISR_CAT))
#if (OSEE_RH850_CORE3_340_ISR_CAT == 1)
_osEE_rh850_core3_ei340:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_340_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei340, .-_osEE_rh850_core3_ei340
#else
_osEE_rh850_core3_ei340:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_340_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei340, .-_osEE_rh850_core3_ei340
#endif
#endif /* OSEE_RH850_CORE3_340_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_341_ISR_CAT))
#if (OSEE_RH850_CORE3_341_ISR_CAT == 1)
_osEE_rh850_core3_ei341:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_341_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei341, .-_osEE_rh850_core3_ei341
#else
_osEE_rh850_core3_ei341:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_341_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei341, .-_osEE_rh850_core3_ei341
#endif
#endif /* OSEE_RH850_CORE3_341_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_342_ISR_CAT))
#if (OSEE_RH850_CORE3_342_ISR_CAT == 1)
_osEE_rh850_core3_ei342:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_342_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei342, .-_osEE_rh850_core3_ei342
#else
_osEE_rh850_core3_ei342:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_342_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei342, .-_osEE_rh850_core3_ei342
#endif
#endif /* OSEE_RH850_CORE3_342_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_343_ISR_CAT))
#if (OSEE_RH850_CORE3_343_ISR_CAT == 1)
_osEE_rh850_core3_ei343:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_343_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei343, .-_osEE_rh850_core3_ei343
#else
_osEE_rh850_core3_ei343:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_343_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei343, .-_osEE_rh850_core3_ei343
#endif
#endif /* OSEE_RH850_CORE3_343_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_344_ISR_CAT))
#if (OSEE_RH850_CORE3_344_ISR_CAT == 1)
_osEE_rh850_core3_ei344:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_344_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei344, .-_osEE_rh850_core3_ei344
#else
_osEE_rh850_core3_ei344:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_344_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei344, .-_osEE_rh850_core3_ei344
#endif
#endif /* OSEE_RH850_CORE3_344_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_345_ISR_CAT))
#if (OSEE_RH850_CORE3_345_ISR_CAT == 1)
_osEE_rh850_core3_ei345:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_345_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei345, .-_osEE_rh850_core3_ei345
#else
_osEE_rh850_core3_ei345:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_345_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei345, .-_osEE_rh850_core3_ei345
#endif
#endif /* OSEE_RH850_CORE3_345_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_346_ISR_CAT))
#if (OSEE_RH850_CORE3_346_ISR_CAT == 1)
_osEE_rh850_core3_ei346:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_346_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei346, .-_osEE_rh850_core3_ei346
#else
_osEE_rh850_core3_ei346:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_346_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei346, .-_osEE_rh850_core3_ei346
#endif
#endif /* OSEE_RH850_CORE3_346_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_347_ISR_CAT))
#if (OSEE_RH850_CORE3_347_ISR_CAT == 1)
_osEE_rh850_core3_ei347:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_347_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei347, .-_osEE_rh850_core3_ei347
#else
_osEE_rh850_core3_ei347:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_347_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei347, .-_osEE_rh850_core3_ei347
#endif
#endif /* OSEE_RH850_CORE3_347_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_348_ISR_CAT))
#if (OSEE_RH850_CORE3_348_ISR_CAT == 1)
_osEE_rh850_core3_ei348:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_348_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei348, .-_osEE_rh850_core3_ei348
#else
_osEE_rh850_core3_ei348:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_348_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei348, .-_osEE_rh850_core3_ei348
#endif
#endif /* OSEE_RH850_CORE3_348_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_349_ISR_CAT))
#if (OSEE_RH850_CORE3_349_ISR_CAT == 1)
_osEE_rh850_core3_ei349:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_349_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei349, .-_osEE_rh850_core3_ei349
#else
_osEE_rh850_core3_ei349:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_349_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei349, .-_osEE_rh850_core3_ei349
#endif
#endif /* OSEE_RH850_CORE3_349_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_350_ISR_CAT))
#if (OSEE_RH850_CORE3_350_ISR_CAT == 1)
_osEE_rh850_core3_ei350:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_350_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei350, .-_osEE_rh850_core3_ei350
#else
_osEE_rh850_core3_ei350:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_350_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei350, .-_osEE_rh850_core3_ei350
#endif
#endif /* OSEE_RH850_CORE3_350_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_351_ISR_CAT))
#if (OSEE_RH850_CORE3_351_ISR_CAT == 1)
_osEE_rh850_core3_ei351:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_351_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei351, .-_osEE_rh850_core3_ei351
#else
_osEE_rh850_core3_ei351:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_351_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei351, .-_osEE_rh850_core3_ei351
#endif
#endif /* OSEE_RH850_CORE3_351_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_352_ISR_CAT))
#if (OSEE_RH850_CORE3_352_ISR_CAT == 1)
_osEE_rh850_core3_ei352:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_352_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei352, .-_osEE_rh850_core3_ei352
#else
_osEE_rh850_core3_ei352:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_352_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei352, .-_osEE_rh850_core3_ei352
#endif
#endif /* OSEE_RH850_CORE3_352_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_353_ISR_CAT))
#if (OSEE_RH850_CORE3_353_ISR_CAT == 1)
_osEE_rh850_core3_ei353:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_353_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei353, .-_osEE_rh850_core3_ei353
#else
_osEE_rh850_core3_ei353:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_353_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei353, .-_osEE_rh850_core3_ei353
#endif
#endif /* OSEE_RH850_CORE3_353_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_354_ISR_CAT))
#if (OSEE_RH850_CORE3_354_ISR_CAT == 1)
_osEE_rh850_core3_ei354:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_354_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei354, .-_osEE_rh850_core3_ei354
#else
_osEE_rh850_core3_ei354:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_354_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei354, .-_osEE_rh850_core3_ei354
#endif
#endif /* OSEE_RH850_CORE3_354_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_355_ISR_CAT))
#if (OSEE_RH850_CORE3_355_ISR_CAT == 1)
_osEE_rh850_core3_ei355:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_355_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei355, .-_osEE_rh850_core3_ei355
#else
_osEE_rh850_core3_ei355:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_355_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei355, .-_osEE_rh850_core3_ei355
#endif
#endif /* OSEE_RH850_CORE3_355_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_356_ISR_CAT))
#if (OSEE_RH850_CORE3_356_ISR_CAT == 1)
_osEE_rh850_core3_ei356:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_356_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei356, .-_osEE_rh850_core3_ei356
#else
_osEE_rh850_core3_ei356:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_356_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei356, .-_osEE_rh850_core3_ei356
#endif
#endif /* OSEE_RH850_CORE3_356_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_357_ISR_CAT))
#if (OSEE_RH850_CORE3_357_ISR_CAT == 1)
_osEE_rh850_core3_ei357:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_357_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei357, .-_osEE_rh850_core3_ei357
#else
_osEE_rh850_core3_ei357:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_357_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei357, .-_osEE_rh850_core3_ei357
#endif
#endif /* OSEE_RH850_CORE3_357_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_358_ISR_CAT))
#if (OSEE_RH850_CORE3_358_ISR_CAT == 1)
_osEE_rh850_core3_ei358:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_358_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei358, .-_osEE_rh850_core3_ei358
#else
_osEE_rh850_core3_ei358:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_358_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei358, .-_osEE_rh850_core3_ei358
#endif
#endif /* OSEE_RH850_CORE3_358_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_359_ISR_CAT))
#if (OSEE_RH850_CORE3_359_ISR_CAT == 1)
_osEE_rh850_core3_ei359:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_359_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei359, .-_osEE_rh850_core3_ei359
#else
_osEE_rh850_core3_ei359:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_359_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei359, .-_osEE_rh850_core3_ei359
#endif
#endif /* OSEE_RH850_CORE3_359_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_360_ISR_CAT))
#if (OSEE_RH850_CORE3_360_ISR_CAT == 1)
_osEE_rh850_core3_ei360:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_360_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei360, .-_osEE_rh850_core3_ei360
#else
_osEE_rh850_core3_ei360:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_360_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei360, .-_osEE_rh850_core3_ei360
#endif
#endif /* OSEE_RH850_CORE3_360_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_361_ISR_CAT))
#if (OSEE_RH850_CORE3_361_ISR_CAT == 1)
_osEE_rh850_core3_ei361:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_361_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei361, .-_osEE_rh850_core3_ei361
#else
_osEE_rh850_core3_ei361:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_361_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei361, .-_osEE_rh850_core3_ei361
#endif
#endif /* OSEE_RH850_CORE3_361_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_362_ISR_CAT))
#if (OSEE_RH850_CORE3_362_ISR_CAT == 1)
_osEE_rh850_core3_ei362:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_362_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei362, .-_osEE_rh850_core3_ei362
#else
_osEE_rh850_core3_ei362:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_362_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei362, .-_osEE_rh850_core3_ei362
#endif
#endif /* OSEE_RH850_CORE3_362_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_363_ISR_CAT))
#if (OSEE_RH850_CORE3_363_ISR_CAT == 1)
_osEE_rh850_core3_ei363:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_363_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei363, .-_osEE_rh850_core3_ei363
#else
_osEE_rh850_core3_ei363:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_363_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei363, .-_osEE_rh850_core3_ei363
#endif
#endif /* OSEE_RH850_CORE3_363_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_364_ISR_CAT))
#if (OSEE_RH850_CORE3_364_ISR_CAT == 1)
_osEE_rh850_core3_ei364:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_364_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei364, .-_osEE_rh850_core3_ei364
#else
_osEE_rh850_core3_ei364:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_364_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei364, .-_osEE_rh850_core3_ei364
#endif
#endif /* OSEE_RH850_CORE3_364_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_365_ISR_CAT))
#if (OSEE_RH850_CORE3_365_ISR_CAT == 1)
_osEE_rh850_core3_ei365:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_365_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei365, .-_osEE_rh850_core3_ei365
#else
_osEE_rh850_core3_ei365:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_365_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei365, .-_osEE_rh850_core3_ei365
#endif
#endif /* OSEE_RH850_CORE3_365_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_366_ISR_CAT))
#if (OSEE_RH850_CORE3_366_ISR_CAT == 1)
_osEE_rh850_core3_ei366:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_366_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei366, .-_osEE_rh850_core3_ei366
#else
_osEE_rh850_core3_ei366:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_366_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei366, .-_osEE_rh850_core3_ei366
#endif
#endif /* OSEE_RH850_CORE3_366_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_367_ISR_CAT))
#if (OSEE_RH850_CORE3_367_ISR_CAT == 1)
_osEE_rh850_core3_ei367:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_367_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei367, .-_osEE_rh850_core3_ei367
#else
_osEE_rh850_core3_ei367:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_367_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei367, .-_osEE_rh850_core3_ei367
#endif
#endif /* OSEE_RH850_CORE3_367_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_368_ISR_CAT))
#if (OSEE_RH850_CORE3_368_ISR_CAT == 1)
_osEE_rh850_core3_ei368:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_368_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei368, .-_osEE_rh850_core3_ei368
#else
_osEE_rh850_core3_ei368:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_368_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei368, .-_osEE_rh850_core3_ei368
#endif
#endif /* OSEE_RH850_CORE3_368_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_369_ISR_CAT))
#if (OSEE_RH850_CORE3_369_ISR_CAT == 1)
_osEE_rh850_core3_ei369:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_369_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei369, .-_osEE_rh850_core3_ei369
#else
_osEE_rh850_core3_ei369:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_369_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei369, .-_osEE_rh850_core3_ei369
#endif
#endif /* OSEE_RH850_CORE3_369_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_370_ISR_CAT))
#if (OSEE_RH850_CORE3_370_ISR_CAT == 1)
_osEE_rh850_core3_ei370:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_370_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei370, .-_osEE_rh850_core3_ei370
#else
_osEE_rh850_core3_ei370:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_370_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei370, .-_osEE_rh850_core3_ei370
#endif
#endif /* OSEE_RH850_CORE3_370_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_371_ISR_CAT))
#if (OSEE_RH850_CORE3_371_ISR_CAT == 1)
_osEE_rh850_core3_ei371:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_371_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei371, .-_osEE_rh850_core3_ei371
#else
_osEE_rh850_core3_ei371:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_371_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei371, .-_osEE_rh850_core3_ei371
#endif
#endif /* OSEE_RH850_CORE3_371_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_372_ISR_CAT))
#if (OSEE_RH850_CORE3_372_ISR_CAT == 1)
_osEE_rh850_core3_ei372:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_372_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei372, .-_osEE_rh850_core3_ei372
#else
_osEE_rh850_core3_ei372:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_372_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei372, .-_osEE_rh850_core3_ei372
#endif
#endif /* OSEE_RH850_CORE3_372_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_373_ISR_CAT))
#if (OSEE_RH850_CORE3_373_ISR_CAT == 1)
_osEE_rh850_core3_ei373:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_373_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei373, .-_osEE_rh850_core3_ei373
#else
_osEE_rh850_core3_ei373:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_373_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei373, .-_osEE_rh850_core3_ei373
#endif
#endif /* OSEE_RH850_CORE3_373_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_374_ISR_CAT))
#if (OSEE_RH850_CORE3_374_ISR_CAT == 1)
_osEE_rh850_core3_ei374:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_374_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei374, .-_osEE_rh850_core3_ei374
#else
_osEE_rh850_core3_ei374:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_374_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei374, .-_osEE_rh850_core3_ei374
#endif
#endif /* OSEE_RH850_CORE3_374_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_375_ISR_CAT))
#if (OSEE_RH850_CORE3_375_ISR_CAT == 1)
_osEE_rh850_core3_ei375:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_375_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei375, .-_osEE_rh850_core3_ei375
#else
_osEE_rh850_core3_ei375:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_375_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei375, .-_osEE_rh850_core3_ei375
#endif
#endif /* OSEE_RH850_CORE3_375_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_376_ISR_CAT))
#if (OSEE_RH850_CORE3_376_ISR_CAT == 1)
_osEE_rh850_core3_ei376:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_376_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei376, .-_osEE_rh850_core3_ei376
#else
_osEE_rh850_core3_ei376:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_376_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei376, .-_osEE_rh850_core3_ei376
#endif
#endif /* OSEE_RH850_CORE3_376_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_377_ISR_CAT))
#if (OSEE_RH850_CORE3_377_ISR_CAT == 1)
_osEE_rh850_core3_ei377:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_377_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei377, .-_osEE_rh850_core3_ei377
#else
_osEE_rh850_core3_ei377:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_377_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei377, .-_osEE_rh850_core3_ei377
#endif
#endif /* OSEE_RH850_CORE3_377_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_378_ISR_CAT))
#if (OSEE_RH850_CORE3_378_ISR_CAT == 1)
_osEE_rh850_core3_ei378:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_378_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei378, .-_osEE_rh850_core3_ei378
#else
_osEE_rh850_core3_ei378:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_378_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei378, .-_osEE_rh850_core3_ei378
#endif
#endif /* OSEE_RH850_CORE3_378_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_379_ISR_CAT))
#if (OSEE_RH850_CORE3_379_ISR_CAT == 1)
_osEE_rh850_core3_ei379:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_379_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei379, .-_osEE_rh850_core3_ei379
#else
_osEE_rh850_core3_ei379:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_379_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei379, .-_osEE_rh850_core3_ei379
#endif
#endif /* OSEE_RH850_CORE3_379_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_380_ISR_CAT))
#if (OSEE_RH850_CORE3_380_ISR_CAT == 1)
_osEE_rh850_core3_ei380:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_380_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei380, .-_osEE_rh850_core3_ei380
#else
_osEE_rh850_core3_ei380:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_380_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei380, .-_osEE_rh850_core3_ei380
#endif
#endif /* OSEE_RH850_CORE3_380_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_381_ISR_CAT))
#if (OSEE_RH850_CORE3_381_ISR_CAT == 1)
_osEE_rh850_core3_ei381:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_381_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei381, .-_osEE_rh850_core3_ei381
#else
_osEE_rh850_core3_ei381:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_381_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei381, .-_osEE_rh850_core3_ei381
#endif
#endif /* OSEE_RH850_CORE3_381_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_382_ISR_CAT))
#if (OSEE_RH850_CORE3_382_ISR_CAT == 1)
_osEE_rh850_core3_ei382:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_382_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei382, .-_osEE_rh850_core3_ei382
#else
_osEE_rh850_core3_ei382:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_382_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei382, .-_osEE_rh850_core3_ei382
#endif
#endif /* OSEE_RH850_CORE3_382_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_383_ISR_CAT))
#if (OSEE_RH850_CORE3_383_ISR_CAT == 1)
_osEE_rh850_core3_ei383:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_383_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei383, .-_osEE_rh850_core3_ei383
#else
_osEE_rh850_core3_ei383:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_383_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei383, .-_osEE_rh850_core3_ei383
#endif
#endif /* OSEE_RH850_CORE3_383_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_384_ISR_CAT))
#if (OSEE_RH850_CORE3_384_ISR_CAT == 1)
_osEE_rh850_core3_ei384:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_384_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei384, .-_osEE_rh850_core3_ei384
#else
_osEE_rh850_core3_ei384:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_384_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei384, .-_osEE_rh850_core3_ei384
#endif
#endif /* OSEE_RH850_CORE3_384_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_385_ISR_CAT))
#if (OSEE_RH850_CORE3_385_ISR_CAT == 1)
_osEE_rh850_core3_ei385:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_385_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei385, .-_osEE_rh850_core3_ei385
#else
_osEE_rh850_core3_ei385:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_385_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei385, .-_osEE_rh850_core3_ei385
#endif
#endif /* OSEE_RH850_CORE3_385_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_386_ISR_CAT))
#if (OSEE_RH850_CORE3_386_ISR_CAT == 1)
_osEE_rh850_core3_ei386:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_386_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei386, .-_osEE_rh850_core3_ei386
#else
_osEE_rh850_core3_ei386:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_386_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei386, .-_osEE_rh850_core3_ei386
#endif
#endif /* OSEE_RH850_CORE3_386_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_387_ISR_CAT))
#if (OSEE_RH850_CORE3_387_ISR_CAT == 1)
_osEE_rh850_core3_ei387:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_387_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei387, .-_osEE_rh850_core3_ei387
#else
_osEE_rh850_core3_ei387:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_387_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei387, .-_osEE_rh850_core3_ei387
#endif
#endif /* OSEE_RH850_CORE3_387_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_388_ISR_CAT))
#if (OSEE_RH850_CORE3_388_ISR_CAT == 1)
_osEE_rh850_core3_ei388:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_388_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei388, .-_osEE_rh850_core3_ei388
#else
_osEE_rh850_core3_ei388:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_388_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei388, .-_osEE_rh850_core3_ei388
#endif
#endif /* OSEE_RH850_CORE3_388_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_389_ISR_CAT))
#if (OSEE_RH850_CORE3_389_ISR_CAT == 1)
_osEE_rh850_core3_ei389:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_389_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei389, .-_osEE_rh850_core3_ei389
#else
_osEE_rh850_core3_ei389:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_389_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei389, .-_osEE_rh850_core3_ei389
#endif
#endif /* OSEE_RH850_CORE3_389_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_390_ISR_CAT))
#if (OSEE_RH850_CORE3_390_ISR_CAT == 1)
_osEE_rh850_core3_ei390:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_390_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei390, .-_osEE_rh850_core3_ei390
#else
_osEE_rh850_core3_ei390:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_390_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei390, .-_osEE_rh850_core3_ei390
#endif
#endif /* OSEE_RH850_CORE3_390_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_391_ISR_CAT))
#if (OSEE_RH850_CORE3_391_ISR_CAT == 1)
_osEE_rh850_core3_ei391:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_391_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei391, .-_osEE_rh850_core3_ei391
#else
_osEE_rh850_core3_ei391:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_391_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei391, .-_osEE_rh850_core3_ei391
#endif
#endif /* OSEE_RH850_CORE3_391_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_392_ISR_CAT))
#if (OSEE_RH850_CORE3_392_ISR_CAT == 1)
_osEE_rh850_core3_ei392:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_392_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei392, .-_osEE_rh850_core3_ei392
#else
_osEE_rh850_core3_ei392:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_392_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei392, .-_osEE_rh850_core3_ei392
#endif
#endif /* OSEE_RH850_CORE3_392_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_393_ISR_CAT))
#if (OSEE_RH850_CORE3_393_ISR_CAT == 1)
_osEE_rh850_core3_ei393:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_393_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei393, .-_osEE_rh850_core3_ei393
#else
_osEE_rh850_core3_ei393:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_393_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei393, .-_osEE_rh850_core3_ei393
#endif
#endif /* OSEE_RH850_CORE3_393_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_394_ISR_CAT))
#if (OSEE_RH850_CORE3_394_ISR_CAT == 1)
_osEE_rh850_core3_ei394:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_394_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei394, .-_osEE_rh850_core3_ei394
#else
_osEE_rh850_core3_ei394:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_394_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei394, .-_osEE_rh850_core3_ei394
#endif
#endif /* OSEE_RH850_CORE3_394_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_395_ISR_CAT))
#if (OSEE_RH850_CORE3_395_ISR_CAT == 1)
_osEE_rh850_core3_ei395:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_395_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei395, .-_osEE_rh850_core3_ei395
#else
_osEE_rh850_core3_ei395:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_395_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei395, .-_osEE_rh850_core3_ei395
#endif
#endif /* OSEE_RH850_CORE3_395_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_396_ISR_CAT))
#if (OSEE_RH850_CORE3_396_ISR_CAT == 1)
_osEE_rh850_core3_ei396:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_396_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei396, .-_osEE_rh850_core3_ei396
#else
_osEE_rh850_core3_ei396:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_396_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei396, .-_osEE_rh850_core3_ei396
#endif
#endif /* OSEE_RH850_CORE3_396_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_397_ISR_CAT))
#if (OSEE_RH850_CORE3_397_ISR_CAT == 1)
_osEE_rh850_core3_ei397:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_397_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei397, .-_osEE_rh850_core3_ei397
#else
_osEE_rh850_core3_ei397:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_397_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei397, .-_osEE_rh850_core3_ei397
#endif
#endif /* OSEE_RH850_CORE3_397_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_398_ISR_CAT))
#if (OSEE_RH850_CORE3_398_ISR_CAT == 1)
_osEE_rh850_core3_ei398:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_398_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei398, .-_osEE_rh850_core3_ei398
#else
_osEE_rh850_core3_ei398:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_398_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei398, .-_osEE_rh850_core3_ei398
#endif
#endif /* OSEE_RH850_CORE3_398_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_399_ISR_CAT))
#if (OSEE_RH850_CORE3_399_ISR_CAT == 1)
_osEE_rh850_core3_ei399:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_399_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei399, .-_osEE_rh850_core3_ei399
#else
_osEE_rh850_core3_ei399:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_399_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei399, .-_osEE_rh850_core3_ei399
#endif
#endif /* OSEE_RH850_CORE3_399_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_400_ISR_CAT))
#if (OSEE_RH850_CORE3_400_ISR_CAT == 1)
_osEE_rh850_core3_ei400:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_400_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei400, .-_osEE_rh850_core3_ei400
#else
_osEE_rh850_core3_ei400:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_400_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei400, .-_osEE_rh850_core3_ei400
#endif
#endif /* OSEE_RH850_CORE3_400_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_401_ISR_CAT))
#if (OSEE_RH850_CORE3_401_ISR_CAT == 1)
_osEE_rh850_core3_ei401:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_401_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei401, .-_osEE_rh850_core3_ei401
#else
_osEE_rh850_core3_ei401:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_401_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei401, .-_osEE_rh850_core3_ei401
#endif
#endif /* OSEE_RH850_CORE3_401_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_402_ISR_CAT))
#if (OSEE_RH850_CORE3_402_ISR_CAT == 1)
_osEE_rh850_core3_ei402:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_402_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei402, .-_osEE_rh850_core3_ei402
#else
_osEE_rh850_core3_ei402:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_402_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei402, .-_osEE_rh850_core3_ei402
#endif
#endif /* OSEE_RH850_CORE3_402_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_403_ISR_CAT))
#if (OSEE_RH850_CORE3_403_ISR_CAT == 1)
_osEE_rh850_core3_ei403:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_403_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei403, .-_osEE_rh850_core3_ei403
#else
_osEE_rh850_core3_ei403:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_403_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei403, .-_osEE_rh850_core3_ei403
#endif
#endif /* OSEE_RH850_CORE3_403_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_404_ISR_CAT))
#if (OSEE_RH850_CORE3_404_ISR_CAT == 1)
_osEE_rh850_core3_ei404:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_404_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei404, .-_osEE_rh850_core3_ei404
#else
_osEE_rh850_core3_ei404:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_404_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei404, .-_osEE_rh850_core3_ei404
#endif
#endif /* OSEE_RH850_CORE3_404_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_405_ISR_CAT))
#if (OSEE_RH850_CORE3_405_ISR_CAT == 1)
_osEE_rh850_core3_ei405:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_405_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei405, .-_osEE_rh850_core3_ei405
#else
_osEE_rh850_core3_ei405:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_405_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei405, .-_osEE_rh850_core3_ei405
#endif
#endif /* OSEE_RH850_CORE3_405_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_406_ISR_CAT))
#if (OSEE_RH850_CORE3_406_ISR_CAT == 1)
_osEE_rh850_core3_ei406:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_406_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei406, .-_osEE_rh850_core3_ei406
#else
_osEE_rh850_core3_ei406:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_406_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei406, .-_osEE_rh850_core3_ei406
#endif
#endif /* OSEE_RH850_CORE3_406_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_407_ISR_CAT))
#if (OSEE_RH850_CORE3_407_ISR_CAT == 1)
_osEE_rh850_core3_ei407:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_407_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei407, .-_osEE_rh850_core3_ei407
#else
_osEE_rh850_core3_ei407:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_407_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei407, .-_osEE_rh850_core3_ei407
#endif
#endif /* OSEE_RH850_CORE3_407_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_408_ISR_CAT))
#if (OSEE_RH850_CORE3_408_ISR_CAT == 1)
_osEE_rh850_core3_ei408:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_408_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei408, .-_osEE_rh850_core3_ei408
#else
_osEE_rh850_core3_ei408:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_408_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei408, .-_osEE_rh850_core3_ei408
#endif
#endif /* OSEE_RH850_CORE3_408_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_409_ISR_CAT))
#if (OSEE_RH850_CORE3_409_ISR_CAT == 1)
_osEE_rh850_core3_ei409:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_409_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei409, .-_osEE_rh850_core3_ei409
#else
_osEE_rh850_core3_ei409:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_409_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei409, .-_osEE_rh850_core3_ei409
#endif
#endif /* OSEE_RH850_CORE3_409_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_410_ISR_CAT))
#if (OSEE_RH850_CORE3_410_ISR_CAT == 1)
_osEE_rh850_core3_ei410:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_410_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei410, .-_osEE_rh850_core3_ei410
#else
_osEE_rh850_core3_ei410:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_410_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei410, .-_osEE_rh850_core3_ei410
#endif
#endif /* OSEE_RH850_CORE3_410_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_411_ISR_CAT))
#if (OSEE_RH850_CORE3_411_ISR_CAT == 1)
_osEE_rh850_core3_ei411:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_411_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei411, .-_osEE_rh850_core3_ei411
#else
_osEE_rh850_core3_ei411:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_411_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei411, .-_osEE_rh850_core3_ei411
#endif
#endif /* OSEE_RH850_CORE3_411_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_412_ISR_CAT))
#if (OSEE_RH850_CORE3_412_ISR_CAT == 1)
_osEE_rh850_core3_ei412:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_412_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei412, .-_osEE_rh850_core3_ei412
#else
_osEE_rh850_core3_ei412:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_412_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei412, .-_osEE_rh850_core3_ei412
#endif
#endif /* OSEE_RH850_CORE3_412_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_413_ISR_CAT))
#if (OSEE_RH850_CORE3_413_ISR_CAT == 1)
_osEE_rh850_core3_ei413:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_413_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei413, .-_osEE_rh850_core3_ei413
#else
_osEE_rh850_core3_ei413:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_413_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei413, .-_osEE_rh850_core3_ei413
#endif
#endif /* OSEE_RH850_CORE3_413_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_414_ISR_CAT))
#if (OSEE_RH850_CORE3_414_ISR_CAT == 1)
_osEE_rh850_core3_ei414:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_414_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei414, .-_osEE_rh850_core3_ei414
#else
_osEE_rh850_core3_ei414:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_414_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei414, .-_osEE_rh850_core3_ei414
#endif
#endif /* OSEE_RH850_CORE3_414_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_415_ISR_CAT))
#if (OSEE_RH850_CORE3_415_ISR_CAT == 1)
_osEE_rh850_core3_ei415:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_415_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei415, .-_osEE_rh850_core3_ei415
#else
_osEE_rh850_core3_ei415:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_415_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei415, .-_osEE_rh850_core3_ei415
#endif
#endif /* OSEE_RH850_CORE3_415_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_416_ISR_CAT))
#if (OSEE_RH850_CORE3_416_ISR_CAT == 1)
_osEE_rh850_core3_ei416:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_416_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei416, .-_osEE_rh850_core3_ei416
#else
_osEE_rh850_core3_ei416:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_416_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei416, .-_osEE_rh850_core3_ei416
#endif
#endif /* OSEE_RH850_CORE3_416_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_417_ISR_CAT))
#if (OSEE_RH850_CORE3_417_ISR_CAT == 1)
_osEE_rh850_core3_ei417:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_417_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei417, .-_osEE_rh850_core3_ei417
#else
_osEE_rh850_core3_ei417:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_417_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei417, .-_osEE_rh850_core3_ei417
#endif
#endif /* OSEE_RH850_CORE3_417_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_418_ISR_CAT))
#if (OSEE_RH850_CORE3_418_ISR_CAT == 1)
_osEE_rh850_core3_ei418:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_418_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei418, .-_osEE_rh850_core3_ei418
#else
_osEE_rh850_core3_ei418:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_418_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei418, .-_osEE_rh850_core3_ei418
#endif
#endif /* OSEE_RH850_CORE3_418_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_419_ISR_CAT))
#if (OSEE_RH850_CORE3_419_ISR_CAT == 1)
_osEE_rh850_core3_ei419:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_419_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei419, .-_osEE_rh850_core3_ei419
#else
_osEE_rh850_core3_ei419:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_419_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei419, .-_osEE_rh850_core3_ei419
#endif
#endif /* OSEE_RH850_CORE3_419_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_420_ISR_CAT))
#if (OSEE_RH850_CORE3_420_ISR_CAT == 1)
_osEE_rh850_core3_ei420:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_420_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei420, .-_osEE_rh850_core3_ei420
#else
_osEE_rh850_core3_ei420:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_420_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei420, .-_osEE_rh850_core3_ei420
#endif
#endif /* OSEE_RH850_CORE3_420_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_421_ISR_CAT))
#if (OSEE_RH850_CORE3_421_ISR_CAT == 1)
_osEE_rh850_core3_ei421:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_421_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei421, .-_osEE_rh850_core3_ei421
#else
_osEE_rh850_core3_ei421:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_421_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei421, .-_osEE_rh850_core3_ei421
#endif
#endif /* OSEE_RH850_CORE3_421_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_422_ISR_CAT))
#if (OSEE_RH850_CORE3_422_ISR_CAT == 1)
_osEE_rh850_core3_ei422:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_422_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei422, .-_osEE_rh850_core3_ei422
#else
_osEE_rh850_core3_ei422:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_422_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei422, .-_osEE_rh850_core3_ei422
#endif
#endif /* OSEE_RH850_CORE3_422_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_423_ISR_CAT))
#if (OSEE_RH850_CORE3_423_ISR_CAT == 1)
_osEE_rh850_core3_ei423:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_423_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei423, .-_osEE_rh850_core3_ei423
#else
_osEE_rh850_core3_ei423:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_423_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei423, .-_osEE_rh850_core3_ei423
#endif
#endif /* OSEE_RH850_CORE3_423_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_424_ISR_CAT))
#if (OSEE_RH850_CORE3_424_ISR_CAT == 1)
_osEE_rh850_core3_ei424:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_424_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei424, .-_osEE_rh850_core3_ei424
#else
_osEE_rh850_core3_ei424:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_424_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei424, .-_osEE_rh850_core3_ei424
#endif
#endif /* OSEE_RH850_CORE3_424_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_425_ISR_CAT))
#if (OSEE_RH850_CORE3_425_ISR_CAT == 1)
_osEE_rh850_core3_ei425:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_425_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei425, .-_osEE_rh850_core3_ei425
#else
_osEE_rh850_core3_ei425:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_425_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei425, .-_osEE_rh850_core3_ei425
#endif
#endif /* OSEE_RH850_CORE3_425_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_426_ISR_CAT))
#if (OSEE_RH850_CORE3_426_ISR_CAT == 1)
_osEE_rh850_core3_ei426:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_426_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei426, .-_osEE_rh850_core3_ei426
#else
_osEE_rh850_core3_ei426:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_426_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei426, .-_osEE_rh850_core3_ei426
#endif
#endif /* OSEE_RH850_CORE3_426_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_427_ISR_CAT))
#if (OSEE_RH850_CORE3_427_ISR_CAT == 1)
_osEE_rh850_core3_ei427:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_427_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei427, .-_osEE_rh850_core3_ei427
#else
_osEE_rh850_core3_ei427:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_427_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei427, .-_osEE_rh850_core3_ei427
#endif
#endif /* OSEE_RH850_CORE3_427_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_428_ISR_CAT))
#if (OSEE_RH850_CORE3_428_ISR_CAT == 1)
_osEE_rh850_core3_ei428:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_428_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei428, .-_osEE_rh850_core3_ei428
#else
_osEE_rh850_core3_ei428:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_428_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei428, .-_osEE_rh850_core3_ei428
#endif
#endif /* OSEE_RH850_CORE3_428_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_429_ISR_CAT))
#if (OSEE_RH850_CORE3_429_ISR_CAT == 1)
_osEE_rh850_core3_ei429:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_429_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei429, .-_osEE_rh850_core3_ei429
#else
_osEE_rh850_core3_ei429:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_429_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei429, .-_osEE_rh850_core3_ei429
#endif
#endif /* OSEE_RH850_CORE3_429_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_430_ISR_CAT))
#if (OSEE_RH850_CORE3_430_ISR_CAT == 1)
_osEE_rh850_core3_ei430:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_430_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei430, .-_osEE_rh850_core3_ei430
#else
_osEE_rh850_core3_ei430:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_430_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei430, .-_osEE_rh850_core3_ei430
#endif
#endif /* OSEE_RH850_CORE3_430_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_431_ISR_CAT))
#if (OSEE_RH850_CORE3_431_ISR_CAT == 1)
_osEE_rh850_core3_ei431:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_431_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei431, .-_osEE_rh850_core3_ei431
#else
_osEE_rh850_core3_ei431:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_431_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei431, .-_osEE_rh850_core3_ei431
#endif
#endif /* OSEE_RH850_CORE3_431_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_432_ISR_CAT))
#if (OSEE_RH850_CORE3_432_ISR_CAT == 1)
_osEE_rh850_core3_ei432:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_432_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei432, .-_osEE_rh850_core3_ei432
#else
_osEE_rh850_core3_ei432:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_432_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei432, .-_osEE_rh850_core3_ei432
#endif
#endif /* OSEE_RH850_CORE3_432_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_433_ISR_CAT))
#if (OSEE_RH850_CORE3_433_ISR_CAT == 1)
_osEE_rh850_core3_ei433:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_433_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei433, .-_osEE_rh850_core3_ei433
#else
_osEE_rh850_core3_ei433:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_433_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei433, .-_osEE_rh850_core3_ei433
#endif
#endif /* OSEE_RH850_CORE3_433_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_434_ISR_CAT))
#if (OSEE_RH850_CORE3_434_ISR_CAT == 1)
_osEE_rh850_core3_ei434:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_434_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei434, .-_osEE_rh850_core3_ei434
#else
_osEE_rh850_core3_ei434:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_434_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei434, .-_osEE_rh850_core3_ei434
#endif
#endif /* OSEE_RH850_CORE3_434_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_435_ISR_CAT))
#if (OSEE_RH850_CORE3_435_ISR_CAT == 1)
_osEE_rh850_core3_ei435:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_435_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei435, .-_osEE_rh850_core3_ei435
#else
_osEE_rh850_core3_ei435:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_435_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei435, .-_osEE_rh850_core3_ei435
#endif
#endif /* OSEE_RH850_CORE3_435_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_436_ISR_CAT))
#if (OSEE_RH850_CORE3_436_ISR_CAT == 1)
_osEE_rh850_core3_ei436:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_436_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei436, .-_osEE_rh850_core3_ei436
#else
_osEE_rh850_core3_ei436:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_436_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei436, .-_osEE_rh850_core3_ei436
#endif
#endif /* OSEE_RH850_CORE3_436_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_437_ISR_CAT))
#if (OSEE_RH850_CORE3_437_ISR_CAT == 1)
_osEE_rh850_core3_ei437:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_437_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei437, .-_osEE_rh850_core3_ei437
#else
_osEE_rh850_core3_ei437:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_437_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei437, .-_osEE_rh850_core3_ei437
#endif
#endif /* OSEE_RH850_CORE3_437_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_438_ISR_CAT))
#if (OSEE_RH850_CORE3_438_ISR_CAT == 1)
_osEE_rh850_core3_ei438:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_438_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei438, .-_osEE_rh850_core3_ei438
#else
_osEE_rh850_core3_ei438:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_438_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei438, .-_osEE_rh850_core3_ei438
#endif
#endif /* OSEE_RH850_CORE3_438_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_439_ISR_CAT))
#if (OSEE_RH850_CORE3_439_ISR_CAT == 1)
_osEE_rh850_core3_ei439:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_439_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei439, .-_osEE_rh850_core3_ei439
#else
_osEE_rh850_core3_ei439:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_439_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei439, .-_osEE_rh850_core3_ei439
#endif
#endif /* OSEE_RH850_CORE3_439_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_440_ISR_CAT))
#if (OSEE_RH850_CORE3_440_ISR_CAT == 1)
_osEE_rh850_core3_ei440:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_440_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei440, .-_osEE_rh850_core3_ei440
#else
_osEE_rh850_core3_ei440:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_440_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei440, .-_osEE_rh850_core3_ei440
#endif
#endif /* OSEE_RH850_CORE3_440_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_441_ISR_CAT))
#if (OSEE_RH850_CORE3_441_ISR_CAT == 1)
_osEE_rh850_core3_ei441:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_441_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei441, .-_osEE_rh850_core3_ei441
#else
_osEE_rh850_core3_ei441:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_441_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei441, .-_osEE_rh850_core3_ei441
#endif
#endif /* OSEE_RH850_CORE3_441_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_442_ISR_CAT))
#if (OSEE_RH850_CORE3_442_ISR_CAT == 1)
_osEE_rh850_core3_ei442:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_442_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei442, .-_osEE_rh850_core3_ei442
#else
_osEE_rh850_core3_ei442:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_442_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei442, .-_osEE_rh850_core3_ei442
#endif
#endif /* OSEE_RH850_CORE3_442_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_443_ISR_CAT))
#if (OSEE_RH850_CORE3_443_ISR_CAT == 1)
_osEE_rh850_core3_ei443:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_443_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei443, .-_osEE_rh850_core3_ei443
#else
_osEE_rh850_core3_ei443:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_443_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei443, .-_osEE_rh850_core3_ei443
#endif
#endif /* OSEE_RH850_CORE3_443_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_444_ISR_CAT))
#if (OSEE_RH850_CORE3_444_ISR_CAT == 1)
_osEE_rh850_core3_ei444:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_444_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei444, .-_osEE_rh850_core3_ei444
#else
_osEE_rh850_core3_ei444:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_444_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei444, .-_osEE_rh850_core3_ei444
#endif
#endif /* OSEE_RH850_CORE3_444_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_445_ISR_CAT))
#if (OSEE_RH850_CORE3_445_ISR_CAT == 1)
_osEE_rh850_core3_ei445:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_445_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei445, .-_osEE_rh850_core3_ei445
#else
_osEE_rh850_core3_ei445:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_445_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei445, .-_osEE_rh850_core3_ei445
#endif
#endif /* OSEE_RH850_CORE3_445_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_446_ISR_CAT))
#if (OSEE_RH850_CORE3_446_ISR_CAT == 1)
_osEE_rh850_core3_ei446:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_446_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei446, .-_osEE_rh850_core3_ei446
#else
_osEE_rh850_core3_ei446:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_446_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei446, .-_osEE_rh850_core3_ei446
#endif
#endif /* OSEE_RH850_CORE3_446_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_447_ISR_CAT))
#if (OSEE_RH850_CORE3_447_ISR_CAT == 1)
_osEE_rh850_core3_ei447:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_447_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei447, .-_osEE_rh850_core3_ei447
#else
_osEE_rh850_core3_ei447:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_447_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei447, .-_osEE_rh850_core3_ei447
#endif
#endif /* OSEE_RH850_CORE3_447_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_448_ISR_CAT))
#if (OSEE_RH850_CORE3_448_ISR_CAT == 1)
_osEE_rh850_core3_ei448:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_448_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei448, .-_osEE_rh850_core3_ei448
#else
_osEE_rh850_core3_ei448:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_448_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei448, .-_osEE_rh850_core3_ei448
#endif
#endif /* OSEE_RH850_CORE3_448_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_449_ISR_CAT))
#if (OSEE_RH850_CORE3_449_ISR_CAT == 1)
_osEE_rh850_core3_ei449:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_449_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei449, .-_osEE_rh850_core3_ei449
#else
_osEE_rh850_core3_ei449:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_449_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei449, .-_osEE_rh850_core3_ei449
#endif
#endif /* OSEE_RH850_CORE3_449_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_450_ISR_CAT))
#if (OSEE_RH850_CORE3_450_ISR_CAT == 1)
_osEE_rh850_core3_ei450:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_450_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei450, .-_osEE_rh850_core3_ei450
#else
_osEE_rh850_core3_ei450:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_450_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei450, .-_osEE_rh850_core3_ei450
#endif
#endif /* OSEE_RH850_CORE3_450_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_451_ISR_CAT))
#if (OSEE_RH850_CORE3_451_ISR_CAT == 1)
_osEE_rh850_core3_ei451:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_451_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei451, .-_osEE_rh850_core3_ei451
#else
_osEE_rh850_core3_ei451:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_451_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei451, .-_osEE_rh850_core3_ei451
#endif
#endif /* OSEE_RH850_CORE3_451_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_452_ISR_CAT))
#if (OSEE_RH850_CORE3_452_ISR_CAT == 1)
_osEE_rh850_core3_ei452:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_452_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei452, .-_osEE_rh850_core3_ei452
#else
_osEE_rh850_core3_ei452:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_452_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei452, .-_osEE_rh850_core3_ei452
#endif
#endif /* OSEE_RH850_CORE3_452_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_453_ISR_CAT))
#if (OSEE_RH850_CORE3_453_ISR_CAT == 1)
_osEE_rh850_core3_ei453:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_453_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei453, .-_osEE_rh850_core3_ei453
#else
_osEE_rh850_core3_ei453:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_453_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei453, .-_osEE_rh850_core3_ei453
#endif
#endif /* OSEE_RH850_CORE3_453_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_454_ISR_CAT))
#if (OSEE_RH850_CORE3_454_ISR_CAT == 1)
_osEE_rh850_core3_ei454:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_454_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei454, .-_osEE_rh850_core3_ei454
#else
_osEE_rh850_core3_ei454:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_454_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei454, .-_osEE_rh850_core3_ei454
#endif
#endif /* OSEE_RH850_CORE3_454_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_455_ISR_CAT))
#if (OSEE_RH850_CORE3_455_ISR_CAT == 1)
_osEE_rh850_core3_ei455:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_455_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei455, .-_osEE_rh850_core3_ei455
#else
_osEE_rh850_core3_ei455:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_455_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei455, .-_osEE_rh850_core3_ei455
#endif
#endif /* OSEE_RH850_CORE3_455_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_456_ISR_CAT))
#if (OSEE_RH850_CORE3_456_ISR_CAT == 1)
_osEE_rh850_core3_ei456:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_456_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei456, .-_osEE_rh850_core3_ei456
#else
_osEE_rh850_core3_ei456:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_456_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei456, .-_osEE_rh850_core3_ei456
#endif
#endif /* OSEE_RH850_CORE3_456_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_457_ISR_CAT))
#if (OSEE_RH850_CORE3_457_ISR_CAT == 1)
_osEE_rh850_core3_ei457:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_457_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei457, .-_osEE_rh850_core3_ei457
#else
_osEE_rh850_core3_ei457:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_457_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei457, .-_osEE_rh850_core3_ei457
#endif
#endif /* OSEE_RH850_CORE3_457_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_458_ISR_CAT))
#if (OSEE_RH850_CORE3_458_ISR_CAT == 1)
_osEE_rh850_core3_ei458:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_458_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei458, .-_osEE_rh850_core3_ei458
#else
_osEE_rh850_core3_ei458:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_458_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei458, .-_osEE_rh850_core3_ei458
#endif
#endif /* OSEE_RH850_CORE3_458_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_459_ISR_CAT))
#if (OSEE_RH850_CORE3_459_ISR_CAT == 1)
_osEE_rh850_core3_ei459:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_459_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei459, .-_osEE_rh850_core3_ei459
#else
_osEE_rh850_core3_ei459:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_459_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei459, .-_osEE_rh850_core3_ei459
#endif
#endif /* OSEE_RH850_CORE3_459_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_460_ISR_CAT))
#if (OSEE_RH850_CORE3_460_ISR_CAT == 1)
_osEE_rh850_core3_ei460:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_460_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei460, .-_osEE_rh850_core3_ei460
#else
_osEE_rh850_core3_ei460:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_460_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei460, .-_osEE_rh850_core3_ei460
#endif
#endif /* OSEE_RH850_CORE3_460_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_461_ISR_CAT))
#if (OSEE_RH850_CORE3_461_ISR_CAT == 1)
_osEE_rh850_core3_ei461:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_461_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei461, .-_osEE_rh850_core3_ei461
#else
_osEE_rh850_core3_ei461:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_461_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei461, .-_osEE_rh850_core3_ei461
#endif
#endif /* OSEE_RH850_CORE3_461_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_462_ISR_CAT))
#if (OSEE_RH850_CORE3_462_ISR_CAT == 1)
_osEE_rh850_core3_ei462:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_462_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei462, .-_osEE_rh850_core3_ei462
#else
_osEE_rh850_core3_ei462:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_462_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei462, .-_osEE_rh850_core3_ei462
#endif
#endif /* OSEE_RH850_CORE3_462_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_463_ISR_CAT))
#if (OSEE_RH850_CORE3_463_ISR_CAT == 1)
_osEE_rh850_core3_ei463:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_463_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei463, .-_osEE_rh850_core3_ei463
#else
_osEE_rh850_core3_ei463:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_463_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei463, .-_osEE_rh850_core3_ei463
#endif
#endif /* OSEE_RH850_CORE3_463_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_464_ISR_CAT))
#if (OSEE_RH850_CORE3_464_ISR_CAT == 1)
_osEE_rh850_core3_ei464:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_464_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei464, .-_osEE_rh850_core3_ei464
#else
_osEE_rh850_core3_ei464:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_464_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei464, .-_osEE_rh850_core3_ei464
#endif
#endif /* OSEE_RH850_CORE3_464_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_465_ISR_CAT))
#if (OSEE_RH850_CORE3_465_ISR_CAT == 1)
_osEE_rh850_core3_ei465:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_465_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei465, .-_osEE_rh850_core3_ei465
#else
_osEE_rh850_core3_ei465:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_465_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei465, .-_osEE_rh850_core3_ei465
#endif
#endif /* OSEE_RH850_CORE3_465_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_466_ISR_CAT))
#if (OSEE_RH850_CORE3_466_ISR_CAT == 1)
_osEE_rh850_core3_ei466:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_466_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei466, .-_osEE_rh850_core3_ei466
#else
_osEE_rh850_core3_ei466:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_466_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei466, .-_osEE_rh850_core3_ei466
#endif
#endif /* OSEE_RH850_CORE3_466_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_467_ISR_CAT))
#if (OSEE_RH850_CORE3_467_ISR_CAT == 1)
_osEE_rh850_core3_ei467:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_467_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei467, .-_osEE_rh850_core3_ei467
#else
_osEE_rh850_core3_ei467:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_467_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei467, .-_osEE_rh850_core3_ei467
#endif
#endif /* OSEE_RH850_CORE3_467_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_468_ISR_CAT))
#if (OSEE_RH850_CORE3_468_ISR_CAT == 1)
_osEE_rh850_core3_ei468:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_468_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei468, .-_osEE_rh850_core3_ei468
#else
_osEE_rh850_core3_ei468:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_468_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei468, .-_osEE_rh850_core3_ei468
#endif
#endif /* OSEE_RH850_CORE3_468_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_469_ISR_CAT))
#if (OSEE_RH850_CORE3_469_ISR_CAT == 1)
_osEE_rh850_core3_ei469:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_469_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei469, .-_osEE_rh850_core3_ei469
#else
_osEE_rh850_core3_ei469:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_469_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei469, .-_osEE_rh850_core3_ei469
#endif
#endif /* OSEE_RH850_CORE3_469_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_470_ISR_CAT))
#if (OSEE_RH850_CORE3_470_ISR_CAT == 1)
_osEE_rh850_core3_ei470:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_470_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei470, .-_osEE_rh850_core3_ei470
#else
_osEE_rh850_core3_ei470:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_470_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei470, .-_osEE_rh850_core3_ei470
#endif
#endif /* OSEE_RH850_CORE3_470_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_471_ISR_CAT))
#if (OSEE_RH850_CORE3_471_ISR_CAT == 1)
_osEE_rh850_core3_ei471:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_471_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei471, .-_osEE_rh850_core3_ei471
#else
_osEE_rh850_core3_ei471:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_471_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei471, .-_osEE_rh850_core3_ei471
#endif
#endif /* OSEE_RH850_CORE3_471_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_472_ISR_CAT))
#if (OSEE_RH850_CORE3_472_ISR_CAT == 1)
_osEE_rh850_core3_ei472:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_472_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei472, .-_osEE_rh850_core3_ei472
#else
_osEE_rh850_core3_ei472:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_472_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei472, .-_osEE_rh850_core3_ei472
#endif
#endif /* OSEE_RH850_CORE3_472_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_473_ISR_CAT))
#if (OSEE_RH850_CORE3_473_ISR_CAT == 1)
_osEE_rh850_core3_ei473:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_473_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei473, .-_osEE_rh850_core3_ei473
#else
_osEE_rh850_core3_ei473:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_473_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei473, .-_osEE_rh850_core3_ei473
#endif
#endif /* OSEE_RH850_CORE3_473_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_474_ISR_CAT))
#if (OSEE_RH850_CORE3_474_ISR_CAT == 1)
_osEE_rh850_core3_ei474:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_474_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei474, .-_osEE_rh850_core3_ei474
#else
_osEE_rh850_core3_ei474:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_474_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei474, .-_osEE_rh850_core3_ei474
#endif
#endif /* OSEE_RH850_CORE3_474_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_475_ISR_CAT))
#if (OSEE_RH850_CORE3_475_ISR_CAT == 1)
_osEE_rh850_core3_ei475:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_475_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei475, .-_osEE_rh850_core3_ei475
#else
_osEE_rh850_core3_ei475:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_475_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei475, .-_osEE_rh850_core3_ei475
#endif
#endif /* OSEE_RH850_CORE3_475_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_476_ISR_CAT))
#if (OSEE_RH850_CORE3_476_ISR_CAT == 1)
_osEE_rh850_core3_ei476:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_476_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei476, .-_osEE_rh850_core3_ei476
#else
_osEE_rh850_core3_ei476:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_476_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei476, .-_osEE_rh850_core3_ei476
#endif
#endif /* OSEE_RH850_CORE3_476_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_477_ISR_CAT))
#if (OSEE_RH850_CORE3_477_ISR_CAT == 1)
_osEE_rh850_core3_ei477:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_477_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei477, .-_osEE_rh850_core3_ei477
#else
_osEE_rh850_core3_ei477:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_477_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei477, .-_osEE_rh850_core3_ei477
#endif
#endif /* OSEE_RH850_CORE3_477_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_478_ISR_CAT))
#if (OSEE_RH850_CORE3_478_ISR_CAT == 1)
_osEE_rh850_core3_ei478:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_478_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei478, .-_osEE_rh850_core3_ei478
#else
_osEE_rh850_core3_ei478:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_478_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei478, .-_osEE_rh850_core3_ei478
#endif
#endif /* OSEE_RH850_CORE3_478_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_479_ISR_CAT))
#if (OSEE_RH850_CORE3_479_ISR_CAT == 1)
_osEE_rh850_core3_ei479:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_479_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei479, .-_osEE_rh850_core3_ei479
#else
_osEE_rh850_core3_ei479:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_479_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei479, .-_osEE_rh850_core3_ei479
#endif
#endif /* OSEE_RH850_CORE3_479_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_480_ISR_CAT))
#if (OSEE_RH850_CORE3_480_ISR_CAT == 1)
_osEE_rh850_core3_ei480:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_480_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei480, .-_osEE_rh850_core3_ei480
#else
_osEE_rh850_core3_ei480:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_480_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei480, .-_osEE_rh850_core3_ei480
#endif
#endif /* OSEE_RH850_CORE3_480_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_481_ISR_CAT))
#if (OSEE_RH850_CORE3_481_ISR_CAT == 1)
_osEE_rh850_core3_ei481:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_481_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei481, .-_osEE_rh850_core3_ei481
#else
_osEE_rh850_core3_ei481:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_481_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei481, .-_osEE_rh850_core3_ei481
#endif
#endif /* OSEE_RH850_CORE3_481_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_482_ISR_CAT))
#if (OSEE_RH850_CORE3_482_ISR_CAT == 1)
_osEE_rh850_core3_ei482:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_482_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei482, .-_osEE_rh850_core3_ei482
#else
_osEE_rh850_core3_ei482:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_482_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei482, .-_osEE_rh850_core3_ei482
#endif
#endif /* OSEE_RH850_CORE3_482_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_483_ISR_CAT))
#if (OSEE_RH850_CORE3_483_ISR_CAT == 1)
_osEE_rh850_core3_ei483:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_483_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei483, .-_osEE_rh850_core3_ei483
#else
_osEE_rh850_core3_ei483:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_483_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei483, .-_osEE_rh850_core3_ei483
#endif
#endif /* OSEE_RH850_CORE3_483_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_484_ISR_CAT))
#if (OSEE_RH850_CORE3_484_ISR_CAT == 1)
_osEE_rh850_core3_ei484:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_484_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei484, .-_osEE_rh850_core3_ei484
#else
_osEE_rh850_core3_ei484:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_484_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei484, .-_osEE_rh850_core3_ei484
#endif
#endif /* OSEE_RH850_CORE3_484_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_485_ISR_CAT))
#if (OSEE_RH850_CORE3_485_ISR_CAT == 1)
_osEE_rh850_core3_ei485:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_485_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei485, .-_osEE_rh850_core3_ei485
#else
_osEE_rh850_core3_ei485:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_485_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei485, .-_osEE_rh850_core3_ei485
#endif
#endif /* OSEE_RH850_CORE3_485_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_486_ISR_CAT))
#if (OSEE_RH850_CORE3_486_ISR_CAT == 1)
_osEE_rh850_core3_ei486:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_486_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei486, .-_osEE_rh850_core3_ei486
#else
_osEE_rh850_core3_ei486:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_486_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei486, .-_osEE_rh850_core3_ei486
#endif
#endif /* OSEE_RH850_CORE3_486_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_487_ISR_CAT))
#if (OSEE_RH850_CORE3_487_ISR_CAT == 1)
_osEE_rh850_core3_ei487:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_487_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei487, .-_osEE_rh850_core3_ei487
#else
_osEE_rh850_core3_ei487:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_487_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei487, .-_osEE_rh850_core3_ei487
#endif
#endif /* OSEE_RH850_CORE3_487_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_488_ISR_CAT))
#if (OSEE_RH850_CORE3_488_ISR_CAT == 1)
_osEE_rh850_core3_ei488:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_488_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei488, .-_osEE_rh850_core3_ei488
#else
_osEE_rh850_core3_ei488:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_488_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei488, .-_osEE_rh850_core3_ei488
#endif
#endif /* OSEE_RH850_CORE3_488_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_489_ISR_CAT))
#if (OSEE_RH850_CORE3_489_ISR_CAT == 1)
_osEE_rh850_core3_ei489:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_489_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei489, .-_osEE_rh850_core3_ei489
#else
_osEE_rh850_core3_ei489:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_489_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei489, .-_osEE_rh850_core3_ei489
#endif
#endif /* OSEE_RH850_CORE3_489_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_490_ISR_CAT))
#if (OSEE_RH850_CORE3_490_ISR_CAT == 1)
_osEE_rh850_core3_ei490:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_490_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei490, .-_osEE_rh850_core3_ei490
#else
_osEE_rh850_core3_ei490:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_490_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei490, .-_osEE_rh850_core3_ei490
#endif
#endif /* OSEE_RH850_CORE3_490_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_491_ISR_CAT))
#if (OSEE_RH850_CORE3_491_ISR_CAT == 1)
_osEE_rh850_core3_ei491:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_491_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei491, .-_osEE_rh850_core3_ei491
#else
_osEE_rh850_core3_ei491:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_491_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei491, .-_osEE_rh850_core3_ei491
#endif
#endif /* OSEE_RH850_CORE3_491_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_492_ISR_CAT))
#if (OSEE_RH850_CORE3_492_ISR_CAT == 1)
_osEE_rh850_core3_ei492:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_492_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei492, .-_osEE_rh850_core3_ei492
#else
_osEE_rh850_core3_ei492:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_492_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei492, .-_osEE_rh850_core3_ei492
#endif
#endif /* OSEE_RH850_CORE3_492_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_493_ISR_CAT))
#if (OSEE_RH850_CORE3_493_ISR_CAT == 1)
_osEE_rh850_core3_ei493:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_493_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei493, .-_osEE_rh850_core3_ei493
#else
_osEE_rh850_core3_ei493:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_493_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei493, .-_osEE_rh850_core3_ei493
#endif
#endif /* OSEE_RH850_CORE3_493_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_494_ISR_CAT))
#if (OSEE_RH850_CORE3_494_ISR_CAT == 1)
_osEE_rh850_core3_ei494:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_494_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei494, .-_osEE_rh850_core3_ei494
#else
_osEE_rh850_core3_ei494:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_494_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei494, .-_osEE_rh850_core3_ei494
#endif
#endif /* OSEE_RH850_CORE3_494_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_495_ISR_CAT))
#if (OSEE_RH850_CORE3_495_ISR_CAT == 1)
_osEE_rh850_core3_ei495:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_495_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei495, .-_osEE_rh850_core3_ei495
#else
_osEE_rh850_core3_ei495:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_495_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei495, .-_osEE_rh850_core3_ei495
#endif
#endif /* OSEE_RH850_CORE3_495_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_496_ISR_CAT))
#if (OSEE_RH850_CORE3_496_ISR_CAT == 1)
_osEE_rh850_core3_ei496:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_496_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei496, .-_osEE_rh850_core3_ei496
#else
_osEE_rh850_core3_ei496:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_496_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei496, .-_osEE_rh850_core3_ei496
#endif
#endif /* OSEE_RH850_CORE3_496_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_497_ISR_CAT))
#if (OSEE_RH850_CORE3_497_ISR_CAT == 1)
_osEE_rh850_core3_ei497:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_497_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei497, .-_osEE_rh850_core3_ei497
#else
_osEE_rh850_core3_ei497:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_497_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei497, .-_osEE_rh850_core3_ei497
#endif
#endif /* OSEE_RH850_CORE3_497_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_498_ISR_CAT))
#if (OSEE_RH850_CORE3_498_ISR_CAT == 1)
_osEE_rh850_core3_ei498:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_498_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei498, .-_osEE_rh850_core3_ei498
#else
_osEE_rh850_core3_ei498:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_498_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei498, .-_osEE_rh850_core3_ei498
#endif
#endif /* OSEE_RH850_CORE3_498_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_499_ISR_CAT))
#if (OSEE_RH850_CORE3_499_ISR_CAT == 1)
_osEE_rh850_core3_ei499:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_499_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei499, .-_osEE_rh850_core3_ei499
#else
_osEE_rh850_core3_ei499:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_499_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei499, .-_osEE_rh850_core3_ei499
#endif
#endif /* OSEE_RH850_CORE3_499_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_500_ISR_CAT))
#if (OSEE_RH850_CORE3_500_ISR_CAT == 1)
_osEE_rh850_core3_ei500:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_500_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei500, .-_osEE_rh850_core3_ei500
#else
_osEE_rh850_core3_ei500:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_500_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei500, .-_osEE_rh850_core3_ei500
#endif
#endif /* OSEE_RH850_CORE3_500_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_501_ISR_CAT))
#if (OSEE_RH850_CORE3_501_ISR_CAT == 1)
_osEE_rh850_core3_ei501:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_501_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei501, .-_osEE_rh850_core3_ei501
#else
_osEE_rh850_core3_ei501:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_501_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei501, .-_osEE_rh850_core3_ei501
#endif
#endif /* OSEE_RH850_CORE3_501_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_502_ISR_CAT))
#if (OSEE_RH850_CORE3_502_ISR_CAT == 1)
_osEE_rh850_core3_ei502:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_502_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei502, .-_osEE_rh850_core3_ei502
#else
_osEE_rh850_core3_ei502:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_502_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei502, .-_osEE_rh850_core3_ei502
#endif
#endif /* OSEE_RH850_CORE3_502_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_503_ISR_CAT))
#if (OSEE_RH850_CORE3_503_ISR_CAT == 1)
_osEE_rh850_core3_ei503:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_503_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei503, .-_osEE_rh850_core3_ei503
#else
_osEE_rh850_core3_ei503:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_503_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei503, .-_osEE_rh850_core3_ei503
#endif
#endif /* OSEE_RH850_CORE3_503_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_504_ISR_CAT))
#if (OSEE_RH850_CORE3_504_ISR_CAT == 1)
_osEE_rh850_core3_ei504:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_504_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei504, .-_osEE_rh850_core3_ei504
#else
_osEE_rh850_core3_ei504:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_504_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei504, .-_osEE_rh850_core3_ei504
#endif
#endif /* OSEE_RH850_CORE3_504_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_505_ISR_CAT))
#if (OSEE_RH850_CORE3_505_ISR_CAT == 1)
_osEE_rh850_core3_ei505:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_505_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei505, .-_osEE_rh850_core3_ei505
#else
_osEE_rh850_core3_ei505:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_505_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei505, .-_osEE_rh850_core3_ei505
#endif
#endif /* OSEE_RH850_CORE3_505_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_506_ISR_CAT))
#if (OSEE_RH850_CORE3_506_ISR_CAT == 1)
_osEE_rh850_core3_ei506:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_506_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei506, .-_osEE_rh850_core3_ei506
#else
_osEE_rh850_core3_ei506:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_506_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei506, .-_osEE_rh850_core3_ei506
#endif
#endif /* OSEE_RH850_CORE3_506_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_507_ISR_CAT))
#if (OSEE_RH850_CORE3_507_ISR_CAT == 1)
_osEE_rh850_core3_ei507:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_507_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei507, .-_osEE_rh850_core3_ei507
#else
_osEE_rh850_core3_ei507:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_507_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei507, .-_osEE_rh850_core3_ei507
#endif
#endif /* OSEE_RH850_CORE3_507_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_508_ISR_CAT))
#if (OSEE_RH850_CORE3_508_ISR_CAT == 1)
_osEE_rh850_core3_ei508:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_508_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei508, .-_osEE_rh850_core3_ei508
#else
_osEE_rh850_core3_ei508:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_508_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei508, .-_osEE_rh850_core3_ei508
#endif
#endif /* OSEE_RH850_CORE3_508_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_509_ISR_CAT))
#if (OSEE_RH850_CORE3_509_ISR_CAT == 1)
_osEE_rh850_core3_ei509:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_509_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei509, .-_osEE_rh850_core3_ei509
#else
_osEE_rh850_core3_ei509:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_509_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei509, .-_osEE_rh850_core3_ei509
#endif
#endif /* OSEE_RH850_CORE3_509_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_510_ISR_CAT))
#if (OSEE_RH850_CORE3_510_ISR_CAT == 1)
_osEE_rh850_core3_ei510:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_510_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei510, .-_osEE_rh850_core3_ei510
#else
_osEE_rh850_core3_ei510:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_510_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei510, .-_osEE_rh850_core3_ei510
#endif
#endif /* OSEE_RH850_CORE3_510_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_511_ISR_CAT))
#if (OSEE_RH850_CORE3_511_ISR_CAT == 1)
_osEE_rh850_core3_ei511:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_511_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei511, .-_osEE_rh850_core3_ei511
#else
_osEE_rh850_core3_ei511:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_511_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei511, .-_osEE_rh850_core3_ei511
#endif
#endif /* OSEE_RH850_CORE3_511_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_512_ISR_CAT))
#if (OSEE_RH850_CORE3_512_ISR_CAT == 1)
_osEE_rh850_core3_ei512:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_512_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei512, .-_osEE_rh850_core3_ei512
#else
_osEE_rh850_core3_ei512:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_512_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei512, .-_osEE_rh850_core3_ei512
#endif
#endif /* OSEE_RH850_CORE3_512_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_513_ISR_CAT))
#if (OSEE_RH850_CORE3_513_ISR_CAT == 1)
_osEE_rh850_core3_ei513:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_513_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei513, .-_osEE_rh850_core3_ei513
#else
_osEE_rh850_core3_ei513:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_513_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei513, .-_osEE_rh850_core3_ei513
#endif
#endif /* OSEE_RH850_CORE3_513_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_514_ISR_CAT))
#if (OSEE_RH850_CORE3_514_ISR_CAT == 1)
_osEE_rh850_core3_ei514:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_514_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei514, .-_osEE_rh850_core3_ei514
#else
_osEE_rh850_core3_ei514:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_514_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei514, .-_osEE_rh850_core3_ei514
#endif
#endif /* OSEE_RH850_CORE3_514_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_515_ISR_CAT))
#if (OSEE_RH850_CORE3_515_ISR_CAT == 1)
_osEE_rh850_core3_ei515:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_515_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei515, .-_osEE_rh850_core3_ei515
#else
_osEE_rh850_core3_ei515:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_515_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei515, .-_osEE_rh850_core3_ei515
#endif
#endif /* OSEE_RH850_CORE3_515_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_516_ISR_CAT))
#if (OSEE_RH850_CORE3_516_ISR_CAT == 1)
_osEE_rh850_core3_ei516:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_516_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei516, .-_osEE_rh850_core3_ei516
#else
_osEE_rh850_core3_ei516:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_516_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei516, .-_osEE_rh850_core3_ei516
#endif
#endif /* OSEE_RH850_CORE3_516_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_517_ISR_CAT))
#if (OSEE_RH850_CORE3_517_ISR_CAT == 1)
_osEE_rh850_core3_ei517:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_517_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei517, .-_osEE_rh850_core3_ei517
#else
_osEE_rh850_core3_ei517:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_517_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei517, .-_osEE_rh850_core3_ei517
#endif
#endif /* OSEE_RH850_CORE3_517_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_518_ISR_CAT))
#if (OSEE_RH850_CORE3_518_ISR_CAT == 1)
_osEE_rh850_core3_ei518:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_518_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei518, .-_osEE_rh850_core3_ei518
#else
_osEE_rh850_core3_ei518:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_518_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei518, .-_osEE_rh850_core3_ei518
#endif
#endif /* OSEE_RH850_CORE3_518_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_519_ISR_CAT))
#if (OSEE_RH850_CORE3_519_ISR_CAT == 1)
_osEE_rh850_core3_ei519:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_519_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei519, .-_osEE_rh850_core3_ei519
#else
_osEE_rh850_core3_ei519:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_519_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei519, .-_osEE_rh850_core3_ei519
#endif
#endif /* OSEE_RH850_CORE3_519_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_520_ISR_CAT))
#if (OSEE_RH850_CORE3_520_ISR_CAT == 1)
_osEE_rh850_core3_ei520:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_520_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei520, .-_osEE_rh850_core3_ei520
#else
_osEE_rh850_core3_ei520:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_520_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei520, .-_osEE_rh850_core3_ei520
#endif
#endif /* OSEE_RH850_CORE3_520_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_521_ISR_CAT))
#if (OSEE_RH850_CORE3_521_ISR_CAT == 1)
_osEE_rh850_core3_ei521:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_521_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei521, .-_osEE_rh850_core3_ei521
#else
_osEE_rh850_core3_ei521:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_521_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei521, .-_osEE_rh850_core3_ei521
#endif
#endif /* OSEE_RH850_CORE3_521_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_522_ISR_CAT))
#if (OSEE_RH850_CORE3_522_ISR_CAT == 1)
_osEE_rh850_core3_ei522:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_522_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei522, .-_osEE_rh850_core3_ei522
#else
_osEE_rh850_core3_ei522:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_522_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei522, .-_osEE_rh850_core3_ei522
#endif
#endif /* OSEE_RH850_CORE3_522_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_523_ISR_CAT))
#if (OSEE_RH850_CORE3_523_ISR_CAT == 1)
_osEE_rh850_core3_ei523:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_523_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei523, .-_osEE_rh850_core3_ei523
#else
_osEE_rh850_core3_ei523:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_523_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei523, .-_osEE_rh850_core3_ei523
#endif
#endif /* OSEE_RH850_CORE3_523_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_524_ISR_CAT))
#if (OSEE_RH850_CORE3_524_ISR_CAT == 1)
_osEE_rh850_core3_ei524:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_524_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei524, .-_osEE_rh850_core3_ei524
#else
_osEE_rh850_core3_ei524:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_524_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei524, .-_osEE_rh850_core3_ei524
#endif
#endif /* OSEE_RH850_CORE3_524_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_525_ISR_CAT))
#if (OSEE_RH850_CORE3_525_ISR_CAT == 1)
_osEE_rh850_core3_ei525:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_525_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei525, .-_osEE_rh850_core3_ei525
#else
_osEE_rh850_core3_ei525:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_525_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei525, .-_osEE_rh850_core3_ei525
#endif
#endif /* OSEE_RH850_CORE3_525_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_526_ISR_CAT))
#if (OSEE_RH850_CORE3_526_ISR_CAT == 1)
_osEE_rh850_core3_ei526:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_526_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei526, .-_osEE_rh850_core3_ei526
#else
_osEE_rh850_core3_ei526:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_526_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei526, .-_osEE_rh850_core3_ei526
#endif
#endif /* OSEE_RH850_CORE3_526_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_527_ISR_CAT))
#if (OSEE_RH850_CORE3_527_ISR_CAT == 1)
_osEE_rh850_core3_ei527:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_527_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei527, .-_osEE_rh850_core3_ei527
#else
_osEE_rh850_core3_ei527:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_527_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei527, .-_osEE_rh850_core3_ei527
#endif
#endif /* OSEE_RH850_CORE3_527_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_528_ISR_CAT))
#if (OSEE_RH850_CORE3_528_ISR_CAT == 1)
_osEE_rh850_core3_ei528:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_528_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei528, .-_osEE_rh850_core3_ei528
#else
_osEE_rh850_core3_ei528:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_528_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei528, .-_osEE_rh850_core3_ei528
#endif
#endif /* OSEE_RH850_CORE3_528_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_529_ISR_CAT))
#if (OSEE_RH850_CORE3_529_ISR_CAT == 1)
_osEE_rh850_core3_ei529:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_529_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei529, .-_osEE_rh850_core3_ei529
#else
_osEE_rh850_core3_ei529:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_529_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei529, .-_osEE_rh850_core3_ei529
#endif
#endif /* OSEE_RH850_CORE3_529_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_530_ISR_CAT))
#if (OSEE_RH850_CORE3_530_ISR_CAT == 1)
_osEE_rh850_core3_ei530:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_530_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei530, .-_osEE_rh850_core3_ei530
#else
_osEE_rh850_core3_ei530:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_530_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei530, .-_osEE_rh850_core3_ei530
#endif
#endif /* OSEE_RH850_CORE3_530_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_531_ISR_CAT))
#if (OSEE_RH850_CORE3_531_ISR_CAT == 1)
_osEE_rh850_core3_ei531:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_531_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei531, .-_osEE_rh850_core3_ei531
#else
_osEE_rh850_core3_ei531:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_531_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei531, .-_osEE_rh850_core3_ei531
#endif
#endif /* OSEE_RH850_CORE3_531_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_532_ISR_CAT))
#if (OSEE_RH850_CORE3_532_ISR_CAT == 1)
_osEE_rh850_core3_ei532:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_532_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei532, .-_osEE_rh850_core3_ei532
#else
_osEE_rh850_core3_ei532:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_532_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei532, .-_osEE_rh850_core3_ei532
#endif
#endif /* OSEE_RH850_CORE3_532_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_533_ISR_CAT))
#if (OSEE_RH850_CORE3_533_ISR_CAT == 1)
_osEE_rh850_core3_ei533:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_533_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei533, .-_osEE_rh850_core3_ei533
#else
_osEE_rh850_core3_ei533:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_533_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei533, .-_osEE_rh850_core3_ei533
#endif
#endif /* OSEE_RH850_CORE3_533_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_534_ISR_CAT))
#if (OSEE_RH850_CORE3_534_ISR_CAT == 1)
_osEE_rh850_core3_ei534:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_534_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei534, .-_osEE_rh850_core3_ei534
#else
_osEE_rh850_core3_ei534:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_534_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei534, .-_osEE_rh850_core3_ei534
#endif
#endif /* OSEE_RH850_CORE3_534_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_535_ISR_CAT))
#if (OSEE_RH850_CORE3_535_ISR_CAT == 1)
_osEE_rh850_core3_ei535:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_535_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei535, .-_osEE_rh850_core3_ei535
#else
_osEE_rh850_core3_ei535:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_535_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei535, .-_osEE_rh850_core3_ei535
#endif
#endif /* OSEE_RH850_CORE3_535_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_536_ISR_CAT))
#if (OSEE_RH850_CORE3_536_ISR_CAT == 1)
_osEE_rh850_core3_ei536:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_536_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei536, .-_osEE_rh850_core3_ei536
#else
_osEE_rh850_core3_ei536:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_536_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei536, .-_osEE_rh850_core3_ei536
#endif
#endif /* OSEE_RH850_CORE3_536_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_537_ISR_CAT))
#if (OSEE_RH850_CORE3_537_ISR_CAT == 1)
_osEE_rh850_core3_ei537:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_537_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei537, .-_osEE_rh850_core3_ei537
#else
_osEE_rh850_core3_ei537:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_537_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei537, .-_osEE_rh850_core3_ei537
#endif
#endif /* OSEE_RH850_CORE3_537_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_538_ISR_CAT))
#if (OSEE_RH850_CORE3_538_ISR_CAT == 1)
_osEE_rh850_core3_ei538:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_538_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei538, .-_osEE_rh850_core3_ei538
#else
_osEE_rh850_core3_ei538:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_538_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei538, .-_osEE_rh850_core3_ei538
#endif
#endif /* OSEE_RH850_CORE3_538_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_539_ISR_CAT))
#if (OSEE_RH850_CORE3_539_ISR_CAT == 1)
_osEE_rh850_core3_ei539:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_539_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei539, .-_osEE_rh850_core3_ei539
#else
_osEE_rh850_core3_ei539:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_539_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei539, .-_osEE_rh850_core3_ei539
#endif
#endif /* OSEE_RH850_CORE3_539_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_540_ISR_CAT))
#if (OSEE_RH850_CORE3_540_ISR_CAT == 1)
_osEE_rh850_core3_ei540:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_540_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei540, .-_osEE_rh850_core3_ei540
#else
_osEE_rh850_core3_ei540:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_540_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei540, .-_osEE_rh850_core3_ei540
#endif
#endif /* OSEE_RH850_CORE3_540_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_541_ISR_CAT))
#if (OSEE_RH850_CORE3_541_ISR_CAT == 1)
_osEE_rh850_core3_ei541:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_541_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei541, .-_osEE_rh850_core3_ei541
#else
_osEE_rh850_core3_ei541:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_541_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei541, .-_osEE_rh850_core3_ei541
#endif
#endif /* OSEE_RH850_CORE3_541_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_542_ISR_CAT))
#if (OSEE_RH850_CORE3_542_ISR_CAT == 1)
_osEE_rh850_core3_ei542:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_542_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei542, .-_osEE_rh850_core3_ei542
#else
_osEE_rh850_core3_ei542:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_542_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei542, .-_osEE_rh850_core3_ei542
#endif
#endif /* OSEE_RH850_CORE3_542_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_543_ISR_CAT))
#if (OSEE_RH850_CORE3_543_ISR_CAT == 1)
_osEE_rh850_core3_ei543:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_543_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei543, .-_osEE_rh850_core3_ei543
#else
_osEE_rh850_core3_ei543:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_543_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei543, .-_osEE_rh850_core3_ei543
#endif
#endif /* OSEE_RH850_CORE3_543_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_544_ISR_CAT))
#if (OSEE_RH850_CORE3_544_ISR_CAT == 1)
_osEE_rh850_core3_ei544:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_544_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei544, .-_osEE_rh850_core3_ei544
#else
_osEE_rh850_core3_ei544:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_544_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei544, .-_osEE_rh850_core3_ei544
#endif
#endif /* OSEE_RH850_CORE3_544_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_545_ISR_CAT))
#if (OSEE_RH850_CORE3_545_ISR_CAT == 1)
_osEE_rh850_core3_ei545:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_545_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei545, .-_osEE_rh850_core3_ei545
#else
_osEE_rh850_core3_ei545:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_545_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei545, .-_osEE_rh850_core3_ei545
#endif
#endif /* OSEE_RH850_CORE3_545_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_546_ISR_CAT))
#if (OSEE_RH850_CORE3_546_ISR_CAT == 1)
_osEE_rh850_core3_ei546:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_546_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei546, .-_osEE_rh850_core3_ei546
#else
_osEE_rh850_core3_ei546:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_546_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei546, .-_osEE_rh850_core3_ei546
#endif
#endif /* OSEE_RH850_CORE3_546_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_547_ISR_CAT))
#if (OSEE_RH850_CORE3_547_ISR_CAT == 1)
_osEE_rh850_core3_ei547:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_547_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei547, .-_osEE_rh850_core3_ei547
#else
_osEE_rh850_core3_ei547:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_547_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei547, .-_osEE_rh850_core3_ei547
#endif
#endif /* OSEE_RH850_CORE3_547_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_548_ISR_CAT))
#if (OSEE_RH850_CORE3_548_ISR_CAT == 1)
_osEE_rh850_core3_ei548:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_548_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei548, .-_osEE_rh850_core3_ei548
#else
_osEE_rh850_core3_ei548:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_548_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei548, .-_osEE_rh850_core3_ei548
#endif
#endif /* OSEE_RH850_CORE3_548_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_549_ISR_CAT))
#if (OSEE_RH850_CORE3_549_ISR_CAT == 1)
_osEE_rh850_core3_ei549:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_549_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei549, .-_osEE_rh850_core3_ei549
#else
_osEE_rh850_core3_ei549:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_549_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei549, .-_osEE_rh850_core3_ei549
#endif
#endif /* OSEE_RH850_CORE3_549_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_550_ISR_CAT))
#if (OSEE_RH850_CORE3_550_ISR_CAT == 1)
_osEE_rh850_core3_ei550:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_550_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei550, .-_osEE_rh850_core3_ei550
#else
_osEE_rh850_core3_ei550:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_550_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei550, .-_osEE_rh850_core3_ei550
#endif
#endif /* OSEE_RH850_CORE3_550_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_551_ISR_CAT))
#if (OSEE_RH850_CORE3_551_ISR_CAT == 1)
_osEE_rh850_core3_ei551:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_551_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei551, .-_osEE_rh850_core3_ei551
#else
_osEE_rh850_core3_ei551:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_551_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei551, .-_osEE_rh850_core3_ei551
#endif
#endif /* OSEE_RH850_CORE3_551_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_552_ISR_CAT))
#if (OSEE_RH850_CORE3_552_ISR_CAT == 1)
_osEE_rh850_core3_ei552:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_552_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei552, .-_osEE_rh850_core3_ei552
#else
_osEE_rh850_core3_ei552:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_552_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei552, .-_osEE_rh850_core3_ei552
#endif
#endif /* OSEE_RH850_CORE3_552_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_553_ISR_CAT))
#if (OSEE_RH850_CORE3_553_ISR_CAT == 1)
_osEE_rh850_core3_ei553:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_553_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei553, .-_osEE_rh850_core3_ei553
#else
_osEE_rh850_core3_ei553:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_553_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei553, .-_osEE_rh850_core3_ei553
#endif
#endif /* OSEE_RH850_CORE3_553_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_554_ISR_CAT))
#if (OSEE_RH850_CORE3_554_ISR_CAT == 1)
_osEE_rh850_core3_ei554:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_554_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei554, .-_osEE_rh850_core3_ei554
#else
_osEE_rh850_core3_ei554:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_554_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei554, .-_osEE_rh850_core3_ei554
#endif
#endif /* OSEE_RH850_CORE3_554_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_555_ISR_CAT))
#if (OSEE_RH850_CORE3_555_ISR_CAT == 1)
_osEE_rh850_core3_ei555:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_555_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei555, .-_osEE_rh850_core3_ei555
#else
_osEE_rh850_core3_ei555:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_555_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei555, .-_osEE_rh850_core3_ei555
#endif
#endif /* OSEE_RH850_CORE3_555_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_556_ISR_CAT))
#if (OSEE_RH850_CORE3_556_ISR_CAT == 1)
_osEE_rh850_core3_ei556:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_556_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei556, .-_osEE_rh850_core3_ei556
#else
_osEE_rh850_core3_ei556:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_556_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei556, .-_osEE_rh850_core3_ei556
#endif
#endif /* OSEE_RH850_CORE3_556_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_557_ISR_CAT))
#if (OSEE_RH850_CORE3_557_ISR_CAT == 1)
_osEE_rh850_core3_ei557:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_557_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei557, .-_osEE_rh850_core3_ei557
#else
_osEE_rh850_core3_ei557:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_557_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei557, .-_osEE_rh850_core3_ei557
#endif
#endif /* OSEE_RH850_CORE3_557_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_558_ISR_CAT))
#if (OSEE_RH850_CORE3_558_ISR_CAT == 1)
_osEE_rh850_core3_ei558:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_558_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei558, .-_osEE_rh850_core3_ei558
#else
_osEE_rh850_core3_ei558:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_558_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei558, .-_osEE_rh850_core3_ei558
#endif
#endif /* OSEE_RH850_CORE3_558_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_559_ISR_CAT))
#if (OSEE_RH850_CORE3_559_ISR_CAT == 1)
_osEE_rh850_core3_ei559:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_559_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei559, .-_osEE_rh850_core3_ei559
#else
_osEE_rh850_core3_ei559:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_559_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei559, .-_osEE_rh850_core3_ei559
#endif
#endif /* OSEE_RH850_CORE3_559_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_560_ISR_CAT))
#if (OSEE_RH850_CORE3_560_ISR_CAT == 1)
_osEE_rh850_core3_ei560:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_560_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei560, .-_osEE_rh850_core3_ei560
#else
_osEE_rh850_core3_ei560:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_560_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei560, .-_osEE_rh850_core3_ei560
#endif
#endif /* OSEE_RH850_CORE3_560_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_561_ISR_CAT))
#if (OSEE_RH850_CORE3_561_ISR_CAT == 1)
_osEE_rh850_core3_ei561:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_561_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei561, .-_osEE_rh850_core3_ei561
#else
_osEE_rh850_core3_ei561:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_561_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei561, .-_osEE_rh850_core3_ei561
#endif
#endif /* OSEE_RH850_CORE3_561_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_562_ISR_CAT))
#if (OSEE_RH850_CORE3_562_ISR_CAT == 1)
_osEE_rh850_core3_ei562:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_562_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei562, .-_osEE_rh850_core3_ei562
#else
_osEE_rh850_core3_ei562:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_562_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei562, .-_osEE_rh850_core3_ei562
#endif
#endif /* OSEE_RH850_CORE3_562_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_563_ISR_CAT))
#if (OSEE_RH850_CORE3_563_ISR_CAT == 1)
_osEE_rh850_core3_ei563:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_563_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei563, .-_osEE_rh850_core3_ei563
#else
_osEE_rh850_core3_ei563:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_563_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei563, .-_osEE_rh850_core3_ei563
#endif
#endif /* OSEE_RH850_CORE3_563_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_564_ISR_CAT))
#if (OSEE_RH850_CORE3_564_ISR_CAT == 1)
_osEE_rh850_core3_ei564:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_564_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei564, .-_osEE_rh850_core3_ei564
#else
_osEE_rh850_core3_ei564:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_564_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei564, .-_osEE_rh850_core3_ei564
#endif
#endif /* OSEE_RH850_CORE3_564_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_565_ISR_CAT))
#if (OSEE_RH850_CORE3_565_ISR_CAT == 1)
_osEE_rh850_core3_ei565:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_565_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei565, .-_osEE_rh850_core3_ei565
#else
_osEE_rh850_core3_ei565:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_565_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei565, .-_osEE_rh850_core3_ei565
#endif
#endif /* OSEE_RH850_CORE3_565_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_566_ISR_CAT))
#if (OSEE_RH850_CORE3_566_ISR_CAT == 1)
_osEE_rh850_core3_ei566:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_566_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei566, .-_osEE_rh850_core3_ei566
#else
_osEE_rh850_core3_ei566:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_566_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei566, .-_osEE_rh850_core3_ei566
#endif
#endif /* OSEE_RH850_CORE3_566_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_567_ISR_CAT))
#if (OSEE_RH850_CORE3_567_ISR_CAT == 1)
_osEE_rh850_core3_ei567:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_567_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei567, .-_osEE_rh850_core3_ei567
#else
_osEE_rh850_core3_ei567:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_567_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei567, .-_osEE_rh850_core3_ei567
#endif
#endif /* OSEE_RH850_CORE3_567_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_568_ISR_CAT))
#if (OSEE_RH850_CORE3_568_ISR_CAT == 1)
_osEE_rh850_core3_ei568:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_568_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei568, .-_osEE_rh850_core3_ei568
#else
_osEE_rh850_core3_ei568:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_568_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei568, .-_osEE_rh850_core3_ei568
#endif
#endif /* OSEE_RH850_CORE3_568_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_569_ISR_CAT))
#if (OSEE_RH850_CORE3_569_ISR_CAT == 1)
_osEE_rh850_core3_ei569:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_569_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei569, .-_osEE_rh850_core3_ei569
#else
_osEE_rh850_core3_ei569:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_569_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei569, .-_osEE_rh850_core3_ei569
#endif
#endif /* OSEE_RH850_CORE3_569_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_570_ISR_CAT))
#if (OSEE_RH850_CORE3_570_ISR_CAT == 1)
_osEE_rh850_core3_ei570:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_570_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei570, .-_osEE_rh850_core3_ei570
#else
_osEE_rh850_core3_ei570:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_570_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei570, .-_osEE_rh850_core3_ei570
#endif
#endif /* OSEE_RH850_CORE3_570_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_571_ISR_CAT))
#if (OSEE_RH850_CORE3_571_ISR_CAT == 1)
_osEE_rh850_core3_ei571:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_571_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei571, .-_osEE_rh850_core3_ei571
#else
_osEE_rh850_core3_ei571:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_571_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei571, .-_osEE_rh850_core3_ei571
#endif
#endif /* OSEE_RH850_CORE3_571_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_572_ISR_CAT))
#if (OSEE_RH850_CORE3_572_ISR_CAT == 1)
_osEE_rh850_core3_ei572:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_572_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei572, .-_osEE_rh850_core3_ei572
#else
_osEE_rh850_core3_ei572:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_572_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei572, .-_osEE_rh850_core3_ei572
#endif
#endif /* OSEE_RH850_CORE3_572_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_573_ISR_CAT))
#if (OSEE_RH850_CORE3_573_ISR_CAT == 1)
_osEE_rh850_core3_ei573:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_573_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei573, .-_osEE_rh850_core3_ei573
#else
_osEE_rh850_core3_ei573:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_573_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei573, .-_osEE_rh850_core3_ei573
#endif
#endif /* OSEE_RH850_CORE3_573_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_574_ISR_CAT))
#if (OSEE_RH850_CORE3_574_ISR_CAT == 1)
_osEE_rh850_core3_ei574:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_574_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei574, .-_osEE_rh850_core3_ei574
#else
_osEE_rh850_core3_ei574:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_574_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei574, .-_osEE_rh850_core3_ei574
#endif
#endif /* OSEE_RH850_CORE3_574_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_575_ISR_CAT))
#if (OSEE_RH850_CORE3_575_ISR_CAT == 1)
_osEE_rh850_core3_ei575:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_575_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei575, .-_osEE_rh850_core3_ei575
#else
_osEE_rh850_core3_ei575:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_575_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei575, .-_osEE_rh850_core3_ei575
#endif
#endif /* OSEE_RH850_CORE3_575_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_576_ISR_CAT))
#if (OSEE_RH850_CORE3_576_ISR_CAT == 1)
_osEE_rh850_core3_ei576:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_576_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei576, .-_osEE_rh850_core3_ei576
#else
_osEE_rh850_core3_ei576:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_576_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei576, .-_osEE_rh850_core3_ei576
#endif
#endif /* OSEE_RH850_CORE3_576_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_577_ISR_CAT))
#if (OSEE_RH850_CORE3_577_ISR_CAT == 1)
_osEE_rh850_core3_ei577:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_577_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei577, .-_osEE_rh850_core3_ei577
#else
_osEE_rh850_core3_ei577:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_577_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei577, .-_osEE_rh850_core3_ei577
#endif
#endif /* OSEE_RH850_CORE3_577_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_578_ISR_CAT))
#if (OSEE_RH850_CORE3_578_ISR_CAT == 1)
_osEE_rh850_core3_ei578:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_578_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei578, .-_osEE_rh850_core3_ei578
#else
_osEE_rh850_core3_ei578:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_578_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei578, .-_osEE_rh850_core3_ei578
#endif
#endif /* OSEE_RH850_CORE3_578_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_579_ISR_CAT))
#if (OSEE_RH850_CORE3_579_ISR_CAT == 1)
_osEE_rh850_core3_ei579:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_579_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei579, .-_osEE_rh850_core3_ei579
#else
_osEE_rh850_core3_ei579:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_579_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei579, .-_osEE_rh850_core3_ei579
#endif
#endif /* OSEE_RH850_CORE3_579_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_580_ISR_CAT))
#if (OSEE_RH850_CORE3_580_ISR_CAT == 1)
_osEE_rh850_core3_ei580:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_580_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei580, .-_osEE_rh850_core3_ei580
#else
_osEE_rh850_core3_ei580:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_580_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei580, .-_osEE_rh850_core3_ei580
#endif
#endif /* OSEE_RH850_CORE3_580_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_581_ISR_CAT))
#if (OSEE_RH850_CORE3_581_ISR_CAT == 1)
_osEE_rh850_core3_ei581:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_581_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei581, .-_osEE_rh850_core3_ei581
#else
_osEE_rh850_core3_ei581:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_581_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei581, .-_osEE_rh850_core3_ei581
#endif
#endif /* OSEE_RH850_CORE3_581_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_582_ISR_CAT))
#if (OSEE_RH850_CORE3_582_ISR_CAT == 1)
_osEE_rh850_core3_ei582:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_582_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei582, .-_osEE_rh850_core3_ei582
#else
_osEE_rh850_core3_ei582:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_582_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei582, .-_osEE_rh850_core3_ei582
#endif
#endif /* OSEE_RH850_CORE3_582_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_583_ISR_CAT))
#if (OSEE_RH850_CORE3_583_ISR_CAT == 1)
_osEE_rh850_core3_ei583:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_583_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei583, .-_osEE_rh850_core3_ei583
#else
_osEE_rh850_core3_ei583:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_583_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei583, .-_osEE_rh850_core3_ei583
#endif
#endif /* OSEE_RH850_CORE3_583_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_584_ISR_CAT))
#if (OSEE_RH850_CORE3_584_ISR_CAT == 1)
_osEE_rh850_core3_ei584:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_584_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei584, .-_osEE_rh850_core3_ei584
#else
_osEE_rh850_core3_ei584:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_584_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei584, .-_osEE_rh850_core3_ei584
#endif
#endif /* OSEE_RH850_CORE3_584_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_585_ISR_CAT))
#if (OSEE_RH850_CORE3_585_ISR_CAT == 1)
_osEE_rh850_core3_ei585:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_585_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei585, .-_osEE_rh850_core3_ei585
#else
_osEE_rh850_core3_ei585:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_585_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei585, .-_osEE_rh850_core3_ei585
#endif
#endif /* OSEE_RH850_CORE3_585_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_586_ISR_CAT))
#if (OSEE_RH850_CORE3_586_ISR_CAT == 1)
_osEE_rh850_core3_ei586:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_586_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei586, .-_osEE_rh850_core3_ei586
#else
_osEE_rh850_core3_ei586:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_586_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei586, .-_osEE_rh850_core3_ei586
#endif
#endif /* OSEE_RH850_CORE3_586_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_587_ISR_CAT))
#if (OSEE_RH850_CORE3_587_ISR_CAT == 1)
_osEE_rh850_core3_ei587:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_587_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei587, .-_osEE_rh850_core3_ei587
#else
_osEE_rh850_core3_ei587:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_587_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei587, .-_osEE_rh850_core3_ei587
#endif
#endif /* OSEE_RH850_CORE3_587_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_588_ISR_CAT))
#if (OSEE_RH850_CORE3_588_ISR_CAT == 1)
_osEE_rh850_core3_ei588:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_588_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei588, .-_osEE_rh850_core3_ei588
#else
_osEE_rh850_core3_ei588:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_588_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei588, .-_osEE_rh850_core3_ei588
#endif
#endif /* OSEE_RH850_CORE3_588_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_589_ISR_CAT))
#if (OSEE_RH850_CORE3_589_ISR_CAT == 1)
_osEE_rh850_core3_ei589:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_589_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei589, .-_osEE_rh850_core3_ei589
#else
_osEE_rh850_core3_ei589:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_589_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei589, .-_osEE_rh850_core3_ei589
#endif
#endif /* OSEE_RH850_CORE3_589_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_590_ISR_CAT))
#if (OSEE_RH850_CORE3_590_ISR_CAT == 1)
_osEE_rh850_core3_ei590:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_590_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei590, .-_osEE_rh850_core3_ei590
#else
_osEE_rh850_core3_ei590:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_590_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei590, .-_osEE_rh850_core3_ei590
#endif
#endif /* OSEE_RH850_CORE3_590_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_591_ISR_CAT))
#if (OSEE_RH850_CORE3_591_ISR_CAT == 1)
_osEE_rh850_core3_ei591:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_591_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei591, .-_osEE_rh850_core3_ei591
#else
_osEE_rh850_core3_ei591:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_591_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei591, .-_osEE_rh850_core3_ei591
#endif
#endif /* OSEE_RH850_CORE3_591_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_592_ISR_CAT))
#if (OSEE_RH850_CORE3_592_ISR_CAT == 1)
_osEE_rh850_core3_ei592:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_592_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei592, .-_osEE_rh850_core3_ei592
#else
_osEE_rh850_core3_ei592:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_592_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei592, .-_osEE_rh850_core3_ei592
#endif
#endif /* OSEE_RH850_CORE3_592_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_593_ISR_CAT))
#if (OSEE_RH850_CORE3_593_ISR_CAT == 1)
_osEE_rh850_core3_ei593:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_593_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei593, .-_osEE_rh850_core3_ei593
#else
_osEE_rh850_core3_ei593:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_593_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei593, .-_osEE_rh850_core3_ei593
#endif
#endif /* OSEE_RH850_CORE3_593_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_594_ISR_CAT))
#if (OSEE_RH850_CORE3_594_ISR_CAT == 1)
_osEE_rh850_core3_ei594:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_594_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei594, .-_osEE_rh850_core3_ei594
#else
_osEE_rh850_core3_ei594:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_594_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei594, .-_osEE_rh850_core3_ei594
#endif
#endif /* OSEE_RH850_CORE3_594_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_595_ISR_CAT))
#if (OSEE_RH850_CORE3_595_ISR_CAT == 1)
_osEE_rh850_core3_ei595:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_595_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei595, .-_osEE_rh850_core3_ei595
#else
_osEE_rh850_core3_ei595:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_595_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei595, .-_osEE_rh850_core3_ei595
#endif
#endif /* OSEE_RH850_CORE3_595_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_596_ISR_CAT))
#if (OSEE_RH850_CORE3_596_ISR_CAT == 1)
_osEE_rh850_core3_ei596:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_596_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei596, .-_osEE_rh850_core3_ei596
#else
_osEE_rh850_core3_ei596:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_596_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei596, .-_osEE_rh850_core3_ei596
#endif
#endif /* OSEE_RH850_CORE3_596_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_597_ISR_CAT))
#if (OSEE_RH850_CORE3_597_ISR_CAT == 1)
_osEE_rh850_core3_ei597:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_597_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei597, .-_osEE_rh850_core3_ei597
#else
_osEE_rh850_core3_ei597:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_597_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei597, .-_osEE_rh850_core3_ei597
#endif
#endif /* OSEE_RH850_CORE3_597_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_598_ISR_CAT))
#if (OSEE_RH850_CORE3_598_ISR_CAT == 1)
_osEE_rh850_core3_ei598:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_598_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei598, .-_osEE_rh850_core3_ei598
#else
_osEE_rh850_core3_ei598:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_598_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei598, .-_osEE_rh850_core3_ei598
#endif
#endif /* OSEE_RH850_CORE3_598_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_599_ISR_CAT))
#if (OSEE_RH850_CORE3_599_ISR_CAT == 1)
_osEE_rh850_core3_ei599:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_599_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei599, .-_osEE_rh850_core3_ei599
#else
_osEE_rh850_core3_ei599:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_599_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei599, .-_osEE_rh850_core3_ei599
#endif
#endif /* OSEE_RH850_CORE3_599_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_600_ISR_CAT))
#if (OSEE_RH850_CORE3_600_ISR_CAT == 1)
_osEE_rh850_core3_ei600:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_600_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei600, .-_osEE_rh850_core3_ei600
#else
_osEE_rh850_core3_ei600:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_600_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei600, .-_osEE_rh850_core3_ei600
#endif
#endif /* OSEE_RH850_CORE3_600_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_601_ISR_CAT))
#if (OSEE_RH850_CORE3_601_ISR_CAT == 1)
_osEE_rh850_core3_ei601:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_601_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei601, .-_osEE_rh850_core3_ei601
#else
_osEE_rh850_core3_ei601:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_601_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei601, .-_osEE_rh850_core3_ei601
#endif
#endif /* OSEE_RH850_CORE3_601_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_602_ISR_CAT))
#if (OSEE_RH850_CORE3_602_ISR_CAT == 1)
_osEE_rh850_core3_ei602:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_602_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei602, .-_osEE_rh850_core3_ei602
#else
_osEE_rh850_core3_ei602:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_602_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei602, .-_osEE_rh850_core3_ei602
#endif
#endif /* OSEE_RH850_CORE3_602_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_603_ISR_CAT))
#if (OSEE_RH850_CORE3_603_ISR_CAT == 1)
_osEE_rh850_core3_ei603:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_603_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei603, .-_osEE_rh850_core3_ei603
#else
_osEE_rh850_core3_ei603:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_603_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei603, .-_osEE_rh850_core3_ei603
#endif
#endif /* OSEE_RH850_CORE3_603_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_604_ISR_CAT))
#if (OSEE_RH850_CORE3_604_ISR_CAT == 1)
_osEE_rh850_core3_ei604:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_604_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei604, .-_osEE_rh850_core3_ei604
#else
_osEE_rh850_core3_ei604:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_604_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei604, .-_osEE_rh850_core3_ei604
#endif
#endif /* OSEE_RH850_CORE3_604_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_605_ISR_CAT))
#if (OSEE_RH850_CORE3_605_ISR_CAT == 1)
_osEE_rh850_core3_ei605:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_605_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei605, .-_osEE_rh850_core3_ei605
#else
_osEE_rh850_core3_ei605:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_605_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei605, .-_osEE_rh850_core3_ei605
#endif
#endif /* OSEE_RH850_CORE3_605_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_606_ISR_CAT))
#if (OSEE_RH850_CORE3_606_ISR_CAT == 1)
_osEE_rh850_core3_ei606:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_606_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei606, .-_osEE_rh850_core3_ei606
#else
_osEE_rh850_core3_ei606:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_606_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei606, .-_osEE_rh850_core3_ei606
#endif
#endif /* OSEE_RH850_CORE3_606_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_607_ISR_CAT))
#if (OSEE_RH850_CORE3_607_ISR_CAT == 1)
_osEE_rh850_core3_ei607:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_607_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei607, .-_osEE_rh850_core3_ei607
#else
_osEE_rh850_core3_ei607:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_607_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei607, .-_osEE_rh850_core3_ei607
#endif
#endif /* OSEE_RH850_CORE3_607_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_608_ISR_CAT))
#if (OSEE_RH850_CORE3_608_ISR_CAT == 1)
_osEE_rh850_core3_ei608:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_608_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei608, .-_osEE_rh850_core3_ei608
#else
_osEE_rh850_core3_ei608:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_608_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei608, .-_osEE_rh850_core3_ei608
#endif
#endif /* OSEE_RH850_CORE3_608_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_609_ISR_CAT))
#if (OSEE_RH850_CORE3_609_ISR_CAT == 1)
_osEE_rh850_core3_ei609:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_609_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei609, .-_osEE_rh850_core3_ei609
#else
_osEE_rh850_core3_ei609:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_609_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei609, .-_osEE_rh850_core3_ei609
#endif
#endif /* OSEE_RH850_CORE3_609_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_610_ISR_CAT))
#if (OSEE_RH850_CORE3_610_ISR_CAT == 1)
_osEE_rh850_core3_ei610:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_610_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei610, .-_osEE_rh850_core3_ei610
#else
_osEE_rh850_core3_ei610:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_610_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei610, .-_osEE_rh850_core3_ei610
#endif
#endif /* OSEE_RH850_CORE3_610_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_611_ISR_CAT))
#if (OSEE_RH850_CORE3_611_ISR_CAT == 1)
_osEE_rh850_core3_ei611:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_611_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei611, .-_osEE_rh850_core3_ei611
#else
_osEE_rh850_core3_ei611:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_611_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei611, .-_osEE_rh850_core3_ei611
#endif
#endif /* OSEE_RH850_CORE3_611_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_612_ISR_CAT))
#if (OSEE_RH850_CORE3_612_ISR_CAT == 1)
_osEE_rh850_core3_ei612:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_612_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei612, .-_osEE_rh850_core3_ei612
#else
_osEE_rh850_core3_ei612:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_612_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei612, .-_osEE_rh850_core3_ei612
#endif
#endif /* OSEE_RH850_CORE3_612_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_613_ISR_CAT))
#if (OSEE_RH850_CORE3_613_ISR_CAT == 1)
_osEE_rh850_core3_ei613:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_613_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei613, .-_osEE_rh850_core3_ei613
#else
_osEE_rh850_core3_ei613:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_613_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei613, .-_osEE_rh850_core3_ei613
#endif
#endif /* OSEE_RH850_CORE3_613_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_614_ISR_CAT))
#if (OSEE_RH850_CORE3_614_ISR_CAT == 1)
_osEE_rh850_core3_ei614:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_614_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei614, .-_osEE_rh850_core3_ei614
#else
_osEE_rh850_core3_ei614:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_614_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei614, .-_osEE_rh850_core3_ei614
#endif
#endif /* OSEE_RH850_CORE3_614_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_615_ISR_CAT))
#if (OSEE_RH850_CORE3_615_ISR_CAT == 1)
_osEE_rh850_core3_ei615:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_615_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei615, .-_osEE_rh850_core3_ei615
#else
_osEE_rh850_core3_ei615:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_615_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei615, .-_osEE_rh850_core3_ei615
#endif
#endif /* OSEE_RH850_CORE3_615_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_616_ISR_CAT))
#if (OSEE_RH850_CORE3_616_ISR_CAT == 1)
_osEE_rh850_core3_ei616:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_616_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei616, .-_osEE_rh850_core3_ei616
#else
_osEE_rh850_core3_ei616:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_616_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei616, .-_osEE_rh850_core3_ei616
#endif
#endif /* OSEE_RH850_CORE3_616_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_617_ISR_CAT))
#if (OSEE_RH850_CORE3_617_ISR_CAT == 1)
_osEE_rh850_core3_ei617:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_617_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei617, .-_osEE_rh850_core3_ei617
#else
_osEE_rh850_core3_ei617:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_617_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei617, .-_osEE_rh850_core3_ei617
#endif
#endif /* OSEE_RH850_CORE3_617_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_618_ISR_CAT))
#if (OSEE_RH850_CORE3_618_ISR_CAT == 1)
_osEE_rh850_core3_ei618:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_618_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei618, .-_osEE_rh850_core3_ei618
#else
_osEE_rh850_core3_ei618:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_618_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei618, .-_osEE_rh850_core3_ei618
#endif
#endif /* OSEE_RH850_CORE3_618_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_619_ISR_CAT))
#if (OSEE_RH850_CORE3_619_ISR_CAT == 1)
_osEE_rh850_core3_ei619:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_619_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei619, .-_osEE_rh850_core3_ei619
#else
_osEE_rh850_core3_ei619:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_619_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei619, .-_osEE_rh850_core3_ei619
#endif
#endif /* OSEE_RH850_CORE3_619_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_620_ISR_CAT))
#if (OSEE_RH850_CORE3_620_ISR_CAT == 1)
_osEE_rh850_core3_ei620:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_620_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei620, .-_osEE_rh850_core3_ei620
#else
_osEE_rh850_core3_ei620:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_620_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei620, .-_osEE_rh850_core3_ei620
#endif
#endif /* OSEE_RH850_CORE3_620_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_621_ISR_CAT))
#if (OSEE_RH850_CORE3_621_ISR_CAT == 1)
_osEE_rh850_core3_ei621:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_621_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei621, .-_osEE_rh850_core3_ei621
#else
_osEE_rh850_core3_ei621:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_621_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei621, .-_osEE_rh850_core3_ei621
#endif
#endif /* OSEE_RH850_CORE3_621_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_622_ISR_CAT))
#if (OSEE_RH850_CORE3_622_ISR_CAT == 1)
_osEE_rh850_core3_ei622:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_622_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei622, .-_osEE_rh850_core3_ei622
#else
_osEE_rh850_core3_ei622:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_622_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei622, .-_osEE_rh850_core3_ei622
#endif
#endif /* OSEE_RH850_CORE3_622_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_623_ISR_CAT))
#if (OSEE_RH850_CORE3_623_ISR_CAT == 1)
_osEE_rh850_core3_ei623:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_623_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei623, .-_osEE_rh850_core3_ei623
#else
_osEE_rh850_core3_ei623:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_623_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei623, .-_osEE_rh850_core3_ei623
#endif
#endif /* OSEE_RH850_CORE3_623_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_624_ISR_CAT))
#if (OSEE_RH850_CORE3_624_ISR_CAT == 1)
_osEE_rh850_core3_ei624:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_624_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei624, .-_osEE_rh850_core3_ei624
#else
_osEE_rh850_core3_ei624:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_624_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei624, .-_osEE_rh850_core3_ei624
#endif
#endif /* OSEE_RH850_CORE3_624_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_625_ISR_CAT))
#if (OSEE_RH850_CORE3_625_ISR_CAT == 1)
_osEE_rh850_core3_ei625:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_625_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei625, .-_osEE_rh850_core3_ei625
#else
_osEE_rh850_core3_ei625:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_625_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei625, .-_osEE_rh850_core3_ei625
#endif
#endif /* OSEE_RH850_CORE3_625_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_626_ISR_CAT))
#if (OSEE_RH850_CORE3_626_ISR_CAT == 1)
_osEE_rh850_core3_ei626:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_626_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei626, .-_osEE_rh850_core3_ei626
#else
_osEE_rh850_core3_ei626:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_626_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei626, .-_osEE_rh850_core3_ei626
#endif
#endif /* OSEE_RH850_CORE3_626_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_627_ISR_CAT))
#if (OSEE_RH850_CORE3_627_ISR_CAT == 1)
_osEE_rh850_core3_ei627:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_627_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei627, .-_osEE_rh850_core3_ei627
#else
_osEE_rh850_core3_ei627:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_627_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei627, .-_osEE_rh850_core3_ei627
#endif
#endif /* OSEE_RH850_CORE3_627_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_628_ISR_CAT))
#if (OSEE_RH850_CORE3_628_ISR_CAT == 1)
_osEE_rh850_core3_ei628:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_628_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei628, .-_osEE_rh850_core3_ei628
#else
_osEE_rh850_core3_ei628:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_628_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei628, .-_osEE_rh850_core3_ei628
#endif
#endif /* OSEE_RH850_CORE3_628_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_629_ISR_CAT))
#if (OSEE_RH850_CORE3_629_ISR_CAT == 1)
_osEE_rh850_core3_ei629:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_629_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei629, .-_osEE_rh850_core3_ei629
#else
_osEE_rh850_core3_ei629:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_629_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei629, .-_osEE_rh850_core3_ei629
#endif
#endif /* OSEE_RH850_CORE3_629_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_630_ISR_CAT))
#if (OSEE_RH850_CORE3_630_ISR_CAT == 1)
_osEE_rh850_core3_ei630:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_630_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei630, .-_osEE_rh850_core3_ei630
#else
_osEE_rh850_core3_ei630:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_630_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei630, .-_osEE_rh850_core3_ei630
#endif
#endif /* OSEE_RH850_CORE3_630_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_631_ISR_CAT))
#if (OSEE_RH850_CORE3_631_ISR_CAT == 1)
_osEE_rh850_core3_ei631:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_631_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei631, .-_osEE_rh850_core3_ei631
#else
_osEE_rh850_core3_ei631:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_631_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei631, .-_osEE_rh850_core3_ei631
#endif
#endif /* OSEE_RH850_CORE3_631_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_632_ISR_CAT))
#if (OSEE_RH850_CORE3_632_ISR_CAT == 1)
_osEE_rh850_core3_ei632:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_632_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei632, .-_osEE_rh850_core3_ei632
#else
_osEE_rh850_core3_ei632:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_632_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei632, .-_osEE_rh850_core3_ei632
#endif
#endif /* OSEE_RH850_CORE3_632_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_633_ISR_CAT))
#if (OSEE_RH850_CORE3_633_ISR_CAT == 1)
_osEE_rh850_core3_ei633:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_633_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei633, .-_osEE_rh850_core3_ei633
#else
_osEE_rh850_core3_ei633:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_633_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei633, .-_osEE_rh850_core3_ei633
#endif
#endif /* OSEE_RH850_CORE3_633_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_634_ISR_CAT))
#if (OSEE_RH850_CORE3_634_ISR_CAT == 1)
_osEE_rh850_core3_ei634:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_634_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei634, .-_osEE_rh850_core3_ei634
#else
_osEE_rh850_core3_ei634:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_634_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei634, .-_osEE_rh850_core3_ei634
#endif
#endif /* OSEE_RH850_CORE3_634_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_635_ISR_CAT))
#if (OSEE_RH850_CORE3_635_ISR_CAT == 1)
_osEE_rh850_core3_ei635:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_635_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei635, .-_osEE_rh850_core3_ei635
#else
_osEE_rh850_core3_ei635:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_635_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei635, .-_osEE_rh850_core3_ei635
#endif
#endif /* OSEE_RH850_CORE3_635_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_636_ISR_CAT))
#if (OSEE_RH850_CORE3_636_ISR_CAT == 1)
_osEE_rh850_core3_ei636:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_636_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei636, .-_osEE_rh850_core3_ei636
#else
_osEE_rh850_core3_ei636:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_636_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei636, .-_osEE_rh850_core3_ei636
#endif
#endif /* OSEE_RH850_CORE3_636_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_637_ISR_CAT))
#if (OSEE_RH850_CORE3_637_ISR_CAT == 1)
_osEE_rh850_core3_ei637:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_637_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei637, .-_osEE_rh850_core3_ei637
#else
_osEE_rh850_core3_ei637:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_637_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei637, .-_osEE_rh850_core3_ei637
#endif
#endif /* OSEE_RH850_CORE3_637_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_638_ISR_CAT))
#if (OSEE_RH850_CORE3_638_ISR_CAT == 1)
_osEE_rh850_core3_ei638:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_638_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei638, .-_osEE_rh850_core3_ei638
#else
_osEE_rh850_core3_ei638:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_638_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei638, .-_osEE_rh850_core3_ei638
#endif
#endif /* OSEE_RH850_CORE3_638_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_639_ISR_CAT))
#if (OSEE_RH850_CORE3_639_ISR_CAT == 1)
_osEE_rh850_core3_ei639:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_639_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei639, .-_osEE_rh850_core3_ei639
#else
_osEE_rh850_core3_ei639:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_639_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei639, .-_osEE_rh850_core3_ei639
#endif
#endif /* OSEE_RH850_CORE3_639_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_640_ISR_CAT))
#if (OSEE_RH850_CORE3_640_ISR_CAT == 1)
_osEE_rh850_core3_ei640:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_640_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei640, .-_osEE_rh850_core3_ei640
#else
_osEE_rh850_core3_ei640:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_640_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei640, .-_osEE_rh850_core3_ei640
#endif
#endif /* OSEE_RH850_CORE3_640_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_641_ISR_CAT))
#if (OSEE_RH850_CORE3_641_ISR_CAT == 1)
_osEE_rh850_core3_ei641:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_641_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei641, .-_osEE_rh850_core3_ei641
#else
_osEE_rh850_core3_ei641:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_641_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei641, .-_osEE_rh850_core3_ei641
#endif
#endif /* OSEE_RH850_CORE3_641_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_642_ISR_CAT))
#if (OSEE_RH850_CORE3_642_ISR_CAT == 1)
_osEE_rh850_core3_ei642:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_642_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei642, .-_osEE_rh850_core3_ei642
#else
_osEE_rh850_core3_ei642:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_642_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei642, .-_osEE_rh850_core3_ei642
#endif
#endif /* OSEE_RH850_CORE3_642_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_643_ISR_CAT))
#if (OSEE_RH850_CORE3_643_ISR_CAT == 1)
_osEE_rh850_core3_ei643:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_643_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei643, .-_osEE_rh850_core3_ei643
#else
_osEE_rh850_core3_ei643:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_643_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei643, .-_osEE_rh850_core3_ei643
#endif
#endif /* OSEE_RH850_CORE3_643_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_644_ISR_CAT))
#if (OSEE_RH850_CORE3_644_ISR_CAT == 1)
_osEE_rh850_core3_ei644:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_644_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei644, .-_osEE_rh850_core3_ei644
#else
_osEE_rh850_core3_ei644:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_644_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei644, .-_osEE_rh850_core3_ei644
#endif
#endif /* OSEE_RH850_CORE3_644_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_645_ISR_CAT))
#if (OSEE_RH850_CORE3_645_ISR_CAT == 1)
_osEE_rh850_core3_ei645:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_645_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei645, .-_osEE_rh850_core3_ei645
#else
_osEE_rh850_core3_ei645:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_645_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei645, .-_osEE_rh850_core3_ei645
#endif
#endif /* OSEE_RH850_CORE3_645_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_646_ISR_CAT))
#if (OSEE_RH850_CORE3_646_ISR_CAT == 1)
_osEE_rh850_core3_ei646:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_646_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei646, .-_osEE_rh850_core3_ei646
#else
_osEE_rh850_core3_ei646:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_646_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei646, .-_osEE_rh850_core3_ei646
#endif
#endif /* OSEE_RH850_CORE3_646_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_647_ISR_CAT))
#if (OSEE_RH850_CORE3_647_ISR_CAT == 1)
_osEE_rh850_core3_ei647:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_647_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei647, .-_osEE_rh850_core3_ei647
#else
_osEE_rh850_core3_ei647:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_647_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei647, .-_osEE_rh850_core3_ei647
#endif
#endif /* OSEE_RH850_CORE3_647_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_648_ISR_CAT))
#if (OSEE_RH850_CORE3_648_ISR_CAT == 1)
_osEE_rh850_core3_ei648:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_648_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei648, .-_osEE_rh850_core3_ei648
#else
_osEE_rh850_core3_ei648:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_648_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei648, .-_osEE_rh850_core3_ei648
#endif
#endif /* OSEE_RH850_CORE3_648_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_649_ISR_CAT))
#if (OSEE_RH850_CORE3_649_ISR_CAT == 1)
_osEE_rh850_core3_ei649:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_649_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei649, .-_osEE_rh850_core3_ei649
#else
_osEE_rh850_core3_ei649:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_649_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei649, .-_osEE_rh850_core3_ei649
#endif
#endif /* OSEE_RH850_CORE3_649_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_650_ISR_CAT))
#if (OSEE_RH850_CORE3_650_ISR_CAT == 1)
_osEE_rh850_core3_ei650:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_650_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei650, .-_osEE_rh850_core3_ei650
#else
_osEE_rh850_core3_ei650:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_650_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei650, .-_osEE_rh850_core3_ei650
#endif
#endif /* OSEE_RH850_CORE3_650_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_651_ISR_CAT))
#if (OSEE_RH850_CORE3_651_ISR_CAT == 1)
_osEE_rh850_core3_ei651:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_651_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei651, .-_osEE_rh850_core3_ei651
#else
_osEE_rh850_core3_ei651:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_651_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei651, .-_osEE_rh850_core3_ei651
#endif
#endif /* OSEE_RH850_CORE3_651_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_652_ISR_CAT))
#if (OSEE_RH850_CORE3_652_ISR_CAT == 1)
_osEE_rh850_core3_ei652:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_652_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei652, .-_osEE_rh850_core3_ei652
#else
_osEE_rh850_core3_ei652:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_652_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei652, .-_osEE_rh850_core3_ei652
#endif
#endif /* OSEE_RH850_CORE3_652_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_653_ISR_CAT))
#if (OSEE_RH850_CORE3_653_ISR_CAT == 1)
_osEE_rh850_core3_ei653:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_653_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei653, .-_osEE_rh850_core3_ei653
#else
_osEE_rh850_core3_ei653:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_653_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei653, .-_osEE_rh850_core3_ei653
#endif
#endif /* OSEE_RH850_CORE3_653_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_654_ISR_CAT))
#if (OSEE_RH850_CORE3_654_ISR_CAT == 1)
_osEE_rh850_core3_ei654:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_654_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei654, .-_osEE_rh850_core3_ei654
#else
_osEE_rh850_core3_ei654:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_654_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei654, .-_osEE_rh850_core3_ei654
#endif
#endif /* OSEE_RH850_CORE3_654_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_655_ISR_CAT))
#if (OSEE_RH850_CORE3_655_ISR_CAT == 1)
_osEE_rh850_core3_ei655:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_655_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei655, .-_osEE_rh850_core3_ei655
#else
_osEE_rh850_core3_ei655:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_655_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei655, .-_osEE_rh850_core3_ei655
#endif
#endif /* OSEE_RH850_CORE3_655_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_656_ISR_CAT))
#if (OSEE_RH850_CORE3_656_ISR_CAT == 1)
_osEE_rh850_core3_ei656:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_656_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei656, .-_osEE_rh850_core3_ei656
#else
_osEE_rh850_core3_ei656:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_656_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei656, .-_osEE_rh850_core3_ei656
#endif
#endif /* OSEE_RH850_CORE3_656_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_657_ISR_CAT))
#if (OSEE_RH850_CORE3_657_ISR_CAT == 1)
_osEE_rh850_core3_ei657:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_657_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei657, .-_osEE_rh850_core3_ei657
#else
_osEE_rh850_core3_ei657:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_657_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei657, .-_osEE_rh850_core3_ei657
#endif
#endif /* OSEE_RH850_CORE3_657_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_658_ISR_CAT))
#if (OSEE_RH850_CORE3_658_ISR_CAT == 1)
_osEE_rh850_core3_ei658:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_658_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei658, .-_osEE_rh850_core3_ei658
#else
_osEE_rh850_core3_ei658:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_658_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei658, .-_osEE_rh850_core3_ei658
#endif
#endif /* OSEE_RH850_CORE3_658_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_659_ISR_CAT))
#if (OSEE_RH850_CORE3_659_ISR_CAT == 1)
_osEE_rh850_core3_ei659:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_659_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei659, .-_osEE_rh850_core3_ei659
#else
_osEE_rh850_core3_ei659:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_659_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei659, .-_osEE_rh850_core3_ei659
#endif
#endif /* OSEE_RH850_CORE3_659_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_660_ISR_CAT))
#if (OSEE_RH850_CORE3_660_ISR_CAT == 1)
_osEE_rh850_core3_ei660:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_660_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei660, .-_osEE_rh850_core3_ei660
#else
_osEE_rh850_core3_ei660:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_660_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei660, .-_osEE_rh850_core3_ei660
#endif
#endif /* OSEE_RH850_CORE3_660_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_661_ISR_CAT))
#if (OSEE_RH850_CORE3_661_ISR_CAT == 1)
_osEE_rh850_core3_ei661:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_661_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei661, .-_osEE_rh850_core3_ei661
#else
_osEE_rh850_core3_ei661:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_661_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei661, .-_osEE_rh850_core3_ei661
#endif
#endif /* OSEE_RH850_CORE3_661_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_662_ISR_CAT))
#if (OSEE_RH850_CORE3_662_ISR_CAT == 1)
_osEE_rh850_core3_ei662:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_662_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei662, .-_osEE_rh850_core3_ei662
#else
_osEE_rh850_core3_ei662:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_662_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei662, .-_osEE_rh850_core3_ei662
#endif
#endif /* OSEE_RH850_CORE3_662_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_663_ISR_CAT))
#if (OSEE_RH850_CORE3_663_ISR_CAT == 1)
_osEE_rh850_core3_ei663:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_663_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei663, .-_osEE_rh850_core3_ei663
#else
_osEE_rh850_core3_ei663:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_663_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei663, .-_osEE_rh850_core3_ei663
#endif
#endif /* OSEE_RH850_CORE3_663_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_664_ISR_CAT))
#if (OSEE_RH850_CORE3_664_ISR_CAT == 1)
_osEE_rh850_core3_ei664:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_664_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei664, .-_osEE_rh850_core3_ei664
#else
_osEE_rh850_core3_ei664:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_664_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei664, .-_osEE_rh850_core3_ei664
#endif
#endif /* OSEE_RH850_CORE3_664_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_665_ISR_CAT))
#if (OSEE_RH850_CORE3_665_ISR_CAT == 1)
_osEE_rh850_core3_ei665:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_665_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei665, .-_osEE_rh850_core3_ei665
#else
_osEE_rh850_core3_ei665:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_665_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei665, .-_osEE_rh850_core3_ei665
#endif
#endif /* OSEE_RH850_CORE3_665_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_666_ISR_CAT))
#if (OSEE_RH850_CORE3_666_ISR_CAT == 1)
_osEE_rh850_core3_ei666:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_666_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei666, .-_osEE_rh850_core3_ei666
#else
_osEE_rh850_core3_ei666:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_666_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei666, .-_osEE_rh850_core3_ei666
#endif
#endif /* OSEE_RH850_CORE3_666_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_667_ISR_CAT))
#if (OSEE_RH850_CORE3_667_ISR_CAT == 1)
_osEE_rh850_core3_ei667:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_667_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei667, .-_osEE_rh850_core3_ei667
#else
_osEE_rh850_core3_ei667:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_667_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei667, .-_osEE_rh850_core3_ei667
#endif
#endif /* OSEE_RH850_CORE3_667_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_668_ISR_CAT))
#if (OSEE_RH850_CORE3_668_ISR_CAT == 1)
_osEE_rh850_core3_ei668:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_668_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei668, .-_osEE_rh850_core3_ei668
#else
_osEE_rh850_core3_ei668:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_668_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei668, .-_osEE_rh850_core3_ei668
#endif
#endif /* OSEE_RH850_CORE3_668_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_669_ISR_CAT))
#if (OSEE_RH850_CORE3_669_ISR_CAT == 1)
_osEE_rh850_core3_ei669:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_669_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei669, .-_osEE_rh850_core3_ei669
#else
_osEE_rh850_core3_ei669:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_669_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei669, .-_osEE_rh850_core3_ei669
#endif
#endif /* OSEE_RH850_CORE3_669_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_670_ISR_CAT))
#if (OSEE_RH850_CORE3_670_ISR_CAT == 1)
_osEE_rh850_core3_ei670:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_670_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei670, .-_osEE_rh850_core3_ei670
#else
_osEE_rh850_core3_ei670:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_670_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei670, .-_osEE_rh850_core3_ei670
#endif
#endif /* OSEE_RH850_CORE3_670_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_671_ISR_CAT))
#if (OSEE_RH850_CORE3_671_ISR_CAT == 1)
_osEE_rh850_core3_ei671:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_671_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei671, .-_osEE_rh850_core3_ei671
#else
_osEE_rh850_core3_ei671:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_671_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei671, .-_osEE_rh850_core3_ei671
#endif
#endif /* OSEE_RH850_CORE3_671_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_672_ISR_CAT))
#if (OSEE_RH850_CORE3_672_ISR_CAT == 1)
_osEE_rh850_core3_ei672:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_672_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei672, .-_osEE_rh850_core3_ei672
#else
_osEE_rh850_core3_ei672:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_672_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei672, .-_osEE_rh850_core3_ei672
#endif
#endif /* OSEE_RH850_CORE3_672_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_673_ISR_CAT))
#if (OSEE_RH850_CORE3_673_ISR_CAT == 1)
_osEE_rh850_core3_ei673:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_673_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei673, .-_osEE_rh850_core3_ei673
#else
_osEE_rh850_core3_ei673:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_673_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei673, .-_osEE_rh850_core3_ei673
#endif
#endif /* OSEE_RH850_CORE3_673_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_674_ISR_CAT))
#if (OSEE_RH850_CORE3_674_ISR_CAT == 1)
_osEE_rh850_core3_ei674:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_674_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei674, .-_osEE_rh850_core3_ei674
#else
_osEE_rh850_core3_ei674:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_674_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei674, .-_osEE_rh850_core3_ei674
#endif
#endif /* OSEE_RH850_CORE3_674_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_675_ISR_CAT))
#if (OSEE_RH850_CORE3_675_ISR_CAT == 1)
_osEE_rh850_core3_ei675:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_675_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei675, .-_osEE_rh850_core3_ei675
#else
_osEE_rh850_core3_ei675:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_675_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei675, .-_osEE_rh850_core3_ei675
#endif
#endif /* OSEE_RH850_CORE3_675_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_676_ISR_CAT))
#if (OSEE_RH850_CORE3_676_ISR_CAT == 1)
_osEE_rh850_core3_ei676:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_676_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei676, .-_osEE_rh850_core3_ei676
#else
_osEE_rh850_core3_ei676:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_676_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei676, .-_osEE_rh850_core3_ei676
#endif
#endif /* OSEE_RH850_CORE3_676_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_677_ISR_CAT))
#if (OSEE_RH850_CORE3_677_ISR_CAT == 1)
_osEE_rh850_core3_ei677:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_677_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei677, .-_osEE_rh850_core3_ei677
#else
_osEE_rh850_core3_ei677:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_677_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei677, .-_osEE_rh850_core3_ei677
#endif
#endif /* OSEE_RH850_CORE3_677_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_678_ISR_CAT))
#if (OSEE_RH850_CORE3_678_ISR_CAT == 1)
_osEE_rh850_core3_ei678:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_678_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei678, .-_osEE_rh850_core3_ei678
#else
_osEE_rh850_core3_ei678:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_678_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei678, .-_osEE_rh850_core3_ei678
#endif
#endif /* OSEE_RH850_CORE3_678_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_679_ISR_CAT))
#if (OSEE_RH850_CORE3_679_ISR_CAT == 1)
_osEE_rh850_core3_ei679:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_679_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei679, .-_osEE_rh850_core3_ei679
#else
_osEE_rh850_core3_ei679:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_679_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei679, .-_osEE_rh850_core3_ei679
#endif
#endif /* OSEE_RH850_CORE3_679_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_680_ISR_CAT))
#if (OSEE_RH850_CORE3_680_ISR_CAT == 1)
_osEE_rh850_core3_ei680:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_680_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei680, .-_osEE_rh850_core3_ei680
#else
_osEE_rh850_core3_ei680:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_680_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei680, .-_osEE_rh850_core3_ei680
#endif
#endif /* OSEE_RH850_CORE3_680_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_681_ISR_CAT))
#if (OSEE_RH850_CORE3_681_ISR_CAT == 1)
_osEE_rh850_core3_ei681:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_681_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei681, .-_osEE_rh850_core3_ei681
#else
_osEE_rh850_core3_ei681:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_681_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei681, .-_osEE_rh850_core3_ei681
#endif
#endif /* OSEE_RH850_CORE3_681_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_682_ISR_CAT))
#if (OSEE_RH850_CORE3_682_ISR_CAT == 1)
_osEE_rh850_core3_ei682:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_682_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei682, .-_osEE_rh850_core3_ei682
#else
_osEE_rh850_core3_ei682:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_682_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei682, .-_osEE_rh850_core3_ei682
#endif
#endif /* OSEE_RH850_CORE3_682_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_683_ISR_CAT))
#if (OSEE_RH850_CORE3_683_ISR_CAT == 1)
_osEE_rh850_core3_ei683:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_683_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei683, .-_osEE_rh850_core3_ei683
#else
_osEE_rh850_core3_ei683:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_683_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei683, .-_osEE_rh850_core3_ei683
#endif
#endif /* OSEE_RH850_CORE3_683_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_684_ISR_CAT))
#if (OSEE_RH850_CORE3_684_ISR_CAT == 1)
_osEE_rh850_core3_ei684:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_684_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei684, .-_osEE_rh850_core3_ei684
#else
_osEE_rh850_core3_ei684:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_684_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei684, .-_osEE_rh850_core3_ei684
#endif
#endif /* OSEE_RH850_CORE3_684_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_685_ISR_CAT))
#if (OSEE_RH850_CORE3_685_ISR_CAT == 1)
_osEE_rh850_core3_ei685:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_685_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei685, .-_osEE_rh850_core3_ei685
#else
_osEE_rh850_core3_ei685:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_685_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei685, .-_osEE_rh850_core3_ei685
#endif
#endif /* OSEE_RH850_CORE3_685_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_686_ISR_CAT))
#if (OSEE_RH850_CORE3_686_ISR_CAT == 1)
_osEE_rh850_core3_ei686:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_686_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei686, .-_osEE_rh850_core3_ei686
#else
_osEE_rh850_core3_ei686:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_686_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei686, .-_osEE_rh850_core3_ei686
#endif
#endif /* OSEE_RH850_CORE3_686_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_687_ISR_CAT))
#if (OSEE_RH850_CORE3_687_ISR_CAT == 1)
_osEE_rh850_core3_ei687:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_687_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei687, .-_osEE_rh850_core3_ei687
#else
_osEE_rh850_core3_ei687:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_687_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei687, .-_osEE_rh850_core3_ei687
#endif
#endif /* OSEE_RH850_CORE3_687_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_688_ISR_CAT))
#if (OSEE_RH850_CORE3_688_ISR_CAT == 1)
_osEE_rh850_core3_ei688:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_688_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei688, .-_osEE_rh850_core3_ei688
#else
_osEE_rh850_core3_ei688:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_688_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei688, .-_osEE_rh850_core3_ei688
#endif
#endif /* OSEE_RH850_CORE3_688_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_689_ISR_CAT))
#if (OSEE_RH850_CORE3_689_ISR_CAT == 1)
_osEE_rh850_core3_ei689:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_689_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei689, .-_osEE_rh850_core3_ei689
#else
_osEE_rh850_core3_ei689:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_689_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei689, .-_osEE_rh850_core3_ei689
#endif
#endif /* OSEE_RH850_CORE3_689_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_690_ISR_CAT))
#if (OSEE_RH850_CORE3_690_ISR_CAT == 1)
_osEE_rh850_core3_ei690:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_690_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei690, .-_osEE_rh850_core3_ei690
#else
_osEE_rh850_core3_ei690:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_690_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei690, .-_osEE_rh850_core3_ei690
#endif
#endif /* OSEE_RH850_CORE3_690_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_691_ISR_CAT))
#if (OSEE_RH850_CORE3_691_ISR_CAT == 1)
_osEE_rh850_core3_ei691:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_691_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei691, .-_osEE_rh850_core3_ei691
#else
_osEE_rh850_core3_ei691:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_691_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei691, .-_osEE_rh850_core3_ei691
#endif
#endif /* OSEE_RH850_CORE3_691_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_692_ISR_CAT))
#if (OSEE_RH850_CORE3_692_ISR_CAT == 1)
_osEE_rh850_core3_ei692:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_692_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei692, .-_osEE_rh850_core3_ei692
#else
_osEE_rh850_core3_ei692:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_692_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei692, .-_osEE_rh850_core3_ei692
#endif
#endif /* OSEE_RH850_CORE3_692_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_693_ISR_CAT))
#if (OSEE_RH850_CORE3_693_ISR_CAT == 1)
_osEE_rh850_core3_ei693:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_693_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei693, .-_osEE_rh850_core3_ei693
#else
_osEE_rh850_core3_ei693:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_693_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei693, .-_osEE_rh850_core3_ei693
#endif
#endif /* OSEE_RH850_CORE3_693_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_694_ISR_CAT))
#if (OSEE_RH850_CORE3_694_ISR_CAT == 1)
_osEE_rh850_core3_ei694:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_694_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei694, .-_osEE_rh850_core3_ei694
#else
_osEE_rh850_core3_ei694:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_694_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei694, .-_osEE_rh850_core3_ei694
#endif
#endif /* OSEE_RH850_CORE3_694_ISR_CAT */
#if (defined(OSEE_RH850_CORE3_695_ISR_CAT))
#if (OSEE_RH850_CORE3_695_ISR_CAT == 1)
_osEE_rh850_core3_ei695:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_695_ISR_HND, r6
  jr      _osEE_rh850_call_isr1
.size _osEE_rh850_core3_ei695, .-_osEE_rh850_core3_ei695
#else
_osEE_rh850_core3_ei695:
  pushsp  r1-r19
  mov     OSEE_RH850_CORE3_695_ISR_TID, r6
  jr      _osEE_rh850_call_isr2
  .size  _osEE_rh850_core3_ei695, .-_osEE_rh850_core3_ei695
#endif
#endif /* OSEE_RH850_CORE3_695_ISR_CAT */

