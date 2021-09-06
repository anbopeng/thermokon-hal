/**
  ******************************************************************************
  * @file    modbus_test.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MODBUS_TEST_H__
#define __MODBUS_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define PACKED __attribute__((packed, aligned(1)))
typedef struct
{
	uint8_t  slaveID;
	uint8_t  function_code;
	uint16_t start_Register;
	uint16_t register_count;
}PACKED modbus_register_t;

void clear_buffer(uint8_t *buffer, uint8_t length);
uint8_t reflect_byte(uint8_t input);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
uint16_t modbus_calculateCrc(uint8_t* data, int data_length);
int modbus_read_registers(modbus_register_t modbus_register);
char * string_output(uint16_t reg_name);
void detect_thermokon_sensor(void);

#ifdef __cplusplus
}
#endif

#endif /* __MODBUS_TEST_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
