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

/** \file   ee_oo_counter.c
 *  \brief  OSEK Counters, Alarms & Schedule Tables Implementation.
 *
 *  This files contains all OSEK Kernel Alarms Implementation in Erika
 *  Enterprise.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#include "ee_internal.h"

FUNC(StatusType, OS_CODE)
  osEE_alarm_set_rel
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db,
  VAR(TickType,   AUTOMATIC)                      increment,
  VAR(TickType,   AUTOMATIC)                      cycle
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_AlarmCB, AUTOMATIC, OS_APPL_DATA)
    p_alarm_cb = osEE_alarm_get_cb(p_alarm_db);
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_alarm_get_trigger_db(p_alarm_db);
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
#if (!defined(OSEE_SINGLECORE))
  CONST(CoreIdType, AUTOMATIC)
    counter_core_id = p_counter_db->core_id;
  /* Lock the Core Lock witch the counter is tied */
  osEE_lock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */

  if (p_trigger_cb->active) {
    ev = E_OS_STATE;
  } else {
    p_alarm_cb->cycle = cycle;

    osEE_counter_insert_rel_trigger(
      p_counter_db, p_trigger_db, increment
    );
    ev = E_OK;
  }
#if (!defined(OSEE_SINGLECORE))
  osEE_unlock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */
  return ev;
}

FUNC(StatusType, OS_CODE)
  osEE_alarm_set_abs
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db,
  VAR(TickType,   AUTOMATIC)                      start,
  VAR(TickType,   AUTOMATIC)                      cycle
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_AlarmCB, AUTOMATIC, OS_APPL_DATA)
    p_alarm_cb = osEE_alarm_get_cb(p_alarm_db);
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_alarm_get_trigger_db(p_alarm_db);
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
#if (!defined(OSEE_SINGLECORE))
    CONST(CoreIdType, AUTOMATIC)
    counter_core_id = p_counter_db->core_id;
/* Lock the Core Lock to whom the counter is tied */
  osEE_lock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */

  if (p_trigger_cb->active) {
    ev = E_OS_STATE;
  } else {
    p_alarm_cb->cycle = cycle;

    osEE_counter_insert_abs_trigger(
      p_counter_db, p_trigger_db, start
    );

    ev = E_OK;
  }
#if (!defined(OSEE_SINGLECORE))
  osEE_unlock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */
  return ev;
}

FUNC(StatusType, OS_CODE)
  osEE_alarm_cancel
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_alarm_get_trigger_db(p_alarm_db);
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
  CONSTP2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)
    p_counter_db = p_trigger_db->p_counter_db;
#if (!defined(OSEE_SINGLECORE))
  CONST(CoreIdType, AUTOMATIC)
    counter_core_id = p_counter_db->core_id;
/* Lock the Core Lock to whom the counter is tied */
  osEE_lock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */

  if (!p_trigger_cb->active) {
    ev = E_OS_NOFUNC;
  } else {
    osEE_counter_cancel_trigger(p_counter_db, p_trigger_db);
    ev = E_OK;
  }
#if (!defined(OSEE_SINGLECORE))
  osEE_unlock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */
  return ev;
}

FUNC(StatusType, OS_CODE)
  osEE_alarm_get
(
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db,
  P2VAR(TickType, AUTOMATIC, OS_APPL_DATA)        p_tick
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_alarm_get_trigger_db(p_alarm_db);
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
  CONSTP2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)
    p_counter_db = p_trigger_db->p_counter_db;
#if (!defined(OSEE_SINGLECORE))
  CONST(CoreIdType, AUTOMATIC)
    counter_core_id = p_counter_db->core_id;
/* Lock the Core Lock to whom the counter is tied */
  osEE_lock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */

  if (!p_trigger_cb->active) {
    ev = E_OS_NOFUNC;
  } else {
    *p_tick = osEE_counter_eval_delta(p_counter_db, p_trigger_cb->when);
    ev = E_OK;
  }
#if (!defined(OSEE_SINGLECORE))
  osEE_unlock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */
  return ev;
}

