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
  VAR(OsEE_bool, AUTOMATIC)
    work_not_done = OSEE_TRUE;

  /* Update Trigger Status */
  p_trigger_db->p_trigger_cb->when   = when;

  while ((p_current != NULL) && work_not_done) {
    CONST(TickType, AUTOMATIC) current_when = p_current->p_trigger_cb->when;

    if (current_when > counter_value) {
      /* "Current" belong to this counter-loop */
      if ((when >= current_when) || (when <= counter_value)) {
        /* (when >= current_when) => "New" after "current", still in this loop.
           (when <= counter_value) => "New" in next loop. */
        p_previous  = p_current;
        p_current   = p_current->p_trigger_cb->p_next;
      } else {
        work_not_done = OSEE_FALSE;
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
        work_not_done = OSEE_FALSE;
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
}

static FUNC(StatusType, OS_CODE)
  osEE_handle_action
(
  P2VAR(OsEE_action, AUTOMATIC, OS_APPL_CONST) p_action
)
{
  VAR(StatusType, AUTOMATIC) ev = E_OK;
  switch (p_action->type) {
    case OSEE_ACTION_TASK:
    {
      CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
        p_tdb     = p_action->param.p_tdb;

      ev = osEE_task_activated(p_tdb);
      if (ev == E_OK) {
        (void)osEE_scheduler_task_insert(osEE_get_kernel(), p_tdb);
      }
    }
    break;
#if (defined(OSEE_HAS_EVENTS))
    case OSEE_ACTION_EVENT:
    {
      P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)
        p_sn;
      CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)
        p_tdb = p_action->param.p_tdb;
      CONST(EventMaskType, AUTOMATIC)
        mask = p_action->param.mask;

      p_sn = osEE_task_event_set_mask(p_tdb, mask, &ev);

      if (p_sn != NULL) {
        /* Release the TASK (and the SN) */
        (void)osEE_scheduler_task_unblocked(osEE_get_kernel(), p_sn);
      }
    }
    break;
#endif /* OSEE_HAS_EVENTS */
    case OSEE_ACTION_COUNTER:
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
      /* TODO: Add some fault assertion here, unreachable default clause */
      ev = E_OK;
    break;
  }

#if (defined(OSEE_HAS_ERRORHOOK))
  if (ev != E_OK) {
    CONSTP2VAR(OsEE_CCB, AUTOMATIC, OS_APPL_DATA)
      p_ccb = osEE_get_curr_core()->p_ccb;
    osEE_set_service_id(p_ccb, OSId_Action);
    osEE_call_error_hook(p_ccb, ev);
  }
#endif /* OSEE_HAS_ERRORHOOK */

  return ev;
}

#if (defined(OSEE_HAS_ALARMS))
static FUNC(void, OS_CODE)
  osEE_counter_handle_alarm
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_trigger_to_be_handled_db
)
{
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST)       p_cdb;
  P2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)  p_trigger_to_be_handled_cb;

  (void)osEE_handle_action(
    &osEE_trigger_get_alarm_db(p_trigger_to_be_handled_db)->action
  );

  /* Re-enter in critical section to reinsert alarm-trigger if needed */
  p_cdb = osEE_lock_and_get_curr_core();

  p_trigger_to_be_handled_cb = p_trigger_to_be_handled_db->p_trigger_cb;

  if (p_trigger_to_be_handled_cb->status == OSEE_TRIGGER_EXPIRED) {
    CONST(TickType, AUTOMATIC) cycle = osEE_alarm_get_cb(
        osEE_trigger_get_alarm_db(p_trigger_to_be_handled_db)
      )->cycle;
    if (cycle > 0U) {
      /* Reinsert the trigger in timer wheel as relative with delta equal to
         cycle */
      p_trigger_to_be_handled_cb->status = OSEE_TRIGGER_ACTIVE;
      osEE_counter_insert_rel_trigger(p_counter_db,
        p_trigger_to_be_handled_db, cycle);
    } else {
      p_trigger_to_be_handled_cb->status = OSEE_TRIGGER_INACTIVE;
    }
  }
  /* Exit from critical section for the next action */
  osEE_unlock_core(p_cdb);
}

