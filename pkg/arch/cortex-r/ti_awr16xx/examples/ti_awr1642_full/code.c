

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if 0
#include <math.h>
#include <time.h>
#endif /* 0 */

#include <ti/drivers/soc/soc.h>
#include <ti/drivers/esm/esm.h>

#include "ee.h"
#include "ee_assert.h"

static ESM_Handle   esmHandle;
static SOC_Handle   socHandle;

/*
 * TASK AND ISR2 MUST BE C SYMBOL
 */
enum OSEE_ASSERTIONS {
  OSEE_ASSERT_FIN = 0,
  OSEE_ASSERT_INIT,
  OSEE_ASSERT_TASK1_FIRED,
  OSEE_ASSERT_TASK2_FIRED,
  OSEE_ASSERT_TASK1_POST,
  OSEE_ASSERT_TASK2_ENDED,
  OSEE_ASSERT_TASK1_ENDED,
  OSEE_ASSERT_TASK3_NOT_FIRED,
  OSEE_ASSERT_TASK3_FIRED,
  OSEE_ASSERT_TASKS_ENDED,
  OSEE_ASSERT_DIM
};
OSEE_TYPEASSERTVALUE osEE_assertions[OSEE_ASSERT_DIM];

/* Final result */
volatile OSEE_TYPEASSERTVALUE result;

/* Counters */
OsEE_reg volatile task1_fired;
OsEE_reg volatile task2_fired;
OsEE_reg volatile task1_ended;
OsEE_reg volatile task2_ended;
OsEE_reg volatile task3_fired;
OsEE_reg volatile task3_ended;
OsEE_reg volatile task4_fired;
OsEE_reg volatile task5_fired;
OsEE_reg volatile isr2_fired;
OsEE_reg volatile isr2_armed;

/* Stack Pointers */
OsEE_addr volatile task1_sp;
OsEE_addr volatile task2_sp;
OsEE_addr volatile task3_sp;
OsEE_addr volatile task4_sp;
OsEE_addr volatile task5_sp;
OsEE_addr volatile main_sp;

/* This semaphore is initialized inside the Background Task */
extern SemType V;

#define OSEE_BREAK_POINT()  do {                            \
    printf("Test Failed!!!, line:" OSEE_S(__LINE__) "\n");  \
    for(;;);                                                \
  } while ( 0 )

void free_task1(void) {
  isr2_armed  = 0;
}

void idle_hook(void) {
  OsEE_addr volatile curr_sp, curr_sp_after;

  printf("MAIN | After  | We are in Idle LOOP\n");

  osEE_assert(OSEE_ASSERT_INIT, OSEE_TRUE, OSEE_ASSERT_NIL);

  curr_sp = osEE_get_SP();
  printf("MAIN | BEFORE | TASK1 Activation Stack Pointer:<%p>\n", curr_sp);
  ActivateTask(Task1);
  curr_sp_after = osEE_get_SP();
  printf("MAIN | AFTER | TASK1 Returned Stack Pointer:<%p>\n", curr_sp_after);

  if ( curr_sp != curr_sp_after ) {
    OSEE_BREAK_POINT();
  }

  osEE_assert(
    OSEE_ASSERT_TASKS_ENDED,
    task1_ended && task2_ended && task3_ended,
    OSEE_ASSERT_TASK3_FIRED
  );
  osEE_assert_range(OSEE_ASSERT_FIN, OSEE_ASSERT_INIT, OSEE_ASSERT_TASKS_ENDED);
  result = osEE_assert_last();

  if (result == OSEE_ASSERT_YES) {
    printf("MAIN | TEST SUCCESS!!!\n");
  } else {
    printf("MAIN | TEST FAILED!!!\n");
  }

  /* Enable the Alarm to make the test cyclic. The printf seems to use
     semihosting on JTAG, the baudrate of this connection seems to be really
     slow, so we need a really slow cycle (20 seconds, OIL is configured to
     give a seconds for system timer ticks) to complete the cycle without
     losing activations. */
  printf("Enabling | Alarms For Ciclic Test\n");
  SetRelAlarm(AlarmTask1, 1U, 20U);
  SetRelAlarm(AlarmFreeTask1, 11U, 20U);

  /* Forever loop: background activities (if any) should go here */
  for(;;)
  {
    curr_sp = osEE_get_SP();
    if ( curr_sp != curr_sp_after ) {
      OSEE_BREAK_POINT();
    }

    if (main_sp == 0) {
      main_sp = curr_sp;
    } else if (main_sp != curr_sp) {
      OSEE_BREAK_POINT();
    }
  }
}

/*
 * TASK 1
 */
