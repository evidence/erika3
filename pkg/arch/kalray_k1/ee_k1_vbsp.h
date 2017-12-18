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

/** \file  ee_k1_vbsp.h
 *  \brief  TO BE DOCUMENTED!!!
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_K1_VBSP_H_))
#define OSEE_K1_VBSP_H_

#ifdef OSEE_TICKED_LOCKS
#define __K1_SPINLOCK_SET_TICKET
#else
#define __K1_SPINLOCK_SET_BACKOFF
#endif
#include <vbsp.h>
#include <HAL/hal/hal.h>

/* Include the full Kalray HAL support for K1 */
#include "ee_cfg.h"
#include "ee_compiler_gcc.h"
#include "ee_platform_types.h"

/* #define EE_K1_FULL_PREEMPTION */

 /* __builtin_k1_wpurge(): purge the data cache write buffer (for cached stores)
  */
 /* __builtin_k1_fence(): wait until all on fly write are commit to the SMEM.
    It must be called if you want to make sure that your write buffer finished
    commit data in the SMEM.
    It must also be called if you want to make sure that all on fly uncached
    stores are commit  in the SMEM */

/* mOS_dinval(): invalidate the data cache */

/* Read Memory barrier */
OSEE_STATIC_INLINE void osEE_k1_rmb ( void ) {
  /* invalidate the data cache */
  mOS_dinval();
}

/* Write Memory Barrier */
OSEE_STATIC_INLINE void osEE_k1_wmb ( void ) {
  /* purge the data cache write buffer (for cached stores) */
  __builtin_k1_wpurge();
  /* wait until all on fly write are commit to the SMEM. */
  __builtin_k1_fence();
}

/* Full Memory Barrier */
OSEE_STATIC_INLINE void osEE_k1_mb ( void ) {
  osEE_k1_rmb ();
  osEE_k1_wmb ();
}

OSEE_STATIC_INLINE void osEE_k1_idle_enter ( void ) {
  mOS_idle1();
}

OSEE_STATIC_INLINE void osEE_hal_spin_init_lock ( OsEE_spin_lock * p_lock ) {
  __k1_fspinlock_init(p_lock);
}

OSEE_STATIC_INLINE
  void osEE_hal_spin_lock ( OsEE_spin_lock * p_lock )
{
  osEE_k1_rmb();
  __k1_fspinlock_lock(p_lock);
}

OSEE_STATIC_INLINE
  OsEE_bool osEE_hal_spin_trylock ( OsEE_spin_lock * p_lock )
{
  OsEE_bool accessed = __k1_fspinlock_trylock(p_lock);
  if ( accessed ) {
    osEE_k1_rmb();
  }
  return accessed;
}

OSEE_STATIC_INLINE void osEE_hal_spin_unlock ( OsEE_spin_lock * p_lock ) {
  osEE_k1_wmb();
  __k1_fspinlock_unlock(p_lock);
}

#endif /* !EE_K1_VBSP_H_ */
