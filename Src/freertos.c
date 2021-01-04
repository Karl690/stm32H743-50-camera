/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "constant.h"
#include "dcmi.h"
#include "i2c.h"
#include "lcd.h"
#include "vcp.h"
#include "command.h"
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

/* USER CODE END Variables */
/* Definitions for DisplayLCDThrea */
osThreadId_t DisplayLCDThreaHandle;
const osThreadAttr_t DisplayLCDThrea_attributes = {
  .name = "DisplayLCDThrea",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 128 * 4
};
/* Definitions for QueryVCPThread */
osThreadId_t QueryVCPThreadHandle;
const osThreadAttr_t QueryVCPThread_attributes = {
  .name = "QueryVCPThread",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDisplayLCDThread(void *argument);
void StartQueryVCPThread(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of DisplayLCDThrea */
  DisplayLCDThreaHandle = osThreadNew(StartDisplayLCDThread, NULL, &DisplayLCDThrea_attributes);

  /* creation of QueryVCPThread */
  QueryVCPThreadHandle = osThreadNew(StartQueryVCPThread, NULL, &QueryVCPThread_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDisplayLCDThread */
/**
  * @brief  Function implementing the DisplayLCDThrea thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDisplayLCDThread */
void StartDisplayLCDThread(void *argument)
{
  /* init code for USB_DEVICE */

	extern uint8_t IsDrawingAxis;
	extern uint8_t IsLiveStream;
	LCD_Init();

#ifndef _AUTO_VIDEO_LIVE
	while (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
	{
		LED_Blink(5, 10);
		HAL_Delay(10);
	}
#endif

	extern uint32_t DCMI_FrameIsReady;
	extern uint16_t DCMI_BUF[FRAME_HEIGHT][FRAME_WIDTH];
	extern uint8_t LCD_log_text[30];
	Camera_Init_Device(&hi2c1, CAMERA_RESOLUTION_MODE);
	HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)&DCMI_BUF, FRAME_WIDTH * FRAME_HEIGHT * 2 / 4);
	for(;;)
	{

		if (DCMI_FrameIsReady)
		{
			DCMI_FrameIsReady = 0;
			if(IsLiveStream)
				draw_rgb565_frame(&st7735_pObj,0,0,(uint8_t*)&DCMI_BUF[0][0], ST7735Ctx.Width, 80,IsDrawingAxis);
			else
				LCD_Logo();
		}else {
			//LCD_Logo();
		}

		if(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) != GPIO_PIN_RESET) {
			IsLiveStream = IsLiveStream == 1?0:1;
			HAL_Delay(100);
		}

		LED_Blink(1, 1);

	}
  /* USER CODE END StartDisplayLCDThread */
}


/* USER CODE BEGIN Header_StartQueryVCPThread */
/**
* @brief Function implementing the QueryVCPThread thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartQueryVCPThread */
void StartQueryVCPThread(void *argument)
{
	/* USER CODE BEGIN StartQueryVCPThread */
	/* Infinite loop */
	extern uint8_t COMM_RECV_BUF[MAX_BUF_SIZE];
	extern uint8_t COMM_TRANS_BUF[MAX_BUF_SIZE];

	while(1)
	{

		osDelay(1);

	}
	/* USER CODE END StartQueryVCPThread */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
