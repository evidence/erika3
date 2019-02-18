/*# ###*B*###
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
  # ###*E*###
*/

/**
 * \file  ee_cortex_r_boot.S
 * \brief Start-up code
 *
 *
 * \author  Errico Guidieri
 * \date    2017
 */

/*============================================================================
  ============================================================================
                    Exception Modes Stacks Declaration (Weak)
  ============================================================================
  ==========================================================================*/
  .section .stack, "aw", %nobits

#if (defined(OSEE_MODE_SYS_STACK_SIZE))
  .equ  Mode_SYS_Stack_Size, OSEE_MODE_SYS_STACK_SIZE
#else
  .equ  Mode_SYS_Stack_Size, 8192
#endif

#if (defined(OSEE_MODE_SVC_STACK_SIZE))
  .equ  Mode_SVC_Stack_Size, OSEE_MODE_SVC_STACK_SIZE
#else
  .equ  Mode_SVC_Stack_Size, 2048
#endif

#if (defined(OSEE_EXCEPTIONS_STACK_SIZE))
  .equ  Mode_EXE_Stack_Size, OSEE_EXCEPTIONS_STACK_SIZE
#else
  .equ  Mode_EXE_Stack_Size, 1024
#endif

/*=============================================================================
                                 USR Mode Stack
  ===========================================================================*/
  .weak   osEE_cortex_r_usr_stack_top
  .weak   osEE_cortex_r_usr_stack_bottom

  .align  3
osEE_cortex_r_usr_stack_top:
    .space    Mode_SYS_Stack_Size
  .size osEE_cortex_r_usr_stack_top, . - osEE_cortex_r_usr_stack_top

osEE_cortex_r_usr_stack_bottom:
  .size osEE_cortex_r_usr_stack_bottom, . - osEE_cortex_r_usr_stack_bottom

/*=============================================================================
                                 SVC Mode Stack
  ===========================================================================*/
  .weak   osEE_cortex_r_svc_stack_top
  .weak   osEE_cortex_r_svc_stack_bottom

  .align  3
osEE_cortex_r_svc_stack_top:
    .space    Mode_EXE_Stack_Size
  .size osEE_cortex_r_svc_stack_top, . - osEE_cortex_r_svc_stack_top

osEE_cortex_r_svc_stack_bottom:
  .size osEE_cortex_r_svc_stack_bottom, . - osEE_cortex_r_svc_stack_bottom

/*=============================================================================
                                 FIQ Mode Stack
  ===========================================================================*/
  .weak   osEE_cortex_r_fiq_stack_top
  .weak   osEE_cortex_r_fiq_stack_bottom

  .align  3
osEE_cortex_r_fiq_stack_top:
    .space    Mode_EXE_Stack_Size
  .size osEE_cortex_r_fiq_stack_top, . - osEE_cortex_r_fiq_stack_top

osEE_cortex_r_fiq_stack_bottom:
  .size osEE_cortex_r_fiq_stack_bottom, . - osEE_cortex_r_fiq_stack_bottom

/*=============================================================================
                                 IRQ Mode Stack
  ===========================================================================*/
  .weak   osEE_cortex_r_irq_stack_top
  .weak   osEE_cortex_r_irq_stack_bottom

  .align  3
osEE_cortex_r_irq_stack_top:
    .space    Mode_EXE_Stack_Size
  .size osEE_cortex_r_irq_stack_top, . - osEE_cortex_r_irq_stack_top

osEE_cortex_r_irq_stack_bottom:
  .size osEE_cortex_r_irq_stack_bottom, . - osEE_cortex_r_irq_stack_bottom

/*=============================================================================
                                 ABT Mode Stack
  ===========================================================================*/
  .weak  osEE_cortex_r_abt_stack_top
  .weak  osEE_cortex_r_abt_stack_bottom

  .align  3
osEE_cortex_r_abt_stack_top:
    .space    Mode_EXE_Stack_Size
  .size osEE_cortex_r_abt_stack_top, . - osEE_cortex_r_abt_stack_top

osEE_cortex_r_abt_stack_bottom:
  .size osEE_cortex_r_abt_stack_bottom, . - osEE_cortex_r_abt_stack_bottom

/*=============================================================================
                                 UND Mode Stack
  ===========================================================================*/
  .weak   osEE_cortex_r_und_stack_top
  .weak   osEE_cortex_r_und_stack_bottom

  .align  3
osEE_cortex_r_und_stack_top:
    .space    Mode_EXE_Stack_Size
  .size osEE_cortex_r_und_stack_top, . - osEE_cortex_r_und_stack_top

osEE_cortex_r_und_stack_bottom:
  .size osEE_cortex_r_und_stack_bottom, . - osEE_cortex_r_und_stack_bottom