TASK(Task1)
{
  OsEE_addr curr_sp;

  printf("TASK1\n");

  task1_fired++;
  if (task1_fired == 1) {
    osEE_assert(OSEE_ASSERT_TASK1_FIRED, OSEE_TRUE, OSEE_ASSERT_INIT);
  } else {
    isr2_armed = 1U;
  }

  curr_sp = osEE_get_SP();
  if (task1_sp == 0) {
    task1_sp = curr_sp;
  } else if (task1_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  printf("TASK1 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  printf("TASK1 | Before | TASK2 Activation\n");
  ActivateTask(Task2);
  printf("TASK1 | After  | Resuming from preemption\n");
  printf("TASK1 | After  | Stack Pointer:<%p>\n", osEE_get_SP());

  if (task1_fired == 1) {
    osEE_assert(OSEE_ASSERT_TASK1_POST, OSEE_TRUE, OSEE_ASSERT_TASK2_FIRED);
  }

  printf("TASK1 | Before | Post Semaphore for TASK2\n");
  PostSem(&V);
  printf("TASK1 | After  | Resuming from preemption\n");
  printf("TASK1 | After  | Stack Pointer:<%p>\n", osEE_get_SP());

  if (task1_fired == 1) {
    osEE_assert(OSEE_ASSERT_TASK1_ENDED, OSEE_TRUE, OSEE_ASSERT_TASK2_ENDED);
    osEE_assert(OSEE_ASSERT_TASK3_NOT_FIRED, task3_fired == 0, OSEE_ASSERT_TASK1_ENDED);
  } else {
    printf("TASK1 | Before | Wait for release from ISR\n");
    while (isr2_armed) {
      ; /* Wait ISR2 release */
    }
    printf("TASK1 | After  | Released by ISR\n");
  }
  curr_sp = osEE_get_SP();
  if (task1_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  ++task1_ended;
  TerminateTask();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  OsEE_addr  curr_sp;
  printf("TASK2\n");

  curr_sp = osEE_get_SP();
  if (task2_sp == 0) {
    task2_sp = curr_sp;
  } else if (task2_sp != curr_sp) {
    OSEE_BREAK_POINT();
  }

  ++task2_fired;
  if (task2_fired == 1) {
    osEE_assert(OSEE_ASSERT_TASK2_FIRED, OSEE_TRUE, OSEE_ASSERT_TASK1_FIRED);
  }

  printf("TASK2 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  printf("TASK2 | Before | Wait on Semaphore\n");
  WaitSem(&V);
  printf("TASK2 | After  | Resuming From Wait\n");
  printf("TASK2 | After  | Stack Pointer:<%p>\n", osEE_get_SP());

  if (task2_fired == 1) {
    osEE_assert(OSEE_ASSERT_TASK2_ENDED, OSEE_TRUE, OSEE_ASSERT_TASK1_POST);
  }
  printf("TASK2 | Before | Activating TASK3\n");
  ActivateTask(Task3);
  task2_ended++;
  printf("TASK2 Terminated\n");
}

TASK(Task3) {
  OsEE_addr  curr_sp;

  printf("TASK3\n");

  curr_sp = osEE_get_SP();
  if (task3_fired > 1) {
    if (task3_sp == 0) {
      task3_sp = curr_sp;
    } else if (task3_sp != curr_sp) {
      OSEE_BREAK_POINT();
    }
  }

  ++task3_fired;

  printf("TASK3 | Before | Activating TASK4\n");
  printf("TASK3 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  ActivateTask(Task4);

  if (task3_fired == 1) {
    osEE_assert(OSEE_ASSERT_TASK3_FIRED, OSEE_TRUE, OSEE_ASSERT_TASK3_NOT_FIRED);
  }
  ++task3_ended;

  printf("TASK3 Termination\n");
}

TASK(Task4) {
  OsEE_addr  curr_sp;

  printf("TASK4\n");

  curr_sp = osEE_get_SP();
  if (task4_fired >= 1) {
    if (task4_sp == 0) {
      task4_sp = curr_sp;
    } else if (task4_sp != curr_sp) {
      OSEE_BREAK_POINT();
    }
  }
  ++task4_fired;

  printf("TASK4 | Before | Activating TASK5\n");
  printf("TASK4 | Before | Stack Pointer:<%p>\n", osEE_get_SP());
  ActivateTask(Task5);
  printf("TASK4 | After  | Resuming After Preemption\n");
  printf("TASK4 | After  | Stack Pointer:<%p>\n", osEE_get_SP());

  if (task4_fired > 1) {
    curr_sp = osEE_get_SP();
    if (task4_sp != curr_sp) {
      OSEE_BREAK_POINT();
    }
  }

  printf("TASK4 Termination\n");
}

TASK(Task5) {
  OsEE_addr  curr_sp;

  printf("TASK5\n");

  curr_sp = osEE_get_SP();

  printf("TASK5 Stack Pointer:<%p>\n", osEE_get_SP());
  if (task5_fired > 1) {
    if (task5_sp == 0) {
      task5_sp = curr_sp;
    } else if (task5_sp != curr_sp) {
      OSEE_BREAK_POINT();
    }
  }

  ++task5_fired;

  printf("TASK5 Termination\n");
}

int main(void) {
  int             errMain;
  int32_t         errCode;
  SOC_Cfg         socCfg;

  /* Initialize the SOC configuration: */
  memset ((void *)&socCfg, 0, sizeof(SOC_Cfg));

  printf("\n"); /* The first printf is used as lazy initialization of stdout */

  
  esmHandle = ESM_init(1); /* Clear the Errors */
  /* In this example ESM handler is not used but in general must be kept. */
  (void)esmHandle;

  /* Populate the SOC configuration: */
  socCfg.clockCfg = SOC_SysClock_INIT;

  /* Initialize the SOC Module */
  socHandle = SOC_init(&socCfg, &errCode);

  if (socHandle  == NULL)
  {
    printf ("Error: SOC Module Initialization failed [Error code %d]\n", errCode);
    errMain = -1;
  } else {
    printf("!!!Hello World!!!\n");
    errMain = 0;
  }

  if (errMain == 0) {
    StartOS(OSDEFAULTAPPMODE);
  }

  return errMain;
}
