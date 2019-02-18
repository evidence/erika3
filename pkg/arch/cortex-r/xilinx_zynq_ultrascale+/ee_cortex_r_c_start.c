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

/** \file   ee_cortex_r_c_start.c
 *  \brief  ARMv7-R Start-UP (C part)
 *
 *  \author  Errico Guidieri
 *  \date    2017
 */
/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"
#include "xscugic.h"
#include "xscugic_hw.h"
#include "xttcps.h"

#include "ee_internal.h"

#if (defined(OSEE_HAS_SYSTEM_TIMER))
#define OSEE_TICK_RATE_HZ (OSEE_GIGA / OSTICKDURATION)
#else
#define OSEE_TICK_RATE_HZ (10U)
#endif /* OSEE_HAS_SYSTEM_TIMER */

/* Interrupt Controller handler structures */
static XScuGic  osEE_x_gic;
/* Timer used to generate the tick interrupt. */
static XTtcPs   osEE_x_timer;

OsEE_reg osEE_prio_dropping_int_id = ((OsEE_reg)-1);

OsEE_core_id osEE_cortex_r_vcore_id_offset = INVALID_CORE_ID;

static void osEE_cortex_r_gicd_init(void)
{
  /* Get the interrupt controller configuration.
     There's only one GIC for the R5 cluster with id equal to 0, obviously. */
  XScuGic_Config * const p_gic_conf = XScuGic_LookupConfig(0U);

  /* Initialize the GIC hardware and data structure */
  XScuGic_CfgInitialize(&osEE_x_gic, p_gic_conf, p_gic_conf->CpuBaseAddress);

  /* Assure that the running priority is reset to unmasked */
  if (OSEE_ARMV7_GIC_ICCRPR != OSEE_ARMV7_GIC_RUNNING_PRIO_IDLE) {
    OsEE_reg int_id = 0U;
    do {
      OSEE_ARMV7_GIC_EOIR = int_id;
      osEE_prio_dropping_int_id = int_id;

      if (++int_id > 0x3FFU) {
        int_id = 0;
        xil_printf("In %s: GIC initialization failed. "
          "Dropping priority has not been possible...\r\n",  __func__);
      }
    } while (OSEE_ARMV7_GIC_ICCRPR != OSEE_ARMV7_GIC_RUNNING_PRIO_IDLE);
  }
}

void __attribute__((constructor)) osEE_cortex_r_c_start(void)
{
  if (osEE_cortex_r_vcore_id_offset == INVALID_CORE_ID) {
    osEE_cortex_r_vcore_id_offset = osEE_cortex_r_get_vcore_id_raw();
  }

#if (defined(OSEE_API_DYNAMIC))
  /* GICD initialization */
  osEE_cortex_r_gicd_init();
  /* OS data structures initialization */
  osEE_os_init();

  osEE_get_curr_core()->p_idle_task->hdb.p_sdb->p_bos = osEE_get_SP();
#endif /* OSEE_API_DYNAMIC */
}

#if (defined(OSEE_API_DYNAMIC))
OsEE_cortex_r_hnd_type osEE_cortex_r_int_vectors
  [OsNumberOfCores][XSCUGIC_MAX_NUM_INTR_INPUTS] =
{
  [0 ... (OsNumberOfCores - 1U)] =
  {
    [0 ... (XSCUGIC_MAX_NUM_INTR_INPUTS - 1U)] =
    {
      .cat = OSEE_ISR_CAT_2,
      .hnd.tid = INVALID_TASK
    }
  }
};

#if (defined(OSEE_API_DYNAMIC))
static
#else
extern
#endif /* OSEE_API_DYNAMIC */
OsEE_TW osEE_sys_timer_wrap[OsNumberOfCores];

