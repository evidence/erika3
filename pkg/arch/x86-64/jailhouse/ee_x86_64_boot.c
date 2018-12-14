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

#include "ee_internal.h"
#include <inmate.h>
#include "ee_print.h"
#if 0
#ifdef CONFIG_UART_OXPCIE952
#define UART_BASE       0xe010
#else
#define UART_BASE       0x3f8
#endif
#define UART_LSR        0x5
#define UART_LSR_THRE   0x20
#define UART_IDLE_LOOPS 100
#endif

OsEE_core_id osEE_x86_64_core_id_offset;

extern int main(void);

void inmate_main(void)
{
    bool loop = true;
/*
    int n;
    printk_uart_base = UART_BASE;
    do {
        for (n = 0; n < UART_IDLE_LOOPS; n++)
            if (!(inb(UART_BASE + UART_LSR) & UART_LSR_THRE))
                break;
    } while (n < UART_IDLE_LOOPS);
*/
    comm_region->cell_state = JAILHOUSE_CELL_RUNNING_LOCKED;

    /* Initialize  Interrupt Descriptor Table */
    osEE_x86_64_int_init();

    /* Initialize  Interrupt Controller */
    if(osEE_x86_64_int_controller_init()) {
        /* Error in interrupt controller initialization (e.g., no CPU support) */
        OSEE_PRINT("Error in interrupt controller initialization.\n");
        for(;;);
    }

    /* Handle Virtual Core IDs */
    osEE_x86_64_core_id_offset = osEE_x86_64_get_core_id_raw();

    /* Then, calibrate the platform tick frequency (X2APIC, TSC) */
    osEE_x86_64_calibrate_platform_tick_freq();

    /* ERIKA's Dynamic data structures initialization */
#if (defined(OSEE_API_DYNAMIC))
    osEE_os_init();
#endif /* OSEE_API_DYNAMIC */

    main();

    osEE_hal_disableIRQ();

    OSEE_PRINT("ERIKA tasks terminated.\n");

    while (loop && (comm_region->cell_state != JAILHOUSE_CELL_SHUT_DOWN)) {

        switch (comm_region->msg_to_cell) {
            case JAILHOUSE_MSG_SHUTDOWN_REQUEST:
            loop = false;
            break;

        default:
            jailhouse_send_reply_from_cell(comm_region, JAILHOUSE_MSG_UNKNOWN);
            break;
        }
    }

    printk("ERIKA Stopped\n");

    comm_region->cell_state = JAILHOUSE_CELL_SHUT_DOWN;
}
