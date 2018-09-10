#ifndef SHARED_H
#define SHARED_H

#include "ee.h"
#include "ee_tc2x5_board.h"

DeclareTask(TaskMaster);
DeclareTask(TaskCpu0Remote);
DeclareTask(TaskSlave1);
DeclareTask(TaskSlave2);

ISR2(button_handler);

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
#define US_LED_ON (200000U)
static void led_blink(enum OsEE_tc2x5_led_id theled)
{
  DisableAllInterrupts();
  osEE_tc2x5_turn_led(theled, OSEE_TRIBOARD_2X5_LED_ON);
  EnableAllInterrupts();

  osEE_tc_delay(US_LED_ON);

  DisableAllInterrupts();
  osEE_tc2x5_turn_led(theled, OSEE_TRIBOARD_2X5_LED_OFF);
  EnableAllInterrupts();
}

/* Used to enhance tracing */
static void idle_hook_body(void) {
  __asm__ volatile(
    "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
    "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
}

#endif /* SHARED_H */
