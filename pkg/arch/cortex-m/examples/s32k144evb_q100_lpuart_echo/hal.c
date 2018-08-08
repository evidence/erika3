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

extern void LPUART_DRV_IRQHandler(uint32_t instance);

/*
 * S32K SDK
 */

/*! @brief Count of peripheral clock user configurations */
#define NUM_OF_PERIPHERAL_CLOCKS_0 (8U)

peripheral_clock_config_t peripheralClockConfig0[NUM_OF_PERIPHERAL_CLOCKS_0] = {
    {
        .clockName        = LPUART0_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_SIRC_DIV1,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = LPUART1_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_SIRC_DIV1,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = LPUART2_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_SIRC_DIV1,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = PORTA_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = PORTB_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = PORTC_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = PORTD_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
    {
        .clockName        = PORTE_CLK,
        .clkGate          = true,
        .clkSrc           = CLK_SRC_OFF,
        .frac             = MULTIPLY_BY_ONE,
        .divider          = DIVIDE_BY_ONE,
    },
};

/* *************************************************************************
 * Configuration structure for Clock Configuration 0
 * ************************************************************************* */
/*! @brief User Configuration structure clockMan1_InitConfig0 */
clock_manager_user_config_t clockMan1_InitConfig0 = {
    /*! @brief Configuration of SIRC */
    .scgConfig =
    {
        .sircConfig =
        {
            .initialize       = true,                                /*!< Initialize */
            /* SIRCCSR */
            .enableInStop     = true,                                /*!< SIRCSTEN  */
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
            .prediv           = SCG_SPLL_CLOCK_PREDIV_BY_1,          /*!< PREDIV     */
            .mult             = SCG_SPLL_CLOCK_MULTIPLY_BY_28,       /*!< MULT       */
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
        .peripheralClocks = peripheralClockConfig0,                  /*!< Peripheral clock control configurations  */
        .count = NUM_OF_PERIPHERAL_CLOCKS_0,                         /*!< Number of the peripheral clock control configurations  */
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
    &clockMan1_InitConfig0
};

/*! \brief	Count of user Callbacks */
#define	CLOCK_MANAGER_CALLBACK_CNT	0U

/*! \brief	Array of pointers to User defined Callbacks configuration structures */
clock_manager_callback_user_config_t const * const
g_clockManCallbacksArr[] = {(void*)0};

/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS (7U)

/*! @brief Array of pin configuration structures */
pin_settings_config_t g_pin_mux_InitConfigArr[NUM_OF_CONFIGURED_PINS] =
{
    {
        .base          = PORTC,
        .pinPortIdx    = 7u,
        .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT2,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = NULL,
        .digitalFilter = false,
    },
    {
        .base          = PORTC,
        .pinPortIdx    = 6u,
        .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT2,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = NULL,
        .digitalFilter = false,
    },
    {
        .base          = PORTA,
        .pinPortIdx    = 10u,
        .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_HIGH_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT7,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = NULL,
        .digitalFilter = false,
    },
    {
        .base          = PORTC,
        .pinPortIdx    = 5u,
        .pullConfig    = PORT_INTERNAL_PULL_UP_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT7,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = NULL,
        .digitalFilter = false,
    },
    {
        .base          = PORTC,
        .pinPortIdx    = 4u,
        .pullConfig    = PORT_INTERNAL_PULL_DOWN_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT7,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = NULL,
        .digitalFilter = false,
    },
    {
        .base          = PORTA,
        .pinPortIdx    = 5u,
        .pullConfig    = PORT_INTERNAL_PULL_UP_ENABLED,
        .passiveFilter = true,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT7,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = NULL,
        .digitalFilter = false,
    },
    {
        .base          = PORTA,
        .pinPortIdx    = 4u,
        .pullConfig    = PORT_INTERNAL_PULL_UP_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT7,
        .pinLock       = false,
        .intConfig     = PORT_DMA_INT_DISABLED,
        .clearIntFlag  = false,
        .gpioBase      = NULL,
        .digitalFilter = false,
    }
};

/*! @brief Physical channel number for channel configuration #0 */
#define EDMA_CHN0_NUMBER   0U

/*! @brief The total number of configured channels */
#define EDMA_CONFIGURED_CHANNELS_COUNT   1U

edma_state_t dmaController1_State;

edma_chn_state_t dmaController1Chn0_State;

edma_chn_state_t * const edmaChnStateArray[] = {
    &dmaController1Chn0_State
};

edma_channel_config_t dmaController1Chn0_Config = {
    .channelPriority = EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN0_NUMBER,
    .source = EDMA_REQ_LPUART0_RX,
    .callback = NULL,
    .callbackParam = NULL
};

const edma_channel_config_t * const edmaChnConfigArray[] = {
    &dmaController1Chn0_Config
};

const edma_user_config_t dmaController1_InitConfig0 = {
  .chnArbitration = EDMA_ARBITRATION_FIXED_PRIORITY,
  .notHaltOnError = false,
};

/*! @brief Device instance number */
#define INST_LPUART1 (1U)

/*! lpuart1 configuration structure */
const lpuart_user_config_t lpuart1_InitConfig0 = {
  .transferType = LPUART_USING_INTERRUPTS,
  .baudRate = 115200U,
  .parityMode = LPUART_PARITY_DISABLED,
  .stopBitCount = LPUART_ONE_STOP_BIT,
  .bitCountPerChar = LPUART_8_BITS_PER_CHAR,
  .rxDMAChannel = 0U,
  .txDMAChannel = 0U,
};


/*! Driver state structure */
lpuart_state_t lpuart1_State;
#endif	/* OS_EE_LIB_S32_SDK */

FUNC(void, APPL_CODE) DemoHAL_Init( void )
{
#ifdef	OS_EE_LIB_S32_SDK
/* Initialize and configure clocks
 * - see clock manager component for details
 */
  CLOCK_SYS_Init((clock_manager_user_config_t const **)g_clockManConfigsArr,
    CLOCK_MANAGER_CONFIG_CNT,
    (clock_manager_callback_user_config_t **)g_clockManCallbacksArr,
    CLOCK_MANAGER_CALLBACK_CNT
  );

  CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

  /* Initialize pins
   *	-	See PinSettings component for more info
   */
  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
#endif /* OS_EE_LIB_S32_SDK */
}

FUNC(void, APPL_CODE) DemoHAL_MainFunction(void) {

}

/* Serial HAL */
FUNC(void, APPL_CODE) DemoHAL_SerialInit(void) {
#ifdef	OS_EE_LIB_S32_SDK
  /* Initialize LPUART instance */
  LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);
#endif
}


FUNC(void, APPL_CODE) DemoHAL_SerialWrite_Async(
  P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA) buffer,
  VAR(MemSize, AUTOMATIC)                   length
)
{
#ifdef	OS_EE_LIB_S32_SDK
  LPUART_DRV_SendData(INST_LPUART1, buffer, length);
#endif
}

FUNC(status_t, APPL_CODE) DemoHAL_SerialWrite_Status(
  void
)
{
#ifdef	OS_EE_LIB_S32_SDK
  uint32_t bytesRemaining;
  return LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemaining);
#endif
}

FUNC(void, APPL_CODE) DemoHAL_SerialWrite(
  P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA) buffer,
  VAR(MemSize, AUTOMATIC)                   length
)
{
#ifdef	OS_EE_LIB_S32_SDK
  DemoHAL_SerialWrite_Async(buffer, length);
  /* Wait for transfer to be completed */
  while (DemoHAL_SerialWrite_Status() != STATUS_SUCCESS);
#endif
}

FUNC(void, APPL_CODE) DemoHAL_SerialRead(
  P2VAR(uint8_t, AUTOMATIC, OS_APPL_DATA) buffer,
  VAR(MemSize, AUTOMATIC)                 length
)
{
#ifdef	OS_EE_LIB_S32_SDK
  uint32_t bytesRemaining;
  LPUART_DRV_ReceiveData(INST_LPUART1, buffer, length);
  /* Wait for transfer to be completed */
  while(LPUART_DRV_GetReceiveStatus(INST_LPUART1, &bytesRemaining) !=
    STATUS_SUCCESS);
#endif
}

FUNC(void, APPL_CODE) DemoHAL_SerialISRHandler(
  void
)
{
#ifdef	OS_EE_LIB_S32_SDK
  LPUART_DRV_IRQHandler(INST_LPUART1);
#endif
}