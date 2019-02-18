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

/** \file	ee_s32k1xx_irq.h
 *  \brief	S32K144 IRQs.
 *
 *  This files contains the interfaces of the IRQs support for NXP S32K144
 *  Architecture available in Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */
#ifndef OSEE_S32K144_IRQ_H
#define	OSEE_S32K144_IRQ_H

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
				ISR IDs
 =============================================================================*/

/**
 * DMA Channel 0 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_00_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 1 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA1_ISR_ID		(			\
	OSEE_CORTEX_M_INT_01_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 2 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA2_ISR_ID		(			\
	OSEE_CORTEX_M_INT_02_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 3 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA3_ISR_ID		(			\
	OSEE_CORTEX_M_INT_03_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 4 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA4_ISR_ID		(			\
	OSEE_CORTEX_M_INT_04_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 5 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA5_ISR_ID		(			\
	OSEE_CORTEX_M_INT_05_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 6 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA6_ISR_ID		(			\
	OSEE_CORTEX_M_INT_06_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 7 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA7_ISR_ID		(			\
	OSEE_CORTEX_M_INT_07_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 8 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA8_ISR_ID		(			\
	OSEE_CORTEX_M_INT_08_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 9 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA9_ISR_ID		(			\
	OSEE_CORTEX_M_INT_09_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 10 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA10_ISR_ID		(			\
	OSEE_CORTEX_M_INT_0A_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 11 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA11_ISR_ID		(			\
	OSEE_CORTEX_M_INT_0B_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 12 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA12_ISR_ID		(			\
	OSEE_CORTEX_M_INT_0C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 13 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA13_ISR_ID		(			\
	OSEE_CORTEX_M_INT_0D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 14 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA14_ISR_ID		(			\
	OSEE_CORTEX_M_INT_0E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Channel 15 Transfer Complete.
 */
#define	OSEE_CORTEX_M_DMA15_ISR_ID		(			\
	OSEE_CORTEX_M_INT_0F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * DMA Error Channels 0-15.
 */
#define	OSEE_CORTEX_M_DMA_ERR_ISR_ID		(			\
	OSEE_CORTEX_M_INT_10_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * MCM FPU Sources.
 */
#define	OSEE_CORTEX_M_MCM_FPU_ISR_ID		(			\
	OSEE_CORTEX_M_INT_11_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Flash Memory Command Complete.
 */
#define	OSEE_CORTEX_M_FTFC_CMD_ISR_ID		(			\
	OSEE_CORTEX_M_INT_12_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Flash Memory Read Collision.
 */
#define	OSEE_CORTEX_M_FTFC_RDC_ISR_ID		(			\
	OSEE_CORTEX_M_INT_13_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * PMC Low Voltage Detection.
 */
#define	OSEE_CORTEX_M_PMC_LVD_ISR_ID		(			\
	OSEE_CORTEX_M_INT_14_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Flash Memory Double Bit Fault Detection.
 */
#define	OSEE_CORTEX_M_FTFC_FAULT_ISR_ID		(			\
	OSEE_CORTEX_M_INT_15_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Watch-Dog and External Watch-Dog Monitor.
 */
#define	OSEE_CORTEX_M_WDOG_EWM_ISR_ID		(			\
	OSEE_CORTEX_M_INT_16_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * RCM.
 */
#define	OSEE_CORTEX_M_RCM_ISR_ID		(			\
	OSEE_CORTEX_M_INT_17_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPI2C0 Master.
 */
#define	OSEE_CORTEX_M_LPI2C0_MASTER_ISR_ID		(		\
	OSEE_CORTEX_M_INT_18_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPI2C0 Slave.
 */
#define	OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_ID		(		\
	OSEE_CORTEX_M_INT_19_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPSPI0.
 */
#define	OSEE_CORTEX_M_LPSPI0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_1A_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPSPI1.
 */
#define	OSEE_CORTEX_M_LPSPI1_ISR_ID		(			\
	OSEE_CORTEX_M_INT_1B_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPSPI2.
 */
#define	OSEE_CORTEX_M_LPSPI2_ISR_ID		(			\
	OSEE_CORTEX_M_INT_1C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * LPI2C1 Master.
 */
#define	OSEE_CORTEX_M_LPI2C1_MASTER_ISR_ID		(		\
	OSEE_CORTEX_M_INT_1D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPI2C1 Slave.
 */
#define	OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_ID		(		\
	OSEE_CORTEX_M_INT_1E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/**
 * LPUART0.
 */
#define	OSEE_CORTEX_M_LPUART0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_1F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPUART1.
 */
#define	OSEE_CORTEX_M_LPUART1_ISR_ID		(			\
	OSEE_CORTEX_M_INT_21_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPUART2.
 */
#define	OSEE_CORTEX_M_LPUART2_ISR_ID		(			\
	OSEE_CORTEX_M_INT_23_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * ADC0.
 */
#define	OSEE_CORTEX_M_ADC0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_27_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * ADC1.
 */
