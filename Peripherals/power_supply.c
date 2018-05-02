#include "power_supply.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "stm32f0xx_ll_tim.h"
#include "debug.h"
#include "inputs.h"
#include "pid_controller.h"

static void TIM1_GPIO_Init(void);
void TIM1_Init(void);
void TIM6_Init(void);
void StepdownProcess (void);

PIDControl PID_stepdown;

void PowerSupply_Init(void)
{
    //PIDInit(&PID_stepdown, 1.5, 1.1, 0, 0.001, 0, 1000, AUTOMATIC, DIRECT);  
    PIDInit(&PID_stepdown, 1.1, 1, 0, 0.001, 0, 1000, AUTOMATIC, DIRECT);  
    PIDSetpointSet(&PID_stepdown,580);
    TIM1_GPIO_Init();
    TIM1_Init();
    TIM6_Init();  
}

/* TIM1 init function */
void TIM1_Init(void)
{

  LL_TIM_InitTypeDef TIM_InitStruct;

  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct;
  LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct;
  
  /* Peripheral clock enable */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  /* TIM1 interrupt Init */
  //NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0);
  //NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 1000;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM1, &TIM_InitStruct);

  LL_TIM_EnableARRPreload(TIM1);

  LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_RESET);

  LL_TIM_DisableMasterSlaveMode(TIM1);
  
  
  LL_TIM_DisableARRPreload(TIM1);

  LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1);
  LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1N);

  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_ENABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
  TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_HIGH;
  LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

  //LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH1);

  TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_ENABLE;
  TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_ENABLE;
  TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
  TIM_BDTRInitStruct.DeadTime = 20;
  TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
  TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_LOW;
  TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_ENABLE;
  LL_TIM_BDTR_Init(TIM1, &TIM_BDTRInitStruct);
  
  
 
  //LL_TIM_EnableIT_UPDATE(TIM1);
  LL_TIM_EnableCounter(TIM1);

}

/* TIM6 init function */
void TIM6_Init(void)
{

  LL_TIM_InitTypeDef TIM_InitStruct;

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

  /* TIM6 interrupt Init */
  NVIC_SetPriority(TIM6_IRQn, 0);
  NVIC_EnableIRQ(TIM6_IRQn);

  TIM_InitStruct.Prescaler = 48;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 1000;
  LL_TIM_Init(TIM6, &TIM_InitStruct);

  LL_TIM_EnableARRPreload(TIM6);
  LL_TIM_EnableIT_UPDATE(TIM6);
   LL_TIM_EnableCounter(TIM6);
}



/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PB6   ------> USART1_TX
     PB7   ------> USART1_RX
*/
static void TIM1_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

  /**/
  GPIO_InitStruct.Pin = SMPS_PMOS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
  LL_GPIO_Init(SMPS_PMOS_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SMPS_NMOS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
  LL_GPIO_Init(SMPS_NMOS_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = DISCHG_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
  LL_GPIO_Init(DISCHG_GPIO_Port, &GPIO_InitStruct);

}

#define NAPETI 4321
void TIM6_IRQHandler(void)
{
    static uint16_t i=0;
    if(LL_TIM_IsActiveFlag_UPDATE(TIM6))
    {
        LL_TIM_ClearFlag_UPDATE(TIM6);
        StepdownProcess();
        
    }
}

#define CONSTANT_VOLTAGE 0
#define CONSTANT_CURRENT 1

uint32_t mode=CONSTANT_CURRENT;

void StepdownProcess (void)
{
    uint16_t value=0;
    if(mode==CONSTANT_VOLTAGE)
    {
        value=Inputs_ADC_getRecalculatedValue(ADC_FB_ADC);
    }
    else if(mode==CONSTANT_CURRENT)
    {
        value=Inputs_ADC_getRecalculatedValue(ADC_CHARGE_CURR);
        if(Inputs_ADC_getRecalculatedValue(ADC_FB_ADC)<4500) value=0;
    }
        
        PIDInputSet(&PID_stepdown,value);
        PIDCompute(&PID_stepdown);
        uint16_t n=PIDOutputGet(&PID_stepdown);
      //  uint16_t value=Inputs_ADC_getRecalculatedValue(ADC_FB_ADC);
        
        
        //if(value<NAPETI) i++;
        //else if (value>NAPETI) i--;
        //if(i<1000)i++;
        //else i=0;
//Inputs_ADC_printValues();
        //SMART_DEBUGF(DEBUG_POWER, ("U: %d,%d,%d \r\n",Inputs_ADC_getRecalculatedValue(ADC_FB_ADC),n,Inputs_ADC_getRecalculatedValue(ADC_CHARGE_CURR) ));
       // Inputs_ADC_printChannel(ADC_CHARGE_CURR);
        LL_TIM_OC_SetCompareCH1(TIM1, n);
}