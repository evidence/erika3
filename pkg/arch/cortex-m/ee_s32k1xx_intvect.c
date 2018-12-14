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

/** \file	ee_s32k144_intvect.c
 *  \brief	S32K144 MCUs Interrupts vector.
 *
 *  This files contains the implementation of S32K144 MCUs Interrupts vector in
 *  Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise Internals */
#include "ee_internal.h"

/*
 * MCU System Initialization.
 */

FUNC(void, OS_CODE) osEE_cortex_m_mcu_system_init(void)
{

/*
 * DMA Channel 0 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA0_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA0_ISR) &&		\
			(OSEE_CORTEX_M_DMA0_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA0_NUM		(				\
	OSEE_CORTEX_M_DMA0_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA0_NUM, OSEE_CORTEX_M_DMA0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA0_NUM);
#endif	/* OSEE_CORTEX_M_DMA0_ISR */

/*
 * DMA Channel 1 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA1_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA1_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA1_ISR) &&		\
			(OSEE_CORTEX_M_DMA1_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA1_NUM		(				\
	OSEE_CORTEX_M_DMA1_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA1_NUM, OSEE_CORTEX_M_DMA1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA1_NUM);
#endif	/* OSEE_CORTEX_M_DMA1_ISR */

/*
 * DMA Channel 2 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA2_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA2_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA2_ISR) &&		\
			(OSEE_CORTEX_M_DMA2_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA2_NUM		(				\
	OSEE_CORTEX_M_DMA2_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA2_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA2_NUM, OSEE_CORTEX_M_DMA2_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA2_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA2_NUM);
#endif	/* OSEE_CORTEX_M_DMA2_ISR */

/*
 * DMA Channel 3 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA3_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA3_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA3_ISR) &&		\
			(OSEE_CORTEX_M_DMA3_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA3_NUM		(				\
	OSEE_CORTEX_M_DMA3_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA3_NUM, OSEE_CORTEX_M_DMA3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA3_NUM);
#endif	/* OSEE_CORTEX_M_DMA3_ISR */

/*
 * DMA Channel 4 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA4_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA4_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA4_ISR) &&		\
			(OSEE_CORTEX_M_DMA4_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA4_NUM		(				\
	OSEE_CORTEX_M_DMA4_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA4_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA4_NUM, OSEE_CORTEX_M_DMA4_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA4_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA4_NUM);
#endif	/* OSEE_CORTEX_M_DMA4_ISR */

/*
 * DMA Channel 5 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA5_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA5_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA5_ISR) &&		\
			(OSEE_CORTEX_M_DMA5_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA5_NUM		(				\
	OSEE_CORTEX_M_DMA5_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA5_NUM, OSEE_CORTEX_M_DMA5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA5_NUM);
#endif	/* OSEE_CORTEX_M_DMA5_ISR */

/*
 * DMA Channel 6 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA6_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA6_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA6_ISR) &&		\
			(OSEE_CORTEX_M_DMA6_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA6_NUM		(				\
	OSEE_CORTEX_M_DMA6_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA6_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA6_NUM, OSEE_CORTEX_M_DMA6_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA6_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA6_NUM);
#endif	/* OSEE_CORTEX_M_DMA6_ISR */

/*
 * DMA Channel 7 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA7_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA7_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA7_ISR) &&		\
			(OSEE_CORTEX_M_DMA7_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA7_NUM		(				\
	OSEE_CORTEX_M_DMA7_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA7_NUM, OSEE_CORTEX_M_DMA7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA7_NUM);
#endif	/* OSEE_CORTEX_M_DMA7_ISR */

/*
 * DMA Channel 8 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA8_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA8_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA8_ISR) &&		\
			(OSEE_CORTEX_M_DMA8_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA8_NUM		(				\
	OSEE_CORTEX_M_DMA8_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA8_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA8_NUM, OSEE_CORTEX_M_DMA8_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA8_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA8_NUM);
#endif	/* OSEE_CORTEX_M_DMA8_ISR */

/*
 * DMA Channel 9 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA9_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA9_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA9_ISR) &&		\
			(OSEE_CORTEX_M_DMA9_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA9_NUM		(				\
	OSEE_CORTEX_M_DMA9_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA9_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA9_NUM, OSEE_CORTEX_M_DMA9_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA9_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA9_NUM);
#endif	/* OSEE_CORTEX_M_DMA9_ISR */

/*
 * DMA Channel 10 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA10_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA10_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA10_ISR) &&		\
			(OSEE_CORTEX_M_DMA10_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA10_NUM		(				\
	OSEE_CORTEX_M_DMA10_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA10_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA10_NUM, OSEE_CORTEX_M_DMA10_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA10_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA10_NUM);
#endif	/* OSEE_CORTEX_M_DMA10_ISR */

/*
 * DMA Channel 11 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA11_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA11_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA11_ISR) &&		\
			(OSEE_CORTEX_M_DMA11_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA11_NUM		(				\
	OSEE_CORTEX_M_DMA11_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA11_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA11_NUM, OSEE_CORTEX_M_DMA11_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA11_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA11_NUM);
#endif	/* OSEE_CORTEX_M_DMA11_ISR */

/*
 * DMA Channel 12 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA12_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA12_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA12_ISR) &&		\
			(OSEE_CORTEX_M_DMA12_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA12_NUM		(				\
	OSEE_CORTEX_M_DMA12_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA12_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA12_NUM, OSEE_CORTEX_M_DMA12_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA12_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA12_NUM);
#endif	/* OSEE_CORTEX_M_DMA12_ISR */

/*
 * DMA Channel 13 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA13_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA13_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA13_ISR) &&		\
			(OSEE_CORTEX_M_DMA13_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA13_NUM		(				\
	OSEE_CORTEX_M_DMA13_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA13_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA13_NUM, OSEE_CORTEX_M_DMA13_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA13_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA13_NUM);
#endif	/* OSEE_CORTEX_M_DMA13_ISR */

/*
 * DMA Channel 14 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA14_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA14_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA14_ISR) &&		\
			(OSEE_CORTEX_M_DMA14_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA14_NUM		(				\
	OSEE_CORTEX_M_DMA14_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA14_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA14_NUM, OSEE_CORTEX_M_DMA14_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA14_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA14_NUM);
#endif	/* OSEE_CORTEX_M_DMA14_ISR */

/*
 * DMA Channel 15 Transfer Complete interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA15_ISR_TID) &&		\
			(OSEE_CORTEX_M_DMA15_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA15_ISR) &&		\
			(OSEE_CORTEX_M_DMA15_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA15_NUM		(				\
	OSEE_CORTEX_M_DMA15_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA15_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA15_NUM, OSEE_CORTEX_M_DMA15_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA15_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA15_NUM);
#endif	/* OSEE_CORTEX_M_DMA15_ISR */

/*
 * DMA Error Channels 0-15 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DMA_ERR_ISR_TID) &&	\
			(OSEE_CORTEX_M_DMA_ERR_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_DMA_ERR_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ERR_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_DMA_ERR_NUM		(			\
	OSEE_CORTEX_M_DMA_ERR_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_DMA_ERR_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_DMA_ERR_NUM, OSEE_CORTEX_M_DMA_ERR_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_DMA_ERR_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_DMA_ERR_NUM);
#endif	/* OSEE_CORTEX_M_DMA_ERR_ISR */

/*
 * MCM FPU Sources.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_MCM_FPU_ISR_TID) &&	\
			(OSEE_CORTEX_M_MCM_FPU_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_MCM_FPU_ISR) &&		\
			(OSEE_CORTEX_M_DMA_MCM_FPU_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_MCM_FPU_NUM		(			\
	OSEE_CORTEX_M_MCM_FPU_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_MCM_FPU_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_MCM_FPU_NUM, OSEE_CORTEX_M_MCM_FPU_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_MCM_FPU_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_MCM_FPU_NUM);
#endif	/* OSEE_CORTEX_M_MCM_FPU_ISR */

/*
 * Flash Memory Command Complete.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTFC_CMD_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTFC_CMD_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTFC_CMD_ISR) &&		\
			(OSEE_CORTEX_M_DMA_FTFC_CMD_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTFC_CMD_NUM		(			\
	OSEE_CORTEX_M_FTFC_CMD_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_FTFC_CMD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTFC_CMD_NUM, OSEE_CORTEX_M_FTFC_CMD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTFC_CMD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTFC_CMD_NUM);
#endif	/* OSEE_CORTEX_M_FTFC_CMD_ISR */

/*
 * Flash Memory Read Collision.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTFC_RDC_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTFC_RDC_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTFC_RDC_ISR) &&		\
			(OSEE_CORTEX_M_DMA_FTFC_RDC_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTFC_RDC_NUM		(			\
	OSEE_CORTEX_M_FTFC_RDC_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_FTFC_RDC_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTFC_RDC_NUM, OSEE_CORTEX_M_FTFC_RDC_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTFC_RDC_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTFC_RDC_NUM);
#endif	/* OSEE_CORTEX_M_FTFC_RDC_ISR */

/*
 * PMC Low Voltage Detection.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PMC_LVD_ISR_TID) &&	\
			(OSEE_CORTEX_M_PMC_LVD_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PMC_LVD_ISR) &&		\
			(OSEE_CORTEX_M_DMA_PMC_LVD_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PMC_LVD_NUM		(			\
	OSEE_CORTEX_M_PMC_LVD_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_PMC_LVD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PMC_LVD_NUM, OSEE_CORTEX_M_PMC_LVD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PMC_LVD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PMC_LVD_NUM);
#endif	/* OSEE_CORTEX_M_PMC_LVD_ISR */

/*
 * Flash Memory Double Bit Fault Detection.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTFC_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTFC_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTFC_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_DMA_FTFC_FAULT_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTFC_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTFC_FAULT_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_FTFC_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTFC_FAULT_NUM, OSEE_CORTEX_M_FTFC_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTFC_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTFC_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTFC_FAULT_ISR */

/*
 * Watch-Dog and External Watch-Dog Monitor.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_WDOG_EWM_ISR_TID) &&	\
			(OSEE_CORTEX_M_WDOG_EWM_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_WDOG_EWM_ISR) &&		\
			(OSEE_CORTEX_M_DMA_WDOG_EWM_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_WDOG_EWM_NUM		(			\
	OSEE_CORTEX_M_WDOG_EWM_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_WDOG_EWM_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_WDOG_EWM_NUM, OSEE_CORTEX_M_WDOG_EWM_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_WDOG_EWM_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_WDOG_EWM_NUM);
#endif	/* OSEE_CORTEX_M_WDOG_EWM_ISR */

/*
 * RCM.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_RCM_ISR_TID) &&		\
			(OSEE_CORTEX_M_RCM_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_RCM_ISR) &&		\
			(OSEE_CORTEX_M_DMA_RCM_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_RCM_NUM		(				\
	OSEE_CORTEX_M_RCM_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_RCM_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_RCM_NUM, OSEE_CORTEX_M_RCM_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_RCM_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_RCM_NUM);
#endif	/* OSEE_CORTEX_M_RCM_ISR */

/*
 * LPI2C0 Master.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPI2C0_MASTER_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPI2C0_MASTER_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_LPI2C0_MASTER_ISR) &&	\
			(OSEE_CORTEX_M_DMA_LPI2C0_MASTER_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_LPI2C0_MASTER_NUM		(			\
	OSEE_CORTEX_M_LPI2C0_MASTER_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPI2C0_MASTER_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPI2C0_MASTER_NUM,
		OSEE_CORTEX_M_LPI2C0_MASTER_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPI2C0_MASTER_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPI2C0_MASTER_NUM);
#endif	/* OSEE_CORTEX_M_LPI2C0_MASTER_ISR */

/*
 * LPI2C0 Slave.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_LPI2C0_SLAVE_ISR) &&	\
			(OSEE_CORTEX_M_DMA_LPI2C0_SLAVE_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_LPI2C0_SLAVE_NUM		(			\
	OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPI2C0_SLAVE_NUM,
		OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPI2C0_SLAVE_NUM);
#endif	/* OSEE_CORTEX_M_LPI2C0_SLAVE_ISR */

/*
 * LPSPI0.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPSPI0_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPSPI0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPSPI0_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPSPI0_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPSPI0_NUM		(			\
	OSEE_CORTEX_M_LPSPI0_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_LPSPI0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPSPI0_NUM, OSEE_CORTEX_M_LPSPI0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPSPI0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPSPI0_NUM);
#endif	/* OSEE_CORTEX_M_LPSPI0_ISR */

/*
 * LPSPI1.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPSPI1_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPSPI1_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPSPI1_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPSPI1_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPSPI1_NUM		(			\
	OSEE_CORTEX_M_LPSPI1_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_LPSPI1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPSPI1_NUM, OSEE_CORTEX_M_LPSPI1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPSPI1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPSPI1_NUM);
#endif	/* OSEE_CORTEX_M_LPSPI1_ISR */

/*
 * LPSPI2.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPSPI2_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPSPI2_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPSPI2_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPSPI2_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPSPI2_NUM		(			\
	OSEE_CORTEX_M_LPSPI2_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_LPSPI2_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPSPI2_NUM, OSEE_CORTEX_M_LPSPI2_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPSPI2_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPSPI2_NUM);
#endif	/* OSEE_CORTEX_M_LPSPI2_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * LPI2C1 Master.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPI2C1_MASTER_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPI2C1_MASTER_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_LPI2C1_MASTER_ISR) &&	\
			(OSEE_CORTEX_M_DMA_LPI2C1_MASTER_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_LPI2C1_MASTER_NUM		(			\
	OSEE_CORTEX_M_LPI2C1_MASTER_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPI2C1_MASTER_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPI2C1_MASTER_NUM,
		OSEE_CORTEX_M_LPI2C1_MASTER_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPI2C1_MASTER_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPI2C1_MASTER_NUM);
#endif	/* OSEE_CORTEX_M_LPI2C1_MASTER_ISR */

/*
 * LPI2C1 Slave.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_LPI2C1_SLAVE_ISR) &&	\
			(OSEE_CORTEX_M_DMA_LPI2C1_SLAVE_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_LPI2C1_SLAVE_NUM		(			\
	OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPI2C1_SLAVE_NUM,
		OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPI2C1_SLAVE_NUM);
#endif	/* OSEE_CORTEX_M_LPI2C1_SLAVE_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * LPUART0.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPUART0_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPUART0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPUART0_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPUART0_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPUART0_NUM		(			\
	OSEE_CORTEX_M_LPUART0_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPUART0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPUART0_NUM,
		OSEE_CORTEX_M_LPUART0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPUART0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPUART0_NUM);
#endif	/* OSEE_CORTEX_M_LPUART0_ISR */

/*
 * LPUART1.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPUART1_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPUART1_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPUART1_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPUART1_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPUART1_NUM		(			\
	OSEE_CORTEX_M_LPUART1_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPUART1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPUART1_NUM,
		OSEE_CORTEX_M_LPUART1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPUART1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPUART1_NUM);
#endif	/* OSEE_CORTEX_M_LPUART1_ISR */

/*
 * LPUART2.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPUART2_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPUART2_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPUART2_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPUART2_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPUART2_NUM		(			\
	OSEE_CORTEX_M_LPUART2_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPUART2_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPUART2_NUM,
		OSEE_CORTEX_M_LPUART2_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPUART2_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPUART2_NUM);
#endif	/* OSEE_CORTEX_M_LPUART2_ISR */

/*
 * ADC0.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ADC0_ISR_TID) &&		\
			(OSEE_CORTEX_M_ADC0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ADC0_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ADC0_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ADC0_NUM		(				\
	OSEE_CORTEX_M_ADC0_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ADC0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ADC0_NUM,
		OSEE_CORTEX_M_ADC0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ADC0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ADC0_NUM);
#endif	/* OSEE_CORTEX_M_ADC0_ISR */

/*
 * ADC1.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ADC1_ISR_TID) &&		\
			(OSEE_CORTEX_M_ADC1_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ADC1_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ADC1_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ADC1_NUM		(				\
	OSEE_CORTEX_M_ADC1_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ADC1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ADC1_NUM,
		OSEE_CORTEX_M_ADC1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ADC1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ADC1_NUM);
#endif	/* OSEE_CORTEX_M_ADC1_ISR */

/*
 * CMP0.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CMP0_ISR_TID) &&		\
			(OSEE_CORTEX_M_CMP0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CMP0_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CMP0_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CMP0_NUM		(				\
	OSEE_CORTEX_M_CMP0_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CMP0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CMP0_NUM,
		OSEE_CORTEX_M_CMP0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CMP0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CMP0_NUM);
#endif	/* OSEE_CORTEX_M_CMP0_ISR */

/*
 * ERM Single Fault.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ERM_SINGLE_ISR_TID) &&	\
			(OSEE_CORTEX_M_ERM_SINGLE_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ERM_SINGLE_ISR) &&	\
			(OSEE_CORTEX_M_DMA_ERM_SINGLE_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ERM_SINGLE_NUM		(			\
	OSEE_CORTEX_M_ERM_SINGLE_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ERM_SINGLE_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ERM_SINGLE_NUM,
		OSEE_CORTEX_M_ERM_SINGLE_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ERM_SINGLE_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ERM_SINGLE_NUM);
#endif	/* OSEE_CORTEX_M_ERM_SINGLE_ISR */

/*
 * ERM Double Fault-
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ERM_DOUBLE_ISR_TID) &&	\
			(OSEE_CORTEX_M_ERM_DOUBLE_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ERM_DOUBLE_ISR) &&	\
			(OSEE_CORTEX_M_DMA_ERM_DOUBLE_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ERM_DOUBLE_NUM		(			\
	OSEE_CORTEX_M_ERM_DOUBLE_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ERM_DOUBLE_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ERM_DOUBLE_NUM,
		OSEE_CORTEX_M_ERM_DOUBLE_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ERM_DOUBLE_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ERM_DOUBLE_NUM);
#endif	/* OSEE_CORTEX_M_ERM_DOUBLE_ISR */

/*
 * RTC Alarm.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_RTC_ALARM_ISR_TID) &&	\
			(OSEE_CORTEX_M_RTC_ALARM_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_RTC_ALARM_ISR) &&		\
			(OSEE_CORTEX_M_DMA_RTC_ALARM_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_RTC_ALARM_NUM		(			\
	OSEE_CORTEX_M_RTC_ALARM_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_RTC_ALARM_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_RTC_ALARM_NUM,
		OSEE_CORTEX_M_RTC_ALARM_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_RTC_ALARM_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_RTC_ALARM_NUM);
#endif	/* OSEE_CORTEX_M_RTC_ALARM_ISR */

/*
 * RTC Seconds.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_RTC_SECONDS_ISR_TID) &&	\
			(OSEE_CORTEX_M_RTC_SECONDS_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_RTC_SECONDS_ISR) &&	\
			(OSEE_CORTEX_M_DMA_RTC_SECONDS_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_RTC_SECONDS_NUM		(			\
	OSEE_CORTEX_M_RTC_SECONDS_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_RTC_SECONDS_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_RTC_SECONDS_NUM,
		OSEE_CORTEX_M_RTC_SECONDS_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_RTC_SECONDS_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_RTC_SECONDS_NUM);
#endif	/* OSEE_CORTEX_M_RTC_SECONDS_ISR */

/*
 * LPIT0 Channel 0.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPIT0_CH0_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPIT0_CH0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPIT0_CH0_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPIT0_CH0_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPIT0_CH0_NUM		(			\
	OSEE_CORTEX_M_LPIT0_CH0_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPIT0_CH0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPIT0_CH0_NUM,
		OSEE_CORTEX_M_LPIT0_CH0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPIT0_CH0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPIT0_CH0_NUM);
#endif	/* OSEE_CORTEX_M_LPIT0_CH0_ISR */

/*
 * LPIT0 Channel 1.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPIT0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPIT0_CH1_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPIT0_CH1_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPIT0_CH1_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPIT0_CH1_NUM		(			\
	OSEE_CORTEX_M_LPIT0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPIT0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPIT0_CH1_NUM,
		OSEE_CORTEX_M_LPIT0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPIT0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPIT0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_LPIT0_CH1_ISR */

/*
 * LPIT0 Channel 2.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPIT0_CH2_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPIT0_CH2_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPIT0_CH2_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPIT0_CH2_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPIT0_CH2_NUM		(			\
	OSEE_CORTEX_M_LPIT0_CH2_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPIT0_CH2_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPIT0_CH2_NUM,
		OSEE_CORTEX_M_LPIT0_CH2_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPIT0_CH2_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPIT0_CH2_NUM);
#endif	/* OSEE_CORTEX_M_LPIT0_CH2_ISR */

/*
 * LPIT0 Channel 3.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPIT0_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPIT0_CH3_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPIT0_CH3_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPIT0_CH3_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPIT0_CH3_NUM		(			\
	OSEE_CORTEX_M_LPIT0_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPIT0_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPIT0_CH3_NUM,
		OSEE_CORTEX_M_LPIT0_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPIT0_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPIT0_CH3_NUM);
#endif	/* OSEE_CORTEX_M_LPIT0_CH3_ISR */

/*
 * PDB0.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PDB0_ISR_TID) &&		\
			(OSEE_CORTEX_M_PDB0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PDB0_ISR) &&		\
			(OSEE_CORTEX_M_DMA_PDB0_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PDB0_NUM		(				\
	OSEE_CORTEX_M_PDB0_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_PDB0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PDB0_NUM,
		OSEE_CORTEX_M_PDB0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PDB0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PDB0_NUM);
#endif	/* OSEE_CORTEX_M_PDB0_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * SAI1 Tx.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_SAI1_TX_ISR_TID) &&	\
			(OSEE_CORTEX_M_SAI1_TX_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_SAI1_TX_ISR) &&		\
			(OSEE_CORTEX_M_DMA_SAI1_TX_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_SAI1_TX_NUM		(			\
	OSEE_CORTEX_M_SAI1_TX_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_SAI1_TX_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_SAI1_TX_NUM,
		OSEE_CORTEX_M_SAI1_TX_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_SAI1_TX_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_SAI1_TX_NUM);
#endif	/* OSEE_CORTEX_M_SAI1_TX_ISR */

/*
 * SAI1 Rx.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_SAI1_RX_ISR_TID) &&	\
			(OSEE_CORTEX_M_SAI1_RX_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_SAI1_RX_ISR) &&		\
			(OSEE_CORTEX_M_DMA_SAI1_RX_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_SAI1_RX_NUM		(			\
	OSEE_CORTEX_M_SAI1_RX_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_SAI1_RX_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_SAI1_RX_NUM,
		OSEE_CORTEX_M_SAI1_RX_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_SAI1_RX_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_SAI1_RX_NUM);
#endif	/* OSEE_CORTEX_M_SAI1_RX_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * SCG.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_SCG_ISR_TID) &&		\
			(OSEE_CORTEX_M_SCG_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_SCG_ISR) &&		\
			(OSEE_CORTEX_M_DMA_SCG_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_SCG_NUM		(				\
	OSEE_CORTEX_M_SCG_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_SCG_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_SCG_NUM,
		OSEE_CORTEX_M_SCG_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_SCG_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_SCG_NUM);
#endif	/* OSEE_CORTEX_M_SCG_ISR */

/*
 * LPTMR0.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_LPTMR0_ISR_TID) &&	\
			(OSEE_CORTEX_M_LPTMR0_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_LPTMR0_ISR) &&		\
			(OSEE_CORTEX_M_DMA_LPTMR0_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_LPTMR0_NUM		(			\
	OSEE_CORTEX_M_LPTMR0_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_LPTMR0_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_LPTMR0_NUM,
		OSEE_CORTEX_M_LPTMR0_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_LPTMR0_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_LPTMR0_NUM);
#endif	/* OSEE_CORTEX_M_LPTMR0_ISR */

/*
 * Port A pin detect interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PORTA_ISR_TID) &&		\
			(OSEE_CORTEX_M_PORTA_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PORTA_ISR) &&		\
			(OSEE_CORTEX_M_PORTA_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PORTA_NUM		(				\
	OSEE_CORTEX_M_PORTA_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_PORTA_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PORTA_NUM, OSEE_CORTEX_M_PORTA_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PORTA_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PORTA_NUM);
#endif	/* OSEE_CORTEX_M_PORTA_ISR */

/*
 * Port B pin detect interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PORTB_ISR_TID) &&		\
			(OSEE_CORTEX_M_PORTB_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PORTB_ISR) &&		\
			(OSEE_CORTEX_M_PORTB_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PORTB_NUM		(				\
	OSEE_CORTEX_M_PORTB_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_PORTB_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PORTB_NUM, OSEE_CORTEX_M_PORTB_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PORTB_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PORTB_NUM);
#endif	/* OSEE_CORTEX_M_PORTB_ISR */

/*
 * Port C pin detect interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PORTC_ISR_TID) &&		\
			(OSEE_CORTEX_M_PORTC_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PORTC_ISR) &&		\
			(OSEE_CORTEX_M_PORTC_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PORTC_NUM		(				\
	OSEE_CORTEX_M_PORTC_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_PORTC_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PORTC_NUM, OSEE_CORTEX_M_PORTC_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PORTC_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PORTC_NUM);
#endif	/* OSEE_CORTEX_M_PORTC_ISR */

/*
 * Port D pin detect interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PORTD_ISR_TID) &&		\
			(OSEE_CORTEX_M_PORTD_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PORTD_ISR) &&		\
			(OSEE_CORTEX_M_PORTD_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PORTD_NUM		(				\
	OSEE_CORTEX_M_PORTD_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_PORTD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PORTD_NUM, OSEE_CORTEX_M_PORTD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PORTD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PORTD_NUM);
#endif	/* OSEE_CORTEX_M_PORTD_ISR */

/*
 * Port E pin detect interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PORTE_ISR_TID) &&		\
			(OSEE_CORTEX_M_PORTE_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PORTE_ISR) &&		\
			(OSEE_CORTEX_M_PORTE_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PORTE_NUM		(				\
	OSEE_CORTEX_M_PORTE_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_PORTE_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PORTE_NUM, OSEE_CORTEX_M_PORTE_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PORTE_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PORTE_NUM);
#endif	/* OSEE_CORTEX_M_PORTE_ISR */

/*
 * Software Interrupt.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_SWI_ISR_TID) &&		\
			(OSEE_CORTEX_M_SWI_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_SWI_ISR) &&		\
			(OSEE_CORTEX_M_SWI_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_SWI_NUM		(				\
	OSEE_CORTEX_M_SWI_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_SWI_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_SWI_NUM, OSEE_CORTEX_M_SWI_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_SWI_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_SWI_NUM);
#endif	/* OSEE_CORTEX_M_SWI_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * QSPI.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_QSPI_ISR_TID) &&		\
			(OSEE_CORTEX_M_QSPI_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_QSPI_ISR) &&		\
			(OSEE_CORTEX_M_QSPI_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_QSPI_NUM		(				\
	OSEE_CORTEX_M_QSPI_ISR_ID - OSEE_CORTEX_M_OVERALL_EXC_NUM	\
)
#ifdef	OSEE_CORTEX_M_QSPI_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_QSPI_NUM, OSEE_CORTEX_M_QSPI_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_QSPI_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_QSPI_NUM);
#endif	/* OSEE_CORTEX_M_QSPI_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * PDB1.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_PDB1_ISR_TID) &&		\
			(OSEE_CORTEX_M_PDB1_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_PDB1_ISR) &&		\
			(OSEE_CORTEX_M_DMA_PDB1_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_PDB1_NUM		(				\
	OSEE_CORTEX_M_PDB1_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_PDB1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_PDB1_NUM,
		OSEE_CORTEX_M_PDB1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_PDB1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_PDB1_NUM);
#endif	/* OSEE_CORTEX_M_PDB1_ISR */

/*
 * FlexIO.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FLEXIO_ISR_TID) &&	\
			(OSEE_CORTEX_M_FLEXIO_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FLEXIO_ISR) &&		\
			(OSEE_CORTEX_M_DMA_FLEXIO_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FLEXIO_NUM		(			\
	OSEE_CORTEX_M_FLEXIO_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FLEXIO_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FLEXIO_NUM,
		OSEE_CORTEX_M_FLEXIO_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FLEXIO_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FLEXIO_NUM);
#endif	/* OSEE_CORTEX_M_FLEXIO_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * SAI0 Tx.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_SAI0_TX_ISR_TID) &&	\
			(OSEE_CORTEX_M_SAI0_TX_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_SAI0_TX_ISR) &&		\
			(OSEE_CORTEX_M_DMA_SAI0_TX_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_SAI0_TX_NUM		(			\
	OSEE_CORTEX_M_SAI0_TX_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_SAI0_TX_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_SAI0_TX_NUM,
		OSEE_CORTEX_M_SAI0_TX_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_SAI0_TX_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_SAI0_TX_NUM);
#endif	/* OSEE_CORTEX_M_SAI0_TX_ISR */

/*
 * SAI0 Rx.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_SAI0_RX_ISR_TID) &&	\
			(OSEE_CORTEX_M_SAI0_RX_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_SAI0_RX_ISR) &&		\
			(OSEE_CORTEX_M_DMA_SAI0_RX_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_SAI0_RX_NUM		(			\
	OSEE_CORTEX_M_SAI0_RX_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_SAI0_RX_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_SAI0_RX_NUM,
		OSEE_CORTEX_M_SAI0_RX_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_SAI0_RX_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_SAI0_RX_NUM);
#endif	/* OSEE_CORTEX_M_SAI0_RX_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * Ethernet Timer.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ENET_TIMER_ISR_TID) &&	\
			(OSEE_CORTEX_M_ENET_TIMER_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ENET_TIMER_ISR) &&	\
			(OSEE_CORTEX_M_DMA_ENET_TIMER_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ENET_TIMER_NUM		(			\
	OSEE_CORTEX_M_ENET_TIMER_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ENET_TIMER_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ENET_TIMER_NUM,
		OSEE_CORTEX_M_ENET_TIMER_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ENET_TIMER_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ENET_TIMER_NUM);
#endif	/* OSEE_CORTEX_M_ENET_TIMER_ISR */

/*
 * Ethernet Tx.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ENET_TX_ISR_TID) &&	\
			(OSEE_CORTEX_M_ENET_TX_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ENET_TX_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ENET_TX_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ENET_TX_NUM		(			\
	OSEE_CORTEX_M_ENET_TX_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ENET_TX_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ENET_TX_NUM,
		OSEE_CORTEX_M_ENET_TX_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ENET_TX_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ENET_TX_NUM);
#endif	/* OSEE_CORTEX_M_ENET_TX_ISR */

/*
 * Ethernet Rx.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ENET_RX_ISR_TID) &&	\
			(OSEE_CORTEX_M_ENET_RX_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ENET_RX_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ENET_RX_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ENET_RX_NUM		(			\
	OSEE_CORTEX_M_ENET_RX_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ENET_RX_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ENET_RX_NUM,
		OSEE_CORTEX_M_ENET_RX_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ENET_RX_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ENET_RX_NUM);
#endif	/* OSEE_CORTEX_M_ENET_RX_ISR */

/*
 * Ethernet Error.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ENET_ERR_ISR_TID) &&	\
			(OSEE_CORTEX_M_ENET_ERR_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ENET_ERR_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ENET_ERR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ENET_ERR_NUM		(			\
	OSEE_CORTEX_M_ENET_ERR_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ENET_ERR_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ENET_ERR_NUM,
		OSEE_CORTEX_M_ENET_ERR_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ENET_ERR_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ENET_ERR_NUM);
#endif	/* OSEE_CORTEX_M_ENET_ERR_ISR */

/*
 * Ethernet Stop.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ENET_STOP_ISR_TID) &&	\
			(OSEE_CORTEX_M_ENET_STOP_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ENET_STOP_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ENET_STOP_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ENET_STOP_NUM		(			\
	OSEE_CORTEX_M_ENET_STOP_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ENET_STOP_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ENET_STOP_NUM,
		OSEE_CORTEX_M_ENET_STOP_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ENET_STOP_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ENET_STOP_NUM);
#endif	/* OSEE_CORTEX_M_ENET_STOP_ISR */

/*
 * Ethernet Wake-Up.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_ENET_WAKE_ISR_TID) &&	\
			(OSEE_CORTEX_M_ENET_WAKE_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_ENET_WAKE_ISR) &&		\
			(OSEE_CORTEX_M_DMA_ENET_WAKE_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_ENET_WAKE_NUM		(			\
	OSEE_CORTEX_M_ENET_WAKE_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_ENET_WAKE_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_ENET_WAKE_NUM,
		OSEE_CORTEX_M_ENET_WAKE_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_ENET_WAKE_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_ENET_WAKE_NUM);
#endif	/* OSEE_CORTEX_M_ENET_WAKE_ISR */

/*
 * CAN0 OR'ed.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN0_ORED_ISR_TID) &&	\
			(OSEE_CORTEX_M_CAN0_ORED_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CAN0_ORED_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CAN0_ORED_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CAN0_ORED_NUM		(			\
	OSEE_CORTEX_M_CAN0_ORED_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN0_ORED_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN0_ORED_NUM,
		OSEE_CORTEX_M_CAN0_ORED_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN0_ORED_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN0_ORED_NUM);
#endif	/* OSEE_CORTEX_M_CAN0_ORED_ISR */

/*
 * CAN0 Error.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN0_ERR_ISR_TID) &&	\
			(OSEE_CORTEX_M_CAN0_ERR_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CAN0_ERR_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CAN0_ERR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CAN0_ERR_NUM		(			\
	OSEE_CORTEX_M_CAN0_ERR_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN0_ERR_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN0_ERR_NUM,
		OSEE_CORTEX_M_CAN0_ERR_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN0_ERR_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN0_ERR_NUM);
#endif	/* OSEE_CORTEX_M_CAN0_ERR_ISR */

/*
 * CAN0 Wake-up.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN0_WAKE_ISR_TID) &&	\
			(OSEE_CORTEX_M_CAN0_WAKE_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CAN0_WAKE_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CAN0_WAKE_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CAN0_WAKE_NUM		(			\
	OSEE_CORTEX_M_CAN0_WAKE_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN0_WAKE_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN0_WAKE_NUM,
		OSEE_CORTEX_M_CAN0_WAKE_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN0_WAKE_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN0_WAKE_NUM);
#endif	/* OSEE_CORTEX_M_CAN0_WAKE_ISR */

/*
 * CAN0 OR'ed Channel 0 to Channel 15.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_TID)	\
			&& (OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_CAN0_ORED_0_15_ISR) &&	\
			(OSEE_CORTEX_M_DMA_CAN0_ORED_0_15_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_CAN0_ORED_0_15_NUM		(		\
	OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN0_ORED_0_15_NUM,
		OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN0_ORED_0_15_NUM);
#endif	/* OSEE_CORTEX_M_CAN0_ORED_0_15_ISR */

/*
 * CAN0 OR'ed Channel 16 to Channel 31.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_TID)	\
			&& (OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_CAN0_ORED_16_31_ISR) &&	\
			(OSEE_CORTEX_M_DMA_CAN0_ORED_16_31_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_CAN0_ORED_16_31_NUM		(		\
	OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN0_ORED_16_31_NUM,
		OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN0_ORED_16_31_NUM);
#endif	/* OSEE_CORTEX_M_CAN0_ORED_16_31_ISR */

/*
 * CAN1 OR'ed.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN1_ORED_ISR_TID) &&	\
			(OSEE_CORTEX_M_CAN1_ORED_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CAN1_ORED_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CAN1_ORED_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CAN1_ORED_NUM		(			\
	OSEE_CORTEX_M_CAN1_ORED_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN1_ORED_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN1_ORED_NUM,
		OSEE_CORTEX_M_CAN1_ORED_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN1_ORED_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN1_ORED_NUM);
#endif	/* OSEE_CORTEX_M_CAN1_ORED_ISR */

/*
 * CAN1 Error.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN1_ERR_ISR_TID) &&	\
			(OSEE_CORTEX_M_CAN1_ERR_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CAN1_ERR_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CAN1_ERR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CAN1_ERR_NUM		(			\
	OSEE_CORTEX_M_CAN1_ERR_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN1_ERR_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN1_ERR_NUM,
		OSEE_CORTEX_M_CAN1_ERR_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN1_ERR_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN1_ERR_NUM);
#endif	/* OSEE_CORTEX_M_CAN1_ERR_ISR */

/*
 * CAN1 OR'ed Channel 0 to Channel 15.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_TID)	\
			&& (OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_CAN1_ORED_0_15_ISR) &&	\
			(OSEE_CORTEX_M_DMA_CAN1_ORED_0_15_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_CAN1_ORED_0_15_NUM		(		\
	OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN1_ORED_0_15_NUM,
		OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN1_ORED_0_15_NUM);
#endif	/* OSEE_CORTEX_M_CAN1_ORED_0_15_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * CAN1 OR'ed Channel 16 to Channel 31.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_TID)	\
			&& (OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_CAN1_ORED_16_31_ISR) &&	\
			(OSEE_CORTEX_M_DMA_CAN1_ORED_16_31_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_CAN1_ORED_16_31_NUM		(		\
	OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN1_ORED_16_31_NUM,
		OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN1_ORED_16_31_NUM);
#endif	/* OSEE_CORTEX_M_CAN1_ORED_16_31_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * CAN2 OR'ed.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN2_ORED_ISR_TID) &&	\
			(OSEE_CORTEX_M_CAN2_ORED_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CAN2_ORED_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CAN2_ORED_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CAN2_ORED_NUM		(			\
	OSEE_CORTEX_M_CAN2_ORED_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN2_ORED_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN2_ORED_NUM,
		OSEE_CORTEX_M_CAN2_ORED_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN2_ORED_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN2_ORED_NUM);
#endif	/* OSEE_CORTEX_M_CAN2_ORED_ISR */

/*
 * CAN2 Error.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN2_ERR_ISR_TID) &&	\
			(OSEE_CORTEX_M_CAN2_ERR_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_CAN2_ERR_ISR) &&		\
			(OSEE_CORTEX_M_DMA_CAN2_ERR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_CAN2_ERR_NUM		(			\
	OSEE_CORTEX_M_CAN2_ERR_ISR_ID -					\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN2_ERR_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN2_ERR_NUM,
		OSEE_CORTEX_M_CAN2_ERR_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN2_ERR_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN2_ERR_NUM);
#endif	/* OSEE_CORTEX_M_CAN2_ERR_ISR */

/*
 * CAN2 OR'ed Channel 0 to Channel 15.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_TID)	\
			&& (OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_CAN2_ORED_0_15_ISR) &&	\
			(OSEE_CORTEX_M_DMA_CAN2_ORED_0_15_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_CAN2_ORED_0_15_NUM		(		\
	OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN2_ORED_0_15_NUM,
		OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN2_ORED_0_15_NUM);
#endif	/* OSEE_CORTEX_M_CAN2_ORED_0_15_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * CAN2 OR'ed Channel 16 to Channel 31.
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_TID)	\
			&& (OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_CAN2_ORED_16_31_ISR) &&	\
			(OSEE_CORTEX_M_DMA_CAN2_ORED_16_31_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_CAN2_ORED_16_31_NUM		(		\
	OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_CAN2_ORED_16_31_NUM,
		OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_CAN2_ORED_16_31_NUM);
#endif	/* OSEE_CORTEX_M_CAN2_ORED_16_31_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * FTM0 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM0_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM0_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM0_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM0_CH0_CH1_ISR */

/*
 * FTM0 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM0_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM0_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM0_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM0_CH2_CH3_ISR */

/*
 * FTM0 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM0_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM0_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM0_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM0_CH4_CH5_ISR */

/*
 * FTM0 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM0_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM0_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM0_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM0_CH6_CH7_ISR */

/*
 * FTM0 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM0_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM0_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM0_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM0_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM0_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM0_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM0_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM0_FAULT_NUM,
		OSEE_CORTEX_M_FTM0_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM0_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM0_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM0_FAULT_ISR */

/*
 * FTM0 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM0_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM0_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM0_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR */

/*
 * FTM1 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM1_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM1_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM1_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM1_CH0_CH1_ISR */

/*
 * FTM1 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM1_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM1_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM1_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM1_CH2_CH3_ISR */

/*
 * FTM1 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM1_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM1_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM1_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM1_CH4_CH5_ISR */

/*
 * FTM1 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM1_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM1_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM1_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM1_CH6_CH7_ISR */

/*
 * FTM1 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM1_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM1_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM1_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM1_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM1_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM1_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM1_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM1_FAULT_NUM,
		OSEE_CORTEX_M_FTM1_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM1_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM1_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM1_FAULT_ISR */

/*
 * FTM1 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM1_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM1_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM1_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR */

/*
 * FTM2 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM2_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM2_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM2_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM2_CH0_CH1_ISR */

/*
 * FTM2 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM2_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM2_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM2_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM2_CH2_CH3_ISR */

/*
 * FTM2 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM2_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM2_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM2_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM2_CH4_CH5_ISR */

/*
 * FTM2 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM2_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM2_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM2_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM2_CH6_CH7_ISR */

/*
 * FTM2 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM2_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM2_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM2_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM2_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM2_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM2_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM2_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM2_FAULT_NUM,
		OSEE_CORTEX_M_FTM2_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM2_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM2_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM2_FAULT_ISR */

/*
 * FTM2 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM2_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM2_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM2_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR */

/*
 * FTM3 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM3_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM3_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM3_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM3_CH0_CH1_ISR */

/*
 * FTM3 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM3_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM3_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM3_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM3_CH2_CH3_ISR */

/*
 * FTM3 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM3_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM3_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM3_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM3_CH4_CH5_ISR */

/*
 * FTM3 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM3_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM3_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM3_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM3_CH6_CH7_ISR */

/*
 * FTM3 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM3_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM3_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM3_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM3_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM3_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM3_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM3_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM3_FAULT_NUM,
		OSEE_CORTEX_M_FTM3_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM3_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM3_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM3_FAULT_ISR */

/*
 * FTM3 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM3_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM3_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM3_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * FTM4 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM4_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM4_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM4_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM4_CH0_CH1_ISR */

/*
 * FTM4 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM4_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM4_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM4_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM4_CH2_CH3_ISR */

/*
 * FTM4 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM4_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM4_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM4_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM4_CH4_CH5_ISR */

/*
 * FTM4 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM4_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM4_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM4_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM4_CH6_CH7_ISR */

/*
 * FTM4 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM4_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM4_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM4_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM4_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM4_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM4_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM4_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM4_FAULT_NUM,
		OSEE_CORTEX_M_FTM4_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM4_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM4_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM4_FAULT_ISR */

/*
 * FTM4 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM4_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM4_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM4_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR */

/*
 * FTM5 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM5_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM5_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM5_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM5_CH0_CH1_ISR */

/*
 * FTM5 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM5_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM5_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM5_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM5_CH2_CH3_ISR */

/*
 * FTM5 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM5_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM5_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM5_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM5_CH4_CH5_ISR */

/*
 * FTM5 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM5_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM5_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM5_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM5_CH6_CH7_ISR */

/*
 * FTM5 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM5_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM5_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM5_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM5_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM5_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM5_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM5_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM5_FAULT_NUM,
		OSEE_CORTEX_M_FTM5_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM5_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM5_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM5_FAULT_ISR */

/*
 * FTM5 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM5_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM5_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM5_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR */

/*
 * FTM6 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM6_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM6_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM6_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM6_CH0_CH1_ISR */

/*
 * FTM6 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM6_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM6_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM6_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM6_CH2_CH3_ISR */

/*
 * FTM6 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM6_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM6_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM6_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM6_CH4_CH5_ISR */

/*
 * FTM6 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM6_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM6_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM6_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM6_CH6_CH7_ISR */

/*
 * FTM6 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM6_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM6_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM6_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM6_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM6_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM6_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM6_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM6_FAULT_NUM,
		OSEE_CORTEX_M_FTM6_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM6_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM6_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM6_FAULT_ISR */

/*
 * FTM6 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM6_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM6_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM6_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR */

/*
 * FTM7 Channel 0 Channel 1 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR) &&	\
			(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM7_CH0_CH1_NUM		(			\
	OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM7_CH0_CH1_NUM,
		OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM7_CH0_CH1_NUM);
#endif	/* OSEE_CORTEX_M_FTM7_CH0_CH1_ISR */

/*
 * FTM7 Channel 2 Channel 3 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR) &&	\
			(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM7_CH2_CH3_NUM		(			\
	OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM7_CH2_CH3_NUM,
		OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM7_CH2_CH3_NUM);
#endif	/* OSEE_CORTEX_M_FTM7_CH2_CH3_ISR */

/*
 * FTM7 Channel 4 Channel 5 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR) &&	\
			(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM7_CH4_CH5_NUM		(			\
	OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM7_CH4_CH5_NUM,
		OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM7_CH4_CH5_NUM);
#endif	/* OSEE_CORTEX_M_FTM7_CH4_CH5_ISR */

/*
 * FTM7 Channel 6 Channel 7 interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR) &&	\
			(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM7_CH6_CH7_NUM		(			\
	OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM7_CH6_CH7_NUM,
		OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM7_CH6_CH7_NUM);
#endif	/* OSEE_CORTEX_M_FTM7_CH6_CH7_ISR */

/*
 * FTM7 Fault interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM7_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_FTM7_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_FTM7_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_FTM7_FAULT_ISR_CAT == 1)		\
		)							\
)
#define	OSEE_CORTEX_M_FTM7_FAULT_NUM		(			\
	OSEE_CORTEX_M_FTM7_FAULT_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM7_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM7_FAULT_NUM,
		OSEE_CORTEX_M_FTM7_FAULT_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM7_FAULT_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM7_FAULT_NUM);
#endif	/* OSEE_CORTEX_M_FTM7_FAULT_ISR */

/*
 * FTM7 Overflow Reload interrupt initialization
 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_TID)	\
			&& (OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR) &&	\
			(OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_CAT == 1)	\
		)							\
)
#define	OSEE_CORTEX_M_FTM7_OVF_RELOAD_NUM		(		\
	OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_ID -				\
	OSEE_CORTEX_M_OVERALL_EXC_NUM					\
)
#ifdef	OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_PRI
	OSEE_CORTEX_M_NVIC_SET_PRI(
		OSEE_CORTEX_M_FTM7_OVF_RELOAD_NUM,
		OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_PRI
	);
#endif	/* OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_PRI */
	OSEE_CORTEX_M_NVIC_INT_ENABLE(OSEE_CORTEX_M_FTM7_OVF_RELOAD_NUM);
#endif	/* OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

}	/* osEE_cortex_m_mcu_system_init() */

