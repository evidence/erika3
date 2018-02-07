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

/** \file   ee_aarch64_boot.c
 *  \brief  Guest Start-UP (C part)
 *
 *  \author  Errico Guidieri
 *  \date    2017
 */
#include "ee_internal.h"

extern int main(void);

extern OsEE_stack stack_bottom[];
#if (defined(OSEE_GIC_HAS_MAX_NUM_PRIO_DISCOVERY))
OsEE_isr_prio osEE_gic_max_num_prio;
#endif /* OSEE_GIC_HAS_MAX_NUM_PRIO_DISCOVERY */

#define INVALID_CORE_ID ((OsEE_core_id)-1)
OsEE_core_id osEE_aarch64_vcore_id_offset = INVALID_CORE_ID;

void osEE_c_start(void)
{
  if (osEE_aarch64_vcore_id_offset == INVALID_CORE_ID) {
    /* XXX: This code suppose that in case of multicore guest, the hypervisor
            will enable the core with the lowest mpidr_el{1,3} (lowest cpu id),
            as "master"/start-up core. To Be Checked */
    osEE_aarch64_vcore_id_offset = osEE_aarch64_get_vcore_id_raw();
  }
  /* Enable Alignment Checks */
  {
    OsEE_reg const sctlr = osEE_aarch64_SCTLR() | OSEE_AARCH64_SCTLR_SA |
                            OSEE_AARCH64_SCTLR_A;
    osEE_aarch64_set_SCTLR(sctlr);
  }
#if (defined(OSEE_GIC_HAS_MAX_NUM_PRIO_DISCOVERY))
  {
    OsEE_isr_prio pmr;
    /* Determine number of priorities */
    osEE_mmio_write32(OSEE_GICC_BASE + OSEE_GICC_PMR, 0xFF);
    pmr = osEE_mmio_read32(OSEE_GICC_BASE + OSEE_GICC_PMR);
    osEE_gic_max_num_prio = (OsEE_isr_prio)(256U/(256U - pmr));
  }
#endif /* OSEE_GIC_HAS_MAX_NUM_PRIO_DISCOVERY */
  /* Initialize GICC */
  osEE_gicd_init(); /* TODO: Only on Master Core */
  osEE_gicc_init();

#if (defined(OSEE_API_DYNAMIC))
  /* OS data structures initialiazation */
  osEE_os_init();
  osEE_get_curr_core()->p_idle_task->hdb.p_sdb->p_bos = (OsEE_addr)stack_bottom;
#endif /* OSEE_API_DYNAMIC */
  /* Application main */
  (void)main();

  while ( 1 ) {
    __asm__ volatile("wfi" : : : "memory");
  }
}
