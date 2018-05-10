#include "inputs.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "stm32f0xx_ll_exti.h"
#include "debug.h"
#include "directives.h"
#include "stm32f0xx_ll_adc.h"
#include "internal_timer.h"
#include "stm32f0xx_ll_dma.h"
#include "debug.h"

static uint8_t pressed_btn;
#define apply_Q(x)  ((x) >> 11)
uint16_t ADC_ConvertedValue[ADC_CHANNELS];
uint32_t ADC_Val[ADC_CHANNELS];

static void setPressedBtn(uint8_t btnMask)
{
    pressed_btn = btnMask;
}

uint8_t Inputs_BTN_getBtn(void)
{
    return pressed_btn;
}

uint8_t Inputs_BTN_isBtnPressed(uint8_t btnMask)
{
    uint8_t mask = Inputs_BTN_getBtn();
    if (mask & btnMask)
        return 1;
    else
        return 0;
}

void Inputs_BTN_clearBtnBuffer(void)
{
    pressed_btn = 0;
}

void Inputs_BTN_Init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    LL_EXTI_InitTypeDef EXTI_InitStruct;

    LL_AHB1_GRP1_EnableClock(BTN_LEFT_CLOCK);
    LL_AHB1_GRP1_EnableClock(BTN_RIGHT_CLOCK);
    LL_AHB1_GRP1_EnableClock(BTN_UP_CLOCK);
    LL_AHB1_GRP1_EnableClock(BTN_DOWN_CLOCK);
    LL_AHB1_GRP1_EnableClock(BTN_OK_CLOCK);
    LL_AHB1_GRP1_EnableClock(BTN_STOP_CLOCK);

    GPIO_InitStruct.Pin = BTN_LEFT_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    LL_GPIO_Init(BTN_LEFT_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BTN_RIGHT_PIN;
    LL_GPIO_Init(BTN_RIGHT_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BTN_UP_PIN;
    LL_GPIO_Init(BTN_UP_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BTN_DOWN_PIN;
    LL_GPIO_Init(BTN_DOWN_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BTN_OK_PIN;
    LL_GPIO_Init(BTN_OK_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BTN_STOP_PIN;
    LL_GPIO_Init(BTN_STOP_PORT, &GPIO_InitStruct);

    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE11);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE2);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE1);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE12);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE10);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE14);

    EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1 | LL_EXTI_LINE_2 | LL_EXTI_LINE_10 | LL_EXTI_LINE_11 | LL_EXTI_LINE_12 | LL_EXTI_LINE_14;
    EXTI_InitStruct.LineCommand = ENABLE;
    EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
    EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
    LL_EXTI_Init(&EXTI_InitStruct);

    NVIC_EnableIRQ(EXTI0_1_IRQn);
    NVIC_EnableIRQ(EXTI2_3_IRQn);
    NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void Inputs_ADC_Init(void)
{
    LL_ADC_InitTypeDef ADC_InitStruct;
    LL_ADC_REG_InitTypeDef ADC_REG_InitStruct;
    LL_DMA_InitTypeDef DMA_InitStruct;

    LL_GPIO_InitTypeDef GPIO_InitStruct;

    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

    LL_AHB1_GRP1_EnableClock(INTERNAL_THERMISTOR_CLOCK);
    LL_AHB1_GRP1_EnableClock(BATT_THERMISTOR_CLOCK);
    LL_AHB1_GRP1_EnableClock(VCC_IN_ADC_CLOCK);
    LL_AHB1_GRP1_EnableClock(V_BUS_ADC_CLOCK);
    LL_AHB1_GRP1_EnableClock(BATT_VTG_ADC_CLOCK);
    LL_AHB1_GRP1_EnableClock(FB_ADC_CLOCK);
    LL_AHB1_GRP1_EnableClock(CHARGE_CURR_ADC_CLOCK);
    LL_AHB1_GRP1_EnableClock(DISCHARGE_CURR_ADC_CLOCK);

    NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

    GPIO_InitStruct.Pin = BATT_VTG_ADC_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(BATT_VTG_ADC_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = V_BUS_ADC_PIN;
    LL_GPIO_Init(V_BUS_ADC_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = VCC_IN_ADC_PIN;
    LL_GPIO_Init(VCC_IN_ADC_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DISCHARGE_CURR_ADC_PIN;
    LL_GPIO_Init(DISCHARGE_CURR_ADC_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = CHARGE_CURR_ADC_PIN;
    LL_GPIO_Init(CHARGE_CURR_ADC_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BATT_THERMISTOR_PIN;
    LL_GPIO_Init(BATT_THERMISTOR_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = INTERNAL_THERMISTOR_PIN;
    LL_GPIO_Init(INTERNAL_THERMISTOR_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = FB_ADC_PIN;
    LL_GPIO_Init(FB_ADC_PORT, &GPIO_InitStruct);

    LL_DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
    DMA_InitStruct.Mode = LL_DMA_MODE_CIRCULAR;
    DMA_InitStruct.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
    DMA_InitStruct.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
    DMA_InitStruct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;
    DMA_InitStruct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;
    DMA_InitStruct.Priority = LL_DMA_PRIORITY_HIGH;
    DMA_InitStruct.MemoryOrM2MDstAddress = (uint32_t) & ADC_ConvertedValue;
    DMA_InitStruct.PeriphOrM2MSrcAddress = (uint32_t) & ADC1->DR;
    DMA_InitStruct.NbData = ADC_CHANNELS;
    DMA_InitStruct.Priority = LL_DMA_PRIORITY_MEDIUM;
    LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &DMA_InitStruct);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);

    LL_ADC_REG_SetSequencerChannels(ADC1, BATT_VTG_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, V_BUS_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, VCC_IN_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, DISCHARGE_CURR_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, CHARGE_CURR_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, BATT_THERMISTOR_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, INTERNAL_THERMISTOR_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, FB_ADC_CH);
    LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_16);
    LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_17);

    ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
    ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
    LL_ADC_Init(ADC1, &ADC_InitStruct);

    LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_ASYNC);

    ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_EXT_TIM3_TRGO;
    ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
    ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
    ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_LIMITED;
    ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
    LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);

    TIM3_Enable();
    SMART_DEBUGF(DEBUG_ADC, ("ADC calibrate ...", ADC1->DR));

    if ((ADC1->CR & ADC_CR_ADEN) != 0) {
        ADC1->CR |= ADC_CR_ADDIS;
    }
    while ((ADC1->CR & ADC_CR_ADEN) != 0) {
        /* For robust implementation, add here time-out management */
    }
    ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN;
    ADC1->CR |= ADC_CR_ADCAL;
    while ((ADC1->CR & ADC_CR_ADCAL) != 0) {
        /* For robust implementation, add here time-out management */
    }

    SMART_DEBUGF(DEBUG_ADC, ("calibration value: %ld\r\n", ADC1->DR));

    LL_ADC_Enable(ADC1);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);

    LL_ADC_REG_SetSequencerScanDirection(ADC1, LL_ADC_REG_SEQ_SCAN_DIR_FORWARD);

    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);

    LL_ADC_Enable(ADC1);
    LL_ADC_REG_StartConversion(ADC1);

    ADC->CCR |= ADC_CCR_VREFEN | ADC_CCR_TSEN; //enable VrefInt, cpu temperature

    SMART_DEBUGF(DEBUG_ADC, ("ADC chanels: %d\r\n", ADC_CHANNELS));

}

