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

/** \file   ee_ar_sched_table.c
 *  \brief  OSEK AlarmsImplementation.
 *
 *  This files contains all OSEK Kernel Alarms Implementation in Erika
 *  Enterprise.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#include "ee_internal.h"

FUNC(StatusType, OS_CODE)
  osEE_st_start_rel
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_DATA) p_st_db,
  VAR(TickType,   AUTOMATIC)                      offset
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_SchedTabCB, AUTOMATIC, OS_APPL_DATA)
    p_st_cb = osEE_st_get_cb(p_st_db);
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_st_get_trigger_db(p_st_db);
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
#if (!defined(OSEE_SINGLECORE))
  CONST(CoreIdType, AUTOMATIC)
    counter_core_id = p_counter_db->core_id;
  /* Lock the Core Lock witch the counter is tied */
  osEE_lock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */

  if (p_trigger_cb->status > OSEE_TRIGGER_CANCELED) {
    ev = E_OS_STATE;
  } else {
/* Initialize ST data structure
    (Even though the ST is Reenabled it has to restart from the beginning) */
    
    p_st_cb->p_next_table = NULL;
    p_st_cb->position     = 0U;
    p_st_cb->deviation    = 0;
    p_st_cb->st_status    = SCHEDULETABLE_RUNNING;
    p_st_cb->start        = osEE_counter_eval_when(p_counter_db, offset);

    if (p_trigger_cb->status == OSEE_TRIGGER_CANCELED) {
      /* Re-turn on the trigger, that is in handling, since is handling I'll set
         'here' when based on offset */
      p_trigger_cb->when   = p_st_cb->start;
      p_trigger_cb->status = OSEE_TRIGGER_REENABLED;
    } else {
      /* Turn On the Trigger */
      p_trigger_cb->status = OSEE_TRIGGER_ACTIVE;

      osEE_counter_insert_rel_trigger(p_counter_db, p_trigger_db,
        offset  + (*p_st_db->p_expiry_point_array)[0].offset
      );
    }
    ev = E_OK;
  }
#if (!defined(OSEE_SINGLECORE))
  osEE_unlock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */
  return ev;
}

FUNC(StatusType, OS_CODE)
  osEE_st_start_abs
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_DATA) p_st_db,
  VAR(TickType,   AUTOMATIC)                      start
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_SchedTabCB, AUTOMATIC, OS_APPL_DATA)
    p_st_cb = osEE_st_get_cb(p_st_db);
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_st_get_trigger_db(p_st_db);
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
#if (!defined(OSEE_SINGLECORE))
  CONST(CoreIdType, AUTOMATIC)
    counter_core_id = p_counter_db->core_id;
  /* Lock the Core Lock witch the counter is tied */
  osEE_lock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */

  if (p_trigger_cb->status > OSEE_TRIGGER_CANCELED) {
    ev = E_OS_STATE;
  } else {
/* Initialize ST data structure
   (Even though the ST is Reenabled it has to restart from the beginning) */
    p_st_cb->p_next_table = NULL;
    p_st_cb->position     = 0U;
    p_st_cb->deviation    = 0;
    p_st_cb->st_status    =
      (p_st_db->sync_strategy == OSEE_SCHEDTABLE_SYNC_IMPLICIT)?
        SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS:
        SCHEDULETABLE_RUNNING;
    p_st_cb->start        = start;

    if (p_trigger_cb->status == OSEE_TRIGGER_CANCELED) {
      /* Re-turn on the trigger, that is in handling, since is handling I'll set
         here 'when' based on start */
      p_trigger_cb->when   = start;
      p_trigger_cb->status = OSEE_TRIGGER_REENABLED;
    } else {
      /* Turn On the Trigger */
      p_trigger_cb->status = OSEE_TRIGGER_ACTIVE;

      osEE_counter_insert_abs_trigger(p_counter_db, p_trigger_db,
        start + (*p_st_db->p_expiry_point_array)[0].offset
      );
    }

    ev = E_OK;
  }
#if (!defined(OSEE_SINGLECORE))
  osEE_unlock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */
  return ev;
}

FUNC(StatusType, OS_CODE)
  osEE_st_stop
(
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST)  p_st_db
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_SchedTabCB, AUTOMATIC, OS_APPL_DATA)
    p_st_cb = osEE_st_get_cb(p_st_db);
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_st_get_trigger_db(p_st_db);
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

  if (p_trigger_cb->status <= OSEE_TRIGGER_CANCELED) {
/* [SWS_Os_00280] If the schedule table with identifier <ScheduleTableID> is
   in state SCHEDULETABLE_STOPPED when calling StopScheduleTable(),
   StopScheduleTable() shall return E_OS_NOFUNC. */
    ev = E_OS_NOFUNC;
  } else if (p_trigger_cb->status >= OSEE_TRIGGER_EXPIRED) {
    p_trigger_cb->status = OSEE_TRIGGER_CANCELED;

    /* Stop Next ST if needed */
    if (p_st_cb->p_next_table != NULL) {
      osEE_st_get_cb(p_st_cb->p_next_table)->st_status = SCHEDULETABLE_STOPPED;
    }

    p_st_cb->st_status = SCHEDULETABLE_STOPPED;

    ev = E_OK;
  } else {
    p_trigger_cb->status = OSEE_TRIGGER_INACTIVE;

    /* Stop Next ST if needed */
    if (p_st_cb->p_next_table != NULL) {
      osEE_st_get_cb(p_st_cb->p_next_table)->st_status = SCHEDULETABLE_STOPPED;
    }

    p_st_cb->st_status = SCHEDULETABLE_STOPPED;

    osEE_counter_cancel_trigger(p_counter_db, p_trigger_db);

    ev = E_OK;
  }
