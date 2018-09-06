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

/** \file	ee_cortex_m_system.h
 *  \brief	Cortex-M System Initialization.
 *
 *  This files contains the sourcess of the System Initialization for Cortex-M
 *  Architecture available in Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise Internals */
#include "ee_internal.h"


#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
/* Stacks Initialization. */
FUNC(void, OS_CODE) osEE_cortex_m_stack_init(void)
{
  MemSize      i;
  OsEE_stack * p_stack;
  OsEE_CDB   * const p_cdb = osEE_get_curr_core();
  
  /* Initialize all TASK stacks */
  for (i = 0U; i  < (p_cdb->chdb.stack_num - 1U); ++i) {
    MemSize j;
    p_stack = (OsEE_stack *)(*p_cdb->chdb.p_sdb_array)[i].p_bos;
    for (j = 0U;
	  j < (*p_cdb->chdb.p_sdb_array)[i].stack_size / sizeof(OsEE_stack);
	  ++j)
    {
      (*p_stack) = OSEE_FILL_PATTERN;
      ++p_stack;
    }
  }

  /* Initialize System Stack */
  {
    OsEE_stack * const p_curr_sp = osEE_get_SP();
    p_stack = (OsEE_stack *)
      (*p_cdb->chdb.p_sdb_array)[(p_cdb->chdb.stack_num - 1U)].p_bos;

    while (p_stack < p_curr_sp) {
      (*p_stack) = OSEE_FILL_PATTERN;
      ++p_stack;
    }
  }
}
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

/* Dummy Handler to link all handlers. */
extern FUNC(void, OS_CODE) osEE_cortex_m_mcu_system_init( void );

/* Implemented in ee_cortex_m_irq_asm.S */
extern FUNC(void, OS_CODE) osEE_set_switch_context_pri( void );

/*
 * System Initialization.
 */
