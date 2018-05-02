#include "battery.h"
#include "debug.h"
#include "inputs.h"

BatteryParam_s battery;
Battery_s lead;

void Battery_setState(Battery_controll_state_e newstate)
{
    battery.controll_state = newstate;
}

Battery_controll_state_e Battery_getState(void)
{
    return battery.controll_state;
}

void battery_Uset(uint32_t voltage)
{
    ;
}

void battery_Iset(uint32_t current)
{
    ;
}

uint32_t battery_Uget(void)
{
    return Inputs_ADC_getRecalgulatedValue(ADC_V_BATT);
}

uint32_t battery_Icharge_get(void)
{
    return Inputs_ADC_getRecalgulatedValue(ADC_CHARGE_CURR);
}

uint32_t battery_Idischarge_get(void)
{
    return Inputs_ADC_getRecalgulatedValue(ADC_DISCHARGE_CURR);
}

uint32_t battery_UccGet(void)
{
    return Inputs_ADC_getRecalgulatedValue(ADC_FB_ADC);
}