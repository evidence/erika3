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

/** \file   ee_x86_64_timer_setup.c
 *  \brief  Calibrate timer tickis using values contained in
 *  Jailhouse communication region.
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#include "ee_internal.h"
#include <inmate.h>
#include "ee_x86_64_tsc_internal.h"
#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC))
#include "ee_x86_64_x2apic_internal.h"
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC */
#ifdef EE_X86_64_TIME_SETUP_DEBUG
#include "ee_print.h"
#endif

#if (!defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC))
#error Unsupported Device as Interrupt controller!
#endif

#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC_NO_TSC_DEADLINE))
/* Note: comm_region->apic_khz is 0 (error due to Jailhouse common region?) */
#error Not supported NO_TSC_DEADLINE X2APIC mode for Jailhouse platform
#endif

/*==============================================================================
                  Timer frequency (hz) Computation
 =============================================================================*/
extern uint64_t x86_64_x2apic_timer_tick_freq_hz;

void osEE_x86_64_calibrate_platform_tick_freq(void)
{
	uint64_t x2apic_tick_freq_hz;
	uint64_t tsc_tick_freq_hz;

	/* X2APIC Calibration.*/
	if(x86_64_x2apic_tsc_deadline) {
		x2apic_tick_freq_hz = comm_region->tsc_khz * 1000L;
	} else {
		x2apic_tick_freq_hz = comm_region->apic_khz * 1000L;
	}

	osEE_x86_64_set_apic_timer_tick_freq(x2apic_tick_freq_hz);
#ifdef EE_X86_64_TIME_SETUP_DEBUG
	OSEE_PRINT("Calibrated X2APIC Timer frequency: %lu.%03lu kHz (0x%lx)\n",
		   x2apic_tick_freq_hz / OSEE_KILO,
		   x2apic_tick_freq_hz % OSEE_KILO,
		   x2apic_tick_freq_hz);
#endif

	/* TSC Calibration */
	if(osEE_x86_64_tsc()) {
		tsc_tick_freq_hz = comm_region->tsc_khz * 1000L;
		osEE_x86_64_tsc_init(tsc_tick_freq_hz);
		/* Call Jailhouse tsc_init to allow 'inmate' tsc_read() */
		tsc_init();
#ifdef EE_X86_64_TIME_SETUP_DEBUG
		OSEE_PRINT("Calibrated TSC Timer frequency: %lu.%03lu kHz (0x%lx)\n",
			   tsc_tick_freq_hz / OSEE_KILO,
			   tsc_tick_freq_hz % OSEE_KILO,
			   tsc_tick_freq_hz);
#endif
	}
}
