/** \addtogroup User
 * @{ */

/**
 * \defgroup Main
 *
 * This is main module. It is most important part of project. There
 * is an infinite loop of code, which contains reading of MPU, reading
 * of temp sensors, reading analog and digital inputs, process relay.
 * @{
 */

#include "stm32f0xx.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"
#include "pins.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_cortex.h"
#include "systick.h"
#include "stm32f0xx_hal.h"
#include "debug.h"
#include "directives.h"
#include "stm32f0xx_ll_iwdg.h"
#include <string.h>
#include "timer.h"
#include "LEDS.h"
#include "uart.h"
#include "i2c.h"
#include "eeprom.h"
#include "ssd1306.h"
#include "ugui.h"
#include "UI.h"
#include "inputs.h"
#include "internal_timer.h"

static void LL_Init(void);
static void SystemClock_Config(void);
void WDG_restart(void);

/**
 * @brief Instance for Independent Watchdog
 */
IWDG_TypeDef IWDG1;

/**
 * @brief Instance of struct timer for use functions from timer module
 */
struct timer tim;

UG_GUI gui;

/**
 * @brief Main function of whole project
 * @return none
 */
int main(void)
{
    LL_Init();
    Uart_LL_init();
    LEDS_init();

    ssd1306_rst_init();

    SMART_DEBUGF(DEBUG_INIT, ("\r\n------------------\r\n"));
    SMART_DEBUGF(DEBUG_INIT, ("Battery analyzer\r\n"));
    SMART_DEBUGF(DEBUG_INIT, ("  sw version %s\r\n", SW_VERSION));
    SMART_DEBUGF(DEBUG_INIT, ("  build %s\r\n", __TIME__));
    SMART_DEBUGF(DEBUG_INIT, ("------------------\r\n\r\n"));
    SMART_DEBUGF(DEBUG_INIT, ("System clock %ld MHz\r\n\r\n", SystemCoreClock / 1000000));

    LEDS_setColor((uint8_t[]) COLOR_YELLOW);
    LEDS_show();

    TIM3_Init();
    Inputs_BTN_Init();
    Inputs_ADC_Init();

    ssd1306_rst();

    I2C_LL_init();

    ssd1306_init();

    timer_set(&tim, 500);
    while (!timer_expired(&tim));
    ssd1306_Update_display();
    timer_reset(&tim);
    while (!timer_expired(&tim));
    UG_Init(&gui, pixelset, 128, 64);

    UG_FontSelect(&FONT_6X8_CZECH);
    UG_SetBackcolor(0);
    UG_SetForecolor(1);
    UG_FillScreen(200);
    ssd1306_Update_display();
    timer_reset(&tim);
    while (!timer_expired(&tim));

    UI_TIMER_Init();
    main_state_set(MAIN_STATE_NORMAL);
    TIM16_Init();
    while (1) {
        ;
    }

}

static void LL_Init(void)
{
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
    NVIC_SetPriority(SVC_IRQn, 0);
    NVIC_SetPriority(PendSV_IRQn, 0);
    NVIC_SetPriority(SysTick_IRQn, 0);
    SystemClock_Config();
    SysTick_Config(SystemCoreClock / 1000);

#if USE_WDT
    LL_IWDG_SetPrescaler(&IWDG1, LL_IWDG_PRESCALER_4);
    LL_IWDG_Enable(&IWDG1);
#endif
}

/**
 * @brief Restart watchdog timer, must be called in periodical time
 */
void WDG_restart(void)
{
#if USE_WDT
    LL_IWDG_ReloadCounter(&IWDG1);
#endif
}

static void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

    if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1) {
    }
    LL_RCC_HSI_Enable();

    /* Wait till HSI is ready */
    while (LL_RCC_HSI_IsReady() != 1) {

    }
    LL_RCC_HSI_SetCalibTrimming(16);

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);

    LL_RCC_PLL_Enable();

    /* Wait till PLL is ready */
    while (LL_RCC_PLL_IsReady() != 1) {

    }
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    /* Wait till System clock is ready */
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {

    }
    LL_Init1msTick(48000000);

    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);

    LL_SetSystemCoreClock(48000000);

    /* SysTick_IRQn interrupt configuration */
    NVIC_SetPriority(SysTick_IRQn, 0);
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(unsigned int * hf_args)
{

    volatile unsigned long stacked_r0;
    volatile unsigned long stacked_r1;
    volatile unsigned long stacked_r2;
    volatile unsigned long stacked_r3;
    volatile unsigned long stacked_r12;
    volatile unsigned long stacked_lr;
    volatile unsigned long stacked_pc;
    volatile unsigned long stacked_psr;

    stacked_r0 = ((unsigned long) hf_args[0]);
    stacked_r1 = ((unsigned long) hf_args[1]);
    stacked_r2 = ((unsigned long) hf_args[2]);
    stacked_r3 = ((unsigned long) hf_args[3]);
    stacked_r12 = ((unsigned long) hf_args[4]);
    stacked_lr = ((unsigned long) hf_args[5]);
    stacked_pc = ((unsigned long) hf_args[6]);
    stacked_psr = ((unsigned long) hf_args[7]);

    // debug_break();
    //    __BKPT();

    SMART_PRINTF("\r\n\r\n[Hard fault handler]\r\n");
    SMART_PRINTF("R0 = 0x%08lX\r\n", stacked_r0);
    SMART_PRINTF("R1 = 0x%08lX\r\n", stacked_r1);
    SMART_PRINTF("R2 = 0x%08lX\r\n", stacked_r2);
    SMART_PRINTF("R3 = 0x%08lX\r\n", stacked_r3);
    SMART_PRINTF("R12 = 0x%08lX\r\n", stacked_r12);
    SMART_PRINTF("LR [R14] = 0x%08lX  subroutine call return address\r\n", stacked_lr);
    SMART_PRINTF("PC [R15] = 0x%08lX  program counter\r\n", stacked_pc);
    SMART_PRINTF("PSR = 0x%08lX\r\n", stacked_psr);
    SMART_PRINTF("SHCSR = 0x%08lX\r\n", SCB->SHCSR); // System handler and control Register
    SMART_PRINTF("ICSR = 0x%08lX\r\n", SCB->ICSR); // Interrupt Control and State Register
    SMART_PRINTF("AIRCR = 0x%08lX\r\n", SCB->AIRCR); // Application Interrupt and Reset Control Register
    SMART_PRINTF("SCR = 0x%08lX\r\n", SCB->SCR); // System Control Register
    SMART_PRINTF("CCR = 0x%08lX\r\n", SCB->CCR); // Configuration Control Register
    SMART_PRINTF("SHP[0] = 0x%08lX\r\n", SCB->SHP[0]); // System Handlers Priority Registers. [0] is RESERVED
    SMART_PRINTF("SHP[1] = 0x%08lX\r\n", SCB->SHP[1]); // System Handlers Priority Registers. [0] is RESERVED

    while (1);
    //halt();
}

//void HardFault_Handler(void)
//{ 
//    print_hardFault();
//}