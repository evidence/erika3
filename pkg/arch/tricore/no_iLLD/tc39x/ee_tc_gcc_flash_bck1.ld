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
 *  \brief  Linker script file for GCC compiler for TC39X (no iLLD integration)
 *  \author Errico Guidieri
 *  \date   2018
 */
 
OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_start)
/* This is how you force to link symbols
EXTERN(osEE_tc_bmhd_0_orig)
EXTERN(osEE_tc_bmhd_1_orig)
EXTERN(osEE_tc_bmhd_2_orig)
EXTERN(osEE_tc_bmhd_3_orig)
EXTERN(osEE_tc_bmhd_4_orig)
EXTERN(osEE_tc_bmhd_0_copy)
EXTERN(osEE_tc_bmhd_1_copy)
EXTERN(osEE_tc_bmhd_2_copy)
EXTERN(osEE_tc_bmhd_3_copy)
EXTERN(osEE_tc_bmhd_4_copy)
*/
/* Force to link the variable that contains the "TriCore ID" used to compile */
EXTERN(__TRICORE_DERIVATE_NAME__)
__TRICORE_DERIVATE_MEMORY_MAP__ = 0x3900;

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

/* CPU2 CSA list size */
__CSA2_SIZE = DEFINED (__CSA2_SIZE) ? __CSA2_SIZE : __CSA_SIZE;
/* CPU2 Interrupt stack size */
__ISTACK2_SIZE = DEFINED (__ISTACK2_SIZE) ? __ISTACK2_SIZE : __ISTACK_SIZE;
/* CPU2 User stack size */
__USTACK2_SIZE = DEFINED (__USTACK2_SIZE) ? __USTACK2_SIZE : __USTACK_SIZE;

/* CPU3 CSA list size */
__CSA3_SIZE = DEFINED (__CSA3_SIZE) ? __CSA3_SIZE : __CSA_SIZE;
/* CPU3 Interrupt stack size */
__ISTACK3_SIZE = DEFINED (__ISTACK3_SIZE) ? __ISTACK3_SIZE : __ISTACK_SIZE;
/* CPU3 User stack size */
__USTACK3_SIZE = DEFINED (__USTACK3_SIZE) ? __USTACK3_SIZE : __USTACK_SIZE;

/* CPU4 CSA list size */
__CSA4_SIZE = DEFINED (__CSA4_SIZE) ? __CSA4_SIZE : __CSA_SIZE;
/* CPU4 Interrupt stack size */
__ISTACK4_SIZE = DEFINED (__ISTACK4_SIZE) ? __ISTACK4_SIZE : __ISTACK_SIZE;
/* CPU4 User stack size */
__USTACK4_SIZE = DEFINED (__USTACK4_SIZE) ? __USTACK4_SIZE : __USTACK_SIZE;

/* CPU6 CSA list size */
__CSA6_SIZE = DEFINED (__CSA6_SIZE) ? __CSA6_SIZE : __CSA_SIZE;
/* CPU6 Interrupt stack size */
__ISTACK6_SIZE = DEFINED (__ISTACK6_SIZE) ? __ISTACK6_SIZE : __ISTACK_SIZE;
/* CPU6 User stack size */
__USTACK6_SIZE = DEFINED (__USTACK6_SIZE) ? __USTACK6_SIZE : __USTACK_SIZE;

__DSPR5_START = 0x10000000;
__DSPR4_START = 0x30000000;
__DSPR3_START = 0x40000000;
__DSPR2_START = 0x50000000;
__DSPR1_START = 0x60000000;
__DSPR0_START = 0x70000000;

__DSPR5_SIZE = 96k;
__DSPR4_SIZE = 96k;
__DSPR3_SIZE = 96k;
__DSPR2_SIZE = 96k;
__DSPR1_SIZE = DEFINED (__DSPR1_SIZE) ? __DSPR1_SIZE : 240k;
__DSPR0_SIZE = DEFINED (__DSPR0_SIZE) ? __DSPR0_SIZE : 240k;

/* 256 byte guard area */
__CSA0_OFFSET    = (__DSPR0_SIZE  - 256 - __CSA0_SIZE);
/* 256 byte guard area */
__ISTACK0_OFFSET = (__CSA0_OFFSET - 256 - __ISTACK0_SIZE);
/* 256 byte guard area */
__USTACK0_OFFSET = (__ISTACK0_OFFSET - 256 - __USTACK0_SIZE);

/* 256 byte guard area */
__CSA1_OFFSET    = (__DSPR1_SIZE  - 256  - __CSA1_SIZE);
/* 256 byte guard area */
__ISTACK1_OFFSET = (__CSA1_OFFSET - 256 - __ISTACK1_SIZE);
/* 256 byte guard area */
__USTACK1_OFFSET = (__ISTACK1_OFFSET - 256 - __USTACK1_SIZE);

/* 256 byte guard area */
__CSA2_OFFSET    = (__DSPR2_SIZE  - 256  - __CSA2_SIZE);
/* 256 byte guard area */
__ISTACK2_OFFSET = (__CSA2_OFFSET - 256 - __ISTACK2_SIZE);
/* 256 byte guard area */
__USTACK2_OFFSET = (__ISTACK2_OFFSET - 256 - __USTACK2_SIZE);

/* 256 byte guard area */
__CSA3_OFFSET    = (__DSPR3_SIZE  - 256 - __CSA3_SIZE);
/* 256 byte guard area */
__ISTACK3_OFFSET = (__CSA3_OFFSET - 256 - __ISTACK3_SIZE);
/* 256 byte guard area */
__USTACK3_OFFSET = (__ISTACK3_OFFSET - 256 - __USTACK3_SIZE);

/* 256 byte guard area */
__CSA4_OFFSET    = (__DSPR4_SIZE  - 256 - __CSA4_SIZE);
/* 256 byte guard area */
__ISTACK4_OFFSET = (__CSA4_OFFSET - 256 - __ISTACK4_SIZE);
/* 256 byte guard area */
__USTACK4_OFFSET = (__ISTACK4_OFFSET - 256 - __USTACK4_SIZE);

/* 256 byte guard area */
__CSA6_OFFSET    = (__DSPR5_SIZE  - 256 - __CSA6_SIZE);
/* 256 byte guard area */
__ISTACK6_OFFSET = (__CSA6_OFFSET - 256 - __ISTACK6_SIZE);
/* 256 byte guard area */
__USTACK6_OFFSET = (__ISTACK6_OFFSET - 256 - __USTACK6_SIZE);

