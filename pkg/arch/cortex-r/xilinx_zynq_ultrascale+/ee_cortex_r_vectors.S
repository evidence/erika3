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
 * \file  ee_cortex_r_vectors.S
 * \brief Exception Vectors
 *
 *
 * \author  Errico Guidieri
 * \date    2017
 */

/*============================================================================
  ============================================================================
                               Exception Vector
  ============================================================================
  ==========================================================================*/
#if (!defined(OSEE_CORTEX_R_VECTOR_TABLE))
#define OSEE_CORTEX_R_VECTOR_TABLE _vector_table
#endif /* OSEE_CORTEX_R_VECTOR_TABLE */


#if (!defined(OSEE_CORTEX_R_RESET_HANDLER))
#define OSEE_CORTEX_R_RESET_HANDLER _boot
#endif /* OSEE_CORTEX_R_RESET_HANDLER */

  .extern OSEE_CORTEX_R_RESET_HANDLER

/* Table 11-3 Link Register Adjustments ARM DEN 0042A ID041714
  Exception     Adjustment  Return instruction  Instruction returned to
    SVC             0         MOVS PC, R14        Next instruction
    Undef           0         MOVS PC, R14        Next instruction
    Prefetch Abort  -4        SUBS PC, R14, #4    Aborting instruction
    Data abort      -8        SUBS PC, R14, #8    Aborting instruction (precise)
    IRQ             -4        SUBS PC, R14, #4    Next instruction
    FIQ             -4        SUBS PC, R14, #4    Next instruction
*/

  .section .vectors, "a"

  .global OSEE_CORTEX_R_VECTOR_TABLE
OSEE_CORTEX_R_VECTOR_TABLE:
    ldr pc, =OSEE_CORTEX_R_RESET_HANDLER    /* Reset Vector           */
    ldr pc, =osEE_cortex_r_und_inst_vec     /* Und Vector             */
    ldr pc, =osEE_cortex_r_svc_vec          /* SVC Vector             */
    ldr pc, =osEE_cortex_r_prefetch_abt_vec /* Prefetch Abort Vector  */
    ldr pc, =osEE_cortex_r_data_abt_vec     /* Data Abort Vector      */
    ldr pc, =osEE_cortex_r_dummy_hnd        /* Reserved               */
    ldr pc, =osEE_cortex_r_irq_vec          /* IRQ Vector             */
    ldr pc, =osEE_cortex_r_fiq_vec          /* FIQ Vector             */

/*=============================================================================
  =============================================================================
                   Exception Modes Vectors & Default Handlers
  =============================================================================
  ===========================================================================*/

  .section .text, "ax", %progbits
/*=============================================================================
                                Default Handlers
  ===========================================================================*/
  .global osEE_cortex_r_dummy_hnd
  .type osEE_cortex_r_dummy_hnd, %function
osEE_cortex_r_dummy_hnd:
    b  osEE_cortex_r_dummy_hnd
  .size osEE_cortex_r_dummy_hnd, . - osEE_cortex_r_dummy_hnd

  .weak osEE_cortex_r_und_inst_hnd
  .type osEE_cortex_r_und_inst_hnd, %function
osEE_cortex_r_und_inst_hnd:
    b  osEE_cortex_r_dummy_hnd
  .size osEE_cortex_r_und_inst_hnd, . - osEE_cortex_r_und_inst_hnd

  .weak osEE_cortex_r_svc_hnd
  .type osEE_cortex_r_svc_hnd, %function
osEE_cortex_r_svc_hnd:
    b  osEE_cortex_r_dummy_hnd
  .size osEE_cortex_r_svc_hnd, . - osEE_cortex_r_svc_hnd

  .weak osEE_cortex_r_prefetch_abt_hnd
  .type osEE_cortex_r_prefetch_abt_hnd, %function
osEE_cortex_r_prefetch_abt_hnd:
    b  osEE_cortex_r_dummy_hnd
  .size osEE_cortex_r_prefetch_abt_hnd, . - osEE_cortex_r_prefetch_abt_hnd

  .weak osEE_cortex_r_data_abt_hnd
  .type osEE_cortex_r_data_abt_hnd, %function
osEE_cortex_r_data_abt_hnd:
    b  osEE_cortex_r_dummy_hnd
  .size osEE_cortex_r_data_abt_hnd, . - osEE_cortex_r_data_abt_hnd

  .weak osEE_cortex_r_fiq_hnd
  .type osEE_cortex_r_fiq_hnd, %function
osEE_cortex_r_fiq_hnd:
    b  osEE_cortex_r_dummy_hnd
  .size osEE_cortex_r_fiq_hnd, . - osEE_cortex_r_fiq_hnd

/*=============================================================================
                              Exception Vectors
  ===========================================================================*/

/* Undefined Instruction Vector */
  .global osEE_cortex_r_und_inst_vec
  .type   osEE_cortex_r_und_inst_vec, % function
osEE_cortex_r_und_inst_vec:
    push  {r0-r3,r12,lr}            /* Save C scratch registers */
    sub   r0, lr, #4                /* Faulty Address to be passed to HND */

    blx   osEE_cortex_r_und_inst_hnd  /* Call C HND here */

    pop   {r0-r3,r12,lr}            /* Restore C scratch registers */
    movs  pc, lr                    /* return after faulty instruction */
  .size osEE_cortex_r_und_inst_vec, . - osEE_cortex_r_und_inst_vec

/* SWI/SVC Instructions Vector */
  .global osEE_cortex_r_svc_vec
  .type   osEE_cortex_r_svc_vec, % function
