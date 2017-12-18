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

## \file  ee_k1_wrapper.S
## \brief  TO BE DOCUMENTED!!!
##
## \note  TO BE DOCUMENTED!!!
##
## \author  Errico Guidieri
## \date  2016

#include <HAL/hal/hal.h>
#include "HAL/hal/context.h"
#include "mOS_common_types_s_c.h"

.section .locked_text, "ax", @progbits
.align 8
.global osEE_k1_interrupt_wrapper
.proc osEE_k1_interrupt_wrapper
ee_k1_interrupt_wrapper:
# Prepare the Function Frame (16)
  add $r12, $r12, -16
  ;;
# Save two callee registers without any specific meaning to use as temp
# variables.
# Read the process Identification Register $pi indocumentation file
  sd 0[$r12] = $p16
  make $r16 = _scoreboard_start
  get $r17, $pcr
  ;;
# Extract PID bitfiled from $pcr
  extfz $r17, $r17, 15, 11
  ;;
# PID * MOS_SCOREBOARD_PER_CPU_ELEMENT_SIZE (=256) => PID << 8
  sll $r17, $r17, 8
  ;;
# $r16 = $_scoreboard_start.SCB_VCORE.PER_CPU[pid]
  add $r16, $r16, $r17
  ;;
# Load the Shadow Stack Pointer and reserve the space for a Context
# The Shadow Stack Pointer at this point contains th SP of the preempted stack
# I want to save the context (that is the preempted context) to the previous
# stack
  lw $r17 = MOS_VC_REG_SSP[$r16]
  ;;
  add $r17, $r17, -_K1_VCONTEXT64_SIZE
  ;;
# Save to the stack the new $r16 and $r17
# (_vk1_context64_save don't clobber these, so useless)
  sd 8[$r12], $p16
  ;;
  _vk1_context64_save $r17
  ;;
# Reload previous to saving $r16 ($_scoreboard_start.SCB_VCORE.PER_CPU[pid])
# and $r17 (SSP) in $r0 and $r1 (useless, it's still in $r16)
  ld $p0 = 8[$r12]
  ;;
# Load originals (before ee_k1_interrupt_wrapper call) $r16 and $r17 and set
# them in the saved context to made it coherent
  ld $p2, 0[$r12]
  ;;
  sd _K1_CONTEXT_P16[$r17], $p2
  ;;
# Get the Virtual PS + Set the ctx pointer as second parameter for __k1_do_int
  lw $r0 = MOS_VC_REG_PS[ $r0 ]
  copy   $r1, $r17
  ;;
# Set the IRQ ID (VC.PS.EC) as __k1_do_int first parameter
# Prepare the Scratch Stack (16) for called function __k1_do_int
  srl $r0 = $r0, 28
  add   $r12, $r12, -16
  call  __k1_do_int            ## jump to C code
    ;;
# Unwind the Stack (Scratch Stack + this function frame = 32) +
# Get Scoreboard Base +
# Get PCR
  add   $r12, $r12, 32
  make $r0 = _scoreboard_start
  get $r1, $pcr
  ;;
# Get PID
  extfz $r1, $r1, 15, 11
  ;;
# $r1 = PID * MOS_SCOREBOARD_PER_CPU_ELEMENT_SIZE (=256) => PID << 8
  sll $r1, $r1, 8
  ;;
# $r0 = $_scoreboard_start.SCB_VCORE.PER_CPU[pid]
  add $r0, $r0, $r1
  ;;
  lw $r13 = MOS_VC_REG_SSP[$r0]
  ;;
  add $r13, $r13, -_K1_VCONTEXT64_SIZE
  ;;
  _vk1_context64_restore $r13
  ;;
  scall MOS_VC_RFE
  ;;
  #I CANNOT FIND INFORMATION ABOUT THIS DIRECTIVE. I suppose that the effect is
  #equal to: .size ee_k1_interrupt_wrapper, .-ee_k1_interrupt_wrapper
  .endp osEE_k1_interrupt_wrapper

#==============================================================================#
#if 0 /* Not Needed !!! */
.section .locked_text, "ax", @progbits
.align 8
.global osEE_os_int_context_restore
.proc osEE_os_int_context_restore
osEE_os_int_context_restore:
# Use r13 to restore the stack
  copy $r13, $r0
  ;;
# The set back of the stack it's done here!
  _vk1_context64_restore $r13
  ;;
# Stack Unwind
  add   $r12, $r12, _K1_VCONTEXT64_SIZE
  ;;
# Ret need it's own bundle
  ret
  ;;
  .endp __vk1_asm_interrupt_handler
#endif /* 0 */

#==============================================================================#

.section .text, "ax", @progbits
.align 8
.global osEE_os_scall

.section .text, "ax", @progbits
.global osEE_k1_scall_wrapper
.proc osEE_k1_scall_wrapper
.type   ee_k1_scall_wrapper, @function
osEE_k1_scall_wrapper:
# Prepare the Function Frame (16)
# Read the Return Address
add $r12 = $r12, -32
get $r8 = $ra
;;
# Save $r10 on the stack and make it equal to $r7
copy $r10 = $r7
sw 16 [$r12] = $r10
;;
sw 20 [$r12] = $r8
add $r12 = $r12, -16
call osEE_os_scall
;;
add $r12 = $r12, 16
;;
lw $r8 = 20 [$r12]
;;
lw $r10 = 16 [$r12]
add $r12 = $r12, 32
;;
set $ra = $r8
;;
scall MOS_VC_RFE
;;
ret
;;
.endp

