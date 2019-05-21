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

/** \file   r_synch.c
 *  \brief  Software barrier implementation, preferred over hardware barr since
 *          I want to know which cores has been the last to leave the barrier.
 *
 *  \author Errico Gudieri
 *  \date   2018
 */

#include "r_prj.h"


/*#############################################################################
 # local types
 #############################################################################*/

/******************************************************************************
 * PE activation state
 *****************************************************************************/
typedef struct {
  StatusType            ev;
  OsEE_bool   volatile  valid;
} synch_act_status;


/******************************************************************************
 * synchronization locals
 *****************************************************************************/
typedef struct
{
  OsEE_barrier      app_barrier;
  CoreMaskType      app_core_mask;
  synch_act_status  app_conc_act_rv[OS_CORE_ID_ARR_SIZE];

} synch_state_t;


/*#############################################################################
 # local variables
 ############################################################################*/

/******************************************************************************
 * PE synchronization state
 *****************************************************************************/
static synch_state_t g_synch;


/*#############################################################################
 # local functions
 ############################################################################*/


/******************************************************************************
 * Function Name : osEE_rh850_set_bit_l
 * Description   : set MEV
 * Arguments     : p_barr   = pointer to ERIKA barrier structure
 *               : p_wait_mask  = time to wait in PE ticks
 * Return Value  : none
 *****************************************************************************/
__asm volatile static void
  synch_rh850_set_bit_l(OsEE_reg volatile * p_mem, OsEE_reg bit_pos)
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
/* Seems that two snoozes are needed to guarantee the opportunity to commit
   changes */
  snooze
  snooze
  br      mem_r
mem_w:
}


/******************************************************************************
 * Function Name : osEE_rh850_cmpswapw_l
 * Description   : swap MEV
 * Arguments     : p_mem    = memory to swap
 *         : exp_value  = current value
 *         : new_value    = new value to store
 * Return Value  : none
 *****************************************************************************/
__asm volatile static OsEE_reg
  synch_rh850_cmpswapw_l(OsEE_reg volatile * p_mem, OsEE_reg exp_value,
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
/* Seems that two snoozes are needed to guarantee the opportunity to commit
   changes */
  snooze
  snooze
  br      cmp_swap
not_swap:
/* If p_mem value is not the expected one, clear the load link. */
  cll
swapped:
}


/*#############################################################################
 # API
 ############################################################################*/


/******************************************************************************
 * Function Name : R_SYNC_ManageBarrier
 * Description   : manage mutual exclusion between PEs
 * Arguments     : none
 * Return Value  : none
 *******************************************************************************/
OsEE_bool R_SYNCH_ManageBarrier(void)
{
  OsEE_bool is_last = OSEE_FALSE;
  CoreMaskType const exit_mask  = (0xFFFFFFFFU ^
    (((CoreMaskType)0x1U << OS_CORE_ID_ARR_SIZE) - 1U));

  OsEE_reg wait_mask, all_exited;

  /* If not all cores have left the previous use of this barrier
       wait for it. */
  while ((g_synch.app_barrier.value & exit_mask) != 0U)
  {
    _snooze();
  }

  /* Set current CPU as entered */
  synch_rh850_set_bit_l(&g_synch.app_barrier.value,
    (OsEE_reg)osEE_get_curr_core_id());

  /* Snapshot of the wait mask */
  wait_mask = g_synch.app_core_mask;
  while ((g_synch.app_barrier.value & wait_mask) != wait_mask)
  {
    /* Wait for all other cores/CPUs */
    /* Refresh the snapshot of the wait mask */
    _snooze();
    wait_mask = g_synch.app_core_mask;
  }

  all_exited = (wait_mask << OS_CORE_ID_ARR_SIZE) | wait_mask;

  /* Set current CPU as exited */
  synch_rh850_set_bit_l(&g_synch.app_barrier.value,
    ((OsEE_reg)osEE_get_curr_core_id() + (OsEE_reg)OS_CORE_ID_ARR_SIZE));

  /* Try to reset the barrier */
  is_last =
    (synch_rh850_cmpswapw_l(&g_synch.app_barrier.value, all_exited, 0U) ==
      all_exited);

  /* Force the emptying of the Write Buffer */
  __memory_barrier();
  /* WR Diab Documentation says that intrinsics may be reordered, so _syncm();
     is not exactly what we want. */

  return is_last;
}

/******************************************************************************
 * Function Name : R_SYNCH_InitBarrier
 * Description   : initialize mutual exclusion
 * Arguments     : none
 * Return Value  : none
 *****************************************************************************/
void R_SYNCH_InitBarrier(void) {
  CoreNumType core_num;

  g_synch.app_barrier.value = 0U;
  g_synch.app_core_mask     = 0U;

  for (core_num = OS_CORE_ID_0; core_num < OS_CORE_ID_ARR_SIZE; ++core_num)
  {
    g_synch.app_conc_act_rv[core_num].ev    = E_OS_LIMIT;
    g_synch.app_conc_act_rv[core_num].valid = OSEE_FALSE;
  }
}

/******************************************************************************
 * Function Name : R_SYNC_SetPeActive
 * Description   : update local mask of active Processor Elements (PEs)
 * Arguments     : mask   = PE to add
 * Return Value  : none
 *****************************************************************************/
void R_SYNCH_SetPeActive(CoreMaskType mask)
{
  g_synch.app_core_mask |= mask;
}


/******************************************************************************
 * Function Name : R_SYNCH_GetPeValid
 * Description   : check if requested PE is valid
 * Arguments     : core   = PE
 * Return Value  : is PE valid
 *****************************************************************************/
OsEE_bool R_SYNCH_GetPeValid(CoreNumType core)
{
  return g_synch.app_conc_act_rv[core].valid;
}


/******************************************************************************
 * Function Name : R_SYNCH_SetPeValid
 * Description   : configure PE valid flag as requested
 * Arguments     : core   = PE
 *         : valid    = valid/invalid
 * Return Value  : none
 *****************************************************************************/
void R_SYNCH_SetPeValid(CoreNumType core, OsEE_bool valid)
{
  g_synch.app_conc_act_rv[core].valid = valid;
}


/******************************************************************************
 * Function Name : R_SYNC_GetPeStatus
 * Description   : return PE structure status
 * Arguments     : core   = PE
 * Return Value  : PE structure status
 *****************************************************************************/
StatusType R_SYNCH_GetPeStatus(CoreNumType core)
{
  return g_synch.app_conc_act_rv[core].ev;

}


/******************************************************************************
 * Function Name : R_SYNC_SetPeStatus
 * Description   : return PE structure status
 * Arguments     : core   = PE
 *         : ev   = status
 * Return Value  : PE structure status
 *****************************************************************************/
void R_SYNCH_SetPeStatus(CoreNumType core, StatusType ev)
{
  g_synch.app_conc_act_rv[core].ev = ev;

}

