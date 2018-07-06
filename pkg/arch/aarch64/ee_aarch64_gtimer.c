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
  OsEE_reg const gtimer_freq = osEE_aarch64_gtimer_get_freq();
  osEE_system_timer_expected_ticks = osEE_aarch64_gtimer_get_ticks() +
    OSEE_NANO_TO_TICKS(OSTICKDURATION, gtimer_freq);

  osEE_aarch64_gtimer_start(osEE_system_timer_expected_ticks,
    OSEE_AARCH64_GTIMER_UPPERCOUNT);

  return;
}

#if (!defined(OSEE_AARCH64_GTIMER_GUARD))
/* TODO: Tie OSEE_AARCH64_GTIMER_GUARD to ratio cpu_freq/gtimer_freq */
#define OSEE_AARCH64_GTIMER_GUARD (10U)
#endif /* OSEE_AARCH64_GTIMER_GUARD */

void osEE_aarch64_system_timer_handler(void)
{
  OsEE_reg   gtimer_ticks;
  OsEE_reg   gtimer_latency;
  OsEE_reg   const gtimer_freq  = osEE_aarch64_gtimer_get_freq();
  OsEE_reg   const gitmer_delta =
    OSEE_NANO_TO_TICKS(OSTICKDURATION, gtimer_freq);

  OsEE_CDB * const p_cdb = osEE_get_curr_core();

  osEE_counter_increment(p_cdb->p_sys_counter_db);

  gtimer_ticks = osEE_aarch64_gtimer_get_ticks();
  gtimer_latency = (gtimer_ticks - osEE_system_timer_expected_ticks);

  if (gtimer_latency < (gitmer_delta - OSEE_AARCH64_GTIMER_GUARD)) { 
    osEE_system_timer_expected_ticks += gitmer_delta;
  } else {
    osEE_system_timer_expected_ticks  = gtimer_ticks + gitmer_delta
      - OSEE_AARCH64_GTIMER_GUARD;
  }

  osEE_aarch64_gtimer_start(osEE_system_timer_expected_ticks,
    OSEE_AARCH64_GTIMER_UPPERCOUNT);

  return;
}

#endif /* OSEE_SYSTEM_TIMER_DEVICE */
