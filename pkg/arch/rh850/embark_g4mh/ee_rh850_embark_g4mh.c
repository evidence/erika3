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

/** \file   ee_rh850_embark_g4mh.c
 *  \brief  OS features Integration file with Embark G4MH Software Library
 *
 *  \author Errico Guidieri
 *  \date   2018
 */
#include "ee_internal.h"
#include <r_rh850.h>
#if 0
/* Free Running Mode too complicated for now */
#if (defined(OSEE_HAS_SYSTEM_TIMER))
/* Work around for missing primitive to handle OSTM in free-running mode */
#include <r_ostm_dev.h>
#endif /* OSEE_HAS_SYSTEM_TIMER */
#endif /* 0 */

#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
#if (!defined(OSEE_RH850_EI_REFTABLE_CNT))
#define OSEE_RH850_EI_REFTABLE_CNT (695U)
#endif /* !OSEE_RH850_EI_REFTABLE_CNT */

/* Alternative Reference Table for Core0 */
extern g4mh_isr_t osEE_rh850_core0_reftabl_ei[OSEE_RH850_EI_REFTABLE_CNT];
#endif /* 0 */

#if (defined(OSEE_SINGLECORE))
extern OsEE_rh850_embark_g4mh_intc_cfg g_intc_OsEECfg;

OSEE_STATIC_INLINE OsEE_rh850_embark_g4mh_intc_cfg * OSEE_ALWAYS_INLINE
  osEE_rh850_get_intc_cfg(CoreIdType core_id)
{
  /* Touch unused parameter */
  (void)core_id;
  return &g_intc_OsEECfg;
}

#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
OSEE_STATIC_INLINE g4mh_isr_t * OSEE_ALWAYS_INLINE
  osEE_rh850_get_reftabl_ei(CoreIdType core_id)
{
  /* Touch unused parameter */
  (void)core_id;
  return &osEE_rh850_core0_reftabl_ei[0U];
}
#endif /* 0 */
#else

extern OsEE_rh850_embark_g4mh_intc_cfg g_intc_OsEEPeid0Cfg;
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
extern OsEE_rh850_embark_g4mh_intc_cfg g_intc_OsEEPeid1Cfg;
#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
extern g4mh_isr_t osEE_rh850_core1_reftabl_ei[OSEE_RH850_EI_REFTABLE_CNT];
#endif /* 0 */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
extern OsEE_rh850_embark_g4mh_intc_cfg g_intc_OsEEPeid2Cfg;
#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
extern g4mh_isr_t osEE_rh850_core2_reftabl_ei[OSEE_RH850_EI_REFTABLE_CNT];
#endif /* 0 */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
extern OsEE_rh850_embark_g4mh_intc_cfg g_intc_OsEEPeid3Cfg;
#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
extern g4mh_isr_t osEE_rh850_core3_reftabl_ei[OSEE_RH850_EI_REFTABLE_CNT];
#endif /* 0 */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
extern OsEE_rh850_embark_g4mh_intc_cfg g_intc_OsEEPeid4Cfg;
#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
extern g4mh_isr_t osEE_rh850_core4_reftabl_ei[OSEE_RH850_EI_REFTABLE_CNT];
#endif /* 0 */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x20U)
extern OsEE_rh850_embark_g4mh_intc_cfg g_intc_OsEEPeid5Cfg;
#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
extern g4mh_isr_t osEE_rh850_core5_reftabl_ei[OSEE_RH850_EI_REFTABLE_CNT];
#endif /* 0 */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x20U */

