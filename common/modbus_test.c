/**
  ******************************************************************************
  * @file    modbus_test.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "modbus_test.h"
#include "usart.h"
#include "stdio.h"


#define MAX_READ_PER_TRANSACTION 16
#define PER_SUPPLY_ENABLE_PORT	GPIOB
#define PER_SUPPLY_ENABLE_PIN	GPIO_PIN_5
#define MAX_REPEAT_COUNT 5

#define MODBUS_M1_PORT   		GPIOB
#define MODBUS_M1_PIN    		GPIO_PIN_7

#define MODBUS_M2_PORT   		GPIOB
#define MODBUS_M2_PIN    		GPIO_PIN_2



static uint8_t rx_chr;
static uint8_t rx_buffer[MAX_READ_PER_TRANSACTION] ={0};
static uint8_t current_index = 0;


#define CRC_POLYNOMIAL 0x8005 //P(x)=x^16+x^15+x^2+1 = 1000 0000 0000 0101

void clear_buffer(uint8_t *buffer, uint8_t length)
{
	for( int i =0; i < length;  i++)
		buffer[i] = 0;
	
}
uint8_t reflect_byte(uint8_t input)
{
	//swap upper and lower nybbles
	input = (input & 0xF0) >> 4 | (input & 0x0F) << 4;
	//swap adjacent pairs
	input = (input & 0xCC) >> 2 | (input & 0x33) << 2;
	//swap adjacent bits
	input = (input & 0xAA) >> 1 | (input & 0x55) << 1;
	return input;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	
	if(huart->Instance == LPUART1)
	{ 
		
		rx_buffer[current_index++] = rx_chr;
		HAL_UART_Receive_IT(&hlpuart1, &rx_chr,1); // save char from uart receive
	}

}

uint16_t modbus_calculateCrc(uint8_t* data, int data_length)
{
	uint16_t crc = 65535;
	uint16_t byte_counter;
	uint8_t bit_counter;
	
	
	for (byte_counter = 0; byte_counter < data_length; byte_counter++)
	{ 
		//turns out that the MODBUS CRC implementation requres that the input bytes be reflected
		crc ^= reflect_byte(data[byte_counter])<<8;
		for (bit_counter = 0; bit_counter < 8; bit_counter++)
		{ 
			if (crc & 0x8000)
			{
				crc = (crc << 1) ^ CRC_POLYNOMIAL;
			}
			else
			{
				crc = (crc << 1);
			}
		}
	}
	//reuse byte counter here, to reflect the result, as the MODBUS CRC calculation requires that the
	//crc be reflected
	byte_counter = reflect_byte(crc&0xFF)<<8;
	byte_counter += reflect_byte(crc>>8);
	
	return byte_counter;
}

int modbus_read_registers(modbus_register_t modbus_register)
{
	uint8_t txData[8] = {0};
	uint16_t crc;
	//construct the array to transmit
	txData[0]=modbus_register.slaveID;
	txData[1]=modbus_register.function_code;
	txData[2]=(uint8_t)(modbus_register.start_Register>>8);
	txData[3]=(uint8_t)(modbus_register.start_Register&0xFF);
	txData[4]=(uint8_t)(modbus_register.register_count>>8);
	txData[5]=(uint8_t)(modbus_register.register_count&0xFF);
	//6 and 7 have the CRC
	crc = modbus_calculateCrc(txData,6);
	txData[6]=(uint8_t)(crc&0xFF);
	txData[7]=(uint8_t)(crc>>8);

	
		//set the MODBUS to transmit mode
	HAL_GPIO_WritePin(MODBUS_M1_PORT,MODBUS_M1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MODBUS_M2_PORT,MODBUS_M2_PIN, GPIO_PIN_SET);

	//wait for the idle period (4ms)
	HAL_Delay(4);
	
	printf("MODBUS_TX:");
	
	for(int i=0;i<8;i++)
	{
		HAL_UART_Transmit(&hlpuart1,&txData[i],1,1000);
		printf(" %02X",txData[i]);
	}

	HAL_UART_Receive_IT(&hlpuart1,&rx_chr,1);
	
	printf("\r\n");
	
	//required delay for idle period of modbus specification
	HAL_Delay(4);
	
	//switch to receive mode
	HAL_GPIO_WritePin(MODBUS_M1_PORT,MODBUS_M1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MODBUS_M2_PORT,MODBUS_M2_PIN, GPIO_PIN_RESET);
	
	uint32_t tickstart = HAL_GetTick();
	
	while(((HAL_GetTick() - tickstart) < 100))
	{
		//reset the watchdog to prevent a reset while waiting on the timeout

	}
	
	printf("MODBUS_RX: ");
  if (current_index >0)
	{
		for (int i =0; i < current_index; i++)
		{
			printf("%02x ",rx_buffer[i]);
		}
		printf("\r\n");
		crc = modbus_calculateCrc(rx_buffer, current_index-2);
		printf("CRC:\r\n");
		printf("Received:0x%02X%02X\r\n", rx_buffer[current_index-2], rx_buffer[current_index-1]);
		printf("Expected:0x%02X%02X\r\n", crc&0xFF, crc>>8);	
		
		return current_index;
	}else return -1;
	
	
}


char * string_output(uint16_t reg_name)
{
	switch(reg_name)
	{
		case 1: return "Temperature";
		case 2: return "Relative Humidity";
		case 3: return "Absolution Humidity";
		case 4: return "Enthalpy";
		case 5: return "Dew Point";
		case 6: return "CO2";
		case 7: return "VOC";
		case 8: return "CO2_VOC";
		case 9: return "Flow";
		case 10: return "Pressure";
		case 11: return "Brightness";
		case 12: return "Condensation";
		case 13: return "Ambient Pressure";
		default: return "No Support";
	}

}

void detect_thermokon_sensor(void)
{
	modbus_register_t modbus_temp_reg = {0};
	int	result = -1;
	uint16_t sensor_amount = 0;
	
 	HAL_GPIO_WritePin(PER_SUPPLY_ENABLE_PORT, PER_SUPPLY_ENABLE_PIN, GPIO_PIN_SET);

	modbus_temp_reg.slaveID = 1;
	modbus_temp_reg.function_code = 3;
	modbus_temp_reg.start_Register = (uint16_t)0;
	modbus_temp_reg.register_count =(uint16_t)1;
	
  result = modbus_read_registers(modbus_temp_reg);
	for (int i =0; i < MAX_REPEAT_COUNT; i++)
  {
 
		if(result <= 0)
		{
		  HAL_Delay(20);
			result = modbus_read_registers(modbus_temp_reg);
				
		}else break;
    	
  }
		
	sensor_amount = rx_buffer[4];

	printf("You need to read %02d registers totally!\r\n", sensor_amount);

	if (sensor_amount)
	{

		for (int i =0; i< sensor_amount; i ++)
		{
			clear_buffer(rx_buffer, MAX_READ_PER_TRANSACTION);
			current_index =0;
			modbus_temp_reg.slaveID = 1;
			modbus_temp_reg.function_code = 3;
			modbus_temp_reg.start_Register = (1000+100*i)+8;
			modbus_temp_reg.register_count =1;

			result = modbus_read_registers(modbus_temp_reg);
			for(int j =0; j < MAX_REPEAT_COUNT ; j++)
			{
				if(result <= 0)
				{
					result = modbus_read_registers(modbus_temp_reg);
				}else break;
			}
			    
			//print_result(temp,MAX_READ_PER_TRANSACTION);
			printf("Register %02d is %s!\r\n", rx_buffer[4],string_output(rx_buffer[4]));
		}

	}
	
	HAL_GPIO_WritePin(PER_SUPPLY_ENABLE_PORT, PER_SUPPLY_ENABLE_PIN, GPIO_PIN_RESET);

	return;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
