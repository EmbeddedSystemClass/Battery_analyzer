#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"

void Uart_LL_init(void)
{
    LL_USART_InitTypeDef USART_InitStruct;
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    LL_USART_ClockInitTypeDef USART_Clock_InitStruct;

    LL_USART_ClockStructInit(&USART_Clock_InitStruct);
    LL_USART_ClockInit(UART_UART, &USART_Clock_InitStruct);

    LL_AHB1_GRP1_EnableClock(UART_PINS_CLOCK);
    LL_APB1_GRP2_EnableClock(UART_UART_CLOCK);
    GPIO_InitStruct.Pin = UART_TX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = UART_AF;
    LL_GPIO_Init(UART_PINS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = UART_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    GPIO_InitStruct.Alternate = UART_AF;
    LL_GPIO_Init(UART_PINS_PORT, &GPIO_InitStruct);

    USART_InitStruct.BaudRate = UART_SPEED;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_8;
    LL_USART_Init(UART_UART, &USART_InitStruct);
    
    LL_USART_Enable(UART_UART);
}


void uart_putchar(int ch)
{
    uint8_t c = ch;
    while (LL_USART_IsActiveFlag_TC(UART_UART) != SET);
    LL_USART_TransmitData8(UART_UART, c);
}
