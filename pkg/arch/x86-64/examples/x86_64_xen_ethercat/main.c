/*###*B*###
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

#include "ee.h"
#include "intel_i210.h"

/** timeout value in us for tx frame to return to rx */
#define EC_TIMEOUTRET      2000

#define SLAVE_NB			4
#define CHANNELS_NB			4


// References:
//	https://openethercatsociety.github.io/doc/soem/tutorial_8txt.html

int ec_init(const char *ifname);
int ec_config_init(uint8_t usetable);
extern int ec_slavecount;
int ec_config_map(void *pIOmap);
void print_slave_info (void);
void set_operational (void);
int ec_send_processdata(void);
int ec_receive_processdata(int timeout);
void set_output_int16 (uint16_t slave_nb, uint8_t module_index, int16_t value);


void ee_usleep (uint32_t usec);
void ee_usleep (uint32_t usec)
{
		// SetRelAlarm() wants the number of ticks
		// OSTICKDURATION is expressed in nsec
		//OSEE_PRINT("ee_usleep(%u)\n", usec);
		uint32_t duration = usec*1000/OSTICKDURATION;
		if (duration == 0)
			duration = 1;
		SetRelAlarm(SleepAlarm, duration, 0);
		//OSEE_PRINT("Calling WaitEvent()...\n");
		WaitEvent(SleepEvent);
}

void ee_port_lock(void);
void ee_port_lock(void)
{
	//OSEE_PRINT("Locking...\n");
	GetResource(PortLock);
	//OSEE_PRINT("Locked.\n");
}

void ee_port_unlock(void);
void ee_port_unlock(void)
{
	//OSEE_PRINT("Unlocking...\n");
	ReleaseResource(PortLock);
	//OSEE_PRINT("Unlocked.\n");
}



DeclareTask(Task1);


char IOmap[4096];

void idle_hook(void);

void idle_hook(void)
{
}


TASK (Task1)
{
	uint8_t channel = 0x0;

	OSEE_PRINT("Started.\n");

	if (ec_init("0"))
		OSEE_PRINT("Interface successfully initialized\n");
	else
		OSEE_PRINT("ERROR: Interface not initialized!\n");

   /* find and auto-config slaves */
   if ( ec_config_init(0) > 0 )
	      OSEE_PRINT("%d slaves found and configured.\n",ec_slavecount);
   else
	      OSEE_PRINT("ERROR: no slave found.\n");

   print_slave_info();

   ec_config_map(&IOmap);

   set_operational();
   print_slave_info();

   for (unsigned int i = 1;;++i) {

	   if ((i%10000) == 0) {
		   channel++;
		   channel %= CHANNELS_NB;
	   }
       set_output_int16(SLAVE_NB, 0x0, 0x0001 << channel);

       ec_send_processdata();
       ec_receive_processdata(EC_TIMEOUTRET);
   }

}

int main(void)
{
		OSEE_PRINT("Starting...\n");

        if (eth_discover_devices() < 0)
                return 0;

        if (eth_get_device(0) == NULL) {
                OSEE_PRINT("ERROR: no devices found\n");
                return 0;
        } else if (eth_get_device(1) != NULL) {
        		OSEE_PRINT("WARNING: more than one device found\n");
        }

        OSEE_PRINT("Starting ERIKA...\n");
        StartOS(OSDEFAULTAPPMODE);
        return 0;
}