/*============================================================================
  ============================================================================
                             Optional Heap Definition
  ============================================================================
  ==========================================================================*/
#if (defined(OSEE_HEAP_SIZE))
  .section  .heap, "aw", %nobits

  .equ    Heap_Size, OSEE_HEAP_SIZE

  .globl  osEE_cortex_r_heap_base
  .globl  osEE_cortex_r_heap_end

  .align 3
osEE_cortex_r_heap_base:
    .space    Heap_Size
  .size osEE_cortex_r_heap_base, . - osEE_cortex_r_heap_base

osEE_cortex_r_heap_end:
  .size osEE_cortex_r_heap_end, . - osEE_cortex_r_heap_end
#endif /* OSEE_HEAP_SIZE */

/*=============================================================================
  =============================================================================
                                    Reset Handler
  =============================================================================
  ===========================================================================*/

/*=============================================================================
                                   Utility Macros
  ===========================================================================*/
/* CPSR Macros: */
  .equ  CPSR_MODE_USR,        0x10
  .equ  CPSR_MODE_FIQ,        0x11
  .equ  CPSR_MODE_IRQ,        0x12
  .equ  CPSR_MODE_SVC,        0x13
  .equ  CPSR_MODE_ABT,        0x17
  .equ  CPSR_MODE_UND,        0x1B
  .equ  CPSR_MODE_SYS,        0x1F

  .equ  CPSR_I_BIT,           0x80
  .equ  CPSR_F_BIT,           0x40

/* SCTRL Macros: */
  .equ  SCTRL_M_BIT,          0x00000001 /* MMU/MPU enable bit        */
  .equ  SCTRL_A_BIT,          0x00000002 /* Alignement Checking Bit   */
  .equ  SCTRL_C_BIT,          0x00000004 /* Data & Unified Cache Bit  */
  .equ  SCTRL_I_BIT,          0x00001000 /* Instruction Cache Bit     */

/* MPIDR Macros: */
  .equ  MPIDR_AFF0,           0xFF

/* Zynq Ultrascale RPU Macros: */
  .equ  RPU_GLBL_CNTL,        0xFF9A0000
  .equ  RPU_ERR_INJ,          0xFF9A0020
  .equ  RPU_0_PWRCTL,         0xFF9A0108
  .equ  RPU_1_PWRCTL,         0xFF9A0208
  .equ  RST_LPD_DBG,          0xFF5E0240
  .equ  BOOT_MODE_USER,       0xFF5E0200

  .equ  FAULT_LOG_ENABLE_MSK, 0x101
  .equ  PWRCTL_MASK,          0x1


  .extern osEE_sbss_start
  .extern osEE_sbss_end
  .extern osEE_bss_start
  .extern osEE_bss_end

#if (defined(OSEE_C_LIB))
  .extern __libc_init_array
  .extern __libc_fini_array
  .extern exit
#endif /* OSEE_C_LIB */
  .extern osEE_cortex_r_c_start

/* Using .set to make a 'symbol alias' of the 'Vector Table' help to
   fetch the latter from libee.a with a Linker Script with ENTRY(_boot). */
#if (!defined(OSEE_CORTEX_R_VECTOR_TABLE))
#define OSEE_CORTEX_R_VECTOR_TABLE _vector_table
#endif /* OSEE_CORTEX_R_VECTOR_TABLE */

  .global OSEE_CORTEX_R_VECTOR_TABLE
  .set vector_base, OSEE_CORTEX_R_VECTOR_TABLE

  .section .boot,"axS", %progbits

  .global _boot
  .type   _boot,  %function
_boot:
/*=============================================================================
                              Init Stack Pointers
  ===========================================================================*/
    cps #CPSR_MODE_FIQ
    ldr sp, =osEE_cortex_r_fiq_stack_bottom

    cps #CPSR_MODE_IRQ
    ldr sp, =osEE_cortex_r_irq_stack_bottom

    cps #CPSR_MODE_SVC
    ldr sp, =osEE_cortex_r_svc_stack_bottom

    cps #CPSR_MODE_ABT
    ldr sp, =osEE_cortex_r_abt_stack_bottom

    cps #CPSR_MODE_UND
    ldr sp, =osEE_cortex_r_und_stack_bottom

    cps #CPSR_MODE_SYS
    ldr sp, =osEE_cortex_r_usr_stack_bottom

/*=============================================================================
                 Disable MPU and Caches (not needed in cold reset)
  ===========================================================================*/
/* Read SCTRL CP15 Control Register */
    mrc p15, 0, r0, c1, c0, 0
/* Disable MPU (M bit) & data cache (C bit) */
    bic r0, r0, #SCTRL_M_BIT | SCTRL_C_BIT
/* Disable instruction cache (I bit) [2 instructions needed, mask too big] */
    bic r0, r0, #SCTRL_I_BIT