/*
 * Interrupt Vector Definition
 */

#if	(defined(OSEE_API_DYNAMIC))

/* [GS]: ID */

/*
 * DMA Channel 0 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA0_IRQHandler, OSEE_CORTEX_M_DMA0_ISR_ID)

/*
 * DMA Channel 1 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA1_IRQHandler, OSEE_CORTEX_M_DMA1_ISR_ID)

/*
 * DMA Channel 2 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA2_IRQHandler, OSEE_CORTEX_M_DMA2_ISR_ID)

/*
 * DMA Channel 3 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA3_IRQHandler, OSEE_CORTEX_M_DMA3_ISR_ID)

/*
 * DMA Channel 4 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA4_IRQHandler, OSEE_CORTEX_M_DMA4_ISR_ID)

/*
 * DMA Channel 5 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA5_IRQHandler, OSEE_CORTEX_M_DMA5_ISR_ID)

/*
 * DMA Channel 6 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA6_IRQHandler, OSEE_CORTEX_M_DMA6_ISR_ID)

/*
 * DMA Channel 7 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA7_IRQHandler, OSEE_CORTEX_M_DMA7_ISR_ID)

/*
 * DMA Channel 8 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA8_IRQHandler, OSEE_CORTEX_M_DMA8_ISR_ID)

/*
 * DMA Channel 9 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA9_IRQHandler, OSEE_CORTEX_M_DMA9_ISR_ID)

/*
 * DMA Channel 10 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA10_IRQHandler, OSEE_CORTEX_M_DMA10_ISR_ID)

/*
 * DMA Channel 11 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA11_IRQHandler, OSEE_CORTEX_M_DMA11_ISR_ID)

/*
 * DMA Channel 12 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA12_IRQHandler, OSEE_CORTEX_M_DMA12_ISR_ID)

/*
 * DMA Channel 13 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA13_IRQHandler, OSEE_CORTEX_M_DMA13_ISR_ID)

/*
 * DMA Channel 14 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA14_IRQHandler, OSEE_CORTEX_M_DMA14_ISR_ID)

/*
 * DMA Channel 15 Transfer Complete interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(DMA15_IRQHandler, OSEE_CORTEX_M_DMA15_ISR_ID)

/*
 * DMA Error Channels 0-15 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	DMA_Error_IRQHandler, OSEE_CORTEX_M_DMA_ERR_ISR_ID
)

/*
 * MCM FPU Sources.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(MCM_IRQHandler, OSEE_CORTEX_M_MCM_FPU_ISR_ID)

/*
 * Flash Memory Command Complete.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(FTFC_IRQHandler, OSEE_CORTEX_M_FTFC_CMD_ISR_ID)

/*
 * Flash Memory Read Collision.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	Read_Collision_IRQHandler, OSEE_CORTEX_M_FTFC_RDC_ISR_ID
)

/*
 * PMC Low Voltage Detection.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(LVD_LVW_IRQHandler, OSEE_CORTEX_M_PMC_LVD_ISR_ID)

/*
 * Flash Memory Double Bit Fault Detection.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTFC_Fault_IRQHandler, OSEE_CORTEX_M_FTFC_FAULT_ISR_ID
)

/*
 * Watch-Dog and External Watch-Dog Monitor.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	WDOG_EWM_IRQHandler, OSEE_CORTEX_M_WDOG_EWM_ISR_ID
)

/*
 * RCM.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(RCM_IRQHandler, OSEE_CORTEX_M_RCM_ISR_ID)

/*
 * LPI2C0 Master.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C0_Master_IRQHandler, OSEE_CORTEX_M_LPI2C0_MASTER_ISR_ID
)

/*
 * LPI2C0 Slave.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C0_Slave_IRQHandler, OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_ID
)

/*
 * LPSPI0.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(LPSPI0_IRQHandler, OSEE_CORTEX_M_LPSPI0_ISR_ID)

/*
 * LPSPI1.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(LPSPI1_IRQHandler, OSEE_CORTEX_M_LPSPI1_ISR_ID)

/*
 * LPSPI2.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(LPSPI2_IRQHandler, OSEE_CORTEX_M_LPSPI2_ISR_ID)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * LPI2C1 Master.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C1_Master_IRQHandler, OSEE_CORTEX_M_LPI2C1_MASTER_ISR_ID
)

/*
 * LPI2C1 Slave.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C1_Slave_IRQHandler, OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_ID
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * LPUART0.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(LPUART0_IRQHandler, OSEE_CORTEX_M_LPUART0_ISR_ID)

/*
 * LPUART1.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPUART1_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART1_ISR_ID
)

/*
 * LPUART2.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPUART2_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART2_ISR_ID
)

/*
 * ADC0.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(ADC0_IRQHandler, OSEE_CORTEX_M_ADC0_ISR_ID)

/*
 * ADC1.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(ADC1_IRQHandler, OSEE_CORTEX_M_ADC1_ISR_ID)

/*
 * CMP0.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(CMP0_IRQHandler, OSEE_CORTEX_M_CMP0_ISR_ID)

/*
 * ERM Single Fault.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	ERM_single_fault_IRQHandler, OSEE_CORTEX_M_ERM_SINGLE_ISR_ID
)

/*
 * ERM Double Fault.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	ERM_double_fault_IRQHandler, OSEE_CORTEX_M_ERM_DOUBLE_ISR_ID
)

/*
 * RTC Alarm.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(RTC_IRQHandler, OSEE_CORTEX_M_RTC_ALARM_ISR_ID)

/*
 * RTC Seconds.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	RTC_Seconds_IRQHandler, OSEE_CORTEX_M_RTC_SECONDS_ISR_ID
)

/*
 * LPIT0 Channel 0.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch0_IRQHandler, OSEE_CORTEX_M_LPIT0_CH0_ISR_ID
)

/*
 * LPIT0 Channel 1.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch1_IRQHandler, OSEE_CORTEX_M_LPIT0_CH1_ISR_ID
)

/*
 * LPIT0 Channel 2.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch2_IRQHandler, OSEE_CORTEX_M_LPIT0_CH2_ISR_ID
)

/*
 * LPIT0 Channel 3.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch3_IRQHandler, OSEE_CORTEX_M_LPIT0_CH3_ISR_ID
)

/*
 * PDB0.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(PDB0_IRQHandler, OSEE_CORTEX_M_PDB0_ISR_ID)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * SAI1 Tx.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	SAI1_Tx_IRQHandler, OSEE_CORTEX_M_SAI1_TX_ISR_ID
)

/*
 * SAI1 Rx.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	SAI1_Rx_IRQHandler, OSEE_CORTEX_M_SAI1_RX_ISR_ID
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * SCG.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(SCG_IRQHandler, OSEE_CORTEX_M_SCG_ISR_ID)

/*
 * LPTMR0.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(LPTMR0_IRQHandler, OSEE_CORTEX_M_LPTMR0_ISR_ID)

/*
 * Port A pin detect interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(PORTA_IRQHandler, OSEE_CORTEX_M_PORTA_ISR_ID)

/*
 * Port B pin detect interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(PORTB_IRQHandler, OSEE_CORTEX_M_PORTB_ISR_ID)

/*
 * Port C pin detect interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(PORTC_IRQHandler, OSEE_CORTEX_M_PORTC_ISR_ID)

/*
 * Port D pin detect interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(PORTD_IRQHandler, OSEE_CORTEX_M_PORTD_ISR_ID)

/*
 * Port E pin detect interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(PORTE_IRQHandler, OSEE_CORTEX_M_PORTE_ISR_ID)

/*
 * Software Interrupt.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(SWI_IRQHandler, OSEE_CORTEX_M_SWI_ISR_ID)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * QSPI.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(QSPI_IRQHandler, OSEE_CORTEX_M_QSPI_ISR_ID)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * PDB1.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(PDB1_IRQHandler, OSEE_CORTEX_M_PDB1_ISR_ID)

/*
 * FlexIO.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(FLEXIO_IRQHandler, OSEE_CORTEX_M_FLEXIO_ISR_ID)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * SAI0 Tx.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	SAI0_Tx_IRQHandler, OSEE_CORTEX_M_SAI0_TX_ISR_ID
)

/*
 * SAI0 Rx.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	SAI0_Rx_IRQHandler, OSEE_CORTEX_M_SAI0_RX_ISR_ID
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * Ethernet Timer.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_TIMER_IRQHandler, OSEE_CORTEX_M_ENET_TIMER_ISR_ID
)

/*
 * Ethernet Tx.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(ENET_TX_IRQHandler, OSEE_CORTEX_M_ENET_TX_ISR_ID)

/*
 * Ethernet Rx.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(ENET_RX_IRQHandler, OSEE_CORTEX_M_ENET_RX_ISR_ID)

/*
 * Ethernet Error.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_ERR_IRQHandler, OSEE_CORTEX_M_ENET_ERR_ISR_ID
)

/*
 * Ethernet Stop.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_STOP_IRQHandler, OSEE_CORTEX_M_ENET_STOP_ISR_ID
)

/*
 * Ethernet Wake-Up.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_WAKE_IRQHandler, OSEE_CORTEX_M_ENET_WAKE_ISR_ID
)

/*
 * CAN0 OR'ed.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_ORed_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_ISR_ID
)

/*
 * CAN0 Error.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_Error_IRQHandler, OSEE_CORTEX_M_CAN0_ERR_ISR_ID
)

/*
 * CAN0 Wake-Up.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_Wake_Up_IRQHandler, OSEE_CORTEX_M_CAN0_WAKE_ISR_ID
)

/*
 * CAN0 OR'ed Channel 0 to Channel 15.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_ORed_0_15_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_ID
)

/*
 * CAN0 OR'ed Channel 16 to Channel 31.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_ORed_16_31_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_ID
)

/*
 * CAN1 OR'ed.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_ORed_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_ISR_ID
)

/*
 * CAN1 Error.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_Error_IRQHandler, OSEE_CORTEX_M_CAN1_ERR_ISR_ID
)

/*
 * CAN1 OR'ed Channel 0 to Channel 15.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_ORed_0_15_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_ID
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * CAN1 OR'ed Channel 16 to Channel 31.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_ORed_16_31_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_ID
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * CAN2 OR'ed.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_ORed_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_ISR_ID
)

/*
 * CAN2 Error.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_Error_IRQHandler, OSEE_CORTEX_M_CAN2_ERR_ISR_ID
)

/*
 * CAN2 OR'ed Channel 0 to Channel 15.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_ORed_0_15_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_ID
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * CAN2 OR'ed Channel 16 to Channel 31.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_ORed_16_31_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_ID
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * FTM0 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM0_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_ID
)

/*
 * FTM0 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM0_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_ID
)

/*
 * FTM0 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM0_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_ID
)

/*
 * FTM0 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM0_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_ID
)

/*
 * FTM0 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM0_Fault_IRQHandler, OSEE_CORTEX_M_FTM0_FAULT_ISR_ID
)

/*
 * FTM0 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM0_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_ID
)

/*
 * FTM1 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM1_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_ID
)

/*
 * FTM1 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM1_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_ID
)

/*
 * FTM1 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM1_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_ID
)

/*
 * FTM1 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM1_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_ID
)

/*
 * FTM1 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM1_Fault_IRQHandler, OSEE_CORTEX_M_FTM1_FAULT_ISR_ID
)

/*
 * FTM1 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM1_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_ID
)

/*
 * FTM2 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM2_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_ID
)

/*
 * FTM2 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM2_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_ID
)

/*
 * FTM2 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM2_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_ID
)

/*
 * FTM2 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM2_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_ID
)

/*
 * FTM2 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM2_Fault_IRQHandler, OSEE_CORTEX_M_FTM2_FAULT_ISR_ID
)

/*
 * FTM2 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM2_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_ID
)

/*
 * FTM3 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM3_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_ID
)

/*
 * FTM3 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM3_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_ID
)

/*
 * FTM3 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM3_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_ID
)

/*
 * FTM3 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM3_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_ID
)

/*
 * FTM3 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM3_Fault_IRQHandler, OSEE_CORTEX_M_FTM3_FAULT_ISR_ID
)

/*
 * FTM3 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM3_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_ID
)

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * FTM4 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM4_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_ID
)

/*
 * FTM4 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM4_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_ID
)

/*
 * FTM4 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM4_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_ID
)

/*
 * FTM4 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM4_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_ID
)

/*
 * FTM4 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM4_Fault_IRQHandler, OSEE_CORTEX_M_FTM4_FAULT_ISR_ID
)

/*
 * FTM4 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM4_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_ID
)

/*
 * FTM5 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM5_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_ID
)

/*
 * FTM5 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM5_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_ID
)

/*
 * FTM5 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM5_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_ID
)

/*
 * FTM5 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM5_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_ID
)

/*
 * FTM5 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM5_Fault_IRQHandler, OSEE_CORTEX_M_FTM5_FAULT_ISR_ID
)

/*
 * FTM5 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM5_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_ID
)

/*
 * FTM6 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM6_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_ID
)

/*
 * FTM6 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM6_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_ID
)

/*
 * FTM6 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM6_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_ID
)

/*
 * FTM6 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM6_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_ID
)

/*
 * FTM6 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM6_Fault_IRQHandler, OSEE_CORTEX_M_FTM6_FAULT_ISR_ID
)

/*
 * FTM6 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM6_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_ID
)

/*
 * FTM7 Channel 0 Channel 1 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM7_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_ID
)

/*
 * FTM7 Channel 2 Channel 3 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM7_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_ID
)

/*
 * FTM7 Channel 4 Channel 5 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM7_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_ID
)

/*
 * FTM7 Channel 6 Channel 7 interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM7_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_ID
)

/*
 * FTM7 Fault interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM7_Fault_IRQHandler, OSEE_CORTEX_M_FTM7_FAULT_ISR_ID
)

/*
 * FTM7 Overflow Reload interrupt handler
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
  FTM7_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_ID
)
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

#else  /* OSEE_API_DYNAMIC */

