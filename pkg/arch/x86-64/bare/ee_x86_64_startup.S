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

/** \file   ee_x86_64_startup.S
 *  \brief  ERIKA3 bare bone boot.s
 *
 *  \author Bruno Morelli, Ida Savino
 *  \date   2018
 */


# multiboot header
.section .rodata.multiboot
.align 4

# GRUB header
.long 0x1BADB002            # magic number
.long 0x3                   # flags: align, meminfo
.long -(0x1BADB002 + 0x3)   # checksum: -(magic+flags)


# GDT64 Entries
.equ NULL, 0         # Null descriptor.
.equ CODE, 1         # The code descriptor.
.equ DATA, 2         # The data descriptor.

# Initial kernel stack
.section .kernel_stack
.Lstack_bottom:
.align 0x1000
.byte 0
.skip 8 * 1024 # 8 KB
.byte 0
.Lstack_top:

# The linker script specifies _start as the entry point to the kernel and the
# bootloader will jump to this position once the kernel has been loaded. It
# doesn't make sense to return from this function as the bootloader is gone.
.code32
.section .text.startup
.global _start
.type _start, @function
_start:
    cli
	# Welcome to kernel mode!
	# To set up a stack, we simply set the esp register to point to the top of
	# our stack (as it grows downwards).
	movl $.Lstack_top, %esp

    # Disable the old paging
    mov %cr0, %eax
    and $0x7FFFFFFF, %eax   # Clear the PG-bit (bit 31 of CR0)
    mov %eax, %cr0

    # Mapping 1:1 virtual-physical memory
    # Clear the tables (from 0x1000 to 0x5000)
    mov $pml4t, %edi       # %edi contains destination address
    mov %edi, %cr3          # Save %edi value
    xor %eax, %eax          # %eax contains the value to be written
    mov $4096, %ecx         # %ecx contains number of repetions
    rep stosl

    # Setup of page table level 4/3/2
    mov %cr3, %edi          # Restore %edi value
    movl $pdpt, %eax
    orl $3, %eax
    movl %eax, (%edi)    # PML4T[0]-->PDPT

    movl $pdpt, %edi
    movl $pdt, %eax
    orl $3, %eax
    movl %eax, (%edi)    # PDPT[0]-->PDT

    movl $pdt, %edi
    movl $pt, %eax
    orl $3, %eax
    movl %eax, (%edi)     # PDT[0]-->PT

    # Setup of page table level 1 (Mapping from 0x0 to code_end)
    movl $pt, %edi
    mov $0x00000003, %ebx   # Page Present, Page readable/writable
    mov $code_end, %ecx
    shr $12, %ecx
setPTEntry:
    movl %ebx, (%edi)
    add $0x1000, %ebx
    add $8, %edi
    loop setPTEntry

    # Enable PAE-paging
    mov %cr4, %eax
    or $0x20, %eax          # Set the PAE-bit (bit 5 of CR4).
    mov %eax, %cr4

    # Switch from Protected Mode
    mov $0xC0000080, %ecx   # Set the C-register to 0xC0000080, which is the EFER MSR
    rdmsr                   # Read from the model-specific register
    or $0x100, %eax         # Set the LM-bit (bit 8 of EFER MSR)
    wrmsr                   # Write to the model-specific register

    # Enabling paging
    mov %cr0, %eax
    or $0x80000000, %eax    # Set the PG-bit (bit 31 of CR0)
    mov %eax, %cr0

    # Enabling Streaming SIMD Extensions (SSE)
    # Note: used to allow float/double operations
    mov %cr0, %eax
    and $0xFFFFFFFB, %eax	# clear coprocessor emulation CR0.EM
    or $0x2, %eax		# set coprocessor monitoring  CR0.MP
    mov %eax, %cr0
    mov %cr4, %eax
    or  $0x600, %eax		# set CR4.OSFXSR, CR4.OSXMMEXCPT (bit 9,10)
    mov %eax, %cr4

    # Load the 64-bit global descriptor table
    lgdt (GDTD64)
    # Jump to 64-bit long mode
    ljmp $(CODE << 3) , $startup64

	# In case the function returns, we'll want to put the computer into an
	# infinite loop. To do that, we use the clear interrupt ('cli') instruction
	# to disable interrupts, the halt instruction ('hlt') to stop the CPU until
	# the next interrupt arrives, and jumping to the halt instruction if it ever
	# continues execution, just to be safe. We will create a local label rather
	# than real symbol and jump to there endlessly.
	cli
	hlt
.Lhang:
	jmp .Lhang

# Set the size of the _start symbol to the current location '.' minus its start.
# This is useful when debugging or when you implement call tracing.
.size _start, . - _start

.code64
startup64:
    cli
    movw $(DATA << 3), %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

	movq $.Lstack_top, %rsp

    # Prepare frame pointer
    xor %rbp, %rbp
    push %rbp
    mov %rsp,%rbp

       # PIC: disable all IRQs
       movb $0xff, %al
       outb %al, $0xa1
       outb %al, $0x21

	# We are now ready to actually execute C code.
	call arch_startup

	# In case the function returns, we'll want to put the computer into an
	# infinite loop.
	cli
	hlt
.Lhang64:
	jmp .Lhang64

# Global Descriptor Table
GDT64:
_null:
    .word 0xFFFF    # Limit low (0:15)
    .word 0         # Base low (0:15)
    .byte 0         # Base middle (16:23)
    .byte 0         # Access
    .byte 1         # Granularity
    .byte 0         # Base high (24:31)
_code:
    .word 0         # Limit low (0:15)
    .word 0         # Base low (0:15)
    .byte 0         # Base middle (16:23)
    .byte 0x9a      # Access (bit1=read bit3=exec bit5=longmode bit7=present)
    .byte 0xaf      # Granularity, 64 bits flag, limit high (16:19)
    .byte 0         # Base high (25:31)
_data:
    .word 0         # Limit low (0:15).
    .word 0         # Base low (0:15).
    .byte 0         # Base middle (16:23)
    .byte 0x92      # Access (bit1=write bit5=longmodei bit7=present)
    .byte 0x0       # Granularity, limit high(16:19)
    .byte 0         # Base high (24:31)

# GDT Descriptor
GDTD64:
    .word GDTD64 - GDT64 - 1    # Table size (byte) - 1
    .quad GDT64                 # Pointer to table
