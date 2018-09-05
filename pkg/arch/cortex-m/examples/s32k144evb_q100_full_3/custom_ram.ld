/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2018 Evidence s.r.l.
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

/** \file	code.c
 *  \brief	Custom Linker Script
 *
 *  This file contains a Custom Linker Script for NXP S32SDK 0.8.6 EAR Startup
 *  Code (RAM).
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/******************************************************************************
 *	ENTRY POINT							      *
 ******************************************************************************/
ENTRY(Reset_Handler)

/******************************************************************************
 *	STACK & HEAP SIZES						      *
 ******************************************************************************/
HEAP_SIZE	= DEFINED(__heap_size__)  ? __heap_size__  : 0x00000400;
STACK_SIZE	= DEFINED(__stack_size__) ? __stack_size__ : 0x00000400;

/******************************************************************************
 *	MEMORY								      *
 ******************************************************************************/
MEMORY
{
	/* SRAM_L */
	m_interrupts	(RX)	: ORIGIN = 0x1FFF8000, LENGTH = 0x00000400
	m_text		(RX)	: ORIGIN = 0x1FFF8400, LENGTH = 0x00007C00

	/* SRAM_U */
	m_data		(RW)	: ORIGIN = 0x20000000, LENGTH = 0x00007000
}

/******************************************************************************
 *	OUTPUT SECTIONS							      *
 ******************************************************************************/
SECTIONS
{
	/* Interrupt Vector Table goes first into internal RAM		      */
	.interrupts :
	{
		__VECTOR_TABLE = .;
		. = ALIGN(4);
		KEEP(*(.isr_vector))	/* Interrupt Vector Table	      */
		. = ALIGN(4);
	} > m_interrupts

	__VECTOR_RAM = __VECTOR_TABLE;
	__RAM_VECTOR_TABLE_SIZE = 0x0;

	/* The program code and read-only data goes into internal RAM	      */
	.text :
	{
		. = ALIGN(4);
		*(.text)	/* .text sections (code)		      */
		*(.text*)	/* .text* sections (code)		      */
		*(.rodata)	/* .rodata sections (constants, etc.)	      */
		*(.rodata*)	/* .rodata* sections (constants, etc.)	      */
		*(.glue_7)	/* glue arm to thumb code		      */
		*(.glue_7t)	/* glue thumb to arm code		      */
		*(.eh_frame)
		KEEP (*(.init))
		KEEP (*(.fini))
		. = ALIGN(4);
	} > m_text

	/* Section for storing functions that needs to execute from RAM	      */
	.code_ram :
	{
		. = ALIGN(4);
		__CODE_RAM = .;
		*(.code_ram)	/* Custom section for storing code in RAM     */
		/* Symbol is used by start-up for data initialization.	      */
		__CODE_ROM = .;
		__CODE_END = .;	/* No copy				      */
		. = ALIGN(4);
	} > m_text

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > m_text

	.ARM :
	{
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	} > m_text

	.ctors :
	{
		__CTOR_LIST__ = .;
		KEEP (*crtbegin.o(.ctors))
		KEEP (*crtbegin?.o(.ctors))
		KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
		__CTOR_END__ = .;
	} > m_text

	.dtors :
	{
		__DTOR_LIST__ = .;
		KEEP (*crtbegin.o(.dtors))
		KEEP (*crtbegin?.o(.dtors))
		KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
		__DTOR_END__ = .;
	} > m_text

	.preinit_array :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > m_text

	.init_array :
	{
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > m_text

	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > m_text

	__etext = .;	/* Define a global symbol at end of code.	      */
	__DATA_ROM = .;	/* Symbol is used by startup for data initialization. */
	__DATA_END = __DATA_ROM;	/* No copy			      */

	/*
	 * Custom Section Block that can be used to place data at absolute
	 * address.
	 *
	 * Example:	Use __attribute__((section (".customSection"))) to
	 * 		place data here.
	 */
	.customSectionBlock  ORIGIN(m_data) :
	{
		/* Keep section even if not referenced.			      */
		KEEP(*(.customSection))
	} > m_data

	.data :
	{
		. = ALIGN(4);
		__DATA_RAM = .;
		/* Create a global symbol at data start.		      */
		__data_start__ = .;
		*(.data)	/* .data sections			      */
		*(.data*)	/* .data* sections			      */
		KEEP(*(.jcr*))
		. = ALIGN(4);
		/* Define a global symbol at data end.			      */
		__data_end__ = .;
	} > m_data

	/* Uninitialized data section. */
	.bss :
	{
		/*
		 * This is used by the startup in order to initialize the .bss
		 * section.
		 */
		. = ALIGN(4);
		__BSS_START = .;
		__bss_start__ = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		__BSS_END = .;
	} > m_data

	.heap :
	{
		. = ALIGN(8);
		__end__ = .;
		PROVIDE(end = .);
		PROVIDE(_end = .);
		PROVIDE(__end = .);
		__HeapBase = .;
		. += HEAP_SIZE;
		__HeapLimit = .;
		__heap_limit = .;
	} > m_data

	.stack :
	{
		. = ALIGN(8);
		. += STACK_SIZE;
	} > m_data

	/* Initializes stack on the end of block			      */
	__StackTop   = ORIGIN(m_data) + LENGTH(m_data);
	__StackLimit = __StackTop - STACK_SIZE;
	PROVIDE(__stack = __StackTop);

	.ARM.attributes 0 : { *(.ARM.attributes) }

	ASSERT(__StackLimit >= __HeapLimit, "region m_data overflowed with stack and heap")

	/DISCARD/ : {
		*(.FlashConfig)
	}
}	/* SECTIONS */

