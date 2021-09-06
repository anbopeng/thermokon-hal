/**
  ******************************************************************************
  * @file    internal_flash_test.c
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
#include "internal_flash_test.h"
#include "stdio.h"
#include "internal_flash.h"

uint8_t write_buffer[64] = {0};
uint8_t read_buffer[64] = {0};

void init_buf(uint8_t *read_buffer, uint8_t *write_buffer,uint8_t size, uint8_t base)
{
	uint8_t i;
	
	for (i =0; i < size ; i++)
	{
		read_buffer[i] = 0;
		write_buffer[i] = i + base;
	}

}

void print_buf(uint8_t *buffer, uint8_t size)
{
	uint8_t  j =0;
	int8_t i = 0;
	uint8_t *current_ptr = buffer;
	while( j < size)
	{
			printf("%02d ", *current_ptr);
			if (!((i+1)%8))
			{
				 i = -1;
				 printf("\r\n");
				 
			}
			current_ptr++;
			i++;
			j++;
	}
}


void internal_flash_test(void)
{
		uint8_t j;	
		j = 0;
		flash_erase_all();
	
		while(j < NUM_PAGES)
		{
			printf("\tBLOCK %02d\r\n\r\n", j);
			init_buf(read_buffer, write_buffer,64, j);
			printf("block %02d is writing!\r\n", j);
			print_buf(write_buffer, 64);
			
			flash_writeblock(j, write_buffer, 64);
			
			//HAL_Delay(200);

			printf("\r\nblock %02d is reading!\r\n", j);
			
			flash_readblock(j, read_buffer, 64);
			
			print_buf(read_buffer, 64);
			j++;
			printf("***********************\r\n\r\n");
			HAL_Delay(1000);  


	  }	
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
