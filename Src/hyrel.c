/*
 * function.c
 *
 *  Created on: Jan 6, 2021
 *      Author: falcon
 */
#include "main.h"
#include "pins.h"
#include "hyrel.h"

byte 						Tick1000hzCounter = 0;
byte 						Tick100hzCounter = 0;
byte 						Tick10hzCounter = 0;
byte 						Tick1hzCounter = 0;
uint16_t                    ExtendedSliceTimeNeeded = 0;   // down counter of extra slice times needed
uint32_t                    Seconds = 0;               // needed for heartbeat (number of seconds since boot)
uint16_t                    SliceCnt = 0;              // current slice being processed
unsigned 					GlobalSync = 1;//causes all timers to reset and synchronize, makes all hot heads on canbus time toghether
_Bool                     	CanImmediateRxIsAvail; // flag to indicate an immediate can message is ready to be processed


#define GLOBAL_SYNC                         (GlobalSync)
#define SET_GLOBAL_SYNC_BIT                 (GlobalSync = 1)
#define CLR_GLOBAL_SYNC_BIT                 (GlobalSync = 0)


const PFUNC F1000HZ[NUM_1000HZ] =
{
		OhNoMrBill,             // can't use slice 0 and this is time slot to execute the next slower slice
		Spare,//serialProcessor,
		Spare,//CommandProcessor,       // can't move to foreground due to collision on global "ExecutionPtr"
		Spare,//SequenceEngine,         // controls a lot of ms increment timers -- MUST STAY IN 1000Hz loop
		Spare,//canProcessRxQueueNoReturn,
		Spare,//canProcessTxQueueNoReturn,
		Spare,
		Spare,//loop_1000Hz_simple_work,    // keep as last call in this array

};

const PFUNC F100HZ[NUM_100HZ] =
{
		OhNoMrBill,             // can't use slice 0 and this is time slot to execute the next slower slice
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,//loop_100Hz_simple_work, // keep as last call in this array
};

const PFUNC F10HZ[NUM_10HZ] =
{
		OhNoMrBill,             // can't use slice 0 and this is time slot to execute the next slower slice
		Spare,//soapstringController,
		Spare,//sendUpdateToHost,
		Spare,//checkBlockingWaits,
		Spare,//EdgeTriggerSendResults, // move into simple_work if space needed
		Spare,//checkForCompletedAbort,
		Spare,//ReportXYZLocation,
		Spare,
		Spare,
		Spare,//loop_10Hz_simple_work,  // keep as last call in this array
};

const PFUNC F1HZ[NUM_1HZ] =
{
		OhNoMrBill,
		BlinkLed,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,
		Spare,//loop_1Hz_simple_work,   // keep as last call in this array
};
void Spare (void)
{
	// placeholder call for empty slice
}

////////////////////////////////////////////////////////////////////////////////PC8

void OhNoMrBill(void)
{
	// XXXX should send an ERROR .... should never get here
}
void BlinkLed(void){
	TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}
////////////////////////////////////////////////////////////////////////////////

void Heartbeat(void)
{
	//TogglePin(HeartBeat_Port,HeartBeat_Pin);
}


//This function is called thousands of times per second as a callback function of SysTick.
void FUNC_SystickCallback()
{
	if (ExtendedSliceTimeNeeded > 0)
	{   // some slices require extra time, so count down timer and don't call the next slice.
		ExtendedSliceTimeNeeded--;
	}
	else
	{
		MainControlLoop();
	}
}

void ProcessEverySlice(void)
{   // all code in this method will be executed EVERY SYSTICK and therefore comes out of the
	// time budget for EVERY slice.   Only put code here that cannot exist in an actual slice
	if (GLOBAL_SYNC)
	{   //reset all event pointers so that  all heads on the canbus are in sync
		CLR_GLOBAL_SYNC_BIT;
		SliceCnt                       = 0;
		Tick1000hzCounter = 0;
		Tick100hzCounter = 0;
		Tick10hzCounter = 0;
		Tick1hzCounter = 0;
	}

	if (CanImmediateRxIsAvail)
	{   // should only be a STEP or LASER_POWER(raster)
		//canProcessRxQueue();
	}
	// called two times to match possible incoming rate (4000 slices/sec vs approx 8000 packet/sec on the can
	//canAddToRxQueue();              // check if any incomingRX messages and add to rx queue
	//canAddToRxQueue();              // check if any incomingRX messages and add to rx queue
}

void MainControlLoop(void)
{
	//ProcessEverySlice();
	SliceCnt++;
	if (++ Tick1000hzCounter == NUM_1000HZ)
	{
		Tick1000hzCounter = 0;//reset khz counter
		if (++ Tick100hzCounter == NUM_100HZ)
		{
			Tick100hzCounter = 0;
			if (++Tick10hzCounter == NUM_10HZ)
			{
				Tick10hzCounter = 0;
				if (++Tick1hzCounter == NUM_1HZ)
				{
					Tick1hzCounter = 0;
					SliceCnt = 0;
				}
				F1HZ[Tick1hzCounter]();

			}
			else
				F10HZ[Tick10hzCounter]();
		}
		else
			F100HZ[Tick100hzCounter]();
	}
	else
		F1000HZ[Tick1000hzCounter]();
}