MEMORY
{
/* Scratch-Pad RAMs Core6 */
/*  DMI_DSPR5_local (w!xpc6): org = 0xD0000000, len = 96K */
  DMI_DSPR5       (w!xpc6): org = 0x10000000, len = 96K
  PMI_PSPR5       (wx!pc6): org = 0x10100000, len = 64K

/* Scratch-Pad RAMs Core4 */
/*  DMI_DSPR4_local (w!xpc4): org = 0xD0000000, len = 96K */
  DMI_DSPR4       (w!xpc4): org = 0x30000000, len = 96K
  PMI_PSPR4       (wx!pc4): org = 0x30100000, len = 64K

/* Scratch-Pad RAMs Core3 */
/*  DMI_DSPR3_local (w!xpc3): org = 0xD0000000, len = 96K */
  DMI_DSPR3       (w!xpc3): org = 0x40000000, len = 96K
  PMI_PSPR3       (wx!pc3): org = 0x40100000, len = 64K

/* Scratch-Pad RAMs Core2 */
/*  DMI_DSPR2_local (w!xpc2): org = 0xD0000000, len = 96K */
  DMI_DSPR2       (w!xpc2): org = 0x50000000, len = 96K
  PMI_PSPR2       (wx!pc2): org = 0x50100000, len = 64K

/* Scratch-Pad RAMs Core1 */
/*  DMI_DSPR1_local (w!xpc1): org = 0xD0000000, len = 240K */
  DMI_DSPR1       (w!xpc1): org = 0x60000000, len = 240K
  PMI_PSPR1       (wx!pc1): org = 0x60100000, len = 64K

/* Scratch-Pad RAMs Core0 */
/*  DMI_DSPR0_local (w!xpc0): org = 0xD0000000, len = 240K */
  DMI_DSPR0       (w!xpc0): org = 0x70000000, len = 240K
  PMI_PSPR0       (wx!pc0): org = 0x70100000, len = 64K

/* Program Scratch-Pad RAM (PSPR). Local Addressing */
/*  PMI_PSRAM_local (wx!p): org = 0xC0000000, len = 64K */

/* Program Flash Memory 0 (PFLASH0) */
  PMU_PFLASH0     (rx!p): org = 0x80000000, len = 3M
  PMU_PFLASH0_nc  (rx!p): org = 0xA0000000, len = 3M

/* Program Flash Memory 1 (PFLASH1) */ 
  PMU_PFLASH1     (rx!p): org = 0x80300000, len = 3M
  PMU_PFLASH1_nc  (rx!p): org = 0xA0300000, len = 3M

/* Program Flash Memory 2 (PFLASH2) */
  PMU_PFLASH2     (rx!p): org = 0x80600000, len = 3M
  PMU_PFLASH2_nc  (rx!p): org = 0xA0600000, len = 3M

/* Program Flash Memory 3 (PFLASH3) */ 
  PMU_PFLASH3     (rx!p): org = 0x80900000, len = 3M
  PMU_PFLASH3_nc  (rx!p): org = 0xA0900000, len = 3M

/* Program Flash Memory 4 (PFLASH4) */ 
  PMU_PFLASH4     (rx!p): org = 0x80C00000, len = 3M
  PMU_PFLASH4_nc  (rx!p): org = 0xA0C00000, len = 3M

/* Program Flash Memory 5 (PFLASH5) */ 
  PMU_PFLASH5     (rx!p): org = 0x80F00000, len = 1M
  PMU_PFLASH5_nc  (rx!p): org = 0xA0F00000, len = 1M

/* Data Flash Memory (DFLASH0) */
  PMU_DFLASH0     (r!xp): org = 0xAF000000, len = 1M

/* User Configuration Blocks (UCB)*/
  PMU_UCB         (rx!p): org = 0xAf400000, len = 24K

/* Distributed LMU Core0 */
  DLMU_SRAM0    (w!xpc0): org = 0x90000000, len = 64K
  DLMU_SRAM0_nc (w!xpc0): org = 0xB0000000, len = 64K

/* Distributed LMU Core1 */
  DLMU_SRAM1    (w!xpc1): org = 0x90010000, len = 64K
  DLMU_SRAM1_nc (w!xpc1): org = 0xB0010000, len = 64K

/* Distributed LMU Core2 */
  DLMU_SRAM2    (w!xpc2): org = 0x90020000, len = 64K
  DLMU_SRAM2_nc (w!xpc2): org = 0xB0020000, len = 64K

/* Distributed LMU Core3 */
  DLMU_SRAM3    (w!xpc3): org = 0x90030000, len = 64K
  DLMU_SRAM3_nc (w!xpc3): org = 0xB0030000, len = 64K

/* Global Data RAM (LMU) */
  LMU_SRAM        (w!xp): org = 0x90040000, len = 768K
/* Global Data RAM (LMU). Not Cached (NC)*/
  LMU_SRAM_nc     (w!xp): org = 0xB0040000, len = 768K

/* Distributed LMU Core3 */
  DLMU_SRAM4    (w!xpc4): org = 0x90100000, len = 64K
  DLMU_SRAM4_nc (w!xpc4): org = 0xB0100000, len = 64K

/* Distributed LMU Core6 */
  DLMU_SRAM5    (w!xpc6): org = 0x90110000, len = 64K
  DLMU_SRAM5_nc (w!xpc6): org = 0xb0110000, len = 64K

  EDMEM           (w!xp): org = 0x99000000, len = 4M
  EDMEM_nc        (w!xp): org = 0xB9000000, len = 4M
}

/* Map local memory address to a global address */
/* REGION_MAP(CPU6 , ORIGIN(DMI_DSPR5_local), LENGTH(DMI_DSPR5_local), ORIGIN(DMI_DSPR5))
REGION_MAP(CPU4 , ORIGIN(DMI_DSPR4_local), LENGTH(DMI_DSPR4_local), ORIGIN(DMI_DSPR4))
REGION_MAP(CPU3 , ORIGIN(DMI_DSPR3_local), LENGTH(DMI_DSPR3_local), ORIGIN(DMI_DSPR3))
REGION_MAP(CPU2 , ORIGIN(DMI_DSPR2_local), LENGTH(DMI_DSPR2_local), ORIGIN(DMI_DSPR2))
REGION_MAP(CPU1 , ORIGIN(DMI_DSPR1_local), LENGTH(DMI_DSPR1_local), ORIGIN(DMI_DSPR1))
REGION_MAP(CPU0 , ORIGIN(DMI_DSPR0_local), LENGTH(DMI_DSPR0_local), ORIGIN(DMI_DSPR0)) */

/* Un-comment one of the below statements to enable CpuX DMI RAM to hold global
   variables */
/* REGION_ALIAS(GLOBAL_RAM , DMI_DSPR2) */
/* REGION_ALIAS(GLOBAL_RAM , DMI_DSPR1) */
REGION_ALIAS(GLOBAL_RAM , DMI_DSPR0)
/* REGION_ALIAS(GLOBAL_RAM , LMU_SRAM) */

REGION_ALIAS(GLOBAL_ROM , PMU_PFLASH0)

