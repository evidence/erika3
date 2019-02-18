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

/** \file   intel_i210.h
 *  \brief  Intel i210 driver header
 *
 *  \author Claudio Scordino <claudio@evidence.eu.com>
 *  \date   2019
 */

#ifndef INTEL_I210_H
#define INTEL_I210_H

#include <ee.h>
#include <ee_hal.h>
#include <ee_pci.h>
#include <ee_x86_64_memory_mgmt.h>

// ============================ Jailhouse => Xen types =========================
//PCI
#define  PCI_CFG_VENDOR_ID  OSEE_PCI_CFG_VENDOR
#define  PCI_CFG_DEVICE_ID	OSEE_PCI_CFG_DEVICE

#define  PCI_CFG_BAR		OSEE_PCI_BAR0_32
#define  PCI_CFG_COMMAND	OSEE_PCI_COMMAND
#define  PCI_CMD_MEM		OSEE_PCI_COMMAND_MEMORY
#define  PCI_CMD_MASTER		OSEE_PCI_COMMAND_MASTER

#define  pci_read_config	osEE_pci_read_config
#define  pci_write_config	osEE_pci_write_config

#define	 mmio_read32(x)		osEE_mmio_read32((OsEE_reg)(x))
#define  mmio_write32(x, y)		osEE_mmio_write32((OsEE_reg) (x), y)

#define  map_range(x, y, z)	osEE_x86_64_map_range((OsEE_paddr)(x), y, z)

#define pci_msix_set_vector 	osEE_pci_msix_set_vector

#define MAX_DEVICE_NAME		10

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

static inline void cpu_relax(void)
{
        asm volatile("rep; nop" : : : "memory");
}

static inline int pci_find_device(uint16_t vendor, uint16_t device,
        uint16_t start_bdf)
{
	uint16_t ret_bdf = 0;
	osEE_pci_find_device(vendor, device, start_bdf, &ret_bdf);
	return ret_bdf;
}

static inline void delay_us(uint64_t max_cycles)
{
	int cycles;
	for(cycles = max_cycles; cycles > 0; --cycles)
		cpu_relax();
		//asm volatile("nop":::"memory");
}


// ============================ Hardware =======================================
/* Taken using "sudo lspci -nn" */
#define ETH_VENDORID		0x8086
#define ETH_DEVICEID		0x1533

#define NUM_QUEUES		4	// i210 has 4 rx and 4 tx queues

#define ETH_IRQ_VECTOR		33

// Regions size according to "sudo lspci -vvv":
#define BAR0_SIZE		(1024 * 1024)
#define BAR3_SIZE		(16 * 1024)

// Offset of BAR3 (see https://en.wikipedia.org/wiki/PCI_configuration_space)
#define BAR3_OFFST		0x1C

#define BAR_TYPE_MSK		(3 << 1)
#define BAR_TYPE_32BIT		(0 << 1)


// ============================ Data structures ================================
#define RX_BUFFER_SIZE          2048	// This must be written into RCTL.BSIZE
#define RX_DESCR_NB		16	// Number of descriptors in the rx queue
					// It affects RDT
#define TX_DESCR_NB		16
#define DEVS_MAX_NB		3	// Maximum number of handled devices

// ============================ Registers ======================================
#define E1000_CTRL	0x00000	// Device Control - RW
	#define E1000_CTRL_FD		(1 << 0)	// Full-Duplex
	#define E1000_CTRL_SLU		(1 << 6)	// Set link up (Force Link)
	#define E1000_CTRL_SPEED_MSK	(3 << 8)	// Link speed mask
	#define E1000_CTRL_SPEED_100	(1 << 8)	// 100 Mb/s speed
	#define E1000_CTRL_FRCSPD	(1 << 11)	// Force Speed
	#define E1000_CTRL_FRCDPLX	(1 << 12)	// Force Duplex
	#define E1000_CTRL_SDP0		(1 << 16)
	#define E1000_CTRL_SDP1		(1 << 17)
	#define E1000_CTRL_RST		(1 << 26)	// Reset
#define E1000_STATUS	0x00008	// Device Status - RO
	#define E1000_STATUS_FD		(1 << 0)	// Full Duplex
	#define E1000_STATUS_LU		(1 << 1)	// Link up
	#define E1000_STATUS_SPEED_MSK	(3 << 6)	// Link speed mask
	#define E1000_STATUS_SPEED_10	(0 << 6)	// Speed 10  Mb/s
	#define E1000_STATUS_SPEED_100	(1 << 6)	// Speed 100 Mb/s
	#define E1000_STATUS_RST_DONE	(1 << 21)	// Reset done
