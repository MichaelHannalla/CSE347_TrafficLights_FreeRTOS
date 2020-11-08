/*
*Term Project - Multi-junction Traffic Light Controller
*CSE347 - Embedded System Design
*** Train Approaching Mode ***
*/

#ifndef TRAIN_H_
#define TRAIN_H_

///// Macros /////

#define tSafety_in_ms 	  30000
#define TRAIN_PRI         4
#define TRAIN_PERIOD_TICKS   (uint32_t)(((float)tSafety_in_ms / 1000) * configTICK_RATE_HZ) //5000 milliseconds



#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "initializations.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "stack_macros.h"
#include <stdbool.h> 
#include <stdint.h>
#include "Normal.h"
#include "Pedestrians.h"
#include "UART.h"


///// Prototypes /////

void vTrainApproaching(void *pvParameters);			// Train Approaching Mode Task
void InitializePORTEInterrupt (void);
void TrainSensorsHandler(void);									// Train Sensors ISR
inline void TurnOffSiren(void);
inline void TurnOnSiren(void);
inline void OpenTrainGate(void);
inline void CloseTrainGate(void);
inline void StopAllJunctions(void);

bool TrainCrossed;
xSemaphoreHandle xBinaryTrainSensor1Semaphore;

#endif