/* Ensure all previous loads/stores have completed (warm boot) */
    dsb
/* Write Back SCTRL CP15 Control Register */
    mcr p15, 0, r0, c1, c0, 0
/* Ensure subsequent instructionss execute wrt new MPU settings */
    isb

#if (defined(OSEE_CORTEX_R_VFP))
/*=============================================================================
                                    Enable VFP
  ===========================================================================*/
/*
 * Enable access to VFP by enabling access to Coprocessors 10 and 11.
 * Enables Full Access i.e. in both privileged and non privileged modes
 */
/* Read Coprocessor Access Control Register (CPACR) */
    mrc   p15, 0, r0, c1, c0, 2
/* Enable access to CP 10 & 11 */
    orr   r0, r0, #(0xF << 20)
/* Write Back Coprocessor Access Control Register (CPACR) */
    mcr   p15, 0, r0, c1, c0, 2
/* Synchronize processor status */
    isb
/* Enable FPU Access */
    vmrs  r3, fpexc
    orr   r1, r3, #(1<<30)
    vmsr  fpexc, r1
#endif /* OSEE_CORTEX_R_VFP */

/* The following initialization is Zynq Ultrascale RPU specific from BSP.
   To Be Reenabled if ERIKA will be integrated with BSP */
#if 0
/*=============================================================================
                      Disable Branch prediction, TCM ECC checks
  ===========================================================================*/
/* Read ACTLR */
    mrc   p15, 0, r0, c1, c0, 1
/* Enable RSDIS bit 17 to disable the return stack */
    orr   r0, r0, #(0x1 << 17)
/* Set BP bit 16, Clear BP bit 15:
   Branch always not taken and history table updates disabled */
    orr   r0, r0, #(0x1 << 16)
    bic   r0, r0, #(0x1 << 15)
/* Disable B1TCM ECC check */
    bic   r0, r0, #(0x1 << 27)
/* Disable B0TCM ECC check */
    bic   r0, r0, #(0x1 << 26)
/* Disable ATCM ECC check */
    bic   r0, r0, #(0x1 << 25)
/* Enable ECC with no forced write through with [5:3]=0b101 */
    orr   r0, r0, #(0x1 << 5)
    bic   r0, r0, #(0x1 << 4)
    orr   r0, r0, #(0x1 << 3)
/* Write Back ACTLR */
    mcr   p15, 0, r0, c1, c0, 1
/* Complete all outstanding explicit memory operations*/
    dsb
/*=============================================================================
                                Cache Invalidation
  ===========================================================================*/
    mov   r0, #0
/* Invalidate icache */
    mcr   p15, 0, r0, c7, c5, 0
/* Invalidate entire data cache */
    mcr   p15, 0, r0, c15, c5, 0
    isb

/*=============================================================================
                           RPU Specific Initializations
  ===========================================================================*/
/* Enable fault log for lock step */
    ldr   r0, =RPU_GLBL_CNTL
    ldr   r1, [r0]
    ands  r1, r1, #0x8
/* Branch to initialization if split mode */
    bne   .Linit
/* Check for boot mode if in lock step, branch to init if JTAG boot mode */
    ldr   r0, =BOOT_MODE_USER
    ldr   r1, [r0]
    ands  r1, r1, #0xF
    beq   .Linit
/* Reset the debug logic */
    ldr   r0, =RST_LPD_DBG
    ldr   r1, [r0]
    orr   r1, r1, #(0x1 << 1)
    orr   r1, r1, #(0x1 << 4)
    orr   r1, r1, #(0x1 << 5)
    str   r1, [r0]
/* Enable fault log */
    ldr   r0, =RPU_ERR_INJ
    ldr   r1, =FAULT_LOG_ENABLE_MSK
    ldr   r2, [r0]
    orr   r2, r2, r1
    str   r2, [r0]
    dsb

/* Initialize MPU */
.Linit:
    blx   Init_MPU
#endif /* Zynq Ultrascale+ RPU from BSP initialization */

/*=============================================================================
                              Enable Branch prediction
  ===========================================================================*/
/* Read ACTLR */
    mrc   p15, 0, r0, c1, c0, 1
/* Clear RSDIS bit 17 to enable return stack */
    bic   r0, r0, #(0x1 << 17)
/* Clear BP bit 15 and BP bit 16:
   Normal operation, BP is taken from the global history table.*/
    bic   r0, r0, #(0x1 << 16)
    bic   r0, r0, #(0x1 << 15)
/* Disable DBWR for errata 780125 */
    orr   r0, r0, #(0x1 << 14)
/* Write Back ACTLR */
    mcr   p15, 0, r0, c1, c0, 1
/*=============================================================================
                        Cache Invalidation & Enabling
  ===========================================================================*/
    mov   r0, #0
