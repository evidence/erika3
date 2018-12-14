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

 /** \file   ee_os_mem_map_gnu_hightec.h
  *  \brief  OS part for HighTec GCC compiler of MemMap.h
  *  \author Errico Guidieri
  *  \date 2018
  */
/* MUST NOT be guards here because this file is supposed to be included
   multiple time in a single compilation unit */

/* Flag Error until we are sure that we are correct */
#define MEMMAP_ERROR

/******************************************************************************
                    ERIKA OS memory mapping code section
 *****************************************************************************/
#ifdef OS_STOP_SEC_CODE
  #undef OS_STOP_SEC_CODE
  #ifdef OS_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section "ee_kernel_text" started
  #endif
#endif

#ifdef OS_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a "ee_kernel_text" section while a CODE section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section "ee_kernel_text" ax
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

/******************************************************************************
            ERIKA OS memory mapping not initialized data section
 *****************************************************************************/
#ifdef OS_STOP_SEC_VAR_CLEARED
  #undef OS_STOP_SEC_VAR_CLEARED
  #ifdef OS_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section "ee_kernel_bss" started
  #endif
#endif

#ifdef OS_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section "ee_kernel_bss" awB
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
              ERIKA OS memory mapping initialized data section
 *****************************************************************************/
#ifdef OS_STOP_SEC_VAR_INIT
  #undef OS_STOP_SEC_VAR_INIT
  #ifdef OS_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section "ee_kernel_data" started
  #endif
#endif

#ifdef OS_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section "ee_kernel_data" aw
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                    ERIKA OS memory mapping stack section
 *****************************************************************************/
#ifdef OS_STOP_SEC_STACK
  #undef OS_STOP_SEC_STACK
  #ifdef OS_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section "ee_kernel_stack" started
  #endif
#endif

#ifdef OS_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_kernel_stack" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section "ee_kernel_stack" 8 awB
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                    ERIKA OS memory mapping const section
 *****************************************************************************/
#ifdef OS_STOP_SEC_CONST
  #undef OS_STOP_SEC_CONST
  #ifdef OS_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section "ee_kernel_const" started
  #endif
#endif

#ifdef OS_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a "ee_kernel_const" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section ".rodata" a
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

/******************************************************************************
          ERIKA OS global memory mapping not initialized data section
 *****************************************************************************/
#ifdef OS_STOP_SEC_GLOBAL_VAR_CLEARED
  #undef OS_STOP_SEC_GLOBAL_VAR_CLEARED
  #ifdef OS_START_SEC_GLOBAL_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_GLOBAL_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section "ee_gbl_kernel_bss" started
  #endif
#endif

#ifdef OS_START_SEC_GLOBAL_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".ee_gbl_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #pragma section ".bss_lmu" awB
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                  ERIKA API memory mapping code section
 *****************************************************************************/
#ifdef API_STOP_SEC_CODE
  #undef API_STOP_SEC_CODE
  #ifdef API_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef API_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section "ee_api_text" started
  #endif
#endif

#ifdef API_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a "ee_api_text" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section "ee_api_text" ax
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

/******************************************************************************
              ERIKA API memory mapping not initialized data section
 *****************************************************************************/
#ifdef API_STOP_SEC_VAR_CLEARED
  #undef API_STOP_SEC_VAR_CLEARED
  #ifdef API_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef API_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error "No section "ee_api_bss" started"
  #endif
#endif

#ifdef API_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_api_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section "ee_api_bss" awB
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                ERIKA API memory mapping initialized data section
 *****************************************************************************/
#ifdef API_STOP_SEC_VAR_INIT
  #undef API_STOP_SEC_VAR_INIT
  #ifdef API_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef API_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section "ee_api_data" started
  #endif
#endif

#ifdef API_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_api_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section "ee_api_data" aw
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
  ERIKA OS core specific ERIKA OS memory mapping not initialized data section
 *****************************************************************************/
#ifdef OS_CORE0_STOP_SEC_VAR_CLEARED
  #undef OS_CORE0_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE0_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU0.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU0.ee_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU0.ee_kernel_bss" awBc0
    #endif
    #pragma section ".bss_cpu0" awBc0
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_VAR_CLEARED
  #undef OS_CORE1_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE1_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU1.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU1.ee_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU1.ee_kernel_bss" awBc1
    #endif
    #pragma section ".bss_cpu1" awBc1
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_VAR_CLEARED
  #undef OS_CORE2_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE2_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU2.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU2.ee_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU2.ee_kernel_bss" awBc2
    #endif
    #pragma section ".bss_cpu2" awBc2
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_VAR_CLEARED
  #undef OS_CORE3_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE3_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU3.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU3.ee_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU3.ee_kernel_bss" awBc3
    #endif
    #pragma section ".bss_cpu3" awBc3
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_VAR_CLEARED
  #undef OS_CORE4_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE4_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU4.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU4.ee_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU4.ee_kernel_bss" awBc4
    #endif
    #pragma section ".bss_cpu4" awBc4
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_VAR_CLEARED
  #undef OS_CORE6_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE6_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU6.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE6_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU6.ee_kernel_bss" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU6.ee_kernel_bss" awBc6
    #endif
    #pragma section ".bss_cpu6" awBc6
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
    ERIKA OS core specific ERIKA OS memory mapping initialized data section
 *****************************************************************************/
