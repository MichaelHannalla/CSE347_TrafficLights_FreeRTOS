#ifndef PEDESRTRIANS_C_
#define PEDESRTRIANS_C_


#include "Pedestrians.h"



void vTaskPedestrians(void *pvParameters)
{
	xSemaphoreTake ( xPedestrianSemaphore, 0);                            //waiting for semaphore to execute task
	
	for( ;; )
	{
		xSemaphoreTake(xPedestrianSemaphore, portMAX_DELAY);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		printText("Allowing pedestrian to cross. \n\r");
		GPIO_PORTB_DATA_R = (SOUTH_RED | NORTH_RED | EAST_RED | WEST_RED) ;/*turn on all RED lights
                                                                              and turn off all green lights */
		//Timer0A_DelayMs(TCROSS_PERIOD_TICKS);                              // a 10 second delay
		vTaskDelay(TCROSS_PERIOD_TICKS);
		xSemaphoreGive(xMutex);
	}
}
void GPIO_PORTA_Handler(void)
{
    GPIO_PORTA_ICR_R |= PEDESTRIAN_PBS_OR_EMERGENCY;                      //clears port E interrupt flag
    printText("Pedestrian button is pressed. \n\r");
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xPedestrianSemaphore, &xHigherPriorityTaskWoken);

}

#endif
