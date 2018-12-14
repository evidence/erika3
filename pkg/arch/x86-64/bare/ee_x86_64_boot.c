/* ###*B*###
 * Erika Enterprise, version 3
 *
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of th:we License, or (at
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

/** \file   ee_x86_64_boot.c
 *  \brief  Erika Boot (C part)
 *
 *  \author Bruno Morelli, Ida Savino
 *  \date   2018
 */

#include "ee_internal.h"
#include "ee_x86_64_memory_mgmt.h"
#include "ee_print.h"

OsEE_core_id osEE_x86_64_core_id_offset;

/* Address of the first global constructor (Defined by the linker script) */
extern void (*__CTORS_START)(void);
/* Address of the last global constructor (Defined by the linker script) */
extern void (*__CTORS_END)(void);

static void run_constructors(void)
{
    void (** volatile ctor)(void);

    /* Call constructors of all global object instances */
    for (ctor = &__CTORS_START; ctor != &__CTORS_END; ++ctor)
        (*ctor)();
}

extern int main(void);
void arch_startup(void);

void arch_startup(void)
{
    /* Initialize the virtual memory (page-table heap, libc) */
    /* Note the HAS TO BE THE FIRST INSTRUCTION!!!! */
    osEE_x86_64_memory_init();

    /* Initialize  Interrupt Descriptor Table */
    osEE_x86_64_int_init();

    /* Initialize Interrupt Controller */
    if(osEE_x86_64_int_controller_init()) {
        /* Error in interrupt controller initialization (e.g., no CPU support) */
        OSEE_PRINT("Error in interrupt controller initialization.\n");
        for(;;);
    }

    /* Handle Virtual Core IDs */
    osEE_x86_64_core_id_offset = osEE_x86_64_get_core_id_raw();

    /* Then, calibrate the platform tick frequency (APIC, TSC) */
    osEE_x86_64_calibrate_platform_tick_freq();

    /* ERIKA's Dynamic data structures initialization */
#if (defined(OSEE_API_DYNAMIC))
    osEE_os_init();
#endif /* OSEE_API_DYNAMIC */

    /* BSS segment has been already initialized by GRUB */
    run_constructors();

    main();

    __builtin_unreachable();
}