/* [GS]: TID */

/*
 * DMA Channel 0 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA0_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA0_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA0_IRQHandler, OSEE_CORTEX_M_DMA0_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA0_ISR) &&		\
		(OSEE_CORTEX_M_DMA0_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA0_IRQHandler, OSEE_CORTEX_M_DMA0_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA0_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA0_ISR */

/*
 * DMA Channel 1 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA1_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA1_IRQHandler, OSEE_CORTEX_M_DMA1_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA1_ISR) &&		\
		(OSEE_CORTEX_M_DMA1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA1_IRQHandler, OSEE_CORTEX_M_DMA1_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA1_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA1_ISR */

/*
 * DMA Channel 2 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA2_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA2_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA2_IRQHandler, OSEE_CORTEX_M_DMA2_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA2_ISR) &&		\
		(OSEE_CORTEX_M_DMA2_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA2_IRQHandler, OSEE_CORTEX_M_DMA2_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA2_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA2_ISR */

/*
 * DMA Channel 3 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA3_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA3_IRQHandler, OSEE_CORTEX_M_DMA3_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA3_ISR) &&		\
		(OSEE_CORTEX_M_DMA3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA3_IRQHandler, OSEE_CORTEX_M_DMA3_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA3_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA3_ISR */

/*
 * DMA Channel 4 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA4_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA4_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA4_IRQHandler, OSEE_CORTEX_M_DMA4_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA4_ISR) &&		\
		(OSEE_CORTEX_M_DMA4_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA4_IRQHandler, OSEE_CORTEX_M_DMA4_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA4_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA0_ISR */

