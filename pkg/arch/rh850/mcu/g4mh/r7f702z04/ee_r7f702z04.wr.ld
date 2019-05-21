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

/** \file   ee_r7f702z04.wr.ld
 *  \brief  Linker script file for WR Diab compiler (no iLLD integration)
 *  \author Errico Guidieri
 *  \date   2018
 */
 
-Xgenerate-copytables
/*******************************************************************************
                Memory layout for RH850/E2x - R7F702Z04
*******************************************************************************/
MEMORY
{
    R_FLASH       : ORIGIN = 0x00000000,  LENGTH = 8M
    R_BOOT        : ORIGIN = 0x08000000,  LENGTH = 64k
    /* Self RAM is limited to 4k, the other 28k are used with explicit address */
    R_LRAM_CPU1   : ORIGIN = 0xFDA01000,  LENGTH = 28k
    R_LRAM_CPU0   : ORIGIN = 0xFDC01000,  LENGTH = 28k
    R_LRAM        : ORIGIN = 0xFDE00000,  LENGTH = 4k
    R_GRAM        : ORIGIN = 0xFE000000,  LENGTH = 704k  /* Global RAM */
}

/*******************************************************************************
                                Sections
*******************************************************************************/
SECTIONS
{
  GROUP : {
    /* Direct Vector and Reference Table */
    .g4mh_int (TEXT) : {}

    /* Code */
    .text (TEXT)  align(4) : {}

    /* Required by Diab when use -l:libc.a */
    .init (TEXT)  align(4) : {}

    /* Required by Diab when use -l:libc.a */
    .fini (TEXT)  align(4) : {}

    /* Required by Diab when use -l:libc.a */
    .ctors (TEXT) align(4) : {}

    /* Required by Diab when use -l:libc.a */
    .dtors (TEXT) align(4) : {}

    /* Large const data, align on an 8 byte boundary */
    .rodata (CONST) align(8) : {}

    /* small const data, align on an 8 byte boundary */
    .sdata2 (CONST) align(8) : {}

    /* __DATA_ROM is the location in flash used to store initialization
    /* values for global data. The linker puts a copy of the data at this
    /* "pointer". */
    /* Align to 8 byte boundary to allow init in crt0.o using double word
       widths */
    .copytable (CONST) align(8) : {
      __DATA_ROM = .;
    }
  } > R_FLASH

  GROUP : {
    /* align to 8 byte boundary to allow double word init in crt0 */
    . = align(8);
    __DATA_RAM = .;

    /* Initialized large data */
    .data (DATA)  load(>R_FLASH) COPYTABLE : {}

    /* Initialized small data */
    . = align(16);
    __SDA_BASE = .;

    .sdata (DATA)  load(>R_FLASH) COPYTABLE : {}
    __DATA_END = .;

    /* Both init to 0 and uninitialized data may be included in
       .bss and .sbss */
    /* align to 8 byte boundary to allow double word init in crt0 */
    . = align(8);
    __BSS_START = .;

    /* Want to put .sbss close to .sdata so that the single SDA register can be
       used for both */
    /* Uninitialized small data */
    .sbss (BSS) align(4) : {}

    /* Uninitialized large data */
    .bss  (BSS) align(4) : {}

    __BSS_END = .;
  } > R_GRAM

  GROUP : {
    /* Stack */
    . = align(16);
    __SP_END = .;
    . += 0x800;
    __SP_INIT = .;

    /* G4MH variables in LRAM (PE specific) */
    .g4mh_sdata (DATA) LOAD(>R_FLASH) COPYTABLE : {}
  } > R_LRAM

  GROUP : {
    /* Core0 TASKs private stacks */
    .CPU0.ee_kernel_stack (BSS) align(16) : {}

    /* Initialized Core0 Kernel Data */
    .CPU0.ee_kernel_data (DATA) LOAD(>R_FLASH) COPYTABLE align(4) : {
      *(.CPU0.ee_kernel_data)
      *(.CPU0.ee_kernel_sdata)
    }

    .CPU0.ee_kernel_data (BSS) align(4) : {
      *(.CPU0.ee_kernel_bss)
      *(.CPU0.ee_kernel_sbss)
    }
  } > R_LRAM_CPU0

  GROUP : {
    /* Core1 TASKs private stacks */
    .CPU1.ee_kernel_stack (BSS) align(16) : {}

    /* Initialized Core1 Kernel Data.
       (I use a named copytable, since core local data have to (re-)initialized
       in each Core)
       Wind River Diab Compiler Linker User's Guide, 5.9.6
       Par. COPYTABLE Specification[Named Copy Tables] pag 34 */
    .CPU1.ee_kernel_data (DATA) LOAD(>R_FLASH) COPYTABLE[WR_CPU1_CT] align(4) :
    {
      *(.CPU1.ee_kernel_data)
      *(.CPU1.ee_kernel_sdata)
    }

    .CPU1.ee_kernel_data (BSS) COPYTABLE[WR_CPU1_CT] align(4) : {
      *(.CPU1.ee_kernel_bss)
      *(.CPU1.ee_kernel_sbss)
    }
  } > R_LRAM_CPU1

}

/******************************************************************************
                              Global Symbols
******************************************************************************/

/* used by crt0.o */
___SP_INIT = __SP_INIT - 8;

/* used by r_boot.wr.asm */
_SP_INIT_ = ___SP_INIT;    

/* used by init.o; init.s uses 2 '_', but .o has 3 '_' */
___DATA_RAM =   __DATA_RAM;
___DATA_ROM =   __DATA_ROM;
___DATA_END =   __DATA_END;
___BSS_START =  __BSS_START;
___BSS_END =    __BSS_END;

/* _SDA_BASE_ is initialized by the linker to be the start of .sdata + half of max offset. */
/* Max offset is 16 bits with -tRH850EH and 23 bits with -tRH850GH */

/* _SDA2_BASE_ is initialized by the linker to be the start of .sdata2 + half of max offset. */
/* Max offset is 16 bits with -tRH850EH and 23 bits with -tRH850GH */
