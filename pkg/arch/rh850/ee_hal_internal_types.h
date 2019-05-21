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

/** \file   ee_internal_types.h
 *  \brief  HAL Internal Types.
 *
 *  This files contains all HAL internal types and symbols for ARMv7-R
 *  Architecture in Erika Enterprise.
 *
 *  \note COULD BE raplaced by AUTOSAR Type definition paradigm or being the
 *        implementation
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#ifndef OSEE_HAL_INTERNAL_TYPES_H
#define OSEE_HAL_INTERNAL_TYPES_H

#include "ee_platform_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/*============================================================================
                      Basic Control Register Types
  ==========================================================================*/

/* PSW: Program Status Word register type */
typedef union {
/* PSW, 32-bit access */
  OsEE_reg        reg;
  struct {
/* Bit 0, Result Zero */
    unsigned int  Z   :1;
/* Bit 1, Result Signed (negative) */
    unsigned int  S   :1;
/* Bit 2, Result Overflowed */
    unsigned int  OV  :1;
/* Bit 3, Result generate Carry */
    unsigned int  CY  :1;
/* Bit 4, Result Saturated */
    unsigned int  SAT :1;
/* Bit 5, EI level Interrupts Disabled (0:Enabled) */
    unsigned int  ID  :1;
/* Bit 6, Exception in process
   (1:An exception other than an interrupt is being serviced) */
    unsigned int  EP  :1;
/* Bit 7, FE level exceptions Disabled (0:Enabled) */
    unsigned int  NP  :1;
/* Bit [8-14], Reserved */
    unsigned int      :7;
/* Bit 15, 0:RBASE or 1:EBASE is used as exception processing base */
    unsigned int  EBV :1;
/* Bit 16, FPU Co-processor Enabled */
    unsigned int  CU0 :1;
/* Bit 17, FXU Co-processor Enabled */
    unsigned int  CU1 :1;
/* Bit 18, CU2 Reserved for future Co-processors */
    unsigned int  CU2 :1;
/* Bit [19-29], Reserved */
    unsigned int      :11;
/* Bit 30, User mode (0:Supervisor, 1:User Mode) */
    unsigned int      :1;
/* Bit 31, reserved */
    unsigned int      :1;
  }               bits;
} OsEE_psw;

/* MCTL: Machine Control */
typedef union {
/* PSW, 32-bit access */
  OsEE_reg        reg;
  struct {
/* Bit 0, 1:Allow EI/DI Instructions in User Mode */
    unsigned int  UIC :1;
/* Bit [1,31] Reserved */
    unsigned int      :31;
  }               bits;
} OsEE_mctl;

/*============================================================================
                      Interrupt Function Register Types
  ==========================================================================*/
/* ISPR: Interrupt Serviced Priority */
typedef union {
/* ISPR, 32-bit access */
    OsEE_reg            reg;
    struct {
/* Bit 0-15, Interrupts Priorities Pending */
      unsigned int ISP :16;
/* Bit [16-31], Reserved */
      unsigned int     :16;
    }                   bits;
} OsEE_ispr;

/* PLMR:  Interrupt Priority Level Mask */
typedef union {
/* ISPR, 32-bit access */
    OsEE_reg            reg;
    struct {
/* Bit [0-4], Interrupts Priorities Level Mask */
      unsigned int PLM :5;
/* Bit [5-31], Reserved */
      unsigned int     :27;
    }                   bits;
} OsEE_plmr;

/*============================================================================
                                Register Groups
 ===========================================================================*/
/*
 * To Utilize With the Diab Specific Intrinsic Functions
 *    __ldsr(n,m,v)
 *    v = __stsr(n,m)
 */