/*
 * DMA Channel 5 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA5_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA5_IRQHandler, OSEE_CORTEX_M_DMA5_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA5_ISR) &&		\
		(OSEE_CORTEX_M_DMA5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA5_IRQHandler, OSEE_CORTEX_M_DMA5_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA5_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA5_ISR */

/*
 * DMA Channel 6 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA6_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA6_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA6_IRQHandler, OSEE_CORTEX_M_DMA6_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA6_ISR) &&		\
		(OSEE_CORTEX_M_DMA6_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA6_IRQHandler, OSEE_CORTEX_M_DMA6_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA6_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA6_ISR */

/*
 * DMA Channel 7 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA7_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA7_IRQHandler, OSEE_CORTEX_M_DMA7_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA7_ISR) &&		\
		(OSEE_CORTEX_M_DMA7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA7_IRQHandler, OSEE_CORTEX_M_DMA7_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA7_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA7_ISR */

/*
 * DMA Channel 8 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA8_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA8_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA8_IRQHandler, OSEE_CORTEX_M_DMA8_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA8_ISR) &&		\
		(OSEE_CORTEX_M_DMA8_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA8_IRQHandler, OSEE_CORTEX_M_DMA8_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA8_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA8_ISR */

/*
 * DMA Channel 9 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA9_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA9_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA9_IRQHandler, OSEE_CORTEX_M_DMA9_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA9_ISR) &&		\
		(OSEE_CORTEX_M_DMA9_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA9_IRQHandler, OSEE_CORTEX_M_DMA9_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA9_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA9_ISR */

