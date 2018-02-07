/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */
#include "ee_internal.h"
#include <inmate.h>
#include "ee_tegraX1_pinmux.h"
#include "shared_data.h"

/*==============================================================================
                            Features Configuration
 =============================================================================*/
#define TEGRAX1_PWM_ENABLE
#define TEGRAX1_ENCODER_ENABLE
//#define TEGRAX1_SIM_ENABLE

/*==============================================================================
                      Shared Memory Communication Defines
 =============================================================================*/

/* Const Pointer To Shared Data */
typedef void volatile * phys_addr_t;
u64 volatile * const p_shared_area = (u64 volatile *)SHARED_DATA_ADDR;

/*==============================================================================
                                TASKs an ISR2 IDs
 =============================================================================*/
TaskType  isr_id;
TaskType  pin_isr_id;
TaskType  data_xchg_id;

/*==============================================================================
                                BEGIN PWM Driver
 =============================================================================*/

#define TEGRAX1_PIN_PWM TEGRAX1_PIN_SPI1_MOSI
#define TEGRAX1_PWM_OUT \
    (*TEGRAX1_GPIO_REG_ADDR(u16, TEGRAX1_GPIO_OUT, TEGRAX1_PIN_PWM))
#define TEGRAX1_PWM_MSK TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_PWM)

#define PWM_MIN_INTERARRIVAL_US (25U)
#define PWM_MIN_TICKS OSEE_MICRO_TO_TICKS(PWM_MIN_INTERARRIVAL_US,\
  osEE_aarch64_gtimer_get_freq())

static volatile u64 jitter_cnt;
static volatile u64 jitter_max;
static volatile u64 jitter_avg;
static volatile u64 jitter_tot;
static volatile u64 jitter_min = ((u64)-1);

#if (defined(TEGRAX1_PWM_ENABLE))

#define TEGRAX1_PWM_FREQUENCY_HZ      (2000U)
#define TEGRAX1_DATA_XCHG_FREQ_HZ     (10U)
#define TEGRAX1_DATA_XCHG_TICKS       \
  ((TEGRAX1_PWM_FREQUENCY_HZ*2U)/TEGRAX1_DATA_XCHG_FREQ_HZ)
#define PWM_INVERTED_FRONT
/* 10s */
#define PWM_JITTER_CNT_RESET      ((TEGRAX1_PWM_FREQUENCY_HZ*2U)*10U)
#define PWM_DUTY_SLICES           (100U)

#define JOYSTICK_PULSES           (1024U)
#define JOYSTICK_TO_PWM_DUTY(j)   (((j)*PWM_DUTY_SLICES)/JOYSTICK_PULSES)
#define PWM_DUTY_TO_JOYSTICK(d)   (((d)*JOYSTICK_PULSES)/PWM_DUTY_SLICES)

#if 0
#define PWM_MIN_DUTY_SLICES OSEE_MICRO_TO_TICKS(PWM_MIN_INTERARRIVAL_US,
  (TEGRAX1_PWM_FREQUENCY_HZ * PWM_DUTY_SLICES) )
#else
#define PWM_MIN_DUTY_SLICES (1U)
#endif

//#define PWM_STARTING_DUTY         (70U)
#define PWM_STARTING_DUTY         PWM_MIN_DUTY_SLICES

//static volatile u32       pwm_frequency;
static volatile u16       pwm_duty;
static volatile u64       pwm_expected_ticks;

enum pwm_front {
  PWM_ZERO_TO_ONE_FRONT = 0U,
  PWM_ONE_TO_ZERO_FRONT
};

static u64 pwm_get_ticks_next_front(enum pwm_front front) {
  u64 pwm_ticks_next_front;
  u16 front_duty;
  if (front == PWM_ONE_TO_ZERO_FRONT) {
#if (!defined(PWM_INVERTED_FRONT))
    front_duty = pwm_duty;
#else
    front_duty = (PWM_DUTY_SLICES - pwm_duty);
#endif /* !PWM_INVERTED_FRONT */
  } else {
#if (!defined(PWM_INVERTED_FRONT))
    front_duty = (PWM_DUTY_SLICES - pwm_duty);
#else
    front_duty = pwm_duty;
#endif /* !PWM_INVERTED_FRONT */
  }
  /* pwm_ticks_next_front = (osEE_aarch64_gtimer_get_freq() * front_duty) /
      (pwm_frequency * PWM_DUTY_SLICES); */
  pwm_ticks_next_front = (osEE_aarch64_gtimer_get_freq() * front_duty) /
      (TEGRAX1_PWM_FREQUENCY_HZ * PWM_DUTY_SLICES);
  return pwm_ticks_next_front;
}

