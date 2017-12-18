/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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

/** \file	task.cpp
 *  \brief	Task.
 *
 *  This file contains the code of application task for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2017
 */

/* ERIKA Enterprise. */
#include "ee.h"

/* Arduino SDK. */
#include "Arduino.h"

extern "C" {

extern int led;

extern int led_val;

unsigned int volatile TaskL1_count;

TASK(TaskL1)
{

  cli();
  Serial.write("TASK-L1\r\n", strlen("TASK-L1\r\n"));
  sei();

  if ( led_val == LOW ) {
    /* turn the LED on (HIGH is the voltage level) */
    digitalWrite(led, HIGH);
    led_val = HIGH;
  }
  else {
    /* turn the LED off by making the voltage LOW */
    digitalWrite(led, LOW);
    led_val = LOW;
  }

  ++TaskL1_count;
  TerminateTask();

};

}	/* extern "C" */
