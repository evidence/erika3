/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 Evidence s.r.l.
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
 * <https://www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
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

/*
 *
 * This file derives from a modification of the Infineon startup scripts,
 * distributed under the following license:
 *
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 */

/** \file   ee_tc_gcc_flash.ld
 *  \brief  Linker script file for GCC compiler (no iLLD integration)
 *  \author Errico Guidieri
 *  \date   2018
 */
 
OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_start)

/* Force to link the variable that contains the "TriCore ID" used to compile */
EXTERN(__TRICORE_DERIVATE_NAME__)
__TRICORE_DERIVATE_MEMORY_MAP__ = 0x2200;

/* CSA list size */
__CSA_SIZE = DEFINED (__CSA_SIZE) ? __CSA_SIZE : 8k;
/* Interrupt stack size */
__ISTACK_SIZE = DEFINED (__ISTACK_SIZE) ? __ISTACK_SIZE : 1K;
/* User stack size */
__USTACK_SIZE = DEFINED (__USTACK_SIZE) ? __USTACK_SIZE : 4K;

/* Heap size */
__HEAP_SIZE = DEFINED (__HEAP_SIZE) ? __HEAP_SIZE : 0k;

__DSPR_START  = 0x70000000;
__DSPR_SIZE   = 88K;

/* 1k guard area */
__CSA0_OFFSET    = (__DSPR_SIZE  - 1K  - __CSA_SIZE);
/* 256 byte guard area */
__ISTACK0_OFFSET = (__CSA0_OFFSET - 256 - __ISTACK_SIZE);
/* 256 byte guard area */
__USTACK0_OFFSET = (__ISTACK0_OFFSET - 256 - __USTACK_SIZE);

MEMORY
{
/* Program Flash Memory (PFLASH0) */ 
  PMU_PFLASH0   (rx!p): org = 0x80000000, len = 1M
  PMU_PFLASH_nc (rx!p): org = 0xA0000000, len = 1M
/* Data Flash Memory (DFLASH0) */ 
  PMU_DFLASH0   (r!xp): org = 0xAF000000, len = 1M+16K
/* Boot ROM (BROM) */ 
  BROM          (rx!p): org = 0x8FFF8000, len = 32K

/* Program Scratch-Pad RAM (PSPR) */ 
  PMI_PSPR_loc  (wx!p): org = 0xC0000000, len = 8K
  PMI_PSPR      (wx!p): org = 0x70100000, len = 8K
/* Data Scratch-Pad RAM (DSPR) */ 
  DMI_DSPR_loc  (w!xp): org = 0xD0000000, len = 88K
  DMI_DSPR      (w!xp): org = 0x70000000, len = 88K

  /* Extended Memory */
  EDMEM           (w!xp): org = 0x9f000000, len = 512K
  EDMEM_nc        (w!xp): org = 0xBf000000, len = 512K
}

/* Map local memory address to a global address */ 
REGION_MAP(CPU0 , ORIGIN(DMI_DSPR_loc), LENGTH(DMI_DSPR_loc), ORIGIN(DMI_DSPR))
REGION_MAP(CPU0 , ORIGIN(PMI_PSPR_loc), LENGTH(PMI_PSPR_loc), ORIGIN(PMI_PSPR))

