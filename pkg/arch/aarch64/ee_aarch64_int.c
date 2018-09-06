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

/** \file   ee_aarch64_int.c
 *  \brief  Interrupt configuration.
 *
 *  This files contains the interrupt configuration implementation for
 *  a specific Architecture in Erika Enterprise.
 *
 *  \author  Errico Gudiieri
 *  \date    2017
 */

#include "ee_internal.h"

OsEE_aarch64_hnd_type
  osEE_aarch64_ppi_isr_vectors[OsNumberOfCores][OSEE_GIC_MIN_SPI_ID];
  
OsEE_aarch64_hnd_type
  osEE_aarch64_spi_isr_vectors[OSEE_GIC_ISR_NUM - OSEE_GIC_MIN_SPI_ID];

void osEE_aarch64_isr_wrapper(OsEE_ISR_CTX * p_isr_ctx)
{
  uint32_t irqn;

  while ( 1 ) {
    irqn = osEE_gicc_read_ack();
    if (irqn == OSEE_GIC_SPURIOUS_ISR) {
      break;
    }
    {
#if (!defined(OSEE_SINGLECORE))
      /* Special IIRQ that ask the core to preempt actual TASK */
      if (irqn == OSEE_AARCH64_RESCHEDULE_IIRQ)
      {
        /* TODO: Implement Schedule Point in ISR2 */
      } else
#endif /* !OSEE_SINGLECORE */
      {
        OsEE_aarch64_hnd_type * p_hnd;

        if (irqn < OSEE_GIC_MIN_SPI_ID) {
          CoreIdType const cpu_id = osEE_get_curr_core_id();
          p_hnd = &osEE_aarch64_ppi_isr_vectors[cpu_id][irqn];
        } else {
          p_hnd = &osEE_aarch64_spi_isr_vectors[irqn - OSEE_GIC_MIN_SPI_ID];
        }

        if (p_hnd->cat == OSEE_ISR_CAT_2) {
          TaskType const tid = p_hnd->hnd.tid;
          if (tid != INVALID_TASK) {
            osEE_activate_isr2(tid);
          } else {
            osEE_gicc_eoi(irqn);
          }
        } else if (p_hnd->cat == OSEE_ISR_CAT_1) {
          void (* const p_hnd_func) (void) = p_hnd->hnd.p_hnd_func;
          if (p_hnd_func != NULL) {
            p_hnd_func();
          }
          osEE_gicc_eoi(irqn);
        } else {
          osEE_gicc_eoi(irqn);
        }
      }
    }
  }
}

static StatusType osEE_aarch64_configure_isr2(OsEE_TDB * p_tdb, ISRSource source_id)
{
  StatusType              ev;
  /* Pointer to the ISR handler struct */
  OsEE_aarch64_hnd_type * p_hnd;
  /* HW priority mask */
/* IRQ priority handling in jailhouse is bugged */
#if (!defined(OSEE_PLATFORM_JAILHOUSE))
  OsEE_isr_prio const hw_prio_mask =
    osEE_isr2_virt_to_hw_prio(p_tdb->ready_prio);
#endif /* !OSEE_PLATFORM_JAILHOUSE */

  if (source_id < OSEE_GIC_MIN_SPI_ID) {
    p_hnd = &osEE_aarch64_ppi_isr_vectors[osEE_get_curr_core_id()][source_id];
  } else if (source_id < OSEE_GIC_ISR_NUM) {
    p_hnd = &osEE_aarch64_spi_isr_vectors[source_id - OSEE_GIC_MIN_SPI_ID];
    /* If the source_id is a SPI. Set Current CPU as target for the given
       source */
#if (!defined(OSEE_PLATFORM_JAILHOUSE))
    osEE_gic_v2_set_itargetsr(source_id, osEE_gic_v2_get_cpuif_mask());
#endif /* !OSEE_PLATFORM_JAILHOUSE */
  } else {
    p_hnd = NULL;
  }

  if (p_hnd != NULL) {
    /* Configure the handler struct */
    p_hnd->cat     = OSEE_ISR_CAT_2;
    p_hnd->hnd.tid = p_tdb->tid;
#if (!defined(OSEE_PLATFORM_JAILHOUSE))
    osEE_gic_v2_set_hw_prio(source_id, hw_prio_mask);
#endif /* !OSEE_PLATFORM_JAILHOUSE */
    osEE_gic_v2_enable_irq(source_id);
    ev = E_OK;
  } else {
    ev = E_OS_SYS_INIT;
  }
  return ev;
}

FUNC(OsEE_bool, OS_CODE) osEE_cpu_startos(void)
{
  OsEE_bool const continue_startos = osEE_std_cpu_startos();

#if (!defined(OSEE_API_DYNAMIC))
  if (continue_startos == OSEE_TRUE) {
    size_t i;
#if (!defined(OSEE_SINGLECORE))
    CoreIdType const core_id = osEE_get_curr_core_id();
#endif /* !OSEE_SINGLECORE */
/* Initialize ISRs of this core */
    OsEE_KDB * const p_kdb   = osEE_get_kernel();
  
    for (i = 0U; i < (p_kdb->tdb_array_size - 1U); ++i)
    {
      /* ISR2 initialization */
      OsEE_TDB  * const p_tdb = (*p_kdb->p_tdb_ptr_array)[i];

#if (!defined(OSEE_SINGLECORE))
      if (p_tdb->orig_core_id != core_id) {
        continue;
      } else
#endif /* !OSEE_SINGLECORE */
      if (p_tdb->task_type == OSEE_TASK_TYPE_ISR2) {
        osEE_aarch64_configure_isr2(p_tdb, p_tdb->hdb.isr2_src);
      }
    }
#if (defined(OSEE_HAS_SYSTEM_TIMER))
    osEE_aarch64_system_timer_init();
#endif /* OSEE_HAS_SYSTEM_TIMER */
  }
#endif /* !OSEE_API_DYNAMIC */

  return continue_startos;
}

#if (defined(OSEE_API_DYNAMIC))
StatusType osEE_hal_set_isr2_source
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb,
  VAR(ISRSource,  AUTOMATIC)                source_id
)
{

  StatusType const ev = osEE_aarch64_configure_isr2(p_tdb, source_id);

  if (ev == E_OK) {
    p_tdb->hdb.isr2_src = source_id;
  }

  return ev;
}
#endif /* OSEE_API_DYNAMIC */
