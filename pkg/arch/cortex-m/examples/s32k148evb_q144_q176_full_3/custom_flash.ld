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
 *  Code (FLASH).
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
HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x00000400;
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x00000400;

/******************************************************************************
 *	INTERRUPT VECTOR TABLE SIZE IN RAM				      *
 ******************************************************************************/
/*
 * If symbol __flash_vector_table__=1 is defined at link time the interrupt
 * vector will not be copied to RAM.
 * Warning: Using the interrupt vector from Flash will not allow
 * INT_SYS_InstallHandler because the section is Read Only.
 */
M_VECTOR_RAM_SIZE = DEFINED(__flash_vector_table__) ? 0x0 : 0x0400;

/******************************************************************************
 *	MEMORY								      *
 ******************************************************************************/
MEMORY
{
	/* Flash */
	m_interrupts	(RX)	: ORIGIN = 0x00000000, LENGTH = 0x00000400
	m_flash_config	(RX)	: ORIGIN = 0x00000400, LENGTH = 0x00000010
	m_text		(RX)	: ORIGIN = 0x00000410, LENGTH = 0x0017FBF0

	/* SRAM_L */
	m_data_l	(RW)	: ORIGIN = 0x1FFE0000, LENGTH = 0x00020000

	/* SRAM_U */
	m_data_u	(RW)	: ORIGIN = 0x20000000, LENGTH = 0x0001F000
}

/******************************************************************************
 *	OUTPUT SECTIONS							      *
 ******************************************************************************/
SECTIONS
{
	/* Interrupt Vector Table goes first into internal FLASH	      */
	.interrupts :
	{
		__VECTOR_TABLE = .;
		. = ALIGN(4);
		KEEP(*(.isr_vector))	/* Interrupt Vector Table	      */
		. = ALIGN(4);
	} > m_interrupts

	.flash_config :
	{
		. = ALIGN(4);
		KEEP(*(.FlashConfig))	/* Flash Configuration Field (FCF)    */
		. = ALIGN(4);
	} > m_flash_config

	/* The program code and read-only data goes into internal FLASH	      */
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
	.interrupts_ram :
	{
		. = ALIGN(4);
		__VECTOR_RAM__ = .;
		/* Create a global symbol at interrupt ram start.	      */
		__interrupts_ram_start__ = .;
		*(.m_interrupts_ram)	/* This is a user defined section.    */
		. += M_VECTOR_RAM_SIZE;
		. = ALIGN(4);
		/* Define a global symbol at interrupt ram end.		      */
		__interrupts_ram_end__ = .;
	} > m_data_l

	__VECTOR_RAM = DEFINED(__flash_vector_table__) ? ORIGIN(m_interrupts) : __VECTOR_RAM__ ;
	__RAM_VECTOR_TABLE_SIZE = DEFINED(__flash_vector_table__) ? 0x0 : (__interrupts_ram_end__ - __interrupts_ram_start__) ;

	.data : AT(__DATA_ROM)
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
	} > m_data_l

	__DATA_END = __DATA_ROM + (__data_end__ - __data_start__);
	/* Symbol is used by code initialization.			      */
	__CODE_ROM = __DATA_END;
	.code : AT(__CODE_ROM)
	{
		. = ALIGN(4);
		__CODE_RAM = .;
		/* Create a global symbol at code start.		      */
		__code_start__ = .;
		*(.code_ram)	/* Custom section for storing code in RAM     */
		. = ALIGN(4);
		/* Define a global symbol at code end.			      */
		__code_end__ = .;
	} > m_data_l

	__CODE_END = __CODE_ROM + (__code_end__ - __code_start__);

	/*
	 * Custom Section Block that can be used to place data at absolute
	 * address.
	 *
	 * Example:	Use __attribute__((section (".customSection"))) to place
	 * 		data here.
	 */
	.customSectionBlock  ORIGIN(m_data_u) :
	{
		/* Keep section even if not referenced.			      */
		KEEP(*(.customSection))
	} > m_data_u

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
	} > m_data_u

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
	} > m_data_u

	.stack :
	{
		. = ALIGN(8);
		. += STACK_SIZE;
	} > m_data_u

	/* Initializes stack on the end of block			      */
	__StackTop   = ORIGIN(m_data_u) + LENGTH(m_data_u);
	__StackLimit = __StackTop - STACK_SIZE;
	PROVIDE(__stack = __StackTop);

	.ARM.attributes 0 : { *(.ARM.attributes) }

	ASSERT(__StackLimit >= __HeapLimit, "region m_data_u overflowed with stack and heap")
}	/* SECTIONS */

