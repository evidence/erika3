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

/** \file   ee_ti_awr16xx_system_timer.c
 *  \brief  Implementation of system timer with RTI peripheral
 *
 *  \author Errico Guidieri
 *  \date   2019
 */

#include "ee_internal.h"
#include "ee_ti_awr16xx_rti.h"
#include <ti/drivers/osal/DebugP.h>

/* RTI Device Regs */
typedef struct {
  OsEE_reg RTIGCTRL;
  OsEE_reg RTITBCTRL;
  OsEE_reg RTICAPCTRL;
  OsEE_reg RTICOMPCTRL;
  OsEE_reg RTIFRC0;
  OsEE_reg RTIUC0;
  OsEE_reg RTICPUC0;
  OsEE_reg reserved0;
  OsEE_reg RTICAFRC0;
  OsEE_reg RTICAUC0;
  OsEE_reg reserved1;
  OsEE_reg reserved2;
  OsEE_reg RTIFRC1;
  OsEE_reg RTIUC1;
  OsEE_reg RTICPUC1;
  OsEE_reg reserved3;
  OsEE_reg RTICAFRC1;
  OsEE_reg RTICAUC1;
  OsEE_reg reserved4;
  OsEE_reg reserved5;
  OsEE_reg RTICOMP0;
  OsEE_reg RTIUDCP0;
  OsEE_reg RTICOMP1;
  OsEE_reg RTIUDCP1;
  OsEE_reg RTICOMP2;
  OsEE_reg RTIUDCP2;
  OsEE_reg RTICOMP3;
  OsEE_reg RTIUDCP3;
  OsEE_reg RTITBLCOMP;
  OsEE_reg RTITBLHCOMP;
  OsEE_reg reserved6;
  OsEE_reg reserved7;
  OsEE_reg RTISETINTENA;
  OsEE_reg RTICLEARINTENA;
  OsEE_reg RTIINTFLAG;
  OsEE_reg reserverd8;
  OsEE_reg RTIDWDCTRL;
  OsEE_reg RTIDWDPRLD;
  OsEE_reg RTIWDSTATUS;
  OsEE_reg RTIWDKEY;
  OsEE_reg RTIDWDCNTR;
  OsEE_reg RTIWWDRXNCTRL;
  OsEE_reg RTIWWDSIZECTRL;
  OsEE_reg RTIINTCLRENABLE;
  OsEE_reg RTICOMP0CLR;
  OsEE_reg RTICOMP1CLR;
  OsEE_reg RTICOMP2CLR;
  OsEE_reg RTICOMP3CLR;
} OsEE_ti_rti_regs;

#if (!defined(OSEE_TI_RTI_MODULE_BASE_ADDRESS))
#define OSEE_TI_RTI_MODULE_BASE_ADDRESS (0xFFFFFC00U)
#endif /* !OSEE_TI_RTI_MODULE_BASE_ADDRESS */

#define OSEE_TI_RTI_P\
  ((OsEE_ti_rti_regs volatile *)OSEE_TI_RTI_MODULE_BASE_ADDRESS)

/* Timer Global Control Register Description
 * Bit#         Name            Value
 * 31-20        RESERVED
 * 19-16        NTUSEL          0h NTU0
 *                              5h NTU1
 *                              Ah NTU2
 *                              Fh NTU3
 * 15           COS             0h Counters stopped during emulation halt
 *                              1h Counters running during emulation halt
 * 14-2         RESERVED
 * 1            CNT1EN          0h Counter block 1 is stopped (disabled)
 *                              1h Counter block 1 is running (enabled)
 * 0            CNT0EN          0h Counter block 0 is stopped (disabled)
 *                              1h Counter block 0 is running (enabled)
 */
#define OSEE_TI_RTI_GCTRL_CNT0EN      (0x1U)
#define OSEE_TI_RTI_GCTRL_CNT1EN      (0x2U)
#define OSEE_TI_RTI_GCTRL_COS         (0x8000U)

