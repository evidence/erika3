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

/** \file  ee_k1_cluster_boot.c
 *  \brief  TO BE DOCUMENTED!!!.
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author  Errico Giudieri
 *  \date  2016
 */

#include "ee_cfg.h"
#include "ee_internal.h"

#include <string.h>

/* newlib required functions and symbols */
__thread struct _reent _impure_thread_data __attribute__((weak));

extern void _init(void) __attribute__((weak));

extern void __attribute__ ((noreturn, weak)) exit(int reval);

extern int main(int argc, char *argv[], char **envp);

/* Assembly Wrappers for Interrupts an Scalls */
/* extern void ee_k1_interrupt_wrapper ( void ); Not Used */
extern void osEE_k1_scall_wrapper ( void );

/* Big stack's for pe's (kind of thread stack) */
extern __k1_uint8_t _bss_start;
extern __k1_uint8_t _bss_end;
extern __k1_uint8_t _sbss_start;
extern __k1_uint8_t _sbss_end;

extern __k1_uint8_t _tbss_start;
extern __k1_uint32_t _tbss_size;

extern __k1_uint8_t _tdata_start;
extern __k1_uint32_t _tdata_size;

/* extern __k1_uint32_t _tls_size; */

/* System Call User Space Handler */
/* int
osEE_os_scall (int r0, int r1, int r2, int r3, int r4, int r5, int r6, int r7);
*/

#if (defined(OSEE_HAS_COMM_HOOK))
OsEE_spin_lock comm_lock;
#endif

char **environ __attribute__((weak));

static void _tls_init(void) {

  if ( _init ) {
    /* K1 EABI states that $r13 hold the thread local storage base */
    register unsigned long tls_base __asm__("r13");
    __k1_uint8_t *tls_data = (__k1_uint8_t *) tls_base;
    __k1_uint8_t *tls_bss = tls_data + (&_tbss_start - &_tdata_start);
    __k1_copy_section(tls_data, &_tdata_start, (__k1_uint32_t)&_tdata_size);

    __k1_bss_section(tls_bss,(__k1_uint32_t)&_tbss_size);

    _REENT_INIT_PTR(&_impure_thread_data);
    /* Finish initialization of reent */
    _REENT->_stdin  = &(_REENT->__sf[0]);
    _REENT->_stdout = &(_REENT->__sf[1]);
    _REENT->_stderr = &(_REENT->__sf[2]);
  }
}

#if (defined(ERIKA_HAS_SYSTEM_TIMER))
#define CLOCK_FREQ         (__bsp_frequency/(_K1_DEFAULT_CLOCK_DIV + 1))

#if defined(SYSTEM_TICK_MS)
#define CLOCK_RELOAD       EE_MILLI_TO_TICKS(SYSTEM_TICK_MS, CLOCK_FREQ)
#elif defined(SYSTEM_TICK_US)
#define CLOCK_RELOAD       EE_MICRO_TO_TICKS(SYSTEM_TICK_MS, CLOCK_FREQ)
#else
#define CLOCK_RELOAD_1_MS  EE_MILLI_TO_TICKS(1, CLOCK_FREQ)
#define CLOCK_RELOAD       CLOCK_RELOAD_1_MS
#endif /* SYSTEM_TICK_MS || SYSTEM_TICK_US || default */
#endif /* ERIKA_HAS_SYSTEM_TIMER */

void _pe_init ( void ) {
  int pid = __k1_get_cpu_id();

  __k1_uint8_t *tls_base = __k1_tls_pe_base_address(pid);
  __k1_setup_tls_pe(tls_base);

  _tls_init();

  /* I don't want to change stack for Interrupts, but it's OK for exception
   * and default handlers are good. */
  /* _scoreboard_start.SCB_VCORE.PER_CPU[pid].SFR_PS.isw = 0; */
  _scoreboard_start.SCB_VCORE.PER_CPU[pid].SFR_PS.esw = 1;

  /* _scoreboard_start.SCB_VCORE.PER_CPU[pid].SFR_IT = ee_k1_interrupt_wrapper;
   */
  _scoreboard_start.SCB_VCORE.PER_CPU[pid].SFR_SC = osEE_k1_scall_wrapper;

  /* Alternative version with mOS services */
  /* mOS_register_it_handler(&ee_k1_interrupt_wrapper); */
  /* mOS_register_scall_handler(&ee_k1_scall_wrapper); */

  __builtin_k1_wpurge();
  __builtin_k1_fence();

}

/* Communication Hook Handler Body */
#if (defined(EE_HAS_COMM_HOOK))