static void osEE_cortex_r_system_timer_hnd(void) {
  /* Handle System Timer in a special way */
  TaskFunc p_timer_hnd =
    osEE_sys_timer_wrap[osEE_get_curr_core_id()].real_task_func;

  if (p_timer_hnd != NULL) {
    p_timer_hnd();
  } else {
    /* TODO: Handle System Timer Tick */
  }

  XTtcPs_ClearInterruptStatus(&osEE_x_timer,
    XTtcPs_GetInterruptStatus(&osEE_x_timer));
}

FUNC(void, OS_CODE)
  osEE_cortex_r_gicd_conf
(
  VAR(ISRSource,  AUTOMATIC)  source_id,
  VAR(TaskPrio,   AUTOMATIC)  virt_prio
)
{
  /* Configure the Priority for the interrupts. Leave the Trigger Type
     untouched, is the driver that shall select the right trigger */
  TaskPrio    isr2_old_prio;
  uint8_t     isr2_old_trigger_type;

  XScuGic_GetPriTrigTypeByDistAddr(XPAR_SCUGIC_0_DIST_BASEADDR, source_id,
    &isr2_old_prio, &isr2_old_trigger_type);
  /* Translate virtual to hardware priority */
  XScuGic_SetPriTrigTypeByDistAddr(XPAR_SCUGIC_0_DIST_BASEADDR, source_id,
    OSEE_ISR2_VIRT_TO_HW_PRIO(virt_prio), isr2_old_trigger_type);

  /* Enable the interrupt a GIC level. */
  XScuGic_EnableIntr(XPAR_SCUGIC_0_DIST_BASEADDR, source_id);
}

FUNC(StatusType, OS_CODE)
  osEE_hal_set_isr2_source
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb,
  VAR(ISRSource,  AUTOMATIC)                source_id
)
{
  StatusType  ev = E_OK;

  CoreIdType              const
    core_id = osEE_get_curr_core_id();
  OsEE_cortex_r_hnd_type  * const
    p_hnd = &osEE_cortex_r_int_vectors[core_id][source_id];

#if (defined(OSEE_TICK_RATE_HZ))
  if (source_id == XPAR_XTTCPS_0_INTR) {
    OsEE_TW * const p_tw = &osEE_sys_timer_wrap[core_id];
    if (p_tw->p_tdb == NULL) {
      /* It is a system timer handler: Wrap the TASK function Call */
      p_tw->p_tdb          = p_tdb;
      p_tw->real_task_func = p_tdb->task_func;

      p_tdb->task_func = osEE_cortex_r_system_timer_hnd;
    } else {
      ev = E_OS_STATE;
    }
  }
  if (ev == E_OK)
#endif /* OSEE_TICK_RATE_HZ */
  {
    p_tdb->hdb.isr2_src = source_id;
    p_hnd->cat          = OSEE_ISR_CAT_2;
    p_hnd->hnd.tid      = p_tdb->tid;

    osEE_cortex_r_gicd_conf(source_id, p_tdb->ready_prio);
  }

  return ev;
}
#else
/* TODO: */
#endif /* OSEE_API_DYNAMIC */

