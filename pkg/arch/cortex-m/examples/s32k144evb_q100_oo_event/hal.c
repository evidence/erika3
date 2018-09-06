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

/** \file	hal.c
 *  \brief	Hardware Abstraction Layer Sources.
 *
 *  This file contains the sources of the HAL for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* Header */
#include "hal.h"

#ifdef	OS_EE_LIB_S32_SDK
/*
 * S32K SDK
 */
#include "device_registers.h"
#include "clock_manager.h"
#include "interrupt_manager.h"
#include "pins_driver.h"
#include "ftm_ic_driver.h"
#include "ftm_mc_driver.h"
#include "ftm_qd_driver.h"
#include "ftm_oc_driver.h"
#include "ftm_pwm_driver.h"
#include "system_S32K144.h"

/*! @brief Count of peripheral clock user configurations */
#define	NUM_OF_PERIPHERAL_CLOCKS	3U

/*! \brief peripheral clock configuration */
peripheral_clock_config_t const
peripheralClockConfig[NUM_OF_PERIPHERAL_CLOCKS] = {
    {
        .clockName        = PCC_PORTC_CLOCK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = PCC_PORTD_CLOCK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = PCC_FTM0_CLOCK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
};

/*! \brief	User Configuration structure clockMan_InitConfig */
clock_manager_user_config_t const
clockMan_InitConfig = {
    /*! @brief Configuration of SIRC */
    .scgConfig =
    {
        .sircConfig =
        {
            .initialize       = true,                                /*!< Initialize */
            /* SIRCCSR */
            .enableInStop     = false,                               /*!< SIRCSTEN  */
            .enableInLowPower = true,                                /*!< SIRCLPEN  */
            .locked           = false,                               /*!< LK        */
            /* SIRCCFG */
            .range            = SCG_SIRC_RANGE_HIGH,                 /*!< RANGE - High range (8 MHz) */
            /* SIRCDIV */
            .div1             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< SIRCDIV1  */
            .div2             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< SIRCDIV2  */
        },
        .fircConfig =
        {
            .initialize       = true,                                /*!< Initialize */
            /* FIRCCSR */
            .regulator        = true,                                /*!< FIRCREGOFF */
            .locked           = false,                               /*!< LK         */
            /* FIRCCFG */
            .range            = SCG_FIRC_RANGE_48M,                  /*!< RANGE      */
            /* FIRCDIV */
            .div1             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< FIRCDIV1   */
            .div2             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< FIRCDIV2   */
        },
        .rtcConfig =
        {
            .initialize       = true,                                /*!< Initialize  */
            .rtcClkInFreq     = 0U,                                  /*!< RTC_CLKIN   */
        },
        .soscConfig =
        {
            .initialize       = true,                                /*!< Initialize */
            .freq             = 8000000U,                            /*!< Frequency  */
            /* SOSCCSR */
            .monitorMode      = SCG_SOSC_MONITOR_DISABLE,            /*!< SOSCCM      */
            .locked           = false,                               /*!< LK          */
            /* SOSCCFG */
            .extRef           = SCG_SOSC_REF_OSC,                    /*!< EREFS       */
            .gain             = SCG_SOSC_GAIN_LOW,                   /*!< HGO         */
            .range            = SCG_SOSC_RANGE_MID,                  /*!< RANGE       */
            /* SOSCDIV */
            .div1             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< SOSCDIV1    */
            .div2             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< SOSCDIV2    */
        },
        .spllConfig =
        {
            .initialize       = true,                                /*!< Initialize */
            /* SPLLCSR */
            .monitorMode      = SCG_SPLL_MONITOR_DISABLE,            /*!< SPLLCM     */
            .locked           = false,                               /*!< LK         */
            /* SPLLCFG */
            .prediv           = 0U,                                  /*!< PREDIV     */
            .mult             = 12U,                                 /*!< MULT       */
            .src              = 0U,                                  /*!< SOURCE     */
            /* SPLLDIV */
            .div1             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< SPLLDIV1   */
            .div2             = SCG_ASYNC_CLOCK_DIV_BY_1,            /*!< SPLLDIV2   */
        },
        .clockOutConfig =
        {
            .initialize       = true,                                /*!< Initialize    */
            .source           = SCG_CLOCKOUT_SRC_FIRC,               /*!< SCG CLKOUTSEL     */
        },
        .clockModeConfig =
        {
            .initialize       = true,                                /*!< Initialize */
            .rccrConfig =              /*!< RCCR - Run Clock Control Register          */
            {
                .src          = SCG_SYSTEM_CLOCK_SRC_FIRC,           /*!< SCS        */
                .divCore      = SCG_SYSTEM_CLOCK_DIV_BY_1,           /*!< DIVCORE    */
                .divBus       = SCG_SYSTEM_CLOCK_DIV_BY_2,           /*!< DIVBUS     */
                .divSlow      = SCG_SYSTEM_CLOCK_DIV_BY_2,           /*!< DIVSLOW    */
            },
            .vccrConfig =              /*!< VCCR - VLPR Clock Control Register         */
            {
                .src          = SCG_SYSTEM_CLOCK_SRC_SIRC,           /*!< SCS        */
                .divCore      = SCG_SYSTEM_CLOCK_DIV_BY_2,           /*!< DIVCORE    */
                .divBus       = SCG_SYSTEM_CLOCK_DIV_BY_1,           /*!< DIVBUS     */
                .divSlow      = SCG_SYSTEM_CLOCK_DIV_BY_4,           /*!< DIVSLOW    */
            },
            .hccrConfig =              /*!< HCCR - HSRUN Clock Control Register        */
            {
                .src          = SCG_SYSTEM_CLOCK_SRC_SYS_PLL,        /*!< SCS        */
                .divCore      = SCG_SYSTEM_CLOCK_DIV_BY_1,           /*!< DIVCORE    */
                .divBus       = SCG_SYSTEM_CLOCK_DIV_BY_2,           /*!< DIVBUS     */
                .divSlow      = SCG_SYSTEM_CLOCK_DIV_BY_4,           /*!< DIVSLOW    */
            },
        },
    },
    .pccConfig =
    {
        .peripheralClocks = (peripheral_clock_config_t*) peripheralClockConfig, /*!< Peripheral clock control configurations  */
        .count = NUM_OF_PERIPHERAL_CLOCKS,                                      /*!< Number of the peripheral clock control configurations  */
    },
    .simConfig =
    {
        .clockOutConfig =              /*!< Clock Out configuration.           */
        {
            .initialize       = true,                                /*!< Initialize    */
            .enable           = false,                               /*!< CLKOUTEN      */
            .source           = SIM_CLKOUT_SEL_SYSTEM_SCG_CLKOUT,    /*!< CLKOUTSEL     */
            .divider          = SIM_CLKOUT_DIV_BY_1,                 /*!< CLKOUTDIV     */
        },
        .lpoClockConfig =              /*!< Low Power Clock configuration.     */
        {
            .initialize       = true,                                /*!< Initialize    */
            .enableLpo1k      = true,                                /*!< LPO1KCLKEN    */
            .enableLpo32k     = true,                                /*!< LPO32KCLKEN   */
            .sourceLpoClk     = SIM_LPO_CLK_SEL_LPO_128K,            /*!< LPOCLKSEL     */
            .sourceRtcClk     = SIM_RTCCLK_SEL_SOSCDIV1_CLK,         /*!< RTCCLKSEL     */
        },
        .platGateConfig =              /*!< Platform Gate Clock configuration. */
        {
            .initialize       = true,                                /*!< Initialize    */
            .enableMscm       = true,                                /*!< CGCMSCM       */
            .enableMpu        = true,                                /*!< CGCMPU        */
            .enableDma        = true,                                /*!< CGCDMA        */
            .enableErm        = true,                                /*!< CGCERM        */
            .enableEim        = true,                                /*!< CGCEIM        */
        },

        .qspiRefClkGating =            /*!< Quad Spi Internal Reference Clock Gating. */
        {
            .enableQspiRefClk  = false,                              /*!< Qspi reference clock gating    */
        },
        .tclkConfig =                  /*!< TCLK CLOCK configuration. */
        {
            .initialize       = true,                                /*!< Initialize    */
            .tclkFreq[0]      = 0U,                                  /*!< TCLK0         */
            .tclkFreq[1]      = 0U,                                  /*!< TCLK1         */
            .tclkFreq[2]      = 0U,                                  /*!< TCLK2         */
        },
        .traceClockConfig =            /*!< Debug trace Clock Configuration. */
        {
            .initialize       = true,                                /*!< Initialize    */
            .divEnable        = true,                                /*!< TRACEDIVEN    */
            .source           = CLOCK_TRACE_SRC_CORE_CLK,            /*!< TRACECLK_SEL  */
            .divider          = 0U,                                  /*!< TRACEDIV      */
            .divFraction      = false,                               /*!< TRACEFRAC     */
        },
    },
    .pmcConfig =
    {
        .lpoClockConfig =              /*!< Low Power Clock configuration.     */
        {
            .initialize       = true,                                /*!< Initialize             */
            .enable           = true,                                /*!< Enable/disable LPO     */
            .trimValue        = 0,                                   /*!< Trimming value for LPO */
        },
    },
};

/*! \brief	Count of user configuration structures */
#define	CLOCK_MANAGER_CONFIG_CNT	1U

/*! \brief	Array of pointers to User configuration structures */
clock_manager_user_config_t const * const
g_clockManConfigsArr[] = {
    &clockMan_InitConfig
};

/*! \brief	Count of user Callbacks */
#define	CLOCK_MANAGER_CALLBACK_CNT	0U

/*! \brief	Array of pointers to User defined Callbacks configuration structures */
clock_manager_callback_user_config_t const * const
g_clockManCallbacksArr[] = {(void*)0};

/*! \brief User number of configured pins */
#define	NUM_OF_CONFIGURED_PINS		5U

/*! @brief Array of pin configuration structures */
const pin_settings_config_t g_pin_mux_InitConfigArr[NUM_OF_CONFIGURED_PINS] = {
    {
           .base          = PORTC,
           .pinPortIdx    = 12u,
           .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
           .passiveFilter = false,
           .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
           .mux           = PORT_MUX_AS_GPIO,
           .pinLock       = false,
           .intConfig     = PORT_DMA_INT_DISABLED,
           .clearIntFlag  = false,
           .gpioBase      = PTC,
           .direction     = GPIO_INPUT_DIRECTION,
    },
    {
           .base          = PORTC,
           .pinPortIdx    = 13u,
           .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
           .passiveFilter = false,
           .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
           .mux           = PORT_MUX_AS_GPIO,
           .pinLock       = false,
           .intConfig     = PORT_DMA_INT_DISABLED,
           .gpioBase      = PTC,
           .direction     = GPIO_INPUT_DIRECTION,
    },
    {
           .base          = PORTD,
           .pinPortIdx    = 0u,
           .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
           .passiveFilter = false,
           .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
           .mux           = PORT_MUX_AS_GPIO,
           .pinLock       = false,
           .intConfig     = PORT_DMA_INT_DISABLED,
           .clearIntFlag  = false,
           .gpioBase      = PTD,
           .direction     = GPIO_OUTPUT_DIRECTION,
    },
    {
           .base          = PORTD,
           .pinPortIdx    = 15u,
           .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
           .passiveFilter = false,
           .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
           .mux           = PORT_MUX_AS_GPIO,
           .pinLock       = false,
           .intConfig     = PORT_DMA_INT_DISABLED,
           .clearIntFlag  = false,
           .gpioBase      = PTD,
           .direction     = GPIO_OUTPUT_DIRECTION,
    },
    {
           .base          = PORTD,
           .pinPortIdx    = 16u,
           .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
           .passiveFilter = false,
           .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
           .mux           = PORT_MUX_AS_GPIO,
           .pinLock       = false,
           .intConfig     = PORT_DMA_INT_DISABLED,
           .clearIntFlag  = false,
           .gpioBase      = PTD,
           .direction     = GPIO_OUTPUT_DIRECTION,
    },
};
#endif	/* OS_EE_LIB_S32_SDK */

FUNC(void, APPL_CODE) DemoHAL_Init( void )
{
#ifdef	OS_EE_LIB_S32_SDK
	/* Initialize and configure clocks
	 * 	-	see clock manager component for details
	 */
	CLOCK_SYS_Init(
		(clock_manager_user_config_t const **)g_clockManConfigsArr,
		CLOCK_MANAGER_CONFIG_CNT,
		(clock_manager_callback_user_config_t **)g_clockManCallbacksArr,
		CLOCK_MANAGER_CALLBACK_CNT
	);
	CLOCK_SYS_UpdateConfiguration(
		0U,
		CLOCK_MANAGER_POLICY_AGREEMENT
	);

	/* Initialize pins
	 *	-	See PinSettings component for more info
	 */
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
#endif	/* OS_EE_LIB_S32_SDK */

	DemoHAL_LedInit();
}

#ifdef	OS_EE_LIB_S32_SDK
/**
  * @brief  Inserts a delay time.
  * @param  interval: specifies the delay time length, in milliseconds.
  * @retval None
  */
static FUNC(void, APPL_CODE) HAL_Delay(
	VAR(MemSize, AUTOMATIC)	interval
)
{
	volatile VAR(MemSize, AUTOMATIC) TimingDelay = interval;

	while(--TimingDelay != 0U);
}
#endif	/* OS_EE_LIB_S32_SDK */

FUNC(void, APPL_CODE) DemoHAL_Delay(
	VAR(MemSize, AUTOMATIC)	interval
)
{
	HAL_Delay(interval*1024*10);
}

FUNC(void, APPL_CODE) DemoHAL_MainFunction( void ) {}

/* Leds HAL */
#ifdef	OS_EE_LIB_S32_SDK
#define	LED_PORT	PORTD
#define	LED_GPIO_PORT	PTD
#define	PCC_CLOCK	PCC_PORTD_CLOCK
#define	LED0		15U
#define	LED1		16U
#define	LED2		0U
#endif	/* OS_EE_LIB_S32_SDK */

FUNC(void, APPL_CODE) DemoHAL_LedInit( void )
{
#ifdef	OS_EE_LIB_S32_SDK
	PINS_DRV_SetPinsDirection(
		LED_GPIO_PORT,
		((1 << LED0) | (1 << LED1) | (1 << LED2))
	);
	
	PINS_DRV_SetPins(
		LED_GPIO_PORT,
		((1 << LED0) | (1 << LED1) | (1 << LED2))
	);
	
#endif	/* OS_EE_LIB_S32_SDK */
}

FUNC(void, APPL_CODE) DemoHAL_LedOn(
	VAR(DemoHAL_Led, AUTOMATIC)				led
)
{
	switch (led) {
	case DEMO_HAL_LED_0:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_WritePin(LED_GPIO_PORT, LED0, 0U);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_1:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_WritePin(LED_GPIO_PORT, LED1, 0U);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_2:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_WritePin(LED_GPIO_PORT, LED2, 0U);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_3:
	case DEMO_HAL_LED_4:
	case DEMO_HAL_LED_5:
	case DEMO_HAL_LED_6:
	case DEMO_HAL_LED_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_LedOff(
	VAR(DemoHAL_Led, AUTOMATIC)	led
)
{
	switch (led) {
	case DEMO_HAL_LED_0:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_WritePin(LED_GPIO_PORT, LED0, 1U);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_1:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_WritePin(LED_GPIO_PORT, LED1, 1U);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_2:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_WritePin(LED_GPIO_PORT, LED2, 1U);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_3:
	case DEMO_HAL_LED_4:
	case DEMO_HAL_LED_5:
	case DEMO_HAL_LED_6:
	case DEMO_HAL_LED_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_LedToggle(
	VAR(DemoHAL_Led, AUTOMATIC)				led
)
{
	switch (led) {
	case DEMO_HAL_LED_0:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_TogglePins(LED_GPIO_PORT, (1 << LED0));
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_1:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_TogglePins(LED_GPIO_PORT, (1 << LED1));
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_2:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_TogglePins(LED_GPIO_PORT, (1 << LED2));
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_LED_3:
	case DEMO_HAL_LED_4:
	case DEMO_HAL_LED_5:
	case DEMO_HAL_LED_6:
	case DEMO_HAL_LED_7:
	default:
		break;
	}
}

/* Buttons HAL */
#ifdef	OS_EE_LIB_S32_SDK
#define	BUTTON_PORT		PORTC
#define	BUTTON_GPIO_PORT	PTC
#define	BUTTON0			12U
#define	BUTTON1			13U

extern FUNC(void, OS_CODE) OSEE_NAKED (PORTC_IRQHandler)( void );
#endif	/* OS_EE_LIB_S32_SDK */

FUNC(void, APPL_CODE) DemoHAL_ButtonInit( void )
{
#ifdef	OS_EE_LIB_S32_SDK
	PINS_DRV_SetPinsDirection(
		BUTTON_GPIO_PORT, (~(1U << BUTTON0) & ~(1U << BUTTON1))
	);
#endif	/* OS_EE_LIB_S32_SDK */
}

FUNC(OsEE_bool, APPL_CODE) DemoHAL_ButtonRead(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	VAR(OsEE_bool, AUTOMATIC)		value = 0U;
#ifdef	OS_EE_LIB_S32_SDK
	VAR(pins_channel_type_t, AUTOMATIC)	channel_value =
					PINS_DRV_ReadPins(BUTTON_GPIO_PORT);
#endif	/* OS_EE_LIB_S32_SDK */
	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_S32_SDK
		value = ((channel_value & (1 << BUTTON0)) >> BUTTON0);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_S32_SDK
		value = ((channel_value & (1 << BUTTON1)) >> BUTTON1);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
	return !value;
}

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptEnable(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_SetPinIntSel(
			BUTTON_PORT, BUTTON0, PORT_INT_RISING_EDGE
		);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_SetPinIntSel(
			BUTTON_PORT, BUTTON1, PORT_INT_FALLING_EDGE
		);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptDisable(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_SetPinIntSel(
			BUTTON_PORT, BUTTON0, PORT_DMA_INT_DISABLED
		);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_S32_SDK
		PINS_DRV_SetPinIntSel(
			BUTTON_PORT, BUTTON1, PORT_DMA_INT_DISABLED
		);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptAck(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_S32_SDK
		/* Clear interrupt flag */
		PINS_DRV_ClearPinIntFlagCmd(BUTTON_PORT, BUTTON0);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_S32_SDK
		/* Clear interrupt flag */
		PINS_DRV_ClearPinIntFlagCmd(BUTTON_PORT, BUTTON1);
#endif	/* OS_EE_LIB_S32_SDK */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
}

/* Timer HAL */
#ifdef	OS_EE_LIB_S32_SDK
/*! @brief Device instance number */
#define INST_FLEXTIMER1 0U

/* Write your local variable definition here */
ftm_state_t ftmStateStruct;

/* Timer mode configuration for flexTimer1 */
ftm_timer_param_t flexTimer1_TimerConfig =
{
    FTM_MODE_UP_TIMER, /* counter mode */
    0U, /* Initial counter value */
    37500U, /* Final counter value */
};
/* Global configuration of flexTimer1 */
ftm_user_config_t const flexTimer1_InitConfig =
{
    {
        false,   /* Software trigger state */
        false,  /* Hardware trigger 1 state */
        false,  /* Hardware trigger 2 state */
        false,  /* Hardware trigger 3 state */
        false, /* Max loading point state */
        false, /* Min loading point state */
        FTM_SYSTEM_CLOCK, /* Update mode for INVCTRL register */
        FTM_SYSTEM_CLOCK, /* Update mode for SWOCTRL register */
        FTM_SYSTEM_CLOCK, /* Update mode for OUTMASK register */
        FTM_SYSTEM_CLOCK, /* Update mode for CNTIN register */
        false, /* Automatic clear of the trigger*/
        FTM_UPDATE_NOW, /* Synchronization point */
    },
     FTM_MODE_UP_TIMER, /*!< Mode of operation for FTM */
     FTM_CLOCK_DIVID_BY_128, /* FTM clock prescaler */
     FTM_CLOCK_SOURCE_SYSTEMCLK,   /* FTM clock source */
     FTM_BDM_MODE_00, /* FTM debug mode */
     true, /* Interrupt state */
     false /* Initialization trigger */
};
#endif	/* OS_EE_LIB_S32_SDK */

FUNC(void, APPL_CODE) DemoHAL_TimerInit( VAR(MemSize, AUTOMATIC) period )
{
#ifdef	OS_EE_LIB_S32_SDK
	/* Initialize Flex Timer instance as simple timer */
	FTM_DRV_Init(INST_FLEXTIMER1, &flexTimer1_InitConfig, &ftmStateStruct);
	/* Setup the counter to trigger an interrupt every 1 ms */
	flexTimer1_TimerConfig.finalValue = 375*period;
	FTM_DRV_InitCounter(INST_FLEXTIMER1, &flexTimer1_TimerConfig);
	/* Start the counter */
	FTM_DRV_CounterStart(INST_FLEXTIMER1);
#endif	/* OS_EE_LIB_S32_SDK */
}

FUNC(void, APPL_CODE) DemoHAL_TimerDelay( VAR(MemSize, AUTOMATIC) interval )
{ (void)interval; }

FUNC(void, APPL_CODE) DemoHAL_TimerAck( void )
{
#ifdef	OS_EE_LIB_S32_SDK
#ifdef	OS_EE_LIB_S32_SDK_0_8_6_EAR
	/* Clear FTM Timer Overflow flag */
	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER1, FTM_TIME_OVER_FLOW_FLAG);
#else	/* OS_EE_LIB_S32_SDK_0_8_6_EAR */
	/* Clear FTM Timer Overflow flag */
	FTM_DRV_ClearTimerOverflow(g_ftmBase[INST_FLEXTIMER1]);
#endif	/* OS_EE_LIB_S32_SDK_0_8_6_EAR */
#endif	/* OS_EE_LIB_S32_SDK */
}

/* Serial HAL */

FUNC(void, APPL_CODE) DemoHAL_SerialInit( void ) {}

FUNC(void, APPL_CODE) DemoHAL_SerialWrite(
	P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA)	buffer,
	VAR(MemSize, AUTOMATIC)						length
) { (void)buffer; (void)length;}