void ADC_Value(void)
{
    //    static uint8_t i = 0;
    //    SMART_DEBUGF(SMART_DEBUG_ON, ("0 %ld %ld\r\n", ADC_ConvertedValue[0], apply_Q(ADC_Val[0])));

    //    SMART_DEBUGF(SMART_DEBUG_ON, ("1 %ld %ld\r\n", ADC_ConvertedValue[1], apply_Q(ADC_Val[1])));
    //    SMART_DEBUGF(SMART_DEBUG_ON, ("Calib int %ld\r\n", __LL_ADC_CALC_VREFANALOG_VOLTAGE(apply_Q(ADC_Val[1]), LL_ADC_RESOLUTION_12B)));
    //    uint32_t val = __LL_ADC_CALC_VREFANALOG_VOLTAGE(apply_Q(ADC_Val[1]), LL_ADC_RESOLUTION_12B);
    //    uint32_t meas = __LL_ADC_CALC_DATA_TO_VOLTAGE(val, apply_Q(ADC_Val[0]), LL_ADC_RESOLUTION_12B);
    //    meas = meas * 152;
    //    meas = meas / 10;
    //    meas = meas - (16587/10);  

    //    SMART_DEBUGF(SMART_DEBUG_ON, ("Calib vol %ld\r\n", __LL_ADC_CALC_DATA_TO_VOLTAGE(val, apply_Q(ADC_Val[1]), LL_ADC_RESOLUTION_12B)));
    //    SMART_DEBUGF(SMART_DEBUG_ON, ("in volt %ld\r\n", meas));
    //    i++;
    //    if (i == 1)
    //        i = 0;
}

