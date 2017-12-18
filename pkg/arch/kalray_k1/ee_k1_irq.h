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

/** \file  ee_k1_irq.h
 *  \brief  Header with definition for Interrupt handling
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Guidieri
 *  \date  2016
 */
#if (!defined(OSEE_K1_IRQ_H))
#define OSEE_K1_IRQ_H

#include "ee_k1_vbsp.h"

/* Remapping on virtual PE event for reschedule */
#define OSEE_K1_RESCHEDULE_IIRQ  BSP_IT_PE_0
/* Number of IRQ */
#define OSEE_ISR_NUMBER          BSP_NB_IT_SOURCES

/* Macro to declare ISR: always valid */
#define DeclareIsr(f) void f ( void )

/* Declare an ISR (category 1) */
#define ISR1(f) void f ( void )

/* Define an ISR (category 2). Used only for client code. The wrapper is moved
   inside ee_tricore_intvec.c to isolate better user code from Kernel code.
   In TriCore Architecture ISR ID and ISR Priority are the same.
   I Use ISR ID as interrupt vector entry because is tied to handler name
   and I can easily reconstruct that here */
#define ISR2(f) ISR1(f)

/* OSEK Standard Macro for ISR declaration */


#if (!defined(OSEE_TRACE_KERNEL))
#define ISR(f) void f ( void )
#else
#define ISR(f)                                \
static void OsEE_S_J(f,ISR2Body) ( void );    \
void f ( void ) {                             \
  OsEE_S_J(f,ISR2Body)();                     \
}                                             \
static void OsEE_S_J(f,ISR2Body) ( void )
#endif /* !OSEE_TRACE_KERNEL */

/* Central Handler */
extern void osEE_os_it_handler (int nb, __k1_vcontext_t *ctx);

/* Interrupt Frame Restore */
extern void osEE_os_int_context_restore (__k1_vcontext_t *ctx);

#endif /* OSEE_K1_IRQ_H */
