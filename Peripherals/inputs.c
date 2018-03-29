#include "inputs.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "stm32f0xx_ll_exti.h"
#include "debug.h"
#include "directives.h"

static uint8_t pressed_btn;

static void setPressedBtn(uint8_t btnMask)
{
    pressed_btn = btnMask;
}

uint8_t Inputs_BTN_getBtn(void)
{
    uint8_t temp = pressed_btn;
    pressed_btn = 0;
    return temp;
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

void EXTI0_1_IRQHandler(void) {
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1))
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
        setPressedBtn(BTN_UP_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn UP pressed\r\n"));
    }
}

void EXTI2_3_IRQHandler(void) {
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_2))
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
        setPressedBtn(BTN_RIGHT_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn RIGHT pressed\r\n"));
    }
}

void EXTI4_15_IRQHandler(void) {
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10))
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);
        setPressedBtn(BTN_OK_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn OK pressed\r\n"));
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11))
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
        setPressedBtn(BTN_LEFT_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn LEFT pressed\r\n"));
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12))
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
        setPressedBtn(BTN_DOWN_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn DOWN pressed\r\n"));
    }
    if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_14))
    {
        LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
        setPressedBtn(BTN_STOP_MASK);
        SMART_DEBUGF(DEBUG_BTN, ("Btn STOP pressed\r\n"));
    }
}