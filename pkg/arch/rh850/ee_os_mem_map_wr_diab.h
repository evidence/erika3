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

 /** @file   ee_os_mem_map_gnu_hightec.h
  *  @brief  OS part for HighTec GCC compiler of MemMap.h
  *  @author Errico Guidieri
  *  @date 2018
  */
/* MUST NOT be guards here because this file is supposed to be included
   multiple time in a single compilation unit */

/* Flag Error until we are sure that we are correct */
#define MEMMAP_ERROR

/******************************************************************************
                  ERIKA OS memory mapping code section
 ******************************************************************************/
#ifdef OS_STOP_SEC_CODE
  #undef OS_STOP_SEC_CODE
  #ifdef OS_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if 0
      #pragma section CODE X
    #endif
  #else
    #error No section "ee_kernel_text" started
  #endif
#endif

#ifdef OS_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a "ee_kernel_text" section while a section is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section CODE "ee_kernel_text" X
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

/******************************************************************************
              ERIKA OS memory mapping not initialized data section
 ******************************************************************************/
#ifdef OS_STOP_SEC_VAR_CLEARED
  #undef OS_STOP_SEC_VAR_CLEARED
  #ifdef OS_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section DATA
      #pragma section SDATA
    #endif
  #else
    #error No section "ee_kernel_bss" started
  #endif
#endif

#ifdef OS_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section DATA "ee_kernel_data" "ee_kernel_bss"
      #pragma section SDATA "ee_kernel_sdata" "ee_kernel_sbss"
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
              ERIKA OS memory mapping initialized data section
 ******************************************************************************/
#ifdef OS_STOP_SEC_VAR_INIT
  #undef OS_STOP_SEC_VAR_INIT
  #ifdef OS_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section DATA
      #pragma section SDATA
    #endif
  #else
    #error No section "ee_kernel_data" started
  #endif
#endif

#ifdef OS_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_kernel_data" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section DATA "ee_kernel_data" "ee_kernel_bss"
      #pragma section SDATA "ee_kernel_sdata" "ee_kernel_sbss"
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                    ERIKA OS memory mapping stack section
 ******************************************************************************/
#ifdef OS_STOP_SEC_STACK
  #undef OS_STOP_SEC_STACK
  #ifdef OS_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section DATA
    #endif
  #else
    #error No section "ee_kernel_stack" started
  #endif
#endif

#ifdef OS_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_kernel_stack" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section DATA "ee_kernel_stack" "ee_kernel_stack"
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                    ERIKA OS memory mapping const section
 ******************************************************************************/
#ifdef OS_STOP_SEC_CONST
  #undef OS_STOP_SEC_CONST
  #ifdef OS_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section CONST
    #endif
  #else
    #error No section "ee_kernel_const" started
  #endif
#endif

#ifdef OS_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a "ee_kernel_const" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section CONST "ee_kernel_const" "ee_kernel_const"
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

/******************************************************************************
              ERIKA OS global memory mapping not initialized data section
 ******************************************************************************/
#ifdef OS_STOP_SEC_GLOBAL_VAR_CLEARED
  #undef OS_STOP_SEC_GLOBAL_VAR_CLEARED
  #ifdef OS_START_SEC_GLOBAL_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_GLOBAL_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
#if 0
      #pragma section DATA
      #pragma section SDATA
#endif
  #else
    #error No section "ee_gbl_kernel_bss" started
  #endif
#endif

#ifdef OS_START_SEC_GLOBAL_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".ee_gbl_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
#if 0
      #pragma section DATA "ee_gbl_kernel_data" "ee_gbl_kernel_bss"
      #pragma section SDATA "ee_gbl_kernel_sdata" "ee_gbl_kernel_sbss"
#endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                  ERIKA API memory mapping code section
 ******************************************************************************/
#ifdef API_STOP_SEC_CODE
  #undef API_STOP_SEC_CODE
  #ifdef API_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef API_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if 0
      #pragma section CODE X
    #endif
  #else
    #error No section "ee_api_text" started
  #endif
#endif

#ifdef API_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a "ee_api_text" section while a section is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section CODE "ee_api_text" X
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

/******************************************************************************
              ERIKA API memory mapping not initialized data section
 ******************************************************************************/
#ifdef API_STOP_SEC_VAR_CLEARED
  #undef API_STOP_SEC_VAR_CLEARED
  #ifdef API_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef API_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section DATA
      #pragma section SDATA
    #endif
  #else
    #error "No section "ee_api_bss" started"
  #endif
#endif