#if (!defined(OSEE_HAS_SYSTEM_TIMER))
#define OSEE_TI_RTI_INIT_STORAGE
#else
#define OSEE_TI_RTI_INIT_STORAGE static
#endif /* !OSEE_HAS_SYSTEM_TIMER */

OSEE_TI_RTI_INIT_STORAGE void osEE_ti_awr16xx_rti_init(void)
{
  /* Disable both counters in initialization */
  OSEE_TI_RTI_P->RTIGCTRL &=
    (~(OSEE_TI_RTI_GCTRL_CNT0EN | OSEE_TI_RTI_GCTRL_CNT1EN));

  /* Reset all the interrupts pending (bits are write 1 to clear in
     privileged mode [w1cp]):
     [18] OVL1INT Free running counter 1 overflow interrupt flag.
     [16] OVL0INT Free running counter 0 overflow interrupt flag.
     [17] Timebase interrupt flag. This flag is set when the TBEXT bit is
          cleared by detection of a missing external clock edge.
          (not by software)
     ...
     [3]  INT3 Interrupt flag 3. These bits determine if an interrupt due to a
          Compare 3 match is pending
     [2]  INT2 Interrupt flag 2. These bits determine if an interrupt due to a
          Compare 2 match is pending
     [1]  INT1 Interrupt flag 1. These bits determine if an interrupt due to a
          Compare 1 match is pending
     [0]  INT0 Interrupt flag 0. These bits determine if an interrupt due to a
          Compare 0 match is pending
  */
  OSEE_TI_RTI_P->RTIINTFLAG = 0x0007000FU;

  /* Assure the the increment for free running counter 0 is given by internal
     prescaler => bit TBEXT[0] = 0 and INC[1] = 0, all other bits are reserved.
     So assign 0 is what we want */
  OSEE_TI_RTI_P->RTITBCTRL = 0U;

  /* Reset All Counters */
  OSEE_TI_RTI_P->RTIFRC0  = 0U;
  OSEE_TI_RTI_P->RTIUC0   = 0U;
  OSEE_TI_RTI_P->RTIFRC1  = 0U;
  OSEE_TI_RTI_P->RTIUC1   = 0U;

  /* Set the minimum possible prescaler... */
  OSEE_TI_RTI_P->RTICPUC0 = 1U;
  OSEE_TI_RTI_P->RTICPUC1 = 1U;

  /* Arbitrarily assign CMP0 and CMP1 to FRC0 and CMP2 and CMP3 to FRC1.
     The selection bit is the first of each byte, with CMP3 assigned to the
     MSB and other descending order */
  OSEE_TI_RTI_P->RTICOMPCTRL = 0x010100U;

#if (!defined(OSEE_HAS_SYSTEM_TIMER))
  /* Re-enable both counters */
  OSEE_TI_RTI_P->RTIGCTRL |= (
    OSEE_TI_RTI_GCTRL_CNT0EN | OSEE_TI_RTI_GCTRL_CNT1EN
#if (!defined(OSEE_DEBUG))
  /* When we are in debug block the counters on breakpoints */
      | OSEE_TI_RTI_GCTRL_COS
#endif /* !OSEE_DEBUG */
  );
#endif /* !OSEE_HAS_SYSTEM_TIMER */
}

OsEE_reg osEE_ti_awr16xx_get_frc(enum ti_rti_frc frc)
{
  OsEE_reg ret_value;
  switch (frc) {
    case TI_RTI_FRC_1:
      ret_value = OSEE_TI_RTI_P->RTIFRC1;
      break;
    case TI_RTI_FRC_0:
    default:
      ret_value = OSEE_TI_RTI_P->RTIFRC0;
      break;
  }
  return ret_value;
}