/* Invalidate icache */
    mcr   p15, 0, r0, c7, c5, 0
/* Invalidate entire data cache */
    mcr   p15, 0, r0, c15, c5, 0
    isb
/* Enable icahce and dcache */
    mrc   p15, 0, r1, c1, c0 ,0
    ldr   r0, =0x1005
    orr   r1, r1, r0
    dsb
    mcr   p15, 0, r1, c1, c0, 0
/* Flush prefetch buffer */
    isb

#if (!defined(OSEE_ULTRASCALE_PLUS_VEC_TABLE_IN_OCM))
/*=============================================================================
                  Set vector table in TCM/LOVEC
  ARM DDI 0460D SCTRL 4.3.16 c1, System Control Register
  ...
  [13] V Determines the location of exception vectors:
    0 = normal exception vectors selected,
        address range = 0x00000000 - 0x0000001C
    1 = high exception vectors (HIVECS) selected,
        address range = 0xFFFF0000-0xFFFF001C.
  The primary input VINITHIm defines the reset value.
  ===========================================================================*/
/* Read SCTRL */
    mrc p15, 0, r0, c1, c0, 0
/* Reset bit 13: */
    bic r0, r0, #(0x1 << 13)
/* Write Back SCTRL */
    mcr p15, 0, r0, c1, c0, 0
#endif /* !OSEE_ULTRASCALE_PLUS_VEC_TABLE_IN_OCM */

/*=============================================================================
                   Clear cp15 regs with unknown reset values
  ===========================================================================*/
    mov r0, #0x0
    mcr p15, 0, r0, c5, c0, 0   /* DFSR */
    mcr p15, 0, r0, c5, c0, 1   /* IFSR */
    mcr p15, 0, r0, c6, c0, 0   /* DFAR */
    mcr p15, 0, r0, c6, c0, 2   /* IFAR */
    mcr p15, 0, r0, c9, c13, 2  /* PMXEVCNTR */
    mcr p15, 0, r0, c13, c0, 2  /* TPIDRURW */
    mcr p15, 0, r0, c13, c0, 3  /* TPIDRURO */

/*=============================================================================
                         Reset and start Cycle Counter
  ===========================================================================*/
    mov r0, #0x80000000         /* Clear overflow & Enable cycle counter MASK */
    mov r1, #0xd                /* D, C, E */
/* Clear Overflow */
    mcr p15, 0, r0, c9, c12, 3
    mcr p15, 0, r1, c9, c12, 0
/* Enable Cycle Counter */
    mcr p15, 0, r0, c9, c12, 1

/*=============================================================================
                 Warm Start-Up Check & .(s)bss initialization
  ===========================================================================*/
/* Read MPIDR register */
    mrc p15, 0, r0, c0, c0, 5
/* Get affinity level 0 -> CPU ID */
    ands  r0, r0, #MPIDR_AFF0
    bne .Lcore1
/* Load PWRCTRL address for core 0 */
    ldr r0, =RPU_0_PWRCTL
    b   .Ltest_boot_status
.Lcore1:
/* Load PWRCTRL address for core 1 */
    ldr r0, =RPU_1_PWRCTL
.Ltest_boot_status:
/* Read PWRCTRL register */
    ldr r0, [r0]
/* Extract and test PWRCTRL */
    ands  r0, r0, #PWRCTL_MASK
/* if warm reset, skip the clearing of BSS and SBSS */
    bne .Lend_bss

/* Clear .sbss & .bss */
    mov r0, #0
/* Clear .sbss */
    ldr r1, =osEE_sbss_start
    ldr r2, =osEE_sbss_end
.Lloop_sbss:
    cmp r1, r2
/* If no .sbss, no clearing required */
    bge .Lend_sbss
    str r0, [r1], #4
    b .Lloop_sbss
.Lend_sbss:

/* Clear .bss */
    ldr r1, =osEE_bss_start
    ldr r2, =osEE_bss_end
.Lloop_bss:
    cmp r1, r2
/* If no .bss, no clearing required */
    bge .Lend_bss
    str r0, [r1], #4
    b .Lloop_bss
.Lend_bss:

/*=============================================================================
                       Enable asynchronous aborts Exception
  ===========================================================================*/
    cpsie a

/*=============================================================================
                              libc initialization
  ===========================================================================*/
#if (defined(OSEE_C_LIB))
/* Run global constructors */
    blx __libc_init_array
/* Jump to main C code */
    blx osEE_cortex_r_c_start
/* Cleanup global constructors */
    blx __libc_fini_array
/* Libc exit */
    blx exit
#else
/* Jump to main C code */
    blx osEE_cortex_r_c_start
#endif /* OSEE_C_LIB */
.Lpanic:
    b   .Lpanic /* We should never get here */
  .size _start, . - _start