/* Map Cached and Non-Cached Addresses */
REGION_MIRROR("PMU_PFLASH0", "PMU_PFLASH0_nc")
REGION_MIRROR("PMU_PFLASH1", "PMU_PFLASH1_nc")
REGION_MIRROR("PMU_PFLASH2", "PMU_PFLASH2_nc")
REGION_MIRROR("PMU_PFLASH3", "PMU_PFLASH3_nc")
REGION_MIRROR("PMU_PFLASH4", "PMU_PFLASH4_nc")
REGION_MIRROR("PMU_PFLASH5", "PMU_PFLASH5_nc")
REGION_MIRROR("DLMU_SRAM0", "DLMU_SRAM0_nc")
REGION_MIRROR("DLMU_SRAM1", "DLMU_SRAM1_nc")
REGION_MIRROR("DLMU_SRAM2", "DLMU_SRAM2_nc")
REGION_MIRROR("DLMU_SRAM3", "DLMU_SRAM3_nc")
REGION_MIRROR("DLMU_SRAM4", "DLMU_SRAM4_nc")
REGION_MIRROR("DLMU_SRAM5", "DLMU_SRAM4_nc")
REGION_MIRROR("LMU_SRAM", "LMU_SRAM_nc")

/* Sections located at absolute fixed address */
  /* Fixed memory Allocations for stack memory and CSA */
CORE_ID = CPU6;
SECTIONS
{
  CORE_SEC(.ustack) (__DSPR5_START + __USTACK6_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    __USTACK6_AREA_END = .;
    *(.ustack_cpu6)
    PROVIDE(__USTACK6_END = .);
    . = __USTACK6_AREA_END + __USTACK6_SIZE;
    . = ALIGN(8);
    PROVIDE(__USTACK6 = .);
  } > DMI_DSPR5

  CORE_SEC(.istack) (__DSPR5_START + __ISTACK6_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    PROVIDE(__ISTACK6_END = .);
    . += __ISTACK6_SIZE;
    PROVIDE(__ISTACK6 = .);
  } > DMI_DSPR5

  CORE_SEC(.csa) (__DSPR5_START + __CSA6_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA6 = .);
    . += __CSA6_SIZE;
    PROVIDE(__CSA6_END = .);
  } > DMI_DSPR5
}

CORE_ID = CPU4;
SECTIONS
{
  CORE_SEC(.ustack) (__DSPR4_START + __USTACK4_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    __USTACK4_AREA_END = .;
    *(.ustack_cpu4)
    PROVIDE(__USTACK4_END = .);
    . = __USTACK4_AREA_END + __USTACK4_SIZE;
    . = ALIGN(8);
    PROVIDE(__USTACK4 = .);
  } > DMI_DSPR4

  CORE_SEC(.istack) (__DSPR4_START + __ISTACK4_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    PROVIDE(__ISTACK4_END = .);
    . += __ISTACK4_SIZE;
    PROVIDE(__ISTACK4 = .);
  } > DMI_DSPR4

  CORE_SEC(.csa) (__DSPR4_START + __CSA4_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA4 = .);
    . += __CSA4_SIZE;
    PROVIDE(__CSA4_END = .);
  } > DMI_DSPR4
}

CORE_ID = CPU3;
SECTIONS
{
  CORE_SEC(.ustack) (__DSPR3_START + __USTACK3_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    __USTACK3_AREA_END = .;
    *(.ustack_cpu3)
    PROVIDE(__USTACK3_END = .);
    . = __USTACK3_AREA_END + __USTACK3_SIZE;
    . = ALIGN(8);
    PROVIDE(__USTACK3 = .);
  } > DMI_DSPR3

  CORE_SEC(.istack) (__DSPR3_START + __ISTACK3_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    PROVIDE(__ISTACK3_END = .);
    . += __ISTACK3_SIZE;
    PROVIDE(__ISTACK3 = .);
  } > DMI_DSPR3

  CORE_SEC(.csa) (__DSPR3_START + __CSA3_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA3 = .);
    . += __CSA3_SIZE;
    PROVIDE(__CSA3_END = .);
  } > DMI_DSPR3
}

CORE_ID = CPU2;
SECTIONS
{
  CORE_SEC(.ustack) (__DSPR2_START + __USTACK2_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    __USTACK2_AREA_END = .;
    *(.ustack_cpu2)
    PROVIDE(__USTACK2_END = .);
    . = __USTACK2_AREA_END + __USTACK2_SIZE;
    . = ALIGN(8);
    PROVIDE(__USTACK2 = .);
  } > DMI_DSPR2

  CORE_SEC(.istack) (__DSPR2_START + __ISTACK2_OFFSET) : ALIGN(8) FLAGS(aw)
  {
    PROVIDE(__ISTACK2_END = .);
    . += __ISTACK2_SIZE;
    PROVIDE(__ISTACK2 = .);
  } > DMI_DSPR2

  CORE_SEC(.csa) (__DSPR2_START + __CSA2_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA2 = .);
    . += __CSA2_SIZE;
    PROVIDE(__CSA2_END = .);
  } > DMI_DSPR2
}

CORE_ID = CPU1;
SECTIONS
{
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
}

CORE_ID = CPU0;
SECTIONS
{
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
    . += __ISTACK0_SIZE;
    PROVIDE(__ISTACK0 = .);
  } > DMI_DSPR0

  CORE_SEC(.csa) (__DSPR0_START + __CSA0_OFFSET) : ALIGN(64) FLAGS(aw)
  {
    PROVIDE(__CSA0 = .);
    . += __CSA0_SIZE;
    PROVIDE(__CSA0_END = .);
  } > DMI_DSPR0
}

/* Fixed memory Allocations for _start */
CORE_ID = GLOBAL ;
SECTIONS
{
  /*  This section is always required as user start address absolutely
      restricted at address 0xA0000020 */
  .startup (0xA0000020) : FLAGS(rxl)
  {
    KEEP (*(.startup));
  } > PMU_PFLASH0_nc =0x800
}

/*Fixed memory Allocations for BMHD*/
CORE_ID = GLOBAL;
SECTIONS {
  .bmhd_0_orig (0xAF400000) : FLAGS(arl) { KEEP (*(.bmhd_0_orig)); } > PMU_UCB
  .bmhd_1_orig (0xAF400200) : FLAGS(arl) { KEEP (*(.bmhd_1_orig)); } > PMU_UCB
  .bmhd_2_orig (0xAF400400) : FLAGS(arl) { KEEP (*(.bmhd_2_orig)); } > PMU_UCB
  .bmhd_3_orig (0xAF400600) : FLAGS(arl) { KEEP (*(.bmhd_3_orig)); } > PMU_UCB
  .ucb_res     (0xAF400800) : FLAGS(arl) { . += 0x200; } > PMU_UCB
  .bmhd_0_copy (0xAF401000) : FLAGS(arl) { KEEP (*(.bmhd_0_copy)); } > PMU_UCB
  .bmhd_1_copy (0xAF401200) : FLAGS(arl) { KEEP (*(.bmhd_1_copy)); } > PMU_UCB
  .bmhd_2_copy (0xAF401400) : FLAGS(arl) { KEEP (*(.bmhd_2_copy)); } > PMU_UCB
  .bmhd_3_copy (0xAF401600) : FLAGS(arl) { KEEP (*(.bmhd_3_copy)); } > PMU_UCB
}

CORE_ID = CPU6;
SECTIONS
{

  /*
   * Section for interrupt table CPU0
   */
  .inttab_cpu6 : ALIGN(8192) FLAGS(ax)
  {
    KEEP (*(.inttab_cpu6));
    KEEP (*(.*.inttab_cpu6));
    . = ALIGN(8);
  } > PMU_PFLASH5
}

