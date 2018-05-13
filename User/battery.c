#include "battery.h"
#include "debug.h"
#include "inputs.h"

BatteryParam_s battery;
Battery_s lead;

uint32_t t_last;

typedef enum {
    CHARGING_STATE_CC = 0,
    CHARGING_STATE_CV,
    CHARGING_STATE_STOP,
} CHARGING_STATES_t;

static CHARGING_STATES_t charging_state = CHARGING_STATE_CC;

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

void battery_Icharge_set(uint32_t current)
{
    ;
}

void battery_Idischarge_set(uint32_t current)
{
    ;
}

uint32_t battery_Uget(void)
{
    return Inputs_ADC_getRecalculatedValue(ADC_FB_ADC);
}

uint32_t battery_Icharge_get(void)
{
    return Inputs_ADC_getRecalculatedValue(ADC_CHARGE_CURR);
}

uint32_t battery_Idischarge_get(void)
{
    return Inputs_ADC_getRecalculatedValue(ADC_DISCHARGE_CURR);
}

uint32_t battery_UccGet(void)
{
    return Inputs_ADC_getRecalculatedValue(ADC_FB_ADC);
}

uint32_t battery_Capacity(uint32_t capacity, uint32_t t)//mAmVs  
{
    if (Battery_getState() == BATTERY_CHARGE)
        capacity += battery_Icharge_get()*(t - t_last);
    if (Battery_getState() == BATTERY_DISCHARGE)
        capacity += battery_Idischarge_get()*(t - t_last);
    t_last = t;
    return capacity;
}

uint64_t charge_Pb_Acid(uint32_t t, uint64_t cappacity)
{
    if (Battery_getState() == BATTERY_STOP)
        charging_state = CHARGING_STATE_STOP;
    if (t > lead.Max_charging_time)
        charging_state = CHARGING_STATE_STOP;
    if (battery_UccGet() < (lead.Ucharge_cell * lead.Cells) + 1000)
        charging_state = CHARGING_STATE_STOP;
    battery_Capacity(cappacity, t);

    switch (charging_state) {
    case CHARGING_STATE_CC:
        battery_Icharge_set(lead.Icharge);
        if (battery_Uget() >= lead.Cells * lead.Ucharge_cell)
            charging_state = CHARGING_STATE_CV;
        //          LEDS_setColor(COLOR_RED);
        break;

    case CHARGING_STATE_CV:
        battery_Uset(lead.Cells * lead.Ucharge_cell);
        if (battery_Icharge_get() <= lead.Icutoff)
            charging_state = CHARGING_STATE_STOP;
        //            LEDS_setColor(COLOR_ORANGE);            
        break;

    case CHARGING_STATE_STOP:
        battery_Icharge_set(0);
        //            LEDS_setColor(COLOR_RED);
        break;

    }
    return (cappacity);
}

uint64_t battery_discharge(uint32_t t, uint64_t cappacity)
{
    if (Battery_getState() != BATTERY_DISCHARGE)
        Battery_setState(BATTERY_STOP);
    if (battery_Uget() > lead.Udischarge_minimal * lead.Cells)
        battery_Idischarge_set(lead.Idischarge);
    battery_Capacity(cappacity, t);
}
