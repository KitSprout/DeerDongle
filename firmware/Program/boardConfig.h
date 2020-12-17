/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    boardConfig.h
 *  @author  KitSprout
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __BOARDCONFIG_H
#define __BOARDCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Define ----------------------------------------------------------------------------------*/

#define KS_HW_BOARD_NAME                        "NULL"
#define KS_HW_MCU_NAME                          "STM32L011F4U6"

#define KS_HW_USE_CLOCK_SOUCE_INT               (0U)
#define KS_HW_USE_CLOCK_SOUCE_EXT               (1U)
#define KS_HW_HCLOCK_SOUCE                      KS_HW_USE_CLOCK_SOUCE_INT
#define KS_HW_LCLOCK_SOUCE                      KS_HW_USE_CLOCK_SOUCE_INT

#define KS_FW_UART_HAL_LIBRARY                  (0U)
#define KS_FW_I2C_HAL_LIBRARY                   (0U)


/* -------- LED and KEY */

#define LED_R_PIN                               GPIO_PIN_4
#define LED_R_GPIO_PORT                         GPIOA
#define LED_R_Set()                             __GPIO_SET(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Reset()                           __GPIO_RST(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Toggle()                          __GPIO_TOG(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_On()                              LED_R_Reset()
#define LED_R_Off()                             LED_R_Set()

#define LED_G_PIN                               GPIO_PIN_5
#define LED_G_GPIO_PORT                         GPIOA
#define LED_G_Set()                             __GPIO_SET(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Reset()                           __GPIO_RST(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Toggle()                          __GPIO_TOG(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_On()                              LED_G_Reset()
#define LED_G_Off()                             LED_G_Set()

#define LED_B_PIN                               GPIO_PIN_6
#define LED_B_GPIO_PORT                         GPIOA
#define LED_B_Set()                             __GPIO_SET(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Reset()                           __GPIO_RST(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Toggle()                          __GPIO_TOG(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_On()                              LED_B_Reset()
#define LED_B_Off()                             LED_B_Set()

#define KEY_PIN                                 GPIO_PIN_9
#define KEY_GPIO_PORT                           GPIOB
#define KEY_READ()                              (__GPIO_READ(KEY_GPIO_PORT, KEY_PIN) == KEY_PIN)


/* -------- TIM Timer */

#define TIMER2                                  TIM2
#define TIMER2_CLK_ENABLE()                     __HAL_RCC_TIM2_CLK_ENABLE()
#define TIMER2_IRQn                             TIM2_IRQn
#define TIMER2_TIMx_IRQHandler                  TIM2_IRQHandler
#define TIMER2_TIMx_IRQn_PREEMPT                0U
#define TIMER2_TIMx_IRQn_SUB                    1U


/* -------- UART Serial */

#define SERIAL_MAX_TXBUF                        16
#define SERIAL_MAX_RXBUF                        16

#define SERIAL_UARTx                            USART2
#define SERIAL_UARTx_CLK_ENABLE()               __HAL_RCC_USART2_CLK_ENABLE()
#define SERIAL_UARTx_IRQn                       USART2_IRQn
#define SERIAL_UARTx_IRQHandler                 USART2_IRQHandler
#define SERIAL_UARTx_IRQn_PREEMPT               0U
#define SERIAL_UARTx_IRQn_SUB                   1U

#define SERIAL_UARTx_FORCE_RESET()              __HAL_RCC_USART2_FORCE_RESET()
#define SERIAL_UARTx_RELEASE_RESET()            __HAL_RCC_USART2_RELEASE_RESET()

#define SERIAL_TX_PIN                           GPIO_PIN_9
#define SERIAL_TX_GPIO_PORT                     GPIOA
#define SERIAL_TX_AF                            GPIO_AF4_USART2

#define SERIAL_RX_PIN                           GPIO_PIN_10
#define SERIAL_RX_GPIO_PORT                     GPIOA
#define SERIAL_RX_AF                            GPIO_AF4_USART2

#define SERIAL_BAUDRATE                         115200
#define SERIAL_BYTESIZE                         UART_WORDLENGTH_8B
#define SERIAL_STOPBITS                         UART_STOPBITS_1
#define SERIAL_PARITY                           UART_PARITY_NONE
#define SERIAL_HARDWARECTRL                     UART_HWCONTROL_NONE
#define SERIAL_MODE                             UART_MODE_TX_RX
#define SERIAL_OVERSAMPLE                       UART_OVERSAMPLING_16


/* -------- Buzzer */

#define BUZ_PIN                                 GPIO_PIN_1
#define BUZ_GPIO_PORT                           GPIOB
#define BUZ_Set()                               __GPIO_SET(BUZ_GPIO_PORT, BUZ_PIN)
#define BUZ_Reset()                             __GPIO_RST(BUZ_GPIO_PORT, BUZ_PIN)
#define BUZ_Toggle()                            __GPIO_TOG(BUZ_GPIO_PORT, BUZ_PIN)
#define BUZ_On()                                BUZ_Set()
#define BUZ_Off()                               BUZ_Reset()


/* Macro -----------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
