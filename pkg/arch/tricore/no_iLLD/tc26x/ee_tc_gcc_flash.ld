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

/**
 *
 * This file derives from a modification of the Infineon startup scripts,
 * distributed under the following license:
 *
 * \file Lcf_Gnuc_Tricore_Tc.lsl
 * \brief Linker command file for Gnuc compiler.
 *
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
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
 */

/** \file   ee_tc_gcc_flash.ld
 *  \brief  Linker script file for GCC compiler (no iLLD integration)
 *  \author Errico Guidieri
 *  \date   2017
 */
 
OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_start)

/* Force to link the variable that contains the "TriCore ID" used to compile */
EXTERN(__TRICORE_DERIVATE_NAME__)
__TRICORE_DERIVATE_MEMORY_MAP__ = 0x2600;

/* CSA list size */
__CSA_SIZE = DEFINED (__CSA_SIZE) ? __CSA_SIZE : 8k;
/* Interrupt stack size */
__ISTACK_SIZE = DEFINED (__ISTACK_SIZE) ? __ISTACK_SIZE : 1K;
/* User stack size */
__USTACK_SIZE = DEFINED (__USTACK_SIZE) ? __USTACK_SIZE : 4K;

/* Heap size */
__HEAP_SIZE = DEFINED (__HEAP_SIZE) ? __HEAP_SIZE : 0k;

/* CPU0 CSA list size */
__CSA0_SIZE = DEFINED (__CSA0_SIZE) ? __CSA0_SIZE : __CSA_SIZE;
/* CPU0 Interrupt stack size */
__ISTACK0_SIZE = DEFINED (__ISTACK0_SIZE) ? __ISTACK0_SIZE : __ISTACK_SIZE;
/* CPU0 User stack size */
__USTACK0_SIZE = DEFINED (__USTACK0_SIZE) ? __USTACK0_SIZE : __USTACK_SIZE;

/* CPU1 CSA list size */
__CSA1_SIZE = DEFINED (__CSA1_SIZE) ? __CSA1_SIZE : __CSA_SIZE;
/* CPU1 Interrupt stack size */
__ISTACK1_SIZE = DEFINED (__ISTACK1_SIZE) ? __ISTACK1_SIZE : __ISTACK_SIZE;
/* CPU1 User stack size */
__USTACK1_SIZE = DEFINED (__USTACK1_SIZE) ? __USTACK1_SIZE : __USTACK_SIZE;

__DSPR1_START = 0x60000000;
__DSPR0_START = 0x70000000;

__DSPR1_SIZE = 120k;
__DSPR0_SIZE = 72k;

/* 1k guard area */
__CSA0_OFFSET    = (__DSPR0_SIZE  - 1k  - __CSA0_SIZE);
/* 256 byte guard area */
__ISTACK0_OFFSET = (__CSA0_OFFSET - 256 - __ISTACK0_SIZE);
/* 256 byte guard area */
__USTACK0_OFFSET = (__ISTACK0_OFFSET - 256 - __USTACK0_SIZE);

/* 1k guard area */
__CSA1_OFFSET    = (__DSPR1_SIZE  - 1k  - __CSA1_SIZE);
/* 256 byte guard area */
__ISTACK1_OFFSET = (__CSA1_OFFSET - 256 - __ISTACK1_SIZE);
/* 256 byte guard area */
__USTACK1_OFFSET = (__ISTACK1_OFFSET - 256 - __USTACK1_SIZE);

MEMORY
{
/* Scratch-Pad RAMs Core1 */
  DMI_DSPR1_local (w!xpc1): org = 0xD0000000, len = 120K
  DMI_DSPR1       (w!xpc1): org = 0x60000000, len = 120K
  PMI_PSPR1       (wx!pc1): org = 0x60100000, len = 32K

/* Scratch-Pad RAMs Core0 */
  DMI_DSPR0_local (w!xpc0): org = 0xD0000000, len = 72K
  DMI_DSPR0       (w!xpc0): org = 0x70000000, len = 72K
  PMI_PSPR0       (wx!pc0): org = 0x70100000, len = 16K

/* Program Scratch-Pad RAM (PSPR). Local Addressing */
  PMI_PSRAM_local (wx!p): org = 0xC0000000, len = 24K

/* Program Flash Memory (PFLASH0) */
  PMU_PFLASH      (rx!p): org = 0x80000000, len = 1M+512K
  PMU_PFLASH_nc   (rx!p): org = 0xA0000000, len = 1M+512K

/* Data Flash Memory (DFLASH0) */
  PMU_DFLASH0     (r!xp): org = 0xAF000000, len = 1M+16K

  EDMEM           (w!xp): org = 0x9f000000, len = 1M
  EDMEM_nc        (w!xp): org = 0xBf000000, len = 1M

/* Boot ROM (BROM) */
  BROM            (rx!p): org = 0x8FFF8000, len = 32K
}