void communication_hook_handler_body ( void ) {
  /* Put this in some kind of cycle */
  while ( 1 ) {
    EE_k1_spin_lock(&comm_lock);
    CommunicationHook();
    EE_k1_spin_unlock(&comm_lock);

    EE_k1_optimized_task_preemption_point();
  }
}
#endif /* EE_HAS_COMM_HOOK */

void __attribute__((section(TARGET_TEXT)))
  _do_master_pe(uint32_t old_sp __attribute__((unused)))
{
  int ret_val;
  k1_boot_args_t args;

  /* newlib initialization */
  __k1_bss_section(((__k1_uint8_t*) &_bss_start),
      ((__k1_uint32_t)&_bss_end) - ((__k1_uint32_t) &_bss_start));
  __k1_bss_section(((__k1_uint8_t*) &_sbss_start),
      ((__k1_uint32_t)&_sbss_end) - ((__k1_uint32_t) &_sbss_start));

  _pe_init();

  if ( _init ) {
    _init ();
  }

  get_k1_boot_args(&args);

  if ( _init ) {
    environ = args.envp;
  }

#if (defined(OSEE_API_DYNAMIC))
  /* Configure data structures for Kernel */
  osEE_os_init();
#endif /* OSEE_API_DYNAMIC */

  /* Interrupts enabling it's done inside StartOS */
  mOS_it_disable();
  mOS_set_it_level(0);

#if (defined(OSEE_HAS_COMM_HOOK))
  osEE_hal_spin_init_lock(&comm_lock);
#endif

#if (!defined(OSEE_SINGLECORE))
  /* Catch this context as Idle TASK */
  StartOS(OSDEFAULTAPPMODE);

  /* Write Barrier */
  __builtin_k1_wpurge();
  __builtin_k1_fence();

  mOS_it_disable();

  /* Synchronize with the startup of the other cores */
  for (unsigned int i = 1U; i < OSEE_K1_CORE_NUMBER; ++i ) {
    while (
      __k1_umem_read32(&KCB_WJ.core_ctrls[i].ccb.os_status) !=
         OSEE_KERNEL_STARTED )
    {
      ; /* Wait for the start of i */
    }
  }
  mOS_it_enable();

#if (defined(OSEE_CONF_LIBGOMP))
#if (defined(OSEE_HAS_COMM_HOOK))
  {
    OsEE_CDB * const p_cdb        = osEE_get_curr_core();
    OsEE_TDB * const p_idle_task  = p_cdb->p_idle_task;

    p_idle_task->task_func = communication_hook_handler_body;

    osEE_hal_start_idle_task ( &p_idle_task->hdb,
      communication_hook_handler_body );
  }
#endif /* OSEE_HAS_COMM_HOOK */
  ret_val = 0;
#else
  ret_val = main(args.argc, args.argv, args.envp);
#endif  /* OSEE_CONF_LIBGOMP */
#else
  ret_val = main(args.argc, args.argv, args.envp);
#endif /* !OSEE_SINGLECORE */
  if ( exit ) {
    exit ( ret_val );
  }
}

void __attribute__((section(TARGET_TEXT)))
  _do_slave_pe ( uint32_t old_sp __attribute__((unused)) )
{
  _pe_init();

#if (!defined(OSEE_SINGLECORE))
  mOS_set_it_level(0);
  while (
    __k1_umem_read32(&KCB_WJ.core_ctrls[OSEE_K1_MAIN_CORE].ccb.os_status) !=
      OSEE_KERNEL_STARTED )
  {
    ; /* cycle until master pe has done what he needs */
  }

  /* Catch this context as Idle TASK */
  StartOS(OSDEFAULTAPPMODE);

  do {
#if (defined(OSEE_HAS_COMM_HOOK))
    if ( isPendingOffload() ) {
      if ( osEE_hal_spin_trylock(&comm_lock) ) {
        CommunicationHook();
        osEE_hal_spin_unlock(&comm_lock);
      }
    }
#endif
#if (!defined(OSEE_K1_FULL_PREEMPTION))
    /* Disable User Interrupt Line before go to sleep and handle that after
     * wake-up */
    mOS_it_disable_num(MOS_VC_IT_USER_0);

#if (defined(ERIKA_HAS_SYSTEM_TIMER))
    mOS_it_disable_num(MOS_VC_IT_TIMER_0);
#endif /* ERIKA_HAS_SYSTEM_TIMER */

    /* Sleep until the event will wake me up */
    mOS_idle1();

    /* Enter in a critical section */
    /* mOS_it_disable(); */

    /* Invalidate the cache and prepare to read data structures*/
    /* mOS_dinval(); */

    /* Restore "User" interrupt line */
    /* mOS_it_clear_num(MOS_VC_IT_USER_0); */
    /* mOS_it_enable_num(MOS_VC_IT_USER_0); */
    mOS_pe_event_clear(BSP_EV_LINE);
    mOS_pe_event_clear(BSP_IT_LINE);
    mOS_it_clear_num(10); /*  EE_ISR_ID_RM_IIRQ2 */
#if (defined(ERIKA_HAS_SYSTEM_TIMER))
    mOS_it_enable_num(MOS_VC_IT_TIMER_0);
#endif /* ERIKA_HAS_SYSTEM_TIMER */

    osEE_k1_optimized_task_preemption_point();

#else
    /* Sleep until the event will wake me up */
    mOS_idle1();
    /* Restore "User" interrupt line */
    mOS_pe_event_clear(BSP_EV_LINE);
    mOS_pe_event_clear(BSP_IT_LINE);
    mOS_it_clear_num(10); /*  EE_ISR_ID_RM_IIRQ2 */
#endif /* !EE_K1_FULL_PREEMPTION */
  } while ( 1 );
#endif /* !EE_SINGLECORE */
}