OSEE_STATIC_INLINE OsEE_rh850_embark_g4mh_intc_cfg * OSEE_ALWAYS_INLINE
  osEE_rh850_get_intc_cfg(CoreIdType core_id)
{
  OsEE_rh850_embark_g4mh_intc_cfg * p_intc_cfg;

  switch(core_id) {
    case OS_CORE_ID_0:
      p_intc_cfg = &g_intc_OsEEPeid0Cfg;
    break;
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
    case OS_CORE_ID_1:
      p_intc_cfg = &g_intc_OsEEPeid1Cfg;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
    case OS_CORE_ID_2:
      p_intc_cfg = &g_intc_OsEEPeid2Cfg;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
    case OS_CORE_ID_3:
      p_intc_cfg = &g_intc_OsEEPeid3Cfg;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
    case OS_CORE_ID_4:
      p_intc_cfg = &g_intc_OsEEPeid4Cfg;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x20U)
    case OS_CORE_ID_5:
      p_intc_cfg = &g_intc_OsEEPeid5Cfg;
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x20U */
    default:
      /* This should never happens */
      p_intc_cfg = NULL;
    break;
  }

  return p_intc_cfg;
}

#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
OSEE_STATIC_INLINE g4mh_isr_t * OSEE_ALWAYS_INLINE
  osEE_rh850_get_reftabl_ei(CoreIdType core_id)
{
  g4mh_isr_t * p_g4mh_isr;

  switch(core_id) {
    case OS_CORE_ID_0:
      p_g4mh_isr = &osEE_rh850_core0_reftabl_ei[0U];
    break;
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
    case OS_CORE_ID_1:
      p_g4mh_isr = &osEE_rh850_core1_reftabl_ei[0U];
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
    case OS_CORE_ID_2:
      p_g4mh_isr = &osEE_rh850_core2_reftabl_ei[0U];
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
    case OS_CORE_ID_3:
      p_g4mh_isr = &osEE_rh850_core3_reftabl_ei[0U];
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
    case OS_CORE_ID_4:
      p_g4mh_isr = &osEE_rh850_core4_reftabl_ei[0U];
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x20U)
    case OS_CORE_ID_5:
      p_g4mh_isr = &osEE_rh850_core5_reftabl_ei[0U];
    break;
#endif /* OSEE_CORE_ID_VALID_MASK & 0x20U */
    default:
      /* This should never happens */
      p_g4mh_isr = NULL;
    break;
  }

  return p_g4mh_isr;
}
#endif /* 0 */
#endif /* else OSEE_SINGLECORE */

/* Nothing to do. All the initialiazation is done in osEE_os_init */
OsEE_bool osEE_cpu_startos(void)
{
#if (defined(OSEE_HAS_SYSTEM_TIMER))
  MemSize i;
  MemSize tdb_size;
  OsEE_KDB * const p_kdb = osEE_get_kernel();
#endif /* OSEE_HAS_SYSTEM_TIMER */
  CoreIdType const curr_core_id = osEE_get_curr_core_id();
  OsEE_rh850_embark_g4mh_intc_cfg * const
    p_intc_cfg = osEE_rh850_get_intc_cfg(curr_core_id);

#if 0 /* EG: Alternate Reference Table for Interrupts is no more needed */
  /* Set Alternative Reference Table */
  R_G4MH_SetRefTable(osEE_rh850_get_reftabl_ei(curr_core_id));
#endif /* 0 */
  /* Initialize the INTC */
  R_INTC_Init(p_intc_cfg->p_intc_cfg_array, p_intc_cfg->intc_cfg_num);
#if (!defined(OSEE_SINGLECORE))
  osEE_rh850_setup_inter_irqs();
#endif /* !OSEE_SINGLECORE */
#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
  osEE_rh850_initialize_core_stacks();
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

#if (defined(OSEE_HAS_SYSTEM_TIMER))
  tdb_size = p_kdb->tdb_array_size - 1U;
  for (i = 0U; i < tdb_size; ++i) {
    /* ISR2 initialization */
    OsEE_TDB  * const p_tdb = (*p_kdb->p_tdb_ptr_array)[i];
#if (!defined(OSEE_SINGLECORE))
    if (p_tdb->orig_core_id == curr_core_id) {
#endif /* !OSEE_SINGLECORE */
      if (p_tdb->task_type == OSEE_TASK_TYPE_ISR2) {
        if (p_tdb->task_func == &osEE_rh850_system_timer_handler) {
          osEE_rh850_initialize_system_timer(p_tdb);
          break;
        }
      }
#if (!defined(OSEE_SINGLECORE))
    }
#endif /* !OSEE_SINGLECORE */
  }
#endif /* OSEE_HAS_SYSTEM_TIMER */
  return OSEE_TRUE;
}

