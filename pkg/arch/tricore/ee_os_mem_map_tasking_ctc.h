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

 /** \file   ee_os_mem_map_tasking_ctc.h
  *  \brief  OS part for TASKING CTC compiler of MemMap.h
  *  \author Errico Guidieri
  *  \date  2019
  */
/* I need configuration for this MemMap even without OS-Applications */
#include "ee_cfg.h"
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
      #pragma section code restore
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
      #pragma section code "ee_kernel_text"
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
    #if (OSEE_CORE_ID_VALID_MASK == 1U)
      #pragma section farbss  restore
      #pragma section nearbss restore
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
    #if (OSEE_CORE_ID_VALID_MASK == 1U)
      #pragma section farbss  "private0"
      #pragma section nearbss "private0"
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
    #pragma section fardata   restore
    #pragma section neardata  restore
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
    #if (OSEE_CORE_ID_VALID_MASK == 1U)
      #pragma section fardata   "private0"
      #pragma section neardata  "private0"
    #else
      #pragma section fardata   "ee_kernel_data"
      #pragma section neardata  "ee_kernel_data"
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

    #pragma section farbss restore
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
    #pragma section farbss "private0"
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
      #pragma section farrom  restore
      #pragma section nearrom restore
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
      #pragma section farrom  "ee_kernel_const"
      #pragma section nearrom "ee_kernel_const"
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
    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss  "ee_gbl_kernel_bss"
    #pragma section nearbss "ee_gbl_kernel_bss"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/******************************************************************************
          ERIKA OS global memory mapping initialized data section
 *****************************************************************************/
#ifdef OS_STOP_SEC_GLOBAL_VAR_INIT
  #undef OS_STOP_SEC_GLOBAL_VAR_INIT
  #ifdef OS_START_SEC_GLOBAL_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_START_SEC_GLOBAL_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION
    #pragma section fardata  restore
    #pragma section neardata restore
  #else
    #error No section "ee_gbl_kernel_data" started
  #endif
#endif

#ifdef OS_START_SEC_GLOBAL_VAR_INIT
  #ifdef OSEE_OPEN_DATA_SECTION
    #error Starting a ".ee_gbl_kernel_data" section while a DATA section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #pragma section farbss  "ee_gbl_kernel_data"
    #pragma section nearbss "ee_gbl_kernel_data"
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
    #pragma section code restore
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
    #pragma section code "ee_api_text"
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
    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss  "ee_api_bss"
    #pragma section nearbss "ee_api_bss"
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
    #pragma section fardata   restore
    #pragma section neardata  restore
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
    #pragma section fardata  "ee_api_data"
    #pragma section neardata "ee_api_data"
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

    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss  "private0"
    #pragma section nearbss "private0"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_VAR_CLEARED
  #undef OS_CORE1_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE1_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss  "private1"
    #pragma section nearbss "private1"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_VAR_CLEARED
  #undef OS_CORE2_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE2_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss  "private2"
    #pragma section nearbss "private2"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_VAR_CLEARED
  #undef OS_CORE3_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE3_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss  "private3"
    #pragma section nearbss "private3"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_VAR_CLEARED
  #undef OS_CORE4_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE4_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss "private4"
    #pragma section nearbss "private4"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_VAR_CLEARED
  #undef OS_CORE6_STOP_SEC_VAR_CLEARED
  #ifdef OS_CORE6_START_SEC_VAR_CLEARED
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_VAR_CLEARED
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss  restore
    #pragma section nearbss restore
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
    #pragma section farbss "private5"
    #pragma section nearbss "private5"
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

    #pragma section fardata   restore
    #pragma section neardata  restore
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
    #pragma section fardata   "private0"
    #pragma section neardata  "private0"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_VAR_INIT
  #undef OS_CORE1_STOP_SEC_VAR_INIT
  #ifdef OS_CORE1_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section fardata   restore
    #pragma section neardata  restore
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
    #pragma section fardata   "private1"
    #pragma section neardata  "private1"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_VAR_INIT
  #undef OS_CORE2_STOP_SEC_VAR_INIT
  #ifdef OS_CORE2_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section fardata   restore
    #pragma section neardata  restore
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
    #pragma section fardata   "private2"
    #pragma section neardata  "private2"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_VAR_INIT
  #undef OS_CORE3_STOP_SEC_VAR_INIT
  #ifdef OS_CORE3_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section fardata   restore
    #pragma section neardata  restore
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
    #pragma section fardata   "private3"
    #pragma section neardata  "private3"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_VAR_INIT
  #undef OS_CORE4_STOP_SEC_VAR_INIT
  #ifdef OS_CORE4_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section fardata   restore
    #pragma section neardata  restore
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
    #pragma section fardata   "private4"
    #pragma section neardata  "private4"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_VAR_INIT
  #undef OS_CORE6_STOP_SEC_VAR_INIT
  #ifdef OS_CORE6_START_SEC_VAR_INIT
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_VAR_INIT
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section fardata restore
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
    #pragma section fardata   "private5"
    #pragma section neardata  "private5"
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  restore
      #pragma section nearrom restore
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  "CPU0.ee_kernel_const"
      #pragma section nearrom "CPU0.ee_kernel_const"
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  restore
      #pragma section nearrom restore
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  "CPU1.ee_kernel_const"
      #pragma section nearrom "CPU1.ee_kernel_const"
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  restore
      #pragma section nearrom restore
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  "CPU2.ee_kernel_const"
      #pragma section nearrom "CPU2.ee_kernel_const"
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  restore
      #pragma section nearrom restore
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  "CPU3.ee_kernel_const"
      #pragma section nearrom "CPU3.ee_kernel_const"
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  restore
      #pragma section nearrom restore
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  "CPU4.ee_kernel_const"
      #pragma section nearrom "CPU4.ee_kernel_const"
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  restore
      #pragma section nearrom restore
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
    #if (defined(__CORE_TC162__))
      #pragma section farrom  "CPU6.ee_kernel_const"
      #pragma section nearrom "CPU6.ee_kernel_const"
    #endif
    #define OSEE_OPEN_CONST_SECTION
  #endif
