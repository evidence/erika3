/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_aarch64.lds
 *  \brief  Jailhouse ERIKA's Cell Linker Script
 *
 *  \author  Errico Guidieri
 *  \date    2017
 */
SECTIONS {
  . = 0;
  .osee_boot  : { *(.osee_boot) }

  . = 0x1000;
  .cmdline  : {
    *(.cmdline)
    BYTE(0); /* empty string in case no buffer is provided */
  }

  bss_start = .;
  .bss    : {
    *(.bss)
  }

  . = ALIGN(4);
  .text   : {
    *(.text)
  }

  .rodata   : {
    *(.rodata)
  }

  .data   : {
    *(.data)
  }

  . = ALIGN(16);
  stack_bottom = .;
  . = ALIGN(4096);
  . = . + 0x1000;
  stack_top = .;
}

ENTRY(__osEE_reset_entry)
