#include "eeprom.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "stm32f0xx_ll_i2c.h"
#include "debug.h"

void EEPROM_WriteByte(uint16_t Addr, uint8_t Data)
{
    uint8_t TxBuffer[3];
    TxBuffer[0] = (Addr >> 8) & 0xff;
    TxBuffer[1] = (Addr) & 0xff;
    TxBuffer[2] = Data;
    uint8_t TxIndex = 0;
#if 0
    LL_I2C_HandleTransfer(I2C, EEPROM_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, 3, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
    while (!LL_I2C_IsActiveFlag_STOP(I2C)) // Loop until end of transfer received (STOP flag raised)
    {
        if (LL_I2C_IsActiveFlag_TXIS(I2C)) {
            /* Write data in Transmit Data register. TXIS flag is cleared by writing data in TXDR register */
            LL_I2C_TransmitData8(I2C, TxBuffer[TxIndex]);
            TxIndex++;
        }
    }
    LL_I2C_ClearFlag_STOP(I2C);
#else
//    while (LL_I2C_IsActiveFlag_BUSY(I2C) == RESET);
    LL_I2C_HandleTransfer(I2C, EEPROM_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, 3, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
    
    while (LL_I2C_IsActiveFlag_TXIS(I2C) != RESET);
    LL_I2C_TransmitData8(I2C, TxBuffer[0]);
    while (LL_I2C_IsActiveFlag_TXIS(I2C) != RESET);
    LL_I2C_TransmitData8(I2C, TxBuffer[1]);
    while (LL_I2C_IsActiveFlag_TXIS(I2C) != RESET);
    LL_I2C_TransmitData8(I2C, TxBuffer[2]);
    
    while (LL_I2C_IsActiveFlag_STOP(I2C) != RESET);
    LL_I2C_ClearFlag_STOP(I2C);
#endif
    
    SMART_DEBUGF(DEBUG_I2C, ("EEPROM write at: %d, 0x%02X\r\n", Addr, Data));
}

uint8_t EEPROM_ReadByte(uint8_t Addr)
{
    uint8_t TxBuffer[2];
    TxBuffer[0] = (Addr >> 8) & 0xff;
    TxBuffer[1] = (Addr) & 0xff;
    uint8_t TxIndex = 0;
    uint8_t buffer = 0;
#if 0
    LL_I2C_HandleTransfer(I2C, EEPROM_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, ubNbDataToTransmit_I2C, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
    while (!LL_I2C_IsActiveFlag_STOP(I2C)) // Loop until end of transfer received (STOP flag raised)
    {
        /* Check TXIS flag value in ISR register */
        if (LL_I2C_IsActiveFlag_TXIS(I2C)) {
            /* Write data in Transmit Data register. TXIS flag is cleared by writing data in TXDR register */
            LL_I2C_TransmitData8(I2C, TxBuffer[TxIndex]);
            TxIndex++;
        }
    }

    LL_I2C_HandleTransfer(I2C, EEPROM_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

    while (!LL_I2C_IsActiveFlag_STOP(I2C)) // Loop until end of transfer received (STOP flag raised)
    {
        /* Check RXNE flag value in ISR register */
        if (LL_I2C_IsActiveFlag_RXNE(I2C)) {
            /* Read character in Receive Data register. RXNE flag is cleared by reading data in RXDR register */
            buffer = LL_I2C_ReceiveData8(I2C);
        }
    }
    
    while (LL_I2C_IsActiveFlag_STOP(I2C) != RESET);
    LL_I2C_ClearFlag_STOP(I2C);
#else
//    while (LL_I2C_IsActiveFlag_BUSY(I2C))
//    {
//    }
    LL_I2C_HandleTransfer(I2C, EEPROM_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, 2, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

    while (LL_I2C_IsActiveFlag_TXIS(I2C) != RESET);
    LL_I2C_TransmitData8(I2C, TxBuffer[0]);
    while (LL_I2C_IsActiveFlag_TXIS(I2C) != RESET);
    LL_I2C_TransmitData8(I2C, TxBuffer[1]);

    LL_I2C_HandleTransfer(I2C, EEPROM_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

    while (LL_I2C_IsActiveFlag_RXNE(I2C) != RESET);
    buffer = LL_I2C_ReceiveData8(I2C);
    
    while (LL_I2C_IsActiveFlag_STOP(I2C) == RESET);
    LL_I2C_ClearFlag_STOP(I2C);
#endif

    SMART_DEBUGF(DEBUG_I2C, ("EEPROM read from: %d, %d\r\n", Addr, buffer));
    return buffer;
}