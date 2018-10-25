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

/** \file   ee_hal.h
 *  \brief  HAL support visible to the application.
 *
 *  This files contains all HAL for a specific Architecture in
 *  Erika Enterprise.
 *
 *  \author Michele Pes
 *  \date   2017
 */

#ifndef OSEE_HAL_H
#define OSEE_HAL_H

/*==============================================================================
                          HAL Types and structures
 =============================================================================*/
#include "ee_cfg.h"
#include "ee_platform_types.h"
#include "ee_utils.h"
#include "ee_compiler.h"

#if (!defined(__GNUC__))
#error Unsupported compiler!
#endif /* !__GNUC__ */

#if (defined(__cplusplus))
extern "C" {
#endif

/*==============================================================================
                            Array Utilities
 =============================================================================*/

/* Fill Pattern Used for Array Monitoring */
#if (!defined(OSEE_FILL_PATTERN))
#define OSEE_FILL_PATTERN 0xA5A5A5A5U
#endif /* !OSEE_FILL_PATTERN */

/* Use Range Designated Initializers */
#define OSEE_FILL_ARRAY(array) \
  = {[0 ... (sizeof(array)/sizeof((array)[0U]) - 1U)] = OSEE_FILL_PATTERN}

/*==============================================================================
                 Utility Macros for debugging and tracing purposes
 =============================================================================*/
#if 0 /* Software Breakpoint support: temporary disabled */
#define OSEE_BREAK_POINT()        __asm__ volatile ("int 3\n")
#define OSEE_GLOBAL_LABEL(label)  __asm__(".globl " #label "\n" #label ":")
#endif /* 0 */

OSEE_STATIC_INLINE OsEE_reg osEE_x86_64_read_msr(unsigned int msr)
{
  uint32_t low, high;
  __asm__ volatile("rdmsr" : "=a" (low), "=d" (high) : "c" (msr));
  return ((OsEE_reg)high << 32U) | low;
}

OSEE_STATIC_INLINE void osEE_x86_64_write_msr(unsigned int msr, uint64_t val)
{
  __asm__ volatile("wrmsr"
    : /* no output */
    : "c" (msr), "a" ((uint32_t)val), "d" ((uint32_t)(val >> 32))
    : "memory");
}

OSEE_STATIC_INLINE void osEE_cpu_relax(void) {
  __asm__ volatile("rep; nop" : : : "memory");
}

/* Context handling functions for Tasking */
OSEE_STATIC_INLINE OsEE_addr osEE_get_SP(void)
{
  OsEE_addr sp;
  __asm__ volatile("mov %%rsp, %0\n" : "=g"(sp));
  return sp;
}


/*==============================================================================
                            Core IDs Utilities
 =============================================================================*/
/* XXX: Maybe I need a global data structures like {KDB,KCB} for the HAL
        architecture dependent? */
extern OsEE_core_id osEE_x86_64_core_id_offset;

/* Defined according to the managed PIC (APIC, x2APIC, ..) */
OsEE_core_id osEE_x86_64_get_local_apic_id(void);

OSEE_STATIC_INLINE OsEE_core_id osEE_x86_64_get_core_id_raw(void) {
       return osEE_x86_64_get_local_apic_id();
}

OSEE_STATIC_INLINE OsEE_core_id osEE_get_curr_core_id(void) {
  return  osEE_x86_64_get_core_id_raw() - osEE_x86_64_core_id_offset;
}

/*==============================================================================
                            Interrupt management
 =============================================================================*/
void osEE_x86_64_int_init(void); /*Initialize idt */
void set_interrupt_handler(uint32_t source_id, OsEE_void_cb callback);

/* Initialize the local apic*/
void osEE_x86_64_int_controller_init(void);

void call_int(unsigned int source_id);
/**
 * \def OSEE_CALL_INT(int_id)
 * Call the interrupt \int_id
 * \warning int_id must be an immediate
 */
#define OSEE_CALL_INT(int_id) __asm__ volatile("int %0" : : "n"(int_id));
void osEE_x86_64_int_send_ipi(unsigned int cpu_id, unsigned int vector);

/* Send ACK for the end of interrupt */
void osEE_x86_64_int_send_eoi(void);

/*==============================================================================
                            I/O management
 =============================================================================*/
void osEE_x86_64_ioapic_init(void);

void osEE_x86_64_ioapic_setup_irq(unsigned int pin, unsigned int vector);


enum ee_ioapic_delivery_mode {
	FIXED = 0, //!< deliver on the INTR signal of all destination processors
	LOWEST_PRIORITY, //!< deliver to lowest-priority destination CPU
	SMI, //!< system management interrupt (vector ignored)
	NMI = 4, //!< non-maskable interrupt (vector ignored)
	INIT, //!< perform INIT at destination processors (vector ignored)
	EXTINT = 7 //!< deliver as an external (PIC) interrupt on all destination processors
};

void osEE_x86_64_ioapic_setup_irq_extended(OsEE_core_id core_id,
					   unsigned int pin,
					   unsigned int vector,
					   enum ee_ioapic_delivery_mode delmode,
					   unsigned int active_low);


/*==============================================================================
                                 Timer Support
 =============================================================================*/
/* Check whether APIC supports one-shot operation using a TSC deadline value */
OSEE_STATIC_INLINE OsEE_reg osEE_x86_64_apic_tsc_deadline(void)
{
    uint32_t ecx;

    /* CPUID with EAX=1: 24th bit of ECX */
    __asm__ volatile("cpuid" : "=c" (ecx) : "a" (1) : "rbx", "rdx", "memory");

    return  (OsEE_reg)(!!(ecx & (1 << 24)));
}

/* Calibrate the timer tick frequency */
extern void osEE_x86_64_set_timer_tick_freq(uint64_t tick_freq_hz);
/* Initialize the one-shot timer with the interrupt source */
extern void osEE_x86_64_oneshot_timer_init(unsigned int vector);
/* Set the deadline for the timer */
extern void osEE_x86_64_timer_set_deadline(uint64_t timeout_ns);

/* Type of supported system timer (corresponds to system timer interrupt id) */
#define OSEE_X86_64_APIC_TIMER    32

#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_x86_64_system_timer_handler(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

/*=============================================================================
                                    ISR macros
 ============================================================================*/

/* Macro to declare ISR: always valid */
#define DeclareIsr(f) void f (void)

/* Declare an ISR (category 1) */
#define ISR1(f) void f (void)

/* Define an ISR (category 2). Used only for client code. */
#define ISR2(f) ISR1(f)

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_H */
