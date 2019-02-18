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

/** \file   ee_get_kernel_and_core.h
 *  \brief  HAL internal.
 *
 *  This files contains kernel and core entry points data structures retrieving
 *  and locking functions.
 *
 *  \author Errico Guidieri
 *  \author Giuseppe Serano
 *  \date   2018
 */

#ifndef OSEE_GET_CURRENT_CORE_H
#define OSEE_GET_CURRENT_CORE_H

#include "ee_platform_types.h"
#include "ee_kernel_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/** KDB - Kernel Descriptor Block. Data structure in FLASH that stores
 *  information about the kernel
 */
extern OsEE_KDB osEE_kdb_var;

/** CDB - Core Descriptor Block. Data structure in FLASH that stores
 *  information about one of the available cores
 */
extern OsEE_CDB osEE_cdb_var;

/** KCB - Kernel Control Block. Data structure in RAM that stores
 *  information about the kernel
 */
extern OsEE_KCB osEE_kcb_var;

/** CCB - Core Control Block. Data structure in RAM that stores
 *  information about one of the available croes
 */
extern OsEE_CCB osEE_ccb_var;

#if (defined(OSEE_API_DYNAMIC))
extern OsEE_TCB   osEE_tcb_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
extern OsEE_SN    osEE_sn_array[OSEE_SN_ARRAY_SIZE];
extern OsEE_TDB   osEE_tdb_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
extern OsEE_TDB * osEE_tdb_ptr_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
#endif /* OSEE_API_DYNAMIC */

/**
 *  \brief Returns the pointer to CDB.
 *  
 *  This function is called internally to get the CDB pointer, which contains
 *  the information related to the only core available.
 *  
 *  \return The function returns a ponter to the CDB data structure of the 
 *  unique core available.
 */
OSEE_STATIC_INLINE OsEE_CDB * osEE_get_curr_core(void) {
  return &osEE_cdb_var;
}

/**
 *  \brief Returns a pointer to the CDB
 *  
 *  The function returns the pointer to the CDB of the core specified as 
 *  parameter.
 *  Since the machine is a single core machine, the function returns the only
 *  CDB available.
 *  
 *  \param [in] core_id The core for which we should return the information
 *  \return Always returns the only CDB available (it's a single core machine)
 */
OSEE_STATIC_INLINE OsEE_CDB * osEE_get_core(CoreIdType core_id) {
  (void)core_id;
  return &osEE_cdb_var;
}

/**
 *  \brief Returns the pointer to the Kernel descriptor Block
 *  
 *  The KDB is the data structure containing the global kernel information.
 *  This function returns a pointer to it.
 *  
 *  \return The function returns the pointer to the KDB block
 */
OSEE_STATIC_INLINE OsEE_KDB * osEE_get_kernel(void) {
  return &osEE_kdb_var;
}

/**
 *  \brief Locks the kernel.
 *  
 *  On single core machines this function is void since there is no locking 
 *  of the kernel.
 */
OSEE_STATIC_INLINE void osEE_lock_kernel(void) {}

/**
 *  \brief Locks the kernel and gets the Kernel Descriptor Block pointer
 *  
 *  On single core machines, there is no lock. The function therefore has the 
 *  same effect as osEE_get_kernel().
 *  
 *  \return This function returnd the Kernel Descriptor Block pointer
 */
OSEE_STATIC_INLINE OsEE_KDB * osEE_lock_and_get_kernel(void) {
  osEE_lock_kernel ();
  return osEE_get_kernel();
}

/**
 *  \brief Unlocks the kernel.
 *  
 *  On single core machines this function is void since there is no locking 
 *  of the kernel.
 */
OSEE_STATIC_INLINE void osEE_unlock_kernel(void) {}

/**
 *  \brief Locks the kernel and gets the current core ID
 *  
 *  On single core machines, there is no kernel locking.
 *  The function returns the current core ID, which is the only one available, 0.
 *  
 *  \return On single core machines, it returns ID 0, which is the first core.
 */
OSEE_STATIC_INLINE CoreIdType osEE_lock_and_get_curr_core_id(void) {
  return 0;
}

/**
 *  \brief Locks a specific core ID
 *  
 *  On multicore machines, there is the need to lock a specific core
 *  (e.g. because we have to activate a remote task, which is implemented with 
 *  a direct modification of the kernel data structures of the remote core).
 *  
 *  Since this is a single core configuration, this dunction is void.
 *  
 *  \param [in] core_id The core to lock	
 */
OSEE_STATIC_INLINE void osEE_lock_core_id(CoreIdType core_id) {
  (void)core_id;
}

/**
 *  \brief Locks a specific core
 *  
 *  Similar to osEE_lock_core_id(), but it receives a CDB pointer instead of 
 *  the ID. Void on single core configurations.
 *  
 *  \param [in] p_cdb The core to lock
 */
OSEE_STATIC_INLINE void osEE_lock_core(OsEE_CDB * const p_cdb) {
  (void)p_cdb;
}

/**
 *  \brief Locks a specific core and gets its data structure
 *  
 *  Similar to osEE_lock_and_get_curr_core_id(), but it returns a CDB pointer 
 *  instead of returning the ID. The locking is void on single core 
 *  configurations.
 *  
 *  \param [in] core_id The ID of the core to lock
 *  \return The function returns a pointer to the CDB pointer
 */
OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_core(CoreIdType core_id) {
  (void)core_id;
  return osEE_get_curr_core();
}

/**
 *  \brief Locks the current core and gets its data structure
 *  
 *  Similar to osEE_lock_and_get_curr_core_id(), but it returns a CDB pointer 
 *  instead of returning the ID. The locking is void on single core 
 *  configurations.
 *  
 *  \return The function returns a pointer to the CDB pointer of the current
 *          core
 */
OSEE_STATIC_INLINE OsEE_CDB * osEE_lock_and_get_curr_core(void) {
  return osEE_get_curr_core();
}

/**
 *  \brief Unlocks a specific core
 *  
 *  Unlocks a core whose ID has been passed as parameter.
 *  Void on single core machines.
 *  
 *  \param [in] core_id The core ID to unlock
 */
OSEE_STATIC_INLINE void osEE_unlock_core_id(CoreIdType core_id) {
  (void)core_id;
}

/**
 *  \brief Unlocks a specific core
 *  
 *  Unlocks a core whose CDB pointer has been passed as parameter.
 *  Void on single core machines.
 *  
 *  \param [in] p_cdb The core ID to unlock
 */
OSEE_STATIC_INLINE void osEE_unlock_core(OsEE_CDB * const p_cdb) {
  (void)p_cdb;
}

/**
 *  \brief Unlocks the current core
 *  
 *  Unlocks the current core.
 *  Void on single core machines.
 */
OSEE_STATIC_INLINE void osEE_unlock_curr_core(void) {}

#if (defined(__cplusplus))
}
#endif

#endif /* OSEE_GET_CURRENT_CORE_H */
