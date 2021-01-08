/*
 * led.h
 *
 *  Created on: Jan 6, 2021
 *      Author: falcon
 */

#ifndef _PINS_H_
#define _PINS_H_

GPIO_PinState GetPinStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void SetPinStatus(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* SRC_LED_H_ */
