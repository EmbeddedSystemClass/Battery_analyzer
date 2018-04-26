#include "battery.h"
#include "debug.h"
#include "inputs.h"

BatteryParam_s battery;

void battery_Uset(uint32_t voltage)
{
    battery.voltage = voltage;
}

void battery_Iset(uint32_t current)
{
    battery.current = current;
}

uint32_t battery_Uget(void)
{
    return battery.voltage;
}

uint32_t battery_Iget(void)
{
    return battery.current;
}

uint32_t battery_UccGet(void)
{
    return Inputs_ADC_getRecalgulatedValue(ADC_FB_ADC);
}