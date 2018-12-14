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
 *  \date   2017
 */

#ifndef OSEE_GET_CURRENT_CORE_H
#define OSEE_GET_CURRENT_CORE_H

#include "ee_platform_types.h"
#include "ee_kernel_types.h"
#include "ee_hal_mc.h"

#if (defined(__cplusplus))
extern "C" {
#endif

#define OS_START_SEC_CONST
#include "Os_MemMap.h"
extern OsEE_KDB osEE_kdb_var;
#define OS_STOP_SEC_CONST
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_INIT
#include "Os_MemMap.h"
extern OsEE_KCB osEE_kcb_var;
#define OS_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

OSEE_STATIC_INLINE OsEE_KDB * OSEE_ALWAYS_INLINE osEE_get_kernel(void) {
  return &osEE_kdb_var;
}

#if (defined(OSEE_SINGLECORE))

extern OsEE_CDB osEE_cdb_var;
extern OsEE_CCB osEE_ccb_var;

#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */

#if (defined(OSEE_API_DYNAMIC))
extern OsEE_TCB   osEE_tcb_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
extern OsEE_SN    osEE_sn_array[OSEE_SN_ARRAY_SIZE];
extern OsEE_TDB   osEE_tdb_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
extern OsEE_TDB * osEE_tdb_ptr_array[OSEE_TASK_ARRAY_SIZE + OsNumberOfCores];
#endif /* OSEE_API_DYNAMIC */

OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE osEE_get_curr_core(void) {
  return &osEE_cdb_var;
}

OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE
  osEE_get_core(CoreIdType core_id)
{
  (void)core_id;
  return &osEE_cdb_var;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_lock_kernel(void) {}

OSEE_STATIC_INLINE OsEE_KDB * OSEE_ALWAYS_INLINE osEE_lock_and_get_kernel(void)
{
  osEE_lock_kernel ();
  return osEE_get_kernel();
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_unlock_kernel(void) {}

OSEE_STATIC_INLINE CoreIdType OSEE_ALWAYS_INLINE
  osEE_lock_and_get_curr_core_id(void)
{
  return OS_CORE_ID_0;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_lock_core_id(CoreIdType core_id)
{
  (void)core_id;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_lock_core(OsEE_CDB * const p_cdb)
{
  (void)p_cdb;
}

OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE
  osEE_lock_and_get_core(CoreIdType core_id)
{
  (void)core_id;
  return osEE_get_curr_core();
}

OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE
  osEE_lock_and_get_curr_core(void)
{
  return osEE_get_curr_core();
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_unlock_core_id(CoreIdType core_id)
{
  (void)core_id;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_unlock_core(OsEE_CDB * const p_cdb)
{
  (void)p_cdb;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_unlock_curr_core (void) {}
#else

#define OS_CORE0_START_SEC_CONST
#include "Os_MemMap.h"
extern OsEE_CDB osEE_cdb_var_core0;
#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance_core0;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */
#define OS_CORE0_STOP_SEC_CONST
#include "Os_MemMap.h"

#define OS_CORE0_START_SEC_VAR_INIT
#include "Os_MemMap.h"
extern OsEE_CCB osEE_ccb_var_core0;
#define OS_CORE0_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
#define OS_CORE1_START_SEC_CONST
#include "Os_MemMap.h"
extern OsEE_CDB osEE_cdb_var_core1;
#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance_core1;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */
#define OS_CORE1_STOP_SEC_CONST
#include "Os_MemMap.h"

#define OS_CORE1_START_SEC_VAR_INIT
#include "Os_MemMap.h"
extern OsEE_CCB osEE_ccb_var_core1;
#define OS_CORE1_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
#define OS_CORE2_START_SEC_CONST
#include "Os_MemMap.h"
extern OsEE_CDB osEE_cdb_var_core2;
#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance_core2;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */
#define OS_CORE2_STOP_SEC_CONST
#include "Os_MemMap.h"

#define OS_CORE2_START_SEC_VAR_INIT
#include "Os_MemMap.h"
extern OsEE_CCB osEE_ccb_var_core2;
#define OS_CORE2_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
#define OS_CORE3_START_SEC_CONST
#include "Os_MemMap.h"
extern OsEE_CDB osEE_cdb_var_core3;
#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance_core3;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */
#define OS_CORE3_STOP_SEC_CONST
#include "Os_MemMap.h"

#define OS_CORE3_START_SEC_VAR_INIT
#include "Os_MemMap.h"
extern OsEE_CCB osEE_ccb_var_core3;
#define OS_CORE3_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
#define OS_CORE4_START_SEC_CONST
#include "Os_MemMap.h"
extern OsEE_CDB osEE_cdb_var_core4;
#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance_core4;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */
#define OS_CORE4_STOP_SEC_CONST
#include "Os_MemMap.h"

#define OS_CORE4_START_SEC_VAR_INIT
#include "Os_MemMap.h"
extern OsEE_CCB osEE_ccb_var_core4;
#define OS_CORE4_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
#define OS_CORE6_START_SEC_CONST
#include "Os_MemMap.h"
extern OsEE_CDB osEE_cdb_var_core6;
#if (defined(OSEE_TC_HAS_ISR1_TO_CONF))
extern OsEE_isr1_db osEE_isr1_db_instance_core6;
#endif /* OSEE_TC_HAS_ISR1_TO_CONF */
#define OS_CORE6_STOP_SEC_CONST
#include "Os_MemMap.h"

#define OS_CORE6_START_SEC_VAR_INIT
#include "Os_MemMap.h"
extern OsEE_CCB osEE_ccb_var_core6;
#define OS_CORE6_STOP_SEC_VAR_INIT
#include "Os_MemMap.h"

#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */

extern OsEE_CDB * osEE_get_core(CoreIdType core_id);

#if (defined(OSEE_TC_DISABLE_A9_OPTIMIZATION))
OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE osEE_get_curr_core(void) {
  return osEE_get_core(osEE_get_curr_core_id());
}
#else
OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE osEE_get_curr_core(void) {
  OsEE_CDB * p_cdb;
  osEE_tc_getareg(a9, p_cdb);
  return p_cdb;
}
#endif /* OSEE_TC_DISABLE_A9_OPTIMIZATION */

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_lock_kernel(void) {
  osEE_hal_spin_lock(osEE_kdb_var.p_lock);
}

OSEE_STATIC_INLINE OsEE_KDB * OSEE_ALWAYS_INLINE osEE_lock_and_get_kernel(void)
{
  osEE_lock_kernel();
  return osEE_get_kernel();
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_unlock_kernel(void) {
  osEE_hal_spin_unlock(osEE_kdb_var.p_lock);
}

OSEE_STATIC_INLINE CoreIdType OSEE_ALWAYS_INLINE
  osEE_lock_and_get_curr_core_id(void)
{
  OsEE_CDB * const p_cdb = osEE_get_curr_core();

  osEE_hal_spin_lock(p_cdb->p_lock);

  return osEE_get_curr_core_id();
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_lock_core_id(CoreIdType core_id)
{
  OsEE_CDB * const p_cdb = osEE_get_core(core_id);

  osEE_hal_spin_lock(p_cdb->p_lock);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_lock_core(OsEE_CDB * const p_cdb)
{
  osEE_hal_spin_lock(p_cdb->p_lock);
}

OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE
  osEE_lock_and_get_core(CoreIdType core_id)
{
  OsEE_CDB * const p_cdb = osEE_get_core(core_id);

  osEE_hal_spin_lock(p_cdb->p_lock);

  return p_cdb;
}

OSEE_STATIC_INLINE OsEE_CDB * OSEE_ALWAYS_INLINE
  osEE_lock_and_get_curr_core(void)
{
  OsEE_CDB * const p_cdb = osEE_get_curr_core();

  osEE_hal_spin_lock(p_cdb->p_lock);

  return p_cdb;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_unlock_core_id(CoreIdType core_id)
{
  OsEE_CDB * const p_cdb = osEE_get_core(core_id);

  osEE_hal_spin_unlock(p_cdb->p_lock);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_unlock_core(OsEE_CDB * const p_cdb)
{
  osEE_hal_spin_unlock(p_cdb->p_lock);
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE
  osEE_unlock_curr_core(void)
{
  OsEE_CDB * const p_cdb = osEE_get_curr_core();

  osEE_hal_spin_unlock(p_cdb->p_lock);
}

#endif /* OSEE_SINGLECORE */

#if (defined(__cplusplus))
}
#endif

#endif /* OSEE_GET_CURRENT_CORE_H */
