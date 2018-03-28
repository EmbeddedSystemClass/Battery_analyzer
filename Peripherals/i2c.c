#include "i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "stm32f0xx_ll_i2c.h"
#include "debug.h"

void I2C_LL_init(void)
{
    uint32_t status;
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    LL_I2C_InitTypeDef I2C_InitStruct;

    LL_AHB1_GRP1_EnableClock(I2C_PINS_CLOCK);
    LL_APB1_GRP1_EnableClock(I2C_CLOCK);

    GPIO_InitStruct.Pin = I2C_SDA_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
//    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = I2C_AF;
    LL_GPIO_Init(I2C_PINS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = I2C_SCL_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
//    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = I2C_AF;
    LL_GPIO_Init(I2C_PINS_PORT, &GPIO_InitStruct);

    I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
    I2C_InitStruct.Timing = 0x2010091A;
    I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
    I2C_InitStruct.DigitalFilter = 0;
    I2C_InitStruct.OwnAddress1 = 0;
    I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
    I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
    status = LL_I2C_Init(I2C, &I2C_InitStruct);

    LL_I2C_EnableAutoEndMode(I2C);
    LL_I2C_SetOwnAddress2(I2C, 0, LL_I2C_OWNADDRESS2_NOMASK);
    LL_I2C_DisableOwnAddress2(I2C);
    LL_I2C_DisableGeneralCall(I2C);
    LL_I2C_EnableClockStretching(I2C);
    LL_I2C_Enable(I2C);
    SMART_DEBUGF(DEBUG_INIT, ("I2C initialization %s\r\n", status == SUCCESS ? "OK" : "ERROR"));
}
