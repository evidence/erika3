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

/** \file   ee_x86_64_memory_mgmt.c
 *  \brief  Memory management.
 *
 *  \author Bruno Morelli, Ida Savino
 *  \date   2018
 */

#include "ee_platform_types.h"
#include "ee_x86_64_memory_mgmt.h"

#define PAGE_MASK    (~(PAGE_SIZE - 1))
#define PG_4K_MASK   (~(1UL << 7))
#define PG_RW        (1UL << 1)
#define PG_PRESENT   (1UL << 0)
#define PG_PCD       (1UL << 4)

#define PT_LEVEL        4
#define HEAP_PT_ENTRIES 512

/* Variable define in the linker script */
extern void *_pt_heap_base;
extern void *_pt_heap_end;
extern uint64_t pdt[];
extern uint64_t heap_pt[];

extern void *_libc_heap_base;
extern void *_libc_heap_end;

/* Heap current position (should be page aligned) */
static OsEE_paddr heap_pos = (OsEE_paddr)&_pt_heap_base;
static OsEE_paddr heap_end = (OsEE_paddr)&_pt_heap_end;

static OsEE_paddr libc_heap_base = (OsEE_paddr)&_libc_heap_base;
static OsEE_paddr libc_heap_end = (OsEE_paddr)&_libc_heap_end;

int osEE_x86_64_memory_init(void)
{
	pdt[1] = (uint64_t)&heap_pt | PG_RW | PG_PRESENT;
	for(int i = 0; i < HEAP_PT_ENTRIES; i++)
		heap_pt[i] = ((uint64_t)(&_pt_heap_base) + i * PAGE_SIZE)
			     | PG_RW | PG_PRESENT;

	return osEE_x86_64_map_range(libc_heap_base,
				     libc_heap_end - libc_heap_base,
				     MAP_CACHED);
}

static OsEE_paddr heap_page_alloc(void)
{
	OsEE_paddr base;

	if( heap_pos > heap_end)
		return -1;

	base = (heap_pos + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
	heap_pos += PAGE_SIZE;

	return base;
}

static OsEE_vaddr _map_range(OsEE_paddr start, size_t size,
			     enum OsEE_map_type map_type)
{
	OsEE_paddr pt_addr, *pt_entry, *pt;
	unsigned long alloc_size;
	unsigned long vaddr;

	vaddr = (unsigned long)start;
	alloc_size =  ((vaddr + size + PAGE_SIZE - 1) & PAGE_MASK) -
		      (vaddr & PAGE_MASK);

	asm volatile("mov %%cr3,%0" : "=r" (pt_addr));
	while (alloc_size > 0) {
		pt_addr &= PAGE_MASK;
		pt = (unsigned long *)pt_addr;
		/* Entry in the PML4T */
		pt_entry = &pt[(vaddr >> 39) & 0x1ff];
		if (*pt_entry & PG_PRESENT) {
			pt = (unsigned long *)(*pt_entry & PAGE_MASK);
		} else {
			pt = (OsEE_paddr *)heap_page_alloc();
			if (pt == (OsEE_paddr *)-1)
				return -1;
			*pt_entry = (unsigned long)pt | PG_RW | PG_PRESENT;
		}
		/* Entry in the PDPT */
		pt_entry = &pt[(vaddr >> 30) & 0x1ff];
		if (*pt_entry & PG_PRESENT) {
			pt = (unsigned long *)(*pt_entry & PAGE_MASK);
		} else {
			pt = (OsEE_paddr *)heap_page_alloc();
			if (pt == (OsEE_paddr *)-1)
				return -1;
			*pt_entry = (unsigned long)pt | PG_RW | PG_PRESENT;
		}
		/* Entry in PDT */
		pt_entry = &pt[(vaddr >> 21) & 0x1ff];
		if (*pt_entry & PG_PRESENT) {
			pt = (unsigned long *)(*pt_entry & PAGE_MASK);
		} else {
			pt = (OsEE_paddr *)heap_page_alloc();
			if (pt == (OsEE_paddr *)-1)
				return -1;
			*pt_entry = (unsigned long)pt | PG_RW | PG_PRESENT;
		}
		/*Entry in PT */
		pt_entry = &pt[(vaddr >> 12) & 0x1ff];
		*pt_entry = (vaddr & PG_4K_MASK) |
			(map_type == MAP_UNCACHED ? PG_PCD : 0) |
			PG_RW | PG_PRESENT;
		/* Invalidate TLB */
		osEE_x86_64_invalidate_vaddr_tlb(vaddr);
		/* Allocate next page */
		alloc_size -= PAGE_SIZE;
		vaddr += PAGE_SIZE;
	}

	return (OsEE_vaddr) start;
}

int osEE_x86_64_map_range(OsEE_paddr start, size_t size,
			  enum OsEE_map_type map_type)
{
	OsEE_vaddr addr;

	/* Allocate pages for the page tables */
	if (heap_pos > heap_end)
		return -1;

	/* TODO check the sign extension (bits 48-63) in the address */

	/* Allocate requested pages from start to start+size */
	addr = _map_range(start, size, map_type);
	if (addr == -1)
		return -1;

	return 0;
}
