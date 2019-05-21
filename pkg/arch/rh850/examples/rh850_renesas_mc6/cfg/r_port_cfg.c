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

/** \file   r_port_cfg.c
 *  \brief  project configuration of port and pin function driver
 *
 *  \author Errico Guidieri
 *  \date   2018
 */

#include <r_prj.h>

/*##############################################################################
 # project configuration
 ##############################################################################*/


/*******************************************************************************
 * pin configuration
 *******************************************************************************/
const port_cfg_t g_port_PrjCfg[] =
{
  { /* SW1 */
    PORT24_2,
    PORT_IN,
    PORT_NA
  },
  { /* SW2 */
    PORT24_3,
    PORT_IN,
    PORT_NA
  },

  { /* LED1 Blue */
    PORT20_0,
    PORT_OUT,
    PORT_LOW
  },
  { /* LED2 Blue */
    PORT20_1,
    PORT_OUT,
    PORT_LOW
  },
  { /* LED3 Blue */
    PORT20_2,
    PORT_OUT,
    PORT_LOW
  },
  { /* LED4 Blue */
    PORT20_3,
    PORT_OUT,
    PORT_LOW
  },

  { /* LED5 White */
    PORT22_0,
    PORT_OUT,
    PORT_LOW
  },
  { /* LED6 White */
    PORT22_1,
    PORT_OUT,
    PORT_LOW
  },
  { /* LED7 White */
    PORT22_2,
    PORT_OUT,
    PORT_LOW
  },
  { /* LED8 White */
    PORT22_3,
    PORT_OUT,
    PORT_LOW
  },

  { /* BTN1 */
    PORT24_0,
    PORT_IN,
    PORT_NA
  },
  { /* BTN2 */
    PORT24_1,
    PORT_IN,
    PORT_NA
  },
  { /* EVTO */
    PORT33_9,
    PORT_OUT_ALT3,
    PORT_LOW,
    PORT_STRENGTH_HIGH
  },
};

/*******************************************************************************
 * number of pins in configuration
 *******************************************************************************/
const uint32 g_port_PrjCfgCnt = sizeof(g_port_PrjCfg) / sizeof(g_port_PrjCfg[0]);

