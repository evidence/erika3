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

/**
    \file   ee_tc_intvec.c
    \brief  TriCore interrupts vector implementation.
    \author Errico Guidieri
    \date   2017
 */

#include "ee_internal.h"

static void OSEE_COMPILER_KEEP osEE_tc_isr2_wrapper(TaskType isr2_tid);

#if (defined(OSEE_SINGLECORE))
#define OSEE_CORE0_S _
#else
#define OSEE_CORE0_S _core0_
#endif /* OSEE_SINGLECORE */

/* Two pre-processor steps to let macros explode */
#define OSEE_ISR1_DEF(c,  c_id, f,  p)  OSEE_ISR1_ENTRY_DEF(c,  c_id, f,  p)
#define OSEE_ISR2_DEF(c,  c_id, id, p)  OSEE_ISR2_ENTRY_DEF(c,  c_id, id, p)
#define OSEE_ISR_ALIGN(c, c_id, p)      OSEE_ISR_ENTRY_ALIGN(c, c_id, p)

#if (defined(__TASKING__))

#if (defined(OSEE_TC_CLONE_OS))
/* Disable code cloning for interrupt vector */
#pragma code_core_association default
#endif /* OSEE_TC_CLONE_OS */

/* Use _Pragma(extern ...) To Force these symbols to be linked in elf file
   from an archive */
#define OSEE_ISR1_ENTRY_DEF(c, c_id, f, p)                      \
  void __interrupt_fast(p) OSEE_VECTORS_TABLE(c_id) __bisr_(p)  \
    osEE_tc##c##isr1_entry_##p(void)                            \
  {                                                             \
    f();                                                        \
  }

#define OSEE_ISR2_ENTRY_DEF(c, c_id, id, p)             \
  void __interrupt_fast(p) OSEE_VECTORS_TABLE(c_id)     \
    osEE_tc##c##isr2_entry_##p(void)                    \
  {                                                     \
    osEE_tc_isr2_wrapper(id);                           \
  }

#define OSEE_ISR_ENTRY_ALIGN(c, c_id, p)            \
  void __interrupt_fast(p) OSEE_VECTORS_TABLE(c_id) \
    osEE_tc##c##isr_dummy_entry_##p(void)           \
  {                                                 \
    for(;;);                                        \
  }

#elif (defined(__GNUC__))

#define OSEE_ISR1_ENTRY_DEF(c, c_id, f, p)                      \
  __asm__ (".globl osEE_tc" OSEE_S(c) "isr1_entry_" OSEE_S(p)); \
  __asm__ ("osEE_tc" OSEE_S(c) "isr1_entry_" OSEE_S(p) ":");    \
  __asm__ ("bisr " OSEE_S(p));                                  \
  __asm__ ("movh.a %a15,hi:" OSEE_S(f));                        \
  __asm__ ("lea %a15,[%a15]lo:" OSEE_S(f));                     \
  __asm__ ("calli %a15");                                       \
  __asm__ ("rslcx");                                            \
  __asm__ ("rfe");                                              \
  __asm__ (".align 5");

/* This macro do not use "bisr" instruction (Begin ISR = Save LC + enable)
   because we need to handle stacked list in critical section. */
#define OSEE_ISR2_ENTRY_DEF(c, c_id, id, p)                     \
  __asm__ (".globl osEE_tc" OSEE_S(c) "isr2_entry_" OSEE_S(p)); \
  __asm__ ("osEE_tc" OSEE_S(c) "isr2_entry_" OSEE_S(p) ":");    \
  __asm__ ("svlcx");                                            \
  __asm__ ("mov %d4, " OSEE_S(id));                             \
  __asm__ ("j osEE_tc_isr2_wrapper");                           \
  __asm__ (".align 5");

/*  I would have loved to use .org assembly directive (or .= instruction)
    instead generate dummy entries, but assembler ignore two .org consecutive
    directives (or two .= or any combination of the two) */
#define OSEE_ISR_ENTRY_ALIGN(c, c_id, p)                              \
  __asm__ (".globl osEE_tc" OSEE_S(c) "isr_dummy_entry_" OSEE_S(p));  \
  __asm__ ("osEE_tc" OSEE_S(c) "isr_dummy_entry_" OSEE_S(p) ":");     \
  __asm__ ("j .");                                                    \
  __asm__ (".align  5");                                              \

__asm__ ("\n\
  .section .inttab_cpu0, \"ax\", @progbits\n\
  .globl __INTTAB0\n\
__INTTAB0:");
/* ERIKA's Interrupt Vector Definition */
#if (defined(OSEE_TC_CORE0_ISR_MAX_PRIO))
__asm__(
"  .skip 0x20");
#endif /* OSEE_TC_CORE0_ISR_MAX_PRIO */
#else
#error Unknown Compiler!
#endif /* __TASKING____ || __GNUC__ */
#if (defined(OSEE_TC_CORE0_ISR_MAX_PRIO))
#if (defined(OSEE_TC_CORE0_1_ISR_CAT))
#if (OSEE_TC_CORE0_1_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_1_ISR_TID, 1)
#elif (OSEE_TC_CORE0_1_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_1_ISR_HND, 1)
#else
#error Invalid value for OSEE_TC_CORE0_1_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 1)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 1)
#endif /* OSEE_TC_CORE0_1_ISR_CAT */
#if (defined(OSEE_TC_CORE0_2_ISR_CAT))
#if (OSEE_TC_CORE0_2_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_2_ISR_TID, 2)
#elif (OSEE_TC_CORE0_2_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_2_ISR_HND, 2)
#else
#error Invalid value for OSEE_TC_CORE0_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 2)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 2)
#endif /* OSEE_TC_CORE0_2_ISR_CAT */
#if (defined(OSEE_TC_CORE0_3_ISR_CAT))
#if (OSEE_TC_CORE0_3_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_3_ISR_TID, 3)
#elif (OSEE_TC_CORE0_3_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_3_ISR_HND, 3)
#else
#error Invalid value for OSEE_TC_CORE0_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 3)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 3)
#endif /* OSEE_TC_CORE0_3_ISR_CAT */
#if (defined(OSEE_TC_CORE0_4_ISR_CAT))
#if (OSEE_TC_CORE0_4_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_4_ISR_TID, 4)
#elif (OSEE_TC_CORE0_4_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_4_ISR_HND, 4)
#else
#error Invalid value for OSEE_TC_CORE0_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 4)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 4)
#endif /* OSEE_TC_CORE0_4_ISR_CAT */
#if (defined(OSEE_TC_CORE0_5_ISR_CAT))
#if (OSEE_TC_CORE0_5_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_5_ISR_TID, 5)
#elif (OSEE_TC_CORE0_5_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_5_ISR_HND, 5)
#else
#error Invalid value for OSEE_TC_CORE0_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 5)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 5)
#endif /* OSEE_TC_CORE0_5_ISR_CAT */
#if (defined(OSEE_TC_CORE0_6_ISR_CAT))
#if (OSEE_TC_CORE0_6_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_6_ISR_TID, 6)
#elif (OSEE_TC_CORE0_6_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_6_ISR_HND, 6)
#else
#error Invalid value for OSEE_TC_CORE0_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 6)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 6)
#endif /* OSEE_TC_CORE0_6_ISR_CAT */
#if (defined(OSEE_TC_CORE0_7_ISR_CAT))
#if (OSEE_TC_CORE0_7_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_7_ISR_TID, 7)
#elif (OSEE_TC_CORE0_7_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_7_ISR_HND, 7)
#else
#error Invalid value for OSEE_TC_CORE0_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 7)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 7)
#endif /* OSEE_TC_CORE0_7_ISR_CAT */
#if (defined(OSEE_TC_CORE0_8_ISR_CAT))
#if (OSEE_TC_CORE0_8_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_8_ISR_TID, 8)
#elif (OSEE_TC_CORE0_8_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_8_ISR_HND, 8)
#else
#error Invalid value for OSEE_TC_CORE0_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 8)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 8)
#endif /* OSEE_TC_CORE0_8_ISR_CAT */
#if (defined(OSEE_TC_CORE0_9_ISR_CAT))
#if (OSEE_TC_CORE0_9_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_9_ISR_TID, 9)
#elif (OSEE_TC_CORE0_9_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_9_ISR_HND, 9)
#else
#error Invalid value for OSEE_TC_CORE0_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 9)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 9)
#endif /* OSEE_TC_CORE0_9_ISR_CAT */
#if (defined(OSEE_TC_CORE0_10_ISR_CAT))
#if (OSEE_TC_CORE0_10_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_10_ISR_TID, 10)
#elif (OSEE_TC_CORE0_10_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_10_ISR_HND, 10)
#else
#error Invalid value for OSEE_TC_CORE0_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 10)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 10)
#endif /* OSEE_TC_CORE0_10_ISR_CAT */
#if (defined(OSEE_TC_CORE0_11_ISR_CAT))
#if (OSEE_TC_CORE0_11_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_11_ISR_TID, 11)
#elif (OSEE_TC_CORE0_11_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_11_ISR_HND, 11)
#else
#error Invalid value for OSEE_TC_CORE0_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 11)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 11)
#endif /* OSEE_TC_CORE0_11_ISR_CAT */
#if (defined(OSEE_TC_CORE0_12_ISR_CAT))
#if (OSEE_TC_CORE0_12_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_12_ISR_TID, 12)
#elif (OSEE_TC_CORE0_12_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_12_ISR_HND, 12)
#else
#error Invalid value for OSEE_TC_CORE0_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 12)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 12)
#endif /* OSEE_TC_CORE0_12_ISR_CAT */
#if (defined(OSEE_TC_CORE0_13_ISR_CAT))
#if (OSEE_TC_CORE0_13_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_13_ISR_TID, 13)
#elif (OSEE_TC_CORE0_13_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_13_ISR_HND, 13)
#else
#error Invalid value for OSEE_TC_CORE0_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 13)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 13)
#endif /* OSEE_TC_CORE0_13_ISR_CAT */
#if (defined(OSEE_TC_CORE0_14_ISR_CAT))
#if (OSEE_TC_CORE0_14_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_14_ISR_TID, 14)
#elif (OSEE_TC_CORE0_14_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_14_ISR_HND, 14)
#else
#error Invalid value for OSEE_TC_CORE0_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 14)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 14)
#endif /* OSEE_TC_CORE0_14_ISR_CAT */
#if (defined(OSEE_TC_CORE0_15_ISR_CAT))
#if (OSEE_TC_CORE0_15_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_15_ISR_TID, 15)
#elif (OSEE_TC_CORE0_15_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_15_ISR_HND, 15)
#else
#error Invalid value for OSEE_TC_CORE0_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 15)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 15)
#endif /* OSEE_TC_CORE0_15_ISR_CAT */
#if (defined(OSEE_TC_CORE0_16_ISR_CAT))
#if (OSEE_TC_CORE0_16_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_16_ISR_TID, 16)
#elif (OSEE_TC_CORE0_16_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_16_ISR_HND, 16)
#else
#error Invalid value for OSEE_TC_CORE0_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 16)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 16)
#endif /* OSEE_TC_CORE0_16_ISR_CAT */
#if (defined(OSEE_TC_CORE0_17_ISR_CAT))
#if (OSEE_TC_CORE0_17_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_17_ISR_TID, 17)
#elif (OSEE_TC_CORE0_17_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_17_ISR_HND, 17)
#else
#error Invalid value for OSEE_TC_CORE0_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 17)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 17)
#endif /* OSEE_TC_CORE0_17_ISR_CAT */
#if (defined(OSEE_TC_CORE0_18_ISR_CAT))
#if (OSEE_TC_CORE0_18_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_18_ISR_TID, 18)
#elif (OSEE_TC_CORE0_18_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_18_ISR_HND, 18)
#else
#error Invalid value for OSEE_TC_CORE0_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 18)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 18)
#endif /* OSEE_TC_CORE0_18_ISR_CAT */
#if (defined(OSEE_TC_CORE0_19_ISR_CAT))
#if (OSEE_TC_CORE0_19_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_19_ISR_TID, 19)
#elif (OSEE_TC_CORE0_19_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_19_ISR_HND, 19)
#else
#error Invalid value for OSEE_TC_CORE0_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 19)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 19)
#endif /* OSEE_TC_CORE0_19_ISR_CAT */
#if (defined(OSEE_TC_CORE0_20_ISR_CAT))
#if (OSEE_TC_CORE0_20_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_20_ISR_TID, 20)
#elif (OSEE_TC_CORE0_20_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_20_ISR_HND, 20)
#else
#error Invalid value for OSEE_TC_CORE0_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 20)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 20)
#endif /* OSEE_TC_CORE0_20_ISR_CAT */
#if (defined(OSEE_TC_CORE0_21_ISR_CAT))
#if (OSEE_TC_CORE0_21_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_21_ISR_TID, 21)
#elif (OSEE_TC_CORE0_21_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_21_ISR_HND, 21)
#else
#error Invalid value for OSEE_TC_CORE0_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 21)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 21)
#endif /* OSEE_TC_CORE0_21_ISR_CAT */
#if (defined(OSEE_TC_CORE0_22_ISR_CAT))
#if (OSEE_TC_CORE0_22_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_22_ISR_TID, 22)
#elif (OSEE_TC_CORE0_22_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_22_ISR_HND, 22)
#else
#error Invalid value for OSEE_TC_CORE0_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 22)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 22)
#endif /* OSEE_TC_CORE0_22_ISR_CAT */
#if (defined(OSEE_TC_CORE0_23_ISR_CAT))
#if (OSEE_TC_CORE0_23_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_23_ISR_TID, 23)
#elif (OSEE_TC_CORE0_23_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_23_ISR_HND, 23)
#else
#error Invalid value for OSEE_TC_CORE0_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 23)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 23)
#endif /* OSEE_TC_CORE0_23_ISR_CAT */
#if (defined(OSEE_TC_CORE0_24_ISR_CAT))
#if (OSEE_TC_CORE0_24_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_24_ISR_TID, 24)
#elif (OSEE_TC_CORE0_24_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_24_ISR_HND, 24)
#else
#error Invalid value for OSEE_TC_CORE0_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 24)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 24)
#endif /* OSEE_TC_CORE0_24_ISR_CAT */
#if (defined(OSEE_TC_CORE0_25_ISR_CAT))
#if (OSEE_TC_CORE0_25_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_25_ISR_TID, 25)
#elif (OSEE_TC_CORE0_25_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_25_ISR_HND, 25)
#else
#error Invalid value for OSEE_TC_CORE0_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 25)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 25)
#endif /* OSEE_TC_CORE0_25_ISR_CAT */
#if (defined(OSEE_TC_CORE0_26_ISR_CAT))
#if (OSEE_TC_CORE0_26_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_26_ISR_TID, 26)
#elif (OSEE_TC_CORE0_26_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_26_ISR_HND, 26)
#else
#error Invalid value for OSEE_TC_CORE0_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 26)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 26)
#endif /* OSEE_TC_CORE0_26_ISR_CAT */
#if (defined(OSEE_TC_CORE0_27_ISR_CAT))
#if (OSEE_TC_CORE0_27_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_27_ISR_TID, 27)
#elif (OSEE_TC_CORE0_27_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_27_ISR_HND, 27)
#else
#error Invalid value for OSEE_TC_CORE0_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 27)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 27)
#endif /* OSEE_TC_CORE0_27_ISR_CAT */
#if (defined(OSEE_TC_CORE0_28_ISR_CAT))
#if (OSEE_TC_CORE0_28_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_28_ISR_TID, 28)
#elif (OSEE_TC_CORE0_28_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_28_ISR_HND, 28)
#else
#error Invalid value for OSEE_TC_CORE0_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 28)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 28)
#endif /* OSEE_TC_CORE0_28_ISR_CAT */
#if (defined(OSEE_TC_CORE0_29_ISR_CAT))
#if (OSEE_TC_CORE0_29_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_29_ISR_TID, 29)
#elif (OSEE_TC_CORE0_29_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_29_ISR_HND, 29)
#else
#error Invalid value for OSEE_TC_CORE0_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 29)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 29)
#endif /* OSEE_TC_CORE0_29_ISR_CAT */
#if (defined(OSEE_TC_CORE0_30_ISR_CAT))
#if (OSEE_TC_CORE0_30_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_30_ISR_TID, 30)
#elif (OSEE_TC_CORE0_30_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_30_ISR_HND, 30)
#else
#error Invalid value for OSEE_TC_CORE0_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 30)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 30)
#endif /* OSEE_TC_CORE0_30_ISR_CAT */
#if (defined(OSEE_TC_CORE0_31_ISR_CAT))
#if (OSEE_TC_CORE0_31_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_31_ISR_TID, 31)
#elif (OSEE_TC_CORE0_31_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_31_ISR_HND, 31)
#else
#error Invalid value for OSEE_TC_CORE0_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 31)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 31)
#endif /* OSEE_TC_CORE0_31_ISR_CAT */
#if (defined(OSEE_TC_CORE0_32_ISR_CAT))
#if (OSEE_TC_CORE0_32_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_32_ISR_TID, 32)
#elif (OSEE_TC_CORE0_32_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_32_ISR_HND, 32)
#else
#error Invalid value for OSEE_TC_CORE0_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 32)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 32)
#endif /* OSEE_TC_CORE0_32_ISR_CAT */
#if (defined(OSEE_TC_CORE0_33_ISR_CAT))
#if (OSEE_TC_CORE0_33_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_33_ISR_TID, 33)
#elif (OSEE_TC_CORE0_33_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_33_ISR_HND, 33)
#else
#error Invalid value for OSEE_TC_CORE0_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 33)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 33)
#endif /* OSEE_TC_CORE0_33_ISR_CAT */
#if (defined(OSEE_TC_CORE0_34_ISR_CAT))
#if (OSEE_TC_CORE0_34_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_34_ISR_TID, 34)
#elif (OSEE_TC_CORE0_34_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_34_ISR_HND, 34)
#else
#error Invalid value for OSEE_TC_CORE0_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 34)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 34)
#endif /* OSEE_TC_CORE0_34_ISR_CAT */
#if (defined(OSEE_TC_CORE0_35_ISR_CAT))
#if (OSEE_TC_CORE0_35_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_35_ISR_TID, 35)
#elif (OSEE_TC_CORE0_35_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_35_ISR_HND, 35)
#else
#error Invalid value for OSEE_TC_CORE0_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 35)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 35)
#endif /* OSEE_TC_CORE0_35_ISR_CAT */
#if (defined(OSEE_TC_CORE0_36_ISR_CAT))
#if (OSEE_TC_CORE0_36_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_36_ISR_TID, 36)
#elif (OSEE_TC_CORE0_36_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_36_ISR_HND, 36)
#else
#error Invalid value for OSEE_TC_CORE0_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 36)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 36)
#endif /* OSEE_TC_CORE0_36_ISR_CAT */
#if (defined(OSEE_TC_CORE0_37_ISR_CAT))
#if (OSEE_TC_CORE0_37_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_37_ISR_TID, 37)
#elif (OSEE_TC_CORE0_37_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_37_ISR_HND, 37)
#else
#error Invalid value for OSEE_TC_CORE0_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 37)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 37)
#endif /* OSEE_TC_CORE0_37_ISR_CAT */
#if (defined(OSEE_TC_CORE0_38_ISR_CAT))
#if (OSEE_TC_CORE0_38_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_38_ISR_TID, 38)
#elif (OSEE_TC_CORE0_38_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_38_ISR_HND, 38)
#else
#error Invalid value for OSEE_TC_CORE0_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 38)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 38)
#endif /* OSEE_TC_CORE0_38_ISR_CAT */
#if (defined(OSEE_TC_CORE0_39_ISR_CAT))
#if (OSEE_TC_CORE0_39_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_39_ISR_TID, 39)
#elif (OSEE_TC_CORE0_39_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_39_ISR_HND, 39)
#else
#error Invalid value for OSEE_TC_CORE0_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 39)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 39)
#endif /* OSEE_TC_CORE0_39_ISR_CAT */
#if (defined(OSEE_TC_CORE0_40_ISR_CAT))
#if (OSEE_TC_CORE0_40_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_40_ISR_TID, 40)
#elif (OSEE_TC_CORE0_40_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_40_ISR_HND, 40)
#else
#error Invalid value for OSEE_TC_CORE0_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 40)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 40)
#endif /* OSEE_TC_CORE0_40_ISR_CAT */
#if (defined(OSEE_TC_CORE0_41_ISR_CAT))
#if (OSEE_TC_CORE0_41_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_41_ISR_TID, 41)
#elif (OSEE_TC_CORE0_41_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_41_ISR_HND, 41)
#else
#error Invalid value for OSEE_TC_CORE0_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 41)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 41)
#endif /* OSEE_TC_CORE0_41_ISR_CAT */
#if (defined(OSEE_TC_CORE0_42_ISR_CAT))
#if (OSEE_TC_CORE0_42_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_42_ISR_TID, 42)
#elif (OSEE_TC_CORE0_42_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_42_ISR_HND, 42)
#else
#error Invalid value for OSEE_TC_CORE0_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 42)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 42)
#endif /* OSEE_TC_CORE0_42_ISR_CAT */
#if (defined(OSEE_TC_CORE0_43_ISR_CAT))
#if (OSEE_TC_CORE0_43_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_43_ISR_TID, 43)
#elif (OSEE_TC_CORE0_43_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_43_ISR_HND, 43)
#else
#error Invalid value for OSEE_TC_CORE0_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 43)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 43)
#endif /* OSEE_TC_CORE0_43_ISR_CAT */
#if (defined(OSEE_TC_CORE0_44_ISR_CAT))
#if (OSEE_TC_CORE0_44_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_44_ISR_TID, 44)
#elif (OSEE_TC_CORE0_44_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_44_ISR_HND, 44)
#else
#error Invalid value for OSEE_TC_CORE0_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 44)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 44)
#endif /* OSEE_TC_CORE0_44_ISR_CAT */
#if (defined(OSEE_TC_CORE0_45_ISR_CAT))
#if (OSEE_TC_CORE0_45_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_45_ISR_TID, 45)
#elif (OSEE_TC_CORE0_45_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_45_ISR_HND, 45)
#else
#error Invalid value for OSEE_TC_CORE0_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 45)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 45)
#endif /* OSEE_TC_CORE0_45_ISR_CAT */
#if (defined(OSEE_TC_CORE0_46_ISR_CAT))
#if (OSEE_TC_CORE0_46_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_46_ISR_TID, 46)
#elif (OSEE_TC_CORE0_46_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_46_ISR_HND, 46)
#else
#error Invalid value for OSEE_TC_CORE0_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 46)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 46)
#endif /* OSEE_TC_CORE0_46_ISR_CAT */
#if (defined(OSEE_TC_CORE0_47_ISR_CAT))
#if (OSEE_TC_CORE0_47_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_47_ISR_TID, 47)
#elif (OSEE_TC_CORE0_47_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_47_ISR_HND, 47)
#else
#error Invalid value for OSEE_TC_CORE0_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 47)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 47)
#endif /* OSEE_TC_CORE0_47_ISR_CAT */
#if (defined(OSEE_TC_CORE0_48_ISR_CAT))
#if (OSEE_TC_CORE0_48_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_48_ISR_TID, 48)
#elif (OSEE_TC_CORE0_48_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_48_ISR_HND, 48)
#else
#error Invalid value for OSEE_TC_CORE0_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 48)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 48)
#endif /* OSEE_TC_CORE0_48_ISR_CAT */
#if (defined(OSEE_TC_CORE0_49_ISR_CAT))
#if (OSEE_TC_CORE0_49_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_49_ISR_TID, 49)
#elif (OSEE_TC_CORE0_49_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_49_ISR_HND, 49)
#else
#error Invalid value for OSEE_TC_CORE0_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 49)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 49)
#endif /* OSEE_TC_CORE0_49_ISR_CAT */
#if (defined(OSEE_TC_CORE0_50_ISR_CAT))
#if (OSEE_TC_CORE0_50_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_50_ISR_TID, 50)
#elif (OSEE_TC_CORE0_50_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_50_ISR_HND, 50)
#else
#error Invalid value for OSEE_TC_CORE0_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 50)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 50)
#endif /* OSEE_TC_CORE0_50_ISR_CAT */
#if (defined(OSEE_TC_CORE0_51_ISR_CAT))
#if (OSEE_TC_CORE0_51_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_51_ISR_TID, 51)
#elif (OSEE_TC_CORE0_51_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_51_ISR_HND, 51)
#else
#error Invalid value for OSEE_TC_CORE0_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 51)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 51)
#endif /* OSEE_TC_CORE0_51_ISR_CAT */
#if (defined(OSEE_TC_CORE0_52_ISR_CAT))
#if (OSEE_TC_CORE0_52_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_52_ISR_TID, 52)
#elif (OSEE_TC_CORE0_52_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_52_ISR_HND, 52)
#else
#error Invalid value for OSEE_TC_CORE0_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 52)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 52)
#endif /* OSEE_TC_CORE0_52_ISR_CAT */
#if (defined(OSEE_TC_CORE0_53_ISR_CAT))
#if (OSEE_TC_CORE0_53_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_53_ISR_TID, 53)
#elif (OSEE_TC_CORE0_53_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_53_ISR_HND, 53)
#else
#error Invalid value for OSEE_TC_CORE0_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 53)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 53)
#endif /* OSEE_TC_CORE0_53_ISR_CAT */
#if (defined(OSEE_TC_CORE0_54_ISR_CAT))
#if (OSEE_TC_CORE0_54_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_54_ISR_TID, 54)
#elif (OSEE_TC_CORE0_54_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_54_ISR_HND, 54)
#else
#error Invalid value for OSEE_TC_CORE0_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 54)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 54)
#endif /* OSEE_TC_CORE0_54_ISR_CAT */
#if (defined(OSEE_TC_CORE0_55_ISR_CAT))
#if (OSEE_TC_CORE0_55_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_55_ISR_TID, 55)
#elif (OSEE_TC_CORE0_55_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_55_ISR_HND, 55)
#else
#error Invalid value for OSEE_TC_CORE0_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 55)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 55)
#endif /* OSEE_TC_CORE0_55_ISR_CAT */
#if (defined(OSEE_TC_CORE0_56_ISR_CAT))
#if (OSEE_TC_CORE0_56_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_56_ISR_TID, 56)
#elif (OSEE_TC_CORE0_56_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_56_ISR_HND, 56)
#else
#error Invalid value for OSEE_TC_CORE0_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 56)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 56)
#endif /* OSEE_TC_CORE0_56_ISR_CAT */
#if (defined(OSEE_TC_CORE0_57_ISR_CAT))
#if (OSEE_TC_CORE0_57_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_57_ISR_TID, 57)
#elif (OSEE_TC_CORE0_57_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_57_ISR_HND, 57)
#else
#error Invalid value for OSEE_TC_CORE0_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 57)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 57)
#endif /* OSEE_TC_CORE0_57_ISR_CAT */
#if (defined(OSEE_TC_CORE0_58_ISR_CAT))
#if (OSEE_TC_CORE0_58_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_58_ISR_TID, 58)
#elif (OSEE_TC_CORE0_58_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_58_ISR_HND, 58)
#else
#error Invalid value for OSEE_TC_CORE0_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 58)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 58)
#endif /* OSEE_TC_CORE0_58_ISR_CAT */
#if (defined(OSEE_TC_CORE0_59_ISR_CAT))
#if (OSEE_TC_CORE0_59_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_59_ISR_TID, 59)
#elif (OSEE_TC_CORE0_59_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_59_ISR_HND, 59)
#else
#error Invalid value for OSEE_TC_CORE0_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 59)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 59)
#endif /* OSEE_TC_CORE0_59_ISR_CAT */
#if (defined(OSEE_TC_CORE0_60_ISR_CAT))
#if (OSEE_TC_CORE0_60_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_60_ISR_TID, 60)
#elif (OSEE_TC_CORE0_60_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_60_ISR_HND, 60)
#else
#error Invalid value for OSEE_TC_CORE0_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 60)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 60)
#endif /* OSEE_TC_CORE0_60_ISR_CAT */
#if (defined(OSEE_TC_CORE0_61_ISR_CAT))
#if (OSEE_TC_CORE0_61_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_61_ISR_TID, 61)
#elif (OSEE_TC_CORE0_61_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_61_ISR_HND, 61)
#else
#error Invalid value for OSEE_TC_CORE0_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 61)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 61)
#endif /* OSEE_TC_CORE0_61_ISR_CAT */
#if (defined(OSEE_TC_CORE0_62_ISR_CAT))
#if (OSEE_TC_CORE0_62_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_62_ISR_TID, 62)
#elif (OSEE_TC_CORE0_62_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_62_ISR_HND, 62)
#else
#error Invalid value for OSEE_TC_CORE0_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 62)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 62)
#endif /* OSEE_TC_CORE0_62_ISR_CAT */
#if (defined(OSEE_TC_CORE0_63_ISR_CAT))
#if (OSEE_TC_CORE0_63_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_63_ISR_TID, 63)
#elif (OSEE_TC_CORE0_63_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_63_ISR_HND, 63)
#else
#error Invalid value for OSEE_TC_CORE0_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 63)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 63)
#endif /* OSEE_TC_CORE0_63_ISR_CAT */
#if (defined(OSEE_TC_CORE0_64_ISR_CAT))
#if (OSEE_TC_CORE0_64_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_64_ISR_TID, 64)
#elif (OSEE_TC_CORE0_64_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_64_ISR_HND, 64)
#else
#error Invalid value for OSEE_TC_CORE0_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 64)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 64)
#endif /* OSEE_TC_CORE0_64_ISR_CAT */
#if (defined(OSEE_TC_CORE0_65_ISR_CAT))
#if (OSEE_TC_CORE0_65_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_65_ISR_TID, 65)
#elif (OSEE_TC_CORE0_65_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_65_ISR_HND, 65)
#else
#error Invalid value for OSEE_TC_CORE0_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 65)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 65)
#endif /* OSEE_TC_CORE0_65_ISR_CAT */
#if (defined(OSEE_TC_CORE0_66_ISR_CAT))
#if (OSEE_TC_CORE0_66_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_66_ISR_TID, 66)
#elif (OSEE_TC_CORE0_66_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_66_ISR_HND, 66)
#else
#error Invalid value for OSEE_TC_CORE0_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 66)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 66)
#endif /* OSEE_TC_CORE0_66_ISR_CAT */
#if (defined(OSEE_TC_CORE0_67_ISR_CAT))
#if (OSEE_TC_CORE0_67_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_67_ISR_TID, 67)
#elif (OSEE_TC_CORE0_67_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_67_ISR_HND, 67)
#else
#error Invalid value for OSEE_TC_CORE0_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 67)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 67)
#endif /* OSEE_TC_CORE0_67_ISR_CAT */
#if (defined(OSEE_TC_CORE0_68_ISR_CAT))
#if (OSEE_TC_CORE0_68_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_68_ISR_TID, 68)
#elif (OSEE_TC_CORE0_68_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_68_ISR_HND, 68)
#else
#error Invalid value for OSEE_TC_CORE0_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 68)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 68)
#endif /* OSEE_TC_CORE0_68_ISR_CAT */
#if (defined(OSEE_TC_CORE0_69_ISR_CAT))
#if (OSEE_TC_CORE0_69_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_69_ISR_TID, 69)
#elif (OSEE_TC_CORE0_69_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_69_ISR_HND, 69)
#else
#error Invalid value for OSEE_TC_CORE0_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 69)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 69)
#endif /* OSEE_TC_CORE0_69_ISR_CAT */
#if (defined(OSEE_TC_CORE0_70_ISR_CAT))
#if (OSEE_TC_CORE0_70_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_70_ISR_TID, 70)
#elif (OSEE_TC_CORE0_70_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_70_ISR_HND, 70)
#else
#error Invalid value for OSEE_TC_CORE0_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 70)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 70)
#endif /* OSEE_TC_CORE0_70_ISR_CAT */
#if (defined(OSEE_TC_CORE0_71_ISR_CAT))
#if (OSEE_TC_CORE0_71_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_71_ISR_TID, 71)
#elif (OSEE_TC_CORE0_71_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_71_ISR_HND, 71)
#else
#error Invalid value for OSEE_TC_CORE0_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 71)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 71)
#endif /* OSEE_TC_CORE0_71_ISR_CAT */
#if (defined(OSEE_TC_CORE0_72_ISR_CAT))
#if (OSEE_TC_CORE0_72_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_72_ISR_TID, 72)
#elif (OSEE_TC_CORE0_72_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_72_ISR_HND, 72)
#else
#error Invalid value for OSEE_TC_CORE0_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 72)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 72)
#endif /* OSEE_TC_CORE0_72_ISR_CAT */
#if (defined(OSEE_TC_CORE0_73_ISR_CAT))
#if (OSEE_TC_CORE0_73_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_73_ISR_TID, 73)
#elif (OSEE_TC_CORE0_73_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_73_ISR_HND, 73)
#else
#error Invalid value for OSEE_TC_CORE0_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 73)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 73)
#endif /* OSEE_TC_CORE0_73_ISR_CAT */
#if (defined(OSEE_TC_CORE0_74_ISR_CAT))
#if (OSEE_TC_CORE0_74_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_74_ISR_TID, 74)
#elif (OSEE_TC_CORE0_74_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_74_ISR_HND, 74)
#else
#error Invalid value for OSEE_TC_CORE0_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 74)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 74)
#endif /* OSEE_TC_CORE0_74_ISR_CAT */
#if (defined(OSEE_TC_CORE0_75_ISR_CAT))
#if (OSEE_TC_CORE0_75_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_75_ISR_TID, 75)
#elif (OSEE_TC_CORE0_75_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_75_ISR_HND, 75)
#else
#error Invalid value for OSEE_TC_CORE0_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 75)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 75)
#endif /* OSEE_TC_CORE0_75_ISR_CAT */
#if (defined(OSEE_TC_CORE0_76_ISR_CAT))
#if (OSEE_TC_CORE0_76_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_76_ISR_TID, 76)
#elif (OSEE_TC_CORE0_76_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_76_ISR_HND, 76)
#else
#error Invalid value for OSEE_TC_CORE0_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 76)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 76)
#endif /* OSEE_TC_CORE0_76_ISR_CAT */
#if (defined(OSEE_TC_CORE0_77_ISR_CAT))
#if (OSEE_TC_CORE0_77_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_77_ISR_TID, 77)
#elif (OSEE_TC_CORE0_77_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_77_ISR_HND, 77)
#else
#error Invalid value for OSEE_TC_CORE0_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 77)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 77)
#endif /* OSEE_TC_CORE0_77_ISR_CAT */
#if (defined(OSEE_TC_CORE0_78_ISR_CAT))
#if (OSEE_TC_CORE0_78_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_78_ISR_TID, 78)
#elif (OSEE_TC_CORE0_78_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_78_ISR_HND, 78)
#else
#error Invalid value for OSEE_TC_CORE0_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 78)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 78)
#endif /* OSEE_TC_CORE0_78_ISR_CAT */
#if (defined(OSEE_TC_CORE0_79_ISR_CAT))
#if (OSEE_TC_CORE0_79_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_79_ISR_TID, 79)
#elif (OSEE_TC_CORE0_79_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_79_ISR_HND, 79)
#else
#error Invalid value for OSEE_TC_CORE0_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 79)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 79)
#endif /* OSEE_TC_CORE0_79_ISR_CAT */
#if (defined(OSEE_TC_CORE0_80_ISR_CAT))
#if (OSEE_TC_CORE0_80_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_80_ISR_TID, 80)
#elif (OSEE_TC_CORE0_80_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_80_ISR_HND, 80)
#else
#error Invalid value for OSEE_TC_CORE0_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 80)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 80)
#endif /* OSEE_TC_CORE0_80_ISR_CAT */
#if (defined(OSEE_TC_CORE0_81_ISR_CAT))
#if (OSEE_TC_CORE0_81_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_81_ISR_TID, 81)
#elif (OSEE_TC_CORE0_81_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_81_ISR_HND, 81)
#else
#error Invalid value for OSEE_TC_CORE0_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 81)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 81)
#endif /* OSEE_TC_CORE0_81_ISR_CAT */
#if (defined(OSEE_TC_CORE0_82_ISR_CAT))
#if (OSEE_TC_CORE0_82_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_82_ISR_TID, 82)
#elif (OSEE_TC_CORE0_82_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_82_ISR_HND, 82)
#else
#error Invalid value for OSEE_TC_CORE0_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 82)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 82)
#endif /* OSEE_TC_CORE0_82_ISR_CAT */
#if (defined(OSEE_TC_CORE0_83_ISR_CAT))
#if (OSEE_TC_CORE0_83_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_83_ISR_TID, 83)
#elif (OSEE_TC_CORE0_83_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_83_ISR_HND, 83)
#else
#error Invalid value for OSEE_TC_CORE0_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 83)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 83)
#endif /* OSEE_TC_CORE0_83_ISR_CAT */
#if (defined(OSEE_TC_CORE0_84_ISR_CAT))
#if (OSEE_TC_CORE0_84_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_84_ISR_TID, 84)
#elif (OSEE_TC_CORE0_84_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_84_ISR_HND, 84)
#else
#error Invalid value for OSEE_TC_CORE0_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 84)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 84)
#endif /* OSEE_TC_CORE0_84_ISR_CAT */
#if (defined(OSEE_TC_CORE0_85_ISR_CAT))
#if (OSEE_TC_CORE0_85_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_85_ISR_TID, 85)
#elif (OSEE_TC_CORE0_85_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_85_ISR_HND, 85)
#else
#error Invalid value for OSEE_TC_CORE0_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 85)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 85)
#endif /* OSEE_TC_CORE0_85_ISR_CAT */
#if (defined(OSEE_TC_CORE0_86_ISR_CAT))
#if (OSEE_TC_CORE0_86_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_86_ISR_TID, 86)
#elif (OSEE_TC_CORE0_86_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_86_ISR_HND, 86)
#else
#error Invalid value for OSEE_TC_CORE0_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 86)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 86)
#endif /* OSEE_TC_CORE0_86_ISR_CAT */
#if (defined(OSEE_TC_CORE0_87_ISR_CAT))
#if (OSEE_TC_CORE0_87_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_87_ISR_TID, 87)
#elif (OSEE_TC_CORE0_87_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_87_ISR_HND, 87)
#else
#error Invalid value for OSEE_TC_CORE0_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 87)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 87)
#endif /* OSEE_TC_CORE0_87_ISR_CAT */
#if (defined(OSEE_TC_CORE0_88_ISR_CAT))
#if (OSEE_TC_CORE0_88_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_88_ISR_TID, 88)
#elif (OSEE_TC_CORE0_88_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_88_ISR_HND, 88)
#else
#error Invalid value for OSEE_TC_CORE0_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 88)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 88)
#endif /* OSEE_TC_CORE0_88_ISR_CAT */
#if (defined(OSEE_TC_CORE0_89_ISR_CAT))
#if (OSEE_TC_CORE0_89_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_89_ISR_TID, 89)
#elif (OSEE_TC_CORE0_89_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_89_ISR_HND, 89)
#else
#error Invalid value for OSEE_TC_CORE0_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 89)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 89)
#endif /* OSEE_TC_CORE0_89_ISR_CAT */
#if (defined(OSEE_TC_CORE0_90_ISR_CAT))
#if (OSEE_TC_CORE0_90_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_90_ISR_TID, 90)
#elif (OSEE_TC_CORE0_90_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_90_ISR_HND, 90)
#else
#error Invalid value for OSEE_TC_CORE0_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 90)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 90)
#endif /* OSEE_TC_CORE0_90_ISR_CAT */
#if (defined(OSEE_TC_CORE0_91_ISR_CAT))
#if (OSEE_TC_CORE0_91_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_91_ISR_TID, 91)
#elif (OSEE_TC_CORE0_91_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_91_ISR_HND, 91)
#else
#error Invalid value for OSEE_TC_CORE0_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 91)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 91)
#endif /* OSEE_TC_CORE0_91_ISR_CAT */
#if (defined(OSEE_TC_CORE0_92_ISR_CAT))
#if (OSEE_TC_CORE0_92_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_92_ISR_TID, 92)
#elif (OSEE_TC_CORE0_92_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_92_ISR_HND, 92)
#else
#error Invalid value for OSEE_TC_CORE0_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 92)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 92)
#endif /* OSEE_TC_CORE0_92_ISR_CAT */
#if (defined(OSEE_TC_CORE0_93_ISR_CAT))
#if (OSEE_TC_CORE0_93_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_93_ISR_TID, 93)
#elif (OSEE_TC_CORE0_93_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_93_ISR_HND, 93)
#else
#error Invalid value for OSEE_TC_CORE0_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 93)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 93)
#endif /* OSEE_TC_CORE0_93_ISR_CAT */
#if (defined(OSEE_TC_CORE0_94_ISR_CAT))
#if (OSEE_TC_CORE0_94_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_94_ISR_TID, 94)
#elif (OSEE_TC_CORE0_94_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_94_ISR_HND, 94)
#else
#error Invalid value for OSEE_TC_CORE0_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 94)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 94)
#endif /* OSEE_TC_CORE0_94_ISR_CAT */
#if (defined(OSEE_TC_CORE0_95_ISR_CAT))
#if (OSEE_TC_CORE0_95_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_95_ISR_TID, 95)
#elif (OSEE_TC_CORE0_95_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_95_ISR_HND, 95)
#else
#error Invalid value for OSEE_TC_CORE0_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 95)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 95)
#endif /* OSEE_TC_CORE0_95_ISR_CAT */
#if (defined(OSEE_TC_CORE0_96_ISR_CAT))
#if (OSEE_TC_CORE0_96_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_96_ISR_TID, 96)
#elif (OSEE_TC_CORE0_96_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_96_ISR_HND, 96)
#else
#error Invalid value for OSEE_TC_CORE0_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 96)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 96)
#endif /* OSEE_TC_CORE0_96_ISR_CAT */
#if (defined(OSEE_TC_CORE0_97_ISR_CAT))
#if (OSEE_TC_CORE0_97_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_97_ISR_TID, 97)
#elif (OSEE_TC_CORE0_97_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_97_ISR_HND, 97)
#else
#error Invalid value for OSEE_TC_CORE0_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 97)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 97)
#endif /* OSEE_TC_CORE0_97_ISR_CAT */
#if (defined(OSEE_TC_CORE0_98_ISR_CAT))
#if (OSEE_TC_CORE0_98_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_98_ISR_TID, 98)
#elif (OSEE_TC_CORE0_98_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_98_ISR_HND, 98)
#else
#error Invalid value for OSEE_TC_CORE0_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 98)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 98)
#endif /* OSEE_TC_CORE0_98_ISR_CAT */
#if (defined(OSEE_TC_CORE0_99_ISR_CAT))
#if (OSEE_TC_CORE0_99_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_99_ISR_TID, 99)
#elif (OSEE_TC_CORE0_99_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_99_ISR_HND, 99)
#else
#error Invalid value for OSEE_TC_CORE0_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 99)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 99)
#endif /* OSEE_TC_CORE0_99_ISR_CAT */
#if (defined(OSEE_TC_CORE0_100_ISR_CAT))
#if (OSEE_TC_CORE0_100_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_100_ISR_TID, 100)
#elif (OSEE_TC_CORE0_100_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_100_ISR_HND, 100)
#else
#error Invalid value for OSEE_TC_CORE0_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 100)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 100)
#endif /* OSEE_TC_CORE0_100_ISR_CAT */
#if (defined(OSEE_TC_CORE0_101_ISR_CAT))
#if (OSEE_TC_CORE0_101_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_101_ISR_TID, 101)
#elif (OSEE_TC_CORE0_101_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_101_ISR_HND, 101)
#else
#error Invalid value for OSEE_TC_CORE0_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 101)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 101)
#endif /* OSEE_TC_CORE0_101_ISR_CAT */
#if (defined(OSEE_TC_CORE0_102_ISR_CAT))
#if (OSEE_TC_CORE0_102_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_102_ISR_TID, 102)
#elif (OSEE_TC_CORE0_102_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_102_ISR_HND, 102)
#else
#error Invalid value for OSEE_TC_CORE0_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 102)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 102)
#endif /* OSEE_TC_CORE0_102_ISR_CAT */
#if (defined(OSEE_TC_CORE0_103_ISR_CAT))
#if (OSEE_TC_CORE0_103_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_103_ISR_TID, 103)
#elif (OSEE_TC_CORE0_103_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_103_ISR_HND, 103)
#else
#error Invalid value for OSEE_TC_CORE0_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 103)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 103)
#endif /* OSEE_TC_CORE0_103_ISR_CAT */
#if (defined(OSEE_TC_CORE0_104_ISR_CAT))
#if (OSEE_TC_CORE0_104_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_104_ISR_TID, 104)
#elif (OSEE_TC_CORE0_104_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_104_ISR_HND, 104)
#else
#error Invalid value for OSEE_TC_CORE0_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 104)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 104)
#endif /* OSEE_TC_CORE0_104_ISR_CAT */
#if (defined(OSEE_TC_CORE0_105_ISR_CAT))
#if (OSEE_TC_CORE0_105_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_105_ISR_TID, 105)
#elif (OSEE_TC_CORE0_105_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_105_ISR_HND, 105)
#else
#error Invalid value for OSEE_TC_CORE0_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 105)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 105)
#endif /* OSEE_TC_CORE0_105_ISR_CAT */
#if (defined(OSEE_TC_CORE0_106_ISR_CAT))
#if (OSEE_TC_CORE0_106_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_106_ISR_TID, 106)
#elif (OSEE_TC_CORE0_106_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_106_ISR_HND, 106)
#else
#error Invalid value for OSEE_TC_CORE0_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 106)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 106)
#endif /* OSEE_TC_CORE0_106_ISR_CAT */
#if (defined(OSEE_TC_CORE0_107_ISR_CAT))
#if (OSEE_TC_CORE0_107_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_107_ISR_TID, 107)
#elif (OSEE_TC_CORE0_107_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_107_ISR_HND, 107)
#else
#error Invalid value for OSEE_TC_CORE0_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 107)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 107)
#endif /* OSEE_TC_CORE0_107_ISR_CAT */
#if (defined(OSEE_TC_CORE0_108_ISR_CAT))
#if (OSEE_TC_CORE0_108_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_108_ISR_TID, 108)
#elif (OSEE_TC_CORE0_108_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_108_ISR_HND, 108)
#else
#error Invalid value for OSEE_TC_CORE0_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 108)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 108)
#endif /* OSEE_TC_CORE0_108_ISR_CAT */
#if (defined(OSEE_TC_CORE0_109_ISR_CAT))
#if (OSEE_TC_CORE0_109_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_109_ISR_TID, 109)
#elif (OSEE_TC_CORE0_109_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_109_ISR_HND, 109)
#else
#error Invalid value for OSEE_TC_CORE0_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 109)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 109)
#endif /* OSEE_TC_CORE0_109_ISR_CAT */
#if (defined(OSEE_TC_CORE0_110_ISR_CAT))
#if (OSEE_TC_CORE0_110_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_110_ISR_TID, 110)
#elif (OSEE_TC_CORE0_110_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_110_ISR_HND, 110)
#else
#error Invalid value for OSEE_TC_CORE0_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 110)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 110)
#endif /* OSEE_TC_CORE0_110_ISR_CAT */
#if (defined(OSEE_TC_CORE0_111_ISR_CAT))
#if (OSEE_TC_CORE0_111_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_111_ISR_TID, 111)
#elif (OSEE_TC_CORE0_111_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_111_ISR_HND, 111)
#else
#error Invalid value for OSEE_TC_CORE0_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 111)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 111)
#endif /* OSEE_TC_CORE0_111_ISR_CAT */
#if (defined(OSEE_TC_CORE0_112_ISR_CAT))
#if (OSEE_TC_CORE0_112_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_112_ISR_TID, 112)
#elif (OSEE_TC_CORE0_112_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_112_ISR_HND, 112)
#else
#error Invalid value for OSEE_TC_CORE0_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 112)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 112)
#endif /* OSEE_TC_CORE0_112_ISR_CAT */
#if (defined(OSEE_TC_CORE0_113_ISR_CAT))
#if (OSEE_TC_CORE0_113_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_113_ISR_TID, 113)
#elif (OSEE_TC_CORE0_113_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_113_ISR_HND, 113)
#else
#error Invalid value for OSEE_TC_CORE0_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 113)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 113)
#endif /* OSEE_TC_CORE0_113_ISR_CAT */
#if (defined(OSEE_TC_CORE0_114_ISR_CAT))
#if (OSEE_TC_CORE0_114_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_114_ISR_TID, 114)
#elif (OSEE_TC_CORE0_114_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_114_ISR_HND, 114)
#else
#error Invalid value for OSEE_TC_CORE0_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 114)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 114)
#endif /* OSEE_TC_CORE0_114_ISR_CAT */
#if (defined(OSEE_TC_CORE0_115_ISR_CAT))
#if (OSEE_TC_CORE0_115_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_115_ISR_TID, 115)
#elif (OSEE_TC_CORE0_115_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_115_ISR_HND, 115)
#else
#error Invalid value for OSEE_TC_CORE0_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 115)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 115)
#endif /* OSEE_TC_CORE0_115_ISR_CAT */
#if (defined(OSEE_TC_CORE0_116_ISR_CAT))
#if (OSEE_TC_CORE0_116_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_116_ISR_TID, 116)
#elif (OSEE_TC_CORE0_116_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_116_ISR_HND, 116)
#else
#error Invalid value for OSEE_TC_CORE0_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 116)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 116)
#endif /* OSEE_TC_CORE0_116_ISR_CAT */
#if (defined(OSEE_TC_CORE0_117_ISR_CAT))
#if (OSEE_TC_CORE0_117_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_117_ISR_TID, 117)
#elif (OSEE_TC_CORE0_117_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_117_ISR_HND, 117)
#else
#error Invalid value for OSEE_TC_CORE0_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 117)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 117)
#endif /* OSEE_TC_CORE0_117_ISR_CAT */
#if (defined(OSEE_TC_CORE0_118_ISR_CAT))
#if (OSEE_TC_CORE0_118_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_118_ISR_TID, 118)
#elif (OSEE_TC_CORE0_118_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_118_ISR_HND, 118)
#else
#error Invalid value for OSEE_TC_CORE0_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 118)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 118)
#endif /* OSEE_TC_CORE0_118_ISR_CAT */
#if (defined(OSEE_TC_CORE0_119_ISR_CAT))
#if (OSEE_TC_CORE0_119_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_119_ISR_TID, 119)
#elif (OSEE_TC_CORE0_119_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_119_ISR_HND, 119)
#else
#error Invalid value for OSEE_TC_CORE0_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 119)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 119)
#endif /* OSEE_TC_CORE0_119_ISR_CAT */
#if (defined(OSEE_TC_CORE0_120_ISR_CAT))
#if (OSEE_TC_CORE0_120_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_120_ISR_TID, 120)
#elif (OSEE_TC_CORE0_120_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_120_ISR_HND, 120)
#else
#error Invalid value for OSEE_TC_CORE0_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 120)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 120)
#endif /* OSEE_TC_CORE0_120_ISR_CAT */
#if (defined(OSEE_TC_CORE0_121_ISR_CAT))
#if (OSEE_TC_CORE0_121_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_121_ISR_TID, 121)
#elif (OSEE_TC_CORE0_121_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_121_ISR_HND, 121)
#else
#error Invalid value for OSEE_TC_CORE0_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 121)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 121)
#endif /* OSEE_TC_CORE0_121_ISR_CAT */
#if (defined(OSEE_TC_CORE0_122_ISR_CAT))
#if (OSEE_TC_CORE0_122_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_122_ISR_TID, 122)
#elif (OSEE_TC_CORE0_122_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_122_ISR_HND, 122)
#else
#error Invalid value for OSEE_TC_CORE0_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 122)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 122)
#endif /* OSEE_TC_CORE0_122_ISR_CAT */
#if (defined(OSEE_TC_CORE0_123_ISR_CAT))
#if (OSEE_TC_CORE0_123_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_123_ISR_TID, 123)
#elif (OSEE_TC_CORE0_123_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_123_ISR_HND, 123)
#else
#error Invalid value for OSEE_TC_CORE0_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 123)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 123)
#endif /* OSEE_TC_CORE0_123_ISR_CAT */
#if (defined(OSEE_TC_CORE0_124_ISR_CAT))
#if (OSEE_TC_CORE0_124_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_124_ISR_TID, 124)
#elif (OSEE_TC_CORE0_124_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_124_ISR_HND, 124)
#else
#error Invalid value for OSEE_TC_CORE0_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 124)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 124)
#endif /* OSEE_TC_CORE0_124_ISR_CAT */
#if (defined(OSEE_TC_CORE0_125_ISR_CAT))
#if (OSEE_TC_CORE0_125_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_125_ISR_TID, 125)
#elif (OSEE_TC_CORE0_125_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_125_ISR_HND, 125)
#else
#error Invalid value for OSEE_TC_CORE0_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 125)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 125)
#endif /* OSEE_TC_CORE0_125_ISR_CAT */
#if (defined(OSEE_TC_CORE0_126_ISR_CAT))
#if (OSEE_TC_CORE0_126_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_126_ISR_TID, 126)
#elif (OSEE_TC_CORE0_126_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_126_ISR_HND, 126)
#else
#error Invalid value for OSEE_TC_CORE0_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 126)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 126)
#endif /* OSEE_TC_CORE0_126_ISR_CAT */
#if (defined(OSEE_TC_CORE0_127_ISR_CAT))
#if (OSEE_TC_CORE0_127_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_127_ISR_TID, 127)
#elif (OSEE_TC_CORE0_127_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_127_ISR_HND, 127)
#else
#error Invalid value for OSEE_TC_CORE0_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 127)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 127)
#endif /* OSEE_TC_CORE0_127_ISR_CAT */
#if (defined(OSEE_TC_CORE0_128_ISR_CAT))
#if (OSEE_TC_CORE0_128_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_128_ISR_TID, 128)
#elif (OSEE_TC_CORE0_128_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_128_ISR_HND, 128)
#else
#error Invalid value for OSEE_TC_CORE0_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 128)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 128)
#endif /* OSEE_TC_CORE0_128_ISR_CAT */
#if (defined(OSEE_TC_CORE0_129_ISR_CAT))
#if (OSEE_TC_CORE0_129_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_129_ISR_TID, 129)
#elif (OSEE_TC_CORE0_129_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_129_ISR_HND, 129)
#else
#error Invalid value for OSEE_TC_CORE0_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 129)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 129)
#endif /* OSEE_TC_CORE0_129_ISR_CAT */
#if (defined(OSEE_TC_CORE0_130_ISR_CAT))
#if (OSEE_TC_CORE0_130_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_130_ISR_TID, 130)
#elif (OSEE_TC_CORE0_130_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_130_ISR_HND, 130)
#else
#error Invalid value for OSEE_TC_CORE0_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 130)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 130)
#endif /* OSEE_TC_CORE0_130_ISR_CAT */
#if (defined(OSEE_TC_CORE0_131_ISR_CAT))
#if (OSEE_TC_CORE0_131_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_131_ISR_TID, 131)
#elif (OSEE_TC_CORE0_131_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_131_ISR_HND, 131)
#else
#error Invalid value for OSEE_TC_CORE0_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 131)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 131)
#endif /* OSEE_TC_CORE0_131_ISR_CAT */
#if (defined(OSEE_TC_CORE0_132_ISR_CAT))
#if (OSEE_TC_CORE0_132_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_132_ISR_TID, 132)
#elif (OSEE_TC_CORE0_132_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_132_ISR_HND, 132)
#else
#error Invalid value for OSEE_TC_CORE0_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 132)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 132)
#endif /* OSEE_TC_CORE0_132_ISR_CAT */
#if (defined(OSEE_TC_CORE0_133_ISR_CAT))
#if (OSEE_TC_CORE0_133_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_133_ISR_TID, 133)
#elif (OSEE_TC_CORE0_133_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_133_ISR_HND, 133)
#else
#error Invalid value for OSEE_TC_CORE0_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 133)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 133)
#endif /* OSEE_TC_CORE0_133_ISR_CAT */
#if (defined(OSEE_TC_CORE0_134_ISR_CAT))
#if (OSEE_TC_CORE0_134_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_134_ISR_TID, 134)
#elif (OSEE_TC_CORE0_134_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_134_ISR_HND, 134)
#else
#error Invalid value for OSEE_TC_CORE0_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 134)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 134)
#endif /* OSEE_TC_CORE0_134_ISR_CAT */
#if (defined(OSEE_TC_CORE0_135_ISR_CAT))
#if (OSEE_TC_CORE0_135_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_135_ISR_TID, 135)
#elif (OSEE_TC_CORE0_135_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_135_ISR_HND, 135)
#else
#error Invalid value for OSEE_TC_CORE0_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 135)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 135)
#endif /* OSEE_TC_CORE0_135_ISR_CAT */
#if (defined(OSEE_TC_CORE0_136_ISR_CAT))
#if (OSEE_TC_CORE0_136_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_136_ISR_TID, 136)
#elif (OSEE_TC_CORE0_136_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_136_ISR_HND, 136)
#else
#error Invalid value for OSEE_TC_CORE0_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 136)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 136)
#endif /* OSEE_TC_CORE0_136_ISR_CAT */
#if (defined(OSEE_TC_CORE0_137_ISR_CAT))
#if (OSEE_TC_CORE0_137_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_137_ISR_TID, 137)
#elif (OSEE_TC_CORE0_137_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_137_ISR_HND, 137)
#else
#error Invalid value for OSEE_TC_CORE0_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 137)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 137)
#endif /* OSEE_TC_CORE0_137_ISR_CAT */
#if (defined(OSEE_TC_CORE0_138_ISR_CAT))
#if (OSEE_TC_CORE0_138_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_138_ISR_TID, 138)
#elif (OSEE_TC_CORE0_138_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_138_ISR_HND, 138)
#else
#error Invalid value for OSEE_TC_CORE0_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 138)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 138)
#endif /* OSEE_TC_CORE0_138_ISR_CAT */
#if (defined(OSEE_TC_CORE0_139_ISR_CAT))
#if (OSEE_TC_CORE0_139_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_139_ISR_TID, 139)
#elif (OSEE_TC_CORE0_139_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_139_ISR_HND, 139)
#else
#error Invalid value for OSEE_TC_CORE0_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 139)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 139)
#endif /* OSEE_TC_CORE0_139_ISR_CAT */
#if (defined(OSEE_TC_CORE0_140_ISR_CAT))
#if (OSEE_TC_CORE0_140_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_140_ISR_TID, 140)
#elif (OSEE_TC_CORE0_140_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_140_ISR_HND, 140)
#else
#error Invalid value for OSEE_TC_CORE0_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 140)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 140)
#endif /* OSEE_TC_CORE0_140_ISR_CAT */
#if (defined(OSEE_TC_CORE0_141_ISR_CAT))
#if (OSEE_TC_CORE0_141_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_141_ISR_TID, 141)
#elif (OSEE_TC_CORE0_141_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_141_ISR_HND, 141)
#else
#error Invalid value for OSEE_TC_CORE0_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 141)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 141)
#endif /* OSEE_TC_CORE0_141_ISR_CAT */
#if (defined(OSEE_TC_CORE0_142_ISR_CAT))
#if (OSEE_TC_CORE0_142_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_142_ISR_TID, 142)
#elif (OSEE_TC_CORE0_142_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_142_ISR_HND, 142)
#else
#error Invalid value for OSEE_TC_CORE0_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 142)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 142)
#endif /* OSEE_TC_CORE0_142_ISR_CAT */
#if (defined(OSEE_TC_CORE0_143_ISR_CAT))
#if (OSEE_TC_CORE0_143_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_143_ISR_TID, 143)
#elif (OSEE_TC_CORE0_143_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_143_ISR_HND, 143)
#else
#error Invalid value for OSEE_TC_CORE0_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 143)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 143)
#endif /* OSEE_TC_CORE0_143_ISR_CAT */
#if (defined(OSEE_TC_CORE0_144_ISR_CAT))
#if (OSEE_TC_CORE0_144_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_144_ISR_TID, 144)
#elif (OSEE_TC_CORE0_144_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_144_ISR_HND, 144)
#else
#error Invalid value for OSEE_TC_CORE0_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 144)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 144)
#endif /* OSEE_TC_CORE0_144_ISR_CAT */
#if (defined(OSEE_TC_CORE0_145_ISR_CAT))
#if (OSEE_TC_CORE0_145_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_145_ISR_TID, 145)
#elif (OSEE_TC_CORE0_145_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_145_ISR_HND, 145)
#else
#error Invalid value for OSEE_TC_CORE0_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 145)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 145)
#endif /* OSEE_TC_CORE0_145_ISR_CAT */
#if (defined(OSEE_TC_CORE0_146_ISR_CAT))
#if (OSEE_TC_CORE0_146_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_146_ISR_TID, 146)
#elif (OSEE_TC_CORE0_146_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_146_ISR_HND, 146)
#else
#error Invalid value for OSEE_TC_CORE0_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 146)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 146)
#endif /* OSEE_TC_CORE0_146_ISR_CAT */
#if (defined(OSEE_TC_CORE0_147_ISR_CAT))
#if (OSEE_TC_CORE0_147_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_147_ISR_TID, 147)
#elif (OSEE_TC_CORE0_147_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_147_ISR_HND, 147)
#else
#error Invalid value for OSEE_TC_CORE0_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 147)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 147)
#endif /* OSEE_TC_CORE0_147_ISR_CAT */
#if (defined(OSEE_TC_CORE0_148_ISR_CAT))
#if (OSEE_TC_CORE0_148_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_148_ISR_TID, 148)
#elif (OSEE_TC_CORE0_148_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_148_ISR_HND, 148)
#else
#error Invalid value for OSEE_TC_CORE0_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 148)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 148)
#endif /* OSEE_TC_CORE0_148_ISR_CAT */
#if (defined(OSEE_TC_CORE0_149_ISR_CAT))
#if (OSEE_TC_CORE0_149_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_149_ISR_TID, 149)
#elif (OSEE_TC_CORE0_149_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_149_ISR_HND, 149)
#else
#error Invalid value for OSEE_TC_CORE0_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 149)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 149)
#endif /* OSEE_TC_CORE0_149_ISR_CAT */
#if (defined(OSEE_TC_CORE0_150_ISR_CAT))
#if (OSEE_TC_CORE0_150_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_150_ISR_TID, 150)
#elif (OSEE_TC_CORE0_150_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_150_ISR_HND, 150)
#else
#error Invalid value for OSEE_TC_CORE0_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 150)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 150)
#endif /* OSEE_TC_CORE0_150_ISR_CAT */
#if (defined(OSEE_TC_CORE0_151_ISR_CAT))
#if (OSEE_TC_CORE0_151_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_151_ISR_TID, 151)
#elif (OSEE_TC_CORE0_151_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_151_ISR_HND, 151)
#else
#error Invalid value for OSEE_TC_CORE0_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 151)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 151)
#endif /* OSEE_TC_CORE0_151_ISR_CAT */
#if (defined(OSEE_TC_CORE0_152_ISR_CAT))
#if (OSEE_TC_CORE0_152_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_152_ISR_TID, 152)
#elif (OSEE_TC_CORE0_152_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_152_ISR_HND, 152)
#else
#error Invalid value for OSEE_TC_CORE0_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 152)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 152)
#endif /* OSEE_TC_CORE0_152_ISR_CAT */
#if (defined(OSEE_TC_CORE0_153_ISR_CAT))
#if (OSEE_TC_CORE0_153_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_153_ISR_TID, 153)
#elif (OSEE_TC_CORE0_153_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_153_ISR_HND, 153)
#else
#error Invalid value for OSEE_TC_CORE0_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 153)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 153)
#endif /* OSEE_TC_CORE0_153_ISR_CAT */
#if (defined(OSEE_TC_CORE0_154_ISR_CAT))
#if (OSEE_TC_CORE0_154_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_154_ISR_TID, 154)
#elif (OSEE_TC_CORE0_154_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_154_ISR_HND, 154)
#else
#error Invalid value for OSEE_TC_CORE0_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 154)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 154)
#endif /* OSEE_TC_CORE0_154_ISR_CAT */
#if (defined(OSEE_TC_CORE0_155_ISR_CAT))
#if (OSEE_TC_CORE0_155_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_155_ISR_TID, 155)
#elif (OSEE_TC_CORE0_155_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_155_ISR_HND, 155)
#else
#error Invalid value for OSEE_TC_CORE0_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 155)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 155)
#endif /* OSEE_TC_CORE0_155_ISR_CAT */
#if (defined(OSEE_TC_CORE0_156_ISR_CAT))
#if (OSEE_TC_CORE0_156_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_156_ISR_TID, 156)
#elif (OSEE_TC_CORE0_156_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_156_ISR_HND, 156)
#else
#error Invalid value for OSEE_TC_CORE0_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 156)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 156)
#endif /* OSEE_TC_CORE0_156_ISR_CAT */
#if (defined(OSEE_TC_CORE0_157_ISR_CAT))
#if (OSEE_TC_CORE0_157_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_157_ISR_TID, 157)
#elif (OSEE_TC_CORE0_157_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_157_ISR_HND, 157)
#else
#error Invalid value for OSEE_TC_CORE0_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 157)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 157)
#endif /* OSEE_TC_CORE0_157_ISR_CAT */
#if (defined(OSEE_TC_CORE0_158_ISR_CAT))
#if (OSEE_TC_CORE0_158_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_158_ISR_TID, 158)
#elif (OSEE_TC_CORE0_158_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_158_ISR_HND, 158)
#else
#error Invalid value for OSEE_TC_CORE0_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 158)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 158)
#endif /* OSEE_TC_CORE0_158_ISR_CAT */
#if (defined(OSEE_TC_CORE0_159_ISR_CAT))
#if (OSEE_TC_CORE0_159_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_159_ISR_TID, 159)
#elif (OSEE_TC_CORE0_159_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_159_ISR_HND, 159)
#else
#error Invalid value for OSEE_TC_CORE0_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 159)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 159)
#endif /* OSEE_TC_CORE0_159_ISR_CAT */
#if (defined(OSEE_TC_CORE0_160_ISR_CAT))
#if (OSEE_TC_CORE0_160_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_160_ISR_TID, 160)
#elif (OSEE_TC_CORE0_160_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_160_ISR_HND, 160)
#else
#error Invalid value for OSEE_TC_CORE0_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 160)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 160)
#endif /* OSEE_TC_CORE0_160_ISR_CAT */
#if (defined(OSEE_TC_CORE0_161_ISR_CAT))
#if (OSEE_TC_CORE0_161_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_161_ISR_TID, 161)
#elif (OSEE_TC_CORE0_161_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_161_ISR_HND, 161)
#else
#error Invalid value for OSEE_TC_CORE0_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 161)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 161)
#endif /* OSEE_TC_CORE0_161_ISR_CAT */
#if (defined(OSEE_TC_CORE0_162_ISR_CAT))
#if (OSEE_TC_CORE0_162_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_162_ISR_TID, 162)
#elif (OSEE_TC_CORE0_162_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_162_ISR_HND, 162)
#else
#error Invalid value for OSEE_TC_CORE0_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 162)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 162)
#endif /* OSEE_TC_CORE0_162_ISR_CAT */
#if (defined(OSEE_TC_CORE0_163_ISR_CAT))
#if (OSEE_TC_CORE0_163_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_163_ISR_TID, 163)
#elif (OSEE_TC_CORE0_163_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_163_ISR_HND, 163)
#else
#error Invalid value for OSEE_TC_CORE0_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 163)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 163)
#endif /* OSEE_TC_CORE0_163_ISR_CAT */
#if (defined(OSEE_TC_CORE0_164_ISR_CAT))
#if (OSEE_TC_CORE0_164_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_164_ISR_TID, 164)
#elif (OSEE_TC_CORE0_164_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_164_ISR_HND, 164)
#else
#error Invalid value for OSEE_TC_CORE0_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 164)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 164)
#endif /* OSEE_TC_CORE0_164_ISR_CAT */
#if (defined(OSEE_TC_CORE0_165_ISR_CAT))
#if (OSEE_TC_CORE0_165_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_165_ISR_TID, 165)
#elif (OSEE_TC_CORE0_165_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_165_ISR_HND, 165)
#else
#error Invalid value for OSEE_TC_CORE0_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 165)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 165)
#endif /* OSEE_TC_CORE0_165_ISR_CAT */
#if (defined(OSEE_TC_CORE0_166_ISR_CAT))
#if (OSEE_TC_CORE0_166_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_166_ISR_TID, 166)
#elif (OSEE_TC_CORE0_166_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_166_ISR_HND, 166)
#else
#error Invalid value for OSEE_TC_CORE0_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 166)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 166)
#endif /* OSEE_TC_CORE0_166_ISR_CAT */
#if (defined(OSEE_TC_CORE0_167_ISR_CAT))
#if (OSEE_TC_CORE0_167_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_167_ISR_TID, 167)
#elif (OSEE_TC_CORE0_167_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_167_ISR_HND, 167)
#else
#error Invalid value for OSEE_TC_CORE0_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 167)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 167)
#endif /* OSEE_TC_CORE0_167_ISR_CAT */
#if (defined(OSEE_TC_CORE0_168_ISR_CAT))
#if (OSEE_TC_CORE0_168_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_168_ISR_TID, 168)
#elif (OSEE_TC_CORE0_168_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_168_ISR_HND, 168)
#else
#error Invalid value for OSEE_TC_CORE0_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 168)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 168)
#endif /* OSEE_TC_CORE0_168_ISR_CAT */
#if (defined(OSEE_TC_CORE0_169_ISR_CAT))
#if (OSEE_TC_CORE0_169_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_169_ISR_TID, 169)
#elif (OSEE_TC_CORE0_169_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_169_ISR_HND, 169)
#else
#error Invalid value for OSEE_TC_CORE0_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 169)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 169)
#endif /* OSEE_TC_CORE0_169_ISR_CAT */
#if (defined(OSEE_TC_CORE0_170_ISR_CAT))
#if (OSEE_TC_CORE0_170_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_170_ISR_TID, 170)
#elif (OSEE_TC_CORE0_170_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_170_ISR_HND, 170)
#else
#error Invalid value for OSEE_TC_CORE0_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 170)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 170)
#endif /* OSEE_TC_CORE0_170_ISR_CAT */
#if (defined(OSEE_TC_CORE0_171_ISR_CAT))
#if (OSEE_TC_CORE0_171_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_171_ISR_TID, 171)
#elif (OSEE_TC_CORE0_171_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_171_ISR_HND, 171)
#else
#error Invalid value for OSEE_TC_CORE0_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 171)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 171)
#endif /* OSEE_TC_CORE0_171_ISR_CAT */
#if (defined(OSEE_TC_CORE0_172_ISR_CAT))
#if (OSEE_TC_CORE0_172_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_172_ISR_TID, 172)
#elif (OSEE_TC_CORE0_172_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_172_ISR_HND, 172)
#else
#error Invalid value for OSEE_TC_CORE0_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 172)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 172)
#endif /* OSEE_TC_CORE0_172_ISR_CAT */
#if (defined(OSEE_TC_CORE0_173_ISR_CAT))
#if (OSEE_TC_CORE0_173_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_173_ISR_TID, 173)
#elif (OSEE_TC_CORE0_173_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_173_ISR_HND, 173)
#else
#error Invalid value for OSEE_TC_CORE0_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 173)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 173)
#endif /* OSEE_TC_CORE0_173_ISR_CAT */
#if (defined(OSEE_TC_CORE0_174_ISR_CAT))
#if (OSEE_TC_CORE0_174_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_174_ISR_TID, 174)
#elif (OSEE_TC_CORE0_174_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_174_ISR_HND, 174)
#else
#error Invalid value for OSEE_TC_CORE0_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 174)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 174)
#endif /* OSEE_TC_CORE0_174_ISR_CAT */
#if (defined(OSEE_TC_CORE0_175_ISR_CAT))
#if (OSEE_TC_CORE0_175_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_175_ISR_TID, 175)
#elif (OSEE_TC_CORE0_175_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_175_ISR_HND, 175)
#else
#error Invalid value for OSEE_TC_CORE0_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 175)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 175)
#endif /* OSEE_TC_CORE0_175_ISR_CAT */
#if (defined(OSEE_TC_CORE0_176_ISR_CAT))
#if (OSEE_TC_CORE0_176_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_176_ISR_TID, 176)
#elif (OSEE_TC_CORE0_176_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_176_ISR_HND, 176)
#else
#error Invalid value for OSEE_TC_CORE0_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 176)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 176)
#endif /* OSEE_TC_CORE0_176_ISR_CAT */
#if (defined(OSEE_TC_CORE0_177_ISR_CAT))
#if (OSEE_TC_CORE0_177_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_177_ISR_TID, 177)
#elif (OSEE_TC_CORE0_177_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_177_ISR_HND, 177)
#else
#error Invalid value for OSEE_TC_CORE0_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 177)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 177)
#endif /* OSEE_TC_CORE0_177_ISR_CAT */
#if (defined(OSEE_TC_CORE0_178_ISR_CAT))
#if (OSEE_TC_CORE0_178_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_178_ISR_TID, 178)
#elif (OSEE_TC_CORE0_178_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_178_ISR_HND, 178)
#else
#error Invalid value for OSEE_TC_CORE0_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 178)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 178)
#endif /* OSEE_TC_CORE0_178_ISR_CAT */
#if (defined(OSEE_TC_CORE0_179_ISR_CAT))
#if (OSEE_TC_CORE0_179_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_179_ISR_TID, 179)
#elif (OSEE_TC_CORE0_179_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_179_ISR_HND, 179)
#else
#error Invalid value for OSEE_TC_CORE0_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 179)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 179)
#endif /* OSEE_TC_CORE0_179_ISR_CAT */
#if (defined(OSEE_TC_CORE0_180_ISR_CAT))
#if (OSEE_TC_CORE0_180_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_180_ISR_TID, 180)
#elif (OSEE_TC_CORE0_180_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_180_ISR_HND, 180)
#else
#error Invalid value for OSEE_TC_CORE0_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 180)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 180)
#endif /* OSEE_TC_CORE0_180_ISR_CAT */
#if (defined(OSEE_TC_CORE0_181_ISR_CAT))
#if (OSEE_TC_CORE0_181_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_181_ISR_TID, 181)
#elif (OSEE_TC_CORE0_181_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_181_ISR_HND, 181)
#else
#error Invalid value for OSEE_TC_CORE0_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 181)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 181)
#endif /* OSEE_TC_CORE0_181_ISR_CAT */
#if (defined(OSEE_TC_CORE0_182_ISR_CAT))
#if (OSEE_TC_CORE0_182_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_182_ISR_TID, 182)
#elif (OSEE_TC_CORE0_182_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_182_ISR_HND, 182)
#else
#error Invalid value for OSEE_TC_CORE0_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 182)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 182)
#endif /* OSEE_TC_CORE0_182_ISR_CAT */
#if (defined(OSEE_TC_CORE0_183_ISR_CAT))
#if (OSEE_TC_CORE0_183_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_183_ISR_TID, 183)
#elif (OSEE_TC_CORE0_183_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_183_ISR_HND, 183)
#else
#error Invalid value for OSEE_TC_CORE0_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 183)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 183)
#endif /* OSEE_TC_CORE0_183_ISR_CAT */
#if (defined(OSEE_TC_CORE0_184_ISR_CAT))
#if (OSEE_TC_CORE0_184_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_184_ISR_TID, 184)
#elif (OSEE_TC_CORE0_184_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_184_ISR_HND, 184)
#else
#error Invalid value for OSEE_TC_CORE0_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 184)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 184)
#endif /* OSEE_TC_CORE0_184_ISR_CAT */
#if (defined(OSEE_TC_CORE0_185_ISR_CAT))
#if (OSEE_TC_CORE0_185_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_185_ISR_TID, 185)
#elif (OSEE_TC_CORE0_185_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_185_ISR_HND, 185)
#else
#error Invalid value for OSEE_TC_CORE0_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 185)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 185)
#endif /* OSEE_TC_CORE0_185_ISR_CAT */
#if (defined(OSEE_TC_CORE0_186_ISR_CAT))
#if (OSEE_TC_CORE0_186_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_186_ISR_TID, 186)
#elif (OSEE_TC_CORE0_186_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_186_ISR_HND, 186)
#else
#error Invalid value for OSEE_TC_CORE0_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 186)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 186)
#endif /* OSEE_TC_CORE0_186_ISR_CAT */
#if (defined(OSEE_TC_CORE0_187_ISR_CAT))
#if (OSEE_TC_CORE0_187_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_187_ISR_TID, 187)
#elif (OSEE_TC_CORE0_187_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_187_ISR_HND, 187)
#else
#error Invalid value for OSEE_TC_CORE0_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 187)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 187)
#endif /* OSEE_TC_CORE0_187_ISR_CAT */
#if (defined(OSEE_TC_CORE0_188_ISR_CAT))
#if (OSEE_TC_CORE0_188_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_188_ISR_TID, 188)
#elif (OSEE_TC_CORE0_188_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_188_ISR_HND, 188)
#else
#error Invalid value for OSEE_TC_CORE0_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 188)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 188)
#endif /* OSEE_TC_CORE0_188_ISR_CAT */
#if (defined(OSEE_TC_CORE0_189_ISR_CAT))
#if (OSEE_TC_CORE0_189_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_189_ISR_TID, 189)
#elif (OSEE_TC_CORE0_189_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_189_ISR_HND, 189)
#else
#error Invalid value for OSEE_TC_CORE0_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 189)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 189)
#endif /* OSEE_TC_CORE0_189_ISR_CAT */
#if (defined(OSEE_TC_CORE0_190_ISR_CAT))
#if (OSEE_TC_CORE0_190_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_190_ISR_TID, 190)
#elif (OSEE_TC_CORE0_190_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_190_ISR_HND, 190)
#else
#error Invalid value for OSEE_TC_CORE0_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 190)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 190)
#endif /* OSEE_TC_CORE0_190_ISR_CAT */
#if (defined(OSEE_TC_CORE0_191_ISR_CAT))
#if (OSEE_TC_CORE0_191_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_191_ISR_TID, 191)
#elif (OSEE_TC_CORE0_191_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_191_ISR_HND, 191)
#else
#error Invalid value for OSEE_TC_CORE0_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 191)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 191)
#endif /* OSEE_TC_CORE0_191_ISR_CAT */
#if (defined(OSEE_TC_CORE0_192_ISR_CAT))
#if (OSEE_TC_CORE0_192_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_192_ISR_TID, 192)
#elif (OSEE_TC_CORE0_192_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_192_ISR_HND, 192)
#else
#error Invalid value for OSEE_TC_CORE0_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 192)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 192)
#endif /* OSEE_TC_CORE0_192_ISR_CAT */
#if (defined(OSEE_TC_CORE0_193_ISR_CAT))
#if (OSEE_TC_CORE0_193_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_193_ISR_TID, 193)
#elif (OSEE_TC_CORE0_193_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_193_ISR_HND, 193)
#else
#error Invalid value for OSEE_TC_CORE0_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 193)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 193)
#endif /* OSEE_TC_CORE0_193_ISR_CAT */
#if (defined(OSEE_TC_CORE0_194_ISR_CAT))
#if (OSEE_TC_CORE0_194_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_194_ISR_TID, 194)
#elif (OSEE_TC_CORE0_194_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_194_ISR_HND, 194)
#else
#error Invalid value for OSEE_TC_CORE0_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 194)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 194)
#endif /* OSEE_TC_CORE0_194_ISR_CAT */
#if (defined(OSEE_TC_CORE0_195_ISR_CAT))
#if (OSEE_TC_CORE0_195_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_195_ISR_TID, 195)
#elif (OSEE_TC_CORE0_195_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_195_ISR_HND, 195)
#else
#error Invalid value for OSEE_TC_CORE0_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 195)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 195)
#endif /* OSEE_TC_CORE0_195_ISR_CAT */
#if (defined(OSEE_TC_CORE0_196_ISR_CAT))
#if (OSEE_TC_CORE0_196_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_196_ISR_TID, 196)
#elif (OSEE_TC_CORE0_196_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_196_ISR_HND, 196)
#else
#error Invalid value for OSEE_TC_CORE0_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 196)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 196)
#endif /* OSEE_TC_CORE0_196_ISR_CAT */
#if (defined(OSEE_TC_CORE0_197_ISR_CAT))
#if (OSEE_TC_CORE0_197_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_197_ISR_TID, 197)
#elif (OSEE_TC_CORE0_197_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_197_ISR_HND, 197)
#else
#error Invalid value for OSEE_TC_CORE0_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 197)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 197)
#endif /* OSEE_TC_CORE0_197_ISR_CAT */
#if (defined(OSEE_TC_CORE0_198_ISR_CAT))
#if (OSEE_TC_CORE0_198_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_198_ISR_TID, 198)
#elif (OSEE_TC_CORE0_198_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_198_ISR_HND, 198)
#else
#error Invalid value for OSEE_TC_CORE0_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 198)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 198)
#endif /* OSEE_TC_CORE0_198_ISR_CAT */
#if (defined(OSEE_TC_CORE0_199_ISR_CAT))
#if (OSEE_TC_CORE0_199_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_199_ISR_TID, 199)
#elif (OSEE_TC_CORE0_199_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_199_ISR_HND, 199)
#else
#error Invalid value for OSEE_TC_CORE0_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 199)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 199)
#endif /* OSEE_TC_CORE0_199_ISR_CAT */
#if (defined(OSEE_TC_CORE0_200_ISR_CAT))
#if (OSEE_TC_CORE0_200_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_200_ISR_TID, 200)
#elif (OSEE_TC_CORE0_200_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_200_ISR_HND, 200)
#else
#error Invalid value for OSEE_TC_CORE0_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 200)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 200)
#endif /* OSEE_TC_CORE0_200_ISR_CAT */
#if (defined(OSEE_TC_CORE0_201_ISR_CAT))
#if (OSEE_TC_CORE0_201_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_201_ISR_TID, 201)
#elif (OSEE_TC_CORE0_201_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_201_ISR_HND, 201)
#else
#error Invalid value for OSEE_TC_CORE0_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 201)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 201)
#endif /* OSEE_TC_CORE0_201_ISR_CAT */
#if (defined(OSEE_TC_CORE0_202_ISR_CAT))
#if (OSEE_TC_CORE0_202_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_202_ISR_TID, 202)
#elif (OSEE_TC_CORE0_202_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_202_ISR_HND, 202)
#else
#error Invalid value for OSEE_TC_CORE0_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 202)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 202)
#endif /* OSEE_TC_CORE0_202_ISR_CAT */
#if (defined(OSEE_TC_CORE0_203_ISR_CAT))
#if (OSEE_TC_CORE0_203_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_203_ISR_TID, 203)
#elif (OSEE_TC_CORE0_203_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_203_ISR_HND, 203)
#else
#error Invalid value for OSEE_TC_CORE0_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 203)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 203)
#endif /* OSEE_TC_CORE0_203_ISR_CAT */
#if (defined(OSEE_TC_CORE0_204_ISR_CAT))
#if (OSEE_TC_CORE0_204_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_204_ISR_TID, 204)
#elif (OSEE_TC_CORE0_204_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_204_ISR_HND, 204)
#else
#error Invalid value for OSEE_TC_CORE0_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 204)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 204)
#endif /* OSEE_TC_CORE0_204_ISR_CAT */
#if (defined(OSEE_TC_CORE0_205_ISR_CAT))
#if (OSEE_TC_CORE0_205_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_205_ISR_TID, 205)
#elif (OSEE_TC_CORE0_205_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_205_ISR_HND, 205)
#else
#error Invalid value for OSEE_TC_CORE0_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 205)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 205)
#endif /* OSEE_TC_CORE0_205_ISR_CAT */
#if (defined(OSEE_TC_CORE0_206_ISR_CAT))
#if (OSEE_TC_CORE0_206_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_206_ISR_TID, 206)
#elif (OSEE_TC_CORE0_206_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_206_ISR_HND, 206)
#else
#error Invalid value for OSEE_TC_CORE0_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 206)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 206)
#endif /* OSEE_TC_CORE0_206_ISR_CAT */
#if (defined(OSEE_TC_CORE0_207_ISR_CAT))
#if (OSEE_TC_CORE0_207_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_207_ISR_TID, 207)
#elif (OSEE_TC_CORE0_207_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_207_ISR_HND, 207)
#else
#error Invalid value for OSEE_TC_CORE0_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 207)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 207)
#endif /* OSEE_TC_CORE0_207_ISR_CAT */
#if (defined(OSEE_TC_CORE0_208_ISR_CAT))
#if (OSEE_TC_CORE0_208_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_208_ISR_TID, 208)
#elif (OSEE_TC_CORE0_208_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_208_ISR_HND, 208)
#else
#error Invalid value for OSEE_TC_CORE0_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 208)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 208)
#endif /* OSEE_TC_CORE0_208_ISR_CAT */
#if (defined(OSEE_TC_CORE0_209_ISR_CAT))
#if (OSEE_TC_CORE0_209_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_209_ISR_TID, 209)
#elif (OSEE_TC_CORE0_209_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_209_ISR_HND, 209)
#else
#error Invalid value for OSEE_TC_CORE0_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 209)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 209)
#endif /* OSEE_TC_CORE0_209_ISR_CAT */
#if (defined(OSEE_TC_CORE0_210_ISR_CAT))
#if (OSEE_TC_CORE0_210_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_210_ISR_TID, 210)
#elif (OSEE_TC_CORE0_210_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_210_ISR_HND, 210)
#else
#error Invalid value for OSEE_TC_CORE0_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 210)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 210)
#endif /* OSEE_TC_CORE0_210_ISR_CAT */
#if (defined(OSEE_TC_CORE0_211_ISR_CAT))
#if (OSEE_TC_CORE0_211_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_211_ISR_TID, 211)
#elif (OSEE_TC_CORE0_211_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_211_ISR_HND, 211)
#else
#error Invalid value for OSEE_TC_CORE0_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 211)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 211)
#endif /* OSEE_TC_CORE0_211_ISR_CAT */
#if (defined(OSEE_TC_CORE0_212_ISR_CAT))
#if (OSEE_TC_CORE0_212_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_212_ISR_TID, 212)
#elif (OSEE_TC_CORE0_212_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_212_ISR_HND, 212)
#else
#error Invalid value for OSEE_TC_CORE0_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 212)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 212)
#endif /* OSEE_TC_CORE0_212_ISR_CAT */
#if (defined(OSEE_TC_CORE0_213_ISR_CAT))
#if (OSEE_TC_CORE0_213_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_213_ISR_TID, 213)
#elif (OSEE_TC_CORE0_213_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_213_ISR_HND, 213)
#else
#error Invalid value for OSEE_TC_CORE0_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 213)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 213)
#endif /* OSEE_TC_CORE0_213_ISR_CAT */
#if (defined(OSEE_TC_CORE0_214_ISR_CAT))
#if (OSEE_TC_CORE0_214_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_214_ISR_TID, 214)
#elif (OSEE_TC_CORE0_214_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_214_ISR_HND, 214)
#else
#error Invalid value for OSEE_TC_CORE0_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 214)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 214)
#endif /* OSEE_TC_CORE0_214_ISR_CAT */
#if (defined(OSEE_TC_CORE0_215_ISR_CAT))
#if (OSEE_TC_CORE0_215_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_215_ISR_TID, 215)
#elif (OSEE_TC_CORE0_215_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_215_ISR_HND, 215)
#else
#error Invalid value for OSEE_TC_CORE0_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 215)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 215)
#endif /* OSEE_TC_CORE0_215_ISR_CAT */
#if (defined(OSEE_TC_CORE0_216_ISR_CAT))
#if (OSEE_TC_CORE0_216_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_216_ISR_TID, 216)
#elif (OSEE_TC_CORE0_216_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_216_ISR_HND, 216)
#else
#error Invalid value for OSEE_TC_CORE0_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 216)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 216)
#endif /* OSEE_TC_CORE0_216_ISR_CAT */
#if (defined(OSEE_TC_CORE0_217_ISR_CAT))
#if (OSEE_TC_CORE0_217_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_217_ISR_TID, 217)
#elif (OSEE_TC_CORE0_217_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_217_ISR_HND, 217)
#else
#error Invalid value for OSEE_TC_CORE0_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 217)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 217)
#endif /* OSEE_TC_CORE0_217_ISR_CAT */
#if (defined(OSEE_TC_CORE0_218_ISR_CAT))
#if (OSEE_TC_CORE0_218_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_218_ISR_TID, 218)
#elif (OSEE_TC_CORE0_218_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_218_ISR_HND, 218)
#else
#error Invalid value for OSEE_TC_CORE0_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 218)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 218)
#endif /* OSEE_TC_CORE0_218_ISR_CAT */
#if (defined(OSEE_TC_CORE0_219_ISR_CAT))
#if (OSEE_TC_CORE0_219_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_219_ISR_TID, 219)
#elif (OSEE_TC_CORE0_219_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_219_ISR_HND, 219)
#else
#error Invalid value for OSEE_TC_CORE0_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 219)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 219)
#endif /* OSEE_TC_CORE0_219_ISR_CAT */
#if (defined(OSEE_TC_CORE0_220_ISR_CAT))
#if (OSEE_TC_CORE0_220_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_220_ISR_TID, 220)
#elif (OSEE_TC_CORE0_220_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_220_ISR_HND, 220)
#else
#error Invalid value for OSEE_TC_CORE0_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 220)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 220)
#endif /* OSEE_TC_CORE0_220_ISR_CAT */
#if (defined(OSEE_TC_CORE0_221_ISR_CAT))
#if (OSEE_TC_CORE0_221_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_221_ISR_TID, 221)
#elif (OSEE_TC_CORE0_221_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_221_ISR_HND, 221)
#else
#error Invalid value for OSEE_TC_CORE0_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 221)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 221)
#endif /* OSEE_TC_CORE0_221_ISR_CAT */
#if (defined(OSEE_TC_CORE0_222_ISR_CAT))
#if (OSEE_TC_CORE0_222_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_222_ISR_TID, 222)
#elif (OSEE_TC_CORE0_222_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_222_ISR_HND, 222)
#else
#error Invalid value for OSEE_TC_CORE0_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 222)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 222)
#endif /* OSEE_TC_CORE0_222_ISR_CAT */
#if (defined(OSEE_TC_CORE0_223_ISR_CAT))
#if (OSEE_TC_CORE0_223_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_223_ISR_TID, 223)
#elif (OSEE_TC_CORE0_223_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_223_ISR_HND, 223)
#else
#error Invalid value for OSEE_TC_CORE0_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 223)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 223)
#endif /* OSEE_TC_CORE0_223_ISR_CAT */
#if (defined(OSEE_TC_CORE0_224_ISR_CAT))
#if (OSEE_TC_CORE0_224_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_224_ISR_TID, 224)
#elif (OSEE_TC_CORE0_224_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_224_ISR_HND, 224)
#else
#error Invalid value for OSEE_TC_CORE0_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 224)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 224)
#endif /* OSEE_TC_CORE0_224_ISR_CAT */
#if (defined(OSEE_TC_CORE0_225_ISR_CAT))
#if (OSEE_TC_CORE0_225_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_225_ISR_TID, 225)
#elif (OSEE_TC_CORE0_225_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_225_ISR_HND, 225)
#else
#error Invalid value for OSEE_TC_CORE0_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 225)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 225)
#endif /* OSEE_TC_CORE0_225_ISR_CAT */
#if (defined(OSEE_TC_CORE0_226_ISR_CAT))
#if (OSEE_TC_CORE0_226_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_226_ISR_TID, 226)
#elif (OSEE_TC_CORE0_226_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_226_ISR_HND, 226)
#else
#error Invalid value for OSEE_TC_CORE0_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 226)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 226)
#endif /* OSEE_TC_CORE0_226_ISR_CAT */
#if (defined(OSEE_TC_CORE0_227_ISR_CAT))
#if (OSEE_TC_CORE0_227_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_227_ISR_TID, 227)
#elif (OSEE_TC_CORE0_227_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_227_ISR_HND, 227)
#else
#error Invalid value for OSEE_TC_CORE0_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 227)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 227)
#endif /* OSEE_TC_CORE0_227_ISR_CAT */
#if (defined(OSEE_TC_CORE0_228_ISR_CAT))
#if (OSEE_TC_CORE0_228_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_228_ISR_TID, 228)
#elif (OSEE_TC_CORE0_228_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_228_ISR_HND, 228)
#else
#error Invalid value for OSEE_TC_CORE0_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 228)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 228)
#endif /* OSEE_TC_CORE0_228_ISR_CAT */
#if (defined(OSEE_TC_CORE0_229_ISR_CAT))
#if (OSEE_TC_CORE0_229_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_229_ISR_TID, 229)
#elif (OSEE_TC_CORE0_229_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_229_ISR_HND, 229)
#else
#error Invalid value for OSEE_TC_CORE0_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 229)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 229)
#endif /* OSEE_TC_CORE0_229_ISR_CAT */
#if (defined(OSEE_TC_CORE0_230_ISR_CAT))
#if (OSEE_TC_CORE0_230_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_230_ISR_TID, 230)
#elif (OSEE_TC_CORE0_230_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_230_ISR_HND, 230)
#else
#error Invalid value for OSEE_TC_CORE0_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 230)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 230)
#endif /* OSEE_TC_CORE0_230_ISR_CAT */
#if (defined(OSEE_TC_CORE0_231_ISR_CAT))
#if (OSEE_TC_CORE0_231_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_231_ISR_TID, 231)
#elif (OSEE_TC_CORE0_231_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_231_ISR_HND, 231)
#else
#error Invalid value for OSEE_TC_CORE0_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 231)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 231)
#endif /* OSEE_TC_CORE0_231_ISR_CAT */
#if (defined(OSEE_TC_CORE0_232_ISR_CAT))
#if (OSEE_TC_CORE0_232_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_232_ISR_TID, 232)
#elif (OSEE_TC_CORE0_232_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_232_ISR_HND, 232)
#else
#error Invalid value for OSEE_TC_CORE0_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 232)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 232)
#endif /* OSEE_TC_CORE0_232_ISR_CAT */
#if (defined(OSEE_TC_CORE0_233_ISR_CAT))
#if (OSEE_TC_CORE0_233_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_233_ISR_TID, 233)
#elif (OSEE_TC_CORE0_233_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_233_ISR_HND, 233)
#else
#error Invalid value for OSEE_TC_CORE0_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 233)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 233)
#endif /* OSEE_TC_CORE0_233_ISR_CAT */
#if (defined(OSEE_TC_CORE0_234_ISR_CAT))
#if (OSEE_TC_CORE0_234_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_234_ISR_TID, 234)
#elif (OSEE_TC_CORE0_234_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_234_ISR_HND, 234)
#else
#error Invalid value for OSEE_TC_CORE0_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 234)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 234)
#endif /* OSEE_TC_CORE0_234_ISR_CAT */
#if (defined(OSEE_TC_CORE0_235_ISR_CAT))
#if (OSEE_TC_CORE0_235_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_235_ISR_TID, 235)
#elif (OSEE_TC_CORE0_235_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_235_ISR_HND, 235)
#else
#error Invalid value for OSEE_TC_CORE0_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 235)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 235)
#endif /* OSEE_TC_CORE0_235_ISR_CAT */
#if (defined(OSEE_TC_CORE0_236_ISR_CAT))
#if (OSEE_TC_CORE0_236_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_236_ISR_TID, 236)
#elif (OSEE_TC_CORE0_236_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_236_ISR_HND, 236)
#else
#error Invalid value for OSEE_TC_CORE0_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 236)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 236)
#endif /* OSEE_TC_CORE0_236_ISR_CAT */
#if (defined(OSEE_TC_CORE0_237_ISR_CAT))
#if (OSEE_TC_CORE0_237_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_237_ISR_TID, 237)
#elif (OSEE_TC_CORE0_237_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_237_ISR_HND, 237)
#else
#error Invalid value for OSEE_TC_CORE0_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 237)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 237)
#endif /* OSEE_TC_CORE0_237_ISR_CAT */
#if (defined(OSEE_TC_CORE0_238_ISR_CAT))
#if (OSEE_TC_CORE0_238_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_238_ISR_TID, 238)
#elif (OSEE_TC_CORE0_238_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_238_ISR_HND, 238)
#else
#error Invalid value for OSEE_TC_CORE0_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 238)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 238)
#endif /* OSEE_TC_CORE0_238_ISR_CAT */
#if (defined(OSEE_TC_CORE0_239_ISR_CAT))
#if (OSEE_TC_CORE0_239_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_239_ISR_TID, 239)
#elif (OSEE_TC_CORE0_239_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_239_ISR_HND, 239)
#else
#error Invalid value for OSEE_TC_CORE0_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 239)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 239)
#endif /* OSEE_TC_CORE0_239_ISR_CAT */
#if (defined(OSEE_TC_CORE0_240_ISR_CAT))
#if (OSEE_TC_CORE0_240_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_240_ISR_TID, 240)
#elif (OSEE_TC_CORE0_240_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_240_ISR_HND, 240)
#else
#error Invalid value for OSEE_TC_CORE0_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 240)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 240)
#endif /* OSEE_TC_CORE0_240_ISR_CAT */
#if (defined(OSEE_TC_CORE0_241_ISR_CAT))
#if (OSEE_TC_CORE0_241_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_241_ISR_TID, 241)
#elif (OSEE_TC_CORE0_241_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_241_ISR_HND, 241)
#else
#error Invalid value for OSEE_TC_CORE0_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 241)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 241)
#endif /* OSEE_TC_CORE0_241_ISR_CAT */
#if (defined(OSEE_TC_CORE0_242_ISR_CAT))
#if (OSEE_TC_CORE0_242_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_242_ISR_TID, 242)
#elif (OSEE_TC_CORE0_242_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_242_ISR_HND, 242)
#else
#error Invalid value for OSEE_TC_CORE0_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 242)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 242)
#endif /* OSEE_TC_CORE0_242_ISR_CAT */
#if (defined(OSEE_TC_CORE0_243_ISR_CAT))
#if (OSEE_TC_CORE0_243_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_243_ISR_TID, 243)
#elif (OSEE_TC_CORE0_243_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_243_ISR_HND, 243)
#else
#error Invalid value for OSEE_TC_CORE0_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 243)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 243)
#endif /* OSEE_TC_CORE0_243_ISR_CAT */
#if (defined(OSEE_TC_CORE0_244_ISR_CAT))
#if (OSEE_TC_CORE0_244_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_244_ISR_TID, 244)
#elif (OSEE_TC_CORE0_244_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_244_ISR_HND, 244)
#else
#error Invalid value for OSEE_TC_CORE0_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 244)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 244)
#endif /* OSEE_TC_CORE0_244_ISR_CAT */
#if (defined(OSEE_TC_CORE0_245_ISR_CAT))
#if (OSEE_TC_CORE0_245_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_245_ISR_TID, 245)
#elif (OSEE_TC_CORE0_245_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_245_ISR_HND, 245)
#else
#error Invalid value for OSEE_TC_CORE0_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 245)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 245)
#endif /* OSEE_TC_CORE0_245_ISR_CAT */
#if (defined(OSEE_TC_CORE0_246_ISR_CAT))
#if (OSEE_TC_CORE0_246_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_246_ISR_TID, 246)
#elif (OSEE_TC_CORE0_246_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_246_ISR_HND, 246)
#else
#error Invalid value for OSEE_TC_CORE0_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 246)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 246)
#endif /* OSEE_TC_CORE0_246_ISR_CAT */
#if (defined(OSEE_TC_CORE0_247_ISR_CAT))
#if (OSEE_TC_CORE0_247_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_247_ISR_TID, 247)
#elif (OSEE_TC_CORE0_247_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_247_ISR_HND, 247)
#else
#error Invalid value for OSEE_TC_CORE0_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 247)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 247)
#endif /* OSEE_TC_CORE0_247_ISR_CAT */
#if (defined(OSEE_TC_CORE0_248_ISR_CAT))
#if (OSEE_TC_CORE0_248_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_248_ISR_TID, 248)
#elif (OSEE_TC_CORE0_248_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_248_ISR_HND, 248)
#else
#error Invalid value for OSEE_TC_CORE0_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 248)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 248)
#endif /* OSEE_TC_CORE0_248_ISR_CAT */
#if (defined(OSEE_TC_CORE0_249_ISR_CAT))
#if (OSEE_TC_CORE0_249_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_249_ISR_TID, 249)
#elif (OSEE_TC_CORE0_249_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_249_ISR_HND, 249)
#else
#error Invalid value for OSEE_TC_CORE0_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 249)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 249)
#endif /* OSEE_TC_CORE0_249_ISR_CAT */
#if (defined(OSEE_TC_CORE0_250_ISR_CAT))
#if (OSEE_TC_CORE0_250_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_250_ISR_TID, 250)
#elif (OSEE_TC_CORE0_250_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_250_ISR_HND, 250)
#else
#error Invalid value for OSEE_TC_CORE0_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 250)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 250)
#endif /* OSEE_TC_CORE0_250_ISR_CAT */
#if (defined(OSEE_TC_CORE0_251_ISR_CAT))
#if (OSEE_TC_CORE0_251_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_251_ISR_TID, 251)
#elif (OSEE_TC_CORE0_251_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_251_ISR_HND, 251)
#else
#error Invalid value for OSEE_TC_CORE0_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 251)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 251)
#endif /* OSEE_TC_CORE0_251_ISR_CAT */
#if (defined(OSEE_TC_CORE0_252_ISR_CAT))
#if (OSEE_TC_CORE0_252_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_252_ISR_TID, 252)
#elif (OSEE_TC_CORE0_252_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_252_ISR_HND, 252)
#else
#error Invalid value for OSEE_TC_CORE0_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 252)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 252)
#endif /* OSEE_TC_CORE0_252_ISR_CAT */
#if (defined(OSEE_TC_CORE0_253_ISR_CAT))
#if (OSEE_TC_CORE0_253_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_253_ISR_TID, 253)
#elif (OSEE_TC_CORE0_253_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_253_ISR_HND, 253)
#else
#error Invalid value for OSEE_TC_CORE0_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 253)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 253)
#endif /* OSEE_TC_CORE0_253_ISR_CAT */
#if (defined(OSEE_TC_CORE0_254_ISR_CAT))
#if (OSEE_TC_CORE0_254_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_254_ISR_TID, 254)
#elif (OSEE_TC_CORE0_254_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_254_ISR_HND, 254)
#else
#error Invalid value for OSEE_TC_CORE0_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 254)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 254)
#endif /* OSEE_TC_CORE0_254_ISR_CAT */
#if (defined(OSEE_TC_CORE0_255_ISR_CAT))
#if (OSEE_TC_CORE0_255_ISR_CAT == 2)
OSEE_ISR2_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_255_ISR_TID, 255)
#elif (OSEE_TC_CORE0_255_ISR_CAT == 1)
OSEE_ISR1_DEF(OSEE_CORE0_S, 0, OSEE_TC_CORE0_255_ISR_HND, 255)
#else
#error Invalid value for OSEE_TC_CORE0_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE0_ISR_MAX_PRIO >= 255)
OSEE_ISR_ALIGN(OSEE_CORE0_S, 0, 255)
#endif /* OSEE_TC_CORE0_255_ISR_CAT */
#endif /* OSEE_TC_CORE0_ISR_MAX_PRIO */
#if (defined(__GNUC__))
__asm__ ("\t.size __INTTAB0, . - __INTTAB0\n\
\t.section .text,\"ax\",@progbits");
#endif /* __GNUC__ */

#if (!defined(OSEE_SINGLECORE))

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x02U)
#if (defined(__GNUC__))
__asm__ ("\n\
  .section .inttab_cpu1, \"ax\", @progbits\n\
  .globl __INTTAB1\n\
__INTTAB1:");
/* ERIKA's Interrupt Vector Definition */
#if (defined(OSEE_TC_CORE1_ISR_MAX_PRIO))
__asm__(
"  .skip 0x20");
#endif /* OSEE_TC_CORE1_ISR_MAX_PRIO */
#endif /* __GNUC__ */
#if (defined(OSEE_TC_CORE1_ISR_MAX_PRIO))
OSEE_ISR2_DEF(_core1_, 1, -1, 1)
#if (defined(OSEE_TC_CORE1_2_ISR_CAT))
#if (OSEE_TC_CORE1_2_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_2_ISR_TID, 2)
#elif (OSEE_TC_CORE1_2_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_2_ISR_HND, 2)
#else
#error Invalid value for OSEE_TC_CORE1_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 2)
OSEE_ISR_ALIGN(_core1_, 1, 2)
#endif /* OSEE_TC_CORE1_2_ISR_CAT */
#if (defined(OSEE_TC_CORE1_3_ISR_CAT))
#if (OSEE_TC_CORE1_3_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_3_ISR_TID, 3)
#elif (OSEE_TC_CORE1_3_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_3_ISR_HND, 3)
#else
#error Invalid value for OSEE_TC_CORE1_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 3)
OSEE_ISR_ALIGN(_core1_, 1, 3)
#endif /* OSEE_TC_CORE1_3_ISR_CAT */
#if (defined(OSEE_TC_CORE1_4_ISR_CAT))
#if (OSEE_TC_CORE1_4_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_4_ISR_TID, 4)
#elif (OSEE_TC_CORE1_4_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_4_ISR_HND, 4)
#else
#error Invalid value for OSEE_TC_CORE1_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 4)
OSEE_ISR_ALIGN(_core1_, 1, 4)
#endif /* OSEE_TC_CORE1_4_ISR_CAT */
#if (defined(OSEE_TC_CORE1_5_ISR_CAT))
#if (OSEE_TC_CORE1_5_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_5_ISR_TID, 5)
#elif (OSEE_TC_CORE1_5_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_5_ISR_HND, 5)
#else
#error Invalid value for OSEE_TC_CORE1_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 5)
OSEE_ISR_ALIGN(_core1_, 1, 5)
#endif /* OSEE_TC_CORE1_5_ISR_CAT */
#if (defined(OSEE_TC_CORE1_6_ISR_CAT))
#if (OSEE_TC_CORE1_6_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_6_ISR_TID, 6)
#elif (OSEE_TC_CORE1_6_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_6_ISR_HND, 6)
#else
#error Invalid value for OSEE_TC_CORE1_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 6)
OSEE_ISR_ALIGN(_core1_, 1, 6)
#endif /* OSEE_TC_CORE1_6_ISR_CAT */
#if (defined(OSEE_TC_CORE1_7_ISR_CAT))
#if (OSEE_TC_CORE1_7_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_7_ISR_TID, 7)
#elif (OSEE_TC_CORE1_7_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_7_ISR_HND, 7)
#else
#error Invalid value for OSEE_TC_CORE1_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 7)
OSEE_ISR_ALIGN(_core1_, 1, 7)
#endif /* OSEE_TC_CORE1_7_ISR_CAT */
#if (defined(OSEE_TC_CORE1_8_ISR_CAT))
#if (OSEE_TC_CORE1_8_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_8_ISR_TID, 8)
#elif (OSEE_TC_CORE1_8_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_8_ISR_HND, 8)
#else
#error Invalid value for OSEE_TC_CORE1_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 8)
OSEE_ISR_ALIGN(_core1_, 1, 8)
#endif /* OSEE_TC_CORE1_8_ISR_CAT */
#if (defined(OSEE_TC_CORE1_9_ISR_CAT))
#if (OSEE_TC_CORE1_9_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_9_ISR_TID, 9)
#elif (OSEE_TC_CORE1_9_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_9_ISR_HND, 9)
#else
#error Invalid value for OSEE_TC_CORE1_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 9)
OSEE_ISR_ALIGN(_core1_, 1, 9)
#endif /* OSEE_TC_CORE1_9_ISR_CAT */
#if (defined(OSEE_TC_CORE1_10_ISR_CAT))
#if (OSEE_TC_CORE1_10_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_10_ISR_TID, 10)
#elif (OSEE_TC_CORE1_10_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_10_ISR_HND, 10)
#else
#error Invalid value for OSEE_TC_CORE1_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 10)
OSEE_ISR_ALIGN(_core1_, 1, 10)
#endif /* OSEE_TC_CORE1_10_ISR_CAT */
#if (defined(OSEE_TC_CORE1_11_ISR_CAT))
#if (OSEE_TC_CORE1_11_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_11_ISR_TID, 11)
#elif (OSEE_TC_CORE1_11_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_11_ISR_HND, 11)
#else
#error Invalid value for OSEE_TC_CORE1_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 11)
OSEE_ISR_ALIGN(_core1_, 1, 11)
#endif /* OSEE_TC_CORE1_11_ISR_CAT */
#if (defined(OSEE_TC_CORE1_12_ISR_CAT))
#if (OSEE_TC_CORE1_12_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_12_ISR_TID, 12)
#elif (OSEE_TC_CORE1_12_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_12_ISR_HND, 12)
#else
#error Invalid value for OSEE_TC_CORE1_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 12)
OSEE_ISR_ALIGN(_core1_, 1, 12)
#endif /* OSEE_TC_CORE1_12_ISR_CAT */
#if (defined(OSEE_TC_CORE1_13_ISR_CAT))
#if (OSEE_TC_CORE1_13_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_13_ISR_TID, 13)
#elif (OSEE_TC_CORE1_13_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_13_ISR_HND, 13)
#else
#error Invalid value for OSEE_TC_CORE1_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 13)
OSEE_ISR_ALIGN(_core1_, 1, 13)
#endif /* OSEE_TC_CORE1_13_ISR_CAT */
#if (defined(OSEE_TC_CORE1_14_ISR_CAT))
#if (OSEE_TC_CORE1_14_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_14_ISR_TID, 14)
#elif (OSEE_TC_CORE1_14_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_14_ISR_HND, 14)
#else
#error Invalid value for OSEE_TC_CORE1_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 14)
OSEE_ISR_ALIGN(_core1_, 1, 14)
#endif /* OSEE_TC_CORE1_14_ISR_CAT */
#if (defined(OSEE_TC_CORE1_15_ISR_CAT))
#if (OSEE_TC_CORE1_15_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_15_ISR_TID, 15)
#elif (OSEE_TC_CORE1_15_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_15_ISR_HND, 15)
#else
#error Invalid value for OSEE_TC_CORE1_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 15)
OSEE_ISR_ALIGN(_core1_, 1, 15)
#endif /* OSEE_TC_CORE1_15_ISR_CAT */
#if (defined(OSEE_TC_CORE1_16_ISR_CAT))
#if (OSEE_TC_CORE1_16_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_16_ISR_TID, 16)
#elif (OSEE_TC_CORE1_16_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_16_ISR_HND, 16)
#else
#error Invalid value for OSEE_TC_CORE1_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 16)
OSEE_ISR_ALIGN(_core1_, 1, 16)
#endif /* OSEE_TC_CORE1_16_ISR_CAT */
#if (defined(OSEE_TC_CORE1_17_ISR_CAT))
#if (OSEE_TC_CORE1_17_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_17_ISR_TID, 17)
#elif (OSEE_TC_CORE1_17_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_17_ISR_HND, 17)
#else
#error Invalid value for OSEE_TC_CORE1_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 17)
OSEE_ISR_ALIGN(_core1_, 1, 17)
#endif /* OSEE_TC_CORE1_17_ISR_CAT */
#if (defined(OSEE_TC_CORE1_18_ISR_CAT))
#if (OSEE_TC_CORE1_18_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_18_ISR_TID, 18)
#elif (OSEE_TC_CORE1_18_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_18_ISR_HND, 18)
#else
#error Invalid value for OSEE_TC_CORE1_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 18)
OSEE_ISR_ALIGN(_core1_, 1, 18)
#endif /* OSEE_TC_CORE1_18_ISR_CAT */
#if (defined(OSEE_TC_CORE1_19_ISR_CAT))
#if (OSEE_TC_CORE1_19_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_19_ISR_TID, 19)
#elif (OSEE_TC_CORE1_19_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_19_ISR_HND, 19)
#else
#error Invalid value for OSEE_TC_CORE1_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 19)
OSEE_ISR_ALIGN(_core1_, 1, 19)
#endif /* OSEE_TC_CORE1_19_ISR_CAT */
#if (defined(OSEE_TC_CORE1_20_ISR_CAT))
#if (OSEE_TC_CORE1_20_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_20_ISR_TID, 20)
#elif (OSEE_TC_CORE1_20_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_20_ISR_HND, 20)
#else
#error Invalid value for OSEE_TC_CORE1_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 20)
OSEE_ISR_ALIGN(_core1_, 1, 20)
#endif /* OSEE_TC_CORE1_20_ISR_CAT */
#if (defined(OSEE_TC_CORE1_21_ISR_CAT))
#if (OSEE_TC_CORE1_21_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_21_ISR_TID, 21)
#elif (OSEE_TC_CORE1_21_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_21_ISR_HND, 21)
#else
#error Invalid value for OSEE_TC_CORE1_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 21)
OSEE_ISR_ALIGN(_core1_, 1, 21)
#endif /* OSEE_TC_CORE1_21_ISR_CAT */
#if (defined(OSEE_TC_CORE1_22_ISR_CAT))
#if (OSEE_TC_CORE1_22_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_22_ISR_TID, 22)
#elif (OSEE_TC_CORE1_22_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_22_ISR_HND, 22)
#else
#error Invalid value for OSEE_TC_CORE1_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 22)
OSEE_ISR_ALIGN(_core1_, 1, 22)
#endif /* OSEE_TC_CORE1_22_ISR_CAT */
#if (defined(OSEE_TC_CORE1_23_ISR_CAT))
#if (OSEE_TC_CORE1_23_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_23_ISR_TID, 23)
#elif (OSEE_TC_CORE1_23_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_23_ISR_HND, 23)
#else
#error Invalid value for OSEE_TC_CORE1_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 23)
OSEE_ISR_ALIGN(_core1_, 1, 23)
#endif /* OSEE_TC_CORE1_23_ISR_CAT */
#if (defined(OSEE_TC_CORE1_24_ISR_CAT))
#if (OSEE_TC_CORE1_24_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_24_ISR_TID, 24)
#elif (OSEE_TC_CORE1_24_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_24_ISR_HND, 24)
#else
#error Invalid value for OSEE_TC_CORE1_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 24)
OSEE_ISR_ALIGN(_core1_, 1, 24)
#endif /* OSEE_TC_CORE1_24_ISR_CAT */
#if (defined(OSEE_TC_CORE1_25_ISR_CAT))
#if (OSEE_TC_CORE1_25_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_25_ISR_TID, 25)
#elif (OSEE_TC_CORE1_25_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_25_ISR_HND, 25)
#else
#error Invalid value for OSEE_TC_CORE1_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 25)
OSEE_ISR_ALIGN(_core1_, 1, 25)
#endif /* OSEE_TC_CORE1_25_ISR_CAT */
#if (defined(OSEE_TC_CORE1_26_ISR_CAT))
#if (OSEE_TC_CORE1_26_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_26_ISR_TID, 26)
#elif (OSEE_TC_CORE1_26_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_26_ISR_HND, 26)
#else
#error Invalid value for OSEE_TC_CORE1_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 26)
OSEE_ISR_ALIGN(_core1_, 1, 26)
#endif /* OSEE_TC_CORE1_26_ISR_CAT */
#if (defined(OSEE_TC_CORE1_27_ISR_CAT))
#if (OSEE_TC_CORE1_27_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_27_ISR_TID, 27)
#elif (OSEE_TC_CORE1_27_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_27_ISR_HND, 27)
#else
#error Invalid value for OSEE_TC_CORE1_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 27)
OSEE_ISR_ALIGN(_core1_, 1, 27)
#endif /* OSEE_TC_CORE1_27_ISR_CAT */
#if (defined(OSEE_TC_CORE1_28_ISR_CAT))
#if (OSEE_TC_CORE1_28_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_28_ISR_TID, 28)
#elif (OSEE_TC_CORE1_28_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_28_ISR_HND, 28)
#else
#error Invalid value for OSEE_TC_CORE1_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 28)
OSEE_ISR_ALIGN(_core1_, 1, 28)
#endif /* OSEE_TC_CORE1_28_ISR_CAT */
#if (defined(OSEE_TC_CORE1_29_ISR_CAT))
#if (OSEE_TC_CORE1_29_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_29_ISR_TID, 29)
#elif (OSEE_TC_CORE1_29_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_29_ISR_HND, 29)
#else
#error Invalid value for OSEE_TC_CORE1_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 29)
OSEE_ISR_ALIGN(_core1_, 1, 29)
#endif /* OSEE_TC_CORE1_29_ISR_CAT */
#if (defined(OSEE_TC_CORE1_30_ISR_CAT))
#if (OSEE_TC_CORE1_30_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_30_ISR_TID, 30)
#elif (OSEE_TC_CORE1_30_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_30_ISR_HND, 30)
#else
#error Invalid value for OSEE_TC_CORE1_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 30)
OSEE_ISR_ALIGN(_core1_, 1, 30)
#endif /* OSEE_TC_CORE1_30_ISR_CAT */
#if (defined(OSEE_TC_CORE1_31_ISR_CAT))
#if (OSEE_TC_CORE1_31_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_31_ISR_TID, 31)
#elif (OSEE_TC_CORE1_31_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_31_ISR_HND, 31)
#else
#error Invalid value for OSEE_TC_CORE1_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 31)
OSEE_ISR_ALIGN(_core1_, 1, 31)
#endif /* OSEE_TC_CORE1_31_ISR_CAT */
#if (defined(OSEE_TC_CORE1_32_ISR_CAT))
#if (OSEE_TC_CORE1_32_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_32_ISR_TID, 32)
#elif (OSEE_TC_CORE1_32_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_32_ISR_HND, 32)
#else
#error Invalid value for OSEE_TC_CORE1_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 32)
OSEE_ISR_ALIGN(_core1_, 1, 32)
#endif /* OSEE_TC_CORE1_32_ISR_CAT */
#if (defined(OSEE_TC_CORE1_33_ISR_CAT))
#if (OSEE_TC_CORE1_33_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_33_ISR_TID, 33)
#elif (OSEE_TC_CORE1_33_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_33_ISR_HND, 33)
#else
#error Invalid value for OSEE_TC_CORE1_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 33)
OSEE_ISR_ALIGN(_core1_, 1, 33)
#endif /* OSEE_TC_CORE1_33_ISR_CAT */
#if (defined(OSEE_TC_CORE1_34_ISR_CAT))
#if (OSEE_TC_CORE1_34_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_34_ISR_TID, 34)
#elif (OSEE_TC_CORE1_34_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_34_ISR_HND, 34)
#else
#error Invalid value for OSEE_TC_CORE1_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 34)
OSEE_ISR_ALIGN(_core1_, 1, 34)
#endif /* OSEE_TC_CORE1_34_ISR_CAT */
#if (defined(OSEE_TC_CORE1_35_ISR_CAT))
#if (OSEE_TC_CORE1_35_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_35_ISR_TID, 35)
#elif (OSEE_TC_CORE1_35_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_35_ISR_HND, 35)
#else
#error Invalid value for OSEE_TC_CORE1_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 35)
OSEE_ISR_ALIGN(_core1_, 1, 35)
#endif /* OSEE_TC_CORE1_35_ISR_CAT */
#if (defined(OSEE_TC_CORE1_36_ISR_CAT))
#if (OSEE_TC_CORE1_36_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_36_ISR_TID, 36)
#elif (OSEE_TC_CORE1_36_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_36_ISR_HND, 36)
#else
#error Invalid value for OSEE_TC_CORE1_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 36)
OSEE_ISR_ALIGN(_core1_, 1, 36)
#endif /* OSEE_TC_CORE1_36_ISR_CAT */
#if (defined(OSEE_TC_CORE1_37_ISR_CAT))
#if (OSEE_TC_CORE1_37_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_37_ISR_TID, 37)
#elif (OSEE_TC_CORE1_37_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_37_ISR_HND, 37)
#else
#error Invalid value for OSEE_TC_CORE1_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 37)
OSEE_ISR_ALIGN(_core1_, 1, 37)
#endif /* OSEE_TC_CORE1_37_ISR_CAT */
#if (defined(OSEE_TC_CORE1_38_ISR_CAT))
#if (OSEE_TC_CORE1_38_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_38_ISR_TID, 38)
#elif (OSEE_TC_CORE1_38_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_38_ISR_HND, 38)
#else
#error Invalid value for OSEE_TC_CORE1_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 38)
OSEE_ISR_ALIGN(_core1_, 1, 38)
#endif /* OSEE_TC_CORE1_38_ISR_CAT */
#if (defined(OSEE_TC_CORE1_39_ISR_CAT))
#if (OSEE_TC_CORE1_39_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_39_ISR_TID, 39)
#elif (OSEE_TC_CORE1_39_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_39_ISR_HND, 39)
#else
#error Invalid value for OSEE_TC_CORE1_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 39)
OSEE_ISR_ALIGN(_core1_, 1, 39)
#endif /* OSEE_TC_CORE1_39_ISR_CAT */
#if (defined(OSEE_TC_CORE1_40_ISR_CAT))
#if (OSEE_TC_CORE1_40_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_40_ISR_TID, 40)
#elif (OSEE_TC_CORE1_40_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_40_ISR_HND, 40)
#else
#error Invalid value for OSEE_TC_CORE1_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 40)
OSEE_ISR_ALIGN(_core1_, 1, 40)
#endif /* OSEE_TC_CORE1_40_ISR_CAT */
#if (defined(OSEE_TC_CORE1_41_ISR_CAT))
#if (OSEE_TC_CORE1_41_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_41_ISR_TID, 41)
#elif (OSEE_TC_CORE1_41_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_41_ISR_HND, 41)
#else
#error Invalid value for OSEE_TC_CORE1_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 41)
OSEE_ISR_ALIGN(_core1_, 1, 41)
#endif /* OSEE_TC_CORE1_41_ISR_CAT */
#if (defined(OSEE_TC_CORE1_42_ISR_CAT))
#if (OSEE_TC_CORE1_42_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_42_ISR_TID, 42)
#elif (OSEE_TC_CORE1_42_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_42_ISR_HND, 42)
#else
#error Invalid value for OSEE_TC_CORE1_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 42)
OSEE_ISR_ALIGN(_core1_, 1, 42)
#endif /* OSEE_TC_CORE1_42_ISR_CAT */
#if (defined(OSEE_TC_CORE1_43_ISR_CAT))
#if (OSEE_TC_CORE1_43_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_43_ISR_TID, 43)
#elif (OSEE_TC_CORE1_43_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_43_ISR_HND, 43)
#else
#error Invalid value for OSEE_TC_CORE1_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 43)
OSEE_ISR_ALIGN(_core1_, 1, 43)
#endif /* OSEE_TC_CORE1_43_ISR_CAT */
#if (defined(OSEE_TC_CORE1_44_ISR_CAT))
#if (OSEE_TC_CORE1_44_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_44_ISR_TID, 44)
#elif (OSEE_TC_CORE1_44_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_44_ISR_HND, 44)
#else
#error Invalid value for OSEE_TC_CORE1_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 44)
OSEE_ISR_ALIGN(_core1_, 1, 44)
#endif /* OSEE_TC_CORE1_44_ISR_CAT */
#if (defined(OSEE_TC_CORE1_45_ISR_CAT))
#if (OSEE_TC_CORE1_45_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_45_ISR_TID, 45)
#elif (OSEE_TC_CORE1_45_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_45_ISR_HND, 45)
#else
#error Invalid value for OSEE_TC_CORE1_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 45)
OSEE_ISR_ALIGN(_core1_, 1, 45)
#endif /* OSEE_TC_CORE1_45_ISR_CAT */
#if (defined(OSEE_TC_CORE1_46_ISR_CAT))
#if (OSEE_TC_CORE1_46_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_46_ISR_TID, 46)
#elif (OSEE_TC_CORE1_46_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_46_ISR_HND, 46)
#else
#error Invalid value for OSEE_TC_CORE1_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 46)
OSEE_ISR_ALIGN(_core1_, 1, 46)
#endif /* OSEE_TC_CORE1_46_ISR_CAT */
#if (defined(OSEE_TC_CORE1_47_ISR_CAT))
#if (OSEE_TC_CORE1_47_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_47_ISR_TID, 47)
#elif (OSEE_TC_CORE1_47_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_47_ISR_HND, 47)
#else
#error Invalid value for OSEE_TC_CORE1_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 47)
OSEE_ISR_ALIGN(_core1_, 1, 47)
#endif /* OSEE_TC_CORE1_47_ISR_CAT */
#if (defined(OSEE_TC_CORE1_48_ISR_CAT))
#if (OSEE_TC_CORE1_48_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_48_ISR_TID, 48)
#elif (OSEE_TC_CORE1_48_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_48_ISR_HND, 48)
#else
#error Invalid value for OSEE_TC_CORE1_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 48)
OSEE_ISR_ALIGN(_core1_, 1, 48)
#endif /* OSEE_TC_CORE1_48_ISR_CAT */
#if (defined(OSEE_TC_CORE1_49_ISR_CAT))
#if (OSEE_TC_CORE1_49_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_49_ISR_TID, 49)
#elif (OSEE_TC_CORE1_49_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_49_ISR_HND, 49)
#else
#error Invalid value for OSEE_TC_CORE1_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 49)
OSEE_ISR_ALIGN(_core1_, 1, 49)
#endif /* OSEE_TC_CORE1_49_ISR_CAT */
#if (defined(OSEE_TC_CORE1_50_ISR_CAT))
#if (OSEE_TC_CORE1_50_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_50_ISR_TID, 50)
#elif (OSEE_TC_CORE1_50_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_50_ISR_HND, 50)
#else
#error Invalid value for OSEE_TC_CORE1_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 50)
OSEE_ISR_ALIGN(_core1_, 1, 50)
#endif /* OSEE_TC_CORE1_50_ISR_CAT */
#if (defined(OSEE_TC_CORE1_51_ISR_CAT))
#if (OSEE_TC_CORE1_51_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_51_ISR_TID, 51)
#elif (OSEE_TC_CORE1_51_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_51_ISR_HND, 51)
#else
#error Invalid value for OSEE_TC_CORE1_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 51)
OSEE_ISR_ALIGN(_core1_, 1, 51)
#endif /* OSEE_TC_CORE1_51_ISR_CAT */
#if (defined(OSEE_TC_CORE1_52_ISR_CAT))
#if (OSEE_TC_CORE1_52_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_52_ISR_TID, 52)
#elif (OSEE_TC_CORE1_52_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_52_ISR_HND, 52)
#else
#error Invalid value for OSEE_TC_CORE1_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 52)
OSEE_ISR_ALIGN(_core1_, 1, 52)
#endif /* OSEE_TC_CORE1_52_ISR_CAT */
#if (defined(OSEE_TC_CORE1_53_ISR_CAT))
#if (OSEE_TC_CORE1_53_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_53_ISR_TID, 53)
#elif (OSEE_TC_CORE1_53_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_53_ISR_HND, 53)
#else
#error Invalid value for OSEE_TC_CORE1_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 53)
OSEE_ISR_ALIGN(_core1_, 1, 53)
#endif /* OSEE_TC_CORE1_53_ISR_CAT */
#if (defined(OSEE_TC_CORE1_54_ISR_CAT))
#if (OSEE_TC_CORE1_54_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_54_ISR_TID, 54)
#elif (OSEE_TC_CORE1_54_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_54_ISR_HND, 54)
#else
#error Invalid value for OSEE_TC_CORE1_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 54)
OSEE_ISR_ALIGN(_core1_, 1, 54)
#endif /* OSEE_TC_CORE1_54_ISR_CAT */
#if (defined(OSEE_TC_CORE1_55_ISR_CAT))
#if (OSEE_TC_CORE1_55_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_55_ISR_TID, 55)
#elif (OSEE_TC_CORE1_55_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_55_ISR_HND, 55)
#else
#error Invalid value for OSEE_TC_CORE1_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 55)
OSEE_ISR_ALIGN(_core1_, 1, 55)
#endif /* OSEE_TC_CORE1_55_ISR_CAT */
#if (defined(OSEE_TC_CORE1_56_ISR_CAT))
#if (OSEE_TC_CORE1_56_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_56_ISR_TID, 56)
#elif (OSEE_TC_CORE1_56_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_56_ISR_HND, 56)
#else
#error Invalid value for OSEE_TC_CORE1_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 56)
OSEE_ISR_ALIGN(_core1_, 1, 56)
#endif /* OSEE_TC_CORE1_56_ISR_CAT */
#if (defined(OSEE_TC_CORE1_57_ISR_CAT))
#if (OSEE_TC_CORE1_57_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_57_ISR_TID, 57)
#elif (OSEE_TC_CORE1_57_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_57_ISR_HND, 57)
#else
#error Invalid value for OSEE_TC_CORE1_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 57)
OSEE_ISR_ALIGN(_core1_, 1, 57)
#endif /* OSEE_TC_CORE1_57_ISR_CAT */
#if (defined(OSEE_TC_CORE1_58_ISR_CAT))
#if (OSEE_TC_CORE1_58_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_58_ISR_TID, 58)
#elif (OSEE_TC_CORE1_58_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_58_ISR_HND, 58)
#else
#error Invalid value for OSEE_TC_CORE1_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 58)
OSEE_ISR_ALIGN(_core1_, 1, 58)
#endif /* OSEE_TC_CORE1_58_ISR_CAT */
#if (defined(OSEE_TC_CORE1_59_ISR_CAT))
#if (OSEE_TC_CORE1_59_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_59_ISR_TID, 59)
#elif (OSEE_TC_CORE1_59_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_59_ISR_HND, 59)
#else
#error Invalid value for OSEE_TC_CORE1_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 59)
OSEE_ISR_ALIGN(_core1_, 1, 59)
#endif /* OSEE_TC_CORE1_59_ISR_CAT */
#if (defined(OSEE_TC_CORE1_60_ISR_CAT))
#if (OSEE_TC_CORE1_60_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_60_ISR_TID, 60)
#elif (OSEE_TC_CORE1_60_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_60_ISR_HND, 60)
#else
#error Invalid value for OSEE_TC_CORE1_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 60)
OSEE_ISR_ALIGN(_core1_, 1, 60)
#endif /* OSEE_TC_CORE1_60_ISR_CAT */
#if (defined(OSEE_TC_CORE1_61_ISR_CAT))
#if (OSEE_TC_CORE1_61_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_61_ISR_TID, 61)
#elif (OSEE_TC_CORE1_61_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_61_ISR_HND, 61)
#else
#error Invalid value for OSEE_TC_CORE1_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 61)
OSEE_ISR_ALIGN(_core1_, 1, 61)
#endif /* OSEE_TC_CORE1_61_ISR_CAT */
#if (defined(OSEE_TC_CORE1_62_ISR_CAT))
#if (OSEE_TC_CORE1_62_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_62_ISR_TID, 62)
#elif (OSEE_TC_CORE1_62_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_62_ISR_HND, 62)
#else
#error Invalid value for OSEE_TC_CORE1_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 62)
OSEE_ISR_ALIGN(_core1_, 1, 62)
#endif /* OSEE_TC_CORE1_62_ISR_CAT */
#if (defined(OSEE_TC_CORE1_63_ISR_CAT))
#if (OSEE_TC_CORE1_63_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_63_ISR_TID, 63)
#elif (OSEE_TC_CORE1_63_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_63_ISR_HND, 63)
#else
#error Invalid value for OSEE_TC_CORE1_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 63)
OSEE_ISR_ALIGN(_core1_, 1, 63)
#endif /* OSEE_TC_CORE1_63_ISR_CAT */
#if (defined(OSEE_TC_CORE1_64_ISR_CAT))
#if (OSEE_TC_CORE1_64_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_64_ISR_TID, 64)
#elif (OSEE_TC_CORE1_64_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_64_ISR_HND, 64)
#else
#error Invalid value for OSEE_TC_CORE1_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 64)
OSEE_ISR_ALIGN(_core1_, 1, 64)
#endif /* OSEE_TC_CORE1_64_ISR_CAT */
#if (defined(OSEE_TC_CORE1_65_ISR_CAT))
#if (OSEE_TC_CORE1_65_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_65_ISR_TID, 65)
#elif (OSEE_TC_CORE1_65_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_65_ISR_HND, 65)
#else
#error Invalid value for OSEE_TC_CORE1_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 65)
OSEE_ISR_ALIGN(_core1_, 1, 65)
#endif /* OSEE_TC_CORE1_65_ISR_CAT */
#if (defined(OSEE_TC_CORE1_66_ISR_CAT))
#if (OSEE_TC_CORE1_66_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_66_ISR_TID, 66)
#elif (OSEE_TC_CORE1_66_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_66_ISR_HND, 66)
#else
#error Invalid value for OSEE_TC_CORE1_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 66)
OSEE_ISR_ALIGN(_core1_, 1, 66)
#endif /* OSEE_TC_CORE1_66_ISR_CAT */
#if (defined(OSEE_TC_CORE1_67_ISR_CAT))
#if (OSEE_TC_CORE1_67_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_67_ISR_TID, 67)
#elif (OSEE_TC_CORE1_67_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_67_ISR_HND, 67)
#else
#error Invalid value for OSEE_TC_CORE1_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 67)
OSEE_ISR_ALIGN(_core1_, 1, 67)
#endif /* OSEE_TC_CORE1_67_ISR_CAT */
#if (defined(OSEE_TC_CORE1_68_ISR_CAT))
#if (OSEE_TC_CORE1_68_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_68_ISR_TID, 68)
#elif (OSEE_TC_CORE1_68_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_68_ISR_HND, 68)
#else
#error Invalid value for OSEE_TC_CORE1_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 68)
OSEE_ISR_ALIGN(_core1_, 1, 68)
#endif /* OSEE_TC_CORE1_68_ISR_CAT */
#if (defined(OSEE_TC_CORE1_69_ISR_CAT))
#if (OSEE_TC_CORE1_69_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_69_ISR_TID, 69)
#elif (OSEE_TC_CORE1_69_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_69_ISR_HND, 69)
#else
#error Invalid value for OSEE_TC_CORE1_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 69)
OSEE_ISR_ALIGN(_core1_, 1, 69)
#endif /* OSEE_TC_CORE1_69_ISR_CAT */
#if (defined(OSEE_TC_CORE1_70_ISR_CAT))
#if (OSEE_TC_CORE1_70_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_70_ISR_TID, 70)
#elif (OSEE_TC_CORE1_70_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_70_ISR_HND, 70)
#else
#error Invalid value for OSEE_TC_CORE1_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 70)
OSEE_ISR_ALIGN(_core1_, 1, 70)
#endif /* OSEE_TC_CORE1_70_ISR_CAT */
#if (defined(OSEE_TC_CORE1_71_ISR_CAT))
#if (OSEE_TC_CORE1_71_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_71_ISR_TID, 71)
#elif (OSEE_TC_CORE1_71_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_71_ISR_HND, 71)
#else
#error Invalid value for OSEE_TC_CORE1_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 71)
OSEE_ISR_ALIGN(_core1_, 1, 71)
#endif /* OSEE_TC_CORE1_71_ISR_CAT */
#if (defined(OSEE_TC_CORE1_72_ISR_CAT))
#if (OSEE_TC_CORE1_72_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_72_ISR_TID, 72)
#elif (OSEE_TC_CORE1_72_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_72_ISR_HND, 72)
#else
#error Invalid value for OSEE_TC_CORE1_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 72)
OSEE_ISR_ALIGN(_core1_, 1, 72)
#endif /* OSEE_TC_CORE1_72_ISR_CAT */
#if (defined(OSEE_TC_CORE1_73_ISR_CAT))
#if (OSEE_TC_CORE1_73_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_73_ISR_TID, 73)
#elif (OSEE_TC_CORE1_73_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_73_ISR_HND, 73)
#else
#error Invalid value for OSEE_TC_CORE1_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 73)
OSEE_ISR_ALIGN(_core1_, 1, 73)
#endif /* OSEE_TC_CORE1_73_ISR_CAT */
#if (defined(OSEE_TC_CORE1_74_ISR_CAT))
#if (OSEE_TC_CORE1_74_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_74_ISR_TID, 74)
#elif (OSEE_TC_CORE1_74_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_74_ISR_HND, 74)
#else
#error Invalid value for OSEE_TC_CORE1_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 74)
OSEE_ISR_ALIGN(_core1_, 1, 74)
#endif /* OSEE_TC_CORE1_74_ISR_CAT */
#if (defined(OSEE_TC_CORE1_75_ISR_CAT))
#if (OSEE_TC_CORE1_75_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_75_ISR_TID, 75)
#elif (OSEE_TC_CORE1_75_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_75_ISR_HND, 75)
#else
#error Invalid value for OSEE_TC_CORE1_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 75)
OSEE_ISR_ALIGN(_core1_, 1, 75)
#endif /* OSEE_TC_CORE1_75_ISR_CAT */
#if (defined(OSEE_TC_CORE1_76_ISR_CAT))
#if (OSEE_TC_CORE1_76_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_76_ISR_TID, 76)
#elif (OSEE_TC_CORE1_76_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_76_ISR_HND, 76)
#else
#error Invalid value for OSEE_TC_CORE1_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 76)
OSEE_ISR_ALIGN(_core1_, 1, 76)
#endif /* OSEE_TC_CORE1_76_ISR_CAT */
#if (defined(OSEE_TC_CORE1_77_ISR_CAT))
#if (OSEE_TC_CORE1_77_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_77_ISR_TID, 77)
#elif (OSEE_TC_CORE1_77_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_77_ISR_HND, 77)
#else
#error Invalid value for OSEE_TC_CORE1_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 77)
OSEE_ISR_ALIGN(_core1_, 1, 77)
#endif /* OSEE_TC_CORE1_77_ISR_CAT */
#if (defined(OSEE_TC_CORE1_78_ISR_CAT))
#if (OSEE_TC_CORE1_78_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_78_ISR_TID, 78)
#elif (OSEE_TC_CORE1_78_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_78_ISR_HND, 78)
#else
#error Invalid value for OSEE_TC_CORE1_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 78)
OSEE_ISR_ALIGN(_core1_, 1, 78)
#endif /* OSEE_TC_CORE1_78_ISR_CAT */
#if (defined(OSEE_TC_CORE1_79_ISR_CAT))
#if (OSEE_TC_CORE1_79_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_79_ISR_TID, 79)
#elif (OSEE_TC_CORE1_79_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_79_ISR_HND, 79)
#else
#error Invalid value for OSEE_TC_CORE1_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 79)
OSEE_ISR_ALIGN(_core1_, 1, 79)
#endif /* OSEE_TC_CORE1_79_ISR_CAT */
#if (defined(OSEE_TC_CORE1_80_ISR_CAT))
#if (OSEE_TC_CORE1_80_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_80_ISR_TID, 80)
#elif (OSEE_TC_CORE1_80_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_80_ISR_HND, 80)
#else
#error Invalid value for OSEE_TC_CORE1_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 80)
OSEE_ISR_ALIGN(_core1_, 1, 80)
#endif /* OSEE_TC_CORE1_80_ISR_CAT */
#if (defined(OSEE_TC_CORE1_81_ISR_CAT))
#if (OSEE_TC_CORE1_81_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_81_ISR_TID, 81)
#elif (OSEE_TC_CORE1_81_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_81_ISR_HND, 81)
#else
#error Invalid value for OSEE_TC_CORE1_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 81)
OSEE_ISR_ALIGN(_core1_, 1, 81)
#endif /* OSEE_TC_CORE1_81_ISR_CAT */
#if (defined(OSEE_TC_CORE1_82_ISR_CAT))
#if (OSEE_TC_CORE1_82_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_82_ISR_TID, 82)
#elif (OSEE_TC_CORE1_82_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_82_ISR_HND, 82)
#else
#error Invalid value for OSEE_TC_CORE1_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 82)
OSEE_ISR_ALIGN(_core1_, 1, 82)
#endif /* OSEE_TC_CORE1_82_ISR_CAT */
#if (defined(OSEE_TC_CORE1_83_ISR_CAT))
#if (OSEE_TC_CORE1_83_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_83_ISR_TID, 83)
#elif (OSEE_TC_CORE1_83_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_83_ISR_HND, 83)
#else
#error Invalid value for OSEE_TC_CORE1_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 83)
OSEE_ISR_ALIGN(_core1_, 1, 83)
#endif /* OSEE_TC_CORE1_83_ISR_CAT */
#if (defined(OSEE_TC_CORE1_84_ISR_CAT))
#if (OSEE_TC_CORE1_84_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_84_ISR_TID, 84)
#elif (OSEE_TC_CORE1_84_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_84_ISR_HND, 84)
#else
#error Invalid value for OSEE_TC_CORE1_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 84)
OSEE_ISR_ALIGN(_core1_, 1, 84)
#endif /* OSEE_TC_CORE1_84_ISR_CAT */
#if (defined(OSEE_TC_CORE1_85_ISR_CAT))
#if (OSEE_TC_CORE1_85_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_85_ISR_TID, 85)
#elif (OSEE_TC_CORE1_85_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_85_ISR_HND, 85)
#else
#error Invalid value for OSEE_TC_CORE1_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 85)
OSEE_ISR_ALIGN(_core1_, 1, 85)
#endif /* OSEE_TC_CORE1_85_ISR_CAT */
#if (defined(OSEE_TC_CORE1_86_ISR_CAT))
#if (OSEE_TC_CORE1_86_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_86_ISR_TID, 86)
#elif (OSEE_TC_CORE1_86_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_86_ISR_HND, 86)
#else
#error Invalid value for OSEE_TC_CORE1_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 86)
OSEE_ISR_ALIGN(_core1_, 1, 86)
#endif /* OSEE_TC_CORE1_86_ISR_CAT */
#if (defined(OSEE_TC_CORE1_87_ISR_CAT))
#if (OSEE_TC_CORE1_87_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_87_ISR_TID, 87)
#elif (OSEE_TC_CORE1_87_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_87_ISR_HND, 87)
#else
#error Invalid value for OSEE_TC_CORE1_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 87)
OSEE_ISR_ALIGN(_core1_, 1, 87)
#endif /* OSEE_TC_CORE1_87_ISR_CAT */
#if (defined(OSEE_TC_CORE1_88_ISR_CAT))
#if (OSEE_TC_CORE1_88_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_88_ISR_TID, 88)
#elif (OSEE_TC_CORE1_88_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_88_ISR_HND, 88)
#else
#error Invalid value for OSEE_TC_CORE1_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 88)
OSEE_ISR_ALIGN(_core1_, 1, 88)
#endif /* OSEE_TC_CORE1_88_ISR_CAT */
#if (defined(OSEE_TC_CORE1_89_ISR_CAT))
#if (OSEE_TC_CORE1_89_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_89_ISR_TID, 89)
#elif (OSEE_TC_CORE1_89_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_89_ISR_HND, 89)
#else
#error Invalid value for OSEE_TC_CORE1_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 89)
OSEE_ISR_ALIGN(_core1_, 1, 89)
#endif /* OSEE_TC_CORE1_89_ISR_CAT */
#if (defined(OSEE_TC_CORE1_90_ISR_CAT))
#if (OSEE_TC_CORE1_90_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_90_ISR_TID, 90)
#elif (OSEE_TC_CORE1_90_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_90_ISR_HND, 90)
#else
#error Invalid value for OSEE_TC_CORE1_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 90)
OSEE_ISR_ALIGN(_core1_, 1, 90)
#endif /* OSEE_TC_CORE1_90_ISR_CAT */
#if (defined(OSEE_TC_CORE1_91_ISR_CAT))
#if (OSEE_TC_CORE1_91_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_91_ISR_TID, 91)
#elif (OSEE_TC_CORE1_91_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_91_ISR_HND, 91)
#else
#error Invalid value for OSEE_TC_CORE1_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 91)
OSEE_ISR_ALIGN(_core1_, 1, 91)
#endif /* OSEE_TC_CORE1_91_ISR_CAT */
#if (defined(OSEE_TC_CORE1_92_ISR_CAT))
#if (OSEE_TC_CORE1_92_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_92_ISR_TID, 92)
#elif (OSEE_TC_CORE1_92_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_92_ISR_HND, 92)
#else
#error Invalid value for OSEE_TC_CORE1_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 92)
OSEE_ISR_ALIGN(_core1_, 1, 92)
#endif /* OSEE_TC_CORE1_92_ISR_CAT */
#if (defined(OSEE_TC_CORE1_93_ISR_CAT))
#if (OSEE_TC_CORE1_93_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_93_ISR_TID, 93)
#elif (OSEE_TC_CORE1_93_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_93_ISR_HND, 93)
#else
#error Invalid value for OSEE_TC_CORE1_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 93)
OSEE_ISR_ALIGN(_core1_, 1, 93)
#endif /* OSEE_TC_CORE1_93_ISR_CAT */
#if (defined(OSEE_TC_CORE1_94_ISR_CAT))
#if (OSEE_TC_CORE1_94_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_94_ISR_TID, 94)
#elif (OSEE_TC_CORE1_94_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_94_ISR_HND, 94)
#else
#error Invalid value for OSEE_TC_CORE1_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 94)
OSEE_ISR_ALIGN(_core1_, 1, 94)
#endif /* OSEE_TC_CORE1_94_ISR_CAT */
#if (defined(OSEE_TC_CORE1_95_ISR_CAT))
#if (OSEE_TC_CORE1_95_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_95_ISR_TID, 95)
#elif (OSEE_TC_CORE1_95_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_95_ISR_HND, 95)
#else
#error Invalid value for OSEE_TC_CORE1_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 95)
OSEE_ISR_ALIGN(_core1_, 1, 95)
#endif /* OSEE_TC_CORE1_95_ISR_CAT */
#if (defined(OSEE_TC_CORE1_96_ISR_CAT))
#if (OSEE_TC_CORE1_96_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_96_ISR_TID, 96)
#elif (OSEE_TC_CORE1_96_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_96_ISR_HND, 96)
#else
#error Invalid value for OSEE_TC_CORE1_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 96)
OSEE_ISR_ALIGN(_core1_, 1, 96)
#endif /* OSEE_TC_CORE1_96_ISR_CAT */
#if (defined(OSEE_TC_CORE1_97_ISR_CAT))
#if (OSEE_TC_CORE1_97_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_97_ISR_TID, 97)
#elif (OSEE_TC_CORE1_97_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_97_ISR_HND, 97)
#else
#error Invalid value for OSEE_TC_CORE1_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 97)
OSEE_ISR_ALIGN(_core1_, 1, 97)
#endif /* OSEE_TC_CORE1_97_ISR_CAT */
#if (defined(OSEE_TC_CORE1_98_ISR_CAT))
#if (OSEE_TC_CORE1_98_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_98_ISR_TID, 98)
#elif (OSEE_TC_CORE1_98_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_98_ISR_HND, 98)
#else
#error Invalid value for OSEE_TC_CORE1_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 98)
OSEE_ISR_ALIGN(_core1_, 1, 98)
#endif /* OSEE_TC_CORE1_98_ISR_CAT */
#if (defined(OSEE_TC_CORE1_99_ISR_CAT))
#if (OSEE_TC_CORE1_99_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_99_ISR_TID, 99)
#elif (OSEE_TC_CORE1_99_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_99_ISR_HND, 99)
#else
#error Invalid value for OSEE_TC_CORE1_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 99)
OSEE_ISR_ALIGN(_core1_, 1, 99)
#endif /* OSEE_TC_CORE1_99_ISR_CAT */
#if (defined(OSEE_TC_CORE1_100_ISR_CAT))
#if (OSEE_TC_CORE1_100_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_100_ISR_TID, 100)
#elif (OSEE_TC_CORE1_100_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_100_ISR_HND, 100)
#else
#error Invalid value for OSEE_TC_CORE1_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 100)
OSEE_ISR_ALIGN(_core1_, 1, 100)
#endif /* OSEE_TC_CORE1_100_ISR_CAT */
#if (defined(OSEE_TC_CORE1_101_ISR_CAT))
#if (OSEE_TC_CORE1_101_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_101_ISR_TID, 101)
#elif (OSEE_TC_CORE1_101_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_101_ISR_HND, 101)
#else
#error Invalid value for OSEE_TC_CORE1_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 101)
OSEE_ISR_ALIGN(_core1_, 1, 101)
#endif /* OSEE_TC_CORE1_101_ISR_CAT */
#if (defined(OSEE_TC_CORE1_102_ISR_CAT))
#if (OSEE_TC_CORE1_102_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_102_ISR_TID, 102)
#elif (OSEE_TC_CORE1_102_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_102_ISR_HND, 102)
#else
#error Invalid value for OSEE_TC_CORE1_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 102)
OSEE_ISR_ALIGN(_core1_, 1, 102)
#endif /* OSEE_TC_CORE1_102_ISR_CAT */
#if (defined(OSEE_TC_CORE1_103_ISR_CAT))
#if (OSEE_TC_CORE1_103_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_103_ISR_TID, 103)
#elif (OSEE_TC_CORE1_103_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_103_ISR_HND, 103)
#else
#error Invalid value for OSEE_TC_CORE1_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 103)
OSEE_ISR_ALIGN(_core1_, 1, 103)
#endif /* OSEE_TC_CORE1_103_ISR_CAT */
#if (defined(OSEE_TC_CORE1_104_ISR_CAT))
#if (OSEE_TC_CORE1_104_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_104_ISR_TID, 104)
#elif (OSEE_TC_CORE1_104_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_104_ISR_HND, 104)
#else
#error Invalid value for OSEE_TC_CORE1_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 104)
OSEE_ISR_ALIGN(_core1_, 1, 104)
#endif /* OSEE_TC_CORE1_104_ISR_CAT */
#if (defined(OSEE_TC_CORE1_105_ISR_CAT))
#if (OSEE_TC_CORE1_105_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_105_ISR_TID, 105)
#elif (OSEE_TC_CORE1_105_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_105_ISR_HND, 105)
#else
#error Invalid value for OSEE_TC_CORE1_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 105)
OSEE_ISR_ALIGN(_core1_, 1, 105)
#endif /* OSEE_TC_CORE1_105_ISR_CAT */
#if (defined(OSEE_TC_CORE1_106_ISR_CAT))
#if (OSEE_TC_CORE1_106_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_106_ISR_TID, 106)
#elif (OSEE_TC_CORE1_106_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_106_ISR_HND, 106)
#else
#error Invalid value for OSEE_TC_CORE1_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 106)
OSEE_ISR_ALIGN(_core1_, 1, 106)
#endif /* OSEE_TC_CORE1_106_ISR_CAT */
#if (defined(OSEE_TC_CORE1_107_ISR_CAT))
#if (OSEE_TC_CORE1_107_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_107_ISR_TID, 107)
#elif (OSEE_TC_CORE1_107_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_107_ISR_HND, 107)
#else
#error Invalid value for OSEE_TC_CORE1_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 107)
OSEE_ISR_ALIGN(_core1_, 1, 107)
#endif /* OSEE_TC_CORE1_107_ISR_CAT */
#if (defined(OSEE_TC_CORE1_108_ISR_CAT))
#if (OSEE_TC_CORE1_108_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_108_ISR_TID, 108)
#elif (OSEE_TC_CORE1_108_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_108_ISR_HND, 108)
#else
#error Invalid value for OSEE_TC_CORE1_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 108)
OSEE_ISR_ALIGN(_core1_, 1, 108)
#endif /* OSEE_TC_CORE1_108_ISR_CAT */
#if (defined(OSEE_TC_CORE1_109_ISR_CAT))
#if (OSEE_TC_CORE1_109_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_109_ISR_TID, 109)
#elif (OSEE_TC_CORE1_109_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_109_ISR_HND, 109)
#else
#error Invalid value for OSEE_TC_CORE1_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 109)
OSEE_ISR_ALIGN(_core1_, 1, 109)
#endif /* OSEE_TC_CORE1_109_ISR_CAT */
#if (defined(OSEE_TC_CORE1_110_ISR_CAT))
#if (OSEE_TC_CORE1_110_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_110_ISR_TID, 110)
#elif (OSEE_TC_CORE1_110_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_110_ISR_HND, 110)
#else
#error Invalid value for OSEE_TC_CORE1_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 110)
OSEE_ISR_ALIGN(_core1_, 1, 110)
#endif /* OSEE_TC_CORE1_110_ISR_CAT */
#if (defined(OSEE_TC_CORE1_111_ISR_CAT))
#if (OSEE_TC_CORE1_111_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_111_ISR_TID, 111)
#elif (OSEE_TC_CORE1_111_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_111_ISR_HND, 111)
#else
#error Invalid value for OSEE_TC_CORE1_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 111)
OSEE_ISR_ALIGN(_core1_, 1, 111)
#endif /* OSEE_TC_CORE1_111_ISR_CAT */
#if (defined(OSEE_TC_CORE1_112_ISR_CAT))
#if (OSEE_TC_CORE1_112_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_112_ISR_TID, 112)
#elif (OSEE_TC_CORE1_112_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_112_ISR_HND, 112)
#else
#error Invalid value for OSEE_TC_CORE1_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 112)
OSEE_ISR_ALIGN(_core1_, 1, 112)
#endif /* OSEE_TC_CORE1_112_ISR_CAT */
#if (defined(OSEE_TC_CORE1_113_ISR_CAT))
#if (OSEE_TC_CORE1_113_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_113_ISR_TID, 113)
#elif (OSEE_TC_CORE1_113_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_113_ISR_HND, 113)
#else
#error Invalid value for OSEE_TC_CORE1_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 113)
OSEE_ISR_ALIGN(_core1_, 1, 113)
#endif /* OSEE_TC_CORE1_113_ISR_CAT */
#if (defined(OSEE_TC_CORE1_114_ISR_CAT))
#if (OSEE_TC_CORE1_114_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_114_ISR_TID, 114)
#elif (OSEE_TC_CORE1_114_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_114_ISR_HND, 114)
#else
#error Invalid value for OSEE_TC_CORE1_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 114)
OSEE_ISR_ALIGN(_core1_, 1, 114)
#endif /* OSEE_TC_CORE1_114_ISR_CAT */
#if (defined(OSEE_TC_CORE1_115_ISR_CAT))
#if (OSEE_TC_CORE1_115_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_115_ISR_TID, 115)
#elif (OSEE_TC_CORE1_115_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_115_ISR_HND, 115)
#else
#error Invalid value for OSEE_TC_CORE1_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 115)
OSEE_ISR_ALIGN(_core1_, 1, 115)
#endif /* OSEE_TC_CORE1_115_ISR_CAT */
#if (defined(OSEE_TC_CORE1_116_ISR_CAT))
#if (OSEE_TC_CORE1_116_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_116_ISR_TID, 116)
#elif (OSEE_TC_CORE1_116_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_116_ISR_HND, 116)
#else
#error Invalid value for OSEE_TC_CORE1_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 116)
OSEE_ISR_ALIGN(_core1_, 1, 116)
#endif /* OSEE_TC_CORE1_116_ISR_CAT */
#if (defined(OSEE_TC_CORE1_117_ISR_CAT))
#if (OSEE_TC_CORE1_117_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_117_ISR_TID, 117)
#elif (OSEE_TC_CORE1_117_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_117_ISR_HND, 117)
#else
#error Invalid value for OSEE_TC_CORE1_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 117)
OSEE_ISR_ALIGN(_core1_, 1, 117)
#endif /* OSEE_TC_CORE1_117_ISR_CAT */
#if (defined(OSEE_TC_CORE1_118_ISR_CAT))
#if (OSEE_TC_CORE1_118_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_118_ISR_TID, 118)
#elif (OSEE_TC_CORE1_118_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_118_ISR_HND, 118)
#else
#error Invalid value for OSEE_TC_CORE1_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 118)
OSEE_ISR_ALIGN(_core1_, 1, 118)
#endif /* OSEE_TC_CORE1_118_ISR_CAT */
#if (defined(OSEE_TC_CORE1_119_ISR_CAT))
#if (OSEE_TC_CORE1_119_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_119_ISR_TID, 119)
#elif (OSEE_TC_CORE1_119_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_119_ISR_HND, 119)
#else
#error Invalid value for OSEE_TC_CORE1_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 119)
OSEE_ISR_ALIGN(_core1_, 1, 119)
#endif /* OSEE_TC_CORE1_119_ISR_CAT */
#if (defined(OSEE_TC_CORE1_120_ISR_CAT))
#if (OSEE_TC_CORE1_120_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_120_ISR_TID, 120)
#elif (OSEE_TC_CORE1_120_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_120_ISR_HND, 120)
#else
#error Invalid value for OSEE_TC_CORE1_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 120)
OSEE_ISR_ALIGN(_core1_, 1, 120)
#endif /* OSEE_TC_CORE1_120_ISR_CAT */
#if (defined(OSEE_TC_CORE1_121_ISR_CAT))
#if (OSEE_TC_CORE1_121_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_121_ISR_TID, 121)
#elif (OSEE_TC_CORE1_121_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_121_ISR_HND, 121)
#else
#error Invalid value for OSEE_TC_CORE1_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 121)
OSEE_ISR_ALIGN(_core1_, 1, 121)
#endif /* OSEE_TC_CORE1_121_ISR_CAT */
#if (defined(OSEE_TC_CORE1_122_ISR_CAT))
#if (OSEE_TC_CORE1_122_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_122_ISR_TID, 122)
#elif (OSEE_TC_CORE1_122_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_122_ISR_HND, 122)
#else
#error Invalid value for OSEE_TC_CORE1_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 122)
OSEE_ISR_ALIGN(_core1_, 1, 122)
#endif /* OSEE_TC_CORE1_122_ISR_CAT */
#if (defined(OSEE_TC_CORE1_123_ISR_CAT))
#if (OSEE_TC_CORE1_123_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_123_ISR_TID, 123)
#elif (OSEE_TC_CORE1_123_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_123_ISR_HND, 123)
#else
#error Invalid value for OSEE_TC_CORE1_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 123)
OSEE_ISR_ALIGN(_core1_, 1, 123)
#endif /* OSEE_TC_CORE1_123_ISR_CAT */
#if (defined(OSEE_TC_CORE1_124_ISR_CAT))
#if (OSEE_TC_CORE1_124_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_124_ISR_TID, 124)
#elif (OSEE_TC_CORE1_124_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_124_ISR_HND, 124)
#else
#error Invalid value for OSEE_TC_CORE1_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 124)
OSEE_ISR_ALIGN(_core1_, 1, 124)
#endif /* OSEE_TC_CORE1_124_ISR_CAT */
#if (defined(OSEE_TC_CORE1_125_ISR_CAT))
#if (OSEE_TC_CORE1_125_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_125_ISR_TID, 125)
#elif (OSEE_TC_CORE1_125_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_125_ISR_HND, 125)
#else
#error Invalid value for OSEE_TC_CORE1_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 125)
OSEE_ISR_ALIGN(_core1_, 1, 125)
#endif /* OSEE_TC_CORE1_125_ISR_CAT */
#if (defined(OSEE_TC_CORE1_126_ISR_CAT))
#if (OSEE_TC_CORE1_126_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_126_ISR_TID, 126)
#elif (OSEE_TC_CORE1_126_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_126_ISR_HND, 126)
#else
#error Invalid value for OSEE_TC_CORE1_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 126)
OSEE_ISR_ALIGN(_core1_, 1, 126)
#endif /* OSEE_TC_CORE1_126_ISR_CAT */
#if (defined(OSEE_TC_CORE1_127_ISR_CAT))
#if (OSEE_TC_CORE1_127_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_127_ISR_TID, 127)
#elif (OSEE_TC_CORE1_127_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_127_ISR_HND, 127)
#else
#error Invalid value for OSEE_TC_CORE1_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 127)
OSEE_ISR_ALIGN(_core1_, 1, 127)
#endif /* OSEE_TC_CORE1_127_ISR_CAT */
#if (defined(OSEE_TC_CORE1_128_ISR_CAT))
#if (OSEE_TC_CORE1_128_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_128_ISR_TID, 128)
#elif (OSEE_TC_CORE1_128_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_128_ISR_HND, 128)
#else
#error Invalid value for OSEE_TC_CORE1_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 128)
OSEE_ISR_ALIGN(_core1_, 1, 128)
#endif /* OSEE_TC_CORE1_128_ISR_CAT */
#if (defined(OSEE_TC_CORE1_129_ISR_CAT))
#if (OSEE_TC_CORE1_129_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_129_ISR_TID, 129)
#elif (OSEE_TC_CORE1_129_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_129_ISR_HND, 129)
#else
#error Invalid value for OSEE_TC_CORE1_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 129)
OSEE_ISR_ALIGN(_core1_, 1, 129)
#endif /* OSEE_TC_CORE1_129_ISR_CAT */
#if (defined(OSEE_TC_CORE1_130_ISR_CAT))
#if (OSEE_TC_CORE1_130_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_130_ISR_TID, 130)
#elif (OSEE_TC_CORE1_130_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_130_ISR_HND, 130)
#else
#error Invalid value for OSEE_TC_CORE1_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 130)
OSEE_ISR_ALIGN(_core1_, 1, 130)
#endif /* OSEE_TC_CORE1_130_ISR_CAT */
#if (defined(OSEE_TC_CORE1_131_ISR_CAT))
#if (OSEE_TC_CORE1_131_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_131_ISR_TID, 131)
#elif (OSEE_TC_CORE1_131_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_131_ISR_HND, 131)
#else
#error Invalid value for OSEE_TC_CORE1_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 131)
OSEE_ISR_ALIGN(_core1_, 1, 131)
#endif /* OSEE_TC_CORE1_131_ISR_CAT */
#if (defined(OSEE_TC_CORE1_132_ISR_CAT))
#if (OSEE_TC_CORE1_132_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_132_ISR_TID, 132)
#elif (OSEE_TC_CORE1_132_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_132_ISR_HND, 132)
#else
#error Invalid value for OSEE_TC_CORE1_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 132)
OSEE_ISR_ALIGN(_core1_, 1, 132)
#endif /* OSEE_TC_CORE1_132_ISR_CAT */
#if (defined(OSEE_TC_CORE1_133_ISR_CAT))
#if (OSEE_TC_CORE1_133_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_133_ISR_TID, 133)
#elif (OSEE_TC_CORE1_133_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_133_ISR_HND, 133)
#else
#error Invalid value for OSEE_TC_CORE1_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 133)
OSEE_ISR_ALIGN(_core1_, 1, 133)
#endif /* OSEE_TC_CORE1_133_ISR_CAT */
#if (defined(OSEE_TC_CORE1_134_ISR_CAT))
#if (OSEE_TC_CORE1_134_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_134_ISR_TID, 134)
#elif (OSEE_TC_CORE1_134_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_134_ISR_HND, 134)
#else
#error Invalid value for OSEE_TC_CORE1_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 134)
OSEE_ISR_ALIGN(_core1_, 1, 134)
#endif /* OSEE_TC_CORE1_134_ISR_CAT */
#if (defined(OSEE_TC_CORE1_135_ISR_CAT))
#if (OSEE_TC_CORE1_135_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_135_ISR_TID, 135)
#elif (OSEE_TC_CORE1_135_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_135_ISR_HND, 135)
#else
#error Invalid value for OSEE_TC_CORE1_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 135)
OSEE_ISR_ALIGN(_core1_, 1, 135)
#endif /* OSEE_TC_CORE1_135_ISR_CAT */
#if (defined(OSEE_TC_CORE1_136_ISR_CAT))
#if (OSEE_TC_CORE1_136_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_136_ISR_TID, 136)
#elif (OSEE_TC_CORE1_136_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_136_ISR_HND, 136)
#else
#error Invalid value for OSEE_TC_CORE1_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 136)
OSEE_ISR_ALIGN(_core1_, 1, 136)
#endif /* OSEE_TC_CORE1_136_ISR_CAT */
#if (defined(OSEE_TC_CORE1_137_ISR_CAT))
#if (OSEE_TC_CORE1_137_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_137_ISR_TID, 137)
#elif (OSEE_TC_CORE1_137_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_137_ISR_HND, 137)
#else
#error Invalid value for OSEE_TC_CORE1_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 137)
OSEE_ISR_ALIGN(_core1_, 1, 137)
#endif /* OSEE_TC_CORE1_137_ISR_CAT */
#if (defined(OSEE_TC_CORE1_138_ISR_CAT))
#if (OSEE_TC_CORE1_138_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_138_ISR_TID, 138)
#elif (OSEE_TC_CORE1_138_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_138_ISR_HND, 138)
#else
#error Invalid value for OSEE_TC_CORE1_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 138)
OSEE_ISR_ALIGN(_core1_, 1, 138)
#endif /* OSEE_TC_CORE1_138_ISR_CAT */
#if (defined(OSEE_TC_CORE1_139_ISR_CAT))
#if (OSEE_TC_CORE1_139_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_139_ISR_TID, 139)
#elif (OSEE_TC_CORE1_139_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_139_ISR_HND, 139)
#else
#error Invalid value for OSEE_TC_CORE1_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 139)
OSEE_ISR_ALIGN(_core1_, 1, 139)
#endif /* OSEE_TC_CORE1_139_ISR_CAT */
#if (defined(OSEE_TC_CORE1_140_ISR_CAT))
#if (OSEE_TC_CORE1_140_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_140_ISR_TID, 140)
#elif (OSEE_TC_CORE1_140_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_140_ISR_HND, 140)
#else
#error Invalid value for OSEE_TC_CORE1_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 140)
OSEE_ISR_ALIGN(_core1_, 1, 140)
#endif /* OSEE_TC_CORE1_140_ISR_CAT */
#if (defined(OSEE_TC_CORE1_141_ISR_CAT))
#if (OSEE_TC_CORE1_141_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_141_ISR_TID, 141)
#elif (OSEE_TC_CORE1_141_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_141_ISR_HND, 141)
#else
#error Invalid value for OSEE_TC_CORE1_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 141)
OSEE_ISR_ALIGN(_core1_, 1, 141)
#endif /* OSEE_TC_CORE1_141_ISR_CAT */
#if (defined(OSEE_TC_CORE1_142_ISR_CAT))
#if (OSEE_TC_CORE1_142_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_142_ISR_TID, 142)
#elif (OSEE_TC_CORE1_142_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_142_ISR_HND, 142)
#else
#error Invalid value for OSEE_TC_CORE1_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 142)
OSEE_ISR_ALIGN(_core1_, 1, 142)
#endif /* OSEE_TC_CORE1_142_ISR_CAT */
#if (defined(OSEE_TC_CORE1_143_ISR_CAT))
#if (OSEE_TC_CORE1_143_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_143_ISR_TID, 143)
#elif (OSEE_TC_CORE1_143_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_143_ISR_HND, 143)
#else
#error Invalid value for OSEE_TC_CORE1_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 143)
OSEE_ISR_ALIGN(_core1_, 1, 143)
#endif /* OSEE_TC_CORE1_143_ISR_CAT */
#if (defined(OSEE_TC_CORE1_144_ISR_CAT))
#if (OSEE_TC_CORE1_144_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_144_ISR_TID, 144)
#elif (OSEE_TC_CORE1_144_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_144_ISR_HND, 144)
#else
#error Invalid value for OSEE_TC_CORE1_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 144)
OSEE_ISR_ALIGN(_core1_, 1, 144)
#endif /* OSEE_TC_CORE1_144_ISR_CAT */
#if (defined(OSEE_TC_CORE1_145_ISR_CAT))
#if (OSEE_TC_CORE1_145_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_145_ISR_TID, 145)
#elif (OSEE_TC_CORE1_145_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_145_ISR_HND, 145)
#else
#error Invalid value for OSEE_TC_CORE1_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 145)
OSEE_ISR_ALIGN(_core1_, 1, 145)
#endif /* OSEE_TC_CORE1_145_ISR_CAT */
#if (defined(OSEE_TC_CORE1_146_ISR_CAT))
#if (OSEE_TC_CORE1_146_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_146_ISR_TID, 146)
#elif (OSEE_TC_CORE1_146_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_146_ISR_HND, 146)
#else
#error Invalid value for OSEE_TC_CORE1_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 146)
OSEE_ISR_ALIGN(_core1_, 1, 146)
#endif /* OSEE_TC_CORE1_146_ISR_CAT */
#if (defined(OSEE_TC_CORE1_147_ISR_CAT))
#if (OSEE_TC_CORE1_147_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_147_ISR_TID, 147)
#elif (OSEE_TC_CORE1_147_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_147_ISR_HND, 147)
#else
#error Invalid value for OSEE_TC_CORE1_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 147)
OSEE_ISR_ALIGN(_core1_, 1, 147)
#endif /* OSEE_TC_CORE1_147_ISR_CAT */
#if (defined(OSEE_TC_CORE1_148_ISR_CAT))
#if (OSEE_TC_CORE1_148_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_148_ISR_TID, 148)
#elif (OSEE_TC_CORE1_148_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_148_ISR_HND, 148)
#else
#error Invalid value for OSEE_TC_CORE1_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 148)
OSEE_ISR_ALIGN(_core1_, 1, 148)
#endif /* OSEE_TC_CORE1_148_ISR_CAT */
#if (defined(OSEE_TC_CORE1_149_ISR_CAT))
#if (OSEE_TC_CORE1_149_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_149_ISR_TID, 149)
#elif (OSEE_TC_CORE1_149_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_149_ISR_HND, 149)
#else
#error Invalid value for OSEE_TC_CORE1_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 149)
OSEE_ISR_ALIGN(_core1_, 1, 149)
#endif /* OSEE_TC_CORE1_149_ISR_CAT */
#if (defined(OSEE_TC_CORE1_150_ISR_CAT))
#if (OSEE_TC_CORE1_150_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_150_ISR_TID, 150)
#elif (OSEE_TC_CORE1_150_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_150_ISR_HND, 150)
#else
#error Invalid value for OSEE_TC_CORE1_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 150)
OSEE_ISR_ALIGN(_core1_, 1, 150)
#endif /* OSEE_TC_CORE1_150_ISR_CAT */
#if (defined(OSEE_TC_CORE1_151_ISR_CAT))
#if (OSEE_TC_CORE1_151_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_151_ISR_TID, 151)
#elif (OSEE_TC_CORE1_151_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_151_ISR_HND, 151)
#else
#error Invalid value for OSEE_TC_CORE1_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 151)
OSEE_ISR_ALIGN(_core1_, 1, 151)
#endif /* OSEE_TC_CORE1_151_ISR_CAT */
#if (defined(OSEE_TC_CORE1_152_ISR_CAT))
#if (OSEE_TC_CORE1_152_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_152_ISR_TID, 152)
#elif (OSEE_TC_CORE1_152_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_152_ISR_HND, 152)
#else
#error Invalid value for OSEE_TC_CORE1_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 152)
OSEE_ISR_ALIGN(_core1_, 1, 152)
#endif /* OSEE_TC_CORE1_152_ISR_CAT */
#if (defined(OSEE_TC_CORE1_153_ISR_CAT))
#if (OSEE_TC_CORE1_153_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_153_ISR_TID, 153)
#elif (OSEE_TC_CORE1_153_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_153_ISR_HND, 153)
#else
#error Invalid value for OSEE_TC_CORE1_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 153)
OSEE_ISR_ALIGN(_core1_, 1, 153)
#endif /* OSEE_TC_CORE1_153_ISR_CAT */
#if (defined(OSEE_TC_CORE1_154_ISR_CAT))
#if (OSEE_TC_CORE1_154_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_154_ISR_TID, 154)
#elif (OSEE_TC_CORE1_154_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_154_ISR_HND, 154)
#else
#error Invalid value for OSEE_TC_CORE1_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 154)
OSEE_ISR_ALIGN(_core1_, 1, 154)
#endif /* OSEE_TC_CORE1_154_ISR_CAT */
#if (defined(OSEE_TC_CORE1_155_ISR_CAT))
#if (OSEE_TC_CORE1_155_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_155_ISR_TID, 155)
#elif (OSEE_TC_CORE1_155_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_155_ISR_HND, 155)
#else
#error Invalid value for OSEE_TC_CORE1_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 155)
OSEE_ISR_ALIGN(_core1_, 1, 155)
#endif /* OSEE_TC_CORE1_155_ISR_CAT */
#if (defined(OSEE_TC_CORE1_156_ISR_CAT))
#if (OSEE_TC_CORE1_156_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_156_ISR_TID, 156)
#elif (OSEE_TC_CORE1_156_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_156_ISR_HND, 156)
#else
#error Invalid value for OSEE_TC_CORE1_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 156)
OSEE_ISR_ALIGN(_core1_, 1, 156)
#endif /* OSEE_TC_CORE1_156_ISR_CAT */
#if (defined(OSEE_TC_CORE1_157_ISR_CAT))
#if (OSEE_TC_CORE1_157_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_157_ISR_TID, 157)
#elif (OSEE_TC_CORE1_157_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_157_ISR_HND, 157)
#else
#error Invalid value for OSEE_TC_CORE1_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 157)
OSEE_ISR_ALIGN(_core1_, 1, 157)
#endif /* OSEE_TC_CORE1_157_ISR_CAT */
#if (defined(OSEE_TC_CORE1_158_ISR_CAT))
#if (OSEE_TC_CORE1_158_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_158_ISR_TID, 158)
#elif (OSEE_TC_CORE1_158_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_158_ISR_HND, 158)
#else
#error Invalid value for OSEE_TC_CORE1_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 158)
OSEE_ISR_ALIGN(_core1_, 1, 158)
#endif /* OSEE_TC_CORE1_158_ISR_CAT */
#if (defined(OSEE_TC_CORE1_159_ISR_CAT))
#if (OSEE_TC_CORE1_159_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_159_ISR_TID, 159)
#elif (OSEE_TC_CORE1_159_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_159_ISR_HND, 159)
#else
#error Invalid value for OSEE_TC_CORE1_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 159)
OSEE_ISR_ALIGN(_core1_, 1, 159)
#endif /* OSEE_TC_CORE1_159_ISR_CAT */
#if (defined(OSEE_TC_CORE1_160_ISR_CAT))
#if (OSEE_TC_CORE1_160_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_160_ISR_TID, 160)
#elif (OSEE_TC_CORE1_160_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_160_ISR_HND, 160)
#else
#error Invalid value for OSEE_TC_CORE1_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 160)
OSEE_ISR_ALIGN(_core1_, 1, 160)
#endif /* OSEE_TC_CORE1_160_ISR_CAT */
#if (defined(OSEE_TC_CORE1_161_ISR_CAT))
#if (OSEE_TC_CORE1_161_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_161_ISR_TID, 161)
#elif (OSEE_TC_CORE1_161_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_161_ISR_HND, 161)
#else
#error Invalid value for OSEE_TC_CORE1_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 161)
OSEE_ISR_ALIGN(_core1_, 1, 161)
#endif /* OSEE_TC_CORE1_161_ISR_CAT */
#if (defined(OSEE_TC_CORE1_162_ISR_CAT))
#if (OSEE_TC_CORE1_162_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_162_ISR_TID, 162)
#elif (OSEE_TC_CORE1_162_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_162_ISR_HND, 162)
#else
#error Invalid value for OSEE_TC_CORE1_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 162)
OSEE_ISR_ALIGN(_core1_, 1, 162)
#endif /* OSEE_TC_CORE1_162_ISR_CAT */
#if (defined(OSEE_TC_CORE1_163_ISR_CAT))
#if (OSEE_TC_CORE1_163_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_163_ISR_TID, 163)
#elif (OSEE_TC_CORE1_163_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_163_ISR_HND, 163)
#else
#error Invalid value for OSEE_TC_CORE1_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 163)
OSEE_ISR_ALIGN(_core1_, 1, 163)
#endif /* OSEE_TC_CORE1_163_ISR_CAT */
#if (defined(OSEE_TC_CORE1_164_ISR_CAT))
#if (OSEE_TC_CORE1_164_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_164_ISR_TID, 164)
#elif (OSEE_TC_CORE1_164_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_164_ISR_HND, 164)
#else
#error Invalid value for OSEE_TC_CORE1_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 164)
OSEE_ISR_ALIGN(_core1_, 1, 164)
#endif /* OSEE_TC_CORE1_164_ISR_CAT */
#if (defined(OSEE_TC_CORE1_165_ISR_CAT))
#if (OSEE_TC_CORE1_165_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_165_ISR_TID, 165)
#elif (OSEE_TC_CORE1_165_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_165_ISR_HND, 165)
#else
#error Invalid value for OSEE_TC_CORE1_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 165)
OSEE_ISR_ALIGN(_core1_, 1, 165)
#endif /* OSEE_TC_CORE1_165_ISR_CAT */
#if (defined(OSEE_TC_CORE1_166_ISR_CAT))
#if (OSEE_TC_CORE1_166_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_166_ISR_TID, 166)
#elif (OSEE_TC_CORE1_166_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_166_ISR_HND, 166)
#else
#error Invalid value for OSEE_TC_CORE1_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 166)
OSEE_ISR_ALIGN(_core1_, 1, 166)
#endif /* OSEE_TC_CORE1_166_ISR_CAT */
#if (defined(OSEE_TC_CORE1_167_ISR_CAT))
#if (OSEE_TC_CORE1_167_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_167_ISR_TID, 167)
#elif (OSEE_TC_CORE1_167_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_167_ISR_HND, 167)
#else
#error Invalid value for OSEE_TC_CORE1_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 167)
OSEE_ISR_ALIGN(_core1_, 1, 167)
#endif /* OSEE_TC_CORE1_167_ISR_CAT */
#if (defined(OSEE_TC_CORE1_168_ISR_CAT))
#if (OSEE_TC_CORE1_168_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_168_ISR_TID, 168)
#elif (OSEE_TC_CORE1_168_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_168_ISR_HND, 168)
#else
#error Invalid value for OSEE_TC_CORE1_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 168)
OSEE_ISR_ALIGN(_core1_, 1, 168)
#endif /* OSEE_TC_CORE1_168_ISR_CAT */
#if (defined(OSEE_TC_CORE1_169_ISR_CAT))
#if (OSEE_TC_CORE1_169_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_169_ISR_TID, 169)
#elif (OSEE_TC_CORE1_169_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_169_ISR_HND, 169)
#else
#error Invalid value for OSEE_TC_CORE1_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 169)
OSEE_ISR_ALIGN(_core1_, 1, 169)
#endif /* OSEE_TC_CORE1_169_ISR_CAT */
#if (defined(OSEE_TC_CORE1_170_ISR_CAT))
#if (OSEE_TC_CORE1_170_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_170_ISR_TID, 170)
#elif (OSEE_TC_CORE1_170_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_170_ISR_HND, 170)
#else
#error Invalid value for OSEE_TC_CORE1_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 170)
OSEE_ISR_ALIGN(_core1_, 1, 170)
#endif /* OSEE_TC_CORE1_170_ISR_CAT */
#if (defined(OSEE_TC_CORE1_171_ISR_CAT))
#if (OSEE_TC_CORE1_171_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_171_ISR_TID, 171)
#elif (OSEE_TC_CORE1_171_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_171_ISR_HND, 171)
#else
#error Invalid value for OSEE_TC_CORE1_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 171)
OSEE_ISR_ALIGN(_core1_, 1, 171)
#endif /* OSEE_TC_CORE1_171_ISR_CAT */
#if (defined(OSEE_TC_CORE1_172_ISR_CAT))
#if (OSEE_TC_CORE1_172_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_172_ISR_TID, 172)
#elif (OSEE_TC_CORE1_172_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_172_ISR_HND, 172)
#else
#error Invalid value for OSEE_TC_CORE1_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 172)
OSEE_ISR_ALIGN(_core1_, 1, 172)
#endif /* OSEE_TC_CORE1_172_ISR_CAT */
#if (defined(OSEE_TC_CORE1_173_ISR_CAT))
#if (OSEE_TC_CORE1_173_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_173_ISR_TID, 173)
#elif (OSEE_TC_CORE1_173_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_173_ISR_HND, 173)
#else
#error Invalid value for OSEE_TC_CORE1_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 173)
OSEE_ISR_ALIGN(_core1_, 1, 173)
#endif /* OSEE_TC_CORE1_173_ISR_CAT */
#if (defined(OSEE_TC_CORE1_174_ISR_CAT))
#if (OSEE_TC_CORE1_174_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_174_ISR_TID, 174)
#elif (OSEE_TC_CORE1_174_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_174_ISR_HND, 174)
#else
#error Invalid value for OSEE_TC_CORE1_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 174)
OSEE_ISR_ALIGN(_core1_, 1, 174)
#endif /* OSEE_TC_CORE1_174_ISR_CAT */
#if (defined(OSEE_TC_CORE1_175_ISR_CAT))
#if (OSEE_TC_CORE1_175_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_175_ISR_TID, 175)
#elif (OSEE_TC_CORE1_175_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_175_ISR_HND, 175)
#else
#error Invalid value for OSEE_TC_CORE1_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 175)
OSEE_ISR_ALIGN(_core1_, 1, 175)
#endif /* OSEE_TC_CORE1_175_ISR_CAT */
#if (defined(OSEE_TC_CORE1_176_ISR_CAT))
#if (OSEE_TC_CORE1_176_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_176_ISR_TID, 176)
#elif (OSEE_TC_CORE1_176_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_176_ISR_HND, 176)
#else
#error Invalid value for OSEE_TC_CORE1_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 176)
OSEE_ISR_ALIGN(_core1_, 1, 176)
#endif /* OSEE_TC_CORE1_176_ISR_CAT */
#if (defined(OSEE_TC_CORE1_177_ISR_CAT))
#if (OSEE_TC_CORE1_177_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_177_ISR_TID, 177)
#elif (OSEE_TC_CORE1_177_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_177_ISR_HND, 177)
#else
#error Invalid value for OSEE_TC_CORE1_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 177)
OSEE_ISR_ALIGN(_core1_, 1, 177)
#endif /* OSEE_TC_CORE1_177_ISR_CAT */
#if (defined(OSEE_TC_CORE1_178_ISR_CAT))
#if (OSEE_TC_CORE1_178_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_178_ISR_TID, 178)
#elif (OSEE_TC_CORE1_178_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_178_ISR_HND, 178)
#else
#error Invalid value for OSEE_TC_CORE1_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 178)
OSEE_ISR_ALIGN(_core1_, 1, 178)
#endif /* OSEE_TC_CORE1_178_ISR_CAT */
#if (defined(OSEE_TC_CORE1_179_ISR_CAT))
#if (OSEE_TC_CORE1_179_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_179_ISR_TID, 179)
#elif (OSEE_TC_CORE1_179_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_179_ISR_HND, 179)
#else
#error Invalid value for OSEE_TC_CORE1_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 179)
OSEE_ISR_ALIGN(_core1_, 1, 179)
#endif /* OSEE_TC_CORE1_179_ISR_CAT */
#if (defined(OSEE_TC_CORE1_180_ISR_CAT))
#if (OSEE_TC_CORE1_180_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_180_ISR_TID, 180)
#elif (OSEE_TC_CORE1_180_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_180_ISR_HND, 180)
#else
#error Invalid value for OSEE_TC_CORE1_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 180)
OSEE_ISR_ALIGN(_core1_, 1, 180)
#endif /* OSEE_TC_CORE1_180_ISR_CAT */
#if (defined(OSEE_TC_CORE1_181_ISR_CAT))
#if (OSEE_TC_CORE1_181_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_181_ISR_TID, 181)
#elif (OSEE_TC_CORE1_181_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_181_ISR_HND, 181)
#else
#error Invalid value for OSEE_TC_CORE1_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 181)
OSEE_ISR_ALIGN(_core1_, 1, 181)
#endif /* OSEE_TC_CORE1_181_ISR_CAT */
#if (defined(OSEE_TC_CORE1_182_ISR_CAT))
#if (OSEE_TC_CORE1_182_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_182_ISR_TID, 182)
#elif (OSEE_TC_CORE1_182_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_182_ISR_HND, 182)
#else
#error Invalid value for OSEE_TC_CORE1_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 182)
OSEE_ISR_ALIGN(_core1_, 1, 182)
#endif /* OSEE_TC_CORE1_182_ISR_CAT */
#if (defined(OSEE_TC_CORE1_183_ISR_CAT))
#if (OSEE_TC_CORE1_183_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_183_ISR_TID, 183)
#elif (OSEE_TC_CORE1_183_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_183_ISR_HND, 183)
#else
#error Invalid value for OSEE_TC_CORE1_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 183)
OSEE_ISR_ALIGN(_core1_, 1, 183)
#endif /* OSEE_TC_CORE1_183_ISR_CAT */
#if (defined(OSEE_TC_CORE1_184_ISR_CAT))
#if (OSEE_TC_CORE1_184_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_184_ISR_TID, 184)
#elif (OSEE_TC_CORE1_184_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_184_ISR_HND, 184)
#else
#error Invalid value for OSEE_TC_CORE1_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 184)
OSEE_ISR_ALIGN(_core1_, 1, 184)
#endif /* OSEE_TC_CORE1_184_ISR_CAT */
#if (defined(OSEE_TC_CORE1_185_ISR_CAT))
#if (OSEE_TC_CORE1_185_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_185_ISR_TID, 185)
#elif (OSEE_TC_CORE1_185_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_185_ISR_HND, 185)
#else
#error Invalid value for OSEE_TC_CORE1_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 185)
OSEE_ISR_ALIGN(_core1_, 1, 185)
#endif /* OSEE_TC_CORE1_185_ISR_CAT */
#if (defined(OSEE_TC_CORE1_186_ISR_CAT))
#if (OSEE_TC_CORE1_186_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_186_ISR_TID, 186)
#elif (OSEE_TC_CORE1_186_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_186_ISR_HND, 186)
#else
#error Invalid value for OSEE_TC_CORE1_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 186)
OSEE_ISR_ALIGN(_core1_, 1, 186)
#endif /* OSEE_TC_CORE1_186_ISR_CAT */
#if (defined(OSEE_TC_CORE1_187_ISR_CAT))
#if (OSEE_TC_CORE1_187_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_187_ISR_TID, 187)
#elif (OSEE_TC_CORE1_187_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_187_ISR_HND, 187)
#else
#error Invalid value for OSEE_TC_CORE1_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 187)
OSEE_ISR_ALIGN(_core1_, 1, 187)
#endif /* OSEE_TC_CORE1_187_ISR_CAT */
#if (defined(OSEE_TC_CORE1_188_ISR_CAT))
#if (OSEE_TC_CORE1_188_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_188_ISR_TID, 188)
#elif (OSEE_TC_CORE1_188_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_188_ISR_HND, 188)
#else
#error Invalid value for OSEE_TC_CORE1_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 188)
OSEE_ISR_ALIGN(_core1_, 1, 188)
#endif /* OSEE_TC_CORE1_188_ISR_CAT */
#if (defined(OSEE_TC_CORE1_189_ISR_CAT))
#if (OSEE_TC_CORE1_189_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_189_ISR_TID, 189)
#elif (OSEE_TC_CORE1_189_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_189_ISR_HND, 189)
#else
#error Invalid value for OSEE_TC_CORE1_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 189)
OSEE_ISR_ALIGN(_core1_, 1, 189)
#endif /* OSEE_TC_CORE1_189_ISR_CAT */
#if (defined(OSEE_TC_CORE1_190_ISR_CAT))
#if (OSEE_TC_CORE1_190_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_190_ISR_TID, 190)
#elif (OSEE_TC_CORE1_190_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_190_ISR_HND, 190)
#else
#error Invalid value for OSEE_TC_CORE1_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 190)
OSEE_ISR_ALIGN(_core1_, 1, 190)
#endif /* OSEE_TC_CORE1_190_ISR_CAT */
#if (defined(OSEE_TC_CORE1_191_ISR_CAT))
#if (OSEE_TC_CORE1_191_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_191_ISR_TID, 191)
#elif (OSEE_TC_CORE1_191_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_191_ISR_HND, 191)
#else
#error Invalid value for OSEE_TC_CORE1_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 191)
OSEE_ISR_ALIGN(_core1_, 1, 191)
#endif /* OSEE_TC_CORE1_191_ISR_CAT */
#if (defined(OSEE_TC_CORE1_192_ISR_CAT))
#if (OSEE_TC_CORE1_192_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_192_ISR_TID, 192)
#elif (OSEE_TC_CORE1_192_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_192_ISR_HND, 192)
#else
#error Invalid value for OSEE_TC_CORE1_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 192)
OSEE_ISR_ALIGN(_core1_, 1, 192)
#endif /* OSEE_TC_CORE1_192_ISR_CAT */
#if (defined(OSEE_TC_CORE1_193_ISR_CAT))
#if (OSEE_TC_CORE1_193_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_193_ISR_TID, 193)
#elif (OSEE_TC_CORE1_193_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_193_ISR_HND, 193)
#else
#error Invalid value for OSEE_TC_CORE1_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 193)
OSEE_ISR_ALIGN(_core1_, 1, 193)
#endif /* OSEE_TC_CORE1_193_ISR_CAT */
#if (defined(OSEE_TC_CORE1_194_ISR_CAT))
#if (OSEE_TC_CORE1_194_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_194_ISR_TID, 194)
#elif (OSEE_TC_CORE1_194_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_194_ISR_HND, 194)
#else
#error Invalid value for OSEE_TC_CORE1_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 194)
OSEE_ISR_ALIGN(_core1_, 1, 194)
#endif /* OSEE_TC_CORE1_194_ISR_CAT */
#if (defined(OSEE_TC_CORE1_195_ISR_CAT))
#if (OSEE_TC_CORE1_195_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_195_ISR_TID, 195)
#elif (OSEE_TC_CORE1_195_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_195_ISR_HND, 195)
#else
#error Invalid value for OSEE_TC_CORE1_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 195)
OSEE_ISR_ALIGN(_core1_, 1, 195)
#endif /* OSEE_TC_CORE1_195_ISR_CAT */
#if (defined(OSEE_TC_CORE1_196_ISR_CAT))
#if (OSEE_TC_CORE1_196_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_196_ISR_TID, 196)
#elif (OSEE_TC_CORE1_196_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_196_ISR_HND, 196)
#else
#error Invalid value for OSEE_TC_CORE1_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 196)
OSEE_ISR_ALIGN(_core1_, 1, 196)
#endif /* OSEE_TC_CORE1_196_ISR_CAT */
#if (defined(OSEE_TC_CORE1_197_ISR_CAT))
#if (OSEE_TC_CORE1_197_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_197_ISR_TID, 197)
#elif (OSEE_TC_CORE1_197_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_197_ISR_HND, 197)
#else
#error Invalid value for OSEE_TC_CORE1_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 197)
OSEE_ISR_ALIGN(_core1_, 1, 197)
#endif /* OSEE_TC_CORE1_197_ISR_CAT */
#if (defined(OSEE_TC_CORE1_198_ISR_CAT))
#if (OSEE_TC_CORE1_198_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_198_ISR_TID, 198)
#elif (OSEE_TC_CORE1_198_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_198_ISR_HND, 198)
#else
#error Invalid value for OSEE_TC_CORE1_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 198)
OSEE_ISR_ALIGN(_core1_, 1, 198)
#endif /* OSEE_TC_CORE1_198_ISR_CAT */
#if (defined(OSEE_TC_CORE1_199_ISR_CAT))
#if (OSEE_TC_CORE1_199_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_199_ISR_TID, 199)
#elif (OSEE_TC_CORE1_199_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_199_ISR_HND, 199)
#else
#error Invalid value for OSEE_TC_CORE1_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 199)
OSEE_ISR_ALIGN(_core1_, 1, 199)
#endif /* OSEE_TC_CORE1_199_ISR_CAT */
#if (defined(OSEE_TC_CORE1_200_ISR_CAT))
#if (OSEE_TC_CORE1_200_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_200_ISR_TID, 200)
#elif (OSEE_TC_CORE1_200_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_200_ISR_HND, 200)
#else
#error Invalid value for OSEE_TC_CORE1_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 200)
OSEE_ISR_ALIGN(_core1_, 1, 200)
#endif /* OSEE_TC_CORE1_200_ISR_CAT */
#if (defined(OSEE_TC_CORE1_201_ISR_CAT))
#if (OSEE_TC_CORE1_201_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_201_ISR_TID, 201)
#elif (OSEE_TC_CORE1_201_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_201_ISR_HND, 201)
#else
#error Invalid value for OSEE_TC_CORE1_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 201)
OSEE_ISR_ALIGN(_core1_, 1, 201)
#endif /* OSEE_TC_CORE1_201_ISR_CAT */
#if (defined(OSEE_TC_CORE1_202_ISR_CAT))
#if (OSEE_TC_CORE1_202_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_202_ISR_TID, 202)
#elif (OSEE_TC_CORE1_202_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_202_ISR_HND, 202)
#else
#error Invalid value for OSEE_TC_CORE1_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 202)
OSEE_ISR_ALIGN(_core1_, 1, 202)
#endif /* OSEE_TC_CORE1_202_ISR_CAT */
#if (defined(OSEE_TC_CORE1_203_ISR_CAT))
#if (OSEE_TC_CORE1_203_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_203_ISR_TID, 203)
#elif (OSEE_TC_CORE1_203_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_203_ISR_HND, 203)
#else
#error Invalid value for OSEE_TC_CORE1_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 203)
OSEE_ISR_ALIGN(_core1_, 1, 203)
#endif /* OSEE_TC_CORE1_203_ISR_CAT */
#if (defined(OSEE_TC_CORE1_204_ISR_CAT))
#if (OSEE_TC_CORE1_204_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_204_ISR_TID, 204)
#elif (OSEE_TC_CORE1_204_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_204_ISR_HND, 204)
#else
#error Invalid value for OSEE_TC_CORE1_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 204)
OSEE_ISR_ALIGN(_core1_, 1, 204)
#endif /* OSEE_TC_CORE1_204_ISR_CAT */
#if (defined(OSEE_TC_CORE1_205_ISR_CAT))
#if (OSEE_TC_CORE1_205_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_205_ISR_TID, 205)
#elif (OSEE_TC_CORE1_205_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_205_ISR_HND, 205)
#else
#error Invalid value for OSEE_TC_CORE1_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 205)
OSEE_ISR_ALIGN(_core1_, 1, 205)
#endif /* OSEE_TC_CORE1_205_ISR_CAT */
#if (defined(OSEE_TC_CORE1_206_ISR_CAT))
#if (OSEE_TC_CORE1_206_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_206_ISR_TID, 206)
#elif (OSEE_TC_CORE1_206_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_206_ISR_HND, 206)
#else
#error Invalid value for OSEE_TC_CORE1_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 206)
OSEE_ISR_ALIGN(_core1_, 1, 206)
#endif /* OSEE_TC_CORE1_206_ISR_CAT */
#if (defined(OSEE_TC_CORE1_207_ISR_CAT))
#if (OSEE_TC_CORE1_207_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_207_ISR_TID, 207)
#elif (OSEE_TC_CORE1_207_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_207_ISR_HND, 207)
#else
#error Invalid value for OSEE_TC_CORE1_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 207)
OSEE_ISR_ALIGN(_core1_, 1, 207)
#endif /* OSEE_TC_CORE1_207_ISR_CAT */
#if (defined(OSEE_TC_CORE1_208_ISR_CAT))
#if (OSEE_TC_CORE1_208_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_208_ISR_TID, 208)
#elif (OSEE_TC_CORE1_208_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_208_ISR_HND, 208)
#else
#error Invalid value for OSEE_TC_CORE1_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 208)
OSEE_ISR_ALIGN(_core1_, 1, 208)
#endif /* OSEE_TC_CORE1_208_ISR_CAT */
#if (defined(OSEE_TC_CORE1_209_ISR_CAT))
#if (OSEE_TC_CORE1_209_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_209_ISR_TID, 209)
#elif (OSEE_TC_CORE1_209_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_209_ISR_HND, 209)
#else
#error Invalid value for OSEE_TC_CORE1_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 209)
OSEE_ISR_ALIGN(_core1_, 1, 209)
#endif /* OSEE_TC_CORE1_209_ISR_CAT */
#if (defined(OSEE_TC_CORE1_210_ISR_CAT))
#if (OSEE_TC_CORE1_210_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_210_ISR_TID, 210)
#elif (OSEE_TC_CORE1_210_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_210_ISR_HND, 210)
#else
#error Invalid value for OSEE_TC_CORE1_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 210)
OSEE_ISR_ALIGN(_core1_, 1, 210)
#endif /* OSEE_TC_CORE1_210_ISR_CAT */
#if (defined(OSEE_TC_CORE1_211_ISR_CAT))
#if (OSEE_TC_CORE1_211_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_211_ISR_TID, 211)
#elif (OSEE_TC_CORE1_211_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_211_ISR_HND, 211)
#else
#error Invalid value for OSEE_TC_CORE1_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 211)
OSEE_ISR_ALIGN(_core1_, 1, 211)
#endif /* OSEE_TC_CORE1_211_ISR_CAT */
#if (defined(OSEE_TC_CORE1_212_ISR_CAT))
#if (OSEE_TC_CORE1_212_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_212_ISR_TID, 212)
#elif (OSEE_TC_CORE1_212_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_212_ISR_HND, 212)
#else
#error Invalid value for OSEE_TC_CORE1_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 212)
OSEE_ISR_ALIGN(_core1_, 1, 212)
#endif /* OSEE_TC_CORE1_212_ISR_CAT */
#if (defined(OSEE_TC_CORE1_213_ISR_CAT))
#if (OSEE_TC_CORE1_213_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_213_ISR_TID, 213)
#elif (OSEE_TC_CORE1_213_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_213_ISR_HND, 213)
#else
#error Invalid value for OSEE_TC_CORE1_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 213)
OSEE_ISR_ALIGN(_core1_, 1, 213)
#endif /* OSEE_TC_CORE1_213_ISR_CAT */
#if (defined(OSEE_TC_CORE1_214_ISR_CAT))
#if (OSEE_TC_CORE1_214_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_214_ISR_TID, 214)
#elif (OSEE_TC_CORE1_214_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_214_ISR_HND, 214)
#else
#error Invalid value for OSEE_TC_CORE1_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 214)
OSEE_ISR_ALIGN(_core1_, 1, 214)
#endif /* OSEE_TC_CORE1_214_ISR_CAT */
#if (defined(OSEE_TC_CORE1_215_ISR_CAT))
#if (OSEE_TC_CORE1_215_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_215_ISR_TID, 215)
#elif (OSEE_TC_CORE1_215_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_215_ISR_HND, 215)
#else
#error Invalid value for OSEE_TC_CORE1_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 215)
OSEE_ISR_ALIGN(_core1_, 1, 215)
#endif /* OSEE_TC_CORE1_215_ISR_CAT */
#if (defined(OSEE_TC_CORE1_216_ISR_CAT))
#if (OSEE_TC_CORE1_216_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_216_ISR_TID, 216)
#elif (OSEE_TC_CORE1_216_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_216_ISR_HND, 216)
#else
#error Invalid value for OSEE_TC_CORE1_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 216)
OSEE_ISR_ALIGN(_core1_, 1, 216)
#endif /* OSEE_TC_CORE1_216_ISR_CAT */
#if (defined(OSEE_TC_CORE1_217_ISR_CAT))
#if (OSEE_TC_CORE1_217_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_217_ISR_TID, 217)
#elif (OSEE_TC_CORE1_217_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_217_ISR_HND, 217)
#else
#error Invalid value for OSEE_TC_CORE1_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 217)
OSEE_ISR_ALIGN(_core1_, 1, 217)
#endif /* OSEE_TC_CORE1_217_ISR_CAT */
#if (defined(OSEE_TC_CORE1_218_ISR_CAT))
#if (OSEE_TC_CORE1_218_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_218_ISR_TID, 218)
#elif (OSEE_TC_CORE1_218_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_218_ISR_HND, 218)
#else
#error Invalid value for OSEE_TC_CORE1_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 218)
OSEE_ISR_ALIGN(_core1_, 1, 218)
#endif /* OSEE_TC_CORE1_218_ISR_CAT */
#if (defined(OSEE_TC_CORE1_219_ISR_CAT))
#if (OSEE_TC_CORE1_219_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_219_ISR_TID, 219)
#elif (OSEE_TC_CORE1_219_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_219_ISR_HND, 219)
#else
#error Invalid value for OSEE_TC_CORE1_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 219)
OSEE_ISR_ALIGN(_core1_, 1, 219)
#endif /* OSEE_TC_CORE1_219_ISR_CAT */
#if (defined(OSEE_TC_CORE1_220_ISR_CAT))
#if (OSEE_TC_CORE1_220_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_220_ISR_TID, 220)
#elif (OSEE_TC_CORE1_220_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_220_ISR_HND, 220)
#else
#error Invalid value for OSEE_TC_CORE1_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 220)
OSEE_ISR_ALIGN(_core1_, 1, 220)
#endif /* OSEE_TC_CORE1_220_ISR_CAT */
#if (defined(OSEE_TC_CORE1_221_ISR_CAT))
#if (OSEE_TC_CORE1_221_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_221_ISR_TID, 221)
#elif (OSEE_TC_CORE1_221_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_221_ISR_HND, 221)
#else
#error Invalid value for OSEE_TC_CORE1_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 221)
OSEE_ISR_ALIGN(_core1_, 1, 221)
#endif /* OSEE_TC_CORE1_221_ISR_CAT */
#if (defined(OSEE_TC_CORE1_222_ISR_CAT))
#if (OSEE_TC_CORE1_222_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_222_ISR_TID, 222)
#elif (OSEE_TC_CORE1_222_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_222_ISR_HND, 222)
#else
#error Invalid value for OSEE_TC_CORE1_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 222)
OSEE_ISR_ALIGN(_core1_, 1, 222)
#endif /* OSEE_TC_CORE1_222_ISR_CAT */
#if (defined(OSEE_TC_CORE1_223_ISR_CAT))
#if (OSEE_TC_CORE1_223_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_223_ISR_TID, 223)
#elif (OSEE_TC_CORE1_223_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_223_ISR_HND, 223)
#else
#error Invalid value for OSEE_TC_CORE1_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 223)
OSEE_ISR_ALIGN(_core1_, 1, 223)
#endif /* OSEE_TC_CORE1_223_ISR_CAT */
#if (defined(OSEE_TC_CORE1_224_ISR_CAT))
#if (OSEE_TC_CORE1_224_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_224_ISR_TID, 224)
#elif (OSEE_TC_CORE1_224_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_224_ISR_HND, 224)
#else
#error Invalid value for OSEE_TC_CORE1_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 224)
OSEE_ISR_ALIGN(_core1_, 1, 224)
#endif /* OSEE_TC_CORE1_224_ISR_CAT */
#if (defined(OSEE_TC_CORE1_225_ISR_CAT))
#if (OSEE_TC_CORE1_225_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_225_ISR_TID, 225)
#elif (OSEE_TC_CORE1_225_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_225_ISR_HND, 225)
#else
#error Invalid value for OSEE_TC_CORE1_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 225)
OSEE_ISR_ALIGN(_core1_, 1, 225)
#endif /* OSEE_TC_CORE1_225_ISR_CAT */
#if (defined(OSEE_TC_CORE1_226_ISR_CAT))
#if (OSEE_TC_CORE1_226_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_226_ISR_TID, 226)
#elif (OSEE_TC_CORE1_226_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_226_ISR_HND, 226)
#else
#error Invalid value for OSEE_TC_CORE1_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 226)
OSEE_ISR_ALIGN(_core1_, 1, 226)
#endif /* OSEE_TC_CORE1_226_ISR_CAT */
#if (defined(OSEE_TC_CORE1_227_ISR_CAT))
#if (OSEE_TC_CORE1_227_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_227_ISR_TID, 227)
#elif (OSEE_TC_CORE1_227_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_227_ISR_HND, 227)
#else
#error Invalid value for OSEE_TC_CORE1_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 227)
OSEE_ISR_ALIGN(_core1_, 1, 227)
#endif /* OSEE_TC_CORE1_227_ISR_CAT */
#if (defined(OSEE_TC_CORE1_228_ISR_CAT))
#if (OSEE_TC_CORE1_228_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_228_ISR_TID, 228)
#elif (OSEE_TC_CORE1_228_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_228_ISR_HND, 228)
#else
#error Invalid value for OSEE_TC_CORE1_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 228)
OSEE_ISR_ALIGN(_core1_, 1, 228)
#endif /* OSEE_TC_CORE1_228_ISR_CAT */
#if (defined(OSEE_TC_CORE1_229_ISR_CAT))
#if (OSEE_TC_CORE1_229_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_229_ISR_TID, 229)
#elif (OSEE_TC_CORE1_229_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_229_ISR_HND, 229)
#else
#error Invalid value for OSEE_TC_CORE1_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 229)
OSEE_ISR_ALIGN(_core1_, 1, 229)
#endif /* OSEE_TC_CORE1_229_ISR_CAT */
#if (defined(OSEE_TC_CORE1_230_ISR_CAT))
#if (OSEE_TC_CORE1_230_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_230_ISR_TID, 230)
#elif (OSEE_TC_CORE1_230_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_230_ISR_HND, 230)
#else
#error Invalid value for OSEE_TC_CORE1_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 230)
OSEE_ISR_ALIGN(_core1_, 1, 230)
#endif /* OSEE_TC_CORE1_230_ISR_CAT */
#if (defined(OSEE_TC_CORE1_231_ISR_CAT))
#if (OSEE_TC_CORE1_231_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_231_ISR_TID, 231)
#elif (OSEE_TC_CORE1_231_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_231_ISR_HND, 231)
#else
#error Invalid value for OSEE_TC_CORE1_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 231)
OSEE_ISR_ALIGN(_core1_, 1, 231)
#endif /* OSEE_TC_CORE1_231_ISR_CAT */
#if (defined(OSEE_TC_CORE1_232_ISR_CAT))
#if (OSEE_TC_CORE1_232_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_232_ISR_TID, 232)
#elif (OSEE_TC_CORE1_232_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_232_ISR_HND, 232)
#else
#error Invalid value for OSEE_TC_CORE1_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 232)
OSEE_ISR_ALIGN(_core1_, 1, 232)
#endif /* OSEE_TC_CORE1_232_ISR_CAT */
#if (defined(OSEE_TC_CORE1_233_ISR_CAT))
#if (OSEE_TC_CORE1_233_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_233_ISR_TID, 233)
#elif (OSEE_TC_CORE1_233_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_233_ISR_HND, 233)
#else
#error Invalid value for OSEE_TC_CORE1_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 233)
OSEE_ISR_ALIGN(_core1_, 1, 233)
#endif /* OSEE_TC_CORE1_233_ISR_CAT */
#if (defined(OSEE_TC_CORE1_234_ISR_CAT))
#if (OSEE_TC_CORE1_234_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_234_ISR_TID, 234)
#elif (OSEE_TC_CORE1_234_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_234_ISR_HND, 234)
#else
#error Invalid value for OSEE_TC_CORE1_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 234)
OSEE_ISR_ALIGN(_core1_, 1, 234)
#endif /* OSEE_TC_CORE1_234_ISR_CAT */
#if (defined(OSEE_TC_CORE1_235_ISR_CAT))
#if (OSEE_TC_CORE1_235_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_235_ISR_TID, 235)
#elif (OSEE_TC_CORE1_235_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_235_ISR_HND, 235)
#else
#error Invalid value for OSEE_TC_CORE1_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 235)
OSEE_ISR_ALIGN(_core1_, 1, 235)
#endif /* OSEE_TC_CORE1_235_ISR_CAT */
#if (defined(OSEE_TC_CORE1_236_ISR_CAT))
#if (OSEE_TC_CORE1_236_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_236_ISR_TID, 236)
#elif (OSEE_TC_CORE1_236_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_236_ISR_HND, 236)
#else
#error Invalid value for OSEE_TC_CORE1_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 236)
OSEE_ISR_ALIGN(_core1_, 1, 236)
#endif /* OSEE_TC_CORE1_236_ISR_CAT */
#if (defined(OSEE_TC_CORE1_237_ISR_CAT))
#if (OSEE_TC_CORE1_237_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_237_ISR_TID, 237)
#elif (OSEE_TC_CORE1_237_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_237_ISR_HND, 237)
#else
#error Invalid value for OSEE_TC_CORE1_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 237)
OSEE_ISR_ALIGN(_core1_, 1, 237)
#endif /* OSEE_TC_CORE1_237_ISR_CAT */
#if (defined(OSEE_TC_CORE1_238_ISR_CAT))
#if (OSEE_TC_CORE1_238_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_238_ISR_TID, 238)
#elif (OSEE_TC_CORE1_238_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_238_ISR_HND, 238)
#else
#error Invalid value for OSEE_TC_CORE1_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 238)
OSEE_ISR_ALIGN(_core1_, 1, 238)
#endif /* OSEE_TC_CORE1_238_ISR_CAT */
#if (defined(OSEE_TC_CORE1_239_ISR_CAT))
#if (OSEE_TC_CORE1_239_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_239_ISR_TID, 239)
#elif (OSEE_TC_CORE1_239_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_239_ISR_HND, 239)
#else
#error Invalid value for OSEE_TC_CORE1_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 239)
OSEE_ISR_ALIGN(_core1_, 1, 239)
#endif /* OSEE_TC_CORE1_239_ISR_CAT */
#if (defined(OSEE_TC_CORE1_240_ISR_CAT))
#if (OSEE_TC_CORE1_240_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_240_ISR_TID, 240)
#elif (OSEE_TC_CORE1_240_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_240_ISR_HND, 240)
#else
#error Invalid value for OSEE_TC_CORE1_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 240)
OSEE_ISR_ALIGN(_core1_, 1, 240)
#endif /* OSEE_TC_CORE1_240_ISR_CAT */
#if (defined(OSEE_TC_CORE1_241_ISR_CAT))
#if (OSEE_TC_CORE1_241_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_241_ISR_TID, 241)
#elif (OSEE_TC_CORE1_241_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_241_ISR_HND, 241)
#else
#error Invalid value for OSEE_TC_CORE1_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 241)
OSEE_ISR_ALIGN(_core1_, 1, 241)
#endif /* OSEE_TC_CORE1_241_ISR_CAT */
#if (defined(OSEE_TC_CORE1_242_ISR_CAT))
#if (OSEE_TC_CORE1_242_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_242_ISR_TID, 242)
#elif (OSEE_TC_CORE1_242_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_242_ISR_HND, 242)
#else
#error Invalid value for OSEE_TC_CORE1_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 242)
OSEE_ISR_ALIGN(_core1_, 1, 242)
#endif /* OSEE_TC_CORE1_242_ISR_CAT */
#if (defined(OSEE_TC_CORE1_243_ISR_CAT))
#if (OSEE_TC_CORE1_243_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_243_ISR_TID, 243)
#elif (OSEE_TC_CORE1_243_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_243_ISR_HND, 243)
#else
#error Invalid value for OSEE_TC_CORE1_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 243)
OSEE_ISR_ALIGN(_core1_, 1, 243)
#endif /* OSEE_TC_CORE1_243_ISR_CAT */
#if (defined(OSEE_TC_CORE1_244_ISR_CAT))
#if (OSEE_TC_CORE1_244_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_244_ISR_TID, 244)
#elif (OSEE_TC_CORE1_244_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_244_ISR_HND, 244)
#else
#error Invalid value for OSEE_TC_CORE1_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 244)
OSEE_ISR_ALIGN(_core1_, 1, 244)
#endif /* OSEE_TC_CORE1_244_ISR_CAT */
#if (defined(OSEE_TC_CORE1_245_ISR_CAT))
#if (OSEE_TC_CORE1_245_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_245_ISR_TID, 245)
#elif (OSEE_TC_CORE1_245_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_245_ISR_HND, 245)
#else
#error Invalid value for OSEE_TC_CORE1_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 245)
OSEE_ISR_ALIGN(_core1_, 1, 245)
#endif /* OSEE_TC_CORE1_245_ISR_CAT */
#if (defined(OSEE_TC_CORE1_246_ISR_CAT))
#if (OSEE_TC_CORE1_246_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_246_ISR_TID, 246)
#elif (OSEE_TC_CORE1_246_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_246_ISR_HND, 246)
#else
#error Invalid value for OSEE_TC_CORE1_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 246)
OSEE_ISR_ALIGN(_core1_, 1, 246)
#endif /* OSEE_TC_CORE1_246_ISR_CAT */
#if (defined(OSEE_TC_CORE1_247_ISR_CAT))
#if (OSEE_TC_CORE1_247_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_247_ISR_TID, 247)
#elif (OSEE_TC_CORE1_247_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_247_ISR_HND, 247)
#else
#error Invalid value for OSEE_TC_CORE1_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 247)
OSEE_ISR_ALIGN(_core1_, 1, 247)
#endif /* OSEE_TC_CORE1_247_ISR_CAT */
#if (defined(OSEE_TC_CORE1_248_ISR_CAT))
#if (OSEE_TC_CORE1_248_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_248_ISR_TID, 248)
#elif (OSEE_TC_CORE1_248_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_248_ISR_HND, 248)
#else
#error Invalid value for OSEE_TC_CORE1_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 248)
OSEE_ISR_ALIGN(_core1_, 1, 248)
#endif /* OSEE_TC_CORE1_248_ISR_CAT */
#if (defined(OSEE_TC_CORE1_249_ISR_CAT))
#if (OSEE_TC_CORE1_249_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_249_ISR_TID, 249)
#elif (OSEE_TC_CORE1_249_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_249_ISR_HND, 249)
#else
#error Invalid value for OSEE_TC_CORE1_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 249)
OSEE_ISR_ALIGN(_core1_, 1, 249)
#endif /* OSEE_TC_CORE1_249_ISR_CAT */
#if (defined(OSEE_TC_CORE1_250_ISR_CAT))
#if (OSEE_TC_CORE1_250_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_250_ISR_TID, 250)
#elif (OSEE_TC_CORE1_250_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_250_ISR_HND, 250)
#else
#error Invalid value for OSEE_TC_CORE1_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 250)
OSEE_ISR_ALIGN(_core1_, 1, 250)
#endif /* OSEE_TC_CORE1_250_ISR_CAT */
#if (defined(OSEE_TC_CORE1_251_ISR_CAT))
#if (OSEE_TC_CORE1_251_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_251_ISR_TID, 251)
#elif (OSEE_TC_CORE1_251_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_251_ISR_HND, 251)
#else
#error Invalid value for OSEE_TC_CORE1_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 251)
OSEE_ISR_ALIGN(_core1_, 1, 251)
#endif /* OSEE_TC_CORE1_251_ISR_CAT */
#if (defined(OSEE_TC_CORE1_252_ISR_CAT))
#if (OSEE_TC_CORE1_252_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_252_ISR_TID, 252)
#elif (OSEE_TC_CORE1_252_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_252_ISR_HND, 252)
#else
#error Invalid value for OSEE_TC_CORE1_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 252)
OSEE_ISR_ALIGN(_core1_, 1, 252)
#endif /* OSEE_TC_CORE1_252_ISR_CAT */
#if (defined(OSEE_TC_CORE1_253_ISR_CAT))
#if (OSEE_TC_CORE1_253_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_253_ISR_TID, 253)
#elif (OSEE_TC_CORE1_253_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_253_ISR_HND, 253)
#else
#error Invalid value for OSEE_TC_CORE1_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 253)
OSEE_ISR_ALIGN(_core1_, 1, 253)
#endif /* OSEE_TC_CORE1_253_ISR_CAT */
#if (defined(OSEE_TC_CORE1_254_ISR_CAT))
#if (OSEE_TC_CORE1_254_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_254_ISR_TID, 254)
#elif (OSEE_TC_CORE1_254_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_254_ISR_HND, 254)
#else
#error Invalid value for OSEE_TC_CORE1_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 254)
OSEE_ISR_ALIGN(_core1_, 1, 254)
#endif /* OSEE_TC_CORE1_254_ISR_CAT */
#if (defined(OSEE_TC_CORE1_255_ISR_CAT))
#if (OSEE_TC_CORE1_255_ISR_CAT == 2)
OSEE_ISR2_DEF(_core1_, 1, OSEE_TC_CORE1_255_ISR_TID, 255)
#elif (OSEE_TC_CORE1_255_ISR_CAT == 1)
OSEE_ISR1_DEF(_core1_, 1, OSEE_TC_CORE1_255_ISR_HND, 255)
#else
#error Invalid value for OSEE_TC_CORE1_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE1_ISR_MAX_PRIO >= 255)
OSEE_ISR_ALIGN(_core1_, 1, 255)
#endif /* OSEE_TC_CORE1_255_ISR_CAT */
#endif /* OSEE_TC_CORE1_ISR_MAX_PRIO */
#if (defined(__GNUC__))
__asm__ ("\t.size __INTTAB1, . - __INTTAB1\n\
\t.section .text,\"ax\",@progbits");
#endif /* __GNUC__ */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x02U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x04U)
#if (defined(__GNUC__))
__asm__ ("\n\
  .section .inttab_cpu2, \"ax\", @progbits\n\
  .globl __INTTAB2\n\
__INTTAB2:");
/* ERIKA's Interrupt Vector Definition */
#if (defined(OSEE_TC_CORE2_ISR_MAX_PRIO))
__asm__(
"  .skip 0x20");
#endif /* OSEE_TC_CORE2_ISR_MAX_PRIO */
#endif /* __GNUC__ */
#if (defined(OSEE_TC_CORE2_ISR_MAX_PRIO))
OSEE_ISR2_DEF(_core2_, 2, -1, 1)
#if (defined(OSEE_TC_CORE2_2_ISR_CAT))
#if (OSEE_TC_CORE2_2_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_2_ISR_TID, 2)
#elif (OSEE_TC_CORE2_2_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_2_ISR_HND, 2)
#else
#error Invalid value for OSEE_TC_CORE2_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 2)
OSEE_ISR_ALIGN(_core2_, 2, 2)
#endif /* OSEE_TC_CORE2_2_ISR_CAT */
#if (defined(OSEE_TC_CORE2_3_ISR_CAT))
#if (OSEE_TC_CORE2_3_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_3_ISR_TID, 3)
#elif (OSEE_TC_CORE2_3_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_3_ISR_HND, 3)
#else
#error Invalid value for OSEE_TC_CORE2_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 3)
OSEE_ISR_ALIGN(_core2_, 2, 3)
#endif /* OSEE_TC_CORE2_3_ISR_CAT */
#if (defined(OSEE_TC_CORE2_4_ISR_CAT))
#if (OSEE_TC_CORE2_4_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_4_ISR_TID, 4)
#elif (OSEE_TC_CORE2_4_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_4_ISR_HND, 4)
#else
#error Invalid value for OSEE_TC_CORE2_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 4)
OSEE_ISR_ALIGN(_core2_, 2, 4)
#endif /* OSEE_TC_CORE2_4_ISR_CAT */
#if (defined(OSEE_TC_CORE2_5_ISR_CAT))
#if (OSEE_TC_CORE2_5_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_5_ISR_TID, 5)
#elif (OSEE_TC_CORE2_5_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_5_ISR_HND, 5)
#else
#error Invalid value for OSEE_TC_CORE2_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 5)
OSEE_ISR_ALIGN(_core2_, 2, 5)
#endif /* OSEE_TC_CORE2_5_ISR_CAT */
#if (defined(OSEE_TC_CORE2_6_ISR_CAT))
#if (OSEE_TC_CORE2_6_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_6_ISR_TID, 6)
#elif (OSEE_TC_CORE2_6_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_6_ISR_HND, 6)
#else
#error Invalid value for OSEE_TC_CORE2_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 6)
OSEE_ISR_ALIGN(_core2_, 2, 6)
#endif /* OSEE_TC_CORE2_6_ISR_CAT */
#if (defined(OSEE_TC_CORE2_7_ISR_CAT))
#if (OSEE_TC_CORE2_7_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_7_ISR_TID, 7)
#elif (OSEE_TC_CORE2_7_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_7_ISR_HND, 7)
#else
#error Invalid value for OSEE_TC_CORE2_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 7)
OSEE_ISR_ALIGN(_core2_, 2, 7)
#endif /* OSEE_TC_CORE2_7_ISR_CAT */
#if (defined(OSEE_TC_CORE2_8_ISR_CAT))
#if (OSEE_TC_CORE2_8_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_8_ISR_TID, 8)
#elif (OSEE_TC_CORE2_8_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_8_ISR_HND, 8)
#else
#error Invalid value for OSEE_TC_CORE2_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 8)
OSEE_ISR_ALIGN(_core2_, 2, 8)
#endif /* OSEE_TC_CORE2_8_ISR_CAT */
#if (defined(OSEE_TC_CORE2_9_ISR_CAT))
#if (OSEE_TC_CORE2_9_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_9_ISR_TID, 9)
#elif (OSEE_TC_CORE2_9_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_9_ISR_HND, 9)
#else
#error Invalid value for OSEE_TC_CORE2_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 9)
OSEE_ISR_ALIGN(_core2_, 2, 9)
#endif /* OSEE_TC_CORE2_9_ISR_CAT */
#if (defined(OSEE_TC_CORE2_10_ISR_CAT))
#if (OSEE_TC_CORE2_10_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_10_ISR_TID, 10)
#elif (OSEE_TC_CORE2_10_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_10_ISR_HND, 10)
#else
#error Invalid value for OSEE_TC_CORE2_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 10)
OSEE_ISR_ALIGN(_core2_, 2, 10)
#endif /* OSEE_TC_CORE2_10_ISR_CAT */
#if (defined(OSEE_TC_CORE2_11_ISR_CAT))
#if (OSEE_TC_CORE2_11_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_11_ISR_TID, 11)
#elif (OSEE_TC_CORE2_11_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_11_ISR_HND, 11)
#else
#error Invalid value for OSEE_TC_CORE2_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 11)
OSEE_ISR_ALIGN(_core2_, 2, 11)
#endif /* OSEE_TC_CORE2_11_ISR_CAT */
#if (defined(OSEE_TC_CORE2_12_ISR_CAT))
#if (OSEE_TC_CORE2_12_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_12_ISR_TID, 12)
#elif (OSEE_TC_CORE2_12_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_12_ISR_HND, 12)
#else
#error Invalid value for OSEE_TC_CORE2_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 12)
OSEE_ISR_ALIGN(_core2_, 2, 12)
#endif /* OSEE_TC_CORE2_12_ISR_CAT */
#if (defined(OSEE_TC_CORE2_13_ISR_CAT))
#if (OSEE_TC_CORE2_13_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_13_ISR_TID, 13)
#elif (OSEE_TC_CORE2_13_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_13_ISR_HND, 13)
#else
#error Invalid value for OSEE_TC_CORE2_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 13)
OSEE_ISR_ALIGN(_core2_, 2, 13)
#endif /* OSEE_TC_CORE2_13_ISR_CAT */
#if (defined(OSEE_TC_CORE2_14_ISR_CAT))
#if (OSEE_TC_CORE2_14_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_14_ISR_TID, 14)
#elif (OSEE_TC_CORE2_14_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_14_ISR_HND, 14)
#else
#error Invalid value for OSEE_TC_CORE2_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 14)
OSEE_ISR_ALIGN(_core2_, 2, 14)
#endif /* OSEE_TC_CORE2_14_ISR_CAT */
#if (defined(OSEE_TC_CORE2_15_ISR_CAT))
#if (OSEE_TC_CORE2_15_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_15_ISR_TID, 15)
#elif (OSEE_TC_CORE2_15_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_15_ISR_HND, 15)
#else
#error Invalid value for OSEE_TC_CORE2_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 15)
OSEE_ISR_ALIGN(_core2_, 2, 15)
#endif /* OSEE_TC_CORE2_15_ISR_CAT */
#if (defined(OSEE_TC_CORE2_16_ISR_CAT))
#if (OSEE_TC_CORE2_16_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_16_ISR_TID, 16)
#elif (OSEE_TC_CORE2_16_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_16_ISR_HND, 16)
#else
#error Invalid value for OSEE_TC_CORE2_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 16)
OSEE_ISR_ALIGN(_core2_, 2, 16)
#endif /* OSEE_TC_CORE2_16_ISR_CAT */
#if (defined(OSEE_TC_CORE2_17_ISR_CAT))
#if (OSEE_TC_CORE2_17_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_17_ISR_TID, 17)
#elif (OSEE_TC_CORE2_17_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_17_ISR_HND, 17)
#else
#error Invalid value for OSEE_TC_CORE2_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 17)
OSEE_ISR_ALIGN(_core2_, 2, 17)
#endif /* OSEE_TC_CORE2_17_ISR_CAT */
#if (defined(OSEE_TC_CORE2_18_ISR_CAT))
#if (OSEE_TC_CORE2_18_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_18_ISR_TID, 18)
#elif (OSEE_TC_CORE2_18_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_18_ISR_HND, 18)
#else
#error Invalid value for OSEE_TC_CORE2_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 18)
OSEE_ISR_ALIGN(_core2_, 2, 18)
#endif /* OSEE_TC_CORE2_18_ISR_CAT */
#if (defined(OSEE_TC_CORE2_19_ISR_CAT))
#if (OSEE_TC_CORE2_19_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_19_ISR_TID, 19)
#elif (OSEE_TC_CORE2_19_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_19_ISR_HND, 19)
#else
#error Invalid value for OSEE_TC_CORE2_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 19)
OSEE_ISR_ALIGN(_core2_, 2, 19)
#endif /* OSEE_TC_CORE2_19_ISR_CAT */
#if (defined(OSEE_TC_CORE2_20_ISR_CAT))
#if (OSEE_TC_CORE2_20_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_20_ISR_TID, 20)
#elif (OSEE_TC_CORE2_20_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_20_ISR_HND, 20)
#else
#error Invalid value for OSEE_TC_CORE2_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 20)
OSEE_ISR_ALIGN(_core2_, 2, 20)
#endif /* OSEE_TC_CORE2_20_ISR_CAT */
#if (defined(OSEE_TC_CORE2_21_ISR_CAT))
#if (OSEE_TC_CORE2_21_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_21_ISR_TID, 21)
#elif (OSEE_TC_CORE2_21_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_21_ISR_HND, 21)
#else
#error Invalid value for OSEE_TC_CORE2_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 21)
OSEE_ISR_ALIGN(_core2_, 2, 21)
#endif /* OSEE_TC_CORE2_21_ISR_CAT */
#if (defined(OSEE_TC_CORE2_22_ISR_CAT))
#if (OSEE_TC_CORE2_22_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_22_ISR_TID, 22)
#elif (OSEE_TC_CORE2_22_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_22_ISR_HND, 22)
#else
#error Invalid value for OSEE_TC_CORE2_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 22)
OSEE_ISR_ALIGN(_core2_, 2, 22)
#endif /* OSEE_TC_CORE2_22_ISR_CAT */
#if (defined(OSEE_TC_CORE2_23_ISR_CAT))
#if (OSEE_TC_CORE2_23_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_23_ISR_TID, 23)
#elif (OSEE_TC_CORE2_23_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_23_ISR_HND, 23)
#else
#error Invalid value for OSEE_TC_CORE2_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 23)
OSEE_ISR_ALIGN(_core2_, 2, 23)
#endif /* OSEE_TC_CORE2_23_ISR_CAT */
#if (defined(OSEE_TC_CORE2_24_ISR_CAT))
#if (OSEE_TC_CORE2_24_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_24_ISR_TID, 24)
#elif (OSEE_TC_CORE2_24_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_24_ISR_HND, 24)
#else
#error Invalid value for OSEE_TC_CORE2_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 24)
OSEE_ISR_ALIGN(_core2_, 2, 24)
#endif /* OSEE_TC_CORE2_24_ISR_CAT */
#if (defined(OSEE_TC_CORE2_25_ISR_CAT))
#if (OSEE_TC_CORE2_25_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_25_ISR_TID, 25)
#elif (OSEE_TC_CORE2_25_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_25_ISR_HND, 25)
#else
#error Invalid value for OSEE_TC_CORE2_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 25)
OSEE_ISR_ALIGN(_core2_, 2, 25)
#endif /* OSEE_TC_CORE2_25_ISR_CAT */
#if (defined(OSEE_TC_CORE2_26_ISR_CAT))
#if (OSEE_TC_CORE2_26_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_26_ISR_TID, 26)
#elif (OSEE_TC_CORE2_26_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_26_ISR_HND, 26)
#else
#error Invalid value for OSEE_TC_CORE2_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 26)
OSEE_ISR_ALIGN(_core2_, 2, 26)
#endif /* OSEE_TC_CORE2_26_ISR_CAT */
#if (defined(OSEE_TC_CORE2_27_ISR_CAT))
#if (OSEE_TC_CORE2_27_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_27_ISR_TID, 27)
#elif (OSEE_TC_CORE2_27_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_27_ISR_HND, 27)
#else
#error Invalid value for OSEE_TC_CORE2_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 27)
OSEE_ISR_ALIGN(_core2_, 2, 27)
#endif /* OSEE_TC_CORE2_27_ISR_CAT */
#if (defined(OSEE_TC_CORE2_28_ISR_CAT))
#if (OSEE_TC_CORE2_28_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_28_ISR_TID, 28)
#elif (OSEE_TC_CORE2_28_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_28_ISR_HND, 28)
#else
#error Invalid value for OSEE_TC_CORE2_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 28)
OSEE_ISR_ALIGN(_core2_, 2, 28)
#endif /* OSEE_TC_CORE2_28_ISR_CAT */
#if (defined(OSEE_TC_CORE2_29_ISR_CAT))
#if (OSEE_TC_CORE2_29_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_29_ISR_TID, 29)
#elif (OSEE_TC_CORE2_29_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_29_ISR_HND, 29)
#else
#error Invalid value for OSEE_TC_CORE2_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 29)
OSEE_ISR_ALIGN(_core2_, 2, 29)
#endif /* OSEE_TC_CORE2_29_ISR_CAT */
#if (defined(OSEE_TC_CORE2_30_ISR_CAT))
#if (OSEE_TC_CORE2_30_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_30_ISR_TID, 30)
#elif (OSEE_TC_CORE2_30_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_30_ISR_HND, 30)
#else
#error Invalid value for OSEE_TC_CORE2_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 30)
OSEE_ISR_ALIGN(_core2_, 2, 30)
#endif /* OSEE_TC_CORE2_30_ISR_CAT */
#if (defined(OSEE_TC_CORE2_31_ISR_CAT))
#if (OSEE_TC_CORE2_31_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_31_ISR_TID, 31)
#elif (OSEE_TC_CORE2_31_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_31_ISR_HND, 31)
#else
#error Invalid value for OSEE_TC_CORE2_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 31)
OSEE_ISR_ALIGN(_core2_, 2, 31)
#endif /* OSEE_TC_CORE2_31_ISR_CAT */
#if (defined(OSEE_TC_CORE2_32_ISR_CAT))
#if (OSEE_TC_CORE2_32_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_32_ISR_TID, 32)
#elif (OSEE_TC_CORE2_32_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_32_ISR_HND, 32)
#else
#error Invalid value for OSEE_TC_CORE2_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 32)
OSEE_ISR_ALIGN(_core2_, 2, 32)
#endif /* OSEE_TC_CORE2_32_ISR_CAT */
#if (defined(OSEE_TC_CORE2_33_ISR_CAT))
#if (OSEE_TC_CORE2_33_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_33_ISR_TID, 33)
#elif (OSEE_TC_CORE2_33_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_33_ISR_HND, 33)
#else
#error Invalid value for OSEE_TC_CORE2_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 33)
OSEE_ISR_ALIGN(_core2_, 2, 33)
#endif /* OSEE_TC_CORE2_33_ISR_CAT */
#if (defined(OSEE_TC_CORE2_34_ISR_CAT))
#if (OSEE_TC_CORE2_34_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_34_ISR_TID, 34)
#elif (OSEE_TC_CORE2_34_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_34_ISR_HND, 34)
#else
#error Invalid value for OSEE_TC_CORE2_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 34)
OSEE_ISR_ALIGN(_core2_, 2, 34)
#endif /* OSEE_TC_CORE2_34_ISR_CAT */
#if (defined(OSEE_TC_CORE2_35_ISR_CAT))
#if (OSEE_TC_CORE2_35_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_35_ISR_TID, 35)
#elif (OSEE_TC_CORE2_35_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_35_ISR_HND, 35)
#else
#error Invalid value for OSEE_TC_CORE2_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 35)
OSEE_ISR_ALIGN(_core2_, 2, 35)
#endif /* OSEE_TC_CORE2_35_ISR_CAT */
#if (defined(OSEE_TC_CORE2_36_ISR_CAT))
#if (OSEE_TC_CORE2_36_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_36_ISR_TID, 36)
#elif (OSEE_TC_CORE2_36_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_36_ISR_HND, 36)
#else
#error Invalid value for OSEE_TC_CORE2_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 36)
OSEE_ISR_ALIGN(_core2_, 2, 36)
#endif /* OSEE_TC_CORE2_36_ISR_CAT */
#if (defined(OSEE_TC_CORE2_37_ISR_CAT))
#if (OSEE_TC_CORE2_37_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_37_ISR_TID, 37)
#elif (OSEE_TC_CORE2_37_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_37_ISR_HND, 37)
#else
#error Invalid value for OSEE_TC_CORE2_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 37)
OSEE_ISR_ALIGN(_core2_, 2, 37)
#endif /* OSEE_TC_CORE2_37_ISR_CAT */
#if (defined(OSEE_TC_CORE2_38_ISR_CAT))
#if (OSEE_TC_CORE2_38_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_38_ISR_TID, 38)
#elif (OSEE_TC_CORE2_38_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_38_ISR_HND, 38)
#else
#error Invalid value for OSEE_TC_CORE2_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 38)
OSEE_ISR_ALIGN(_core2_, 2, 38)
#endif /* OSEE_TC_CORE2_38_ISR_CAT */
#if (defined(OSEE_TC_CORE2_39_ISR_CAT))
#if (OSEE_TC_CORE2_39_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_39_ISR_TID, 39)
#elif (OSEE_TC_CORE2_39_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_39_ISR_HND, 39)
#else
#error Invalid value for OSEE_TC_CORE2_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 39)
OSEE_ISR_ALIGN(_core2_, 2, 39)
#endif /* OSEE_TC_CORE2_39_ISR_CAT */
#if (defined(OSEE_TC_CORE2_40_ISR_CAT))
#if (OSEE_TC_CORE2_40_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_40_ISR_TID, 40)
#elif (OSEE_TC_CORE2_40_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_40_ISR_HND, 40)
#else
#error Invalid value for OSEE_TC_CORE2_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 40)
OSEE_ISR_ALIGN(_core2_, 2, 40)
#endif /* OSEE_TC_CORE2_40_ISR_CAT */
#if (defined(OSEE_TC_CORE2_41_ISR_CAT))
#if (OSEE_TC_CORE2_41_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_41_ISR_TID, 41)
#elif (OSEE_TC_CORE2_41_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_41_ISR_HND, 41)
#else
#error Invalid value for OSEE_TC_CORE2_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 41)
OSEE_ISR_ALIGN(_core2_, 2, 41)
#endif /* OSEE_TC_CORE2_41_ISR_CAT */
#if (defined(OSEE_TC_CORE2_42_ISR_CAT))
#if (OSEE_TC_CORE2_42_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_42_ISR_TID, 42)
#elif (OSEE_TC_CORE2_42_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_42_ISR_HND, 42)
#else
#error Invalid value for OSEE_TC_CORE2_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 42)
OSEE_ISR_ALIGN(_core2_, 2, 42)
#endif /* OSEE_TC_CORE2_42_ISR_CAT */
#if (defined(OSEE_TC_CORE2_43_ISR_CAT))
#if (OSEE_TC_CORE2_43_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_43_ISR_TID, 43)
#elif (OSEE_TC_CORE2_43_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_43_ISR_HND, 43)
#else
#error Invalid value for OSEE_TC_CORE2_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 43)
OSEE_ISR_ALIGN(_core2_, 2, 43)
#endif /* OSEE_TC_CORE2_43_ISR_CAT */
#if (defined(OSEE_TC_CORE2_44_ISR_CAT))
#if (OSEE_TC_CORE2_44_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_44_ISR_TID, 44)
#elif (OSEE_TC_CORE2_44_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_44_ISR_HND, 44)
#else
#error Invalid value for OSEE_TC_CORE2_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 44)
OSEE_ISR_ALIGN(_core2_, 2, 44)
#endif /* OSEE_TC_CORE2_44_ISR_CAT */
#if (defined(OSEE_TC_CORE2_45_ISR_CAT))
#if (OSEE_TC_CORE2_45_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_45_ISR_TID, 45)
#elif (OSEE_TC_CORE2_45_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_45_ISR_HND, 45)
#else
#error Invalid value for OSEE_TC_CORE2_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 45)
OSEE_ISR_ALIGN(_core2_, 2, 45)
#endif /* OSEE_TC_CORE2_45_ISR_CAT */
#if (defined(OSEE_TC_CORE2_46_ISR_CAT))
#if (OSEE_TC_CORE2_46_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_46_ISR_TID, 46)
#elif (OSEE_TC_CORE2_46_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_46_ISR_HND, 46)
#else
#error Invalid value for OSEE_TC_CORE2_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 46)
OSEE_ISR_ALIGN(_core2_, 2, 46)
#endif /* OSEE_TC_CORE2_46_ISR_CAT */
#if (defined(OSEE_TC_CORE2_47_ISR_CAT))
#if (OSEE_TC_CORE2_47_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_47_ISR_TID, 47)
#elif (OSEE_TC_CORE2_47_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_47_ISR_HND, 47)
#else
#error Invalid value for OSEE_TC_CORE2_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 47)
OSEE_ISR_ALIGN(_core2_, 2, 47)
#endif /* OSEE_TC_CORE2_47_ISR_CAT */
#if (defined(OSEE_TC_CORE2_48_ISR_CAT))
#if (OSEE_TC_CORE2_48_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_48_ISR_TID, 48)
#elif (OSEE_TC_CORE2_48_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_48_ISR_HND, 48)
#else
#error Invalid value for OSEE_TC_CORE2_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 48)
OSEE_ISR_ALIGN(_core2_, 2, 48)
#endif /* OSEE_TC_CORE2_48_ISR_CAT */
#if (defined(OSEE_TC_CORE2_49_ISR_CAT))
#if (OSEE_TC_CORE2_49_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_49_ISR_TID, 49)
#elif (OSEE_TC_CORE2_49_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_49_ISR_HND, 49)
#else
#error Invalid value for OSEE_TC_CORE2_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 49)
OSEE_ISR_ALIGN(_core2_, 2, 49)
#endif /* OSEE_TC_CORE2_49_ISR_CAT */
#if (defined(OSEE_TC_CORE2_50_ISR_CAT))
#if (OSEE_TC_CORE2_50_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_50_ISR_TID, 50)
#elif (OSEE_TC_CORE2_50_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_50_ISR_HND, 50)
#else
#error Invalid value for OSEE_TC_CORE2_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 50)
OSEE_ISR_ALIGN(_core2_, 2, 50)
#endif /* OSEE_TC_CORE2_50_ISR_CAT */
#if (defined(OSEE_TC_CORE2_51_ISR_CAT))
#if (OSEE_TC_CORE2_51_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_51_ISR_TID, 51)
#elif (OSEE_TC_CORE2_51_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_51_ISR_HND, 51)
#else
#error Invalid value for OSEE_TC_CORE2_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 51)
OSEE_ISR_ALIGN(_core2_, 2, 51)
#endif /* OSEE_TC_CORE2_51_ISR_CAT */
#if (defined(OSEE_TC_CORE2_52_ISR_CAT))
#if (OSEE_TC_CORE2_52_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_52_ISR_TID, 52)
#elif (OSEE_TC_CORE2_52_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_52_ISR_HND, 52)
#else
#error Invalid value for OSEE_TC_CORE2_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 52)
OSEE_ISR_ALIGN(_core2_, 2, 52)
#endif /* OSEE_TC_CORE2_52_ISR_CAT */
#if (defined(OSEE_TC_CORE2_53_ISR_CAT))
#if (OSEE_TC_CORE2_53_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_53_ISR_TID, 53)
#elif (OSEE_TC_CORE2_53_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_53_ISR_HND, 53)
#else
#error Invalid value for OSEE_TC_CORE2_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 53)
OSEE_ISR_ALIGN(_core2_, 2, 53)
#endif /* OSEE_TC_CORE2_53_ISR_CAT */
#if (defined(OSEE_TC_CORE2_54_ISR_CAT))
#if (OSEE_TC_CORE2_54_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_54_ISR_TID, 54)
#elif (OSEE_TC_CORE2_54_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_54_ISR_HND, 54)
#else
#error Invalid value for OSEE_TC_CORE2_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 54)
OSEE_ISR_ALIGN(_core2_, 2, 54)
#endif /* OSEE_TC_CORE2_54_ISR_CAT */
#if (defined(OSEE_TC_CORE2_55_ISR_CAT))
#if (OSEE_TC_CORE2_55_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_55_ISR_TID, 55)
#elif (OSEE_TC_CORE2_55_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_55_ISR_HND, 55)
#else
#error Invalid value for OSEE_TC_CORE2_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 55)
OSEE_ISR_ALIGN(_core2_, 2, 55)
#endif /* OSEE_TC_CORE2_55_ISR_CAT */
#if (defined(OSEE_TC_CORE2_56_ISR_CAT))
#if (OSEE_TC_CORE2_56_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_56_ISR_TID, 56)
#elif (OSEE_TC_CORE2_56_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_56_ISR_HND, 56)
#else
#error Invalid value for OSEE_TC_CORE2_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 56)
OSEE_ISR_ALIGN(_core2_, 2, 56)
#endif /* OSEE_TC_CORE2_56_ISR_CAT */
#if (defined(OSEE_TC_CORE2_57_ISR_CAT))
#if (OSEE_TC_CORE2_57_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_57_ISR_TID, 57)
#elif (OSEE_TC_CORE2_57_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_57_ISR_HND, 57)
#else
#error Invalid value for OSEE_TC_CORE2_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 57)
OSEE_ISR_ALIGN(_core2_, 2, 57)
#endif /* OSEE_TC_CORE2_57_ISR_CAT */
#if (defined(OSEE_TC_CORE2_58_ISR_CAT))
#if (OSEE_TC_CORE2_58_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_58_ISR_TID, 58)
#elif (OSEE_TC_CORE2_58_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_58_ISR_HND, 58)
#else
#error Invalid value for OSEE_TC_CORE2_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 58)
OSEE_ISR_ALIGN(_core2_, 2, 58)
#endif /* OSEE_TC_CORE2_58_ISR_CAT */
#if (defined(OSEE_TC_CORE2_59_ISR_CAT))
#if (OSEE_TC_CORE2_59_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_59_ISR_TID, 59)
#elif (OSEE_TC_CORE2_59_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_59_ISR_HND, 59)
#else
#error Invalid value for OSEE_TC_CORE2_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 59)
OSEE_ISR_ALIGN(_core2_, 2, 59)
#endif /* OSEE_TC_CORE2_59_ISR_CAT */
#if (defined(OSEE_TC_CORE2_60_ISR_CAT))
#if (OSEE_TC_CORE2_60_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_60_ISR_TID, 60)
#elif (OSEE_TC_CORE2_60_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_60_ISR_HND, 60)
#else
#error Invalid value for OSEE_TC_CORE2_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 60)
OSEE_ISR_ALIGN(_core2_, 2, 60)
#endif /* OSEE_TC_CORE2_60_ISR_CAT */
#if (defined(OSEE_TC_CORE2_61_ISR_CAT))
#if (OSEE_TC_CORE2_61_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_61_ISR_TID, 61)
#elif (OSEE_TC_CORE2_61_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_61_ISR_HND, 61)
#else
#error Invalid value for OSEE_TC_CORE2_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 61)
OSEE_ISR_ALIGN(_core2_, 2, 61)
#endif /* OSEE_TC_CORE2_61_ISR_CAT */
#if (defined(OSEE_TC_CORE2_62_ISR_CAT))
#if (OSEE_TC_CORE2_62_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_62_ISR_TID, 62)
#elif (OSEE_TC_CORE2_62_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_62_ISR_HND, 62)
#else
#error Invalid value for OSEE_TC_CORE2_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 62)
OSEE_ISR_ALIGN(_core2_, 2, 62)
#endif /* OSEE_TC_CORE2_62_ISR_CAT */
#if (defined(OSEE_TC_CORE2_63_ISR_CAT))
#if (OSEE_TC_CORE2_63_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_63_ISR_TID, 63)
#elif (OSEE_TC_CORE2_63_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_63_ISR_HND, 63)
#else
#error Invalid value for OSEE_TC_CORE2_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 63)
OSEE_ISR_ALIGN(_core2_, 2, 63)
#endif /* OSEE_TC_CORE2_63_ISR_CAT */
#if (defined(OSEE_TC_CORE2_64_ISR_CAT))
#if (OSEE_TC_CORE2_64_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_64_ISR_TID, 64)
#elif (OSEE_TC_CORE2_64_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_64_ISR_HND, 64)
#else
#error Invalid value for OSEE_TC_CORE2_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 64)
OSEE_ISR_ALIGN(_core2_, 2, 64)
#endif /* OSEE_TC_CORE2_64_ISR_CAT */
#if (defined(OSEE_TC_CORE2_65_ISR_CAT))
#if (OSEE_TC_CORE2_65_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_65_ISR_TID, 65)
#elif (OSEE_TC_CORE2_65_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_65_ISR_HND, 65)
#else
#error Invalid value for OSEE_TC_CORE2_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 65)
OSEE_ISR_ALIGN(_core2_, 2, 65)
#endif /* OSEE_TC_CORE2_65_ISR_CAT */
#if (defined(OSEE_TC_CORE2_66_ISR_CAT))
#if (OSEE_TC_CORE2_66_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_66_ISR_TID, 66)
#elif (OSEE_TC_CORE2_66_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_66_ISR_HND, 66)
#else
#error Invalid value for OSEE_TC_CORE2_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 66)
OSEE_ISR_ALIGN(_core2_, 2, 66)
#endif /* OSEE_TC_CORE2_66_ISR_CAT */
#if (defined(OSEE_TC_CORE2_67_ISR_CAT))
#if (OSEE_TC_CORE2_67_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_67_ISR_TID, 67)
#elif (OSEE_TC_CORE2_67_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_67_ISR_HND, 67)
#else
#error Invalid value for OSEE_TC_CORE2_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 67)
OSEE_ISR_ALIGN(_core2_, 2, 67)
#endif /* OSEE_TC_CORE2_67_ISR_CAT */
#if (defined(OSEE_TC_CORE2_68_ISR_CAT))
#if (OSEE_TC_CORE2_68_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_68_ISR_TID, 68)
#elif (OSEE_TC_CORE2_68_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_68_ISR_HND, 68)
#else
#error Invalid value for OSEE_TC_CORE2_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 68)
OSEE_ISR_ALIGN(_core2_, 2, 68)
#endif /* OSEE_TC_CORE2_68_ISR_CAT */
#if (defined(OSEE_TC_CORE2_69_ISR_CAT))
#if (OSEE_TC_CORE2_69_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_69_ISR_TID, 69)
#elif (OSEE_TC_CORE2_69_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_69_ISR_HND, 69)
#else
#error Invalid value for OSEE_TC_CORE2_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 69)
OSEE_ISR_ALIGN(_core2_, 2, 69)
#endif /* OSEE_TC_CORE2_69_ISR_CAT */
#if (defined(OSEE_TC_CORE2_70_ISR_CAT))
#if (OSEE_TC_CORE2_70_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_70_ISR_TID, 70)
#elif (OSEE_TC_CORE2_70_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_70_ISR_HND, 70)
#else
#error Invalid value for OSEE_TC_CORE2_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 70)
OSEE_ISR_ALIGN(_core2_, 2, 70)
#endif /* OSEE_TC_CORE2_70_ISR_CAT */
#if (defined(OSEE_TC_CORE2_71_ISR_CAT))
#if (OSEE_TC_CORE2_71_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_71_ISR_TID, 71)
#elif (OSEE_TC_CORE2_71_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_71_ISR_HND, 71)
#else
#error Invalid value for OSEE_TC_CORE2_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 71)
OSEE_ISR_ALIGN(_core2_, 2, 71)
#endif /* OSEE_TC_CORE2_71_ISR_CAT */
#if (defined(OSEE_TC_CORE2_72_ISR_CAT))
#if (OSEE_TC_CORE2_72_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_72_ISR_TID, 72)
#elif (OSEE_TC_CORE2_72_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_72_ISR_HND, 72)
#else
#error Invalid value for OSEE_TC_CORE2_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 72)
OSEE_ISR_ALIGN(_core2_, 2, 72)
#endif /* OSEE_TC_CORE2_72_ISR_CAT */
#if (defined(OSEE_TC_CORE2_73_ISR_CAT))
#if (OSEE_TC_CORE2_73_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_73_ISR_TID, 73)
#elif (OSEE_TC_CORE2_73_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_73_ISR_HND, 73)
#else
#error Invalid value for OSEE_TC_CORE2_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 73)
OSEE_ISR_ALIGN(_core2_, 2, 73)
#endif /* OSEE_TC_CORE2_73_ISR_CAT */
#if (defined(OSEE_TC_CORE2_74_ISR_CAT))
#if (OSEE_TC_CORE2_74_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_74_ISR_TID, 74)
#elif (OSEE_TC_CORE2_74_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_74_ISR_HND, 74)
#else
#error Invalid value for OSEE_TC_CORE2_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 74)
OSEE_ISR_ALIGN(_core2_, 2, 74)
#endif /* OSEE_TC_CORE2_74_ISR_CAT */
#if (defined(OSEE_TC_CORE2_75_ISR_CAT))
#if (OSEE_TC_CORE2_75_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_75_ISR_TID, 75)
#elif (OSEE_TC_CORE2_75_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_75_ISR_HND, 75)
#else
#error Invalid value for OSEE_TC_CORE2_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 75)
OSEE_ISR_ALIGN(_core2_, 2, 75)
#endif /* OSEE_TC_CORE2_75_ISR_CAT */
#if (defined(OSEE_TC_CORE2_76_ISR_CAT))
#if (OSEE_TC_CORE2_76_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_76_ISR_TID, 76)
#elif (OSEE_TC_CORE2_76_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_76_ISR_HND, 76)
#else
#error Invalid value for OSEE_TC_CORE2_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 76)
OSEE_ISR_ALIGN(_core2_, 2, 76)
#endif /* OSEE_TC_CORE2_76_ISR_CAT */
#if (defined(OSEE_TC_CORE2_77_ISR_CAT))
#if (OSEE_TC_CORE2_77_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_77_ISR_TID, 77)
#elif (OSEE_TC_CORE2_77_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_77_ISR_HND, 77)
#else
#error Invalid value for OSEE_TC_CORE2_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 77)
OSEE_ISR_ALIGN(_core2_, 2, 77)
#endif /* OSEE_TC_CORE2_77_ISR_CAT */
#if (defined(OSEE_TC_CORE2_78_ISR_CAT))
#if (OSEE_TC_CORE2_78_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_78_ISR_TID, 78)
#elif (OSEE_TC_CORE2_78_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_78_ISR_HND, 78)
#else
#error Invalid value for OSEE_TC_CORE2_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 78)
OSEE_ISR_ALIGN(_core2_, 2, 78)
#endif /* OSEE_TC_CORE2_78_ISR_CAT */
#if (defined(OSEE_TC_CORE2_79_ISR_CAT))
#if (OSEE_TC_CORE2_79_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_79_ISR_TID, 79)
#elif (OSEE_TC_CORE2_79_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_79_ISR_HND, 79)
#else
#error Invalid value for OSEE_TC_CORE2_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 79)
OSEE_ISR_ALIGN(_core2_, 2, 79)
#endif /* OSEE_TC_CORE2_79_ISR_CAT */
#if (defined(OSEE_TC_CORE2_80_ISR_CAT))
#if (OSEE_TC_CORE2_80_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_80_ISR_TID, 80)
#elif (OSEE_TC_CORE2_80_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_80_ISR_HND, 80)
#else
#error Invalid value for OSEE_TC_CORE2_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 80)
OSEE_ISR_ALIGN(_core2_, 2, 80)
#endif /* OSEE_TC_CORE2_80_ISR_CAT */
#if (defined(OSEE_TC_CORE2_81_ISR_CAT))
#if (OSEE_TC_CORE2_81_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_81_ISR_TID, 81)
#elif (OSEE_TC_CORE2_81_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_81_ISR_HND, 81)
#else
#error Invalid value for OSEE_TC_CORE2_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 81)
OSEE_ISR_ALIGN(_core2_, 2, 81)
#endif /* OSEE_TC_CORE2_81_ISR_CAT */
#if (defined(OSEE_TC_CORE2_82_ISR_CAT))
#if (OSEE_TC_CORE2_82_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_82_ISR_TID, 82)
#elif (OSEE_TC_CORE2_82_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_82_ISR_HND, 82)
#else
#error Invalid value for OSEE_TC_CORE2_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 82)
OSEE_ISR_ALIGN(_core2_, 2, 82)
#endif /* OSEE_TC_CORE2_82_ISR_CAT */
#if (defined(OSEE_TC_CORE2_83_ISR_CAT))
#if (OSEE_TC_CORE2_83_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_83_ISR_TID, 83)
#elif (OSEE_TC_CORE2_83_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_83_ISR_HND, 83)
#else
#error Invalid value for OSEE_TC_CORE2_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 83)
OSEE_ISR_ALIGN(_core2_, 2, 83)
#endif /* OSEE_TC_CORE2_83_ISR_CAT */
#if (defined(OSEE_TC_CORE2_84_ISR_CAT))
#if (OSEE_TC_CORE2_84_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_84_ISR_TID, 84)
#elif (OSEE_TC_CORE2_84_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_84_ISR_HND, 84)
#else
#error Invalid value for OSEE_TC_CORE2_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 84)
OSEE_ISR_ALIGN(_core2_, 2, 84)
#endif /* OSEE_TC_CORE2_84_ISR_CAT */
#if (defined(OSEE_TC_CORE2_85_ISR_CAT))
#if (OSEE_TC_CORE2_85_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_85_ISR_TID, 85)
#elif (OSEE_TC_CORE2_85_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_85_ISR_HND, 85)
#else
#error Invalid value for OSEE_TC_CORE2_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 85)
OSEE_ISR_ALIGN(_core2_, 2, 85)
#endif /* OSEE_TC_CORE2_85_ISR_CAT */
#if (defined(OSEE_TC_CORE2_86_ISR_CAT))
#if (OSEE_TC_CORE2_86_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_86_ISR_TID, 86)
#elif (OSEE_TC_CORE2_86_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_86_ISR_HND, 86)
#else
#error Invalid value for OSEE_TC_CORE2_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 86)
OSEE_ISR_ALIGN(_core2_, 2, 86)
#endif /* OSEE_TC_CORE2_86_ISR_CAT */
#if (defined(OSEE_TC_CORE2_87_ISR_CAT))
#if (OSEE_TC_CORE2_87_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_87_ISR_TID, 87)
#elif (OSEE_TC_CORE2_87_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_87_ISR_HND, 87)
#else
#error Invalid value for OSEE_TC_CORE2_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 87)
OSEE_ISR_ALIGN(_core2_, 2, 87)
#endif /* OSEE_TC_CORE2_87_ISR_CAT */
#if (defined(OSEE_TC_CORE2_88_ISR_CAT))
#if (OSEE_TC_CORE2_88_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_88_ISR_TID, 88)
#elif (OSEE_TC_CORE2_88_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_88_ISR_HND, 88)
#else
#error Invalid value for OSEE_TC_CORE2_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 88)
OSEE_ISR_ALIGN(_core2_, 2, 88)
#endif /* OSEE_TC_CORE2_88_ISR_CAT */
#if (defined(OSEE_TC_CORE2_89_ISR_CAT))
#if (OSEE_TC_CORE2_89_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_89_ISR_TID, 89)
#elif (OSEE_TC_CORE2_89_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_89_ISR_HND, 89)
#else
#error Invalid value for OSEE_TC_CORE2_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 89)
OSEE_ISR_ALIGN(_core2_, 2, 89)
#endif /* OSEE_TC_CORE2_89_ISR_CAT */
#if (defined(OSEE_TC_CORE2_90_ISR_CAT))
#if (OSEE_TC_CORE2_90_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_90_ISR_TID, 90)
#elif (OSEE_TC_CORE2_90_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_90_ISR_HND, 90)
#else
#error Invalid value for OSEE_TC_CORE2_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 90)
OSEE_ISR_ALIGN(_core2_, 2, 90)
#endif /* OSEE_TC_CORE2_90_ISR_CAT */
#if (defined(OSEE_TC_CORE2_91_ISR_CAT))
#if (OSEE_TC_CORE2_91_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_91_ISR_TID, 91)
#elif (OSEE_TC_CORE2_91_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_91_ISR_HND, 91)
#else
#error Invalid value for OSEE_TC_CORE2_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 91)
OSEE_ISR_ALIGN(_core2_, 2, 91)
#endif /* OSEE_TC_CORE2_91_ISR_CAT */
#if (defined(OSEE_TC_CORE2_92_ISR_CAT))
#if (OSEE_TC_CORE2_92_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_92_ISR_TID, 92)
#elif (OSEE_TC_CORE2_92_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_92_ISR_HND, 92)
#else
#error Invalid value for OSEE_TC_CORE2_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 92)
OSEE_ISR_ALIGN(_core2_, 2, 92)
#endif /* OSEE_TC_CORE2_92_ISR_CAT */
#if (defined(OSEE_TC_CORE2_93_ISR_CAT))
#if (OSEE_TC_CORE2_93_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_93_ISR_TID, 93)
#elif (OSEE_TC_CORE2_93_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_93_ISR_HND, 93)
#else
#error Invalid value for OSEE_TC_CORE2_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 93)
OSEE_ISR_ALIGN(_core2_, 2, 93)
#endif /* OSEE_TC_CORE2_93_ISR_CAT */
#if (defined(OSEE_TC_CORE2_94_ISR_CAT))
#if (OSEE_TC_CORE2_94_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_94_ISR_TID, 94)
#elif (OSEE_TC_CORE2_94_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_94_ISR_HND, 94)
#else
#error Invalid value for OSEE_TC_CORE2_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 94)
OSEE_ISR_ALIGN(_core2_, 2, 94)
#endif /* OSEE_TC_CORE2_94_ISR_CAT */
#if (defined(OSEE_TC_CORE2_95_ISR_CAT))
#if (OSEE_TC_CORE2_95_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_95_ISR_TID, 95)
#elif (OSEE_TC_CORE2_95_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_95_ISR_HND, 95)
#else
#error Invalid value for OSEE_TC_CORE2_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 95)
OSEE_ISR_ALIGN(_core2_, 2, 95)
#endif /* OSEE_TC_CORE2_95_ISR_CAT */
#if (defined(OSEE_TC_CORE2_96_ISR_CAT))
#if (OSEE_TC_CORE2_96_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_96_ISR_TID, 96)
#elif (OSEE_TC_CORE2_96_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_96_ISR_HND, 96)
#else
#error Invalid value for OSEE_TC_CORE2_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 96)
OSEE_ISR_ALIGN(_core2_, 2, 96)
#endif /* OSEE_TC_CORE2_96_ISR_CAT */
#if (defined(OSEE_TC_CORE2_97_ISR_CAT))
#if (OSEE_TC_CORE2_97_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_97_ISR_TID, 97)
#elif (OSEE_TC_CORE2_97_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_97_ISR_HND, 97)
#else
#error Invalid value for OSEE_TC_CORE2_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 97)
OSEE_ISR_ALIGN(_core2_, 2, 97)
#endif /* OSEE_TC_CORE2_97_ISR_CAT */
#if (defined(OSEE_TC_CORE2_98_ISR_CAT))
#if (OSEE_TC_CORE2_98_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_98_ISR_TID, 98)
#elif (OSEE_TC_CORE2_98_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_98_ISR_HND, 98)
#else
#error Invalid value for OSEE_TC_CORE2_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 98)
OSEE_ISR_ALIGN(_core2_, 2, 98)
#endif /* OSEE_TC_CORE2_98_ISR_CAT */
#if (defined(OSEE_TC_CORE2_99_ISR_CAT))
#if (OSEE_TC_CORE2_99_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_99_ISR_TID, 99)
#elif (OSEE_TC_CORE2_99_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_99_ISR_HND, 99)
#else
#error Invalid value for OSEE_TC_CORE2_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 99)
OSEE_ISR_ALIGN(_core2_, 2, 99)
#endif /* OSEE_TC_CORE2_99_ISR_CAT */
#if (defined(OSEE_TC_CORE2_100_ISR_CAT))
#if (OSEE_TC_CORE2_100_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_100_ISR_TID, 100)
#elif (OSEE_TC_CORE2_100_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_100_ISR_HND, 100)
#else
#error Invalid value for OSEE_TC_CORE2_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 100)
OSEE_ISR_ALIGN(_core2_, 2, 100)
#endif /* OSEE_TC_CORE2_100_ISR_CAT */
#if (defined(OSEE_TC_CORE2_101_ISR_CAT))
#if (OSEE_TC_CORE2_101_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_101_ISR_TID, 101)
#elif (OSEE_TC_CORE2_101_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_101_ISR_HND, 101)
#else
#error Invalid value for OSEE_TC_CORE2_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 101)
OSEE_ISR_ALIGN(_core2_, 2, 101)
#endif /* OSEE_TC_CORE2_101_ISR_CAT */
#if (defined(OSEE_TC_CORE2_102_ISR_CAT))
#if (OSEE_TC_CORE2_102_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_102_ISR_TID, 102)
#elif (OSEE_TC_CORE2_102_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_102_ISR_HND, 102)
#else
#error Invalid value for OSEE_TC_CORE2_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 102)
OSEE_ISR_ALIGN(_core2_, 2, 102)
#endif /* OSEE_TC_CORE2_102_ISR_CAT */
#if (defined(OSEE_TC_CORE2_103_ISR_CAT))
#if (OSEE_TC_CORE2_103_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_103_ISR_TID, 103)
#elif (OSEE_TC_CORE2_103_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_103_ISR_HND, 103)
#else
#error Invalid value for OSEE_TC_CORE2_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 103)
OSEE_ISR_ALIGN(_core2_, 2, 103)
#endif /* OSEE_TC_CORE2_103_ISR_CAT */
#if (defined(OSEE_TC_CORE2_104_ISR_CAT))
#if (OSEE_TC_CORE2_104_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_104_ISR_TID, 104)
#elif (OSEE_TC_CORE2_104_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_104_ISR_HND, 104)
#else
#error Invalid value for OSEE_TC_CORE2_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 104)
OSEE_ISR_ALIGN(_core2_, 2, 104)
#endif /* OSEE_TC_CORE2_104_ISR_CAT */
#if (defined(OSEE_TC_CORE2_105_ISR_CAT))
#if (OSEE_TC_CORE2_105_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_105_ISR_TID, 105)
#elif (OSEE_TC_CORE2_105_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_105_ISR_HND, 105)
#else
#error Invalid value for OSEE_TC_CORE2_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 105)
OSEE_ISR_ALIGN(_core2_, 2, 105)
#endif /* OSEE_TC_CORE2_105_ISR_CAT */
#if (defined(OSEE_TC_CORE2_106_ISR_CAT))
#if (OSEE_TC_CORE2_106_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_106_ISR_TID, 106)
#elif (OSEE_TC_CORE2_106_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_106_ISR_HND, 106)
#else
#error Invalid value for OSEE_TC_CORE2_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 106)
OSEE_ISR_ALIGN(_core2_, 2, 106)
#endif /* OSEE_TC_CORE2_106_ISR_CAT */
#if (defined(OSEE_TC_CORE2_107_ISR_CAT))
#if (OSEE_TC_CORE2_107_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_107_ISR_TID, 107)
#elif (OSEE_TC_CORE2_107_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_107_ISR_HND, 107)
#else
#error Invalid value for OSEE_TC_CORE2_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 107)
OSEE_ISR_ALIGN(_core2_, 2, 107)
#endif /* OSEE_TC_CORE2_107_ISR_CAT */
#if (defined(OSEE_TC_CORE2_108_ISR_CAT))
#if (OSEE_TC_CORE2_108_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_108_ISR_TID, 108)
#elif (OSEE_TC_CORE2_108_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_108_ISR_HND, 108)
#else
#error Invalid value for OSEE_TC_CORE2_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 108)
OSEE_ISR_ALIGN(_core2_, 2, 108)
#endif /* OSEE_TC_CORE2_108_ISR_CAT */
#if (defined(OSEE_TC_CORE2_109_ISR_CAT))
#if (OSEE_TC_CORE2_109_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_109_ISR_TID, 109)
#elif (OSEE_TC_CORE2_109_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_109_ISR_HND, 109)
#else
#error Invalid value for OSEE_TC_CORE2_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 109)
OSEE_ISR_ALIGN(_core2_, 2, 109)
#endif /* OSEE_TC_CORE2_109_ISR_CAT */
#if (defined(OSEE_TC_CORE2_110_ISR_CAT))
#if (OSEE_TC_CORE2_110_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_110_ISR_TID, 110)
#elif (OSEE_TC_CORE2_110_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_110_ISR_HND, 110)
#else
#error Invalid value for OSEE_TC_CORE2_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 110)
OSEE_ISR_ALIGN(_core2_, 2, 110)
#endif /* OSEE_TC_CORE2_110_ISR_CAT */
#if (defined(OSEE_TC_CORE2_111_ISR_CAT))
#if (OSEE_TC_CORE2_111_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_111_ISR_TID, 111)
#elif (OSEE_TC_CORE2_111_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_111_ISR_HND, 111)
#else
#error Invalid value for OSEE_TC_CORE2_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 111)
OSEE_ISR_ALIGN(_core2_, 2, 111)
#endif /* OSEE_TC_CORE2_111_ISR_CAT */
#if (defined(OSEE_TC_CORE2_112_ISR_CAT))
#if (OSEE_TC_CORE2_112_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_112_ISR_TID, 112)
#elif (OSEE_TC_CORE2_112_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_112_ISR_HND, 112)
#else
#error Invalid value for OSEE_TC_CORE2_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 112)
OSEE_ISR_ALIGN(_core2_, 2, 112)
#endif /* OSEE_TC_CORE2_112_ISR_CAT */
#if (defined(OSEE_TC_CORE2_113_ISR_CAT))
#if (OSEE_TC_CORE2_113_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_113_ISR_TID, 113)
#elif (OSEE_TC_CORE2_113_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_113_ISR_HND, 113)
#else
#error Invalid value for OSEE_TC_CORE2_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 113)
OSEE_ISR_ALIGN(_core2_, 2, 113)
#endif /* OSEE_TC_CORE2_113_ISR_CAT */
#if (defined(OSEE_TC_CORE2_114_ISR_CAT))
#if (OSEE_TC_CORE2_114_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_114_ISR_TID, 114)
#elif (OSEE_TC_CORE2_114_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_114_ISR_HND, 114)
#else
#error Invalid value for OSEE_TC_CORE2_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 114)
OSEE_ISR_ALIGN(_core2_, 2, 114)
#endif /* OSEE_TC_CORE2_114_ISR_CAT */
#if (defined(OSEE_TC_CORE2_115_ISR_CAT))
#if (OSEE_TC_CORE2_115_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_115_ISR_TID, 115)
#elif (OSEE_TC_CORE2_115_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_115_ISR_HND, 115)
#else
#error Invalid value for OSEE_TC_CORE2_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 115)
OSEE_ISR_ALIGN(_core2_, 2, 115)
#endif /* OSEE_TC_CORE2_115_ISR_CAT */
#if (defined(OSEE_TC_CORE2_116_ISR_CAT))
#if (OSEE_TC_CORE2_116_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_116_ISR_TID, 116)
#elif (OSEE_TC_CORE2_116_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_116_ISR_HND, 116)
#else
#error Invalid value for OSEE_TC_CORE2_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 116)
OSEE_ISR_ALIGN(_core2_, 2, 116)
#endif /* OSEE_TC_CORE2_116_ISR_CAT */
#if (defined(OSEE_TC_CORE2_117_ISR_CAT))
#if (OSEE_TC_CORE2_117_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_117_ISR_TID, 117)
#elif (OSEE_TC_CORE2_117_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_117_ISR_HND, 117)
#else
#error Invalid value for OSEE_TC_CORE2_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 117)
OSEE_ISR_ALIGN(_core2_, 2, 117)
#endif /* OSEE_TC_CORE2_117_ISR_CAT */
#if (defined(OSEE_TC_CORE2_118_ISR_CAT))
#if (OSEE_TC_CORE2_118_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_118_ISR_TID, 118)
#elif (OSEE_TC_CORE2_118_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_118_ISR_HND, 118)
#else
#error Invalid value for OSEE_TC_CORE2_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 118)
OSEE_ISR_ALIGN(_core2_, 2, 118)
#endif /* OSEE_TC_CORE2_118_ISR_CAT */
#if (defined(OSEE_TC_CORE2_119_ISR_CAT))
#if (OSEE_TC_CORE2_119_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_119_ISR_TID, 119)
#elif (OSEE_TC_CORE2_119_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_119_ISR_HND, 119)
#else
#error Invalid value for OSEE_TC_CORE2_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 119)
OSEE_ISR_ALIGN(_core2_, 2, 119)
#endif /* OSEE_TC_CORE2_119_ISR_CAT */
#if (defined(OSEE_TC_CORE2_120_ISR_CAT))
#if (OSEE_TC_CORE2_120_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_120_ISR_TID, 120)
#elif (OSEE_TC_CORE2_120_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_120_ISR_HND, 120)
#else
#error Invalid value for OSEE_TC_CORE2_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 120)
OSEE_ISR_ALIGN(_core2_, 2, 120)
#endif /* OSEE_TC_CORE2_120_ISR_CAT */
#if (defined(OSEE_TC_CORE2_121_ISR_CAT))
#if (OSEE_TC_CORE2_121_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_121_ISR_TID, 121)
#elif (OSEE_TC_CORE2_121_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_121_ISR_HND, 121)
#else
#error Invalid value for OSEE_TC_CORE2_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 121)
OSEE_ISR_ALIGN(_core2_, 2, 121)
#endif /* OSEE_TC_CORE2_121_ISR_CAT */
#if (defined(OSEE_TC_CORE2_122_ISR_CAT))
#if (OSEE_TC_CORE2_122_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_122_ISR_TID, 122)
#elif (OSEE_TC_CORE2_122_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_122_ISR_HND, 122)
#else
#error Invalid value for OSEE_TC_CORE2_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 122)
OSEE_ISR_ALIGN(_core2_, 2, 122)
#endif /* OSEE_TC_CORE2_122_ISR_CAT */
#if (defined(OSEE_TC_CORE2_123_ISR_CAT))
#if (OSEE_TC_CORE2_123_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_123_ISR_TID, 123)
#elif (OSEE_TC_CORE2_123_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_123_ISR_HND, 123)
#else
#error Invalid value for OSEE_TC_CORE2_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 123)
OSEE_ISR_ALIGN(_core2_, 2, 123)
#endif /* OSEE_TC_CORE2_123_ISR_CAT */
#if (defined(OSEE_TC_CORE2_124_ISR_CAT))
#if (OSEE_TC_CORE2_124_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_124_ISR_TID, 124)
#elif (OSEE_TC_CORE2_124_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_124_ISR_HND, 124)
#else
#error Invalid value for OSEE_TC_CORE2_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 124)
OSEE_ISR_ALIGN(_core2_, 2, 124)
#endif /* OSEE_TC_CORE2_124_ISR_CAT */
#if (defined(OSEE_TC_CORE2_125_ISR_CAT))
#if (OSEE_TC_CORE2_125_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_125_ISR_TID, 125)
#elif (OSEE_TC_CORE2_125_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_125_ISR_HND, 125)
#else
#error Invalid value for OSEE_TC_CORE2_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 125)
OSEE_ISR_ALIGN(_core2_, 2, 125)
#endif /* OSEE_TC_CORE2_125_ISR_CAT */
#if (defined(OSEE_TC_CORE2_126_ISR_CAT))
#if (OSEE_TC_CORE2_126_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_126_ISR_TID, 126)
#elif (OSEE_TC_CORE2_126_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_126_ISR_HND, 126)
#else
#error Invalid value for OSEE_TC_CORE2_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 126)
OSEE_ISR_ALIGN(_core2_, 2, 126)
#endif /* OSEE_TC_CORE2_126_ISR_CAT */
#if (defined(OSEE_TC_CORE2_127_ISR_CAT))
#if (OSEE_TC_CORE2_127_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_127_ISR_TID, 127)
#elif (OSEE_TC_CORE2_127_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_127_ISR_HND, 127)
#else
#error Invalid value for OSEE_TC_CORE2_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 127)
OSEE_ISR_ALIGN(_core2_, 2, 127)
#endif /* OSEE_TC_CORE2_127_ISR_CAT */
#if (defined(OSEE_TC_CORE2_128_ISR_CAT))
#if (OSEE_TC_CORE2_128_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_128_ISR_TID, 128)
#elif (OSEE_TC_CORE2_128_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_128_ISR_HND, 128)
#else
#error Invalid value for OSEE_TC_CORE2_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 128)
OSEE_ISR_ALIGN(_core2_, 2, 128)
#endif /* OSEE_TC_CORE2_128_ISR_CAT */
#if (defined(OSEE_TC_CORE2_129_ISR_CAT))
#if (OSEE_TC_CORE2_129_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_129_ISR_TID, 129)
#elif (OSEE_TC_CORE2_129_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_129_ISR_HND, 129)
#else
#error Invalid value for OSEE_TC_CORE2_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 129)
OSEE_ISR_ALIGN(_core2_, 2, 129)
#endif /* OSEE_TC_CORE2_129_ISR_CAT */
#if (defined(OSEE_TC_CORE2_130_ISR_CAT))
#if (OSEE_TC_CORE2_130_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_130_ISR_TID, 130)
#elif (OSEE_TC_CORE2_130_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_130_ISR_HND, 130)
#else
#error Invalid value for OSEE_TC_CORE2_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 130)
OSEE_ISR_ALIGN(_core2_, 2, 130)
#endif /* OSEE_TC_CORE2_130_ISR_CAT */
#if (defined(OSEE_TC_CORE2_131_ISR_CAT))
#if (OSEE_TC_CORE2_131_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_131_ISR_TID, 131)
#elif (OSEE_TC_CORE2_131_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_131_ISR_HND, 131)
#else
#error Invalid value for OSEE_TC_CORE2_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 131)
OSEE_ISR_ALIGN(_core2_, 2, 131)
#endif /* OSEE_TC_CORE2_131_ISR_CAT */
#if (defined(OSEE_TC_CORE2_132_ISR_CAT))
#if (OSEE_TC_CORE2_132_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_132_ISR_TID, 132)
#elif (OSEE_TC_CORE2_132_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_132_ISR_HND, 132)
#else
#error Invalid value for OSEE_TC_CORE2_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 132)
OSEE_ISR_ALIGN(_core2_, 2, 132)
#endif /* OSEE_TC_CORE2_132_ISR_CAT */
#if (defined(OSEE_TC_CORE2_133_ISR_CAT))
#if (OSEE_TC_CORE2_133_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_133_ISR_TID, 133)
#elif (OSEE_TC_CORE2_133_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_133_ISR_HND, 133)
#else
#error Invalid value for OSEE_TC_CORE2_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 133)
OSEE_ISR_ALIGN(_core2_, 2, 133)
#endif /* OSEE_TC_CORE2_133_ISR_CAT */
#if (defined(OSEE_TC_CORE2_134_ISR_CAT))
#if (OSEE_TC_CORE2_134_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_134_ISR_TID, 134)
#elif (OSEE_TC_CORE2_134_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_134_ISR_HND, 134)
#else
#error Invalid value for OSEE_TC_CORE2_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 134)
OSEE_ISR_ALIGN(_core2_, 2, 134)
#endif /* OSEE_TC_CORE2_134_ISR_CAT */
#if (defined(OSEE_TC_CORE2_135_ISR_CAT))
#if (OSEE_TC_CORE2_135_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_135_ISR_TID, 135)
#elif (OSEE_TC_CORE2_135_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_135_ISR_HND, 135)
#else
#error Invalid value for OSEE_TC_CORE2_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 135)
OSEE_ISR_ALIGN(_core2_, 2, 135)
#endif /* OSEE_TC_CORE2_135_ISR_CAT */
#if (defined(OSEE_TC_CORE2_136_ISR_CAT))
#if (OSEE_TC_CORE2_136_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_136_ISR_TID, 136)
#elif (OSEE_TC_CORE2_136_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_136_ISR_HND, 136)
#else
#error Invalid value for OSEE_TC_CORE2_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 136)
OSEE_ISR_ALIGN(_core2_, 2, 136)
#endif /* OSEE_TC_CORE2_136_ISR_CAT */
#if (defined(OSEE_TC_CORE2_137_ISR_CAT))
#if (OSEE_TC_CORE2_137_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_137_ISR_TID, 137)
#elif (OSEE_TC_CORE2_137_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_137_ISR_HND, 137)
#else
#error Invalid value for OSEE_TC_CORE2_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 137)
OSEE_ISR_ALIGN(_core2_, 2, 137)
#endif /* OSEE_TC_CORE2_137_ISR_CAT */
#if (defined(OSEE_TC_CORE2_138_ISR_CAT))
#if (OSEE_TC_CORE2_138_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_138_ISR_TID, 138)
#elif (OSEE_TC_CORE2_138_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_138_ISR_HND, 138)
#else
#error Invalid value for OSEE_TC_CORE2_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 138)
OSEE_ISR_ALIGN(_core2_, 2, 138)
#endif /* OSEE_TC_CORE2_138_ISR_CAT */
#if (defined(OSEE_TC_CORE2_139_ISR_CAT))
#if (OSEE_TC_CORE2_139_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_139_ISR_TID, 139)
#elif (OSEE_TC_CORE2_139_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_139_ISR_HND, 139)
#else
#error Invalid value for OSEE_TC_CORE2_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 139)
OSEE_ISR_ALIGN(_core2_, 2, 139)
#endif /* OSEE_TC_CORE2_139_ISR_CAT */
#if (defined(OSEE_TC_CORE2_140_ISR_CAT))
#if (OSEE_TC_CORE2_140_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_140_ISR_TID, 140)
#elif (OSEE_TC_CORE2_140_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_140_ISR_HND, 140)
#else
#error Invalid value for OSEE_TC_CORE2_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 140)
OSEE_ISR_ALIGN(_core2_, 2, 140)
#endif /* OSEE_TC_CORE2_140_ISR_CAT */
#if (defined(OSEE_TC_CORE2_141_ISR_CAT))
#if (OSEE_TC_CORE2_141_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_141_ISR_TID, 141)
#elif (OSEE_TC_CORE2_141_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_141_ISR_HND, 141)
#else
#error Invalid value for OSEE_TC_CORE2_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 141)
OSEE_ISR_ALIGN(_core2_, 2, 141)
#endif /* OSEE_TC_CORE2_141_ISR_CAT */
#if (defined(OSEE_TC_CORE2_142_ISR_CAT))
#if (OSEE_TC_CORE2_142_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_142_ISR_TID, 142)
#elif (OSEE_TC_CORE2_142_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_142_ISR_HND, 142)
#else
#error Invalid value for OSEE_TC_CORE2_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 142)
OSEE_ISR_ALIGN(_core2_, 2, 142)
#endif /* OSEE_TC_CORE2_142_ISR_CAT */
#if (defined(OSEE_TC_CORE2_143_ISR_CAT))
#if (OSEE_TC_CORE2_143_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_143_ISR_TID, 143)
#elif (OSEE_TC_CORE2_143_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_143_ISR_HND, 143)
#else
#error Invalid value for OSEE_TC_CORE2_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 143)
OSEE_ISR_ALIGN(_core2_, 2, 143)
#endif /* OSEE_TC_CORE2_143_ISR_CAT */
#if (defined(OSEE_TC_CORE2_144_ISR_CAT))
#if (OSEE_TC_CORE2_144_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_144_ISR_TID, 144)
#elif (OSEE_TC_CORE2_144_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_144_ISR_HND, 144)
#else
#error Invalid value for OSEE_TC_CORE2_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 144)
OSEE_ISR_ALIGN(_core2_, 2, 144)
#endif /* OSEE_TC_CORE2_144_ISR_CAT */
#if (defined(OSEE_TC_CORE2_145_ISR_CAT))
#if (OSEE_TC_CORE2_145_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_145_ISR_TID, 145)
#elif (OSEE_TC_CORE2_145_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_145_ISR_HND, 145)
#else
#error Invalid value for OSEE_TC_CORE2_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 145)
OSEE_ISR_ALIGN(_core2_, 2, 145)
#endif /* OSEE_TC_CORE2_145_ISR_CAT */
#if (defined(OSEE_TC_CORE2_146_ISR_CAT))
#if (OSEE_TC_CORE2_146_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_146_ISR_TID, 146)
#elif (OSEE_TC_CORE2_146_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_146_ISR_HND, 146)
#else
#error Invalid value for OSEE_TC_CORE2_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 146)
OSEE_ISR_ALIGN(_core2_, 2, 146)
#endif /* OSEE_TC_CORE2_146_ISR_CAT */
#if (defined(OSEE_TC_CORE2_147_ISR_CAT))
#if (OSEE_TC_CORE2_147_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_147_ISR_TID, 147)
#elif (OSEE_TC_CORE2_147_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_147_ISR_HND, 147)
#else
#error Invalid value for OSEE_TC_CORE2_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 147)
OSEE_ISR_ALIGN(_core2_, 2, 147)
#endif /* OSEE_TC_CORE2_147_ISR_CAT */
#if (defined(OSEE_TC_CORE2_148_ISR_CAT))
#if (OSEE_TC_CORE2_148_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_148_ISR_TID, 148)
#elif (OSEE_TC_CORE2_148_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_148_ISR_HND, 148)
#else
#error Invalid value for OSEE_TC_CORE2_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 148)
OSEE_ISR_ALIGN(_core2_, 2, 148)
#endif /* OSEE_TC_CORE2_148_ISR_CAT */
#if (defined(OSEE_TC_CORE2_149_ISR_CAT))
#if (OSEE_TC_CORE2_149_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_149_ISR_TID, 149)
#elif (OSEE_TC_CORE2_149_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_149_ISR_HND, 149)
#else
#error Invalid value for OSEE_TC_CORE2_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 149)
OSEE_ISR_ALIGN(_core2_, 2, 149)
#endif /* OSEE_TC_CORE2_149_ISR_CAT */
#if (defined(OSEE_TC_CORE2_150_ISR_CAT))
#if (OSEE_TC_CORE2_150_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_150_ISR_TID, 150)
#elif (OSEE_TC_CORE2_150_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_150_ISR_HND, 150)
#else
#error Invalid value for OSEE_TC_CORE2_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 150)
OSEE_ISR_ALIGN(_core2_, 2, 150)
#endif /* OSEE_TC_CORE2_150_ISR_CAT */
#if (defined(OSEE_TC_CORE2_151_ISR_CAT))
#if (OSEE_TC_CORE2_151_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_151_ISR_TID, 151)
#elif (OSEE_TC_CORE2_151_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_151_ISR_HND, 151)
#else
#error Invalid value for OSEE_TC_CORE2_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 151)
OSEE_ISR_ALIGN(_core2_, 2, 151)
#endif /* OSEE_TC_CORE2_151_ISR_CAT */
#if (defined(OSEE_TC_CORE2_152_ISR_CAT))
#if (OSEE_TC_CORE2_152_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_152_ISR_TID, 152)
#elif (OSEE_TC_CORE2_152_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_152_ISR_HND, 152)
#else
#error Invalid value for OSEE_TC_CORE2_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 152)
OSEE_ISR_ALIGN(_core2_, 2, 152)
#endif /* OSEE_TC_CORE2_152_ISR_CAT */
#if (defined(OSEE_TC_CORE2_153_ISR_CAT))
#if (OSEE_TC_CORE2_153_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_153_ISR_TID, 153)
#elif (OSEE_TC_CORE2_153_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_153_ISR_HND, 153)
#else
#error Invalid value for OSEE_TC_CORE2_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 153)
OSEE_ISR_ALIGN(_core2_, 2, 153)
#endif /* OSEE_TC_CORE2_153_ISR_CAT */
#if (defined(OSEE_TC_CORE2_154_ISR_CAT))
#if (OSEE_TC_CORE2_154_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_154_ISR_TID, 154)
#elif (OSEE_TC_CORE2_154_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_154_ISR_HND, 154)
#else
#error Invalid value for OSEE_TC_CORE2_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 154)
OSEE_ISR_ALIGN(_core2_, 2, 154)
#endif /* OSEE_TC_CORE2_154_ISR_CAT */
#if (defined(OSEE_TC_CORE2_155_ISR_CAT))
#if (OSEE_TC_CORE2_155_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_155_ISR_TID, 155)
#elif (OSEE_TC_CORE2_155_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_155_ISR_HND, 155)
#else
#error Invalid value for OSEE_TC_CORE2_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 155)
OSEE_ISR_ALIGN(_core2_, 2, 155)
#endif /* OSEE_TC_CORE2_155_ISR_CAT */
#if (defined(OSEE_TC_CORE2_156_ISR_CAT))
#if (OSEE_TC_CORE2_156_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_156_ISR_TID, 156)
#elif (OSEE_TC_CORE2_156_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_156_ISR_HND, 156)
#else
#error Invalid value for OSEE_TC_CORE2_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 156)
OSEE_ISR_ALIGN(_core2_, 2, 156)
#endif /* OSEE_TC_CORE2_156_ISR_CAT */
#if (defined(OSEE_TC_CORE2_157_ISR_CAT))
#if (OSEE_TC_CORE2_157_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_157_ISR_TID, 157)
#elif (OSEE_TC_CORE2_157_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_157_ISR_HND, 157)
#else
#error Invalid value for OSEE_TC_CORE2_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 157)
OSEE_ISR_ALIGN(_core2_, 2, 157)
#endif /* OSEE_TC_CORE2_157_ISR_CAT */
#if (defined(OSEE_TC_CORE2_158_ISR_CAT))
#if (OSEE_TC_CORE2_158_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_158_ISR_TID, 158)
#elif (OSEE_TC_CORE2_158_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_158_ISR_HND, 158)
#else
#error Invalid value for OSEE_TC_CORE2_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 158)
OSEE_ISR_ALIGN(_core2_, 2, 158)
#endif /* OSEE_TC_CORE2_158_ISR_CAT */
#if (defined(OSEE_TC_CORE2_159_ISR_CAT))
#if (OSEE_TC_CORE2_159_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_159_ISR_TID, 159)
#elif (OSEE_TC_CORE2_159_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_159_ISR_HND, 159)
#else
#error Invalid value for OSEE_TC_CORE2_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 159)
OSEE_ISR_ALIGN(_core2_, 2, 159)
#endif /* OSEE_TC_CORE2_159_ISR_CAT */
#if (defined(OSEE_TC_CORE2_160_ISR_CAT))
#if (OSEE_TC_CORE2_160_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_160_ISR_TID, 160)
#elif (OSEE_TC_CORE2_160_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_160_ISR_HND, 160)
#else
#error Invalid value for OSEE_TC_CORE2_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 160)
OSEE_ISR_ALIGN(_core2_, 2, 160)
#endif /* OSEE_TC_CORE2_160_ISR_CAT */
#if (defined(OSEE_TC_CORE2_161_ISR_CAT))
#if (OSEE_TC_CORE2_161_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_161_ISR_TID, 161)
#elif (OSEE_TC_CORE2_161_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_161_ISR_HND, 161)
#else
#error Invalid value for OSEE_TC_CORE2_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 161)
OSEE_ISR_ALIGN(_core2_, 2, 161)
#endif /* OSEE_TC_CORE2_161_ISR_CAT */
#if (defined(OSEE_TC_CORE2_162_ISR_CAT))
#if (OSEE_TC_CORE2_162_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_162_ISR_TID, 162)
#elif (OSEE_TC_CORE2_162_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_162_ISR_HND, 162)
#else
#error Invalid value for OSEE_TC_CORE2_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 162)
OSEE_ISR_ALIGN(_core2_, 2, 162)
#endif /* OSEE_TC_CORE2_162_ISR_CAT */
#if (defined(OSEE_TC_CORE2_163_ISR_CAT))
#if (OSEE_TC_CORE2_163_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_163_ISR_TID, 163)
#elif (OSEE_TC_CORE2_163_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_163_ISR_HND, 163)
#else
#error Invalid value for OSEE_TC_CORE2_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 163)
OSEE_ISR_ALIGN(_core2_, 2, 163)
#endif /* OSEE_TC_CORE2_163_ISR_CAT */
#if (defined(OSEE_TC_CORE2_164_ISR_CAT))
#if (OSEE_TC_CORE2_164_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_164_ISR_TID, 164)
#elif (OSEE_TC_CORE2_164_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_164_ISR_HND, 164)
#else
#error Invalid value for OSEE_TC_CORE2_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 164)
OSEE_ISR_ALIGN(_core2_, 2, 164)
#endif /* OSEE_TC_CORE2_164_ISR_CAT */
#if (defined(OSEE_TC_CORE2_165_ISR_CAT))
#if (OSEE_TC_CORE2_165_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_165_ISR_TID, 165)
#elif (OSEE_TC_CORE2_165_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_165_ISR_HND, 165)
#else
#error Invalid value for OSEE_TC_CORE2_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 165)
OSEE_ISR_ALIGN(_core2_, 2, 165)
#endif /* OSEE_TC_CORE2_165_ISR_CAT */
#if (defined(OSEE_TC_CORE2_166_ISR_CAT))
#if (OSEE_TC_CORE2_166_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_166_ISR_TID, 166)
#elif (OSEE_TC_CORE2_166_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_166_ISR_HND, 166)
#else
#error Invalid value for OSEE_TC_CORE2_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 166)
OSEE_ISR_ALIGN(_core2_, 2, 166)
#endif /* OSEE_TC_CORE2_166_ISR_CAT */
#if (defined(OSEE_TC_CORE2_167_ISR_CAT))
#if (OSEE_TC_CORE2_167_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_167_ISR_TID, 167)
#elif (OSEE_TC_CORE2_167_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_167_ISR_HND, 167)
#else
#error Invalid value for OSEE_TC_CORE2_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 167)
OSEE_ISR_ALIGN(_core2_, 2, 167)
#endif /* OSEE_TC_CORE2_167_ISR_CAT */
#if (defined(OSEE_TC_CORE2_168_ISR_CAT))
#if (OSEE_TC_CORE2_168_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_168_ISR_TID, 168)
#elif (OSEE_TC_CORE2_168_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_168_ISR_HND, 168)
#else
#error Invalid value for OSEE_TC_CORE2_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 168)
OSEE_ISR_ALIGN(_core2_, 2, 168)
#endif /* OSEE_TC_CORE2_168_ISR_CAT */
#if (defined(OSEE_TC_CORE2_169_ISR_CAT))
#if (OSEE_TC_CORE2_169_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_169_ISR_TID, 169)
#elif (OSEE_TC_CORE2_169_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_169_ISR_HND, 169)
#else
#error Invalid value for OSEE_TC_CORE2_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 169)
OSEE_ISR_ALIGN(_core2_, 2, 169)
#endif /* OSEE_TC_CORE2_169_ISR_CAT */
#if (defined(OSEE_TC_CORE2_170_ISR_CAT))
#if (OSEE_TC_CORE2_170_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_170_ISR_TID, 170)
#elif (OSEE_TC_CORE2_170_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_170_ISR_HND, 170)
#else
#error Invalid value for OSEE_TC_CORE2_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 170)
OSEE_ISR_ALIGN(_core2_, 2, 170)
#endif /* OSEE_TC_CORE2_170_ISR_CAT */
#if (defined(OSEE_TC_CORE2_171_ISR_CAT))
#if (OSEE_TC_CORE2_171_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_171_ISR_TID, 171)
#elif (OSEE_TC_CORE2_171_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_171_ISR_HND, 171)
#else
#error Invalid value for OSEE_TC_CORE2_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 171)
OSEE_ISR_ALIGN(_core2_, 2, 171)
#endif /* OSEE_TC_CORE2_171_ISR_CAT */
#if (defined(OSEE_TC_CORE2_172_ISR_CAT))
#if (OSEE_TC_CORE2_172_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_172_ISR_TID, 172)
#elif (OSEE_TC_CORE2_172_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_172_ISR_HND, 172)
#else
#error Invalid value for OSEE_TC_CORE2_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 172)
OSEE_ISR_ALIGN(_core2_, 2, 172)
#endif /* OSEE_TC_CORE2_172_ISR_CAT */
#if (defined(OSEE_TC_CORE2_173_ISR_CAT))
#if (OSEE_TC_CORE2_173_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_173_ISR_TID, 173)
#elif (OSEE_TC_CORE2_173_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_173_ISR_HND, 173)
#else
#error Invalid value for OSEE_TC_CORE2_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 173)
OSEE_ISR_ALIGN(_core2_, 2, 173)
#endif /* OSEE_TC_CORE2_173_ISR_CAT */
#if (defined(OSEE_TC_CORE2_174_ISR_CAT))
#if (OSEE_TC_CORE2_174_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_174_ISR_TID, 174)
#elif (OSEE_TC_CORE2_174_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_174_ISR_HND, 174)
#else
#error Invalid value for OSEE_TC_CORE2_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 174)
OSEE_ISR_ALIGN(_core2_, 2, 174)
#endif /* OSEE_TC_CORE2_174_ISR_CAT */
#if (defined(OSEE_TC_CORE2_175_ISR_CAT))
#if (OSEE_TC_CORE2_175_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_175_ISR_TID, 175)
#elif (OSEE_TC_CORE2_175_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_175_ISR_HND, 175)
#else
#error Invalid value for OSEE_TC_CORE2_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 175)
OSEE_ISR_ALIGN(_core2_, 2, 175)
#endif /* OSEE_TC_CORE2_175_ISR_CAT */
#if (defined(OSEE_TC_CORE2_176_ISR_CAT))
#if (OSEE_TC_CORE2_176_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_176_ISR_TID, 176)
#elif (OSEE_TC_CORE2_176_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_176_ISR_HND, 176)
#else
#error Invalid value for OSEE_TC_CORE2_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 176)
OSEE_ISR_ALIGN(_core2_, 2, 176)
#endif /* OSEE_TC_CORE2_176_ISR_CAT */
#if (defined(OSEE_TC_CORE2_177_ISR_CAT))
#if (OSEE_TC_CORE2_177_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_177_ISR_TID, 177)
#elif (OSEE_TC_CORE2_177_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_177_ISR_HND, 177)
#else
#error Invalid value for OSEE_TC_CORE2_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 177)
OSEE_ISR_ALIGN(_core2_, 2, 177)
#endif /* OSEE_TC_CORE2_177_ISR_CAT */
#if (defined(OSEE_TC_CORE2_178_ISR_CAT))
#if (OSEE_TC_CORE2_178_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_178_ISR_TID, 178)
#elif (OSEE_TC_CORE2_178_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_178_ISR_HND, 178)
#else
#error Invalid value for OSEE_TC_CORE2_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 178)
OSEE_ISR_ALIGN(_core2_, 2, 178)
#endif /* OSEE_TC_CORE2_178_ISR_CAT */
#if (defined(OSEE_TC_CORE2_179_ISR_CAT))
#if (OSEE_TC_CORE2_179_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_179_ISR_TID, 179)
#elif (OSEE_TC_CORE2_179_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_179_ISR_HND, 179)
#else
#error Invalid value for OSEE_TC_CORE2_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 179)
OSEE_ISR_ALIGN(_core2_, 2, 179)
#endif /* OSEE_TC_CORE2_179_ISR_CAT */
#if (defined(OSEE_TC_CORE2_180_ISR_CAT))
#if (OSEE_TC_CORE2_180_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_180_ISR_TID, 180)
#elif (OSEE_TC_CORE2_180_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_180_ISR_HND, 180)
#else
#error Invalid value for OSEE_TC_CORE2_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 180)
OSEE_ISR_ALIGN(_core2_, 2, 180)
#endif /* OSEE_TC_CORE2_180_ISR_CAT */
#if (defined(OSEE_TC_CORE2_181_ISR_CAT))
#if (OSEE_TC_CORE2_181_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_181_ISR_TID, 181)
#elif (OSEE_TC_CORE2_181_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_181_ISR_HND, 181)
#else
#error Invalid value for OSEE_TC_CORE2_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 181)
OSEE_ISR_ALIGN(_core2_, 2, 181)
#endif /* OSEE_TC_CORE2_181_ISR_CAT */
#if (defined(OSEE_TC_CORE2_182_ISR_CAT))
#if (OSEE_TC_CORE2_182_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_182_ISR_TID, 182)
#elif (OSEE_TC_CORE2_182_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_182_ISR_HND, 182)
#else
#error Invalid value for OSEE_TC_CORE2_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 182)
OSEE_ISR_ALIGN(_core2_, 2, 182)
#endif /* OSEE_TC_CORE2_182_ISR_CAT */
#if (defined(OSEE_TC_CORE2_183_ISR_CAT))
#if (OSEE_TC_CORE2_183_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_183_ISR_TID, 183)
#elif (OSEE_TC_CORE2_183_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_183_ISR_HND, 183)
#else
#error Invalid value for OSEE_TC_CORE2_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 183)
OSEE_ISR_ALIGN(_core2_, 2, 183)
#endif /* OSEE_TC_CORE2_183_ISR_CAT */
#if (defined(OSEE_TC_CORE2_184_ISR_CAT))
#if (OSEE_TC_CORE2_184_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_184_ISR_TID, 184)
#elif (OSEE_TC_CORE2_184_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_184_ISR_HND, 184)
#else
#error Invalid value for OSEE_TC_CORE2_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 184)
OSEE_ISR_ALIGN(_core2_, 2, 184)
#endif /* OSEE_TC_CORE2_184_ISR_CAT */
#if (defined(OSEE_TC_CORE2_185_ISR_CAT))
#if (OSEE_TC_CORE2_185_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_185_ISR_TID, 185)
#elif (OSEE_TC_CORE2_185_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_185_ISR_HND, 185)
#else
#error Invalid value for OSEE_TC_CORE2_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 185)
OSEE_ISR_ALIGN(_core2_, 2, 185)
#endif /* OSEE_TC_CORE2_185_ISR_CAT */
#if (defined(OSEE_TC_CORE2_186_ISR_CAT))
#if (OSEE_TC_CORE2_186_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_186_ISR_TID, 186)
#elif (OSEE_TC_CORE2_186_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_186_ISR_HND, 186)
#else
#error Invalid value for OSEE_TC_CORE2_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 186)
OSEE_ISR_ALIGN(_core2_, 2, 186)
#endif /* OSEE_TC_CORE2_186_ISR_CAT */
#if (defined(OSEE_TC_CORE2_187_ISR_CAT))
#if (OSEE_TC_CORE2_187_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_187_ISR_TID, 187)
#elif (OSEE_TC_CORE2_187_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_187_ISR_HND, 187)
#else
#error Invalid value for OSEE_TC_CORE2_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 187)
OSEE_ISR_ALIGN(_core2_, 2, 187)
#endif /* OSEE_TC_CORE2_187_ISR_CAT */
#if (defined(OSEE_TC_CORE2_188_ISR_CAT))
#if (OSEE_TC_CORE2_188_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_188_ISR_TID, 188)
#elif (OSEE_TC_CORE2_188_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_188_ISR_HND, 188)
#else
#error Invalid value for OSEE_TC_CORE2_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 188)
OSEE_ISR_ALIGN(_core2_, 2, 188)
#endif /* OSEE_TC_CORE2_188_ISR_CAT */
#if (defined(OSEE_TC_CORE2_189_ISR_CAT))
#if (OSEE_TC_CORE2_189_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_189_ISR_TID, 189)
#elif (OSEE_TC_CORE2_189_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_189_ISR_HND, 189)
#else
#error Invalid value for OSEE_TC_CORE2_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 189)
OSEE_ISR_ALIGN(_core2_, 2, 189)
#endif /* OSEE_TC_CORE2_189_ISR_CAT */
#if (defined(OSEE_TC_CORE2_190_ISR_CAT))
#if (OSEE_TC_CORE2_190_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_190_ISR_TID, 190)
#elif (OSEE_TC_CORE2_190_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_190_ISR_HND, 190)
#else
#error Invalid value for OSEE_TC_CORE2_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 190)
OSEE_ISR_ALIGN(_core2_, 2, 190)
#endif /* OSEE_TC_CORE2_190_ISR_CAT */
#if (defined(OSEE_TC_CORE2_191_ISR_CAT))
#if (OSEE_TC_CORE2_191_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_191_ISR_TID, 191)
#elif (OSEE_TC_CORE2_191_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_191_ISR_HND, 191)
#else
#error Invalid value for OSEE_TC_CORE2_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 191)
OSEE_ISR_ALIGN(_core2_, 2, 191)
#endif /* OSEE_TC_CORE2_191_ISR_CAT */
#if (defined(OSEE_TC_CORE2_192_ISR_CAT))
#if (OSEE_TC_CORE2_192_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_192_ISR_TID, 192)
#elif (OSEE_TC_CORE2_192_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_192_ISR_HND, 192)
#else
#error Invalid value for OSEE_TC_CORE2_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 192)
OSEE_ISR_ALIGN(_core2_, 2, 192)
#endif /* OSEE_TC_CORE2_192_ISR_CAT */
#if (defined(OSEE_TC_CORE2_193_ISR_CAT))
#if (OSEE_TC_CORE2_193_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_193_ISR_TID, 193)
#elif (OSEE_TC_CORE2_193_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_193_ISR_HND, 193)
#else
#error Invalid value for OSEE_TC_CORE2_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 193)
OSEE_ISR_ALIGN(_core2_, 2, 193)
#endif /* OSEE_TC_CORE2_193_ISR_CAT */
#if (defined(OSEE_TC_CORE2_194_ISR_CAT))
#if (OSEE_TC_CORE2_194_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_194_ISR_TID, 194)
#elif (OSEE_TC_CORE2_194_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_194_ISR_HND, 194)
#else
#error Invalid value for OSEE_TC_CORE2_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 194)
OSEE_ISR_ALIGN(_core2_, 2, 194)
#endif /* OSEE_TC_CORE2_194_ISR_CAT */
#if (defined(OSEE_TC_CORE2_195_ISR_CAT))
#if (OSEE_TC_CORE2_195_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_195_ISR_TID, 195)
#elif (OSEE_TC_CORE2_195_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_195_ISR_HND, 195)
#else
#error Invalid value for OSEE_TC_CORE2_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 195)
OSEE_ISR_ALIGN(_core2_, 2, 195)
#endif /* OSEE_TC_CORE2_195_ISR_CAT */
#if (defined(OSEE_TC_CORE2_196_ISR_CAT))
#if (OSEE_TC_CORE2_196_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_196_ISR_TID, 196)
#elif (OSEE_TC_CORE2_196_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_196_ISR_HND, 196)
#else
#error Invalid value for OSEE_TC_CORE2_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 196)
OSEE_ISR_ALIGN(_core2_, 2, 196)
#endif /* OSEE_TC_CORE2_196_ISR_CAT */
#if (defined(OSEE_TC_CORE2_197_ISR_CAT))
#if (OSEE_TC_CORE2_197_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_197_ISR_TID, 197)
#elif (OSEE_TC_CORE2_197_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_197_ISR_HND, 197)
#else
#error Invalid value for OSEE_TC_CORE2_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 197)
OSEE_ISR_ALIGN(_core2_, 2, 197)
#endif /* OSEE_TC_CORE2_197_ISR_CAT */
#if (defined(OSEE_TC_CORE2_198_ISR_CAT))
#if (OSEE_TC_CORE2_198_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_198_ISR_TID, 198)
#elif (OSEE_TC_CORE2_198_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_198_ISR_HND, 198)
#else
#error Invalid value for OSEE_TC_CORE2_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 198)
OSEE_ISR_ALIGN(_core2_, 2, 198)
#endif /* OSEE_TC_CORE2_198_ISR_CAT */
#if (defined(OSEE_TC_CORE2_199_ISR_CAT))
#if (OSEE_TC_CORE2_199_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_199_ISR_TID, 199)
#elif (OSEE_TC_CORE2_199_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_199_ISR_HND, 199)
#else
#error Invalid value for OSEE_TC_CORE2_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 199)
OSEE_ISR_ALIGN(_core2_, 2, 199)
#endif /* OSEE_TC_CORE2_199_ISR_CAT */
#if (defined(OSEE_TC_CORE2_200_ISR_CAT))
#if (OSEE_TC_CORE2_200_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_200_ISR_TID, 200)
#elif (OSEE_TC_CORE2_200_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_200_ISR_HND, 200)
#else
#error Invalid value for OSEE_TC_CORE2_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 200)
OSEE_ISR_ALIGN(_core2_, 2, 200)
#endif /* OSEE_TC_CORE2_200_ISR_CAT */
#if (defined(OSEE_TC_CORE2_201_ISR_CAT))
#if (OSEE_TC_CORE2_201_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_201_ISR_TID, 201)
#elif (OSEE_TC_CORE2_201_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_201_ISR_HND, 201)
#else
#error Invalid value for OSEE_TC_CORE2_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 201)
OSEE_ISR_ALIGN(_core2_, 2, 201)
#endif /* OSEE_TC_CORE2_201_ISR_CAT */
#if (defined(OSEE_TC_CORE2_202_ISR_CAT))
#if (OSEE_TC_CORE2_202_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_202_ISR_TID, 202)
#elif (OSEE_TC_CORE2_202_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_202_ISR_HND, 202)
#else
#error Invalid value for OSEE_TC_CORE2_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 202)
OSEE_ISR_ALIGN(_core2_, 2, 202)
#endif /* OSEE_TC_CORE2_202_ISR_CAT */
#if (defined(OSEE_TC_CORE2_203_ISR_CAT))
#if (OSEE_TC_CORE2_203_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_203_ISR_TID, 203)
#elif (OSEE_TC_CORE2_203_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_203_ISR_HND, 203)
#else
#error Invalid value for OSEE_TC_CORE2_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 203)
OSEE_ISR_ALIGN(_core2_, 2, 203)
#endif /* OSEE_TC_CORE2_203_ISR_CAT */
#if (defined(OSEE_TC_CORE2_204_ISR_CAT))
#if (OSEE_TC_CORE2_204_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_204_ISR_TID, 204)
#elif (OSEE_TC_CORE2_204_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_204_ISR_HND, 204)
#else
#error Invalid value for OSEE_TC_CORE2_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 204)
OSEE_ISR_ALIGN(_core2_, 2, 204)
#endif /* OSEE_TC_CORE2_204_ISR_CAT */
#if (defined(OSEE_TC_CORE2_205_ISR_CAT))
#if (OSEE_TC_CORE2_205_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_205_ISR_TID, 205)
#elif (OSEE_TC_CORE2_205_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_205_ISR_HND, 205)
#else
#error Invalid value for OSEE_TC_CORE2_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 205)
OSEE_ISR_ALIGN(_core2_, 2, 205)
#endif /* OSEE_TC_CORE2_205_ISR_CAT */
#if (defined(OSEE_TC_CORE2_206_ISR_CAT))
#if (OSEE_TC_CORE2_206_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_206_ISR_TID, 206)
#elif (OSEE_TC_CORE2_206_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_206_ISR_HND, 206)
#else
#error Invalid value for OSEE_TC_CORE2_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 206)
OSEE_ISR_ALIGN(_core2_, 2, 206)
#endif /* OSEE_TC_CORE2_206_ISR_CAT */
#if (defined(OSEE_TC_CORE2_207_ISR_CAT))
#if (OSEE_TC_CORE2_207_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_207_ISR_TID, 207)
#elif (OSEE_TC_CORE2_207_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_207_ISR_HND, 207)
#else
#error Invalid value for OSEE_TC_CORE2_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 207)
OSEE_ISR_ALIGN(_core2_, 2, 207)
#endif /* OSEE_TC_CORE2_207_ISR_CAT */
#if (defined(OSEE_TC_CORE2_208_ISR_CAT))
#if (OSEE_TC_CORE2_208_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_208_ISR_TID, 208)
#elif (OSEE_TC_CORE2_208_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_208_ISR_HND, 208)
#else
#error Invalid value for OSEE_TC_CORE2_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 208)
OSEE_ISR_ALIGN(_core2_, 2, 208)
#endif /* OSEE_TC_CORE2_208_ISR_CAT */
#if (defined(OSEE_TC_CORE2_209_ISR_CAT))
#if (OSEE_TC_CORE2_209_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_209_ISR_TID, 209)
#elif (OSEE_TC_CORE2_209_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_209_ISR_HND, 209)
#else
#error Invalid value for OSEE_TC_CORE2_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 209)
OSEE_ISR_ALIGN(_core2_, 2, 209)
#endif /* OSEE_TC_CORE2_209_ISR_CAT */
#if (defined(OSEE_TC_CORE2_210_ISR_CAT))
#if (OSEE_TC_CORE2_210_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_210_ISR_TID, 210)
#elif (OSEE_TC_CORE2_210_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_210_ISR_HND, 210)
#else
#error Invalid value for OSEE_TC_CORE2_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 210)
OSEE_ISR_ALIGN(_core2_, 2, 210)
#endif /* OSEE_TC_CORE2_210_ISR_CAT */
#if (defined(OSEE_TC_CORE2_211_ISR_CAT))
#if (OSEE_TC_CORE2_211_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_211_ISR_TID, 211)
#elif (OSEE_TC_CORE2_211_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_211_ISR_HND, 211)
#else
#error Invalid value for OSEE_TC_CORE2_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 211)
OSEE_ISR_ALIGN(_core2_, 2, 211)
#endif /* OSEE_TC_CORE2_211_ISR_CAT */
#if (defined(OSEE_TC_CORE2_212_ISR_CAT))
#if (OSEE_TC_CORE2_212_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_212_ISR_TID, 212)
#elif (OSEE_TC_CORE2_212_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_212_ISR_HND, 212)
#else
#error Invalid value for OSEE_TC_CORE2_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 212)
OSEE_ISR_ALIGN(_core2_, 2, 212)
#endif /* OSEE_TC_CORE2_212_ISR_CAT */
#if (defined(OSEE_TC_CORE2_213_ISR_CAT))
#if (OSEE_TC_CORE2_213_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_213_ISR_TID, 213)
#elif (OSEE_TC_CORE2_213_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_213_ISR_HND, 213)
#else
#error Invalid value for OSEE_TC_CORE2_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 213)
OSEE_ISR_ALIGN(_core2_, 2, 213)
#endif /* OSEE_TC_CORE2_213_ISR_CAT */
#if (defined(OSEE_TC_CORE2_214_ISR_CAT))
#if (OSEE_TC_CORE2_214_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_214_ISR_TID, 214)
#elif (OSEE_TC_CORE2_214_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_214_ISR_HND, 214)
#else
#error Invalid value for OSEE_TC_CORE2_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 214)
OSEE_ISR_ALIGN(_core2_, 2, 214)
#endif /* OSEE_TC_CORE2_214_ISR_CAT */
#if (defined(OSEE_TC_CORE2_215_ISR_CAT))
#if (OSEE_TC_CORE2_215_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_215_ISR_TID, 215)
#elif (OSEE_TC_CORE2_215_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_215_ISR_HND, 215)
#else
#error Invalid value for OSEE_TC_CORE2_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 215)
OSEE_ISR_ALIGN(_core2_, 2, 215)
#endif /* OSEE_TC_CORE2_215_ISR_CAT */
#if (defined(OSEE_TC_CORE2_216_ISR_CAT))
#if (OSEE_TC_CORE2_216_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_216_ISR_TID, 216)
#elif (OSEE_TC_CORE2_216_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_216_ISR_HND, 216)
#else
#error Invalid value for OSEE_TC_CORE2_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 216)
OSEE_ISR_ALIGN(_core2_, 2, 216)
#endif /* OSEE_TC_CORE2_216_ISR_CAT */
#if (defined(OSEE_TC_CORE2_217_ISR_CAT))
#if (OSEE_TC_CORE2_217_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_217_ISR_TID, 217)
#elif (OSEE_TC_CORE2_217_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_217_ISR_HND, 217)
#else
#error Invalid value for OSEE_TC_CORE2_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 217)
OSEE_ISR_ALIGN(_core2_, 2, 217)
#endif /* OSEE_TC_CORE2_217_ISR_CAT */
#if (defined(OSEE_TC_CORE2_218_ISR_CAT))
#if (OSEE_TC_CORE2_218_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_218_ISR_TID, 218)
#elif (OSEE_TC_CORE2_218_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_218_ISR_HND, 218)
#else
#error Invalid value for OSEE_TC_CORE2_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 218)
OSEE_ISR_ALIGN(_core2_, 2, 218)
#endif /* OSEE_TC_CORE2_218_ISR_CAT */
#if (defined(OSEE_TC_CORE2_219_ISR_CAT))
#if (OSEE_TC_CORE2_219_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_219_ISR_TID, 219)
#elif (OSEE_TC_CORE2_219_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_219_ISR_HND, 219)
#else
#error Invalid value for OSEE_TC_CORE2_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 219)
OSEE_ISR_ALIGN(_core2_, 2, 219)
#endif /* OSEE_TC_CORE2_219_ISR_CAT */
#if (defined(OSEE_TC_CORE2_220_ISR_CAT))
#if (OSEE_TC_CORE2_220_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_220_ISR_TID, 220)
#elif (OSEE_TC_CORE2_220_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_220_ISR_HND, 220)
#else
#error Invalid value for OSEE_TC_CORE2_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 220)
OSEE_ISR_ALIGN(_core2_, 2, 220)
#endif /* OSEE_TC_CORE2_220_ISR_CAT */
#if (defined(OSEE_TC_CORE2_221_ISR_CAT))
#if (OSEE_TC_CORE2_221_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_221_ISR_TID, 221)
#elif (OSEE_TC_CORE2_221_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_221_ISR_HND, 221)
#else
#error Invalid value for OSEE_TC_CORE2_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 221)
OSEE_ISR_ALIGN(_core2_, 2, 221)
#endif /* OSEE_TC_CORE2_221_ISR_CAT */
#if (defined(OSEE_TC_CORE2_222_ISR_CAT))
#if (OSEE_TC_CORE2_222_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_222_ISR_TID, 222)
#elif (OSEE_TC_CORE2_222_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_222_ISR_HND, 222)
#else
#error Invalid value for OSEE_TC_CORE2_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 222)
OSEE_ISR_ALIGN(_core2_, 2, 222)
#endif /* OSEE_TC_CORE2_222_ISR_CAT */
#if (defined(OSEE_TC_CORE2_223_ISR_CAT))
#if (OSEE_TC_CORE2_223_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_223_ISR_TID, 223)
#elif (OSEE_TC_CORE2_223_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_223_ISR_HND, 223)
#else
#error Invalid value for OSEE_TC_CORE2_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 223)
OSEE_ISR_ALIGN(_core2_, 2, 223)
#endif /* OSEE_TC_CORE2_223_ISR_CAT */
#if (defined(OSEE_TC_CORE2_224_ISR_CAT))
#if (OSEE_TC_CORE2_224_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_224_ISR_TID, 224)
#elif (OSEE_TC_CORE2_224_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_224_ISR_HND, 224)
#else
#error Invalid value for OSEE_TC_CORE2_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 224)
OSEE_ISR_ALIGN(_core2_, 2, 224)
#endif /* OSEE_TC_CORE2_224_ISR_CAT */
#if (defined(OSEE_TC_CORE2_225_ISR_CAT))
#if (OSEE_TC_CORE2_225_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_225_ISR_TID, 225)
#elif (OSEE_TC_CORE2_225_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_225_ISR_HND, 225)
#else
#error Invalid value for OSEE_TC_CORE2_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 225)
OSEE_ISR_ALIGN(_core2_, 2, 225)
#endif /* OSEE_TC_CORE2_225_ISR_CAT */
#if (defined(OSEE_TC_CORE2_226_ISR_CAT))
#if (OSEE_TC_CORE2_226_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_226_ISR_TID, 226)
#elif (OSEE_TC_CORE2_226_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_226_ISR_HND, 226)
#else
#error Invalid value for OSEE_TC_CORE2_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 226)
OSEE_ISR_ALIGN(_core2_, 2, 226)
#endif /* OSEE_TC_CORE2_226_ISR_CAT */
#if (defined(OSEE_TC_CORE2_227_ISR_CAT))
#if (OSEE_TC_CORE2_227_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_227_ISR_TID, 227)
#elif (OSEE_TC_CORE2_227_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_227_ISR_HND, 227)
#else
#error Invalid value for OSEE_TC_CORE2_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 227)
OSEE_ISR_ALIGN(_core2_, 2, 227)
#endif /* OSEE_TC_CORE2_227_ISR_CAT */
#if (defined(OSEE_TC_CORE2_228_ISR_CAT))
#if (OSEE_TC_CORE2_228_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_228_ISR_TID, 228)
#elif (OSEE_TC_CORE2_228_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_228_ISR_HND, 228)
#else
#error Invalid value for OSEE_TC_CORE2_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 228)
OSEE_ISR_ALIGN(_core2_, 2, 228)
#endif /* OSEE_TC_CORE2_228_ISR_CAT */
#if (defined(OSEE_TC_CORE2_229_ISR_CAT))
#if (OSEE_TC_CORE2_229_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_229_ISR_TID, 229)
#elif (OSEE_TC_CORE2_229_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_229_ISR_HND, 229)
#else
#error Invalid value for OSEE_TC_CORE2_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 229)
OSEE_ISR_ALIGN(_core2_, 2, 229)
#endif /* OSEE_TC_CORE2_229_ISR_CAT */
#if (defined(OSEE_TC_CORE2_230_ISR_CAT))
#if (OSEE_TC_CORE2_230_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_230_ISR_TID, 230)
#elif (OSEE_TC_CORE2_230_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_230_ISR_HND, 230)
#else
#error Invalid value for OSEE_TC_CORE2_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 230)
OSEE_ISR_ALIGN(_core2_, 2, 230)
#endif /* OSEE_TC_CORE2_230_ISR_CAT */
#if (defined(OSEE_TC_CORE2_231_ISR_CAT))
#if (OSEE_TC_CORE2_231_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_231_ISR_TID, 231)
#elif (OSEE_TC_CORE2_231_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_231_ISR_HND, 231)
#else
#error Invalid value for OSEE_TC_CORE2_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 231)
OSEE_ISR_ALIGN(_core2_, 2, 231)
#endif /* OSEE_TC_CORE2_231_ISR_CAT */
#if (defined(OSEE_TC_CORE2_232_ISR_CAT))
#if (OSEE_TC_CORE2_232_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_232_ISR_TID, 232)
#elif (OSEE_TC_CORE2_232_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_232_ISR_HND, 232)
#else
#error Invalid value for OSEE_TC_CORE2_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 232)
OSEE_ISR_ALIGN(_core2_, 2, 232)
#endif /* OSEE_TC_CORE2_232_ISR_CAT */
#if (defined(OSEE_TC_CORE2_233_ISR_CAT))
#if (OSEE_TC_CORE2_233_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_233_ISR_TID, 233)
#elif (OSEE_TC_CORE2_233_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_233_ISR_HND, 233)
#else
#error Invalid value for OSEE_TC_CORE2_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 233)
OSEE_ISR_ALIGN(_core2_, 2, 233)
#endif /* OSEE_TC_CORE2_233_ISR_CAT */
#if (defined(OSEE_TC_CORE2_234_ISR_CAT))
#if (OSEE_TC_CORE2_234_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_234_ISR_TID, 234)
#elif (OSEE_TC_CORE2_234_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_234_ISR_HND, 234)
#else
#error Invalid value for OSEE_TC_CORE2_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 234)
OSEE_ISR_ALIGN(_core2_, 2, 234)
#endif /* OSEE_TC_CORE2_234_ISR_CAT */
#if (defined(OSEE_TC_CORE2_235_ISR_CAT))
#if (OSEE_TC_CORE2_235_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_235_ISR_TID, 235)
#elif (OSEE_TC_CORE2_235_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_235_ISR_HND, 235)
#else
#error Invalid value for OSEE_TC_CORE2_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 235)
OSEE_ISR_ALIGN(_core2_, 2, 235)
#endif /* OSEE_TC_CORE2_235_ISR_CAT */
#if (defined(OSEE_TC_CORE2_236_ISR_CAT))
#if (OSEE_TC_CORE2_236_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_236_ISR_TID, 236)
#elif (OSEE_TC_CORE2_236_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_236_ISR_HND, 236)
#else
#error Invalid value for OSEE_TC_CORE2_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 236)
OSEE_ISR_ALIGN(_core2_, 2, 236)
#endif /* OSEE_TC_CORE2_236_ISR_CAT */
#if (defined(OSEE_TC_CORE2_237_ISR_CAT))
#if (OSEE_TC_CORE2_237_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_237_ISR_TID, 237)
#elif (OSEE_TC_CORE2_237_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_237_ISR_HND, 237)
#else
#error Invalid value for OSEE_TC_CORE2_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 237)
OSEE_ISR_ALIGN(_core2_, 2, 237)
#endif /* OSEE_TC_CORE2_237_ISR_CAT */
#if (defined(OSEE_TC_CORE2_238_ISR_CAT))
#if (OSEE_TC_CORE2_238_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_238_ISR_TID, 238)
#elif (OSEE_TC_CORE2_238_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_238_ISR_HND, 238)
#else
#error Invalid value for OSEE_TC_CORE2_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 238)
OSEE_ISR_ALIGN(_core2_, 2, 238)
#endif /* OSEE_TC_CORE2_238_ISR_CAT */
#if (defined(OSEE_TC_CORE2_239_ISR_CAT))
#if (OSEE_TC_CORE2_239_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_239_ISR_TID, 239)
#elif (OSEE_TC_CORE2_239_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_239_ISR_HND, 239)
#else
#error Invalid value for OSEE_TC_CORE2_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 239)
OSEE_ISR_ALIGN(_core2_, 2, 239)
#endif /* OSEE_TC_CORE2_239_ISR_CAT */
#if (defined(OSEE_TC_CORE2_240_ISR_CAT))
#if (OSEE_TC_CORE2_240_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_240_ISR_TID, 240)
#elif (OSEE_TC_CORE2_240_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_240_ISR_HND, 240)
#else
#error Invalid value for OSEE_TC_CORE2_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 240)
OSEE_ISR_ALIGN(_core2_, 2, 240)
#endif /* OSEE_TC_CORE2_240_ISR_CAT */
#if (defined(OSEE_TC_CORE2_241_ISR_CAT))
#if (OSEE_TC_CORE2_241_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_241_ISR_TID, 241)
#elif (OSEE_TC_CORE2_241_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_241_ISR_HND, 241)
#else
#error Invalid value for OSEE_TC_CORE2_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 241)
OSEE_ISR_ALIGN(_core2_, 2, 241)
#endif /* OSEE_TC_CORE2_241_ISR_CAT */
#if (defined(OSEE_TC_CORE2_242_ISR_CAT))
#if (OSEE_TC_CORE2_242_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_242_ISR_TID, 242)
#elif (OSEE_TC_CORE2_242_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_242_ISR_HND, 242)
#else
#error Invalid value for OSEE_TC_CORE2_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 242)
OSEE_ISR_ALIGN(_core2_, 2, 242)
#endif /* OSEE_TC_CORE2_242_ISR_CAT */
#if (defined(OSEE_TC_CORE2_243_ISR_CAT))
#if (OSEE_TC_CORE2_243_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_243_ISR_TID, 243)
#elif (OSEE_TC_CORE2_243_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_243_ISR_HND, 243)
#else
#error Invalid value for OSEE_TC_CORE2_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 243)
OSEE_ISR_ALIGN(_core2_, 2, 243)
#endif /* OSEE_TC_CORE2_243_ISR_CAT */
#if (defined(OSEE_TC_CORE2_244_ISR_CAT))
#if (OSEE_TC_CORE2_244_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_244_ISR_TID, 244)
#elif (OSEE_TC_CORE2_244_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_244_ISR_HND, 244)
#else
#error Invalid value for OSEE_TC_CORE2_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 244)
OSEE_ISR_ALIGN(_core2_, 2, 244)
#endif /* OSEE_TC_CORE2_244_ISR_CAT */
#if (defined(OSEE_TC_CORE2_245_ISR_CAT))
#if (OSEE_TC_CORE2_245_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_245_ISR_TID, 245)
#elif (OSEE_TC_CORE2_245_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_245_ISR_HND, 245)
#else
#error Invalid value for OSEE_TC_CORE2_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 245)
OSEE_ISR_ALIGN(_core2_, 2, 245)
#endif /* OSEE_TC_CORE2_245_ISR_CAT */
#if (defined(OSEE_TC_CORE2_246_ISR_CAT))
#if (OSEE_TC_CORE2_246_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_246_ISR_TID, 246)
#elif (OSEE_TC_CORE2_246_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_246_ISR_HND, 246)
#else
#error Invalid value for OSEE_TC_CORE2_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 246)
OSEE_ISR_ALIGN(_core2_, 2, 246)
#endif /* OSEE_TC_CORE2_246_ISR_CAT */
#if (defined(OSEE_TC_CORE2_247_ISR_CAT))
#if (OSEE_TC_CORE2_247_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_247_ISR_TID, 247)
#elif (OSEE_TC_CORE2_247_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_247_ISR_HND, 247)
#else
#error Invalid value for OSEE_TC_CORE2_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 247)
OSEE_ISR_ALIGN(_core2_, 2, 247)
#endif /* OSEE_TC_CORE2_247_ISR_CAT */
#if (defined(OSEE_TC_CORE2_248_ISR_CAT))
#if (OSEE_TC_CORE2_248_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_248_ISR_TID, 248)
#elif (OSEE_TC_CORE2_248_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_248_ISR_HND, 248)
#else
#error Invalid value for OSEE_TC_CORE2_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 248)
OSEE_ISR_ALIGN(_core2_, 2, 248)
#endif /* OSEE_TC_CORE2_248_ISR_CAT */
#if (defined(OSEE_TC_CORE2_249_ISR_CAT))
#if (OSEE_TC_CORE2_249_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_249_ISR_TID, 249)
#elif (OSEE_TC_CORE2_249_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_249_ISR_HND, 249)
#else
#error Invalid value for OSEE_TC_CORE2_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 249)
OSEE_ISR_ALIGN(_core2_, 2, 249)
#endif /* OSEE_TC_CORE2_249_ISR_CAT */
#if (defined(OSEE_TC_CORE2_250_ISR_CAT))
#if (OSEE_TC_CORE2_250_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_250_ISR_TID, 250)
#elif (OSEE_TC_CORE2_250_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_250_ISR_HND, 250)
#else
#error Invalid value for OSEE_TC_CORE2_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 250)
OSEE_ISR_ALIGN(_core2_, 2, 250)
#endif /* OSEE_TC_CORE2_250_ISR_CAT */
#if (defined(OSEE_TC_CORE2_251_ISR_CAT))
#if (OSEE_TC_CORE2_251_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_251_ISR_TID, 251)
#elif (OSEE_TC_CORE2_251_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_251_ISR_HND, 251)
#else
#error Invalid value for OSEE_TC_CORE2_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 251)
OSEE_ISR_ALIGN(_core2_, 2, 251)
#endif /* OSEE_TC_CORE2_251_ISR_CAT */
#if (defined(OSEE_TC_CORE2_252_ISR_CAT))
#if (OSEE_TC_CORE2_252_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_252_ISR_TID, 252)
#elif (OSEE_TC_CORE2_252_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_252_ISR_HND, 252)
#else
#error Invalid value for OSEE_TC_CORE2_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 252)
OSEE_ISR_ALIGN(_core2_, 2, 252)
#endif /* OSEE_TC_CORE2_252_ISR_CAT */
#if (defined(OSEE_TC_CORE2_253_ISR_CAT))
#if (OSEE_TC_CORE2_253_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_253_ISR_TID, 253)
#elif (OSEE_TC_CORE2_253_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_253_ISR_HND, 253)
#else
#error Invalid value for OSEE_TC_CORE2_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 253)
OSEE_ISR_ALIGN(_core2_, 2, 253)
#endif /* OSEE_TC_CORE2_253_ISR_CAT */
#if (defined(OSEE_TC_CORE2_254_ISR_CAT))
#if (OSEE_TC_CORE2_254_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_254_ISR_TID, 254)
#elif (OSEE_TC_CORE2_254_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_254_ISR_HND, 254)
#else
#error Invalid value for OSEE_TC_CORE2_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 254)
OSEE_ISR_ALIGN(_core2_, 2, 254)
#endif /* OSEE_TC_CORE2_254_ISR_CAT */
#if (defined(OSEE_TC_CORE2_255_ISR_CAT))
#if (OSEE_TC_CORE2_255_ISR_CAT == 2)
OSEE_ISR2_DEF(_core2_, 2, OSEE_TC_CORE2_255_ISR_TID, 255)
#elif (OSEE_TC_CORE2_255_ISR_CAT == 1)
OSEE_ISR1_DEF(_core2_, 2, OSEE_TC_CORE2_255_ISR_HND, 255)
#else
#error Invalid value for OSEE_TC_CORE2_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE2_ISR_MAX_PRIO >= 255)
OSEE_ISR_ALIGN(_core2_, 2, 255)
#endif /* OSEE_TC_CORE2_255_ISR_CAT */
#endif /* OSEE_TC_CORE2_ISR_MAX_PRIO */
#if (defined(__GNUC__))
__asm__ ("\t.size __INTTAB2, . - __INTTAB2\n\
\t.section .text,\"ax\",@progbits");
#endif /* __GNUC__ */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x04U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x08U)
#if (defined(__GNUC__))
__asm__ ("\n\
  .section .inttab_cpu3, \"ax\", @progbits\n\
  .globl __INTTAB3\n\
__INTTAB3:");
/* ERIKA's Interrupt Vector Definition */
#if (defined(OSEE_TC_CORE3_ISR_MAX_PRIO))
__asm__(
"  .skip 0x20");
#endif /* OSEE_TC_CORE3_ISR_MAX_PRIO */
#endif /* __GNUC__ */
#if (defined(OSEE_TC_CORE3_ISR_MAX_PRIO))
OSEE_ISR2_DEF(_core3_, 3, -1, 1)
#if (defined(OSEE_TC_CORE3_2_ISR_CAT))
#if (OSEE_TC_CORE3_2_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_2_ISR_TID, 2)
#elif (OSEE_TC_CORE3_2_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_2_ISR_HND, 2)
#else
#error Invalid value for OSEE_TC_CORE3_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 2)
OSEE_ISR_ALIGN(_core3_, 3, 2)
#endif /* OSEE_TC_CORE3_2_ISR_CAT */
#if (defined(OSEE_TC_CORE3_3_ISR_CAT))
#if (OSEE_TC_CORE3_3_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_3_ISR_TID, 3)
#elif (OSEE_TC_CORE3_3_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_3_ISR_HND, 3)
#else
#error Invalid value for OSEE_TC_CORE3_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 3)
OSEE_ISR_ALIGN(_core3_, 3, 3)
#endif /* OSEE_TC_CORE3_3_ISR_CAT */
#if (defined(OSEE_TC_CORE3_4_ISR_CAT))
#if (OSEE_TC_CORE3_4_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_4_ISR_TID, 4)
#elif (OSEE_TC_CORE3_4_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_4_ISR_HND, 4)
#else
#error Invalid value for OSEE_TC_CORE3_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 4)
OSEE_ISR_ALIGN(_core3_, 3, 4)
#endif /* OSEE_TC_CORE3_4_ISR_CAT */
#if (defined(OSEE_TC_CORE3_5_ISR_CAT))
#if (OSEE_TC_CORE3_5_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_5_ISR_TID, 5)
#elif (OSEE_TC_CORE3_5_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_5_ISR_HND, 5)
#else
#error Invalid value for OSEE_TC_CORE3_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 5)
OSEE_ISR_ALIGN(_core3_, 3, 5)
#endif /* OSEE_TC_CORE3_5_ISR_CAT */
#if (defined(OSEE_TC_CORE3_6_ISR_CAT))
#if (OSEE_TC_CORE3_6_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_6_ISR_TID, 6)
#elif (OSEE_TC_CORE3_6_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_6_ISR_HND, 6)
#else
#error Invalid value for OSEE_TC_CORE3_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 6)
OSEE_ISR_ALIGN(_core3_, 3, 6)
#endif /* OSEE_TC_CORE3_6_ISR_CAT */
#if (defined(OSEE_TC_CORE3_7_ISR_CAT))
#if (OSEE_TC_CORE3_7_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_7_ISR_TID, 7)
#elif (OSEE_TC_CORE3_7_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_7_ISR_HND, 7)
#else
#error Invalid value for OSEE_TC_CORE3_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 7)
OSEE_ISR_ALIGN(_core3_, 3, 7)
#endif /* OSEE_TC_CORE3_7_ISR_CAT */
#if (defined(OSEE_TC_CORE3_8_ISR_CAT))
#if (OSEE_TC_CORE3_8_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_8_ISR_TID, 8)
#elif (OSEE_TC_CORE3_8_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_8_ISR_HND, 8)
#else
#error Invalid value for OSEE_TC_CORE3_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 8)
OSEE_ISR_ALIGN(_core3_, 3, 8)
#endif /* OSEE_TC_CORE3_8_ISR_CAT */
#if (defined(OSEE_TC_CORE3_9_ISR_CAT))
#if (OSEE_TC_CORE3_9_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_9_ISR_TID, 9)
#elif (OSEE_TC_CORE3_9_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_9_ISR_HND, 9)
#else
#error Invalid value for OSEE_TC_CORE3_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 9)
OSEE_ISR_ALIGN(_core3_, 3, 9)
#endif /* OSEE_TC_CORE3_9_ISR_CAT */
#if (defined(OSEE_TC_CORE3_10_ISR_CAT))
#if (OSEE_TC_CORE3_10_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_10_ISR_TID, 10)
#elif (OSEE_TC_CORE3_10_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_10_ISR_HND, 10)
#else
#error Invalid value for OSEE_TC_CORE3_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 10)
OSEE_ISR_ALIGN(_core3_, 3, 10)
#endif /* OSEE_TC_CORE3_10_ISR_CAT */
#if (defined(OSEE_TC_CORE3_11_ISR_CAT))
#if (OSEE_TC_CORE3_11_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_11_ISR_TID, 11)
#elif (OSEE_TC_CORE3_11_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_11_ISR_HND, 11)
#else
#error Invalid value for OSEE_TC_CORE3_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 11)
OSEE_ISR_ALIGN(_core3_, 3, 11)
#endif /* OSEE_TC_CORE3_11_ISR_CAT */
#if (defined(OSEE_TC_CORE3_12_ISR_CAT))
#if (OSEE_TC_CORE3_12_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_12_ISR_TID, 12)
#elif (OSEE_TC_CORE3_12_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_12_ISR_HND, 12)
#else
#error Invalid value for OSEE_TC_CORE3_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 12)
OSEE_ISR_ALIGN(_core3_, 3, 12)
#endif /* OSEE_TC_CORE3_12_ISR_CAT */
#if (defined(OSEE_TC_CORE3_13_ISR_CAT))
#if (OSEE_TC_CORE3_13_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_13_ISR_TID, 13)
#elif (OSEE_TC_CORE3_13_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_13_ISR_HND, 13)
#else
#error Invalid value for OSEE_TC_CORE3_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 13)
OSEE_ISR_ALIGN(_core3_, 3, 13)
#endif /* OSEE_TC_CORE3_13_ISR_CAT */
#if (defined(OSEE_TC_CORE3_14_ISR_CAT))
#if (OSEE_TC_CORE3_14_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_14_ISR_TID, 14)
#elif (OSEE_TC_CORE3_14_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_14_ISR_HND, 14)
#else
#error Invalid value for OSEE_TC_CORE3_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 14)
OSEE_ISR_ALIGN(_core3_, 3, 14)
#endif /* OSEE_TC_CORE3_14_ISR_CAT */
#if (defined(OSEE_TC_CORE3_15_ISR_CAT))
#if (OSEE_TC_CORE3_15_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_15_ISR_TID, 15)
#elif (OSEE_TC_CORE3_15_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_15_ISR_HND, 15)
#else
#error Invalid value for OSEE_TC_CORE3_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 15)
OSEE_ISR_ALIGN(_core3_, 3, 15)
#endif /* OSEE_TC_CORE3_15_ISR_CAT */
#if (defined(OSEE_TC_CORE3_16_ISR_CAT))
#if (OSEE_TC_CORE3_16_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_16_ISR_TID, 16)
#elif (OSEE_TC_CORE3_16_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_16_ISR_HND, 16)
#else
#error Invalid value for OSEE_TC_CORE3_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 16)
OSEE_ISR_ALIGN(_core3_, 3, 16)
#endif /* OSEE_TC_CORE3_16_ISR_CAT */
#if (defined(OSEE_TC_CORE3_17_ISR_CAT))
#if (OSEE_TC_CORE3_17_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_17_ISR_TID, 17)
#elif (OSEE_TC_CORE3_17_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_17_ISR_HND, 17)
#else
#error Invalid value for OSEE_TC_CORE3_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 17)
OSEE_ISR_ALIGN(_core3_, 3, 17)
#endif /* OSEE_TC_CORE3_17_ISR_CAT */
#if (defined(OSEE_TC_CORE3_18_ISR_CAT))
#if (OSEE_TC_CORE3_18_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_18_ISR_TID, 18)
#elif (OSEE_TC_CORE3_18_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_18_ISR_HND, 18)
#else
#error Invalid value for OSEE_TC_CORE3_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 18)
OSEE_ISR_ALIGN(_core3_, 3, 18)
#endif /* OSEE_TC_CORE3_18_ISR_CAT */
#if (defined(OSEE_TC_CORE3_19_ISR_CAT))
#if (OSEE_TC_CORE3_19_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_19_ISR_TID, 19)
#elif (OSEE_TC_CORE3_19_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_19_ISR_HND, 19)
#else
#error Invalid value for OSEE_TC_CORE3_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 19)
OSEE_ISR_ALIGN(_core3_, 3, 19)
#endif /* OSEE_TC_CORE3_19_ISR_CAT */
#if (defined(OSEE_TC_CORE3_20_ISR_CAT))
#if (OSEE_TC_CORE3_20_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_20_ISR_TID, 20)
#elif (OSEE_TC_CORE3_20_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_20_ISR_HND, 20)
#else
#error Invalid value for OSEE_TC_CORE3_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 20)
OSEE_ISR_ALIGN(_core3_, 3, 20)
#endif /* OSEE_TC_CORE3_20_ISR_CAT */
#if (defined(OSEE_TC_CORE3_21_ISR_CAT))
#if (OSEE_TC_CORE3_21_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_21_ISR_TID, 21)
#elif (OSEE_TC_CORE3_21_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_21_ISR_HND, 21)
#else
#error Invalid value for OSEE_TC_CORE3_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 21)
OSEE_ISR_ALIGN(_core3_, 3, 21)
#endif /* OSEE_TC_CORE3_21_ISR_CAT */
#if (defined(OSEE_TC_CORE3_22_ISR_CAT))
#if (OSEE_TC_CORE3_22_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_22_ISR_TID, 22)
#elif (OSEE_TC_CORE3_22_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_22_ISR_HND, 22)
#else
#error Invalid value for OSEE_TC_CORE3_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 22)
OSEE_ISR_ALIGN(_core3_, 3, 22)
#endif /* OSEE_TC_CORE3_22_ISR_CAT */
#if (defined(OSEE_TC_CORE3_23_ISR_CAT))
#if (OSEE_TC_CORE3_23_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_23_ISR_TID, 23)
#elif (OSEE_TC_CORE3_23_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_23_ISR_HND, 23)
#else
#error Invalid value for OSEE_TC_CORE3_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 23)
OSEE_ISR_ALIGN(_core3_, 3, 23)
#endif /* OSEE_TC_CORE3_23_ISR_CAT */
#if (defined(OSEE_TC_CORE3_24_ISR_CAT))
#if (OSEE_TC_CORE3_24_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_24_ISR_TID, 24)
#elif (OSEE_TC_CORE3_24_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_24_ISR_HND, 24)
#else
#error Invalid value for OSEE_TC_CORE3_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 24)
OSEE_ISR_ALIGN(_core3_, 3, 24)
#endif /* OSEE_TC_CORE3_24_ISR_CAT */
#if (defined(OSEE_TC_CORE3_25_ISR_CAT))
#if (OSEE_TC_CORE3_25_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_25_ISR_TID, 25)
#elif (OSEE_TC_CORE3_25_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_25_ISR_HND, 25)
#else
#error Invalid value for OSEE_TC_CORE3_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 25)
OSEE_ISR_ALIGN(_core3_, 3, 25)
#endif /* OSEE_TC_CORE3_25_ISR_CAT */
#if (defined(OSEE_TC_CORE3_26_ISR_CAT))
#if (OSEE_TC_CORE3_26_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_26_ISR_TID, 26)
#elif (OSEE_TC_CORE3_26_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_26_ISR_HND, 26)
#else
#error Invalid value for OSEE_TC_CORE3_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 26)
OSEE_ISR_ALIGN(_core3_, 3, 26)
#endif /* OSEE_TC_CORE3_26_ISR_CAT */
#if (defined(OSEE_TC_CORE3_27_ISR_CAT))
#if (OSEE_TC_CORE3_27_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_27_ISR_TID, 27)
#elif (OSEE_TC_CORE3_27_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_27_ISR_HND, 27)
#else
#error Invalid value for OSEE_TC_CORE3_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 27)
OSEE_ISR_ALIGN(_core3_, 3, 27)
#endif /* OSEE_TC_CORE3_27_ISR_CAT */
#if (defined(OSEE_TC_CORE3_28_ISR_CAT))
#if (OSEE_TC_CORE3_28_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_28_ISR_TID, 28)
#elif (OSEE_TC_CORE3_28_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_28_ISR_HND, 28)
#else
#error Invalid value for OSEE_TC_CORE3_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 28)
OSEE_ISR_ALIGN(_core3_, 3, 28)
#endif /* OSEE_TC_CORE3_28_ISR_CAT */
#if (defined(OSEE_TC_CORE3_29_ISR_CAT))
#if (OSEE_TC_CORE3_29_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_29_ISR_TID, 29)
#elif (OSEE_TC_CORE3_29_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_29_ISR_HND, 29)
#else
#error Invalid value for OSEE_TC_CORE3_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 29)
OSEE_ISR_ALIGN(_core3_, 3, 29)
#endif /* OSEE_TC_CORE3_29_ISR_CAT */
#if (defined(OSEE_TC_CORE3_30_ISR_CAT))
#if (OSEE_TC_CORE3_30_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_30_ISR_TID, 30)
#elif (OSEE_TC_CORE3_30_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_30_ISR_HND, 30)
#else
#error Invalid value for OSEE_TC_CORE3_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 30)
OSEE_ISR_ALIGN(_core3_, 3, 30)
#endif /* OSEE_TC_CORE3_30_ISR_CAT */
#if (defined(OSEE_TC_CORE3_31_ISR_CAT))
#if (OSEE_TC_CORE3_31_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_31_ISR_TID, 31)
#elif (OSEE_TC_CORE3_31_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_31_ISR_HND, 31)
#else
#error Invalid value for OSEE_TC_CORE3_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 31)
OSEE_ISR_ALIGN(_core3_, 3, 31)
#endif /* OSEE_TC_CORE3_31_ISR_CAT */
#if (defined(OSEE_TC_CORE3_32_ISR_CAT))
#if (OSEE_TC_CORE3_32_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_32_ISR_TID, 32)
#elif (OSEE_TC_CORE3_32_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_32_ISR_HND, 32)
#else
#error Invalid value for OSEE_TC_CORE3_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 32)
OSEE_ISR_ALIGN(_core3_, 3, 32)
#endif /* OSEE_TC_CORE3_32_ISR_CAT */
#if (defined(OSEE_TC_CORE3_33_ISR_CAT))
#if (OSEE_TC_CORE3_33_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_33_ISR_TID, 33)
#elif (OSEE_TC_CORE3_33_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_33_ISR_HND, 33)
#else
#error Invalid value for OSEE_TC_CORE3_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 33)
OSEE_ISR_ALIGN(_core3_, 3, 33)
#endif /* OSEE_TC_CORE3_33_ISR_CAT */
#if (defined(OSEE_TC_CORE3_34_ISR_CAT))
#if (OSEE_TC_CORE3_34_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_34_ISR_TID, 34)
#elif (OSEE_TC_CORE3_34_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_34_ISR_HND, 34)
#else
#error Invalid value for OSEE_TC_CORE3_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 34)
OSEE_ISR_ALIGN(_core3_, 3, 34)
#endif /* OSEE_TC_CORE3_34_ISR_CAT */
#if (defined(OSEE_TC_CORE3_35_ISR_CAT))
#if (OSEE_TC_CORE3_35_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_35_ISR_TID, 35)
#elif (OSEE_TC_CORE3_35_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_35_ISR_HND, 35)
#else
#error Invalid value for OSEE_TC_CORE3_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 35)
OSEE_ISR_ALIGN(_core3_, 3, 35)
#endif /* OSEE_TC_CORE3_35_ISR_CAT */
#if (defined(OSEE_TC_CORE3_36_ISR_CAT))
#if (OSEE_TC_CORE3_36_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_36_ISR_TID, 36)
#elif (OSEE_TC_CORE3_36_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_36_ISR_HND, 36)
#else
#error Invalid value for OSEE_TC_CORE3_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 36)
OSEE_ISR_ALIGN(_core3_, 3, 36)
#endif /* OSEE_TC_CORE3_36_ISR_CAT */
#if (defined(OSEE_TC_CORE3_37_ISR_CAT))
#if (OSEE_TC_CORE3_37_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_37_ISR_TID, 37)
#elif (OSEE_TC_CORE3_37_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_37_ISR_HND, 37)
#else
#error Invalid value for OSEE_TC_CORE3_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 37)
OSEE_ISR_ALIGN(_core3_, 3, 37)
#endif /* OSEE_TC_CORE3_37_ISR_CAT */
#if (defined(OSEE_TC_CORE3_38_ISR_CAT))
#if (OSEE_TC_CORE3_38_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_38_ISR_TID, 38)
#elif (OSEE_TC_CORE3_38_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_38_ISR_HND, 38)
#else
#error Invalid value for OSEE_TC_CORE3_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 38)
OSEE_ISR_ALIGN(_core3_, 3, 38)
#endif /* OSEE_TC_CORE3_38_ISR_CAT */
#if (defined(OSEE_TC_CORE3_39_ISR_CAT))
#if (OSEE_TC_CORE3_39_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_39_ISR_TID, 39)
#elif (OSEE_TC_CORE3_39_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_39_ISR_HND, 39)
#else
#error Invalid value for OSEE_TC_CORE3_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 39)
OSEE_ISR_ALIGN(_core3_, 3, 39)
#endif /* OSEE_TC_CORE3_39_ISR_CAT */
#if (defined(OSEE_TC_CORE3_40_ISR_CAT))
#if (OSEE_TC_CORE3_40_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_40_ISR_TID, 40)
#elif (OSEE_TC_CORE3_40_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_40_ISR_HND, 40)
#else
#error Invalid value for OSEE_TC_CORE3_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 40)
OSEE_ISR_ALIGN(_core3_, 3, 40)
#endif /* OSEE_TC_CORE3_40_ISR_CAT */
#if (defined(OSEE_TC_CORE3_41_ISR_CAT))
#if (OSEE_TC_CORE3_41_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_41_ISR_TID, 41)
#elif (OSEE_TC_CORE3_41_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_41_ISR_HND, 41)
#else
#error Invalid value for OSEE_TC_CORE3_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 41)
OSEE_ISR_ALIGN(_core3_, 3, 41)
#endif /* OSEE_TC_CORE3_41_ISR_CAT */
#if (defined(OSEE_TC_CORE3_42_ISR_CAT))
#if (OSEE_TC_CORE3_42_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_42_ISR_TID, 42)
#elif (OSEE_TC_CORE3_42_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_42_ISR_HND, 42)
#else
#error Invalid value for OSEE_TC_CORE3_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 42)
OSEE_ISR_ALIGN(_core3_, 3, 42)
#endif /* OSEE_TC_CORE3_42_ISR_CAT */
#if (defined(OSEE_TC_CORE3_43_ISR_CAT))
#if (OSEE_TC_CORE3_43_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_43_ISR_TID, 43)
#elif (OSEE_TC_CORE3_43_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_43_ISR_HND, 43)
#else
#error Invalid value for OSEE_TC_CORE3_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 43)
OSEE_ISR_ALIGN(_core3_, 3, 43)
#endif /* OSEE_TC_CORE3_43_ISR_CAT */
#if (defined(OSEE_TC_CORE3_44_ISR_CAT))
#if (OSEE_TC_CORE3_44_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_44_ISR_TID, 44)
#elif (OSEE_TC_CORE3_44_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_44_ISR_HND, 44)
#else
#error Invalid value for OSEE_TC_CORE3_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 44)
OSEE_ISR_ALIGN(_core3_, 3, 44)
#endif /* OSEE_TC_CORE3_44_ISR_CAT */
#if (defined(OSEE_TC_CORE3_45_ISR_CAT))
#if (OSEE_TC_CORE3_45_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_45_ISR_TID, 45)
#elif (OSEE_TC_CORE3_45_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_45_ISR_HND, 45)
#else
#error Invalid value for OSEE_TC_CORE3_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 45)
OSEE_ISR_ALIGN(_core3_, 3, 45)
#endif /* OSEE_TC_CORE3_45_ISR_CAT */
#if (defined(OSEE_TC_CORE3_46_ISR_CAT))
#if (OSEE_TC_CORE3_46_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_46_ISR_TID, 46)
#elif (OSEE_TC_CORE3_46_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_46_ISR_HND, 46)
#else
#error Invalid value for OSEE_TC_CORE3_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 46)
OSEE_ISR_ALIGN(_core3_, 3, 46)
#endif /* OSEE_TC_CORE3_46_ISR_CAT */
#if (defined(OSEE_TC_CORE3_47_ISR_CAT))
#if (OSEE_TC_CORE3_47_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_47_ISR_TID, 47)
#elif (OSEE_TC_CORE3_47_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_47_ISR_HND, 47)
#else
#error Invalid value for OSEE_TC_CORE3_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 47)
OSEE_ISR_ALIGN(_core3_, 3, 47)
#endif /* OSEE_TC_CORE3_47_ISR_CAT */
#if (defined(OSEE_TC_CORE3_48_ISR_CAT))
#if (OSEE_TC_CORE3_48_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_48_ISR_TID, 48)
#elif (OSEE_TC_CORE3_48_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_48_ISR_HND, 48)
#else
#error Invalid value for OSEE_TC_CORE3_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 48)
OSEE_ISR_ALIGN(_core3_, 3, 48)
#endif /* OSEE_TC_CORE3_48_ISR_CAT */
#if (defined(OSEE_TC_CORE3_49_ISR_CAT))
#if (OSEE_TC_CORE3_49_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_49_ISR_TID, 49)
#elif (OSEE_TC_CORE3_49_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_49_ISR_HND, 49)
#else
#error Invalid value for OSEE_TC_CORE3_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 49)
OSEE_ISR_ALIGN(_core3_, 3, 49)
#endif /* OSEE_TC_CORE3_49_ISR_CAT */
#if (defined(OSEE_TC_CORE3_50_ISR_CAT))
#if (OSEE_TC_CORE3_50_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_50_ISR_TID, 50)
#elif (OSEE_TC_CORE3_50_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_50_ISR_HND, 50)
#else
#error Invalid value for OSEE_TC_CORE3_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 50)
OSEE_ISR_ALIGN(_core3_, 3, 50)
#endif /* OSEE_TC_CORE3_50_ISR_CAT */
#if (defined(OSEE_TC_CORE3_51_ISR_CAT))
#if (OSEE_TC_CORE3_51_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_51_ISR_TID, 51)
#elif (OSEE_TC_CORE3_51_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_51_ISR_HND, 51)
#else
#error Invalid value for OSEE_TC_CORE3_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 51)
OSEE_ISR_ALIGN(_core3_, 3, 51)
#endif /* OSEE_TC_CORE3_51_ISR_CAT */
#if (defined(OSEE_TC_CORE3_52_ISR_CAT))
#if (OSEE_TC_CORE3_52_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_52_ISR_TID, 52)
#elif (OSEE_TC_CORE3_52_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_52_ISR_HND, 52)
#else
#error Invalid value for OSEE_TC_CORE3_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 52)
OSEE_ISR_ALIGN(_core3_, 3, 52)
#endif /* OSEE_TC_CORE3_52_ISR_CAT */
#if (defined(OSEE_TC_CORE3_53_ISR_CAT))
#if (OSEE_TC_CORE3_53_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_53_ISR_TID, 53)
#elif (OSEE_TC_CORE3_53_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_53_ISR_HND, 53)
#else
#error Invalid value for OSEE_TC_CORE3_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 53)
OSEE_ISR_ALIGN(_core3_, 3, 53)
#endif /* OSEE_TC_CORE3_53_ISR_CAT */
#if (defined(OSEE_TC_CORE3_54_ISR_CAT))
#if (OSEE_TC_CORE3_54_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_54_ISR_TID, 54)
#elif (OSEE_TC_CORE3_54_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_54_ISR_HND, 54)
#else
#error Invalid value for OSEE_TC_CORE3_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 54)
OSEE_ISR_ALIGN(_core3_, 3, 54)
#endif /* OSEE_TC_CORE3_54_ISR_CAT */
#if (defined(OSEE_TC_CORE3_55_ISR_CAT))
#if (OSEE_TC_CORE3_55_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_55_ISR_TID, 55)
#elif (OSEE_TC_CORE3_55_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_55_ISR_HND, 55)
#else
#error Invalid value for OSEE_TC_CORE3_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 55)
OSEE_ISR_ALIGN(_core3_, 3, 55)
#endif /* OSEE_TC_CORE3_55_ISR_CAT */
#if (defined(OSEE_TC_CORE3_56_ISR_CAT))
#if (OSEE_TC_CORE3_56_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_56_ISR_TID, 56)
#elif (OSEE_TC_CORE3_56_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_56_ISR_HND, 56)
#else
#error Invalid value for OSEE_TC_CORE3_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 56)
OSEE_ISR_ALIGN(_core3_, 3, 56)
#endif /* OSEE_TC_CORE3_56_ISR_CAT */
#if (defined(OSEE_TC_CORE3_57_ISR_CAT))
#if (OSEE_TC_CORE3_57_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_57_ISR_TID, 57)
#elif (OSEE_TC_CORE3_57_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_57_ISR_HND, 57)
#else
#error Invalid value for OSEE_TC_CORE3_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 57)
OSEE_ISR_ALIGN(_core3_, 3, 57)
#endif /* OSEE_TC_CORE3_57_ISR_CAT */
#if (defined(OSEE_TC_CORE3_58_ISR_CAT))
#if (OSEE_TC_CORE3_58_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_58_ISR_TID, 58)
#elif (OSEE_TC_CORE3_58_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_58_ISR_HND, 58)
#else
#error Invalid value for OSEE_TC_CORE3_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 58)
OSEE_ISR_ALIGN(_core3_, 3, 58)
#endif /* OSEE_TC_CORE3_58_ISR_CAT */
#if (defined(OSEE_TC_CORE3_59_ISR_CAT))
#if (OSEE_TC_CORE3_59_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_59_ISR_TID, 59)
#elif (OSEE_TC_CORE3_59_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_59_ISR_HND, 59)
#else
#error Invalid value for OSEE_TC_CORE3_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 59)
OSEE_ISR_ALIGN(_core3_, 3, 59)
#endif /* OSEE_TC_CORE3_59_ISR_CAT */
#if (defined(OSEE_TC_CORE3_60_ISR_CAT))
#if (OSEE_TC_CORE3_60_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_60_ISR_TID, 60)
#elif (OSEE_TC_CORE3_60_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_60_ISR_HND, 60)
#else
#error Invalid value for OSEE_TC_CORE3_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 60)
OSEE_ISR_ALIGN(_core3_, 3, 60)
#endif /* OSEE_TC_CORE3_60_ISR_CAT */
#if (defined(OSEE_TC_CORE3_61_ISR_CAT))
#if (OSEE_TC_CORE3_61_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_61_ISR_TID, 61)
#elif (OSEE_TC_CORE3_61_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_61_ISR_HND, 61)
#else
#error Invalid value for OSEE_TC_CORE3_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 61)
OSEE_ISR_ALIGN(_core3_, 3, 61)
#endif /* OSEE_TC_CORE3_61_ISR_CAT */
#if (defined(OSEE_TC_CORE3_62_ISR_CAT))
#if (OSEE_TC_CORE3_62_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_62_ISR_TID, 62)
#elif (OSEE_TC_CORE3_62_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_62_ISR_HND, 62)
#else
#error Invalid value for OSEE_TC_CORE3_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 62)
OSEE_ISR_ALIGN(_core3_, 3, 62)
#endif /* OSEE_TC_CORE3_62_ISR_CAT */
#if (defined(OSEE_TC_CORE3_63_ISR_CAT))
#if (OSEE_TC_CORE3_63_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_63_ISR_TID, 63)
#elif (OSEE_TC_CORE3_63_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_63_ISR_HND, 63)
#else
#error Invalid value for OSEE_TC_CORE3_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 63)
OSEE_ISR_ALIGN(_core3_, 3, 63)
#endif /* OSEE_TC_CORE3_63_ISR_CAT */
#if (defined(OSEE_TC_CORE3_64_ISR_CAT))
#if (OSEE_TC_CORE3_64_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_64_ISR_TID, 64)
#elif (OSEE_TC_CORE3_64_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_64_ISR_HND, 64)
#else
#error Invalid value for OSEE_TC_CORE3_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 64)
OSEE_ISR_ALIGN(_core3_, 3, 64)
#endif /* OSEE_TC_CORE3_64_ISR_CAT */
#if (defined(OSEE_TC_CORE3_65_ISR_CAT))
#if (OSEE_TC_CORE3_65_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_65_ISR_TID, 65)
#elif (OSEE_TC_CORE3_65_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_65_ISR_HND, 65)
#else
#error Invalid value for OSEE_TC_CORE3_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 65)
OSEE_ISR_ALIGN(_core3_, 3, 65)
#endif /* OSEE_TC_CORE3_65_ISR_CAT */
#if (defined(OSEE_TC_CORE3_66_ISR_CAT))
#if (OSEE_TC_CORE3_66_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_66_ISR_TID, 66)
#elif (OSEE_TC_CORE3_66_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_66_ISR_HND, 66)
#else
#error Invalid value for OSEE_TC_CORE3_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 66)
OSEE_ISR_ALIGN(_core3_, 3, 66)
#endif /* OSEE_TC_CORE3_66_ISR_CAT */
#if (defined(OSEE_TC_CORE3_67_ISR_CAT))
#if (OSEE_TC_CORE3_67_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_67_ISR_TID, 67)
#elif (OSEE_TC_CORE3_67_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_67_ISR_HND, 67)
#else
#error Invalid value for OSEE_TC_CORE3_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 67)
OSEE_ISR_ALIGN(_core3_, 3, 67)
#endif /* OSEE_TC_CORE3_67_ISR_CAT */
#if (defined(OSEE_TC_CORE3_68_ISR_CAT))
#if (OSEE_TC_CORE3_68_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_68_ISR_TID, 68)
#elif (OSEE_TC_CORE3_68_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_68_ISR_HND, 68)
#else
#error Invalid value for OSEE_TC_CORE3_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 68)
OSEE_ISR_ALIGN(_core3_, 3, 68)
#endif /* OSEE_TC_CORE3_68_ISR_CAT */
#if (defined(OSEE_TC_CORE3_69_ISR_CAT))
#if (OSEE_TC_CORE3_69_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_69_ISR_TID, 69)
#elif (OSEE_TC_CORE3_69_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_69_ISR_HND, 69)
#else
#error Invalid value for OSEE_TC_CORE3_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 69)
OSEE_ISR_ALIGN(_core3_, 3, 69)
#endif /* OSEE_TC_CORE3_69_ISR_CAT */
#if (defined(OSEE_TC_CORE3_70_ISR_CAT))
#if (OSEE_TC_CORE3_70_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_70_ISR_TID, 70)
#elif (OSEE_TC_CORE3_70_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_70_ISR_HND, 70)
#else
#error Invalid value for OSEE_TC_CORE3_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 70)
OSEE_ISR_ALIGN(_core3_, 3, 70)
#endif /* OSEE_TC_CORE3_70_ISR_CAT */
#if (defined(OSEE_TC_CORE3_71_ISR_CAT))
#if (OSEE_TC_CORE3_71_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_71_ISR_TID, 71)
#elif (OSEE_TC_CORE3_71_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_71_ISR_HND, 71)
#else
#error Invalid value for OSEE_TC_CORE3_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 71)
OSEE_ISR_ALIGN(_core3_, 3, 71)
#endif /* OSEE_TC_CORE3_71_ISR_CAT */
#if (defined(OSEE_TC_CORE3_72_ISR_CAT))
#if (OSEE_TC_CORE3_72_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_72_ISR_TID, 72)
#elif (OSEE_TC_CORE3_72_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_72_ISR_HND, 72)
#else
#error Invalid value for OSEE_TC_CORE3_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 72)
OSEE_ISR_ALIGN(_core3_, 3, 72)
#endif /* OSEE_TC_CORE3_72_ISR_CAT */
#if (defined(OSEE_TC_CORE3_73_ISR_CAT))
#if (OSEE_TC_CORE3_73_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_73_ISR_TID, 73)
#elif (OSEE_TC_CORE3_73_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_73_ISR_HND, 73)
#else
#error Invalid value for OSEE_TC_CORE3_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 73)
OSEE_ISR_ALIGN(_core3_, 3, 73)
#endif /* OSEE_TC_CORE3_73_ISR_CAT */
#if (defined(OSEE_TC_CORE3_74_ISR_CAT))
#if (OSEE_TC_CORE3_74_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_74_ISR_TID, 74)
#elif (OSEE_TC_CORE3_74_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_74_ISR_HND, 74)
#else
#error Invalid value for OSEE_TC_CORE3_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 74)
OSEE_ISR_ALIGN(_core3_, 3, 74)
#endif /* OSEE_TC_CORE3_74_ISR_CAT */
#if (defined(OSEE_TC_CORE3_75_ISR_CAT))
#if (OSEE_TC_CORE3_75_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_75_ISR_TID, 75)
#elif (OSEE_TC_CORE3_75_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_75_ISR_HND, 75)
#else
#error Invalid value for OSEE_TC_CORE3_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 75)
OSEE_ISR_ALIGN(_core3_, 3, 75)
#endif /* OSEE_TC_CORE3_75_ISR_CAT */
#if (defined(OSEE_TC_CORE3_76_ISR_CAT))
#if (OSEE_TC_CORE3_76_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_76_ISR_TID, 76)
#elif (OSEE_TC_CORE3_76_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_76_ISR_HND, 76)
#else
#error Invalid value for OSEE_TC_CORE3_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 76)
OSEE_ISR_ALIGN(_core3_, 3, 76)
#endif /* OSEE_TC_CORE3_76_ISR_CAT */
#if (defined(OSEE_TC_CORE3_77_ISR_CAT))
#if (OSEE_TC_CORE3_77_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_77_ISR_TID, 77)
#elif (OSEE_TC_CORE3_77_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_77_ISR_HND, 77)
#else
#error Invalid value for OSEE_TC_CORE3_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 77)
OSEE_ISR_ALIGN(_core3_, 3, 77)
#endif /* OSEE_TC_CORE3_77_ISR_CAT */
#if (defined(OSEE_TC_CORE3_78_ISR_CAT))
#if (OSEE_TC_CORE3_78_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_78_ISR_TID, 78)
#elif (OSEE_TC_CORE3_78_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_78_ISR_HND, 78)
#else
#error Invalid value for OSEE_TC_CORE3_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 78)
OSEE_ISR_ALIGN(_core3_, 3, 78)
#endif /* OSEE_TC_CORE3_78_ISR_CAT */
#if (defined(OSEE_TC_CORE3_79_ISR_CAT))
#if (OSEE_TC_CORE3_79_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_79_ISR_TID, 79)
#elif (OSEE_TC_CORE3_79_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_79_ISR_HND, 79)
#else
#error Invalid value for OSEE_TC_CORE3_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 79)
OSEE_ISR_ALIGN(_core3_, 3, 79)
#endif /* OSEE_TC_CORE3_79_ISR_CAT */
#if (defined(OSEE_TC_CORE3_80_ISR_CAT))
#if (OSEE_TC_CORE3_80_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_80_ISR_TID, 80)
#elif (OSEE_TC_CORE3_80_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_80_ISR_HND, 80)
#else
#error Invalid value for OSEE_TC_CORE3_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 80)
OSEE_ISR_ALIGN(_core3_, 3, 80)
#endif /* OSEE_TC_CORE3_80_ISR_CAT */
#if (defined(OSEE_TC_CORE3_81_ISR_CAT))
#if (OSEE_TC_CORE3_81_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_81_ISR_TID, 81)
#elif (OSEE_TC_CORE3_81_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_81_ISR_HND, 81)
#else
#error Invalid value for OSEE_TC_CORE3_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 81)
OSEE_ISR_ALIGN(_core3_, 3, 81)
#endif /* OSEE_TC_CORE3_81_ISR_CAT */
#if (defined(OSEE_TC_CORE3_82_ISR_CAT))
#if (OSEE_TC_CORE3_82_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_82_ISR_TID, 82)
#elif (OSEE_TC_CORE3_82_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_82_ISR_HND, 82)
#else
#error Invalid value for OSEE_TC_CORE3_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 82)
OSEE_ISR_ALIGN(_core3_, 3, 82)
#endif /* OSEE_TC_CORE3_82_ISR_CAT */
#if (defined(OSEE_TC_CORE3_83_ISR_CAT))
#if (OSEE_TC_CORE3_83_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_83_ISR_TID, 83)
#elif (OSEE_TC_CORE3_83_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_83_ISR_HND, 83)
#else
#error Invalid value for OSEE_TC_CORE3_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 83)
OSEE_ISR_ALIGN(_core3_, 3, 83)
#endif /* OSEE_TC_CORE3_83_ISR_CAT */
#if (defined(OSEE_TC_CORE3_84_ISR_CAT))
#if (OSEE_TC_CORE3_84_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_84_ISR_TID, 84)
#elif (OSEE_TC_CORE3_84_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_84_ISR_HND, 84)
#else
#error Invalid value for OSEE_TC_CORE3_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 84)
OSEE_ISR_ALIGN(_core3_, 3, 84)
#endif /* OSEE_TC_CORE3_84_ISR_CAT */
#if (defined(OSEE_TC_CORE3_85_ISR_CAT))
#if (OSEE_TC_CORE3_85_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_85_ISR_TID, 85)
#elif (OSEE_TC_CORE3_85_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_85_ISR_HND, 85)
#else
#error Invalid value for OSEE_TC_CORE3_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 85)
OSEE_ISR_ALIGN(_core3_, 3, 85)
#endif /* OSEE_TC_CORE3_85_ISR_CAT */
#if (defined(OSEE_TC_CORE3_86_ISR_CAT))
#if (OSEE_TC_CORE3_86_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_86_ISR_TID, 86)
#elif (OSEE_TC_CORE3_86_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_86_ISR_HND, 86)
#else
#error Invalid value for OSEE_TC_CORE3_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 86)
OSEE_ISR_ALIGN(_core3_, 3, 86)
#endif /* OSEE_TC_CORE3_86_ISR_CAT */
#if (defined(OSEE_TC_CORE3_87_ISR_CAT))
#if (OSEE_TC_CORE3_87_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_87_ISR_TID, 87)
#elif (OSEE_TC_CORE3_87_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_87_ISR_HND, 87)
#else
#error Invalid value for OSEE_TC_CORE3_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 87)
OSEE_ISR_ALIGN(_core3_, 3, 87)
#endif /* OSEE_TC_CORE3_87_ISR_CAT */
#if (defined(OSEE_TC_CORE3_88_ISR_CAT))
#if (OSEE_TC_CORE3_88_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_88_ISR_TID, 88)
#elif (OSEE_TC_CORE3_88_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_88_ISR_HND, 88)
#else
#error Invalid value for OSEE_TC_CORE3_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 88)
OSEE_ISR_ALIGN(_core3_, 3, 88)
#endif /* OSEE_TC_CORE3_88_ISR_CAT */
#if (defined(OSEE_TC_CORE3_89_ISR_CAT))
#if (OSEE_TC_CORE3_89_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_89_ISR_TID, 89)
#elif (OSEE_TC_CORE3_89_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_89_ISR_HND, 89)
#else
#error Invalid value for OSEE_TC_CORE3_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 89)
OSEE_ISR_ALIGN(_core3_, 3, 89)
#endif /* OSEE_TC_CORE3_89_ISR_CAT */
#if (defined(OSEE_TC_CORE3_90_ISR_CAT))
#if (OSEE_TC_CORE3_90_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_90_ISR_TID, 90)
#elif (OSEE_TC_CORE3_90_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_90_ISR_HND, 90)
#else
#error Invalid value for OSEE_TC_CORE3_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 90)
OSEE_ISR_ALIGN(_core3_, 3, 90)
#endif /* OSEE_TC_CORE3_90_ISR_CAT */
#if (defined(OSEE_TC_CORE3_91_ISR_CAT))
#if (OSEE_TC_CORE3_91_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_91_ISR_TID, 91)
#elif (OSEE_TC_CORE3_91_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_91_ISR_HND, 91)
#else
#error Invalid value for OSEE_TC_CORE3_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 91)
OSEE_ISR_ALIGN(_core3_, 3, 91)
#endif /* OSEE_TC_CORE3_91_ISR_CAT */
#if (defined(OSEE_TC_CORE3_92_ISR_CAT))
#if (OSEE_TC_CORE3_92_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_92_ISR_TID, 92)
#elif (OSEE_TC_CORE3_92_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_92_ISR_HND, 92)
#else
#error Invalid value for OSEE_TC_CORE3_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 92)
OSEE_ISR_ALIGN(_core3_, 3, 92)
#endif /* OSEE_TC_CORE3_92_ISR_CAT */
#if (defined(OSEE_TC_CORE3_93_ISR_CAT))
#if (OSEE_TC_CORE3_93_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_93_ISR_TID, 93)
#elif (OSEE_TC_CORE3_93_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_93_ISR_HND, 93)
#else
#error Invalid value for OSEE_TC_CORE3_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 93)
OSEE_ISR_ALIGN(_core3_, 3, 93)
#endif /* OSEE_TC_CORE3_93_ISR_CAT */
#if (defined(OSEE_TC_CORE3_94_ISR_CAT))
#if (OSEE_TC_CORE3_94_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_94_ISR_TID, 94)
#elif (OSEE_TC_CORE3_94_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_94_ISR_HND, 94)
#else
#error Invalid value for OSEE_TC_CORE3_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 94)
OSEE_ISR_ALIGN(_core3_, 3, 94)
#endif /* OSEE_TC_CORE3_94_ISR_CAT */
#if (defined(OSEE_TC_CORE3_95_ISR_CAT))
#if (OSEE_TC_CORE3_95_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_95_ISR_TID, 95)
#elif (OSEE_TC_CORE3_95_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_95_ISR_HND, 95)
#else
#error Invalid value for OSEE_TC_CORE3_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 95)
OSEE_ISR_ALIGN(_core3_, 3, 95)
#endif /* OSEE_TC_CORE3_95_ISR_CAT */
#if (defined(OSEE_TC_CORE3_96_ISR_CAT))
#if (OSEE_TC_CORE3_96_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_96_ISR_TID, 96)
#elif (OSEE_TC_CORE3_96_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_96_ISR_HND, 96)
#else
#error Invalid value for OSEE_TC_CORE3_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 96)
OSEE_ISR_ALIGN(_core3_, 3, 96)
#endif /* OSEE_TC_CORE3_96_ISR_CAT */
#if (defined(OSEE_TC_CORE3_97_ISR_CAT))
#if (OSEE_TC_CORE3_97_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_97_ISR_TID, 97)
#elif (OSEE_TC_CORE3_97_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_97_ISR_HND, 97)
#else
#error Invalid value for OSEE_TC_CORE3_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 97)
OSEE_ISR_ALIGN(_core3_, 3, 97)
#endif /* OSEE_TC_CORE3_97_ISR_CAT */
#if (defined(OSEE_TC_CORE3_98_ISR_CAT))
#if (OSEE_TC_CORE3_98_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_98_ISR_TID, 98)
#elif (OSEE_TC_CORE3_98_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_98_ISR_HND, 98)
#else
#error Invalid value for OSEE_TC_CORE3_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 98)
OSEE_ISR_ALIGN(_core3_, 3, 98)
#endif /* OSEE_TC_CORE3_98_ISR_CAT */
#if (defined(OSEE_TC_CORE3_99_ISR_CAT))
#if (OSEE_TC_CORE3_99_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_99_ISR_TID, 99)
#elif (OSEE_TC_CORE3_99_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_99_ISR_HND, 99)
#else
#error Invalid value for OSEE_TC_CORE3_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 99)
OSEE_ISR_ALIGN(_core3_, 3, 99)
#endif /* OSEE_TC_CORE3_99_ISR_CAT */
#if (defined(OSEE_TC_CORE3_100_ISR_CAT))
#if (OSEE_TC_CORE3_100_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_100_ISR_TID, 100)
#elif (OSEE_TC_CORE3_100_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_100_ISR_HND, 100)
#else
#error Invalid value for OSEE_TC_CORE3_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 100)
OSEE_ISR_ALIGN(_core3_, 3, 100)
#endif /* OSEE_TC_CORE3_100_ISR_CAT */
#if (defined(OSEE_TC_CORE3_101_ISR_CAT))
#if (OSEE_TC_CORE3_101_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_101_ISR_TID, 101)
#elif (OSEE_TC_CORE3_101_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_101_ISR_HND, 101)
#else
#error Invalid value for OSEE_TC_CORE3_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 101)
OSEE_ISR_ALIGN(_core3_, 3, 101)
#endif /* OSEE_TC_CORE3_101_ISR_CAT */
#if (defined(OSEE_TC_CORE3_102_ISR_CAT))
#if (OSEE_TC_CORE3_102_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_102_ISR_TID, 102)
#elif (OSEE_TC_CORE3_102_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_102_ISR_HND, 102)
#else
#error Invalid value for OSEE_TC_CORE3_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 102)
OSEE_ISR_ALIGN(_core3_, 3, 102)
#endif /* OSEE_TC_CORE3_102_ISR_CAT */
#if (defined(OSEE_TC_CORE3_103_ISR_CAT))
#if (OSEE_TC_CORE3_103_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_103_ISR_TID, 103)
#elif (OSEE_TC_CORE3_103_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_103_ISR_HND, 103)
#else
#error Invalid value for OSEE_TC_CORE3_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 103)
OSEE_ISR_ALIGN(_core3_, 3, 103)
#endif /* OSEE_TC_CORE3_103_ISR_CAT */
#if (defined(OSEE_TC_CORE3_104_ISR_CAT))
#if (OSEE_TC_CORE3_104_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_104_ISR_TID, 104)
#elif (OSEE_TC_CORE3_104_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_104_ISR_HND, 104)
#else
#error Invalid value for OSEE_TC_CORE3_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 104)
OSEE_ISR_ALIGN(_core3_, 3, 104)
#endif /* OSEE_TC_CORE3_104_ISR_CAT */
#if (defined(OSEE_TC_CORE3_105_ISR_CAT))
#if (OSEE_TC_CORE3_105_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_105_ISR_TID, 105)
#elif (OSEE_TC_CORE3_105_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_105_ISR_HND, 105)
#else
#error Invalid value for OSEE_TC_CORE3_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 105)
OSEE_ISR_ALIGN(_core3_, 3, 105)
#endif /* OSEE_TC_CORE3_105_ISR_CAT */
#if (defined(OSEE_TC_CORE3_106_ISR_CAT))
#if (OSEE_TC_CORE3_106_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_106_ISR_TID, 106)
#elif (OSEE_TC_CORE3_106_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_106_ISR_HND, 106)
#else
#error Invalid value for OSEE_TC_CORE3_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 106)
OSEE_ISR_ALIGN(_core3_, 3, 106)
#endif /* OSEE_TC_CORE3_106_ISR_CAT */
#if (defined(OSEE_TC_CORE3_107_ISR_CAT))
#if (OSEE_TC_CORE3_107_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_107_ISR_TID, 107)
#elif (OSEE_TC_CORE3_107_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_107_ISR_HND, 107)
#else
#error Invalid value for OSEE_TC_CORE3_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 107)
OSEE_ISR_ALIGN(_core3_, 3, 107)
#endif /* OSEE_TC_CORE3_107_ISR_CAT */
#if (defined(OSEE_TC_CORE3_108_ISR_CAT))
#if (OSEE_TC_CORE3_108_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_108_ISR_TID, 108)
#elif (OSEE_TC_CORE3_108_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_108_ISR_HND, 108)
#else
#error Invalid value for OSEE_TC_CORE3_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 108)
OSEE_ISR_ALIGN(_core3_, 3, 108)
#endif /* OSEE_TC_CORE3_108_ISR_CAT */
#if (defined(OSEE_TC_CORE3_109_ISR_CAT))
#if (OSEE_TC_CORE3_109_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_109_ISR_TID, 109)
#elif (OSEE_TC_CORE3_109_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_109_ISR_HND, 109)
#else
#error Invalid value for OSEE_TC_CORE3_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 109)
OSEE_ISR_ALIGN(_core3_, 3, 109)
#endif /* OSEE_TC_CORE3_109_ISR_CAT */
#if (defined(OSEE_TC_CORE3_110_ISR_CAT))
#if (OSEE_TC_CORE3_110_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_110_ISR_TID, 110)
#elif (OSEE_TC_CORE3_110_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_110_ISR_HND, 110)
#else
#error Invalid value for OSEE_TC_CORE3_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 110)
OSEE_ISR_ALIGN(_core3_, 3, 110)
#endif /* OSEE_TC_CORE3_110_ISR_CAT */
#if (defined(OSEE_TC_CORE3_111_ISR_CAT))
#if (OSEE_TC_CORE3_111_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_111_ISR_TID, 111)
#elif (OSEE_TC_CORE3_111_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_111_ISR_HND, 111)
#else
#error Invalid value for OSEE_TC_CORE3_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 111)
OSEE_ISR_ALIGN(_core3_, 3, 111)
#endif /* OSEE_TC_CORE3_111_ISR_CAT */
#if (defined(OSEE_TC_CORE3_112_ISR_CAT))
#if (OSEE_TC_CORE3_112_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_112_ISR_TID, 112)
#elif (OSEE_TC_CORE3_112_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_112_ISR_HND, 112)
#else
#error Invalid value for OSEE_TC_CORE3_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 112)
OSEE_ISR_ALIGN(_core3_, 3, 112)
#endif /* OSEE_TC_CORE3_112_ISR_CAT */
#if (defined(OSEE_TC_CORE3_113_ISR_CAT))
#if (OSEE_TC_CORE3_113_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_113_ISR_TID, 113)
#elif (OSEE_TC_CORE3_113_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_113_ISR_HND, 113)
#else
#error Invalid value for OSEE_TC_CORE3_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 113)
OSEE_ISR_ALIGN(_core3_, 3, 113)
#endif /* OSEE_TC_CORE3_113_ISR_CAT */
#if (defined(OSEE_TC_CORE3_114_ISR_CAT))
#if (OSEE_TC_CORE3_114_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_114_ISR_TID, 114)
#elif (OSEE_TC_CORE3_114_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_114_ISR_HND, 114)
#else
#error Invalid value for OSEE_TC_CORE3_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 114)
OSEE_ISR_ALIGN(_core3_, 3, 114)
#endif /* OSEE_TC_CORE3_114_ISR_CAT */
#if (defined(OSEE_TC_CORE3_115_ISR_CAT))
#if (OSEE_TC_CORE3_115_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_115_ISR_TID, 115)
#elif (OSEE_TC_CORE3_115_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_115_ISR_HND, 115)
#else
#error Invalid value for OSEE_TC_CORE3_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 115)
OSEE_ISR_ALIGN(_core3_, 3, 115)
#endif /* OSEE_TC_CORE3_115_ISR_CAT */
#if (defined(OSEE_TC_CORE3_116_ISR_CAT))
#if (OSEE_TC_CORE3_116_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_116_ISR_TID, 116)
#elif (OSEE_TC_CORE3_116_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_116_ISR_HND, 116)
#else
#error Invalid value for OSEE_TC_CORE3_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 116)
OSEE_ISR_ALIGN(_core3_, 3, 116)
#endif /* OSEE_TC_CORE3_116_ISR_CAT */
#if (defined(OSEE_TC_CORE3_117_ISR_CAT))
#if (OSEE_TC_CORE3_117_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_117_ISR_TID, 117)
#elif (OSEE_TC_CORE3_117_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_117_ISR_HND, 117)
#else
#error Invalid value for OSEE_TC_CORE3_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 117)
OSEE_ISR_ALIGN(_core3_, 3, 117)
#endif /* OSEE_TC_CORE3_117_ISR_CAT */
#if (defined(OSEE_TC_CORE3_118_ISR_CAT))
#if (OSEE_TC_CORE3_118_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_118_ISR_TID, 118)
#elif (OSEE_TC_CORE3_118_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_118_ISR_HND, 118)
#else
#error Invalid value for OSEE_TC_CORE3_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 118)
OSEE_ISR_ALIGN(_core3_, 3, 118)
#endif /* OSEE_TC_CORE3_118_ISR_CAT */
#if (defined(OSEE_TC_CORE3_119_ISR_CAT))
#if (OSEE_TC_CORE3_119_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_119_ISR_TID, 119)
#elif (OSEE_TC_CORE3_119_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_119_ISR_HND, 119)
#else
#error Invalid value for OSEE_TC_CORE3_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 119)
OSEE_ISR_ALIGN(_core3_, 3, 119)
#endif /* OSEE_TC_CORE3_119_ISR_CAT */
#if (defined(OSEE_TC_CORE3_120_ISR_CAT))
#if (OSEE_TC_CORE3_120_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_120_ISR_TID, 120)
#elif (OSEE_TC_CORE3_120_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_120_ISR_HND, 120)
#else
#error Invalid value for OSEE_TC_CORE3_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 120)
OSEE_ISR_ALIGN(_core3_, 3, 120)
#endif /* OSEE_TC_CORE3_120_ISR_CAT */
#if (defined(OSEE_TC_CORE3_121_ISR_CAT))
#if (OSEE_TC_CORE3_121_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_121_ISR_TID, 121)
#elif (OSEE_TC_CORE3_121_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_121_ISR_HND, 121)
#else
#error Invalid value for OSEE_TC_CORE3_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 121)
OSEE_ISR_ALIGN(_core3_, 3, 121)
#endif /* OSEE_TC_CORE3_121_ISR_CAT */
#if (defined(OSEE_TC_CORE3_122_ISR_CAT))
#if (OSEE_TC_CORE3_122_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_122_ISR_TID, 122)
#elif (OSEE_TC_CORE3_122_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_122_ISR_HND, 122)
#else
#error Invalid value for OSEE_TC_CORE3_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 122)
OSEE_ISR_ALIGN(_core3_, 3, 122)
#endif /* OSEE_TC_CORE3_122_ISR_CAT */
#if (defined(OSEE_TC_CORE3_123_ISR_CAT))
#if (OSEE_TC_CORE3_123_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_123_ISR_TID, 123)
#elif (OSEE_TC_CORE3_123_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_123_ISR_HND, 123)
#else
#error Invalid value for OSEE_TC_CORE3_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 123)
OSEE_ISR_ALIGN(_core3_, 3, 123)
#endif /* OSEE_TC_CORE3_123_ISR_CAT */
#if (defined(OSEE_TC_CORE3_124_ISR_CAT))
#if (OSEE_TC_CORE3_124_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_124_ISR_TID, 124)
#elif (OSEE_TC_CORE3_124_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_124_ISR_HND, 124)
#else
#error Invalid value for OSEE_TC_CORE3_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 124)
OSEE_ISR_ALIGN(_core3_, 3, 124)
#endif /* OSEE_TC_CORE3_124_ISR_CAT */
#if (defined(OSEE_TC_CORE3_125_ISR_CAT))
#if (OSEE_TC_CORE3_125_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_125_ISR_TID, 125)
#elif (OSEE_TC_CORE3_125_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_125_ISR_HND, 125)
#else
#error Invalid value for OSEE_TC_CORE3_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 125)
OSEE_ISR_ALIGN(_core3_, 3, 125)
#endif /* OSEE_TC_CORE3_125_ISR_CAT */
#if (defined(OSEE_TC_CORE3_126_ISR_CAT))
#if (OSEE_TC_CORE3_126_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_126_ISR_TID, 126)
#elif (OSEE_TC_CORE3_126_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_126_ISR_HND, 126)
#else
#error Invalid value for OSEE_TC_CORE3_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 126)
OSEE_ISR_ALIGN(_core3_, 3, 126)
#endif /* OSEE_TC_CORE3_126_ISR_CAT */
#if (defined(OSEE_TC_CORE3_127_ISR_CAT))
#if (OSEE_TC_CORE3_127_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_127_ISR_TID, 127)
#elif (OSEE_TC_CORE3_127_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_127_ISR_HND, 127)
#else
#error Invalid value for OSEE_TC_CORE3_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 127)
OSEE_ISR_ALIGN(_core3_, 3, 127)
#endif /* OSEE_TC_CORE3_127_ISR_CAT */
#if (defined(OSEE_TC_CORE3_128_ISR_CAT))
#if (OSEE_TC_CORE3_128_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_128_ISR_TID, 128)
#elif (OSEE_TC_CORE3_128_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_128_ISR_HND, 128)
#else
#error Invalid value for OSEE_TC_CORE3_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 128)
OSEE_ISR_ALIGN(_core3_, 3, 128)
#endif /* OSEE_TC_CORE3_128_ISR_CAT */
#if (defined(OSEE_TC_CORE3_129_ISR_CAT))
#if (OSEE_TC_CORE3_129_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_129_ISR_TID, 129)
#elif (OSEE_TC_CORE3_129_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_129_ISR_HND, 129)
#else
#error Invalid value for OSEE_TC_CORE3_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 129)
OSEE_ISR_ALIGN(_core3_, 3, 129)
#endif /* OSEE_TC_CORE3_129_ISR_CAT */
#if (defined(OSEE_TC_CORE3_130_ISR_CAT))
#if (OSEE_TC_CORE3_130_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_130_ISR_TID, 130)
#elif (OSEE_TC_CORE3_130_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_130_ISR_HND, 130)
#else
#error Invalid value for OSEE_TC_CORE3_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 130)
OSEE_ISR_ALIGN(_core3_, 3, 130)
#endif /* OSEE_TC_CORE3_130_ISR_CAT */
#if (defined(OSEE_TC_CORE3_131_ISR_CAT))
#if (OSEE_TC_CORE3_131_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_131_ISR_TID, 131)
#elif (OSEE_TC_CORE3_131_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_131_ISR_HND, 131)
#else
#error Invalid value for OSEE_TC_CORE3_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 131)
OSEE_ISR_ALIGN(_core3_, 3, 131)
#endif /* OSEE_TC_CORE3_131_ISR_CAT */
#if (defined(OSEE_TC_CORE3_132_ISR_CAT))
#if (OSEE_TC_CORE3_132_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_132_ISR_TID, 132)
#elif (OSEE_TC_CORE3_132_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_132_ISR_HND, 132)
#else
#error Invalid value for OSEE_TC_CORE3_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 132)
OSEE_ISR_ALIGN(_core3_, 3, 132)
#endif /* OSEE_TC_CORE3_132_ISR_CAT */
#if (defined(OSEE_TC_CORE3_133_ISR_CAT))
#if (OSEE_TC_CORE3_133_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_133_ISR_TID, 133)
#elif (OSEE_TC_CORE3_133_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_133_ISR_HND, 133)
#else
#error Invalid value for OSEE_TC_CORE3_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 133)
OSEE_ISR_ALIGN(_core3_, 3, 133)
#endif /* OSEE_TC_CORE3_133_ISR_CAT */
#if (defined(OSEE_TC_CORE3_134_ISR_CAT))
#if (OSEE_TC_CORE3_134_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_134_ISR_TID, 134)
#elif (OSEE_TC_CORE3_134_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_134_ISR_HND, 134)
#else
#error Invalid value for OSEE_TC_CORE3_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 134)
OSEE_ISR_ALIGN(_core3_, 3, 134)
#endif /* OSEE_TC_CORE3_134_ISR_CAT */
#if (defined(OSEE_TC_CORE3_135_ISR_CAT))
#if (OSEE_TC_CORE3_135_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_135_ISR_TID, 135)
#elif (OSEE_TC_CORE3_135_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_135_ISR_HND, 135)
#else
#error Invalid value for OSEE_TC_CORE3_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 135)
OSEE_ISR_ALIGN(_core3_, 3, 135)
#endif /* OSEE_TC_CORE3_135_ISR_CAT */
#if (defined(OSEE_TC_CORE3_136_ISR_CAT))
#if (OSEE_TC_CORE3_136_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_136_ISR_TID, 136)
#elif (OSEE_TC_CORE3_136_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_136_ISR_HND, 136)
#else
#error Invalid value for OSEE_TC_CORE3_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 136)
OSEE_ISR_ALIGN(_core3_, 3, 136)
#endif /* OSEE_TC_CORE3_136_ISR_CAT */
#if (defined(OSEE_TC_CORE3_137_ISR_CAT))
#if (OSEE_TC_CORE3_137_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_137_ISR_TID, 137)
#elif (OSEE_TC_CORE3_137_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_137_ISR_HND, 137)
#else
#error Invalid value for OSEE_TC_CORE3_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 137)
OSEE_ISR_ALIGN(_core3_, 3, 137)
#endif /* OSEE_TC_CORE3_137_ISR_CAT */
#if (defined(OSEE_TC_CORE3_138_ISR_CAT))
#if (OSEE_TC_CORE3_138_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_138_ISR_TID, 138)
#elif (OSEE_TC_CORE3_138_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_138_ISR_HND, 138)
#else
#error Invalid value for OSEE_TC_CORE3_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 138)
OSEE_ISR_ALIGN(_core3_, 3, 138)
#endif /* OSEE_TC_CORE3_138_ISR_CAT */
#if (defined(OSEE_TC_CORE3_139_ISR_CAT))
#if (OSEE_TC_CORE3_139_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_139_ISR_TID, 139)
#elif (OSEE_TC_CORE3_139_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_139_ISR_HND, 139)
#else
#error Invalid value for OSEE_TC_CORE3_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 139)
OSEE_ISR_ALIGN(_core3_, 3, 139)
#endif /* OSEE_TC_CORE3_139_ISR_CAT */
#if (defined(OSEE_TC_CORE3_140_ISR_CAT))
#if (OSEE_TC_CORE3_140_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_140_ISR_TID, 140)
#elif (OSEE_TC_CORE3_140_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_140_ISR_HND, 140)
#else
#error Invalid value for OSEE_TC_CORE3_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 140)
OSEE_ISR_ALIGN(_core3_, 3, 140)
#endif /* OSEE_TC_CORE3_140_ISR_CAT */
#if (defined(OSEE_TC_CORE3_141_ISR_CAT))
#if (OSEE_TC_CORE3_141_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_141_ISR_TID, 141)
#elif (OSEE_TC_CORE3_141_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_141_ISR_HND, 141)
#else
#error Invalid value for OSEE_TC_CORE3_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 141)
OSEE_ISR_ALIGN(_core3_, 3, 141)
#endif /* OSEE_TC_CORE3_141_ISR_CAT */
#if (defined(OSEE_TC_CORE3_142_ISR_CAT))
#if (OSEE_TC_CORE3_142_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_142_ISR_TID, 142)
#elif (OSEE_TC_CORE3_142_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_142_ISR_HND, 142)
#else
#error Invalid value for OSEE_TC_CORE3_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 142)
OSEE_ISR_ALIGN(_core3_, 3, 142)
#endif /* OSEE_TC_CORE3_142_ISR_CAT */
#if (defined(OSEE_TC_CORE3_143_ISR_CAT))
#if (OSEE_TC_CORE3_143_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_143_ISR_TID, 143)
#elif (OSEE_TC_CORE3_143_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_143_ISR_HND, 143)
#else
#error Invalid value for OSEE_TC_CORE3_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 143)
OSEE_ISR_ALIGN(_core3_, 3, 143)
#endif /* OSEE_TC_CORE3_143_ISR_CAT */
#if (defined(OSEE_TC_CORE3_144_ISR_CAT))
#if (OSEE_TC_CORE3_144_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_144_ISR_TID, 144)
#elif (OSEE_TC_CORE3_144_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_144_ISR_HND, 144)
#else
#error Invalid value for OSEE_TC_CORE3_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 144)
OSEE_ISR_ALIGN(_core3_, 3, 144)
#endif /* OSEE_TC_CORE3_144_ISR_CAT */
#if (defined(OSEE_TC_CORE3_145_ISR_CAT))
#if (OSEE_TC_CORE3_145_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_145_ISR_TID, 145)
#elif (OSEE_TC_CORE3_145_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_145_ISR_HND, 145)
#else
#error Invalid value for OSEE_TC_CORE3_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 145)
OSEE_ISR_ALIGN(_core3_, 3, 145)
#endif /* OSEE_TC_CORE3_145_ISR_CAT */
#if (defined(OSEE_TC_CORE3_146_ISR_CAT))
#if (OSEE_TC_CORE3_146_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_146_ISR_TID, 146)
#elif (OSEE_TC_CORE3_146_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_146_ISR_HND, 146)
#else
#error Invalid value for OSEE_TC_CORE3_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 146)
OSEE_ISR_ALIGN(_core3_, 3, 146)
#endif /* OSEE_TC_CORE3_146_ISR_CAT */
#if (defined(OSEE_TC_CORE3_147_ISR_CAT))
#if (OSEE_TC_CORE3_147_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_147_ISR_TID, 147)
#elif (OSEE_TC_CORE3_147_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_147_ISR_HND, 147)
#else
#error Invalid value for OSEE_TC_CORE3_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 147)
OSEE_ISR_ALIGN(_core3_, 3, 147)
#endif /* OSEE_TC_CORE3_147_ISR_CAT */
#if (defined(OSEE_TC_CORE3_148_ISR_CAT))
#if (OSEE_TC_CORE3_148_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_148_ISR_TID, 148)
#elif (OSEE_TC_CORE3_148_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_148_ISR_HND, 148)
#else
#error Invalid value for OSEE_TC_CORE3_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 148)
OSEE_ISR_ALIGN(_core3_, 3, 148)
#endif /* OSEE_TC_CORE3_148_ISR_CAT */
#if (defined(OSEE_TC_CORE3_149_ISR_CAT))
#if (OSEE_TC_CORE3_149_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_149_ISR_TID, 149)
#elif (OSEE_TC_CORE3_149_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_149_ISR_HND, 149)
#else
#error Invalid value for OSEE_TC_CORE3_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 149)
OSEE_ISR_ALIGN(_core3_, 3, 149)
#endif /* OSEE_TC_CORE3_149_ISR_CAT */
#if (defined(OSEE_TC_CORE3_150_ISR_CAT))
#if (OSEE_TC_CORE3_150_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_150_ISR_TID, 150)
#elif (OSEE_TC_CORE3_150_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_150_ISR_HND, 150)
#else
#error Invalid value for OSEE_TC_CORE3_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 150)
OSEE_ISR_ALIGN(_core3_, 3, 150)
#endif /* OSEE_TC_CORE3_150_ISR_CAT */
#if (defined(OSEE_TC_CORE3_151_ISR_CAT))
#if (OSEE_TC_CORE3_151_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_151_ISR_TID, 151)
#elif (OSEE_TC_CORE3_151_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_151_ISR_HND, 151)
#else
#error Invalid value for OSEE_TC_CORE3_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 151)
OSEE_ISR_ALIGN(_core3_, 3, 151)
#endif /* OSEE_TC_CORE3_151_ISR_CAT */
#if (defined(OSEE_TC_CORE3_152_ISR_CAT))
#if (OSEE_TC_CORE3_152_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_152_ISR_TID, 152)
#elif (OSEE_TC_CORE3_152_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_152_ISR_HND, 152)
#else
#error Invalid value for OSEE_TC_CORE3_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 152)
OSEE_ISR_ALIGN(_core3_, 3, 152)
#endif /* OSEE_TC_CORE3_152_ISR_CAT */
#if (defined(OSEE_TC_CORE3_153_ISR_CAT))
#if (OSEE_TC_CORE3_153_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_153_ISR_TID, 153)
#elif (OSEE_TC_CORE3_153_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_153_ISR_HND, 153)
#else
#error Invalid value for OSEE_TC_CORE3_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 153)
OSEE_ISR_ALIGN(_core3_, 3, 153)
#endif /* OSEE_TC_CORE3_153_ISR_CAT */
#if (defined(OSEE_TC_CORE3_154_ISR_CAT))
#if (OSEE_TC_CORE3_154_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_154_ISR_TID, 154)
#elif (OSEE_TC_CORE3_154_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_154_ISR_HND, 154)
#else
#error Invalid value for OSEE_TC_CORE3_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 154)
OSEE_ISR_ALIGN(_core3_, 3, 154)
#endif /* OSEE_TC_CORE3_154_ISR_CAT */
#if (defined(OSEE_TC_CORE3_155_ISR_CAT))
#if (OSEE_TC_CORE3_155_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_155_ISR_TID, 155)
#elif (OSEE_TC_CORE3_155_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_155_ISR_HND, 155)
#else
#error Invalid value for OSEE_TC_CORE3_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 155)
OSEE_ISR_ALIGN(_core3_, 3, 155)
#endif /* OSEE_TC_CORE3_155_ISR_CAT */
#if (defined(OSEE_TC_CORE3_156_ISR_CAT))
#if (OSEE_TC_CORE3_156_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_156_ISR_TID, 156)
#elif (OSEE_TC_CORE3_156_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_156_ISR_HND, 156)
#else
#error Invalid value for OSEE_TC_CORE3_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 156)
OSEE_ISR_ALIGN(_core3_, 3, 156)
#endif /* OSEE_TC_CORE3_156_ISR_CAT */
#if (defined(OSEE_TC_CORE3_157_ISR_CAT))
#if (OSEE_TC_CORE3_157_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_157_ISR_TID, 157)
#elif (OSEE_TC_CORE3_157_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_157_ISR_HND, 157)
#else
#error Invalid value for OSEE_TC_CORE3_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 157)
OSEE_ISR_ALIGN(_core3_, 3, 157)
#endif /* OSEE_TC_CORE3_157_ISR_CAT */
#if (defined(OSEE_TC_CORE3_158_ISR_CAT))
#if (OSEE_TC_CORE3_158_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_158_ISR_TID, 158)
#elif (OSEE_TC_CORE3_158_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_158_ISR_HND, 158)
#else
#error Invalid value for OSEE_TC_CORE3_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 158)
OSEE_ISR_ALIGN(_core3_, 3, 158)
#endif /* OSEE_TC_CORE3_158_ISR_CAT */
#if (defined(OSEE_TC_CORE3_159_ISR_CAT))
#if (OSEE_TC_CORE3_159_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_159_ISR_TID, 159)
#elif (OSEE_TC_CORE3_159_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_159_ISR_HND, 159)
#else
#error Invalid value for OSEE_TC_CORE3_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 159)
OSEE_ISR_ALIGN(_core3_, 3, 159)
#endif /* OSEE_TC_CORE3_159_ISR_CAT */
#if (defined(OSEE_TC_CORE3_160_ISR_CAT))
#if (OSEE_TC_CORE3_160_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_160_ISR_TID, 160)
#elif (OSEE_TC_CORE3_160_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_160_ISR_HND, 160)
#else
#error Invalid value for OSEE_TC_CORE3_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 160)
OSEE_ISR_ALIGN(_core3_, 3, 160)
#endif /* OSEE_TC_CORE3_160_ISR_CAT */
#if (defined(OSEE_TC_CORE3_161_ISR_CAT))
#if (OSEE_TC_CORE3_161_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_161_ISR_TID, 161)
#elif (OSEE_TC_CORE3_161_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_161_ISR_HND, 161)
#else
#error Invalid value for OSEE_TC_CORE3_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 161)
OSEE_ISR_ALIGN(_core3_, 3, 161)
#endif /* OSEE_TC_CORE3_161_ISR_CAT */
#if (defined(OSEE_TC_CORE3_162_ISR_CAT))
#if (OSEE_TC_CORE3_162_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_162_ISR_TID, 162)
#elif (OSEE_TC_CORE3_162_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_162_ISR_HND, 162)
#else
#error Invalid value for OSEE_TC_CORE3_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 162)
OSEE_ISR_ALIGN(_core3_, 3, 162)
#endif /* OSEE_TC_CORE3_162_ISR_CAT */
#if (defined(OSEE_TC_CORE3_163_ISR_CAT))
#if (OSEE_TC_CORE3_163_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_163_ISR_TID, 163)
#elif (OSEE_TC_CORE3_163_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_163_ISR_HND, 163)
#else
#error Invalid value for OSEE_TC_CORE3_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 163)
OSEE_ISR_ALIGN(_core3_, 3, 163)
#endif /* OSEE_TC_CORE3_163_ISR_CAT */
#if (defined(OSEE_TC_CORE3_164_ISR_CAT))
#if (OSEE_TC_CORE3_164_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_164_ISR_TID, 164)
#elif (OSEE_TC_CORE3_164_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_164_ISR_HND, 164)
#else
#error Invalid value for OSEE_TC_CORE3_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 164)
OSEE_ISR_ALIGN(_core3_, 3, 164)
#endif /* OSEE_TC_CORE3_164_ISR_CAT */
#if (defined(OSEE_TC_CORE3_165_ISR_CAT))
#if (OSEE_TC_CORE3_165_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_165_ISR_TID, 165)
#elif (OSEE_TC_CORE3_165_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_165_ISR_HND, 165)
#else
#error Invalid value for OSEE_TC_CORE3_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 165)
OSEE_ISR_ALIGN(_core3_, 3, 165)
#endif /* OSEE_TC_CORE3_165_ISR_CAT */
#if (defined(OSEE_TC_CORE3_166_ISR_CAT))
#if (OSEE_TC_CORE3_166_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_166_ISR_TID, 166)
#elif (OSEE_TC_CORE3_166_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_166_ISR_HND, 166)
#else
#error Invalid value for OSEE_TC_CORE3_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 166)
OSEE_ISR_ALIGN(_core3_, 3, 166)
#endif /* OSEE_TC_CORE3_166_ISR_CAT */
#if (defined(OSEE_TC_CORE3_167_ISR_CAT))
#if (OSEE_TC_CORE3_167_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_167_ISR_TID, 167)
#elif (OSEE_TC_CORE3_167_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_167_ISR_HND, 167)
#else
#error Invalid value for OSEE_TC_CORE3_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 167)
OSEE_ISR_ALIGN(_core3_, 3, 167)
#endif /* OSEE_TC_CORE3_167_ISR_CAT */
#if (defined(OSEE_TC_CORE3_168_ISR_CAT))
#if (OSEE_TC_CORE3_168_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_168_ISR_TID, 168)
#elif (OSEE_TC_CORE3_168_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_168_ISR_HND, 168)
#else
#error Invalid value for OSEE_TC_CORE3_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 168)
OSEE_ISR_ALIGN(_core3_, 3, 168)
#endif /* OSEE_TC_CORE3_168_ISR_CAT */
#if (defined(OSEE_TC_CORE3_169_ISR_CAT))
#if (OSEE_TC_CORE3_169_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_169_ISR_TID, 169)
#elif (OSEE_TC_CORE3_169_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_169_ISR_HND, 169)
#else
#error Invalid value for OSEE_TC_CORE3_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 169)
OSEE_ISR_ALIGN(_core3_, 3, 169)
#endif /* OSEE_TC_CORE3_169_ISR_CAT */
#if (defined(OSEE_TC_CORE3_170_ISR_CAT))
#if (OSEE_TC_CORE3_170_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_170_ISR_TID, 170)
#elif (OSEE_TC_CORE3_170_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_170_ISR_HND, 170)
#else
#error Invalid value for OSEE_TC_CORE3_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 170)
OSEE_ISR_ALIGN(_core3_, 3, 170)
#endif /* OSEE_TC_CORE3_170_ISR_CAT */
#if (defined(OSEE_TC_CORE3_171_ISR_CAT))
#if (OSEE_TC_CORE3_171_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_171_ISR_TID, 171)
#elif (OSEE_TC_CORE3_171_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_171_ISR_HND, 171)
#else
#error Invalid value for OSEE_TC_CORE3_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 171)
OSEE_ISR_ALIGN(_core3_, 3, 171)
#endif /* OSEE_TC_CORE3_171_ISR_CAT */
#if (defined(OSEE_TC_CORE3_172_ISR_CAT))
#if (OSEE_TC_CORE3_172_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_172_ISR_TID, 172)
#elif (OSEE_TC_CORE3_172_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_172_ISR_HND, 172)
#else
#error Invalid value for OSEE_TC_CORE3_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 172)
OSEE_ISR_ALIGN(_core3_, 3, 172)
#endif /* OSEE_TC_CORE3_172_ISR_CAT */
#if (defined(OSEE_TC_CORE3_173_ISR_CAT))
#if (OSEE_TC_CORE3_173_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_173_ISR_TID, 173)
#elif (OSEE_TC_CORE3_173_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_173_ISR_HND, 173)
#else
#error Invalid value for OSEE_TC_CORE3_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 173)
OSEE_ISR_ALIGN(_core3_, 3, 173)
#endif /* OSEE_TC_CORE3_173_ISR_CAT */
#if (defined(OSEE_TC_CORE3_174_ISR_CAT))
#if (OSEE_TC_CORE3_174_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_174_ISR_TID, 174)
#elif (OSEE_TC_CORE3_174_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_174_ISR_HND, 174)
#else
#error Invalid value for OSEE_TC_CORE3_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 174)
OSEE_ISR_ALIGN(_core3_, 3, 174)
#endif /* OSEE_TC_CORE3_174_ISR_CAT */
#if (defined(OSEE_TC_CORE3_175_ISR_CAT))
#if (OSEE_TC_CORE3_175_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_175_ISR_TID, 175)
#elif (OSEE_TC_CORE3_175_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_175_ISR_HND, 175)
#else
#error Invalid value for OSEE_TC_CORE3_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 175)
OSEE_ISR_ALIGN(_core3_, 3, 175)
#endif /* OSEE_TC_CORE3_175_ISR_CAT */
#if (defined(OSEE_TC_CORE3_176_ISR_CAT))
#if (OSEE_TC_CORE3_176_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_176_ISR_TID, 176)
#elif (OSEE_TC_CORE3_176_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_176_ISR_HND, 176)
#else
#error Invalid value for OSEE_TC_CORE3_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 176)
OSEE_ISR_ALIGN(_core3_, 3, 176)
#endif /* OSEE_TC_CORE3_176_ISR_CAT */
#if (defined(OSEE_TC_CORE3_177_ISR_CAT))
#if (OSEE_TC_CORE3_177_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_177_ISR_TID, 177)
#elif (OSEE_TC_CORE3_177_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_177_ISR_HND, 177)
#else
#error Invalid value for OSEE_TC_CORE3_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 177)
OSEE_ISR_ALIGN(_core3_, 3, 177)
#endif /* OSEE_TC_CORE3_177_ISR_CAT */
#if (defined(OSEE_TC_CORE3_178_ISR_CAT))
#if (OSEE_TC_CORE3_178_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_178_ISR_TID, 178)
#elif (OSEE_TC_CORE3_178_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_178_ISR_HND, 178)
#else
#error Invalid value for OSEE_TC_CORE3_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 178)
OSEE_ISR_ALIGN(_core3_, 3, 178)
#endif /* OSEE_TC_CORE3_178_ISR_CAT */
#if (defined(OSEE_TC_CORE3_179_ISR_CAT))
#if (OSEE_TC_CORE3_179_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_179_ISR_TID, 179)
#elif (OSEE_TC_CORE3_179_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_179_ISR_HND, 179)
#else
#error Invalid value for OSEE_TC_CORE3_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 179)
OSEE_ISR_ALIGN(_core3_, 3, 179)
#endif /* OSEE_TC_CORE3_179_ISR_CAT */
#if (defined(OSEE_TC_CORE3_180_ISR_CAT))
#if (OSEE_TC_CORE3_180_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_180_ISR_TID, 180)
#elif (OSEE_TC_CORE3_180_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_180_ISR_HND, 180)
#else
#error Invalid value for OSEE_TC_CORE3_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 180)
OSEE_ISR_ALIGN(_core3_, 3, 180)
#endif /* OSEE_TC_CORE3_180_ISR_CAT */
#if (defined(OSEE_TC_CORE3_181_ISR_CAT))
#if (OSEE_TC_CORE3_181_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_181_ISR_TID, 181)
#elif (OSEE_TC_CORE3_181_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_181_ISR_HND, 181)
#else
#error Invalid value for OSEE_TC_CORE3_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 181)
OSEE_ISR_ALIGN(_core3_, 3, 181)
#endif /* OSEE_TC_CORE3_181_ISR_CAT */
#if (defined(OSEE_TC_CORE3_182_ISR_CAT))
#if (OSEE_TC_CORE3_182_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_182_ISR_TID, 182)
#elif (OSEE_TC_CORE3_182_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_182_ISR_HND, 182)
#else
#error Invalid value for OSEE_TC_CORE3_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 182)
OSEE_ISR_ALIGN(_core3_, 3, 182)
#endif /* OSEE_TC_CORE3_182_ISR_CAT */
#if (defined(OSEE_TC_CORE3_183_ISR_CAT))
#if (OSEE_TC_CORE3_183_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_183_ISR_TID, 183)
#elif (OSEE_TC_CORE3_183_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_183_ISR_HND, 183)
#else
#error Invalid value for OSEE_TC_CORE3_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 183)
OSEE_ISR_ALIGN(_core3_, 3, 183)
#endif /* OSEE_TC_CORE3_183_ISR_CAT */
#if (defined(OSEE_TC_CORE3_184_ISR_CAT))
#if (OSEE_TC_CORE3_184_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_184_ISR_TID, 184)
#elif (OSEE_TC_CORE3_184_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_184_ISR_HND, 184)
#else
#error Invalid value for OSEE_TC_CORE3_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 184)
OSEE_ISR_ALIGN(_core3_, 3, 184)
#endif /* OSEE_TC_CORE3_184_ISR_CAT */
#if (defined(OSEE_TC_CORE3_185_ISR_CAT))
#if (OSEE_TC_CORE3_185_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_185_ISR_TID, 185)
#elif (OSEE_TC_CORE3_185_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_185_ISR_HND, 185)
#else
#error Invalid value for OSEE_TC_CORE3_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 185)
OSEE_ISR_ALIGN(_core3_, 3, 185)
#endif /* OSEE_TC_CORE3_185_ISR_CAT */
#if (defined(OSEE_TC_CORE3_186_ISR_CAT))
#if (OSEE_TC_CORE3_186_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_186_ISR_TID, 186)
#elif (OSEE_TC_CORE3_186_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_186_ISR_HND, 186)
#else
#error Invalid value for OSEE_TC_CORE3_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 186)
OSEE_ISR_ALIGN(_core3_, 3, 186)
#endif /* OSEE_TC_CORE3_186_ISR_CAT */
#if (defined(OSEE_TC_CORE3_187_ISR_CAT))
#if (OSEE_TC_CORE3_187_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_187_ISR_TID, 187)
#elif (OSEE_TC_CORE3_187_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_187_ISR_HND, 187)
#else
#error Invalid value for OSEE_TC_CORE3_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 187)
OSEE_ISR_ALIGN(_core3_, 3, 187)
#endif /* OSEE_TC_CORE3_187_ISR_CAT */
#if (defined(OSEE_TC_CORE3_188_ISR_CAT))
#if (OSEE_TC_CORE3_188_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_188_ISR_TID, 188)
#elif (OSEE_TC_CORE3_188_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_188_ISR_HND, 188)
#else
#error Invalid value for OSEE_TC_CORE3_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 188)
OSEE_ISR_ALIGN(_core3_, 3, 188)
#endif /* OSEE_TC_CORE3_188_ISR_CAT */
#if (defined(OSEE_TC_CORE3_189_ISR_CAT))
#if (OSEE_TC_CORE3_189_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_189_ISR_TID, 189)
#elif (OSEE_TC_CORE3_189_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_189_ISR_HND, 189)
#else
#error Invalid value for OSEE_TC_CORE3_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 189)
OSEE_ISR_ALIGN(_core3_, 3, 189)
#endif /* OSEE_TC_CORE3_189_ISR_CAT */
#if (defined(OSEE_TC_CORE3_190_ISR_CAT))
#if (OSEE_TC_CORE3_190_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_190_ISR_TID, 190)
#elif (OSEE_TC_CORE3_190_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_190_ISR_HND, 190)
#else
#error Invalid value for OSEE_TC_CORE3_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 190)
OSEE_ISR_ALIGN(_core3_, 3, 190)
#endif /* OSEE_TC_CORE3_190_ISR_CAT */
#if (defined(OSEE_TC_CORE3_191_ISR_CAT))
#if (OSEE_TC_CORE3_191_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_191_ISR_TID, 191)
#elif (OSEE_TC_CORE3_191_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_191_ISR_HND, 191)
#else
#error Invalid value for OSEE_TC_CORE3_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 191)
OSEE_ISR_ALIGN(_core3_, 3, 191)
#endif /* OSEE_TC_CORE3_191_ISR_CAT */
#if (defined(OSEE_TC_CORE3_192_ISR_CAT))
#if (OSEE_TC_CORE3_192_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_192_ISR_TID, 192)
#elif (OSEE_TC_CORE3_192_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_192_ISR_HND, 192)
#else
#error Invalid value for OSEE_TC_CORE3_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 192)
OSEE_ISR_ALIGN(_core3_, 3, 192)
#endif /* OSEE_TC_CORE3_192_ISR_CAT */
#if (defined(OSEE_TC_CORE3_193_ISR_CAT))
#if (OSEE_TC_CORE3_193_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_193_ISR_TID, 193)
#elif (OSEE_TC_CORE3_193_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_193_ISR_HND, 193)
#else
#error Invalid value for OSEE_TC_CORE3_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 193)
OSEE_ISR_ALIGN(_core3_, 3, 193)
#endif /* OSEE_TC_CORE3_193_ISR_CAT */
#if (defined(OSEE_TC_CORE3_194_ISR_CAT))
#if (OSEE_TC_CORE3_194_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_194_ISR_TID, 194)
#elif (OSEE_TC_CORE3_194_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_194_ISR_HND, 194)
#else
#error Invalid value for OSEE_TC_CORE3_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 194)
OSEE_ISR_ALIGN(_core3_, 3, 194)
#endif /* OSEE_TC_CORE3_194_ISR_CAT */
#if (defined(OSEE_TC_CORE3_195_ISR_CAT))
#if (OSEE_TC_CORE3_195_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_195_ISR_TID, 195)
#elif (OSEE_TC_CORE3_195_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_195_ISR_HND, 195)
#else
#error Invalid value for OSEE_TC_CORE3_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 195)
OSEE_ISR_ALIGN(_core3_, 3, 195)
#endif /* OSEE_TC_CORE3_195_ISR_CAT */
#if (defined(OSEE_TC_CORE3_196_ISR_CAT))
#if (OSEE_TC_CORE3_196_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_196_ISR_TID, 196)
#elif (OSEE_TC_CORE3_196_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_196_ISR_HND, 196)
#else
#error Invalid value for OSEE_TC_CORE3_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 196)
OSEE_ISR_ALIGN(_core3_, 3, 196)
#endif /* OSEE_TC_CORE3_196_ISR_CAT */
#if (defined(OSEE_TC_CORE3_197_ISR_CAT))
#if (OSEE_TC_CORE3_197_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_197_ISR_TID, 197)
#elif (OSEE_TC_CORE3_197_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_197_ISR_HND, 197)
#else
#error Invalid value for OSEE_TC_CORE3_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 197)
OSEE_ISR_ALIGN(_core3_, 3, 197)
#endif /* OSEE_TC_CORE3_197_ISR_CAT */
#if (defined(OSEE_TC_CORE3_198_ISR_CAT))
#if (OSEE_TC_CORE3_198_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_198_ISR_TID, 198)
#elif (OSEE_TC_CORE3_198_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_198_ISR_HND, 198)
#else
#error Invalid value for OSEE_TC_CORE3_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 198)
OSEE_ISR_ALIGN(_core3_, 3, 198)
#endif /* OSEE_TC_CORE3_198_ISR_CAT */
#if (defined(OSEE_TC_CORE3_199_ISR_CAT))
#if (OSEE_TC_CORE3_199_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_199_ISR_TID, 199)
#elif (OSEE_TC_CORE3_199_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_199_ISR_HND, 199)
#else
#error Invalid value for OSEE_TC_CORE3_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 199)
OSEE_ISR_ALIGN(_core3_, 3, 199)
#endif /* OSEE_TC_CORE3_199_ISR_CAT */
#if (defined(OSEE_TC_CORE3_200_ISR_CAT))
#if (OSEE_TC_CORE3_200_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_200_ISR_TID, 200)
#elif (OSEE_TC_CORE3_200_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_200_ISR_HND, 200)
#else
#error Invalid value for OSEE_TC_CORE3_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 200)
OSEE_ISR_ALIGN(_core3_, 3, 200)
#endif /* OSEE_TC_CORE3_200_ISR_CAT */
#if (defined(OSEE_TC_CORE3_201_ISR_CAT))
#if (OSEE_TC_CORE3_201_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_201_ISR_TID, 201)
#elif (OSEE_TC_CORE3_201_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_201_ISR_HND, 201)
#else
#error Invalid value for OSEE_TC_CORE3_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 201)
OSEE_ISR_ALIGN(_core3_, 3, 201)
#endif /* OSEE_TC_CORE3_201_ISR_CAT */
#if (defined(OSEE_TC_CORE3_202_ISR_CAT))
#if (OSEE_TC_CORE3_202_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_202_ISR_TID, 202)
#elif (OSEE_TC_CORE3_202_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_202_ISR_HND, 202)
#else
#error Invalid value for OSEE_TC_CORE3_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 202)
OSEE_ISR_ALIGN(_core3_, 3, 202)
#endif /* OSEE_TC_CORE3_202_ISR_CAT */
#if (defined(OSEE_TC_CORE3_203_ISR_CAT))
#if (OSEE_TC_CORE3_203_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_203_ISR_TID, 203)
#elif (OSEE_TC_CORE3_203_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_203_ISR_HND, 203)
#else
#error Invalid value for OSEE_TC_CORE3_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 203)
OSEE_ISR_ALIGN(_core3_, 3, 203)
#endif /* OSEE_TC_CORE3_203_ISR_CAT */
#if (defined(OSEE_TC_CORE3_204_ISR_CAT))
#if (OSEE_TC_CORE3_204_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_204_ISR_TID, 204)
#elif (OSEE_TC_CORE3_204_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_204_ISR_HND, 204)
#else
#error Invalid value for OSEE_TC_CORE3_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 204)
OSEE_ISR_ALIGN(_core3_, 3, 204)
#endif /* OSEE_TC_CORE3_204_ISR_CAT */
#if (defined(OSEE_TC_CORE3_205_ISR_CAT))
#if (OSEE_TC_CORE3_205_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_205_ISR_TID, 205)
#elif (OSEE_TC_CORE3_205_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_205_ISR_HND, 205)
#else
#error Invalid value for OSEE_TC_CORE3_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 205)
OSEE_ISR_ALIGN(_core3_, 3, 205)
#endif /* OSEE_TC_CORE3_205_ISR_CAT */
#if (defined(OSEE_TC_CORE3_206_ISR_CAT))
#if (OSEE_TC_CORE3_206_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_206_ISR_TID, 206)
#elif (OSEE_TC_CORE3_206_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_206_ISR_HND, 206)
#else
#error Invalid value for OSEE_TC_CORE3_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 206)
OSEE_ISR_ALIGN(_core3_, 3, 206)
#endif /* OSEE_TC_CORE3_206_ISR_CAT */
#if (defined(OSEE_TC_CORE3_207_ISR_CAT))
#if (OSEE_TC_CORE3_207_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_207_ISR_TID, 207)
#elif (OSEE_TC_CORE3_207_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_207_ISR_HND, 207)
#else
#error Invalid value for OSEE_TC_CORE3_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 207)
OSEE_ISR_ALIGN(_core3_, 3, 207)
#endif /* OSEE_TC_CORE3_207_ISR_CAT */
#if (defined(OSEE_TC_CORE3_208_ISR_CAT))
#if (OSEE_TC_CORE3_208_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_208_ISR_TID, 208)
#elif (OSEE_TC_CORE3_208_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_208_ISR_HND, 208)
#else
#error Invalid value for OSEE_TC_CORE3_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 208)
OSEE_ISR_ALIGN(_core3_, 3, 208)
#endif /* OSEE_TC_CORE3_208_ISR_CAT */
#if (defined(OSEE_TC_CORE3_209_ISR_CAT))
#if (OSEE_TC_CORE3_209_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_209_ISR_TID, 209)
#elif (OSEE_TC_CORE3_209_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_209_ISR_HND, 209)
#else
#error Invalid value for OSEE_TC_CORE3_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 209)
OSEE_ISR_ALIGN(_core3_, 3, 209)
#endif /* OSEE_TC_CORE3_209_ISR_CAT */
#if (defined(OSEE_TC_CORE3_210_ISR_CAT))
#if (OSEE_TC_CORE3_210_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_210_ISR_TID, 210)
#elif (OSEE_TC_CORE3_210_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_210_ISR_HND, 210)
#else
#error Invalid value for OSEE_TC_CORE3_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 210)
OSEE_ISR_ALIGN(_core3_, 3, 210)
#endif /* OSEE_TC_CORE3_210_ISR_CAT */
#if (defined(OSEE_TC_CORE3_211_ISR_CAT))
#if (OSEE_TC_CORE3_211_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_211_ISR_TID, 211)
#elif (OSEE_TC_CORE3_211_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_211_ISR_HND, 211)
#else
#error Invalid value for OSEE_TC_CORE3_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 211)
OSEE_ISR_ALIGN(_core3_, 3, 211)
#endif /* OSEE_TC_CORE3_211_ISR_CAT */
#if (defined(OSEE_TC_CORE3_212_ISR_CAT))
#if (OSEE_TC_CORE3_212_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_212_ISR_TID, 212)
#elif (OSEE_TC_CORE3_212_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_212_ISR_HND, 212)
#else
#error Invalid value for OSEE_TC_CORE3_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 212)
OSEE_ISR_ALIGN(_core3_, 3, 212)
#endif /* OSEE_TC_CORE3_212_ISR_CAT */
#if (defined(OSEE_TC_CORE3_213_ISR_CAT))
#if (OSEE_TC_CORE3_213_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_213_ISR_TID, 213)
#elif (OSEE_TC_CORE3_213_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_213_ISR_HND, 213)
#else
#error Invalid value for OSEE_TC_CORE3_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 213)
OSEE_ISR_ALIGN(_core3_, 3, 213)
#endif /* OSEE_TC_CORE3_213_ISR_CAT */
#if (defined(OSEE_TC_CORE3_214_ISR_CAT))
#if (OSEE_TC_CORE3_214_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_214_ISR_TID, 214)
#elif (OSEE_TC_CORE3_214_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_214_ISR_HND, 214)
#else
#error Invalid value for OSEE_TC_CORE3_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 214)
OSEE_ISR_ALIGN(_core3_, 3, 214)
#endif /* OSEE_TC_CORE3_214_ISR_CAT */
#if (defined(OSEE_TC_CORE3_215_ISR_CAT))
#if (OSEE_TC_CORE3_215_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_215_ISR_TID, 215)
#elif (OSEE_TC_CORE3_215_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_215_ISR_HND, 215)
#else
#error Invalid value for OSEE_TC_CORE3_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 215)
OSEE_ISR_ALIGN(_core3_, 3, 215)
#endif /* OSEE_TC_CORE3_215_ISR_CAT */
#if (defined(OSEE_TC_CORE3_216_ISR_CAT))
#if (OSEE_TC_CORE3_216_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_216_ISR_TID, 216)
#elif (OSEE_TC_CORE3_216_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_216_ISR_HND, 216)
#else
#error Invalid value for OSEE_TC_CORE3_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 216)
OSEE_ISR_ALIGN(_core3_, 3, 216)
#endif /* OSEE_TC_CORE3_216_ISR_CAT */
#if (defined(OSEE_TC_CORE3_217_ISR_CAT))
#if (OSEE_TC_CORE3_217_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_217_ISR_TID, 217)
#elif (OSEE_TC_CORE3_217_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_217_ISR_HND, 217)
#else
#error Invalid value for OSEE_TC_CORE3_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 217)
OSEE_ISR_ALIGN(_core3_, 3, 217)
#endif /* OSEE_TC_CORE3_217_ISR_CAT */
#if (defined(OSEE_TC_CORE3_218_ISR_CAT))
#if (OSEE_TC_CORE3_218_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_218_ISR_TID, 218)
#elif (OSEE_TC_CORE3_218_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_218_ISR_HND, 218)
#else
#error Invalid value for OSEE_TC_CORE3_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 218)
OSEE_ISR_ALIGN(_core3_, 3, 218)
#endif /* OSEE_TC_CORE3_218_ISR_CAT */
#if (defined(OSEE_TC_CORE3_219_ISR_CAT))
#if (OSEE_TC_CORE3_219_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_219_ISR_TID, 219)
#elif (OSEE_TC_CORE3_219_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_219_ISR_HND, 219)
#else
#error Invalid value for OSEE_TC_CORE3_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 219)
OSEE_ISR_ALIGN(_core3_, 3, 219)
#endif /* OSEE_TC_CORE3_219_ISR_CAT */
#if (defined(OSEE_TC_CORE3_220_ISR_CAT))
#if (OSEE_TC_CORE3_220_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_220_ISR_TID, 220)
#elif (OSEE_TC_CORE3_220_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_220_ISR_HND, 220)
#else
#error Invalid value for OSEE_TC_CORE3_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 220)
OSEE_ISR_ALIGN(_core3_, 3, 220)
#endif /* OSEE_TC_CORE3_220_ISR_CAT */
#if (defined(OSEE_TC_CORE3_221_ISR_CAT))
#if (OSEE_TC_CORE3_221_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_221_ISR_TID, 221)
#elif (OSEE_TC_CORE3_221_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_221_ISR_HND, 221)
#else
#error Invalid value for OSEE_TC_CORE3_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 221)
OSEE_ISR_ALIGN(_core3_, 3, 221)
#endif /* OSEE_TC_CORE3_221_ISR_CAT */
#if (defined(OSEE_TC_CORE3_222_ISR_CAT))
#if (OSEE_TC_CORE3_222_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_222_ISR_TID, 222)
#elif (OSEE_TC_CORE3_222_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_222_ISR_HND, 222)
#else
#error Invalid value for OSEE_TC_CORE3_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 222)
OSEE_ISR_ALIGN(_core3_, 3, 222)
#endif /* OSEE_TC_CORE3_222_ISR_CAT */
#if (defined(OSEE_TC_CORE3_223_ISR_CAT))
#if (OSEE_TC_CORE3_223_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_223_ISR_TID, 223)
#elif (OSEE_TC_CORE3_223_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_223_ISR_HND, 223)
#else
#error Invalid value for OSEE_TC_CORE3_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 223)
OSEE_ISR_ALIGN(_core3_, 3, 223)
#endif /* OSEE_TC_CORE3_223_ISR_CAT */
#if (defined(OSEE_TC_CORE3_224_ISR_CAT))
#if (OSEE_TC_CORE3_224_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_224_ISR_TID, 224)
#elif (OSEE_TC_CORE3_224_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_224_ISR_HND, 224)
#else
#error Invalid value for OSEE_TC_CORE3_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 224)
OSEE_ISR_ALIGN(_core3_, 3, 224)
#endif /* OSEE_TC_CORE3_224_ISR_CAT */
#if (defined(OSEE_TC_CORE3_225_ISR_CAT))
#if (OSEE_TC_CORE3_225_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_225_ISR_TID, 225)
#elif (OSEE_TC_CORE3_225_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_225_ISR_HND, 225)
#else
#error Invalid value for OSEE_TC_CORE3_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 225)
OSEE_ISR_ALIGN(_core3_, 3, 225)
#endif /* OSEE_TC_CORE3_225_ISR_CAT */
#if (defined(OSEE_TC_CORE3_226_ISR_CAT))
#if (OSEE_TC_CORE3_226_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_226_ISR_TID, 226)
#elif (OSEE_TC_CORE3_226_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_226_ISR_HND, 226)
#else
#error Invalid value for OSEE_TC_CORE3_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 226)
OSEE_ISR_ALIGN(_core3_, 3, 226)
#endif /* OSEE_TC_CORE3_226_ISR_CAT */
#if (defined(OSEE_TC_CORE3_227_ISR_CAT))
#if (OSEE_TC_CORE3_227_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_227_ISR_TID, 227)
#elif (OSEE_TC_CORE3_227_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_227_ISR_HND, 227)
#else
#error Invalid value for OSEE_TC_CORE3_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 227)
OSEE_ISR_ALIGN(_core3_, 3, 227)
#endif /* OSEE_TC_CORE3_227_ISR_CAT */
#if (defined(OSEE_TC_CORE3_228_ISR_CAT))
#if (OSEE_TC_CORE3_228_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_228_ISR_TID, 228)
#elif (OSEE_TC_CORE3_228_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_228_ISR_HND, 228)
#else
#error Invalid value for OSEE_TC_CORE3_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 228)
OSEE_ISR_ALIGN(_core3_, 3, 228)
#endif /* OSEE_TC_CORE3_228_ISR_CAT */
#if (defined(OSEE_TC_CORE3_229_ISR_CAT))
#if (OSEE_TC_CORE3_229_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_229_ISR_TID, 229)
#elif (OSEE_TC_CORE3_229_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_229_ISR_HND, 229)
#else
#error Invalid value for OSEE_TC_CORE3_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 229)
OSEE_ISR_ALIGN(_core3_, 3, 229)
#endif /* OSEE_TC_CORE3_229_ISR_CAT */
#if (defined(OSEE_TC_CORE3_230_ISR_CAT))
#if (OSEE_TC_CORE3_230_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_230_ISR_TID, 230)
#elif (OSEE_TC_CORE3_230_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_230_ISR_HND, 230)
#else
#error Invalid value for OSEE_TC_CORE3_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 230)
OSEE_ISR_ALIGN(_core3_, 3, 230)
#endif /* OSEE_TC_CORE3_230_ISR_CAT */
#if (defined(OSEE_TC_CORE3_231_ISR_CAT))
#if (OSEE_TC_CORE3_231_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_231_ISR_TID, 231)
#elif (OSEE_TC_CORE3_231_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_231_ISR_HND, 231)
#else
#error Invalid value for OSEE_TC_CORE3_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 231)
OSEE_ISR_ALIGN(_core3_, 3, 231)
#endif /* OSEE_TC_CORE3_231_ISR_CAT */
#if (defined(OSEE_TC_CORE3_232_ISR_CAT))
#if (OSEE_TC_CORE3_232_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_232_ISR_TID, 232)
#elif (OSEE_TC_CORE3_232_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_232_ISR_HND, 232)
#else
#error Invalid value for OSEE_TC_CORE3_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 232)
OSEE_ISR_ALIGN(_core3_, 3, 232)
#endif /* OSEE_TC_CORE3_232_ISR_CAT */
#if (defined(OSEE_TC_CORE3_233_ISR_CAT))
#if (OSEE_TC_CORE3_233_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_233_ISR_TID, 233)
#elif (OSEE_TC_CORE3_233_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_233_ISR_HND, 233)
#else
#error Invalid value for OSEE_TC_CORE3_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 233)
OSEE_ISR_ALIGN(_core3_, 3, 233)
#endif /* OSEE_TC_CORE3_233_ISR_CAT */
#if (defined(OSEE_TC_CORE3_234_ISR_CAT))
#if (OSEE_TC_CORE3_234_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_234_ISR_TID, 234)
#elif (OSEE_TC_CORE3_234_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_234_ISR_HND, 234)
#else
#error Invalid value for OSEE_TC_CORE3_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 234)
OSEE_ISR_ALIGN(_core3_, 3, 234)
#endif /* OSEE_TC_CORE3_234_ISR_CAT */
#if (defined(OSEE_TC_CORE3_235_ISR_CAT))
#if (OSEE_TC_CORE3_235_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_235_ISR_TID, 235)
#elif (OSEE_TC_CORE3_235_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_235_ISR_HND, 235)
#else
#error Invalid value for OSEE_TC_CORE3_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 235)
OSEE_ISR_ALIGN(_core3_, 3, 235)
#endif /* OSEE_TC_CORE3_235_ISR_CAT */
#if (defined(OSEE_TC_CORE3_236_ISR_CAT))
#if (OSEE_TC_CORE3_236_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_236_ISR_TID, 236)
#elif (OSEE_TC_CORE3_236_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_236_ISR_HND, 236)
#else
#error Invalid value for OSEE_TC_CORE3_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 236)
OSEE_ISR_ALIGN(_core3_, 3, 236)
#endif /* OSEE_TC_CORE3_236_ISR_CAT */
#if (defined(OSEE_TC_CORE3_237_ISR_CAT))
#if (OSEE_TC_CORE3_237_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_237_ISR_TID, 237)
#elif (OSEE_TC_CORE3_237_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_237_ISR_HND, 237)
#else
#error Invalid value for OSEE_TC_CORE3_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 237)
OSEE_ISR_ALIGN(_core3_, 3, 237)
#endif /* OSEE_TC_CORE3_237_ISR_CAT */
#if (defined(OSEE_TC_CORE3_238_ISR_CAT))
#if (OSEE_TC_CORE3_238_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_238_ISR_TID, 238)
#elif (OSEE_TC_CORE3_238_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_238_ISR_HND, 238)
#else
#error Invalid value for OSEE_TC_CORE3_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 238)
OSEE_ISR_ALIGN(_core3_, 3, 238)
#endif /* OSEE_TC_CORE3_238_ISR_CAT */
#if (defined(OSEE_TC_CORE3_239_ISR_CAT))
#if (OSEE_TC_CORE3_239_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_239_ISR_TID, 239)
#elif (OSEE_TC_CORE3_239_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_239_ISR_HND, 239)
#else
#error Invalid value for OSEE_TC_CORE3_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 239)
OSEE_ISR_ALIGN(_core3_, 3, 239)
#endif /* OSEE_TC_CORE3_239_ISR_CAT */
#if (defined(OSEE_TC_CORE3_240_ISR_CAT))
#if (OSEE_TC_CORE3_240_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_240_ISR_TID, 240)
#elif (OSEE_TC_CORE3_240_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_240_ISR_HND, 240)
#else
#error Invalid value for OSEE_TC_CORE3_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 240)
OSEE_ISR_ALIGN(_core3_, 3, 240)
#endif /* OSEE_TC_CORE3_240_ISR_CAT */
#if (defined(OSEE_TC_CORE3_241_ISR_CAT))
#if (OSEE_TC_CORE3_241_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_241_ISR_TID, 241)
#elif (OSEE_TC_CORE3_241_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_241_ISR_HND, 241)
#else
#error Invalid value for OSEE_TC_CORE3_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 241)
OSEE_ISR_ALIGN(_core3_, 3, 241)
#endif /* OSEE_TC_CORE3_241_ISR_CAT */
#if (defined(OSEE_TC_CORE3_242_ISR_CAT))
#if (OSEE_TC_CORE3_242_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_242_ISR_TID, 242)
#elif (OSEE_TC_CORE3_242_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_242_ISR_HND, 242)
#else
#error Invalid value for OSEE_TC_CORE3_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 242)
OSEE_ISR_ALIGN(_core3_, 3, 242)
#endif /* OSEE_TC_CORE3_242_ISR_CAT */
#if (defined(OSEE_TC_CORE3_243_ISR_CAT))
#if (OSEE_TC_CORE3_243_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_243_ISR_TID, 243)
#elif (OSEE_TC_CORE3_243_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_243_ISR_HND, 243)
#else
#error Invalid value for OSEE_TC_CORE3_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 243)
OSEE_ISR_ALIGN(_core3_, 3, 243)
#endif /* OSEE_TC_CORE3_243_ISR_CAT */
#if (defined(OSEE_TC_CORE3_244_ISR_CAT))
#if (OSEE_TC_CORE3_244_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_244_ISR_TID, 244)
#elif (OSEE_TC_CORE3_244_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_244_ISR_HND, 244)
#else
#error Invalid value for OSEE_TC_CORE3_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 244)
OSEE_ISR_ALIGN(_core3_, 3, 244)
#endif /* OSEE_TC_CORE3_244_ISR_CAT */
#if (defined(OSEE_TC_CORE3_245_ISR_CAT))
#if (OSEE_TC_CORE3_245_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_245_ISR_TID, 245)
#elif (OSEE_TC_CORE3_245_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_245_ISR_HND, 245)
#else
#error Invalid value for OSEE_TC_CORE3_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 245)
OSEE_ISR_ALIGN(_core3_, 3, 245)
#endif /* OSEE_TC_CORE3_245_ISR_CAT */
#if (defined(OSEE_TC_CORE3_246_ISR_CAT))
#if (OSEE_TC_CORE3_246_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_246_ISR_TID, 246)
#elif (OSEE_TC_CORE3_246_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_246_ISR_HND, 246)
#else
#error Invalid value for OSEE_TC_CORE3_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 246)
OSEE_ISR_ALIGN(_core3_, 3, 246)
#endif /* OSEE_TC_CORE3_246_ISR_CAT */
#if (defined(OSEE_TC_CORE3_247_ISR_CAT))
#if (OSEE_TC_CORE3_247_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_247_ISR_TID, 247)
#elif (OSEE_TC_CORE3_247_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_247_ISR_HND, 247)
#else
#error Invalid value for OSEE_TC_CORE3_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 247)
OSEE_ISR_ALIGN(_core3_, 3, 247)
#endif /* OSEE_TC_CORE3_247_ISR_CAT */
#if (defined(OSEE_TC_CORE3_248_ISR_CAT))
#if (OSEE_TC_CORE3_248_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_248_ISR_TID, 248)
#elif (OSEE_TC_CORE3_248_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_248_ISR_HND, 248)
#else
#error Invalid value for OSEE_TC_CORE3_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 248)
OSEE_ISR_ALIGN(_core3_, 3, 248)
#endif /* OSEE_TC_CORE3_248_ISR_CAT */
#if (defined(OSEE_TC_CORE3_249_ISR_CAT))
#if (OSEE_TC_CORE3_249_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_249_ISR_TID, 249)
#elif (OSEE_TC_CORE3_249_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_249_ISR_HND, 249)
#else
#error Invalid value for OSEE_TC_CORE3_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 249)
OSEE_ISR_ALIGN(_core3_, 3, 249)
#endif /* OSEE_TC_CORE3_249_ISR_CAT */
#if (defined(OSEE_TC_CORE3_250_ISR_CAT))
#if (OSEE_TC_CORE3_250_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_250_ISR_TID, 250)
#elif (OSEE_TC_CORE3_250_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_250_ISR_HND, 250)
#else
#error Invalid value for OSEE_TC_CORE3_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 250)
OSEE_ISR_ALIGN(_core3_, 3, 250)
#endif /* OSEE_TC_CORE3_250_ISR_CAT */
#if (defined(OSEE_TC_CORE3_251_ISR_CAT))
#if (OSEE_TC_CORE3_251_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_251_ISR_TID, 251)
#elif (OSEE_TC_CORE3_251_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_251_ISR_HND, 251)
#else
#error Invalid value for OSEE_TC_CORE3_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 251)
OSEE_ISR_ALIGN(_core3_, 3, 251)
#endif /* OSEE_TC_CORE3_251_ISR_CAT */
#if (defined(OSEE_TC_CORE3_252_ISR_CAT))
#if (OSEE_TC_CORE3_252_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_252_ISR_TID, 252)
#elif (OSEE_TC_CORE3_252_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_252_ISR_HND, 252)
#else
#error Invalid value for OSEE_TC_CORE3_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 252)
OSEE_ISR_ALIGN(_core3_, 3, 252)
#endif /* OSEE_TC_CORE3_252_ISR_CAT */
#if (defined(OSEE_TC_CORE3_253_ISR_CAT))
#if (OSEE_TC_CORE3_253_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_253_ISR_TID, 253)
#elif (OSEE_TC_CORE3_253_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_253_ISR_HND, 253)
#else
#error Invalid value for OSEE_TC_CORE3_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 253)
OSEE_ISR_ALIGN(_core3_, 3, 253)
#endif /* OSEE_TC_CORE3_253_ISR_CAT */
#if (defined(OSEE_TC_CORE3_254_ISR_CAT))
#if (OSEE_TC_CORE3_254_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_254_ISR_TID, 254)
#elif (OSEE_TC_CORE3_254_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_254_ISR_HND, 254)
#else
#error Invalid value for OSEE_TC_CORE3_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 254)
OSEE_ISR_ALIGN(_core3_, 3, 254)
#endif /* OSEE_TC_CORE3_254_ISR_CAT */
#if (defined(OSEE_TC_CORE3_255_ISR_CAT))
#if (OSEE_TC_CORE3_255_ISR_CAT == 2)
OSEE_ISR2_DEF(_core3_, 3, OSEE_TC_CORE3_255_ISR_TID, 255)
#elif (OSEE_TC_CORE3_255_ISR_CAT == 1)
OSEE_ISR1_DEF(_core3_, 3, OSEE_TC_CORE3_255_ISR_HND, 255)
#else
#error Invalid value for OSEE_TC_CORE3_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE3_ISR_MAX_PRIO >= 255)
OSEE_ISR_ALIGN(_core3_, 3, 255)
#endif /* OSEE_TC_CORE3_255_ISR_CAT */
#endif /* OSEE_TC_CORE3_ISR_MAX_PRIO */
#if (defined(__GNUC__))
__asm__ ("\t.size __INTTAB3, . - __INTTAB3\n\
\t.section .text,\"ax\",@progbits");
#endif /* __GNUC__ */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x08U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x10U)
#if (defined(__GNUC__))
__asm__ ("\n\
  .section .inttab_cpu4, \"ax\", @progbits\n\
  .globl __INTTAB4\n\
__INTTAB4:");
/* ERIKA's Interrupt Vector Definition */
#if (defined(OSEE_TC_CORE4_ISR_MAX_PRIO))
__asm__(
"  .skip 0x20");
#endif /* OSEE_TC_CORE4_ISR_MAX_PRIO */
#endif /* __GNUC__ */
#if (defined(OSEE_TC_CORE4_ISR_MAX_PRIO))
OSEE_ISR2_DEF(_core4_, 4, -1, 1)
#if (defined(OSEE_TC_CORE4_2_ISR_CAT))
#if (OSEE_TC_CORE4_2_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_2_ISR_TID, 2)
#elif (OSEE_TC_CORE4_2_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_2_ISR_HND, 2)
#else
#error Invalid value for OSEE_TC_CORE4_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 2)
OSEE_ISR_ALIGN(_core4_, 4, 2)
#endif /* OSEE_TC_CORE4_2_ISR_CAT */
#if (defined(OSEE_TC_CORE4_3_ISR_CAT))
#if (OSEE_TC_CORE4_3_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_3_ISR_TID, 3)
#elif (OSEE_TC_CORE4_3_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_3_ISR_HND, 3)
#else
#error Invalid value for OSEE_TC_CORE4_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 3)
OSEE_ISR_ALIGN(_core4_, 4, 3)
#endif /* OSEE_TC_CORE4_3_ISR_CAT */
#if (defined(OSEE_TC_CORE4_4_ISR_CAT))
#if (OSEE_TC_CORE4_4_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_4_ISR_TID, 4)
#elif (OSEE_TC_CORE4_4_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_4_ISR_HND, 4)
#else
#error Invalid value for OSEE_TC_CORE4_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 4)
OSEE_ISR_ALIGN(_core4_, 4, 4)
#endif /* OSEE_TC_CORE4_4_ISR_CAT */
#if (defined(OSEE_TC_CORE4_5_ISR_CAT))
#if (OSEE_TC_CORE4_5_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_5_ISR_TID, 5)
#elif (OSEE_TC_CORE4_5_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_5_ISR_HND, 5)
#else
#error Invalid value for OSEE_TC_CORE4_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 5)
OSEE_ISR_ALIGN(_core4_, 4, 5)
#endif /* OSEE_TC_CORE4_5_ISR_CAT */
#if (defined(OSEE_TC_CORE4_6_ISR_CAT))
#if (OSEE_TC_CORE4_6_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_6_ISR_TID, 6)
#elif (OSEE_TC_CORE4_6_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_6_ISR_HND, 6)
#else
#error Invalid value for OSEE_TC_CORE4_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 6)
OSEE_ISR_ALIGN(_core4_, 4, 6)
#endif /* OSEE_TC_CORE4_6_ISR_CAT */
#if (defined(OSEE_TC_CORE4_7_ISR_CAT))
#if (OSEE_TC_CORE4_7_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_7_ISR_TID, 7)
#elif (OSEE_TC_CORE4_7_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_7_ISR_HND, 7)
#else
#error Invalid value for OSEE_TC_CORE4_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 7)
OSEE_ISR_ALIGN(_core4_, 4, 7)
#endif /* OSEE_TC_CORE4_7_ISR_CAT */
#if (defined(OSEE_TC_CORE4_8_ISR_CAT))
#if (OSEE_TC_CORE4_8_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_8_ISR_TID, 8)
#elif (OSEE_TC_CORE4_8_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_8_ISR_HND, 8)
#else
#error Invalid value for OSEE_TC_CORE4_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 8)
OSEE_ISR_ALIGN(_core4_, 4, 8)
#endif /* OSEE_TC_CORE4_8_ISR_CAT */
#if (defined(OSEE_TC_CORE4_9_ISR_CAT))
#if (OSEE_TC_CORE4_9_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_9_ISR_TID, 9)
#elif (OSEE_TC_CORE4_9_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_9_ISR_HND, 9)
#else
#error Invalid value for OSEE_TC_CORE4_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 9)
OSEE_ISR_ALIGN(_core4_, 4, 9)
#endif /* OSEE_TC_CORE4_9_ISR_CAT */
#if (defined(OSEE_TC_CORE4_10_ISR_CAT))
#if (OSEE_TC_CORE4_10_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_10_ISR_TID, 10)
#elif (OSEE_TC_CORE4_10_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_10_ISR_HND, 10)
#else
#error Invalid value for OSEE_TC_CORE4_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 10)
OSEE_ISR_ALIGN(_core4_, 4, 10)
#endif /* OSEE_TC_CORE4_10_ISR_CAT */
#if (defined(OSEE_TC_CORE4_11_ISR_CAT))
#if (OSEE_TC_CORE4_11_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_11_ISR_TID, 11)
#elif (OSEE_TC_CORE4_11_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_11_ISR_HND, 11)
#else
#error Invalid value for OSEE_TC_CORE4_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 11)
OSEE_ISR_ALIGN(_core4_, 4, 11)
#endif /* OSEE_TC_CORE4_11_ISR_CAT */
#if (defined(OSEE_TC_CORE4_12_ISR_CAT))
#if (OSEE_TC_CORE4_12_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_12_ISR_TID, 12)
#elif (OSEE_TC_CORE4_12_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_12_ISR_HND, 12)
#else
#error Invalid value for OSEE_TC_CORE4_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 12)
OSEE_ISR_ALIGN(_core4_, 4, 12)
#endif /* OSEE_TC_CORE4_12_ISR_CAT */
#if (defined(OSEE_TC_CORE4_13_ISR_CAT))
#if (OSEE_TC_CORE4_13_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_13_ISR_TID, 13)
#elif (OSEE_TC_CORE4_13_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_13_ISR_HND, 13)
#else
#error Invalid value for OSEE_TC_CORE4_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 13)
OSEE_ISR_ALIGN(_core4_, 4, 13)
#endif /* OSEE_TC_CORE4_13_ISR_CAT */
#if (defined(OSEE_TC_CORE4_14_ISR_CAT))
#if (OSEE_TC_CORE4_14_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_14_ISR_TID, 14)
#elif (OSEE_TC_CORE4_14_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_14_ISR_HND, 14)
#else
#error Invalid value for OSEE_TC_CORE4_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 14)
OSEE_ISR_ALIGN(_core4_, 4, 14)
#endif /* OSEE_TC_CORE4_14_ISR_CAT */
#if (defined(OSEE_TC_CORE4_15_ISR_CAT))
#if (OSEE_TC_CORE4_15_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_15_ISR_TID, 15)
#elif (OSEE_TC_CORE4_15_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_15_ISR_HND, 15)
#else
#error Invalid value for OSEE_TC_CORE4_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 15)
OSEE_ISR_ALIGN(_core4_, 4, 15)
#endif /* OSEE_TC_CORE4_15_ISR_CAT */
#if (defined(OSEE_TC_CORE4_16_ISR_CAT))
#if (OSEE_TC_CORE4_16_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_16_ISR_TID, 16)
#elif (OSEE_TC_CORE4_16_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_16_ISR_HND, 16)
#else
#error Invalid value for OSEE_TC_CORE4_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 16)
OSEE_ISR_ALIGN(_core4_, 4, 16)
#endif /* OSEE_TC_CORE4_16_ISR_CAT */
#if (defined(OSEE_TC_CORE4_17_ISR_CAT))
#if (OSEE_TC_CORE4_17_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_17_ISR_TID, 17)
#elif (OSEE_TC_CORE4_17_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_17_ISR_HND, 17)
#else
#error Invalid value for OSEE_TC_CORE4_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 17)
OSEE_ISR_ALIGN(_core4_, 4, 17)
#endif /* OSEE_TC_CORE4_17_ISR_CAT */
#if (defined(OSEE_TC_CORE4_18_ISR_CAT))
#if (OSEE_TC_CORE4_18_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_18_ISR_TID, 18)
#elif (OSEE_TC_CORE4_18_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_18_ISR_HND, 18)
#else
#error Invalid value for OSEE_TC_CORE4_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 18)
OSEE_ISR_ALIGN(_core4_, 4, 18)
#endif /* OSEE_TC_CORE4_18_ISR_CAT */
#if (defined(OSEE_TC_CORE4_19_ISR_CAT))
#if (OSEE_TC_CORE4_19_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_19_ISR_TID, 19)
#elif (OSEE_TC_CORE4_19_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_19_ISR_HND, 19)
#else
#error Invalid value for OSEE_TC_CORE4_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 19)
OSEE_ISR_ALIGN(_core4_, 4, 19)
#endif /* OSEE_TC_CORE4_19_ISR_CAT */
#if (defined(OSEE_TC_CORE4_20_ISR_CAT))
#if (OSEE_TC_CORE4_20_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_20_ISR_TID, 20)
#elif (OSEE_TC_CORE4_20_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_20_ISR_HND, 20)
#else
#error Invalid value for OSEE_TC_CORE4_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 20)
OSEE_ISR_ALIGN(_core4_, 4, 20)
#endif /* OSEE_TC_CORE4_20_ISR_CAT */
#if (defined(OSEE_TC_CORE4_21_ISR_CAT))
#if (OSEE_TC_CORE4_21_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_21_ISR_TID, 21)
#elif (OSEE_TC_CORE4_21_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_21_ISR_HND, 21)
#else
#error Invalid value for OSEE_TC_CORE4_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 21)
OSEE_ISR_ALIGN(_core4_, 4, 21)
#endif /* OSEE_TC_CORE4_21_ISR_CAT */
#if (defined(OSEE_TC_CORE4_22_ISR_CAT))
#if (OSEE_TC_CORE4_22_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_22_ISR_TID, 22)
#elif (OSEE_TC_CORE4_22_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_22_ISR_HND, 22)
#else
#error Invalid value for OSEE_TC_CORE4_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 22)
OSEE_ISR_ALIGN(_core4_, 4, 22)
#endif /* OSEE_TC_CORE4_22_ISR_CAT */
#if (defined(OSEE_TC_CORE4_23_ISR_CAT))
#if (OSEE_TC_CORE4_23_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_23_ISR_TID, 23)
#elif (OSEE_TC_CORE4_23_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_23_ISR_HND, 23)
#else
#error Invalid value for OSEE_TC_CORE4_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 23)
OSEE_ISR_ALIGN(_core4_, 4, 23)
#endif /* OSEE_TC_CORE4_23_ISR_CAT */
#if (defined(OSEE_TC_CORE4_24_ISR_CAT))
#if (OSEE_TC_CORE4_24_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_24_ISR_TID, 24)
#elif (OSEE_TC_CORE4_24_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_24_ISR_HND, 24)
#else
#error Invalid value for OSEE_TC_CORE4_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 24)
OSEE_ISR_ALIGN(_core4_, 4, 24)
#endif /* OSEE_TC_CORE4_24_ISR_CAT */
#if (defined(OSEE_TC_CORE4_25_ISR_CAT))
#if (OSEE_TC_CORE4_25_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_25_ISR_TID, 25)
#elif (OSEE_TC_CORE4_25_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_25_ISR_HND, 25)
#else
#error Invalid value for OSEE_TC_CORE4_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 25)
OSEE_ISR_ALIGN(_core4_, 4, 25)
#endif /* OSEE_TC_CORE4_25_ISR_CAT */
#if (defined(OSEE_TC_CORE4_26_ISR_CAT))
#if (OSEE_TC_CORE4_26_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_26_ISR_TID, 26)
#elif (OSEE_TC_CORE4_26_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_26_ISR_HND, 26)
#else
#error Invalid value for OSEE_TC_CORE4_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 26)
OSEE_ISR_ALIGN(_core4_, 4, 26)
#endif /* OSEE_TC_CORE4_26_ISR_CAT */
#if (defined(OSEE_TC_CORE4_27_ISR_CAT))
#if (OSEE_TC_CORE4_27_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_27_ISR_TID, 27)
#elif (OSEE_TC_CORE4_27_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_27_ISR_HND, 27)
#else
#error Invalid value for OSEE_TC_CORE4_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 27)
OSEE_ISR_ALIGN(_core4_, 4, 27)
#endif /* OSEE_TC_CORE4_27_ISR_CAT */
#if (defined(OSEE_TC_CORE4_28_ISR_CAT))
#if (OSEE_TC_CORE4_28_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_28_ISR_TID, 28)
#elif (OSEE_TC_CORE4_28_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_28_ISR_HND, 28)
#else
#error Invalid value for OSEE_TC_CORE4_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 28)
OSEE_ISR_ALIGN(_core4_, 4, 28)
#endif /* OSEE_TC_CORE4_28_ISR_CAT */
#if (defined(OSEE_TC_CORE4_29_ISR_CAT))
#if (OSEE_TC_CORE4_29_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_29_ISR_TID, 29)
#elif (OSEE_TC_CORE4_29_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_29_ISR_HND, 29)
#else
#error Invalid value for OSEE_TC_CORE4_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 29)
OSEE_ISR_ALIGN(_core4_, 4, 29)
#endif /* OSEE_TC_CORE4_29_ISR_CAT */
#if (defined(OSEE_TC_CORE4_30_ISR_CAT))
#if (OSEE_TC_CORE4_30_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_30_ISR_TID, 30)
#elif (OSEE_TC_CORE4_30_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_30_ISR_HND, 30)
#else
#error Invalid value for OSEE_TC_CORE4_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 30)
OSEE_ISR_ALIGN(_core4_, 4, 30)
#endif /* OSEE_TC_CORE4_30_ISR_CAT */
#if (defined(OSEE_TC_CORE4_31_ISR_CAT))
#if (OSEE_TC_CORE4_31_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_31_ISR_TID, 31)
#elif (OSEE_TC_CORE4_31_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_31_ISR_HND, 31)
#else
#error Invalid value for OSEE_TC_CORE4_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 31)
OSEE_ISR_ALIGN(_core4_, 4, 31)
#endif /* OSEE_TC_CORE4_31_ISR_CAT */
#if (defined(OSEE_TC_CORE4_32_ISR_CAT))
#if (OSEE_TC_CORE4_32_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_32_ISR_TID, 32)
#elif (OSEE_TC_CORE4_32_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_32_ISR_HND, 32)
#else
#error Invalid value for OSEE_TC_CORE4_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 32)
OSEE_ISR_ALIGN(_core4_, 4, 32)
#endif /* OSEE_TC_CORE4_32_ISR_CAT */
#if (defined(OSEE_TC_CORE4_33_ISR_CAT))
#if (OSEE_TC_CORE4_33_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_33_ISR_TID, 33)
#elif (OSEE_TC_CORE4_33_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_33_ISR_HND, 33)
#else
#error Invalid value for OSEE_TC_CORE4_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 33)
OSEE_ISR_ALIGN(_core4_, 4, 33)
#endif /* OSEE_TC_CORE4_33_ISR_CAT */
#if (defined(OSEE_TC_CORE4_34_ISR_CAT))
#if (OSEE_TC_CORE4_34_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_34_ISR_TID, 34)
#elif (OSEE_TC_CORE4_34_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_34_ISR_HND, 34)
#else
#error Invalid value for OSEE_TC_CORE4_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 34)
OSEE_ISR_ALIGN(_core4_, 4, 34)
#endif /* OSEE_TC_CORE4_34_ISR_CAT */
#if (defined(OSEE_TC_CORE4_35_ISR_CAT))
#if (OSEE_TC_CORE4_35_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_35_ISR_TID, 35)
#elif (OSEE_TC_CORE4_35_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_35_ISR_HND, 35)
#else
#error Invalid value for OSEE_TC_CORE4_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 35)
OSEE_ISR_ALIGN(_core4_, 4, 35)
#endif /* OSEE_TC_CORE4_35_ISR_CAT */
#if (defined(OSEE_TC_CORE4_36_ISR_CAT))
#if (OSEE_TC_CORE4_36_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_36_ISR_TID, 36)
#elif (OSEE_TC_CORE4_36_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_36_ISR_HND, 36)
#else
#error Invalid value for OSEE_TC_CORE4_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 36)
OSEE_ISR_ALIGN(_core4_, 4, 36)
#endif /* OSEE_TC_CORE4_36_ISR_CAT */
#if (defined(OSEE_TC_CORE4_37_ISR_CAT))
#if (OSEE_TC_CORE4_37_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_37_ISR_TID, 37)
#elif (OSEE_TC_CORE4_37_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_37_ISR_HND, 37)
#else
#error Invalid value for OSEE_TC_CORE4_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 37)
OSEE_ISR_ALIGN(_core4_, 4, 37)
#endif /* OSEE_TC_CORE4_37_ISR_CAT */
#if (defined(OSEE_TC_CORE4_38_ISR_CAT))
#if (OSEE_TC_CORE4_38_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_38_ISR_TID, 38)
#elif (OSEE_TC_CORE4_38_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_38_ISR_HND, 38)
#else
#error Invalid value for OSEE_TC_CORE4_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 38)
OSEE_ISR_ALIGN(_core4_, 4, 38)
#endif /* OSEE_TC_CORE4_38_ISR_CAT */
#if (defined(OSEE_TC_CORE4_39_ISR_CAT))
#if (OSEE_TC_CORE4_39_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_39_ISR_TID, 39)
#elif (OSEE_TC_CORE4_39_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_39_ISR_HND, 39)
#else
#error Invalid value for OSEE_TC_CORE4_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 39)
OSEE_ISR_ALIGN(_core4_, 4, 39)
#endif /* OSEE_TC_CORE4_39_ISR_CAT */
#if (defined(OSEE_TC_CORE4_40_ISR_CAT))
#if (OSEE_TC_CORE4_40_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_40_ISR_TID, 40)
#elif (OSEE_TC_CORE4_40_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_40_ISR_HND, 40)
#else
#error Invalid value for OSEE_TC_CORE4_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 40)
OSEE_ISR_ALIGN(_core4_, 4, 40)
#endif /* OSEE_TC_CORE4_40_ISR_CAT */
#if (defined(OSEE_TC_CORE4_41_ISR_CAT))
#if (OSEE_TC_CORE4_41_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_41_ISR_TID, 41)
#elif (OSEE_TC_CORE4_41_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_41_ISR_HND, 41)
#else
#error Invalid value for OSEE_TC_CORE4_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 41)
OSEE_ISR_ALIGN(_core4_, 4, 41)
#endif /* OSEE_TC_CORE4_41_ISR_CAT */
#if (defined(OSEE_TC_CORE4_42_ISR_CAT))
#if (OSEE_TC_CORE4_42_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_42_ISR_TID, 42)
#elif (OSEE_TC_CORE4_42_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_42_ISR_HND, 42)
#else
#error Invalid value for OSEE_TC_CORE4_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 42)
OSEE_ISR_ALIGN(_core4_, 4, 42)
#endif /* OSEE_TC_CORE4_42_ISR_CAT */
#if (defined(OSEE_TC_CORE4_43_ISR_CAT))
#if (OSEE_TC_CORE4_43_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_43_ISR_TID, 43)
#elif (OSEE_TC_CORE4_43_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_43_ISR_HND, 43)
#else
#error Invalid value for OSEE_TC_CORE4_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 43)
OSEE_ISR_ALIGN(_core4_, 4, 43)
#endif /* OSEE_TC_CORE4_43_ISR_CAT */
#if (defined(OSEE_TC_CORE4_44_ISR_CAT))
#if (OSEE_TC_CORE4_44_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_44_ISR_TID, 44)
#elif (OSEE_TC_CORE4_44_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_44_ISR_HND, 44)
#else
#error Invalid value for OSEE_TC_CORE4_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 44)
OSEE_ISR_ALIGN(_core4_, 4, 44)
#endif /* OSEE_TC_CORE4_44_ISR_CAT */
#if (defined(OSEE_TC_CORE4_45_ISR_CAT))
#if (OSEE_TC_CORE4_45_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_45_ISR_TID, 45)
#elif (OSEE_TC_CORE4_45_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_45_ISR_HND, 45)
#else
#error Invalid value for OSEE_TC_CORE4_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 45)
OSEE_ISR_ALIGN(_core4_, 4, 45)
#endif /* OSEE_TC_CORE4_45_ISR_CAT */
#if (defined(OSEE_TC_CORE4_46_ISR_CAT))
#if (OSEE_TC_CORE4_46_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_46_ISR_TID, 46)
#elif (OSEE_TC_CORE4_46_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_46_ISR_HND, 46)
#else
#error Invalid value for OSEE_TC_CORE4_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 46)
OSEE_ISR_ALIGN(_core4_, 4, 46)
#endif /* OSEE_TC_CORE4_46_ISR_CAT */
#if (defined(OSEE_TC_CORE4_47_ISR_CAT))
#if (OSEE_TC_CORE4_47_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_47_ISR_TID, 47)
#elif (OSEE_TC_CORE4_47_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_47_ISR_HND, 47)
#else
#error Invalid value for OSEE_TC_CORE4_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 47)
OSEE_ISR_ALIGN(_core4_, 4, 47)
#endif /* OSEE_TC_CORE4_47_ISR_CAT */
#if (defined(OSEE_TC_CORE4_48_ISR_CAT))
#if (OSEE_TC_CORE4_48_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_48_ISR_TID, 48)
#elif (OSEE_TC_CORE4_48_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_48_ISR_HND, 48)
#else
#error Invalid value for OSEE_TC_CORE4_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 48)
OSEE_ISR_ALIGN(_core4_, 4, 48)
#endif /* OSEE_TC_CORE4_48_ISR_CAT */
#if (defined(OSEE_TC_CORE4_49_ISR_CAT))
#if (OSEE_TC_CORE4_49_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_49_ISR_TID, 49)
#elif (OSEE_TC_CORE4_49_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_49_ISR_HND, 49)
#else
#error Invalid value for OSEE_TC_CORE4_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 49)
OSEE_ISR_ALIGN(_core4_, 4, 49)
#endif /* OSEE_TC_CORE4_49_ISR_CAT */
#if (defined(OSEE_TC_CORE4_50_ISR_CAT))
#if (OSEE_TC_CORE4_50_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_50_ISR_TID, 50)
#elif (OSEE_TC_CORE4_50_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_50_ISR_HND, 50)
#else
#error Invalid value for OSEE_TC_CORE4_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 50)
OSEE_ISR_ALIGN(_core4_, 4, 50)
#endif /* OSEE_TC_CORE4_50_ISR_CAT */
#if (defined(OSEE_TC_CORE4_51_ISR_CAT))
#if (OSEE_TC_CORE4_51_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_51_ISR_TID, 51)
#elif (OSEE_TC_CORE4_51_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_51_ISR_HND, 51)
#else
#error Invalid value for OSEE_TC_CORE4_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 51)
OSEE_ISR_ALIGN(_core4_, 4, 51)
#endif /* OSEE_TC_CORE4_51_ISR_CAT */
#if (defined(OSEE_TC_CORE4_52_ISR_CAT))
#if (OSEE_TC_CORE4_52_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_52_ISR_TID, 52)
#elif (OSEE_TC_CORE4_52_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_52_ISR_HND, 52)
#else
#error Invalid value for OSEE_TC_CORE4_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 52)
OSEE_ISR_ALIGN(_core4_, 4, 52)
#endif /* OSEE_TC_CORE4_52_ISR_CAT */
#if (defined(OSEE_TC_CORE4_53_ISR_CAT))
#if (OSEE_TC_CORE4_53_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_53_ISR_TID, 53)
#elif (OSEE_TC_CORE4_53_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_53_ISR_HND, 53)
#else
#error Invalid value for OSEE_TC_CORE4_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 53)
OSEE_ISR_ALIGN(_core4_, 4, 53)
#endif /* OSEE_TC_CORE4_53_ISR_CAT */
#if (defined(OSEE_TC_CORE4_54_ISR_CAT))
#if (OSEE_TC_CORE4_54_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_54_ISR_TID, 54)
#elif (OSEE_TC_CORE4_54_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_54_ISR_HND, 54)
#else
#error Invalid value for OSEE_TC_CORE4_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 54)
OSEE_ISR_ALIGN(_core4_, 4, 54)
#endif /* OSEE_TC_CORE4_54_ISR_CAT */
#if (defined(OSEE_TC_CORE4_55_ISR_CAT))
#if (OSEE_TC_CORE4_55_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_55_ISR_TID, 55)
#elif (OSEE_TC_CORE4_55_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_55_ISR_HND, 55)
#else
#error Invalid value for OSEE_TC_CORE4_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 55)
OSEE_ISR_ALIGN(_core4_, 4, 55)
#endif /* OSEE_TC_CORE4_55_ISR_CAT */
#if (defined(OSEE_TC_CORE4_56_ISR_CAT))
#if (OSEE_TC_CORE4_56_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_56_ISR_TID, 56)
#elif (OSEE_TC_CORE4_56_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_56_ISR_HND, 56)
#else
#error Invalid value for OSEE_TC_CORE4_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 56)
OSEE_ISR_ALIGN(_core4_, 4, 56)
#endif /* OSEE_TC_CORE4_56_ISR_CAT */
#if (defined(OSEE_TC_CORE4_57_ISR_CAT))
#if (OSEE_TC_CORE4_57_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_57_ISR_TID, 57)
#elif (OSEE_TC_CORE4_57_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_57_ISR_HND, 57)
#else
#error Invalid value for OSEE_TC_CORE4_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 57)
OSEE_ISR_ALIGN(_core4_, 4, 57)
#endif /* OSEE_TC_CORE4_57_ISR_CAT */
#if (defined(OSEE_TC_CORE4_58_ISR_CAT))
#if (OSEE_TC_CORE4_58_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_58_ISR_TID, 58)
#elif (OSEE_TC_CORE4_58_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_58_ISR_HND, 58)
#else
#error Invalid value for OSEE_TC_CORE4_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 58)
OSEE_ISR_ALIGN(_core4_, 4, 58)
#endif /* OSEE_TC_CORE4_58_ISR_CAT */
#if (defined(OSEE_TC_CORE4_59_ISR_CAT))
#if (OSEE_TC_CORE4_59_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_59_ISR_TID, 59)
#elif (OSEE_TC_CORE4_59_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_59_ISR_HND, 59)
#else
#error Invalid value for OSEE_TC_CORE4_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 59)
OSEE_ISR_ALIGN(_core4_, 4, 59)
#endif /* OSEE_TC_CORE4_59_ISR_CAT */
#if (defined(OSEE_TC_CORE4_60_ISR_CAT))
#if (OSEE_TC_CORE4_60_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_60_ISR_TID, 60)
#elif (OSEE_TC_CORE4_60_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_60_ISR_HND, 60)
#else
#error Invalid value for OSEE_TC_CORE4_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 60)
OSEE_ISR_ALIGN(_core4_, 4, 60)
#endif /* OSEE_TC_CORE4_60_ISR_CAT */
#if (defined(OSEE_TC_CORE4_61_ISR_CAT))
#if (OSEE_TC_CORE4_61_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_61_ISR_TID, 61)
#elif (OSEE_TC_CORE4_61_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_61_ISR_HND, 61)
#else
#error Invalid value for OSEE_TC_CORE4_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 61)
OSEE_ISR_ALIGN(_core4_, 4, 61)
#endif /* OSEE_TC_CORE4_61_ISR_CAT */
#if (defined(OSEE_TC_CORE4_62_ISR_CAT))
#if (OSEE_TC_CORE4_62_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_62_ISR_TID, 62)
#elif (OSEE_TC_CORE4_62_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_62_ISR_HND, 62)
#else
#error Invalid value for OSEE_TC_CORE4_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 62)
OSEE_ISR_ALIGN(_core4_, 4, 62)
#endif /* OSEE_TC_CORE4_62_ISR_CAT */
#if (defined(OSEE_TC_CORE4_63_ISR_CAT))
#if (OSEE_TC_CORE4_63_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_63_ISR_TID, 63)
#elif (OSEE_TC_CORE4_63_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_63_ISR_HND, 63)
#else
#error Invalid value for OSEE_TC_CORE4_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 63)
OSEE_ISR_ALIGN(_core4_, 4, 63)
#endif /* OSEE_TC_CORE4_63_ISR_CAT */
#if (defined(OSEE_TC_CORE4_64_ISR_CAT))
#if (OSEE_TC_CORE4_64_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_64_ISR_TID, 64)
#elif (OSEE_TC_CORE4_64_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_64_ISR_HND, 64)
#else
#error Invalid value for OSEE_TC_CORE4_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 64)
OSEE_ISR_ALIGN(_core4_, 4, 64)
#endif /* OSEE_TC_CORE4_64_ISR_CAT */
#if (defined(OSEE_TC_CORE4_65_ISR_CAT))
#if (OSEE_TC_CORE4_65_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_65_ISR_TID, 65)
#elif (OSEE_TC_CORE4_65_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_65_ISR_HND, 65)
#else
#error Invalid value for OSEE_TC_CORE4_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 65)
OSEE_ISR_ALIGN(_core4_, 4, 65)
#endif /* OSEE_TC_CORE4_65_ISR_CAT */
#if (defined(OSEE_TC_CORE4_66_ISR_CAT))
#if (OSEE_TC_CORE4_66_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_66_ISR_TID, 66)
#elif (OSEE_TC_CORE4_66_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_66_ISR_HND, 66)
#else
#error Invalid value for OSEE_TC_CORE4_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 66)
OSEE_ISR_ALIGN(_core4_, 4, 66)
#endif /* OSEE_TC_CORE4_66_ISR_CAT */
#if (defined(OSEE_TC_CORE4_67_ISR_CAT))
#if (OSEE_TC_CORE4_67_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_67_ISR_TID, 67)
#elif (OSEE_TC_CORE4_67_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_67_ISR_HND, 67)
#else
#error Invalid value for OSEE_TC_CORE4_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 67)
OSEE_ISR_ALIGN(_core4_, 4, 67)
#endif /* OSEE_TC_CORE4_67_ISR_CAT */
#if (defined(OSEE_TC_CORE4_68_ISR_CAT))
#if (OSEE_TC_CORE4_68_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_68_ISR_TID, 68)
#elif (OSEE_TC_CORE4_68_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_68_ISR_HND, 68)
#else
#error Invalid value for OSEE_TC_CORE4_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 68)
OSEE_ISR_ALIGN(_core4_, 4, 68)
#endif /* OSEE_TC_CORE4_68_ISR_CAT */
#if (defined(OSEE_TC_CORE4_69_ISR_CAT))
#if (OSEE_TC_CORE4_69_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_69_ISR_TID, 69)
#elif (OSEE_TC_CORE4_69_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_69_ISR_HND, 69)
#else
#error Invalid value for OSEE_TC_CORE4_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 69)
OSEE_ISR_ALIGN(_core4_, 4, 69)
#endif /* OSEE_TC_CORE4_69_ISR_CAT */
#if (defined(OSEE_TC_CORE4_70_ISR_CAT))
#if (OSEE_TC_CORE4_70_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_70_ISR_TID, 70)
#elif (OSEE_TC_CORE4_70_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_70_ISR_HND, 70)
#else
#error Invalid value for OSEE_TC_CORE4_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 70)
OSEE_ISR_ALIGN(_core4_, 4, 70)
#endif /* OSEE_TC_CORE4_70_ISR_CAT */
#if (defined(OSEE_TC_CORE4_71_ISR_CAT))
#if (OSEE_TC_CORE4_71_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_71_ISR_TID, 71)
#elif (OSEE_TC_CORE4_71_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_71_ISR_HND, 71)
#else
#error Invalid value for OSEE_TC_CORE4_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 71)
OSEE_ISR_ALIGN(_core4_, 4, 71)
#endif /* OSEE_TC_CORE4_71_ISR_CAT */
#if (defined(OSEE_TC_CORE4_72_ISR_CAT))
#if (OSEE_TC_CORE4_72_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_72_ISR_TID, 72)
#elif (OSEE_TC_CORE4_72_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_72_ISR_HND, 72)
#else
#error Invalid value for OSEE_TC_CORE4_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 72)
OSEE_ISR_ALIGN(_core4_, 4, 72)
#endif /* OSEE_TC_CORE4_72_ISR_CAT */
#if (defined(OSEE_TC_CORE4_73_ISR_CAT))
#if (OSEE_TC_CORE4_73_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_73_ISR_TID, 73)
#elif (OSEE_TC_CORE4_73_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_73_ISR_HND, 73)
#else
#error Invalid value for OSEE_TC_CORE4_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 73)
OSEE_ISR_ALIGN(_core4_, 4, 73)
#endif /* OSEE_TC_CORE4_73_ISR_CAT */
#if (defined(OSEE_TC_CORE4_74_ISR_CAT))
#if (OSEE_TC_CORE4_74_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_74_ISR_TID, 74)
#elif (OSEE_TC_CORE4_74_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_74_ISR_HND, 74)
#else
#error Invalid value for OSEE_TC_CORE4_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 74)
OSEE_ISR_ALIGN(_core4_, 4, 74)
#endif /* OSEE_TC_CORE4_74_ISR_CAT */
#if (defined(OSEE_TC_CORE4_75_ISR_CAT))
#if (OSEE_TC_CORE4_75_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_75_ISR_TID, 75)
#elif (OSEE_TC_CORE4_75_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_75_ISR_HND, 75)
#else
#error Invalid value for OSEE_TC_CORE4_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 75)
OSEE_ISR_ALIGN(_core4_, 4, 75)
#endif /* OSEE_TC_CORE4_75_ISR_CAT */
#if (defined(OSEE_TC_CORE4_76_ISR_CAT))
#if (OSEE_TC_CORE4_76_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_76_ISR_TID, 76)
#elif (OSEE_TC_CORE4_76_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_76_ISR_HND, 76)
#else
#error Invalid value for OSEE_TC_CORE4_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 76)
OSEE_ISR_ALIGN(_core4_, 4, 76)
#endif /* OSEE_TC_CORE4_76_ISR_CAT */
#if (defined(OSEE_TC_CORE4_77_ISR_CAT))
#if (OSEE_TC_CORE4_77_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_77_ISR_TID, 77)
#elif (OSEE_TC_CORE4_77_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_77_ISR_HND, 77)
#else
#error Invalid value for OSEE_TC_CORE4_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 77)
OSEE_ISR_ALIGN(_core4_, 4, 77)
#endif /* OSEE_TC_CORE4_77_ISR_CAT */
#if (defined(OSEE_TC_CORE4_78_ISR_CAT))
#if (OSEE_TC_CORE4_78_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_78_ISR_TID, 78)
#elif (OSEE_TC_CORE4_78_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_78_ISR_HND, 78)
#else
#error Invalid value for OSEE_TC_CORE4_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 78)
OSEE_ISR_ALIGN(_core4_, 4, 78)
#endif /* OSEE_TC_CORE4_78_ISR_CAT */
#if (defined(OSEE_TC_CORE4_79_ISR_CAT))
#if (OSEE_TC_CORE4_79_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_79_ISR_TID, 79)
#elif (OSEE_TC_CORE4_79_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_79_ISR_HND, 79)
#else
#error Invalid value for OSEE_TC_CORE4_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 79)
OSEE_ISR_ALIGN(_core4_, 4, 79)
#endif /* OSEE_TC_CORE4_79_ISR_CAT */
#if (defined(OSEE_TC_CORE4_80_ISR_CAT))
#if (OSEE_TC_CORE4_80_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_80_ISR_TID, 80)
#elif (OSEE_TC_CORE4_80_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_80_ISR_HND, 80)
#else
#error Invalid value for OSEE_TC_CORE4_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 80)
OSEE_ISR_ALIGN(_core4_, 4, 80)
#endif /* OSEE_TC_CORE4_80_ISR_CAT */
#if (defined(OSEE_TC_CORE4_81_ISR_CAT))
#if (OSEE_TC_CORE4_81_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_81_ISR_TID, 81)
#elif (OSEE_TC_CORE4_81_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_81_ISR_HND, 81)
#else
#error Invalid value for OSEE_TC_CORE4_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 81)
OSEE_ISR_ALIGN(_core4_, 4, 81)
#endif /* OSEE_TC_CORE4_81_ISR_CAT */
#if (defined(OSEE_TC_CORE4_82_ISR_CAT))
#if (OSEE_TC_CORE4_82_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_82_ISR_TID, 82)
#elif (OSEE_TC_CORE4_82_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_82_ISR_HND, 82)
#else
#error Invalid value for OSEE_TC_CORE4_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 82)
OSEE_ISR_ALIGN(_core4_, 4, 82)
#endif /* OSEE_TC_CORE4_82_ISR_CAT */
#if (defined(OSEE_TC_CORE4_83_ISR_CAT))
#if (OSEE_TC_CORE4_83_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_83_ISR_TID, 83)
#elif (OSEE_TC_CORE4_83_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_83_ISR_HND, 83)
#else
#error Invalid value for OSEE_TC_CORE4_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 83)
OSEE_ISR_ALIGN(_core4_, 4, 83)
#endif /* OSEE_TC_CORE4_83_ISR_CAT */
#if (defined(OSEE_TC_CORE4_84_ISR_CAT))
#if (OSEE_TC_CORE4_84_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_84_ISR_TID, 84)
#elif (OSEE_TC_CORE4_84_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_84_ISR_HND, 84)
#else
#error Invalid value for OSEE_TC_CORE4_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 84)
OSEE_ISR_ALIGN(_core4_, 4, 84)
#endif /* OSEE_TC_CORE4_84_ISR_CAT */
#if (defined(OSEE_TC_CORE4_85_ISR_CAT))
#if (OSEE_TC_CORE4_85_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_85_ISR_TID, 85)
#elif (OSEE_TC_CORE4_85_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_85_ISR_HND, 85)
#else
#error Invalid value for OSEE_TC_CORE4_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 85)
OSEE_ISR_ALIGN(_core4_, 4, 85)
#endif /* OSEE_TC_CORE4_85_ISR_CAT */
#if (defined(OSEE_TC_CORE4_86_ISR_CAT))
#if (OSEE_TC_CORE4_86_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_86_ISR_TID, 86)
#elif (OSEE_TC_CORE4_86_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_86_ISR_HND, 86)
#else
#error Invalid value for OSEE_TC_CORE4_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 86)
OSEE_ISR_ALIGN(_core4_, 4, 86)
#endif /* OSEE_TC_CORE4_86_ISR_CAT */
#if (defined(OSEE_TC_CORE4_87_ISR_CAT))
#if (OSEE_TC_CORE4_87_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_87_ISR_TID, 87)
#elif (OSEE_TC_CORE4_87_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_87_ISR_HND, 87)
#else
#error Invalid value for OSEE_TC_CORE4_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 87)
OSEE_ISR_ALIGN(_core4_, 4, 87)
#endif /* OSEE_TC_CORE4_87_ISR_CAT */
#if (defined(OSEE_TC_CORE4_88_ISR_CAT))
#if (OSEE_TC_CORE4_88_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_88_ISR_TID, 88)
#elif (OSEE_TC_CORE4_88_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_88_ISR_HND, 88)
#else
#error Invalid value for OSEE_TC_CORE4_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 88)
OSEE_ISR_ALIGN(_core4_, 4, 88)
#endif /* OSEE_TC_CORE4_88_ISR_CAT */
#if (defined(OSEE_TC_CORE4_89_ISR_CAT))
#if (OSEE_TC_CORE4_89_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_89_ISR_TID, 89)
#elif (OSEE_TC_CORE4_89_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_89_ISR_HND, 89)
#else
#error Invalid value for OSEE_TC_CORE4_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 89)
OSEE_ISR_ALIGN(_core4_, 4, 89)
#endif /* OSEE_TC_CORE4_89_ISR_CAT */
#if (defined(OSEE_TC_CORE4_90_ISR_CAT))
#if (OSEE_TC_CORE4_90_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_90_ISR_TID, 90)
#elif (OSEE_TC_CORE4_90_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_90_ISR_HND, 90)
#else
#error Invalid value for OSEE_TC_CORE4_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 90)
OSEE_ISR_ALIGN(_core4_, 4, 90)
#endif /* OSEE_TC_CORE4_90_ISR_CAT */
#if (defined(OSEE_TC_CORE4_91_ISR_CAT))
#if (OSEE_TC_CORE4_91_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_91_ISR_TID, 91)
#elif (OSEE_TC_CORE4_91_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_91_ISR_HND, 91)
#else
#error Invalid value for OSEE_TC_CORE4_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 91)
OSEE_ISR_ALIGN(_core4_, 4, 91)
#endif /* OSEE_TC_CORE4_91_ISR_CAT */
#if (defined(OSEE_TC_CORE4_92_ISR_CAT))
#if (OSEE_TC_CORE4_92_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_92_ISR_TID, 92)
#elif (OSEE_TC_CORE4_92_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_92_ISR_HND, 92)
#else
#error Invalid value for OSEE_TC_CORE4_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 92)
OSEE_ISR_ALIGN(_core4_, 4, 92)
#endif /* OSEE_TC_CORE4_92_ISR_CAT */
#if (defined(OSEE_TC_CORE4_93_ISR_CAT))
#if (OSEE_TC_CORE4_93_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_93_ISR_TID, 93)
#elif (OSEE_TC_CORE4_93_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_93_ISR_HND, 93)
#else
#error Invalid value for OSEE_TC_CORE4_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 93)
OSEE_ISR_ALIGN(_core4_, 4, 93)
#endif /* OSEE_TC_CORE4_93_ISR_CAT */
#if (defined(OSEE_TC_CORE4_94_ISR_CAT))
#if (OSEE_TC_CORE4_94_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_94_ISR_TID, 94)
#elif (OSEE_TC_CORE4_94_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_94_ISR_HND, 94)
#else
#error Invalid value for OSEE_TC_CORE4_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 94)
OSEE_ISR_ALIGN(_core4_, 4, 94)
#endif /* OSEE_TC_CORE4_94_ISR_CAT */
#if (defined(OSEE_TC_CORE4_95_ISR_CAT))
#if (OSEE_TC_CORE4_95_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_95_ISR_TID, 95)
#elif (OSEE_TC_CORE4_95_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_95_ISR_HND, 95)
#else
#error Invalid value for OSEE_TC_CORE4_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 95)
OSEE_ISR_ALIGN(_core4_, 4, 95)
#endif /* OSEE_TC_CORE4_95_ISR_CAT */
#if (defined(OSEE_TC_CORE4_96_ISR_CAT))
#if (OSEE_TC_CORE4_96_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_96_ISR_TID, 96)
#elif (OSEE_TC_CORE4_96_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_96_ISR_HND, 96)
#else
#error Invalid value for OSEE_TC_CORE4_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 96)
OSEE_ISR_ALIGN(_core4_, 4, 96)
#endif /* OSEE_TC_CORE4_96_ISR_CAT */
#if (defined(OSEE_TC_CORE4_97_ISR_CAT))
#if (OSEE_TC_CORE4_97_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_97_ISR_TID, 97)
#elif (OSEE_TC_CORE4_97_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_97_ISR_HND, 97)
#else
#error Invalid value for OSEE_TC_CORE4_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 97)
OSEE_ISR_ALIGN(_core4_, 4, 97)
#endif /* OSEE_TC_CORE4_97_ISR_CAT */
#if (defined(OSEE_TC_CORE4_98_ISR_CAT))
#if (OSEE_TC_CORE4_98_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_98_ISR_TID, 98)
#elif (OSEE_TC_CORE4_98_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_98_ISR_HND, 98)
#else
#error Invalid value for OSEE_TC_CORE4_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 98)
OSEE_ISR_ALIGN(_core4_, 4, 98)
#endif /* OSEE_TC_CORE4_98_ISR_CAT */
#if (defined(OSEE_TC_CORE4_99_ISR_CAT))
#if (OSEE_TC_CORE4_99_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_99_ISR_TID, 99)
#elif (OSEE_TC_CORE4_99_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_99_ISR_HND, 99)
#else
#error Invalid value for OSEE_TC_CORE4_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 99)
OSEE_ISR_ALIGN(_core4_, 4, 99)
#endif /* OSEE_TC_CORE4_99_ISR_CAT */
#if (defined(OSEE_TC_CORE4_100_ISR_CAT))
#if (OSEE_TC_CORE4_100_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_100_ISR_TID, 100)
#elif (OSEE_TC_CORE4_100_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_100_ISR_HND, 100)
#else
#error Invalid value for OSEE_TC_CORE4_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 100)
OSEE_ISR_ALIGN(_core4_, 4, 100)
#endif /* OSEE_TC_CORE4_100_ISR_CAT */
#if (defined(OSEE_TC_CORE4_101_ISR_CAT))
#if (OSEE_TC_CORE4_101_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_101_ISR_TID, 101)
#elif (OSEE_TC_CORE4_101_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_101_ISR_HND, 101)
#else
#error Invalid value for OSEE_TC_CORE4_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 101)
OSEE_ISR_ALIGN(_core4_, 4, 101)
#endif /* OSEE_TC_CORE4_101_ISR_CAT */
#if (defined(OSEE_TC_CORE4_102_ISR_CAT))
#if (OSEE_TC_CORE4_102_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_102_ISR_TID, 102)
#elif (OSEE_TC_CORE4_102_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_102_ISR_HND, 102)
#else
#error Invalid value for OSEE_TC_CORE4_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 102)
OSEE_ISR_ALIGN(_core4_, 4, 102)
#endif /* OSEE_TC_CORE4_102_ISR_CAT */
#if (defined(OSEE_TC_CORE4_103_ISR_CAT))
#if (OSEE_TC_CORE4_103_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_103_ISR_TID, 103)
#elif (OSEE_TC_CORE4_103_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_103_ISR_HND, 103)
#else
#error Invalid value for OSEE_TC_CORE4_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 103)
OSEE_ISR_ALIGN(_core4_, 4, 103)
#endif /* OSEE_TC_CORE4_103_ISR_CAT */
#if (defined(OSEE_TC_CORE4_104_ISR_CAT))
#if (OSEE_TC_CORE4_104_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_104_ISR_TID, 104)
#elif (OSEE_TC_CORE4_104_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_104_ISR_HND, 104)
#else
#error Invalid value for OSEE_TC_CORE4_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 104)
OSEE_ISR_ALIGN(_core4_, 4, 104)
#endif /* OSEE_TC_CORE4_104_ISR_CAT */
#if (defined(OSEE_TC_CORE4_105_ISR_CAT))
#if (OSEE_TC_CORE4_105_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_105_ISR_TID, 105)
#elif (OSEE_TC_CORE4_105_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_105_ISR_HND, 105)
#else
#error Invalid value for OSEE_TC_CORE4_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 105)
OSEE_ISR_ALIGN(_core4_, 4, 105)
#endif /* OSEE_TC_CORE4_105_ISR_CAT */
#if (defined(OSEE_TC_CORE4_106_ISR_CAT))
#if (OSEE_TC_CORE4_106_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_106_ISR_TID, 106)
#elif (OSEE_TC_CORE4_106_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_106_ISR_HND, 106)
#else
#error Invalid value for OSEE_TC_CORE4_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 106)
OSEE_ISR_ALIGN(_core4_, 4, 106)
#endif /* OSEE_TC_CORE4_106_ISR_CAT */
#if (defined(OSEE_TC_CORE4_107_ISR_CAT))
#if (OSEE_TC_CORE4_107_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_107_ISR_TID, 107)
#elif (OSEE_TC_CORE4_107_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_107_ISR_HND, 107)
#else
#error Invalid value for OSEE_TC_CORE4_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 107)
OSEE_ISR_ALIGN(_core4_, 4, 107)
#endif /* OSEE_TC_CORE4_107_ISR_CAT */
#if (defined(OSEE_TC_CORE4_108_ISR_CAT))
#if (OSEE_TC_CORE4_108_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_108_ISR_TID, 108)
#elif (OSEE_TC_CORE4_108_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_108_ISR_HND, 108)
#else
#error Invalid value for OSEE_TC_CORE4_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 108)
OSEE_ISR_ALIGN(_core4_, 4, 108)
#endif /* OSEE_TC_CORE4_108_ISR_CAT */
#if (defined(OSEE_TC_CORE4_109_ISR_CAT))
#if (OSEE_TC_CORE4_109_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_109_ISR_TID, 109)
#elif (OSEE_TC_CORE4_109_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_109_ISR_HND, 109)
#else
#error Invalid value for OSEE_TC_CORE4_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 109)
OSEE_ISR_ALIGN(_core4_, 4, 109)
#endif /* OSEE_TC_CORE4_109_ISR_CAT */
#if (defined(OSEE_TC_CORE4_110_ISR_CAT))
#if (OSEE_TC_CORE4_110_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_110_ISR_TID, 110)
#elif (OSEE_TC_CORE4_110_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_110_ISR_HND, 110)
#else
#error Invalid value for OSEE_TC_CORE4_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 110)
OSEE_ISR_ALIGN(_core4_, 4, 110)
#endif /* OSEE_TC_CORE4_110_ISR_CAT */
#if (defined(OSEE_TC_CORE4_111_ISR_CAT))
#if (OSEE_TC_CORE4_111_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_111_ISR_TID, 111)
#elif (OSEE_TC_CORE4_111_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_111_ISR_HND, 111)
#else
#error Invalid value for OSEE_TC_CORE4_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 111)
OSEE_ISR_ALIGN(_core4_, 4, 111)
#endif /* OSEE_TC_CORE4_111_ISR_CAT */
#if (defined(OSEE_TC_CORE4_112_ISR_CAT))
#if (OSEE_TC_CORE4_112_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_112_ISR_TID, 112)
#elif (OSEE_TC_CORE4_112_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_112_ISR_HND, 112)
#else
#error Invalid value for OSEE_TC_CORE4_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 112)
OSEE_ISR_ALIGN(_core4_, 4, 112)
#endif /* OSEE_TC_CORE4_112_ISR_CAT */
#if (defined(OSEE_TC_CORE4_113_ISR_CAT))
#if (OSEE_TC_CORE4_113_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_113_ISR_TID, 113)
#elif (OSEE_TC_CORE4_113_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_113_ISR_HND, 113)
#else
#error Invalid value for OSEE_TC_CORE4_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 113)
OSEE_ISR_ALIGN(_core4_, 4, 113)
#endif /* OSEE_TC_CORE4_113_ISR_CAT */
#if (defined(OSEE_TC_CORE4_114_ISR_CAT))
#if (OSEE_TC_CORE4_114_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_114_ISR_TID, 114)
#elif (OSEE_TC_CORE4_114_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_114_ISR_HND, 114)
#else
#error Invalid value for OSEE_TC_CORE4_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 114)
OSEE_ISR_ALIGN(_core4_, 4, 114)
#endif /* OSEE_TC_CORE4_114_ISR_CAT */
#if (defined(OSEE_TC_CORE4_115_ISR_CAT))
#if (OSEE_TC_CORE4_115_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_115_ISR_TID, 115)
#elif (OSEE_TC_CORE4_115_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_115_ISR_HND, 115)
#else
#error Invalid value for OSEE_TC_CORE4_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 115)
OSEE_ISR_ALIGN(_core4_, 4, 115)
#endif /* OSEE_TC_CORE4_115_ISR_CAT */
#if (defined(OSEE_TC_CORE4_116_ISR_CAT))
#if (OSEE_TC_CORE4_116_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_116_ISR_TID, 116)
#elif (OSEE_TC_CORE4_116_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_116_ISR_HND, 116)
#else
#error Invalid value for OSEE_TC_CORE4_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 116)
OSEE_ISR_ALIGN(_core4_, 4, 116)
#endif /* OSEE_TC_CORE4_116_ISR_CAT */
#if (defined(OSEE_TC_CORE4_117_ISR_CAT))
#if (OSEE_TC_CORE4_117_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_117_ISR_TID, 117)
#elif (OSEE_TC_CORE4_117_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_117_ISR_HND, 117)
#else
#error Invalid value for OSEE_TC_CORE4_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 117)
OSEE_ISR_ALIGN(_core4_, 4, 117)
#endif /* OSEE_TC_CORE4_117_ISR_CAT */
#if (defined(OSEE_TC_CORE4_118_ISR_CAT))
#if (OSEE_TC_CORE4_118_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_118_ISR_TID, 118)
#elif (OSEE_TC_CORE4_118_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_118_ISR_HND, 118)
#else
#error Invalid value for OSEE_TC_CORE4_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 118)
OSEE_ISR_ALIGN(_core4_, 4, 118)
#endif /* OSEE_TC_CORE4_118_ISR_CAT */
#if (defined(OSEE_TC_CORE4_119_ISR_CAT))
#if (OSEE_TC_CORE4_119_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_119_ISR_TID, 119)
#elif (OSEE_TC_CORE4_119_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_119_ISR_HND, 119)
#else
#error Invalid value for OSEE_TC_CORE4_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 119)
OSEE_ISR_ALIGN(_core4_, 4, 119)
#endif /* OSEE_TC_CORE4_119_ISR_CAT */
#if (defined(OSEE_TC_CORE4_120_ISR_CAT))
#if (OSEE_TC_CORE4_120_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_120_ISR_TID, 120)
#elif (OSEE_TC_CORE4_120_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_120_ISR_HND, 120)
#else
#error Invalid value for OSEE_TC_CORE4_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 120)
OSEE_ISR_ALIGN(_core4_, 4, 120)
#endif /* OSEE_TC_CORE4_120_ISR_CAT */
#if (defined(OSEE_TC_CORE4_121_ISR_CAT))
#if (OSEE_TC_CORE4_121_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_121_ISR_TID, 121)
#elif (OSEE_TC_CORE4_121_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_121_ISR_HND, 121)
#else
#error Invalid value for OSEE_TC_CORE4_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 121)
OSEE_ISR_ALIGN(_core4_, 4, 121)
#endif /* OSEE_TC_CORE4_121_ISR_CAT */
#if (defined(OSEE_TC_CORE4_122_ISR_CAT))
#if (OSEE_TC_CORE4_122_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_122_ISR_TID, 122)
#elif (OSEE_TC_CORE4_122_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_122_ISR_HND, 122)
#else
#error Invalid value for OSEE_TC_CORE4_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 122)
OSEE_ISR_ALIGN(_core4_, 4, 122)
#endif /* OSEE_TC_CORE4_122_ISR_CAT */
#if (defined(OSEE_TC_CORE4_123_ISR_CAT))
#if (OSEE_TC_CORE4_123_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_123_ISR_TID, 123)
#elif (OSEE_TC_CORE4_123_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_123_ISR_HND, 123)
#else
#error Invalid value for OSEE_TC_CORE4_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 123)
OSEE_ISR_ALIGN(_core4_, 4, 123)
#endif /* OSEE_TC_CORE4_123_ISR_CAT */
#if (defined(OSEE_TC_CORE4_124_ISR_CAT))
#if (OSEE_TC_CORE4_124_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_124_ISR_TID, 124)
#elif (OSEE_TC_CORE4_124_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_124_ISR_HND, 124)
#else
#error Invalid value for OSEE_TC_CORE4_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 124)
OSEE_ISR_ALIGN(_core4_, 4, 124)
#endif /* OSEE_TC_CORE4_124_ISR_CAT */
#if (defined(OSEE_TC_CORE4_125_ISR_CAT))
#if (OSEE_TC_CORE4_125_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_125_ISR_TID, 125)
#elif (OSEE_TC_CORE4_125_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_125_ISR_HND, 125)
#else
#error Invalid value for OSEE_TC_CORE4_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 125)
OSEE_ISR_ALIGN(_core4_, 4, 125)
#endif /* OSEE_TC_CORE4_125_ISR_CAT */
#if (defined(OSEE_TC_CORE4_126_ISR_CAT))
#if (OSEE_TC_CORE4_126_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_126_ISR_TID, 126)
#elif (OSEE_TC_CORE4_126_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_126_ISR_HND, 126)
#else
#error Invalid value for OSEE_TC_CORE4_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 126)
OSEE_ISR_ALIGN(_core4_, 4, 126)
#endif /* OSEE_TC_CORE4_126_ISR_CAT */
#if (defined(OSEE_TC_CORE4_127_ISR_CAT))
#if (OSEE_TC_CORE4_127_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_127_ISR_TID, 127)
#elif (OSEE_TC_CORE4_127_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_127_ISR_HND, 127)
#else
#error Invalid value for OSEE_TC_CORE4_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 127)
OSEE_ISR_ALIGN(_core4_, 4, 127)
#endif /* OSEE_TC_CORE4_127_ISR_CAT */
#if (defined(OSEE_TC_CORE4_128_ISR_CAT))
#if (OSEE_TC_CORE4_128_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_128_ISR_TID, 128)
#elif (OSEE_TC_CORE4_128_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_128_ISR_HND, 128)
#else
#error Invalid value for OSEE_TC_CORE4_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 128)
OSEE_ISR_ALIGN(_core4_, 4, 128)
#endif /* OSEE_TC_CORE4_128_ISR_CAT */
#if (defined(OSEE_TC_CORE4_129_ISR_CAT))
#if (OSEE_TC_CORE4_129_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_129_ISR_TID, 129)
#elif (OSEE_TC_CORE4_129_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_129_ISR_HND, 129)
#else
#error Invalid value for OSEE_TC_CORE4_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 129)
OSEE_ISR_ALIGN(_core4_, 4, 129)
#endif /* OSEE_TC_CORE4_129_ISR_CAT */
#if (defined(OSEE_TC_CORE4_130_ISR_CAT))
#if (OSEE_TC_CORE4_130_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_130_ISR_TID, 130)
#elif (OSEE_TC_CORE4_130_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_130_ISR_HND, 130)
#else
#error Invalid value for OSEE_TC_CORE4_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 130)
OSEE_ISR_ALIGN(_core4_, 4, 130)
#endif /* OSEE_TC_CORE4_130_ISR_CAT */
#if (defined(OSEE_TC_CORE4_131_ISR_CAT))
#if (OSEE_TC_CORE4_131_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_131_ISR_TID, 131)
#elif (OSEE_TC_CORE4_131_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_131_ISR_HND, 131)
#else
#error Invalid value for OSEE_TC_CORE4_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 131)
OSEE_ISR_ALIGN(_core4_, 4, 131)
#endif /* OSEE_TC_CORE4_131_ISR_CAT */
#if (defined(OSEE_TC_CORE4_132_ISR_CAT))
#if (OSEE_TC_CORE4_132_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_132_ISR_TID, 132)
#elif (OSEE_TC_CORE4_132_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_132_ISR_HND, 132)
#else
#error Invalid value for OSEE_TC_CORE4_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 132)
OSEE_ISR_ALIGN(_core4_, 4, 132)
#endif /* OSEE_TC_CORE4_132_ISR_CAT */
#if (defined(OSEE_TC_CORE4_133_ISR_CAT))
#if (OSEE_TC_CORE4_133_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_133_ISR_TID, 133)
#elif (OSEE_TC_CORE4_133_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_133_ISR_HND, 133)
#else
#error Invalid value for OSEE_TC_CORE4_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 133)
OSEE_ISR_ALIGN(_core4_, 4, 133)
#endif /* OSEE_TC_CORE4_133_ISR_CAT */
#if (defined(OSEE_TC_CORE4_134_ISR_CAT))
#if (OSEE_TC_CORE4_134_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_134_ISR_TID, 134)
#elif (OSEE_TC_CORE4_134_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_134_ISR_HND, 134)
#else
#error Invalid value for OSEE_TC_CORE4_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 134)
OSEE_ISR_ALIGN(_core4_, 4, 134)
#endif /* OSEE_TC_CORE4_134_ISR_CAT */
#if (defined(OSEE_TC_CORE4_135_ISR_CAT))
#if (OSEE_TC_CORE4_135_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_135_ISR_TID, 135)
#elif (OSEE_TC_CORE4_135_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_135_ISR_HND, 135)
#else
#error Invalid value for OSEE_TC_CORE4_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 135)
OSEE_ISR_ALIGN(_core4_, 4, 135)
#endif /* OSEE_TC_CORE4_135_ISR_CAT */
#if (defined(OSEE_TC_CORE4_136_ISR_CAT))
#if (OSEE_TC_CORE4_136_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_136_ISR_TID, 136)
#elif (OSEE_TC_CORE4_136_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_136_ISR_HND, 136)
#else
#error Invalid value for OSEE_TC_CORE4_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 136)
OSEE_ISR_ALIGN(_core4_, 4, 136)
#endif /* OSEE_TC_CORE4_136_ISR_CAT */
#if (defined(OSEE_TC_CORE4_137_ISR_CAT))
#if (OSEE_TC_CORE4_137_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_137_ISR_TID, 137)
#elif (OSEE_TC_CORE4_137_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_137_ISR_HND, 137)
#else
#error Invalid value for OSEE_TC_CORE4_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 137)
OSEE_ISR_ALIGN(_core4_, 4, 137)
#endif /* OSEE_TC_CORE4_137_ISR_CAT */
#if (defined(OSEE_TC_CORE4_138_ISR_CAT))
#if (OSEE_TC_CORE4_138_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_138_ISR_TID, 138)
#elif (OSEE_TC_CORE4_138_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_138_ISR_HND, 138)
#else
#error Invalid value for OSEE_TC_CORE4_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 138)
OSEE_ISR_ALIGN(_core4_, 4, 138)
#endif /* OSEE_TC_CORE4_138_ISR_CAT */
#if (defined(OSEE_TC_CORE4_139_ISR_CAT))
#if (OSEE_TC_CORE4_139_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_139_ISR_TID, 139)
#elif (OSEE_TC_CORE4_139_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_139_ISR_HND, 139)
#else
#error Invalid value for OSEE_TC_CORE4_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 139)
OSEE_ISR_ALIGN(_core4_, 4, 139)
#endif /* OSEE_TC_CORE4_139_ISR_CAT */
#if (defined(OSEE_TC_CORE4_140_ISR_CAT))
#if (OSEE_TC_CORE4_140_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_140_ISR_TID, 140)
#elif (OSEE_TC_CORE4_140_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_140_ISR_HND, 140)
#else
#error Invalid value for OSEE_TC_CORE4_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 140)
OSEE_ISR_ALIGN(_core4_, 4, 140)
#endif /* OSEE_TC_CORE4_140_ISR_CAT */
#if (defined(OSEE_TC_CORE4_141_ISR_CAT))
#if (OSEE_TC_CORE4_141_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_141_ISR_TID, 141)
#elif (OSEE_TC_CORE4_141_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_141_ISR_HND, 141)
#else
#error Invalid value for OSEE_TC_CORE4_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 141)
OSEE_ISR_ALIGN(_core4_, 4, 141)
#endif /* OSEE_TC_CORE4_141_ISR_CAT */
#if (defined(OSEE_TC_CORE4_142_ISR_CAT))
#if (OSEE_TC_CORE4_142_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_142_ISR_TID, 142)
#elif (OSEE_TC_CORE4_142_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_142_ISR_HND, 142)
#else
#error Invalid value for OSEE_TC_CORE4_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 142)
OSEE_ISR_ALIGN(_core4_, 4, 142)
#endif /* OSEE_TC_CORE4_142_ISR_CAT */
#if (defined(OSEE_TC_CORE4_143_ISR_CAT))
#if (OSEE_TC_CORE4_143_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_143_ISR_TID, 143)
#elif (OSEE_TC_CORE4_143_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_143_ISR_HND, 143)
#else
#error Invalid value for OSEE_TC_CORE4_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 143)
OSEE_ISR_ALIGN(_core4_, 4, 143)
#endif /* OSEE_TC_CORE4_143_ISR_CAT */
#if (defined(OSEE_TC_CORE4_144_ISR_CAT))
#if (OSEE_TC_CORE4_144_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_144_ISR_TID, 144)
#elif (OSEE_TC_CORE4_144_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_144_ISR_HND, 144)
#else
#error Invalid value for OSEE_TC_CORE4_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 144)
OSEE_ISR_ALIGN(_core4_, 4, 144)
#endif /* OSEE_TC_CORE4_144_ISR_CAT */
#if (defined(OSEE_TC_CORE4_145_ISR_CAT))
#if (OSEE_TC_CORE4_145_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_145_ISR_TID, 145)
#elif (OSEE_TC_CORE4_145_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_145_ISR_HND, 145)
#else
#error Invalid value for OSEE_TC_CORE4_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 145)
OSEE_ISR_ALIGN(_core4_, 4, 145)
#endif /* OSEE_TC_CORE4_145_ISR_CAT */
#if (defined(OSEE_TC_CORE4_146_ISR_CAT))
#if (OSEE_TC_CORE4_146_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_146_ISR_TID, 146)
#elif (OSEE_TC_CORE4_146_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_146_ISR_HND, 146)
#else
#error Invalid value for OSEE_TC_CORE4_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 146)
OSEE_ISR_ALIGN(_core4_, 4, 146)
#endif /* OSEE_TC_CORE4_146_ISR_CAT */
#if (defined(OSEE_TC_CORE4_147_ISR_CAT))
#if (OSEE_TC_CORE4_147_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_147_ISR_TID, 147)
#elif (OSEE_TC_CORE4_147_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_147_ISR_HND, 147)
#else
#error Invalid value for OSEE_TC_CORE4_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 147)
OSEE_ISR_ALIGN(_core4_, 4, 147)
#endif /* OSEE_TC_CORE4_147_ISR_CAT */
#if (defined(OSEE_TC_CORE4_148_ISR_CAT))
#if (OSEE_TC_CORE4_148_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_148_ISR_TID, 148)
#elif (OSEE_TC_CORE4_148_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_148_ISR_HND, 148)
#else
#error Invalid value for OSEE_TC_CORE4_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 148)
OSEE_ISR_ALIGN(_core4_, 4, 148)
#endif /* OSEE_TC_CORE4_148_ISR_CAT */
#if (defined(OSEE_TC_CORE4_149_ISR_CAT))
#if (OSEE_TC_CORE4_149_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_149_ISR_TID, 149)
#elif (OSEE_TC_CORE4_149_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_149_ISR_HND, 149)
#else
#error Invalid value for OSEE_TC_CORE4_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 149)
OSEE_ISR_ALIGN(_core4_, 4, 149)
#endif /* OSEE_TC_CORE4_149_ISR_CAT */
#if (defined(OSEE_TC_CORE4_150_ISR_CAT))
#if (OSEE_TC_CORE4_150_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_150_ISR_TID, 150)
#elif (OSEE_TC_CORE4_150_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_150_ISR_HND, 150)
#else
#error Invalid value for OSEE_TC_CORE4_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 150)
OSEE_ISR_ALIGN(_core4_, 4, 150)
#endif /* OSEE_TC_CORE4_150_ISR_CAT */
#if (defined(OSEE_TC_CORE4_151_ISR_CAT))
#if (OSEE_TC_CORE4_151_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_151_ISR_TID, 151)
#elif (OSEE_TC_CORE4_151_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_151_ISR_HND, 151)
#else
#error Invalid value for OSEE_TC_CORE4_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 151)
OSEE_ISR_ALIGN(_core4_, 4, 151)
#endif /* OSEE_TC_CORE4_151_ISR_CAT */
#if (defined(OSEE_TC_CORE4_152_ISR_CAT))
#if (OSEE_TC_CORE4_152_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_152_ISR_TID, 152)
#elif (OSEE_TC_CORE4_152_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_152_ISR_HND, 152)
#else
#error Invalid value for OSEE_TC_CORE4_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 152)
OSEE_ISR_ALIGN(_core4_, 4, 152)
#endif /* OSEE_TC_CORE4_152_ISR_CAT */
#if (defined(OSEE_TC_CORE4_153_ISR_CAT))
#if (OSEE_TC_CORE4_153_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_153_ISR_TID, 153)
#elif (OSEE_TC_CORE4_153_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_153_ISR_HND, 153)
#else
#error Invalid value for OSEE_TC_CORE4_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 153)
OSEE_ISR_ALIGN(_core4_, 4, 153)
#endif /* OSEE_TC_CORE4_153_ISR_CAT */
#if (defined(OSEE_TC_CORE4_154_ISR_CAT))
#if (OSEE_TC_CORE4_154_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_154_ISR_TID, 154)
#elif (OSEE_TC_CORE4_154_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_154_ISR_HND, 154)
#else
#error Invalid value for OSEE_TC_CORE4_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 154)
OSEE_ISR_ALIGN(_core4_, 4, 154)
#endif /* OSEE_TC_CORE4_154_ISR_CAT */
#if (defined(OSEE_TC_CORE4_155_ISR_CAT))
#if (OSEE_TC_CORE4_155_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_155_ISR_TID, 155)
#elif (OSEE_TC_CORE4_155_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_155_ISR_HND, 155)
#else
#error Invalid value for OSEE_TC_CORE4_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 155)
OSEE_ISR_ALIGN(_core4_, 4, 155)
#endif /* OSEE_TC_CORE4_155_ISR_CAT */
#if (defined(OSEE_TC_CORE4_156_ISR_CAT))
#if (OSEE_TC_CORE4_156_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_156_ISR_TID, 156)
#elif (OSEE_TC_CORE4_156_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_156_ISR_HND, 156)
#else
#error Invalid value for OSEE_TC_CORE4_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 156)
OSEE_ISR_ALIGN(_core4_, 4, 156)
#endif /* OSEE_TC_CORE4_156_ISR_CAT */
#if (defined(OSEE_TC_CORE4_157_ISR_CAT))
#if (OSEE_TC_CORE4_157_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_157_ISR_TID, 157)
#elif (OSEE_TC_CORE4_157_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_157_ISR_HND, 157)
#else
#error Invalid value for OSEE_TC_CORE4_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 157)
OSEE_ISR_ALIGN(_core4_, 4, 157)
#endif /* OSEE_TC_CORE4_157_ISR_CAT */
#if (defined(OSEE_TC_CORE4_158_ISR_CAT))
#if (OSEE_TC_CORE4_158_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_158_ISR_TID, 158)
#elif (OSEE_TC_CORE4_158_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_158_ISR_HND, 158)
#else
#error Invalid value for OSEE_TC_CORE4_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 158)
OSEE_ISR_ALIGN(_core4_, 4, 158)
#endif /* OSEE_TC_CORE4_158_ISR_CAT */
#if (defined(OSEE_TC_CORE4_159_ISR_CAT))
#if (OSEE_TC_CORE4_159_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_159_ISR_TID, 159)
#elif (OSEE_TC_CORE4_159_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_159_ISR_HND, 159)
#else
#error Invalid value for OSEE_TC_CORE4_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 159)
OSEE_ISR_ALIGN(_core4_, 4, 159)
#endif /* OSEE_TC_CORE4_159_ISR_CAT */
#if (defined(OSEE_TC_CORE4_160_ISR_CAT))
#if (OSEE_TC_CORE4_160_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_160_ISR_TID, 160)
#elif (OSEE_TC_CORE4_160_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_160_ISR_HND, 160)
#else
#error Invalid value for OSEE_TC_CORE4_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 160)
OSEE_ISR_ALIGN(_core4_, 4, 160)
#endif /* OSEE_TC_CORE4_160_ISR_CAT */
#if (defined(OSEE_TC_CORE4_161_ISR_CAT))
#if (OSEE_TC_CORE4_161_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_161_ISR_TID, 161)
#elif (OSEE_TC_CORE4_161_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_161_ISR_HND, 161)
#else
#error Invalid value for OSEE_TC_CORE4_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 161)
OSEE_ISR_ALIGN(_core4_, 4, 161)
#endif /* OSEE_TC_CORE4_161_ISR_CAT */
#if (defined(OSEE_TC_CORE4_162_ISR_CAT))
#if (OSEE_TC_CORE4_162_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_162_ISR_TID, 162)
#elif (OSEE_TC_CORE4_162_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_162_ISR_HND, 162)
#else
#error Invalid value for OSEE_TC_CORE4_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 162)
OSEE_ISR_ALIGN(_core4_, 4, 162)
#endif /* OSEE_TC_CORE4_162_ISR_CAT */
#if (defined(OSEE_TC_CORE4_163_ISR_CAT))
#if (OSEE_TC_CORE4_163_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_163_ISR_TID, 163)
#elif (OSEE_TC_CORE4_163_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_163_ISR_HND, 163)
#else
#error Invalid value for OSEE_TC_CORE4_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 163)
OSEE_ISR_ALIGN(_core4_, 4, 163)
#endif /* OSEE_TC_CORE4_163_ISR_CAT */
#if (defined(OSEE_TC_CORE4_164_ISR_CAT))
#if (OSEE_TC_CORE4_164_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_164_ISR_TID, 164)
#elif (OSEE_TC_CORE4_164_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_164_ISR_HND, 164)
#else
#error Invalid value for OSEE_TC_CORE4_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 164)
OSEE_ISR_ALIGN(_core4_, 4, 164)
#endif /* OSEE_TC_CORE4_164_ISR_CAT */
#if (defined(OSEE_TC_CORE4_165_ISR_CAT))
#if (OSEE_TC_CORE4_165_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_165_ISR_TID, 165)
#elif (OSEE_TC_CORE4_165_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_165_ISR_HND, 165)
#else
#error Invalid value for OSEE_TC_CORE4_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 165)
OSEE_ISR_ALIGN(_core4_, 4, 165)
#endif /* OSEE_TC_CORE4_165_ISR_CAT */
#if (defined(OSEE_TC_CORE4_166_ISR_CAT))
#if (OSEE_TC_CORE4_166_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_166_ISR_TID, 166)
#elif (OSEE_TC_CORE4_166_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_166_ISR_HND, 166)
#else
#error Invalid value for OSEE_TC_CORE4_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 166)
OSEE_ISR_ALIGN(_core4_, 4, 166)
#endif /* OSEE_TC_CORE4_166_ISR_CAT */
#if (defined(OSEE_TC_CORE4_167_ISR_CAT))
#if (OSEE_TC_CORE4_167_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_167_ISR_TID, 167)
#elif (OSEE_TC_CORE4_167_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_167_ISR_HND, 167)
#else
#error Invalid value for OSEE_TC_CORE4_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 167)
OSEE_ISR_ALIGN(_core4_, 4, 167)
#endif /* OSEE_TC_CORE4_167_ISR_CAT */
#if (defined(OSEE_TC_CORE4_168_ISR_CAT))
#if (OSEE_TC_CORE4_168_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_168_ISR_TID, 168)
#elif (OSEE_TC_CORE4_168_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_168_ISR_HND, 168)
#else
#error Invalid value for OSEE_TC_CORE4_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 168)
OSEE_ISR_ALIGN(_core4_, 4, 168)
#endif /* OSEE_TC_CORE4_168_ISR_CAT */
#if (defined(OSEE_TC_CORE4_169_ISR_CAT))
#if (OSEE_TC_CORE4_169_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_169_ISR_TID, 169)
#elif (OSEE_TC_CORE4_169_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_169_ISR_HND, 169)
#else
#error Invalid value for OSEE_TC_CORE4_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 169)
OSEE_ISR_ALIGN(_core4_, 4, 169)
#endif /* OSEE_TC_CORE4_169_ISR_CAT */
#if (defined(OSEE_TC_CORE4_170_ISR_CAT))
#if (OSEE_TC_CORE4_170_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_170_ISR_TID, 170)
#elif (OSEE_TC_CORE4_170_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_170_ISR_HND, 170)
#else
#error Invalid value for OSEE_TC_CORE4_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 170)
OSEE_ISR_ALIGN(_core4_, 4, 170)
#endif /* OSEE_TC_CORE4_170_ISR_CAT */
#if (defined(OSEE_TC_CORE4_171_ISR_CAT))
#if (OSEE_TC_CORE4_171_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_171_ISR_TID, 171)
#elif (OSEE_TC_CORE4_171_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_171_ISR_HND, 171)
#else
#error Invalid value for OSEE_TC_CORE4_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 171)
OSEE_ISR_ALIGN(_core4_, 4, 171)
#endif /* OSEE_TC_CORE4_171_ISR_CAT */
#if (defined(OSEE_TC_CORE4_172_ISR_CAT))
#if (OSEE_TC_CORE4_172_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_172_ISR_TID, 172)
#elif (OSEE_TC_CORE4_172_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_172_ISR_HND, 172)
#else
#error Invalid value for OSEE_TC_CORE4_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 172)
OSEE_ISR_ALIGN(_core4_, 4, 172)
#endif /* OSEE_TC_CORE4_172_ISR_CAT */
#if (defined(OSEE_TC_CORE4_173_ISR_CAT))
#if (OSEE_TC_CORE4_173_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_173_ISR_TID, 173)
#elif (OSEE_TC_CORE4_173_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_173_ISR_HND, 173)
#else
#error Invalid value for OSEE_TC_CORE4_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 173)
OSEE_ISR_ALIGN(_core4_, 4, 173)
#endif /* OSEE_TC_CORE4_173_ISR_CAT */
#if (defined(OSEE_TC_CORE4_174_ISR_CAT))
#if (OSEE_TC_CORE4_174_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_174_ISR_TID, 174)
#elif (OSEE_TC_CORE4_174_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_174_ISR_HND, 174)
#else
#error Invalid value for OSEE_TC_CORE4_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 174)
OSEE_ISR_ALIGN(_core4_, 4, 174)
#endif /* OSEE_TC_CORE4_174_ISR_CAT */
#if (defined(OSEE_TC_CORE4_175_ISR_CAT))
#if (OSEE_TC_CORE4_175_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_175_ISR_TID, 175)
#elif (OSEE_TC_CORE4_175_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_175_ISR_HND, 175)
#else
#error Invalid value for OSEE_TC_CORE4_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 175)
OSEE_ISR_ALIGN(_core4_, 4, 175)
#endif /* OSEE_TC_CORE4_175_ISR_CAT */
#if (defined(OSEE_TC_CORE4_176_ISR_CAT))
#if (OSEE_TC_CORE4_176_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_176_ISR_TID, 176)
#elif (OSEE_TC_CORE4_176_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_176_ISR_HND, 176)
#else
#error Invalid value for OSEE_TC_CORE4_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 176)
OSEE_ISR_ALIGN(_core4_, 4, 176)
#endif /* OSEE_TC_CORE4_176_ISR_CAT */
#if (defined(OSEE_TC_CORE4_177_ISR_CAT))
#if (OSEE_TC_CORE4_177_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_177_ISR_TID, 177)
#elif (OSEE_TC_CORE4_177_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_177_ISR_HND, 177)
#else
#error Invalid value for OSEE_TC_CORE4_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 177)
OSEE_ISR_ALIGN(_core4_, 4, 177)
#endif /* OSEE_TC_CORE4_177_ISR_CAT */
#if (defined(OSEE_TC_CORE4_178_ISR_CAT))
#if (OSEE_TC_CORE4_178_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_178_ISR_TID, 178)
#elif (OSEE_TC_CORE4_178_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_178_ISR_HND, 178)
#else
#error Invalid value for OSEE_TC_CORE4_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 178)
OSEE_ISR_ALIGN(_core4_, 4, 178)
#endif /* OSEE_TC_CORE4_178_ISR_CAT */
#if (defined(OSEE_TC_CORE4_179_ISR_CAT))
#if (OSEE_TC_CORE4_179_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_179_ISR_TID, 179)
#elif (OSEE_TC_CORE4_179_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_179_ISR_HND, 179)
#else
#error Invalid value for OSEE_TC_CORE4_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 179)
OSEE_ISR_ALIGN(_core4_, 4, 179)
#endif /* OSEE_TC_CORE4_179_ISR_CAT */
#if (defined(OSEE_TC_CORE4_180_ISR_CAT))
#if (OSEE_TC_CORE4_180_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_180_ISR_TID, 180)
#elif (OSEE_TC_CORE4_180_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_180_ISR_HND, 180)
#else
#error Invalid value for OSEE_TC_CORE4_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 180)
OSEE_ISR_ALIGN(_core4_, 4, 180)
#endif /* OSEE_TC_CORE4_180_ISR_CAT */
#if (defined(OSEE_TC_CORE4_181_ISR_CAT))
#if (OSEE_TC_CORE4_181_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_181_ISR_TID, 181)
#elif (OSEE_TC_CORE4_181_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_181_ISR_HND, 181)
#else
#error Invalid value for OSEE_TC_CORE4_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 181)
OSEE_ISR_ALIGN(_core4_, 4, 181)
#endif /* OSEE_TC_CORE4_181_ISR_CAT */
#if (defined(OSEE_TC_CORE4_182_ISR_CAT))
#if (OSEE_TC_CORE4_182_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_182_ISR_TID, 182)
#elif (OSEE_TC_CORE4_182_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_182_ISR_HND, 182)
#else
#error Invalid value for OSEE_TC_CORE4_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 182)
OSEE_ISR_ALIGN(_core4_, 4, 182)
#endif /* OSEE_TC_CORE4_182_ISR_CAT */
#if (defined(OSEE_TC_CORE4_183_ISR_CAT))
#if (OSEE_TC_CORE4_183_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_183_ISR_TID, 183)
#elif (OSEE_TC_CORE4_183_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_183_ISR_HND, 183)
#else
#error Invalid value for OSEE_TC_CORE4_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 183)
OSEE_ISR_ALIGN(_core4_, 4, 183)
#endif /* OSEE_TC_CORE4_183_ISR_CAT */
#if (defined(OSEE_TC_CORE4_184_ISR_CAT))
#if (OSEE_TC_CORE4_184_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_184_ISR_TID, 184)
#elif (OSEE_TC_CORE4_184_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_184_ISR_HND, 184)
#else
#error Invalid value for OSEE_TC_CORE4_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 184)
OSEE_ISR_ALIGN(_core4_, 4, 184)
#endif /* OSEE_TC_CORE4_184_ISR_CAT */
#if (defined(OSEE_TC_CORE4_185_ISR_CAT))
#if (OSEE_TC_CORE4_185_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_185_ISR_TID, 185)
#elif (OSEE_TC_CORE4_185_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_185_ISR_HND, 185)
#else
#error Invalid value for OSEE_TC_CORE4_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 185)
OSEE_ISR_ALIGN(_core4_, 4, 185)
#endif /* OSEE_TC_CORE4_185_ISR_CAT */
#if (defined(OSEE_TC_CORE4_186_ISR_CAT))
#if (OSEE_TC_CORE4_186_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_186_ISR_TID, 186)
#elif (OSEE_TC_CORE4_186_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_186_ISR_HND, 186)
#else
#error Invalid value for OSEE_TC_CORE4_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 186)
OSEE_ISR_ALIGN(_core4_, 4, 186)
#endif /* OSEE_TC_CORE4_186_ISR_CAT */
#if (defined(OSEE_TC_CORE4_187_ISR_CAT))
#if (OSEE_TC_CORE4_187_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_187_ISR_TID, 187)
#elif (OSEE_TC_CORE4_187_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_187_ISR_HND, 187)
#else
#error Invalid value for OSEE_TC_CORE4_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 187)
OSEE_ISR_ALIGN(_core4_, 4, 187)
#endif /* OSEE_TC_CORE4_187_ISR_CAT */
#if (defined(OSEE_TC_CORE4_188_ISR_CAT))
#if (OSEE_TC_CORE4_188_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_188_ISR_TID, 188)
#elif (OSEE_TC_CORE4_188_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_188_ISR_HND, 188)
#else
#error Invalid value for OSEE_TC_CORE4_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 188)
OSEE_ISR_ALIGN(_core4_, 4, 188)
#endif /* OSEE_TC_CORE4_188_ISR_CAT */
#if (defined(OSEE_TC_CORE4_189_ISR_CAT))
#if (OSEE_TC_CORE4_189_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_189_ISR_TID, 189)
#elif (OSEE_TC_CORE4_189_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_189_ISR_HND, 189)
#else
#error Invalid value for OSEE_TC_CORE4_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 189)
OSEE_ISR_ALIGN(_core4_, 4, 189)
#endif /* OSEE_TC_CORE4_189_ISR_CAT */
#if (defined(OSEE_TC_CORE4_190_ISR_CAT))
#if (OSEE_TC_CORE4_190_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_190_ISR_TID, 190)
#elif (OSEE_TC_CORE4_190_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_190_ISR_HND, 190)
#else
#error Invalid value for OSEE_TC_CORE4_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 190)
OSEE_ISR_ALIGN(_core4_, 4, 190)
#endif /* OSEE_TC_CORE4_190_ISR_CAT */
#if (defined(OSEE_TC_CORE4_191_ISR_CAT))
#if (OSEE_TC_CORE4_191_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_191_ISR_TID, 191)
#elif (OSEE_TC_CORE4_191_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_191_ISR_HND, 191)
#else
#error Invalid value for OSEE_TC_CORE4_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 191)
OSEE_ISR_ALIGN(_core4_, 4, 191)
#endif /* OSEE_TC_CORE4_191_ISR_CAT */
#if (defined(OSEE_TC_CORE4_192_ISR_CAT))
#if (OSEE_TC_CORE4_192_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_192_ISR_TID, 192)
#elif (OSEE_TC_CORE4_192_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_192_ISR_HND, 192)
#else
#error Invalid value for OSEE_TC_CORE4_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 192)
OSEE_ISR_ALIGN(_core4_, 4, 192)
#endif /* OSEE_TC_CORE4_192_ISR_CAT */
#if (defined(OSEE_TC_CORE4_193_ISR_CAT))
#if (OSEE_TC_CORE4_193_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_193_ISR_TID, 193)
#elif (OSEE_TC_CORE4_193_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_193_ISR_HND, 193)
#else
#error Invalid value for OSEE_TC_CORE4_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 193)
OSEE_ISR_ALIGN(_core4_, 4, 193)
#endif /* OSEE_TC_CORE4_193_ISR_CAT */
#if (defined(OSEE_TC_CORE4_194_ISR_CAT))
#if (OSEE_TC_CORE4_194_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_194_ISR_TID, 194)
#elif (OSEE_TC_CORE4_194_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_194_ISR_HND, 194)
#else
#error Invalid value for OSEE_TC_CORE4_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 194)
OSEE_ISR_ALIGN(_core4_, 4, 194)
#endif /* OSEE_TC_CORE4_194_ISR_CAT */
#if (defined(OSEE_TC_CORE4_195_ISR_CAT))
#if (OSEE_TC_CORE4_195_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_195_ISR_TID, 195)
#elif (OSEE_TC_CORE4_195_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_195_ISR_HND, 195)
#else
#error Invalid value for OSEE_TC_CORE4_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 195)
OSEE_ISR_ALIGN(_core4_, 4, 195)
#endif /* OSEE_TC_CORE4_195_ISR_CAT */
#if (defined(OSEE_TC_CORE4_196_ISR_CAT))
#if (OSEE_TC_CORE4_196_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_196_ISR_TID, 196)
#elif (OSEE_TC_CORE4_196_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_196_ISR_HND, 196)
#else
#error Invalid value for OSEE_TC_CORE4_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 196)
OSEE_ISR_ALIGN(_core4_, 4, 196)
#endif /* OSEE_TC_CORE4_196_ISR_CAT */
#if (defined(OSEE_TC_CORE4_197_ISR_CAT))
#if (OSEE_TC_CORE4_197_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_197_ISR_TID, 197)
#elif (OSEE_TC_CORE4_197_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_197_ISR_HND, 197)
#else
#error Invalid value for OSEE_TC_CORE4_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 197)
OSEE_ISR_ALIGN(_core4_, 4, 197)
#endif /* OSEE_TC_CORE4_197_ISR_CAT */
#if (defined(OSEE_TC_CORE4_198_ISR_CAT))
#if (OSEE_TC_CORE4_198_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_198_ISR_TID, 198)
#elif (OSEE_TC_CORE4_198_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_198_ISR_HND, 198)
#else
#error Invalid value for OSEE_TC_CORE4_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 198)
OSEE_ISR_ALIGN(_core4_, 4, 198)
#endif /* OSEE_TC_CORE4_198_ISR_CAT */
#if (defined(OSEE_TC_CORE4_199_ISR_CAT))
#if (OSEE_TC_CORE4_199_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_199_ISR_TID, 199)
#elif (OSEE_TC_CORE4_199_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_199_ISR_HND, 199)
#else
#error Invalid value for OSEE_TC_CORE4_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 199)
OSEE_ISR_ALIGN(_core4_, 4, 199)
#endif /* OSEE_TC_CORE4_199_ISR_CAT */
#if (defined(OSEE_TC_CORE4_200_ISR_CAT))
#if (OSEE_TC_CORE4_200_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_200_ISR_TID, 200)
#elif (OSEE_TC_CORE4_200_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_200_ISR_HND, 200)
#else
#error Invalid value for OSEE_TC_CORE4_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 200)
OSEE_ISR_ALIGN(_core4_, 4, 200)
#endif /* OSEE_TC_CORE4_200_ISR_CAT */
#if (defined(OSEE_TC_CORE4_201_ISR_CAT))
#if (OSEE_TC_CORE4_201_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_201_ISR_TID, 201)
#elif (OSEE_TC_CORE4_201_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_201_ISR_HND, 201)
#else
#error Invalid value for OSEE_TC_CORE4_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 201)
OSEE_ISR_ALIGN(_core4_, 4, 201)
#endif /* OSEE_TC_CORE4_201_ISR_CAT */
#if (defined(OSEE_TC_CORE4_202_ISR_CAT))
#if (OSEE_TC_CORE4_202_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_202_ISR_TID, 202)
#elif (OSEE_TC_CORE4_202_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_202_ISR_HND, 202)
#else
#error Invalid value for OSEE_TC_CORE4_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 202)
OSEE_ISR_ALIGN(_core4_, 4, 202)
#endif /* OSEE_TC_CORE4_202_ISR_CAT */
#if (defined(OSEE_TC_CORE4_203_ISR_CAT))
#if (OSEE_TC_CORE4_203_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_203_ISR_TID, 203)
#elif (OSEE_TC_CORE4_203_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_203_ISR_HND, 203)
#else
#error Invalid value for OSEE_TC_CORE4_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 203)
OSEE_ISR_ALIGN(_core4_, 4, 203)
#endif /* OSEE_TC_CORE4_203_ISR_CAT */
#if (defined(OSEE_TC_CORE4_204_ISR_CAT))
#if (OSEE_TC_CORE4_204_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_204_ISR_TID, 204)
#elif (OSEE_TC_CORE4_204_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_204_ISR_HND, 204)
#else
#error Invalid value for OSEE_TC_CORE4_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 204)
OSEE_ISR_ALIGN(_core4_, 4, 204)
#endif /* OSEE_TC_CORE4_204_ISR_CAT */
#if (defined(OSEE_TC_CORE4_205_ISR_CAT))
#if (OSEE_TC_CORE4_205_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_205_ISR_TID, 205)
#elif (OSEE_TC_CORE4_205_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_205_ISR_HND, 205)
#else
#error Invalid value for OSEE_TC_CORE4_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 205)
OSEE_ISR_ALIGN(_core4_, 4, 205)
#endif /* OSEE_TC_CORE4_205_ISR_CAT */
#if (defined(OSEE_TC_CORE4_206_ISR_CAT))
#if (OSEE_TC_CORE4_206_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_206_ISR_TID, 206)
#elif (OSEE_TC_CORE4_206_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_206_ISR_HND, 206)
#else
#error Invalid value for OSEE_TC_CORE4_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 206)
OSEE_ISR_ALIGN(_core4_, 4, 206)
#endif /* OSEE_TC_CORE4_206_ISR_CAT */
#if (defined(OSEE_TC_CORE4_207_ISR_CAT))
#if (OSEE_TC_CORE4_207_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_207_ISR_TID, 207)
#elif (OSEE_TC_CORE4_207_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_207_ISR_HND, 207)
#else
#error Invalid value for OSEE_TC_CORE4_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 207)
OSEE_ISR_ALIGN(_core4_, 4, 207)
#endif /* OSEE_TC_CORE4_207_ISR_CAT */
#if (defined(OSEE_TC_CORE4_208_ISR_CAT))
#if (OSEE_TC_CORE4_208_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_208_ISR_TID, 208)
#elif (OSEE_TC_CORE4_208_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_208_ISR_HND, 208)
#else
#error Invalid value for OSEE_TC_CORE4_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 208)
OSEE_ISR_ALIGN(_core4_, 4, 208)
#endif /* OSEE_TC_CORE4_208_ISR_CAT */
#if (defined(OSEE_TC_CORE4_209_ISR_CAT))
#if (OSEE_TC_CORE4_209_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_209_ISR_TID, 209)
#elif (OSEE_TC_CORE4_209_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_209_ISR_HND, 209)
#else
#error Invalid value for OSEE_TC_CORE4_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 209)
OSEE_ISR_ALIGN(_core4_, 4, 209)
#endif /* OSEE_TC_CORE4_209_ISR_CAT */
#if (defined(OSEE_TC_CORE4_210_ISR_CAT))
#if (OSEE_TC_CORE4_210_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_210_ISR_TID, 210)
#elif (OSEE_TC_CORE4_210_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_210_ISR_HND, 210)
#else
#error Invalid value for OSEE_TC_CORE4_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 210)
OSEE_ISR_ALIGN(_core4_, 4, 210)
#endif /* OSEE_TC_CORE4_210_ISR_CAT */
#if (defined(OSEE_TC_CORE4_211_ISR_CAT))
#if (OSEE_TC_CORE4_211_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_211_ISR_TID, 211)
#elif (OSEE_TC_CORE4_211_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_211_ISR_HND, 211)
#else
#error Invalid value for OSEE_TC_CORE4_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 211)
OSEE_ISR_ALIGN(_core4_, 4, 211)
#endif /* OSEE_TC_CORE4_211_ISR_CAT */
#if (defined(OSEE_TC_CORE4_212_ISR_CAT))
#if (OSEE_TC_CORE4_212_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_212_ISR_TID, 212)
#elif (OSEE_TC_CORE4_212_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_212_ISR_HND, 212)
#else
#error Invalid value for OSEE_TC_CORE4_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 212)
OSEE_ISR_ALIGN(_core4_, 4, 212)
#endif /* OSEE_TC_CORE4_212_ISR_CAT */
#if (defined(OSEE_TC_CORE4_213_ISR_CAT))
#if (OSEE_TC_CORE4_213_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_213_ISR_TID, 213)
#elif (OSEE_TC_CORE4_213_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_213_ISR_HND, 213)
#else
#error Invalid value for OSEE_TC_CORE4_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 213)
OSEE_ISR_ALIGN(_core4_, 4, 213)
#endif /* OSEE_TC_CORE4_213_ISR_CAT */
#if (defined(OSEE_TC_CORE4_214_ISR_CAT))
#if (OSEE_TC_CORE4_214_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_214_ISR_TID, 214)
#elif (OSEE_TC_CORE4_214_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_214_ISR_HND, 214)
#else
#error Invalid value for OSEE_TC_CORE4_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 214)
OSEE_ISR_ALIGN(_core4_, 4, 214)
#endif /* OSEE_TC_CORE4_214_ISR_CAT */
#if (defined(OSEE_TC_CORE4_215_ISR_CAT))
#if (OSEE_TC_CORE4_215_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_215_ISR_TID, 215)
#elif (OSEE_TC_CORE4_215_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_215_ISR_HND, 215)
#else
#error Invalid value for OSEE_TC_CORE4_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 215)
OSEE_ISR_ALIGN(_core4_, 4, 215)
#endif /* OSEE_TC_CORE4_215_ISR_CAT */
#if (defined(OSEE_TC_CORE4_216_ISR_CAT))
#if (OSEE_TC_CORE4_216_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_216_ISR_TID, 216)
#elif (OSEE_TC_CORE4_216_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_216_ISR_HND, 216)
#else
#error Invalid value for OSEE_TC_CORE4_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 216)
OSEE_ISR_ALIGN(_core4_, 4, 216)
#endif /* OSEE_TC_CORE4_216_ISR_CAT */
#if (defined(OSEE_TC_CORE4_217_ISR_CAT))
#if (OSEE_TC_CORE4_217_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_217_ISR_TID, 217)
#elif (OSEE_TC_CORE4_217_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_217_ISR_HND, 217)
#else
#error Invalid value for OSEE_TC_CORE4_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 217)
OSEE_ISR_ALIGN(_core4_, 4, 217)
#endif /* OSEE_TC_CORE4_217_ISR_CAT */
#if (defined(OSEE_TC_CORE4_218_ISR_CAT))
#if (OSEE_TC_CORE4_218_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_218_ISR_TID, 218)
#elif (OSEE_TC_CORE4_218_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_218_ISR_HND, 218)
#else
#error Invalid value for OSEE_TC_CORE4_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 218)
OSEE_ISR_ALIGN(_core4_, 4, 218)
#endif /* OSEE_TC_CORE4_218_ISR_CAT */
#if (defined(OSEE_TC_CORE4_219_ISR_CAT))
#if (OSEE_TC_CORE4_219_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_219_ISR_TID, 219)
#elif (OSEE_TC_CORE4_219_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_219_ISR_HND, 219)
#else
#error Invalid value for OSEE_TC_CORE4_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 219)
OSEE_ISR_ALIGN(_core4_, 4, 219)
#endif /* OSEE_TC_CORE4_219_ISR_CAT */
#if (defined(OSEE_TC_CORE4_220_ISR_CAT))
#if (OSEE_TC_CORE4_220_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_220_ISR_TID, 220)
#elif (OSEE_TC_CORE4_220_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_220_ISR_HND, 220)
#else
#error Invalid value for OSEE_TC_CORE4_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 220)
OSEE_ISR_ALIGN(_core4_, 4, 220)
#endif /* OSEE_TC_CORE4_220_ISR_CAT */
#if (defined(OSEE_TC_CORE4_221_ISR_CAT))
#if (OSEE_TC_CORE4_221_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_221_ISR_TID, 221)
#elif (OSEE_TC_CORE4_221_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_221_ISR_HND, 221)
#else
#error Invalid value for OSEE_TC_CORE4_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 221)
OSEE_ISR_ALIGN(_core4_, 4, 221)
#endif /* OSEE_TC_CORE4_221_ISR_CAT */
#if (defined(OSEE_TC_CORE4_222_ISR_CAT))
#if (OSEE_TC_CORE4_222_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_222_ISR_TID, 222)
#elif (OSEE_TC_CORE4_222_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_222_ISR_HND, 222)
#else
#error Invalid value for OSEE_TC_CORE4_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 222)
OSEE_ISR_ALIGN(_core4_, 4, 222)
#endif /* OSEE_TC_CORE4_222_ISR_CAT */
#if (defined(OSEE_TC_CORE4_223_ISR_CAT))
#if (OSEE_TC_CORE4_223_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_223_ISR_TID, 223)
#elif (OSEE_TC_CORE4_223_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_223_ISR_HND, 223)
#else
#error Invalid value for OSEE_TC_CORE4_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 223)
OSEE_ISR_ALIGN(_core4_, 4, 223)
#endif /* OSEE_TC_CORE4_223_ISR_CAT */
#if (defined(OSEE_TC_CORE4_224_ISR_CAT))
#if (OSEE_TC_CORE4_224_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_224_ISR_TID, 224)
#elif (OSEE_TC_CORE4_224_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_224_ISR_HND, 224)
#else
#error Invalid value for OSEE_TC_CORE4_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 224)
OSEE_ISR_ALIGN(_core4_, 4, 224)
#endif /* OSEE_TC_CORE4_224_ISR_CAT */
#if (defined(OSEE_TC_CORE4_225_ISR_CAT))
#if (OSEE_TC_CORE4_225_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_225_ISR_TID, 225)
#elif (OSEE_TC_CORE4_225_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_225_ISR_HND, 225)
#else
#error Invalid value for OSEE_TC_CORE4_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 225)
OSEE_ISR_ALIGN(_core4_, 4, 225)
#endif /* OSEE_TC_CORE4_225_ISR_CAT */
#if (defined(OSEE_TC_CORE4_226_ISR_CAT))
#if (OSEE_TC_CORE4_226_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_226_ISR_TID, 226)
#elif (OSEE_TC_CORE4_226_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_226_ISR_HND, 226)
#else
#error Invalid value for OSEE_TC_CORE4_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 226)
OSEE_ISR_ALIGN(_core4_, 4, 226)
#endif /* OSEE_TC_CORE4_226_ISR_CAT */
#if (defined(OSEE_TC_CORE4_227_ISR_CAT))
#if (OSEE_TC_CORE4_227_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_227_ISR_TID, 227)
#elif (OSEE_TC_CORE4_227_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_227_ISR_HND, 227)
#else
#error Invalid value for OSEE_TC_CORE4_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 227)
OSEE_ISR_ALIGN(_core4_, 4, 227)
#endif /* OSEE_TC_CORE4_227_ISR_CAT */
#if (defined(OSEE_TC_CORE4_228_ISR_CAT))
#if (OSEE_TC_CORE4_228_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_228_ISR_TID, 228)
#elif (OSEE_TC_CORE4_228_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_228_ISR_HND, 228)
#else
#error Invalid value for OSEE_TC_CORE4_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 228)
OSEE_ISR_ALIGN(_core4_, 4, 228)
#endif /* OSEE_TC_CORE4_228_ISR_CAT */
#if (defined(OSEE_TC_CORE4_229_ISR_CAT))
#if (OSEE_TC_CORE4_229_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_229_ISR_TID, 229)
#elif (OSEE_TC_CORE4_229_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_229_ISR_HND, 229)
#else
#error Invalid value for OSEE_TC_CORE4_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 229)
OSEE_ISR_ALIGN(_core4_, 4, 229)
#endif /* OSEE_TC_CORE4_229_ISR_CAT */
#if (defined(OSEE_TC_CORE4_230_ISR_CAT))
#if (OSEE_TC_CORE4_230_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_230_ISR_TID, 230)
#elif (OSEE_TC_CORE4_230_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_230_ISR_HND, 230)
#else
#error Invalid value for OSEE_TC_CORE4_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 230)
OSEE_ISR_ALIGN(_core4_, 4, 230)
#endif /* OSEE_TC_CORE4_230_ISR_CAT */
#if (defined(OSEE_TC_CORE4_231_ISR_CAT))
#if (OSEE_TC_CORE4_231_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_231_ISR_TID, 231)
#elif (OSEE_TC_CORE4_231_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_231_ISR_HND, 231)
#else
#error Invalid value for OSEE_TC_CORE4_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 231)
OSEE_ISR_ALIGN(_core4_, 4, 231)
#endif /* OSEE_TC_CORE4_231_ISR_CAT */
#if (defined(OSEE_TC_CORE4_232_ISR_CAT))
#if (OSEE_TC_CORE4_232_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_232_ISR_TID, 232)
#elif (OSEE_TC_CORE4_232_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_232_ISR_HND, 232)
#else
#error Invalid value for OSEE_TC_CORE4_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 232)
OSEE_ISR_ALIGN(_core4_, 4, 232)
#endif /* OSEE_TC_CORE4_232_ISR_CAT */
#if (defined(OSEE_TC_CORE4_233_ISR_CAT))
#if (OSEE_TC_CORE4_233_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_233_ISR_TID, 233)
#elif (OSEE_TC_CORE4_233_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_233_ISR_HND, 233)
#else
#error Invalid value for OSEE_TC_CORE4_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 233)
OSEE_ISR_ALIGN(_core4_, 4, 233)
#endif /* OSEE_TC_CORE4_233_ISR_CAT */
#if (defined(OSEE_TC_CORE4_234_ISR_CAT))
#if (OSEE_TC_CORE4_234_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_234_ISR_TID, 234)
#elif (OSEE_TC_CORE4_234_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_234_ISR_HND, 234)
#else
#error Invalid value for OSEE_TC_CORE4_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 234)
OSEE_ISR_ALIGN(_core4_, 4, 234)
#endif /* OSEE_TC_CORE4_234_ISR_CAT */
#if (defined(OSEE_TC_CORE4_235_ISR_CAT))
#if (OSEE_TC_CORE4_235_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_235_ISR_TID, 235)
#elif (OSEE_TC_CORE4_235_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_235_ISR_HND, 235)
#else
#error Invalid value for OSEE_TC_CORE4_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 235)
OSEE_ISR_ALIGN(_core4_, 4, 235)
#endif /* OSEE_TC_CORE4_235_ISR_CAT */
#if (defined(OSEE_TC_CORE4_236_ISR_CAT))
#if (OSEE_TC_CORE4_236_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_236_ISR_TID, 236)
#elif (OSEE_TC_CORE4_236_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_236_ISR_HND, 236)
#else
#error Invalid value for OSEE_TC_CORE4_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 236)
OSEE_ISR_ALIGN(_core4_, 4, 236)
#endif /* OSEE_TC_CORE4_236_ISR_CAT */
#if (defined(OSEE_TC_CORE4_237_ISR_CAT))
#if (OSEE_TC_CORE4_237_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_237_ISR_TID, 237)
#elif (OSEE_TC_CORE4_237_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_237_ISR_HND, 237)
#else
#error Invalid value for OSEE_TC_CORE4_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 237)
OSEE_ISR_ALIGN(_core4_, 4, 237)
#endif /* OSEE_TC_CORE4_237_ISR_CAT */
#if (defined(OSEE_TC_CORE4_238_ISR_CAT))
#if (OSEE_TC_CORE4_238_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_238_ISR_TID, 238)
#elif (OSEE_TC_CORE4_238_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_238_ISR_HND, 238)
#else
#error Invalid value for OSEE_TC_CORE4_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 238)
OSEE_ISR_ALIGN(_core4_, 4, 238)
#endif /* OSEE_TC_CORE4_238_ISR_CAT */
#if (defined(OSEE_TC_CORE4_239_ISR_CAT))
#if (OSEE_TC_CORE4_239_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_239_ISR_TID, 239)
#elif (OSEE_TC_CORE4_239_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_239_ISR_HND, 239)
#else
#error Invalid value for OSEE_TC_CORE4_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 239)
OSEE_ISR_ALIGN(_core4_, 4, 239)
#endif /* OSEE_TC_CORE4_239_ISR_CAT */
#if (defined(OSEE_TC_CORE4_240_ISR_CAT))
#if (OSEE_TC_CORE4_240_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_240_ISR_TID, 240)
#elif (OSEE_TC_CORE4_240_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_240_ISR_HND, 240)
#else
#error Invalid value for OSEE_TC_CORE4_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 240)
OSEE_ISR_ALIGN(_core4_, 4, 240)
#endif /* OSEE_TC_CORE4_240_ISR_CAT */
#if (defined(OSEE_TC_CORE4_241_ISR_CAT))
#if (OSEE_TC_CORE4_241_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_241_ISR_TID, 241)
#elif (OSEE_TC_CORE4_241_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_241_ISR_HND, 241)
#else
#error Invalid value for OSEE_TC_CORE4_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 241)
OSEE_ISR_ALIGN(_core4_, 4, 241)
#endif /* OSEE_TC_CORE4_241_ISR_CAT */
#if (defined(OSEE_TC_CORE4_242_ISR_CAT))
#if (OSEE_TC_CORE4_242_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_242_ISR_TID, 242)
#elif (OSEE_TC_CORE4_242_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_242_ISR_HND, 242)
#else
#error Invalid value for OSEE_TC_CORE4_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 242)
OSEE_ISR_ALIGN(_core4_, 4, 242)
#endif /* OSEE_TC_CORE4_242_ISR_CAT */
#if (defined(OSEE_TC_CORE4_243_ISR_CAT))
#if (OSEE_TC_CORE4_243_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_243_ISR_TID, 243)
#elif (OSEE_TC_CORE4_243_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_243_ISR_HND, 243)
#else
#error Invalid value for OSEE_TC_CORE4_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 243)
OSEE_ISR_ALIGN(_core4_, 4, 243)
#endif /* OSEE_TC_CORE4_243_ISR_CAT */
#if (defined(OSEE_TC_CORE4_244_ISR_CAT))
#if (OSEE_TC_CORE4_244_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_244_ISR_TID, 244)
#elif (OSEE_TC_CORE4_244_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_244_ISR_HND, 244)
#else
#error Invalid value for OSEE_TC_CORE4_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 244)
OSEE_ISR_ALIGN(_core4_, 4, 244)
#endif /* OSEE_TC_CORE4_244_ISR_CAT */
#if (defined(OSEE_TC_CORE4_245_ISR_CAT))
#if (OSEE_TC_CORE4_245_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_245_ISR_TID, 245)
#elif (OSEE_TC_CORE4_245_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_245_ISR_HND, 245)
#else
#error Invalid value for OSEE_TC_CORE4_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 245)
OSEE_ISR_ALIGN(_core4_, 4, 245)
#endif /* OSEE_TC_CORE4_245_ISR_CAT */
#if (defined(OSEE_TC_CORE4_246_ISR_CAT))
#if (OSEE_TC_CORE4_246_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_246_ISR_TID, 246)
#elif (OSEE_TC_CORE4_246_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_246_ISR_HND, 246)
#else
#error Invalid value for OSEE_TC_CORE4_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 246)
OSEE_ISR_ALIGN(_core4_, 4, 246)
#endif /* OSEE_TC_CORE4_246_ISR_CAT */
#if (defined(OSEE_TC_CORE4_247_ISR_CAT))
#if (OSEE_TC_CORE4_247_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_247_ISR_TID, 247)
#elif (OSEE_TC_CORE4_247_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_247_ISR_HND, 247)
#else
#error Invalid value for OSEE_TC_CORE4_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 247)
OSEE_ISR_ALIGN(_core4_, 4, 247)
#endif /* OSEE_TC_CORE4_247_ISR_CAT */
#if (defined(OSEE_TC_CORE4_248_ISR_CAT))
#if (OSEE_TC_CORE4_248_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_248_ISR_TID, 248)
#elif (OSEE_TC_CORE4_248_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_248_ISR_HND, 248)
#else
#error Invalid value for OSEE_TC_CORE4_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 248)
OSEE_ISR_ALIGN(_core4_, 4, 248)
#endif /* OSEE_TC_CORE4_248_ISR_CAT */
#if (defined(OSEE_TC_CORE4_249_ISR_CAT))
#if (OSEE_TC_CORE4_249_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_249_ISR_TID, 249)
#elif (OSEE_TC_CORE4_249_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_249_ISR_HND, 249)
#else
#error Invalid value for OSEE_TC_CORE4_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 249)
OSEE_ISR_ALIGN(_core4_, 4, 249)
#endif /* OSEE_TC_CORE4_249_ISR_CAT */
#if (defined(OSEE_TC_CORE4_250_ISR_CAT))
#if (OSEE_TC_CORE4_250_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_250_ISR_TID, 250)
#elif (OSEE_TC_CORE4_250_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_250_ISR_HND, 250)
#else
#error Invalid value for OSEE_TC_CORE4_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 250)
OSEE_ISR_ALIGN(_core4_, 4, 250)
#endif /* OSEE_TC_CORE4_250_ISR_CAT */
#if (defined(OSEE_TC_CORE4_251_ISR_CAT))
#if (OSEE_TC_CORE4_251_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_251_ISR_TID, 251)
#elif (OSEE_TC_CORE4_251_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_251_ISR_HND, 251)
#else
#error Invalid value for OSEE_TC_CORE4_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 251)
OSEE_ISR_ALIGN(_core4_, 4, 251)
#endif /* OSEE_TC_CORE4_251_ISR_CAT */
#if (defined(OSEE_TC_CORE4_252_ISR_CAT))
#if (OSEE_TC_CORE4_252_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_252_ISR_TID, 252)
#elif (OSEE_TC_CORE4_252_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_252_ISR_HND, 252)
#else
#error Invalid value for OSEE_TC_CORE4_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 252)
OSEE_ISR_ALIGN(_core4_, 4, 252)
#endif /* OSEE_TC_CORE4_252_ISR_CAT */
#if (defined(OSEE_TC_CORE4_253_ISR_CAT))
#if (OSEE_TC_CORE4_253_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_253_ISR_TID, 253)
#elif (OSEE_TC_CORE4_253_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_253_ISR_HND, 253)
#else
#error Invalid value for OSEE_TC_CORE4_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 253)
OSEE_ISR_ALIGN(_core4_, 4, 253)
#endif /* OSEE_TC_CORE4_253_ISR_CAT */
#if (defined(OSEE_TC_CORE4_254_ISR_CAT))
#if (OSEE_TC_CORE4_254_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_254_ISR_TID, 254)
#elif (OSEE_TC_CORE4_254_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_254_ISR_HND, 254)
#else
#error Invalid value for OSEE_TC_CORE4_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 254)
OSEE_ISR_ALIGN(_core4_, 4, 254)
#endif /* OSEE_TC_CORE4_254_ISR_CAT */
#if (defined(OSEE_TC_CORE4_255_ISR_CAT))
#if (OSEE_TC_CORE4_255_ISR_CAT == 2)
OSEE_ISR2_DEF(_core4_, 4, OSEE_TC_CORE4_255_ISR_TID, 255)
#elif (OSEE_TC_CORE4_255_ISR_CAT == 1)
OSEE_ISR1_DEF(_core4_, 4, OSEE_TC_CORE4_255_ISR_HND, 255)
#else
#error Invalid value for OSEE_TC_CORE4_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE4_ISR_MAX_PRIO >= 255)
OSEE_ISR_ALIGN(_core4_, 4, 255)
#endif /* OSEE_TC_CORE4_255_ISR_CAT */
#endif /* OSEE_TC_CORE4_ISR_MAX_PRIO */
#if (defined(__GNUC__))
__asm__ ("\t.size __INTTAB4, . - __INTTAB4\n\
\t.section .text,\"ax\",@progbits");
#endif /* __GNUC__ */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x10U */

#if (defined(OSEE_CORE_ID_VALID_MASK)) && (OSEE_CORE_ID_VALID_MASK & 0x40U)
#if (defined(__GNUC__))
__asm__ ("\n\
  .section .inttab_cpu6, \"ax\", @progbits\n\
  .globl __INTTAB6\n\
__INTTAB6:");
/* ERIKA's Interrupt Vector Definition */
#if (defined(OSEE_TC_CORE6_ISR_MAX_PRIO))
__asm__(
"  .skip 0x20");
#endif /* OSEE_TC_CORE6_ISR_MAX_PRIO */
#endif /* __GNUC__ */
#if (defined(OSEE_TC_CORE6_ISR_MAX_PRIO))
OSEE_ISR2_DEF(_core6_, 5, -1, 1)
#if (defined(OSEE_TC_CORE6_2_ISR_CAT))
#if (OSEE_TC_CORE6_2_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_2_ISR_TID, 2)
#elif (OSEE_TC_CORE6_2_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_2_ISR_HND, 2)
#else
#error Invalid value for OSEE_TC_CORE6_2_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 2)
OSEE_ISR_ALIGN(_core6_, 5, 2)
#endif /* OSEE_TC_CORE6_2_ISR_CAT */
#if (defined(OSEE_TC_CORE6_3_ISR_CAT))
#if (OSEE_TC_CORE6_3_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_3_ISR_TID, 3)
#elif (OSEE_TC_CORE6_3_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_3_ISR_HND, 3)
#else
#error Invalid value for OSEE_TC_CORE6_3_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 3)
OSEE_ISR_ALIGN(_core6_, 5, 3)
#endif /* OSEE_TC_CORE6_3_ISR_CAT */
#if (defined(OSEE_TC_CORE6_4_ISR_CAT))
#if (OSEE_TC_CORE6_4_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_4_ISR_TID, 4)
#elif (OSEE_TC_CORE6_4_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_4_ISR_HND, 4)
#else
#error Invalid value for OSEE_TC_CORE6_4_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 4)
OSEE_ISR_ALIGN(_core6_, 5, 4)
#endif /* OSEE_TC_CORE6_4_ISR_CAT */
#if (defined(OSEE_TC_CORE6_5_ISR_CAT))
#if (OSEE_TC_CORE6_5_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_5_ISR_TID, 5)
#elif (OSEE_TC_CORE6_5_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_5_ISR_HND, 5)
#else
#error Invalid value for OSEE_TC_CORE6_5_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 5)
OSEE_ISR_ALIGN(_core6_, 5, 5)
#endif /* OSEE_TC_CORE6_5_ISR_CAT */
#if (defined(OSEE_TC_CORE6_6_ISR_CAT))
#if (OSEE_TC_CORE6_6_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_6_ISR_TID, 6)
#elif (OSEE_TC_CORE6_6_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_6_ISR_HND, 6)
#else
#error Invalid value for OSEE_TC_CORE6_6_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 6)
OSEE_ISR_ALIGN(_core6_, 5, 6)
#endif /* OSEE_TC_CORE6_6_ISR_CAT */
#if (defined(OSEE_TC_CORE6_7_ISR_CAT))
#if (OSEE_TC_CORE6_7_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_7_ISR_TID, 7)
#elif (OSEE_TC_CORE6_7_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_7_ISR_HND, 7)
#else
#error Invalid value for OSEE_TC_CORE6_7_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 7)
OSEE_ISR_ALIGN(_core6_, 5, 7)
#endif /* OSEE_TC_CORE6_7_ISR_CAT */
#if (defined(OSEE_TC_CORE6_8_ISR_CAT))
#if (OSEE_TC_CORE6_8_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_8_ISR_TID, 8)
#elif (OSEE_TC_CORE6_8_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_8_ISR_HND, 8)
#else
#error Invalid value for OSEE_TC_CORE6_8_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 8)
OSEE_ISR_ALIGN(_core6_, 5, 8)
#endif /* OSEE_TC_CORE6_8_ISR_CAT */
#if (defined(OSEE_TC_CORE6_9_ISR_CAT))
#if (OSEE_TC_CORE6_9_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_9_ISR_TID, 9)
#elif (OSEE_TC_CORE6_9_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_9_ISR_HND, 9)
#else
#error Invalid value for OSEE_TC_CORE6_9_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 9)
OSEE_ISR_ALIGN(_core6_, 5, 9)
#endif /* OSEE_TC_CORE6_9_ISR_CAT */
#if (defined(OSEE_TC_CORE6_10_ISR_CAT))
#if (OSEE_TC_CORE6_10_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_10_ISR_TID, 10)
#elif (OSEE_TC_CORE6_10_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_10_ISR_HND, 10)
#else
#error Invalid value for OSEE_TC_CORE6_10_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 10)
OSEE_ISR_ALIGN(_core6_, 5, 10)
#endif /* OSEE_TC_CORE6_10_ISR_CAT */
#if (defined(OSEE_TC_CORE6_11_ISR_CAT))
#if (OSEE_TC_CORE6_11_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_11_ISR_TID, 11)
#elif (OSEE_TC_CORE6_11_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_11_ISR_HND, 11)
#else
#error Invalid value for OSEE_TC_CORE6_11_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 11)
OSEE_ISR_ALIGN(_core6_, 5, 11)
#endif /* OSEE_TC_CORE6_11_ISR_CAT */
#if (defined(OSEE_TC_CORE6_12_ISR_CAT))
#if (OSEE_TC_CORE6_12_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_12_ISR_TID, 12)
#elif (OSEE_TC_CORE6_12_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_12_ISR_HND, 12)
#else
#error Invalid value for OSEE_TC_CORE6_12_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 12)
OSEE_ISR_ALIGN(_core6_, 5, 12)
#endif /* OSEE_TC_CORE6_12_ISR_CAT */
#if (defined(OSEE_TC_CORE6_13_ISR_CAT))
#if (OSEE_TC_CORE6_13_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_13_ISR_TID, 13)
#elif (OSEE_TC_CORE6_13_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_13_ISR_HND, 13)
#else
#error Invalid value for OSEE_TC_CORE6_13_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 13)
OSEE_ISR_ALIGN(_core6_, 5, 13)
#endif /* OSEE_TC_CORE6_13_ISR_CAT */
#if (defined(OSEE_TC_CORE6_14_ISR_CAT))
#if (OSEE_TC_CORE6_14_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_14_ISR_TID, 14)
#elif (OSEE_TC_CORE6_14_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_14_ISR_HND, 14)
#else
#error Invalid value for OSEE_TC_CORE6_14_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 14)
OSEE_ISR_ALIGN(_core6_, 5, 14)
#endif /* OSEE_TC_CORE6_14_ISR_CAT */
#if (defined(OSEE_TC_CORE6_15_ISR_CAT))
#if (OSEE_TC_CORE6_15_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_15_ISR_TID, 15)
#elif (OSEE_TC_CORE6_15_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_15_ISR_HND, 15)
#else
#error Invalid value for OSEE_TC_CORE6_15_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 15)
OSEE_ISR_ALIGN(_core6_, 5, 15)
#endif /* OSEE_TC_CORE6_15_ISR_CAT */
#if (defined(OSEE_TC_CORE6_16_ISR_CAT))
#if (OSEE_TC_CORE6_16_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_16_ISR_TID, 16)
#elif (OSEE_TC_CORE6_16_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_16_ISR_HND, 16)
#else
#error Invalid value for OSEE_TC_CORE6_16_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 16)
OSEE_ISR_ALIGN(_core6_, 5, 16)
#endif /* OSEE_TC_CORE6_16_ISR_CAT */
#if (defined(OSEE_TC_CORE6_17_ISR_CAT))
#if (OSEE_TC_CORE6_17_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_17_ISR_TID, 17)
#elif (OSEE_TC_CORE6_17_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_17_ISR_HND, 17)
#else
#error Invalid value for OSEE_TC_CORE6_17_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 17)
OSEE_ISR_ALIGN(_core6_, 5, 17)
#endif /* OSEE_TC_CORE6_17_ISR_CAT */
#if (defined(OSEE_TC_CORE6_18_ISR_CAT))
#if (OSEE_TC_CORE6_18_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_18_ISR_TID, 18)
#elif (OSEE_TC_CORE6_18_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_18_ISR_HND, 18)
#else
#error Invalid value for OSEE_TC_CORE6_18_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 18)
OSEE_ISR_ALIGN(_core6_, 5, 18)
#endif /* OSEE_TC_CORE6_18_ISR_CAT */
#if (defined(OSEE_TC_CORE6_19_ISR_CAT))
#if (OSEE_TC_CORE6_19_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_19_ISR_TID, 19)
#elif (OSEE_TC_CORE6_19_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_19_ISR_HND, 19)
#else
#error Invalid value for OSEE_TC_CORE6_19_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 19)
OSEE_ISR_ALIGN(_core6_, 5, 19)
#endif /* OSEE_TC_CORE6_19_ISR_CAT */
#if (defined(OSEE_TC_CORE6_20_ISR_CAT))
#if (OSEE_TC_CORE6_20_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_20_ISR_TID, 20)
#elif (OSEE_TC_CORE6_20_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_20_ISR_HND, 20)
#else
#error Invalid value for OSEE_TC_CORE6_20_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 20)
OSEE_ISR_ALIGN(_core6_, 5, 20)
#endif /* OSEE_TC_CORE6_20_ISR_CAT */
#if (defined(OSEE_TC_CORE6_21_ISR_CAT))
#if (OSEE_TC_CORE6_21_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_21_ISR_TID, 21)
#elif (OSEE_TC_CORE6_21_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_21_ISR_HND, 21)
#else
#error Invalid value for OSEE_TC_CORE6_21_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 21)
OSEE_ISR_ALIGN(_core6_, 5, 21)
#endif /* OSEE_TC_CORE6_21_ISR_CAT */
#if (defined(OSEE_TC_CORE6_22_ISR_CAT))
#if (OSEE_TC_CORE6_22_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_22_ISR_TID, 22)
#elif (OSEE_TC_CORE6_22_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_22_ISR_HND, 22)
#else
#error Invalid value for OSEE_TC_CORE6_22_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 22)
OSEE_ISR_ALIGN(_core6_, 5, 22)
#endif /* OSEE_TC_CORE6_22_ISR_CAT */
#if (defined(OSEE_TC_CORE6_23_ISR_CAT))
#if (OSEE_TC_CORE6_23_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_23_ISR_TID, 23)
#elif (OSEE_TC_CORE6_23_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_23_ISR_HND, 23)
#else
#error Invalid value for OSEE_TC_CORE6_23_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 23)
OSEE_ISR_ALIGN(_core6_, 5, 23)
#endif /* OSEE_TC_CORE6_23_ISR_CAT */
#if (defined(OSEE_TC_CORE6_24_ISR_CAT))
#if (OSEE_TC_CORE6_24_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_24_ISR_TID, 24)
#elif (OSEE_TC_CORE6_24_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_24_ISR_HND, 24)
#else
#error Invalid value for OSEE_TC_CORE6_24_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 24)
OSEE_ISR_ALIGN(_core6_, 5, 24)
#endif /* OSEE_TC_CORE6_24_ISR_CAT */
#if (defined(OSEE_TC_CORE6_25_ISR_CAT))
#if (OSEE_TC_CORE6_25_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_25_ISR_TID, 25)
#elif (OSEE_TC_CORE6_25_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_25_ISR_HND, 25)
#else
#error Invalid value for OSEE_TC_CORE6_25_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 25)
OSEE_ISR_ALIGN(_core6_, 5, 25)
#endif /* OSEE_TC_CORE6_25_ISR_CAT */
#if (defined(OSEE_TC_CORE6_26_ISR_CAT))
#if (OSEE_TC_CORE6_26_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_26_ISR_TID, 26)
#elif (OSEE_TC_CORE6_26_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_26_ISR_HND, 26)
#else
#error Invalid value for OSEE_TC_CORE6_26_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 26)
OSEE_ISR_ALIGN(_core6_, 5, 26)
#endif /* OSEE_TC_CORE6_26_ISR_CAT */
#if (defined(OSEE_TC_CORE6_27_ISR_CAT))
#if (OSEE_TC_CORE6_27_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_27_ISR_TID, 27)
#elif (OSEE_TC_CORE6_27_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_27_ISR_HND, 27)
#else
#error Invalid value for OSEE_TC_CORE6_27_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 27)
OSEE_ISR_ALIGN(_core6_, 5, 27)
#endif /* OSEE_TC_CORE6_27_ISR_CAT */
#if (defined(OSEE_TC_CORE6_28_ISR_CAT))
#if (OSEE_TC_CORE6_28_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_28_ISR_TID, 28)
#elif (OSEE_TC_CORE6_28_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_28_ISR_HND, 28)
#else
#error Invalid value for OSEE_TC_CORE6_28_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 28)
OSEE_ISR_ALIGN(_core6_, 5, 28)
#endif /* OSEE_TC_CORE6_28_ISR_CAT */
#if (defined(OSEE_TC_CORE6_29_ISR_CAT))
#if (OSEE_TC_CORE6_29_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_29_ISR_TID, 29)
#elif (OSEE_TC_CORE6_29_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_29_ISR_HND, 29)
#else
#error Invalid value for OSEE_TC_CORE6_29_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 29)
OSEE_ISR_ALIGN(_core6_, 5, 29)
#endif /* OSEE_TC_CORE6_29_ISR_CAT */
#if (defined(OSEE_TC_CORE6_30_ISR_CAT))
#if (OSEE_TC_CORE6_30_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_30_ISR_TID, 30)
#elif (OSEE_TC_CORE6_30_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_30_ISR_HND, 30)
#else
#error Invalid value for OSEE_TC_CORE6_30_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 30)
OSEE_ISR_ALIGN(_core6_, 5, 30)
#endif /* OSEE_TC_CORE6_30_ISR_CAT */
#if (defined(OSEE_TC_CORE6_31_ISR_CAT))
#if (OSEE_TC_CORE6_31_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_31_ISR_TID, 31)
#elif (OSEE_TC_CORE6_31_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_31_ISR_HND, 31)
#else
#error Invalid value for OSEE_TC_CORE6_31_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 31)
OSEE_ISR_ALIGN(_core6_, 5, 31)
#endif /* OSEE_TC_CORE6_31_ISR_CAT */
#if (defined(OSEE_TC_CORE6_32_ISR_CAT))
#if (OSEE_TC_CORE6_32_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_32_ISR_TID, 32)
#elif (OSEE_TC_CORE6_32_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_32_ISR_HND, 32)
#else
#error Invalid value for OSEE_TC_CORE6_32_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 32)
OSEE_ISR_ALIGN(_core6_, 5, 32)
#endif /* OSEE_TC_CORE6_32_ISR_CAT */
#if (defined(OSEE_TC_CORE6_33_ISR_CAT))
#if (OSEE_TC_CORE6_33_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_33_ISR_TID, 33)
#elif (OSEE_TC_CORE6_33_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_33_ISR_HND, 33)
#else
#error Invalid value for OSEE_TC_CORE6_33_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 33)
OSEE_ISR_ALIGN(_core6_, 5, 33)
#endif /* OSEE_TC_CORE6_33_ISR_CAT */
#if (defined(OSEE_TC_CORE6_34_ISR_CAT))
#if (OSEE_TC_CORE6_34_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_34_ISR_TID, 34)
#elif (OSEE_TC_CORE6_34_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_34_ISR_HND, 34)
#else
#error Invalid value for OSEE_TC_CORE6_34_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 34)
OSEE_ISR_ALIGN(_core6_, 5, 34)
#endif /* OSEE_TC_CORE6_34_ISR_CAT */
#if (defined(OSEE_TC_CORE6_35_ISR_CAT))
#if (OSEE_TC_CORE6_35_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_35_ISR_TID, 35)
#elif (OSEE_TC_CORE6_35_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_35_ISR_HND, 35)
#else
#error Invalid value for OSEE_TC_CORE6_35_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 35)
OSEE_ISR_ALIGN(_core6_, 5, 35)
#endif /* OSEE_TC_CORE6_35_ISR_CAT */
#if (defined(OSEE_TC_CORE6_36_ISR_CAT))
#if (OSEE_TC_CORE6_36_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_36_ISR_TID, 36)
#elif (OSEE_TC_CORE6_36_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_36_ISR_HND, 36)
#else
#error Invalid value for OSEE_TC_CORE6_36_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 36)
OSEE_ISR_ALIGN(_core6_, 5, 36)
#endif /* OSEE_TC_CORE6_36_ISR_CAT */
#if (defined(OSEE_TC_CORE6_37_ISR_CAT))
#if (OSEE_TC_CORE6_37_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_37_ISR_TID, 37)
#elif (OSEE_TC_CORE6_37_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_37_ISR_HND, 37)
#else
#error Invalid value for OSEE_TC_CORE6_37_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 37)
OSEE_ISR_ALIGN(_core6_, 5, 37)
#endif /* OSEE_TC_CORE6_37_ISR_CAT */
#if (defined(OSEE_TC_CORE6_38_ISR_CAT))
#if (OSEE_TC_CORE6_38_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_38_ISR_TID, 38)
#elif (OSEE_TC_CORE6_38_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_38_ISR_HND, 38)
#else
#error Invalid value for OSEE_TC_CORE6_38_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 38)
OSEE_ISR_ALIGN(_core6_, 5, 38)
#endif /* OSEE_TC_CORE6_38_ISR_CAT */
#if (defined(OSEE_TC_CORE6_39_ISR_CAT))
#if (OSEE_TC_CORE6_39_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_39_ISR_TID, 39)
#elif (OSEE_TC_CORE6_39_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_39_ISR_HND, 39)
#else
#error Invalid value for OSEE_TC_CORE6_39_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 39)
OSEE_ISR_ALIGN(_core6_, 5, 39)
#endif /* OSEE_TC_CORE6_39_ISR_CAT */
#if (defined(OSEE_TC_CORE6_40_ISR_CAT))
#if (OSEE_TC_CORE6_40_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_40_ISR_TID, 40)
#elif (OSEE_TC_CORE6_40_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_40_ISR_HND, 40)
#else
#error Invalid value for OSEE_TC_CORE6_40_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 40)
OSEE_ISR_ALIGN(_core6_, 5, 40)
#endif /* OSEE_TC_CORE6_40_ISR_CAT */
#if (defined(OSEE_TC_CORE6_41_ISR_CAT))
#if (OSEE_TC_CORE6_41_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_41_ISR_TID, 41)
#elif (OSEE_TC_CORE6_41_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_41_ISR_HND, 41)
#else
#error Invalid value for OSEE_TC_CORE6_41_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 41)
OSEE_ISR_ALIGN(_core6_, 5, 41)
#endif /* OSEE_TC_CORE6_41_ISR_CAT */
#if (defined(OSEE_TC_CORE6_42_ISR_CAT))
#if (OSEE_TC_CORE6_42_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_42_ISR_TID, 42)
#elif (OSEE_TC_CORE6_42_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_42_ISR_HND, 42)
#else
#error Invalid value for OSEE_TC_CORE6_42_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 42)
OSEE_ISR_ALIGN(_core6_, 5, 42)
#endif /* OSEE_TC_CORE6_42_ISR_CAT */
#if (defined(OSEE_TC_CORE6_43_ISR_CAT))
#if (OSEE_TC_CORE6_43_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_43_ISR_TID, 43)
#elif (OSEE_TC_CORE6_43_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_43_ISR_HND, 43)
#else
#error Invalid value for OSEE_TC_CORE6_43_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 43)
OSEE_ISR_ALIGN(_core6_, 5, 43)
#endif /* OSEE_TC_CORE6_43_ISR_CAT */
#if (defined(OSEE_TC_CORE6_44_ISR_CAT))
#if (OSEE_TC_CORE6_44_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_44_ISR_TID, 44)
#elif (OSEE_TC_CORE6_44_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_44_ISR_HND, 44)
#else
#error Invalid value for OSEE_TC_CORE6_44_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 44)
OSEE_ISR_ALIGN(_core6_, 5, 44)
#endif /* OSEE_TC_CORE6_44_ISR_CAT */
#if (defined(OSEE_TC_CORE6_45_ISR_CAT))
#if (OSEE_TC_CORE6_45_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_45_ISR_TID, 45)
#elif (OSEE_TC_CORE6_45_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_45_ISR_HND, 45)
#else
#error Invalid value for OSEE_TC_CORE6_45_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 45)
OSEE_ISR_ALIGN(_core6_, 5, 45)
#endif /* OSEE_TC_CORE6_45_ISR_CAT */
#if (defined(OSEE_TC_CORE6_46_ISR_CAT))
#if (OSEE_TC_CORE6_46_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_46_ISR_TID, 46)
#elif (OSEE_TC_CORE6_46_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_46_ISR_HND, 46)
#else
#error Invalid value for OSEE_TC_CORE6_46_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 46)
OSEE_ISR_ALIGN(_core6_, 5, 46)
#endif /* OSEE_TC_CORE6_46_ISR_CAT */
#if (defined(OSEE_TC_CORE6_47_ISR_CAT))
#if (OSEE_TC_CORE6_47_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_47_ISR_TID, 47)
#elif (OSEE_TC_CORE6_47_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_47_ISR_HND, 47)
#else
#error Invalid value for OSEE_TC_CORE6_47_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 47)
OSEE_ISR_ALIGN(_core6_, 5, 47)
#endif /* OSEE_TC_CORE6_47_ISR_CAT */
#if (defined(OSEE_TC_CORE6_48_ISR_CAT))
#if (OSEE_TC_CORE6_48_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_48_ISR_TID, 48)
#elif (OSEE_TC_CORE6_48_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_48_ISR_HND, 48)
#else
#error Invalid value for OSEE_TC_CORE6_48_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 48)
OSEE_ISR_ALIGN(_core6_, 5, 48)
#endif /* OSEE_TC_CORE6_48_ISR_CAT */
#if (defined(OSEE_TC_CORE6_49_ISR_CAT))
#if (OSEE_TC_CORE6_49_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_49_ISR_TID, 49)
#elif (OSEE_TC_CORE6_49_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_49_ISR_HND, 49)
#else
#error Invalid value for OSEE_TC_CORE6_49_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 49)
OSEE_ISR_ALIGN(_core6_, 5, 49)
#endif /* OSEE_TC_CORE6_49_ISR_CAT */
#if (defined(OSEE_TC_CORE6_50_ISR_CAT))
#if (OSEE_TC_CORE6_50_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_50_ISR_TID, 50)
#elif (OSEE_TC_CORE6_50_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_50_ISR_HND, 50)
#else
#error Invalid value for OSEE_TC_CORE6_50_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 50)
OSEE_ISR_ALIGN(_core6_, 5, 50)
#endif /* OSEE_TC_CORE6_50_ISR_CAT */
#if (defined(OSEE_TC_CORE6_51_ISR_CAT))
#if (OSEE_TC_CORE6_51_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_51_ISR_TID, 51)
#elif (OSEE_TC_CORE6_51_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_51_ISR_HND, 51)
#else
#error Invalid value for OSEE_TC_CORE6_51_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 51)
OSEE_ISR_ALIGN(_core6_, 5, 51)
#endif /* OSEE_TC_CORE6_51_ISR_CAT */
#if (defined(OSEE_TC_CORE6_52_ISR_CAT))
#if (OSEE_TC_CORE6_52_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_52_ISR_TID, 52)
#elif (OSEE_TC_CORE6_52_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_52_ISR_HND, 52)
#else
#error Invalid value for OSEE_TC_CORE6_52_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 52)
OSEE_ISR_ALIGN(_core6_, 5, 52)
#endif /* OSEE_TC_CORE6_52_ISR_CAT */
#if (defined(OSEE_TC_CORE6_53_ISR_CAT))
#if (OSEE_TC_CORE6_53_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_53_ISR_TID, 53)
#elif (OSEE_TC_CORE6_53_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_53_ISR_HND, 53)
#else
#error Invalid value for OSEE_TC_CORE6_53_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 53)
OSEE_ISR_ALIGN(_core6_, 5, 53)
#endif /* OSEE_TC_CORE6_53_ISR_CAT */
#if (defined(OSEE_TC_CORE6_54_ISR_CAT))
#if (OSEE_TC_CORE6_54_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_54_ISR_TID, 54)
#elif (OSEE_TC_CORE6_54_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_54_ISR_HND, 54)
#else
#error Invalid value for OSEE_TC_CORE6_54_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 54)
OSEE_ISR_ALIGN(_core6_, 5, 54)
#endif /* OSEE_TC_CORE6_54_ISR_CAT */
#if (defined(OSEE_TC_CORE6_55_ISR_CAT))
#if (OSEE_TC_CORE6_55_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_55_ISR_TID, 55)
#elif (OSEE_TC_CORE6_55_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_55_ISR_HND, 55)
#else
#error Invalid value for OSEE_TC_CORE6_55_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 55)
OSEE_ISR_ALIGN(_core6_, 5, 55)
#endif /* OSEE_TC_CORE6_55_ISR_CAT */
#if (defined(OSEE_TC_CORE6_56_ISR_CAT))
#if (OSEE_TC_CORE6_56_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_56_ISR_TID, 56)
#elif (OSEE_TC_CORE6_56_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_56_ISR_HND, 56)
#else
#error Invalid value for OSEE_TC_CORE6_56_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 56)
OSEE_ISR_ALIGN(_core6_, 5, 56)
#endif /* OSEE_TC_CORE6_56_ISR_CAT */
#if (defined(OSEE_TC_CORE6_57_ISR_CAT))
#if (OSEE_TC_CORE6_57_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_57_ISR_TID, 57)
#elif (OSEE_TC_CORE6_57_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_57_ISR_HND, 57)
#else
#error Invalid value for OSEE_TC_CORE6_57_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 57)
OSEE_ISR_ALIGN(_core6_, 5, 57)
#endif /* OSEE_TC_CORE6_57_ISR_CAT */
#if (defined(OSEE_TC_CORE6_58_ISR_CAT))
#if (OSEE_TC_CORE6_58_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_58_ISR_TID, 58)
#elif (OSEE_TC_CORE6_58_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_58_ISR_HND, 58)
#else
#error Invalid value for OSEE_TC_CORE6_58_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 58)
OSEE_ISR_ALIGN(_core6_, 5, 58)
#endif /* OSEE_TC_CORE6_58_ISR_CAT */
#if (defined(OSEE_TC_CORE6_59_ISR_CAT))
#if (OSEE_TC_CORE6_59_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_59_ISR_TID, 59)
#elif (OSEE_TC_CORE6_59_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_59_ISR_HND, 59)
#else
#error Invalid value for OSEE_TC_CORE6_59_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 59)
OSEE_ISR_ALIGN(_core6_, 5, 59)
#endif /* OSEE_TC_CORE6_59_ISR_CAT */
#if (defined(OSEE_TC_CORE6_60_ISR_CAT))
#if (OSEE_TC_CORE6_60_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_60_ISR_TID, 60)
#elif (OSEE_TC_CORE6_60_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_60_ISR_HND, 60)
#else
#error Invalid value for OSEE_TC_CORE6_60_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 60)
OSEE_ISR_ALIGN(_core6_, 5, 60)
#endif /* OSEE_TC_CORE6_60_ISR_CAT */
#if (defined(OSEE_TC_CORE6_61_ISR_CAT))
#if (OSEE_TC_CORE6_61_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_61_ISR_TID, 61)
#elif (OSEE_TC_CORE6_61_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_61_ISR_HND, 61)
#else
#error Invalid value for OSEE_TC_CORE6_61_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 61)
OSEE_ISR_ALIGN(_core6_, 5, 61)
#endif /* OSEE_TC_CORE6_61_ISR_CAT */
#if (defined(OSEE_TC_CORE6_62_ISR_CAT))
#if (OSEE_TC_CORE6_62_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_62_ISR_TID, 62)
#elif (OSEE_TC_CORE6_62_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_62_ISR_HND, 62)
#else
#error Invalid value for OSEE_TC_CORE6_62_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 62)
OSEE_ISR_ALIGN(_core6_, 5, 62)
#endif /* OSEE_TC_CORE6_62_ISR_CAT */
#if (defined(OSEE_TC_CORE6_63_ISR_CAT))
#if (OSEE_TC_CORE6_63_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_63_ISR_TID, 63)
#elif (OSEE_TC_CORE6_63_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_63_ISR_HND, 63)
#else
#error Invalid value for OSEE_TC_CORE6_63_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 63)
OSEE_ISR_ALIGN(_core6_, 5, 63)
#endif /* OSEE_TC_CORE6_63_ISR_CAT */
#if (defined(OSEE_TC_CORE6_64_ISR_CAT))
#if (OSEE_TC_CORE6_64_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_64_ISR_TID, 64)
#elif (OSEE_TC_CORE6_64_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_64_ISR_HND, 64)
#else
#error Invalid value for OSEE_TC_CORE6_64_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 64)
OSEE_ISR_ALIGN(_core6_, 5, 64)
#endif /* OSEE_TC_CORE6_64_ISR_CAT */
#if (defined(OSEE_TC_CORE6_65_ISR_CAT))
#if (OSEE_TC_CORE6_65_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_65_ISR_TID, 65)
#elif (OSEE_TC_CORE6_65_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_65_ISR_HND, 65)
#else
#error Invalid value for OSEE_TC_CORE6_65_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 65)
OSEE_ISR_ALIGN(_core6_, 5, 65)
#endif /* OSEE_TC_CORE6_65_ISR_CAT */
#if (defined(OSEE_TC_CORE6_66_ISR_CAT))
#if (OSEE_TC_CORE6_66_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_66_ISR_TID, 66)
#elif (OSEE_TC_CORE6_66_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_66_ISR_HND, 66)
#else
#error Invalid value for OSEE_TC_CORE6_66_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 66)
OSEE_ISR_ALIGN(_core6_, 5, 66)
#endif /* OSEE_TC_CORE6_66_ISR_CAT */
#if (defined(OSEE_TC_CORE6_67_ISR_CAT))
#if (OSEE_TC_CORE6_67_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_67_ISR_TID, 67)
#elif (OSEE_TC_CORE6_67_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_67_ISR_HND, 67)
#else
#error Invalid value for OSEE_TC_CORE6_67_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 67)
OSEE_ISR_ALIGN(_core6_, 5, 67)
#endif /* OSEE_TC_CORE6_67_ISR_CAT */
#if (defined(OSEE_TC_CORE6_68_ISR_CAT))
#if (OSEE_TC_CORE6_68_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_68_ISR_TID, 68)
#elif (OSEE_TC_CORE6_68_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_68_ISR_HND, 68)
#else
#error Invalid value for OSEE_TC_CORE6_68_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 68)
OSEE_ISR_ALIGN(_core6_, 5, 68)
#endif /* OSEE_TC_CORE6_68_ISR_CAT */
#if (defined(OSEE_TC_CORE6_69_ISR_CAT))
#if (OSEE_TC_CORE6_69_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_69_ISR_TID, 69)
#elif (OSEE_TC_CORE6_69_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_69_ISR_HND, 69)
#else
#error Invalid value for OSEE_TC_CORE6_69_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 69)
OSEE_ISR_ALIGN(_core6_, 5, 69)
#endif /* OSEE_TC_CORE6_69_ISR_CAT */
#if (defined(OSEE_TC_CORE6_70_ISR_CAT))
#if (OSEE_TC_CORE6_70_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_70_ISR_TID, 70)
#elif (OSEE_TC_CORE6_70_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_70_ISR_HND, 70)
#else
#error Invalid value for OSEE_TC_CORE6_70_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 70)
OSEE_ISR_ALIGN(_core6_, 5, 70)
#endif /* OSEE_TC_CORE6_70_ISR_CAT */
#if (defined(OSEE_TC_CORE6_71_ISR_CAT))
#if (OSEE_TC_CORE6_71_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_71_ISR_TID, 71)
#elif (OSEE_TC_CORE6_71_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_71_ISR_HND, 71)
#else
#error Invalid value for OSEE_TC_CORE6_71_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 71)
OSEE_ISR_ALIGN(_core6_, 5, 71)
#endif /* OSEE_TC_CORE6_71_ISR_CAT */
#if (defined(OSEE_TC_CORE6_72_ISR_CAT))
#if (OSEE_TC_CORE6_72_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_72_ISR_TID, 72)
#elif (OSEE_TC_CORE6_72_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_72_ISR_HND, 72)
#else
#error Invalid value for OSEE_TC_CORE6_72_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 72)
OSEE_ISR_ALIGN(_core6_, 5, 72)
#endif /* OSEE_TC_CORE6_72_ISR_CAT */
#if (defined(OSEE_TC_CORE6_73_ISR_CAT))
#if (OSEE_TC_CORE6_73_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_73_ISR_TID, 73)
#elif (OSEE_TC_CORE6_73_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_73_ISR_HND, 73)
#else
#error Invalid value for OSEE_TC_CORE6_73_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 73)
OSEE_ISR_ALIGN(_core6_, 5, 73)
#endif /* OSEE_TC_CORE6_73_ISR_CAT */
#if (defined(OSEE_TC_CORE6_74_ISR_CAT))
#if (OSEE_TC_CORE6_74_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_74_ISR_TID, 74)
#elif (OSEE_TC_CORE6_74_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_74_ISR_HND, 74)
#else
#error Invalid value for OSEE_TC_CORE6_74_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 74)
OSEE_ISR_ALIGN(_core6_, 5, 74)
#endif /* OSEE_TC_CORE6_74_ISR_CAT */
#if (defined(OSEE_TC_CORE6_75_ISR_CAT))
#if (OSEE_TC_CORE6_75_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_75_ISR_TID, 75)
#elif (OSEE_TC_CORE6_75_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_75_ISR_HND, 75)
#else
#error Invalid value for OSEE_TC_CORE6_75_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 75)
OSEE_ISR_ALIGN(_core6_, 5, 75)
#endif /* OSEE_TC_CORE6_75_ISR_CAT */
#if (defined(OSEE_TC_CORE6_76_ISR_CAT))
#if (OSEE_TC_CORE6_76_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_76_ISR_TID, 76)
#elif (OSEE_TC_CORE6_76_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_76_ISR_HND, 76)
#else
#error Invalid value for OSEE_TC_CORE6_76_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 76)
OSEE_ISR_ALIGN(_core6_, 5, 76)
#endif /* OSEE_TC_CORE6_76_ISR_CAT */
#if (defined(OSEE_TC_CORE6_77_ISR_CAT))
#if (OSEE_TC_CORE6_77_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_77_ISR_TID, 77)
#elif (OSEE_TC_CORE6_77_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_77_ISR_HND, 77)
#else
#error Invalid value for OSEE_TC_CORE6_77_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 77)
OSEE_ISR_ALIGN(_core6_, 5, 77)
#endif /* OSEE_TC_CORE6_77_ISR_CAT */
#if (defined(OSEE_TC_CORE6_78_ISR_CAT))
#if (OSEE_TC_CORE6_78_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_78_ISR_TID, 78)
#elif (OSEE_TC_CORE6_78_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_78_ISR_HND, 78)
#else
#error Invalid value for OSEE_TC_CORE6_78_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 78)
OSEE_ISR_ALIGN(_core6_, 5, 78)
#endif /* OSEE_TC_CORE6_78_ISR_CAT */
#if (defined(OSEE_TC_CORE6_79_ISR_CAT))
#if (OSEE_TC_CORE6_79_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_79_ISR_TID, 79)
#elif (OSEE_TC_CORE6_79_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_79_ISR_HND, 79)
#else
#error Invalid value for OSEE_TC_CORE6_79_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 79)
OSEE_ISR_ALIGN(_core6_, 5, 79)
#endif /* OSEE_TC_CORE6_79_ISR_CAT */
#if (defined(OSEE_TC_CORE6_80_ISR_CAT))
#if (OSEE_TC_CORE6_80_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_80_ISR_TID, 80)
#elif (OSEE_TC_CORE6_80_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_80_ISR_HND, 80)
#else
#error Invalid value for OSEE_TC_CORE6_80_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 80)
OSEE_ISR_ALIGN(_core6_, 5, 80)
#endif /* OSEE_TC_CORE6_80_ISR_CAT */
#if (defined(OSEE_TC_CORE6_81_ISR_CAT))
#if (OSEE_TC_CORE6_81_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_81_ISR_TID, 81)
#elif (OSEE_TC_CORE6_81_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_81_ISR_HND, 81)
#else
#error Invalid value for OSEE_TC_CORE6_81_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 81)
OSEE_ISR_ALIGN(_core6_, 5, 81)
#endif /* OSEE_TC_CORE6_81_ISR_CAT */
#if (defined(OSEE_TC_CORE6_82_ISR_CAT))
#if (OSEE_TC_CORE6_82_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_82_ISR_TID, 82)
#elif (OSEE_TC_CORE6_82_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_82_ISR_HND, 82)
#else
#error Invalid value for OSEE_TC_CORE6_82_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 82)
OSEE_ISR_ALIGN(_core6_, 5, 82)
#endif /* OSEE_TC_CORE6_82_ISR_CAT */
#if (defined(OSEE_TC_CORE6_83_ISR_CAT))
#if (OSEE_TC_CORE6_83_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_83_ISR_TID, 83)
#elif (OSEE_TC_CORE6_83_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_83_ISR_HND, 83)
#else
#error Invalid value for OSEE_TC_CORE6_83_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 83)
OSEE_ISR_ALIGN(_core6_, 5, 83)
#endif /* OSEE_TC_CORE6_83_ISR_CAT */
#if (defined(OSEE_TC_CORE6_84_ISR_CAT))
#if (OSEE_TC_CORE6_84_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_84_ISR_TID, 84)
#elif (OSEE_TC_CORE6_84_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_84_ISR_HND, 84)
#else
#error Invalid value for OSEE_TC_CORE6_84_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 84)
OSEE_ISR_ALIGN(_core6_, 5, 84)
#endif /* OSEE_TC_CORE6_84_ISR_CAT */
#if (defined(OSEE_TC_CORE6_85_ISR_CAT))
#if (OSEE_TC_CORE6_85_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_85_ISR_TID, 85)
#elif (OSEE_TC_CORE6_85_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_85_ISR_HND, 85)
#else
#error Invalid value for OSEE_TC_CORE6_85_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 85)
OSEE_ISR_ALIGN(_core6_, 5, 85)
#endif /* OSEE_TC_CORE6_85_ISR_CAT */
#if (defined(OSEE_TC_CORE6_86_ISR_CAT))
#if (OSEE_TC_CORE6_86_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_86_ISR_TID, 86)
#elif (OSEE_TC_CORE6_86_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_86_ISR_HND, 86)
#else
#error Invalid value for OSEE_TC_CORE6_86_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 86)
OSEE_ISR_ALIGN(_core6_, 5, 86)
#endif /* OSEE_TC_CORE6_86_ISR_CAT */
#if (defined(OSEE_TC_CORE6_87_ISR_CAT))
#if (OSEE_TC_CORE6_87_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_87_ISR_TID, 87)
#elif (OSEE_TC_CORE6_87_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_87_ISR_HND, 87)
#else
#error Invalid value for OSEE_TC_CORE6_87_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 87)
OSEE_ISR_ALIGN(_core6_, 5, 87)
#endif /* OSEE_TC_CORE6_87_ISR_CAT */
#if (defined(OSEE_TC_CORE6_88_ISR_CAT))
#if (OSEE_TC_CORE6_88_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_88_ISR_TID, 88)
#elif (OSEE_TC_CORE6_88_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_88_ISR_HND, 88)
#else
#error Invalid value for OSEE_TC_CORE6_88_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 88)
OSEE_ISR_ALIGN(_core6_, 5, 88)
#endif /* OSEE_TC_CORE6_88_ISR_CAT */
#if (defined(OSEE_TC_CORE6_89_ISR_CAT))
#if (OSEE_TC_CORE6_89_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_89_ISR_TID, 89)
#elif (OSEE_TC_CORE6_89_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_89_ISR_HND, 89)
#else
#error Invalid value for OSEE_TC_CORE6_89_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 89)
OSEE_ISR_ALIGN(_core6_, 5, 89)
#endif /* OSEE_TC_CORE6_89_ISR_CAT */
#if (defined(OSEE_TC_CORE6_90_ISR_CAT))
#if (OSEE_TC_CORE6_90_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_90_ISR_TID, 90)
#elif (OSEE_TC_CORE6_90_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_90_ISR_HND, 90)
#else
#error Invalid value for OSEE_TC_CORE6_90_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 90)
OSEE_ISR_ALIGN(_core6_, 5, 90)
#endif /* OSEE_TC_CORE6_90_ISR_CAT */
#if (defined(OSEE_TC_CORE6_91_ISR_CAT))
#if (OSEE_TC_CORE6_91_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_91_ISR_TID, 91)
#elif (OSEE_TC_CORE6_91_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_91_ISR_HND, 91)
#else
#error Invalid value for OSEE_TC_CORE6_91_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 91)
OSEE_ISR_ALIGN(_core6_, 5, 91)
#endif /* OSEE_TC_CORE6_91_ISR_CAT */
#if (defined(OSEE_TC_CORE6_92_ISR_CAT))
#if (OSEE_TC_CORE6_92_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_92_ISR_TID, 92)
#elif (OSEE_TC_CORE6_92_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_92_ISR_HND, 92)
#else
#error Invalid value for OSEE_TC_CORE6_92_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 92)
OSEE_ISR_ALIGN(_core6_, 5, 92)
#endif /* OSEE_TC_CORE6_92_ISR_CAT */
#if (defined(OSEE_TC_CORE6_93_ISR_CAT))
#if (OSEE_TC_CORE6_93_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_93_ISR_TID, 93)
#elif (OSEE_TC_CORE6_93_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_93_ISR_HND, 93)
#else
#error Invalid value for OSEE_TC_CORE6_93_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 93)
OSEE_ISR_ALIGN(_core6_, 5, 93)
#endif /* OSEE_TC_CORE6_93_ISR_CAT */
#if (defined(OSEE_TC_CORE6_94_ISR_CAT))
#if (OSEE_TC_CORE6_94_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_94_ISR_TID, 94)
#elif (OSEE_TC_CORE6_94_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_94_ISR_HND, 94)
#else
#error Invalid value for OSEE_TC_CORE6_94_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 94)
OSEE_ISR_ALIGN(_core6_, 5, 94)
#endif /* OSEE_TC_CORE6_94_ISR_CAT */
#if (defined(OSEE_TC_CORE6_95_ISR_CAT))
#if (OSEE_TC_CORE6_95_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_95_ISR_TID, 95)
#elif (OSEE_TC_CORE6_95_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_95_ISR_HND, 95)
#else
#error Invalid value for OSEE_TC_CORE6_95_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 95)
OSEE_ISR_ALIGN(_core6_, 5, 95)
#endif /* OSEE_TC_CORE6_95_ISR_CAT */
#if (defined(OSEE_TC_CORE6_96_ISR_CAT))
#if (OSEE_TC_CORE6_96_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_96_ISR_TID, 96)
#elif (OSEE_TC_CORE6_96_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_96_ISR_HND, 96)
#else
#error Invalid value for OSEE_TC_CORE6_96_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 96)
OSEE_ISR_ALIGN(_core6_, 5, 96)
#endif /* OSEE_TC_CORE6_96_ISR_CAT */
#if (defined(OSEE_TC_CORE6_97_ISR_CAT))
#if (OSEE_TC_CORE6_97_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_97_ISR_TID, 97)
#elif (OSEE_TC_CORE6_97_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_97_ISR_HND, 97)
#else
#error Invalid value for OSEE_TC_CORE6_97_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 97)
OSEE_ISR_ALIGN(_core6_, 5, 97)
#endif /* OSEE_TC_CORE6_97_ISR_CAT */
#if (defined(OSEE_TC_CORE6_98_ISR_CAT))
#if (OSEE_TC_CORE6_98_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_98_ISR_TID, 98)
#elif (OSEE_TC_CORE6_98_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_98_ISR_HND, 98)
#else
#error Invalid value for OSEE_TC_CORE6_98_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 98)
OSEE_ISR_ALIGN(_core6_, 5, 98)
#endif /* OSEE_TC_CORE6_98_ISR_CAT */
#if (defined(OSEE_TC_CORE6_99_ISR_CAT))
#if (OSEE_TC_CORE6_99_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_99_ISR_TID, 99)
#elif (OSEE_TC_CORE6_99_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_99_ISR_HND, 99)
#else
#error Invalid value for OSEE_TC_CORE6_99_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 99)
OSEE_ISR_ALIGN(_core6_, 5, 99)
#endif /* OSEE_TC_CORE6_99_ISR_CAT */
#if (defined(OSEE_TC_CORE6_100_ISR_CAT))
#if (OSEE_TC_CORE6_100_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_100_ISR_TID, 100)
#elif (OSEE_TC_CORE6_100_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_100_ISR_HND, 100)
#else
#error Invalid value for OSEE_TC_CORE6_100_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 100)
OSEE_ISR_ALIGN(_core6_, 5, 100)
#endif /* OSEE_TC_CORE6_100_ISR_CAT */
#if (defined(OSEE_TC_CORE6_101_ISR_CAT))
#if (OSEE_TC_CORE6_101_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_101_ISR_TID, 101)
#elif (OSEE_TC_CORE6_101_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_101_ISR_HND, 101)
#else
#error Invalid value for OSEE_TC_CORE6_101_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 101)
OSEE_ISR_ALIGN(_core6_, 5, 101)
#endif /* OSEE_TC_CORE6_101_ISR_CAT */
#if (defined(OSEE_TC_CORE6_102_ISR_CAT))
#if (OSEE_TC_CORE6_102_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_102_ISR_TID, 102)
#elif (OSEE_TC_CORE6_102_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_102_ISR_HND, 102)
#else
#error Invalid value for OSEE_TC_CORE6_102_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 102)
OSEE_ISR_ALIGN(_core6_, 5, 102)
#endif /* OSEE_TC_CORE6_102_ISR_CAT */
#if (defined(OSEE_TC_CORE6_103_ISR_CAT))
#if (OSEE_TC_CORE6_103_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_103_ISR_TID, 103)
#elif (OSEE_TC_CORE6_103_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_103_ISR_HND, 103)
#else
#error Invalid value for OSEE_TC_CORE6_103_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 103)
OSEE_ISR_ALIGN(_core6_, 5, 103)
#endif /* OSEE_TC_CORE6_103_ISR_CAT */
#if (defined(OSEE_TC_CORE6_104_ISR_CAT))
#if (OSEE_TC_CORE6_104_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_104_ISR_TID, 104)
#elif (OSEE_TC_CORE6_104_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_104_ISR_HND, 104)
#else
#error Invalid value for OSEE_TC_CORE6_104_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 104)
OSEE_ISR_ALIGN(_core6_, 5, 104)
#endif /* OSEE_TC_CORE6_104_ISR_CAT */
#if (defined(OSEE_TC_CORE6_105_ISR_CAT))
#if (OSEE_TC_CORE6_105_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_105_ISR_TID, 105)
#elif (OSEE_TC_CORE6_105_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_105_ISR_HND, 105)
#else
#error Invalid value for OSEE_TC_CORE6_105_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 105)
OSEE_ISR_ALIGN(_core6_, 5, 105)
#endif /* OSEE_TC_CORE6_105_ISR_CAT */
#if (defined(OSEE_TC_CORE6_106_ISR_CAT))
#if (OSEE_TC_CORE6_106_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_106_ISR_TID, 106)
#elif (OSEE_TC_CORE6_106_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_106_ISR_HND, 106)
#else
#error Invalid value for OSEE_TC_CORE6_106_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 106)
OSEE_ISR_ALIGN(_core6_, 5, 106)
#endif /* OSEE_TC_CORE6_106_ISR_CAT */
#if (defined(OSEE_TC_CORE6_107_ISR_CAT))
#if (OSEE_TC_CORE6_107_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_107_ISR_TID, 107)
#elif (OSEE_TC_CORE6_107_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_107_ISR_HND, 107)
#else
#error Invalid value for OSEE_TC_CORE6_107_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 107)
OSEE_ISR_ALIGN(_core6_, 5, 107)
#endif /* OSEE_TC_CORE6_107_ISR_CAT */
#if (defined(OSEE_TC_CORE6_108_ISR_CAT))
#if (OSEE_TC_CORE6_108_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_108_ISR_TID, 108)
#elif (OSEE_TC_CORE6_108_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_108_ISR_HND, 108)
#else
#error Invalid value for OSEE_TC_CORE6_108_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 108)
OSEE_ISR_ALIGN(_core6_, 5, 108)
#endif /* OSEE_TC_CORE6_108_ISR_CAT */
#if (defined(OSEE_TC_CORE6_109_ISR_CAT))
#if (OSEE_TC_CORE6_109_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_109_ISR_TID, 109)
#elif (OSEE_TC_CORE6_109_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_109_ISR_HND, 109)
#else
#error Invalid value for OSEE_TC_CORE6_109_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 109)
OSEE_ISR_ALIGN(_core6_, 5, 109)
#endif /* OSEE_TC_CORE6_109_ISR_CAT */
#if (defined(OSEE_TC_CORE6_110_ISR_CAT))
#if (OSEE_TC_CORE6_110_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_110_ISR_TID, 110)
#elif (OSEE_TC_CORE6_110_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_110_ISR_HND, 110)
#else
#error Invalid value for OSEE_TC_CORE6_110_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 110)
OSEE_ISR_ALIGN(_core6_, 5, 110)
#endif /* OSEE_TC_CORE6_110_ISR_CAT */
#if (defined(OSEE_TC_CORE6_111_ISR_CAT))
#if (OSEE_TC_CORE6_111_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_111_ISR_TID, 111)
#elif (OSEE_TC_CORE6_111_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_111_ISR_HND, 111)
#else
#error Invalid value for OSEE_TC_CORE6_111_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 111)
OSEE_ISR_ALIGN(_core6_, 5, 111)
#endif /* OSEE_TC_CORE6_111_ISR_CAT */
#if (defined(OSEE_TC_CORE6_112_ISR_CAT))
#if (OSEE_TC_CORE6_112_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_112_ISR_TID, 112)
#elif (OSEE_TC_CORE6_112_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_112_ISR_HND, 112)
#else
#error Invalid value for OSEE_TC_CORE6_112_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 112)
OSEE_ISR_ALIGN(_core6_, 5, 112)
#endif /* OSEE_TC_CORE6_112_ISR_CAT */
#if (defined(OSEE_TC_CORE6_113_ISR_CAT))
#if (OSEE_TC_CORE6_113_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_113_ISR_TID, 113)
#elif (OSEE_TC_CORE6_113_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_113_ISR_HND, 113)
#else
#error Invalid value for OSEE_TC_CORE6_113_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 113)
OSEE_ISR_ALIGN(_core6_, 5, 113)
#endif /* OSEE_TC_CORE6_113_ISR_CAT */
#if (defined(OSEE_TC_CORE6_114_ISR_CAT))
#if (OSEE_TC_CORE6_114_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_114_ISR_TID, 114)
#elif (OSEE_TC_CORE6_114_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_114_ISR_HND, 114)
#else
#error Invalid value for OSEE_TC_CORE6_114_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 114)
OSEE_ISR_ALIGN(_core6_, 5, 114)
#endif /* OSEE_TC_CORE6_114_ISR_CAT */
#if (defined(OSEE_TC_CORE6_115_ISR_CAT))
#if (OSEE_TC_CORE6_115_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_115_ISR_TID, 115)
#elif (OSEE_TC_CORE6_115_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_115_ISR_HND, 115)
#else
#error Invalid value for OSEE_TC_CORE6_115_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 115)
OSEE_ISR_ALIGN(_core6_, 5, 115)
#endif /* OSEE_TC_CORE6_115_ISR_CAT */
#if (defined(OSEE_TC_CORE6_116_ISR_CAT))
#if (OSEE_TC_CORE6_116_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_116_ISR_TID, 116)
#elif (OSEE_TC_CORE6_116_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_116_ISR_HND, 116)
#else
#error Invalid value for OSEE_TC_CORE6_116_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 116)
OSEE_ISR_ALIGN(_core6_, 5, 116)
#endif /* OSEE_TC_CORE6_116_ISR_CAT */
#if (defined(OSEE_TC_CORE6_117_ISR_CAT))
#if (OSEE_TC_CORE6_117_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_117_ISR_TID, 117)
#elif (OSEE_TC_CORE6_117_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_117_ISR_HND, 117)
#else
#error Invalid value for OSEE_TC_CORE6_117_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 117)
OSEE_ISR_ALIGN(_core6_, 5, 117)
#endif /* OSEE_TC_CORE6_117_ISR_CAT */
#if (defined(OSEE_TC_CORE6_118_ISR_CAT))
#if (OSEE_TC_CORE6_118_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_118_ISR_TID, 118)
#elif (OSEE_TC_CORE6_118_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_118_ISR_HND, 118)
#else
#error Invalid value for OSEE_TC_CORE6_118_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 118)
OSEE_ISR_ALIGN(_core6_, 5, 118)
#endif /* OSEE_TC_CORE6_118_ISR_CAT */
#if (defined(OSEE_TC_CORE6_119_ISR_CAT))
#if (OSEE_TC_CORE6_119_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_119_ISR_TID, 119)
#elif (OSEE_TC_CORE6_119_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_119_ISR_HND, 119)
#else
#error Invalid value for OSEE_TC_CORE6_119_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 119)
OSEE_ISR_ALIGN(_core6_, 5, 119)
#endif /* OSEE_TC_CORE6_119_ISR_CAT */
#if (defined(OSEE_TC_CORE6_120_ISR_CAT))
#if (OSEE_TC_CORE6_120_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_120_ISR_TID, 120)
#elif (OSEE_TC_CORE6_120_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_120_ISR_HND, 120)
#else
#error Invalid value for OSEE_TC_CORE6_120_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 120)
OSEE_ISR_ALIGN(_core6_, 5, 120)
#endif /* OSEE_TC_CORE6_120_ISR_CAT */
#if (defined(OSEE_TC_CORE6_121_ISR_CAT))
#if (OSEE_TC_CORE6_121_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_121_ISR_TID, 121)
#elif (OSEE_TC_CORE6_121_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_121_ISR_HND, 121)
#else
#error Invalid value for OSEE_TC_CORE6_121_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 121)
OSEE_ISR_ALIGN(_core6_, 5, 121)
#endif /* OSEE_TC_CORE6_121_ISR_CAT */
#if (defined(OSEE_TC_CORE6_122_ISR_CAT))
#if (OSEE_TC_CORE6_122_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_122_ISR_TID, 122)
#elif (OSEE_TC_CORE6_122_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_122_ISR_HND, 122)
#else
#error Invalid value for OSEE_TC_CORE6_122_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 122)
OSEE_ISR_ALIGN(_core6_, 5, 122)
#endif /* OSEE_TC_CORE6_122_ISR_CAT */
#if (defined(OSEE_TC_CORE6_123_ISR_CAT))
#if (OSEE_TC_CORE6_123_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_123_ISR_TID, 123)
#elif (OSEE_TC_CORE6_123_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_123_ISR_HND, 123)
#else
#error Invalid value for OSEE_TC_CORE6_123_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 123)
OSEE_ISR_ALIGN(_core6_, 5, 123)
#endif /* OSEE_TC_CORE6_123_ISR_CAT */
#if (defined(OSEE_TC_CORE6_124_ISR_CAT))
#if (OSEE_TC_CORE6_124_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_124_ISR_TID, 124)
#elif (OSEE_TC_CORE6_124_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_124_ISR_HND, 124)
#else
#error Invalid value for OSEE_TC_CORE6_124_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 124)
OSEE_ISR_ALIGN(_core6_, 5, 124)
#endif /* OSEE_TC_CORE6_124_ISR_CAT */
#if (defined(OSEE_TC_CORE6_125_ISR_CAT))
#if (OSEE_TC_CORE6_125_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_125_ISR_TID, 125)
#elif (OSEE_TC_CORE6_125_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_125_ISR_HND, 125)
#else
#error Invalid value for OSEE_TC_CORE6_125_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 125)
OSEE_ISR_ALIGN(_core6_, 5, 125)
#endif /* OSEE_TC_CORE6_125_ISR_CAT */
#if (defined(OSEE_TC_CORE6_126_ISR_CAT))
#if (OSEE_TC_CORE6_126_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_126_ISR_TID, 126)
#elif (OSEE_TC_CORE6_126_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_126_ISR_HND, 126)
#else
#error Invalid value for OSEE_TC_CORE6_126_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 126)
OSEE_ISR_ALIGN(_core6_, 5, 126)
#endif /* OSEE_TC_CORE6_126_ISR_CAT */
#if (defined(OSEE_TC_CORE6_127_ISR_CAT))
#if (OSEE_TC_CORE6_127_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_127_ISR_TID, 127)
#elif (OSEE_TC_CORE6_127_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_127_ISR_HND, 127)
#else
#error Invalid value for OSEE_TC_CORE6_127_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 127)
OSEE_ISR_ALIGN(_core6_, 5, 127)
#endif /* OSEE_TC_CORE6_127_ISR_CAT */
#if (defined(OSEE_TC_CORE6_128_ISR_CAT))
#if (OSEE_TC_CORE6_128_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_128_ISR_TID, 128)
#elif (OSEE_TC_CORE6_128_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_128_ISR_HND, 128)
#else
#error Invalid value for OSEE_TC_CORE6_128_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 128)
OSEE_ISR_ALIGN(_core6_, 5, 128)
#endif /* OSEE_TC_CORE6_128_ISR_CAT */
#if (defined(OSEE_TC_CORE6_129_ISR_CAT))
#if (OSEE_TC_CORE6_129_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_129_ISR_TID, 129)
#elif (OSEE_TC_CORE6_129_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_129_ISR_HND, 129)
#else
#error Invalid value for OSEE_TC_CORE6_129_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 129)
OSEE_ISR_ALIGN(_core6_, 5, 129)
#endif /* OSEE_TC_CORE6_129_ISR_CAT */
#if (defined(OSEE_TC_CORE6_130_ISR_CAT))
#if (OSEE_TC_CORE6_130_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_130_ISR_TID, 130)
#elif (OSEE_TC_CORE6_130_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_130_ISR_HND, 130)
#else
#error Invalid value for OSEE_TC_CORE6_130_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 130)
OSEE_ISR_ALIGN(_core6_, 5, 130)
#endif /* OSEE_TC_CORE6_130_ISR_CAT */
#if (defined(OSEE_TC_CORE6_131_ISR_CAT))
#if (OSEE_TC_CORE6_131_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_131_ISR_TID, 131)
#elif (OSEE_TC_CORE6_131_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_131_ISR_HND, 131)
#else
#error Invalid value for OSEE_TC_CORE6_131_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 131)
OSEE_ISR_ALIGN(_core6_, 5, 131)
#endif /* OSEE_TC_CORE6_131_ISR_CAT */
#if (defined(OSEE_TC_CORE6_132_ISR_CAT))
#if (OSEE_TC_CORE6_132_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_132_ISR_TID, 132)
#elif (OSEE_TC_CORE6_132_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_132_ISR_HND, 132)
#else
#error Invalid value for OSEE_TC_CORE6_132_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 132)
OSEE_ISR_ALIGN(_core6_, 5, 132)
#endif /* OSEE_TC_CORE6_132_ISR_CAT */
#if (defined(OSEE_TC_CORE6_133_ISR_CAT))
#if (OSEE_TC_CORE6_133_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_133_ISR_TID, 133)
#elif (OSEE_TC_CORE6_133_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_133_ISR_HND, 133)
#else
#error Invalid value for OSEE_TC_CORE6_133_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 133)
OSEE_ISR_ALIGN(_core6_, 5, 133)
#endif /* OSEE_TC_CORE6_133_ISR_CAT */
#if (defined(OSEE_TC_CORE6_134_ISR_CAT))
#if (OSEE_TC_CORE6_134_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_134_ISR_TID, 134)
#elif (OSEE_TC_CORE6_134_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_134_ISR_HND, 134)
#else
#error Invalid value for OSEE_TC_CORE6_134_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 134)
OSEE_ISR_ALIGN(_core6_, 5, 134)
#endif /* OSEE_TC_CORE6_134_ISR_CAT */
#if (defined(OSEE_TC_CORE6_135_ISR_CAT))
#if (OSEE_TC_CORE6_135_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_135_ISR_TID, 135)
#elif (OSEE_TC_CORE6_135_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_135_ISR_HND, 135)
#else
#error Invalid value for OSEE_TC_CORE6_135_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 135)
OSEE_ISR_ALIGN(_core6_, 5, 135)
#endif /* OSEE_TC_CORE6_135_ISR_CAT */
#if (defined(OSEE_TC_CORE6_136_ISR_CAT))
#if (OSEE_TC_CORE6_136_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_136_ISR_TID, 136)
#elif (OSEE_TC_CORE6_136_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_136_ISR_HND, 136)
#else
#error Invalid value for OSEE_TC_CORE6_136_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 136)
OSEE_ISR_ALIGN(_core6_, 5, 136)
#endif /* OSEE_TC_CORE6_136_ISR_CAT */
#if (defined(OSEE_TC_CORE6_137_ISR_CAT))
#if (OSEE_TC_CORE6_137_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_137_ISR_TID, 137)
#elif (OSEE_TC_CORE6_137_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_137_ISR_HND, 137)
#else
#error Invalid value for OSEE_TC_CORE6_137_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 137)
OSEE_ISR_ALIGN(_core6_, 5, 137)
#endif /* OSEE_TC_CORE6_137_ISR_CAT */
#if (defined(OSEE_TC_CORE6_138_ISR_CAT))
#if (OSEE_TC_CORE6_138_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_138_ISR_TID, 138)
#elif (OSEE_TC_CORE6_138_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_138_ISR_HND, 138)
#else
#error Invalid value for OSEE_TC_CORE6_138_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 138)
OSEE_ISR_ALIGN(_core6_, 5, 138)
#endif /* OSEE_TC_CORE6_138_ISR_CAT */
#if (defined(OSEE_TC_CORE6_139_ISR_CAT))
#if (OSEE_TC_CORE6_139_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_139_ISR_TID, 139)
#elif (OSEE_TC_CORE6_139_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_139_ISR_HND, 139)
#else
#error Invalid value for OSEE_TC_CORE6_139_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 139)
OSEE_ISR_ALIGN(_core6_, 5, 139)
#endif /* OSEE_TC_CORE6_139_ISR_CAT */
#if (defined(OSEE_TC_CORE6_140_ISR_CAT))
#if (OSEE_TC_CORE6_140_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_140_ISR_TID, 140)
#elif (OSEE_TC_CORE6_140_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_140_ISR_HND, 140)
#else
#error Invalid value for OSEE_TC_CORE6_140_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 140)
OSEE_ISR_ALIGN(_core6_, 5, 140)
#endif /* OSEE_TC_CORE6_140_ISR_CAT */
#if (defined(OSEE_TC_CORE6_141_ISR_CAT))
#if (OSEE_TC_CORE6_141_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_141_ISR_TID, 141)
#elif (OSEE_TC_CORE6_141_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_141_ISR_HND, 141)
#else
#error Invalid value for OSEE_TC_CORE6_141_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 141)
OSEE_ISR_ALIGN(_core6_, 5, 141)
#endif /* OSEE_TC_CORE6_141_ISR_CAT */
#if (defined(OSEE_TC_CORE6_142_ISR_CAT))
#if (OSEE_TC_CORE6_142_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_142_ISR_TID, 142)
#elif (OSEE_TC_CORE6_142_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_142_ISR_HND, 142)
#else
#error Invalid value for OSEE_TC_CORE6_142_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 142)
OSEE_ISR_ALIGN(_core6_, 5, 142)
#endif /* OSEE_TC_CORE6_142_ISR_CAT */
#if (defined(OSEE_TC_CORE6_143_ISR_CAT))
#if (OSEE_TC_CORE6_143_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_143_ISR_TID, 143)
#elif (OSEE_TC_CORE6_143_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_143_ISR_HND, 143)
#else
#error Invalid value for OSEE_TC_CORE6_143_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 143)
OSEE_ISR_ALIGN(_core6_, 5, 143)
#endif /* OSEE_TC_CORE6_143_ISR_CAT */
#if (defined(OSEE_TC_CORE6_144_ISR_CAT))
#if (OSEE_TC_CORE6_144_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_144_ISR_TID, 144)
#elif (OSEE_TC_CORE6_144_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_144_ISR_HND, 144)
#else
#error Invalid value for OSEE_TC_CORE6_144_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 144)
OSEE_ISR_ALIGN(_core6_, 5, 144)
#endif /* OSEE_TC_CORE6_144_ISR_CAT */
#if (defined(OSEE_TC_CORE6_145_ISR_CAT))
#if (OSEE_TC_CORE6_145_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_145_ISR_TID, 145)
#elif (OSEE_TC_CORE6_145_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_145_ISR_HND, 145)
#else
#error Invalid value for OSEE_TC_CORE6_145_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 145)
OSEE_ISR_ALIGN(_core6_, 5, 145)
#endif /* OSEE_TC_CORE6_145_ISR_CAT */
#if (defined(OSEE_TC_CORE6_146_ISR_CAT))
#if (OSEE_TC_CORE6_146_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_146_ISR_TID, 146)
#elif (OSEE_TC_CORE6_146_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_146_ISR_HND, 146)
#else
#error Invalid value for OSEE_TC_CORE6_146_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 146)
OSEE_ISR_ALIGN(_core6_, 5, 146)
#endif /* OSEE_TC_CORE6_146_ISR_CAT */
#if (defined(OSEE_TC_CORE6_147_ISR_CAT))
#if (OSEE_TC_CORE6_147_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_147_ISR_TID, 147)
#elif (OSEE_TC_CORE6_147_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_147_ISR_HND, 147)
#else
#error Invalid value for OSEE_TC_CORE6_147_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 147)
OSEE_ISR_ALIGN(_core6_, 5, 147)
#endif /* OSEE_TC_CORE6_147_ISR_CAT */
#if (defined(OSEE_TC_CORE6_148_ISR_CAT))
#if (OSEE_TC_CORE6_148_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_148_ISR_TID, 148)
#elif (OSEE_TC_CORE6_148_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_148_ISR_HND, 148)
#else
#error Invalid value for OSEE_TC_CORE6_148_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 148)
OSEE_ISR_ALIGN(_core6_, 5, 148)
#endif /* OSEE_TC_CORE6_148_ISR_CAT */
#if (defined(OSEE_TC_CORE6_149_ISR_CAT))
#if (OSEE_TC_CORE6_149_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_149_ISR_TID, 149)
#elif (OSEE_TC_CORE6_149_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_149_ISR_HND, 149)
#else
#error Invalid value for OSEE_TC_CORE6_149_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 149)
OSEE_ISR_ALIGN(_core6_, 5, 149)
#endif /* OSEE_TC_CORE6_149_ISR_CAT */
#if (defined(OSEE_TC_CORE6_150_ISR_CAT))
#if (OSEE_TC_CORE6_150_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_150_ISR_TID, 150)
#elif (OSEE_TC_CORE6_150_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_150_ISR_HND, 150)
#else
#error Invalid value for OSEE_TC_CORE6_150_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 150)
OSEE_ISR_ALIGN(_core6_, 5, 150)
#endif /* OSEE_TC_CORE6_150_ISR_CAT */
#if (defined(OSEE_TC_CORE6_151_ISR_CAT))
#if (OSEE_TC_CORE6_151_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_151_ISR_TID, 151)
#elif (OSEE_TC_CORE6_151_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_151_ISR_HND, 151)
#else
#error Invalid value for OSEE_TC_CORE6_151_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 151)
OSEE_ISR_ALIGN(_core6_, 5, 151)
#endif /* OSEE_TC_CORE6_151_ISR_CAT */
#if (defined(OSEE_TC_CORE6_152_ISR_CAT))
#if (OSEE_TC_CORE6_152_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_152_ISR_TID, 152)
#elif (OSEE_TC_CORE6_152_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_152_ISR_HND, 152)
#else
#error Invalid value for OSEE_TC_CORE6_152_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 152)
OSEE_ISR_ALIGN(_core6_, 5, 152)
#endif /* OSEE_TC_CORE6_152_ISR_CAT */
#if (defined(OSEE_TC_CORE6_153_ISR_CAT))
#if (OSEE_TC_CORE6_153_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_153_ISR_TID, 153)
#elif (OSEE_TC_CORE6_153_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_153_ISR_HND, 153)
#else
#error Invalid value for OSEE_TC_CORE6_153_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 153)
OSEE_ISR_ALIGN(_core6_, 5, 153)
#endif /* OSEE_TC_CORE6_153_ISR_CAT */
#if (defined(OSEE_TC_CORE6_154_ISR_CAT))
#if (OSEE_TC_CORE6_154_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_154_ISR_TID, 154)
#elif (OSEE_TC_CORE6_154_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_154_ISR_HND, 154)
#else
#error Invalid value for OSEE_TC_CORE6_154_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 154)
OSEE_ISR_ALIGN(_core6_, 5, 154)
#endif /* OSEE_TC_CORE6_154_ISR_CAT */
#if (defined(OSEE_TC_CORE6_155_ISR_CAT))
#if (OSEE_TC_CORE6_155_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_155_ISR_TID, 155)
#elif (OSEE_TC_CORE6_155_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_155_ISR_HND, 155)
#else
#error Invalid value for OSEE_TC_CORE6_155_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 155)
OSEE_ISR_ALIGN(_core6_, 5, 155)
#endif /* OSEE_TC_CORE6_155_ISR_CAT */
#if (defined(OSEE_TC_CORE6_156_ISR_CAT))
#if (OSEE_TC_CORE6_156_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_156_ISR_TID, 156)
#elif (OSEE_TC_CORE6_156_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_156_ISR_HND, 156)
#else
#error Invalid value for OSEE_TC_CORE6_156_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 156)
OSEE_ISR_ALIGN(_core6_, 5, 156)
#endif /* OSEE_TC_CORE6_156_ISR_CAT */
#if (defined(OSEE_TC_CORE6_157_ISR_CAT))
#if (OSEE_TC_CORE6_157_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_157_ISR_TID, 157)
#elif (OSEE_TC_CORE6_157_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_157_ISR_HND, 157)
#else
#error Invalid value for OSEE_TC_CORE6_157_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 157)
OSEE_ISR_ALIGN(_core6_, 5, 157)
#endif /* OSEE_TC_CORE6_157_ISR_CAT */
#if (defined(OSEE_TC_CORE6_158_ISR_CAT))
#if (OSEE_TC_CORE6_158_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_158_ISR_TID, 158)
#elif (OSEE_TC_CORE6_158_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_158_ISR_HND, 158)
#else
#error Invalid value for OSEE_TC_CORE6_158_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 158)
OSEE_ISR_ALIGN(_core6_, 5, 158)
#endif /* OSEE_TC_CORE6_158_ISR_CAT */
#if (defined(OSEE_TC_CORE6_159_ISR_CAT))
#if (OSEE_TC_CORE6_159_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_159_ISR_TID, 159)
#elif (OSEE_TC_CORE6_159_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_159_ISR_HND, 159)
#else
#error Invalid value for OSEE_TC_CORE6_159_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 159)
OSEE_ISR_ALIGN(_core6_, 5, 159)
#endif /* OSEE_TC_CORE6_159_ISR_CAT */
#if (defined(OSEE_TC_CORE6_160_ISR_CAT))
#if (OSEE_TC_CORE6_160_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_160_ISR_TID, 160)
#elif (OSEE_TC_CORE6_160_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_160_ISR_HND, 160)
#else
#error Invalid value for OSEE_TC_CORE6_160_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 160)
OSEE_ISR_ALIGN(_core6_, 5, 160)
#endif /* OSEE_TC_CORE6_160_ISR_CAT */
#if (defined(OSEE_TC_CORE6_161_ISR_CAT))
#if (OSEE_TC_CORE6_161_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_161_ISR_TID, 161)
#elif (OSEE_TC_CORE6_161_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_161_ISR_HND, 161)
#else
#error Invalid value for OSEE_TC_CORE6_161_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 161)
OSEE_ISR_ALIGN(_core6_, 5, 161)
#endif /* OSEE_TC_CORE6_161_ISR_CAT */
#if (defined(OSEE_TC_CORE6_162_ISR_CAT))
#if (OSEE_TC_CORE6_162_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_162_ISR_TID, 162)
#elif (OSEE_TC_CORE6_162_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_162_ISR_HND, 162)
#else
#error Invalid value for OSEE_TC_CORE6_162_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 162)
OSEE_ISR_ALIGN(_core6_, 5, 162)
#endif /* OSEE_TC_CORE6_162_ISR_CAT */
#if (defined(OSEE_TC_CORE6_163_ISR_CAT))
#if (OSEE_TC_CORE6_163_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_163_ISR_TID, 163)
#elif (OSEE_TC_CORE6_163_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_163_ISR_HND, 163)
#else
#error Invalid value for OSEE_TC_CORE6_163_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 163)
OSEE_ISR_ALIGN(_core6_, 5, 163)
#endif /* OSEE_TC_CORE6_163_ISR_CAT */
#if (defined(OSEE_TC_CORE6_164_ISR_CAT))
#if (OSEE_TC_CORE6_164_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_164_ISR_TID, 164)
#elif (OSEE_TC_CORE6_164_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_164_ISR_HND, 164)
#else
#error Invalid value for OSEE_TC_CORE6_164_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 164)
OSEE_ISR_ALIGN(_core6_, 5, 164)
#endif /* OSEE_TC_CORE6_164_ISR_CAT */
#if (defined(OSEE_TC_CORE6_165_ISR_CAT))
#if (OSEE_TC_CORE6_165_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_165_ISR_TID, 165)
#elif (OSEE_TC_CORE6_165_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_165_ISR_HND, 165)
#else
#error Invalid value for OSEE_TC_CORE6_165_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 165)
OSEE_ISR_ALIGN(_core6_, 5, 165)
#endif /* OSEE_TC_CORE6_165_ISR_CAT */
#if (defined(OSEE_TC_CORE6_166_ISR_CAT))
#if (OSEE_TC_CORE6_166_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_166_ISR_TID, 166)
#elif (OSEE_TC_CORE6_166_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_166_ISR_HND, 166)
#else
#error Invalid value for OSEE_TC_CORE6_166_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 166)
OSEE_ISR_ALIGN(_core6_, 5, 166)
#endif /* OSEE_TC_CORE6_166_ISR_CAT */
#if (defined(OSEE_TC_CORE6_167_ISR_CAT))
#if (OSEE_TC_CORE6_167_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_167_ISR_TID, 167)
#elif (OSEE_TC_CORE6_167_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_167_ISR_HND, 167)
#else
#error Invalid value for OSEE_TC_CORE6_167_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 167)
OSEE_ISR_ALIGN(_core6_, 5, 167)
#endif /* OSEE_TC_CORE6_167_ISR_CAT */
#if (defined(OSEE_TC_CORE6_168_ISR_CAT))
#if (OSEE_TC_CORE6_168_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_168_ISR_TID, 168)
#elif (OSEE_TC_CORE6_168_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_168_ISR_HND, 168)
#else
#error Invalid value for OSEE_TC_CORE6_168_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 168)
OSEE_ISR_ALIGN(_core6_, 5, 168)
#endif /* OSEE_TC_CORE6_168_ISR_CAT */
#if (defined(OSEE_TC_CORE6_169_ISR_CAT))
#if (OSEE_TC_CORE6_169_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_169_ISR_TID, 169)
#elif (OSEE_TC_CORE6_169_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_169_ISR_HND, 169)
#else
#error Invalid value for OSEE_TC_CORE6_169_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 169)
OSEE_ISR_ALIGN(_core6_, 5, 169)
#endif /* OSEE_TC_CORE6_169_ISR_CAT */
#if (defined(OSEE_TC_CORE6_170_ISR_CAT))
#if (OSEE_TC_CORE6_170_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_170_ISR_TID, 170)
#elif (OSEE_TC_CORE6_170_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_170_ISR_HND, 170)
#else
#error Invalid value for OSEE_TC_CORE6_170_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 170)
OSEE_ISR_ALIGN(_core6_, 5, 170)
#endif /* OSEE_TC_CORE6_170_ISR_CAT */
#if (defined(OSEE_TC_CORE6_171_ISR_CAT))
#if (OSEE_TC_CORE6_171_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_171_ISR_TID, 171)
#elif (OSEE_TC_CORE6_171_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_171_ISR_HND, 171)
#else
#error Invalid value for OSEE_TC_CORE6_171_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 171)
OSEE_ISR_ALIGN(_core6_, 5, 171)
#endif /* OSEE_TC_CORE6_171_ISR_CAT */
#if (defined(OSEE_TC_CORE6_172_ISR_CAT))
#if (OSEE_TC_CORE6_172_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_172_ISR_TID, 172)
#elif (OSEE_TC_CORE6_172_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_172_ISR_HND, 172)
#else
#error Invalid value for OSEE_TC_CORE6_172_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 172)
OSEE_ISR_ALIGN(_core6_, 5, 172)
#endif /* OSEE_TC_CORE6_172_ISR_CAT */
#if (defined(OSEE_TC_CORE6_173_ISR_CAT))
#if (OSEE_TC_CORE6_173_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_173_ISR_TID, 173)
#elif (OSEE_TC_CORE6_173_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_173_ISR_HND, 173)
#else
#error Invalid value for OSEE_TC_CORE6_173_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 173)
OSEE_ISR_ALIGN(_core6_, 5, 173)
#endif /* OSEE_TC_CORE6_173_ISR_CAT */
#if (defined(OSEE_TC_CORE6_174_ISR_CAT))
#if (OSEE_TC_CORE6_174_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_174_ISR_TID, 174)
#elif (OSEE_TC_CORE6_174_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_174_ISR_HND, 174)
#else
#error Invalid value for OSEE_TC_CORE6_174_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 174)
OSEE_ISR_ALIGN(_core6_, 5, 174)
#endif /* OSEE_TC_CORE6_174_ISR_CAT */
#if (defined(OSEE_TC_CORE6_175_ISR_CAT))
#if (OSEE_TC_CORE6_175_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_175_ISR_TID, 175)
#elif (OSEE_TC_CORE6_175_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_175_ISR_HND, 175)
#else
#error Invalid value for OSEE_TC_CORE6_175_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 175)
OSEE_ISR_ALIGN(_core6_, 5, 175)
#endif /* OSEE_TC_CORE6_175_ISR_CAT */
#if (defined(OSEE_TC_CORE6_176_ISR_CAT))
#if (OSEE_TC_CORE6_176_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_176_ISR_TID, 176)
#elif (OSEE_TC_CORE6_176_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_176_ISR_HND, 176)
#else
#error Invalid value for OSEE_TC_CORE6_176_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 176)
OSEE_ISR_ALIGN(_core6_, 5, 176)
#endif /* OSEE_TC_CORE6_176_ISR_CAT */
#if (defined(OSEE_TC_CORE6_177_ISR_CAT))
#if (OSEE_TC_CORE6_177_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_177_ISR_TID, 177)
#elif (OSEE_TC_CORE6_177_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_177_ISR_HND, 177)
#else
#error Invalid value for OSEE_TC_CORE6_177_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 177)
OSEE_ISR_ALIGN(_core6_, 5, 177)
#endif /* OSEE_TC_CORE6_177_ISR_CAT */
#if (defined(OSEE_TC_CORE6_178_ISR_CAT))
#if (OSEE_TC_CORE6_178_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_178_ISR_TID, 178)
#elif (OSEE_TC_CORE6_178_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_178_ISR_HND, 178)
#else
#error Invalid value for OSEE_TC_CORE6_178_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 178)
OSEE_ISR_ALIGN(_core6_, 5, 178)
#endif /* OSEE_TC_CORE6_178_ISR_CAT */
#if (defined(OSEE_TC_CORE6_179_ISR_CAT))
#if (OSEE_TC_CORE6_179_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_179_ISR_TID, 179)
#elif (OSEE_TC_CORE6_179_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_179_ISR_HND, 179)
#else
#error Invalid value for OSEE_TC_CORE6_179_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 179)
OSEE_ISR_ALIGN(_core6_, 5, 179)
#endif /* OSEE_TC_CORE6_179_ISR_CAT */
#if (defined(OSEE_TC_CORE6_180_ISR_CAT))
#if (OSEE_TC_CORE6_180_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_180_ISR_TID, 180)
#elif (OSEE_TC_CORE6_180_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_180_ISR_HND, 180)
#else
#error Invalid value for OSEE_TC_CORE6_180_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 180)
OSEE_ISR_ALIGN(_core6_, 5, 180)
#endif /* OSEE_TC_CORE6_180_ISR_CAT */
#if (defined(OSEE_TC_CORE6_181_ISR_CAT))
#if (OSEE_TC_CORE6_181_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_181_ISR_TID, 181)
#elif (OSEE_TC_CORE6_181_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_181_ISR_HND, 181)
#else
#error Invalid value for OSEE_TC_CORE6_181_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 181)
OSEE_ISR_ALIGN(_core6_, 5, 181)
#endif /* OSEE_TC_CORE6_181_ISR_CAT */
#if (defined(OSEE_TC_CORE6_182_ISR_CAT))
#if (OSEE_TC_CORE6_182_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_182_ISR_TID, 182)
#elif (OSEE_TC_CORE6_182_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_182_ISR_HND, 182)
#else
#error Invalid value for OSEE_TC_CORE6_182_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 182)
OSEE_ISR_ALIGN(_core6_, 5, 182)
#endif /* OSEE_TC_CORE6_182_ISR_CAT */
#if (defined(OSEE_TC_CORE6_183_ISR_CAT))
#if (OSEE_TC_CORE6_183_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_183_ISR_TID, 183)
#elif (OSEE_TC_CORE6_183_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_183_ISR_HND, 183)
#else
#error Invalid value for OSEE_TC_CORE6_183_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 183)
OSEE_ISR_ALIGN(_core6_, 5, 183)
#endif /* OSEE_TC_CORE6_183_ISR_CAT */
#if (defined(OSEE_TC_CORE6_184_ISR_CAT))
#if (OSEE_TC_CORE6_184_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_184_ISR_TID, 184)
#elif (OSEE_TC_CORE6_184_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_184_ISR_HND, 184)
#else
#error Invalid value for OSEE_TC_CORE6_184_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 184)
OSEE_ISR_ALIGN(_core6_, 5, 184)
#endif /* OSEE_TC_CORE6_184_ISR_CAT */
#if (defined(OSEE_TC_CORE6_185_ISR_CAT))
#if (OSEE_TC_CORE6_185_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_185_ISR_TID, 185)
#elif (OSEE_TC_CORE6_185_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_185_ISR_HND, 185)
#else
#error Invalid value for OSEE_TC_CORE6_185_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 185)
OSEE_ISR_ALIGN(_core6_, 5, 185)
#endif /* OSEE_TC_CORE6_185_ISR_CAT */
#if (defined(OSEE_TC_CORE6_186_ISR_CAT))
#if (OSEE_TC_CORE6_186_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_186_ISR_TID, 186)
#elif (OSEE_TC_CORE6_186_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_186_ISR_HND, 186)
#else
#error Invalid value for OSEE_TC_CORE6_186_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 186)
OSEE_ISR_ALIGN(_core6_, 5, 186)
#endif /* OSEE_TC_CORE6_186_ISR_CAT */
#if (defined(OSEE_TC_CORE6_187_ISR_CAT))
#if (OSEE_TC_CORE6_187_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_187_ISR_TID, 187)
#elif (OSEE_TC_CORE6_187_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_187_ISR_HND, 187)
#else
#error Invalid value for OSEE_TC_CORE6_187_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 187)
OSEE_ISR_ALIGN(_core6_, 5, 187)
#endif /* OSEE_TC_CORE6_187_ISR_CAT */
#if (defined(OSEE_TC_CORE6_188_ISR_CAT))
#if (OSEE_TC_CORE6_188_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_188_ISR_TID, 188)
#elif (OSEE_TC_CORE6_188_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_188_ISR_HND, 188)
#else
#error Invalid value for OSEE_TC_CORE6_188_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 188)
OSEE_ISR_ALIGN(_core6_, 5, 188)
#endif /* OSEE_TC_CORE6_188_ISR_CAT */
#if (defined(OSEE_TC_CORE6_189_ISR_CAT))
#if (OSEE_TC_CORE6_189_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_189_ISR_TID, 189)
#elif (OSEE_TC_CORE6_189_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_189_ISR_HND, 189)
#else
#error Invalid value for OSEE_TC_CORE6_189_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 189)
OSEE_ISR_ALIGN(_core6_, 5, 189)
#endif /* OSEE_TC_CORE6_189_ISR_CAT */
#if (defined(OSEE_TC_CORE6_190_ISR_CAT))
#if (OSEE_TC_CORE6_190_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_190_ISR_TID, 190)
#elif (OSEE_TC_CORE6_190_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_190_ISR_HND, 190)
#else
#error Invalid value for OSEE_TC_CORE6_190_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 190)
OSEE_ISR_ALIGN(_core6_, 5, 190)
#endif /* OSEE_TC_CORE6_190_ISR_CAT */
#if (defined(OSEE_TC_CORE6_191_ISR_CAT))
#if (OSEE_TC_CORE6_191_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_191_ISR_TID, 191)
#elif (OSEE_TC_CORE6_191_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_191_ISR_HND, 191)
#else
#error Invalid value for OSEE_TC_CORE6_191_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 191)
OSEE_ISR_ALIGN(_core6_, 5, 191)
#endif /* OSEE_TC_CORE6_191_ISR_CAT */
#if (defined(OSEE_TC_CORE6_192_ISR_CAT))
#if (OSEE_TC_CORE6_192_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_192_ISR_TID, 192)
#elif (OSEE_TC_CORE6_192_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_192_ISR_HND, 192)
#else
#error Invalid value for OSEE_TC_CORE6_192_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 192)
OSEE_ISR_ALIGN(_core6_, 5, 192)
#endif /* OSEE_TC_CORE6_192_ISR_CAT */
#if (defined(OSEE_TC_CORE6_193_ISR_CAT))
#if (OSEE_TC_CORE6_193_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_193_ISR_TID, 193)
#elif (OSEE_TC_CORE6_193_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_193_ISR_HND, 193)
#else
#error Invalid value for OSEE_TC_CORE6_193_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 193)
OSEE_ISR_ALIGN(_core6_, 5, 193)
#endif /* OSEE_TC_CORE6_193_ISR_CAT */
#if (defined(OSEE_TC_CORE6_194_ISR_CAT))
#if (OSEE_TC_CORE6_194_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_194_ISR_TID, 194)
#elif (OSEE_TC_CORE6_194_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_194_ISR_HND, 194)
#else
#error Invalid value for OSEE_TC_CORE6_194_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 194)
OSEE_ISR_ALIGN(_core6_, 5, 194)
#endif /* OSEE_TC_CORE6_194_ISR_CAT */
#if (defined(OSEE_TC_CORE6_195_ISR_CAT))
#if (OSEE_TC_CORE6_195_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_195_ISR_TID, 195)
#elif (OSEE_TC_CORE6_195_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_195_ISR_HND, 195)
#else
#error Invalid value for OSEE_TC_CORE6_195_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 195)
OSEE_ISR_ALIGN(_core6_, 5, 195)
#endif /* OSEE_TC_CORE6_195_ISR_CAT */
#if (defined(OSEE_TC_CORE6_196_ISR_CAT))
#if (OSEE_TC_CORE6_196_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_196_ISR_TID, 196)
#elif (OSEE_TC_CORE6_196_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_196_ISR_HND, 196)
#else
#error Invalid value for OSEE_TC_CORE6_196_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 196)
OSEE_ISR_ALIGN(_core6_, 5, 196)
#endif /* OSEE_TC_CORE6_196_ISR_CAT */
#if (defined(OSEE_TC_CORE6_197_ISR_CAT))
#if (OSEE_TC_CORE6_197_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_197_ISR_TID, 197)
#elif (OSEE_TC_CORE6_197_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_197_ISR_HND, 197)
#else
#error Invalid value for OSEE_TC_CORE6_197_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 197)
OSEE_ISR_ALIGN(_core6_, 5, 197)
#endif /* OSEE_TC_CORE6_197_ISR_CAT */
#if (defined(OSEE_TC_CORE6_198_ISR_CAT))
#if (OSEE_TC_CORE6_198_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_198_ISR_TID, 198)
#elif (OSEE_TC_CORE6_198_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_198_ISR_HND, 198)
#else
#error Invalid value for OSEE_TC_CORE6_198_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 198)
OSEE_ISR_ALIGN(_core6_, 5, 198)
#endif /* OSEE_TC_CORE6_198_ISR_CAT */
#if (defined(OSEE_TC_CORE6_199_ISR_CAT))
#if (OSEE_TC_CORE6_199_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_199_ISR_TID, 199)
#elif (OSEE_TC_CORE6_199_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_199_ISR_HND, 199)
#else
#error Invalid value for OSEE_TC_CORE6_199_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 199)
OSEE_ISR_ALIGN(_core6_, 5, 199)
#endif /* OSEE_TC_CORE6_199_ISR_CAT */
#if (defined(OSEE_TC_CORE6_200_ISR_CAT))
#if (OSEE_TC_CORE6_200_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_200_ISR_TID, 200)
#elif (OSEE_TC_CORE6_200_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_200_ISR_HND, 200)
#else
#error Invalid value for OSEE_TC_CORE6_200_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 200)
OSEE_ISR_ALIGN(_core6_, 5, 200)
#endif /* OSEE_TC_CORE6_200_ISR_CAT */
#if (defined(OSEE_TC_CORE6_201_ISR_CAT))
#if (OSEE_TC_CORE6_201_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_201_ISR_TID, 201)
#elif (OSEE_TC_CORE6_201_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_201_ISR_HND, 201)
#else
#error Invalid value for OSEE_TC_CORE6_201_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 201)
OSEE_ISR_ALIGN(_core6_, 5, 201)
#endif /* OSEE_TC_CORE6_201_ISR_CAT */
#if (defined(OSEE_TC_CORE6_202_ISR_CAT))
#if (OSEE_TC_CORE6_202_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_202_ISR_TID, 202)
#elif (OSEE_TC_CORE6_202_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_202_ISR_HND, 202)
#else
#error Invalid value for OSEE_TC_CORE6_202_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 202)
OSEE_ISR_ALIGN(_core6_, 5, 202)
#endif /* OSEE_TC_CORE6_202_ISR_CAT */
#if (defined(OSEE_TC_CORE6_203_ISR_CAT))
#if (OSEE_TC_CORE6_203_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_203_ISR_TID, 203)
#elif (OSEE_TC_CORE6_203_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_203_ISR_HND, 203)
#else
#error Invalid value for OSEE_TC_CORE6_203_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 203)
OSEE_ISR_ALIGN(_core6_, 5, 203)
#endif /* OSEE_TC_CORE6_203_ISR_CAT */
#if (defined(OSEE_TC_CORE6_204_ISR_CAT))
#if (OSEE_TC_CORE6_204_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_204_ISR_TID, 204)
#elif (OSEE_TC_CORE6_204_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_204_ISR_HND, 204)
#else
#error Invalid value for OSEE_TC_CORE6_204_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 204)
OSEE_ISR_ALIGN(_core6_, 5, 204)
#endif /* OSEE_TC_CORE6_204_ISR_CAT */
#if (defined(OSEE_TC_CORE6_205_ISR_CAT))
#if (OSEE_TC_CORE6_205_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_205_ISR_TID, 205)
#elif (OSEE_TC_CORE6_205_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_205_ISR_HND, 205)
#else
#error Invalid value for OSEE_TC_CORE6_205_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 205)
OSEE_ISR_ALIGN(_core6_, 5, 205)
#endif /* OSEE_TC_CORE6_205_ISR_CAT */
#if (defined(OSEE_TC_CORE6_206_ISR_CAT))
#if (OSEE_TC_CORE6_206_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_206_ISR_TID, 206)
#elif (OSEE_TC_CORE6_206_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_206_ISR_HND, 206)
#else
#error Invalid value for OSEE_TC_CORE6_206_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 206)
OSEE_ISR_ALIGN(_core6_, 5, 206)
#endif /* OSEE_TC_CORE6_206_ISR_CAT */
#if (defined(OSEE_TC_CORE6_207_ISR_CAT))
#if (OSEE_TC_CORE6_207_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_207_ISR_TID, 207)
#elif (OSEE_TC_CORE6_207_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_207_ISR_HND, 207)
#else
#error Invalid value for OSEE_TC_CORE6_207_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 207)
OSEE_ISR_ALIGN(_core6_, 5, 207)
#endif /* OSEE_TC_CORE6_207_ISR_CAT */
#if (defined(OSEE_TC_CORE6_208_ISR_CAT))
#if (OSEE_TC_CORE6_208_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_208_ISR_TID, 208)
#elif (OSEE_TC_CORE6_208_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_208_ISR_HND, 208)
#else
#error Invalid value for OSEE_TC_CORE6_208_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 208)
OSEE_ISR_ALIGN(_core6_, 5, 208)
#endif /* OSEE_TC_CORE6_208_ISR_CAT */
#if (defined(OSEE_TC_CORE6_209_ISR_CAT))
#if (OSEE_TC_CORE6_209_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_209_ISR_TID, 209)
#elif (OSEE_TC_CORE6_209_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_209_ISR_HND, 209)
#else
#error Invalid value for OSEE_TC_CORE6_209_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 209)
OSEE_ISR_ALIGN(_core6_, 5, 209)
#endif /* OSEE_TC_CORE6_209_ISR_CAT */
#if (defined(OSEE_TC_CORE6_210_ISR_CAT))
#if (OSEE_TC_CORE6_210_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_210_ISR_TID, 210)
#elif (OSEE_TC_CORE6_210_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_210_ISR_HND, 210)
#else
#error Invalid value for OSEE_TC_CORE6_210_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 210)
OSEE_ISR_ALIGN(_core6_, 5, 210)
#endif /* OSEE_TC_CORE6_210_ISR_CAT */
#if (defined(OSEE_TC_CORE6_211_ISR_CAT))
#if (OSEE_TC_CORE6_211_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_211_ISR_TID, 211)
#elif (OSEE_TC_CORE6_211_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_211_ISR_HND, 211)
#else
#error Invalid value for OSEE_TC_CORE6_211_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 211)
OSEE_ISR_ALIGN(_core6_, 5, 211)
#endif /* OSEE_TC_CORE6_211_ISR_CAT */
#if (defined(OSEE_TC_CORE6_212_ISR_CAT))
#if (OSEE_TC_CORE6_212_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_212_ISR_TID, 212)
#elif (OSEE_TC_CORE6_212_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_212_ISR_HND, 212)
#else
#error Invalid value for OSEE_TC_CORE6_212_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 212)
OSEE_ISR_ALIGN(_core6_, 5, 212)
#endif /* OSEE_TC_CORE6_212_ISR_CAT */
#if (defined(OSEE_TC_CORE6_213_ISR_CAT))
#if (OSEE_TC_CORE6_213_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_213_ISR_TID, 213)
#elif (OSEE_TC_CORE6_213_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_213_ISR_HND, 213)
#else
#error Invalid value for OSEE_TC_CORE6_213_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 213)
OSEE_ISR_ALIGN(_core6_, 5, 213)
#endif /* OSEE_TC_CORE6_213_ISR_CAT */
#if (defined(OSEE_TC_CORE6_214_ISR_CAT))
#if (OSEE_TC_CORE6_214_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_214_ISR_TID, 214)
#elif (OSEE_TC_CORE6_214_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_214_ISR_HND, 214)
#else
#error Invalid value for OSEE_TC_CORE6_214_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 214)
OSEE_ISR_ALIGN(_core6_, 5, 214)
#endif /* OSEE_TC_CORE6_214_ISR_CAT */
#if (defined(OSEE_TC_CORE6_215_ISR_CAT))
#if (OSEE_TC_CORE6_215_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_215_ISR_TID, 215)
#elif (OSEE_TC_CORE6_215_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_215_ISR_HND, 215)
#else
#error Invalid value for OSEE_TC_CORE6_215_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 215)
OSEE_ISR_ALIGN(_core6_, 5, 215)
#endif /* OSEE_TC_CORE6_215_ISR_CAT */
#if (defined(OSEE_TC_CORE6_216_ISR_CAT))
#if (OSEE_TC_CORE6_216_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_216_ISR_TID, 216)
#elif (OSEE_TC_CORE6_216_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_216_ISR_HND, 216)
#else
#error Invalid value for OSEE_TC_CORE6_216_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 216)
OSEE_ISR_ALIGN(_core6_, 5, 216)
#endif /* OSEE_TC_CORE6_216_ISR_CAT */
#if (defined(OSEE_TC_CORE6_217_ISR_CAT))
#if (OSEE_TC_CORE6_217_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_217_ISR_TID, 217)
#elif (OSEE_TC_CORE6_217_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_217_ISR_HND, 217)
#else
#error Invalid value for OSEE_TC_CORE6_217_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 217)
OSEE_ISR_ALIGN(_core6_, 5, 217)
#endif /* OSEE_TC_CORE6_217_ISR_CAT */
#if (defined(OSEE_TC_CORE6_218_ISR_CAT))
#if (OSEE_TC_CORE6_218_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_218_ISR_TID, 218)
#elif (OSEE_TC_CORE6_218_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_218_ISR_HND, 218)
#else
#error Invalid value for OSEE_TC_CORE6_218_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 218)
OSEE_ISR_ALIGN(_core6_, 5, 218)
#endif /* OSEE_TC_CORE6_218_ISR_CAT */
#if (defined(OSEE_TC_CORE6_219_ISR_CAT))
#if (OSEE_TC_CORE6_219_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_219_ISR_TID, 219)
#elif (OSEE_TC_CORE6_219_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_219_ISR_HND, 219)
#else
#error Invalid value for OSEE_TC_CORE6_219_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 219)
OSEE_ISR_ALIGN(_core6_, 5, 219)
#endif /* OSEE_TC_CORE6_219_ISR_CAT */
#if (defined(OSEE_TC_CORE6_220_ISR_CAT))
#if (OSEE_TC_CORE6_220_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_220_ISR_TID, 220)
#elif (OSEE_TC_CORE6_220_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_220_ISR_HND, 220)
#else
#error Invalid value for OSEE_TC_CORE6_220_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 220)
OSEE_ISR_ALIGN(_core6_, 5, 220)
#endif /* OSEE_TC_CORE6_220_ISR_CAT */
#if (defined(OSEE_TC_CORE6_221_ISR_CAT))
#if (OSEE_TC_CORE6_221_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_221_ISR_TID, 221)
#elif (OSEE_TC_CORE6_221_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_221_ISR_HND, 221)
#else
#error Invalid value for OSEE_TC_CORE6_221_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 221)
OSEE_ISR_ALIGN(_core6_, 5, 221)
#endif /* OSEE_TC_CORE6_221_ISR_CAT */
#if (defined(OSEE_TC_CORE6_222_ISR_CAT))
#if (OSEE_TC_CORE6_222_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_222_ISR_TID, 222)
#elif (OSEE_TC_CORE6_222_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_222_ISR_HND, 222)
#else
#error Invalid value for OSEE_TC_CORE6_222_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 222)
OSEE_ISR_ALIGN(_core6_, 5, 222)
#endif /* OSEE_TC_CORE6_222_ISR_CAT */
#if (defined(OSEE_TC_CORE6_223_ISR_CAT))
#if (OSEE_TC_CORE6_223_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_223_ISR_TID, 223)
#elif (OSEE_TC_CORE6_223_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_223_ISR_HND, 223)
#else
#error Invalid value for OSEE_TC_CORE6_223_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 223)
OSEE_ISR_ALIGN(_core6_, 5, 223)
#endif /* OSEE_TC_CORE6_223_ISR_CAT */
#if (defined(OSEE_TC_CORE6_224_ISR_CAT))
#if (OSEE_TC_CORE6_224_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_224_ISR_TID, 224)
#elif (OSEE_TC_CORE6_224_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_224_ISR_HND, 224)
#else
#error Invalid value for OSEE_TC_CORE6_224_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 224)
OSEE_ISR_ALIGN(_core6_, 5, 224)
#endif /* OSEE_TC_CORE6_224_ISR_CAT */
#if (defined(OSEE_TC_CORE6_225_ISR_CAT))
#if (OSEE_TC_CORE6_225_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_225_ISR_TID, 225)
#elif (OSEE_TC_CORE6_225_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_225_ISR_HND, 225)
#else
#error Invalid value for OSEE_TC_CORE6_225_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 225)
OSEE_ISR_ALIGN(_core6_, 5, 225)
#endif /* OSEE_TC_CORE6_225_ISR_CAT */
#if (defined(OSEE_TC_CORE6_226_ISR_CAT))
#if (OSEE_TC_CORE6_226_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_226_ISR_TID, 226)
#elif (OSEE_TC_CORE6_226_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_226_ISR_HND, 226)
#else
#error Invalid value for OSEE_TC_CORE6_226_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 226)
OSEE_ISR_ALIGN(_core6_, 5, 226)
#endif /* OSEE_TC_CORE6_226_ISR_CAT */
#if (defined(OSEE_TC_CORE6_227_ISR_CAT))
#if (OSEE_TC_CORE6_227_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_227_ISR_TID, 227)
#elif (OSEE_TC_CORE6_227_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_227_ISR_HND, 227)
#else
#error Invalid value for OSEE_TC_CORE6_227_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 227)
OSEE_ISR_ALIGN(_core6_, 5, 227)
#endif /* OSEE_TC_CORE6_227_ISR_CAT */
#if (defined(OSEE_TC_CORE6_228_ISR_CAT))
#if (OSEE_TC_CORE6_228_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_228_ISR_TID, 228)
#elif (OSEE_TC_CORE6_228_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_228_ISR_HND, 228)
#else
#error Invalid value for OSEE_TC_CORE6_228_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 228)
OSEE_ISR_ALIGN(_core6_, 5, 228)
#endif /* OSEE_TC_CORE6_228_ISR_CAT */
#if (defined(OSEE_TC_CORE6_229_ISR_CAT))
#if (OSEE_TC_CORE6_229_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_229_ISR_TID, 229)
#elif (OSEE_TC_CORE6_229_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_229_ISR_HND, 229)
#else
#error Invalid value for OSEE_TC_CORE6_229_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 229)
OSEE_ISR_ALIGN(_core6_, 5, 229)
#endif /* OSEE_TC_CORE6_229_ISR_CAT */
#if (defined(OSEE_TC_CORE6_230_ISR_CAT))
#if (OSEE_TC_CORE6_230_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_230_ISR_TID, 230)
#elif (OSEE_TC_CORE6_230_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_230_ISR_HND, 230)
#else
#error Invalid value for OSEE_TC_CORE6_230_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 230)
OSEE_ISR_ALIGN(_core6_, 5, 230)
#endif /* OSEE_TC_CORE6_230_ISR_CAT */
#if (defined(OSEE_TC_CORE6_231_ISR_CAT))
#if (OSEE_TC_CORE6_231_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_231_ISR_TID, 231)
#elif (OSEE_TC_CORE6_231_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_231_ISR_HND, 231)
#else
#error Invalid value for OSEE_TC_CORE6_231_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 231)
OSEE_ISR_ALIGN(_core6_, 5, 231)
#endif /* OSEE_TC_CORE6_231_ISR_CAT */
#if (defined(OSEE_TC_CORE6_232_ISR_CAT))
#if (OSEE_TC_CORE6_232_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_232_ISR_TID, 232)
#elif (OSEE_TC_CORE6_232_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_232_ISR_HND, 232)
#else
#error Invalid value for OSEE_TC_CORE6_232_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 232)
OSEE_ISR_ALIGN(_core6_, 5, 232)
#endif /* OSEE_TC_CORE6_232_ISR_CAT */
#if (defined(OSEE_TC_CORE6_233_ISR_CAT))
#if (OSEE_TC_CORE6_233_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_233_ISR_TID, 233)
#elif (OSEE_TC_CORE6_233_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_233_ISR_HND, 233)
#else
#error Invalid value for OSEE_TC_CORE6_233_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 233)
OSEE_ISR_ALIGN(_core6_, 5, 233)
#endif /* OSEE_TC_CORE6_233_ISR_CAT */
#if (defined(OSEE_TC_CORE6_234_ISR_CAT))
#if (OSEE_TC_CORE6_234_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_234_ISR_TID, 234)
#elif (OSEE_TC_CORE6_234_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_234_ISR_HND, 234)
#else
#error Invalid value for OSEE_TC_CORE6_234_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 234)
OSEE_ISR_ALIGN(_core6_, 5, 234)
#endif /* OSEE_TC_CORE6_234_ISR_CAT */
#if (defined(OSEE_TC_CORE6_235_ISR_CAT))
#if (OSEE_TC_CORE6_235_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_235_ISR_TID, 235)
#elif (OSEE_TC_CORE6_235_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_235_ISR_HND, 235)
#else
#error Invalid value for OSEE_TC_CORE6_235_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 235)
OSEE_ISR_ALIGN(_core6_, 5, 235)
#endif /* OSEE_TC_CORE6_235_ISR_CAT */
#if (defined(OSEE_TC_CORE6_236_ISR_CAT))
#if (OSEE_TC_CORE6_236_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_236_ISR_TID, 236)
#elif (OSEE_TC_CORE6_236_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_236_ISR_HND, 236)
#else
#error Invalid value for OSEE_TC_CORE6_236_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 236)
OSEE_ISR_ALIGN(_core6_, 5, 236)
#endif /* OSEE_TC_CORE6_236_ISR_CAT */
#if (defined(OSEE_TC_CORE6_237_ISR_CAT))
#if (OSEE_TC_CORE6_237_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_237_ISR_TID, 237)
#elif (OSEE_TC_CORE6_237_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_237_ISR_HND, 237)
#else
#error Invalid value for OSEE_TC_CORE6_237_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 237)
OSEE_ISR_ALIGN(_core6_, 5, 237)
#endif /* OSEE_TC_CORE6_237_ISR_CAT */
#if (defined(OSEE_TC_CORE6_238_ISR_CAT))
#if (OSEE_TC_CORE6_238_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_238_ISR_TID, 238)
#elif (OSEE_TC_CORE6_238_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_238_ISR_HND, 238)
#else
#error Invalid value for OSEE_TC_CORE6_238_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 238)
OSEE_ISR_ALIGN(_core6_, 5, 238)
#endif /* OSEE_TC_CORE6_238_ISR_CAT */
#if (defined(OSEE_TC_CORE6_239_ISR_CAT))
#if (OSEE_TC_CORE6_239_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_239_ISR_TID, 239)
#elif (OSEE_TC_CORE6_239_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_239_ISR_HND, 239)
#else
#error Invalid value for OSEE_TC_CORE6_239_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 239)
OSEE_ISR_ALIGN(_core6_, 5, 239)
#endif /* OSEE_TC_CORE6_239_ISR_CAT */
#if (defined(OSEE_TC_CORE6_240_ISR_CAT))
#if (OSEE_TC_CORE6_240_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_240_ISR_TID, 240)
#elif (OSEE_TC_CORE6_240_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_240_ISR_HND, 240)
#else
#error Invalid value for OSEE_TC_CORE6_240_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 240)
OSEE_ISR_ALIGN(_core6_, 5, 240)
#endif /* OSEE_TC_CORE6_240_ISR_CAT */
#if (defined(OSEE_TC_CORE6_241_ISR_CAT))
#if (OSEE_TC_CORE6_241_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_241_ISR_TID, 241)
#elif (OSEE_TC_CORE6_241_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_241_ISR_HND, 241)
#else
#error Invalid value for OSEE_TC_CORE6_241_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 241)
OSEE_ISR_ALIGN(_core6_, 5, 241)
#endif /* OSEE_TC_CORE6_241_ISR_CAT */
#if (defined(OSEE_TC_CORE6_242_ISR_CAT))
#if (OSEE_TC_CORE6_242_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_242_ISR_TID, 242)
#elif (OSEE_TC_CORE6_242_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_242_ISR_HND, 242)
#else
#error Invalid value for OSEE_TC_CORE6_242_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 242)
OSEE_ISR_ALIGN(_core6_, 5, 242)
#endif /* OSEE_TC_CORE6_242_ISR_CAT */
#if (defined(OSEE_TC_CORE6_243_ISR_CAT))
#if (OSEE_TC_CORE6_243_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_243_ISR_TID, 243)
#elif (OSEE_TC_CORE6_243_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_243_ISR_HND, 243)
#else
#error Invalid value for OSEE_TC_CORE6_243_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 243)
OSEE_ISR_ALIGN(_core6_, 5, 243)
#endif /* OSEE_TC_CORE6_243_ISR_CAT */
#if (defined(OSEE_TC_CORE6_244_ISR_CAT))
#if (OSEE_TC_CORE6_244_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_244_ISR_TID, 244)
#elif (OSEE_TC_CORE6_244_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_244_ISR_HND, 244)
#else
#error Invalid value for OSEE_TC_CORE6_244_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 244)
OSEE_ISR_ALIGN(_core6_, 5, 244)
#endif /* OSEE_TC_CORE6_244_ISR_CAT */
#if (defined(OSEE_TC_CORE6_245_ISR_CAT))
#if (OSEE_TC_CORE6_245_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_245_ISR_TID, 245)
#elif (OSEE_TC_CORE6_245_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_245_ISR_HND, 245)
#else
#error Invalid value for OSEE_TC_CORE6_245_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 245)
OSEE_ISR_ALIGN(_core6_, 5, 245)
#endif /* OSEE_TC_CORE6_245_ISR_CAT */
#if (defined(OSEE_TC_CORE6_246_ISR_CAT))
#if (OSEE_TC_CORE6_246_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_246_ISR_TID, 246)
#elif (OSEE_TC_CORE6_246_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_246_ISR_HND, 246)
#else
#error Invalid value for OSEE_TC_CORE6_246_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 246)
OSEE_ISR_ALIGN(_core6_, 5, 246)
#endif /* OSEE_TC_CORE6_246_ISR_CAT */
#if (defined(OSEE_TC_CORE6_247_ISR_CAT))
#if (OSEE_TC_CORE6_247_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_247_ISR_TID, 247)
#elif (OSEE_TC_CORE6_247_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_247_ISR_HND, 247)
#else
#error Invalid value for OSEE_TC_CORE6_247_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 247)
OSEE_ISR_ALIGN(_core6_, 5, 247)
#endif /* OSEE_TC_CORE6_247_ISR_CAT */
#if (defined(OSEE_TC_CORE6_248_ISR_CAT))
#if (OSEE_TC_CORE6_248_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_248_ISR_TID, 248)
#elif (OSEE_TC_CORE6_248_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_248_ISR_HND, 248)
#else
#error Invalid value for OSEE_TC_CORE6_248_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 248)
OSEE_ISR_ALIGN(_core6_, 5, 248)
#endif /* OSEE_TC_CORE6_248_ISR_CAT */
#if (defined(OSEE_TC_CORE6_249_ISR_CAT))
#if (OSEE_TC_CORE6_249_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_249_ISR_TID, 249)
#elif (OSEE_TC_CORE6_249_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_249_ISR_HND, 249)
#else
#error Invalid value for OSEE_TC_CORE6_249_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 249)
OSEE_ISR_ALIGN(_core6_, 5, 249)
#endif /* OSEE_TC_CORE6_249_ISR_CAT */
#if (defined(OSEE_TC_CORE6_250_ISR_CAT))
#if (OSEE_TC_CORE6_250_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_250_ISR_TID, 250)
#elif (OSEE_TC_CORE6_250_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_250_ISR_HND, 250)
#else
#error Invalid value for OSEE_TC_CORE6_250_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 250)
OSEE_ISR_ALIGN(_core6_, 5, 250)
#endif /* OSEE_TC_CORE6_250_ISR_CAT */
#if (defined(OSEE_TC_CORE6_251_ISR_CAT))
#if (OSEE_TC_CORE6_251_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_251_ISR_TID, 251)
#elif (OSEE_TC_CORE6_251_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_251_ISR_HND, 251)
#else
#error Invalid value for OSEE_TC_CORE6_251_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 251)
OSEE_ISR_ALIGN(_core6_, 5, 251)
#endif /* OSEE_TC_CORE6_251_ISR_CAT */
#if (defined(OSEE_TC_CORE6_252_ISR_CAT))
#if (OSEE_TC_CORE6_252_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_252_ISR_TID, 252)
#elif (OSEE_TC_CORE6_252_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_252_ISR_HND, 252)
#else
#error Invalid value for OSEE_TC_CORE6_252_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 252)
OSEE_ISR_ALIGN(_core6_, 5, 252)
#endif /* OSEE_TC_CORE6_252_ISR_CAT */
#if (defined(OSEE_TC_CORE6_253_ISR_CAT))
#if (OSEE_TC_CORE6_253_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_253_ISR_TID, 253)
#elif (OSEE_TC_CORE6_253_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_253_ISR_HND, 253)
#else
#error Invalid value for OSEE_TC_CORE6_253_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 253)
OSEE_ISR_ALIGN(_core6_, 5, 253)
#endif /* OSEE_TC_CORE6_253_ISR_CAT */
#if (defined(OSEE_TC_CORE6_254_ISR_CAT))
#if (OSEE_TC_CORE6_254_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_254_ISR_TID, 254)
#elif (OSEE_TC_CORE6_254_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_254_ISR_HND, 254)
#else
#error Invalid value for OSEE_TC_CORE6_254_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 254)
OSEE_ISR_ALIGN(_core6_, 5, 254)
#endif /* OSEE_TC_CORE6_254_ISR_CAT */
#if (defined(OSEE_TC_CORE6_255_ISR_CAT))
#if (OSEE_TC_CORE6_255_ISR_CAT == 2)
OSEE_ISR2_DEF(_core6_, 5, OSEE_TC_CORE6_255_ISR_TID, 255)
#elif (OSEE_TC_CORE6_255_ISR_CAT == 1)
OSEE_ISR1_DEF(_core6_, 5, OSEE_TC_CORE6_255_ISR_HND, 255)
#else
#error Invalid value for OSEE_TC_CORE6_255_ISR_CAT
#endif
#elif (defined(OSEE_TC_COMPL_INTTAB)) || (OSEE_TC_CORE6_ISR_MAX_PRIO >= 255)
OSEE_ISR_ALIGN(_core6_, 5, 255)
#endif /* OSEE_TC_CORE6_255_ISR_CAT */
#endif /* OSEE_TC_CORE6_ISR_MAX_PRIO */
#if (defined(__GNUC__))
__asm__ ("\t.size __INTTAB6, . - __INTTAB6\n\
\t.section .text,\"ax\",@progbits");
#endif /* __GNUC__ */
#endif /* OSEE_CORE_ID_VALID_MASK & 0x40U */

#endif /* !OSEE_SINGLECORE */

#if (defined(__GNUC__))
#pragma section
#endif /* __GNUC__ */

static void OSEE_COMPILER_KEEP osEE_tc_isr2_wrapper(TaskType isr2_tid) {
#if (!defined(OSEE_SINGLECORE))
  if (isr2_tid == INVALID_TASK) {
    OsEE_icr icr  = osEE_tc_get_icr();
    if (icr.bits.ccpn == 1U) {
      CONSTP2VAR(OsEE_KDB, AUTOMATIC, OS_APPL_CONST)  p_kdb = osEE_get_kernel();
      CONSTP2CONST(OsEE_KCB, AUTOMATIC, OS_APPL_DATA) p_kcb = p_kdb->p_kcb;
      CONST(OsEE_reg, AUTOMATIC) flags = osEE_begin_primitive();

      /* Ack IIRQ */
      osEE_tc_ack_signal();

      /* Check for ShutdownAllCores */
      if (p_kcb->ar_shutdown_all_cores_flag) {
        CONSTP2VAR(OsEE_CDB, AUTOMATIC, OS_APPL_CONST)
          p_curr_cdb = osEE_get_curr_core();
        osEE_shutdown_os(p_curr_cdb,
          p_kcb->ar_shutdown_all_cores_error);
      } else {
        /* Explicitly re-enable IRQs here to handle the SetEvent cross-core.
           Context restoring executes osEE_scheduler_task_wrapper_restore that
           does not explicitly re-enable interrupts,
           as instead osEE_scheduler_task_wrapper_run does, that handles
           context activation. */
        osEE_hal_enableIRQ();
        (void)osEE_scheduler_task_preemption_point(osEE_get_kernel());
        /* I close OS critical section to handle TP (Timing Protection),
           for IPL (ICR.CCPN) it would have been enough CSA restoring from RFE. */
        osEE_end_primitive(flags);
      }
    }
    /* TODO: handle other internal priorities? System Timer? */
  } else
#endif /* !OSEE_SINGLECORE */
  {
    osEE_activate_isr2(isr2_tid);
  }

#if (!defined(__TASKING__))
  osEE_tc_rslcx();
  osEE_tc_rfe();
#endif /* !__TASKING__ */
}