#define	OSEE_CORTEX_M_ADC1_ISR_ID		(			\
	OSEE_CORTEX_M_INT_28_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CMP0.
 */
#define	OSEE_CORTEX_M_CMP0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_29_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * ERM Single Fault.
 */
#define	OSEE_CORTEX_M_ERM_SINGLE_ISR_ID		(			\
	OSEE_CORTEX_M_INT_2C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * ERM Double Fault.
 */
#define	OSEE_CORTEX_M_ERM_DOUBLE_ISR_ID		(			\
	OSEE_CORTEX_M_INT_2D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * RTC Alarm.
 */
#define	OSEE_CORTEX_M_RTC_ALARM_ISR_ID		(			\
	OSEE_CORTEX_M_INT_2E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * RTC Seconds.
 */
#define	OSEE_CORTEX_M_RTC_SECONDS_ISR_ID	(			\
	OSEE_CORTEX_M_INT_2F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPIT0 Channel 0.
 */
#define	OSEE_CORTEX_M_LPIT0_CH0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_30_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPIT0 Channel 1.
 */
#define	OSEE_CORTEX_M_LPIT0_CH1_ISR_ID		(			\
	OSEE_CORTEX_M_INT_31_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPIT0 Channel 2.
 */
#define	OSEE_CORTEX_M_LPIT0_CH2_ISR_ID		(			\
	OSEE_CORTEX_M_INT_32_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPIT0 Channel 3.
 */
#define	OSEE_CORTEX_M_LPIT0_CH3_ISR_ID		(			\
	OSEE_CORTEX_M_INT_33_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * PDB0.
 */
#define	OSEE_CORTEX_M_PDB0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_34_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * SAI1 Tx.
 */
#define	OSEE_CORTEX_M_SAI1_TX_ISR_ID		(			\
	OSEE_CORTEX_M_INT_37_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * SAI1 Rx.
 */
#define	OSEE_CORTEX_M_SAI1_RX_ISR_ID		(			\
	OSEE_CORTEX_M_INT_38_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/**
 * SCG.
 */
#define	OSEE_CORTEX_M_SCG_ISR_ID		(			\
	OSEE_CORTEX_M_INT_39_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * LPTMR0.
 */
#define	OSEE_CORTEX_M_LPTMR0_ISR_ID		(			\
	OSEE_CORTEX_M_INT_3A_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Port A.
 */
#define	OSEE_CORTEX_M_PORTA_ISR_ID		(			\
	OSEE_CORTEX_M_INT_3B_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Port B.
 */
#define	OSEE_CORTEX_M_PORTB_ISR_ID		(			\
	OSEE_CORTEX_M_INT_3C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Port C.
 */
#define	OSEE_CORTEX_M_PORTC_ISR_ID		(			\
	OSEE_CORTEX_M_INT_3D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Port D
 */
#define	OSEE_CORTEX_M_PORTD_ISR_ID		(			\
	OSEE_CORTEX_M_INT_3E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Port E
 */
#define	OSEE_CORTEX_M_PORTE_ISR_ID		(			\
	OSEE_CORTEX_M_INT_3F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Software Interrupt.
 */
#define	OSEE_CORTEX_M_SWI_ISR_ID		(			\
	OSEE_CORTEX_M_INT_40_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * QSPI.
 */
#define	OSEE_CORTEX_M_QSPI_ISR_ID		(			\
	OSEE_CORTEX_M_INT_41_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/**
 * PDB1.
 */
#define	OSEE_CORTEX_M_PDB1_ISR_ID		(			\
	OSEE_CORTEX_M_INT_44_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FlexIO.
 */
#define	OSEE_CORTEX_M_FLEXIO_ISR_ID		(			\
	OSEE_CORTEX_M_INT_45_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * SAI0 Tx.
 */
#define	OSEE_CORTEX_M_SAI0_TX_ISR_ID		(			\
	OSEE_CORTEX_M_INT_46_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * SAI0 Rx.
 */
#define	OSEE_CORTEX_M_SAI0_RX_ISR_ID		(			\
	OSEE_CORTEX_M_INT_47_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/**
 * Ethernet Timer.
 */
#define	OSEE_CORTEX_M_ENET_TIMER_ISR_ID		(			\
	OSEE_CORTEX_M_INT_48_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Ethernet TX.
 */
#define	OSEE_CORTEX_M_ENET_TX_ISR_ID		(			\
	OSEE_CORTEX_M_INT_49_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Ethernet RX.
 */
#define	OSEE_CORTEX_M_ENET_RX_ISR_ID		(			\
	OSEE_CORTEX_M_INT_4A_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Ethernet Error.
 */
#define	OSEE_CORTEX_M_ENET_ERR_ISR_ID		(			\
	OSEE_CORTEX_M_INT_4B_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Ethernet Stop.
 */
#define	OSEE_CORTEX_M_ENET_STOP_ISR_ID		(			\
	OSEE_CORTEX_M_INT_4C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * Ethernet Wake-Up.
 */
