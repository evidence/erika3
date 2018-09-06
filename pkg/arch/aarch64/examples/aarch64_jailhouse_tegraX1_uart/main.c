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

#include "ee_internal.h"
#include "uart-driver.h"
#include <inmate.h>

/******************************************************************************
 * Handlers and callback
 *****************************************************************************/

static void clock_handler ( void ) {
  uint64_t ticks_per_beat = osEE_aarch64_gtimer_get_freq();
  /* Writing something */
  size_t written = UART_write(UART_C, "...\r\n", 5);
  printk("Written %d bytes\n", written);
  /* Restarting timer */
  osEE_aarch64_gtimer_start(ticks_per_beat, OSEE_AARCH64_GTIMER_COUNTDOWN); 
  return;
}

/* Private callback which will be called everytime a char is received*/
static void my_callback(char c)
{
  printk("%c\n",c);
}

/******************************************************************************
 *  Main
 *****************************************************************************/
int main(void);

int main(void){
  uint64_t ticks_per_beat;
  TaskType isr_clock_id;
  /* Creating a task for the timer */
  CreateTask( &isr_clock_id, OSEE_TASK_TYPE_ISR2, clock_handler,
      1U, 1U, 1U, OSEE_SYSTEM_STACK );
  /* Tie ISR2 With IRQ */
  SetISR2Source(isr_clock_id, OSEE_GTIMER_IRQ);

  /* Setup the UART */
  uint8_t result = UART_init(UART_C, UART_BAUD_38400);
  if(result > 0){
    printk("UART driver init OK\n");
  }
  /* Set the Rx callback; this function will be called by the driver passing
     the received char */
  UART_set_callback(UART_C, my_callback); 

  printk("Starting OS...\n");
  StartOS(OSDEFAULTAPPMODE);

  printk("Starting timer ...\n");
  ticks_per_beat = osEE_aarch64_gtimer_get_freq();
  osEE_aarch64_gtimer_start(ticks_per_beat, OSEE_AARCH64_GTIMER_COUNTDOWN);  

  printk("Starting communication over UART\n");
  
  /* endless loop*/
  while(1) {
    __asm__ volatile("wfi": : : "memory");
  }
  return 0;
}
