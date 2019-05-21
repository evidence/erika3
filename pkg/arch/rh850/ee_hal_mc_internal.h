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
 * ###*E*### */

/** \file   ee_hal.h
 *  \brief  HAL support NOT visible to the application, for multi-core
 *          applications.
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#ifndef OSEE_HAL_MC_INTERNAL_H
#define OSEE_HAL_MC_INTERNAL_H

#include "ee_cfg.h"

#if (!defined(OSEE_SINGLECORE))

#include "ee_hal_mc.h"
#include "ee_kernel_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/******************************************************************************
                              Barrier HAL
 *****************************************************************************/

void osEE_hal_sync_barrier(OsEE_barrier * p_barr,
  OsEE_reg const volatile * p_wait_mask, OsEE_kernel_cb p_synch_cb);

#if 0 /* Moved in asm file */
__asm volatile static void
  osEE_rh850_set_bit_l(OsEE_reg volatile * p_mem, OsEE_reg bit_pos)
{
% reg p_mem, bit_pos; lab mem_r, mem_w;
! "r8", "r9"

  mov     1,        r8
/* Logical shift left r7(1) of bit value (saving in r7)*/
  shl     bit_pos,  r8
mem_r:
/* Load and Link p_mem */
  ldl.w   [p_mem],  r9
/* Set the bit in position "bit_pos" */
  or      r8,       r9
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r9 */
  stc.w   r9,       [p_mem]
/* If for some reason the link has been broken: retry */
  cmp     r0,       r9
  bnz     mem_w
/* It seems that 2 snooze are needed to give to opportunity to commit
   changes in any case */
  snooze
  snooze
  br      mem_r
mem_w:
}

__asm volatile static OsEE_reg
  osEE_rh850_cmpswapw_l(OsEE_reg volatile * p_mem, OsEE_reg exp_value,
    OsEE_reg new_value)
{
% reg p_mem, exp_value, new_value; lab cmp_swap, not_swap, swapped;
! "r9", "r10"

/* Load and Link p_mem */
cmp_swap:
  ldl.w   [p_mem],    r10
  cmp     exp_value,  r10
/* In p_mem is not stored exp_value-> Not Swap */
  bnz     not_swap
  mov     new_value,  r9
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r9 */
  stc.w   r9,         [p_mem]
  cmp     r0,         r9
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
}
#else
/* Moved in asm file */
extern void osEE_rh850_set_bit_l(OsEE_reg volatile * p_mem, OsEE_reg bit_pos);
extern OsEE_reg osEE_rh850_cmpswapw_l(OsEE_reg volatile * p_mem,
  OsEE_reg exp_value, OsEE_reg new_value);
#endif
/******************************************************************************
                            Multicore CPU Startup
 *****************************************************************************/

void osEE_hal_start_core(CoreIdType core_id);

/******************************************************************************
                            Multicore CPU Signal
 *****************************************************************************/

extern void osEE_rh850_setup_inter_irqs(void);

/* Signal the core "cpu" (0/1/2/3/4/5) by sending an IIRQ. */
extern void osEE_hal_signal_core(CoreIdType core_id);

/* Acknowledge the signal received by the core "cpu" (0/1/2/3/4/5) */
extern void osEE_rh850_ack_signal(void);

#if (defined(OSEE_ALLOW_TASK_MIGRATION))
extern void osEE_hal_signal_broadcast(void);
#endif /* OSEE_ALLOW_TASK_MIGRATION */

extern void osEE_rh850_ipir_preemption_point(OsEE_KDB * p_kdb);

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_SINGLECORE */
#endif /* !OSEE_HAL_MC_INTERNAL_H */