CORE_ID = CPU4;
SECTIONS
{

  /*
   * Section for interrupt table CPU0
   */
  .inttab_cpu4 : ALIGN(8192) FLAGS(ax)
  {
    KEEP (*(.inttab_cpu4));
    KEEP (*(.*.inttab_cpu4));
    . = ALIGN(8);
  } > PMU_PFLASH4
}

CORE_ID = CPU3;
SECTIONS
{

  /*
   * Section for interrupt table CPU0
   */
  .inttab_cpu3 : ALIGN(8192) FLAGS(ax)
  {
    KEEP (*(.inttab_cpu3));
    KEEP (*(.*.inttab_cpu3));
    . = ALIGN(8);
  } > PMU_PFLASH3
}

CORE_ID = CPU2;
SECTIONS
{

  /*
   * Section for interrupt table CPU0
   */
  .inttab_cpu2 : ALIGN(8192) FLAGS(ax)
  {
    KEEP (*(.inttab_cpu2));
    KEEP (*(.*.inttab_cpu2));
    . = ALIGN(8);
  } > PMU_PFLASH2
}

CORE_ID = CPU1;
SECTIONS
{

  /*
   * Section for interrupt table CPU0
   */
  .inttab_cpu1 : ALIGN(8192) FLAGS(ax)
  {
    KEEP (*(.inttab_cpu1));
    KEEP (*(.*.inttab_cpu1));
    . = ALIGN(8);
  } > PMU_PFLASH1
}

/*Near Abbsolute Addressable Data Sections*/
/*Near Absolute Data, selectable with patterns and user defined sections*/
CORE_ID = CPU6;
SECTIONS
{
  CORE_SEC(.zdata) (__DSPR5_START): FLAGS(awzl)
  {
    *(.zdata_cpu6)
    *(.zdata_cpu6.*)
     . = ALIGN(2);
  } > DMI_DSPR5 AT> PMU_PFLASH5

  CORE_SEC(.zbss) (NOLOAD): FLAGS(awz)
  {
    *(.zbss_cpu6)
    *(.zbss_cpu6.*)
  } > DMI_DSPR5
}

CORE_ID = CPU4;
SECTIONS
{
  CORE_SEC(.zdata) (__DSPR4_START): FLAGS(awzl)
  {
    *(.zdata_cpu4)
    *(.zdata_cpu4.*)
    . = ALIGN(2);
  } > DMI_DSPR4 AT> PMU_PFLASH4

  CORE_SEC(.zbss) (NOLOAD): FLAGS(awz)
  {
    *(.zbss_cpu4)
    *(.zbss_cpu4.*)
  } > DMI_DSPR4
}

CORE_ID = CPU3;
SECTIONS
{
  CORE_SEC(.zdata) (__DSPR3_START): FLAGS(awzl)
  {
    *(.zdata_cpu3)
    *(.zdata_cpu3.*)
    . = ALIGN(2);
  } > DMI_DSPR3 AT> PMU_PFLASH3

  CORE_SEC(.zbss) (NOLOAD): FLAGS(awz)
  {
    *(.zbss_cpu3)
    *(.zbss_cpu3.*)
  } > DMI_DSPR3
}

CORE_ID = CPU2;
SECTIONS
{
  CORE_SEC(.zdata) (__DSPR2_START): FLAGS(awzl)
  {
    *(.zdata_cpu2)
    *(.zdata_cpu2.*)
    . = ALIGN(2);
  } > DMI_DSPR2 AT> PMU_PFLASH2

  CORE_SEC(.zbss) (NOLOAD): FLAGS(awz)
  {
    *(.zbss_cpu2)
    *(.zbss_cpu2.*)
  } > DMI_DSPR2
}

CORE_ID = CPU1;
SECTIONS
{
  CORE_SEC(.zdata) (__DSPR1_START): FLAGS(awzl)
  {
    *(.zdata_cpu1)
    *(.zdata_cpu1.*)
    . = ALIGN(2);
  } > DMI_DSPR1 AT> PMU_PFLASH1

  CORE_SEC(.zbss) (NOLOAD): FLAGS(awz)
  {
    *(.zbss_cpu1)
    *(.zbss_cpu1.*)
  } > DMI_DSPR1
}

CORE_ID = CPU0;
SECTIONS
{
  CORE_SEC(.zdata) (__DSPR0_START): FLAGS(awzl)
  {
    *(.zdata_cpu0)
    *(.zdata_cpu0.*)
    . = ALIGN(2);
  } > DMI_DSPR0 AT> PMU_PFLASH0

  CORE_SEC(.zbss) (NOLOAD): FLAGS(awz)
  {
      *(.zbss_cpu0)
      *(.zbss_cpu0.*)
  } > DMI_DSPR0
}

/* Near Absolute Data, selectable by toolchain */
CORE_ID = GLOBAL;
SECTIONS
{
  CORE_SEC(.zdata) : FLAGS(awzl)
  {
    *(.zdata)
    *(.zdata.*)
    *(.gnu.linkonce.z.*)
    . = ALIGN(2);
  } > GLOBAL_RAM AT> GLOBAL_ROM

  CORE_SEC(.zbss) (NOLOAD) : FLAGS(awz)
 {
    *(.zbss)
    *(.zbss.*)
    *(.bbss)
    *(.bbss.*)
    *(.gnu.linkonce.zb.*)
  } > GLOBAL_RAM
}

CORE_ID = GLOBAL;
SECTIONS
{
  CORE_SEC(.lmu_zdata) : ALIGN(8) FLAGS(awzl)
  {
    *(.zdata_lmu)
    *(.zdata_lmu.*)
  } > LMU_SRAM_nc AT> GLOBAL_ROM

  CORE_SEC(.lmu_zbss) (NOLOAD) : ALIGN(4) FLAGS(awz)
  {
    *(.zbss_lmu)
    *(.zbss_lmu.*)
  } > LMU_SRAM_nc

  CORE_SEC(.lmu_sbss) (NOLOAD) : ALIGN(4) FLAGS(aws)
  {
    *(.sbss_lmu)
    *(.sbss_lmu.*)
  } > LMU_SRAM_nc

  CORE_SEC(.lmu_sdata) : ALIGN(4) FLAGS(awsl)
  {
    *(.sdata_lmu)
    *(.sdata_lmu.*)
  } > LMU_SRAM_nc AT> GLOBAL_ROM
}

/*Near Absolute Const, selectable with patterns and user defined sections*/
CORE_ID = GLOBAL;
SECTIONS
{
  .zrodata : FLAGS(arzl)
  {
    *(.zrodata)
    *(.zrodata.*)
  } > GLOBAL_ROM
}

