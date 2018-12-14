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

/** \file   ee_x86_64_x2apic_internal.h
 *  \brief  Specific functions/macros for X2APIC management.
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#ifndef OSEE_X86_64_X2APIC_INTERNAL_H
#define OSEE_X86_64_X2APIC_INTERNAL_H

#include "ee_x86_64_apic_internal.h"

#define X2APIC_CONVERT(x)	(x>>4) + 0x800U

/* Define whether the X2APIC is in TSC-Deadline mode according to configuration */
extern uint64_t x86_64_x2apic_tsc_deadline;

/* Check whether APIC supports one-shot operation using a TSC deadline value */
OSEE_STATIC_INLINE
OsEE_reg osEE_x86_64_apic_tsc_deadline(void)
{
    uint32_t ecx;

    /* CPUID with EAX=1: 24th bit of ECX */
    __asm__ volatile("cpuid" : "=c" (ecx) : "a" (1) : "rbx", "rdx", "memory");

    return  (OsEE_reg)(!!(ecx & (1 << 24)));
}

/* Set the x2apic mode according to OIL configuration */
int osEE_x86_64_set_x2apic_mode(void);

/* Macro used in X2APIC-TSC deadline mode */
#define OSEE_X86_64_IA32_TSC_DEADLINE  (0x6E0)
#define OSEE_X86_64_LVTT_TSC_DEADLINE  (1 << 18)

#endif /* OSEE_X86_64_X2APIC_INTERNAL_H */

