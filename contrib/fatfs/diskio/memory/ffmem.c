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

/** \file	ffmem.c
 *  \brief	ERIKA 3 FatFs driver implementation for memory
 *
 *  This module exports memory as a block device (with blocks and
 *  sectors).
 *
 *  \author	Luca Cuomo
 *  \date	2019
 */


/* Library include */
#include <ffmem.h>

/* Standard include */
#if defined(FATFS_LINUX)
#include <string.h>
#include <time.h>
#else
/* Someone will provide the memcpy */
extern void *memcpy(void *dest, const void *src, unsigned long n);
#endif

/*-----------------------------------------------------------------------*/
/* Defines                                                               */
/*-----------------------------------------------------------------------*/
#define ALIGNMENT		(sizeof(long long int))
#define MEM_SECTORS_COUNT	(ram_size/MEM_SECTOR_SIZE)
#define MEM_BLOCK_SIZE	(MEM_SECTOR_SIZE)

/*-----------------------------------------------------------------------*/
/* FFMEM attributes                                                      */
/*-----------------------------------------------------------------------*/
static void * ram_ptr;
static UINT   ram_size;
static DSTATUS dev_status = STA_NOINIT;


/*-----------------------------------------------------------------------*/
/* FFMEM specific function                                               */
/*-----------------------------------------------------------------------*/
DRESULT f_mem_init(const void * addr, UINT size)
{
	DSTATUS res = !FR_OK;
	
	if(addr && size >= MINIMUM_FAT_SIZE){
		ram_ptr = (void *)addr;
		ram_size = size;
		res = FR_OK;
	}
	return res;
}


/*-----------------------------------------------------------------------*/
/* FAT_FS GLUE FUNCTION                                                  */
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	__attribute__((unused))BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return dev_status;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	__attribute__((unused))BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
	dev_status = 0; //init ok 
	return dev_status;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	__attribute__((unused))BYTE pdrv,/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	void * start_addr;
	UINT copied = 0;

	if(!buff || count == 0)
		return RES_ERROR;

	if(disk_status(0) & STA_NOINIT) return RES_NOTRDY;

	/* Checking the alignment */
	start_addr = (void*)((long long int)sector * MEM_BLOCK_SIZE +
					 (long long int) ram_ptr);
	copied = count * MEM_BLOCK_SIZE;
	memcpy((void*)buff, (const void *) start_addr, copied);
	res = RES_OK;
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	__attribute__((unused)) BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	void * dest_addr;
	UINT copied = 0;
	if(!buff || count == 0)
		return RES_ERROR;

	if(disk_status(0) & STA_NOINIT) return RES_NOTRDY;

	/* Checking the alignment */
	dest_addr =  (void*) ((long long int)sector * MEM_BLOCK_SIZE +
					 (long long int) ram_ptr);
	copied = count * MEM_BLOCK_SIZE;
	memcpy((void*)dest_addr, (const void*)buff, copied);
	res = RES_OK;
	return res;
}

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	__attribute__((unused)) BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	if (disk_status(0) & STA_NOINIT) return RES_NOTRDY;	/* Check if card is in the socket */

	/* Initializing return value with error */
	res = RES_ERROR;

	switch (cmd) {

		case CTRL_SYNC :
			{		/* Make sure that no pending write process */
				 res = RES_OK;
	  			break;
			}

		case GET_SECTOR_COUNT:
			{
				if(!buff)
					break;
				/* Get number of sectors on the disk (DWORD) */
				*(DWORD*)buff = MEM_SECTORS_COUNT;
				res = RES_OK;
			}
			break;

		case GET_SECTOR_SIZE:
			{	
				if(!buff)
					break;
				/* Get number of sectors on the disk (DWORD) */
				*(DWORD*)buff = MEM_SECTOR_SIZE;
				res = RES_OK;
			}
			break;

		case GET_BLOCK_SIZE :
			{	
				if(!buff)
					break;
				/* Get erase block size in unit of sector (DWORD) */
				*(DWORD*)buff = MEM_BLOCK_SIZE;
				res = RES_OK;
			}
			break;
		default:
			res = RES_PARERR;
	}
	return res;
}

DWORD get_fattime (void)
{

/*
The DOS date/time format is a bitmask:

               24                16                 8                 0
+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
|Y|Y|Y|Y|Y|Y|Y|M| |M|M|M|D|D|D|D|D| |h|h|h|h|h|m|m|m| |m|m|m|s|s|s|s|s|
+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+
 \___________/\________/\_________/ \________/\____________/\_________/
    year        month       day      hour       minute        second

The year is stored as an offset from 1980. 
Seconds are stored in two-second increments. 
(So if the "second" value is 15, it actually represents 30 seconds.)

*/

#if defined (FATFS_LINUX)
	time_t rawtime;
	struct tm * timeinfo;
	unsigned long FatTime;
	/* getting system time */
	time(&rawtime);
	timeinfo = localtime ( &rawtime );
	
	/* Converting */
	FatTime = ((timeinfo->tm_year - 80) << 25) | 
                        (timeinfo->tm_mon << 21) |
                        (timeinfo->tm_mday << 16) |
                        (timeinfo->tm_hour << 11) |
                        (timeinfo->tm_min << 5) |
                        (timeinfo->tm_sec >> 1);
	return  FatTime ;
#else
	static DWORD fake_time = 0x0;
	return ++fake_time;
#endif
}

