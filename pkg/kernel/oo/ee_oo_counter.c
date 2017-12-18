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
 *  This files contains all OSEK Kernel Counters Implementation in Erika
 *  Enterprise.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#include "ee_internal.h"

FUNC(void, OS_CODE)
  osEE_counter_insert_rel_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_trigger_db,
  VAR(TickType, AUTOMATIC)                       delta
)
{
  osEE_counter_insert_abs_trigger(p_counter_db, p_trigger_db,
    osEE_counter_eval_when(p_counter_db, delta));
}

FUNC(void, OS_CODE)
  osEE_counter_insert_abs_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_trigger_db,
  VAR(TickType, AUTOMATIC)                       when
)
{
  CONSTP2VAR(OsEE_CounterCB, AUTOMATIC, OS_APPL_DATA)
    p_counter_cb  = p_counter_db->p_counter_cb;
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_previous    = NULL;
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_current     = p_counter_cb->trigger_queue;
  CONST(TickType, AUTOMATIC)
    counter_value = p_counter_cb->value;

  /* Update Trigger Status */
  p_trigger_db->p_trigger_cb->active = OSEE_TRUE;
  p_trigger_db->p_trigger_cb->when   = when;

  while (p_current != NULL) {
    CONST(TickType, AUTOMATIC) current_when = p_current->p_trigger_cb->when;

    if (current_when > counter_value) {
      /* "Current" belong to this counter-loop */
      if ((when >= current_when) || (when <= counter_value)) {
        /* (when >= current_when) => "New" after "current", still in this loop.
           (when <= counter_value) => "New" in next loop. */
        p_previous  = p_current;
        p_current   = p_current->p_trigger_cb->p_next;
      } else {
        break;
      }
    } else {
      /* "Current" belong to next counter-loop */
      if ((when <= counter_value) && (when >= current_when)) {
        /* (when <= counter_value) => "New" in the next counter-loop.
         * &&
         * (when >= current_when) => "New" after "current" */
        p_previous  = p_current;
        p_current   = p_current->p_trigger_cb->p_next;
      } else {
        break;
      }
    }
  }

  if (p_previous != NULL) {
    p_previous->p_trigger_cb->p_next  = p_trigger_db;
  } else {
    p_counter_cb->trigger_queue       = p_trigger_db;
  }

  p_trigger_db->p_trigger_cb->p_next = p_current;
}

FUNC(void, OS_CODE)
  osEE_counter_cancel_trigger
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_trigger_db
)
{
  CONSTP2VAR(OsEE_CounterCB, AUTOMATIC, OS_APPL_DATA)
    p_counter_cb  = p_counter_db->p_counter_cb;
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb  = p_trigger_db->p_trigger_cb;
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_current     = p_counter_cb->trigger_queue;

  if (p_current == p_trigger_db) {
    /* The trigger to be removed is the first one in the queue */
    p_counter_cb->trigger_queue = p_trigger_cb->p_next;
  } else {
    P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_previous;
    do {
      p_previous = p_current;
      p_current  = p_current->p_trigger_cb->p_next;
    } while ((p_current != NULL) && (p_current != p_trigger_db));

    if (p_current != NULL) {
      /* Remove p_trigger_db from the list */
      p_previous->p_trigger_cb->p_next = p_trigger_cb->p_next;
    }
  }

  /* Turn Off the Trigger */
  p_trigger_cb->active = OSEE_FALSE;
}

static FUNC(StatusType, OS_CODE)
  osEE_handle_action
