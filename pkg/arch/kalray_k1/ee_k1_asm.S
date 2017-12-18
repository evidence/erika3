/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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
 * <https://www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
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

/**
 * \file  ee_k1_asm.S
 * \brief Kalray K1 Context Switch.
 *
 * This file contains the functions to save and restore registers for
 * context switch & TerminateTask()
 *
 * \author  Errico Guidieri
 * \date    2016
 */

#include <HAL/hal/hal.h>
#include "ee_k1_context.h"
#include "mOS_common_types_s_c.h"

/*=============================================================================
  WARNING (Remember the following when you write assembly code for K1 ISA):
  1) Stack have to be 8 byte alligned (so the frame have to be at least 8 byte
     long) and grows towards "smaller" addresses. The SP (Stack Pointer) is
     $R12.
  2) The K1 architecture is little endian so the variables are written towards
     "bigger" addresses.
  3) The first (bigger in address) word accessible of the function stack frame
     is (STACK_FRAME_SIZE - 4)[SP]. So with a frame of 8 byte the two accessible
     words are (in Order) 4[SP] and 0[SP].
 ============================================================================*/

/* Save Context Macro: Internally used */
  .macro osEE_hal_save_vcontext_m p_from_scb local
/* Allocate context on stack */
    add   $r12 = $r12, -OSEE_K1_TASK_CONTEX_SIZE
    ;;
/* \local = p_from_scb->p_tos */
    lw \local = OSEE_SCB_TOS_OFFSET[\p_from_scb]
    ;;
/* Save the context on the stack */
    osEE_k1_task_vcontext_save $r12
    ;;
/* Save tos nel context */
    sw OSEE_K1_TASK_CONTEXT_PTOS_OFFSET[$r12] = \local
    ;;
/* p_from_scb->p_tos = SP ($r12) */
    sw OSEE_SCB_TOS_OFFSET[\p_from_scb] = $r12
    ;;
  .endm

/* Restore Context Macro: Internally used */
  .macro osEE_hal_restore_vcontext_m p_to_scb local
/* \local = p_to_scb->p_tos */
    lw \local = OSEE_SCB_TOS_OFFSET[\p_to_scb]
    ;;
/* Restore the context */
    osEE_k1_task_vcontext_restore \local
    ;;
/* Get back Old tos to be stored back in p_to_scb */
    lw \local = OSEE_K1_TASK_CONTEXT_PTOS_OFFSET[\local]
    add $r12 = $r12, OSEE_K1_TASK_CONTEX_SIZE
    ;;
/* p_to_scb->p_tos = Old tos */
    sw OSEE_SCB_TOS_OFFSET[\p_to_scb] = \local
    ;;
  .endm

#if 0 /* in mOS environment cannot be used. */
/* Enable Interrupts */
  .macro osEE_hal_enableIRQ_m local
/* \local = 0x00100000 */
    make \local = 1048576
    ;;
    hfxb $ps, \local
    ;;
  .endm
#endif /* 0 */

/*
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
*/
  .align 8
  .globl osEE_hal_save_ctx_and_restore_ctx
  .type osEE_hal_save_ctx_and_restore_ctx, @function
osEE_hal_save_ctx_and_restore_ctx:
  /*  $r0 parameter:  OsEE_TDB * p_to_tdb
      $r1 parameter:  OsEE_SCB * p_to_scb
      $r2 parameter:  OsEE_SCB * p_from_scb */
    osEE_hal_save_vcontext_m $r2 $r3
    ;;
  /* Unconditional brach to restore context */
    goto osEE_hal_restore_ctx
    ;;
  .size osEE_hal_save_ctx_and_restore_ctx, .-osEE_hal_save_ctx_and_restore_ctx

/*
FUNC(void, OS_CODE)
  osEE_hal_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .align 8
  .globl osEE_hal_restore_ctx
  .type osEE_hal_restore_ctx, @function
osEE_hal_restore_ctx:
  /*  $r0 parameter:  OsEE_TDB * p_to_tdb
      $r1 parameter:  OsEE_SCB * p_to_scb
      $r2 local:      p_to_scb->p_tos */
    osEE_hal_restore_vcontext_m $r1 $r2
    ;;
    goto  osEE_scheduler_task_wrapper_restore
    ;;
  .size osEE_hal_restore_ctx, .-osEE_hal_restore_ctx

/*
FUNC(void, OS_CODE)
  osEE_hal_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .align 8
  .globl osEE_hal_ready2stacked
  .type osEE_hal_ready2stacked, @function
osEE_hal_ready2stacked:
  /*  $r0 parameter:  OsEE_TDB * p_to_tdb
      $r1 parameter:  OsEE_SCB * p_to_scb */
/* $r12 = p_to_scb->p_tos ($r1) */
    lw $r12 = OSEE_SCB_TOS_OFFSET[$r1]
    ;;
/* Create the Stack Scratch Area for the Function and call the Task Wrapper */
    add   $r12, $r12, -OSEE_STACK_SCRATCH_AREA_SIZE
    goto  osEE_scheduler_task_wrapper_run
    ;;
  .size osEE_hal_ready2stacked, .-osEE_hal_ready2stacked

