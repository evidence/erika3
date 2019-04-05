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

/** \file   intel_i210.c
 *  \brief  Intel i210 driver
 *
 *  \author Claudio Scordino <claudio@evidence.eu.com>
 *  \date   2019
 */

#include <ee.h>
#include <string.h>

#include "intel_i210.h"
#include "ee_x86_64_tsc.h"


// ============================ Data structures ================================

static struct eth_device devs [DEVS_MAX_NB];
static u16 devs_nb = 0;	// Number of found devices


static u16 mdic_read(u16 dev, unsigned int reg)
{
	u32 val;

	mmio_write32(devs[dev].bar_addr + E1000_MDIC,
		     (reg << E1000_MDIC_REGADD_SHFT) |
		     E1000_MDIC_OP_READ);
	do {
		val = mmio_read32(devs[dev].bar_addr + E1000_MDIC);
		cpu_relax();
	} while (!(val & E1000_MDIC_READY));

	return (u16)val;
}

static void mdic_write(u16 dev, unsigned int reg, u16 val)
{
	mmio_write32(devs[dev].bar_addr + E1000_MDIC,
		     val | (reg << E1000_MDIC_REGADD_SHFT) | E1000_MDIC_OP_WRITE);
	while (!(mmio_read32(devs[dev].bar_addr + E1000_MDIC) & E1000_MDIC_READY))
		cpu_relax();
}