osEE_cortex_r_svc_vec:
    push    {r0-r3,r12,lr}      /* Save C scratch registers */
    tst     r0, #0x20           /* check the T bit */
    /* Conditional Instructions */
    ldrneh  r0, [lr,#-2]        /* Thumb mode */
    bicne   r0, r0, #0xff00     /* Thumb mode */
    ldreq   r0, [lr,#-4]        /* ARM mode */
    biceq   r0, r0, #0xff000000 /* ARM mode */

    blx     osEE_cortex_r_svc_hnd /* Call C HND here */

    pop     {r0-r3,r12,lr}      /* Restore state restore from compiled code */
    movs    pc, lr              /* Return after SVC/SWI Instruction */
  .size osEE_cortex_r_svc_vec, .-osEE_cortex_r_svc_vec

/* Instruction Prefetch Abort Exception Vector */
  .global osEE_cortex_r_prefetch_abt_vec
  .type   osEE_cortex_r_prefetch_abt_vec, % function
osEE_cortex_r_prefetch_abt_vec:
    push  {r0-r3,r12,lr}            /* Save C scratch registers */
    sub   r0, lr, #4                /* Faulty Address to be passed to HND */

    blx   osEE_cortex_r_prefetch_abt_hnd  /* Call C HND here */

    pop   {r0-r3,r12,lr}            /* Restore C scratch registers */
    subs  pc, lr, #4                /* Return to faulty instruction */
  .size osEE_cortex_r_prefetch_abt_vec, . - osEE_cortex_r_prefetch_abt_vec

/* Data Abort Exception Vector */
  .global osEE_cortex_r_data_abt_vec
  .type   osEE_cortex_r_data_abt_vec, % function
osEE_cortex_r_data_abt_vec:
    push  {r0-r3,r12,lr}            /* Save C scratch registers */
    sub   r0, lr, #8                /* Faulty Address to be passed to HND */

    blx   osEE_cortex_r_data_abt_hnd      /* Call C HND here */

    pop   {r0-r3,r12,lr}            /* Restore C scratch registers */
    subs  pc, lr, #8                /* Return to faulty instruction */
  .size osEE_cortex_r_data_abt_vec, . - osEE_cortex_r_data_abt_vec

/*=============================================================================
                              IRQ & FIQ Vectors
  ===========================================================================*/
  .equ    CPSR_MODE_SYS, 0x1F

  .global osEE_cortex_r_irq_vec
  .type   osEE_cortex_r_irq_vec, % function
osEE_cortex_r_irq_vec:
/* Prepare return address to Interrupted Instruction */
    sub     lr, lr, #4
/* ISR Save Status Step:1 Save LR_irq and SPSR_irq to System mode stack */
    srsfd   sp!,  #CPSR_MODE_SYS
/* Switch to System mode */
    cps     #CPSR_MODE_SYS
/* ISR Save Status Step:2 Save C scratch registers */
    push    {r0-r3,r12}
/* If VFPV3D16 is used ->
   ISR Save Status Step:3 Save floating point scratch registers */
#if (defined(OSEE_CORTEX_R_VFP))
    fmrx    r12, fpscr
    push    {r12}
    fmrx    r12, fpexc
    push    {r12}
    fstmfdd sp!, {d0-d7}
#endif /* OSEE_CORTEX_R_VFP */

/* Align stack to a 8 Byte boundary */
    and     r3, sp, #3    /* Calculate Stack adjustment to 8 byte boundary */
    sub     sp, sp, r3    /* Adjust System Stack */
    push    {r3,lr}       /* Put Stack adjustment and System Mode LR on Stack */

/* Call Second Level IRQ HND C routine. Passing Pointer to saved OsEE_ISR_CTX */
    mov     r0, sp
    blx     osEE_cortex_r_irq_hnd

/* Undo stack alignment & restore System Mode LR */
    pop     {r3,lr}       /* Stack adjustment and MODE_SYS LR (= MODE_USR LR) */
    add     sp, sp, r3    /* Undo System Stack (= USR Stack) adjustment */

/* If VFPV3D16 is used -> Restore Save floating point scratch registers */
#if (defined(OSEE_CORTEX_R_VFP))
    fldmfdd sp!, {d0-d7}
    pop     {r12}
    fmxr    fpexc, r12
    pop     {r12}
    fmxr    fpscr, r12
#endif /* OSEE_CORTEX_R_VFP */
/* Restore C scratch registers */
    pop     {r0-r3, r12}

/* Return using RFE from System Mode Stack
   (popping LR_irq and SPSR_irq, saved by srsfd) */
    rfefd   sp!
  .size osEE_cortex_r_irq_vec, . - osEE_cortex_r_irq_vec

  .global osEE_cortex_r_fiq_vec
  .global osEE_cortex_r_fiq_loop
  .type osEE_cortex_r_fiq_vec,  %function
  .type osEE_cortex_r_fiq_loop, %function
osEE_cortex_r_fiq_vec:
    push {r0-r3,r12,lr}                 /* Save C scratch registers */
osEE_cortex_r_fiq_loop:
    blx  osEE_cortex_r_fiq_hnd            /* Call C HND here */
    pop  {r0-r3,r12,lr}                 /* Restore C scratch registers */
    subs  pc, lr, #4                    /* Return to interrupted instruction */
  .size osEE_cortex_r_fiq_vec, . - osEE_cortex_r_fiq_vec
  .size osEE_cortex_r_fiq_loop, . - osEE_cortex_r_fiq_loop


