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

/** \file   ee_x86_64_memory_mgmt.h
 *  \brief  API for virtual memory management.
 *
 *  \author Bruno Morelli, Ida Savino
 *  \date   2018
 */

#ifndef EE_X86_64_MEMORY_MGMT_H
#define EE_X86_64_MEMORY_MGMT_H

#define PAGE_SIZE 4096UL

enum OsEE_map_type { MAP_CACHED, MAP_UNCACHED };

/* Physical address type */
typedef unsigned long OsEE_paddr;

int osEE_x86_64_memory_init(void);

int osEE_x86_64_map_range(OsEE_paddr start, size_t size,
			  enum OsEE_map_type map_type);

OSEE_STATIC_INLINE void osEE_x86_64_invalidate_vaddr_tlb(OsEE_vaddr vaddr)
{
        __asm__ volatile("invlpg (%0)\n\t" : : "r"(vaddr) : "memory");
}
#endif /* EE_X86_64_MEMORY_MGMT_ */