/*Relative A0/A1/A8/A9 Addressable Sections*/
CORE_ID = GLOBAL;
SECTIONS
{
  /*Relative A0 Addressable Data, selectable with patterns and user defined sections*/
  /*Note: A0 addressable area is common, to make the functions callable in any CPU*/
  /*Relative A0 Addressable Data, selectable by toolchain*/
  CORE_SEC(.sdata) : FLAGS(awsl)
  {
    *(.sdata)
    *(.sdata.*)
    . = ALIGN(2);
  } > GLOBAL_RAM AT> GLOBAL_ROM

  CORE_SEC(.sbss) (NOLOAD): FLAGS(aws)
  {
    *(.sbss)
    *(.sbss.*)
  } > GLOBAL_RAM

  _SMALL_DATA_ = SIZEOF(CORE_SEC(.sdata)) ? ADDR(CORE_SEC(.sdata)) : (ADDR(CORE_SEC(.sdata)) & 0xF0000000) + 32k ;
  __A0_MEM = _SMALL_DATA_;
}

CORE_ID = GLOBAL;
SECTIONS
{
  /*Relative A1 Addressable Const, selectable with patterns and user defined sections*/
  /*Note: A1 addressable area is common, to make the functions callable in any CPU*/
  /*Relative A1 Addressable Const, selectable by toolchain*/
  CORE_SEC(.sdata2) : FLAGS(arsl)
  {
    *(.srodata)
    *(.srodata.*)
  } > GLOBAL_ROM
  _SMALL_DATA2_ = SIZEOF(CORE_SEC(.sdata2)) ? ADDR(CORE_SEC(.sdata2)) : (ADDR(CORE_SEC(.sdata2)) & 0xF0000000) + 32k ;
  __A1_MEM = _SMALL_DATA2_;
}

CORE_ID = GLOBAL;
SECTIONS
{
  /*Relative A9 Addressable Data, selectable with patterns and user defined sections*/
  CORE_SEC(.sdata4) :
  {
    *(.a9sdata)
    *(.a9sdata.*)
    . = ALIGN(2);
  } > LMU_SRAM AT> GLOBAL_ROM

  CORE_SEC(.sbss4) :
  {
    *(.a9sbss)
    *(.a9sbss.*)    
  } > LMU_SRAM

  _SMALL_DATA4_ = SIZEOF(CORE_SEC(.sdata4)) ? ADDR(CORE_SEC(.sdata4)) : (ADDR(CORE_SEC(.sdata4)) & 0xF0000000) + 32k ;
  __A9_MEM = _SMALL_DATA4_;

  /*Relative A8 Addressable Const, selectable with patterns and user defined sections*/
  CORE_SEC(.sdata3) : FLAGS(arsl)
  {
    *(.rodata_a8)
    *(.rodata_a8.*)
  } > GLOBAL_ROM

  _SMALL_DATA3_ = SIZEOF(CORE_SEC(.sdata3)) ? ADDR(CORE_SEC(.sdata3)) : (ADDR(CORE_SEC(.sdata3)) & 0xF0000000) + 32k ;
  __A8_MEM = _SMALL_DATA3_;
}

/*Far Data / Far Const Sections, selectable with patterns and user defined sections*/
/*Far Data Sections, selectable with patterns and user defined sections*/
CORE_ID = CPU6 ;
SECTIONS
{
  /*DSRAM5 Sections*/
  CORE_SEC(.data) : FLAGS(awl)
  {
    *(.data_cpu6)
    *(.data_cpu6.*)
    . = ALIGN(2);
  } > DMI_DSPR5 AT> PMU_PFLASH5

  CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
  {
    *(.bss_cpu6)
    *(.bss_cpu6.*)
  } > DMI_DSPR5

  /*DLMU5 Sections*/
  CORE_SEC(.dlmu_data) : FLAGS(awl)
  {
    *(.dlmu_data_cpu6)
    *(.dlmu_data_cpu6.*)
  } > DLMU_SRAM5 AT> PMU_PFLASH5

  CORE_SEC(.dlmu_bss) (NOLOAD) : FLAGS(aw)
  {
    *(.dlmu_bss_cpu6)
    *(.dlmu_bss_cpu6.*)
  } > DLMU_SRAM5
}

CORE_ID = CPU4 ;
SECTIONS
{
  /*DSRAM4 Sections*/
  CORE_SEC(.data) : FLAGS(awl)
  {
    *(.data_cpu4)
    *(.data_cpu4.*)
    . = ALIGN(2);
  } > DMI_DSPR4 AT> PMU_PFLASH4

  CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
  {
    *(.bss_cpu4)
    *(.bss_cpu4.*)
  } > DMI_DSPR4

  /*DLMU4 Sections*/
  CORE_SEC(.dlmu_data) : FLAGS(awl)
  {
    *(.dlmu_data_cpu4)
    *(.dlmu_data_cpu4.*)
  } > DLMU_SRAM4 AT> PMU_PFLASH4

  CORE_SEC(.dlmu_bss) (NOLOAD) : FLAGS(aw)
  {
    *(.dlmu_bss_cpu4)
    *(.dlmu_bss_cpu4.*)
  } > DLMU_SRAM4
}

CORE_ID = CPU3 ;
SECTIONS
{
  /*DSRAM3 Sections*/
  CORE_SEC(.data) : FLAGS(awl)
  {
    *(.data_cpu3)
    *(.data_cpu3.*)
    . = ALIGN(2);
  } > DMI_DSPR3 AT> PMU_PFLASH3

  CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
  {
    *(.bss_cpu3)
    *(.bss_cpu3.*)
  } > DMI_DSPR3

  /*DLMU3 Sections*/
  CORE_SEC(.dlmu_data) : FLAGS(awl)
  {
    *(.dlmu_data_cpu3)
    *(.dlmu_data_cpu3.*)
  } > DLMU_SRAM3 AT> PMU_PFLASH3

  CORE_SEC(.dlmu_bss) (NOLOAD) : FLAGS(aw)
  {
    *(.dlmu_bss_cpu3)
    *(.dlmu_bss_cpu3.*)
  } > DLMU_SRAM3
}

CORE_ID = CPU2 ;
SECTIONS
{
  /*DSRAM2 Sections*/
  CORE_SEC(.data) : FLAGS(awl)
  {
    *(.data_cpu2)
    *(.data_cpu2.*)
    . = ALIGN(2);
  } > DMI_DSPR2 AT> PMU_PFLASH2

  CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
  {
    *(.bss_cpu2)
    *(.bss_cpu2.*)
  } > DMI_DSPR2

  /*DLMU2 Sections*/
  CORE_SEC(.dlmu_data) : FLAGS(awl)
  {
    *(.dlmu_data_cpu2)
    *(.dlmu_data_cpu2.*)
  } > DLMU_SRAM2 AT> PMU_PFLASH2

  CORE_SEC(.dlmu_bss) (NOLOAD) : FLAGS(aw)
  {
    *(.dlmu_bss_cpu2)
    *(.dlmu_bss_cpu2.*)
  } > DLMU_SRAM2
}

