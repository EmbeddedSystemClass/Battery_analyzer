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

typedef enum {
    ADC_BATT_VTG = 0,
    ADC_V_BUS,
    ADC_VCC_IN,
    ADC_DISCHARGE_CURR,
    ADC_CHARGE_CURR,
    ADC_BATT_THERMISTOR,
    ADC_INTERNAL_THERMISTOR,
    ADC_FB_ADC,
    ADC_CPUTEMP,
    ADC_VREF,
    ADC_CHANNELS
} ADC_Channels_e;
 
void Inputs_ADC_Init(void);

void ADC_Value(void);

void Inputs_BTN_Init(void);

uint8_t Inputs_BTN_getBtn(void);

#endif /* INPUTS_H */