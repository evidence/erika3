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

/** \file  ee_scheduler.h
 *  \brief  OSEK Kernel Scheduler Internals.
 *
 *  This files contains all OSEK Kernel Scheduler Internals in Erika Enterprise.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */

#if (!defined(OSEE_SCHEDULER_H))
#define OSEE_SCHEDULER_H

#include "ee_cfg.h"
#include "ee_utils.h"
#include "ee_compiler.h"
#include "ee_platform_types.h"
#include "ee_api_types.h"
#include "ee_hal_internal_types.h"
#include "ee_scheduler_types.h"
#include "ee_kernel_types.h"

FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_rq_insert
(
  P2VAR(OsEE_RQ, AUTOMATIC, OS_APPL_DATA)       p_rq,
  P2VAR(OsEE_SN, AUTOMATIC, OS_APPL_DATA)       p_sn_new,
  CONSTP2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA) p_tdb_new
);

#if (defined(OSEE_ALLOW_TASK_MIGRATION))
typedef VAR(OsEE_SN, TYPEDEF)   OsEE_preempt;
#else
typedef VAR(OsEE_TDB, TYPEDEF)  OsEE_preempt;
#endif /* OSEE_ALLOW_TASK_MIGRATION */

FUNC_P2VAR(OsEE_preempt, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_core_rq_preempt_stk
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_RQ,  AUTOMATIC, OS_APPL_DATA)  p_rq
);

FUNC_P2VAR(OsEE_SN, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_core_pop_running
(
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_RQ,  AUTOMATIC, OS_APPL_DATA)  p_rq
);

/* Scheduler Entry Points */
#if (!defined(OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE))
FUNC(void, OS_CODE)
  osEE_scheduler_task_end
(
  void
);
#endif /* !OSEE_KERNEL_TERMINATE_ACTIVATION_OVERRIDE */

FUNC(void, OS_CODE)
  osEE_scheduler_task_wrapper_run
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_to
);

FUNC(void, OS_CODE)
  osEE_scheduler_task_wrapper_restore
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_to
);

FUNC(StatusType, OS_CODE)
  osEE_scheduler_task_activated
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb_act,
  CONST(OsEE_bool, AUTOMATIC)               is_preemption_point
);

FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_task_preemption_point
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb
);

FUNC_P2VAR(OsEE_TDB, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_task_block_current
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)    p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)    p_cdb,
  P2VAR(OsEE_SN *,  AUTOMATIC, OS_APPL_DATA)  p_sn_blocked
);

FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_task_unblocked
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_SN,  AUTOMATIC, OS_APPL_DATA)  p_sn_released
);

FUNC(void, OS_CODE)
  osEE_scheduler_task_set_running
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb
);

FUNC_P2VAR(OsEE_TDB, OS_APPL_DATA, OS_CODE)
  osEE_scheduler_task_terminated
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  P2VAR(OsEE_TDB *, AUTOMATIC, OS_APPL_DATA)  pp_tdb_from
);

#if (defined(OSEE_API_DYNAMIC))
FUNC(OsEE_bool, OS_CODE)
  osEE_scheduler_task_reserve_activations
(
  P2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_DATA)  p_kdb,
  P2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_DATA)  p_cdb,
  VAR(TaskActivation, AUTOMATIC)            activations
);
#endif /* OSEE_API_DYNAMIC */

#endif /* !OSEE_SCHEDULER_H */