/* Map local memory address to a global address */ 
REGION_MAP(CPU1 , ORIGIN(DMI_DSPR1_local), LENGTH(DMI_DSPR1_local), ORIGIN(DMI_DSPR1))
REGION_MAP(CPU0 , ORIGIN(DMI_DSPR0_local), LENGTH(DMI_DSPR0_local), ORIGIN(DMI_DSPR0))

/* Un-comment one of the below statements to enable CpuX DMI RAM to hold global variables */
/* REGION_ALIAS(GLOBAL_RAM , DMI_DSPR1) */
REGION_ALIAS(GLOBAL_RAM , DMI_DSPR0)

CORE_ID = GLOBAL ;

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
  } > PMU_PFLASH

/* This section is always required as Boot mode header 1 address absolutely
   restricted at address 0x80020000 */
  .bmhd1 (0x80020000) : FLAGS(arl)
  {
    BootModeHeader1  = .;
    KEEP (*(.bmhd1));
  } > PMU_PFLASH

/* This section is always required as user start address absolutely restricted
   at address 0x80000020 */
  .startup (0x80000020) : FLAGS(rxl)
  {
    BootModeIndex = .;
    KEEP (*(.startup));
  } > PMU_PFLASH =0x800

/* This section contains the data indirection pointers to interface external
   devices */
/*  .interface_const (0x80000040) :
  {
    __IF_CONST = .;
    KEEP (*(.interface_const));
  } > PMU_PFLASH
*/

  .zrodata : FLAGS(arzl)
  {
    *(.zrodata)
    *(.zrodata.*)
  } > PMU_PFLASH

  .sdata2 : FLAGS(arsl)
  {
    *(.srodata)
    *(.srodata.*)
  } > PMU_PFLASH

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
    LONG(0 + ADDR(.CPU1.zbss));   LONG(SIZEOF(.CPU1.zbss));
    LONG(0 + ADDR(.CPU1.bss));    LONG(SIZEOF(.CPU1.bss));
    LONG(0 + ADDR(.CPU0.zbss));   LONG(SIZEOF(.CPU0.zbss));
    LONG(0 + ADDR(.CPU0.bss));    LONG(SIZEOF(.CPU0.bss));
    LONG(0 + ADDR(.zbss));        LONG(SIZEOF(.zbss));
    LONG(0 + ADDR(.sbss));        LONG(SIZEOF(.sbss));
    LONG(0 + ADDR(.bss));         LONG(SIZEOF(.bss));
    LONG(0 + ADDR(.lmu_zbss));    LONG(SIZEOF(.lmu_zbss));
    LONG(0 + ADDR(.lmu_sbss));    LONG(SIZEOF(.lmu_sbss));
    LONG(0 + ADDR(.lmu_bss));     LONG(SIZEOF(.lmu_bss));
    LONG(-1);                     LONG(-1);
    PROVIDE(__copy_table = .) ;
    LONG(LOADADDR(.CPU1.zdata));  LONG(ADDR(.CPU1.zdata));  LONG(SIZEOF(.CPU1.zdata));
    LONG(LOADADDR(.CPU1.data));   LONG(ADDR(.CPU1.data));   LONG(SIZEOF(.CPU1.data));
    LONG(LOADADDR(.CPU0.zdata));  LONG(ADDR(.CPU0.zdata));  LONG(SIZEOF(.CPU0.zdata));
    LONG(LOADADDR(.CPU0.data));   LONG(ADDR(.CPU0.data));   LONG(SIZEOF(.CPU0.data));
    LONG(LOADADDR(.zdata));       LONG(ADDR(.zdata));       LONG(SIZEOF(.zdata));
    LONG(LOADADDR(.sdata));       LONG(ADDR(.sdata));       LONG(SIZEOF(.sdata));
    LONG(LOADADDR(.data));        LONG(ADDR(.data));        LONG(SIZEOF(.data));
    LONG(LOADADDR(.lmu_zdata));   LONG(ADDR(.lmu_zdata));   LONG(SIZEOF(.lmu_zdata));
    LONG(LOADADDR(.lmu_sdata));   LONG(ADDR(.lmu_sdata));   LONG(SIZEOF(.lmu_sdata));
    LONG(LOADADDR(.lmu_data));    LONG(ADDR(.lmu_data));    LONG(SIZEOF(.lmu_data));
    LONG(LOADADDR(.CPU0.psram_text)); LONG(ADDR(.CPU0.psram_text)); LONG(SIZEOF(.CPU0.psram_text));
    LONG(LOADADDR(.CPU1.psram_text)); LONG(ADDR(.CPU1.psram_text)); LONG(SIZEOF(.CPU1.psram_text));
    LONG(-1);                         LONG(-1);                     LONG(-1);
    . = ALIGN(8);
  } > PMU_PFLASH

  /*
   * Section for trap table
   */