static void print_ring_regs(u16 dev, int queue)
{
	OSEE_PRINT("%d.RDBAL(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_RDBAL(queue)));
	OSEE_PRINT("%d.RDBAH(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_RDBAH(queue)));
	OSEE_PRINT("%d.RDLEN(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_RDLEN(queue)));
	OSEE_PRINT("%d.RDH(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_RDH(queue)));
	OSEE_PRINT("%d.RDT(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_RDT(queue)));
	OSEE_PRINT("%d.RXDCTL(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_RXDCTL(queue)));

	OSEE_PRINT("%d.TDBAL(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_TDBAL(queue)));
	OSEE_PRINT("%d.TDBAH(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_TDBAH(queue)));
	OSEE_PRINT("%d.TDLEN(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_TDLEN(queue)));
	OSEE_PRINT("%d.TDH(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_TDH(queue)));
	OSEE_PRINT("%d.TDT(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_TDT(queue)));
	OSEE_PRINT("%d.TXDCTL(%d): %x\n", dev, queue, mmio_read32(devs[dev].bar_addr + E1000_TXDCTL(queue)));
}

void print_regs(u16 dev)
{
	u32 val;

	OSEE_PRINT("~~~~~~~~~~~~~~~~~~~~~~~\n");
	OSEE_PRINT("%d.CTRL:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_CTRL));
	OSEE_PRINT("%d.CTRL_EXT:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_CTRL_EXT));
	OSEE_PRINT("%d.STATUS:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_STATUS));
	OSEE_PRINT("%d.TCTL:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_TCTL));
	OSEE_PRINT("%d.TIPG:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_TIPG));
	OSEE_PRINT("%d.GPIE:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_GPIE));
	OSEE_PRINT("%d.IVAR:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_IVAR));
	OSEE_PRINT("%d.IVAR_MISC:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_IVAR_MISC));
	OSEE_PRINT("%d.EIMS:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_EIMS));
	OSEE_PRINT("%d.EICR:\t%x\n", dev, mmio_read32(devs[dev].bar_addr + E1000_EICR));
	OSEE_PRINT("PCI Control register = %x\n", pci_read_config(devs[dev].bdf, 0x4, 2));
	OSEE_PRINT("PCI Status register = %x\n", pci_read_config(devs[dev].bdf, 0x6, 2));

	// Check speeds
	val = mmio_read32(devs[dev].bar_addr + E1000_STATUS);
	val &= E1000_STATUS_SPEED_MSK;
	if (val == E1000_STATUS_SPEED_10)
		OSEE_PRINT("Speed:\t10 Mb/s\n");
	else if (val == E1000_STATUS_SPEED_100)
		OSEE_PRINT("Speed:\t100 Mb/s\n");
	else
		OSEE_PRINT("Speed:\t1000 Mb/s\n");

	val = mmio_read32(devs[dev].bar_addr + E1000_PCS_LCTL);
	val &= E1000_PCS_LCTL_FSV_MSK;
	if (val == E1000_PCS_LCTL_FSV_10)
		OSEE_PRINT("Link speed:\t10 Mb/s\n");
	else if (val == E1000_PCS_LCTL_FSV_100)
		OSEE_PRINT("Link speed:\t100 Mb/s\n");
	else
		OSEE_PRINT("Link speed:\t1000 Mb/s\n");

	val = mdic_read(dev, E1000_MDIC_CCR);
	val &= E1000_MDIC_CCR_SPEED_MSK;
	if (val == E1000_MDIC_CCR_SPEED_10)
		OSEE_PRINT("MDIC Link speed:\t10 Mb/s\n");
	else if (val == E1000_MDIC_CCR_SPEED_100)
		OSEE_PRINT("MDIC Link speed:\t100 Mb/s\n");
	else
		OSEE_PRINT("MDIC Link speed:\t1000 Mb/s\n");

	for (int i = 0; i < NUM_QUEUES; ++i)
		print_ring_regs(dev, i);
}


static void eth_get_mac_addr(u16 dev)
{
	if (mmio_read32(devs[dev].bar_addr + E1000_RAH) & E1000_RAH_AV) {
		*(u32 *)devs[dev].mac = mmio_read32(devs[dev].bar_addr + E1000_RAL);
		*(u16 *)&(devs[dev].mac[4]) = mmio_read32(devs[dev].bar_addr + E1000_RAH);

		OSEE_PRINT("%d.MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", dev,
				devs[dev].mac[0], devs[dev].mac[1], devs[dev].mac[2],
				devs[dev].mac[3], devs[dev].mac[4], devs[dev].mac[5]);
	} else {
		OSEE_PRINT("ERROR: need to get MAC through EERD\n");
	}
}



#ifdef ETH_INTERRUPT_ENABLE
static void interrupt_enable(u16 dev)
{
		// Set MSI IRQ vector

#ifdef OSEE_PLATFORM_X86_64_ENABLE_INTEL_I210_DRIVER_USE_MSIX
		pci_msix_set_vector(devs[dev].bdf, ETH_IRQ_VECTOR, 0);
#else
		pci_msi_set_vector(devs[dev].bdf, ETH_IRQ_VECTOR);
#endif
}
#endif

static void eth_set_speed(u16 dev, u16 speed)
{
	u32 val;

	val = mmio_read32(devs[dev].bar_addr + E1000_CTRL_EXT);

	// Disable low power modes
	// Linux value (dumped): 0x101400C0
	val &= ~(E1000_CTRL_EXT_SD_LP | E1000_CTRL_EXT_PHY_LP);
	if (speed == 100)
		val |= E1000_CTRL_EXT_BYPS; // Bypass speed detection
	mmio_write32(devs[dev].bar_addr + E1000_CTRL_EXT, val);

	if (speed == 100){
		// Linux value (dumped): 0x0A10000C
		val = mmio_read32(devs[dev].bar_addr + E1000_PCS_LCTL);
		val &= ~(E1000_PCS_LCTL_FSV_MSK);
		val |= E1000_PCS_LCTL_FSV_100;
		mmio_write32(devs[dev].bar_addr + E1000_PCS_LCTL, val);

		// Disable 1000 Mb/s in all power modes:
		// Linux value (dumped): 0x0000009D
		mmio_write32(devs[dev].bar_addr + E1000_PHPM,
				mmio_read32(devs[dev].bar_addr + E1000_PHPM) | E1000_PHPM_NO_1000);
	}

	// Linux value (dumped): 0x581F0241
	val = mmio_read32(devs[dev].bar_addr + E1000_CTRL);
	OSEE_PRINT("CTRL (before changing speed):\t%x\n", val);
        val |= E1000_CTRL_SLU; // Set link up
	if (speed == 100) {
		val &= ~(E1000_CTRL_SPEED_MSK);
		val |= E1000_CTRL_SPEED_100; // Set link to 100 Mp/s
		val |= E1000_CTRL_FRCSPD; // Force speed
	} else {
		val &= ~(E1000_CTRL_FRCSPD); // Enable PHY to control MAC speed
	}
	mmio_write32(devs[dev].bar_addr + E1000_CTRL, val);
	delay_us(20000);

	val = mdic_read(dev, E1000_MDIC_CCR);
	if (speed == 100) {
		val &= ~(E1000_MDIC_CCR_SPEED_MSK);
		val |= E1000_MDIC_CCR_SPEED_100;
	}
	val &= ~(E1000_MDIC_CCR_POWER_DOWN); // Power up
	mdic_write(dev, E1000_MDIC_CCR, val);

	OSEE_PRINT("Waiting for link...\n");
	while (!(mmio_read32(devs[dev].bar_addr + E1000_STATUS) & E1000_STATUS_LU))
		cpu_relax();

	devs[dev].speed = speed;

	OSEE_PRINT(" ok\n");
}

static void eth_setup_rx(u16 dev, OsEE_bool accept_bcast)
{
	u32 val;
	// Values taken from pag. 327 and 333 of i210 datasheet for MSI-X single vector

	// Disable interrupt moderation:
	// (i210 datasheet says "A null value is not a valid setting")

#define E1000_EITR_VALUE (0x2 << 2)
	mmio_write32(devs[dev].bar_addr + E1000_EITR_0, E1000_EITR_VALUE);
	mmio_write32(devs[dev].bar_addr + E1000_EITR_1, E1000_EITR_VALUE);
	mmio_write32(devs[dev].bar_addr + E1000_EITR_2, E1000_EITR_VALUE);
	mmio_write32(devs[dev].bar_addr + E1000_EITR_3, E1000_EITR_VALUE);
	mmio_write32(devs[dev].bar_addr + E1000_EITR_4, E1000_EITR_VALUE);

#ifdef OSEE_PLATFORM_X86_64_ENABLE_INTEL_I210_DRIVER_USE_MSIX
	/*Setup for MSIX single vector, pag. 333 */
	// Enable RX interrupts:
	mmio_write32(devs[dev].bar_addr + E1000_IAM, 0x0); //0
	mmio_write32(devs[dev].bar_addr + E1000_EIAC, 0x1); // Setting auto clear for RX
	mmio_write32(devs[dev].bar_addr + E1000_EIAM, 0x0);
	/* When operating in MSI mode (or single MSIX)  and setting any bit
	 in the EIAM register causes the clearing of all bits in the EIMS
	register and the masking of all interrupts after generating a MSI interrupt.*/
	mmio_write32(devs[dev].bar_addr + E1000_EIMS, 0x1);// Set interrupt for RX

#else
	// Enable all interrupts:
	mmio_write32(devs[dev].bar_addr + E1000_IMS, 0xFFFFFFFF);
	mmio_write32(devs[dev].bar_addr + E1000_ICS, 0xFFFFFFFF);

	mmio_write32(devs[dev].bar_addr + E1000_IAM, 0xFFFFFFFF);

	mmio_write32(devs[dev].bar_addr + E1000_EIMS, 0x0);
	mmio_write32(devs[dev].bar_addr + E1000_EICS, 0x0);

	mmio_write32(devs[dev].bar_addr + E1000_EIAC, 0x0);

	mmio_write32(devs[dev].bar_addr + E1000_EIAM, 0x0);
#endif

	// Linux value (dumped): 0x50080004
	val = mmio_read32(devs[dev].bar_addr + E1000_GPIE);
	val |= ((1 << 0) | (1 << 30) | (1 << 31));
	val &= ~(1 << 4); //single MSIX

#if !defined(OSEE_PLATFORM_X86_64_ENABLE_INTEL_I210_DRIVER_USE_MSIX)
	val = 0;
#endif
 	mmio_write32(devs[dev].bar_addr + E1000_GPIE, val);


	// Linux value (dumped): 0x82828181
	mmio_write32(devs[dev].bar_addr + E1000_IVAR,
			mmio_read32(devs[dev].bar_addr + E1000_IVAR) | (1 << 7));
	mmio_write32(devs[dev].bar_addr + E1000_IVAR,
			mmio_read32(devs[dev].bar_addr + E1000_IVAR) & ~(0x7));

	// Linux value (dumped): 0x00008000
	mmio_write32(devs[dev].bar_addr + E1000_IVAR_MISC, (1 << 15));
	mmio_write32(devs[dev].bar_addr + E1000_IVAR_MISC,
			mmio_read32(devs[dev].bar_addr + E1000_IVAR_MISC) & ~(0x7));

	for (int i=0; i < NUM_QUEUES; ++i){
		mmio_write32(devs[dev].bar_addr + E1000_RXDCTL(i),
			mmio_read32(devs[dev].bar_addr + E1000_RXDCTL(i)) & ~(E1000_RXDCTL_ENABLE));
	}

	// Make the ring point to the buffer
	for (int i = 0; i < RX_DESCR_NB; ++i)
		devs[dev].rx_ring[i].addr = (u64) &(devs[dev].buffer [i * RX_BUFFER_SIZE]);

	// These must be programmed when the queue is still disabled:
        mmio_write32(devs[dev].bar_addr + E1000_RDBAL(0), (unsigned long) &(devs[dev].rx_ring));
        mmio_write32(devs[dev].bar_addr + E1000_RDBAH(0), 0);
        mmio_write32(devs[dev].bar_addr + E1000_RDLEN(0), sizeof(devs[dev].rx_ring));
        mmio_write32(devs[dev].bar_addr + E1000_RDH(0), 0);
        mmio_write32(devs[dev].bar_addr + E1000_RDT(0), 0); // Overwritten below

	// Linux value (dumped): 0x04448022
	val = mmio_read32(devs[dev].bar_addr + E1000_RCTL);
	val &= ~(E1000_RCTL_BSIZE);
	val |= (E1000_RCTL_RXEN | E1000_RCTL_SECRC | E1000_RCTL_BSIZE_2048);
	if (accept_bcast)
		val |= (E1000_RCTL_BAM);
	// Enable only the first queue
	mmio_write32(devs[dev].bar_addr + E1000_RXDCTL(0),
			mmio_read32(
					devs[dev].bar_addr + E1000_RXDCTL(0)) | E1000_RXDCTL_ENABLE);

	mmio_write32(devs[dev].bar_addr + E1000_RDT(0), RX_DESCR_NB - 1);

	/* Finally, enabling  the RX */
	mmio_write32(devs[dev].bar_addr + E1000_RCTL, val);
}



static void eth_setup_tx(u16 dev)
{
	for (int i=0; i < NUM_QUEUES; ++i){
		mmio_write32(devs[dev].bar_addr + E1000_TXDCTL(i),
			mmio_read32(devs[dev].bar_addr + E1000_TXDCTL(i)) & ~(E1000_TXDCTL_ENABLE));
	}

	// These must be programmed when the queue is still disabled:
	mmio_write32(devs[dev].bar_addr + E1000_TDBAL(0), (unsigned long) &(devs[dev].tx_ring));
	mmio_write32(devs[dev].bar_addr + E1000_TDBAH(0), 0);
	mmio_write32(devs[dev].bar_addr + E1000_TDLEN(0), sizeof(devs[dev].tx_ring));
	mmio_write32(devs[dev].bar_addr + E1000_TDH(0), 0);
	mmio_write32(devs[dev].bar_addr + E1000_TDT(0), 0);

	// Enable only the first queue
	mmio_write32(devs[dev].bar_addr + E1000_TXDCTL(0),
		mmio_read32((devs[dev].bar_addr)  + E1000_TXDCTL(0)) | E1000_TXDCTL_ENABLE);

	mmio_write32(devs[dev].bar_addr + E1000_TCTL, mmio_read32(devs[dev].bar_addr + E1000_TCTL) |
		E1000_TCTL_EN | E1000_TCTL_PSP | E1000_TCTL_CT_IEEE);
}


#if 0
void irq_handler(void)
{
	/* Reading the packet */
	static int index = 0;
	int slots = 0;

	for (slots = 0; slots < RX_DESCR_NB; ++slots) {
		if (devs[dev].rx_ring[index].dd) {
			//print("Interrupt\n");
			/* Updating statistichs*/
			static u32 current_data = 0;
			u32 data = *((u32*)(devs[dev].rx_ring[index].addr + ETH_PACKET_HEADER_SIZE));
			if(data > (current_data + 1)){
				missing += (data - (current_data + 1));
				//OSEE_PRINT("Data is %d, expecting %d\n", data, current_data + 1);
			}
			current_data = data;
			received_packets++;
			devs[dev].rx_ring[index].dd = 0; //clearing
		}else{
			break;
		}
		/* Rotating buffer */
		index = (index + 1) % RX_DESCR_NB;
	}
	/* Setting head and tail indexes */
	mmio_write32(devs[0].bar_addr + E1000_RDH(0), index);
	mmio_write32(devs[0].bar_addr + E1000_RDT(0), (index + RX_DESCR_NB) % RX_DESCR_NB);
}
#endif


// ============================ API =====================================

/**
 *  \brief Function to get the interface descriptor
 *
 *  \param [in] dev The number of interface (starts from 0)
 *  \return Pointer to the descriptor; NULL in case of wrong device id.
 */
struct eth_device* eth_get_device(u16 dev)
{
	struct eth_device* ret = NULL;
	OSEE_PRINT("eth_get_device(): requested %u total %u\n",
		dev, devs_nb);
	if (dev < devs_nb)
		ret = &(devs[dev]);
	return ret;
}

/**
 *  \brief Function to send an Ethernet frame.
 *
 *  \param [in] dev The number of interface (starts from 0)
 *  \param [in] pkt Pointer to the buffer where the frame is stored
 *  \param [in] size Length of the incoming frame
 *  \param [in] timeout_us Timeout (in us); 0 in case of no timeout.
 */
void eth_send_packet(u16 dev, void *pkt, unsigned int size, uint64_t timeout_us)
{
/* 	OSEE_PRINT("eth_send_packet() -- dev=%u  pkt=%x  size=%u  tout=%u\n", */
/* 			dev, pkt, size, timeout_us); */
	unsigned int idx = devs[dev].tx_idx;
	uint64_t expire;
	memset(&(devs[dev].tx_ring[idx]), 0, sizeof(struct txd));
	devs[dev].tx_ring[idx].addr = (unsigned long)pkt;
	devs[dev].tx_ring[idx].len = size;
	devs[dev].tx_ring[idx].rs = 1;
	devs[dev].tx_ring[idx].ifcs = 1;
	devs[dev].tx_ring[idx].eop = 1;

	devs[dev].tx_idx = (devs[dev].tx_idx + 1) % TX_DESCR_NB;
	mmio_write32(devs[dev].bar_addr + E1000_TDT(0), devs[dev].tx_idx);

	expire = osEE_x86_64_tsc_read() + timeout_us*1000;

	while ((!(devs[dev].tx_ring[idx].dd)) && ((!timeout_us) || (osEE_x86_64_tsc_read() < expire)))
		cpu_relax();
}


/**
 *  \brief Function to receive an Ethernet frame.
 *
 *  \param [in] dev The number of interface (starts from 0)
 *  \param [in] pkt Pointer to the buffer where the incoming frame must be stored
 *  \param [in] len Maximum length of the incoming frame
 *  \param [in] timeout_us Timeout (in us); 0 in case of no timeout (i.e. blocking)
 *  \param [in] bytes_to_drop Starting bytes to drop from the incoming frame
 *  \return Number of bytes actually read.
 */
unsigned int eth_receive_packet(u16 dev, void *pkt, u16 len, uint64_t timeout_us, uint16_t bytes_to_drop)
{
/* 	OSEE_PRINT("eth_receive_packet() -- dev=%u  pkt=%x  len=%u  tout=%u\n", */
/* 			dev, pkt, len, timeout_us); */
        unsigned int idx;
	unsigned int size = 0;
	struct eth_device *d = &(devs[dev]);
	uint64_t expire = osEE_x86_64_tsc_read() + timeout_us*1000;

	// Wait new data
        while (!(d->rx_ring[d->rx_idx].dd)) {
 			if (timeout_us && (osEE_x86_64_tsc_read() > expire))
				goto out;
		cpu_relax();
	}

	// Take new data
	//OSEE_PRINT("Size %x\n",d->rx_ring[d->rx_idx].len);
	size = d->rx_ring[d->rx_idx].len - bytes_to_drop;
	//OSEE_PRINT("eth_receive_packet(): packet received! (size = %u)\n", size);
	if (size > len)
		size = len; // XXX: rest of the packet will be lost!
	memcpy(pkt, (void*) (d->rx_ring)[d->rx_idx].addr + bytes_to_drop, size);

	// Reset receive interface
        idx = d->rx_idx;
        devs[dev].rx_ring[idx].dd = 0;
        d->rx_idx = (d->rx_idx + 1) % RX_DESCR_NB;
        mmio_write32(devs[dev].bar_addr + E1000_RDT(0), idx);

out:
	return size;
}

/**
 *  \brief Facility function for dicovering PCI interfaces
 *
 *  \return 0 in case of success; -1 in case no interface has been found.
 */
int eth_discover_devices(void)
{
	u64 bar, bar3;
	int bdf = 0;
	u16 ctrl;
	int ret = 0;
	OSEE_PRINT("eth_discover_devices() called\n");

	while (devs_nb < DEVS_MAX_NB) {

		bdf = pci_find_device(ETH_VENDORID, ETH_DEVICEID, bdf);
		if (bdf < 0)
			break;
		devs[devs_nb].bdf = bdf;

		OSEE_PRINT("found %04x:%04x at %02x:%02x.%x\n",
				pci_read_config(bdf, PCI_CFG_VENDOR_ID, 2),
				pci_read_config(bdf, PCI_CFG_DEVICE_ID, 2),
				bdf >> 8, (bdf >> 3) & 0x1f, bdf & 0x3);

#if !(defined(OSEE_PLATFORM_JAILHOUSE))
		sprintf(devs[devs_nb].name, "%d", devs_nb);
#else
		/* Jailhouse has no sprintf in the inmate library */
#define ASCII_DIGIT_START (0x30)
		devs[devs_nb].name[0] = (unsigned char)(devs_nb + ASCII_DIGIT_START);
		devs[devs_nb].name[1] = '\0';
#endif
		ctrl = pci_read_config(bdf, 0x4, 2);
		OSEE_PRINT("PCI Control register = %x\n", ctrl);
		ctrl |= 6; // Enable BME and other stuff
		ctrl |= (1 << 10); // No Interrupt Disable
		pci_write_config(bdf, 0x4, ctrl, 2);
		OSEE_PRINT("PCI Control register = %x\n", pci_read_config(bdf, 0x4, 2));

		// Read Base Address Register in the configuration
		bar = pci_read_config(bdf, PCI_CFG_BAR, 4);
		if ((bar & BAR_TYPE_MSK) == BAR_TYPE_32BIT)
			OSEE_PRINT ("bar0 (%lx) is at 32-bit\n", bar);
		else
			OSEE_PRINT ("bar0 (%lx) is at 64-bit\n", bar);
		if ((bar & 0x6) == 0x4)
			bar |= (u64)pci_read_config(bdf, PCI_CFG_BAR + 4, 4) << 32;

		// Map BAR0 in the virtual memory
		devs[devs_nb].bar_addr = (void *)(bar & ~0xfUL);

		map_range(devs[devs_nb].bar_addr, BAR0_SIZE, MAP_UNCACHED);
		OSEE_PRINT("BAR0 at %p\n", devs[devs_nb].bar_addr);

		// Map BAR3 in the virtual memory
		bar3 = pci_read_config(bdf, BAR3_OFFST, 4);
		if ((bar3 & BAR_TYPE_MSK) == BAR_TYPE_32BIT)
			OSEE_PRINT ("bar3 (%lx) is at 32-bit\n", bar3);
		else
			OSEE_PRINT ("bar3 (%lx) is at 64-bit\n", bar3);
		if ((bar3 & 0x6) == 0x4)
			bar3 |= (u64)pci_read_config(bdf, BAR3_OFFST + 4, 4) << 32;
		devs[devs_nb].bar3_addr = (void *)(bar3 & ~0xfUL);

		map_range(devs[devs_nb].bar3_addr, BAR3_SIZE, MAP_UNCACHED);
		OSEE_PRINT("BAR3 at %p\n", devs[devs_nb].bar3_addr);

		pci_write_config(bdf, PCI_CFG_COMMAND,
				PCI_CMD_MEM | PCI_CMD_MASTER, 2);

		// Software reset
		mmio_write32(devs[devs_nb].bar_addr + E1000_CTRL, E1000_CTRL_RST);
		while (!(mmio_read32(devs[devs_nb].bar_addr + E1000_STATUS) | E1000_STATUS_RST_DONE))
			cpu_relax();

		eth_get_mac_addr(devs_nb);

		devs_nb++;
		bdf++;

		/* Breaking */
		break;
	}

 	if (devs_nb < 1) {
		OSEE_PRINT("ERROR: no device found\n");
		ret = -1;
	}

 	OSEE_PRINT("%d PCI devices succesfully initialized\n", devs_nb);

 	return ret;
}

/**
 *  \brief Facility function for enabling one interface.
 *
 *  Important: this function needs eth_discover_devices() to be already called.
 *  \param [in] dev The number of interface (starts from 0)
 *  \param [in] accept_bcast If the interface must accept broadcast packets
 *  \param [in] speed Speed in Mbps (i.e. 100 or 1000)
 */
void eth_setup_device(u16 dev, OsEE_bool accept_bcast, u16 speed)
{
	OSEE_PRINT("eth_setup_device() called\n");
        eth_set_speed(dev, speed);
        eth_setup_rx(dev, accept_bcast);
        eth_setup_tx(dev);
#ifdef ETH_INTERRUPT_ENABLE
        interrupt_enable(dev);
#endif
}
