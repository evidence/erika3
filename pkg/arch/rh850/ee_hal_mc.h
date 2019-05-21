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
 *  \brief  HAL support visible to the application, needed for
 *          inline implementation of ee_get_kernel_and_core.h.
 *          That file needs to declare kernel data structures so has to belong
 *          to conf interface, so this file has to have conf visibility at
 *          least, to allow inline implementation ee_get_kernel_and_core
 *          functions.
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#ifndef OSEE_HAL_MC_H
#define OSEE_HAL_MC_H

#include "ee_cfg.h"

#if (!defined(OSEE_SINGLECORE))

#include "ee_platform_types.h"
#include "ee_kernel_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/******************************************************************************
                              Spinlocks HAL
 *****************************************************************************/

/** @brief Acquire a spin-lock, spin inside if the spin-lock is already busy.
    @param p_lock spin-lock to be acquired. */
#if 0 /* Moved in asm file */
__asm volatile static void osEE_hal_spin_lock(OsEE_spin_lock * p_lock)
{
% reg p_lock ; lab lock, lock_wait, lock_success;
! "r7", "r8"
/* Prepare lock value */
  mov    1,         r8
lock:
/* Load and Link p_lock */
  ldl.w  [p_lock],  r7
/* Remember: r0 is a zero register */
  cmp    r0,        r7
  bnz    lock_wait
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r8 */
  stc.w  r8,        [p_lock]
  cmp    r0,        r8
  bnz    lock_success
lock_wait:
/* Release the link & snooze */
  cll
/* It seems that 2 snooze are needed to give to opportunity to commit
   changes in any case */
  snooze
  snooze
  br     lock
lock_success:
}

/** @brief Try to acquire a spin-lock, immediately exit if it is already busy.
    @param spin_id spin-lock to be acquired id. */
__asm volatile static OsEE_bool osEE_hal_try_spin_lock(OsEE_spin_lock * p_lock)
{
% reg p_lock; lab lock_fail;
! "r7" "r8" "r10"
/* Prepare fail return value */
  mov    0,         r10
/* Prepare lock value */
  mov    1,         r8
/* Load and Link p_lock */
  ldl.w  [p_lock],  r7
/* Remember: r0 is a zero register */
  cmp    r0,        r7
  bnz    lock_fail
/* stc.x Save the result of the store [0,1] on source register. In this case:
         r8 */
  stc.w  r8,        [p_lock]
  cmp    r0,        r8
  bz     lock_fail
/* Set success return value */
  mov    1,         r10
lock_fail:
/* Release the link before leave the block */
  cll
}
#else
/* Moved in asm file */
extern void osEE_hal_spin_lock(OsEE_spin_lock * p_lock);
extern OsEE_bool osEE_hal_try_spin_lock(OsEE_spin_lock * p_lock);
#endif

/** @brief Release a spin lock
    @param p_lock spin-lock to be released id */
OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_hal_spin_unlock(OsEE_spin_lock * p_lock)
{
  /* Force the emptying of the write buffer,
     assuring that the writes are all done */
  __memory_barrier();
  /* WR Diab Documentation says that intrinsics may be reordered, so _syncm();
     is not exactly what we want. */
  /* Release the spinlock, do not wait for the store to actually happens. */
  (*p_lock) = 0U;
}

/* As optimization this is directly called by our implementation of EI
   RefTable and by Embark G4MH, this means that the symbol have to be extern
   and "conf" visible */
extern void osEE_rh850_handle_ipir(void);

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_SINGLECORE */
#endif /* !OSEE_HAL_MC_H */