(
  P2CONST(OsEE_action, AUTOMATIC, OS_APPL_DATA) p_action
)
{
  VAR(StatusType, AUTOMATIC) ev;
  switch (p_action->type) {
    case OSEE_ACTION_TASK:
    {
      CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
        p_tdb = p_action->param.p_tdb;

      ev = osEE_scheduler_task_activated(
            osEE_get_kernel(),
            osEE_get_task_curr_core(p_tdb),
            p_tdb,
            OSEE_FALSE);
    }
    break;
#if (defined(OSEE_HAS_EVENTS))
    case OSEE_ACTION_EVENT:
    {
      CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
        p_tdb = p_action->param.p_tdb;
      CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA)
        p_tcb = p_tdb->p_tcb;
      CONST(EventMaskType, AUTOMATIC)
        mask = p_action->param.mask;
      /* XXX: In case of multicore, I need at least reentrant spinlocks!!! */
      CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)
        p_cdb_rel = osEE_get_task_curr_core(p_tdb);

      osEE_lock_core(p_cdb_rel);
#if (defined(OSEE_HAS_CHECKS))
      if (p_tcb->status == OSEE_TASK_SUSPENDED) {
        osEE_unlock_core(p_cdb_rel);
        ev = E_OS_STATE;
      } else
#endif /* OSEE_HAS_CHECKS */
      {
        /* Set the event mask only if the task is not suspended */

        p_tcb->event_mask |= mask;

        if (((p_tcb->wait_mask & mask) != 0U) &&
            (p_tcb->status == OSEE_TASK_WAITING))
        {
          CONSTP2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
            p_sn = osEE_sn_alloc(&p_cdb_rel->p_ccb->p_free_sn);

          p_sn->p_tdb = p_tdb;

          /* Release the TASK (and the SN) */
          (void)osEE_scheduler_task_unblocked(
                  osEE_get_kernel(), p_cdb_rel, p_sn);
        }

        osEE_unlock_core(p_cdb_rel);

        ev = E_OK;
      }
    }
    break;
#endif /* OSEE_HAS_EVENTS */
    case OSEE_ACTION_COUNTER:
      /* XXX: In case of multicore, I need at least reentrant spinlocks!!! */
      osEE_counter_increment(p_action->param.p_counter_db);
      ev = E_OK;
    break;
    case OSEE_ACTION_CALLBACK:
    {
#if (defined(OSEE_HAS_CONTEXT))
      CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)
        p_ccb = osEE_get_curr_core()->p_ccb;
      CONST(OsEE_os_context, AUTOMATIC)
        prev_os_context = p_ccb->os_context;

      p_ccb->os_context = OSEE_ALARMCALLBACK_CTX;
#endif /* OSEE_HAS_CONTEXT */
      p_action->param.f();
#if (defined(OSEE_HAS_CONTEXT))
      p_ccb->os_context = prev_os_context;
#endif /* OSEE_HAS_CONTEXT */

      ev = E_OK;
    }
    break;
    default:
      /* TODO: Add some fault assertion here, unreacheable default switch clause */
      ev = E_OK;
    break;
  }
  return ev;
}

#if (defined(OSEE_HAS_ALARMS))
static FUNC(StatusType, OS_CODE)
  osEE_trigger_alarm
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA)  p_counter_db,
  P2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_DATA)    p_alarm_db
)
{
  VAR(StatusType, AUTOMATIC) ev;
  CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_db = osEE_alarm_get_trigger_db(p_alarm_db);
  CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
    p_trigger_cb = p_trigger_db->p_trigger_cb;
  CONST(TickType, AUTOMATIC)
    cycle = p_trigger_cb->cycle;

  ev = osEE_handle_action(&p_alarm_db->action);

  /* TODO: Add active check to let call CancelAlarm from callback... */
  if (cycle > 0U) {
    osEE_counter_insert_rel_trigger(
      p_counter_db, p_trigger_db, cycle
    );
  } else {
    p_trigger_cb->active = OSEE_FALSE;
  }

  return ev;
}
#endif /* OSEE_HAS_ALARMS */

