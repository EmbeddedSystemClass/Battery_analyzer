/** \addtogroup Peripherals
 * @{ */

/**
 * \defgroup I2C
 *
 * This module contains I2C routine
 * @{
 */
#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"

/**
 * Initialize low level I2C
 */
void I2C_LL_init(void);


#endif /* I2C_H */
