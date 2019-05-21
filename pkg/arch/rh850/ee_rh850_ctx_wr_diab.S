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
 * \file  ee_rh850_ctx_wr_diab.S
 * \brief RH850G4 Context Switch.
 *
 * This file contains the functions to save and restore registers for
 * context switch & OSEK TerminateTask().
 *
 * \author  Errico Guidieri
 * \date    2018
 */

/*============================================================================
                            Context Macros
  ==========================================================================*/

/* This context i partially filled by PREPARE instruction that use a
   Reg32 list12 bitmask to express which registers have to be saved
   (Look at RH850G4 ISA for more information).
    list12 is a 32-bit register list, defined as follows.
bits   31  30  29  28  27  26  25  24  23  22  21  20 … 1 0
reg    r24 r25 r26 r27 r20 r21 r22 r23 r28 r29 r31    —   r30

Diab AS accepts a 12 bit immediate to represent list12

typedef struct OsEE_CTX_tag {
  struct OsEE_CTX_tag * p_ctx;  Previous ERIKA's Context Pointer
  OsEE_reg              psw;
  OsEE_reg r31_lp;
  OsEE_reg r30_ep;
  OsEE_reg r29;
  OsEE_reg r28;
  OsEE_reg r27;
  OsEE_reg r26;
  OsEE_reg r25;
  OsEE_reg r24;
  OsEE_reg r23;
  OsEE_reg r22;
  OsEE_reg r21;
  OsEE_reg r20;
} OsEE_CTX;
*/

/* Do not allow ASM reordering */
.set  noreorder

.set  OSEE_RH850_CTX_SIZE,            0x38
.set  OSEE_RH850_CTX_PREPARE_MASK,    0xFFF

/* ASM macro do not work for multiple values string */
#define OSEE_RH850_STSR_PSW(reg)      5, reg, 0
#define OSEE_RH850_PSW                5, 2
osEE_hal_save_ctx_m: .macro p_from_scb
/* Save the callee saved registers + reserve two words */
    prepare OSEE_RH850_CTX_PREPARE_MASK, 2
/* Story double word reg 24 old p_from_scb->p_tos and PSW */
    ld.w    0[p_from_scb],      r24
    stsr    OSEE_RH850_STSR_PSW(r25)
    st.dw   r24,                0[sp]
/* Store the actual TOS on the p_from_scb->p_tos */
    st.w    sp,                 0[p_from_scb]
  .endm

/*  .section ".text" */
/*  .align  2 */

/* -- Import Global Symbols */
  .import   _osEE_scheduler_task_wrapper_restore
  .import   _osEE_scheduler_task_wrapper_run
  .import   _osEE_change_context_from_task_end

/*
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
*/
  .globl _osEE_hal_save_ctx_and_restore_ctx
  .type _osEE_hal_save_ctx_and_restore_ctx, @function
_osEE_hal_save_ctx_and_restore_ctx:
  /*  r6 parameter:  OsEE_TDB * p_to_tdb
      r7 parameter:  OsEE_SCB * p_to_scb
      r8 parameter:  OsEE_SCB * p_from_scb  */
    osEE_hal_save_ctx_m r8

/* Unconditional branch to restore context */
    jr _osEE_hal_restore_ctx

  .size _osEE_hal_save_ctx_and_restore_ctx, .-_osEE_hal_save_ctx_and_restore_ctx

/*
FUNC(void, OS_CODE)
  osEE_hal_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .globl _osEE_hal_restore_ctx
  .type _osEE_hal_restore_ctx, @function
_osEE_hal_restore_ctx:
  /*  r6 parameter: OsEE_TDB * p_to_tdb
      r7 parameter: OsEE_SCB * p_to_scb */
/* Set current context on the Stack Pointer SP = p_to_scb->p_tos */
    ld.w    0[r7],  sp
/* Load old p_to_scb->p_tos */
#    ld.dw   0[sp],  r24
    ld.w   0[sp],   r24
/* Restore old p_to_scb->p_tos */
    st.w    r24,    0[r7]
/* Restore old PSW */
#    ldsr    r25,   OSEE_RH850_PSW
#    synci
/* Restore old context discarding the first two words */
    dispose 2,      OSEE_RH850_CTX_PREPARE_MASK

    jr _osEE_scheduler_task_wrapper_restore

  .size _osEE_hal_restore_ctx, .-_osEE_hal_restore_ctx