static inline void pwm_out_zero(void) {
  /* Read-and-modify OUT register */
  TEGRAX1_PWM_OUT &= ~TEGRAX1_PWM_MSK;
}

#if 0
static inline void pwm_out_one(void) {
  /* Read-and-modify OUT register */
  TEGRAX1_PWM_OUT |= TEGRAX1_PWM_MSK;
}
#endif

static inline void pwm_setup_gtimer(u64 pwm_ticks_next_front) {
  pwm_expected_ticks +=  pwm_ticks_next_front;
  osEE_aarch64_gtimer_start(pwm_expected_ticks,
    OSEE_AARCH64_GTIMER_UPPERCOUNT);
}

//static void pwm_start ( u32 freq, u16 duty ) {
static void pwm_start ( u16 duty ) {
  if ( duty > (PWM_DUTY_SLICES - PWM_MIN_DUTY_SLICES) ) {
    duty = (PWM_DUTY_SLICES - PWM_MIN_DUTY_SLICES);
  } if ( duty < PWM_MIN_DUTY_SLICES ) {
    duty = PWM_MIN_DUTY_SLICES;
  }
  /* Set-up configuration */
  /* TODO: Handle Frequency limits */
  //pwm_frequency = freq;
  pwm_duty      = duty;
  pwm_expected_ticks = osEE_aarch64_gtimer_get_ticks();
  /* Assure that output is zero */
  pwm_out_zero();
  /* Start with a Zero-To-One Front */
  pwm_setup_gtimer(pwm_get_ticks_next_front(PWM_ZERO_TO_ONE_FRONT));
}
#endif /* TEGRAX1_PWM_ENABLE */

static void pwm_front_irq( void )
{
  u16 out;
#if (defined(TEGRAX1_PWM_ENABLE))
  u64 pwm_ticks_next_front;
  /* Get Jitter measurement */
  u64 delta = osEE_aarch64_gtimer_get_ticks() - pwm_expected_ticks;
#endif /* TEGRAX1_PWM_ENABLE */

  /* Handle Output */
  /* Read OUT register */
  out = TEGRAX1_PWM_OUT;
  if ( out & TEGRAX1_PWM_MSK ) {
    out &= ~TEGRAX1_PWM_MSK;
#if (defined(TEGRAX1_PWM_ENABLE))
    pwm_ticks_next_front = pwm_get_ticks_next_front(PWM_ZERO_TO_ONE_FRONT);
#endif /* TEGRAX1_PWM_ENABLE */
  } else {
    out |= TEGRAX1_PWM_MSK;
#if (defined(TEGRAX1_PWM_ENABLE))
    pwm_ticks_next_front = pwm_get_ticks_next_front(PWM_ONE_TO_ZERO_FRONT);
#endif /* TEGRAX1_PWM_ENABLE */
  }
  /* Commit Changes */
  TEGRAX1_PWM_OUT = out;

  /* Save min/MAX Jitter */
  if (delta < jitter_min) {
    jitter_min = delta;
  }
  if (delta > jitter_max) {
    jitter_max = delta;
  }
  /* Increment the counter value (I DO NOT HANDLE WRAP AROUND,
     I hope that in 8-10 hours do not wrap!!!) */
  ++jitter_cnt;
  /* Update the AVG value */
  /* jitter_avg = (((jitter_cnt - 1U) * jitter_avg) + delta) / jitter_cnt; */
  /* More Accurate Mean Evaluation (less Truncament), so higher avg value. */
  jitter_tot += delta;
  jitter_avg = jitter_tot / jitter_cnt;
  /* Reset Max every PWM_JITTER_CNT_RESET samples */
  if ( jitter_cnt >= PWM_JITTER_CNT_RESET ) {
    jitter_max = 0U;
    jitter_tot = 0U;
    jitter_cnt = 0U;
  }
#if (defined(TEGRAX1_PWM_ENABLE))
  {
    static u32 decimator;
    if (++decimator == TEGRAX1_DATA_XCHG_TICKS) {
      ActivateTask(data_xchg_id);
      decimator = 0U;
    }
  }
#endif /* TEGRAX1_PWM_ENABLE */

#if (defined(TEGRAX1_PWM_ENABLE))
  /* Configure Timer Forn NEXT Front */
  pwm_setup_gtimer(pwm_ticks_next_front);
#else
  osEE_aarch64_gtimer_start(1U, OSEE_AARCH64_GTIMER_COUNTDOWN);
#endif /* TEGRAX1_PWM_ENABLE */
}
/*==============================================================================
                                END PWM Driver
 =============================================================================*/
