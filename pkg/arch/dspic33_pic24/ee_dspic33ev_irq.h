/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2018 Evidence s.r.l.
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

/** \file	ee_dspic33ev_irq.h
 *  \brief	dsPIC33EV IRQs.
 *
 *  This files contains the interfaces of the IRQs support for dsPIC33EV
 *  Architecture available in Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */
#if	(!defined(OSEE_DSPIC33EV_IRQ_H))
#define	OSEE_DSPIC33EV_IRQ_H

/*==============================================================================
				ISR IDs
 =============================================================================*/

#define	OSEE_DSPIC33_PIC24_OSCFAIL_ISR_ID	0x00U

#define	OSEE_DSPIC33_PIC24_ADDRERR_ISR_ID	0x01U

#define	OSEE_DSPIC33_PIC24_SGHT_ISR_ID		0x02U

#define	OSEE_DSPIC33_PIC24_STKERR_ISR_ID	0x03U

#define	OSEE_DSPIC33_PIC24_MATHERR_ISR_ID	0x04U

#define	OSEE_DSPIC33_PIC24_DMACERR_ISR_ID	0x05U

#define	OSEE_DSPIC33_PIC24_SGST_ISR_ID		0x06U

#define	OSEE_DSPIC33_PIC24_INT0_ISR_ID		0x08U

#define	OSEE_DSPIC33_PIC24_IC1_ISR_ID		0x09U

#define	OSEE_DSPIC33_PIC24_OC1_ISR_ID		0x0AU

#define	OSEE_DSPIC33_PIC24_T1_ISR_ID		0x0BU

#define	OSEE_DSPIC33_PIC24_DMA0_ISR_ID		0x0CU

#define	OSEE_DSPIC33_PIC24_IC2_ISR_ID		0x0DU

#define	OSEE_DSPIC33_PIC24_OC2_ISR_ID		0x0EU

#define	OSEE_DSPIC33_PIC24_T2_ISR_ID		0x0FU

#define	OSEE_DSPIC33_PIC24_T3_ISR_ID		0x10U

#define	OSEE_DSPIC33_PIC24_SPI1E_ISR_ID		0x11U

#define	OSEE_DSPIC33_PIC24_SPI1_ISR_ID		0x12U

#define	OSEE_DSPIC33_PIC24_U1RX_ISR_ID		0x13U

#define	OSEE_DSPIC33_PIC24_U1TX_ISR_ID		0x14U

#define	OSEE_DSPIC33_PIC24_AD1_ISR_ID		0x15U

#define	OSEE_DSPIC33_PIC24_DMA1_ISR_ID		0x16U

#define	OSEE_DSPIC33_PIC24_NVM_ISR_ID		0x17U

#define	OSEE_DSPIC33_PIC24_SI2C1_ISR_ID		0x18U

#define	OSEE_DSPIC33_PIC24_MI2C1_ISR_ID		0x19U

#define	OSEE_DSPIC33_PIC24_CMP1_ISR_ID		0x1AU

#define	OSEE_DSPIC33_PIC24_CN_ISR_ID		0x1BU

#define	OSEE_DSPIC33_PIC24_INT1_ISR_ID		0x1CU

#define	OSEE_DSPIC33_PIC24_DMA2_ISR_ID		0x20U

#define	OSEE_DSPIC33_PIC24_OC3_ISR_ID		0x21U

#define	OSEE_DSPIC33_PIC24_OC4_ISR_ID		0x22U

#define	OSEE_DSPIC33_PIC24_T4_ISR_ID		0x23U

#define	OSEE_DSPIC33_PIC24_T5_ISR_ID		0x24U

#define	OSEE_DSPIC33_PIC24_INT2_ISR_ID		0x25U

#define	OSEE_DSPIC33_PIC24_U2RX_ISR_ID		0x26U

#define	OSEE_DSPIC33_PIC24_U2TX_ISR_ID		0x27U

#define	OSEE_DSPIC33_PIC24_SPI2E_ISR_ID		0x28U

#define	OSEE_DSPIC33_PIC24_SPI2_ISR_ID		0x29U

#define	OSEE_DSPIC33_PIC24_C1RX_ISR_ID		0x2AU

#define	OSEE_DSPIC33_PIC24_C1_ISR_ID		0x2BU

#define	OSEE_DSPIC33_PIC24_DMA3_ISR_ID		0x2CU

#define	OSEE_DSPIC33_PIC24_IC3_ISR_ID		0x2DU

#define	OSEE_DSPIC33_PIC24_IC4_ISR_ID		0x2EU

#define	OSEE_DSPIC33_PIC24_PSEM_ISR_ID		0x41U

#define	OSEE_DSPIC33_PIC24_U1E_ISR_ID		0x49U

#define	OSEE_DSPIC33_PIC24_U2E_ISR_ID		0x4AU

#define	OSEE_DSPIC33_PIC24_C1TX_ISR_ID		0x4EU

#define	OSEE_DSPIC33_PIC24_CTMU_ISR_ID		0x55U

#define	OSEE_DSPIC33_PIC24_PWM1_ISR_ID		0x66U

#define	OSEE_DSPIC33_PIC24_PWM2_ISR_ID		0x67U

#define	OSEE_DSPIC33_PIC24_PWM3_ISR_ID		0x68U

#define	OSEE_DSPIC33_PIC24_ICD_ISR_ID		0x96U

#define	OSEE_DSPIC33_PIC24_I2C1_ISR_ID		0xB5U

#define	OSEE_DSPIC33_PIC24_SENT1ERR_ISR_ID	0xBEU

#define	OSEE_DSPIC33_PIC24_SENT1_ISR_ID		0xBFU

#define	OSEE_DSPIC33_PIC24_SENT2ERR_ISR_ID	0xC0U

#define	OSEE_DSPIC33_PIC24_SENT2_ISR_ID		0xC1U

#define	OSEE_DSPIC33_PIC24_ECCSBE_ISR_ID	0xC2U

#define	OSEE_DSPIC33_PIC24_ISR_ID_NUM		0xC3U

#endif	/* !OSEE_DSPIC33EV_IRQ_H */
