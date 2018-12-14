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

/** \file   ee_x86_64_apic.c
 *  \brief  Interrupt management and timer support based on x86_64 Local APIC.
 *
 *  \author  Ida Savino
 *  \date    2018
 */


#include "ee_internal.h"
#include "ee_x86_64_apic_internal.h"
#include "ee_x86_64_memory_mgmt.h"

/* APIC virtual base address */
OsEE_vaddr osEE_x86_64_apic_base_vaddr;
/* Local apic id */
static OsEE_core_id local_apic_id;
/* TIMER tick frequency (initialization function is PLATFORM-DEPENDENT) */
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
                            Interrupt Controller Init
 =============================================================================*/
int osEE_x86_64_int_controller_init(void)
{
	uint32_t val;
	uint32_t apic_id;
	OsEE_paddr apic_paddr;

	/* Map the APIC page in the virtual memory */
	apic_paddr = (OsEE_paddr) osEE_x86_64_read_msr(MSR_IA32_APIC_BASE);
	apic_paddr &= 0xFFFFF000;
	if (osEE_x86_64_map_range(apic_paddr, PAGE_SIZE, MAP_UNCACHED))
		return -1;
	osEE_x86_64_apic_base_vaddr = (OsEE_vaddr) apic_paddr;

	/* Set the local apic id */
	local_apic_id = (OsEE_core_id)(lapic_read_reg(OSEE_X86_64_APIC_ID) >> 24);

	/* Set Flat model in Destination Format Register */
	lapic_write_reg(OSEE_X86_64_APIC_DFR, 0xFFFFFFFFU);
	/* Set Logical Destination Register */
	apic_id = lapic_read_reg(OSEE_X86_64_APIC_ID) & 0xFF000000U;
	val = lapic_read_reg(OSEE_X86_64_APIC_LDR);
	val &= 0x00FFFFFFU;
	val |= apic_id;
	lapic_write_reg(OSEE_X86_64_APIC_LDR, val);
	val = lapic_read_reg(OSEE_X86_64_APIC_LDR);

	/* Task Priority Register: allows all interrupts (bit 4-7) */
	val = lapic_read_reg(OSEE_X86_64_APIC_TPR) & ~OSEE_X86_64_APIC_TPR_MASK;
	lapic_write_reg(OSEE_X86_64_APIC_TPR, val);

	/* Spurious Interrupt Register
	 * Associate the source id (OSEE_X86_64_APIC_SPURIOUS_VECTOR) for the spurious interrupts
	 */
	val = lapic_read_reg(OSEE_X86_64_APIC_SPIVR);
        val &= 0xFFFFFF00U;
	val |= OSEE_X86_64_APIC_SPURIOUS_VECTOR;   /* Spurious vector */
	val |= 0x100;                              /* Bit 9: apic enabled/disabled */
	lapic_write_reg(OSEE_X86_64_APIC_SPIVR, val);

	/* Timer Local Vector Table */
	lapic_write_reg(OSEE_X86_64_APIC_LVT_TIMER,
			OSEE_X86_64_APIC_LVT_MT_FIXED
			| OSEE_X86_64_APIC_LVT_MASKED);
	/* Thermal Local Vector */
	lapic_write_reg(OSEE_X86_64_APIC_LVT_THERMAL,
			OSEE_X86_64_APIC_LVT_MT_FIXED
			| OSEE_X86_64_APIC_LVT_MASKED
			| OSEE_X86_64_APIC_THERMAL_VECTOR);
	/* Performance Counter Local Vector Table */
	lapic_write_reg(OSEE_X86_64_APIC_LVT_PERF,
			OSEE_X86_64_APIC_LVT_MT_NMI
			| OSEE_X86_64_APIC_LVT_MASKED);
	/* Interrupt 0 Counter Local Vector Table */
	lapic_write_reg(OSEE_X86_64_APIC_LVT_INT0,
			OSEE_X86_64_APIC_LVT_MT_EXTINT
			| OSEE_X86_64_APIC_LVT_MASKED);
	/* Interrupt 1 Counter Local Vector Table */
	lapic_write_reg(OSEE_X86_64_APIC_LVT_INT1,
			OSEE_X86_64_APIC_LVT_MT_NMI
			| OSEE_X86_64_APIC_LVT_MASKED);
	/* Set Error Vector Table */
	lapic_write_reg(OSEE_X86_64_APIC_LVT_ERR,
			OSEE_X86_64_APIC_LVT_MT_FIXED
			| OSEE_X86_64_APIC_LVT_MASKED
			| OSEE_X86_64_APIC_ERROR_VECTOR);

	/* Spec says to clear after enabling OSEE_X86_64_APIC_LVT_ERR */
	lapic_write_reg(OSEE_X86_64_APIC_ESR, 0);

	return 0;
}

/*==============================================================================
                            Interrupt management
 =============================================================================*/
void osEE_x86_64_int_send_ipi(unsigned int cpu_id, unsigned int vector)
{
	/* Interrupt Command Register:
	 * ICRH: bit 24-27  local APIC ID of target processor
	 * ICRL: bit 0-7    vector number
	 *       bit 8-10   message type (000b fixed)
	 *       bit 11     destination mode (0 physical)
	 *       bit 12     delivery status
	 *       bit 14     level (1 assert)
	 *       bit 15     trigger mode (0 edge-triggered)
	 *       bit 16-17  remote read status
	 *       bit 18-19  Destination shorthand (00b destination required)
	 * The interrupt is issued when ICRL is written.
	 */
	lapic_write_reg(OSEE_X86_64_APIC_ICRH, (uint32_t) cpu_id);
	lapic_write_reg(OSEE_X86_64_APIC_ICRL,
			(OSEE_X86_64_APIC_LVL_ASSERT
			 | OSEE_X86_64_APIC_LVT_VEC(vector)));

}

void osEE_x86_64_int_send_eoi(void)
{
	/* End of Interrupt Register */
	lapic_write_reg(OSEE_X86_64_APIC_EOI, OSEE_X86_64_APIC_EOI_ACK);
}


/*==============================================================================
                                 Timer Support
 =============================================================================*/
void osEE_x86_64_oneshot_timer_init(unsigned int vector)
{
	uint32_t val;

	val= lapic_read_reg(OSEE_X86_64_APIC_LVT_TIMER);
	/* Set Timer Local Vector Table: unmask/one-shot and vector 0x00 */
	val &= ~OSEE_X86_64_APIC_LVT_MASK;
	/* Set Timer Local Vector Table: set vector to vector */
	val |= OSEE_X86_64_APIC_LVT_VEC(vector);
	lapic_write_reg(OSEE_X86_64_APIC_LVT_TIMER, val);
	/* Set the timer divider value */
	lapic_write_reg(OSEE_X86_64_APIC_TIMER_DIV,
		osEE_x86_64_lapic_timer_div2reg(APIC_TIMER_DIVIDER));
}

void osEE_x86_64_timer_set_deadline(uint64_t timeout_ns)
{
	uint64_t ticks;

	/* x86_64_apic_timer_tick_freq_hz should be calibrated at boot */
	if (x86_64_timer_tick_freq_hz) {
		/* Calculate the ticks contained int timeout_ns
		 * Make sure divisor (APIC_TIMER*OSEE_GIGA) is 64-bit long!
		 */
	        ticks = (timeout_ns * x86_64_timer_tick_freq_hz)
			/ (APIC_TIMER_DIVIDER * (uint64_t)OSEE_GIGA);

		/* Set the start count value */
		lapic_write_reg(OSEE_X86_64_APIC_TIMER_INIT_CNT, ticks);
	}
}
