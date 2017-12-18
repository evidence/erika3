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

/** \file   ee_avr8_irqstub.h
 *  \brief  AVR8 IRQs Internals.
 *
 *  This files contains the internals of the IRQs support for AVR8 Architecture
 *  available in Erika Enterprise.
 *
 *  \note   TO BE DOCUMENTED!!!
 *
 *  \author Giuseppe Serano
 *  \date   2016
 */

#if (!defined(OSEE_AVR8_IRQSTUB_H))
#define OSEE_AVR8_IRQSTUB_H

/* I need Interals */
#include "ee_internal.h"

/* Plus I need IRQ handling defines */
#include "ee_avr8_irq.h"

#if (!defined(OSEE_API_DYNAMIC))
/*
 * ISR Type 1 stub.
 */
void OSEE_COMPILER_KEEP osEE_avr8_isr1_stub(OsEE_void_cb f);

/*
 * ISR Type 2 stub.
 */
void OSEE_COMPILER_KEEP osEE_avr8_isr2_stub(TaskType t);
#else /* !OSEE_API_DYNAMIC */

/*
 * ISR Type 2 stub.
 */
void OSEE_COMPILER_KEEP osEE_avr8_isr2_stub(OsEE_isr_src_id t);

#endif  /* !OSEE_API_DYNAMIC */

/*
 * Provide IRQ Entry global symbol.
 */
#define OSEE_AVR8_PROVIDE_IRQ_ENTRY(entry)  \
  OSEE_AVR8_PROVIDE_SYM(OSEE_S_J(tag_,entry))

/*
 * Request IRQ Entry global symbol.
 */
#define OSEE_AVR8_REQUEST_IRQ_ENTRY(entry)  \
  OSEE_AVR8_REQUEST_SYM(OSEE_S_J(tag_,entry))

/*
 * ISR pre-stub.
 */
#define OSEE_AVR8_ISR_PRESTUB()       \
do {                                  \
  __asm__ __volatile__("push r24\n"); \
  __asm__ __volatile__("push r25\n"); \
} while(0)

#define OSEE_AVR8_ISR_PREINSTUB()         \
do {                                      \
  __asm__ __volatile__("push r1\n");      \
  __asm__ __volatile__("push r0\n");      \
  __asm__ __volatile__("in   r0, 0x3f\n");\
  __asm__ __volatile__("push r0\n");      \
  __asm__ __volatile__("eor  r1, r1\n");  \
  __asm__ __volatile__("push r18\n");     \
  __asm__ __volatile__("push r19\n");     \
  __asm__ __volatile__("push r20\n");     \
  __asm__ __volatile__("push r21\n");     \
  __asm__ __volatile__("push r22\n");     \
  __asm__ __volatile__("push r23\n");     \
  __asm__ __volatile__("push r26\n");     \
  __asm__ __volatile__("push r27\n");     \
  __asm__ __volatile__("push r30\n");     \
  __asm__ __volatile__("push r31\n");     \
} while(0)

/*
 * ISR post-stub.
 */
#define OSEE_AVR8_ISR_POSTSTUB()    \
do {                                \
  __asm__ __volatile__("pop r25\n");\
  __asm__ __volatile__("pop r24\n");\
} while(0)

#define OSEE_AVR8_ISR_POSTINSTUB()        \
do {                                      \
  __asm__ __volatile__("pop r31\n");      \
  __asm__ __volatile__("pop r30\n");      \
  __asm__ __volatile__("pop r27\n");      \
  __asm__ __volatile__("pop r26\n");      \
  __asm__ __volatile__("pop r23\n");      \
  __asm__ __volatile__("pop r22\n");      \
  __asm__ __volatile__("pop r21\n");      \
  __asm__ __volatile__("pop r20\n");      \
  __asm__ __volatile__("pop r19\n");      \
  __asm__ __volatile__("pop r18\n");      \
  __asm__ __volatile__("pop r0\n");       \
  __asm__ __volatile__("out 0x3f, r0\n"); \
  __asm__ __volatile__("pop r0\n");       \
  __asm__ __volatile__("pop r1\n");       \
} while(0)

#if (!defined(OSEE_API_DYNAMIC))
/* Define an ISR (category 1) */
#define OSEE_AVR8_ISR1_DEFINITION(v,f)\
/* Declare The ISR User handler */    \
extern void f ( void );               \
ISR(v, ISR_NAKED)                     \
{                                     \
  OSEE_AVR8_PROVIDE_IRQ_ENTRY(v);     \
  OSEE_AVR8_ISR_PRESTUB();            \
  osEE_avr8_isr1_stub(f);             \
  EE_AVR8_ISR_POSTSTUB();             \
  reti();                             \
}
#endif  /* !OSEE_API_DYNAMIC */

/* Define an ISR (category 2) */
#define OSEE_AVR8_ISR2_DEFINITION(v,t)\
/* Declare The ISR User handler */    \
ISR(v, ISR_NAKED)                     \
{                                     \
  OSEE_AVR8_PROVIDE_IRQ_ENTRY(v);     \
  OSEE_AVR8_ISR_PRESTUB();            \
  osEE_avr8_isr2_stub(t);             \
  OSEE_AVR8_ISR_POSTSTUB();           \
  reti();                             \
}

/* Un-Defined ISR */
#define OSEE_AVR8_ISR_NOT_DEFINED(v)\
/* Define a NAKED ISR handler */    \
ISR(v, ISR_NAKED)                   \
{                                   \
  OSEE_AVR8_PROVIDE_IRQ_ENTRY(v);   \
  /* Disables IRQ  */               \
  cli();                            \
  /* Hangs in a infinite loop!!! */ \
  for(;;) {                         \
    ;                               \
  }                                 \
}

#endif /* !OSEE_AVR8_IRQSTUB_H */
