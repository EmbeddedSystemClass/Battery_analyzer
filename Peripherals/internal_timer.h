/** \addtogroup Peripherals
 * @{ */
 
/**
 * \defgroup Internal timer
 *
 * This module contains methods for internal timer
 * @{
 */
 
#ifndef INTERNAL_TIMER_H
#define INTERNAL_TIMER_H
 
#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"
 
void TIM3_Init(void);
void TIM3_Enable(void);
 
#endif /* INTERNAL_TIMER_H */