#endif /* OSEE_HAS_ALARMS */

#if (defined(OSEE_HAS_SCHEDULE_TABLES))

#define INVALID_SCHEDULETABLE_POSITION ((MemSize)-1)

static FUNC(void, OS_CODE)
  osEE_counter_handle_st_expiry_point
(
  P2VAR(OsEE_CounterDB, AUTOMATIC, OS_APPL_CONST) p_counter_db,
  P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_trigger_to_be_handled_db
)
{
  CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST)
    p_cdb = osEE_get_curr_core();
  /* Get Schedule Table Configuration Structures */
  P2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST)
    p_st_db = osEE_trigger_get_st_db(p_trigger_to_be_handled_db);
  P2VAR(OsEE_SchedTabCB, AUTOMATIC, OS_APPL_CONST)
    p_st_cb = osEE_st_get_cb(p_st_db);

  do {
    /* Trigger to be reinserted */
    P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST)
      p_trigger_to_reinsert = NULL;
    /* When the new trigger has to expire */
    VAR(TickType, AUTOMATIC)  next_when = 0U;

    /* Enter in Critical Section to Handle Expiry Point */
    osEE_lock_core(p_cdb);
    if (osEE_st_get_trigger_db(p_st_db)->p_trigger_cb->status ==
         OSEE_TRIGGER_EXPIRED)
    {
      /* Utility local var to handle expiry point */
      VAR(TickType, AUTOMATIC)  nextOffset;
      VAR(MemSize, AUTOMATIC)   expiry_position = p_st_cb->position;

      /* This can happen:
          - If a Next Schedule Table is activated, to stop the original
            Schedule Table after the final delay.
          - IF Original Schedule Table is repeating */
      if (expiry_position == INVALID_SCHEDULETABLE_POSITION) {
        /* Get the next Schedule Table */
        CONSTP2VAR(OsEE_SchedTabDB, AUTOMATIC, OS_APPL_CONST)
          p_next_st_db = p_st_cb->p_next_table;

        if (p_next_st_db != NULL) {
          /* Turn-off Orig Schedule Table */
          p_st_cb->st_status    = SCHEDULETABLE_STOPPED;
          osEE_st_get_trigger_db(p_st_db)->p_trigger_cb->
            status = OSEE_TRIGGER_INACTIVE;

          /* Next ST Handling */
          p_st_db = p_next_st_db;
          p_st_cb = osEE_st_get_cb(p_next_st_db);

          p_st_cb->st_status = SCHEDULETABLE_RUNNING;

          p_st_cb->position = 0U;
          /* Set Next ST Start value */
          p_st_cb->start    = p_counter_db->p_counter_cb->value;

          nextOffset = (*p_st_db->p_expiry_point_array)[0U].offset;

          /* Handle special case of some expiry points with offset equal to
             zero */
          if (nextOffset > 0U) {
            /* Schedule the trigger tied to the next Schedule Table */
            p_trigger_to_reinsert = osEE_st_get_trigger_db(p_st_db);
            next_when = p_st_cb->start + nextOffset;
            /* Exit From The Loop */
            p_st_db = NULL;
          }
          /* else first expiry point is handled immediately */
        } else {
          /* Repeating Schedule Table */
          p_st_cb->position = 0U;
          /* Set Repeating ST Start value */
          p_st_cb->start    = p_counter_db->p_counter_cb->value;
          nextOffset        = (*p_st_db->p_expiry_point_array)[0U].offset;

          if (nextOffset > 0U) {
            /* Trigger CB "when" field is used to hold next trigger value, for
               next expiry point */
            p_trigger_to_reinsert = osEE_st_get_trigger_db(p_st_db);
            next_when = p_st_cb->start + nextOffset;
            /* Exit From The Loop */
            p_st_db = NULL;
          }
          /* else (nextOffset == 0) the next loop iteration will handle the
             first expiry point of the repeating ST */
        }
      } else {
        /* Get the Expiry point */
        VAR(MemSize, AUTOMATIC) i;
        /* Expiry point description */
        CONSTP2VAR(OsEE_st_exipiry_point, AUTOMATIC, OS_APPL_CONST)
          p_expiry_point = &(*p_st_db->p_expiry_point_array)[expiry_position];
        CONST(MemSize, AUTOMATIC)
          action_array_size = p_expiry_point->action_array_size;

        /* Handle expiry point actions outside the Critical Section */
        osEE_unlock_core(p_cdb);

        for (i = 0U; i < action_array_size; ++i) {
          (void)osEE_handle_action(&(*p_expiry_point->p_action_array)[i]);
        }

        /* Reenter in critical section after handling actions */
        osEE_lock_core(p_cdb);

        /* if the trigger is still valid... */
        if (osEE_st_get_trigger_db(p_st_db)->p_trigger_cb->status ==
            OSEE_TRIGGER_EXPIRED)
        {
          /* Handle next expiry point insertion in alarm queue */
          /* if it is the last expiry point and if this is not a repeating
             schedule table, handle next schedule table or stop it */
          if (expiry_position == (p_st_db->expiry_point_array_size - 1U)) {
            /* We reached the end of schedule table so we stop it */
            if ((p_st_cb->p_next_table == NULL) && (!p_st_db->repeated)) {
              /* [SWS_Os_00009] If the schedule table is single-shot, the
                  Operating System module shall stop the processing of the
                  schedule table Final Delay ticks after the Final Expiry Point
                  is processed. */
              p_st_cb->st_status  = SCHEDULETABLE_STOPPED;
              /*  This is needed to stop the underlying Trigger tied to the
                  Schedule Table, otherwise the Trigger will reschedule this
                  trigger on the next occurrence of counter.value == when */
              osEE_st_get_trigger_db(p_st_db)->p_trigger_cb->status =
                OSEE_TRIGGER_INACTIVE;
              /* Exit From The Loop */
              p_st_db = NULL;
            } else {
              /* Schedule the final delay for original schedule table */
              p_st_cb->position = INVALID_SCHEDULETABLE_POSITION;
              /* [SWS_Os_0427] If the schedule table is single-shot,
                  the Operating System module shall allow a Final Delay between
                  0 .. OsCounterMaxAllowedValue of the underlying counter. */
              if (p_st_db->duration > p_expiry_point->offset) {
                p_trigger_to_reinsert = osEE_st_get_trigger_db(p_st_db);
                next_when = p_st_cb->start + p_st_db->duration;
                /* Exit From The Loop */
                p_st_db = NULL;
              }
            }
          } else {
            if (p_st_db->sync_strategy == OSEE_SCHEDTABLE_SYNC_EXPLICIT) {
              /* *** TODO: HANDLE SYNCRONIZATION *** */
            }
            /* Schedule the next expiry point */
            ++expiry_position;
            p_st_cb->position = expiry_position;

            nextOffset = (*p_st_db->p_expiry_point_array)[expiry_position].
              offset;

            /* Check if new expiry point is not simultaneous of the
               previous one */
            if (nextOffset > p_expiry_point->offset) {
              p_trigger_to_reinsert = osEE_st_get_trigger_db(p_st_db);
              next_when = p_st_cb->start + nextOffset;
              /* Exit From The Loop */
              p_st_db = NULL;
            }
            /* else handle the next expiry point immediately */
          }
        } else {
          /* Exit From The Loop */
          p_st_db = NULL;
        }
      }
    } else {
      /* Exit From The Loop */
      p_st_db = NULL;
    }

    /* Reinsert the trigger in queue if needed */
    if (p_trigger_to_reinsert != NULL) {
      p_trigger_to_reinsert->p_trigger_cb->status = OSEE_TRIGGER_ACTIVE;
      osEE_counter_insert_abs_trigger(p_counter_db, p_trigger_to_reinsert,
        next_when);
    }
    /* exit critical section for this loop */
    osEE_unlock_core(p_cdb);
  } while (p_st_db != NULL);
}
#endif /* OSEE_HAS_SCHEDULE_TABLES */

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
    P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST) p_triggered_db;
    /* Since only the core that own a counter can increment it, I use
       osEE_get_curr_core, instead reading the CounterDB to get the info.
       This because is more efficient to read SFR than memory. */
    CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST)
      p_cdb = osEE_get_curr_core();

    /* Counter Increment can be done outside lock critical section, since only
       a core is allowed to do that */
    if (p_counter_cb->value >= p_counter_db->info.maxallowedvalue) {
      counter_value       = 0U;
      p_counter_cb->value = 0U;
    } else {
      ++p_counter_cb->value;
      counter_value = p_counter_cb->value;
    }

    /* XXX: The counter core is locked here to get all the triggers expired at
            this tick and when a cycling triggers is reinserted in queue.
            When the action is actually performed the core have to be released
            to not have nested critical sections.
            To handle possible races due to cycling triggers a state
            protocol have been implemented. */
    osEE_lock_core(p_cdb);

    p_triggered_db = p_counter_cb->trigger_queue;

    if (p_triggered_db != NULL) {
      P2CONST(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
        p_triggered_cb = p_triggered_db->p_trigger_cb;

      if (p_triggered_cb->when == counter_value) {
        /* Pop All Triggered from the Trigger Queue */
        P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
          p_current = p_triggered_db;
        P2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_DATA)
          p_previous;

        do {
          /* Now I will use previous to hold the previous checked alarm */
          CONSTP2VAR(OsEE_TriggerCB, AUTOMATIC, OS_APPL_DATA)
            p_current_cb = p_current->p_trigger_cb;
          p_previous = p_current;
          /* Set this Trigger as Expired */
          p_current_cb->status = OSEE_TRIGGER_EXPIRED;
          p_current = p_current_cb->p_next;
        } while ((p_current != NULL) &&
          (p_current->p_trigger_cb->when == counter_value));

        /* I set the end of handled queue */
        p_previous->p_trigger_cb->p_next = NULL;
        /* I set the head of the trigger queue to the current value
           (maybe NULL) */
        p_counter_cb->trigger_queue = p_current;

        /* Handle actions outside the critical sections, to not incur in
           nested critical sections. */
        osEE_unlock_core(p_cdb);

        /* Handle Actions */
        do {
          CONSTP2VAR(OsEE_TriggerDB, AUTOMATIC, OS_APPL_CONST)
            p_trigger_to_be_handled_db = p_triggered_db;

          /* Prepare next trigger to be handled here, before actually handle
           * the current one, otherwise cycling triggers will mess with the
           * list of triggers that have to be handled now */
          p_triggered_db = p_triggered_db->p_trigger_cb->p_next;

#if (defined(OSEE_COUNTER_TRIGGER_TYPES))
          {
            CONSTP2VAR(OsEE_AlarmDB, AUTOMATIC, OS_APPL_CONST) 
              p_alarm_db =
                osEE_trigger_get_alarm_db(p_trigger_to_be_handled_db);
            if (p_alarm_db != NULL) {
              osEE_counter_handle_alarm(p_counter_db,
                p_trigger_to_be_handled_db);
            } else {
              osEE_counter_handle_st_expiry_point(p_counter_db,
                p_trigger_to_be_handled_db);
            }
          }
#elif (defined(OSEE_HAS_ALARMS))
          osEE_counter_handle_alarm(p_counter_db, p_trigger_to_be_handled_db);
#elif (defined(OSEE_HAS_SCHEDULE_TABLES))
          osEE_counter_handle_st_expiry_point(p_counter_db,
            p_trigger_to_be_handled_db);
#endif /* OSEE_COUNTER_TRIGGER_TYPES elif OSEE_HAS_ALARMS elif
          OSEE_HAS_SCHEDULE_TABLES */
        } while (p_triggered_db != NULL);
      } else {
        osEE_unlock_core(p_cdb);
      }
    } else {
      osEE_unlock_core(p_cdb);
    }
  }
}
