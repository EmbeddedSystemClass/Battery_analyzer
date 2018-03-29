#include "internal_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "stm32f0xx_ll_tim.h"
 
void TIM3_Init(void)
{
  LL_TIM_InitTypeDef TIM_InitStruct;
 
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
  
  TIM_InitStruct.Prescaler = 0;
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