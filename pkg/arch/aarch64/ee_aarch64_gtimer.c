/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_aarch64_gtimer.c
 *  \brief  System timer implementation based on AArch64 GTimer.
 *
 *  \author  Errico Gudiieri
 *  \date    2018
 */

#include "ee_internal.h"

/* This file is needed only if System Timer is defined with a device */
#if (defined(OSEE_SYSTEM_TIMER_DEVICE))
/****************************************************************
                    System Timer Support
 ****************************************************************/

#if (OSEE_SYSTEM_TIMER_DEVICE != OSEE_AARCH64_GTIMER)
#error Unsupported Device as System Timer!
#endif /* OSEE_SYSTEM_TIMER_DEVICE != OSEE_AARCH64_GTIMER */

static OsEE_reg osEE_system_timer_expected_ticks;

void osEE_aarch64_system_timer_init(void) {
  osEE_system_timer_expected_ticks = osEE_aarch64_gtimer_get_ticks() +
    OSEE_NANO_TO_TICKS(OSTICKDURATION, osEE_aarch64_gtimer_get_freq());

  osEE_aarch64_gtimer_start(osEE_system_timer_expected_ticks,
    OSEE_AARCH64_GTIMER_UPPERCOUNT);

  return;
}

void osEE_aarch64_system_timer_handler(void)
{
  OsEE_CDB * const p_cdb = osEE_get_curr_core();
  osEE_counter_increment(p_cdb->p_sys_counter_db);

  osEE_system_timer_expected_ticks +=
    OSEE_NANO_TO_TICKS(OSTICKDURATION, osEE_aarch64_gtimer_get_freq());

  osEE_aarch64_gtimer_start(osEE_system_timer_expected_ticks,
    OSEE_AARCH64_GTIMER_UPPERCOUNT);
  return;
}

#endif /* OSEE_SYSTEM_TIMER_DEVICE */