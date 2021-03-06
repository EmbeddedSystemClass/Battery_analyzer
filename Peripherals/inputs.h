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

enum ADC_Channels_e {
    ADC_V_BATT = 0,
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
};
 
void Inputs_ADC_Init(void);

void ADC_Value(void);

void Inputs_ADC_printValues(void);

uint16_t Inputs_ADC_getRecalgulatedValue(enum ADC_Channels_e channel);

void Inputs_BTN_Init(void);

uint8_t Inputs_BTN_getBtn(void);

uint8_t Inputs_BTN_isBtnPressed(uint8_t btnMask);

void Inputs_BTN_clearBtnBuffer(void);

#endif /* INPUTS_H */
