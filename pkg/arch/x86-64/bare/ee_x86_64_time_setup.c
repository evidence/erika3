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
 *  \brief  Calibrate timer tick frequencies using PIT.
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#include "ee_internal.h"
#include "ee_ioport.h"
#include "ee_x86_64_tsc_internal.h"

#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_APIC))
#include "ee_x86_64_apic_internal.h"
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_APIC */
#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC))
#include "ee_x86_64_x2apic_internal.h"
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC */

#define EE_X86_64_TIME_SETUP_DEBUG
#ifdef EE_X86_64_TIME_SETUP_DEBUG
#include "ee_print.h"
#endif

#if (!defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_APIC) \
     && !defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC))
#error Unsupported Device as Interrupt controller!
#endif

#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_APIC))
#define OSEE_APIC_WRITE(reg,value)    lapic_write_reg(reg, value)
#define OSEE_APIC_READ(reg)           lapic_read_reg(reg)
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_APIC */

#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC))
#define OSEE_APIC_WRITE(reg,value)    osEE_x86_64_write_msr(X2APIC_CONVERT(reg), value)
#define OSEE_APIC_READ(reg)           osEE_x86_64_read_msr(X2APIC_CONVERT(reg))
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC */

/* PIT calibration : sample time = 10ms */
static uint16_t pit_sample_time = 0x2E9B; /* 1193180/(1000/10)Hz=11931=0x2e9b */
static int norm_factor_sample_time = 100; /* 100 * 10ms = 1s */

/*==============================================================================
                  Timer frequency (hz) Computation
 =============================================================================*/
void osEE_x86_64_calibrate_platform_tick_freq(void)
{
	uint64_t init_tsc, last_tsc, tsc_tick_freq_hz;
	uint64_t last_apic, apic_tick_freq_hz;
#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC))
	uint64_t x2apic_tick_freq_hz;
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC */

	/* Initialize APIC timer (one-shot mode, divide value = 16)) */
	OSEE_APIC_WRITE(OSEE_X86_64_APIC_LVT_TIMER, 0x10000);
	OSEE_APIC_WRITE(OSEE_X86_64_APIC_TIMER_DIV,
			osEE_x86_64_lapic_timer_div2reg(APIC_TIMER_DIVIDER));

	/* Set the Gate high, disable speaker */
	outb(0x61, (inb(0x61) & ~0x02) | 0x01);
	/* Setup channel 2, mode 0, binary count */
	outb(0x43, 0xB0);

	/* INIT PIT to count the sample time */
	outb(0x42, pit_sample_time & 0xFF);	/* LSB */
	io_wait();		/* short delay */
	outb(0x42, (pit_sample_time >> 8) & 0xFF);	/* MSB */

	/* INIT TSC: read the TSC counter */
	init_tsc = (uint64_t) osEE_x86_64_rdtsc();
	/* INIT APIC timer: start counting from MAX value) */
	OSEE_APIC_WRITE(OSEE_X86_64_APIC_TIMER_INIT_CNT, 0xFFFFFFFF);

	/* Wait until PIT counter reaches zero */
	while ((inb(0x61) & 0x20) == 0);
	/* Read the current values */
	last_tsc = (uint64_t) osEE_x86_64_rdtsc();
	last_apic = (uint64_t) OSEE_APIC_READ(OSEE_X86_64_APIC_TIMER_CURR_CNT);

	/* TSC Calibration.
	 * Read the current TSC. Take into account the initial TSC value
	 * and the sample time.
	 */
	tsc_tick_freq_hz = (last_tsc - init_tsc) * norm_factor_sample_time;
	osEE_x86_64_tsc_init(tsc_tick_freq_hz);
#ifdef EE_X86_64_TIME_SETUP_DEBUG
	OSEE_PRINT("Calibrated TSC Timer frequency: %lu.%03lu kHz (0x%lx)\n",
		   tsc_tick_freq_hz / OSEE_KILO,
		   tsc_tick_freq_hz % OSEE_KILO,
		   tsc_tick_freq_hz);
#endif /* EE_X86_64_TIME_SETUP_DEBUG */

	/* APIC Calibration.
	 * Read the current timer value (counted down from -1).
	 * Take into account OSEE_X86_64_APIC_TIMER_DIV (16) and
	 * the sample time.
	 */
	apic_tick_freq_hz = (0xFFFFFFFF - last_apic)
			  * APIC_TIMER_DIVIDER * norm_factor_sample_time;

#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_APIC))
	osEE_x86_64_set_apic_timer_tick_freq(apic_tick_freq_hz);
#ifdef EE_X86_64_TIME_SETUP_DEBUG
	OSEE_PRINT("Calibrated APIC Timer frequency: %lu.%03lu kHz (0x%lx)\n",
		   apic_tick_freq_hz / OSEE_KILO,
		   apic_tick_freq_hz % OSEE_KILO,
		   apic_tick_freq_hz);
#endif /* EE_X86_64_TIME_SETUP_DEBUG */
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_APIC */

#if (defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC))
	if(x86_64_x2apic_tsc_deadline)
		x2apic_tick_freq_hz = tsc_tick_freq_hz;
	else
		x2apic_tick_freq_hz = apic_tick_freq_hz;
	osEE_x86_64_set_apic_timer_tick_freq(x2apic_tick_freq_hz);
#ifdef EE_X86_64_TIME_SETUP_DEBUG
	OSEE_PRINT("Calibrated X2APIC Timer frequency: %lu.%03lu kHz (0x%lx)\n",
		   x2apic_tick_freq_hz / OSEE_KILO,
		   x2apic_tick_freq_hz % OSEE_KILO,
		   x2apic_tick_freq_hz);
#endif /* EE_X86_64_TIME_SETUP_DEBUG */
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC */
}
