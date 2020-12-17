/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    stm32x_bsp.c
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "kitsprout\kSystem.h"
#include "drivers\stm32l0_tim.h"
#include "modules\serial.h"
#include "stm32x_bsp.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/

void bsp_gpio_init( void )
{
    HAL_Init();
    SystemClock_Config();

    GPIO_InitTypeDef GPIO_InitStruct;

    /* Enable all GPIO Clk *******************************************************/
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* GPIO all analog input *****************************************************/
    GPIO_InitStruct.Pin   = GPIO_PIN_All;
    GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.Pin   = GPIO_PIN_All & (~(GPIO_PIN_13 | GPIO_PIN_14));
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LED_R_Off();
    LED_G_Off();
    LED_B_Off();

    /* GPIO Pin ******************************************************************/
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    GPIO_InitStruct.Pin   = LED_R_PIN;
    HAL_GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin   = LED_G_PIN;
    HAL_GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin   = LED_B_PIN;
    HAL_GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin   = BUZ_PIN;
    HAL_GPIO_Init(BUZ_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    GPIO_InitStruct.Pin   = KEY_PIN;
    HAL_GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStruct);
}

void bsp_timer_init( pFunc event )
{
    htim2.tickEventCallback = event;
    Timer2_Config(SystemCoreClock / 1000000, 5000);
}

void bsp_timer_enable( uint32_t state )
{
    Timer2_Cmd(state);
}

void bsp_uart_serial_init( pFunc event )
{
    hserial.rxEventCallback = event;

    Serial_Config();
    printf("\r\n\f\r\n");
}

/*************************************** END OF FILE ****************************************/