/*==============================================================================
                             BEGIN Encoder Driver
 =============================================================================*/
#if 1
#define TEGRAX1_PIN_ENCODER_CH_A  TEGRAX1_PIN_SPI1_MISO
#define TEGRAX1_PIN_ENCODER_CH_B  TEGRAX1_PIN_SPI1_SCK
#else
#define TEGRAX1_PIN_ENCODER_CH_A  TEGRAX1_PIN_SPI1_CS0
#define TEGRAX1_PIN_ENCODER_CH_B  TEGRAX1_PIN_SPI1_CS1
#endif

#define TEGRAX1_ENCODER_PIN_CH_A_MSK \
  TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_ENCODER_CH_A)
#define TEGRAX1_ENCODER_PIN_CH_B_MSK \
  TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_ENCODER_CH_B)

#define TEGRAX1_ENCODER_PINS_MSK \
  (TEGRAX1_ENCODER_PIN_CH_A_MSK | TEGRAX1_ENCODER_PIN_CH_B_MSK)

static u8 volatile gpio_in_prev;
static s32 volatile gpio_enc_pos;

#if (defined(TEGRAX1_ENCODER_ENABLE))
static void encoder_ch_a(s32 volatile * const p_enc, u8 ch_a, u8 ch_b)
{
  if ( ch_a != 0U ) {
    /* check channel B to see which way encoder is turning */
    if ( ch_b == 0U ) {
      (*p_enc) += 1; /* Clock-Wise: CW */
    } else {
      (*p_enc) -= 1; /* Counter-Clock Wise: CCW */
    }
  }
  /*... must be a high-to-low edge on channel A */
  else {
    /* check channel B to see which way encoder is turning */
    if ( ch_b != 0 ) {
      (*p_enc) += 1; /* Clock-Wise: CW */
    } else {
      (*p_enc) -= 1; /* Counter-Clock Wise: CCW */
    }
  }
}

static void encoder_ch_b(s32 volatile * const p_enc, u8 ch_a, u8 ch_b)
{
  /* look for a low-to-high on channel B */
  if ( ch_b != 0U ) {
    /* check channel A to see which way encoder is turning */
    if ( ch_a != 0U ) {
      (*p_enc) += 1; /* Clock-Wise: CW */
    } else {
      (*p_enc) -= 1; /* Counter-Clock Wise: CCW */
    }
  }
  /* Look for a high-to-low on channel B */
  else {
    /* check channel B to see which way encoder is turning */
    if ( ch_a == 0U) {
      (*p_enc) += 1; /* Clock-Wise: CW */
    } else {
      (*p_enc) -= 1; /* Counter-Clock Wise: CCW */
    }
  }
}
#endif /* TEGRAX1_ENCODER_ENABLE */