#if (!defined(OSEE_SINGLECORE))
  osEE_unlock_core_id(counter_core_id);
#endif /* OSEE_SINGLECORE */

  return ev;
}

FUNC(StatusType, OS_CODE)
  osEE_st_syncronize
(
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST)  p_st_db,
  VAR(TickType, AUTOMATIC)                          value
)
{
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST)
    p_trigger_db = osEE_st_get_trigger_db(p_st_db);
  CONSTP2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST)
    p_counter_db = p_trigger_db->p_counter_db;
  CONSTP2CONST(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
  CONSTP2VAR(OsEE_SchedTabCB, AUTOMATIC, OS_APPL_DATA)
    p_st_cb = osEE_st_get_cb(p_st_db);

/* Check if the ScheduleTable is Started */
  if ((p_st_cb->st_status & SCHEDULETABLE_RUNNING) == SCHEDULETABLE_RUNNING) {
/* Schedule Table position locals */
    VAR(TickType, AUTOMATIC)      st_pos;
    VAR(TickType, AUTOMATIC)      next_when;
    VAR(TickType, AUTOMATIC)      temp_deviation_unsigned; /* MISRA C 10.8 */
    VAR(TickDeltaType, AUTOMATIC) temp_deviation;
    CONST(MemSize, AUTOMATIC) position = p_st_cb->position;

/* [SWS_Os_00457] If the parameters in a call of SyncScheduleTable() are
    valid, SyncScheduleTable() shall provide the Operating System module
    with the current synchronization count for the given schedule table.
    (It is used to synchronize the processing of the schedule table to the
     synchronization counter.) */
/* Evaluate ST "tick position" */
    next_when = p_trigger_cb->when;
    st_pos = next_when - p_st_cb->start;

/* Evaluate Schedule Table Deviation before synchronization */
    temp_deviation_unsigned = st_pos - value;
    temp_deviation = (TickDeltaType)temp_deviation_unsigned;
/* [SWS_Os_00420]: IF the deviation is non-zero AND the next expiry point
    is adjustable AND the table is behind the sync counter
    (TableTicksAheadOfSyncCounter <= TableTicksBehindOfSyncCounter)
    THEN the OS shall set the next EP to expire
    delay - min(MaxShorten, Deviation) ticks from the current expiry. */
/* [SWS_Os_00421]: IF the deviation is non-zero AND the next expiry point
    is adjustable AND the table is ahead of the sync counter
    (TableTicksAheadOfSyncCounter > TableTicksBehindOfSyncCounter)
    THEN the OS shall set the next EP to expire delay +
    min(MaxLengthen, Deviation) ticks from the current expiry. */
    /* Try to synchronize */
    if (temp_deviation != 0) {
      if (temp_deviation > 0) {
        CONST(TickType, AUTOMATIC)
          abs_temp_dev = (TickType)temp_deviation;
        CONST(TickType, AUTOMATIC)
          max_shorten = (*p_st_db->p_expiry_point_array)[position].max_shorten;
        CONST(TickType, AUTOMATIC)
          shortening =
            (max_shorten < abs_temp_dev)? max_shorten: abs_temp_dev;

        /* Evaluate Next-When */
        next_when      -= shortening;
        /* Adjust deviation */
        temp_deviation -= (TickDeltaType)shortening; 
      } else {
        CONST(TickType, AUTOMATIC)
          abs_temp_dev = (TickType)(-temp_deviation);
        VAR(TickType, AUTOMATIC)
          max_lengthen = (*p_st_db->p_expiry_point_array)[position].
            max_lengthen;
        CONST(TickType, AUTOMATIC)
          lengthening =
            (max_lengthen < abs_temp_dev)? max_lengthen: abs_temp_dev;

        /* Evaluate Next-When */
        next_when       += lengthening;
        /* Adjust deviation */
        temp_deviation  -= (TickDeltaType)lengthening;
      }

      /* Cancel the alarm related with the schedule table */
      osEE_counter_cancel_trigger(p_counter_db, p_trigger_db);
      /* Restart the alarm related with the schedule table */
      osEE_counter_insert_abs_trigger(p_counter_db, p_trigger_db,
        next_when);
    }

    /* if st abs(deviation) < st precision -> synchronized! */  
    if ((temp_deviation < p_st_db->precision) &&
        (temp_deviation > -p_st_db->precision))
    {
      /* [SWS_Os_00418]: The Operating System module shall set the state of
          an explicitly synchronized schedule table to
          "running and synchronous" if the deviation is less than or equal to
          the configured OsScheduleTblExplicitPrecision threshold. */
      p_st_cb->st_status  = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
    } else {
      /* Try to synchronize */
      /* [SWS_Os_00419]: The Operating System module shall set the state of
          an explicitly synchronized schedule table to "running" if the
          deviation is greater than the configured
          OsScheduleTblExplicitPrecision threshold. */
      p_st_cb->st_status  = SCHEDULETABLE_RUNNING;
    }

    p_st_cb->deviation = temp_deviation;
  } else {
    /* Otherwise is waiting for synchronization before start
       (p_schedule_table_RAM->status == SCHEDULETABLE_WAITING) */
    /* TODO: handle Schedule Table Synchronous Start */
  }

  return E_OK;
}
