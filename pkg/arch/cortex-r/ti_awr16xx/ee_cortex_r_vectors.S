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
 

;==============================================================================
;                               Exception Vector
;============================================================================== 
#include "ee_arch_override.h"

    .sect ".intvecs"
    .arm

;-- ID of System Mode
CPSR_MODE_SYS  .equ    (0x1FU)

;-------------------------------------------------------------------------------
; interrupt vectors
    .def _osEE_cortex_r_intvec
    .asmfunc
_osEE_cortex_r_intvec
  b   osEE_cortex_r_reset_vec        ; Reset Vector
  b   osEE_cortex_r_und_inst_vec     ; Und Vector
  b   osEE_cortex_r_svc_vec          ; SVC Vector
  b   osEE_cortex_r_prefetch_abt_vec ; Prefetch Abort Vector
  b   osEE_cortex_r_data_abt_vec     ; Data Abort Vector
  b   osEE_cortex_r_reserved_vec     ; Reserved
  b   osEE_cortex_r_irq_vec          ; IRQ Vector
; Placing the FIQ handler here to avoid the branching
    .def osEE_cortex_r_fiq_vec
osEE_cortex_r_fiq_vec
    sub      lr, lr, #4
    srsdb    sp!, #CPSR_MODE_SYS    ; Save LR_irq and SPSR_irq to SYS stack
    cps      #CPSR_MODE_SYS         ; Switch to System mode
    push     {r0-r3, r12, lr}       ; Store normal scratch registers
    blx      osEE_cortex_r_fiq_hnd  ; jump to the handler
    pop      {r0-r3, r12, lr}       ; Restore registers
    rfeia    sp!                    ; Return using RFE from System mode stack
  .endasmfunc
;=============================================================================
;                               Reset Handler
;=============================================================================
  .sect ".startup"
; ARM Cortex R4 Reset handler - startup code
    .global   _c_int00
    .def      osEE_cortex_r_reset_vec
    .asmfunc
osEE_cortex_r_reset_vec
    bl    _c_int00
  ; Done, loop forever
LOOP0:
    b      LOOP0
  .endasmfunc

;==============================================================================
;                               Default Handlers
;==============================================================================
;-- Default Vectors are located in .startup section
  .sect ".startup"

  .weak osEE_cortex_r_und_inst_hnd
  .asmfunc
osEE_cortex_r_und_inst_hnd
    b  osEE_cortex_r_und_inst_hnd
  .endasmfunc

  .weak osEE_cortex_r_svc_hnd
  .asmfunc
osEE_cortex_r_svc_hnd
    b  osEE_cortex_r_svc_hnd
  .endasmfunc

  .weak osEE_cortex_r_prefetch_abt_hnd
  .asmfunc
osEE_cortex_r_prefetch_abt_hnd
    b  osEE_cortex_r_prefetch_abt_hnd
  .endasmfunc

  .weak osEE_cortex_r_data_abt_hnd
  .asmfunc
osEE_cortex_r_data_abt_hnd
    b  osEE_cortex_r_data_abt_hnd
  .endasmfunc

  .weak osEE_cortex_r_fiq_hnd
  .asmfunc
osEE_cortex_r_fiq_hnd
    b  osEE_cortex_r_fiq_hnd
  .endasmfunc

;==============================================================================
;                            Exception Vectors
;==============================================================================
/* Table 11-3 Link Register Adjustments ARM DEN 0042A ID041714
  Exception     Adjustment  Return instruction  Instruction returned to
    SVC             0         MOVS PC, R14        Next instruction
    Undef           0         MOVS PC, R14        Next instruction
    Prefetch Abort  -4        SUBS PC, R14, #4    Aborting instruction
    Data abort      -8        SUBS PC, R14, #8    Aborting instruction (precise)
    IRQ             -4        SUBS PC, R14, #4    Next instruction
    FIQ             -4        SUBS PC, R14, #4    Next instruction
*/
  .text

;------------------------------------------------------------------------------
; ARM undefined instruction exception handler
  .def     osEE_cortex_r_und_inst_vec
  .asmfunc
osEE_cortex_r_und_inst_vec
    push  {r0-r3,r12,lr}              ; Save C scratch registers
    sub   r0, lr, #4                  ; Faulty Address to be passed to HND
    blx   osEE_cortex_r_und_inst_hnd  ; Call C HND here
    pop   {r0-r3,r12,lr}              ; Restore C scratch registers
    movs  pc, lr                      ; return after faulty instruction
  .endasmfunc

;------------------------------------------------------------------------------
; SWI/SVC Instructions Vector
  .def osEE_cortex_r_svc_vec
  .asmfunc
osEE_cortex_r_svc_vec
    srsdb    sp!, #CPSR_MODE_SYS      ; Save LR_svc and SPSR_svc to System mode stack
    cps      #CPSR_MODE_SYS           ; Switch to System mode
    push     {r0-r3, r12, lr}         ; Store normal scratch registers
    cmp      r0, #0
    bne      HND