#endif

/******************************************************************************
      ERIKA OS core specific ERIKA OS memory mapping code section
 ******************************************************************************/
#ifdef OS_CORE0_STOP_SEC_CODE
  #undef OS_CORE0_STOP_SEC_CODE
  #ifdef OS_CORE0_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_CORE0_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code restore
      #endif
      #pragma code_core_association restore
    #endif
  #else
    #error No section ".CPU0.code" started
  #endif
#endif
#ifdef OS_CORE0_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a ".CPU0.code" section while a CODE section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code  "CPU0.code"
      #endif
      #pragma code_core_association private0
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_CODE
  #undef OS_CORE1_STOP_SEC_CODE
  #ifdef OS_CORE1_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code restore
      #endif
      #pragma code_core_association restore
    #endif
  #else
    #error No section ".CPU1.code" started
  #endif
#endif
#ifdef OS_CORE1_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a ".CPU1.code" section while a CODE section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code  "CPU1.code"
      #endif
      #pragma code_core_association private1
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_CODE
  #undef OS_CORE2_STOP_SEC_CODE
  #ifdef OS_CORE2_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code restore
      #endif
      #pragma code_core_association restore
    #endif
  #else
    #error No section ".CPU2.code" started
  #endif
#endif
#ifdef OS_CORE2_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a ".CPU2.code" section while a CODE section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code  "CPU2.code"
      #endif
      #pragma code_core_association private2
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_CODE
  #undef OS_CORE3_STOP_SEC_CODE
  #ifdef OS_CORE3_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code restore
      #endif
      #pragma code_core_association restore
    #endif
  #else
    #error No section ".CPU3.code" started
  #endif
#endif
#ifdef OS_CORE3_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a ".CPU3.code" section while a CODE section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code  "CPU3.code"
      #endif
      #pragma code_core_association private3
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_CODE
  #undef OS_CORE4_STOP_SEC_CODE
  #ifdef OS_CORE4_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code restore
      #endif
      #pragma code_core_association restore
    #endif
  #else
    #error No section ".CPU4.code" started
  #endif
#endif
#ifdef OS_CORE4_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a ".CPU4.code" section while a CODE section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code  "CPU4.code"
      #endif
      #pragma code_core_association private4
    #endif
    #define OSEE_OPEN_CODE_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_CODE
  #undef OS_CORE6_STOP_SEC_CODE
  #ifdef OS_CORE6_START_SEC_CODE
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_CODE
    #undef OSEE_OPEN_CODE_SECTION
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code restore
      #endif
      #pragma code_core_association restore
    #endif
  #else
    #error No section ".CPU6.code" started
  #endif
#endif
#ifdef OS_CORE6_START_SEC_CODE
  #ifdef OSEE_OPEN_CODE_SECTION
    #error Starting a ".CPU6.code" section while a CODE section\
 is already started
  #else
    #undef MEMMAP_ERROR
    #if (defined(__CORE_TC162__))
      #if 0
        #pragma section code  "CPU6.code"
      #endif
      #pragma code_core_association private5
    #endif
    #define OSEE_OPEN_CODE_SECTION
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

    #pragma section farbss restore
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
    #pragma section farbss "private0"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE1_STOP_SEC_STACK
  #undef OS_CORE1_STOP_SEC_STACK
  #ifdef OS_CORE1_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE1_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss restore
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
    #pragma section farbss "private1"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE2_STOP_SEC_STACK
  #undef OS_CORE2_STOP_SEC_STACK
  #ifdef OS_CORE2_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE2_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss restore
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
    #pragma section farbss "private2"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE3_STOP_SEC_STACK
  #undef OS_CORE3_STOP_SEC_STACK
  #ifdef OS_CORE3_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE3_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss restore
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
    #pragma section farbss "private3"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE4_STOP_SEC_STACK
  #undef OS_CORE4_STOP_SEC_STACK
  #ifdef OS_CORE4_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE4_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss restore
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
    #pragma section farbss "private4"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

#ifdef OS_CORE6_STOP_SEC_STACK
  #undef OS_CORE6_STOP_SEC_STACK
  #ifdef OS_CORE6_START_SEC_STACK
    #undef MEMMAP_ERROR
    #undef OS_CORE6_START_SEC_STACK
    #undef OSEE_OPEN_DATA_SECTION

    #pragma section farbss restore
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
    #pragma section farbss "private5"
    #define OSEE_OPEN_DATA_SECTION
  #endif
#endif

/* Check if the "command macro" has been acknowledged */
#ifdef MEMMAP_ERROR
#error Wrong MemMap.h inclusion command macro!
#endif