/*
  CORE_SEC(.traptab_cpu0) : ALIGN(32) FLAGS(ax)
  {
    KEEP(*(.traptab_cpu0))
    KEEP(*(.traptab_cpu0*))
    . = ALIGN(8);
  } > PMU_PFLASH

  CORE_SEC(.traptab_cpu1) : ALIGN(32) FLAGS(ax)
  {
    PROVIDE(__TRAPTAB1 = .);
    KEEP(*(.traptab_cpu1))
    KEEP(*(.traptab_cpu1*))
    . = ALIGN(8);
  } > PMU_PFLASH

  CORE_SEC(.traptab_cpu2) : ALIGN(32) FLAGS(ax)
  {
    PROVIDE(__TRAPTAB2 = .);
    KEEP(*(.traptab_cpu2))
    KEEP(*(.traptab_cpu2*))
    . = ALIGN(8);
  } > PMU_PFLASH
*/

  .traptab : ALIGN(32) FLAGS(ax)
  {
    KEEP(*(.traptab))
    KEEP(*(.traptab*))
    . = ALIGN(8);
  } > PMU_PFLASH


/*
 * C++ exception handling tables. NOTE: gcc emits .eh_frame
 * sections when compiling C sources with debugging enabled (-g).
 * If you can be sure that your final application consists
 * exclusively of C objects (i.e., no C++ objects), you may use
 * the -R option of the "strip" and "objcopy" utilities to remove
 * the .eh_frame section from the executable.
 */
  CORE_SEC(.eh_frame) : FLAGS(axl)
  {
    *(.gcc_except_table)
    __EH_FRAME_BEGIN__ = . ;
    KEEP (*(.eh_frame))
    __EH_FRAME_END__ = . ;
    *(.jcr)
    . = ALIGN(8);
  } > PMU_PFLASH

  /*
   * Constructors and destructors.
   */
  CORE_SEC(.ctors) : FLAGS(axl)
  {
    __CTOR_LIST__ = . ;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2);
    *(.ctors)
    LONG(0) ;
    __CTOR_END__ = . ;
    . = ALIGN(8);
  } > PMU_PFLASH

  CORE_SEC(.dtors) : FLAGS(axl)
  {
    __DTOR_LIST__ = . ;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2);
    *(.dtors)
    LONG(0) ;
    __DTOR_END__ = . ;
    . = ALIGN(8);
  } > PMU_PFLASH

  /*
   * Section for interrupt table CPU0
   */
  CORE_SEC(.inttab_cpu0) : ALIGN(8192) FLAGS(ax)
  {
    KEEP (*(.inttab_cpu0));
    KEEP (*(.*.inttab_cpu0));
    . = ALIGN(8);
  } > PMU_PFLASH

  CORE_SEC(.text) : ALIGN(8) FLAGS(axl)
  {
    PROVIDE(__text_start = .);
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf32.em. */
    *(.gnu.warning)
    . = ALIGN(8);
  } > PMU_PFLASH

  CORE_SEC(.sdata3) : FLAGS(arsl)
  {
    *(.rodata_a8)
    *(.rodata_a8.*)
  } > PMU_PFLASH

  _SMALL_DATA3_ = SIZEOF(CORE_SEC(.sdata3)) ? ADDR(CORE_SEC(.sdata3)) + 32k : (ADDR(CORE_SEC(.sdata3)) & 0xF0000000) + 32k ;
  __A8_MEM = _SMALL_DATA3_;

  /*
   * Section for interrupt table CPU1
   */
  CORE_SEC(.inttab_cpu1) : ALIGN(8192) FLAGS(ax)
  {
    PROVIDE(__INTTAB1 = .);
    KEEP (*(.inttab_cpu1));
    KEEP (*(.*.inttab_cpu1));
    . = ALIGN(8);
  } > PMU_PFLASH

  CORE_SEC(.zdata) : ALIGN(4) FLAGS(awzl)
  {
    *(.zdata)
    *(.zdata.*)
    *(.gnu.linkonce.z.*)
  } > GLOBAL_RAM AT> PMU_PFLASH

  CORE_SEC(.zbss) (NOLOAD) : ALIGN(4) FLAGS(awz)
  {
    *(.zbss)
    *(.zbss.*)
    *(.bbss)
    *(.bbss.*)
    *(.gnu.linkonce.zb.*)	
  } > GLOBAL_RAM

  CORE_SEC(.sdata) : ALIGN(4) FLAGS(awsl)
  {
    *(.sdata)
    *(.sdata.*)
  } > GLOBAL_RAM AT> PMU_PFLASH

  _SMALL_DATA_ = SIZEOF(CORE_SEC(.sdata)) ? ADDR(CORE_SEC(.sdata)) + 32k : (ADDR(CORE_SEC(.sdata)) & 0xF0000000) + 32k ;
  __A0_MEM = _SMALL_DATA_;

  CORE_SEC(.sbss) (NOLOAD) : ALIGN(4) FLAGS(aws)
  {
    *(.sbss)
    *(.sbss.*)
  } > GLOBAL_RAM

  CORE_SEC(.data) : ALIGN(4) FLAGS(awl)
  {
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
  } > GLOBAL_RAM AT> PMU_PFLASH

  CORE_SEC(.bss) (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*) 	
  } > GLOBAL_RAM

  CORE_SEC(.heap) (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    PROVIDE(__HEAP = .);
    . += __HEAP_SIZE;
    PROVIDE(__HEAP_END = .);
  } > GLOBAL_RAM

}

