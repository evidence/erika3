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
#include "ee_ioport.h"
#include "ee_x86_64_memory_mgmt.h"

#define MSR_IA32_APIC_BASE      0x1B

#define OSEE_X86_64_APIC_ID                 0x020U
#define OSEE_X86_64_APIC_TPR                0x080U
#define OSEE_X86_64_APIC_EOI                0x0B0U
#define OSEE_X86_64_APIC_LDR                0x0D0U
#define OSEE_X86_64_APIC_DFR                0x0E0U
#define OSEE_X86_64_APIC_SPIVR              0x0F0U
#define OSEE_X86_64_APIC_ESR                0x280U
#define OSEE_X86_64_APIC_LVT_TIMER          0x320U
#define OSEE_X86_64_APIC_LVT_THERMAL        0x330U
#define OSEE_X86_64_APIC_LVT_PERF           0x340U
#define OSEE_X86_64_APIC_LVT_INT0           0x350U
#define OSEE_X86_64_APIC_LVT_INT1           0x360U
#define OSEE_X86_64_APIC_LVT_ERR            0x370U

#define OSEE_X86_64_APIC_TIMER_INIT_CNT     0x380U
#define OSEE_X86_64_APIC_TIMER_CURR_CNT     0x390U
#define OSEE_X86_64_APIC_TIMER_DIV          0x3E0U

#define OSEE_X86_64_APIC_TPR_MASK           0xFFU
#define OSEE_X86_64_APIC_LVT_MASK           0x300FFU

#define OSEE_X86_64_APIC_LVT_VEC(x)         ((x) & 0xFF)
#define OSEE_X86_64_APIC_LVT_MT_FIXED       (0x00000)
#define OSEE_X86_64_APIC_LVT_MT_SMI         (0x00200)
#define OSEE_X86_64_APIC_LVT_MT_NMI         (0x00400)
#define OSEE_X86_64_APIC_LVT_MT_EXTINT      (0x00700)
#define OSEE_X86_64_APIC_LVT_MASKED         (1U << 16)
#define OSEE_X86_64_APIC_LVT_TIMER_PERIODIC (1U << 17)

#define OSEE_X86_64_APIC_THERMAL_VECTOR     250
#define OSEE_X86_64_APIC_ERROR_VECTOR       254
#define OSEE_X86_64_APIC_SPURIOUS_VECTOR    255

#define NS_PER_USEC             1000UL
#define NS_PER_MSEC             1000000UL
#define NS_PER_SEC              1000000000UL

static OsEE_vaddr apic_base_vaddr;

OSEE_STATIC_INLINE uint32_t lapic_read_reg(uint64_t reg) {
	return *((volatile uint32_t*) (apic_base_vaddr +reg));
}

OSEE_STATIC_INLINE void lapic_write_reg(uint64_t reg, uint32_t val) {
    *((volatile uint32_t*) (apic_base_vaddr + reg)) = val;
}

/*==============================================================================
                            Core IDs Utilities
 =============================================================================*/
OsEE_core_id osEE_x86_64_get_local_apic_id(void) {
	/* TODO: check in case of multi-core */
	return (OsEE_core_id)(lapic_read_reg(OSEE_X86_64_APIC_ID) >> 24);
}

/*==============================================================================
                            Interrupt management
 =============================================================================*/
void osEE_x86_64_int_controller_init(void)
{
	uint32_t val;
	uint32_t apic_id;
	OsEE_paddr apic_paddr;

	/* Retrieve the apic virtual base address */
	apic_paddr = (OsEE_paddr) osEE_x86_64_read_msr(MSR_IA32_APIC_BASE);
	apic_paddr &= 0xFFFFF000;
	/* Map the APIC page in the virtual memory */
	if (osEE_x86_64_map_range(apic_paddr, PAGE_SIZE, MAP_UNCACHED)) {
		/* TODO */
		//printf("Error in memory map\n");
		for(;;);
	}
	apic_base_vaddr = (OsEE_vaddr) apic_paddr;

	/* Set Flate model in Destination Format Register */
	val = lapic_read_reg(OSEE_X86_64_APIC_DFR);
	lapic_write_reg(OSEE_X86_64_APIC_DFR, 0xFFFFFFFFU);
	val = lapic_read_reg(OSEE_X86_64_APIC_DFR);

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
	 * Associate the source id for the spurious interrupts
	 */
	val = lapic_read_reg(OSEE_X86_64_APIC_SPIVR);
        val &= 0xFFFFFF00U;
	val |= OSEE_X86_64_APIC_SPURIOUS_VECTOR;
	val |= 0x100;
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
}

