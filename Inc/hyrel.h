/*
 * function.h
 *
 *  Created on: Jan 6, 2021
 *      Author: falcon
 */

#ifndef SRC_HYREL_H_
#define SRC_HYREL_H_

typedef uint8_t byte;
typedef void (*PFUNC)(void);

#define NUM_1000HZ              8
#define NUM_100HZ               10      // must remain 10 otherwise loop timing will not be correct
#define NUM_10HZ                10      // must remain 10 otherwise loop timing will not be correct
#define NUM_1HZ                 10      // must remain 10 otherwise loop timing will not be correct


typedef enum {
	HZ_1000     = 0,
	HZ_100      = 1,
	HZ_10       = 2,
	HZ_1        = 3
} indexType;

void FUNC_SystickCallback();
void Spare (void);
void OhNoMrBill(void);
void Heartbeat(void);
void BlinkLed();
void ProcessEverySlice(void);
void MainControlLoop(void	);
#endif /* SRC_LED_H_ */
