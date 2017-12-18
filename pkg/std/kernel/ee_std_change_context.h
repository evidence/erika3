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

/** \file   ee_std_change_context.h
 *  \brief  Standard Change Context.
 *
 *  This files contains the declaration of a set of standard internals functions
 *  used to perform context switch.
 *
 *  \note   TO BE DOCUMENTED!!!
 *
 *  \author Errico Guidieri
 *  \date   2016
 */

#if (!defined(OSEE_STD_CHANGE_CONTEXT_H))
#define OSEE_STD_CHANGE_CONTEXT_H

#include "ee_cfg.h"
#include "ee_compiler.h"
#include "ee_utils.h"
#include "ee_platform_types.h"
#include "ee_hal.h"
#include "ee_api_types.h"
#include "ee_hal_internal_types.h"
#include "ee_scheduler_types.h"
#include "ee_kernel_types.h"

/*******************************************************************************
                        Standard HAL For Initialization
 ******************************************************************************/
#if (defined(OSEE_API_DYNAMIC))
FUNC(OsEE_bool, OS_CODE)
  osEE_hal_hdb_init
(
  VAR(CoreIdType, AUTOMATIC)                core_id,
  P2VAR(OsEE_HDB, AUTOMATIC, OS_APPL_DATA)  p_hdb,
  VAR(MemSize, AUTOMATIC)                   stack_size
);
#endif /* OSEE_API_DYNAMIC */

/*******************************************************************************
                           Standard Context Change
 ******************************************************************************/
FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
);

FUNC(void, OS_CODE)
  osEE_hal_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
);

FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
);

FUNC(void, OS_CODE)
  osEE_hal_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
);

FUNC(void, OS_CODE_NO_RETURN)
  osEE_hal_terminate_ctx
(
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_term_scb,
  VAR(OsEE_kernel_cb, AUTOMATIC)            kernel_cb
);

#if (defined(OSEE_API_DYNAMIC))
FUNC(StatusType, OS_CODE)
  osEE_hal_set_isr2_source
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb,
  VAR(ISRSource,  AUTOMATIC)                source_id
);
#endif /* OSEE_API_DYNAMIC */

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_hal_terminate_activation
(
  P2VAR(OsEE_HDB, AUTOMATIC, OS_APPL_DATA)  p_to_term,
  VAR(OsEE_kernel_cb, AUTOMATIC)            kernel_cb
)
{
  osEE_hal_terminate_ctx(p_to_term->p_scb, kernel_cb);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_idle_task_start
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_idle_tdb
)
{
  osEE_hal_save_ctx_and_ready2stacked(p_idle_tdb, p_idle_tdb->hdb.p_scb,
    p_idle_tdb->hdb.p_scb);
}

FUNC(void, OS_CODE)
  osEE_idle_task_terminate
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_idle_tdb
);

#if (defined(OSEE_API_DYNAMIC))
FUNC(OsEE_bool, OS_CODE)
  osEE_std_cpu_startos ( void );
#else
LOCAL_INLINE FUNC(OsEE_bool, OS_CODE)
  osEE_std_cpu_startos ( void ) {
  /* Nothing to do in static configuration */
  return OSEE_TRUE;
}
#endif /* OSEE_API_DYNAMIC */

#if (defined(OSEE_RQ_MULTIQUEUE))
#if (!defined(OSEE_GET_MSB_INLINE))
#define OSEE_GET_MSB_INLINE
#endif /* OSEE_GET_MSB_INLINE */

OSEE_GET_MSB_INLINE FUNC(MemSize, OS_CODE)
  osEE_hal_get_msb
(
  VAR(OsEE_rq_mask, AUTOMATIC) mask
);
#endif /* OSEE_RQ_MULTIQUEUE */

#if (defined(OSEE_SINGLECORE))
LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_hal_signal_broadcast
(
  void
)
{
  /* Nothing to do in single core */
  ((void)0);
}

LOCAL_INLINE FUNC(void, OS_CODE)
  osEE_hal_signal_core
(
  VAR(CoreIdType, AUTOMATIC)  core_id
)
{
  /* Nothing to do in single core */
  ((void)core_id);
}
#endif /* OSEE_SINGLECORE */

#endif /* !OSEE_STD_CHANGE_CONTEXT_H */
