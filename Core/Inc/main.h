/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define TX_Pin GPIO_PIN_2
#define TX_GPIO_Port GPIOA
#define POT_Pin GPIO_PIN_3
#define POT_GPIO_Port GPIOA
#define Current_Pin GPIO_PIN_4
#define Current_GPIO_Port GPIOA
#define Voltage_Pin GPIO_PIN_5
#define Voltage_GPIO_Port GPIOA
#define p1_Pin GPIO_PIN_8
#define p1_GPIO_Port GPIOA
#define p2_Pin GPIO_PIN_9
#define p2_GPIO_Port GPIOA
#define p3_Pin GPIO_PIN_10
#define p3_GPIO_Port GPIOA
#define RX_Pin GPIO_PIN_15
#define RX_GPIO_Port GPIOA
#define A2C8_Pin GPIO_PIN_3
#define A2C8_GPIO_Port GPIOB
#define D2D8_Pin GPIO_PIN_4
#define D2D8_GPIO_Port GPIOB
#define D3D9_Pin GPIO_PIN_5
#define D3D9_GPIO_Port GPIOB
#define D4D10_Pin GPIO_PIN_6
#define D4D10_GPIO_Port GPIOB
#define D5D11_Pin GPIO_PIN_7
#define D5D11_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
