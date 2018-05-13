/** \addtogroup Peripherals
 * @{ */

/**
 * \defgroup Power supply
 *
 * This module contains methods for SMPS
 * @{
 */

#ifndef POWER_SUPPLY_H
#define POWER_SUPPLY_H

#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"

#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

typedef enum {
    STOP = 0,
    DISCHARGE,
    CHARGE_CONSTANT_VOLTAGE,
    CHARGE_CONSTANT_CURRENT,
} PowerSupplyMode_e;

typedef struct {
   PowerSupplyMode_e mode;
   uint32_t min_current;
   uint32_t max_current;
   uint32_t current_current;
   uint32_t min_voltage;
   uint32_t max_voltage;
   uint32_t current_voltage;
} PowerSupplyTypeDef;

#define MIN_VOLTAGE 4500
#define MAX_VOLTAGE 14500
#define MIN_CURRENT 0
#define MAX_CURRENT 3000
#define MAX_DISCHG_CURRENT 150

void PowerSupply_Init(void);

void PowerSupply_Set(PowerSupplyMode_e mode, uint32_t voltage, uint32_t current);


#endif /* POWER_SUPPLY_H */