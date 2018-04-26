/** \addtogroup User
 * @{ */

/**
 * \defgroup Battery
 *
 * There is implemented battery charging and discharging process
 * @{
 */

#ifndef BATTERY_H
#define BATTERY_H

#include "stm32f0xx.h"

typedef struct {
    uint32_t voltage;
    uint32_t current;
} BatteryParam_s;

void battery_Uset(uint32_t voltage);

void battery_Iset(uint32_t current);

uint32_t battery_Uget(void);

uint32_t battery_Iget(void);

#endif /* BATTERY_H */
