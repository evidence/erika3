/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_get_kernel_and_core.h
 *  \brief  HAL internal.
 *
 *  This files contains kernel and core entry points data structures retrieving
 *  and locking functions.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_GET_CURRENT_CORE_H))
#define OSEE_GET_CURRENT_CORE_H

#include "ee_platform_types.h"
#include "ee_kernel_types.h"

extern OsEE_KDB KDB;
extern OsEE_CDB CDB;
extern OsEE_KCB KCB;
extern OsEE_CCB CCB;

#if (defined(EE_API_DYNAMIC))
extern OsEE_TCB tcb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
extern OsEE_SN  sn_array[OSEE_SN_ARRAY_SIZE];
extern OsEE_TDB tdb_array[OSEE_TASK_ARRAY_SIZE + OSEE_USED_CORES];
#endif /* EE_API_DYNAMIC */

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
  return osEE_get_kernel();
}

OSEE_STATIC_INLINE void osEE_unlock_kernel ( void ) {}

OSEE_STATIC_INLINE CoreIdType osEE_lock_and_get_curr_core_id ( void ) {
  return 0;
}

OSEE_STATIC_INLINE void osEE_lock_core_id ( CoreIdType core_id ) {}

OSEE_STATIC_INLINE void osEE_lock_core ( OsEE_CDB * const p_cdb ) {}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_core ( CoreIdType core_id ) {
  return osEE_get_curr_core();
}

OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_curr_core ( void ) {
  return osEE_get_curr_core();
}

OSEE_STATIC_INLINE void osEE_unlock_core_id ( CoreIdType core_id ) {}

OSEE_STATIC_INLINE void osEE_unlock_core ( OsEE_CDB * const p_cdb ) {}

OSEE_STATIC_INLINE void osEE_unlock_curr_core ( void ) {}

#endif /* OSEE_GET_CURRENT_CORE_H */
