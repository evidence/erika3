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
#include "ee_utils.h"
#include "ee_x86_64_x2apic_internal.h"
#include "ee_x86_64_tsc.h"

#ifdef OSEE_X86_64_X2APIC_DEBUG
#include "ee_print.h"
#endif /* OSEE_X86_64_X2APIC_DEBUG */

#if (!defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC_NO_TSC_DEADLINE) \
     && !defined(OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC_TSC_DEADLINE))
#error No definition of X2APIC operating mode (e.g., TSC_DEADLINE)!
#endif

/* Local apic id */
static OsEE_core_id local_apic_id;
/* Define whether APIC supports TSC deadline mode */
uint64_t x86_64_x2apic_tsc_deadline;
/* X2APIC Timer tick frequency (initialization function is PLATFORM-DEPENDENT).
 * In case of X2APIC_NO_TSC_DEADLINE, the timer frequency is the APIC freq.
 * In case of X2APIC_TSC_DEADLINE, the timer frequency is the TSC freq.
 * */
uint64_t x86_64_timer_tick_freq_hz;

/*==============================================================================
                            Core IDs Utilities
 =============================================================================*/
OsEE_core_id osEE_x86_64_get_local_apic_id(void) {
    /* Local apic id set in osEE_x86_64_int_controller_init
     * TODO: check in case of multi-core */
    return local_apic_id;
}

/*==============================================================================
                        Interrupt controller init
 =============================================================================*/
static int osEE_x86_64_x2apic_detect(void)
{
    uint32_t ecx, edx;

    /* CPUID with EAX=1 */
    __asm__ volatile("cpuid" : "=c" (ecx), "=d" (edx) : "a" (1) : "memory");

    /* X2APIC (21th bit of ECX) */
    return OSEE_B_GET(ecx, 1, 21);
}


int osEE_x86_64_set_x2apic_mode(void)
{
    int result = 0;

#ifdef OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC_NO_TSC_DEADLINE
    x86_64_x2apic_tsc_deadline = 0;
#ifdef OSEE_X86_64_X2APIC_DEBUG
    OSEE_PRINT("X2APIC mode: no tsc_deadline\n");
#endif /* OSEE_X86_64_X2APIC_DEBUG */
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC_NO_TSC_DEADLINE */

#ifdef OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC_TSC_DEADLINE
    x86_64_x2apic_tsc_deadline = osEE_x86_64_apic_tsc_deadline();
    if (!x86_64_x2apic_tsc_deadline) {
        result = -1;
#ifdef OSEE_X86_64_X2APIC_DEBUG
        OSEE_PRINT("ERROR: X2APIC tsc_deadline mode not supported!");
    } else {
        OSEE_PRINT("X2APIC mode: tsc_deadline\n");
#endif /* OSEE_X86_64_X2APIC_DEBUG */
    }
#endif /* OSEE_PLATFORM_X86_64_INT_CONTROLLER_X2APIC_NO_TSC_DEADLINE */

    return result;
}