/*
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
*/
  .align 8
  .globl osEE_hal_save_ctx_and_ready2stacked
  .type osEE_hal_save_ctx_and_ready2stacked, @function
osEE_hal_save_ctx_and_ready2stacked:
  /*  $r0 parameter:  OsEE_TDB *  p_to_tdb
      $r1 parameter:  OsEE_SCB *  p_to_scb
      $r2 parameter:  OsEE_SCB *  p_from_scb */
    osEE_hal_save_vcontext_m $r2 $r3
    ;;
    goto osEE_hal_ready2stacked
    ;;
  .size osEE_hal_save_ctx_and_ready2stacked, .-osEE_hal_save_ctx_and_ready2stacked

/*
FUNC(void, OS_CODE_NORETURN)
  osEE_hal_terminate_ctx
(
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_term_scb,
  VAR(OsEE_kernel_callback, AUTOMATIC)      kernel_cb
)
*/
  .align 8
  .globl osEE_hal_terminate_ctx
  .type osEE_hal_terminate_ctx, @function
osEE_hal_terminate_ctx:
  /*  $r0 parameter:  OsEE_SCB *      p_term_scb
      $r1 Parameter:  OsEE_kernel_cb  kernel_cb
      $r2 local:      p_term_scb->p_tos */
/* $r2 = p_term_scb->p_tos ($r0) */
  lw $r2 = OSEE_SCB_TOS_OFFSET[$r0]
  ;;
/* Unwind the STACK + Create SCRATH Area. */
  add $r12 = $r2, -OSEE_STACK_SCRATCH_AREA_SIZE
  icall $r1
  ;;
/* This is a NORETURN Function */
.never_get_here:
  goto .never_get_here
  ;;
  .size osEE_hal_terminate_ctx, .-osEE_hal_terminate_ctx

#==============================================================================#

/*
FUNC(void, OS_CODE)
  osEE_avr7r_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_from
)
{
  CoreIdType core_id = EE_get_core(core_id);
  _scoreboard_start.SCB_VCORE.PER_CPU[core_id].SFR_SPC = &EE_hal_change_context;
  mOS_RFE();
}
*/

  .global osEE_change_context_from_task_end

  .align 8
  .globl osEE_change_context_from_isr2_end
  .proc osEE_change_context_from_isr2_end
osEE_change_context_from_isr2_end:
/* Prepare the Function Frame ($r16,$r17,$r18) */
    add $r12, $r12, -16
    ;;
/* Save two callee registers without any specific meaning to use as temp
   variables.
   Read the process Identification Register $pi in documentation file */
    sd 0[$r12] = $p16
    make $r16 = _scoreboard_start
    get $r17, $pcr
    ;;
/* Save last callee register */
/* Extract PID bitfiled from $pcr */
    sw 8[$r12] = $r18
    extfz $r17, $r17, 15, 11
    ;;
/* PID * MOS_SCOREBOARD_PER_CPU_ELEMENT_SIZE (=256) => PID << 8 */
    sll $r17, $r17, 8
    ;;
/* $r16 = $_scoreboard_start.SCB_VCORE.PER_CPU[pid]
   $r17 = osEE_hal_change_context_from_task_end */
    add $r16, $r16, $r17
    make $r17 = osEE_change_context_from_task_end
    ;;
/* Prepare the SSP to be saved in MOS_VC_REG_SSP
   Save on the shadow program counter the change context routine
   N.B: In a bundle the register update it's the last thing done so the
        following works */
    add $r17 = $r12, 16
    sw MOS_VC_REG_SPC[$r16] = $r17
    ;;
/* Save on the shadow stack pointer the desidered stack.
   (without function frame) */
    sw MOS_VC_REG_SSP[$r16] = $r17
    ;;
/* Load current SPS & Prepare a the HW priority to be maintened on the IL
   (otherwise the RFE will restore the interrupted one, that probaly is the
   TASK's one, enabling ISR2 preemption too soon. */
    lw $r17 = MOS_VC_REG_SPS[$r16]
    make $r18 = OSEE_ISR2_MAX_HW_ASM_PRIO
    ;;
/* Manipulate current SPS to insert the right priority */
    insf $r17 = $r18, 15, 12
    ;;
/* Store the SPS with the right IL ceiling */
    sw MOS_VC_REG_SPS[$r16] = $r17
    ;;
/* Restore $r18 */
    lw $r18 = 8[$r12]
    ;;
/* Destroy the function frame
   Restore $p16 ($r16,$r17)
   N.B: In a bundle the register update it's the last thing done, so the
        following works */
    add $r12, $r12, 16
    ld $p16 = 0[$r12]
    ;;
/* Issue a MOS_VC_RFE scall, no Need to adjust RA. This function is executed
   from an ISR2 end, all the Stack Frame will be discarded. */
    scall MOS_VC_RFE
    ;;
  .endp osEE_change_context_from_isr2_end