CORE_ID = CPU1;

SECTIONS
{
/* Near data sections */
  CORE_SEC(.zdata) : ALIGN(4) FLAGS(awzl)
  {
    *(.zdata_cpu1)
    *(.zdata_cpu1.*)
  } > DMI_DSPR1 AT> PMU_PFLASH

  CORE_SEC(.zbss)(NOLOAD) : ALIGN(4) FLAGS(awz)
  {
    *(.zbss_cpu1)
    *(.zbss_cpu1.*)
  } > DMI_DSPR1
/* Data sections */
  CORE_SEC(.data) : ALIGN(4) FLAGS(awl)
  {
    *(.data_cpu1)
    *(.data_cpu1.*)
  } > DMI_DSPR1 AT> PMU_PFLASH

  CORE_SEC(.bss) (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.bss_cpu1)
    *(.bss_cpu1.*)
  } > DMI_DSPR1

/* Stacks and CSA sections */
  CORE_SEC(.ustack) (__DSPR1_START + __USTACK1_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    __USTACK1_AREA_END = .;
    *(.ustack_cpu1)
    PROVIDE(__USTACK1_END = .);
    . = __USTACK1_AREA_END + __USTACK1_SIZE;
    . = ALIGN(8);
    PROVIDE(__USTACK1 = .);
  } > DMI_DSPR1

  CORE_SEC(.istack) (__DSPR1_START + __ISTACK1_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    PROVIDE(__ISTACK1_END = .);
    . += __ISTACK1_SIZE;
    PROVIDE(__ISTACK1 = .);
  } > DMI_DSPR1

  CORE_SEC(.csa) (__DSPR1_START + __CSA1_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA1 = .);
    . += __CSA1_SIZE;
    PROVIDE(__CSA1_END = .);
  } > DMI_DSPR1

/* Program Scratch-Pad sections */
  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    *(.psram_cpu1)
    *(.cpu1_psram)
  } > PMI_PSPR1 AT> PMU_PFLASH
}

CORE_ID = CPU0;

SECTIONS
{
/* Near data sections */
  CORE_SEC(.zdata) : ALIGN(4) FLAGS(awzl)
  {
    *(.zdata_cpu0)
    *(.zdata_cpu0.*)
  } > DMI_DSPR0 AT> PMU_PFLASH

  CORE_SEC(.zbss) (NOLOAD) : ALIGN(4) FLAGS(awz)
  {
    *(.zbss_cpu0)
    *(.zbss_cpu0.*)
  } > DMI_DSPR0

/* Data sections */
  CORE_SEC(.data) : ALIGN(4) FLAGS(awl)
  {
    *(.data_cpu0)
    *(.data_cpu0.*)
  } > DMI_DSPR0 AT> PMU_PFLASH

  CORE_SEC(.bss) (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.bss_cpu0)
    *(.bss_cpu0.*)
  } > DMI_DSPR0

