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

#include "ee.h"

#include <ff.h>		/* Declarations of FatFs API */
#include <ffmem.h>

/* Memory size */
#define MEM_SIZE (MINIMUM_FAT_SIZE)

#define EE_MEM_LOCAL //use executable data as memory device

#if defined(EE_MEM_LOCAL)
unsigned char memory[MEM_SIZE];
#else
#define memory (const void*)(0x274800000)
#endif

FATFS FatFs; /* FatFs work area needed for each volume */

DeclareTask(Task1);

/* Utility functions */
FRESULT list_file(const void *filename);
static void read_file(const void *filename);
static FRESULT scan_files(char* path);

/******************************************************************************
 *  Main
 *****************************************************************************/

/* This task will scan the File System */
TASK(Task1) {
	char buff[256];

	f_mount(&FatFs, "", 0); /* Give a work area to the default drive */
	/* Setting root */
	buff[0] = '/';
	buff[1] = 0;

	/* Start scanning */
	scan_files(buff);

	/* Unmounting */
	f_mount(NULL, "", 0);

	TerminateTask();
}

void idle_hook(void);

void idle_hook(void) {
	/* endless loop*/
	while (1) {
		asm volatile("wfi": : : "memory");
	}
}

int main(void) {

	uint8_t work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
	UINT bw;
	FIL Fil; /* File object needed for each open file */
	FRESULT res;

	const char* file_content = ""
			"|  ____|  | | |  ____|\n"
			"| |__ __ _| |_| |__ ___  \n"
			"|  __/ _` | __|  __/ __| \n"
			"| | | (_| | |_| |  \\__ \\ \n"
			"|_|__\\__,_|\\__|_|  |___/ \n"
			"  / _ \\| '_ \\             \n"
			" | (_) | | | |            \n"
			"  \\___/|_|_|_|_ ____ \n"
			"|  ____|  ____|___ \\ \n"
			"| |__  | |__    __) | \n"
			"|  __| |  __|  |__ <  \n"
			"| |____| |____ ___) | \n"
			"|______|______|____/  \n"
			"                      ";

#if !defined(EE_MEM_LOCAL)
	/* The shared memory must be mapped as UNCACHED if it's shared
	 * between cpus on different clusters (e.g. Denver and A57)
	 * NOTE: please use proper erika function to map memory or,
	 * if missing, the one provided by the platform/hypervisor */
	map_range(memory, MEM_SIZE, MAP_UNCACHED);
#endif

	f_mem_init(memory, MEM_SIZE);

#if defined(EE_MEM_LOCAL)
	/* Creating the file system and a file */
	/* Create FAT volume */
	res = f_mkfs("", FM_ANY, 0, work, sizeof work);
#endif
	f_mount(&FatFs, "", 0); /* Give a work area to the default drive */

	/* Writing a file */
	res = f_mkdir("test");
	res = f_open(&Fil, "test/erika.txt", FA_WRITE | FA_OPEN_APPEND);
	if (res == FR_OK) {
		/* Create a file */
		f_write(&Fil, file_content, strlen(file_content), &bw);
		f_close(&Fil); /* Close the file */
	} else {
		printk("Cannot create file res\n");
	}

	/* Umounting */
	f_mount(NULL, "", 0);

	printk("Starting OS...\n");
	StartOS(OSDEFAULTAPPMODE);
	return 0;
}

FRESULT list_file(const void *filename) {
	/* listing files */
	FRESULT fr;
	FILINFO fno;

	printk("Dumping infos of file %s\n", filename);
	fr = f_stat(filename, &fno);
	switch (fr) {

	case FR_OK: {
		printk("Size: %lu\n", fno.fsize);
		printk("Timestamp: %u/%02u/%02u, %02u:%02u\n", (fno.fdate >> 9) + 1980,
				fno.fdate >> 5 & 15, fno.fdate & 31, fno.ftime >> 11,
				fno.ftime >> 5 & 63);
		printk("Attributes: %c%c%c%c%c\n", (fno.fattrib & AM_DIR) ? 'D' : '-',
				(fno.fattrib & AM_RDO) ? 'R' : '-',
				(fno.fattrib & AM_HID) ? 'H' : '-',
				(fno.fattrib & AM_SYS) ? 'S' : '-',
				(fno.fattrib & AM_ARC) ? 'A' : '-');

	}
		break;

	case FR_NO_FILE:
		printk("It is not exist.\n");
		break;

	default:
		printk("An error occured. (%d)\n", fr);
	}

	return fr;
}

static void read_file(const void *filename) {
#define READ_BUFF_SIZE (128)
	/* listing files */
	FRESULT fr;
	FIL fil; /* File object */
	char line[READ_BUFF_SIZE]; /* Line buffer */
	UINT bytes_read;

	printk("CONTENT\n");
	/* opening and reading */
	fr = f_open(&fil, filename, FA_READ);
	if (fr)
		return;
	/* Read all lines and display it */
	do {
		memset(line, 0, sizeof(char) * READ_BUFF_SIZE);
		f_read(&fil, line, READ_BUFF_SIZE - 1, &bytes_read);
		printk("%s", line);
	} while (bytes_read >= (READ_BUFF_SIZE - 1));
	printk("\n\n");

	/* Close the file */
	f_close(&fil);
}

static FRESULT scan_files(char *path) {
	FRESULT res;
	DIR dir;
	UINT i, j;
	static FILINFO fno;

	res = f_opendir(&dir, path); /* Open the directory */
	if (res == FR_OK) {
		for (;;) {
			res = f_readdir(&dir, &fno); /* Read a directory item */
			if (res != FR_OK || fno.fname[0] == 0)
				break; /* Break on error or end of dir */
			if (fno.fattrib & AM_DIR) { /* It is a directory */
				i = strlen(path);
				j = strlen(fno.fname);
				path[i] = '/';
				i++;
				memcpy(path + i, fno.fname, j);
				path[i + j] = 0; //terminating the string
				printk("Discovered directory %s\n", path);
				res = scan_files(path); /* Enter the directory */
				if (res != FR_OK)
					break;
				path[i] = 0;
			} else { /* It is a file. */
				char abs_path[256];
				i = strlen(path);
				j = strlen(fno.fname);
				memcpy(abs_path, path, i);
				abs_path[i] = '/';
				i++;
				memcpy(abs_path + i, fno.fname, j);
				abs_path[i + j] = 0; //terminating the string
				list_file(abs_path);
				read_file(abs_path);
			}
		}
		f_closedir(&dir);
	}

	return res;
}