/*
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
*/
  .globl _osEE_hal_save_ctx_and_ready2stacked
  .type _osEE_hal_save_ctx_and_ready2stacked, @function
_osEE_hal_save_ctx_and_ready2stacked:
    /*  r6 parameter: OsEE_TDB * p_to_tdb
        r7 parameter: OsEE_SCB * p_to_scb
        r8 parameter: OsEE_SCB * p_from_scb */
    osEE_hal_save_ctx_m r8

    jr _osEE_hal_ready2stacked

  .size _osEE_hal_save_ctx_and_ready2stacked, .-_osEE_hal_save_ctx_and_ready2stacked

/*
FUNC(void, OS_CODE)
  osEE_hal_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .global _osEE_hal_ready2stacked
  .type   _osEE_hal_ready2stacked, @function
_osEE_hal_ready2stacked:
  /*  r6 parameter: OsEE_TDB * p_to_tdb
      r7 parameter: OsEE_SCB * p_to_scb */
/* SP = p_to_scb->p_tos */
    ld.w 0[r7], sp

    jr _osEE_scheduler_task_wrapper_run

  .size _osEE_hal_ready2stacked, .-_osEE_hal_ready2stacked
/*
FUNC(void, OS_CODE_NORETURN)
  osEE_hal_terminate_ctx
(
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_term_scb,
  VAR(OsEE_kernel_callback, AUTOMATIC)      kernel_cb
)
*/
  .globl _osEE_hal_terminate_ctx
  .type _osEE_hal_terminate_ctx, @function
_osEE_hal_terminate_ctx:
  /*  r6 parameter: OsEE_SCB * p_term_scb
      r7 parameter: kernel_cb */
/* Unwind SP. Load SP = p_term_scb->p_ptos */
    ld.w 0[r6], sp

    jmp  [r7]
/*  This is a NORETURN Function */
  .size _osEE_hal_terminate_ctx, .-_osEE_hal_terminate_ctx

/*
FUNC(void, OS_CODE)
    osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_from
)
{
--Pseudo Code
  ldsr _osEE_change_context_from_task_end, eipc
  eiret
}
*/
  .import _osEE_change_context_from_task_end

  .globl _osEE_change_context_from_isr2_end
  .type _osEE_change_context_from_isr2_end, @function
_osEE_change_context_from_isr2_end:
  /*  r6 parameter: OsEE_TDB * p_to
      r7 parameter: OsEE_TDB * p_from */
    movhi     hi(_osEE_change_context_from_task_end), r0, r8
    movea     lo(_osEE_change_context_from_task_end), r8, r8
    ldsr      r8,  0,  0      # eipc

    #-- Synchronize Pipeline
    #--
    #-- IMPORTANT: Required for 
    #--  - External Interrupt Processing Flow
    #--  - Software Interrupt Processing Flow
    #--  - Peripheral Interrupt Processing Flow
    #--
    #-- Redundant for other types of EI interrupts
    syncp

    #-- return from EI exception
    eiret
  .size _osEE_change_context_from_isr2_end, .-_osEE_change_context_from_isr2_end

#if (!defined(OSEE_SINGLECORE))
/*
void osEE_rh850_ipir_preemption_point(OsEE_KDB * p_kdb)
{
--Pseudo Code
  ldsr _osEE_scheduler_task_preemption_point, eipc
  eiret
}
*/
  .import _osEE_scheduler_task_preemption_point

  .globl _osEE_rh850_ipir_preemption_point
  .type _osEE_rh850_ipir_preemption_point, @function
_osEE_rh850_ipir_preemption_point:
  /*  r6 parameter: OsEE_KDB * p_kdb */
    movhi     hi(_osEE_scheduler_task_preemption_point), r0, r8
    movea     lo(_osEE_scheduler_task_preemption_point), r8, r8
    ldsr      r8,  0,  0      # eipc

    #-- Synchronize Pipeline
    #--
    #-- IMPORTANT: Required for 
    #--  - Software Interrupt Processing Flow
    syncp

    #-- return from EI exception
    eiret
  .size _osEE_rh850_ipir_preemption_point, .-_osEE_rh850_ipir_preemption_point