int osEE_x86_64_int_controller_init(void)
{
    uint32_t reg_value;
    uint32_t val;

    if(!osEE_x86_64_x2apic_detect()) {
#ifdef OSEE_X86_64_X2APIC_DEBUG
	    OSEE_PRINT("X2APIC is not supported\n");
#endif /* OSEE_X86_64_X2APIC_DEBUG */
	    return -1;
    }

    /* Enable x2apic: EN = 1, EXTD = 1 in IA32_APIC_BASE */
    reg_value = osEE_x86_64_read_msr(MSR_IA32_APIC_BASE);
    if(!OSEE_B_GET(reg_value, 1 ,10)) {
#ifdef OSEE_X86_64_X2APIC_DEBUG
        OSEE_PRINT("Enabling X2APIC\n");
#endif
	reg_value = OSEE_B_SET(reg_value, 1U, 11U, 1U); /* enable bit EN - bit 11 */
        reg_value = OSEE_B_SET(reg_value, 1U, 10U, 1U); /* extended mode bit EXTD - bit 10 */
        osEE_x86_64_write_msr(MSR_IA32_APIC_BASE, reg_value);
    }

    /* Set X2apic operating mode */
    if(osEE_x86_64_set_x2apic_mode()) {
#ifdef OSEE_X86_64_X2APIC_DEBUG
	    OSEE_PRINT("X2APIC mode is not supported\n");
#endif /* OSEE_X86_64_X2APIC_DEBUG */
	    return -1;
    }


    /* Set the local apic id */
    local_apic_id = (OsEE_core_id)osEE_x86_64_read_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_ID));

    /* Logical Destrination Register (LDR) is a read-only register.
     * This 32-bit value is referred to as "logical x2APIC ID”.
     * The Destination Format Registeri (DFR) is eliminated in X2APIC Mode
     * since the Flat logical mode is not supported in such mode.*/

    /* Task Priority Register: allows all interrupts (bit 4-7) */
    val = osEE_x86_64_read_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_TPR));
    val &= ~OSEE_X86_64_APIC_TPR_MASK;
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_TPR), val);

    /* Spurious Interrupt Register
     * Associate the source id (OSEE_X86_64_APIC_SPURIOUS_VECTOR) for the spurious interrupts
     */
    val = osEE_x86_64_read_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_SPIVR));
    val &= 0xFFFFFF00U;
    val |= OSEE_X86_64_APIC_SPURIOUS_VECTOR;   /* Spurious vector */
    val |= 0x100;                              /* Bit 9: apic enabled/disabled */
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_SPIVR), val);

    /* Timer Local Vector Table: mode=fixed, int.disabled */
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_LVT_TIMER),
                          OSEE_X86_64_APIC_LVT_MT_FIXED
                          | OSEE_X86_64_APIC_LVT_MASKED);
    /* Thermal Local Vector: mode=fixed, int.disable*/
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_LVT_THERMAL),
                          OSEE_X86_64_APIC_LVT_MT_FIXED
                          | OSEE_X86_64_APIC_LVT_MASKED
                          | OSEE_X86_64_APIC_THERMAL_VECTOR);
    /* Performance Counter Local Vector Table: mode=ignore vector, int.disabled */
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_LVT_PERF),
                          OSEE_X86_64_APIC_LVT_MT_NMI
                          | OSEE_X86_64_APIC_LVT_MASKED);
    /* Interrupt 0 Counter Local Vector Table: mode=external interrupt, int.disabled*/
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_LVT_INT0),
                          OSEE_X86_64_APIC_LVT_MT_EXTINT
                          | OSEE_X86_64_APIC_LVT_MASKED);
    /* Interrupt 1 Counter Local Vector Table: mode=external interrupt, int.disabled */
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_LVT_INT1),
                          OSEE_X86_64_APIC_LVT_MT_NMI
                          | OSEE_X86_64_APIC_LVT_MASKED);
    /* Set Error Vector Table: mode=fixed, int.disabled */
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_LVT_ERR),
                          OSEE_X86_64_APIC_LVT_MT_FIXED
                         | OSEE_X86_64_APIC_LVT_MASKED
                         | OSEE_X86_64_APIC_ERROR_VECTOR);

    /* Spec says to clear after enabling OSEE_X86_64_APIC_LVT_ERR */
    osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_ESR), 0);


    return 0;
}

/*==============================================================================
                            Interrupt management
 =============================================================================*/
void osEE_x86_64_int_send_ipi(unsigned int cpu_id, unsigned int vector)
{
	uint64_t val;

	val = ((uint64_t)cpu_id << 32) | OSEE_X86_64_APIC_LVL_ASSERT | vector;
	/* Fig. 10-28 Intel vol 3, set parameters + assert level */
	osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_ICR), val);
}

void osEE_x86_64_int_send_eoi(void)
{
	osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_EOI),
			      OSEE_X86_64_APIC_EOI_ACK);
}

/*==============================================================================
                                 Timer Support
 =============================================================================*/
void osEE_x86_64_oneshot_timer_init(unsigned int vector)
{
	uint64_t lvtt_vector;

	/* Use TSC Deadline mode if supported*/
	lvtt_vector = (x86_64_x2apic_tsc_deadline) ?
		      (vector | OSEE_X86_64_LVTT_TSC_DEADLINE) :
		      vector;

	osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_LVT_TIMER),
			      lvtt_vector);
	/* Set the timer divider value */
	osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_TIMER_DIV),
		osEE_x86_64_lapic_timer_div2reg(APIC_TIMER_DIVIDER));
	__asm__ volatile("mfence" : : : "memory");
}

void osEE_x86_64_timer_set_deadline(uint64_t timeout_ns)
{
	uint64_t ticks, now;

	if(x86_64_timer_tick_freq_hz) {
		if (x86_64_x2apic_tsc_deadline) {
			/* x86_64_timer_tick_freq_hz is the tsc freq */
			ticks = timeout_ns * x86_64_timer_tick_freq_hz
				/ ((uint64_t)OSEE_GIGA);
			/* Read from the TSC register */
			now = osEE_x86_64_rdtsc();
			/* Deadline: TSC + ticks */
			osEE_x86_64_write_msr(OSEE_X86_64_IA32_TSC_DEADLINE,
					      now + ticks);
		} else {
			ticks = timeout_ns * x86_64_timer_tick_freq_hz
				/ (APIC_TIMER_DIVIDER * (uint64_t)OSEE_GIGA);

			/* Deadline relative: ticks */
			osEE_x86_64_write_msr(X2APIC_CONVERT(OSEE_X86_64_APIC_TIMER_INIT_CNT),
					      ticks);
		}
	}
}