#if (!defined(OSEE_SINGLECORE))
void osEE_hal_start_core(CoreIdType core_id) {
  R_BOOT_SetPeActive((boot_peid_t)(1U << (OsEE_reg)core_id));
}

void osEE_rh850_setup_inter_irqs(void) {
  R_IPIR_ClrChPeIntr(IPIR_CH_0, OSEE_CORE_ID_VALID_MASK);
  R_IPIR_SetChPeEn(IPIR_CH_0, OSEE_CORE_ID_VALID_MASK);
}

/* Signal the core "cpu" (0/1/2/3/4/5) by sending an IIRQ. */
void osEE_hal_signal_core(CoreIdType core_id) {
  /* Trigger interrupt to PE core_id */
  R_IPIR_TrigChPeIntr(IPIR_CH_0, (boot_peid_t)(1U << (OsEE_reg)core_id));
}

/* Acknowledge the signal received by the core "cpu" (0/1/2/3/4/5) */
void osEE_rh850_ack_signal(void) {
  R_IPIR_ClrChPeIntr(IPIR_CH_0, OSEE_CORE_ID_VALID_MASK);
}

#if (defined(OSEE_SCHEDULER_GLOBAL))
void osEE_hal_signal_broadcast(void) {
  R_IPIR_TrigChPeIntr(IPIR_CH_0, OSEE_CORE_ID_VALID_MASK);
}
#endif /* OSEE_SCHEDULER_GLOBAL */
#endif /* !OSEE_SINGLECORE */

void osEE_rh850_isr2_embark_g4mh_wrapper(TaskType tid) {
  /* Rise PLMR and get the previous value back, rising it's not necessary,
     but it doesn't hurt; I'm doing this to get the previous value to be
     restored */
  OsEE_reg flags = osEE_hal_begin_nested_primitive();
  /* For Now I need Only this */
  osEE_activate_isr2(tid);

  /* I need to disable IRQ here since I'm lowering PLMR, and I don't want to
     allow nesting here before context restoring. Multiple ISR context
     stacking for the same TASK have not to happens for stack bounding. */
  osEE_hal_disableIRQ();
  osEE_hal_end_nested_primitive(flags);
}

#if (defined(OSEE_HAS_SYSTEM_TIMER))

#define OSEE_RH850_OSTM0_EIINT OSEE_RH850_DEVICE_18

/* MSTB OSTM Mode Channels array size */
#if (defined(OSEE_CORE_ID_VALID_MASK))
#if (OSEE_CORE_ID_VALID_MASK >= 0x20U)
#define OSEE_MSTB_MOD_CHNL_SIZE (7U)
#elif (OSEE_CORE_ID_VALID_MASK >= 0x10U)
#define OSEE_MSTB_MOD_CHNL_SIZE (6U)
#elif (OSEE_CORE_ID_VALID_MASK >= 0x08U)
#define OSEE_MSTB_MOD_CHNL_SIZE (5U)
#elif (OSEE_CORE_ID_VALID_MASK >= 0x04U)
#define OSEE_MSTB_MOD_CHNL_SIZE (4U)
#elif (OSEE_CORE_ID_VALID_MASK >= 0x02U)
#define OSEE_MSTB_MOD_CHNL_SIZE (3U)
#else
#define OSEE_MSTB_MOD_CHNL_SIZE (2U)
#endif
#else
#define OSEE_MSTB_MOD_CHNL_SIZE (2U)
#endif /* OSEE_CORE_ID_VALID_MASK */