static void encoder_irq ( void ) {
  u8 volatile * const p_gpio_int_clr = TEGRAX1_GPIO_REG_ADDR(u8,
    TEGRAX1_GPIO_INT_CLR, TEGRAX1_PIN_ENCODER_CH_A);
  u8 volatile * const p_gpio_int_sta = TEGRAX1_GPIO_REG_ADDR(u8,
    TEGRAX1_GPIO_INT_STA, TEGRAX1_PIN_ENCODER_CH_A);

#if (defined(TEGRAX1_ENCODER_ENABLE))
  u8 volatile * const p_gpio_in = TEGRAX1_GPIO_REG_ADDR(u8,
    TEGRAX1_GPIO_IN, TEGRAX1_PIN_ENCODER_CH_A);

  u8 const gpio_in          = (*p_gpio_in);
  u8 const gpio_in_flipped  = (gpio_in_prev ^ gpio_in);
  u8 const gpio_ch_a        = (gpio_in) & TEGRAX1_ENCODER_PIN_CH_A_MSK;
  u8 const gpio_ch_b        = (gpio_in) & TEGRAX1_ENCODER_PIN_CH_B_MSK;
  u8 const gpio_int_sta     = (*p_gpio_int_sta);
  u8 gpio_flipped_counter   = 0U;

  /* Channel-A */
  if ((gpio_int_sta & TEGRAX1_ENCODER_PIN_CH_A_MSK) != 0U) {
    encoder_ch_a(&gpio_enc_pos, gpio_ch_a, gpio_ch_b);
    if ((gpio_in_flipped & TEGRAX1_ENCODER_PIN_CH_A_MSK) == 0U) {
      printk("WARNING: INT_STA CH_A, but bit not flipped?!\n");
    }
    ++gpio_flipped_counter;
    /* Clear the GPIO IRQ Flag Channel-A */
    (*p_gpio_int_clr) = TEGRAX1_ENCODER_PIN_CH_A_MSK;
  }
  /* Channel-B */
  if ((gpio_int_sta & TEGRAX1_ENCODER_PIN_CH_B_MSK) != 0U) {
    encoder_ch_b(&gpio_enc_pos, gpio_ch_a, gpio_ch_b);
    if ((gpio_in_flipped & TEGRAX1_ENCODER_PIN_CH_B_MSK) == 0U) {
      printk("WARNING: INT_STA CH_B, but bit not flipped?!\n");
    }
    ++gpio_flipped_counter;
    /* Clear the GPIO IRQ Flag Channel-B */
    (*p_gpio_int_clr) = TEGRAX1_ENCODER_PIN_CH_B_MSK;
  }

  /* Save GPIO in  as Prev GPIO in */
  gpio_in_prev = gpio_in;

  if (gpio_flipped_counter != 1U) {
    printk("WARNING: flipped counter:<%d>\n", gpio_flipped_counter);
    if ( gpio_flipped_counter == 0U ) {
      /* I don't know wich pin flipped, clear everything */
      (*p_gpio_int_clr) = 0xFFU;
    }
  }
  if ((gpio_int_sta & TEGRAX1_ENCODER_PINS_MSK) == TEGRAX1_ENCODER_PINS_MSK) {
    printk("WARNING: both CHA and CHB INT_STA bit set!\n");
    (*p_gpio_int_clr) = TEGRAX1_ENCODER_PINS_MSK;
  }
#else
  printk("GPIO0 interrupt:<%x>\n", (*p_gpio_int_sta));
  (*p_gpio_int_clr) = 0xFFU;
#endif /* TEGRAX1_ENCODER_ENABLE */
}
/*==============================================================================
                                END Encoder Driver
 =============================================================================*/
/*==============================================================================
                               BEGIN Pinmux Driver
 =============================================================================*/
