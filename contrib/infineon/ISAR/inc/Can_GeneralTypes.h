/* ###*B*###
 * Erika Enterprise, version 3
 *
 * Copyright (C) 2018 Evidence s.r.l.
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

/** \brief  Infineon AUTOSAR MCAL CAN General Types for ERIKA
 *          Enterprise.
 *
 *  \author Francesco Bagagli
 *  \date   2019
 */
#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/** \brief  CAN Id and Mask type
 *
 *  Both Std and Ext IDs are used
 */
typedef uint32 Can_IdType;

/** \brief  CAN Id and Mask typeCAN protocol data unit type.
 *
 *  CAN Id and Mask typeCAN protocol data unit type. Used to provide ID, DLC and
 *  SDU from CAN Interface to CAN driver
 */
typedef struct Can_PduType
{
  PduIdType swPduHandle;    /** SW Handle that will identify the request in
                                the confirmation callback function.           */
  uint8 length;             /** DLC                                           */
  Can_IdType id;            /** Identifier of L-PDU                           */
  uint8 *sdu;               /** Pointer to L-SDU                              */
} Can_PduType;

/** \brief  CAN Hardware Object Handle Type
 *
 *  Maximum of 256 hardware objects in the CAN hardware unit
 */
typedef uint16 Can_HwHandleType;

/** \brief  CAN state transition type
 */
typedef enum
{
  CAN_T_START,   /** CAN controller transition value to request state STARTED */
  CAN_T_STOP,    /** CAN controller transition value to request state STOPPED */
  CAN_T_SLEEP,   /** CAN controller transition value to request state SLEEP   */
  CAN_T_WAKEUP   /** CAN controller transition value to request state STOPPED
                     from state SLEEP                                         */
} Can_StateTransitionType;

/** \brief  Type for return values of few of the CAN Driver APIs
 */
typedef enum
{
  CAN_OK,       /** success */
  CAN_NOT_OK,   /** error occurred or wakeup occurred during sleep transition */
  CAN_BUSY      /** transmit request could not be processed because no transmit
                    object was available */
} Can_ReturnType;

/** \brief  Operating modes of the CAN Transceiver Driver
 */
typedef enum
{
  CANTRCV_TRCVMODE_NORMAL,   /** Transceiver mode NORMAL                      */
  CANTRCV_TRCVMODE_SLEEP,    /** Transceiver mode SLEEP                       */
  CANTRCV_TRCVMODE_STANDBY   /** Transceiver mode STANDBY                     */
} CanTrcv_TrcvModeType;

/** \brief  Wakeup modes of the CAN Transceiver Driver
 */
typedef enum
{
  CANTRCV_WUMODE_ENABLE,    /** The notification for wakeup events is
                                enabled on the addressed transceiver.         */
  CANTRCV_WUMODE_CLEAR,     /** A stored wakeup event is cleared on the
                                addressed transceiver.                        */
  CANTRCV_WUMODE_DISABLE    /** The notification for wakeup events is
                                disabled on the addressed transceiver.        */
} CanTrcv_TrcvWakeupModeType;

/** \brief  Wakeup Reason of the CAN Transceiver Driver
 */
typedef enum
{
  CANTRCV_WU_ERROR,        /** Due to an error wake up reason was not detected.
                               This value may only be reported when error was
                               reported to DEM before.                        */
  CANTRCV_WU_BY_BUS,       /** The transceiver has detected, that the network
                               has caused the wake up of the ECU.             */
  CANTRCV_WU_BY_PIN,       /** The transceiver has detected a wake-up event at
                               one of the transceiver's pins (not at the CAN
                               bus).                                          */
  CANTRCV_WU_INTERNALLY,   /** The transceiver has detected, that the network
                               has woken up by the ECU via a request to NORMAL
                               mode.                                          */
  CANTRCV_WU_NOT_SUPPORTED,/** The transceiver does not support any information
                               for the wake up reason.                        */
  CANTRCV_WU_POWER_ON,     /** The transceiver has detected, that the "wake up"
                               is due to an ECU reset after power on.         */
  CANTRCV_WU_RESET,        /** The transceiver has detected, that the "wake up"
                               is due to an ECU reset.                        */
  CANTRCV_WU_BY_SYSERR     /** The transceiver has detected, that the wake up of
                               the ECU was caused by a HW related device
                               failure.                                       */
} CanTrcv_TrcvWakeupReasonType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#endif /* #ifndef CAN_GENERALTYPES_H */

