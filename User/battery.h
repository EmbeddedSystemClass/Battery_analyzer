/** \addtogroup User
 * @{ */

/**
 * \defgroup Battery
 *
 * There is implemented battery charging and discharging process
 * @{
 */

#ifndef BATTERY_H
#define BATTERY_H

#include "stm32f0xx.h"

typedef enum {
    BATTERY_STOP,
    BATTERY_CHARGE,
    BATTERY_DISCHARGE,
} Battery_controll_state_e;

typedef enum {
    BATTERY_LEAD,
    BATTERY_LIION
} Battery_types_e;

typedef struct {
    uint32_t Icharge;
    uint32_t Ucharge_cell;
    uint32_t Cells;
    uint32_t Ucutoff;
    uint32_t Max_charging_time;
    uint32_t Udischarge_minimal;
    uint32_t Idischarge;
    uint32_t ReadOutTimeout;
} Battery_s;

typedef struct {
    Battery_controll_state_e controll_state;
    Battery_types_e battery_type;
} BatteryParam_s;

void battery_Uset(uint32_t voltage);
void battery_Icharge_set(uint32_t current);
void battery_Idischarge_set(uint32_t current);
uint32_t battery_Uget(void);
uint32_t battery_Icharge_get(void);
uint32_t battery_Idischarge_get(void);
uint32_t battery_UccGet(void);
void Battery_setState(Battery_controll_state_e newstate);
Battery_controll_state_e Battery_getState(void);
uint32_t battery_Capacity(uint32_t cappacity, uint32_t t);
uint64_t charge_Pb_Acid (uint32_t t, uint64_t cappacity);
void Battery_setType(Battery_types_e newtype);
Battery_types_e Battery_getType(void);
extern Battery_s lead;
void battery_process(void);
long map(long x, long in_min, long in_max, long out_min, long out_max);
#endif /* BATTERY_H */
