/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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

/** \file	ee_avr8_irqstub.c
 *  \brief	AVR8 IRQs Internals Implementation.
 *
 *  This files contains the internals implementation of the IRQs support for
 *  AVR8 Architecture available in Erika Enterprise.
 *
 *  \note   TO BE DOCUMENTED!!!
 *
 *  \author Giuseppe Serano
 *  \date   2016
 */

/* 
 * I need Kernel inclusion for callbacks and Common Context Implementation,
 * so I include the whole internal.
 */
#include "ee_internal.h"

/* Plus I need Common End-ISR Scheduler Implementation */
#include "ee_avr8_irqstub.h"

#if (!defined(OSEE_API_DYNAMIC))
/*
 * ISR Type 1 stub.
 */
void OSEE_COMPILER_KEEP OSEE_NAKED osEE_avr8_isr1_stub(OsEE_void_cb f)
{

  OSEE_AVR8_ISR_PREINSTUB();

#ifndef	__ATXMEGA__
  /* Enable IRQ */
  osEE_hal_enableIRQ();
#endif /* !__ATXMEGA__ */

  /* Call The ISR User Handler */
  f();

  OSEE_AVR8_ISR_POSTINSTUB();

  OSEE_RETURN();

} /* osEE_avr8_isr1_stub() */

/*
 * ISR Type 2 stub.
 */
void OSEE_COMPILER_KEEP OSEE_NAKED osEE_avr8_isr2_stub(TaskType t)
{

  OSEE_AVR8_ISR_PREINSTUB();

#if (defined(__ATXMEGA__))
  /* Disable IRQ */
  OSEE_hal_disableIRQ();
#endif /* __ATXMEGA__ */

  /* Activate ISR2 */
  osEE_activate_isr2(t);

  OSEE_AVR8_ISR_POSTINSTUB();

  OSEE_RETURN();

} /* osEE_avr8_isr2_stub() */
#else /* !OSEE_API_DYNAMIC */

#if (defined(__AVR_ATmega1281__))
#define OSEE_AVR8_ISR_ID_NUM  (OSEE_AVR8_USART3_TX_ISR_ID + 0x01U)
#else /* __AVR_ATmega1281__ */
#define OSEE_AVR8_ISR_ID_NUM  (OSEE_AVR8_SPM_READY_ISR_ID + 0x01U)
#endif /* __AVR_ATmega1281__ */

TaskType osEE_isr2_task_lookup_table[OSEE_AVR8_ISR_ID_NUM];

FUNC(StatusType, OS_CODE)
  osEE_hal_set_isr2_source
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_tdb,
  VAR(ISRSource,  AUTOMATIC)                source_id
)
{
  osEE_isr2_task_lookup_table[source_id]  = p_tdb->tid;
  p_tdb->hdb.isr2_src                     = source_id;
  return E_OK;
}

/*
 * ISR Type 2 stub.
 */
void OSEE_COMPILER_KEEP OSEE_NAKED osEE_avr8_isr2_stub(ISRSource isr)
{
  TaskType isr_id;

  OSEE_AVR8_ISR_PREINSTUB();

#if (defined(__ATXMEGA__))
  /* Disable IRQ */
  osEE_hal_disableIRQ();
#endif /* __ATXMEGA__ */

  /* Task Lookup */
  isr_id = osEE_isr2_task_lookup_table[isr];

  /* Activate ISR2 */
  osEE_activate_isr2(isr_id);

  OSEE_AVR8_ISR_POSTINSTUB();

  OSEE_RETURN();

} /* osEE_avr8_isr2_stub() */

#endif /* !OSEE_API_DYNAMIC */