FUNC(void, OS_CODE)
  osEE_counter_increment
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_DATA) p_counter_db
)
{
  CONSTP2VAR(OsEE_CounterCB, AUTOMATIC, OS_APPL_DATA)
    p_counter_cb = p_counter_db->p_counter_cb;

#if (defined(OSEE_HAS_COUNTER_PRESCALER))
  CONST(TickType, AUTOMATIC)
    ticksperbase = p_counter_db->info.ticksperbase;
  VAR(OsEE_bool, AUTOMATIC)
    is_real_tick = OSEE_TRUE;
  if (ticksperbase > 1U) {
    ++p_counter_cb->prescaler;
    if (p_counter_cb->prescaler >= ticksperbase) {
      p_counter_cb->prescaler = 0U;
    } else {
      is_real_tick = OSEE_FALSE;
    }
  }
  if (is_real_tick)
#endif /* OSEE_HAS_COUNTER_PRESCALER */
  {
    VAR(TickType, AUTOMATIC) counter_value;
    P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA) p_triggered_db;
    /* Since only the core that own a counter can increment it, I use
       osEE_get_curr_core_id, instead reading the CounterDB to get the info.
       This because is more efficient to read SFR than mamory. */
    CONST(CoreIdType, AUTOMATIC) counter_core_id = osEE_get_curr_core_id();

    /* Counter Increment can be done outside lock critical section, since only
       a core is allowed to do that */
    if (p_counter_cb->value >= p_counter_db->info.maxallowedvalue) {
      counter_value = (p_counter_cb->value = 0U);
    } else {
      counter_value = ++p_counter_cb->value;
    }

    /* XXX: Lock the counter core for all the duration of the service
            otherwise races could happens during the handling of cycling
            triggers.
            Maybe we should find another solution, like having private lock for
            the counters, whenever the locks are not limited resources for the
            HW and falling back to use core locks only for those architectures
            where this is not true. TBD. */
    osEE_lock_core_id(counter_core_id);

    p_triggered_db = p_counter_cb->trigger_queue;

    if (p_triggered_db != NULL) {
      P2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
        p_triggered_cb = p_triggered_db->p_trigger_cb;

      if (p_triggered_cb->when == counter_value) {
        /* Pop All Triggered from the Trigger Queue */
        P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
          p_current = p_triggered_db;
        P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
          p_previous;

        do {
          /* Now I will use previous to hold the previous checked alarm */
          p_previous = p_current;
          p_current = p_current->p_trigger_cb->p_next;
        } while ((p_current != NULL) &&
          (p_current->p_trigger_cb->when == counter_value));

        /* I set the end of handled queue */
        p_previous->p_trigger_cb->p_next = NULL;
        /* I set the head of the trigger queue to the current value
           (maybe NULL) */
        p_counter_cb->trigger_queue = p_current;

        /* XXX: Since we are preparing a sub-queue to handle the "tick", maybe we
                could do a COPY of TriggerCB data to realese sooner the lock,
                but handling the copies is still memory, timing and
                configuration costly: we really have to think about this. */

        do {
          VAR(StatusType, AUTOMATIC)                      ev;
          CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
            p_trigger_to_be_handled = p_triggered_db;

          /* Prepare next trigger to be handled here, before actually handle the
           * current one, otherwise cycling triggers will mess with the list of
           * triggers that have to be handled now */
          p_triggered_db = p_triggered_db->p_trigger_cb->p_next;
          if (p_triggered_db != NULL) {
            p_triggered_cb = p_triggered_db->p_trigger_cb;
          }
#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
          /* TODO */
#elif (defined(OSEE_HAS_ALARMS))
          ev = osEE_trigger_alarm(
                p_counter_db,
                p_trigger_to_be_handled);
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
          /* TODO */
#endif
#if (defined(OSEE_HAS_ERRORHOOK))
          if (ev != E_OK) {
            CONST(OsEE_reg, AUTOMATIC)
              flags = osEE_begin_primitive();
            osEE_call_error_hook(osEE_get_curr_core()->p_ccb, ev);
            osEE_end_primitive(flags);
          }
#else
          (void)ev; /* TODO: Handle ErrorHook */
#endif /* OSEE_HAS_ERRORHOOK */
        } while (p_triggered_db != NULL);
      }
    }
    /* XXX: Unlock the core only at the End of The Service, to not incur in
            races when handling cycling triggers. */
    osEE_unlock_core_id(counter_core_id);
  }
}