#define E1000_CTRL_EXT	0x00018	// Extended Device Control - RW
	#define E1000_CTRL_EXT_BYPS	(1 << 15)	// Speed Select Bypass
	#define E1000_CTRL_EXT_SD_LP	(1 << 18)	// SerDes Low Power Enable
	#define E1000_CTRL_EXT_PHY_LP	(1 << 20)	// PHY Power Down
#define E1000_ICS	0x00C8
	#define	E1000_ICS_TXDW		(1 << 0)	//Sets/reads the mask for Transmit Descriptor Written Back interrupt.
	#define E1000_ICS_RXDW		(1 << 7)	//Sets/reads the mask for Receiver Descriptor Write Back interrupt.
	#define E1000_ICS_GPHY		(1 << 10)	//Sets/Reads the mask for Internal 1000/100/10BASE-T PHY interrupt
#define E1000_RCTL	0x00100  // RX Control - RW
	#define E1000_RCTL_RXEN		(1 << 1)
	#define E1000_RCTL_SBP		(1 << 2)	// Store bad packets
	#define E1000_RCTL_BAM		(1 << 15)	// Accept broadcast packets
	#define E1000_RCTL_BSIZE	0x30000		// Buffer size
	#define E1000_RCTL_BSIZE_2048	0x00000 	// Buffer size = 2048
	#define E1000_RCTL_SECRC	(1 << 26)	// Strip Ethernet CRC From Incoming Packet
#define E1000_TCTL	0x00400  // TX Control - RW
	#define E1000_TCTL_EN		(1 << 1)
	#define E1000_TCTL_PSP		(1 << 3)	// Pad Short Packets
	#define E1000_TCTL_CT_IEEE	(0xf << 4)	// IEEE Collision threshold
#define E1000_TIPG	0x00410  // TX Control - Inter-Packet Gap
	#define E1000_TIPG_IPGT_DEF	(10 << 0)
	#define E1000_TIPG_IPGR1_DEF	(10 << 10)
	#define E1000_TIPG_IPGR2_DEF	(10 << 20)
#define E1000_PHPM	0x00E14  // PHY Power Management
	#define E1000_PHPM_NO_1000	(1 << 6)	// Disable 1000 Mb/s
#define E1000_IMS	0x1508
#define E1000_IAM	0x1510
#define E1000_GPIE	0x1514	// General Purpose Interrupt Enable
	#define E1000_GPIE_MSIX		(1 << 4)	// Multiple MSIX
#define E1000_EICS	0x1520
#define E1000_EIMS	0x1524
#define E1000_EIMC	0x1528
#define E1000_EIAC	0x152C
#define E1000_EIAM	0x1530
#define E1000_EICR	0x1580
#define E1000_EITR_0	0x1680
#define E1000_EITR_1	0x1684
#define E1000_EITR_2	0x1688
#define E1000_EITR_3	0x168C
#define E1000_EITR_4	0x1690
#define E1000_IVAR	0x1700
#define E1000_IVAR_MISC	0x1740
#define E1000_PCS_LCTL	0x4208	// PCS Link Control
	#define E1000_PCS_LCTL_FSV_MSK	(3 << 1)	// Forced Speed Value mask
	#define E1000_PCS_LCTL_FSV_10	(0 << 1)	// Forced Speed 10 Mb/s
	#define E1000_PCS_LCTL_FSV_100	(1 << 1)	// Forced Speed 100 Mb/s
	#define E1000_PCS_LCTL_FDV	(1 << 3)	// Forced Duplex Value
	#define E1000_PCS_LCTL_FSD	(1 << 4)	// Force Speed and Duplex
#define E1000_PCS_LSTS	0x420C	// PCS Link Status
	#define E1000_PCS_LSTS_LINK	(1 << 0)	// Link OK
	#define E1000_PCS_LSTS_SPEED_MSK (3 << 1)	// Speed mask
	#define E1000_PCS_LSTS_SPEED_10	 (0 << 1)	// 10 Mb/s
	#define E1000_PCS_LSTS_SPEED_100 (1 << 1)	// 100 Mb/s
	#define E1000_PCS_LSTS_DUPLEX	 (1 << 3)

#define E1000_RAL	0x05400
#define E1000_RAH	0x05404
	#define E1000_RAH_AV		(1 << 31)

