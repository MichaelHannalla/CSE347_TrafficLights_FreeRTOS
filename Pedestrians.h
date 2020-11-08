#ifndef PEDESRTRIANS_H_
#define PEDESRTRIANS_H_

#include <stdint.h> 
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "initializations.h"
#include "Normal.h"
#include "UART.h"

#define TCROSS_PERIOD_TICKS   10000    //10000 milliseconds

#define PED_PRI              3         // Priority of pedestrian task

xTaskHandle xTaskPedestriansHandle;    // Pedestrian task handle
xSemaphoreHandle xPedestrianSemaphore; // Pedestrian semaphore task handle

void vTaskPedestrians(void *pvParameters);
void GPIO_PORTA_Handler(void);

#endif