/*
void osEE_hal_spin_lock(OsEE_spin_lock * p_lock)
*/
  .globl _osEE_hal_spin_lock
  .type _osEE_hal_spin_lock, @function
_osEE_hal_spin_lock:
  /*  r6 parameter: OsEE_spin_lock * p_lock */
  /* Prepare lock value */
  mov   1,    r8
lock:
/* Load and Link p_lock */
  ldl.w [r6], r7
/* Remember: r0 is a zero register */
  cmp   r0,   r7
  bnz   lock_wait
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r8 */
  stc.w r8,   [r6]
  cmp   r0, r8
  bnz   lock_success
lock_wait:
/* Release the link & snooze */
  cll
/* It seems that 2 snooze are needed to give to opportunity to commit
   changes in any case */
  snooze
  snooze
  br    lock
lock_success:
  jmp   [lp]
  .size _osEE_hal_spin_lock, .-_osEE_hal_spin_lock

/*
void osEE_hal_try_spin_lock(OsEE_spin_lock * p_lock)
*/
  .globl _osEE_hal_try_spin_lock
  .type _osEE_hal_try_spin_lock, @function
_osEE_hal_try_spin_lock:
  /*  r6 parameter: OsEE_spin_lock * p_lock */
/* Prepare fail return value */
  mov    0,     r10
/* Prepare lock value */
  mov    1,     r8
/* Load and Link p_lock */
  ldl.w  [r6],  r7
/* Remember: r0 is a zero register */
  cmp    r0,    r7
  bnz    lock_fail
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r8 */
  stc.w  r8,    [r6]
  cmp    r0,    r8
  bz     lock_fail
/* Set success return value */
  mov    1,     r10
lock_fail:
/* Release the link before leave the block */
  cll
  jmp   [lp]
  .size _osEE_hal_try_spin_lock, .-_osEE_hal_try_spin_lock

/*
extern void osEE_rh850_set_bit_l(OsEE_reg volatile * p_mem, OsEE_reg bit_pos)
 */
  .globl _osEE_rh850_set_bit_l
  .type _osEE_rh850_set_bit_l, @function
_osEE_rh850_set_bit_l:
  /*  r6 parameter: OsEE_reg * p_mem */
  /*  r7 parameter: OsEE_reg   bit_pos */
/* Load and Link p_mem */
  mov   1,    r8
/* Logical shift left r7(1) of bit value (saving in r7)*/
  shl   r7,   r8
mem_r:
/* Load and Link p_mem */
  ldl.w [r6], r9
/* Set the bit in position "bit_pos" */
  or    r8,   r9
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r9 */
  stc.w r9,   [r6]
/* If for some reason the link has been broken retry */
  cmp   r0,   r9
  bnz   mem_w
/* It seems that 2 snooze are needed to give to opportunity to commit
   changes in any case */
  snooze
  snooze
  br    mem_r
mem_w:
  jmp   [lp]
  .size _osEE_rh850_set_bit_l, .-_osEE_rh850_set_bit_l

/*
extern OsEE_reg osEE_rh850_cmpswapw_l(OsEE_reg * volatilep_mem,
    OsEE_reg exp_value, OsEE_reg new_value) */
  .globl _osEE_rh850_cmpswapw_l
  .type _osEE_rh850_cmpswapw_l, @function
_osEE_rh850_cmpswapw_l:
  /*  r6 parameter: OsEE_reg * p_mem */
  /*  r7 parameter: OsEE_reg   exp_value */
  /*  r8 parameter: OsEE_reg   new_value */
/* Load and Link p_mem */
cmp_swap:
  ldl.w   [r6], r10
  cmp     r7,   r10
/* In p_mem is not stored exp_value-> Not Swap */
  bnz     not_swap
  mov     r8,   r9
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r9 */
  stc.w   r9,   [r6]
  cmp     r0,   r9
  bnz     swapped
/* We failed to store new_value, but expected value passed -> retry */
/* It seems that 2 snooze are needed to give to opportunity to commit
   changes in any case */
  snooze
  snooze
  br      cmp_swap
not_swap:
/* If p_mem value is not the expected one, clear the load link. */
  cll
swapped:
  jmp   [lp]
  .size _osEE_rh850_cmpswapw_l, .-_osEE_rh850_cmpswapw_l
#endif /* !OSEE_SINGLECORE */