void osEE_rh850_initialize_system_timer(OsEE_TDB * p_tdb) {
  static int32_t const mstb_chnl_by_core[OS_CORE_ID_ARR_SIZE] = {
#if (defined(OSEE_SYSTEM_TIMER_CORE0_DEVICE))
#if (OSEE_SYSTEM_TIMER_CORE0_DEVICE == OSEE_RH850_OSTM0_EIINT)
    (int32_t)OSTM_0
#else
    (int32_t)OSTM_1
#endif /* OSEE_SYSTEM_TIMER_CORE0_DEVICE == OSEE_RH850_OSTM0_EIINT */
#else
    -1
#endif /* OSEE_SYSTEM_TIMER_CORE0_DEVICE */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x02U)
#if (defined(OSEE_SYSTEM_TIMER_CORE1_DEVICE))
#if (OSEE_SYSTEM_TIMER_CORE1_DEVICE == OSEE_RH850_OSTM0_EIINT)
    , (int32_t)OSTM_0
#else
    , (int32_t)OSTM_2
#endif /* OSEE_SYSTEM_TIMER_CORE1_DEVICE == OSEE_RH850_OSTM0_EIINT */
#else
    , -1
#endif /* OSEE_SYSTEM_TIMER_CORE1_DEVICE */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x04U)
#if (defined(OSEE_SYSTEM_TIMER_CORE2_DEVICE))
#if (OSEE_SYSTEM_TIMER_CORE2_DEVICE == OSEE_RH850_OSTM0_EIINT)
    , (int32_t)OSTM_0
#else
    , (int32_t)OSTM_3
#endif /* OSEE_SYSTEM_TIMER_CORE2_DEVICE == OSEE_RH850_OSTM0_EIINT */
#else
    , -1
#endif /* OSEE_SYSTEM_TIMER_CORE2_DEVICE */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x08U)
#if (defined(OSEE_SYSTEM_TIMER_CORE3_DEVICE))
#if (OSEE_SYSTEM_TIMER_CORE3_DEVICE == OSEE_RH850_OSTM0_EIINT)
    , (int32_t)OSTM_0
#else
    , (int32_t)OSTM_4
#endif /* OSEE_SYSTEM_TIMER_CORE3_DEVICE == OSEE_RH850_OSTM0_EIINT */
#else
    , -1
#endif /* OSEE_SYSTEM_TIMER_CORE3_DEVICE */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x10U)
#if (defined(OSEE_SYSTEM_TIMER_CORE4_DEVICE))
#if (OSEE_SYSTEM_TIMER_CORE4_DEVICE == OSEE_RH850_OSTM0_EIINT)
    , (int32_t)OSTM_0
#else
    , (int32_t)OSTM_5
#endif /* OSEE_SYSTEM_TIMER_CORE4_DEVICE == OSEE_RH850_OSTM0_EIINT */
#else
    , -1
#endif /* OSEE_SYSTEM_TIMER_CORE4_DEVICE */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x20U)
#if (defined(OSEE_SYSTEM_TIMER_CORE5_DEVICE))
#if (OSEE_SYSTEM_TIMER_CORE5_DEVICE == OSEE_RH850_OSTM0_EIINT)
    , (int32_t)OSTM_0
#else
    , (int32_t)OSTM_6
#endif /* OSEE_SYSTEM_TIMER_CORE5_DEVICE == OSEE_RH850_OSTM0_EIINT */
#else
    , -1
#endif /* OSEE_SYSTEM_TIMER_CORE5_DEVICE */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x10U */
  };
  static const TickType ostick_durations[OS_CORE_ID_ARR_SIZE] = {
#if (defined(OSTICKDURATION))
    OSTICKDURATION
#elif (defined(OSTICKDURATION_CORE0))
    OSTICKDURATION_CORE0
#else
    ((TickType)-1)
#endif /* OSTICKDURATION || OSTICKDURATION_CORE0 */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x02U)
#if (defined(OSTICKDURATION_CORE1))
    , OSTICKDURATION_CORE1
#else
    , ((TickType)-1)
#endif /* OSTICKDURATION_CORE1 */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x04U)
#if (defined(OSTICKDURATION_CORE2))
    , OSTICKDURATION_CORE2
#else
    , ((TickType)-1)
#endif /* OSTICKDURATION_CORE2 */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x08U)
#if (defined(OSTICKDURATION_CORE3))
    , OSTICKDURATION_CORE3
#else
    , ((TickType)-1)
#endif /* OSTICKDURATION_CORE3 */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x10U)
#if (defined(OSTICKDURATION_CORE4))
    , OSTICKDURATION_CORE4
#else
    , ((TickType)-1)
#endif /* OSTICKDURATION_CORE4 */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x20U)
#if (defined(OSTICKDURATION_CORE5))
    , OSTICKDURATION_CORE5
#else
    , ((TickType)-1)
#endif /* OSTICKDURATION_CORE5 */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x20U */
  };

  static mstb_mod_chnl_t const mstb_mod_chnl[OSEE_MSTB_MOD_CHNL_SIZE] = {
    MSTB_OSTM_0, MSTB_OSTM_1
#if (OSEE_MSTB_MOD_CHNL_SIZE > 2U)
    , MSTB_OSTM_2
#endif
#if (OSEE_MSTB_MOD_CHNL_SIZE > 3U)
/* To Be Re-enabled when we will get the hands on an Embark for FCC2 */
    , MSTB_OSTM_3
#endif
#if (OSEE_MSTB_MOD_CHNL_SIZE > 4U)
    , MSTB_OSTM_4
#endif
#if (OSEE_MSTB_MOD_CHNL_SIZE > 5U)
    , MSTB_OSTM_5
#endif
#if (OSEE_MSTB_MOD_CHNL_SIZE > 6U)
    , MSTB_OSTM_6
#endif
  };

  CoreIdType  const curr_core_id  = osEE_get_curr_core_id();
  int32_t     const ostm_unit     = mstb_chnl_by_core[curr_core_id];
  ostm_cfg_t        ostm_cfg;

#if (!defined(OSEE_SINGLECORE))
  /* Used to flag ostm0 initialization in case of multicore environment */
  static OsEE_spin_lock     mstb_lock;
  static OsEE_reg volatile  ostm0_init_flag;
  OsEE_bool                 ostm0_init_to_do;

  if (ostm_unit == (int32_t)OSTM_0) {
    ostm0_init_to_do = (osEE_rh850_cmpswapw_l(&ostm0_init_flag, 0U, 1U) == 0U);
  } else {
    ostm0_init_to_do = OSEE_FALSE;
  }
  if (((ostm_unit != (int32_t)OSTM_0) && (ostm_unit != -1)) || ostm0_init_to_do)
#endif /* !OSEE_SINGLECORE */
  {
    ostm_cfg.cmp    = OSTM_CNT_1USEC(ostick_durations[curr_core_id] / 1000U);
    ostm_cfg.tmr    = (ostm_unit_t)ostm_unit;
    ostm_cfg.mode   = OSTM_INTERVAL; /* OSTM_FREERUN; */
    ostm_cfg.ctrl   = OSTM_HW;
    ostm_cfg.lvl    = OSTM_HIGH; /* Initial Level */
    /* Interrupt on counter match but not at counter start */
    ostm_cfg.irq_on = OSTM_IRQ_MATCH;
    /* start OSTM */
    ostm_cfg.ena    = OSTM_ENA;

#if (!defined(OSEE_SINGLECORE))
    osEE_hal_spin_lock(&mstb_lock);
#endif /* !OSEE_SINGLECORE */
    /* Unlock the MSR registers */
    R_MSTB_SetProtection(MSTB_PROT_UNLOCK);
    R_MSTB_SetMode(mstb_mod_chnl[ostm_unit], MSTB_OPER_MODE);
    /* Lock the MSR registers */
    R_MSTB_SetProtection(MSTB_PROT_LOCK);
#if (!defined(OSEE_SINGLECORE))
    osEE_hal_spin_unlock(&mstb_lock);
#endif /* !OSEE_SINGLECORE */

    /* configure scheduler OSTMs
     * IMPORTANT: OSTM configuration can have more channels
     */
    R_OSTM_Init(&ostm_cfg, 1U);
  }
  /* Touch Unused parameter */
  (void)p_tdb;
}