CORE_ID = CPU1 ;
SECTIONS
{
  /*DSRAM1 Sections*/
  CORE_SEC(.data) : FLAGS(awl)
  {
    *(.data_cpu1)
    *(.data_cpu1.*)
    . = ALIGN(2);
  } > DMI_DSPR1 AT> PMU_PFLASH1

  CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
  {
    *(.bss_cpu1)
    *(.bss_cpu1.*)
  } > DMI_DSPR1

  /*DLMU1 Sections*/
  CORE_SEC(.dlmu_data) : FLAGS(awl)
  {
    *(.dlmu_data_cpu1)
    *(.dlmu_data_cpu1.*)
  } > DLMU_SRAM1 AT> PMU_PFLASH1

  CORE_SEC(.dlmu_bss) (NOLOAD) : FLAGS(aw)
  {
    *(.dlmu_bss_cpu1)
    *(.dlmu_bss_cpu1.*)
  } > DLMU_SRAM1
}

CORE_ID = CPU0 ;
SECTIONS
{
  /*DSRAM1 Sections*/
  CORE_SEC(.data) : FLAGS(awl)
  {
    *(.data_cpu0)
    *(.data_cpu0.*)
    . = ALIGN(2);
  } > DMI_DSPR0 AT> PMU_PFLASH0

  CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
  {
    *(.bss_cpu0)
    *(.bss_cpu0.*)
  } > DMI_DSPR0

  /*DLMU1 Sections*/
  CORE_SEC(.dlmu_data) : FLAGS(awl)
  {
    *(.dlmu_data_cpu0)
    *(.dlmu_data_cpu0.*)
  } > DLMU_SRAM0 AT> PMU_PFLASH0

  CORE_SEC(.dlmu_bss) (NOLOAD) : FLAGS(aw)
  {
    *(.dlmu_bss_cpu0)
    *(.dlmu_bss_cpu0.*)
  } > DLMU_SRAM0
}

/*Far Data Sections, selectable by toolchain*/
CORE_ID = GLOBAL;
SECTIONS
{
  CORE_SEC(.data) : FLAGS(awl)
  {
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(2);
  } > GLOBAL_RAM AT> GLOBAL_ROM

  CORE_SEC(.bss) (NOLOAD) : FLAGS(aw)
  {
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
  } > GLOBAL_RAM

  .heap (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    PROVIDE(__HEAP = .);
    . += __HEAP_SIZE;
    PROVIDE(__HEAP_END = .);
  } > GLOBAL_RAM

  CORE_SEC(.lmu_data) : FLAGS(awl)
  {
    *(.data_lmu)
    *(.data_lmu.*)
    *(.lmudata)
    *(.lmudata.*)
  } > LMU_SRAM_nc AT> GLOBAL_ROM

  CORE_SEC(.lmu_bss) (NOLOAD) : ALIGN(4) FLAGS(aw)
  {
    *(.bss_lmu)
    *(.bss_lmu.*)
    *(.lmubss)
    *(.lmubss.*)
  } > LMU_SRAM_nc
}

/*Far Const Sections, selectable with patterns and user defined sections*/
CORE_ID = CPU0;
SECTIONS
{
  CORE_SEC(.rodata) : FLAGS(arl)
  {
    *(.rodata_cpu0)
    *(.rodata_cpu0.*)
  } > PMU_PFLASH0
}

CORE_ID = CPU1;
SECTIONS
{
  CORE_SEC(.rodata) : FLAGS(arl)
  {
    *(.rodata_cpu1)
    *(.rodata_cpu1.*)
  } > PMU_PFLASH1
}

CORE_ID = CPU2;
SECTIONS
{
  CORE_SEC(.rodata) : FLAGS(arl)
  {
    *(.rodata_cpu2)
    *(.rodata_cpu2.*)
  } > PMU_PFLASH2
}

CORE_ID = CPU3;
SECTIONS
{
  CORE_SEC(.rodata) : FLAGS(arl)
  {
    *(.rodata_cpu3)
    *(.rodata_cpu3.*)
  } > PMU_PFLASH3
}

CORE_ID = CPU4;
SECTIONS
{
  CORE_SEC(.rodata) : FLAGS(arl)
  {
    *(.rodata_cpu4)
    *(.rodata_cpu4.*)
  } > PMU_PFLASH4
}

CORE_ID = CPU6;
SECTIONS
{
  CORE_SEC(.rodata) : FLAGS(arl)
  {
    *(.rodata_cpu6)
    *(.rodata_cpu6.*)
  } > PMU_PFLASH5
}

