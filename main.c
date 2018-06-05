#include "main.h"

UART_HandleTypeDef UartHandle;
ADC_HandleTypeDef    AdcHandle;
__IO uint16_t uhADCxConvertedValue = 0;
uint8_t aTxBuffer[] = " ****UART ";
static void SystemClock_Config(void);
static void Error_Handler(void);
int main(void)
{
	
	HAL_Init();
	SystemClock_Config();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct_LED;
	
	GPIO_InitStruct_LED.Pin = BLUE_LED_ON;
	GPIO_InitStruct_LED.Pull = GPIO_PULLUP;
	GPIO_InitStruct_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_LED.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOD,&GPIO_InitStruct_LED);
	
	GPIO_InitStruct_LED.Pin = ORANGE_LED_ON;
	GPIO_InitStruct_LED.Pull = GPIO_PULLUP;
	GPIO_InitStruct_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_LED.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOD,&GPIO_InitStruct_LED);
	
	GPIO_InitStruct_LED.Pin = RED_LED_ON;
	GPIO_InitStruct_LED.Pull = GPIO_PULLUP;
	GPIO_InitStruct_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_LED.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOD,&GPIO_InitStruct_LED);
	
	GPIO_InitStruct_LED.Pin = GREEN_LED_ON;
	GPIO_InitStruct_LED.Pull = GPIO_PULLUP;
	GPIO_InitStruct_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_LED.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOD,&GPIO_InitStruct_LED);
	
	
	
	UartHandle.Instance = USART2;
	
	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	
	if(HAL_UART_Init(&UartHandle))
	{
		Error_Handler();
	}
	if(HAL_UART_Transmit_DMA(&UartHandle, (uint8_t*)aTxBuffer, TXBUFFERSIZE)!= HAL_OK)
  {
    Error_Handler();
  }
	ADC_ChannelConfTypeDef sConfig;
	
	AdcHandle.Instance = ADCx;
	
	AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	AdcHandle.Init.Resolution= ADC_RESOLUTION_12B;
	AdcHandle.Init.ScanConvMode = DISABLE;
	AdcHandle.Init.ContinuousConvMode = ENABLE;
	AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle.Init.NbrOfDiscConversion = 0;
	AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	AdcHandle.Init.NbrOfConversion = 1;
	AdcHandle.Init.DMAContinuousRequests = ENABLE;
	AdcHandle.Init.EOCSelection = DISABLE;
	
	if(HAL_ADC_Init(&AdcHandle)){
		Error_Handler();
	}
	sConfig.Channel = ADCx_CHANNEL;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	sConfig.Offset = 0;
	
	if(HAL_ADC_ConfigChannel(&AdcHandle,&sConfig))
	{
		Error_Handler();
	}
	if(HAL_ADC_Start_DMA(&AdcHandle,(uint32_t*)&uhADCxConvertedValue,1) != HAL_OK)
	{
		Error_Handler();
	}
	
}
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
 
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	HAL_GPIO_WritePin(GPIOD,RED_LED_ON,GPIO_PIN_SET);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	HAL_GPIO_WritePin(GPIOD,BLUE_LED_ON,GPIO_PIN_SET);
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	HAL_GPIO_WritePin(GPIOD,GREEN_LED_ON,GPIO_PIN_SET);
}
static void Error_Handler(void)
{
  /* Turn LED5 on */
	HAL_GPIO_WritePin(GPIOD,ORANGE_LED_ON,GPIO_PIN_SET);
  while(1)
  {
  }
}