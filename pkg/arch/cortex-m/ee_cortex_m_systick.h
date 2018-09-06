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

/** \file	ee_cortex_m_systick.h
 *  \brief	SysTick system timer driver header file.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

#ifndef	OSEE_CORTEX_X_SYSTICK_H
#define	OSEE_CORTEX_X_SYSTICK_H

#include "ee_platform_types.h"
#include "ee_mcu_common_types.h"

#if (defined(__cplusplus))
extern "C" {
#endif

/* SysTick registers */

/** SysTick Control and Status */
#define	OSEE_CORTEX_X_SYSTICK_CTRL_R		OSEE_HWREG(0xE000E010U)
/** SysTick Reload value */
#define	OSEE_CORTEX_X_SYSTICK_RELOAD_R		OSEE_HWREG(0xE000E014U)
/**  SysTick Current value */
#define	OSEE_CORTEX_X_SYSTICK_CURRENT_R		OSEE_HWREG(0xE000E018U)
/**  SysTick Calibration value */
#define	OSEE_CORTEX_X_SYSTICK_CAL_R		OSEE_HWREG(0xE000E01CU)

/*
 * The following are defines for the bit fields in the
 * OSEE_CORTEX_X_SYSTICK_CTRL_R register.
 */

/** Count Flag */
#define	OSEE_CORTEX_X_SYSTICK_CTRL_COUNT	0x00010000U
/** Clock Source */
#define	OSEE_CORTEX_X_SYSTICK_CTRL_CLK_SRC	0x00000004U
/** Interrupt Enable */
#define	OSEE_CORTEX_X_SYSTICK_CTRL_INTEN	0x00000002U
/** Enable */
#define	OSEE_CORTEX_X_SYSTICK_CTRL_ENABLE	0x00000001U

/*
 * The following are defines for the bit fields in the
 * OSEE_CORTEX_X_SYSTICK_RELOAD_R register.
 */

/** Reload Value Mask and Shift-Bits */
#define	OSEE_CORTEX_X_SYSTICK_RELOAD_M		0x00FFFFFFU
#define	OSEE_CORTEX_X_SYSTICK_RELOAD_S		0U

/*
 * The following are defines for the bit fields in the
 * OSEE_CORTEX_X_SYSTICK_CURRENT_R register.
 */

/* Current Value Mask and Shift-Bits. */
#define	OSEE_CORTEX_X_SYSTICK_CURRENT_M	0x00FFFFFFU
#define	OSEE_CORTEX_X_SYSTICK_CURRENT_S	0U

/*
 * The following are defines for the bit fields in the
 * OSEE_CORTEX_X_SYSTICK_CAL_R register.
 */

/** No reference clock */
#define	OSEE_CORTEX_X_SYSTICK_CAL_NOREF		0x80000000U
/** Clock skew */
#define	OSEE_CORTEX_X_SYSTICK_CAL_SKEW		0x40000000U

/** 1ms reference value Mask and Shift-Bits. */
#define	OSEE_CORTEX_X_SYSTICK_CAL_ONEMS_M	0x00FFFFFFU
#define	OSEE_CORTEX_X_SYSTICK_CAL_ONEMS_S	0U

/** error value. No errors happened **/
#define	OSEE_CORTEX_X_SYSTICK_NO_ERRORS		0U
/** error value. Wrong funtion arguments values **/
#define	OSEE_CORTEX_X_SYSTICK_ERR_BAD_ARGS	1U