SECTIONS
{
  /*
  .bmhd_0 (0x80000000) :
  {
    BootModeIndex = .;
    LONG (0x00000000);
    LONG (0xb3590070);
    LONG (0x00000000);
    LONG (0x00000000);
    LONG (0x00000000);
    LONG (0x00000000);
    LONG (0x791eb864);
    LONG (0x86e1479b);
  } */
/* This section is always required as Boot mode header 0 address absolutely
   restricted at address 0x80000000 */
  .bmhd0 (0x80000000) : FLAGS(arl)
  {
    BootModeHeader0 = .;
    KEEP (*(.bmhd0))
  } > PMU_PFLASH0

/* This section is always required as Boot mode header 1 address absolutely
   restricted at address 0x80020000 */
  .bmhd1 (0x80020000) : FLAGS(arl)
  {
    BootModeHeader1  = .;
    KEEP (*(.bmhd1));
  } > PMU_PFLASH0

/* This section is always required as user start address absolutely restricted
   at address 0x80000020 */
  .startup (0x80000020) : FLAGS(rxl)
  {
    BootModeIndex = .;
    KEEP (*(.startup));
  } > PMU_PFLASH0 =0x800

  .zrodata : FLAGS(arzl)
  {
    *(.zrodata)
    *(.zrodata.*)
  } > PMU_PFLASH0

  .sdata2 : FLAGS(arsl)
  {
    *(.srodata)
    *(.srodata.*)
  } > PMU_PFLASH0

  _SMALL_DATA2_ = SIZEOF(CORE_SEC(.sdata2)) ? ADDR(CORE_SEC(.sdata2)) + 32k : (ADDR(CORE_SEC(.sdata2)) & 0xF0000000) + 32k ;
  __A1_MEM = _SMALL_DATA2_;

  .rodata : FLAGS(arl)
  {
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
/*
 * Create the clear and copy tables that tell the startup code
 * which memory areas to clear and to copy, respectively.
 */
    . = ALIGN(4) ;
    PROVIDE(__clear_table = .);
    LONG(0 + ADDR(.zbss));        LONG(SIZEOF(.zbss));
    LONG(0 + ADDR(.sbss));        LONG(SIZEOF(.sbss));
    LONG(0 + ADDR(.bss));         LONG(SIZEOF(.bss));
    LONG(0 + ADDR(.lmu_zbss));    LONG(SIZEOF(.lmu_zbss));
    LONG(0 + ADDR(.lmu_sbss));    LONG(SIZEOF(.lmu_sbss));
    LONG(0 + ADDR(.lmu_bss));     LONG(SIZEOF(.lmu_bss));
    LONG(-1);                     LONG(-1);
    PROVIDE(__copy_table = .) ;
    LONG(LOADADDR(.zdata));       LONG(ADDR(.zdata));       LONG(SIZEOF(.zdata));
    LONG(LOADADDR(.sdata));       LONG(ADDR(.sdata));       LONG(SIZEOF(.sdata));
    LONG(LOADADDR(.data));        LONG(ADDR(.data));        LONG(SIZEOF(.data));
    LONG(LOADADDR(.lmu_zdata));   LONG(ADDR(.lmu_zdata));   LONG(SIZEOF(.lmu_zdata));
    LONG(LOADADDR(.lmu_sdata));   LONG(ADDR(.lmu_sdata));   LONG(SIZEOF(.lmu_sdata));
    LONG(LOADADDR(.lmu_data));    LONG(ADDR(.lmu_data));    LONG(SIZEOF(.lmu_data));
    LONG(LOADADDR(.psram_text));  LONG(ADDR(.psram_text));  LONG(SIZEOF(.psram_text));
    LONG(-1);                     LONG(-1);                 LONG(-1);
    . = ALIGN(8);
  } > PMU_PFLASH0

  /*
   * Section for trap table
   */
  .traptab : ALIGN(32) FLAGS(ax)
  {
    KEEP(*(.traptab))
    KEEP(*(.traptab*))
    . = ALIGN(8);
  } > PMU_PFLASH0


/*
 * C++ exception handling tables. NOTE: gcc emits .eh_frame
 * sections when compiling C sources with debugging enabled (-g).
 * If you can be sure that your final application consists
 * exclusively of C objects (i.e., no C++ objects), you may use
 * the -R option of the "strip" and "objcopy" utilities to remove
 * the .eh_frame section from the executable.
 */
  .eh_frame : FLAGS(axl)
  {
    *(.gcc_except_table)
    __EH_FRAME_BEGIN__ = . ;
    KEEP (*(.eh_frame))
    __EH_FRAME_END__ = . ;
    *(.jcr)
    . = ALIGN(8);
  } > PMU_PFLASH0

  /*
   * Constructors and destructors.
   */
  .ctors : FLAGS(axl)
  {
    __CTOR_LIST__ = . ;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2);
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    LONG(0) ;
    __CTOR_END__ = . ;
    . = ALIGN(8);
  } > PMU_PFLASH0

  .dtors : FLAGS(axl)
  {
    __DTOR_LIST__ = . ;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2);
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    LONG(0) ;
    __DTOR_END__ = . ;
    . = ALIGN(8);
  } > PMU_PFLASH0

  /*
   * Section for interrupt table CPU0
   */
  .inttab_cpu0 : ALIGN(8192) FLAGS(ax)
  {
    KEEP (*(.inttab_cpu0));
    KEEP (*(.*.inttab_cpu0));
    . = ALIGN(8);
  } > PMU_PFLASH0

  .text : ALIGN(8) FLAGS(axl)
  {
    PROVIDE(__text_start = .);
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf32.em. */
    *(.gnu.warning)
    . = ALIGN(8);
  } > PMU_PFLASH0

  .sdata3 : FLAGS(arsl)
  {
    *(.rodata_a8)
    *(.rodata_a8.*)
  } > PMU_PFLASH0

  _SMALL_DATA3_ = SIZEOF(CORE_SEC(.sdata3)) ? ADDR(CORE_SEC(.sdata3)) + 32k : (ADDR(CORE_SEC(.sdata3)) & 0xF0000000) + 32k ;
  __A8_MEM = _SMALL_DATA3_;

  .zdata : ALIGN(4) FLAGS(awzl)
  {
    *(.zdata)
    *(.zdata.*)
    *(.gnu.linkonce.z.*)
  } > DMI_DSPR AT> PMU_PFLASH0

  .zbss (NOLOAD) : ALIGN(4) FLAGS(awz)
  {
    *(.zbss)
    *(.zbss.*)
    *(.bbss)
    *(.bbss.*)
    *(.gnu.linkonce.zb.*)	
  } > DMI_DSPR

  .sdata : ALIGN(4) FLAGS(awsl)
  {
    *(.sdata)
    *(.sdata.*)
  } > DMI_DSPR AT> PMU_PFLASH0

  _SMALL_DATA_ = SIZEOF(CORE_SEC(.sdata)) ? ADDR(CORE_SEC(.sdata)) + 32k : (ADDR(CORE_SEC(.sdata)) & 0xF0000000) + 32k ;
  __A0_MEM = _SMALL_DATA_;

  .sbss (NOLOAD) : ALIGN(4) FLAGS(aws)
  {
    *(.sbss)
    *(.sbss.*)
  } > DMI_DSPR

  .data : ALIGN(4) FLAGS(awl)
  {
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
  } > DMI_DSPR AT> PMU_PFLASH0

  .bss (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*) 	
  } > DMI_DSPR

  .heap (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    PROVIDE(__HEAP = .);
    . += __HEAP_SIZE;
    PROVIDE(__HEAP_END = .);
  } > DMI_DSPR