extern void _fini(void) __attribute__((weak));

extern int __mppa_power_base_exit_return_status __attribute__ ((weak));

#define LOCKED_BUF_SIZE 32
char locked_buf[BSP_NB_PE_MAX][LOCKED_BUF_SIZE] __attribute__ ((section(".locked_data")));

extern unsigned long INTERNAL_RAM_SIZE;

int osEE_os_scall(int r0, int r1, int r2, int r3 __attribute__((unused)),
    int r4 __attribute__((unused)), int r5 __attribute__((unused)),
    int r6 __attribute__((unused)), int r7)
{
  int ret = -1;
  mOS_enable_hw_loop();
  int pid = __k1_get_cpu_id();

  switch ((int) r7) {
    case __NR_exit:
      if ( _fini ) {
        if ( &__mppa_power_base_exit_return_status ) {
          __mppa_power_base_exit_return_status = r0;
        }

        _fini();
      }

      mOS_exit((__k1_spawn_type() != __MPPA_MPPA_SPAWN), r0);

      break;
    case __NR_write:
    {
      int i;
      char *ptr = (char *) r1;
      ret = r2;

      while ( r2 ) {
        for ( i = 0; i < LOCKED_BUF_SIZE && i < r2; ++i ) {
          locked_buf[pid][i] = ptr[i];
        }
        /* EG: ??? It should correspond to __printf_jtag(ptr, r2); of
         * mOS/std_runtime/utask */
        __k1_club_syscall2(4094, (unsigned int) locked_buf[pid], LOCKED_BUF_SIZE > r2 ? r2 : LOCKED_BUF_SIZE);
        r2 = r2 > LOCKED_BUF_SIZE ? r2 - LOCKED_BUF_SIZE : 0;
        ptr += LOCKED_BUF_SIZE;
      }
    }
    break;
    case __NR_cache_flush:
      __builtin_k1_wpurge();
      __builtin_k1_fence();
      mOS_dinval();
      ret = 0;
      break;
    case __NR_probe_address_space:
    {
      /* This would be so much easier if we had a proper BSP */
      uint64_t addr = ((uint64_t) (uint32_t) r0) | (((uint64_t) (uint32_t) r1) << 32);
      ret = 0;

      if ( &VIRT_U_MEM_PAG == 0 ) {
        if (addr >= (uint64_t) (uint32_t) &VIRT_U_MEM_START && addr < (uint64_t) (uint32_t) &VIRT_U_MEM_END) {
          ret = 1;
        }
      } else {
        if (addr >= (uint64_t) (uint32_t) &VIRT_U_MEM_START && addr < (uint64_t) (uint32_t) &INTERNAL_RAM_SIZE) {
          ret = 1;
        }
      }

      if ( addr >= (uint64_t) (uint32_t) CLUSTER_PERIPH_START && addr < (uint64_t) (uint32_t) CLUSTER_PERIPH_END ) {
        ret = 1;
      }
#ifdef __k1io__
      if ( addr >= (uint64_t) (uint32_t) &DDR_START && addr < ((uint64_t) (uint32_t) &DDR_START) + ((uint64_t) (uint32_t) &DDR_SIZE)) {
        ret = 1;
      }

      if ( addr >= (uint64_t) (uint32_t) IO_PERIPH_START && addr < (uint64_t) (uint32_t) IO_PERIPH_END ) {
        ret = 1;
      }
#endif
      if ( &VIRT_U_MEM_PAG != 0 ) {
        if(addr >= (uint64_t) (uint32_t) &VIRT_U_MEM_PAG && addr < (uint64_t) (uint32_t) &VIRT_U_MEM_END){
          ret = 1;
        }
      }
      break;
    }
    default:
      ret = 0;
      break;
  }

  return ret;
}