/*                                                       Access Permission  */
/*      Name                Reg, Group                  (PSW bits SV = !UM) */
/* PC save register when acknowledging EI level exception.          SV      */
#define OSEE_RH850_EIPC      0U, 0U
/* Status save register when acknowledging EI level exception.      SV      */
#define OSEE_RH850_EIPSW     1U, 0U
/* PC save register when acknowledging FE level exception.          SV      */
#define OSEE_RH850_FEPC      2U, 0U
/* Status save registers when acknowledging FE level exception.     SV      */
#define OSEE_RH850_FEPSW     3U, 0U
/* Program Status Word.                          Special (Bit depending) UM */
#define OSEE_RH850_PSW       5U, 0U

/* Floating Point Status Register.                                CU0 & SV  */
#define OSEE_RH850_FPSR      6U, 0U
/* PC save register when Floating Point Exception raise.          CU0 & SV  */
#define OSEE_RH850_FPEPC     7U, 0U
/* Floating Point Operation Status.                                 CU0     */
#define OSEE_RH850_FPST      8U, 0U
/* Floating Point Operation Comparison Result.                      CU0     */
#define OSEE_RH850_FPCC      9U, 0U
/* Floating Point Configuration.                                    CU0     */
#define OSEE_RH850_FPCFG    10U, 0U

/* EI level exception cause.                                        SV      */
#define OSEE_RH850_EIIC     13U, 0U
/* FE level exception cause.                                        SV      */
#define OSEE_RH850_FEIC     14U, 0U
/* CALLT execution PC save register.                                UM      */
#define OSEE_RH850_CTPC     16U, 0U
/* CALLT execution status save register.                            UM      */
#define OSEE_RH850_CTPSW    17U, 0U
/* CALLT base pointer.                                              UM      */
#define OSEE_RH850_CTBP     20U, 0U
/* SNOOZE Instruction Ctrl Register.                                SV      */
#define OSEE_RH850_SNZCFG   21U, 0U
/* EI level exception working register.                             SV      */
#define OSEE_RH850_EIWR     28U, 0U
/* FE level exception working register.                             SV      */
#define OSEE_RH850_FEWR     29U, 0U

/* System Protection Identifier.                                    SV      */
#define OSEE_RH850_SPID      0U, 1U
/* System Protection Identifier List.                               SV      */
#define OSEE_RH850_SPIDLIST  1U, 1U
/* Reset Vector Base Address.                                       SV      */
#define OSEE_RH850_RBASE     2U, 1U
/* Exception Handler Vector Address.                                SV      */
#define OSEE_RH850_EBASE     3U, 1U
/* Base address of the interrupt handler table.                     SV      */
#define OSEE_RH850_INTBP     4U, 1U
/* CPU control.                                                     SV      */
#define OSEE_RH850_MCTL      5U, 1U
/* Processor ID.                                                    SV      */
#define OSEE_RH850_PID       6U, 1U
/* Supervisor Lock.                                                 SV      */
#define OSEE_RH850_SVLOCK    8U, 1U
/* SYSCALL operation setting.                                       SV      */
#define OSEE_RH850_SCCFG    11U, 1U
/* SYSCALL base pointer.                                            SV      */
#define OSEE_RH850_SCBP     12U, 1U
/* Bus Master Identifier.                                           SV      */
#define OSEE_RH850_BMID      1U, 2U
/* Memory Error Address.                                            SV      */
#define OSEE_RH850_MEA       6U, 2U

/*============================================================================
                          Interrupt Registers
 ===========================================================================*/

/*                                                       Access Permission  */
/*      Name                Reg, Group                  (PSW bits SV = !UM) */
/* ISPR: Priority of interrupt being serviced.                     SV       */
#define OSEE_RH850_ISPR     10U, 2U
/* ICSR: Interrupt control status.                                 SV       */
#define OSEE_RH850_ICSR     12U, 2U
/* INTCFG: Interrupt function setting.                             SV       */
#define OSEE_RH850_INTCFG   13U, 2U
/* PLMR: Priority Level Mask Register.                             SV       */
#define OSEE_RH850_PLMR     14U, 2U

