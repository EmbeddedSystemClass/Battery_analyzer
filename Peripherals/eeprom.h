/** \addtogroup Peripherals
 * @{ */

/**
 * \defgroup EEPROM
 *
 * This module contains eeprom routine
 * @{
 */
#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"

void EEPROM_WriteByte(uint16_t Addr, uint8_t Data);
uint8_t EEPROM_ReadByte(uint8_t Addr);


#endif /* EEPROM_H */