OsEE_bool osEE_cpu_startos(void)
{
  /* CPU StartOS Status return */
  OsEE_bool  cpu_startos_done = OSEE_TRUE;

#if (!defined(OSEE_API_DYNAMIC))
  /* GICD initialization */
  osEE_cortex_r_gicd_init();
#endif /* !OSEE_API_DYNAMIC */

  /* Sistem Timer configuration */
#if (defined(OSEE_TICK_RATE_HZ))
  OsEE_TW * const p_tw = &osEE_sys_timer_wrap[osEE_get_curr_core_id()];

  if (p_tw->p_tdb != NULL) {
    int i_status;

    XTtcPs_Config * const p_x_timer_conf =
      XTtcPs_LookupConfig(XPAR_XTTCPS_0_DEVICE_ID);

    i_status = XTtcPs_CfgInitialize(&osEE_x_timer, p_x_timer_conf,
      p_x_timer_conf->BaseAddress);

    if (i_status != XST_SUCCESS) {
      /* Maybe the Timer is already started.
         Try to stop it and reinizialize. */
      XTtcPs_Stop(&osEE_x_timer);

      i_status = XTtcPs_CfgInitialize(&osEE_x_timer, p_x_timer_conf,
        p_x_timer_conf->BaseAddress);

      if (i_status != XST_SUCCESS) {
        xil_printf("In %s: System Timer initialization failed...\r\n",
          __func__);
        /* Flag the initialization as failed. */
        cpu_startos_done = OSEE_FALSE;
      }
    } else {
      XInterval us_interval;
      uint8_t   uc_prescaler;

      XTtcPs_SetOptions(&osEE_x_timer, XTTCPS_OPTION_INTERVAL_MODE |
        XTTCPS_OPTION_WAVE_DISABLE);

      XTtcPs_CalcIntervalFromFreq(&osEE_x_timer, OSEE_TICK_RATE_HZ,
        &us_interval, &uc_prescaler);

      XTtcPs_SetInterval(&osEE_x_timer, us_interval);
        XTtcPs_SetPrescaler(&osEE_x_timer, uc_prescaler);

#if (!defined(OSEE_API_DYNAMIC))
      /* Configure Interrupt for the system Timer. GIC Side */
      osEE_cortex_r_gicd_conf(XPAR_XTTCPS_0_INTR, p_tw->p_tdb->ready_prio);
#endif /* OSEE_API_DYNAMIC */

      /* Enable the interrupt for the system Timer. Peripheral Side
         GIC side is handled. */
      XTtcPs_EnableInterrupts(&osEE_x_timer, XTTCPS_IXR_INTERVAL_MASK);
      XTtcPs_Start(&osEE_x_timer);
    }
  }
#endif /* OSEE_TICK_RATE_HZ */

  cpu_startos_done &= osEE_std_cpu_startos();

  return cpu_startos_done;
}

/* ERIKA's ISR2 Wrapper */
extern void osEE_cortex_r_irq_hnd(OsEE_ISR_CTX * p_isr_ctx) {
  /* ISR Context is unused */
  (void)p_isr_ctx;

  OsEE_reg    irq_id_full;
  OsEE_reg    irq_id;

  /*
   * Read the int_ack register to identify the highest priority interrupt ID
   * and make sure it is valid. Reading Int_Ack will clear the interrupt
   * in the GIC.
   */
  /* XSCUGIC_ACK_INTID_MASK  0x000003FFU < Interrupt ID */
  /* XSCUGIC_CPUID_MASK      0x00000C00U < CPU ID */
  irq_id_full = XScuGic_CPUReadReg(&osEE_x_gic, XSCUGIC_INT_ACK_OFFSET);
  irq_id      = irq_id_full & XSCUGIC_ACK_INTID_MASK;

  if (irq_id < XSCUGIC_MAX_NUM_INTR_INPUTS) {
    CoreIdType const core_id = osEE_get_curr_core_id();
    OsEE_cortex_r_hnd_type OSEE_CONST * const p_hnd =
      &osEE_cortex_r_int_vectors[core_id][irq_id];

    if (p_hnd->cat == OSEE_ISR_CAT_2) {
      TaskType const tid = p_hnd->hnd.tid;
      if (tid != INVALID_TASK) {
        osEE_activate_isr2(tid);
      }
    } else {
      void (* const p_hnd_func) (void) = p_hnd->hnd.p_hnd_func;
      if (p_hnd_func != NULL) {
        p_hnd_func();
      }
    }
  }
}

FUNC(void, OS_CODE)
  osEE_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_from,
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  /* Interrupt Controller Acknowledgement */
  TaskPrio const
    irq_id_full = p_from->hdb.isr2_src | (osEE_get_curr_core_id() << 8U);

  /*
   * Write to the EOI register to Ackownoled the GIC. This should handle IPL
   * automatically.
   */
  XScuGic_CPUWriteReg(&osEE_x_gic, XSCUGIC_EOI_OFFSET, irq_id_full);

  osEE_change_context_from_task_end(p_from, p_to);
}
