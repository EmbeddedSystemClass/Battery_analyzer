/** \addtogroup User
 * @{ */

/**
 * \defgroup SysTick
 *
 * There is implemented SysTick handler, where is millis variable incremented. 
 * In SysTick handler is called watchdog restart to. 
 * @{
 */

#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f0xx.h"

extern uint8_t state;

/**
 * SysTick Handler, called every 1ms internaly
 */
void SysTick_Handler(void);

/**
 * Millis
 * @return number of miiliseconds from system start
 */
uint32_t millis(void);

/**
 * Do blocking delay
 * @param milliseconds
 */
void delay (uint32_t milliseconds);

/**
 * Get num of seconds after start
 * @return 
 */
uint32_t SysTick_getSeconds(void);

#endif /*__SYSTICK */
