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

/** \file   ee_pci.h
 *  \brief  Header for PCI configuration management
 *
 *  \author  Bruno Morelli, Ida Savino
 *  \date    2018
 */

#ifndef EE_PCI_H
#define EE_PCI_H

#define OSEE_BDF(b, d, f) ((f & 0x7) | ((d & 0x1F) << 3) | ((b & 0xFF) << 8))
#define OSEE_PCI_BAR0_32             0x10
#define OSEE_PCI_BAR1_32             0x14
#define OSEE_PCI_BAR2_32             0x18
#define OSEE_PCI_BAR3_32             0x1C
#define OSEE_PCI_BAR4_32             0x20
#define OSEE_PCI_BAR5_32             0x24

#define OSEE_PCI_COMMAND             0x04
#define OSEE_PCI_COMMAND_MASTER      0x04
#define OSEE_PCI_COMMAND_MEMORY      0x02

#define OSEE_PCI_ID_ANY              0xFF
#define OSEE_PCI_CFG_VENDOR          0x00
#define OSEE_PCI_CFG_DEVICE          0x02

int osEE_pci_find_device(uint16_t vendor, uint16_t device,
			 uint16_t start_bdf, uint16_t *rbdf);

uint32_t osEE_pci_read_config(uint16_t bdf, unsigned int addr,
			      unsigned int size);

void osEE_pci_write_config(uint16_t bdf, unsigned int addr,
			   uint32_t value, unsigned int size);

#endif /* EE_PCI_H */
