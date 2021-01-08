/*
 * pins.cpp
 *
 *  Created on: Jan 6, 2021
 *      Author: falcon
 */
#include "main.h"
#include "pins.h"

GPIO_PinState GetPinStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

void SetPinStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}

void TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}
