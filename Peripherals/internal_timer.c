#include "internal_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "stm32f0xx_ll_tim.h"

volatile uint32_t seconds;

void TIM3_Init(void)
{
    LL_TIM_InitTypeDef TIM_InitStruct;

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

    TIM_InitStruct.Prescaler = 10;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 0x4560;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM3, &TIM_InitStruct);

    LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_UPDATE);
}

void TIM3_Enable(void)
{
    LL_TIM_EnableCounter(TIM3);
}

void TIM16_Init(void)
{
#define CLOCK_TIMER_PERIOD ((48000000 / 1000 ) - 1)

    LL_TIM_InitTypeDef TIM_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM16);

    /* TIM15 interrupt Init */
    NVIC_SetPriority(TIM16_IRQn, 3);
    NVIC_EnableIRQ(TIM16_IRQn);

    TIM_InitStruct.Prescaler = 4800;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 10025;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM16, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM16);
    LL_TIM_EnableIT_UPDATE(TIM16);

    LL_TIM_SetClockSource(TIM16, LL_TIM_CLOCKSOURCE_INTERNAL);

    LL_TIM_SetTriggerOutput(TIM16, LL_TIM_TRGO_RESET);

    LL_TIM_DisableMasterSlaveMode(TIM16);
    LL_TIM_EnableCounter(TIM16);

}

void TIM16_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM16) != RESET) {
        LL_TIM_ClearFlag_UPDATE(TIM16);
        seconds++;
    }
}

uint32_t TIM16_getSeconds(void)
{
    return seconds;
}