#define E1000_RDBAL(_n)		(0x0C000 + ((_n) * 0x040)) // Descriptor lower bits
#define E1000_RDBAH(_n)		(0x0C004 + ((_n) * 0x040)) // Descriptor higher bits
#define E1000_RDLEN(_n)		(0x0C008 + ((_n) * 0x040))
#define E1000_RDH(_n)		(0x0C010 + ((_n) * 0x040))
#define E1000_RDT(_n)		(0x0C018 + ((_n) * 0x040))
#define E1000_RXDCTL(_n)	(0x0C028 + ((_n) * 0x040))
	#define E1000_RXDCTL_ENABLE	(1<<25)

#define E1000_TDBAL(_n)		(0x0E000 + ((_n) * 0x040)) // Descriptor lower bits
#define E1000_TDBAH(_n)		(0x0E004 + ((_n) * 0x040)) // Descriptor higher bits
#define E1000_TDLEN(_n)		(0x0E008 + ((_n) * 0x040))
#define E1000_TDH(_n)		(0x0E010 + ((_n) * 0x040))
#define E1000_TDT(_n)		(0x0E018 + ((_n) * 0x040))
#define E1000_TXDCTL(_n)	(0x0E028 + ((_n) * 0x040))
	#define E1000_TXDCTL_ENABLE	(1<<25)

#define E1000_MDIC		0x0020
	#define E1000_MDIC_REGADD_SHFT		16
	#define E1000_MDIC_OP_WRITE		(0x1 << 26)
	#define E1000_MDIC_OP_READ		(0x2 << 26)
	#define E1000_MDIC_READY		(0x1 << 28)
	#define E1000_MDIC_CCR			0
		#define E1000_MDIC_CCR_POWER_DOWN	(1 << 11)
		#define E1000_MDIC_CCR_SPEED_MSK	((1 << 6)|(1 << 13))
		#define E1000_MDIC_CCR_SPEED_10		(0 << 13)
		#define E1000_MDIC_CCR_SPEED_100	(1 << 13)

struct rxd {
	u64	addr;
	u16	len;
	u16	crc;
	u8	dd:1,
		eop:1,
		ixsm:1,
		vp:1,
		udpcs:1,
		tcpcs:1,
		ipcs:1,
		pif:1;
	u8	errors;
	u16	vlan_tag;
} __attribute__((packed));

struct txd {
	u64	addr;
	u16	len;
	u8	cso;
	u8	eop:1,
		ifcs:1,
		ic:1,
		rs:1,
		rps:1,
		dext:1,
		vle:1,
		ide:1;
	u8	dd:1,
		ec:1,
		lc:1,
		tu:1,
		rsv:4;
	u8	css;
	u16	special;
} __attribute__((packed));

struct eth_device {
	char	name [MAX_DEVICE_NAME];
	int	bdf;
	void	*bar_addr;
	void	*bar3_addr;
	u8	mac[6];
	u16	speed;
	u8 buffer[RX_DESCR_NB * RX_BUFFER_SIZE];
	struct rxd rx_ring[RX_DESCR_NB] __attribute__((aligned(128)));
	struct txd tx_ring[TX_DESCR_NB] __attribute__((aligned(128)));
	unsigned int tx_idx, rx_idx;
};

//	Structure of a IEEE 802.3 Ethernet II frame:
//
//	     7           1        6     6         2        46-1500    4
//	------------------------------------------------------------------
//	| Preamble |   Frame   | MAC | MAC |    Type     | Body    | CRC |
//	|          | delimiter | Src | Dst | (Ethertype) |         |     |
//	------------------------------------------------------------------
//
//	Ethertypes:
//	0x88A4		EtherCAT protocol

#define ETHERTYPE_ETHERCAT	0xA488 // EtherCAT is 0x88A4

struct eth_packet {
	u8	dst[6];
	u8	src[6];
	u16	type;
	u8	data[4];
} __attribute__((packed));



struct eth_device* eth_get_device(u16 dev);
void eth_send_packet(u16 dev, void *pkt, unsigned int size, uint64_t timeout_us);
unsigned int eth_receive_packet(u16 dev, void *pkt, u16 len, uint64_t timeout_us, uint16_t bytes_to_drop);
int eth_discover_devices(void);
void eth_setup_device(u16 dev, OsEE_bool accept_bcast, u16 speed);
void print_regs(u16 dev);

//void irq_handler(void);

#endif // INTEL_I210_H