#ifdef OS_CORE0_STOP_SEC_VAR_INIT
  #undef OS_CORE0_STOP_SEC_VAR_INIT
  #ifdef OS_CORE0_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU0.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU0.ee_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU0.ee_kernel_data" awc0
    #endif
    #pragma section ".data_cpu0" awc0
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_VAR_INIT
  #undef OS_CORE1_STOP_SEC_VAR_INIT
  #ifdef OS_CORE1_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU1.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU1.ee_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU1.ee_kernel_data" awc1
    #endif
    #pragma section ".data_cpu1" awc1
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_VAR_INIT
  #undef OS_CORE2_STOP_SEC_VAR_INIT
  #ifdef OS_CORE2_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU2.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU2.ee_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU2.ee_kernel_data" awc2
    #endif
    #pragma section ".data_cpu2" awc2
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_VAR_INIT
  #undef OS_CORE3_STOP_SEC_VAR_INIT
  #ifdef OS_CORE3_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU3.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU3.ee_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU3.ee_kernel_data" awc3
    #endif
    #pragma section ".data_cpu3" awc3
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_VAR_INIT
  #undef OS_CORE4_STOP_SEC_VAR_INIT
  #ifdef OS_CORE4_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU4.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU4.ee_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU4.ee_kernel_data" awc4
    #endif
    #pragma section ".data_cpu4" awc4
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_VAR_INIT
  #undef OS_CORE6_STOP_SEC_VAR_INIT
  #ifdef OS_CORE6_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU6.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE6_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU6.ee_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section ".CPU6.ee_kernel_data" awc6
    #endif
    #pragma section ".data_cpu6" awc6
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
      ERIKA OS core specific ERIKA OS memory mapping const data section
 ******************************************************************************/
#ifdef OS_CORE0_STOP_SEC_CONST
  #undef OS_CORE0_STOP_SEC_CONST
  #ifdef OS_CORE0_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section ".CPU0.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU0.ee_kernel_const" section while a CONST section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #if 0
      #pragma section ".CPU0.ee_kernel_const" ac0
      #endif
      #pragma section ".CPU0.rodata" ac0
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_CONST
  #undef OS_CORE1_STOP_SEC_CONST
  #ifdef OS_CORE1_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section ".CPU1.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU1.ee_kernel_const" section while a CONST section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #if 0
      #pragma section ".CPU1.ee_kernel_const" ac1
      #endif
      #pragma section ".CPU1.rodata" ac1
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_CONST
  #undef OS_CORE2_STOP_SEC_CONST
  #ifdef OS_CORE2_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section ".CPU2.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU2.ee_kernel_const" section while a CONST section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #if 0
      #pragma section ".CPU2.ee_kernel_const" ac2
      #endif
      #pragma section ".CPU2.rodata" ac2
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_CONST
  #undef OS_CORE3_STOP_SEC_CONST
  #ifdef OS_CORE3_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section ".CPU3.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU3.ee_kernel_const" section while a CONST section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #if 0
      #pragma section ".CPU3.ee_kernel_const" ac3
      #endif
      #pragma section ".CPU3.rodata" ac3
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_CONST
  #undef OS_CORE4_STOP_SEC_CONST
  #ifdef OS_CORE4_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section ".CPU4.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU4.ee_kernel_const" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #if 0
      #pragma section ".CPU4.ee_kernel_const" ac4
      #endif
      #pragma section ".CPU4.rodata" ac4
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_CONST
  #undef OS_CORE6_STOP_SEC_CONST
  #ifdef OS_CORE6_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section
    #endif
  #else
    #error No section ".CPU6.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE6_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU6.ee_kernel_const" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #if 0
      #pragma section ".CPU6.ee_kernel_const" ac6
      #endif
      #pragma section ".CPU6.rodata" ac6
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

/******************************************************************************
                    ERIKA OS memory mapping stack section
 *****************************************************************************/
#ifdef OS_CORE0_STOP_SEC_STACK
  #undef OS_CORE0_STOP_SEC_STACK
  #ifdef OS_CORE0_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU0.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU0.ee_kernel_stack" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section".CPU0.ee_kernel_stack" 8 awBc0
    #endif
    #pragma section ".ustack_cpu0" 8 awBc0
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_STACK
  #undef OS_CORE1_STOP_SEC_STACK
  #ifdef OS_CORE1_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU1.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU1.ee_kernel_stack" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section".CPU1.ee_kernel_stack" 8 awBc1
    #endif
    #pragma section ".ustack_cpu1" 8 awBc1
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_STACK
  #undef OS_CORE2_STOP_SEC_STACK
  #ifdef OS_CORE2_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU2.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU2.ee_kernel_stack" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section".CPU2.ee_kernel_stack" 8 awBc2
    #endif
    #pragma section ".ustack_cpu2" 8 awBc2
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_STACK
  #undef OS_CORE3_STOP_SEC_STACK
  #ifdef OS_CORE3_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU3.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU3.ee_kernel_stack" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section".CPU3.ee_kernel_stack" 8 awBc3
    #endif
    #pragma section ".ustack_cpu3" 8 awBc3
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_STACK
  #undef OS_CORE4_STOP_SEC_STACK
  #ifdef OS_CORE4_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU4.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU4.ee_kernel_stack" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section".CPU4.ee_kernel_stack" awBc4
    #endif
    #pragma section ".ustack_cpu4" 8 awBc4
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_STACK
  #undef OS_CORE6_STOP_SEC_STACK
  #ifdef OS_CORE6_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section
  #else
    #error No section ".CPU6.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE6_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU6.ee_kernel_stack" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
    #pragma section".CPU6.ee_kernel_stack" 8 awBc6
    #endif
    #pragma section ".ustack_cpu6" 8 awBc6
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/* Check if the "command macro" has been acknowledged */
#ifdef MEMMAP_ERROR
#error Wrong MemMap.h inclusion command macro!
#endif