; Do not Call The handler but simply switch in supervisor mode
; This is needed by mmWave SDK initialization
    add      r2, sp, #28              ; get address of stack saved SPSR_svc
    ldr      r0, [r2]
    bic      r0, r0, #0x0000001F      ; clear mode bits
    orr      r0, r0, #CPSR_MODE_SYS   ; modify spsr mode bits to system mode
    str      r0, [r2]
    b        RTN
HND:
; Conditional Instructions
    tst     r0, #0x20               ; check the T bit
    ldrneh  r0, [lr,#-2]            ; Thumb mode
    bicne   r0, r0, #0xff00         ; Thumb mode
    ldreq   r0, [lr,#-4]            ; ARM mode
    biceq   r0, r0, #0xff000000     ; ARM mode
    blx     osEE_cortex_r_svc_hnd   ; Call C HND here
RTN:
    pop      {r0-r3, r12, lr}       ; Restore registers
    rfeia    sp!                    ; Return using RFE from System mode stack
  .endasmfunc
;------------------------------------------------------------------------------
; Instruction Prefetch Abort Exception Vector
  .def osEE_cortex_r_prefetch_abt_vec
  .asmfunc
osEE_cortex_r_prefetch_abt_vec:
    push  {r0-r3,r12,lr}            ; Save C scratch registers
    sub   r0, lr, #4                ; Faulty Address to be passed to HND

    blx   osEE_cortex_r_prefetch_abt_hnd  ; Call C HND here

    pop   {r0-r3,r12,lr}            ; Restore C scratch registers
    subs  pc, lr, #4                ; Return to faulty instruction
  .endasmfunc

;------------------------------------------------------------------------------
; Data Abort Exception Vector
  .def osEE_cortex_r_data_abt_vec
  .asmfunc
osEE_cortex_r_data_abt_vec:
    push  {r0-r3,r12,lr}            ; Save C scratch registers
    sub   r0, lr, #8                ; Faulty Address to be passed to HND

    blx   osEE_cortex_r_data_abt_hnd  ; Call C HND here

    pop   {r0-r3,r12,lr}            ; Restore C scratch registers
    subs  pc, lr, #8                ; Return to faulty instruction
  .endasmfunc

;------------------------------------------------------------------------------
; Reserved Exception Vector
  .def osEE_cortex_r_reserved_vec
  .asmfunc
osEE_cortex_r_reserved_vec
    b  osEE_cortex_r_reserved_vec
  .endasmfunc
;==============================================================================
;                              IRQ Vector
;==============================================================================
  .sect ".startup"

  .global osEE_cortex_r_irq_hnd

  .def    osEE_cortex_r_irq_vec
  .asmfunc
osEE_cortex_r_irq_vec:
; Prepare return address to Interrupted Instruction
    sub     lr, lr, #4
; ISR Save Status Step:1 Save LR_irq and SPSR_irq to System mode stack
    srsfd   sp!,  #CPSR_MODE_SYS
; Switch to System mode
    cps     #CPSR_MODE_SYS
; ISR Save Status Step:2 Save C scratch registers
    push    {r0-r3,r12}
; If VFPV3D16 is used ->
#if (defined(OSEE_CORTEX_R_VFP))
; ISR Save Status Step:3 Save floating point scratch registers
    fmrx    r12, fpscr
    push    {r12}
    fmrx    r12, fpexc
    push    {r12}
    vpush   {d0-d7}
#endif /* OSEE_CORTEX_R_VFP */

; Align stack to a 8 Byte boundary
    and     r3, sp, #3    ; Calculate Stack adjustment to 8 byte boundary
    sub     sp, sp, r3    ; Adjust System Stack
    push    {r3,lr}       ; Put Stack adjustment and System Mode LR on Stack

; Call Second Level IRQ HND C routine. Passing Pointer to saved OsEE_ISR_CTX
    mov     r0, sp
    blx     osEE_cortex_r_irq_hnd

; Undo stack alignment & restore System Mode LR
    pop     {r3,lr}       ; Stack adjustment and MODE_SYS LR (= MODE_USR LR)
    add     sp, sp, r3    ; Undo System Stack (= USR Stack) adjustment

#if (defined(OSEE_CORTEX_R_VFP))
; If VFPV3D16 is used -> Restore Save floating point scratch registers
    vpop    {d0-d7}
    pop     {r12}
    fmxr    fpexc, r12
    pop     {r12}
    fmxr    fpscr, r12
#endif /* OSEE_CORTEX_R_VFP */
; Restore C scratch registers
    pop     {r0-r3, r12}

; Return using RFE from System Mode Stack
; (popping LR_irq and SPSR_irq, saved by srsfd)
    rfefd   sp!
  .endasmfunc

