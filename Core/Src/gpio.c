/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */
const int LEDPINS[4]={D5D11_Pin,D4D10_Pin,D3D9_Pin,D2D8_Pin};

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, A2C8_Pin|D2D8_Pin|D3D9_Pin|D4D10_Pin 
                          |D5D11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = p1_Pin|p2_Pin|p3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin */
  GPIO_InitStruct.Pin = A2C8_Pin|D2D8_Pin|D3D9_Pin|D4D10_Pin 
                          |D5D11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void GPIO_Show_Speed(int speed){
	if(0<speed){
		HAL_GPIO_WritePin(A2C8_GPIO_Port, A2C8_Pin, 1);
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[0], !(0<speed));
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[1], !(1<speed));
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[2], !(2<speed));
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[3], !(3<speed));
	}
	if(speed<=0){
		HAL_GPIO_WritePin(A2C8_GPIO_Port, A2C8_Pin, 0);
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[0], speed<-0);
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[1], speed<-1);
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[2], speed<-2);
		HAL_GPIO_WritePin(D2D8_GPIO_Port, LEDPINS[3], speed<-3);
	}
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
