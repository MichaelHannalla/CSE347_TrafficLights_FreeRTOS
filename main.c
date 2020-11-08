/**
 *
 * CSE347 - Embedded Systems Design
 * Faculty of Engineering - Ain Shams University
 * Final Project - Multijunction Controller - Main for Testing Normal Mode
 *
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "initializations.h"
#include "Normal.h"
#include "Pedestrians.h"
#include "Train.h"
#include "tm4c123gh6pm.h"
#include "UART.h"



int main(void)
{
    __asm(" CPSIE I ");
    /* Initialization of ports */
    UART_Init();
    PortA_Init();
    InitializePORTAInterrupt();
    PortB_Init();
    PortE_Init();
    InitializePORTEInterrupt();
    Timers_Init();

    xMutex = xSemaphoreCreateMutex();

    /* Creation of north south normal mode task */
    xTaskCreate(vNormalNorthSouth,
                (const portCHAR *)"Normal NS",
                configMINIMAL_STACK_SIZE,
                NULL, NS_PRI, &xNormalNorthSouthHandle);

    /* Creation of east west normal mode task */
    xTaskCreate(vNormalEastWest,
                (const portCHAR *)"Normal EW",
                configMINIMAL_STACK_SIZE,
                NULL, EW_PRI, &xNormalEastWestHandle);


    vSemaphoreCreateBinary(xPedestrianSemaphore);
    xTaskCreate( vTaskPedestrians, (const portCHAR *)"TaskPedestrians",
                 configMINIMAL_STACK_SIZE,
                 NULL, PED_PRI , &xTaskPedestriansHandle);

    vSemaphoreCreateBinary(xBinaryTrainSensor1Semaphore);
    xTaskCreate( vTrainApproaching, (const portCHAR *)"TaskTrain",
                     configMINIMAL_STACK_SIZE,
                     NULL, TRAIN_PRI , NULL);



    vTaskStartScheduler(); /* Start scheduling */

    for(;;); /* Program should never reach this line */
	return 0;
}
