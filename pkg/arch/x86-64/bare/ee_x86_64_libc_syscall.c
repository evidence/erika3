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

/** \file  ee_x86_64_libc_syscall.c
   \brief  ERIKA3 Syscall implementation
 *
 *  \author Bruno Morelli
 *  \date   2018
 */

#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <reent.h>
#include <stdbool.h>

#include "ee_uart.h"

caddr_t sbrk _PARAMS((int));
int write _PARAMS((int, char *, int));
int read _PARAMS((int, char *, int));
int close _PARAMS((int));
int fstat _PARAMS((int, struct stat *));
int lseek _PARAMS((int, int, int));
int isatty _PARAMS((int));
/* int _open _PARAMS((const char *, int, ...)); */

#if 0
#undef errno
extern int errno;

/* pointer to array of char * strings that define the current environment variables */
char *__env[1] = { 0 };
char **environ = __env;

void _exit();
int _close(int fd);
int _execve(char *name, char **argv, char **env);
int _fork(void);
int _fstat(int file, struct stat *st);
int _getpid(void);
int _isatty(int file);
int _kill(int pid, int sig);
int _link(char *old, char *new);
int _lseek(int file, int ptr, int dir);
/*int _open(const char *name, int flags, ...);*/
int _open(const char *name, int flags, int mode);
int _read(int file, char *ptr, int len);
caddr_t _sbrk(int incr);
int _stat(const char *file, struct stat *st);
clock_t _times(struct tms *buf);
int _unlink(char *name);
int _wait(int *status);
int _write(int file, char *ptr, int len);
int     _gettimeofday   (struct timeval *, void *);
#endif

extern void *_libc_heap_base;
extern void *_libc_heap_end;
static unsigned char *libc_prev_heap_end;
static unsigned char *libc_heap_end = (unsigned char *)&_libc_heap_base;
static unsigned char *libc_heap_limit_addr = (unsigned char *)&_libc_heap_end;

caddr_t sbrk(int incr)
{
	libc_prev_heap_end = libc_heap_end;

	if ((libc_heap_end + incr) > libc_heap_limit_addr)
		return (caddr_t)-1;

	libc_heap_end += incr;

	return (caddr_t)libc_prev_heap_end;
}

int write(int fd, char *ptr, int len)
{
	int i;

	if (fd != 1 && fd != 2) {
		errno = EBADF;
		return -1;
	}
	for (i = 0; i < len; ++i) {
		if (ptr[i] == '\n')
			OsEE_uart_write_byte(COM1, '\r');
		OsEE_uart_write_byte(COM1, ptr[i]);
	}

	return len;
}

int read(int fd, char *ptr, int len)
{
	int err = 0;

	if (fd != 0) {
		errno = EBADF;
		err = -1;
	}

	return err;
}

int close(int fd)
{
	if (fd >= 0 && fd <= 2)
		return 0;

	errno = EBADF;
	return -1;
}

int fstat (int file, struct stat *st)
{
	return 0;
}

int lseek(int fd, int ptr, int dir)
{
	return 0;
}

int isatty(int fd)
{
	return (fd >= 0 && fd <= 2) ? 1 : 0;
}
