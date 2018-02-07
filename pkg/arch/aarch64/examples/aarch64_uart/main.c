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

  /* 1. Setup the UART */
  uint8_t result = UART_init(UART_C, UART_BAUD_38400);
  if(result > 0){
	printk("UART driver init OK\n");
  }
  /* Set the Rx callback; this function will be called by the driver passing
	the recived char */
  UART_set_callback(UART_C, my_callback); 

  printk("Starting OS...\n");
  StartOS(OSDEFAULTAPPMODE);

  printk("Starting timer ...\n");
  ticks_per_beat = osEE_aarch64_gtimer_get_freq();
  osEE_aarch64_gtimer_start(ticks_per_beat, OSEE_AARCH64_GTIMER_COUNTDOWN);  

  printk("Starting communication over UART\n");
  
  /* endless loop*/
  while(1) {
      asm volatile("wfi": : : "memory");
  }
  return 0;
}
