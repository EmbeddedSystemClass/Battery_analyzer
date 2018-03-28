/** \addtogroup Peripherals
 * @{ */

/**
 * \defgroup Uart
 *
 * This module contains uart port for serial communication
 * @{
 */
#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_usart.h"

/**
 * Initialize low level extender USART
 * speed: 57600
 */
void Uart_LL_init(void);

/**
 * Put character to debug
 * @param ch sended character
 */
void uart_putchar(int ch);

#endif /* UART_H */