/** \brief	Start SysTick.
 *
 *  This will start the SysTick counter.
 *
 *  If an ISR has been defined, it is called when the SysTick counter rolls
 *  over.
 *
 *  \note	Calling this function will cause the SysTick counter to
 *  		(re)commence counting from its current value.
 *  		The counter is not automatically reloaded  with the period as
 *  		specified in a previous call to
 *  		\b osEE_cortex_m_systick_set_period().
 *  		If an immediate reload is required, the
 *  		\b OSEE_CORTEX_X_SYSTICK_CURRENT register must be written
 *  		to force this. 
 *  		Any write to this register clears the SysTick counter to 0 and
 *  		will cause a reload with the supplied period on the next clock.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_start(
  void
) {
  OSEE_CORTEX_X_SYSTICK_CTRL_R |= (
    OSEE_CORTEX_X_SYSTICK_CTRL_CLK_SRC | OSEE_CORTEX_X_SYSTICK_CTRL_ENABLE
  );
}

/** \brief	Stop SysTick.
 *
 *  This will stop the SysTick counter.
 *
 *  If an ISR has been defined, it will no longer be called until SysTick is
 *  restarted.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_stop(
  void
) {
  OSEE_CORTEX_X_SYSTICK_CTRL_R &= ~(OSEE_CORTEX_X_SYSTICK_CTRL_ENABLE);
}

/** \brief	Enables the SysTick interrupt.
 *
 *  This function will enable the SysTick interrupt, allowing it to be
 *  reflected to the processor.
 *
 *  \note	The SysTick ISR does not need to clear the SysTick interrupt
 *  		source as this is done automatically by NVIC when the interrupt
 *  		ISR is called.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_enable_int(
  void
) {
  OSEE_CORTEX_X_SYSTICK_CTRL_R |= OSEE_CORTEX_X_SYSTICK_CTRL_INTEN;
}

/** \brief	Disables the SysTick interrupt.
 *
 *  This function will disable the SysTick interrupt, preventing it from being
 *  reflected to the processor.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_disable_int(
  void
) {
  OSEE_CORTEX_X_SYSTICK_CTRL_R &= ~(OSEE_CORTEX_X_SYSTICK_CTRL_INTEN);
}

/** \brief	Sets the period of the SysTick counter.
 *  \param	period is the number of clock ticks in each period of the
 *  		SysTick counter; must be between 1 and 16,777,216, inclusive.
 *  \return	- \b OSEE_CORTEX_X_SYSTICK_ERR_BAD_ARGS:
 *  		     If the \e period is out of range
 *  		- \b OSEE_CORTEX_X_SYSTICK_NO_ERRORS:
 *  		     If the \e period is not out of range
 *
 *  This function sets the rate at which the SysTick counter wraps;
 *  this equates to the number of processor clocks between interrupts.
 *
 *  \note	Calling this function does not cause the SysTick counter to
 *  		reload immediately.
 *  		If an immediate reload is required, the
 *  		\b OSEE_CORTEX_X_SYSTICK_CURRENT register must be written.
 *  		Any write to this register clears the SysTick  counter to 0 and
 *  		will cause a reload with the \e period supplied here on the next
 *  		clock after the SysTick is enabled.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_set_period(
  VAR(OsEE_reg, AUTOMATIC) period
)
{
  if (
    (period != OSEE_CORTEX_X_SYSTICK_RELOAD_S) &&
    (period <= OSEE_CORTEX_X_SYSTICK_RELOAD_M)
  ) {
    OSEE_CORTEX_X_SYSTICK_RELOAD_R = ( period - 1 );
  }
}

/** \brief	Gets the period of the SysTick counter.
 *  \return	Returns the period of the SysTick counter.
 *
 *  This function returns the rate at which the SysTick counter wraps;
 *  this equates to the number of processor clocks between interrupts.
 */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_get_period(
  void
) {
  return ( OSEE_CORTEX_X_SYSTICK_RELOAD_R + 1 );
}

/** @brief	Gets the current value of the SysTick counter.
 *  @return	Returns the current value of the SysTick counter.
 *
 *  This function returns the current value of the SysTick counter; this will
 *  be a value between the period - 1 and zero, inclusive.
 */
OSEE_STATIC_INLINE FUNC(OsEE_reg, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_get_value(
  void
) {
  return OSEE_CORTEX_X_SYSTICK_CURRENT_R;
}

/** Default Clock Frequency (Hz) */
#define	OSEE_CORTEX_X_DEFAULT_CPU_CLOCK	16000000U

/** \brief	Delay with SysTick .
 *  \param	usDelay	Number of us to Delay.
 *
 *  This function delays the program execution by \b usDelay microseconds.
 */
OSEE_STATIC_INLINE FUNC(void, OS_CODE) OSEE_ALWAYS_INLINE
osEE_cortex_m_systick_delay_us(
  VAR(OsEE_reg, AUTOMATIC) usDelay
) {
  CONST(OsEE_reg, AUTOMATIC) start = osEE_cortex_m_systick_get_value();
#ifdef	OSEE_CPU_CLOCK
  VAR(OsEE_reg, AUTOMATIC) ticks =
  OSEE_MICRO_TO_TICKS(usDelay, OSEE_CPU_CLOCK);
#else	/* OSEE_CPU_CLOCK */
  VAR(OsEE_reg, AUTOMATIC) ticks =
  OSEE_MICRO_TO_TICKS(usDelay, OSEE_CORTEX_X_DEFAULT_CPU_CLOCK);
#endif	/* OSEE_CPU_CLOCK */
  /* Bound the delay to max one whole run */
  if (
    (ticks == OSEE_CORTEX_X_SYSTICK_RELOAD_S) ||
    (ticks > OSEE_CORTEX_X_SYSTICK_RELOAD_M)
  ) {
    ticks = ( OSEE_CORTEX_X_SYSTICK_RELOAD_M - 1 );
  }

  while (
    (
      (osEE_cortex_m_systick_get_value() - start) &
      OSEE_CORTEX_X_SYSTICK_RELOAD_M
    ) < ticks
  ){
    ; /* wait */
  }
}

#if (defined(__cplusplus))
}
#endif

#endif	/* OSEE_CORTEX_X_SYSTICK_H */
