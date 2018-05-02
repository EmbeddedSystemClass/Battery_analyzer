/** \addtogroup Peripherals
 * @{ */
 
/**
 * \defgroup Internal timer
 *
 * This module contains methods for internal timer
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
 

#define SMPS_PMOS_Pin LL_GPIO_PIN_8
#define SMPS_PMOS_GPIO_Port GPIOA
#define SMPS_NMOS_Pin LL_GPIO_PIN_13
#define SMPS_NMOS_GPIO_Port GPIOB
#define DISCHG_Pin LL_GPIO_PIN_9
#define DISCHG_GPIO_Port GPIOA

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


void PowerSupply_Init(void);



 
#endif /* POWER_SUPPLY_H */