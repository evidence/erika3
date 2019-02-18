/** @file mss_linker.cmd
*   @brief This is linker description file for Cortex R4 processor of Master subsystem
*   @date 18.March.2015
*   @version 01.00.00
*
*/

/*
* Copyright (C) 2009-2014 Texas Instruments Incorporated - TI web adress www.ti.com
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/*
 * STACK SIZE MACRO DEFINITIONS
 */
#define M_USER_STACK_SIZE   0x2000   /* Multiple of 8 bytes - 6KB */
#define M_PREV_STACK_SIZE   0x10    /* Multiple of 8 bytes - 16B */

/*
 * LINKER OPTIONS
 */
--entry_point=_c_int00
-stack=0x2000
--retain="*(.intvecs)"

/*
 * OPTIONAL LIBRARY INCLUSION
 */
//--library=libc.a

/*
 * SPECIFY THE SYSTEM MEMORY MAP, KEEP ALL MEMORY SIZE multiple of 8 bytes(64 bits) to generate ECC
 */
MEMORY
{
    PROG_VEC_TCMA_RAM   : org = 0x00000000   len = 0x00000048    /* PROGRAM MEMORY    (ROM) (72 Bytes)- 8 BYTE ALIGNED */
    MSS_TCMA_RAM        : org = 0x00000048   len = 0x0003FFB0    /* PROGRAM MEMORY (RAM : TCMA) (256 kB - 72 Bytes)    */
    MSS_TCMA_RAM_END    : org = 0x0003FFF8   len = 0x00000008    /* PROGRAM MEMORY (RAM : TCMA) (128 kB - 72 Bytes)    */
    MSS_TCMB            : org = 0x08000000   len = 0x00030000    /* DATA MEMORY       (RAM : TCMB) (192 kBytes)         */

    MSS_SW_BUFFER       : org = 0x0C200000   len = 0x00002000    /* SOFTWARE BUFFER   (8 kBytes)                       */
}

/*
 * SPECIFY THE SECTIONS ALLOCATION INTO MEMORY
 */
SECTIONS
{
    .intvecs    : { *(.intvecs) }    >  PROG_VEC_TCMA_RAM     ALIGN(8)               /* INTERRUPT VECTORS                 */
    .startup    : { *(.startup) }    >  MSS_TCMA_RAM ALIGN(8)      /* STARTUP CODE - 8 BYTE ALIGNED     */

    GROUP
    {
        .code   : { *(.text) }        , ALIGN(8)                       /* CODE                              */
        .cinit  {}                    , ALIGN(8)
        .const  : { *(.const) }       , ALIGN(8)                       /* CONSTANT DATA                     */

    }                                >   MSS_TCMA_RAM ALIGN(8)          /* CODE SECTION 8 BYTE ALIGNED       */

    .bss:                                                              /* GLOBAL & STATIC VARS              */
    {
      __bss_start = . ;
      /* *(.tcmVimRam) */
      *(.bss)
      __bss_end = . ;
    }                                >  MSS_TCMB ALIGN(8)

    .data:                                                             /* GLOBAL & STATIC VARS with C-init  */
    {
      __cinit_data_start = . ;
      *(.data)
      __cinit_data_end = . ;
    }                                >  MSS_TCMB ALIGN(8)

    .stack:                                                            /* SOFTWARE SYSTEM STACK                */
     {
                                   __stack = .;
                                   __SP_END_USER_MODE = .;             /* SYSTEM/USER MODE STACK END           */
         . += M_USER_STACK_SIZE;   __SP_USER_MODE     = .;             /* SYSTEM/USER MODE STACK START         */
         . += M_PREV_STACK_SIZE;   __SP_SVC_MODE      = .;             /* SVC MODE STACK - NOT USED            */
         . += M_PREV_STACK_SIZE;   __SP_IRQ_MODE      = .;             /* IRQ MODE STACK - NOT USED            */
         . += M_PREV_STACK_SIZE;   __SP_FIQ_MODE      = .;             /* FIQ MODE STACK - NOT USED            */
         . += M_PREV_STACK_SIZE;   __SP_UDEF_MODE     = .;             /* UDEF MODE STACK - NOT USED           */
         . += M_PREV_STACK_SIZE;   __SP_ABT_MODE      = .;             /* ABORT MODE STACK - NOT USED          */

     }                              >  MSS_TCMB  ALIGN(32)      /* SP BASE ADDR 32 BYTE ALIGNED FOR MPU */

}

/*
 * END OF .cmd file
 */


