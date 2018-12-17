/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
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

/** \file   ee_tc_ctx.c
 *  \brief  TriCore change context porting
 *
 *  This files contains the TriCore implemetation of a set of standard internals
 *  functions used to perform context switch.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */


#include "ee_internal.h"

/*******************************************************************************
                           Standard Context Change
 ******************************************************************************/

#if (defined(__GNUC__))
/* The following prevent that the compiler mess up with the stack.
   This imply -fomit-frame-pointer too. */
#pragma GCC optimize ("-O3")
/* The following prevent unwanted inline */
#pragma GCC optimize ("-fno-inline-small-functions")
#endif /* __GNUC__ */

/* This function allocate a ERIKA's context on the stack. It's a real ALLOCA
   function (automatically freed memory), since it will be the CSA restoring
   to do that. */
OSEE_STATIC_INLINE OsEE_CTX * OSEE_ALWAYS_INLINE osEE_tc_alloca_ctx(void) {
  OsEE_CTX * sp = (OsEE_CTX *)osEE_get_SP();
/* Stack grows downward, so the following is the actual stack allocation */
  sp -= 1U;
  osEE_set_SP((OsEE_stack *)sp);
  return sp;
}

OSEE_STATIC_INLINE void OSEE_ALWAYS_INLINE osEE_tc_save_ctx
(
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_scb
)
{
  OsEE_CTX * p_new_ctx;
/* Alloc on the stack the new ERIKA's context */
  p_new_ctx         = osEE_tc_alloca_ctx();
/* Save the previous context */
  p_new_ctx->p_ctx  = p_scb->p_tos;
/* Save the PCXI */
  p_new_ctx->pcxi   = osEE_tc_csa_get_pcxi();
/* Save the RA */
  p_new_ctx->ra     = osEE_tc_get_RA();
/* Save the new Top Of Stack */
  p_scb->p_tos = p_new_ctx;
}

FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
{
/* Save the current Context */
  osEE_tc_save_ctx(p_from_scb);
/* Jump to the restore CTX */
  osEE_tc_jump(osEE_hal_restore_ctx);
/* Touch implicitly used parameters to turn off warnings */
  (void)p_to_tdb;
  (void)p_to_scb;
}

FUNC(void, OS_CODE)
  osEE_hal_restore_ctx
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
{
  OsEE_CTX  const * const p_ctx = p_to_scb->p_tos;
  OsEE_pcxi const         pcxi  = p_ctx->pcxi;
/* Set the return address back */
  osEE_tc_set_RA(p_ctx->ra);
/* Set the PCXI back */
  osEE_tc_csa_set_pcxi(pcxi);
/* Restore the previous Top of Stack */
  p_to_scb->p_tos = p_ctx->p_ctx;
/* Not needed to pop ERIKA's context. It will be the "ret" instruction,
   with CSA restoring, to fix it. */
/* If stack monitoring is turned on I have at least to set back the SP to
   context saved value, to allow the overflow test to pass. */
#if (defined(OSEE_HAS_STACK_MONITORING))
  osEE_set_SP(osEE_tc_csa_link_to_pointer(pcxi)->ctx.uctx.a10);
#endif /* OSEE_HAS_STACK_MONITORING */
/* Jump to Kernel Wrapper: it will be the "ret" inside
   osEE_scheduler_task_wrapper_restore at:
   1) Restore the CSA so the SP,
   2) Return at RA address, that is the address after change context calling
      site */
  osEE_tc_jump(osEE_scheduler_task_wrapper_restore);
/* Touch implicitly used parameter to turn off warnings */
  (void)p_to_tdb;
}

FUNC(void, OS_CODE)
  osEE_hal_save_ctx_and_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_from_scb
)
{
/* Save the current Context */
  osEE_tc_save_ctx(p_from_scb);
/* Jump to the ready to stacked */
  osEE_tc_jump(osEE_hal_ready2stacked);
/* Touch implicitly used parameters to turn off warnings */
  (void)p_to_tdb;
  (void)p_to_scb;
}

FUNC(void, OS_CODE)
  osEE_hal_ready2stacked
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to_tdb,
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_to_scb
)
{
/* Change the SP */
  osEE_set_SP((OsEE_stack *)p_to_scb->p_tos);
/* Prepare the PCXI to implement the CSA unwinding */
  osEE_tc_svlcx();
/* Since a global CSA list is used, even at TASK start-up I need to save
   an ERIKA's context (you can imagine that as all TASKs share the CSA so
   there's never a clean TASK start, since the CSA have to be always restored).

   N.B. The RA saved in this context is not useful, but I prefer to use one
        save ctx code for all the cases for code readability, instead using an
        optimized one for this case */
  osEE_tc_save_ctx(p_to_scb);
/* Jump to Kernel Wrapper */
  osEE_tc_jump(osEE_scheduler_task_wrapper_run);
/* Touch implicitly used parameter to turn off warnings */
  (void)p_to_tdb;
}