#ifdef API_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_api_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section DATA "ee_api_data" "ee_api_bss"
      #pragma section SDATA "ee_api_sdata" "ee_api_sbss"
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
                ERIKA API memory mapping initialized data section
 ******************************************************************************/
#ifdef API_STOP_SEC_VAR_INIT
  #undef API_STOP_SEC_VAR_INIT
  #ifdef API_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef API_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #if 0
      #pragma section DATA
      #pragma section SDATA
    #endif
  #else
    #error No section "ee_api_data" started
  #endif
#endif

#ifdef API_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a "ee_api_data" section while a section is already started
  #else
    #undef MEMMAP_ERROR
    #if 0
      #pragma section DATA "ee_api_data" "ee_api_bss"
      #pragma section SDATA "ee_api_sdata" "ee_api_sbss"
    #endif
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
  ERIKA OS core specific ERIKA OS memory mapping not initialized data section
 ******************************************************************************/
#ifdef OS_CORE0_STOP_SEC_VAR_CLEARED
  #undef OS_CORE0_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE0_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU0.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU0.ee_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU0.ee_kernel_data" ".CPU0.ee_kernel_bss"
    #pragma section SDATA ".CPU0.ee_kernel_sdata" ".CPU0.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_VAR_CLEARED
  #undef OS_CORE1_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE1_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU1.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU1.ee_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU1.ee_kernel_data" ".CPU1.ee_kernel_bss"
    #pragma section SDATA ".CPU1.ee_kernel_sdata" ".CPU1.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_VAR_CLEARED
  #undef OS_CORE2_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE2_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU2.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU2.ee_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU2.ee_kernel_data" ".CPU2.ee_kernel_bss"
    #pragma section SDATA ".CPU2.ee_kernel_sdata" ".CPU2.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_VAR_CLEARED
  #undef OS_CORE3_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE3_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU3.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU3.ee_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU3.ee_kernel_data" ".CPU3.ee_kernel_bss"
    #pragma section SDATA ".CPU3.ee_kernel_sdata" ".CPU3.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_VAR_CLEARED
  #undef OS_CORE4_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE4_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU4.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU4.ee_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU4.ee_kernel_data" ".CPU4.ee_kernel_bss"
    #pragma section SDATA ".CPU4.ee_kernel_sdata" ".CPU4.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE5_STOP_SEC_VAR_CLEARED
  #undef OS_CORE5_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE5_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE5_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU5.ee_kernel_bss" started
  #endif
#endif
#ifdef OS_CORE5_START_SEC_VAR_CLEARED
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU5.ee_kernel_bss" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU5.ee_kernel_data" ".CPU5.ee_kernel_bss"
    #pragma section SDATA ".CPU5.ee_kernel_sdata" ".CPU5.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
  ERIKA OS core specific ERIKA OS memory mapping initialized data section
 ******************************************************************************/
#ifdef OS_CORE0_STOP_SEC_VAR_INIT
  #undef OS_CORE0_STOP_SEC_VAR_INIT
  #ifdef OS_CORE0_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU0.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU0.ee_kernel_data" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU0.ee_kernel_data" ".CPU0.ee_kernel_bss"
    #pragma section SDATA ".CPU0.ee_kernel_sdata" ".CPU0.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_VAR_INIT
  #undef OS_CORE1_STOP_SEC_VAR_INIT
  #ifdef OS_CORE1_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU1.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU1.ee_kernel_data" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU1.ee_kernel_data" ".CPU1.ee_kernel_bss"
    #pragma section SDATA ".CPU1.ee_kernel_sdata" ".CPU1.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_VAR_INIT
  #undef OS_CORE2_STOP_SEC_VAR_INIT
  #ifdef OS_CORE2_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU2.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU2.ee_kernel_data" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU2.ee_kernel_data" ".CPU2.ee_kernel_bss"
    #pragma section SDATA ".CPU2.ee_kernel_sdata" ".CPU2.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_VAR_INIT
  #undef OS_CORE3_STOP_SEC_VAR_INIT
  #ifdef OS_CORE3_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU3.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU3.ee_kernel_data" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU3.ee_kernel_data" ".CPU3.ee_kernel_bss"
    #pragma section SDATA ".CPU3.ee_kernel_sdata" ".CPU3.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_VAR_INIT
  #undef OS_CORE4_STOP_SEC_VAR_INIT
  #ifdef OS_CORE4_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU4.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU4.ee_kernel_data" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU4.ee_kernel_data" ".CPU4.ee_kernel_bss"
    #pragma section SDATA ".CPU4.ee_kernel_sdata" ".CPU4.ee_kernel_sbss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE5_STOP_SEC_VAR_INIT
  #undef OS_CORE5_STOP_SEC_VAR_INIT
  #ifdef OS_CORE5_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE5_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
    #pragma section SDATA
  #else
    #error No section ".CPU5.ee_kernel_data" started
  #endif