#if (!defined(OSEE_SINGLECORE))
#if (!defined(OSEE_SYSTEM_TIMER_CORE0_ISR_TID))
#define OSEE_SYSTEM_TIMER_CORE0_ISR_TID INVALID_TASK
#endif /* OSEE_SYSTEM_TIMER_CORE0_ISR_TID */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x02U)
#if (!defined(OSEE_SYSTEM_TIMER_CORE1_ISR_TID))
#define OSEE_SYSTEM_TIMER_CORE1_ISR_TID INVALID_TASK
#endif /* OSEE_SYSTEM_TIMER_CORE1_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x02U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x04U)
#if (!defined(OSEE_SYSTEM_TIMER_CORE2_ISR_TID))
#define OSEE_SYSTEM_TIMER_CORE2_ISR_TID INVALID_TASK
#endif /* OSEE_SYSTEM_TIMER_CORE2_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x04U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x08U)
#if (!defined(OSEE_SYSTEM_TIMER_CORE3_ISR_TID))
#define OSEE_SYSTEM_TIMER_CORE3_ISR_TID INVALID_TASK
#endif /* OSEE_SYSTEM_TIMER_CORE3_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x08U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x10U)
#if (!defined(OSEE_SYSTEM_TIMER_CORE4_ISR_TID))
#define OSEE_SYSTEM_TIMER_CORE4_ISR_TID INVALID_TASK
#endif /* OSEE_SYSTEM_TIMER_CORE4_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x10U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x20U)
#if (!defined(OSEE_SYSTEM_TIMER_CORE5_ISR_TID))
#define OSEE_SYSTEM_TIMER_CORE5_ISR_TID INVALID_TASK
#endif /* OSEE_SYSTEM_TIMER_CORE5_ISR_TID */
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x20U */
#endif /* !OSEE_SINGLECORE */