/*
 * DMA Channel 10 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA10_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA10_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA10_IRQHandler, OSEE_CORTEX_M_DMA10_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA10_ISR) &&		\
		(OSEE_CORTEX_M_DMA10_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA10_IRQHandler, OSEE_CORTEX_M_DMA10_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA10_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA10_ISR */

/*
 * DMA Channel 11 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA11_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA11_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA11_IRQHandler, OSEE_CORTEX_M_DMA11_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA11_ISR) &&		\
		(OSEE_CORTEX_M_DMA11_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA11_IRQHandler, OSEE_CORTEX_M_DMA11_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA11_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA11_ISR */

/*
 * DMA Channel 12 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA12_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA12_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA12_IRQHandler, OSEE_CORTEX_M_DMA12_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA12_ISR) &&		\
		(OSEE_CORTEX_M_DMA12_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA12_IRQHandler, OSEE_CORTEX_M_DMA12_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA12_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA12_ISR */

/*
 * DMA Channel 13 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA13_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA13_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA13_IRQHandler, OSEE_CORTEX_M_DMA13_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA13_ISR) &&		\
		(OSEE_CORTEX_M_DMA13_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA13_IRQHandler, OSEE_CORTEX_M_DMA13_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA13_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA13_ISR */

/*
 * DMA Channel 14 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA14_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA14_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA14_IRQHandler, OSEE_CORTEX_M_DMA14_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA14_ISR) &&		\
		(OSEE_CORTEX_M_DMA14_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA14_IRQHandler, OSEE_CORTEX_M_DMA14_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA14_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA14_ISR */

/*
 * DMA Channel 15 Transfer Complete interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA15_ISR_TID) &&		\
		(OSEE_CORTEX_M_DMA15_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(DMA15_IRQHandler, OSEE_CORTEX_M_DMA15_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_DMA15_ISR) &&		\
		(OSEE_CORTEX_M_DMA15_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA15_IRQHandler, OSEE_CORTEX_M_DMA15_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA15_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA15_ISR */

/*
 * DMA Error Channels 0-15 interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_DMA_ERR_ISR_TID) &&	\
		(OSEE_CORTEX_M_DMA_ERR_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	DMA_Error_IRQHandler, OSEE_CORTEX_M_DMA_ERR_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_DMA_ERR_ISR) &&		\
		(OSEE_CORTEX_M_DMA_ERR_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DMA_Error_IRQHandler, OSEE_CORTEX_M_DMA_ERR_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DMA_Error_IRQHandler)
#endif /* OSEE_CORTEX_M_DMA_ERR_ISR */

/*
 * MCM FPU Sources.
 */