#endif
#ifdef OS_CORE5_START_SEC_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU5.ee_kernel_data" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU5.ee_kernel_data" ".CPU5.ee_kernel_bss"
    #pragma section SDATA ".CPU5.ee_kernel_sdata" ".CPU5.ee_kernel_sbss"
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
      #pragma section CONST
    #endif
  #else
    #error No section ".CPU0.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU0.ee_kernel_const" data section while a section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section CONST ".CPU0.ee_kernel_const" ".CPU0.ee_kernel_const"
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
      #pragma section CONST
    #endif
  #else
    #error No section ".CPU1.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU1.ee_kernel_const" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section CONST ".CPU1.ee_kernel_const" ".CPU1.ee_kernel_const"
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
      #pragma section CONST
    #endif
  #else
    #error No section ".CPU2.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU2.ee_kernel_const" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section CONST ".CPU2.ee_kernel_const" ".CPU2.ee_kernel_const"
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
      #pragma section CONST
    #endif
  #else
    #error No section ".CPU3.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU3.ee_kernel_const" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section CONST ".CPU3.ee_kernel_const" ".CPU3.ee_kernel_const"
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
      #pragma section CONST
    #endif
  #else
    #error No section ".CPU4.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU4.ee_kernel_const" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section CONST ".CPU4.ee_kernel_const" ".CPU4.ee_kernel_const"
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

#ifdef OS_CORE5_STOP_SEC_CONST
  #undef OS_CORE5_STOP_SEC_CONST
  #ifdef OS_CORE5_START_SEC_CONST
    #undef MEMMAP_ERROR
    #undef OS_CORE5_START_SEC_CONST
    #undef OSEE_OPEN_CONST_SECTION
    #if 0
      #pragma section CONST
    #endif
  #else
    #error No section ".CPU5.ee_kernel_const" started
  #endif
#endif
#ifdef OS_CORE5_START_SEC_CONST
  #ifdef OSEE_OPEN_CONST_SECTION
    #error Starting a ".CPU5.ee_kernel_const" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #if 0
      #pragma section CONST ".CPU5.ee_kernel_const" ".CPU5.ee_kernel_const"
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

/******************************************************************************
                    ERIKA OS memory mapping stack section
 ******************************************************************************/
#ifdef OS_CORE0_STOP_SEC_STACK
  #undef OS_CORE0_STOP_SEC_STACK
  #ifdef OS_CORE0_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
  #else
    #error No section ".CPU0.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU0.ee_kernel_stack" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU0.ee_kernel_stack" ".CPU0.ee_kernel_stack"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_STACK
  #undef OS_CORE1_STOP_SEC_STACK
  #ifdef OS_CORE1_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
  #else
    #error No section ".CPU1.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU1.ee_kernel_stack" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU1.ee_kernel_stack" ".CPU1.ee_kernel_stack"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_STACK
  #undef OS_CORE2_STOP_SEC_STACK
  #ifdef OS_CORE2_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
  #else
    #error No section ".CPU2.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU2.ee_kernel_stack" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU2.ee_kernel_stack" ".CPU2.ee_kernel_stack"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_STACK
  #undef OS_CORE3_STOP_SEC_STACK
  #ifdef OS_CORE3_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
  #else
    #error No section ".CPU3.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU3.ee_kernel_stack" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU3.ee_kernel_stack" ".CPU3.ee_kernel_stack"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_STACK
  #undef OS_CORE4_STOP_SEC_STACK
  #ifdef OS_CORE4_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
  #else
    #error No section ".CPU4.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU4.ee_kernel_stack" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU4.ee_kernel_stack" ".CPU4.ee_kernel_stack"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE5_STOP_SEC_STACK
  #undef OS_CORE5_STOP_SEC_STACK
  #ifdef OS_CORE5_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE5_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section DATA
  #else
    #error No section ".CPU5.ee_kernel_stack" started
  #endif
#endif
#ifdef OS_CORE5_START_SEC_STACK
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".CPU5.ee_kernel_stack" data section while another data section is already started
  #else
    #undef MEMMAP_ERROR
    /* This section will be changed in future */
    #pragma section DATA ".CPU5.ee_kernel_stack" ".CPU5.ee_kernel_stack"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/* Check if the "command macro" has been acknowledged */
#ifdef MEMMAP_ERROR
#error Wrong MemMap.h inclusion command macro!
#endif