/* WARNING: Because of the TriCore Context nature I cannot call the
            kernel_cb as I would have done in any other porting, but I have to
            re-implement "osEE_scheduler_task_end" behavior and
            "osEE_change_context_from_task_end" */
static FUNC(void, OS_CODE) OSEE_NEVER_INLINE
  osEE_tc_change_context_from_task_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
);

extern FUNC(void, OS_CODE) OSEE_NEVER_INLINE
  osEE_tc_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
);

FUNC(void, OS_CODE_NO_RETURN)
  osEE_hal_terminate_ctx
(
  P2VAR(OsEE_SCB, AUTOMATIC, OS_APPL_DATA)  p_term_scb,
  VAR(OsEE_kernel_cb, AUTOMATIC)            kernel_cb
)
{
/* XXX: In this function Hightech GCC 4.9.2.0 compiler allocate 8 bytes on the
        stack for "nothing", this seems deadly, but indeed it's not a big
        deal: it will be CSA restoring ("ret" instruction after
        osEE_hal_restore_ctx) to fix this. */
/* Touch unused parameter */
  (void)kernel_cb;
/* Unwind CSA list */
  {
/* Obtain Free CSA list head */
    OsEE_csa_link fcx                 = osEE_tc_csa_get_fcx();
/* Obtain Previous CSA list head, That is the head of the to_free_queue
   (will be new FCX) */
    OsEE_csa_link to_free_queue_head  = osEE_tc_csa_get_pcxi();
/* Get the the of the CSA list to be freed */
    OsEE_csa_link to_free_queue_tail  = p_term_scb->p_tos->pcxi;
/* Get change context PCXI, "osEE_hal_ready2stacked" PCXI */
    OsEE_csa_link new_pcxi = osEE_tc_csa_get_next(to_free_queue_tail);
/* Append the previous FCX to the to_free_queue */
    osEE_tc_csa_set_next(to_free_queue_tail, fcx);
/* Set the new Free CSA head */
    osEE_tc_csa_set_fcx(to_free_queue_head);
/* Set the PCXI of this funtion to the "osEE_hal_ready2stacked" PCXI. */
    osEE_tc_csa_set_pcxi(new_pcxi);
#if 0
/* Not needed to restore "osEE_hal_ready2stacked" RA since it will be next
   context restoring to set the right RA.
   N.B. Next context restoring could not happens immediatly,
   since a TASK, not yet started with higher priority of the stacked ones,
   could have been activated. */
   osEE_tc_set_RA(p_term_scb->p_tos->ra);
#endif /* 0 */
/* Pop ERIKA's context */
   p_term_scb->p_tos = p_term_scb->p_tos->p_ctx;
  }
/* Try to prevent any instruction scheduling between these two steps of the
   function */
  OSEE_BARRIER();
/* Implement "osEE_scheduler_task_end" behaviour with
   "osEE_hal_ready2stacked" PCXI. */
  {
    P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_to;
    P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_DATA)  p_from;

    p_to = osEE_scheduler_task_terminated(osEE_get_kernel(), &p_from);

    if (p_from->task_type == OSEE_TASK_TYPE_ISR2) {
/* Call osEE_tc_change_context_from_isr2_end to give it a CSA to return from */
      osEE_tc_change_context_from_isr2_end(p_to);
    } else {
/* Prepare to jump to osEE_tc_change_context_from_task_end */
      osEE_tc_setareg(a4, p_to);
      osEE_tc_jump(osEE_tc_change_context_from_task_end);
    }
  }
/* Fake infinite loop: to turn off 'noreturn' function does return warning */
  for(;;) {
    ;
  }
}

FUNC(void, OS_CODE) OSEE_NEVER_INLINE
  osEE_tc_change_context_from_isr2_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
/* Reset PSW Call Depth Counter, so I can force a RFE */
  osEE_tc_set_csfr(OSEE_CSFR_PSW,
    osEE_tc_get_csfr(OSEE_CSFR_PSW) & OSEE_TC_PSW_CDC_CLEAN_MASK
  );
  osEE_tc_set_RA(osEE_tc_change_context_from_task_end);
  osEE_tc_rfe();
/* Touch implicitly used parameters to turn off warnings */
  (void)p_to;
}

static FUNC(void, OS_CODE) OSEE_NEVER_INLINE
  osEE_tc_change_context_from_task_end
(
  P2VAR(OsEE_TDB, AUTOMATIC, OS_APPL_CONST) p_to
)
{
  CONSTP2CONST(OsEE_TCB, AUTOMATIC, OS_APPL_DATA) p_to_tcb  = p_to->p_tcb;

  if (p_to_tcb->status == OSEE_TASK_READY_STACKED) {
    osEE_tc_setareg(a4, p_to);
    osEE_tc_setareg(a5, p_to->hdb.p_scb);
    osEE_tc_jump(osEE_hal_restore_ctx);
  } else {
    osEE_tc_setareg(a4, p_to);
    osEE_tc_setareg(a5, p_to->hdb.p_scb);
    osEE_tc_jump(osEE_hal_ready2stacked);
  }
}

#if defined(__GNUC__)
#pragma GCC reset_options
#endif
