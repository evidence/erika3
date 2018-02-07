# ###*B*###
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

## \file  ee_aarch64_headers.S
## \brief Jailhouse cell start-up code
##
## This file contains the functions to save and restore registers for
## context switch.
##
## \author  Errico Guidieri
## \date    2017

#===============================================================================
#                 ISR Handling (Only for AArch64 architecture)
#===============================================================================

#typedef struct OsEE_ISR_CTX_tag {
#  OsEE_reg x0;
#  OsEE_reg x1;
#  OsEE_reg x2;
#  OsEE_reg x3;
#  OsEE_reg x4;
#  OsEE_reg x5;
#  OsEE_reg x6;
#  OsEE_reg x7;
#  OsEE_reg x8;
#  OsEE_reg x9;
#  OsEE_reg x10;
#  OsEE_reg x11;
#  OsEE_reg x12;
#  OsEE_reg x13;
#  OsEE_reg x14;
#  OsEE_reg x15;
#  OsEE_reg x16;
#  OsEE_reg x17;
#  OsEE_reg x18;
#  OsEE_reg x30_lr;
#  OsEE_reg elr_el1;
#  OsEE_reg spsr_el1;
#} OsEE_ISR_CTX;

  .equ  OSEE_ISR_CTX_SIZE,176

  .globl osEE_aarch64_exception_entry
  .type osEE_aarch64_exception_entry, @function