#if	(							\
		defined(OSEE_CORTEX_M_MCM_FPU_ISR_TID) &&	\
		(OSEE_CORTEX_M_MCM_FPU_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(MCM_IRQHandler, OSEE_CORTEX_M_MCM_FPU_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_MCM_FPU_ISR) &&		\
		(OSEE_CORTEX_M_MCM_FPU_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(MCM_IRQHandler, OSEE_CORTEX_M_MCM_FPU_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(MCM_IRQHandler)
#endif /* OSEE_CORTEX_M_MCM_FPU_ISR */

/*
 * Flash Memory Command Complete.
 */
#if	(							\
		defined(OSEE_CORTEX_M_FTFC_CMD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTFC_CMD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(FTFC_IRQHandler, OSEE_CORTEX_M_FTFC_CMD_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_FTFC_CMD_ISR) &&		\
		(OSEE_CORTEX_M_FTFC_CMD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(FTFC_IRQHandler, OSEE_CORTEX_M_FTFC_CMD_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTFC_IRQHandler)
#endif /* OSEE_CORTEX_M_FTFC_CMD_ISR */

/*
 * Flash Memory read Collision.
 */
#if	(							\
		defined(OSEE_CORTEX_M_FTFC_RDC_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTFC_RDC_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	Read_Collision_IRQHandler, OSEE_CORTEX_M_FTFC_RDC_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_FTFC_RDC_ISR) &&		\
		(OSEE_CORTEX_M_FTFC_RDC_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	Read_Collision_IRQHandler, OSEE_CORTEX_M_FTFC_RDC_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(Read_Collision_IRQHandler)
#endif /* OSEE_CORTEX_M_FTFC_RDC_ISR */

/*
 * PMC Low Voltage Detection.
 */
#if	(							\
		defined(OSEE_CORTEX_M_PMC_LVD_ISR_TID) &&	\
		(OSEE_CORTEX_M_PMC_LVD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LVD_LVW_IRQHandler, OSEE_CORTEX_M_PMC_LVD_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_PMC_LVD_ISR) &&		\
		(OSEE_CORTEX_M_PMC_LVD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(LVD_LVW_IRQHandler, OSEE_CORTEX_M_PMC_LVD_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LVD_LVW_IRQHandler)
#endif /* OSEE_CORTEX_M_PMC_LVD_ISR */

/*
 * Flash Memory Double Bit Fault Detection.
 */
#if	(							\
		defined(OSEE_CORTEX_M_FTFC_FAULT_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTFC_FAULT_ISR_CAT == 2U)	\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTFC_Fault_IRQHandler, OSEE_CORTEX_M_FTFC_FAULT_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_FTFC_FAULT_ISR) &&	\
		(OSEE_CORTEX_M_FTFC_FAULT_ISR_CAT == 1U)	\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTFC_Fault_IRQHandler, OSEE_CORTEX_M_FTFC_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTFC_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTFC_FAULT_ISR */

/*
 * Watch-Dog and External Watch-Dog Monitor.
 */
#if	(							\
		defined(OSEE_CORTEX_M_WDOG_EWM_ISR_TID) &&	\
		(OSEE_CORTEX_M_WDOG_EWM_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	WDOG_EWM_IRQHandler, OSEE_CORTEX_M_WDOG_EWM_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_WDOG_EWM_ISR) &&		\
		(OSEE_CORTEX_M_WDOG_EWM_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(WDOG_EWM_IRQHandler, OSEE_CORTEX_M_WDOG_EWM_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(WDOG_EWM_IRQHandler)
#endif /* OSEE_CORTEX_M_WDOG_EWM_ISR */

/*
 * RCM.
 */
#if	(							\
		defined(OSEE_CORTEX_M_RCM_ISR_TID) &&		\
		(OSEE_CORTEX_M_RCM_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	RCM_IRQHandler, OSEE_CORTEX_M_RCM_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_RCM_ISR) &&		\
		(OSEE_CORTEX_M_RCM_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(RCM_IRQHandler, OSEE_CORTEX_M_RCM_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(RCM_IRQHandler)
#endif /* OSEE_CORTEX_M_RCM_ISR */

/*
 * LPI2C0 Master.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPI2C0_MASTER_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPI2C0_MASTER_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C0_Master_IRQHandler, OSEE_CORTEX_M_LPI2C0_MASTER_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPI2C0_MASTER_ISR) &&		\
		(OSEE_CORTEX_M_LPI2C0_MASTER_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPI2C0_Master_IRQHandler, OSEE_CORTEX_M_LPI2C0_MASTER_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPI2C0_Master_IRQHandler)
#endif /* OSEE_CORTEX_M_LPI2C0_MASTER_ISR */

/*
 * LPI2C0 Slave.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C0_Slave_IRQHandler, OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPI2C0_SLAVE_ISR) &&		\
		(OSEE_CORTEX_M_LPI2C0_SLAVE_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPI2C0_Slave_IRQHandler, OSEE_CORTEX_M_LPI2C0_SLAVE_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPI2C0_Slave_IRQHandler)
#endif /* OSEE_CORTEX_M_LPI2C0_SLAVE_ISR */

/*
 * LPSPI0.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPSPI0_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPSPI0_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(LPSPI0_IRQHandler, OSEE_CORTEX_M_LPSPI0_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_LPSPI0_ISR) &&			\
		(OSEE_CORTEX_M_LPSPI0_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(LPSPI0_IRQHandler, OSEE_CORTEX_M_LPSPI0_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPSPI0_IRQHandler)
#endif /* OSEE_CORTEX_M_LPSPI0_ISR */

/*
 * LPSPI1.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPSPI1_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPSPI1_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(LPSPI1_IRQHandler, OSEE_CORTEX_M_LPSPI1_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_LPSPI1_ISR) &&			\
		(OSEE_CORTEX_M_LPSPI1_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(LPSPI1_IRQHandler, OSEE_CORTEX_M_LPSPI1_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPSPI1_IRQHandler)
#endif /* OSEE_CORTEX_M_LPSPI1_ISR */

/*
 * LPSPI2.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPSPI2_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPSPI2_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(LPSPI2_IRQHandler, OSEE_CORTEX_M_LPSPI2_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_LPSPI2_ISR) &&			\
		(OSEE_CORTEX_M_LPSPI2_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(LPSPI2_IRQHandler, OSEE_CORTEX_M_LPSPI2_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPSPI2_IRQHandler)
#endif /* OSEE_CORTEX_M_LPSPI2_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * LPI2C1 Master.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPI2C1_MASTER_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPI2C1_MASTER_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C1_Master_IRQHandler, OSEE_CORTEX_M_LPI2C1_MASTER_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPI2C1_MASTER_ISR) &&		\
		(OSEE_CORTEX_M_LPI2C1_MASTER_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPI2C1_Master_IRQHandler, OSEE_CORTEX_M_LPI2C1_MASTER_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPI2C1_Master_IRQHandler)
#endif /* OSEE_CORTEX_M_LPI2C1_MASTER_ISR */

/*
 * LPI2C1 Slave.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPI2C1_Slave_IRQHandler, OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPI2C1_SLAVE_ISR) &&		\
		(OSEE_CORTEX_M_LPI2C1_SLAVE_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPI2C1_Slave_IRQHandler, OSEE_CORTEX_M_LPI2C1_SLAVE_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPI2C1_Slave_IRQHandler)
#endif /* OSEE_CORTEX_M_LPI2C1_SLAVE_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * LPUART0.
 */
#if	(							\
		defined(OSEE_CORTEX_M_LPUART0_ISR_TID) &&	\
		(OSEE_CORTEX_M_LPUART0_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPUART0_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART0_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_LPUART0_ISR) &&		\
		(OSEE_CORTEX_M_LPUART0_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPUART0_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART0_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPUART0_RxTx_IRQHandler)
#endif /* OSEE_CORTEX_M_LPUART0_ISR */

/*
 * LPUART1.
 */
#if	(							\
		defined(OSEE_CORTEX_M_LPUART1_ISR_TID) &&	\
		(OSEE_CORTEX_M_LPUART1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPUART1_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART1_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_LPUART1_ISR) &&		\
		(OSEE_CORTEX_M_LPUART1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPUART1_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPUART1_RxTx_IRQHandler)
#endif /* OSEE_CORTEX_M_LPUART1_ISR */

/*
 * LPUART2.
 */
#if	(							\
		defined(OSEE_CORTEX_M_LPUART2_ISR_TID) &&	\
		(OSEE_CORTEX_M_LPUART2_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPUART2_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART2_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_LPUART2_ISR) &&		\
		(OSEE_CORTEX_M_LPUART2_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPUART2_RxTx_IRQHandler, OSEE_CORTEX_M_LPUART2_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPUART2_RxTx_IRQHandler)
#endif /* OSEE_CORTEX_M_LPUART2_ISR */

/*
 * ADC0.
 */
#if	(							\
		defined(OSEE_CORTEX_M_ADC0_ISR_TID) &&		\
		(OSEE_CORTEX_M_ADC0_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(ADC0_IRQHandler, OSEE_CORTEX_M_ADC0_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_ADC0_ISR) &&		\
		(OSEE_CORTEX_M_ADC0_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(ADC0_IRQHandler, OSEE_CORTEX_M_ADC0_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ADC0_IRQHandler)
#endif /* OSEE_CORTEX_M_ADC0_ISR */

/*
 * ADC1.
 */
#if	(							\
		defined(OSEE_CORTEX_M_ADC1_ISR_TID) &&	\
		(OSEE_CORTEX_M_ADC1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(ADC1_IRQHandler, OSEE_CORTEX_M_ADC1_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_ADC1_ISR) &&		\
		(OSEE_CORTEX_M_ADC1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(ADC1_IRQHandler, OSEE_CORTEX_M_ADC1_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ADC1_IRQHandler)
#endif /* OSEE_CORTEX_M_ADC1_ISR */

/*
 * CMP0.
 */
#if	(							\
		defined(OSEE_CORTEX_M_CMP0_ISR_TID) &&		\
		(OSEE_CORTEX_M_CMP0_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(CMP0_IRQHandler, OSEE_CORTEX_M_CMP0_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_CMP0_ISR) &&		\
		(OSEE_CORTEX_M_CMP0_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(CMP0_IRQHandler, OSEE_CORTEX_M_CMP0_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CMP0_IRQHandler)
#endif /* OSEE_CORTEX_M_CMP0_ISR */

/*
 * ERM Single Fault.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ERM_SINGLE_ISR_TID) &&		\
		(OSEE_CORTEX_M_ERM_SINGLE_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ERM_single_fault_IRQHandler, OSEE_CORTEX_M_ERM_SINGLE_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ERM_SINGLE_ISR) &&		\
		(OSEE_CORTEX_M_ERM_SINGLE_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ERM_single_fault_IRQHandler, OSEE_CORTEX_M_ERM_SINGLE_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ERM_single_fault_IRQHandler)
#endif /* OSEE_CORTEX_M_ERM_SINGLE_ISR */

/*
 * ERM Double Fault.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ERM_DOUBLE_ISR_TID) &&		\
		(OSEE_CORTEX_M_ERM_DOUBLE_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ERM_double_fault_IRQHandler, OSEE_CORTEX_M_ERM_DOUBLE_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ERM_DOUBLE_ISR) &&		\
		(OSEE_CORTEX_M_ERM_DOUBLE_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ERM_double_fault_IRQHandler, OSEE_CORTEX_M_ERM_DOUBLE_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ERM_double_fault_IRQHandler)
#endif /* OSEE_CORTEX_M_ERM_DOUBLE_ISR */

/*
 * RTC Alarm.
 */
#if	(								\
		defined(OSEE_CORTEX_M_RTC_ALARM_ISR_TID) &&		\
		(OSEE_CORTEX_M_RTC_ALARM_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(RTC_IRQHandler, OSEE_CORTEX_M_RTC_ALARM_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_RTC_ALARM_ISR) &&			\
		(OSEE_CORTEX_M_RTC_ALARM_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(RTC_IRQHandler, OSEE_CORTEX_M_RTC_ALARM_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(RTC_IRQHandler)
#endif /* OSEE_CORTEX_M_RTC_ALARM_ISR */

/*
 * RTC Seconds.
 */
#if	(								\
		defined(OSEE_CORTEX_M_RTC_SECONDS_ISR_TID) &&		\
		(OSEE_CORTEX_M_RTC_SECONDS_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	RTC_Seconds_IRQHandler, OSEE_CORTEX_M_RTC_SECONDS_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_RTC_SECONDS_ISR) &&		\
		(OSEE_CORTEX_M_RTC_SECONDS_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	RTC_Seconds_IRQHandler, OSEE_CORTEX_M_RTC_SECONDS_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(RTC_Seconds_IRQHandler)
#endif /* OSEE_CORTEX_M_RTC_SECONDS_ISR */

/*
 * LPIT0 Channel 0.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPIT0_CH0_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPIT0_CH0_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch0_IRQHandler, OSEE_CORTEX_M_LPIT0_CH0_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPIT0_CH0_ISR) &&			\
		(OSEE_CORTEX_M_LPIT0_CH0_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPIT0_Ch0_IRQHandler, OSEE_CORTEX_M_LPIT0_CH0_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPIT0_Ch0_IRQHandler)
#endif /* OSEE_CORTEX_M_LPIT0_CH0_ISR */

/*
 * LPIT0 Channel 1.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPIT0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPIT0_CH1_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch1_IRQHandler, OSEE_CORTEX_M_LPIT0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPIT0_CH1_ISR) &&			\
		(OSEE_CORTEX_M_LPIT0_CH1_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPIT0_Ch1_IRQHandler, OSEE_CORTEX_M_LPIT0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPIT0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_LPIT0_CH1_ISR */

/*
 * LPIT0 Channel 2.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPIT0_CH2_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPIT0_CH2_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch2_IRQHandler, OSEE_CORTEX_M_LPIT0_CH2_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPIT0_CH2_ISR) &&			\
		(OSEE_CORTEX_M_LPIT0_CH2_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPIT0_Ch2_IRQHandler, OSEE_CORTEX_M_LPIT0_CH2_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPIT0_Ch2_IRQHandler)
#endif /* OSEE_CORTEX_M_LPIT0_CH2_ISR */

/*
 * LPIT0 Channel 3.
 */
#if	(								\
		defined(OSEE_CORTEX_M_LPIT0_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_LPIT0_CH3_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPIT0_Ch3_IRQHandler, OSEE_CORTEX_M_LPIT0_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_LPIT0_CH3_ISR) &&			\
		(OSEE_CORTEX_M_LPIT0_CH3_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPIT0_Ch3_IRQHandler, OSEE_CORTEX_M_LPIT0_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPIT0_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_LPIT0_CH3_ISR */

/*
 * PDB0.
 */
#if	(								\
		defined(OSEE_CORTEX_M_PDB0_ISR_TID) &&			\
		(OSEE_CORTEX_M_PDB0_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(PDB0_IRQHandler, OSEE_CORTEX_M_PDB0_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_PDB0_ISR) &&			\
		(OSEE_CORTEX_M_PDB0_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(PDB0_IRQHandler, OSEE_CORTEX_M_PDB0_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(PDB0_IRQHandler)
#endif /* OSEE_CORTEX_M_PDB0_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * SAI1 Tx.
 */
#if	(								\
		defined(OSEE_CORTEX_M_SAI1_TX_ISR_TID) &&		\
		(OSEE_CORTEX_M_SAI1_TX_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(SAI1_Tx_IRQHandler, OSEE_CORTEX_M_SAI1_TX_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_SAI1_TX_ISR) &&			\
		(OSEE_CORTEX_M_SAI1_TX_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(SAI1_Tx_IRQHandler, OSEE_CORTEX_M_SAI1_TX_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(SAI1_Tx_IRQHandler)
#endif /* OSEE_CORTEX_M_SAI1_TX_ISR */

/*
 * SAI1 Rx.
 */
#if	(								\
		defined(OSEE_CORTEX_M_SAI1_RX_ISR_TID) &&		\
		(OSEE_CORTEX_M_SAI1_RX_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(SAI1_Rx_IRQHandler, OSEE_CORTEX_M_SAI1_RX_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_SAI1_RX_ISR) &&			\
		(OSEE_CORTEX_M_SAI1_RX_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(SAI1_Rx_IRQHandler, OSEE_CORTEX_M_SAI1_RX_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(SAI1_Rx_IRQHandler)
#endif /* OSEE_CORTEX_M_SAI1_RX_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * SCG.
 */
#if	(								\
		defined(OSEE_CORTEX_M_SCG_ISR_TID) &&			\
		(OSEE_CORTEX_M_SCG_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(SCG_IRQHandler, OSEE_CORTEX_M_SCG_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_SCG_ISR) &&			\
		(OSEE_CORTEX_M_SCG_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(SCG_IRQHandler, OSEE_CORTEX_M_SCG_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(SCG_IRQHandler)
#endif /* OSEE_CORTEX_M_SCG_ISR */

/*
 * LPTMR0.
 */
#if	(							\
		defined(OSEE_CORTEX_M_LPTMR0_ISR_TID) &&	\
		(OSEE_CORTEX_M_LPTMR0_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	LPTMR0_IRQHandler, OSEE_CORTEX_M_LPTMR0_ISR_TID
)
#elif (								\
		defined(OSEE_CORTEX_M_LPTMR0_ISR) &&		\
		(OSEE_CORTEX_M_LPTMR0_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	LPTMR0_IRQHandler, OSEE_CORTEX_M_LPTMR0_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(LPTMR0_IRQHandler)
#endif /* OSEE_CORTEX_M_LPTMR0_ISR */

/*
 * Port A pin detect interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_PORTA_ISR_TID) &&		\
		(OSEE_CORTEX_M_PORTA_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(PORTA_IRQHandler, OSEE_CORTEX_M_PORTA_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_PORTA_ISR) &&		\
		(OSEE_CORTEX_M_PORTA_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(PORTA_IRQHandler, OSEE_CORTEX_M_PORTA_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(PORTA_IRQHandler)
#endif /* OSEE_CORTEX_M_PORTA_ISR */

/*
 * Port B pin detect interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_PORTB_ISR_TID) &&		\
		(OSEE_CORTEX_M_PORTB_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(PORTB_IRQHandler, OSEE_CORTEX_M_PORTB_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_PORTB_ISR) &&		\
		(OSEE_CORTEX_M_PORTB_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(PORTB_IRQHandler, OSEE_CORTEX_M_PORTB_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(PORTB_IRQHandler)
#endif /* OSEE_CORTEX_M_PORTB_ISR */

/*
 * Port C pin detect interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_PORTC_ISR_TID) &&		\
		(OSEE_CORTEX_M_PORTC_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(PORTC_IRQHandler, OSEE_CORTEX_M_PORTC_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_PORTC_ISR) &&		\
		(OSEE_CORTEX_M_PORTC_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(PORTC_IRQHandler, OSEE_CORTEX_M_PORTC_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(PORTC_IRQHandler)
#endif /* OSEE_CORTEX_M_PORTC_ISR */

/*
 * Port D pin detect interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_PORTD_ISR_TID) &&		\
		(OSEE_CORTEX_M_PORTD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(PORTD_IRQHandler, OSEE_CORTEX_M_PORTD_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_PORTD_ISR) &&		\
		(OSEE_CORTEX_M_PORTD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(PORTD_IRQHandler, OSEE_CORTEX_M_PORTD_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(PORTD_IRQHandler)
#endif /* OSEE_CORTEX_M_PORTD_ISR */

/*
 * Port E pin detect interrupt handler
 */
#if	(							\
		defined(OSEE_CORTEX_M_PORTE_ISR_TID) &&		\
		(OSEE_CORTEX_M_PORTE_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(PORTE_IRQHandler, OSEE_CORTEX_M_PORTE_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_PORTE_ISR) &&		\
		(OSEE_CORTEX_M_PORTE_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(PORTE_IRQHandler, OSEE_CORTEX_M_PORTE_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(PORTE_IRQHandler)
#endif /* OSEE_CORTEX_M_PORTE_ISR */

/*
 * Software Interrupt.
 */
#if	(							\
		defined(OSEE_CORTEX_M_SWI_ISR_TID) &&		\
		(OSEE_CORTEX_M_SWI_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(SWI_IRQHandler, OSEE_CORTEX_M_SWI_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_SWI_ISR) &&		\
		(OSEE_CORTEX_M_SWI_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(SWI_IRQHandler, OSEE_CORTEX_M_SWI_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(SWI_IRQHandler)
#endif /* OSEE_CORTEX_M_SWI_ISR */

/*
 * QSPI.
 */
#if	(							\
		defined(OSEE_CORTEX_M_QSPI_ISR_TID) &&		\
		(OSEE_CORTEX_M_QSPI_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(QSPI_IRQHandler, OSEE_CORTEX_M_QSPI_ISR_TID)
#elif (								\
		defined(OSEE_CORTEX_M_QSPI_ISR) &&		\
		(OSEE_CORTEX_M_QSPI_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(QSPI_IRQHandler, OSEE_CORTEX_M_QSPI_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(QSPI_IRQHandler)
#endif /* OSEE_CORTEX_M_QSPI_ISR */

/*
 * PDB1.
 */
#if	(								\
		defined(OSEE_CORTEX_M_PDB1_ISR_TID) &&			\
		(OSEE_CORTEX_M_PDB1_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(PDB1_IRQHandler, OSEE_CORTEX_M_PDB1_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_PDB1_ISR) &&			\
		(OSEE_CORTEX_M_PDB1_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(PDB1_IRQHandler, OSEE_CORTEX_M_PDB1_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(PDB1_IRQHandler)
#endif /* OSEE_CORTEX_M_PDB1_ISR */

/*
 * FlexIO.
 */
#if	(								\
		defined(OSEE_CORTEX_M_FLEXIO_ISR_TID) &&		\
		(OSEE_CORTEX_M_FLEXIO_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(FLEXIO_IRQHandler, OSEE_CORTEX_M_FLEXIO_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_FLEXIO_ISR) &&			\
		(OSEE_CORTEX_M_FLEXIO_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(FLEXIO_IRQHandler, OSEE_CORTEX_M_FLEXIO_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FLEXIO_IRQHandler)
#endif /* OSEE_CORTEX_M_FLEXIO_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * SAI0 Tx.
 */
#if	(								\
		defined(OSEE_CORTEX_M_SAI0_TX_ISR_TID) &&		\
		(OSEE_CORTEX_M_SAI0_TX_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(SAI0_Tx_IRQHandler, OSEE_CORTEX_M_SAI0_TX_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_SAI0_TX_ISR) &&			\
		(OSEE_CORTEX_M_SAI0_TX_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(SAI0_Tx_IRQHandler, OSEE_CORTEX_M_SAI0_TX_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(SAI0_Tx_IRQHandler)
#endif /* OSEE_CORTEX_M_SAI0_TX_ISR */

/*
 * SAI0 Rx.
 */
#if	(								\
		defined(OSEE_CORTEX_M_SAI0_RX_ISR_TID) &&		\
		(OSEE_CORTEX_M_SAI0_RX_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(SAI0_Rx_IRQHandler, OSEE_CORTEX_M_SAI0_RX_ISR_TID)
#elif (									\
		defined(OSEE_CORTEX_M_SAI0_RX_ISR) &&			\
		(OSEE_CORTEX_M_SAI0_RX_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(SAI0_Rx_IRQHandler, OSEE_CORTEX_M_SAI0_RX_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(SAI0_Rx_IRQHandler)
#endif /* OSEE_CORTEX_M_SAI0_RX_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * Ethernet Timer.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ENET_TIMER_ISR_TID) &&		\
		(OSEE_CORTEX_M_ENET_TIMER_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_TIMER_IRQHandler, OSEE_CORTEX_M_ENET_TIMER_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ENET_TIMER_ISR) &&		\
		(OSEE_CORTEX_M_ENET_TIMER_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ENET_TIMER_IRQHandler, OSEE_CORTEX_M_ENET_TIMER_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ENET_TIMER_IRQHandler)
#endif /* OSEE_CORTEX_M_ENET_TIMER_ISR */

/*
 * Ethernet Tx.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ENET_TX_ISR_TID) &&		\
		(OSEE_CORTEX_M_ENET_TX_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_TX_IRQHandler, OSEE_CORTEX_M_ENET_TX_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ENET_TX_ISR) &&			\
		(OSEE_CORTEX_M_ENET_TX_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ENET_TX_IRQHandler, OSEE_CORTEX_M_ENET_TX_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ENET_TX_IRQHandler)
#endif /* OSEE_CORTEX_M_ENET_TX_ISR */

/*
 * Ethernet Rx.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ENET_RX_ISR_TID) &&		\
		(OSEE_CORTEX_M_ENET_RX_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_RX_IRQHandler, OSEE_CORTEX_M_ENET_RX_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ENET_RX_ISR) &&			\
		(OSEE_CORTEX_M_ENET_RX_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ENET_RX_IRQHandler, OSEE_CORTEX_M_ENET_RX_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ENET_RX_IRQHandler)
#endif /* OSEE_CORTEX_M_ENET_RX_ISR */

/*
 * Ethernet Error.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ENET_ERR_ISR_TID) &&		\
		(OSEE_CORTEX_M_ENET_ERR_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_ERR_IRQHandler, OSEE_CORTEX_M_ENET_ERR_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ENET_ERR_ISR) &&			\
		(OSEE_CORTEX_M_ENET_ERR_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ENET_ERR_IRQHandler, OSEE_CORTEX_M_ENET_ERR_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ENET_ERR_IRQHandler)
#endif /* OSEE_CORTEX_M_ENET_ERR_ISR */

/*
 * Ethernet Stop.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ENET_STOP_ISR_TID) &&		\
		(OSEE_CORTEX_M_ENET_STOP_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_STOP_IRQHandler, OSEE_CORTEX_M_ENET_STOP_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ENET_STOP_ISR) &&			\
		(OSEE_CORTEX_M_ENET_STOP_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ENET_STOP_IRQHandler, OSEE_CORTEX_M_ENET_STOP_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ENET_STOP_IRQHandler)
#endif /* OSEE_CORTEX_M_ENET_STOP_ISR */

/*
 * Ethernet Wake-Up.
 */
#if	(								\
		defined(OSEE_CORTEX_M_ENET_WAKE_ISR_TID) &&		\
		(OSEE_CORTEX_M_ENET_WAKE_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	ENET_WAKE_IRQHandler, OSEE_CORTEX_M_ENET_WAKE_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_ENET_WAKE_ISR) &&			\
		(OSEE_CORTEX_M_ENET_WAKE_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	ENET_WAKE_IRQHandler, OSEE_CORTEX_M_ENET_WAKE_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(ENET_WAKE_IRQHandler)
#endif /* OSEE_CORTEX_M_ENET_WAKE_ISR */

/*
 * CAN0 OR'ed
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN0_ORED_ISR_TID) &&		\
		(OSEE_CORTEX_M_CAN0_ORED_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_ORed_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN0_ORED_ISR) &&			\
		(OSEE_CORTEX_M_CAN0_ORED_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN0_ORed_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN0_ORed_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN0_ORED_ISR */

/*
 * CAN0 Error.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN0_ERR_ISR_TID) &&		\
		(OSEE_CORTEX_M_CAN0_ERR_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_Error_IRQHandler, OSEE_CORTEX_M_CAN0_ERR_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN0_ERR_ISR) &&			\
		(OSEE_CORTEX_M_CAN0_ERR_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN0_Error_IRQHandler, OSEE_CORTEX_M_CAN0_ERR_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN0_Error_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN0_ERR_ISR */

/*
 * CAN0 Wake-Up.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN0_WAKE_ISR_TID) &&		\
		(OSEE_CORTEX_M_CAN0_WAKE_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_Wake_Up_IRQHandler, OSEE_CORTEX_M_CAN0_WAKE_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN0_WAKE_ISR) &&			\
		(OSEE_CORTEX_M_CAN0_WAKE_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN0_Wake_Up_IRQHandler, OSEE_CORTEX_M_CAN0_WAKE_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN0_Wake_Up_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN0_WAKE_ISR */

/*
 * CAN0 OR'ed Channel 0 to Channel 15.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_TID) &&	\
		(OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_ORed_0_15_MB_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN0_ORED_0_15_ISR) &&		\
		(OSEE_CORTEX_M_CAN0_ORED_0_15_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN0_ORed_0_15_MB_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_0_15_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN0_ORed_0_15_MB_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN0_ORED_0_15_ISR */

/*
 * CAN0 OR'ed Channel 16 to Channel 31.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_TID) &&	\
		(OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN0_ORed_16_31_MB_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN0_ORED_16_31_ISR) &&		\
		(OSEE_CORTEX_M_CAN0_ORED_16_31_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN0_ORed_16_31_MB_IRQHandler, OSEE_CORTEX_M_CAN0_ORED_16_31_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN0_ORed_16_31_MB_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN0_ORED_16_31_ISR */

/*
 * CAN1 OR'ed
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN1_ORED_ISR_TID) &&		\
		(OSEE_CORTEX_M_CAN1_ORED_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_ORed_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN1_ORED_ISR) &&			\
		(OSEE_CORTEX_M_CAN1_ORED_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN1_ORed_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN1_ORed_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN1_ORED_ISR */

/*
 * CAN1 Error.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN1_ERR_ISR_TID) &&		\
		(OSEE_CORTEX_M_CAN1_ERR_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_Error_IRQHandler, OSEE_CORTEX_M_CAN1_ERR_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN1_ERR_ISR) &&			\
		(OSEE_CORTEX_M_CAN1_ERR_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN1_Error_IRQHandler, OSEE_CORTEX_M_CAN1_ERR_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN1_Error_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN1_ERR_ISR */

/*
 * CAN1 OR'ed Channel 0 to Channel 15.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_TID) &&	\
		(OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_ORed_0_15_MB_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN1_ORED_0_15_ISR) &&		\
		(OSEE_CORTEX_M_CAN1_ORED_0_15_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN1_ORed_0_15_MB_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_0_15_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN1_ORed_0_15_MB_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN1_ORED_0_15_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * CAN1 OR'ed Channel 16 to Channel 31.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_TID) &&	\
		(OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN1_ORed_16_31_MB_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN1_ORED_16_31_ISR) &&		\
		(OSEE_CORTEX_M_CAN1_ORED_16_31_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN1_ORed_16_31_MB_IRQHandler, OSEE_CORTEX_M_CAN1_ORED_16_31_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN1_ORed_16_31_MB_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN1_ORED_16_31_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * CAN2 OR'ed
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN2_ORED_ISR_TID) &&		\
		(OSEE_CORTEX_M_CAN2_ORED_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_ORed_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN2_ORED_ISR) &&			\
		(OSEE_CORTEX_M_CAN2_ORED_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN2_ORed_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN2_ORed_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN2_ORED_ISR */

/*
 * CAN2 Error.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN2_ERR_ISR_TID) &&		\
		(OSEE_CORTEX_M_CAN2_ERR_ISR_CAT == 2U)			\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_Error_IRQHandler, OSEE_CORTEX_M_CAN2_ERR_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN2_ERR_ISR) &&			\
		(OSEE_CORTEX_M_CAN2_ERR_ISR_CAT == 1U)			\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN2_Error_IRQHandler, OSEE_CORTEX_M_CAN2_ERR_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN2_Error_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN2_ERR_ISR */

/*
 * CAN2 OR'ed Channel 0 to Channel 15.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_TID) &&	\
		(OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_ORed_0_15_MB_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN2_ORED_0_15_ISR) &&		\
		(OSEE_CORTEX_M_CAN2_ORED_0_15_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN2_ORed_0_15_MB_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_0_15_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN2_ORed_0_15_MB_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN2_ORED_0_15_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * CAN2 OR'ed Channel 16 to Channel 31.
 */
#if	(								\
		defined(OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_TID) &&	\
		(OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	CAN2_ORed_16_31_MB_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_CAN2_ORED_16_31_ISR) &&		\
		(OSEE_CORTEX_M_CAN2_ORED_16_31_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	CAN2_ORed_16_31_MB_IRQHandler, OSEE_CORTEX_M_CAN2_ORED_16_31_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(CAN2_ORed_16_31_MB_IRQHandler)
#endif /* OSEE_CORTEX_M_CAN2_ORED_16_31_ISR */
#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

/*
 * FTM0 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM0_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM0_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM0_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM0_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM0_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM0_CH0_CH1_ISR */

/*
 * FTM0 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM0_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM0_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM0_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM0_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM0_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM0_CH2_CH3_ISR */

/*
 * FTM0 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM0_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM0_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM0_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM0_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM0_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM0_CH4_CH5_ISR */

/*
 * FTM0 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM0_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM0_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM0_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM0_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM0_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM0_CH6_CH7_ISR */

/*
 * FTM0 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM0_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM0_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM0_Fault_IRQHandler, OSEE_CORTEX_M_FTM0_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM0_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM0_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM0_Fault_IRQHandler, OSEE_CORTEX_M_FTM0_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM0_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM0_FAULT_ISR */

/*
 * FTM0 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM0_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM0_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM0_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM0_OVF_RELOAD_ISR */

/*
 * FTM1 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM1_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM1_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM1_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM1_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM1_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM1_CH0_CH1_ISR */

/*
 * FTM1 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM1_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM1_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM1_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM1_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM1_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM1_CH2_CH3_ISR */

/*
 * FTM1 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM1_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM1_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM1_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM1_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM1_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM1_CH4_CH5_ISR */

/*
 * FTM1 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM1_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM1_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM1_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM1_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM1_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM1_CH6_CH7_ISR */

/*
 * FTM1 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM1_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM1_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM1_Fault_IRQHandler, OSEE_CORTEX_M_FTM1_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM1_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM1_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM1_Fault_IRQHandler, OSEE_CORTEX_M_FTM1_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM1_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM1_FAULT_ISR */

/*
 * FTM1 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM1_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM1_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM1_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM1_OVF_RELOAD_ISR */

/*
 * FTM2 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM2_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM2_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM2_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM2_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM2_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM2_CH0_CH1_ISR */

/*
 * FTM2 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM2_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM2_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM2_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM2_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM2_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM2_CH2_CH3_ISR */

/*
 * FTM2 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM2_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM2_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM2_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM2_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM2_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM2_CH4_CH5_ISR */

/*
 * FTM2 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM2_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM2_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM2_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM2_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM2_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM2_CH6_CH7_ISR */

/*
 * FTM2 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM2_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM2_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM2_Fault_IRQHandler, OSEE_CORTEX_M_FTM2_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM2_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM2_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM2_Fault_IRQHandler, OSEE_CORTEX_M_FTM2_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM2_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM2_FAULT_ISR */

/*
 * FTM2 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM2_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM2_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM2_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM2_OVF_RELOAD_ISR */

/*
 * FTM3 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM3_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM3_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM3_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM3_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM3_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM3_CH0_CH1_ISR */

/*
 * FTM3 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM3_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM3_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM3_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM3_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM3_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM3_CH2_CH3_ISR */

/*
 * FTM3 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM3_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM3_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM3_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM3_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM3_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM3_CH4_CH5_ISR */

/*
 * FTM3 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM3_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM3_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM3_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM3_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM3_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM3_CH6_CH7_ISR */

/*
 * FTM3 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM3_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM3_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM3_Fault_IRQHandler, OSEE_CORTEX_M_FTM3_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM3_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM3_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM3_Fault_IRQHandler, OSEE_CORTEX_M_FTM3_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM3_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM3_FAULT_ISR */

/*
 * FTM3 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM3_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM3_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM3_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM3_OVF_RELOAD_ISR */

#ifdef	OS_EE_ARCH_CORTEX_M_S32K148
/*
 * FTM4 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM4_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM4_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM4_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM4_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM4_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM4_CH0_CH1_ISR */

/*
 * FTM4 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM4_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM4_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM4_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM4_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM4_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM4_CH2_CH3_ISR */

/*
 * FTM4 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM4_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM4_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM4_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM4_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM4_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM4_CH4_CH5_ISR */

/*
 * FTM4 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM4_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM4_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM4_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM4_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM4_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM4_CH6_CH7_ISR */

/*
 * FTM4 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM4_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM4_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM4_Fault_IRQHandler, OSEE_CORTEX_M_FTM4_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM4_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM4_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM4_Fault_IRQHandler, OSEE_CORTEX_M_FTM4_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM4_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM4_FAULT_ISR */

/*
 * FTM4 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM4_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM4_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM4_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM4_OVF_RELOAD_ISR */

/*
 * FTM5 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM5_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM5_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM5_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM5_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM5_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM5_CH0_CH1_ISR */

/*
 * FTM5 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM5_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM5_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM5_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM5_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM5_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM5_CH2_CH3_ISR */

/*
 * FTM5 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM5_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM5_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM5_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM5_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM5_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM5_CH4_CH5_ISR */

/*
 * FTM5 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM5_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM5_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM5_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM5_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM5_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM5_CH6_CH7_ISR */

/*
 * FTM5 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM5_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM5_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM5_Fault_IRQHandler, OSEE_CORTEX_M_FTM5_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM5_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM5_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM5_Fault_IRQHandler, OSEE_CORTEX_M_FTM5_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM5_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM5_FAULT_ISR */

/*
 * FTM5 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM5_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM5_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM5_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM5_OVF_RELOAD_ISR */

/*
 * FTM6 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM6_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM6_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM6_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM6_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM6_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM6_CH0_CH1_ISR */

/*
 * FTM6 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM6_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM6_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM6_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM6_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM6_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM6_CH2_CH3_ISR */

/*
 * FTM6 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM6_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM6_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM6_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM6_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM6_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM6_CH4_CH5_ISR */

/*
 * FTM6 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM6_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM6_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM6_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM6_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM6_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM6_CH6_CH7_ISR */

/*
 * FTM6 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM6_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM6_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM6_Fault_IRQHandler, OSEE_CORTEX_M_FTM6_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM6_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM6_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM6_Fault_IRQHandler, OSEE_CORTEX_M_FTM6_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM6_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM6_FAULT_ISR */

/*
 * FTM6 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM6_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM6_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM6_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM6_OVF_RELOAD_ISR */

/*
 * FTM7 Channel 0 Channel 1 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM7_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR) &&		\
		(OSEE_CORTEX_M_FTM7_CH0_CH1_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM7_Ch0_Ch1_IRQHandler, OSEE_CORTEX_M_FTM7_CH0_CH1_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM7_Ch0_Ch1_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM7_CH0_CH1_ISR */

/*
 * FTM7 Channel 2 Channel 3 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM7_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR) &&		\
		(OSEE_CORTEX_M_FTM7_CH2_CH3_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM7_Ch2_Ch3_IRQHandler, OSEE_CORTEX_M_FTM7_CH2_CH3_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM7_Ch2_Ch3_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM7_CH2_CH3_ISR */

/*
 * FTM7 Channel 4 Channel 5 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM7_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR) &&		\
		(OSEE_CORTEX_M_FTM7_CH4_CH5_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM7_Ch4_Ch5_IRQHandler, OSEE_CORTEX_M_FTM7_CH4_CH5_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM7_Ch4_Ch5_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM7_CH4_CH5_ISR */

/*
 * FTM7 Channel 6 Channel 7 interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM7_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR) &&		\
		(OSEE_CORTEX_M_FTM7_CH6_CH7_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM7_Ch6_Ch7_IRQHandler, OSEE_CORTEX_M_FTM7_CH6_CH7_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM7_Ch6_Ch7_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM7_CH6_CH7_ISR */

/*
 * FTM7 Fault interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM7_FAULT_ISR_TID) &&		\
		(OSEE_CORTEX_M_FTM7_FAULT_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM7_Fault_IRQHandler, OSEE_CORTEX_M_FTM7_FAULT_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM7_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_FTM7_FAULT_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM7_Fault_IRQHandler, OSEE_CORTEX_M_FTM7_FAULT_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM7_Fault_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM7_FAULT_ISR */

/*
 * FTM7 Overflow Reload interrupt handler
 */
#if	(								\
		defined(OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_TID) &&	\
		(OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_CAT == 2U)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	FTM7_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_TID
)
#elif (									\
		defined(OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR) &&		\
		(OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR_CAT == 1U)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(
	FTM7_Ovf_Reload_IRQHandler, OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR
)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(FTM7_Ovf_Reload_IRQHandler)
#endif /* OSEE_CORTEX_M_FTM7_OVF_RELOAD_ISR */

#endif	/* OS_EE_ARCH_CORTEX_M_S32K148 */

#endif	/* OSEE_API_DYNAMIC */