static void pinmux_configuration ( void ) {
  /* Initialize GPIO pin16, pin17, pin18 */
  /* Register to configure a PIN as GPIO */
  u16 volatile * const p_gpio_cnf =
    TEGRAX1_GPIO_REG_ADDR(u16, TEGRAX1_GPIO_CNF, TEGRAX1_PIN_PWM);
  /* Register to configure pin direction */
  u16 volatile * const p_gpio_oe =
    TEGRAX1_GPIO_REG_ADDR(u16, TEGRAX1_GPIO_OE, TEGRAX1_PIN_PWM);

  /* Registers to configure Interrupts */
  /* Register to configure on which event a interrupt is generated */
  u32 volatile * const p_gpio_int_lvl = TEGRAX1_GPIO_REG_ADDR(u32,
    TEGRAX1_GPIO_INT_LVL, TEGRAX1_PIN_ENCODER_CH_A);
  /* Register to clear interrupt bits */
  u8 volatile * const p_gpio_int_clr = TEGRAX1_GPIO_REG_ADDR(u8,
    TEGRAX1_GPIO_INT_CLR, TEGRAX1_PIN_ENCODER_CH_A);
  /* Register to enable interrupts */
  u16 volatile * const p_gpio_int_en  = TEGRAX1_GPIO_REG_ADDR(u16,
    TEGRAX1_GPIO_INT_ENB, TEGRAX1_PIN_ENCODER_CH_A);

  /* PINMUX_AUX registers */
  u16 volatile * const p_pinmux_ch_a =
    tegraX1_get_pinmux_reg_addr(TEGRAX1_PIN_ENCODER_CH_A);
  u16 volatile * const p_pinmux_ch_b =
    tegraX1_get_pinmux_reg_addr(TEGRAX1_PIN_ENCODER_CH_B);

  /* Enable as GPIO pin16, pin17, pin18 (pin17 and pin18 will be
     channel A and B correspondingly */
  u16 const gpio_cnf_msk =
    TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_PWM) |
    TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_ENCODER_CH_A) |
    TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_ENCODER_CH_B);

  /* Set pin16 as output [pin17,pin18 are inputs] */
  u16 const gpio_oe_msk  = TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_PWM);

  /* Interrupts on Both edges for pin17 and pin18 */
  u32 const gpio_lvl_mask =
    TEGRAX1_GPIO_MSK(1,TEGRAX1_PIN_ENCODER_CH_A) |
    TEGRAX1_GPIO_MSK(1,TEGRAX1_PIN_ENCODER_CH_B) |
    TEGRAX1_GPIO_MSK(2,TEGRAX1_PIN_ENCODER_CH_A) |
    TEGRAX1_GPIO_MSK(2,TEGRAX1_PIN_ENCODER_CH_B);

  /* Enable Interupts for pn17,pin18 */
  u8 const gpio_en_mask =
    TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_ENCODER_CH_A) |
    TEGRAX1_GPIO_MSK(0,TEGRAX1_PIN_ENCODER_CH_B);

  printk("GPIO Registers Value Before Setup:\n"
    "CNF:<%p>:=<%x>\n"
    "OE:<%p>:=<%x>\n"
    "LVL:<%p>:=<%x>\n"
    "EN:<%p>:=<%x>\n"
    "Pinmux ChA:<%p>:=<%x>\n"
    "Pinmux ChB:<%p>:=<%x>\n",

    p_gpio_cnf, *p_gpio_cnf,
    p_gpio_oe, *p_gpio_oe,
    p_gpio_int_lvl, *p_gpio_int_lvl,
    p_gpio_int_en, *p_gpio_int_en,
    p_pinmux_ch_a, *p_pinmux_ch_a,
    p_pinmux_ch_b, *p_pinmux_ch_b
  );

  (*p_gpio_cnf)     = gpio_cnf_msk;
  (*p_gpio_oe)      = gpio_oe_msk;
  /* Configure Edge level for interrupts pin16 */
  (*p_gpio_int_lvl) = gpio_lvl_mask;

  /* Input PIN Initial Value: To handle the encoder status */
  gpio_in_prev = (*(TEGRAX1_GPIO_REG_ADDR(u8, TEGRAX1_GPIO_IN,
                  TEGRAX1_PIN_SPI1_MISO)));
  /* Clear the interrupt bits */
  (*p_gpio_int_clr) = TEGRAX1_ENCODER_PINS_MSK;
  /* Enable IRQ for pin17,pin18 */
  (*p_gpio_int_en)  = gpio_en_mask;

  /* Set Pull-Up on CH_A and CH_B PADs */
  (*p_pinmux_ch_a) = (TEGRAX1_PINMUX_SET_FIELD(*p_pinmux_ch_a,
    TEGRAX1_PINMUX_R_PUPD, TEGRAX1_PUPD_PULL_UP) |
      TEGRAX1_PINMUX_MSK_FIELD(TEGRAX1_PINMUX_R_E_INPUT));
  (*p_pinmux_ch_b) = (TEGRAX1_PINMUX_SET_FIELD(*p_pinmux_ch_b,
    TEGRAX1_PINMUX_R_PUPD, TEGRAX1_PUPD_PULL_UP) |
      TEGRAX1_PINMUX_MSK_FIELD(TEGRAX1_PINMUX_R_E_INPUT));

  printk("GPIO Registers Value After Setup:\n"
    "CNF:<%p>:=<%x>\n"
    "OE:<%p>:=<%x>\n"
    "LVL:<%p>:=<%x>\n"
    "EN:<%p>:=<%x>\n"
    "Pinmux ChA:<%p>:=<%x>\n"
    "Pinmux ChB:<%p>:=<%x>\n",
    p_gpio_cnf, *p_gpio_cnf,
    p_gpio_oe,  *p_gpio_oe,
    p_gpio_int_lvl, *p_gpio_int_lvl,
    p_gpio_int_en, *p_gpio_int_en,
    p_pinmux_ch_a, *p_pinmux_ch_a,
    p_pinmux_ch_b, *p_pinmux_ch_b
  );
}
/*==============================================================================
                               END Pinmux Driver
 =============================================================================*/