/* Stacks and CSA sections */

  CORE_SEC(.ustack) (__DSPR0_START + __USTACK0_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    __USTACK0_AREA_END = .;
    *(.ustack_cpu0)
    PROVIDE(__USTACK0_END = .);
    . = __USTACK0_AREA_END + __USTACK0_SIZE;
    . = ALIGN(8);
    PROVIDE(__USTACK0 = .);
  } > DMI_DSPR0

  CORE_SEC(.istack) (__DSPR0_START + __ISTACK0_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    PROVIDE(__ISTACK0_END = .);
    . = . + __ISTACK0_SIZE;
    PROVIDE(__ISTACK0 = .);
  } > DMI_DSPR0

  CORE_SEC(.csa) (__DSPR0_START + __CSA0_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA0 = .);
    . = . + __CSA0_SIZE;
    PROVIDE(__CSA0_END = .);
  } > DMI_DSPR0

/* Program Scratch-Pad sections */
  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    *(.psram_cpu0)
    *(.cpu0_psram)
  } > PMI_PSPR0 AT> PMU_PFLASH
}

/* RAM sections without cpu suffix will go to default ram defined above with REGION_ALIAS */
CORE_ID = GLOBAL;

SECTIONS
{
  CORE_SEC(.lmu_zdata) : ALIGN(4) FLAGS(awzl)
  {
    *(.zdata_lmu)
    *(.zdata_lmu.*)
  } > GLOBAL_RAM AT> PMU_PFLASH

  CORE_SEC(.lmu_zbss) (NOLOAD) : ALIGN(4) FLAGS(awz)
  {
    *(.zbss_lmu)
    *(.zbss_lmu.*)
  } > GLOBAL_RAM

  CORE_SEC(.lmu_sdata) : ALIGN(4) FLAGS(awsl)
  {
    *(.sdata_lmu)
    *(.sdata_lmu.*)
  } > GLOBAL_RAM AT> PMU_PFLASH

  CORE_SEC(.lmu_sbss) (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.sbss_lmu)
    *(.sbss_lmu.*)
  } > GLOBAL_RAM

  _SMALL_DATA4_ = SIZEOF(CORE_SEC(.lmu_sdata)) ? ADDR(CORE_SEC(.lmu_sdata)) + 32k : (ADDR(CORE_SEC(.lmu_sdata)) & 0xF0000000) + 32k ;
  __A9_MEM = _SMALL_DATA4_;

  CORE_SEC(.lmu_data) : ALIGN(4) FLAGS(awl)
  {
     *(.lmu_data)
    *(.lmu_data.*)
    *(.data_lmu)
    *(.data_lmu.*)
    *(.lmudata)
    *(.lmudata.*)
  } > GLOBAL_RAM AT> PMU_PFLASH

  CORE_SEC(.lmu_bss) (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.lmu_bss)
    *(.lmu_bss.*)
    *(.bss_lmu)
    *(.bss_lmu.*)
    *(.lmubss)
    *(.lmubss.*)
  } > GLOBAL_RAM

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
  _. = ASSERT ((__TRICORE_DERIVATE_MEMORY_MAP__ == __TRICORE_DERIVATE_NAME__), "Using wrong Memory Map. This Map is for TC26x");

/* Make sure that _START symbol is in the right place. */
  _. = ASSERT (_start == 0x80000020, "_start is not in the right place");
/* Make sure CSA, stack and heap addresses are properly aligned. */
  _. = ASSERT ((__CSA0 & 0x3f) == 0 , "1llegal CSA0 start address");
  _. = ASSERT ((__CSA0_SIZE & 0x3f) == 0 , "Illegal CSA0 size");
  _. = ASSERT ((__ISTACK0 & 7) == 0 , "ISTACK0 not doubleword aligned");
  _. = ASSERT ((__USTACK0 & 7) == 0 , "USTACK0 not doubleword aligned");
  _. = ASSERT ((__CSA1 & 0x3f) == 0 , "1llegal CSA1 start address");
  _. = ASSERT ((__CSA1_SIZE & 0x3f) == 0 , "Illegal CSA1 size");
  _. = ASSERT ((__ISTACK1 & 7) == 0 , "ISTACK1 not doubleword aligned");
  _. = ASSERT ((__USTACK1 & 7) == 0 , "USTACK1 not doubleword aligned");
  _. = ASSERT ((__HEAP_END & 7) == 0 , "HEAP not doubleword aligned");

