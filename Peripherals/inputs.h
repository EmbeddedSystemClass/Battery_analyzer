/** \addtogroup Peripherals
 * @{ */

/**
 * \defgroup Inputs
 *
 * This module contains inputs procedures
 * @{
 */
#ifndef INPUTS_H
#define INPUTS_H

#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"

void Inputs_BTN_Init(void);

uint8_t Inputs_BTN_getBtn(void);

#endif /* INPUTS_H */