FUNC(void, OS_CODE) osEE_cortex_m_system_init(void)
{
	/* 
	 * Set the priority of PendSV to the minimum one
	 * PendSV is the software interrupt used for context switch
	 */
	osEE_set_switch_context_pri();

	/*
	 * Bus Fault Exception Initialization.
	 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_BUS_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_BUS_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_BUS_FAULT_ISR) &&		\
			(OSEE_CORTEX_M_BUS_FAULT_ISR_CAT == 1)		\
		)							\
)
#ifdef	OSEE_CORTEX_M_BUS_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SYS_PRI1_R |= (
		(
			OSEE_CORTEX_M_BUS_FAULT_ISR_PRI <<
			OSEE_CORTEX_M_NVIC_SYS_PRI1_BUS_S
		) & OSEE_CORTEX_M_NVIC_SYS_PRI1_BUS_M
	);
#endif	/* OSEE_CORTEX_M_BUS_FAULT_ISR_PRI */
#endif	/* OSEE_CORTEX_M_BUS_FAULT_ISR */

	/*
	 * Bus Fault Exception Initialization.
	 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_BUS_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_BUS_FAULT_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_BUS_FAULT_ISR) &&		\
			(OSEE_CORTEX_M_BUS_FAULT_ISR_CAT == 1)		\
		)							\
)
#ifdef	OSEE_CORTEX_M_BUS_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SYS_PRI1_R |= (
		(
			OSEE_CORTEX_M_BUS_FAULT_ISR_PRI <<
			OSEE_CORTEX_M_NVIC_SYS_PRI1_BUS_S
		) & OSEE_CORTEX_M_NVIC_SYS_PRI1_BUS_M
	);
#endif	/* OSEE_CORTEX_M_BUS_FAULT_ISR_PRI */
#endif	/* OSEE_CORTEX_M_BUS_FAULT_ISR */

	/*
	 * Usage Fault Exception Initialization.
	 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_USAGE_FAULT_ISR_TID) &&	\
			(OSEE_CORTEX_M_USAGE_FAULT_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_USAGE_FAULT_ISR) &&	\
			(OSEE_CORTEX_M_USAGE_FAULT_ISR_CAT == 1)	\
		)							\
)
#ifdef	OSEE_CORTEX_M_USAGE_FAULT_ISR_PRI
	OSEE_CORTEX_M_NVIC_SYS_PRI1_R |= (
		(
			OSEE_CORTEX_M_USAGE_FAULT_ISR_PRI <<
			OSEE_CORTEX_M_NVIC_SYS_PRI1_USAGE_S
		) & OSEE_CORTEX_M_NVIC_SYS_PRI1_USAGE_M
	);
#endif	/* OSEE_CORTEX_M_USAGE_FAULT_ISR_PRI */
#endif	/* OSEE_CORTEX_M_USAGE_FAULT_ISR */

	/*
	 * Debug Monitor Exception Initialization.
	 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_DEBUG_MONITOR_ISR_TID) &&	\
			(OSEE_CORTEX_M_DEBUG_MONITOR_ISR_CAT == 2)	\
		) || (							\
			defined(OSEE_CORTEX_M_DEBUG_MONITOR_ISR) &&	\
			(OSEE_CORTEX_M_DEBUG_MONITOR_ISR_CAT == 1)	\
		)							\
)
#ifdef	OSEE_CORTEX_M_DEBUG_MONITOR_ISR_PRI
	OSEE_CORTEX_M_NVIC_SYS_PRI3_R |= (
		(
			OSEE_CORTEX_M_DEBUG_MONITOR_ISR_PRI <<
			OSEE_CORTEX_M_NVIC_SYS_PRI3_DEBUG_S
		) & OSEE_CORTEX_M_NVIC_SYS_PRI3_DEBUG_M
	);
#endif	/* OSEE_CORTEX_M_DEBUG_MONITOR_ISR_PRI */
#endif	/* OSEE_CORTEX_M_DEBUG_MONITOR_ISR */

	/*
	 * SysTick Exception Initialization.
	 */
#if	(								\
		(							\
			defined(OSEE_CORTEX_M_SYSTICK_ISR_TID) &&	\
			(OSEE_CORTEX_M_SYSTICK_ISR_CAT == 2)		\
		) || (							\
			defined(OSEE_CORTEX_M_SYSTICK_ISR) &&		\
			(OSEE_CORTEX_M_SYSTICK_ISR_CAT == 1)		\
		)							\
)
#ifdef	OSEE_CORTEX_M_SYSTICK_ISR_PRI
	OSEE_CORTEX_M_NVIC_SYS_PRI3_R |= (
		(
			OSEE_CORTEX_M_SYSTICK_ISR_PRI <<
			OSEE_CORTEX_M_NVIC_SYS_PRI3_TICK_S
		) &OSEE_CORTEX_M_NVIC_SYS_PRI3_TICK_M
	);
#endif	/* OSEE_CORTEX_M_SYSTICK_ISR_PRI */
#endif	/* OSEE_CORTEX_M_SYSTICK_ISR */

	/* 
	 * MCU System Initialization.
	 */
	osEE_cortex_m_mcu_system_init();

}	/* osEE_cortex_m_system_init() */

#if	(defined(OSEE_API_DYNAMIC))

/* [GS]: ID */

/*
 * Bus Fault Exception Handler.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(BusFault_Handler, OSEE_CORTEX_M_BUS_FAULT_ISR_ID)


/*
 * Usage Fault Exception Handler.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	UsageFault_Handler, OSEE_CORTEX_M_USAGE_FAULT_ISR_ID
)

/*
 * Debug Monitor Exception Handler.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(
	DebugMon_Handler, OSEE_CORTEX_M_DEBUG_MONITOR_ISR_ID
)

/*
 * SysTick Exception Handler.
 */
OSEE_CORTEX_M_ISR2_DEFINITION(SysTick_Handler, OSEE_CORTEX_M_SYSTICK_ISR_ID)

#else	/* OSEE_API_DYNAMIC */

/* [GS]: TID */

/*
 * NMI Exception Handler.
 */
