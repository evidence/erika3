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

/** \file   ee_x86_64_x2apic.c
 *  \brief  Interrupt management and timer support based on x86_64 X2APIC.
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#include "ee_internal.h"
#include "ee_x86_64_tsc.h"

#define OSEE_X86_64_X2APIC_ID          (0x802U)
#define OSEE_X86_64_X2APIC_EOI         (0x80BU)
#define OSEE_X86_64_X2APIC_SPIV        (0x80FU)
#define OSEE_X86_64_X2APIC_ICR         (0x830U)
#define OSEE_X86_64_X2APIC_LVTT        (0x832U)
#define OSEE_X86_64_X2APIC_TMICT       (0x838U)

#define OSEE_X86_64_APIC_LVL_ASSERT    (1 << 14)
#define OSEE_X86_64_APIC_EOI_ACK       (0)
#define OSEE_X86_64_APIC_SPURIOUS_VEC  (0x1FF)

#define OSEE_X86_64_IA32_TSC_DEADLINE  (0x6E0)
#define OSEE_X86_64_LVTT_TSC_DEADLINE  (1 << 18)

/* Define whether APIC supports TSC deadline mode */
static uint64_t tsc_deadline_supported;

/*==============================================================================
                            Core IDs Utilities
 =============================================================================*/
OsEE_core_id osEE_x86_64_get_local_apic_id(void) {
    return (OsEE_core_id)osEE_x86_64_read_msr(OSEE_X86_64_X2APIC_ID);
}

/*==============================================================================
                            Interrupt management
 =============================================================================*/
void osEE_x86_64_int_controller_init(void)
{
    /* Set spurious interrupt vector 255 */
    osEE_x86_64_write_msr(OSEE_X86_64_X2APIC_SPIV, OSEE_X86_64_APIC_SPURIOUS_VEC);

    /* Check whether APIC supports one-shot operation using a TSC deadline value */
    tsc_deadline_supported = osEE_x86_64_apic_tsc_deadline();
}

void osEE_x86_64_int_send_ipi(unsigned int cpu_id, unsigned int vector)
{
    /* Fig. 10-28 Intel vol 3, set parameters + assert level */
    osEE_x86_64_write_msr(OSEE_X86_64_X2APIC_ICR,
                          ((uint64_t)cpu_id << 32) | OSEE_X86_64_APIC_LVL_ASSERT | vector);
}

void osEE_x86_64_int_send_eoi(void)
{
    osEE_x86_64_write_msr(OSEE_X86_64_X2APIC_EOI, OSEE_X86_64_APIC_EOI_ACK);
}

/*==============================================================================
                                 Timer Support
 =============================================================================*/
static uint64_t x86_64_timer_tick_freq_hz = 0;

void osEE_x86_64_set_timer_tick_freq(uint64_t tick_freq_hz)
{
    x86_64_timer_tick_freq_hz = tick_freq_hz;
}

void osEE_x86_64_oneshot_timer_init(unsigned int vector)
{
    if (tsc_deadline_supported) {
	/* Use TSC Deadline mode */
        osEE_x86_64_write_msr(OSEE_X86_64_X2APIC_LVTT,
			      (vector | OSEE_X86_64_LVTT_TSC_DEADLINE));
    } else {
	/* Use One-shot mode */
        osEE_x86_64_write_msr(OSEE_X86_64_X2APIC_LVTT, vector);
    }

    __asm__ volatile("mfence" : : : "memory");
}

void osEE_x86_64_timer_set_deadline(uint64_t timeout_ns)
{
    uint64_t ticks = timeout_ns * x86_64_timer_tick_freq_hz / OSEE_GIGA;
    uint64_t now;

    if (tsc_deadline_supported) {
	/* Read from the TSC register */
        now = osEE_x86_64_rdtsc();
	/* Deadline: TSC + ticks */
        osEE_x86_64_write_msr(OSEE_X86_64_IA32_TSC_DEADLINE, now + ticks);
    } else {
	/* Deadline relative: ticks */
        osEE_x86_64_write_msr(OSEE_X86_64_X2APIC_TMICT, ticks);
    }
}
