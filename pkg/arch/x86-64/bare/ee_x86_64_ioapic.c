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
 * <https://www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 *
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 *  * THIRD PARTIES' MATERIALS
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

/** \file   ee_x86_64_ioapic.c
 *  \brief  x86_64 I/O APIC.
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#include "ee_internal.h"
#include "ee_x86_64_memory_mgmt.h"

#define IOAPIC_IOREGSEL         (0x00)
#define IOAPIC_IOREGWIN         (0x10)
#define IOAPIC_IOREDTBL         (0x10)

#define IOREDTBL_ENTRY_NUMBER           24
#define IOREDTBL_ENTRY_RESET_VALUE_LOW  0x10000
#define IOREDTBL_ENTRY_RESET_VALUE_HIGH 0x0

#define SET_IOREDTBL_VEC(x)             ((x & 0xFF))
#define SET_IOREDTBL_DELVMODE(x)        ((x & 0x01) << 8)
#define SET_IOREDTBL_PINPOL(x)          ((x & 0x01) <<13)
#define SET_IOREDTBL_DEST(x)            ((x & 0xFF) << (56-32))

#define MASK_IOREDTBL_IRQ(x)            (x | 0x10000)
#define UNMASK_IOREDTBL_IRQ(x)          (x & ~(0x10000))

#define IOAPIC_BASE_ADDRESS             0xFEC00000

OSEE_STATIC_INLINE uint32_t ioapic_read_reg(uint32_t reg)
{
	*((volatile uint32_t *)(IOAPIC_BASE_ADDRESS + IOAPIC_IOREGSEL)) = reg;
	return *((volatile uint32_t *)(IOAPIC_BASE_ADDRESS + IOAPIC_IOREGWIN));
}

OSEE_STATIC_INLINE void ioapic_write_reg(uint32_t reg, uint32_t val)
{
	*((volatile uint32_t *)(IOAPIC_BASE_ADDRESS + IOAPIC_IOREGSEL)) = reg;
	*((volatile uint32_t *)(IOAPIC_BASE_ADDRESS + IOAPIC_IOREGWIN)) = val;
}

void osEE_x86_64_ioapic_init(void)
{
	uint32_t reg, data;

	/* Map the IOAPIC into virtual memory */
	if (osEE_x86_64_map_range((OsEE_paddr)IOAPIC_BASE_ADDRESS, PAGE_SIZE,
				  MAP_UNCACHED)) {
		/* TODO */
		//printf("Error in memory map\n");
		for(;;);
	}

	/* Disable all IRQs */
	for (int pin = 0; pin < IOREDTBL_ENTRY_NUMBER; pin++) {
		/* Reset REDIRECTION ENTRY (high) */
		reg = IOAPIC_IOREDTBL + pin * 2 + 1;
		data = IOREDTBL_ENTRY_RESET_VALUE_HIGH;
		ioapic_write_reg(reg, data);
		/* Reset REDIRECTION ENTRY (low) */
		reg = IOAPIC_IOREDTBL + pin * 2;
		data = IOREDTBL_ENTRY_RESET_VALUE_LOW;
		ioapic_write_reg(reg, data);
	}
}

void osEE_x86_64_ioapic_setup_irq(unsigned int pin, unsigned int vector)
{
	osEE_x86_64_ioapic_setup_irq_extended(osEE_x86_64_get_local_apic_id(),
					      pin, vector, FIXED, 0);
}

void osEE_x86_64_ioapic_setup_irq_extended(OsEE_core_id core_id,
					   unsigned int pin,
					   unsigned int vector,
					   enum ee_ioapic_delivery_mode del_mod,
					   unsigned int active_low)
{
	uint32_t reg, data;

	/* REDIRECTION ENTRY (high) Fields: Destination */
	reg = IOAPIC_IOREDTBL + pin * 2 + 1;
	data = IOREDTBL_ENTRY_RESET_VALUE_HIGH;
	data |= SET_IOREDTBL_DEST(core_id);
	ioapic_write_reg(reg, data);

	/* REDIRECTION ENTRY (low) Fields: Vector, Delivery mode,
	 * pin polarity, mask */
	reg = IOAPIC_IOREDTBL + pin * 2;
	data = IOREDTBL_ENTRY_RESET_VALUE_LOW;
	data |= SET_IOREDTBL_VEC(vector);
	data |= SET_IOREDTBL_DELVMODE(del_mod);
	data |= SET_IOREDTBL_PINPOL(active_low);
	data = UNMASK_IOREDTBL_IRQ(data);
	ioapic_write_reg(reg, data);
}
