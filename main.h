#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f4xx_hal.h"
#include "stm_interrupt_handlers.h"

#define USARTx USART2
#define USARTx_CLK_ENABLE() 						__HAL_RCC_USART2_CLK_ENABLE()
#define DMAx_CLK_ENABLE() 							__HAL_RCC_DMA1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE() 		__HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE() 		__HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_TX_PIN 									GPIO_PIN_2
#define USARTx_TX_GPIO_PORT 						GPIOA
#define USARTx_TX_AF 										GPIO_AF7_USART2
#define USARTx_RX_PIN 									GPIO_PIN_3
#define USARTx_RX_GPIO_PORT 						GPIOA
#define USARTx_RX_AF 										GPIO_AF7_USART2

/*USARTx DMA*/
#define USARTx_TX_DMA_CHANNEL 					DMA_CHANNEL_4
#define USARTx_TX_DMA_STREAM 						DMA1_Stream6
#define USARTx_RX_DMA_CHANNEL 					DMA_CHANNEL_4
#define USARTx_RX_DMA_STREAM 						DMA1_Stream5
/*USARTx NVIC*/
#define USARTx_DMA_TX_IRQn 							DMA1_Stream6_IRQn
#define USARTx_DMA_RX_IRQn 							DMA1_Stream5_IRQn
#define USARTx_DMA_TX_IRQHandler 				DMA1_Stream6_IRQHandler
#define USARTx_DMA_RX_IRQHandler 				DMA1_Stream5_IRQHandler
#define USARTx_IRQn 										USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler


#define USARTx_FORCE_RESET() 						__HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET() 					__HAL_RCC_USART2_RELEASE_RESET()
#define TXBUFFERSIZE                     (COUNTOF(aTxBuffer) - 1)
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* ADC DMA*/
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()
#define DMA2x_CLK_ENABLE()               __HAL_RCC_DMA2_CLK_ENABLE()     
#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
     
#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx Channel Pin */
#define ADCx_CHANNEL_PIN                GPIO_PIN_0
#define ADCx_CHANNEL_GPIO_PORT          GPIOB

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL                    ADC_CHANNEL_8

/* Definition for ADCx's DMA */
#define ADCx_DMA_CHANNEL                DMA_CHANNEL_0
#define ADCx_DMA_STREAM                 DMA2_Stream0         

/* Definition for ADCx's NVIC */
#define ADCx_DMA_IRQn                   DMA2_Stream0_IRQn
#define ADCx_DMA_IRQHandler             DMA2_Stream0_IRQHandler

#define GREEN_LED_ON 										GPIO_PIN_12
#define ORANGE_LED_ON 									GPIO_PIN_13
#define RED_LED_ON 											GPIO_PIN_14
#define BLUE_LED_ON 										GPIO_PIN_15
#endif