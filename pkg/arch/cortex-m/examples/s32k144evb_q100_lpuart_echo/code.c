/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2018 Evidence s.r.l.
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

/** \file	code.c
 *  \brief	This example is an simple echo using serial communication
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author	Errico Guidieri
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* HAL */
#include "hal.h"

volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <string.h>
#include <stdbool.h>

static bool strReceived = true;
static uint8_t  i = 0U;
/* Declare a buffer used to store the received data */
static uint8_t  buffer[255] = {0, };

ISR(LPURAT1_ISR2) {

  DemoHAL_SerialISRHandler();

  if (strReceived == false) {
    /* Check if current byte is new line */
    if (buffer[i] == '\n') {
      ActivateTask(ReceiveTask);
    }
    ++i;
  } else {
    if (DemoHAL_SerialWrite_Status() == STATUS_SUCCESS) {
      /* Reset the buffer length and received complete flag */
      i = 0;
      strReceived = false;
    }
  }
}

TASK(ReceiveTask) {

  strReceived = true;
  /* Append null termination to the received string */
  buffer[i] = 0;
  /* Check if data is "Hello Board".
   * If comparison is true, send back "Hello World"
   */
  if (strcmp((char *)buffer, "Hello Board\r\n") == 0) {
    strcpy((char *)buffer, "Hello World!!\r\n");
    i = strlen((char *)buffer);
  }

  /* Send the received data back */
  DemoHAL_SerialWrite_Async(buffer, i);

  TerminateTask();
}

#define welcomeMsg "This example is a simple echo using LPUART\r\n\
it will send back any character you send to it.\r\n\
The board will greet you if you send 'Hello Board'\r\n\
Now you can begin typing:\r\n"

void idle_hook(void) {
  DemoHAL_MainFunction();

  /* Send a welcome message */
  DemoHAL_SerialWrite((uint8_t *)welcomeMsg, strlen(welcomeMsg));

  /* Infinite loop:
   * 	- Receive data from user
   * 	- Echo the received data back
   */
  for (;;) {
    /* Get the received data */
    while (strReceived == false) {
      /* Because the terminal appends new line to user data,
       * receive and store data into a buffer until it is received
       */
      DemoHAL_SerialRead(&buffer[i], 1UL);

      DemoHAL_MainFunction();
    }
  }
}

void StartupHook(void) {
  DemoHAL_SerialInit();
}

int main()
{ 
  DemoHAL_Init();

#if (defined(OSEE_API_DYNAMIC))
  InitOS();

  SetIdleHook(idle_hook);
#endif /* OSEE_API_DYNAMIC */

  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  
  return 0;
}