typedef struct {
/* Here can be saved either EIPC or FIPC */
  OsEE_reg XIPC;
/* Here can be saved either EIPSW or FIPSW */
  OsEE_reg XPSW;
/* Automatic context saving procedure would save this always.
   I don't know why but I'll do the same. Moreover ISA document require this
   saved and restored (e.g 4.1.7) */
  OsEE_reg EIIC;
  OsEE_reg FPSR;
  OsEE_reg FPEPC;
/* This seems to be redundant, but Embark save it. (Under Investigation) */
  OsEE_reg CTPC;
/* This seems to be redundant, but Embark save it. (Under Investigation) */
  OsEE_reg CTPSW;
  OsEE_reg r31_lp;
/* Automatic context saving procedure would save this always.
   I don't know why but I'll do the same, moreover is useful for alignment */
  OsEE_reg r30_gp;
  OsEE_reg r19;
  OsEE_reg r18;
  OsEE_reg r17;
  OsEE_reg r16;
  OsEE_reg r15;
  OsEE_reg r14;
  OsEE_reg r13;
  OsEE_reg r12;
  OsEE_reg r11;
  OsEE_reg r10;
  OsEE_reg r9;
  OsEE_reg r8;
  OsEE_reg r7;
  OsEE_reg r6;
  OsEE_reg r5;
  OsEE_reg r4;
/* Saved only to use popsp r1-r19 to restore the context */
  OsEE_reg r3_sp;
  OsEE_reg r2;
  OsEE_reg r1;
} OsEE_rh850_exception_ctx;

/* This context i partially filled by PREPARE instruction that use a
   Reg32 list12 bitmask to express which registers have to be saved
   (Look at RH850G4 ISA for more information).
    list12 is a 32-bit register list, defined as follows.
bits   31  30  29  28  27  26  25  24  23  22  21  20 ... 1 0
reg    r24 r25 r26 r27 r20 r21 r22 r23 r28 r29 r31    ... r30

Diab AS accepts a 12 bit immediate to represent list12 */
typedef struct OsEE_CTX_tag {
  struct OsEE_CTX_tag * p_ctx;    /* Previous ERIKA's Context Pointer */
  OsEE_reg              psw;
  OsEE_reg r31_lp;
  OsEE_reg r30_ep;
  OsEE_reg r29;
  OsEE_reg r28;
  OsEE_reg r27;
  OsEE_reg r26;
  OsEE_reg r25;
  OsEE_reg r24;
  OsEE_reg r23;
  OsEE_reg r22;
  OsEE_reg r21;
  OsEE_reg r20;

} OsEE_CTX;

/* Stack Control Block: contine le informazioni dinamiche relative allo stack */
typedef struct {
  OsEE_CTX      * p_tos; /* Saved Context */
} OsEE_SCB;

typedef struct {
  OsEE_CTX   * p_bos; /* Bottom Of Stack */
#if (defined(OSEE_HAS_STACK_MONITORING))
  OsEE_CTX   * p_sos; /* Start Of Stack */
#endif /* OSEE_HAS_STACK_MONITORING */
  size_t       stack_size;
} OSEE_CONST   OsEE_SDB;

typedef struct {
  OsEE_SDB          * p_sdb;
  OsEE_SCB          * p_scb;
  /* OsEE_isr_src_id     isr2_src; EG: To Be Re-enabled when supported */
} OSEE_CONST OsEE_HDB;

#if (defined(OSEE_HAS_ORTI)) || (defined(OSEE_HAS_STACK_MONITORING))
typedef struct {
  OsEE_SDB (* p_sdb_array)[];
  OsEE_SCB (* p_scb_array)[];
  size_t   stack_num;
} OSEE_CONST OsEE_CHDB;
#endif /* OSEE_HAS_ORTI || OSEE_HAS_STACK_MONITORING */

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_HAL_INTERNAL_TYPES_H */
