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

/** \file      ee_k1_context.h
 *  \brief     ERIKA TASK context defines and assembly macro
 *
 *  \note  TO BE DOCUMENTED!!!
 *
 *  \author    Errico Guidieri
 *  \date      2016
 */

#if (!defined(OSEE_K1_CONTEXT_H))
#define OSEE_K1_CONTEXT_H

/** These assembly macro contains code to save and restore ERIKA Task context
    check 01_k1dp-VLIWCore.pdf chapter 7.4.1 Register Usage Conventions.

    Basically the TASK context is composed by all GPRs
    (General Purpose registers) that EABI dictate are "callee saved registers" +
    all GPRs with special meaning for EABi +
    RA (Return Address ) and PS (Program Status) SFRs
    (Special Function Registers)

    N.B. These macro cannot use scratch registers (Parameter registers:
         $r0..$r7 + "pure" scratch registers: $r32..$r64), because these are
         supposed to be usable anyware in C or Assembly functions
*/

#if (!defined(__ASSEMBLER__))
#include "ee_hal.h"
#else
#include "ee_cfg.h"

#include <HAL/hal/context.h>
#endif /* !__ASSEMBLER__ */

/* TASK scratch AREA size */
#if (!defined(OSEE_STACK_SCRATCH_AREA_SIZE))
#define OSEE_STACK_SCRATCH_AREA_SIZE 16
#endif /* OSEE_STACK_SCRATCH_AREA_SIZE */
/* Task Function Address offset in TDB */
#define OSEE_TDB_TASKFUNC_OFFSET     20

/* Pointer to Task Description Block (pTDB) offset in TCB */
#define OSEE_TCB_PTDB_OFFSET         0
/* Pointer to Stack Control Block offset in TCB */
#define OSEE_TCB_PSCB_OFFSET         4
/* Context data offset in TCB */
#define OSEE_TCB_CTX_OFFSET          8
/* Status offset in TCB */
#define OSEE_TCB_STATUS_OFFSET       12

/* Pointer of Stack Control Block offset in Stack Description Block (SDB) */
#define OSEE_SDB_BOS_OFFSET          0

/* Pointer Top Of The Stack offset in SCB */
#define OSEE_SCB_TOS_OFFSET          0

#define OSEE_K1_TASK_CONTEXT_R10R11_OFFSET   0
#define OSEE_K1_TASK_CONTEXT_R12R13_OFFSET   8
#define OSEE_K1_TASK_CONTEXT_R14R15_OFFSET   16
#define OSEE_K1_TASK_CONTEXT_R16R17_OFFSET   24
#define OSEE_K1_TASK_CONTEXT_R18R19_OFFSET   32
#define OSEE_K1_TASK_CONTEXT_R20R21_OFFSET   40
#define OSEE_K1_TASK_CONTEXT_R22R23_OFFSET   48
#define OSEE_K1_TASK_CONTEXT_R24R25_OFFSET   56
#define OSEE_K1_TASK_CONTEXT_R26R27_OFFSET   64
#define OSEE_K1_TASK_CONTEXT_R28R29_OFFSET   72
#define OSEE_K1_TASK_CONTEXT_R30R31_OFFSET   80
#define OSEE_K1_TASK_CONTEXT_RA_PS_OFFSET    88
#define OSEE_K1_TASK_CONTEXT_PTOS_OFFSET     96

#define OSEE_K1_TASK_CONTEX_SIZE             104

/* 26 */
#define OSEE_K1_TASK_CONTEX_WORDS (OSEE_K1_TASK_CONTEX_SIZE/sizeof(OsEE_stack))

#if (defined(__ASSEMBLER__))
/*******************************************************************************
  I Need to set IL inside osEE_change_context_from_isr2_end that is a an
  function in assembly, so I need a macro valid in assembly with the right value
 ******************************************************************************/
#if (!defined(OSEE_ISR2_MAX_HW_ASM_PRIO))
#if (!defined(OSEE_ISR2_MAX_PRIO))
#define OSEE_ISR2_MAX_HW_ASM_PRIO 2
#else
#error "If configurator provide OSEE_ISR2_MAX_PRIO MUST provide\
 OSEE_ISR2_MAX_HW_ASM_PRIO too"
#endif /* !OSEE_ISR2_MAX_PRIO */
#endif /* !OSEE_ISR2_MAX_HW_ASM_PRIO */

.macro osEE_k1_task_vcontext_save to
## Store $p10
## Access to the scoreboard (make _scoreboard_start + $pcr)
## $r6 = _scoreboard_start
## $r7 = $pcr
    sd    OSEE_K1_TASK_CONTEXT_R10R11_OFFSET[\to],  $p10  ## $r10 - $r11
    make  $r6, _scoreboard_start
    get   $r7, $pcr
    ;;
## Store $p12
## $r7 = Extract PID bitfiled from $pcr
    sd    OSEE_K1_TASK_CONTEXT_R12R13_OFFSET[\to],  $p12  ## $r12 - $r13
    extfz $r7, $r7, 15, 11
    ;;
