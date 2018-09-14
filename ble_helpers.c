#include "stm32f4xx_hal.h"
#include "main.h"
void InitADC(ADC_HandleTypeDef * AdcHandle){
	
	AdcHandle->Instance = ADCx;
	
	AdcHandle->Init.ClockPrescaler 				= ADC_CLOCKPRESCALER_PCLK_DIV2;
	AdcHandle->Init.Resolution						= ADC_RESOLUTION_12B;
	AdcHandle->Init.ScanConvMode 					= DISABLE;
	AdcHandle->Init.ContinuousConvMode 		= ENABLE;
	AdcHandle->Init.DiscontinuousConvMode = DISABLE;
	AdcHandle->Init.NbrOfDiscConversion 	= 0;
	AdcHandle->Init.ExternalTrigConvEdge 	= ADC_EXTERNALTRIGCONVEDGE_NONE;
	AdcHandle->Init.ExternalTrigConv 			= ADC_EXTERNALTRIGCONV_T1_CC1;
	AdcHandle->Init.DataAlign 						= ADC_DATAALIGN_RIGHT;
	AdcHandle->Init.NbrOfConversion 			= 1;
	AdcHandle->Init.DMAContinuousRequests = ENABLE;
	AdcHandle->Init.EOCSelection 					= DISABLE;
}
void ConfigADC(ADC_ChannelConfTypeDef * sConfig){
	sConfig->Channel 			= ADCx_CHANNEL;
	sConfig->Rank 					= 1;
	sConfig->SamplingTime  = ADC_SAMPLETIME_3CYCLES;
	sConfig->Offset 				= 0;
}
void InitUart2(UART_HandleTypeDef * UartHandle){
	
	UartHandle->Instance = USART2;
	
	UartHandle->Init.BaudRate   	= 9600;
	UartHandle->Init.WordLength 	= UART_WORDLENGTH_8B;
	UartHandle->Init.StopBits   	= UART_STOPBITS_1;
	UartHandle->Init.Parity     	= UART_PARITY_NONE;
	UartHandle->Init.HwFlowCtl  	= UART_HWCONTROL_NONE;
	UartHandle->Init.Mode  				= UART_MODE_TX_RX;
	UartHandle->Init.OverSampling = UART_OVERSAMPLING_16;
}
void InitLed(GPIO_InitTypeDef * GPIO_InitStruct_LED, uint32_t LEDColor){
	
	GPIO_InitStruct_LED->Pin   = LEDColor;
	GPIO_InitStruct_LED->Pull  = GPIO_PULLUP;
	GPIO_InitStruct_LED->Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_LED->Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOD,GPIO_InitStruct_LED);

}
uint8_t MakeCharNumber(uint8_t number)
{
	int i = 0;
	char lTable[] = {'0','1','2','3','4','5','6','7','8','9'};
	while(i<10)
	{
		if(i == number){
			return lTable[i];
		}
		i++;
	}
}
void Convert_ADC_Value_To_Char_Array(uint8_t * txBuffer,uint16_t adc_value){
	uint8_t lowByte = (uint8_t)adc_value;
	uint8_t highByte = (uint8_t)(adc_value >> 8);
	uint16_t temp = 0;
	
	temp = adc_value/1000;
  uint8_t thousends = (uint8_t)temp;
	temp = (adc_value%1000)/100;
	uint8_t hundreds =(uint8_t)temp;
	temp = (adc_value%100)/10;
	uint8_t dec = (uint8_t)temp;
	temp = (adc_value%100)%10;
	uint8_t one = (uint8_t)temp;
	
	txBuffer[0] = MakeCharNumber(thousends);
	txBuffer[1] = MakeCharNumber(hundreds);
	txBuffer[2] = MakeCharNumber(dec);
	txBuffer[3] = MakeCharNumber(one);
	txBuffer[4] = 'm';
	txBuffer[5] = 'v';
	txBuffer[6] = '\r';
	txBuffer[7] = '\n';
}