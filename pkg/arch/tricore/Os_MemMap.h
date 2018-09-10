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

 /** @file   Os_MemMap.h
  *  @brief  AUTOSAR Compliant OS MemMap.h
  *  @author Errico Guidieri
  *  @date 2018
  */
/*******************************************************************************
                                    Requirements
 ******************************************************************************/

/* [SWS_MemMap_00032] For each basic software module description which is part
    of the input configuration a basic software module specific memory mapping
    header file {Mip}_MemMap.h shall be provided by the Memory Mapping if the
    BSW Module descriptions is NOT describing a DependencyOnArtifact as
    requiredArtifact.
    DependencyOnArtifact.category = MEMMAP. Hereby {Mip} is composed
    according <Msn>[_<vi>_<ai>] for basic software modules where:
      * <Msn> is the shortName (case sensitive) of the BswModuleDescription
      * <vi> is the vendorId of the BSW module
      * <ai> is the vendorApiInfix of the BSW module
    The sub part in squared brackets [_<vi>_<ai>] is omitted if no
    vendorApiInfix is defined for the Basic Software Module which indicates
    that it does not use multiple instantiation.
    (SRS_BSW_00465, SRS_BSW_00415, SRS_BSW_00351, SRS_BSW_00464) */

/*******************************************************************************
                            INFORMATION MACROS
 ******************************************************************************/

#undef MEM_VENDOR_ID
#undef MEM_AR_MAJOR_VERSION
#undef MEM_AR_MINOR_VERSION
#undef MEM_AR_PATCH_VERSION
#undef MEM_SW_MAJOR_VERSION
#undef MEM_SW_MINOR_VERSION
#undef MEM_SW_PATCH_VERSION

#define MEM_VENDOR_ID        (0x0065) /* Evidence S.r.l Vendor ID */

/* AUTOSAR Software Specification Version Information */
#define MEM_AR_MAJOR_VERSION        /* ? */
#define MEM_AR_MINOR_VERSION        /* ? */
#define MEM_AR_PATCH_VERSION        /* ? */

#define MEM_SW_MAJOR_VERSION        /* ? */
#define MEM_SW_MINOR_VERSION        /* ? */
#define MEM_SW_PATCH_VERSION        /* ? */

#if (defined(__GNUC__))
#include "ee_os_mem_map_gnu_hightec.h"
#else
#error Unsupported Compiler!
#endif
