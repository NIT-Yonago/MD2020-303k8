/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "can.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "math.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
static int32_t encval;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId MinorLoopTaskHandle;
osThreadId MajorLoopTaskHandle;
osThreadId CanCommunicatioHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartMinorLoopTask(void const * argument);
void StartMajorLoopTask(void const * argument);
void StartCanCommunicationTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of MinorLoopTask */
  osThreadDef(MinorLoopTask, StartMinorLoopTask, osPriorityRealtime, 0, 256);
  MinorLoopTaskHandle = osThreadCreate(osThread(MinorLoopTask), NULL);

  /* definition and creation of MajorLoopTask */
  osThreadDef(MajorLoopTask, StartMajorLoopTask, osPriorityHigh, 0, 1024);
  MajorLoopTaskHandle = osThreadCreate(osThread(MajorLoopTask), NULL);

  /* definition and creation of CanCommunicatio */
  osThreadDef(CanCommunicatio, StartCanCommunicationTask, osPriorityAboveNormal, 0, 512);
  CanCommunicatioHandle = osThreadCreate(osThread(CanCommunicatio), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartMinorLoopTask */
/**
* @brief Function implementing the MinorLoopTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMinorLoopTask */
void StartMinorLoopTask(void const * argument)
{
  /* USER CODE BEGIN StartMinorLoopTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartMinorLoopTask */
}

/* USER CODE BEGIN Header_StartMajorLoopTask */
/**
* @brief Function implementing the MajorLoopTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMajorLoopTask */
void StartMajorLoopTask(void const * argument)
{
  /* USER CODE BEGIN StartMajorLoopTask */
  /* Infinite loop */
  for(;;)
  {
	encval=TIM_Encoder_Value();
//	TxData[5]=encval%200;
	memcpy(TxData,encval,4);
	uint32_t tim=HAL_GetTick();
	float sec=tim/1000.0;
	float duty=0.1*sinf(M_TWOPI*sec);
	Duty_Set(duty);
    osDelay(1);
  }
  /* USER CODE END StartMajorLoopTask */
}

/* USER CODE BEGIN Header_StartCanCommunicationTask */
/**
* @brief Function implementing the CanCommunicatio thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCanCommunicationTask */
void StartCanCommunicationTask(void const * argument)
{
  /* USER CODE BEGIN StartCanCommunicationTask */
  /* Infinite loop */
	HAL_CAN_Start(&hcan);
	if (HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK){
		Error_Handler();
	}

  for(;;)
  {
		TxHeader.StdId = 0x100;
		TxHeader.RTR = CAN_RTR_DATA;
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.DLC = 8;
		TxHeader.TransmitGlobalTime = DISABLE;
		TxData[0] = 100;
		TxData[1] = RxData[1];
		TxData[7] = RxData[2];
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox)
				!= HAL_OK)
			Error_Handler();
		while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3) {

		}
		osDelay(1);
  }
  /* USER CODE END StartCanCommunicationTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
