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

/** \file   ee_x86_64_linker.lds
 *  \brief  Linker script
 *
 *  \author Bruno Morelli, Ida Savino
 *  \date   2018
 */

/* Kernel entry function */
ENTRY(_start)

/* OUTPUT_FORMAT(elf32-i386) */
OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)

MEMORY {
	RAM(rwx) : ORIGIN = 0x0, LENGTH = 640K
	/* Reserved memory (VGA, Video BIOS, Motherboard BIOS) */
}

SECTIONS {

    /* Page tables */
    .page 0x1000 (NOLOAD) : {
	pml4t = .;
	. += 0x1000;
	pdpt = .;
	. += 0x1000;
	pdt = .;
	. += 0x1000;
	pt = .;
	. += 0x1000;
	heap_pt = .;
	. += 0x1000;
    } > RAM

    /* Code and readonly data */
    .text 	: {
        /* fill gaps with int3 opcode to detect invalid jumps */
        /*FILL(0xcc)*/

        /* multiboot header */
        multiboot_header = .;
        KEEP (*(".rodata.multiboot"))

        /* fixed address for IRQ handlers */
        . += 0x1000;

        /* common text (always accessible) */
        _stext_common = .;

        /* start of FAIL* allowed code region */
        _stext_fail = .;

        /* IRQ Handlers */
        KEEP (*(".text.irqhandlers*")) /* ASM */
        *(".text.irq_handler*") /* C */
        *(".text.isrs*") /* C */
        *(".text.isr_*") /* C */
        KEEP (*(".text.idt")) /* ASM */
        . += 16; /* padding after data, workaround for import-trace */

        /* constructors */
        . = ALIGN(8);
        PROVIDE(__CTORS_START = .);
        KEEP (*(.ctors*))
        KEEP (*(.init_array*))
        PROVIDE(__CTORS_END = .);

        /* constructor code */
        _stext_constructors = .;
        KEEP (*(".text.startup"))
        _etext_constructors = .;

        /* common symbols */
        _stext_common_syms = .;
        *("_GLOBAL__I_a")
        _etext_common_syms = .;

        . += 16; /* padding after data, workaround for import-trace */

        /* compiler code (arithmetic routines...) */
        "*libgcc*.a:" ( ".text" )

        /* anonymous read only data (probably strings) */
        /* cannot be separated by source, so put it here */
        _srodata_an = .;
        *(".rodata..L*")
        _erodata_an = .;

        . += 16; /* padding after data, workaround for import-trace */

        . = ALIGN(0x1000);
        _stext = .;
        *(".text*")
        _etext = .;

        /* remaining rodata */
        _srodata = .;
        *(".rodata*")
        _erodata = .;

        _etext_fail_allowed = .;
    } > RAM

    /* Data and Stacks */
    .data 	: {
        _sstack = .; /* to include TSS in FAIL tests, TODO: better placing*/

        /* TSS at known address */
        _stss = .;
        tss = .;
        . += 104;
        _etss = .;

        /* Stacks */
        . = ALIGN(4096);
        _sstack = .;

        _sstack_os = .;
        *(".kernel_stack")
        _estack_os = .;

        _estack = .;

        /* Data */
        . = ALIGN(4096);
        _sdata = .;
        *(".data*")
        *(COMMON);
        _edata = .;
    } > RAM

    /* Statically-allocated variables */
    .bss (NOLOAD)	: {
        *(".bss*")
	. = ALIGN(4096);
	code_end = .;
    } > RAM

    /* Heap starting from 2M (lenght: 2M) */
    _pt_heap_base = 0x200000;
    _pt_heap_end = _pt_heap_base + 2 * 1024 * 1024;

    _libc_heap_base = _pt_heap_end;
    _libc_heap_end = _libc_heap_base + 2 * 1024 * 1024;

    /* Get rid of unnecessary GCC bits */
    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
        *(.note.gnu.build-id)
    }
}