#define	OSEE_CORTEX_M_ENET_WAKE_ISR_ID		(			\
	OSEE_CORTEX_M_INT_4D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN0 OR'ed
 */
#define	OSEE_CORTEX_M_CAN0_ORED_ISR_ID		(			\
	OSEE_CORTEX_M_INT_4E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN0 Error
 */
#define	OSEE_CORTEX_M_CAN0_ERR_ISR_ID		(			\
	OSEE_CORTEX_M_INT_4F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN0 Wake-Up.
 */
#define	OSEE_CORTEX_M_CAN0_WAKE_ISR_ID		(			\
	OSEE_CORTEX_M_INT_50_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN0 OR'ed Channel 0 to Channel 15.
 */
#define	OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_ID	(			\
	OSEE_CORTEX_M_INT_51_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN0 OR'ed Channel 16 to Channel 31.
 */
#define	OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_ID	(			\
	OSEE_CORTEX_M_INT_52_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN1 OR'ed
 */
#define	OSEE_CORTEX_M_CAN1_ORED_ISR_ID		(			\
	OSEE_CORTEX_M_INT_55_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN1 Error
 */
#define	OSEE_CORTEX_M_CAN1_ERR_ISR_ID		(			\
	OSEE_CORTEX_M_INT_56_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN1 OR'ed Channel 0 to Channel 15.
 */
#define	OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_ID	(			\
	OSEE_CORTEX_M_INT_58_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * CAN1 OR'ed Channel 16 to Channel 31.
 */
#define	OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_ID	(			\
	OSEE_CORTEX_M_INT_59_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/**
 * CAN2 OR'ed
 */
#define	OSEE_CORTEX_M_CAN2_ORED_ISR_ID		(			\
	OSEE_CORTEX_M_INT_5C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN2 Error
 */
#define	OSEE_CORTEX_M_CAN2_ERR_ISR_ID		(			\
	OSEE_CORTEX_M_INT_5D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * CAN2 OR'ed Channel 0 to Channel 15.
 */
#define	OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_ID	(			\
	OSEE_CORTEX_M_INT_5F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * CAN2 OR'ed Channel 16 to Channel 31.
 */
#define	OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_ID	(			\
	OSEE_CORTEX_M_INT_60_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/**
 * FTM0 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_63_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM0 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_64_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM0 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_65_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM0 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_66_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM0 Fault
 */
#define	OSEE_CORTEX_M_FTM0_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_67_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM0 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_68_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM1 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_69_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM1 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_6A_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM1 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_6B_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM1 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_6C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM1 Fault
 */
#define	OSEE_CORTEX_M_FTM1_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_6D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM1 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_6E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM2 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_6F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM2 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_70_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM2 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_71_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM2 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_72_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM2 Fault
 */
#define	OSEE_CORTEX_M_FTM2_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_73_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM2 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_74_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM3 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_75_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM3 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_76_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM3 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_77_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM3 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_78_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM3 Fault
 */
#define	OSEE_CORTEX_M_FTM3_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_79_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM3 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_7A_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * FTM4 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_7B_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM4 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_7C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM4 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_7D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM4 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_7E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM4 Fault
 */
#define	OSEE_CORTEX_M_FTM4_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_7F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM4 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_80_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM5 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_81_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM5 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_82_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM5 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_83_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM5 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_84_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM5 Fault
 */
#define	OSEE_CORTEX_M_FTM5_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_85_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM5 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_86_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM6 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_87_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM6 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_88_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM6 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_89_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM6 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_8A_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM6 Fault
 */
#define	OSEE_CORTEX_M_FTM6_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_8B_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM6 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_8C_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM7 Channel 0 Channel 1
 */
#define	OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_ID	(			\
	OSEE_CORTEX_M_INT_8D_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM7 Channel 2 Channel 3
 */
#define	OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_ID	(			\
	OSEE_CORTEX_M_INT_8E_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM7 Channel 4 Channel 5
 */
#define	OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_ID	(			\
	OSEE_CORTEX_M_INT_8F_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM7 Channel 6 Channel 7
 */
#define	OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_ID	(			\
	OSEE_CORTEX_M_INT_90_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM7 Fault
 */
#define	OSEE_CORTEX_M_FTM7_FAULT_ISR_ID	(			\
	OSEE_CORTEX_M_INT_91_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)

/**
 * FTM7 Counter Overflow or Reload Flag.
 */
#define	OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_ID	(			\
	OSEE_CORTEX_M_INT_92_NUM + OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/**
 * ISR Number.
 */
#define	OSEE_CORTEX_M_ISR_ID_NUM	(				\
	OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_ID + 1			\
)
#else	/* OS_EE_ARCH_CORTEX_M_S32K148 */
/**
 * ISR Number.
 */
#define	OSEE_CORTEX_M_ISR_ID_NUM	(				\
	OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_ID + 1			\
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

#if (defined(__cplusplus))
}
#endif

#endif	/* !OSEE_S32K144_IRQ_H */