/*==============================================================================
                                 TASKs & main
 =============================================================================*/
/* 135 RPM at 3.3 V that is 66% of 5V => ~205 100 % */
#define SPEED_MAX_RPM (205U)
#define SPEED_MAX_KMH (300U)

DeclareTask(DataXchg);
TASK(DataXchg) {
#if (defined(TEGRAX1_PWM_ENABLE))
  static unsigned int speed_estimator_i;
  static u64 speed_estimator_encoder[4];
  static u32 speed_estimator_speed[OSEE_ARRAY_ELEMENT_COUNT(speed_estimator_encoder)];
  u32 speed_evaluated = 0U;
  u64 const shared_data_pwm_duty =
    JOYSTICK_TO_PWM_DUTY(p_shared_area[JOYSTICK_POS]);

  if ( shared_data_pwm_duty < PWM_MIN_DUTY_SLICES ) {
    pwm_duty = PWM_MIN_DUTY_SLICES;
  } else if ( shared_data_pwm_duty > (PWM_DUTY_SLICES - PWM_MIN_DUTY_SLICES) ) {
    pwm_duty = (PWM_DUTY_SLICES - PWM_MIN_DUTY_SLICES);
  } else {
    pwm_duty = shared_data_pwm_duty;
  }

  {
    unsigned int i;
    unsigned int const  speed_cnt =
      OSEE_ARRAY_ELEMENT_COUNT(speed_estimator_encoder);
    unsigned int const  prev_i  = (speed_estimator_i - 1U) % speed_cnt;
    u64 const           enc_cnt = gpio_enc_pos;

    /* Save actual Encoder Cnt */
    speed_estimator_encoder[speed_estimator_i] = enc_cnt;
    /* Evaluate Actual Speed in RPM with Encoder 360 Ticks-Revolution */
    speed_estimator_speed[speed_estimator_i] = ((enc_cnt -
      speed_estimator_encoder[prev_i]) * TEGRAX1_DATA_XCHG_FREQ_HZ * 60U) /
        360U;
    /* Move Speed Estimator Index */
    speed_estimator_i =
      (speed_estimator_i + 1U) %
        OSEE_ARRAY_ELEMENT_COUNT(speed_estimator_encoder);
    /* Evaluate the speed mean */
    for (i = 0U; i < speed_cnt; ++i) {
      speed_evaluated += speed_estimator_speed[speed_estimator_i];
    }
    speed_evaluated /= speed_cnt;
  }

  p_shared_area[DUTY_CYCLE_POS] = pwm_duty;
  p_shared_area[ENCODER_POS]    =
    (speed_evaluated * SPEED_MAX_KMH) / SPEED_MAX_RPM;
  p_shared_area[JITTER_MIN_POS] = osEE_aarch64_gtimer_ticks_to_ns(jitter_min);
  p_shared_area[JITTER_AVG_POS] = osEE_aarch64_gtimer_ticks_to_ns(jitter_avg);
  p_shared_area[JITTER_MAX_POS] = osEE_aarch64_gtimer_ticks_to_ns(jitter_max);

#if 0
  printk(
    "PWM parameters, duty:<%d>, shared memory joystick:<%d>\n"
    "PWM timer jitter, avg:<%6ld> ns, min:<%6ld> ns, max:<%6ld> ns\n"
    "PWM AVG on:<%d> Samples\n"
    "Speed Evaluated RPM:<%d>, Emulated KmH:<%d>\n",
    p_shared_area[DUTY_CYCLE_POS], p_shared_area[JOYSTICK_POS],
    p_shared_area[JITTER_AVG_POS],
    p_shared_area[JITTER_MIN_POS],
    p_shared_area[JITTER_MAX_POS],
    jitter_cnt,
    speed_evaluated, p_shared_area[ENCODER_POS]
  );
#endif
#if (defined(TEGRAX1_SIM_ENABLE))
  {
    u64 const max_pwm_duty_joystick =
      PWM_DUTY_TO_JOYSTICK(PWM_DUTY_SLICES - PWM_MIN_DUTY_SLICES);
    u64 const min_pwm_duty_joystick = PWM_DUTY_TO_JOYSTICK(PWM_MIN_DUTY_SLICES);
    u64 const next_pwm_duty_joystick = p_shared_area[JOYSTICK_POS] + 5U;

    if ( next_pwm_duty_joystick >= max_pwm_duty_joystick ) {
      p_shared_area[JOYSTICK_POS] = min_pwm_duty_joystick;
    } else {
      p_shared_area[JOYSTICK_POS] = next_pwm_duty_joystick;
    }
  }
#endif /* TEGRAX1_SIM_ENABLE */
#endif /* TEGRAX1_PWM_ENABLE */
}