## Store $p14
## $r7 = PID * MOS_SCOREBOARD_PER_CPU_ELEMENT_SIZE (=256) => PID << 8
    sd    OSEE_K1_TASK_CONTEXT_R14R15_OFFSET[\to],  $p14  ## $r14 - $r15
    sll   $r7, $r7, 8
    ;;
## Store $p16
## $r6 = $_scoreboard_start.SCB_VCORE.PER_CPU[pid]
    sd    OSEE_K1_TASK_CONTEXT_R16R17_OFFSET[\to],  $p16  ## $r16 - $r17
    add   $r6, $r6, $r7
    ;;
    sd    OSEE_K1_TASK_CONTEXT_R18R19_OFFSET[\to],  $p18  ## $r18 - $r19
    ;;
    sd    OSEE_K1_TASK_CONTEXT_R20R21_OFFSET[\to],  $p20  ## $r20 - $r21
    ;;
    sd    OSEE_K1_TASK_CONTEXT_R22R23_OFFSET[\to],  $p22  ## $r22 - $r23
    ;;
    sd    OSEE_K1_TASK_CONTEXT_R24R25_OFFSET[\to],  $p24  ## $r24 - $r25
    ;;
    sd    OSEE_K1_TASK_CONTEXT_R26R27_OFFSET[\to],  $p26  ## $r26 - $r21
    ;;
    sd    OSEE_K1_TASK_CONTEXT_R28R29_OFFSET[\to],  $p28  ## $r28 - $r29
    ;;
    get   $r8 = $ra  ## I use $p8 (that is scratch) to hold RA & PS
    sd    OSEE_K1_TASK_CONTEXT_R30R31_OFFSET[\to],  $p30  ## $r30 - $r31
    ;;
## Get VCORE PS to be saved ($r6)
    lw    $r9 = MOS_VC_REG_PS[$r6] ## Now $p8 ($r8 & $r9 contains RA PS)
    ;;
    sd    OSEE_K1_TASK_CONTEXT_RA_PS_OFFSET[\to] = $p8  ## $ra - $ps
    ;;
  .endm

  .macro osEE_k1_task_vcontext_restore from
## Temporary Load $ra and $ps on $p10
## Access to the scoreboard
    ld    $p10  = OSEE_K1_TASK_CONTEXT_RA_PS_OFFSET[\from]  ## $ra - $ps
    make  $r8, _scoreboard_start
    get   $r9, $pcr
    ;;
## Restore $p30
## Restore $ra
## Extract PID bitfiled from $pcr
    ld    $p30  = OSEE_K1_TASK_CONTEXT_R30R31_OFFSET[\from] ## $r30 - $r31
    set   $ra   = $r10
    extfz $r9, $r9, 15, 11
    ;;
## Restore $p28
## PID * MOS_SCOREBOARD_PER_CPU_ELEMENT_SIZE (=256) => PID << 8
    ld    $p28  = OSEE_K1_TASK_CONTEXT_R28R29_OFFSET[\from] ## $r28 - $r29
    sll   $r9, $r9, 8
    ;;
## Restore $p26
## $r8 = $_scoreboard_start.SCB_VCORE.PER_CPU[pid]
    ld    $p26  = OSEE_K1_TASK_CONTEXT_R26R27_OFFSET[\from] ## $r26 - $r27
    add   $r8, $r8, $r9
    ;;
## Setting VCORE.PS
    sw    MOS_VC_REG_PS[$r8] = $r11
    ;;
    ld    $p24  = OSEE_K1_TASK_CONTEXT_R24R25_OFFSET[\from] ## $r24 - $r25
    ;;
    ld    $p22  = OSEE_K1_TASK_CONTEXT_R22R23_OFFSET[\from] ## $r22 - $r23
    ;;
    ld    $p20  = OSEE_K1_TASK_CONTEXT_R20R21_OFFSET[\from] ## $r20 - $r21
    ;;
    ld    $p18  = OSEE_K1_TASK_CONTEXT_R18R19_OFFSET[\from] ## $r18 - $r19
    ;;
    ld    $p16  = OSEE_K1_TASK_CONTEXT_R16R17_OFFSET[\from] ## $r16 - $r17
    ;;
    ld    $p14  = OSEE_K1_TASK_CONTEXT_R14R15_OFFSET[\from] ## $r14 - $r15
    ;;
    /* If from registers is $r12 this instructions is supposed to write on
       $r12 its actual value. */
    ld    $p12  = OSEE_K1_TASK_CONTEXT_R12R13_OFFSET[\from] ## $r12 - $r13
    ;;
    ld    $p10  = OSEE_K1_TASK_CONTEXT_R10R11_OFFSET[\from] ## $r10 - $r11
    ;;
  .endm

#endif /* __ASSEMBLER__ */

#endif /* OSEE_K1_CONTEXT_H */
