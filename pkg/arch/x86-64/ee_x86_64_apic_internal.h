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

/** \file   ee_x86_64_apic_internal.h
 *  \brief  Specific functions/macros for APIC management.
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#ifndef OSEE_X86_64_APIC_INTERNAL_H
#define OSEE_X86_64_APIC_INTERNAL_H

#define MSR_IA32_APIC_BASE      0x1B

#define OSEE_X86_64_APIC_ID             0x020U  /* Identifier */
#define OSEE_X86_64_APIC_TPR            0x080U  /* Task Priority Register */
#define OSEE_X86_64_APIC_EOI            0x0B0U  /* End of Interrupt Register */
#define OSEE_X86_64_APIC_LDR            0x0D0U  /* Logical Destination Register */
#define OSEE_X86_64_APIC_DFR            0x0E0U  /* Destination Format Register */
#define OSEE_X86_64_APIC_SPIVR          0x0F0U  /* Spurious Interrupt Vector Register */
#define OSEE_X86_64_APIC_ESR            0x280U  /* Error Status Register */
#define OSEE_X86_64_APIC_ICR            0x300U  /*Interrupt Command Register*/
#define OSEE_X86_64_APIC_ICRL           0x300U  /* ICR low part */
#define OSEE_X86_64_APIC_ICRH           0x310U  /* ICR high part */

#define OSEE_X86_64_APIC_TIMER_INIT_CNT 0x380U  /* Timer initial value */
#define OSEE_X86_64_APIC_TIMER_CURR_CNT 0x390U  /* Timer current value */
#define OSEE_X86_64_APIC_TIMER_DIV      0x3E0U  /* Timer Divider Configuration Register */

#define OSEE_X86_64_APIC_EOI_ACK            (0)
#define OSEE_X86_64_APIC_LVL_ASSERT         (1U <<14)

#define OSEE_X86_64_APIC_TPR_MASK           0xFFU

/* Local Vector Table (LVT) */
#define OSEE_X86_64_APIC_LVT_TIMER      0x320U  /* Timer LVT */
#define OSEE_X86_64_APIC_LVT_THERMAL    0x330U  /* Thermal Sensors LVT */
#define OSEE_X86_64_APIC_LVT_PERF       0x340U  /* Performance Monitor Counter LVT */
#define OSEE_X86_64_APIC_LVT_INT0       0x350U  /* Local Interrupt 0 LVT */
#define OSEE_X86_64_APIC_LVT_INT1       0x360U  /* Local Interrupt 1 LVT */
#define OSEE_X86_64_APIC_LVT_ERR        0x370U  /* Apic Internal Error LVT */
/* Local Vector Table (LVT) Register fields/masks.. */
#define OSEE_X86_64_APIC_LVT_MASK           0x300FFU
#define OSEE_X86_64_APIC_LVT_VEC(x)         ((x) & 0xFF)
/* LVT Message Type (MT) */
#define OSEE_X86_64_APIC_LVT_MT_FIXED       (0x00000)
#define OSEE_X86_64_APIC_LVT_MT_SMI         (0x00200)
#define OSEE_X86_64_APIC_LVT_MT_NMI         (0x00400)
#define OSEE_X86_64_APIC_LVT_MT_EXTINT      (0x00700)
/* LVT Mask (M) --> set to 1 disable interrupt */
#define OSEE_X86_64_APIC_LVT_MASKED         (1U << 16)
/* LVT Timer mode (TMM) --> 1 periodic timer interrutps */
#define OSEE_X86_64_APIC_LVT_TIMER_PERIODIC (1U << 17)
/* LVT vector */
#define OSEE_X86_64_APIC_THERMAL_VECTOR     250
#define OSEE_X86_64_APIC_ERROR_VECTOR       254
#define OSEE_X86_64_APIC_SPURIOUS_VECTOR    255

/* APIC virtual base address */
extern OsEE_vaddr osEE_x86_64_apic_base_vaddr;

OSEE_STATIC_INLINE
uint32_t OSEE_ALWAYS_INLINE lapic_read_reg(uint64_t reg) {
	return *((volatile uint32_t*) (osEE_x86_64_apic_base_vaddr + reg));
}

OSEE_STATIC_INLINE
void OSEE_ALWAYS_INLINE lapic_write_reg(uint64_t reg, uint32_t val) {
	*((volatile uint32_t*) (osEE_x86_64_apic_base_vaddr + reg)) = val;
}

OSEE_STATIC_INLINE
int osEE_x86_64_lapic_timer_div2reg(int div)
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

/* APIC timer tick frequency (initialization function is PLATFORM-DEPENDENT) */
extern uint64_t x86_64_timer_tick_freq_hz;

#define APIC_TIMER_DIVIDER 	16U
OSEE_STATIC_INLINE
void osEE_x86_64_set_apic_timer_tick_freq(uint64_t freq_hz)
{
	x86_64_timer_tick_freq_hz = freq_hz;
}

OSEE_STATIC_INLINE
uint64_t osEE_x86_64_get_apic_timer_tick_freq(void)
{
	return x86_64_timer_tick_freq_hz;
}

#endif /* OSEE_X86_64_APIC_INTERNAL_H */
