/** @file ble_helpers.h
 * 
 * @brief methods to init config  uart, gpio , adc . 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Mateusz Malinowski.  All rights reserved.
 */ 
#ifndef BLE_HELPERS_H
#define BLE_HELPERS_H

void WriteToTxBuffer(void);
uint8_t MakeCharNumber(uint8_t number);
void InitLed(GPIO_InitTypeDef * GPIO_InitStruct_LED, uint32_t LEDColor);
void InitUart2(UART_HandleTypeDef * UartHandle);
void InitADC(ADC_HandleTypeDef * AdcHandle);
void ConfigADC(ADC_ChannelConfTypeDef * sConfig);
void Convert_ADC_Value_To_Char_Array(uint8_t * txBuffer, uint16_t adc_value);


#endif