void Inputs_ADC_printValues(void)
{
    uint32_t val = __LL_ADC_CALC_VREFANALOG_VOLTAGE(apply_Q(ADC_Val[ADC_VREF]), LL_ADC_RESOLUTION_12B);
    for (uint8_t i = 0; i < ADC_CHANNELS; i++) {
        if (i == ADC_CPUTEMP)
            SMART_DEBUGF(DEBUG_ADC, ("ADC ch%d val %ld, temp %ld deg\r\n", i, apply_Q(ADC_Val[i]), __LL_ADC_CALC_TEMPERATURE(val, apply_Q(ADC_Val[i]), LL_ADC_RESOLUTION_12B)));
        else
            SMART_DEBUGF(DEBUG_ADC, ("ADC ch%d val %ld, vtg %ld mV\r\n", i, apply_Q(ADC_Val[i]), __LL_ADC_CALC_DATA_TO_VOLTAGE(val, apply_Q(ADC_Val[i]), LL_ADC_RESOLUTION_12B)));
    }

}

void Inputs_ADC_printChannel(ADC_Channels_e channel)
{
    SMART_DEBUGF(DEBUG_ADC, ("ADC ch%d val %ld,\r\n", channel, apply_Q(ADC_Val[channel])));
}

#define LTC6101_V_SENSE_CALCULATE(adc)  ((adc*330)/6800)

/**
 * @brief get ADC recalculate values
 * @param channel from enum ADC_Channels_e
 * @return value
 */
uint16_t Inputs_ADC_getRecalculatedValue(ADC_Channels_e channel)
{
    uint32_t value = 0;
    uint32_t ref = __LL_ADC_CALC_VREFANALOG_VOLTAGE(apply_Q(ADC_Val[ADC_VREF]), LL_ADC_RESOLUTION_12B);
    uint32_t adc = __LL_ADC_CALC_DATA_TO_VOLTAGE(ref, apply_Q(ADC_Val[channel]), LL_ADC_RESOLUTION_12B);
    switch (channel) {
    case ADC_V_BUS:
    case ADC_VCC_IN:
    {
        value = adc * 11;
        break;
    }
    case ADC_V_BATT:
    {
        value = adc * 11;
        break;
    }
    case ADC_FB_ADC:
    {
        value = (adc * 4667) / 1000;
        break;
    }
    case ADC_DISCHARGE_CURR:
    {
        value = (LTC6101_V_SENSE_CALCULATE(adc)*1000) / 30;
        break;
    }
    case ADC_CHARGE_CURR:
    {
        value = (LTC6101_V_SENSE_CALCULATE(adc)*1000) / 30;
        break;
    }
    case ADC_INTERNAL_THERMISTOR:
    {
        value = (uint16_t) adc;
        break;
    }
    }
    return (uint16_t) value;
}

void DMA1_Channel1_IRQHandler(void)
{
    if (LL_DMA_IsActiveFlag_TC1(DMA1)) {
        LL_ADC_REG_StartConversion(ADC1);
        for (uint32_t i = 0; i < ADC_CHANNELS; i++) {
            ADC_Val[i] -= apply_Q(ADC_Val[i]);
            ADC_Val[i] += ADC_ConvertedValue[i];
        }
        LL_DMA_ClearFlag_TC1(DMA1);
    }
}

void EXTI0_1_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
        setPressedBtn(BTN_UP_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn UP pressed\r\n"));
    }
}

void EXTI2_3_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
        setPressedBtn(BTN_RIGHT_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn RIGHT pressed\r\n"));
    }
}

void EXTI4_15_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
        setPressedBtn(BTN_OK_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn OK pressed\r\n"));
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
        setPressedBtn(BTN_LEFT_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn LEFT pressed\r\n"));
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
        setPressedBtn(BTN_DOWN_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn DOWN pressed\r\n"));
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_14)) {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
        setPressedBtn(BTN_STOP_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn STOP pressed\r\n"));
    }
}