/*Far Const Sections, selectable by toolchain*/
CORE_ID = GLOBAL;
SECTIONS
{
  CORE_SEC(.rodata) : FLAGS(arl)
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
    LONG(0 + ADDR(.CPU6.zbss));     LONG(SIZEOF(.CPU6.zbss));
    LONG(0 + ADDR(.CPU6.bss));      LONG(SIZEOF(.CPU6.bss));
    LONG(0 + ADDR(.CPU6.dlmu_bss)); LONG(SIZEOF(.CPU6.dlmu_bss));
    LONG(0 + ADDR(.CPU4.zbss));     LONG(SIZEOF(.CPU4.zbss));
    LONG(0 + ADDR(.CPU4.bss));      LONG(SIZEOF(.CPU4.bss));
    LONG(0 + ADDR(.CPU4.dlmu_bss)); LONG(SIZEOF(.CPU4.dlmu_bss));
    LONG(0 + ADDR(.CPU3.zbss));     LONG(SIZEOF(.CPU3.zbss));
    LONG(0 + ADDR(.CPU3.bss));      LONG(SIZEOF(.CPU3.bss));
    LONG(0 + ADDR(.CPU3.dlmu_bss)); LONG(SIZEOF(.CPU3.dlmu_bss));
    LONG(0 + ADDR(.CPU2.zbss));     LONG(SIZEOF(.CPU2.zbss));
    LONG(0 + ADDR(.CPU2.bss));      LONG(SIZEOF(.CPU2.bss));
    LONG(0 + ADDR(.CPU2.dlmu_bss)); LONG(SIZEOF(.CPU2.dlmu_bss));
    LONG(0 + ADDR(.CPU1.zbss));     LONG(SIZEOF(.CPU1.zbss));
    LONG(0 + ADDR(.CPU1.bss));      LONG(SIZEOF(.CPU1.bss));
    LONG(0 + ADDR(.CPU1.dlmu_bss)); LONG(SIZEOF(.CPU1.dlmu_bss));
    LONG(0 + ADDR(.CPU0.zbss));     LONG(SIZEOF(.CPU0.zbss));
    LONG(0 + ADDR(.CPU0.bss));      LONG(SIZEOF(.CPU0.bss));
    LONG(0 + ADDR(.CPU0.dlmu_bss)); LONG(SIZEOF(.CPU0.dlmu_bss));
    LONG(0 + ADDR(.zbss));          LONG(SIZEOF(.zbss));
    LONG(0 + ADDR(.sbss));          LONG(SIZEOF(.sbss));
    LONG(0 + ADDR(.bss));           LONG(SIZEOF(.bss));
    LONG(0 + ADDR(.lmu_zbss));      LONG(SIZEOF(.lmu_zbss));
    LONG(0 + ADDR(.lmu_sbss));      LONG(SIZEOF(.lmu_sbss));
    LONG(0 + ADDR(.lmu_bss));       LONG(SIZEOF(.lmu_bss));
    LONG(0 + ADDR(.sbss4));         LONG(SIZEOF(.sbss4));
    LONG(-1);                       LONG(-1);
    PROVIDE(__copy_table = .) ;
    LONG(LOADADDR(.CPU6.zdata));      LONG(0 + ADDR(.CPU6.zdata));      LONG(SIZEOF(.CPU6.zdata));
    LONG(LOADADDR(.CPU6.data));       LONG(0 + ADDR(.CPU6.data));       LONG(SIZEOF(.CPU6.data));
    LONG(LOADADDR(.CPU6.dlmu_data));  LONG(0 + ADDR(.CPU6.dlmu_data));  LONG(SIZEOF(.CPU6.dlmu_data));
    LONG(LOADADDR(.CPU4.zdata));      LONG(0 + ADDR(.CPU4.zdata));      LONG(SIZEOF(.CPU4.zdata));
    LONG(LOADADDR(.CPU4.data));       LONG(0 + ADDR(.CPU4.data));       LONG(SIZEOF(.CPU4.data));
    LONG(LOADADDR(.CPU4.dlmu_data));  LONG(0 + ADDR(.CPU4.dlmu_data));  LONG(SIZEOF(.CPU4.dlmu_data));
    LONG(LOADADDR(.CPU3.zdata));      LONG(0 + ADDR(.CPU3.zdata));      LONG(SIZEOF(.CPU3.zdata));
    LONG(LOADADDR(.CPU3.data));       LONG(0 + ADDR(.CPU3.data));       LONG(SIZEOF(.CPU3.data));
    LONG(LOADADDR(.CPU3.dlmu_data));  LONG(0 + ADDR(.CPU3.dlmu_data));  LONG(SIZEOF(.CPU3.dlmu_data));
    LONG(LOADADDR(.CPU2.zdata));      LONG(0 + ADDR(.CPU2.zdata));      LONG(SIZEOF(.CPU2.zdata));
    LONG(LOADADDR(.CPU2.data));       LONG(0 + ADDR(.CPU2.data));       LONG(SIZEOF(.CPU2.data));
    LONG(LOADADDR(.CPU2.dlmu_data));  LONG(0 + ADDR(.CPU2.dlmu_data));  LONG(SIZEOF(.CPU2.dlmu_data));
    LONG(LOADADDR(.CPU1.zdata));      LONG(0 + ADDR(.CPU1.zdata));      LONG(SIZEOF(.CPU1.zdata));
    LONG(LOADADDR(.CPU1.data));       LONG(0 + ADDR(.CPU1.data));       LONG(SIZEOF(.CPU1.data));
    LONG(LOADADDR(.CPU1.dlmu_data));  LONG(0 + ADDR(.CPU1.dlmu_data));  LONG(SIZEOF(.CPU1.dlmu_data));
    LONG(LOADADDR(.CPU0.zdata));      LONG(0 + ADDR(.CPU0.zdata));      LONG(SIZEOF(.CPU0.zdata));
    LONG(LOADADDR(.CPU0.data));       LONG(0 + ADDR(.CPU0.data));       LONG(SIZEOF(.CPU0.data));
    LONG(LOADADDR(.CPU0.dlmu_data));  LONG(0 + ADDR(.CPU0.dlmu_data));  LONG(SIZEOF(.CPU0.dlmu_data));
    LONG(LOADADDR(.zdata));           LONG(0 + ADDR(.zdata));           LONG(SIZEOF(.zdata));
    LONG(LOADADDR(.sdata));           LONG(0 + ADDR(.sdata));           LONG(SIZEOF(.sdata));
    LONG(LOADADDR(.data));            LONG(0 + ADDR(.data));            LONG(SIZEOF(.data));
    LONG(LOADADDR(.lmu_zdata));       LONG(0 + ADDR(.lmu_zdata));       LONG(SIZEOF(.lmu_zdata));
    LONG(LOADADDR(.lmu_sdata));       LONG(0 + ADDR(.lmu_sdata));       LONG(SIZEOF(.lmu_sdata));
    LONG(LOADADDR(.lmu_data));        LONG(0 + ADDR(.lmu_data));        LONG(SIZEOF(.lmu_data));
    LONG(LOADADDR(.sdata4));          LONG(0 + ADDR(.sdata4));          LONG(SIZEOF(.sdata4));
    LONG(LOADADDR(.CPU0.psram_text)); LONG(0 + ADDR(.CPU0.psram_text)); LONG(SIZEOF(.CPU0.psram_text));
    LONG(LOADADDR(.CPU1.psram_text)); LONG(0 + ADDR(.CPU1.psram_text)); LONG(SIZEOF(.CPU1.psram_text));
    LONG(LOADADDR(.CPU2.psram_text)); LONG(0 + ADDR(.CPU2.psram_text)); LONG(SIZEOF(.CPU2.psram_text));
    LONG(LOADADDR(.CPU3.psram_text)); LONG(0 + ADDR(.CPU3.psram_text)); LONG(SIZEOF(.CPU3.psram_text));
    LONG(LOADADDR(.CPU4.psram_text)); LONG(0 + ADDR(.CPU4.psram_text)); LONG(SIZEOF(.CPU4.psram_text));
    LONG(LOADADDR(.CPU6.psram_text)); LONG(0 + ADDR(.CPU6.psram_text)); LONG(SIZEOF(.CPU6.psram_text));
    LONG(-1);                         LONG(-1);                         LONG(-1);
    . = ALIGN(8);
  } > GLOBAL_ROM
}

/*Code selections*/
/*Code Sections, selectable with patterns and user defined sections*/
CORE_ID = CPU0;
SECTIONS
{
  /*
   * Code executed before calling main extra section for C++ constructor init
   *  -------------------------Start-----------------------------------------
   */
  .init : FLAGS(ax)
  {
    PROVIDE(__init_start = .);
    KEEP(*(.init))
    KEEP(*(.init*))
    PROVIDE(__init_end = .);
    . = ALIGN(8);
  } > PMU_PFLASH0

  .fini : FLAGS(ax)
  {
    PROVIDE(__fini_start = .);
    KEEP(*(.fini))
    KEEP(*(.fini*))
    PROVIDE(__fini_end = .);
    . = ALIGN(8);
  } > PMU_PFLASH0

  .traptab : ALIGN(32) FLAGS(ax)
  {
    KEEP(*(.traptab))
    KEEP(*(.traptab*))
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

  CORE_SEC(.text) : FLAGS(axl)
  {
    *(.text_cpu0)
    *(.text_cpu0.*)
  } > PMU_PFLASH0


  /*
   * Code executed before calling main extra section for C++ constructor init
   *  -------------------------End-----------------------------------------
   */
  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    . = ALIGN(2);
    *(.psram_text_cpu0)
    *(.psram_text_cpu0.*)
    *(.cpu0_psram)
    *(.cpu0_psram.*)
    . = ALIGN(2);
  } > PMI_PSPR0 AT> PMU_PFLASH0
}

