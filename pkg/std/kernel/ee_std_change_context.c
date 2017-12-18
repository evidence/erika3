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

/** \file   ee_std_change_context.c
 *  \brief  Standard Change Context Implementation.
 *
 *  This files contains the definition of a set of standard internals functions
 *  used to perform context switch.
 *
 *  \note TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2016
 */
#include "ee_internal.h"

FUNC(void, OS_CODE)
  osEE_change_context_from_running
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_to_tcb  = p_to->p_tcb;
  CONST(TaskStateType, AUTOMATIC)     status_prev_running = p_to_tcb->status;

  p_to_tcb->status = OSEE_TASK_RUNNING;

  if (status_prev_running == OSEE_TASK_READY_STACKED) {
    osEE_hal_save_ctx_and_restore_ctx(p_to, p_to->hdb.p_scb,
      p_from->hdb.p_scb);
  } else {
    osEE_hal_save_ctx_and_ready2stacked(p_to, p_to->hdb.p_scb,
      p_from->hdb.p_scb);
  }
}

FUNC(void, OS_CODE)
  osEE_change_context_from_task_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  CONSTP2VAR(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_to_tcb  = p_to->p_tcb;
  CONST(TaskStateType, AUTOMATIC)     status_prev_running = p_to_tcb->status;

  p_to_tcb->status = OSEE_TASK_RUNNING;

  if (status_prev_running == OSEE_TASK_READY_STACKED) {
    osEE_hal_restore_ctx(p_to, p_to->hdb.p_scb);
  } else {
    osEE_hal_ready2stacked(p_to, p_to->hdb.p_scb);
  }
  /* STD Implementation do not use p_from here, but I cannot assure
     that any implementation won't do that */
  (void)p_from;
}

FUNC(void, OS_CODE)
  osEE_idle_task_terminate
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_idle_tdb
)
{
  P2VAR(OsEE_CTX, AUTOMATIC, OS_APPL_DATA)      p_ctx;

  CONSTP2VAR(OsEE_HDB, AUTOMATIC, OS_APPL_DATA) p_idle_hdb  = &p_idle_tdb->hdb;
  CONSTP2VAR(OsEE_SDB, AUTOMATIC, OS_APPL_DATA) p_sdb       = p_idle_hdb->p_sdb;
  CONSTP2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA) p_scb       = p_idle_hdb->p_scb;
  CONSTP2VAR(OsEE_CTX, AUTOMATIC, OS_APPL_DATA) p_bos       = p_sdb->p_bos;
  P2VAR(OsEE_CTX, AUTOMATIC, OS_APPL_DATA)      p_tos       = p_scb->p_tos;

  do {
    p_ctx = p_tos;
    p_tos = p_tos->p_ctx;
  } while ((p_tos != NULL) && (p_tos != p_bos));

  /* Unwind the stack until the last context*/
  p_scb->p_tos = p_ctx;

  osEE_hal_restore_ctx(p_idle_tdb, p_scb);
}