/* TODO */
void osEE_x86_64_int_send_ipi(unsigned int cpu_id, unsigned int vector)
{
}

void osEE_x86_64_int_send_eoi(void)
{
	/* End of Interrupt Register */
	lapic_write_reg(OSEE_X86_64_APIC_EOI, 0);
}


/*==============================================================================
                                 Timer Support
 =============================================================================*/
static uint64_t x86_64_timer_tick_freq_hz = 0;
#define TIMER_DIVIDER 16UL

static int osEE_x86_64_lapic_timer_div2reg(int div)
{
/*                 31 - 4      3   2   1     0
 * APIC_TIMER_DIV |   0  | dv[2] | 0 | dv[1:0] |
 * dv     timer divide
 * 000     2
 * 001     4
 * 010     8
 * 011    16
 * 100    32
 * 101    64
 * 110   128
 * 111     1
 */
	int c;
	uint8_t reg = 0x0b;

	if (div <= 1 || div > 128)
		return reg;

	for (c = 0; div > 1; div /= 2)
		c++;

	c -= 1;
	reg = ((c & 0x4) << 1) | (c & 0x3);

	return reg;
}

void osEE_x86_64_set_timer_tick_freq(uint64_t tick_freq_hz)
{
	x86_64_timer_tick_freq_hz = tick_freq_hz;
}

void osEE_x86_64_oneshot_timer_init(unsigned int vector)
{
	uint32_t val;

	val= lapic_read_reg(OSEE_X86_64_APIC_LVT_TIMER);
	/* Set Timer Local Vector Table: unmask/one-shot and vector 0x00 */
	val &= ~OSEE_X86_64_APIC_LVT_MASK;
	/* Set Timer Local Vector Table: set vector to vector */
	val |= OSEE_X86_64_APIC_LVT_VEC(vector);
	lapic_write_reg(OSEE_X86_64_APIC_LVT_TIMER, val);
}

void osEE_x86_64_timer_set_deadline(uint64_t timeout_ns)
{
	uint64_t ticks;

	/* x86_64_timer_tick_freq_hz should be calibrated at boot */
	if (x86_64_timer_tick_freq_hz) {
	        ticks = (timeout_ns * x86_64_timer_tick_freq_hz)
			/ (TIMER_DIVIDER * NS_PER_SEC);
		/* Set the timer divider value */
		lapic_write_reg(OSEE_X86_64_APIC_TIMER_DIV,
			osEE_x86_64_lapic_timer_div2reg(TIMER_DIVIDER));

		/* Set the start count value */
		lapic_write_reg(OSEE_X86_64_APIC_TIMER_INIT_CNT, ticks);
	}
}

/*==============================================================================
                  Timer frequency (hz) Computation
 =============================================================================*/
uint64_t osEE_x86_64_calculate_timer_tick_freq_with_pit(void);
uint64_t osEE_x86_64_calculate_timer_tick_freq_with_pit(void)
{
    uint16_t pit_sample_time;
    uint32_t ticks;
    int norm_factor_sample_time;

    /* Initialize APIC timer (one-shot mode, divide value = 16)) */
    lapic_write_reg(OSEE_X86_64_APIC_LVT_TIMER, 0x10000);
    lapic_write_reg(OSEE_X86_64_APIC_TIMER_DIV,
		    osEE_x86_64_lapic_timer_div2reg(TIMER_DIVIDER));

    /* Set the Gate high, disable speaker */
    outb(0x61, (inb(0x61) & ~0x02) | 0x01);

    /* Setup channel 2, mode 0, binary count */
    outb(0x43, 0xB0);
    /* Set PIT timer for 10ms (1193180/(1000/10) Hz = 11931 = 2e9bh) */
    pit_sample_time = 0x2E9B;
    norm_factor_sample_time = 100; /*100 10ms in a second */

    outb(0x42, pit_sample_time & 0xFF);	/* LSB */
    io_wait();		/* short delay */
    outb(0x42, (pit_sample_time >> 8) & 0xFF);	/* MSB */

    /* reset APIC timer (start counting from MAX value) */
    lapic_write_reg(OSEE_X86_64_APIC_TIMER_INIT_CNT, 0xFFFFFFFF);

    /* wait until PIT counter reaches zero */
    while ((inb(0x61) & 0x20) == 0);
    ticks = lapic_read_reg(OSEE_X86_64_APIC_TIMER_CURR_CNT);

    /* Read the current timer value (counted down from -1) */
    ticks = 0xFFFFFFFF - ticks;
    /* Take into account OSEE_X86_64_APIC_TIMER_DIV (16) and
     * the 10ms sample time
     */
    return (uint64_t)ticks * TIMER_DIVIDER * norm_factor_sample_time;
}
