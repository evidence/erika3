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

/** \file  ee_x86_64_int.c
 *  \brief  Interrupt configuration.
 *
 *  This files contains the interrupt configuration implementation for
 *  a specific Architecture in Erika Enterprise.
 *
 *  \author  Michele Pes
 *  \date    2017
 */

#include "ee_internal.h"

#define NUM_IDT_DESC            64
#define APIC_LVL_ASSERT         (1 << 14)
#define INMATE_CS64             0x10

#define IDT_ATTR_PRESENT        0x80
#define IDT_ATTR_I386_INT_GATE  0xE

#define X86_TABLE_GDT           0
#define X86_TABLE_LDT           1

#define X86_PRIV_LEVEL_0        0
#define X86_PRIV_LEVEL_1        1
#define X86_PRIV_LEVEL_2        2
#define X86_PRIV_LEVEL_3        3

#define INT_CAT_ISR1            1
#define INT_CAT_ISR2            2


struct OsEE_x86_64_dtr {
    uint16_t limit;
    void*    base;
} __attribute__((packed));

struct OsEE_x86_64_idt {
   uint16_t offset_1; /* offset bits 0..15 */
   uint16_t selector; /* a code segment selector in GDT or LDT */
   uint8_t ist;       /* bits 0..2 holds IST offset, rest of bits zero. */
   uint8_t type_attr; /* type and attributes */
   uint16_t offset_2; /* offset bits 16..31 */
   uint32_t offset_3; /* offset bits 32..63 */
   uint32_t zero;     /* reserved */
} __attribute__((packed));
/* static uint32_t idt[NUM_IDT_DESC * 4]; */
static struct OsEE_x86_64_idt osEE_x86_64_idt_entry[NUM_IDT_DESC];

typedef struct {
  uintptr_t isr_hnd;
  uint8_t   category;
} OsEE_x86_64_lookup_table;
static OsEE_x86_64_lookup_table osEE_isr_task_lookup_table[NUM_IDT_DESC];


extern void osEE_x86_64_irq_base(void);


static inline void osEE_x86_64_write_idtr(struct OsEE_x86_64_dtr *val)
{
    asm volatile("lidt %0" : : "m" (*val));
}

void osEE_x86_64_int_send_ipi(unsigned int cpu_id, unsigned int vector)
{
    /* Fig. 10-28 Intel vol 3, set parameters + assert level */
    osEE_x86_64_write_msr(X2APIC_ICR,
                          ((uint64_t)cpu_id << 32) | APIC_LVL_ASSERT | vector);
}

void osEE_x86_64_int_init(void)
{
    struct OsEE_x86_64_dtr dtr;

    dtr.limit = sizeof(osEE_x86_64_idt_entry) - 1;
    dtr.base = osEE_x86_64_idt_entry;

    /* Set spurious interrupt vector 255 */
    osEE_x86_64_write_msr(X2APIC_SPIV, 0x1ff);

    osEE_x86_64_write_idtr(&dtr);
}

static void __attribute__((used)) osEE_x86_64_isr_wrapper(unsigned int vector)
{
    const OsEE_x86_64_lookup_table* const p_int =
        &osEE_isr_task_lookup_table[vector];

    if (p_int->category == INT_CAT_ISR1) {
        OsEE_void_cb handler = (OsEE_void_cb)p_int->isr_hnd;
        (*handler)();
        osEE_x86_64_write_msr(X2APIC_EOI, APIC_EOI_ACK);
    }
    else
        osEE_activate_isr2(p_int->isr_hnd);
}

static void osEE_x86_64_set_int_handler_(uint32_t  source_id,
                             uint8_t   int_type,
                             uintptr_t hnd)
{
    OsEE_x86_64_lookup_table* const p_int_tag =
        &osEE_isr_task_lookup_table[source_id];

    struct OsEE_x86_64_idt* const p_idt_entry =
        &osEE_x86_64_idt_entry[source_id];

    const unsigned long entry = (unsigned long)osEE_x86_64_irq_base
                                + (source_id * 16);

    p_idt_entry->offset_1 = entry & 0xffff;
    p_idt_entry->selector = X86_TABLE_GDT | X86_PRIV_LEVEL_0 | INMATE_CS64;
    p_idt_entry->ist = 0;
    p_idt_entry->type_attr = IDT_ATTR_PRESENT | IDT_ATTR_I386_INT_GATE;
    p_idt_entry->offset_2 = (entry >> 16) & 0xffff;
    p_idt_entry->offset_3 = (entry >> 32) & 0xffffffff;
/*
    idt[source_id * 4] = (entry & 0xffff) | (INMATE_CS64 << 16);
    idt[source_id * 4 + 1] = 0x8e00 | (entry & 0xffff0000);
    idt[source_id * 4 + 2] = entry >> 32;
*/

    p_int_tag->category = int_type;
    p_int_tag->isr_hnd = hnd;
}

