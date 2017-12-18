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

/** \file  ee_get_kernel_and_core.h
 *  \brief  HAL internal.
 *
 *  This files contains kernal and core HAL for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_GET_CURRENT_CORE_H))
#define OSEE_GET_CURRENT_CORE_H

#include "ee_k1_vbsp.h"
#include "ee_hal_internal.h"
#include "ee_kernel_types.h"
#include "ee_kernel_k1.h"

#if (defined(OSEE_HAS_JOBS))

OSEE_STATIC_INLINE OsEE_CDB * osEE_get_curr_core ( void ) {
  return &KDB_WJ.core_descriptors[osEE_get_curr_core_id()];
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_get_core ( CoreIdType  core_id ) {
  return &KDB_WJ.core_descriptors[core_id];
}

OSEE_STATIC_INLINE OsEE_KDB * osEE_get_kernel ( void ) {
  return &KDB_WJ.kdb;
}

OSEE_STATIC_INLINE void osEE_lock_kernel ( void ) {
  osEE_hal_spin_lock(&KCB_WJ.lock);
}

OSEE_STATIC_INLINE OsEE_KDB * osEE_lock_and_get_kernel ( void ) {
  osEE_lock_kernel();
  return osEE_get_kernel();
}

OSEE_STATIC_INLINE void osEE_unlock_kernel ( void ) {
  osEE_hal_spin_unlock(&KCB_WJ.lock);
}

OSEE_STATIC_INLINE CoreIdType osEE_lock_and_get_curr_core_id ( void ) {
  CoreIdType    const core_id   = osEE_get_curr_core_id();
  OsEE_CCB_WL * const p_ccb_wl  = &KCB_WJ.core_ctrls[core_id];

  osEE_hal_spin_lock(&p_ccb_wl->lock);

  return core_id;
}

OSEE_STATIC_INLINE void  osEE_lock_core_id ( CoreIdType core_id ) {
  osEE_hal_spin_lock(&KCB_WJ.core_ctrls[core_id].lock);
}

OSEE_STATIC_INLINE void  osEE_lock_core ( OsEE_CDB * const p_cdb ) {
  /* C single inheritance */
  osEE_hal_spin_lock(&((OsEE_CCB_WL *)p_cdb->p_ccb)->lock);
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_core ( CoreIdType core_id ) {
  OsEE_CDB *    const p_cdb     = &KDB_WJ.core_descriptors[core_id];
  OsEE_CCB_WL * const p_ccb_wl  = &KCB_WJ.core_ctrls[core_id];

  osEE_hal_spin_lock(&p_ccb_wl->lock);

  return p_cdb;
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_curr_core ( void ) {
  return osEE_lock_and_get_core(osEE_get_curr_core_id());
}

OSEE_STATIC_INLINE void osEE_unlock_core_id ( CoreIdType core_id ) {
  OsEE_CCB_WL * const p_ccb_wl = &KCB_WJ.core_ctrls[core_id];

  osEE_hal_spin_unlock(&p_ccb_wl->lock);
}

OSEE_STATIC_INLINE void  osEE_unlock_core ( OsEE_CDB * const p_cdb ) {
  /* C single inheritance */
  osEE_hal_spin_unlock(&((OsEE_CCB_WL *)p_cdb->p_ccb)->lock);
}

OSEE_STATIC_INLINE void osEE_unlock_curr_core ( void ) {
  osEE_unlock_core_id(osEE_get_curr_core_id());
}
#elif (!defined(OSEE_SINGLECORE))

OSEE_STATIC_INLINE OsEE_CDB * osEE_get_curr_core ( void ) {
  return &KDB_WL.core_descriptors[osEE_get_curr_core_id()];
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_get_core ( CoreIdType core_id ) {
  return &KDB_WL.core_descriptors[core_id];
}

OSEE_STATIC_INLINE OsEE_KDB * osEE_get_kernel ( void ) {
  return &KDB_WL.kdb;
}

OSEE_STATIC_INLINE void osEE_lock_kernel ( void ) {
  osEE_k1_spin_lock(&KCB_WL.lock);
}

OSEE_STATIC_INLINE OsEE_KDB * osEE_lock_and_get_kernel ( void ) {
  osEE_lock_kernel();
  return osEE_get_kernel();
}

OSEE_STATIC_INLINE void osEE_unlock_kernel ( void ) {
  osEE_k1_spin_unlock( &KCB_WL.lock );
}

OSEE_STATIC_INLINE CoreIdType osEE_lock_and_get_curr_core_id ( void ) {
  CoreIdType    const core_id   = osEE_get_curr_core_id();
  OsEE_CCB_WL * const p_ccb_wl  = &KCB_WL.core_ctrls[core_id];

  osEE_k1_spin_lock(&p_ccb_wl->lock);

  return core_id;
}

OSEE_STATIC_INLINE void  osEE_lock_core_id ( CoreIdType core_id ) {
  osEE_k1_spin_lock(&KCB_WL.core_ctrls[core_id].lock);
}

OSEE_STATIC_INLINE void  osEE_lock_core ( OsEE_CDB * const p_cdb ) {
  /* C single inheritance */
  osEE_k1_spin_lock(&((OsEE_CCB_WL *)p_cdb->p_ccb)->lock);
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_core ( CoreIdType core_id ) {
  OsEE_CDB *    const p_cdb    = &KDB_WL.core_descriptors[core_id];
  OsEE_CCB_WL * const p_ccb_wl = &KCB_WL.core_ctrls[core_id];

  osEE_k1_spin_lock(&p_ccb_wl->lock);

  return p_cdb;
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_curr_core ( void ) {
  return osEE_lock_and_get_core( osEE_get_curr_core_id() );
}

OSEE_STATIC_INLINE void osEE_unlock_core_id ( CoreIdType  core_id ) {
  OsEE_CCB_WL * const p_ccb_wl = &KCB_WL.core_ctrls[core_id];

  osEE_k1_spin_unlock(&p_ccb_wl->lock);
}

OSEE_STATIC_INLINE void osEE_unlock_core ( OsEE_CDB * const p_cdb ) {
  /* C single inheritance */
  osEE_k1_spin_unlock(&((OsEE_CCB_WL *)p_cdb->p_ccb)->lock);
}

OSEE_STATIC_INLINE void osEE_unlock_curr_core ( void ) {
  osEE_unlock_core_id ( osEE_get_curr_core_id() );
}
#else

extern OsEE_KDB KDB;
extern OsEE_CDB CDB;

#if (defined(OSEE_API_DYNAMIC))
extern OsEE_KCB   KCB;
extern OsEE_CCB   CCB;
extern OsEE_TCB   tcb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
extern OsEE_SN    sn_array[OSEE_SN_ARRAY_SIZE];
extern OsEE_TDB   tdb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
extern OsEE_TDB * tdb_ptr_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
#endif /* OSEE_API_DYNAMIC */

OSEE_STATIC_INLINE OsEE_CDB * osEE_get_curr_core ( void ) {
  return &CDB;
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_get_core ( CoreIdType core_id ) {
  return &CDB;
}

OSEE_STATIC_INLINE OsEE_KDB * osEE_get_kernel ( void ) {
  return &KDB;
}

OSEE_STATIC_INLINE void osEE_lock_kernel ( void ) {}

OSEE_STATIC_INLINE OsEE_KDB * osEE_lock_and_get_kernel ( void ) {
  osEE_lock_kernel ();
  return osEE_get_kernel ();
}

OSEE_STATIC_INLINE void osEE_unlock_kernel ( void ) {}

OSEE_STATIC_INLINE CoreIdType osEE_lock_and_get_curr_core_id ( void ) {
  return 0U;
}

OSEE_STATIC_INLINE void osEE_lock_core_id ( CoreIdType core_id ) {}

OSEE_STATIC_INLINE void  osEE_lock_core ( OsEE_CDB * const p_cdb ) {}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_core ( CoreIdType  core_id ) {
  return osEE_get_curr_core();
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_curr_core ( void ) {
  return osEE_get_curr_core();
}

OSEE_STATIC_INLINE void osEE_unlock_core_id ( CoreIdType core_id ) {}

OSEE_STATIC_INLINE void osEE_unlock_core ( OsEE_CDB * const p_cdb ) {}

OSEE_STATIC_INLINE void osEE_unlock_curr_core ( void ) {}
#endif /* OSEE_SINGLECORE */

#endif /* OSEE_GET_CURRENT_CORE_H */
