/*
   _____             _____                 
  / ____|           / ____|                
 | (___   ___ _ __ | (___  _   _ _ __ ___  
  \___ \ / _ \ '_ \ \___ \| | | | '_ ` _ \ 
  ____) |  __/ | | |____) | |_| | | | | | |
 |_____/ \___|_| |_|_____/ \__,_|_| |_| |_|
                                           
                                           
	Description:	Internal EEPROM HAL level driver header for LoRa only implementation project

	Maintainer: Xubo Peng


*/

#ifndef INTERNAL_FLASH_HEADER
#define INTERNAL_FLASH_HEADER
#include <stdint.h>

/********************************************************************
 *Definitions                                                       *
 ********************************************************************/
#define EEPROM_BASE_ADDR    0x08080000
#define EEPROM_BYTE_SIZE    0x17FF
#define NUM_PAGES 					96  //for 6K EEPROM SIZE
#define PAGE_SIZE 					64	

 /********************************************************************
 *Function Prototypes                                               *
 ********************************************************************/
void flash_writeblock(uint16_t block, uint8_t *data, uint8_t data_size);
void flash_readblock(uint16_t block, uint8_t *data, uint8_t data_size);
void flash_erase_all(void);
 
 /********************************************************************
 *Global Variables                                                  *
 ********************************************************************/

#endif //I2C_FLASH_HEADER
