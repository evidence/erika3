/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2013-2016
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include "ee_internal.h"
#include <inmate.h>

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
uint64_t     osEE_x86_64_tsc_freq_hz;

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
    /* Handle Virtual Core IDs */
    osEE_x86_64_core_id_offset = osEE_x86_64_get_core_id_raw();

    comm_region->cell_state = JAILHOUSE_CELL_RUNNING_LOCKED;

    osEE_x86_64_tsc_freq_hz = tsc_init();
    printk("Calibrated TSC frequency: %lu.%03u kHz\n",
            osEE_x86_64_tsc_freq_hz / OSEE_KILO,
            osEE_x86_64_tsc_freq_hz % OSEE_KILO);

    /* Initialize  Interrupt Descriptor Table */
    osEE_x86_64_int_init();

    /* ERIKA's Dynamic data structures initialization */
#if (defined(OSEE_API_DYNAMIC))
    osEE_os_init();
#endif /* OSEE_API_DYNAMIC */

    main();

    osEE_hal_disableIRQ();

    printk("ERIKA tasks terminated.\n");

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
