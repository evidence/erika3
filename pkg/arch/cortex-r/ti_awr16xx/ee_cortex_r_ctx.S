/*# ###*B*###
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
  # ###*E*###
*/

/**
 * \file  ee_cortex_r_ctx.S
 * \brief ARMv7-R Context Switch
 *
 * This file contains the functions to save and restore registers for
 * context switch & OSEK TerminateTask().
 *
 * \author  Errico Guidieri
 * \date    2019
 */

/*============================================================================
                      Context Macros: Internally used
  ==========================================================================*/

#include "ee_arch_override.h"

#if 0
/* This data structure must have size that is 8 bytes multiple */
typedef struct OsEE_CTX_tag {
  struct OsEE_CTX_tag * p_ctx;
#if (defined(OSEE_CORTEX_R_VFP))
  OsEE_dreg d8;
  OsEE_dreg d9;
  OsEE_dreg d10;
  OsEE_dreg d11;
  OsEE_dreg d12;
  OsEE_dreg d13;
  OsEE_dreg d14;
  OsEE_dreg d15;
#endif /* OSEE_CORTEX_R_VFP */
  OsEE_reg  r4;
  OsEE_reg  r5;
  OsEE_reg  r6;
  OsEE_reg  r7;
  OsEE_reg  r8;
  OsEE_reg  r9;
  OsEE_reg  r10;
  OsEE_reg  r11;
  OsEE_reg  LR_usr; /* Linker Register: r14 (USR bank) */
} OsEE_CTX;
#endif

#if 0
#if (defined(OSEE_CORTEX_R_VFP))
  .equ  OSEE_CTX_SIZE,  104
#else
  .equ  OSEE_CTX_SIZE,  40
#endif /* OSEE_CORTEX_R_VFP */
#endif /* 0 */

osEE_hal_save_ctx_m .macro p_from_scb
/* Store Callee saved registers */
    push    {r4-r11, lr}
#if (defined(OSEE_CORTEX_R_VFP))
/* Store VFP (FPU) Callee saved registers */
    vpush   {d8-d15}
#endif /* OSEE_CORTEX_R_VFP */
/* Push previous p_from_scb->p_tos */
    ldr     r4, [p_from_scb]
    push    {r4}
/* Save current p_from_scb->p_tos = SP */
    str     sp, [p_from_scb]
  .endm

osEE_hal_restore_ctx_m .macro p_to_scb
/* Restore p_to_scb->p_tos */
    ldr     sp, [p_to_scb]
/* Restore previous p_tos */
    pop     {r4}
    str     r4, [p_to_scb]
#if (defined(OSEE_CORTEX_R_VFP))
/* Restore VFP (FPU) Callee saved registers */
    vpop    {d8-d15}
#endif /* OSEE_CORTEX_R_VFP */
/* Restore Callee saved registers */
    pop     {r4-r11, lr}
  .endm

  .global osEE_scheduler_task_wrapper_run
  .global osEE_scheduler_task_wrapper_restore
  .global osEE_scheduler_task_not_terminated

/*
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
*/
  .def osEE_hal_save_ctx_and_restore_ctx
  .asmfunc
osEE_hal_save_ctx_and_restore_ctx
  /*  r0 parameter: OsEE_TDB * p_to_tdb
      r1 parameter: OsEE_SCB * p_to_scb
      r2 parameter: OsEE_SCB * p_from_scb */
    osEE_hal_save_ctx_m r2

/* Unconditional brach to restore context */
    b osEE_hal_restore_ctx
  .endasmfunc

/*
FUNC(void, OS_CODE)
  osEE_hal_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .def osEE_hal_restore_ctx
  .asmfunc
osEE_hal_restore_ctx
  /*  r0 parameter: OsEE_TDB * p_to_tdb
      r1 parameter: OsEE_SCB * p_to_scb */
    osEE_hal_restore_ctx_m r1

    b   osEE_scheduler_task_wrapper_restore
  .endasmfunc

/*
FUNC(void, OS_CODE)
  osEE_hal_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
*/
  .def osEE_hal_ready2stacked
  .asmfunc
osEE_hal_ready2stacked
  /*  r0 parameter: OsEE_TDB * p_to_tdb
      r1 parameter: OsEE_SCB * p_to_scb */
/* SP = p_to_scb->p_tos */
    ldr r1, [r1]
    mov sp, r1

    b  osEE_scheduler_task_wrapper_run
  .endasmfunc

/*
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
*/
  .def osEE_hal_save_ctx_and_ready2stacked
  .asmfunc
osEE_hal_save_ctx_and_ready2stacked
  /*  r0 parameter: OsEE_TDB * p_to_tdb
      r1 parameter: OsEE_SCB * p_to_scb
      r2 parameter: OsEE_SCB * p_from_scb */
    osEE_hal_save_ctx_m r2

    b osEE_hal_ready2stacked
  .endasmfunc

/*
FUNC(void, OS_CODE_NORETURN)
  osEE_hal_terminate_ctx
(
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_term_scb,
  VAR(OsEE_kernel_callback, AUTOMATIC)      kernel_cb
)
*/
  .def osEE_hal_terminate_ctx
  .asmfunc
osEE_hal_terminate_ctx:
  /*  r0 parameter: OsEE_SCB * p_term_scb
      r1 parameter: kernel_cb */
/* Unwind SP */
    ldr r0, [r0]
    mov sp, r0

    bx r1
/* This is a NORETURN Function */
  .endasmfunc

/*
FUNC(OsEE_addr, OS_CODE_NORETURN)
  osEE_get_SP
(
  void
)
*/
  .def osEE_get_SP
  .asmfunc
osEE_get_SP
    mov r0, sp
    bx lr
  .endasmfunc

/*
extern void osEE_cortex_r_switch_to_system_mode(void)
*/
  .def osEE_cortex_r_switch_to_system_mode
  .asmfunc
osEE_cortex_r_switch_to_system_mode
    mov   r0, #0
    svc   #0
    bx    lr
  .endasmfunc

