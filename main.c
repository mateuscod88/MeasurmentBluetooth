#include "main.h"

UART_HandleTypeDef UartHandle;
ADC_HandleTypeDef    AdcHandle;
__IO uint16_t uhADCxConvertedValue = 0;

uint8_t aTxBuffer[4] ;
uint8_t aRxBuffer[10];
static uint8_t txbuf[8];

static void SystemClock_Config(void);
static void Error_Handler(void);


int main(void)
{
	
	HAL_Init();
	SystemClock_Config();
	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct_LED;
	
	/* all user Leds on board Initialization */
	InitLed(&GPIO_InitStruct_LED, BLUE_LED_ON);
	InitLed(&GPIO_InitStruct_LED, ORANGE_LED_ON);
	InitLed(&GPIO_InitStruct_LED, RED_LED_ON);
	InitLed(&GPIO_InitStruct_LED, GREEN_LED_ON);
	
	aTxBuffer[0]= 1; 
	aTxBuffer[1] = 2;
	/*UART 2 Initialization*/
	InitUart2(&UartHandle);
	
	if(HAL_UART_Init(&UartHandle))
	{
		Error_Handler();
	}
	if(HAL_UART_Transmit_DMA(&UartHandle, (uint8_t*)aTxBuffer, TXBUFFERSIZE)!= HAL_OK)
  {
    Error_Handler();
  }
	if(HAL_UART_Receive_DMA(&UartHandle,(uint8_t*)aRxBuffer,1) != HAL_OK)
	{
		Error_Handler();
	}
	
	
	InitADC(&AdcHandle);
	
	if(HAL_ADC_Init(&AdcHandle)){
		Error_Handler();
	}
	/* Config ADC*/
	ADC_ChannelConfTypeDef sConfig;
	ConfigADC(&sConfig);
	
	if(HAL_ADC_ConfigChannel(&AdcHandle,&sConfig))
	{
		Error_Handler();
	}
	while(UartHandle.gState != HAL_UART_STATE_READY){
	}
	if(HAL_ADC_Start_DMA(&AdcHandle,(uint32_t*)&uhADCxConvertedValue,1) != HAL_OK)
	{
		Error_Handler();
	}
	while(1){
		
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
	HAL_UART_IRQHandler(UartHandle); 
	
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	HAL_GPIO_WritePin(GPIOD,ORANGE_LED_ON,GPIO_PIN_SET);
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	Convert_ADC_Value_To_Char_Array(txbuf,uhADCxConvertedValue);
	
	if(UartHandle.gState != HAL_UART_STATE_READY){
	 return;	
	}
	if(HAL_UART_Transmit_DMA(&UartHandle, (uint8_t*)txbuf, 8)!= HAL_OK)
  {
		HAL_GPIO_WritePin(GPIOD,GREEN_LED_ON,GPIO_PIN_SET);
    Error_Handler();
  }
	
}
static void Error_Handler(void)
{
  /* Turn LED5 on */
	HAL_GPIO_WritePin(GPIOD,ORANGE_LED_ON,GPIO_PIN_SET);
  while(1)
  {
  }
}