/* Stacks and CSA sections */
  .ustack (__DSPR_START + __USTACK0_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    __USTACK0_AREA_END = .;
    *(.ustack)
    *(.ustack_cpu0)
    PROVIDE(__USTACK0_END = .);
    . = __USTACK0_AREA_END + __USTACK_SIZE;
    . = ALIGN(8);
    PROVIDE(__USTACK0 = .);
  } > DMI_DSPR

  .istack (__DSPR_START + __ISTACK0_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    PROVIDE(__ISTACK0_END = .);
    . += __ISTACK_SIZE;
    PROVIDE(__ISTACK0 = .);
  } > DMI_DSPR

  .csa (__DSPR_START + __CSA0_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA0 = .);
    . += __CSA_SIZE;
    PROVIDE(__CSA0_END = .);
  } > DMI_DSPR

/* Program Scratch-Pad sections */
  .psram_text : ALIGN(2) FLAGS(awx)
  {
    *(.psram_text)
    *(.psram_cpu0)
    *(.cpu0_psram)
  } > PMI_PSPR AT> PMU_PFLASH0

  .lmu_zdata : ALIGN(4) FLAGS(awzl)
  {
    *(.zdata_lmu)
    *(.zdata_lmu.*)
  } > LMU_SRAM AT> PMU_PFLASH0

  .lmu_zbss (NOLOAD) : ALIGN(4) FLAGS(awz)
  {
    *(.zbss_lmu)
    *(.zbss_lmu.*)
  } > LMU_SRAM

  .lmu_sdata : ALIGN(4) FLAGS(awsl)
  {
    *(.sdata_lmu)
    *(.sdata_lmu.*)
  } > LMU_SRAM AT> PMU_PFLASH0

  .lmu_sbss (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.sbss_lmu)
    *(.sbss_lmu.*)
  } > LMU_SRAM

  _SMALL_DATA4_ = SIZEOF(.lmu_sdata) ? ADDR(.lmu_sdata) + 32k : (ADDR(.lmu_sdata) & 0xF0000000) + 32k ;
  __A9_MEM = _SMALL_DATA4_;

  .lmu_data : ALIGN(4) FLAGS(awl)
  {
    *(.lmu_data)
    *(.lmu_data.*)
    *(.data_lmu)
    *(.data_lmu.*)
    *(.lmudata)
    *(.lmudata.*)
  } > LMU_SRAM AT> PMU_PFLASH0

  .lmu_bss (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.lmu_bss)
    *(.lmu_bss.*)
    *(.bss_lmu)
    *(.bss_lmu.*)
    *(.lmubss)
    *(.lmubss.*)
  } > LMU_SRAM

