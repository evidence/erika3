/* ###*B*###
 * Erika Enterprise, version 3
 *
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of th:we License, or (at
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

/** \file   ee_pci.c
 *  \brief  Support for PCI configuration management
 *
 *  This file contains main functions to find a PCI device configuration
 *  space (b/d/f) and read/write configuration registers.
 *
 *  \author  Bruno Morelli, Ida Savino
 *  \date    2018
 */

#include "ee_platform_types.h"
#include "ee_ioport.h"
#include "ee_pci.h"

#define OSEE_PCI_REG_ADDR_PORT	0xcf8
#define OSEE_PCI_REG_DATA_PORT	0xcfc

#define OSEE_PCI_CONE		(1 << 31)

int osEE_pci_find_device(uint16_t vendor, uint16_t device,
			 uint16_t start_bdf, uint16_t *rbdf)
{
	unsigned int bdf;
	uint16_t vid;

	for (bdf = start_bdf; bdf < 0x10000; bdf++) {
		vid = osEE_pci_read_config(bdf, OSEE_PCI_CFG_VENDOR, 2);
		if (vid == OSEE_PCI_ID_ANY
		    || (vendor != OSEE_PCI_ID_ANY && vendor != vid))
			continue;
		if (device == OSEE_PCI_ID_ANY
		    || osEE_pci_read_config(bdf, OSEE_PCI_CFG_DEVICE,
						   2) == device) {
			*rbdf = bdf;
			return 0;
		}
	}
	return -1;
}

uint32_t osEE_pci_read_config(uint16_t bdf, unsigned int addr,
			      unsigned int size)
{
	outl(OSEE_PCI_REG_ADDR_PORT,
	     OSEE_PCI_CONE | ((uint32_t)bdf << 8) | (addr & 0xfc));
	switch (size) {
	case 1:
		return inb(OSEE_PCI_REG_DATA_PORT + (addr & 0x3));
	case 2:
		return inw(OSEE_PCI_REG_DATA_PORT + (addr & 0x3));
	case 4:
		return inl(OSEE_PCI_REG_DATA_PORT);
	default:
		return -1;
	}
}

void osEE_pci_write_config(uint16_t bdf, unsigned int addr, uint32_t value,
			   unsigned int size)
{
	outl(OSEE_PCI_REG_ADDR_PORT,
	     OSEE_PCI_CONE | ((uint32_t)bdf << 8) | (addr & 0xfc));
	switch (size) {
	case 1:
		outb(OSEE_PCI_REG_DATA_PORT + (addr & 0x3), value);
		break;
	case 2:
		outw(OSEE_PCI_REG_DATA_PORT + (addr & 0x3), value);
		break;
	case 4:
		outl(OSEE_PCI_REG_DATA_PORT, value);
		break;
	}
}
