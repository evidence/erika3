/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_tegraX1_pinmux.h
 *  \brief  Pinmux support for TegraX1.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */

#if (!defined(OSEE_TEGRAX1_PINMUX))
#define OSEE_TEGRAX1_PINMUX

/*==============================================================================
                                   PIN IDs
 =============================================================================*/

/* Pin Port C 0..4 */
#define TEGRAX1_PIN_SPI1_MOSI   (16U)
#define TEGRAX1_PIN_SPI1_MISO   (17U)
#define TEGRAX1_PIN_SPI1_SCK    (18U)
#define TEGRAX1_PIN_SPI1_CS0    (19U)
#define TEGRAX1_PIN_SPI1_CS1    (20U)

/*==============================================================================
                                     GPIO
 =============================================================================*/

#define TEGRAX1_GPIO_BASE_ADDR (0x6000D000U)
#define TEGRAX1_GPIO_CTRL_SIZE (0x100U)

/* TegraX1 GPIO registers offsets
TEGRAX1_GPIO_CNF_[0/1/2/3]           000 004 008 00C
TEGRAX1_GPIO_CNF_MSK_[0/1/2/3]       080 084 088 08C
TEGRAX1_GPIO_OE_[0/1/2/3]            010 014 018 01C
TEGRAX1_GPIO_OE_MSK_[0/1/2/3]        090 094 098 09C
TEGRAX1_GPIO_OUT_[0/1/2/3]           020 024 028 02C
TEGRAX1_GPIO_OUT_MSK_[0/1/2/3]       0A0 0A4 0A8 0AC
TEGRAX1_GPIO_IN_[0/1/2/3]            030 034 038 03C
TEGRAX1_GPIO_INT_STA_[0/1/2/3]       040 044 048 04C
TEGRAX1_GPIO_MSK_INT_STA_[0/1/2/3]   0C0 0C4 0C8 0CC
TEGRAX1_GPIO_INT_ENB_[0/1/2/3]       050 054 058 05C
TEGRAX1_GPIO_MSK_INT_ENB_[0/1/2/3]   0D0 0D4 0D8 0DC
TEGRAX1_GPIO_INT_LVL_[0/1/2/3]       060 064 068 06C
TEGRAX1_GPIO_MSK_INT_LVL_[0/1/2/3]   0E0 0E4 0E8 0EC
TEGRAX1_GPIO_INT_CLR_[0/1/2/3]       070 074 078 07C
TEGRAX1_GPIO_DB_CTRL_[P0/P1/P2/P3]_0 0B0 0B4 0B8 0BC
*/

/* Each controller 32 bit */
#define TEGRAX1_GPIO_MODULE(pin)    ((pin) / 32U)
#define TEGRAX1_GPIO_PORT(pin)      ((((pin) % 32U)/(8U)) * 4U)
#define TEGRAX1_GPIO_MSK(byte,pin)  \
  ((1U << ((pin) % 8U)) << (8U * ((byte) & 0x3U)))

#define TEGRAX1_GPIO_CNF          (0x00U)
#define TEGRAX1_GPIO_CNF_MSK      (0x80U)
#define TEGRAX1_GPIO_OE           (0x10U)
#define TEGRAX1_GPIO_OE_MSK       (0x90U)
#define TEGRAX1_GPIO_OUT          (0x20U)
#define TEGRAX1_GPIO_OUT_MSK      (0xA0U)
#define TEGRAX1_GPIO_IN           (0x30U)
#define TEGRAX1_GPIO_INT_STA      (0x40U)
#define TEGRAX1_GPIO_INT_STA_MSK  (0xC0U)
#define TEGRAX1_GPIO_INT_ENB      (0x50U)
#define TEGRAX1_GPIO_INT_ENB_MSK  (0xD0U)
#define TEGRAX1_GPIO_INT_LVL      (0x60U)
#define TEGRAX1_GPIO_INT_LVL_MSK  (0x0EU)
#define TEGRAX1_GPIO_INT_CLR      (0x070)
#define TEGRAX1_GPIO_DB_CTRL      (0x0B0)

#define TEGRAX1_GPIO_REG_ADDR(type, reg, pin)             \
  (type volatile *)(TEGRAX1_GPIO_BASE_ADDR +              \
    (TEGRAX1_GPIO_MODULE(pin) * TEGRAX1_GPIO_CTRL_SIZE) + \
    (reg) + TEGRAX1_GPIO_PORT(pin))

/*==============================================================================
                                GPIO Port IRQs
 =============================================================================*/

/* GIC GPIO0 IRQ Num EGRA X1 | TRM | DP-07225-001_v1.1p Table 8 */
#define TEGRAX1_GPIO0_IRQ       (32U + OSEE_GIC_MIN_SPI_ID)

/*==============================================================================
                                  PINMUX AUX
 =============================================================================*/
/* PINMUX_AUX is a submodule of MISC at offset 0x3000U.
   This offset is already, took in account by PINMU registers offset.
   (see TegraX1 TRM from pag. 274) */
#define TEGRAX1_MISC_BASE_ADDR (0x70000000U)

#define OSEE_ONES(num)                      ((1U << (num + 1U)) - 1U)
#define OSEE_B_MASK(length, lower_bit)      (OSEE_ONES(length) << (lower_bit))
#define OSEE_B_GET(x, length, lower_bit)    \
  ((x) & OSEE_B_MASK(length, lower_bit))
#define OSEE_B_CLEAR(x, length, lower_bit)  \
  ((x) & (~OSEE_B_MASK(length, lower_bit)))