/* Define a default symbol for address 0. */
  NULL = DEFINED (NULL) ? NULL : 0 ;

/*
 * DWARF debug sections.
 * Symbols in the DWARF debugging sections are relative to the
 * beginning of the section, so we begin them at 0.
 */
/*
 * DWARF 1
 */
  .comment         0 : { *(.comment) }
  .debug           0 : { *(.debug) }
  .line            0 : { *(.line) }
/*
 * GNU DWARF 1 extensions
 */
  .debug_srcinfo   0 : { *(.debug_srcinfo) }
  .debug_sfnames   0 : { *(.debug_sfnames) }
/*
 * DWARF 1.1 and DWARF 2
 */
  .debug_aranges   0 : { *(.debug_aranges) }
  .debug_pubnames  0 : { *(.debug_pubnames) }
/*
 * DWARF 2
 */
  .debug_info      0 : { *(.debug_info) }
  .debug_abbrev    0 : { *(.debug_abbrev) }
  .debug_line      0 : { *(.debug_line) }
  .debug_frame     0 : { *(.debug_frame) }
  .debug_str       0 : { *(.debug_str) }
  .debug_loc       0 : { *(.debug_loc) }
  .debug_macinfo   0 : { *(.debug_macinfo) }
  .debug_ranges    0 : { *(.debug_ranges) }
/*
 * SGI/MIPS DWARF 2 extensions
 */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
/*
 * Optional sections that may only appear when relocating.
 */
/*
 * Optional sections that may appear regardless of relocating.
 */
  .version_info    0 : { *(.version_info) }
  .boffs           0 : { KEEP (*(.boffs)) }
}

/* The symbol __TRICORE_DERIVATE_NAME__ will be defined in the ee_tc_cstart.c and is
 * tested here to confirm that this memory map and the startup file will
 * fit together
*/
  _. = ASSERT ((__TRICORE_DERIVATE_MEMORY_MAP__ == __TRICORE_DERIVATE_NAME__), "Using wrong Memory Map. This Map is for TC22x");

/* Make sure that _START symbol is in the right place. */
  _. = ASSERT (_start == 0x80000020, "_start is not in the right place");
/* Make sure CSA, stack and heap addresses are properly aligned. */
  _. = ASSERT ((__CSA0 & 0x3f) == 0 , "1llegal CSA start address");
  _. = ASSERT ((__CSA_SIZE & 0x3f) == 0 , "Illegal CSA size");
  _. = ASSERT ((__ISTACK0 & 7) == 0 , "ISTACK not double-word aligned");
  _. = ASSERT ((__USTACK0 & 7) == 0 , "USTACK not double-word aligned");
  _. = ASSERT ((__HEAP_END & 7) == 0 , "HEAP not double-word aligned");

