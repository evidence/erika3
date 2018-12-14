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

/** \file   ee_x86_64_tsc.c
 *  \brief  Timestamp Counter
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#include "ee_internal.h"
#include "ee_x86_64_tsc.h"

/* Defines whether TSC is supported */
static uint64_t tsc_supported = 0;

static uint64_t tsc_freq;
static uint64_t tsc_overflow;
static uint64_t tsc_overflows, tsc_last;

void osEE_x86_64_tsc_init(uint64_t tsc_freq_hz)
{
	tsc_supported = (tsc_freq_hz ? osEE_x86_64_tsc() : 0);
	if (tsc_supported) {
		tsc_freq = tsc_freq_hz;
		tsc_overflow = (0x100000000L * OSEE_GIGA) / tsc_freq;
	}
}

uint64_t osEE_x86_64_tsc_read(void)
{
	uint64_t tmr = 0;

	if (tsc_supported) {
		tmr = ((osEE_x86_64_rdtsc() & 0xffffffffLL) * OSEE_GIGA)
		      / tsc_freq;
		if (tmr < tsc_last)
			tsc_overflows += tsc_overflow;
		tsc_last = tmr;
		tmr += tsc_overflows;
	}

	return tmr;
}
