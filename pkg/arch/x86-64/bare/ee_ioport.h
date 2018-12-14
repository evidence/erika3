/* ###*B*###
 * Erika Enterprise, version 3
 *
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of th:we License, or (at
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

/** \file   ee_ioport.h
 *  \brief  IOport input/outupt functions
 *
 *  \author  Ida Savino
 *  \date    2018
 */

#if (!defined(OSEE_IOPORT_H))
#define OSEE_IOPORT_H

OSEE_STATIC_INLINE
void OSEE_ALWAYS_INLINE outb(unsigned short port, uint8_t val)
{
	__asm__ volatile("outb %0, %1" :: "a"(val), "Nd"(port));
}

OSEE_STATIC_INLINE
void OSEE_ALWAYS_INLINE outw(unsigned short port, uint16_t val)
{
	__asm__ volatile("outw %0, %1" :: "a"(val), "Nd"(port));
}

OSEE_STATIC_INLINE
void OSEE_ALWAYS_INLINE outl(unsigned short port, uint32_t val)
{
	__asm__ volatile("outl %0, %1" :: "a"(val), "Nd"(port));
}

OSEE_STATIC_INLINE
uint8_t OSEE_ALWAYS_INLINE inb(unsigned short port)
{
	uint8_t ret;

	__asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));

	return ret;
}

OSEE_STATIC_INLINE
uint16_t OSEE_ALWAYS_INLINE inw(unsigned short port)
{
	uint16_t ret;

	__asm__ volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));

	return ret;
}

OSEE_STATIC_INLINE
uint32_t OSEE_ALWAYS_INLINE inl(unsigned short port)
{
	uint32_t ret;

	__asm__ volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));

	return ret;
}

OSEE_STATIC_INLINE
void OSEE_ALWAYS_INLINE io_wait(void)
{
#if 0
	/* port 0x80 is used for 'checkpoints' during POST.
	 * the Linux kernel seems to think it is free for use
	 */

	__asm__ volatile("outb %al, $0x80");
#else
	inb(0x60);
#endif
}

#endif  /* OSEE_IOPORT_H__*/