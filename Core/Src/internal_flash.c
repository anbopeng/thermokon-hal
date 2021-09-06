/*
   _____             _____                 
  / ____|           / ____|                
 | (___   ___ _ __ | (___  _   _ _ __ ___  
  \___ \ / _ \ '_ \ \___ \| | | | '_ ` _ \ 
  ____) |  __/ | | |____) | |_| | | | | | |
 |_____/ \___|_| |_|_____/ \__,_|_| |_| |_|
                                           
                                           
	Description:	internal EEPROM HAL level driver for LoRa only implementation project

	Maintainer: Xubo Peng

*/

#include "internal_flash.h"
#include "stm32l0xx.h"       
#include "stdio.h"   

#include "stm32l0xx_hal_flash.h"

/********************************************************************
 *Functions internal eeprom write a whole block                                                       *
 ********************************************************************/
void flash_writeblock(uint16_t block, uint8_t *data, uint8_t data_size)
{
  uint8_t j;
	uint8_t *current_data_ptr = data;
//	HAL_StatusTypeDef status = HAL_OK;

  HAL_FLASHEx_DATAEEPROM_Unlock();
	
	//i = 0;
  for(j=0;j<data_size;j++)
  {
      if(HAL_OK == HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, EEPROM_BASE_ADDR + (block*PAGE_SIZE) + j, *current_data_ptr))
			{
						current_data_ptr++;
			
		//				if(i==8) i = 0;

		//				i++;			

			}
			else return;
			
  }
  HAL_FLASHEx_DATAEEPROM_Lock();	
	
}


/********************************************************************
 *Functions internal eeprom read a whole block                                                        *
 ********************************************************************/
void flash_readblock(uint16_t block, uint8_t *data, uint8_t data_size)
{

  uint8_t *wAddr;
	uint8_t *current_ptr = data;
	//uint8_t i, j;

  wAddr=(uint8_t *)(EEPROM_BASE_ADDR + (block * PAGE_SIZE));

  //i = 0;
	//j = 0;
	
  while(data_size--)
  {
      *current_ptr++ = *wAddr++;
//			if(i==8) i = 0;

	//		i++; 
		//	j++;			
  }
		
}

/********************************************************************
 *Functions erase whole internal eeprom                                                        *
 ********************************************************************/
void flash_erase_all()
{
	uint16_t block = 0;
	uint8_t data[64] = {0};
	
	//write all blocks to 00.
	//from here, we can set bits to 'write' to the blocks

	printf("Flash is erasing!\r\n");

	for(block = 0; block < NUM_PAGES; block++)
	{

	  printf("."); 
		flash_writeblock(block, data, 64);
		//HAL_Delay(10);
	}

	printf("\r\nErase Finished!\r\n"); 
}

