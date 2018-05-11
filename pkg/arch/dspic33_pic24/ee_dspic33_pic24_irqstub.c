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

/** \file	ee_dspic33_pic24_irqstub.c
 *  \brief	Microchip DSPIC33/PIC24 IRQs Internals Implementation.
 *
 *  This files contains the internals implementation of the IRQs support for
 *  Microchip DSPIC33/PIC24 Architecture available in Erika Enterprise.
 *
 *  \note	TO BE DOCUMENTED!!!
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* 
 * I need Kernel inclusion for callbacks and Common Context Implementation,
 * so I include the whole internal.
 */
#include "ee_internal.h"

#if	(!defined(OSEE_API_DYNAMIC))

/*
 * ISR Type 1 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_dspic33_pic24_isr1_stub(
  VAR(OsEE_void_cb, AUTOMATIC)	f
)
{

  /* Call The ISR User Handler */
  f();

}	/* osEE_dspic33_pic24_isr1_stub() */

/*
 * ISR Type 2 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_dspic33_pic24_isr2_stub(
  VAR(TaskType, AUTOMATIC)	t
)
{

  OsEE_reg f = osEE_hal_begin_nested_primitive();

  osEE_hal_enableIRQ();

  /* Activate ISR2 */
  osEE_activate_isr2(t);

  (void)f;

}	/* osEE_dspic33_pic24_isr2_stub() */

#else	/* !OSEE_API_DYNAMIC */

VAR(TaskType, OS_VAR_NO_INIT)
osEE_isr2_task_lookup_table[OSEE_DSPIC33_PIC24_ISR_ID_NUM];

FUNC(StatusType, OS_CODE)
  osEE_hal_set_isr2_source
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)	p_tdb,
  VAR(ISRSource,  AUTOMATIC)			source_id
)
{
  osEE_isr2_task_lookup_table[source_id]	= p_tdb->tid;
  p_tdb->hdb.isr2_src				= source_id;
  osEE_dspic33_pic24_ic_set_int_src(
    source_id,
    OSEE_ISR2_VIRT_TO_HW_PRIO(p_tdb->ready_prio),
    1U
  );
  return E_OK;
}	/* osEE_hal_set_isr2_source() */

/*
 * ISR Type 2 stub.
 */
FUNC(void, OS_CODE) OSEE_COMPILER_KEEP
osEE_dspic33_pic24_isr2_stub(
  VAR(OsEE_isr_src_id, AUTOMATIC)	t
)
{
  VAR(TaskType, AUTOMATIC)	isr_id;

  osEE_hal_begin_nested_primitive();

  /* Task Lookup */
  isr_id = osEE_isr2_task_lookup_table[t];

  /* Activate ISR2 */
  osEE_activate_isr2(isr_id);

}	/* osEE_dspic33_pic24_isr2_stub() */

#endif	/* !OSEE_API_DYNAMIC */