void set_interrupt_handler(uint32_t source_id, OsEE_void_cb callback)
{
  osEE_x86_64_set_int_handler_(source_id, INT_CAT_ISR1, (uintptr_t)callback);
}

void call_int(unsigned int source_id)
{
  osEE_x86_64_int_send_ipi(osEE_x86_64_get_core_id_raw(), source_id);
}

#if (defined(OSEE_API_DYNAMIC))
StatusType osEE_hal_set_isr2_source
(
  OsEE_TDB * p_tdb,
  ISRSource  source_id
)
{
  osEE_x86_64_set_int_handler_(source_id, INT_CAT_ISR2, (uintptr_t)p_tdb->tid);
  return E_OK;
}
#endif /* OSEE_API_DYNAMIC */

FUNC(OsEE_bool, OS_CODE) osEE_cpu_startos(void)
{
  OsEE_bool const continue_startos = osEE_std_cpu_startos();

#if (!defined(OSEE_API_DYNAMIC))
  if (continue_startos == OSEE_TRUE) {
    size_t i;
#if (!defined(OSEE_SINGLECORE))
    CoreIdType const core_id = osEE_get_curr_core_id();
#endif /* !OSEE_SINGLECORE */
/* Initialize ISRs of this core */
    OsEE_KDB * const p_kdb   = osEE_get_kernel();

    for (i = 0U; i < (p_kdb->tdb_array_size - 1U); ++i) {
      /* ISR2 initialization */
      OsEE_TDB  * const p_tdb = (*p_kdb->p_tdb_ptr_array)[i];

#if (!defined(OSEE_SINGLECORE))
      if (p_tdb->orig_core_id != core_id) {
        continue;
      } else
#endif /* !OSEE_SINGLECORE */
      if (p_tdb->task_type == OSEE_TASK_TYPE_ISR2) {
        osEE_x86_64_set_int_handler_(p_tdb->hdb.isr2_src, INT_CAT_ISR2, i);
      }
    }
#if (defined(OSEE_HAS_SYSTEM_TIMER))
    osEE_x86_64_system_timer_init();
#endif /* OSEE_HAS_SYSTEM_TIMER */
  }
#endif /* !OSEE_API_DYNAMIC */
  return continue_startos;
}

#ifdef __x86_64__

asm(
".macro irq_prologue vector\n\t"
    "push %rdi\n\t"
    "mov $vector,%rdi\n\t"
    "jmp irq_common\n"
".endm\n\t"


".global osEE_x86_64_irq_base\n\t"
".balign 16\n"

"osEE_x86_64_irq_base: \n"
"vector=0   \n"
".rept 64   \n"
    "irq_prologue vector    \n\t"
    "vector = vector + 1    \n\t"
    ".balign 16             \n\t"
".endr                      \n"

"irq_common:    \n\t"
    "push %rax  \n\t"
    "push %rcx  \n\t"
    "push %rdx  \n\t"
    "push %rsi  \n\t"
    "push %r8   \n\t"
    "push %r9   \n\t"
    "push %r10  \n\t"
    "push %r11  \n\t"

    "call osEE_x86_64_isr_wrapper  \n\t"

    "pop %r11   \n\t"
    "pop %r10   \n\t"
    "pop %r9    \n\t"
    "pop %r8    \n\t"
    "pop %rsi   \n\t"
    "pop %rdx   \n\t"
    "pop %rcx   \n\t"
    "pop %rax   \n\t"

    "pop %rdi   \n\t"

    "iretq"
);

#else
#error Not Implemented!
#endif