#if (defined(OSEE_HAS_SYSTEM_TIMER))
#if (!defined(OSEE_SYSTEM_TIMER_CORE0_DEVICE))
#define OSEE_SYSTEM_TIMER_CORE0_DEVICE OSEE_CORTEX_R_DEVICE_RTIC3
#else
#if (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_CORTEX_R_DEVICE_RTIC0) &&\
    (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_CORTEX_R_DEVICE_RTIC1) &&\
    (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_CORTEX_R_DEVICE_RTIC2) &&\
    (OSEE_SYSTEM_TIMER_CORE0_DEVICE != OSEE_CORTEX_R_DEVICE_RTIC3)
#error Unknown system timer device
#endif /* Device Check */
#endif /* !OSEE_SYSTEM_TIMER_CORE0_DEVICE */

void osEE_cortex_r_initialize_system_timer(OsEE_TDB * p_tdb) {
  /* Evaluate period_tick halving Core Frequency */
  const TickType period_tick =
    OSEE_MICRO_TO_TICKS((OSTICKDURATION/1000U), (OSEE_CPU_CLOCK/2U));

  /* Init RTI */
  osEE_ti_awr16xx_rti_init();

  /* Set the right compare, update registers and enable the right interrupt */
  /* RTISETINTENA has bits corresponding to RTIINTFLAG */
  switch (p_tdb->hdb.isr2_src) {
    case OSEE_CORTEX_R_DEVICE_RTIC0:
      OSEE_TI_RTI_P->RTICOMP0     = period_tick;
      OSEE_TI_RTI_P->RTIUDCP0     = period_tick;
      OSEE_TI_RTI_P->RTISETINTENA = 0x00000001U;
      break;
    case OSEE_CORTEX_R_DEVICE_RTIC1:
      OSEE_TI_RTI_P->RTICOMP1     = period_tick;
      OSEE_TI_RTI_P->RTIUDCP1     = period_tick;
      OSEE_TI_RTI_P->RTISETINTENA = 0x00000002U;
      break;
    case OSEE_CORTEX_R_DEVICE_RTIC2:
      OSEE_TI_RTI_P->RTICOMP2     = period_tick;
      OSEE_TI_RTI_P->RTIUDCP2     = period_tick;
      OSEE_TI_RTI_P->RTISETINTENA = 0x00000004U;
      break;
    case OSEE_CORTEX_R_DEVICE_RTIC3:
      OSEE_TI_RTI_P->RTICOMP3     = period_tick;
      OSEE_TI_RTI_P->RTIUDCP3     = period_tick;
      OSEE_TI_RTI_P->RTISETINTENA = 0x00000008U;
      break;
    default:
      /* Assert False */
      DebugP_assert(0);
      break;
  }

  /* Re-enable both counters */
  OSEE_TI_RTI_P->RTIGCTRL |= (
    OSEE_TI_RTI_GCTRL_CNT0EN | OSEE_TI_RTI_GCTRL_CNT1EN
#if (!defined(OSEE_DEBUG))
  /* When we are in debug block the counters on breakpoints */
      | OSEE_TI_RTI_GCTRL_COS
#endif /* !OSEE_DEBUG */
  );
}

#if (!defined(OSEE_TI_RTI_COMP_INT_OFFSET))
#define OSEE_TI_RTI_COMP_INT_OFFSET (2U)
#endif /* !OSEE_TI_RTI_COMP_INT_OFFSET */

void osEE_cortex_r_system_timer_handler(void) {
  OsEE_CDB * const p_cdb = osEE_get_curr_core();
  osEE_counter_increment(p_cdb->p_sys_counter_db);
  /* Acknowledge peripheral flag: I don't known if needed but it should not
     hurt */
  OSEE_TI_RTI_P->RTIINTFLAG = (OsEE_reg)1U <<
    (p_cdb->p_ccb->p_curr->hdb.isr2_src - OSEE_TI_RTI_COMP_INT_OFFSET);
}

#endif /* OSEE_HAS_SYSTEM_TIMER */