osEE_aarch64_exception_entry:
  stp x0 , x1 , [sp, #-OSEE_ISR_CTX_SIZE]!
  stp x2 , x3 , [sp, #16]
  stp x4 , x5 , [sp, #32]
  stp x6 , x7 , [sp, #48]
  stp x8 , x9 , [sp, #64]
  stp x10, x11, [sp, #80]
  stp x12, x13, [sp, #96]
  stp x14, x15, [sp, #112]
  stp x16, x17, [sp, #128]
  stp x18, x30, [sp, #144]
  mrs x2 , elr_el1
  mrs x3 , spsr_el1
  stp x2 , x3 , [sp, #160]
  mov x0 , sp
  bl osEE_aarch64_isr_wrapper
  ldp x2 , x3,  [sp, #160]
  msr elr_el1, x2
  msr spsr_el1, x3
  ldp x0 , x1,  [sp]
  ldp x2 , x3 , [sp, #16]
  ldp x4 , x5 , [sp, #32]
  ldp x6 , x7 , [sp, #48]
  ldp x8 , x9 , [sp, #64]
  ldp x10, x11, [sp, #80]
  ldp x12, x13, [sp, #96]
  ldp x14, x15, [sp, #112]
  ldp x16, x17, [sp, #128]
  ldp x18, x30, [sp, #144]
  add sp, sp, #OSEE_ISR_CTX_SIZE
  eret
  .size osEE_aarch64_exception_entry, .-osEE_aarch64_exception_entry

  .section ".osee_boot", "ax"
  .globl __osEE_reset_entry
  .type __osEE_reset_entry, @function
__osEE_reset_entry:
# Populate vector base address registers for EL1
  ldr x0, =osEE_aarch64_vectors
  msr	vbar_el1, x0
# Initializate the Stack Pointer
  ldr	x0, =stack_top
  mov	sp, x0
# Enable the floating point and vector instructions in EL1 and EL0
  mov x0, #(3 << 20)
  msr cpacr_el1, x0
# Enable all kind of "exceptions" but interrupts
# (ERIKA's poilicy is doing it in StartOS)
# msr daif, xzr
  msr daifclr, #0xD
# Syncronize all the changes
  isb
# Jump to C code
  b osEE_c_start
  .size __osEE_reset_entry, .-__osEE_reset_entry

#if 1
.macro osEE_aarch64_ventry label jump
  .globl \label
  .align  7
\label:
  b \jump
.endm

## ERIKA Exceptions Vector
  .globl osEE_aarch64_vectors
  .align 11
osEE_aarch64_vectors:
  osEE_aarch64_ventry  osEE_aarch64_SynchronousExceptionSP0 .
  osEE_aarch64_ventry  osEE_aarch64_IrqSP0 .
  osEE_aarch64_ventry  osEE_aarch64_FiqSP0 .
  osEE_aarch64_ventry  osEE_aarch64_SErrorSP0 .

  osEE_aarch64_ventry  osEE_aarch64_SynchronousExceptionSPx .
  osEE_aarch64_ventry  osEE_aarch64_IrqSPx osEE_aarch64_exception_entry
  osEE_aarch64_ventry  osEE_aarch64_FiqSPx .
  osEE_aarch64_ventry  osEE_aarch64_SErrorSPx .

  osEE_aarch64_ventry  osEE_aarch64_SynchronousExceptionA64 .
  osEE_aarch64_ventry  osEE_aarch64_IrqA64 osEE_aarch64_exception_entry
  osEE_aarch64_ventry  osEE_aarch64_FiqA64 .
  osEE_aarch64_ventry  osEE_aarch64_SErrorA64 .

  osEE_aarch64_ventry  osEE_aarch64_SynchronousExceptionA32 .
  osEE_aarch64_ventry  osEE_aarch64_IrqA32 .
  osEE_aarch64_ventry  osEE_aarch64_FiqA32 .
  osEE_aarch64_ventry  osEE_aarch64_SErrorA32 .
#else
## ERIKA Exceptions Vector
  .globl osEE_aarch64_vectors
  .align 11
osEE_aarch64_vectors:
  /* -----------------------------------------------------
   * Current EL with SP0 : 0x0 - 0x200
   * -----------------------------------------------------
   */
#1
  .globl osEE_aarch64_SynchronousExceptionSP0
  .align  7
osEE_aarch64_SynchronousExceptionSP0:
  b .
#2
  .globl osEE_aarch64_IrqSP0
  .align  7
osEE_aarch64_IrqSP0:
  b .
#3
  .align  7
  .globl osEE_aarch64_FiqSP0
osEE_aarch64_FiqSP0:
  b .
#4
  .globl osEE_aarch64_SErrorSP0
  .align  7
osEE_aarch64_SErrorSP0:
  b .
  /* -----------------------------------------------------
   * Current EL with SPx: 0x200 - 0x400
   * -----------------------------------------------------
   */
#5
  .globl osEE_aarch64_SynchronousExceptionSPx
  .align  7
osEE_aarch64_SynchronousExceptionSPx:
  b .
#6
  .globl osEE_aarch64_IrqSPx
  .align  7
osEE_aarch64_IrqSPx:
  b osEE_aarch64_exception_entry
#7
  .global osEE_aarch64_FiqSPx
  .align  7
osEE_aarch64_FiqSPx:
  b .
#8
  .global osEE_aarch64_SErrorSPx
  .align  7
osEE_aarch64_SErrorSPx:
  b .
  /* -----------------------------------------------------
   * Lower EL using AArch64 : 0x400 - 0x600
   * -----------------------------------------------------
   */
#9
  .global osEE_aarch64_SynchronousExceptionA64
  .align  7
osEE_aarch64_SynchronousExceptionA64:
  b .
#10
  .global osEE_aarch64_IrqA64
  .align  7
osEE_aarch64_IrqA64:
  b osEE_aarch64_exception_entry
#11
  .global osEE_aarch64_FiqA64
  .align  7
osEE_aarch64_FiqA64:
  b .
#12
  .global osEE_aarch64_SErrorA64
  .align  7
osEE_aarch64_SErrorA64:
  b .
  /* -----------------------------------------------------
   * Lower EL using AArch32 : 0x600 - 0x800
   * -----------------------------------------------------
   */
#13
  .global osEE_aarch64_SynchronousExceptionA32
  .align  7
osEE_aarch64_SynchronousExceptionA32:
  b .
#14
  .global osEE_aarch64_IrqA32
  .align  7
osEE_aarch64_IrqA32:
  b .
#15
  .global osEE_aarch64_FiqA32
  .align  7
osEE_aarch64_FiqA32:
  b .
#16
  .global osEE_aarch64_SErrorA32
  .align  7
osEE_aarch64_SErrorA32:
  b .
#endif

# XXX: Important (?)
# Allocate a Litteral Pool here (to handle =symbol pseudo-instructions operands)
  .ltorg

