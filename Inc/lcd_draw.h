/**
  ******************************************************************************
  * File Name          : lcd_draw.h
  * Description        : This file provides code for the drawing function in LCD
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
#ifndef __lcd_draw_H
#define __lcd_draw_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "st7735.h"
void draw_grayscale_frame(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height, uint8_t IsAxis);
void draw_rgb565_frame(ST7735_Object_t *pObj, uint32_t Xpos, uint32_t Ypos, uint16_t *pData, uint32_t Width, uint32_t Height, uint8_t IsAxis);


/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ lcd_draw_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



