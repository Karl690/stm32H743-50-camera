/**
  ******************************************************************************
  * File Name          : DCMI.h
  * Description        : This file provides code for the configuration
  *                      of the DCMI instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __color_H
#define __color_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

enum COLOR_FORMAT{
	COLOR_GRAYSCALE,
	COLOR_RGB888,
	COLOR_RGB565,
};

uint32_t convertRGB565ToRGB88(uint16_t rgb565);
uint16_t convertRGB888ToRGB565(uint32_t rgb888);
uint8_t convertRGB565toGray(uint16_t rgb565);
uint16_t convertGrayToRGB565(uint8_t gray);


/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ color_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