CORE_ID = CPU1;
SECTIONS
{
  CORE_SEC(.text) : ALIGN(2) FLAGS(axl)
  {
    *(.text_cpu1)
    *(.text_cpu1.*)
  } > PMU_PFLASH1

  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    *(.psram_text_cpu1)
    *(.psram_text_cpu1.*)
    *(.cpu1_psram)
    *(.cpu1_psram.*)
    . = ALIGN(2);
  } > PMI_PSPR1 AT> PMU_PFLASH1
}

CORE_ID = CPU2;
SECTIONS
{
  CORE_SEC(.text) : ALIGN(2) FLAGS(axl)
  {
    *(.text_cpu2)
    *(.text_cpu2.*)
  } > PMU_PFLASH2

  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    *(.psram_text_cpu2)
    *(.psram_text_cpu2.*)
    *(.cpu2_psram)
    *(.cpu2_psram.*)
    . = ALIGN(2);
  } > PMI_PSPR2 AT> PMU_PFLASH2
}

CORE_ID = CPU3;
SECTIONS
{
  CORE_SEC(.text) : ALIGN(2) FLAGS(axl)
  {
    *(.text_cpu3)
    *(.text_cpu3.*)
  } > PMU_PFLASH3

  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    *(.psram_text_cpu3)
    *(.psram_text_cpu3.*)
    *(.cpu3_psram)
    *(.cpu3_psram.*)
    . = ALIGN(2);
  } > PMI_PSPR3 AT> PMU_PFLASH3
}

CORE_ID = CPU4;
SECTIONS
{
  CORE_SEC(.text) : ALIGN(2) FLAGS(axl)
  {
    *(.text_cpu4)
    *(.text_cpu4.*)
  } > PMU_PFLASH4

  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    *(.psram_text_cpu4)
    *(.psram_text_cpu4.*)
    *(.cpu4_psram)
    *(.cpu4_psram.*)
    . = ALIGN(2);
  } > PMI_PSPR4 AT> PMU_PFLASH4
}

CORE_ID = CPU6;
SECTIONS
{
  CORE_SEC(.text) : ALIGN(2) FLAGS(axl)
  {
    *(.text_cpu6)
    *(.text_cpu6.*)
  } > PMU_PFLASH5

  CORE_SEC(.psram_text) : ALIGN(2) FLAGS(awx)
  {
    *(.psram_text_cpu6)
    *(.psram_text_cpu6.*)
    *(.cpu6_psram)
    *(.cpu6_psram.*)
    . = ALIGN(2);
  } > PMI_PSPR5 AT> PMU_PFLASH5
}

/*Code Sections, selectable by toolchain*/
CORE_ID = GLOBAL;
SECTIONS
{
  CORE_SEC(.text) : FLAGS(axl)
 {
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    *(.gnu.warning)        /* .gnu.warning sections are handled specially by elf32.em. */
    . = ALIGN(4);
  } > GLOBAL_ROM

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
    . = ALIGN(8);
  } > GLOBAL_ROM

/*
 * Constructors and destructors.
 */
  .ctors : FLAGS(ax)
  {
    __CTOR_LIST__ = . ;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2);
/*
 * Code executed before calling main extra section for C++ constructor init
 *  -------------------------Start-----------------------------------------
 */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
/*
 * Code executed before calling main extra section for C++ constructor init
 *  -------------------------End-----------------------------------------
 */
    LONG(0) ;
    __CTOR_END__ = . ;
    . = ALIGN(8);
  } > GLOBAL_ROM

  .dtors : FLAGS(ax)
  {
    __DTOR_LIST__ = . ;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2);
    /*
     * Code executed before calling main extra section for C++ distructor init
     *  -------------------------Start-----------------------------------------
     */
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /*
     * Code executed before calling main extra section for C++ distructor init
     *  -------------------------End-----------------------------------------
     */
    LONG(0) ;
    __DTOR_END__ = . ;
    . = ALIGN(8);
  } > GLOBAL_ROM

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
  _. = ASSERT ((__TRICORE_DERIVATE_MEMORY_MAP__ == __TRICORE_DERIVATE_NAME__),
    "Using wrong Memory Map. This Map is for TC39x");

/* Make sure that _START symbol is in the right place. */
  _. = ASSERT (_start == 0xA0000020, "_start is not in the right place");
/* Make sure CSA, stack and heap addresses are properly aligned. */
  _. = ASSERT ((__CSA0 & 0x3f) == 0 , "1llegal CSA0 start address");
  _. = ASSERT ((__CSA0_SIZE & 0x3f) == 0 , "Illegal CSA0 size");
  _. = ASSERT ((__ISTACK0 & 7) == 0 , "ISTACK0 not doubleword aligned");
  _. = ASSERT ((__USTACK0 & 7) == 0 , "USTACK0 not doubleword aligned");
  _. = ASSERT ((__CSA1 & 0x3f) == 0 , "1llegal CSA1 start address");
  _. = ASSERT ((__CSA1_SIZE & 0x3f) == 0 , "Illegal CSA1 size");
  _. = ASSERT ((__ISTACK1 & 7) == 0 , "ISTACK1 not doubleword aligned");
  _. = ASSERT ((__USTACK1 & 7) == 0 , "USTACK1 not doubleword aligned");
  _. = ASSERT ((__CSA2 & 0x3f) == 0 , "1llegal CSA2 start address");
  _. = ASSERT ((__CSA2_SIZE & 0x3f) == 0 , "Illegal CSA2 size");
  _. = ASSERT ((__ISTACK2 & 7) == 0 , "ISTACK2 not doubleword aligned");
  _. = ASSERT ((__USTACK2 & 7) == 0 , "USTACK2 not doubleword aligned");
  _. = ASSERT ((__CSA3 & 0x3f) == 0 , "1llegal CSA3 start address");
  _. = ASSERT ((__CSA3_SIZE & 0x3f) == 0 , "Illegal CSA3 size");
  _. = ASSERT ((__ISTACK3 & 7) == 0 , "ISTACK3 not doubleword aligned");
  _. = ASSERT ((__USTACK3 & 7) == 0 , "USTACK3 not doubleword aligned");
  _. = ASSERT ((__CSA4 & 0x3f) == 0 , "1llegal CSA4 start address");
  _. = ASSERT ((__CSA4_SIZE & 0x3f) == 0 , "Illegal CSA4 size");
  _. = ASSERT ((__ISTACK4 & 7) == 0 , "ISTACK4 not doubleword aligned");
  _. = ASSERT ((__USTACK4 & 7) == 0 , "USTACK4 not doubleword aligned");
  _. = ASSERT ((__CSA6 & 0x3f) == 0 , "1llegal CSA6 start address");
  _. = ASSERT ((__CSA6_SIZE & 0x3f) == 0 , "Illegal CSA6 size");
  _. = ASSERT ((__ISTACK6 & 7) == 0 , "ISTACK6 not doubleword aligned");
  _. = ASSERT ((__USTACK6 & 7) == 0 , "USTACK6 not doubleword aligned");
  _. = ASSERT ((__HEAP_END & 7) == 0 , "HEAP not doubleword aligned");

