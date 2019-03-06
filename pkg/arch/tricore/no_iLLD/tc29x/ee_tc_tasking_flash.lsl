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
 * This file derives from a modification of the TASKING linker scripts,
 * distributed under the following license:
 *
 * TASKING VX-toolset for TriCore
 * Eclipse project linker script file
 *
 */

/** \file   ee_tc_tasking_flash.lsl
 *  \brief  Linker script file for TASKING compiler (no iLLD integration)
 *  \author Errico Guidieri
 *  \date   2019
 */
#if (!defined(USTACK_TC0))
#define USTACK_TC0 4k
#endif /* !USTACK_TC0 */
#if defined(__PROC_TC29X__)
#include "tc29x.lsl"

section_layout mpe:vtc:abs18
{
  group abs18_not_cached ( run_addr=mem:mpe:lmuram/not_cached ) {
    select ".zbss.ee_gbl_kernel_bss";
    select ".zdata.ee_gbl_kernel_data";
    select ".zdata.ee_kernel_data";
  }

  group api_abs18_not_cached ( run_addr=mem:mpe:lmuram/not_cached ) {
    select ".zbss.ee_api_bss";
    select ".zdata.ee_api_data";
  }
}

section_layout mpe:vtc:linear
{
  group linear_not_cached ( run_addr=mem:mpe:lmuram/not_cached ) {
    select ".bss.ee_gbl_kernel_bss";
    select ".data.ee_gbl_kernel_data";
    select ".data.ee_kernel_data";
  }

  group api_linear_not_cached ( run_addr=mem:mpe:lmuram/not_cached ) {
    select ".bss.ee_api_bss";
    select ".data.ee_api_data";
  }
}
#else
#include <cpu.lsl>
#endif