#define OSEE_B_SET(x, length, lower_bit, v) \
  (OSEE_B_CLEAR(x,length,lower_bit) | ((v & OSEE_ONES(length)) << (lower_bit)))


/* Range Bitmasks. r is a bit range with this syntax h:l.
   It is a trick that uses ternary operator */
#define OSEE_R_LOW(r)     (0?r)
#define OSEE_R_HIGH(r)    (1?r)
#define OSEE_R_LENGTH(r)  (OSEE_R_HIGH(r) - OSEE_R_LOW(r))
#define OSEE_R_MASK(r)    OSEE_B_MASK(OSEE_R_LENGTH(r), OSEE_R_LOW(r))
#define OSEE_R_GET(x,r)   OSEE_B_GET(x, OSEE_R_LENGTH(r), OSEE_R_LOW(r))
#define OSEE_R_CLEAR(x,r) OSEE_B_CLEAR(x, OSEE_R_LENGTH(r), OSEE_R_LOW(r))
#define OSEE_R_SET(x,r,v) OSEE_B_SET(x, OSEE_R_LENGTH(r), OSEE_R_LOW(r), v)

/* Bitmask defines for PINMUX registers */
/* Bit  15 E_PREEMP:
  0 = DISABLE
  1 = ENABLE */
/* (((x) & 1U) << 15U) */
#define TEGRAX1_PINMUX_R_E_PREEMP     15:15
/* Bits 14:13 DRV_TYPE:
  0 = DRIVE_1X
  1 = DRIVE_2X
  2 = DRIVE_3X
  3 = DRIVE_4X */
/* (((x) & 3U) << 13U) */
#define TEGRAX1_PINMUX_R_DRV_TYPE     14:13
/* Bit 12 DISABLE E_SCHMT:
  0 = DISABLE
  1 = ENABLE */
/* (((x) & 1U) << 12U) */
#define TEGRAX1_PINMUX_R_E_SCHMT      12:12
/* Bit 9 DISABLE E_HSM:
  0 = DISABLE
  1 = ENABLE */
/*  (((x) & 1U) << 9U) */
#define TEGRAX1_PINMUX_R_E_HSM        9:9
/* Bit 7 LOCK:
  0 = DISABLE
  1 = ENABLE */
#define TEGRAX1_PINMUX_R_LOCK         7:7
/* Bit 6 E_INPUT:
  0 = DISABLE
  1 = ENABLE  */
#define TEGRAX1_PINMUX_R_E_INPUT      6:6
/* Bit 5 PARK:
  0 = NORMAL
  1 = PARKED */
#define TEGRAX1_PINMUX_R_PARK         5:5
/* Bit 4 TRISTATE:
  0 = PASSTHROUGH
  1 = TRISTATE */
#define TEGRAX1_PINMUX_R_TRISTATE     4:4
/* Bits 3:2 PUPD:
  0 = NONE
  1 = PULL_DOWN
  2 = PULL_UP
  3 = RSVD */
#define TEGRAX1_PINMUX_R_PUPD         3:2
#define TEGRAX1_PUPD_PULL_UP        (0x2U)
/* Bits 1:0 PM:
  0 = FUNC
  1 = RSVD1
  2 = RSVD2
  3 = RSVD3 */
#define TEGRAX1_PINMUX_R_PM           1:0

/* Macro to set bitfields on a PINMUX register */
#define TEGRAX1_PINMUX_SET_FIELD(reg, field, val) OSEE_R_SET(reg, field, val)
#define TEGRAX1_PINMUX_MSK_FIELD(field)           OSEE_R_MASK(field)

/* PAD Registers offset */
#define TEGRAX1_PINMUX_SPI1_MOSI  (0x3050U)
#define TEGRAX1_PINMUX_SPI1_MISO  (0x3054U)
#define TEGRAX1_PINMUX_SPI1_SCK   (0x3058U)
#define TEGRAX1_PINMUX_SPI1_CS0   (0x305CU)
#define TEGRAX1_PINMUX_SPI1_CS1   (0x3060U)

static inline u16 volatile * tegraX1_get_pinmux_reg_addr( u16 const pin_id ) {
  u16 volatile * p_pinmux_reg;
  switch ( pin_id ) {
    case TEGRAX1_PIN_SPI1_MOSI:
      p_pinmux_reg = (u16 volatile *)
        (TEGRAX1_MISC_BASE_ADDR + TEGRAX1_PINMUX_SPI1_MOSI);
      break;
    case TEGRAX1_PIN_SPI1_MISO:
      p_pinmux_reg = (u16 volatile *)
        (TEGRAX1_MISC_BASE_ADDR + TEGRAX1_PINMUX_SPI1_MISO);
      break;
    case TEGRAX1_PIN_SPI1_SCK:
      p_pinmux_reg = (u16 volatile *)
        (TEGRAX1_MISC_BASE_ADDR + TEGRAX1_PINMUX_SPI1_SCK);
      break;
    case TEGRAX1_PIN_SPI1_CS0:
      p_pinmux_reg = (u16 volatile *)
        (TEGRAX1_MISC_BASE_ADDR + TEGRAX1_PINMUX_SPI1_CS0);
      break;
    case TEGRAX1_PIN_SPI1_CS1:
      p_pinmux_reg = (u16 volatile *)
        (TEGRAX1_MISC_BASE_ADDR + TEGRAX1_PINMUX_SPI1_CS1);
      break;
    default:
      p_pinmux_reg = NULL;
    break;
  }
  return p_pinmux_reg;
}

#endif /* OSEE_TEGRAX1_PINMUX */