void osEE_rh850_system_timer_handler_wrapper(void) {
#if (!defined(OSEE_SINGLECORE))
  static TaskType const st_tid[OS_CORE_ID_ARR_SIZE] = {
    OSEE_SYSTEM_TIMER_CORE0_ISR_TID
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x02U)
    , OSEE_SYSTEM_TIMER_CORE1_ISR_TID
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x02U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x04U)
    , OSEE_SYSTEM_TIMER_CORE2_ISR_TID
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x04U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x08U)
    , OSEE_SYSTEM_TIMER_CORE3_ISR_TID
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x08U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x10U)
    , OSEE_SYSTEM_TIMER_CORE4_ISR_TID
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x10U */
#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK >= 0x20U)
    , OSEE_SYSTEM_TIMER_CORE5_ISR_TID
#endif /* OSEE_CORE_ID_VALID_MASK >= 0x20U */
  };
#endif /* !OSEE_SINGLECORE */

#if (defined(OSEE_SINGLECORE))
  osEE_rh850_isr2_embark_g4mh_wrapper(OSEE_SYSTEM_TIMER_CORE0_ISR_TID);
#else
  osEE_rh850_isr2_embark_g4mh_wrapper(st_tid[osEE_get_curr_core_id()]);
#endif /* OSEE_SINGLECORE */
}

void osEE_rh850_system_timer_handler(void) {
  CoreIdType      const curr_core_id  = osEE_get_curr_core_id();
#if 0
  mstb_mod_chnl_t const ostm_unit     = mstb_chnl_by_core[curr_core_id];

  /* Free-Runnig support is more complicated than this. */
  R_OSTM_SetEna(ostm_unit, OSTM_DIS);
  OSTM[ostm_unit].CMP.WORD += OSTM_CNT_1USEC(OSTICKDURATION / 1000U);
  R_OSTM_SetEna(ostm_unit, OSTM_ENA);
#endif /* 0 */

  osEE_counter_increment(osEE_get_core(curr_core_id)->p_sys_counter_db);
}
#endif /* OSEE_HAS_SYSTEM_TIMER */
