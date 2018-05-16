/*# ###*B*###
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
  # ###*E*###
*/

/**
 * \file  ee_x86_64_ctx.S
 * \brief x86_64 Context Switch
 *
 * This file contains the functions to save and restore registers for
 * context switch & OSEK TerminateTask().
 *
 * \author  Errico Guidieri
 * \date    2017
 */

/*============================================================================
                      Context Macros: Internally used
  ==========================================================================*/

.macro osEE_hal_save_ctx_m p_from_scb

    pushf /* This decrements rsp by 8 */
    push    %r15
    push    %r14
    push    %r13
    push    %r12
    push    %rbp
    push    %rbx

    push    (\p_from_scb) # Save previous TOS on stack

    mov     %rsp, (\p_from_scb) # p_from_scb->p_tos = SP
.endm

.macro osEE_hal_restore_ctx_m p_to_scb

    movq  (\p_to_scb), %rsp # SP = p_to_scb->p_tos

/*    pop (\p_to_scb)        *//* Restore previous TOS on SCB */
/* Restore previous TOS on SCB */
    pop %rbx
    mov %rbx, (\p_to_scb)

    pop %rbx
    pop %rbp
    pop %r12
    pop %r13
    pop %r14
    pop %r15
    popf
.endm

/*
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
*/
  .globl osEE_hal_save_ctx_and_restore_ctx
  .type osEE_hal_save_ctx_and_restore_ctx, @function
osEE_hal_save_ctx_and_restore_ctx:
  /*  %rdi parameter: OsEE_TDB * p_tod_tdb
      %rsi parameter: OsEE_SCB * p_to_scb
      %rdx parameter: OsEE_SCB * p_from_scb */
    osEE_hal_save_ctx_m %rdx

/* Unconditional brach to restore context */
    jmp osEE_hal_restore_ctx

  .size osEE_hal_save_ctx_and_restore_ctx, .-osEE_hal_save_ctx_and_restore_ctx

/*
FUNC(void, OS_CODE)
  osEE_hal_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .globl osEE_hal_restore_ctx
  .type osEE_hal_restore_ctx, @function
osEE_hal_restore_ctx:
  /*  %rdi parameter: OsEE_TDB * p_to_tdb
      %rsi parameter: OsEE_SCB * p_to_scb */
    osEE_hal_restore_ctx_m %rsi
    jmp osEE_scheduler_task_wrapper_restore
  .size osEE_hal_restore_ctx, .-osEE_hal_restore_ctx

/*
FUNC(void, OS_CODE)
  osEE_hal_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .global osEE_hal_ready2stacked
  .type   osEE_hal_ready2stacked, @function
osEE_hal_ready2stacked:
  /*  %rdi parameter:  OsEE_TDB * p_to_tdb
      %rsi parameter:  OsEE_SCB * p_to_scb */
/* SP = p_to_scb->p_tos */
    mov (%rsi), %rsp
    jmp osEE_scheduler_task_wrapper_run
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
  .globl osEE_hal_save_ctx_and_ready2stacked
  .type osEE_hal_save_ctx_and_ready2stacked, @function
osEE_hal_save_ctx_and_ready2stacked:
  /*  %rdi parameter: OsEE_TDB * p_to_tdb
      %rsi parameter: OsEE_SCB * p_to_scb
      %rdx parameter: OsEE_SCB * p_from_scb */
    osEE_hal_save_ctx_m %rdx
    jmp osEE_hal_ready2stacked
  .size osEE_hal_save_ctx_and_ready2stacked, .-osEE_hal_save_ctx_and_ready2stacked

/*
FUNC(void, OS_CODE_NORETURN)
  osEE_hal_terminate_ctx
(
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_term_scb,
  VAR(OsEE_kernel_callback, AUTOMATIC)      kernel_cb
)
*/
  .globl osEE_hal_terminate_ctx
  .type osEE_hal_terminate_ctx, @function
osEE_hal_terminate_ctx:
  /*  %rdi parameter:  OsEE_SCB * p_term_scb
      %rsi parameter:  kernel_cb */
/* Unwind SP */
    movq  (%rdi), %rsp

    jmp *%rsi
/* This is a NORETURN Function */
  .size osEE_hal_terminate_ctx, .-osEE_hal_terminate_ctx