#define TEGRAX1_GTIMER_IRQ_PRIO (OSEE_GIC_LOWEST_SEC_PRIORITY + 1U)
#define TEGRAX1_GPIO_IRQ_PRIO   (OSEE_GIC_LOWEST_SEC_PRIORITY)

int main ( void ) {
  StatusType s;

  printk("VCORE ID OFFSET:<%d>\n", osEE_aarch64_vcore_id_offset);
  printk("VCORE ID RAW:<%d>\n", osEE_aarch64_get_vcore_id_raw());
  printk("Kernel CORE ID:<%d>\n", osEE_get_curr_core_id());
  printk("TARGET CORE MASK:<%d>\n", osEE_gic_v2_get_cpuif_mask());
  printk("Timer Frequency:<%ld>\n", osEE_aarch64_gtimer_get_freq());
  printk("50us in timer ticks:<%d>\n", PWM_MIN_TICKS);
  printk("PWM min duty slices (to grant interarrival 25 us at least):<%d>\n",
    PWM_MIN_DUTY_SLICES);
  printk("SCTRL:<%x>\n", osEE_aarch64_SCTLR());

  s = CreateTask(&isr_id, OSEE_TASK_TYPE_ISR2, pwm_front_irq,
       TEGRAX1_GTIMER_IRQ_PRIO, TEGRAX1_GTIMER_IRQ_PRIO, 1U, OSEE_SYSTEM_STACK);

  printk ("TIMER IRQ Is Enabled:<%d><%x>; Priority:<%d>; IGROUP:<%d> "
          "before SetISR2Source, Result (0 is OK):%d\n",
          osEE_gic_v2_is_enabled_irq(OSEE_GTIMER_IRQ),
          osEE_gic_v2_read_isenabler(OSEE_GTIMER_IRQ),
          osEE_gic_v2_read_prio_isr(OSEE_GTIMER_IRQ),
          osEE_gicd_get_igroupr(OSEE_GTIMER_IRQ),
          s
  );

  s = CreateTask(&pin_isr_id, OSEE_TASK_TYPE_ISR2, encoder_irq,
        TEGRAX1_GPIO_IRQ_PRIO, TEGRAX1_GPIO_IRQ_PRIO, 1U, OSEE_SYSTEM_STACK);

  printk ("GPIO0_IRQ Is Enabled:<%d><%x>; Priority:<%d>; IGROUP:<%d>; "
          "ITARGETSR:<%u><%x>; before SetISR2Source, Result (0 is OK):%d\n",
          osEE_gic_v2_is_enabled_irq(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read_isenabler(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read_prio_isr(TEGRAX1_GPIO0_IRQ),
          osEE_gicd_get_igroupr(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read_itargetsr(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read32_itargetsr(TEGRAX1_GPIO0_IRQ),
          s
  );

  /* Create Support Task */
  s = CreateTask(&data_xchg_id, OSEE_TASK_TYPE_BASIC, TASK_FUNC(DataXchg),
        2U, 2U, 1U, OSEE_SYSTEM_STACK);
  /* Tie ISR2s With IRQs */
  s = SetISR2Source(isr_id, OSEE_GTIMER_IRQ);
  printk ("ISRs created and tied with TIMER_IRQ. "
          "TIMER IRQ Is Enabled:<%d><%x>; Priority:<%d>; IGROUP:<%d> "
          "after SetISR2Source, Result (0 is OK):%d\n",
          osEE_gic_v2_is_enabled_irq(OSEE_GTIMER_IRQ),
          osEE_gic_v2_read_isenabler(OSEE_GTIMER_IRQ),
          osEE_gic_v2_read_prio_isr(OSEE_GTIMER_IRQ),
          osEE_gicd_get_igroupr(OSEE_GTIMER_IRQ),
          s
  );

  s = SetISR2Source(pin_isr_id, TEGRAX1_GPIO0_IRQ);
  printk ("ISRs created and tied with GPIO0_IRQ. "
          "GPIO0_IRQ Is Enabled:<%d><%x>; Priority:<%d>; IGROUP:<%d>; "
          "ITARGETSR:<%u><%x>; after SetISR2Source, Result (0 is OK):%d\n",
          osEE_gic_v2_is_enabled_irq(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read_isenabler(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read_prio_isr(TEGRAX1_GPIO0_IRQ),
          osEE_gicd_get_igroupr(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read_itargetsr(TEGRAX1_GPIO0_IRQ),
          osEE_gic_v2_read32_itargetsr(TEGRAX1_GPIO0_IRQ),
          s
  );

  printk("DAIF:<%x>\n", osEE_aarch64_DAIF());
  printk("NZCV:<%x>\n", osEE_aarch64_NZCV());
  printk("CurrentEL:<%d>\n", osEE_aarch64_CurrentEL());
  printk("SPSel:<%d>\n", osEE_aarch64_SPSel());
  printk("SP:<%p>\n", osEE_get_SP());
  StartOS(OSDEFAULTAPPMODE);
  printk("OS Started\n");
  printk("DAIF:<%x>\n", osEE_aarch64_DAIF());
  printk("NZCV:<%x>\n", osEE_aarch64_NZCV());
  printk("CurrentEL:<%d>\n", osEE_aarch64_CurrentEL());
  printk("SPSel:<%d>\n", osEE_aarch64_SPSel());
  printk("SP:<%p>\n", osEE_get_SP());

  /* GPIO Configuration */
  pinmux_configuration();

#if (defined(TEGRAX1_PWM_ENABLE))
  printk("Initializing PWM timer... PWM frequency hz:<%d>\n",
    TEGRAX1_PWM_FREQUENCY_HZ);

  /* Initialize Shared Memory Duty */
  p_shared_area[JOYSTICK_POS] = PWM_DUTY_TO_JOYSTICK(PWM_STARTING_DUTY);
  //pwm_start(TEGRAX1_PWM_FREQUENCY_HZ, 70U);
  pwm_start(PWM_STARTING_DUTY);
#else
  osEE_aarch64_gtimer_start(1U, OSEE_AARCH64_GTIMER_COUNTDOWN);
#endif /* TEGRAX1_PWM_ENABLE */

  while ( 1 ) {
    __asm__ volatile("wfi" : : : "memory");
  }
}
