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

/** \file	ffmem.h
 *  \brief	ERIKA 3 FatFs driver interface for memory
 *
 *  This module exports memory as a block device (with blocks and
 *  sectors.
 *
 *  \author	Luca Cuomo
 *  \date	2019
 */

#ifndef FF_MEM_H
#define FF_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Project include */
#include <ff.h>
#include <diskio.h>

/*-----------------------------------------------------------------------*/
/* 				Defines                                  */
/*-----------------------------------------------------------------------*/
#define MEM_SECTOR_SIZE	(512)
#define MINIMUM_FAT_SIZE (MEM_SECTOR_SIZE * (1024)) //FAT12 acceptable

/**
 * \brief	Initializes the memory virtual block device
 * \param[in]	add	Start address of the memory
 * \param[in]	size	Size of the memory
 * \return		Admitted values:
 * 				- FR_OK: initialization succeeded
 * 				- otherwise: initialization error
 */
DRESULT f_mem_init(const void * addr, UINT size);

#ifdef __cplusplus
}
#endif

#endif //FF_MEM_H
