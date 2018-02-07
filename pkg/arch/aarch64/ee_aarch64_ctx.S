/*# ###*B*###
  # ERIKA Enterprise - a tiny RTOS for small microcontrollers
  #
  # Copyright (C) 2002-2017 Evidence Srl
  #
  # This file is part of ERIKA Enterprise.
  #
  # See LICENSE file.
  # ###*E*###
*/

/**
 * \file  ee_aarch64_ctx.S
 * \brief ARMv8-A aarch64 Context Switch.
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

/*
  typedef struct OsEE_CTX_tag {
    OsEE_reg x19;
    OsEE_reg x20;
    OsEE_reg x21;
    OsEE_reg x22;
    OsEE_reg x23;
    OsEE_reg x24;
    OsEE_reg x25;
    OsEE_reg x26;
    OsEE_reg x27;
    OsEE_reg x28;
    OsEE_reg x29_fp;
    OsEE_reg x30_lr;
    OsEE_reg daif;
    struct OsEE_CTX_tag * p_ctx;
  } OsEE_CTX;
*/

  .equ  OSEE_CTX_SIZE,112

  .macro osEE_hal_save_ctx_m p_from_scb
/* Reserve the space for the CTX and save the First Two Registers */
    stp x19, x20, [sp, #-OSEE_CTX_SIZE]!
    stp x21, x22, [sp, #16]
    stp x23, x24, [sp, #32]
    stp x25, x26, [sp, #48]
    stp x27, x28, [sp, #64]
    stp x29, x30, [sp, #80]
/* Use last scratch registers to hold daif and old-tos since they are not used
   by Change Context APIs */
    mrs x7 , daif
    ldr x8 , [\p_from_scb]
    stp x7 , x8 , [sp, #96]
/* Store the actual TOS on the p_tos */
    mov x7 , sp
    str x7 , [\p_from_scb]
  .endm

  .macro osEE_hal_restore_ctx_m p_to_scb
/* Load the previous context on the Stack Pointer */
    ldr x19, [\p_to_scb]
    mov sp , x19

    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
/* Use last scratch registers to hold daif and old-tos since they are not used
   by Change Context APIs */
    ldp x7 , x8 , [sp], #16
/* I must not change DAIF here */
/*    msr daif, x7 */
    str x8 , [\p_to_scb]
#if 0 /* Previous Implementation for restore CTX (One istruction longer) */
    ldp x19, x20, [sp]
    ldp x21, x22, [sp, #16]
    ldp x23, x24, [sp, #32]
    ldp x25, x26, [sp, #48]
    ldp x27, x28, [sp, #64]
    ldp x29, x30, [sp, #80]
/* Use last scratch registers to hold daif and old-tos since they are not used
   by Change Context APIs */
    ldp x7 , x8 , [sp, #96]
/* I must not change DAIF here */
/*    msr daif, x7 */
    str x8 , [\p_to_scb]
/* Release the Context From the Stack */
    add sp , sp , #OSEE_CTX_SIZE
#endif /* 0 */
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
  /*  x0 parameter:  OsEE_TDB * p_to_tdb
      x1 parameter:  OsEE_SCB * p_to_scb
      x2 parameter:  OsEE_SCB * p_from_scb  */
    osEE_hal_save_ctx_m x2

/* Unconditional brach to restore context */
    b osEE_hal_restore_ctx

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
  /*  x0 parameter: OsEE_TDB * p_to_tdb
      x1 parameter: OsEE_SCB * p_to_scb */
    osEE_hal_restore_ctx_m x1
    b osEE_scheduler_task_wrapper_restore
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
  /*  x0 parameter: OsEE_TDB * p_to_tdb
      x1 parameter: OsEE_SCB * p_to_scb */
/* SP = p_to_scb->p_tos */
    ldr x1, [x1]
    mov sp, x1

    b osEE_scheduler_task_wrapper_run

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
    /*  x0 parameter: OsEE_TDB * p_to_tdb
        x1 parameter: OsEE_SCB * p_to_scb
        x2 parameter: OsEE_SCB * p_from_scb */
    osEE_hal_save_ctx_m x2
    b osEE_hal_ready2stacked
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
  /*  x0 parameter: OsEE_SCB * p_term_scb
      x1 parameter: kernel_cb */
/* Unwind SP */
    ldr x0, [x0]
    mov sp, x0

    br x1
/*  This is a NORETURN Function */
  .size osEE_hal_terminate_ctx, .-osEE_hal_terminate_ctx

/*
FUNC(void, OS_CODE)
    osEE_aarch64_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_from
)
*/
  .equ  OSEE_ISR_CTX_SIZE,176

  .globl osEE_aarch64_change_context_from_isr2_end
  .type osEE_aarch64_change_context_from_isr2_end, @function
osEE_aarch64_change_context_from_isr2_end:
/*  Set I in DAIF section of SPSR to assure that interrupts are masked when
    Jumping to the scheduler */
    mrs x8, spsr_el1
    orr x8, x8, #0x80
    msr spsr_el1, x8
/* Prepare to jump on scheduler function */
/*#adrp x8, :pg_hi21:osEE_change_context_from_task_end
  #add  x8, x8, #:lo12:osEE_change_context_from_task_end */
    ldr x8, =osEE_change_context_from_task_end
    msr elr_el1, x8
/* Returning from ISR */
    eret
  .size osEE_aarch64_change_context_from_isr2_end, .-osEE_aarch64_change_context_from_isr2_end

