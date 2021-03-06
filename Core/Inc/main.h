/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define DEBUG_PORT_HANDLE huart1

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LORA_MOD_RST_Pin GPIO_PIN_13
#define LORA_MOD_RST_GPIO_Port GPIOC
#define LED_ERROR_Pin GPIO_PIN_0
#define LED_ERROR_GPIO_Port GPIOC
#define LED_TXD_Pin GPIO_PIN_1
#define LED_TXD_GPIO_Port GPIOC
#define LED_RXD_Pin GPIO_PIN_2
#define LED_RXD_GPIO_Port GPIOC
#define LED_STATE_Pin GPIO_PIN_3
#define LED_STATE_GPIO_Port GPIOC
#define PWM_R_Pin GPIO_PIN_0
#define PWM_R_GPIO_Port GPIOA
#define PWM_G_Pin GPIO_PIN_1
#define PWM_G_GPIO_Port GPIOA
#define PWM_B_Pin GPIO_PIN_2
#define PWM_B_GPIO_Port GPIOA
#define TX_MCU_RX_GP_Pin GPIO_PIN_10
#define TX_MCU_RX_GP_GPIO_Port GPIOB
#define RX_MCU_TX_GP_Pin GPIO_PIN_11
#define RX_MCU_TX_GP_GPIO_Port GPIOB
#define DEBUG_TX_Pin GPIO_PIN_9
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_10
#define DEBUG_RX_GPIO_Port GPIOA
#define LR_MOD_RX_MCU_TX_Pin GPIO_PIN_10
#define LR_MOD_RX_MCU_TX_GPIO_Port GPIOC
#define LR_MOD_TX_MCU_RX_Pin GPIO_PIN_11
#define LR_MOD_TX_MCU_RX_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
