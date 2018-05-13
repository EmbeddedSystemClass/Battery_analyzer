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
#include "battery.h"

static void PowerSupply_GPIO_Init(void);
static void TIM1_Init(void);
static void TIM6_Init(void);
static void PowerProcess(void);

//staticke promenne pro set/get
static PowerSupplyMode_e power_supply_mode = STOP;

static PowerSupplyTypeDef power_supply;


PIDControl PID_power_supply;

static uint32_t mode = CHARGE_CONSTANT_VOLTAGE;

void PowerSupply_Init(void)
{
    power_supply.mode = STOP;

    //PIDInit(&PID_stepdown, 1.5, 1.1, 0, 0.001, 0, 1000, AUTOMATIC, DIRECT);  
    //PIDInit(&PID_power_supply, 1.1, 1, 0, 0.001, 0, 1000, AUTOMATIC, DIRECT);
    //PIDSetpointSet(&PID_power_supply, 580);
    PowerSupply_GPIO_Init();
    TIM1_Init();
    TIM6_Init();
    PowerSupply_Set(STOP,0,0);
    //PowerSupply_Set(DISCHARGE, 11500, 100-12);
}

/* TIM1 init function */
static void TIM1_Init(void)
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


    LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH2);

    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
    TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
    TIM_OC_InitStruct.CompareValue = 0;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_LOW;
    TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
    TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
    LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);


    //LL_TIM_EnableIT_UPDATE(TIM1);
    LL_TIM_EnableCounter(TIM1);

}

/* TIM6 init function */
static void TIM6_Init(void)
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

static void PowerSupply_GPIO_Init(void)
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

    GPIO_InitStruct.Pin = DISCHG_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
    LL_GPIO_Init(DISCHG_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = FAN_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(FAN_GPIO_Port, &GPIO_InitStruct);
    LL_GPIO_ResetOutputPin(FAN_GPIO_Port, FAN_Pin);
    
    GPIO_InitStruct.Pin = V_BATT_RANGE_Pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(V_BATT_RANGE_GPIO_Port, &GPIO_InitStruct);
    LL_GPIO_SetOutputPin(V_BATT_RANGE_GPIO_Port, V_BATT_RANGE_Pin);
}

void TIM6_IRQHandler(void)
{
    static uint16_t i = 0;
    if (LL_TIM_IsActiveFlag_UPDATE(TIM6)) {
        LL_TIM_ClearFlag_UPDATE(TIM6);
        PowerProcess();

    }
}

static void PowerProcess(void)
{
    uint16_t voltage = 0;
    uint16_t current = 0;

    switch (power_supply.mode) {
    case DISCHARGE:
    {
        LL_TIM_OC_SetCompareCH1(TIM1, 0); //zastaveni nabijeni

        voltage = Inputs_ADC_getRecalculatedValue(ADC_V_BATT);
        //current = Inputs_ADC_getRecalculatedValue(ADC_DISCHARGE_CURR);
        current = Inputs_ADC_getRecalculatedValue(ADC_DISCHARGE_CURR);

        if (voltage < power_supply.min_voltage) current = power_supply.max_current + 1; //umela indikace dosazenim vetsiho proudu nez nastaveny => snizi se proud aby napeti nekleslo pod minimum
        PIDInputSet(&PID_power_supply, current);
        PIDCompute(&PID_power_supply);
        current = PIDOutputGet(&PID_power_supply);
        SMART_DEBUGF(DEBUG_POWER, ("%d\r\n", current));
        LL_TIM_OC_SetCompareCH2(TIM1, current);

        break;
    }
    case CHARGE_CONSTANT_VOLTAGE:
    {
        LL_TIM_OC_SetCompareCH2(TIM1, 0); //zastaveni vybijeni

        voltage = Inputs_ADC_getRecalculatedValue(ADC_V_BATT);
        current = Inputs_ADC_getRecalculatedValue(ADC_CHARGE_CURR);

        if (current > power_supply.max_current) voltage = power_supply.max_voltage + 1; //umela indikace dosazenim vetsiho napeti nez je maximum => snizi se napeti aby nebyl prekrocen maximalni proud

        PIDInputSet(&PID_power_supply, voltage);
        PIDCompute(&PID_power_supply);
        voltage = PIDOutputGet(&PID_power_supply);
        LL_TIM_OC_SetCompareCH1(TIM1, voltage);

        break;
    }
    case CHARGE_CONSTANT_CURRENT:
    {
        LL_TIM_OC_SetCompareCH2(TIM1, 0); //zastaveni vybijeni

        voltage = Inputs_ADC_getRecalculatedValue(ADC_V_BATT);
        current = Inputs_ADC_getRecalculatedValue(ADC_CHARGE_CURR);

        //napeti nesmi klesnout pod minimum
        if (voltage < MIN_VOLTAGE) current = 0; //umele zvyseni proudu
            //napeti nesmi prerust maximum
        else if (voltage > power_supply.max_voltage) current = power_supply.max_current + 1; //umela indikace dosazenim vetsiho proudu nez je maximum => snizi se proud aby nebylo prekroceno maximalni napeti

        PIDInputSet(&PID_power_supply, current);
        PIDCompute(&PID_power_supply);
        current = PIDOutputGet(&PID_power_supply);

        LL_TIM_OC_SetCompareCH1(TIM1, current);
        break;
    }
    case STOP:
    {
        LL_TIM_OC_SetCompareCH1(TIM1, 0); //zastaveni nabijeni
        LL_TIM_OC_SetCompareCH2(TIM1, 0); //zastaveni vybijeni
        break;
    }
    default:
        break;
    }
}

