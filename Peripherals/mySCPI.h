/** \addtogroup Peripherals
 * @{ */

/**
 * \defgroup mySCPI
 *
 * This module contains uart port for serial communication
 * @{
 */
#ifndef MYSCPI_H
#define MYSCPI_H

#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_usart.h"

extern struct Queue_s Rx;

void mySCPI_processInput(void);
void mySCPI_setEOL_detected(void);
#endif /* MYSCPI_H */
