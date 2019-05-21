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
 * \file  ee_rh850_ei_wrapper_ctx_wr_diab.hs
 * \brief EI wrapper context as assembly macros
 *
 * \author  Errico Guidieri
 * \date    2018
 */
 
  #----------------------------------------------------------------------------
  #-- Description : ISR Wrappers
  #----------------------------------------------------------------------------

#-- Save ISR Context Macro
osEE_rh850_save_isr_ctx_m: .macro
  #-- Store remaning GPRs (r1-r19 have to be already pushed)
  pushsp    r30-r31

  #-- Preserve core EI exception registers
  stsr      0,  r16,  0   #-- eipc
  stsr      1,  r15,  0   #-- eipsw
  stsr      13, r14,  0   #-- eiic

  #-- Preserve other system registers
  stsr      6,  r13,  0   #-- fpsr
  stsr      7,  r12,  0   #-- fpepc
  stsr      16, r11,  0   #-- ctpc
  stsr      17, r10,  0   #-- ctpsw

  #-- Push SFRs to stack
  pushsp    r10-r16
  .endm

#-- Restore ISR Context Macro
osEE_rh850_restore_isr_ctx_m: .macro
  #-- Restore SFRs
  popsp     r6-r12

  #-- restore other system registers
  ldsr     r6,  17,   0   # ctpsw
  ldsr     r7,  16,   0   # ctpc
  ldsr     r8,  7,    0   # fpepc
  ldsr     r9,  6,    0   # fpsr

  #-- restore core EI exception registers
  ldsr     r10, 13,   0   # eiic
  ldsr     r11, 1,    0   # eipsw
  ldsr     r12, 0,    0   # eipc

  #-- restore GPRs
  popsp    r30-r31
  popsp    r1-r19
  .endm