void PowerSupply_Set(PowerSupplyMode_e mode, uint32_t voltage, uint32_t current)
{
    switch (mode) {
    case DISCHARGE:
    {
        if (current > MAX_DISCHG_CURRENT) current = MAX_DISCHG_CURRENT;
        //prepnuti z jineho stavu
        if (power_supply.mode != DISCHARGE) {
            power_supply.mode = DISCHARGE;
            PIDInit(&PID_power_supply, 1.1,1, 0, 0.001, 300, 1000, AUTOMATIC, DIRECT); //reinicializace => vycisteni aktualnich promennych => vystupni hodnota bude ihned 0
        }

        power_supply.min_current = current;
        power_supply.max_current = current;
        power_supply.current_current = current;
        power_supply.min_voltage = voltage;
        power_supply.max_voltage = MAX_VOLTAGE;
        power_supply.current_voltage = 0;
        PIDSetpointSet(&PID_power_supply, current);

        LL_GPIO_SetOutputPin(FAN_GPIO_Port, FAN_Pin);
        break;
    }
    case CHARGE_CONSTANT_VOLTAGE:
    {
        //prepnuti z jineho stavu
        if (power_supply.mode != CHARGE_CONSTANT_VOLTAGE) {
            power_supply.mode = CHARGE_CONSTANT_VOLTAGE;
            PIDInit(&PID_power_supply, 1.1, 1, 0, 0.001, 0, 1000, AUTOMATIC, DIRECT); //reinicializace => vycisteni aktualnich promennych => vystupni hodnota bude ihned 0
        }

        power_supply.min_current = MIN_CURRENT;
        power_supply.max_current = current;
        power_supply.current_current = 0;
        power_supply.min_voltage = voltage;
        power_supply.max_voltage = voltage;
        power_supply.current_voltage = voltage;
        PIDSetpointSet(&PID_power_supply, voltage);

        LL_GPIO_ResetOutputPin(FAN_GPIO_Port, FAN_Pin);
        break;
    }
    case CHARGE_CONSTANT_CURRENT:
    {
        //prepnuti z jineho stavu
        if (power_supply.mode != CHARGE_CONSTANT_CURRENT) {
            power_supply.mode = CHARGE_CONSTANT_CURRENT;
            PIDInit(&PID_power_supply, 1.1, 1, 0, 0.001, 0, 1000, AUTOMATIC, DIRECT); //reinicializace => vycisteni aktualnich promennych => vystupni hodnota bude ihned 0
        }

        power_supply.min_current = current;
        power_supply.max_current = current;
        power_supply.current_current = current;
        power_supply.min_voltage = MIN_VOLTAGE;
        power_supply.max_voltage = voltage;
        power_supply.current_voltage = 0;
        PIDSetpointSet(&PID_power_supply, current);

        LL_GPIO_ResetOutputPin(FAN_GPIO_Port, FAN_Pin);
        break;
    }
    case STOP:
    {
        //prepnuti z jineho stavu
        if (power_supply.mode != STOP) {
            power_supply.mode = STOP;
            PIDInit(&PID_power_supply, 1.1, 1, 0, 0.001, 0, 1000, AUTOMATIC, DIRECT); //reinicializace => vycisteni aktualnich promennych => vystupni hodnota bude ihned 0
        }

        power_supply.min_current = 0;
        power_supply.max_current = 0;
        power_supply.current_current = 0;
        power_supply.min_voltage = 0;
        power_supply.max_voltage = 0;
        power_supply.current_voltage = 0;
        PIDSetpointSet(&PID_power_supply, 0);
        
        LL_GPIO_ResetOutputPin(FAN_GPIO_Port, FAN_Pin);
        break;
    }
    default:
        break;
    }
}