#if	(							\
		defined(OSEE_CORTEX_M_NMI_ISR) &&		\
		(OSEE_CORTEX_M_NMI_ISR_CAT == 1)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(NMI_Handler, OSEE_CORTEX_M_NMI_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(NMI_Handler)
#endif	/* OSEE_CORTEX_M_NMI_ISR */

/*
 * Hard Fault Exception Handler.
 */
#if	(							\
		defined(OSEE_CORTEX_M_HARD_FAULT_ISR) &&	\
		(OSEE_CORTEX_M_HARD_FAULT_ISR_CAT == 1)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(HardFault_Handler, OSEE_CORTEX_M_HARD_FAULT_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(HardFault_Handler)
#endif	/* OSEE_CORTEX_M_HARD_FAULT_ISR */

/*
 * Bus Fault Exception Handler.
 */
#if	(							\
		defined(OSEE_CORTEX_M_BUS_FAULT_ISR_TID) &&	\
		(OSEE_CORTEX_M_BUS_FAULT_ISR_CAT == 2)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(BusFault_Handler, OSEE_CORTEX_M_BUS_FAULT_ISR_TID)
#elif	(							\
		defined(OSEE_CORTEX_M_BUS_FAULT_ISR) &&		\
		(OSEE_CORTEX_M_BUS_FAULT_ISR_CAT == 1)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(BusFault_Handler, OSEE_CORTEX_M_BUS_FAULT_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(BusFault_Handler)
#endif	/* OSEE_CORTEX_M_BUS_FAULT_ISR */

/*
 * Usage Fault Exception Handler.
 */
#if	(							\
		defined(OSEE_CORTEX_M_USAGE_FAULT_ISR_TID) &&	\
		(OSEE_CORTEX_M_USAGE_FAULT_ISR_CAT == 2)	\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	UsageFault_Handler, OSEE_CORTEX_M_USAGE_FAULT_ISR_TID
)
#elif	(							\
		defined(OSEE_CORTEX_M_USAGE_FAULT_ISR) &&	\
		(OSEE_CORTEX_M_USAGE_FAULT_ISR_CAT == 1)	\
)
OSEE_CORTEX_M_ISR1_DEFINITION(UsageFault_Handler, OSEE_CORTEX_M_USAGE_FAULT_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(UsageFault_Handler)
#endif	/* OSEE_CORTEX_M_USAGE_FAULT_ISR */

/*
 * Debug Monitor Exception Handler.
 */
#if	(							\
		defined(OSEE_CORTEX_M_DEBUG_MONITOR_ISR_TID) &&	\
		(OSEE_CORTEX_M_DEBUG_MONITOR_ISR_CAT == 2)	\
)
OSEE_CORTEX_M_ISR2_DEFINITION(
	DebugMon_Handler, OSEE_CORTEX_M_DEBUG_MONITOR_ISR_TID
)
#elif	(							\
		defined(OSEE_CORTEX_M_DEBUG_MONITOR_ISR) &&	\
		(OSEE_CORTEX_M_DEBUG_MONITOR_ISR_CAT == 1)	\
)
OSEE_CORTEX_M_ISR1_DEFINITION(DebugMon_Handler, OSEE_CORTEX_M_DEBUG_MONITOR_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(DebugMon_Handler)
#endif	/* OSEE_CORTEX_M_DEBUG_MONITOR_ISR */

/*
 * SysTick Exception Handler.
 */
#if	(							\
		defined(OSEE_CORTEX_M_SYSTICK_ISR_TID) &&	\
		(OSEE_CORTEX_M_SYSTICK_ISR_CAT == 2)		\
)
OSEE_CORTEX_M_ISR2_DEFINITION(SysTick_Handler, OSEE_CORTEX_M_SYSTICK_ISR_TID)
#elif	(							\
		defined(OSEE_CORTEX_M_SYSTICK_ISR) &&		\
		(OSEE_CORTEX_M_SYSTICK_ISR_CAT == 1)		\
)
OSEE_CORTEX_M_ISR1_DEFINITION(SysTick_Handler, OSEE_CORTEX_M_SYSTICK_ISR)
#elif	(defined(OSEE_MCU_EXTENDED_STATUS))
OSEE_CORTEX_M_ISR_NOT_DEFINED(SysTick_Handler)
#endif	/* OSEE_CORTEX_M_SYSTICK_ISR */

#endif	/* OSEE_API_DYNAMIC */
