/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017 Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * See LICENSE file.
 * ###*E*### */

/** \file   ee_conf.h
 *  \brief  Main Configuration Collector.
 *
 *  This files is the main collector in Erika Enterprise for configuration
 *  files.
 *
 *  \author Errico Gudieri
 *  \date   2017
 */

#if (!defined(OSEE_CONF_H))
#define OSEE_CONF_H

#if (defined(__cplusplus))
extern "C" {
#endif

#include "ee.h"
#include "ee_hal_internal_types.h"
#include "ee_scheduler_types.h"
#include "ee_kernel_types.h"
#include "ee_get_kernel_and_core.h"

#if (defined(__cplusplus))
}
#endif

#endif /* !OSEE_CONF_H */
