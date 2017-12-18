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
 * \file  ee_avr8_asm.S
 * \brief AVR8 Context Switch.
 *
 * This file contains the functions to save and restore registers for
 * context switch & OSEK TerminateTask().
 *
 * \author  Errico Guidieri
 * \author  Giuseppe Serano
 * \date    2017
 */

/* Macro Save Context: Internally used */
  .macro osEE_hal_save_vcontext_m p_from_scb_h p_from_scb_l
/* Save working registers of preempted thread on stack */
    push  r2
    push  r3
    push  r4
    push  r5
    push  r6
    push  r7
    push  r8
    push  r9
    push  r10
    push  r11
    push  r12
    push  r13
    push  r14
    push  r15
    push  r16
    push  r17
    push  r28
    push  r29

/* r4:r5 = p_from_scb->p_tos (p_from_scb_l:p_from_scb_h) */
    mov   r30, \p_from_scb_l
    mov   r31, \p_from_scb_h
    ld    r4, z+
    ld    r5, z

/* Save previous tos on stack */
    push r4
    push r5

/* p_from_scb->p_tos = SP (0x3D:0x3E) */
    mov r30, \p_from_scb_l
    mov r31, \p_from_scb_h
    in  r4, 0x3D  /* spl -> r4 */
    in  r5, 0x3E  /* sph -> r5 */
    st  z+, r4
    st  z,  r5
  .endm

/* Macro Restore Context: Internally used */
  .macro osEE_hal_restore_vcontext_m p_to_scb_h p_to_scb_l

/* r4:r5 = p_to_scb->p_tos (p_to_scb_l:p_to_scb_h) */
    mov r30, \p_to_scb_l
    mov r31, \p_to_scb_h
    ld  r4, z+
    ld  r5, z

/* Restore the SP */
    out 0x3D, r4  /* r4 -> spl */
    out 0x3E, r5  /* r5 -> sph */

/* Get previous p_tos from stack (prev_p_tos) */
    pop r5
    pop r4

/* p_to_scb->p_tos = prev_p_tos */
    mov r30, \p_to_scb_l
    mov r31, \p_to_scb_h
    st  z+, r4
    st  z,  r5

/* Now restore the context */
    pop r29
    pop r28
    pop r17
    pop r16
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop r7
    pop r6
    pop r5
    pop r4
    pop r3
    pop r2

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
  .align 2
  .globl osEE_hal_save_ctx_and_restore_ctx
  .type osEE_hal_save_ctx_and_restore_ctx, @function
osEE_hal_save_ctx_and_restore_ctx:
  /*  r25:r24 parameter:  OsEE_TDB * p_to_tdb
      r23:r22 parameter:  OsEE_SCB * p_to_scb
      r21:r20 parameter:  OsEE_SCB * p_from_scb */
    osEE_hal_save_vcontext_m r21 r20

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
  .align 2
  .globl osEE_hal_restore_ctx
  .type osEE_hal_restore_ctx, @function
osEE_hal_restore_ctx:
  /*  r25:r24 parameter:  OsEE_TDB * p_to_tdb
      r23:r22 parameter:  OsEE_SCB * p_to_scb */
    osEE_hal_restore_vcontext_m r23 r22
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
  .align 2
  .global osEE_hal_ready2stacked
  .type   osEE_hal_ready2stacked, @function
osEE_hal_ready2stacked:
  /*  r25:r24 parameter:  OsEE_TDB * p_to_tdb
      r23:r22 parameter:  OsEE_SCB * p_to_scb
      r21:r20 local       p_to_scb->p_tos */
    mov r30, r22
    mov r31, r23
    ld  r20, z+
    ld  r21, z
/* sp = 21:20 */
    out 0x3D, r20
    out 0x3E, r21

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
  .align 2
  .globl osEE_hal_save_ctx_and_ready2stacked
  .type osEE_hal_save_ctx_and_ready2stacked, @function
osEE_hal_save_ctx_and_ready2stacked:
  /*  r25:r24 parameter:  OsEE_TDB * p_to_tdb
      r23:r22 parameter:  OsEE_SCB * p_to_scb
      r21:r20 parameter:  OsEE_SCB * p_from_scb */
    osEE_hal_save_vcontext_m r21 r20
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
  .align 2
  .globl osEE_hal_terminate_ctx
  .type osEE_hal_terminate_ctx, @function
osEE_hal_terminate_ctx:
  /*  r25:r24 parameter:  OsEE_SCB * p_term_scb
      r23:r22 parameter:  kernel_cb
      r21:r20 local       p_term_scb->p_tos */
    mov r30, r24
    mov r31, r25
    ld  r20, z+
    ld  r21, z

/* Unwind SP */
    out 0x3D, r20 /* r20 -> spl */
    out 0x3E, r21 /* r21 -> sph */

/*  Jump to kern_callback (that schedule) */
    mov r30, r22
    mov r31, r23

    ijmp
/* This is a NORETURN Function */
  .size osEE_hal_terminate_ctx, .-osEE_hal_terminate_ctx

