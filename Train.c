/*
*Term Project - Multi-junction traffic light controller
*CSE347 - Embedded System Design
*** Train Approaching Mode ***
*/

#ifndef TRAIN_C_
#define TRAIN_C_

#include "Train.h"
 
void vTrainApproaching(void *pvParameters)  
{
    xSemaphoreTake( xBinaryTrainSensor1Semaphore, 0 );			/* Train Task loop will not be implemented unless it takes
													               a semaphore when sensor 1 detects a train approaching */
    while(1)
    {
        /* The tasks starts when SENSOR1 detects a train approaching, so it stops all junctions, closes
         * the train gate and turns a siren on, then it waits for a duration that ensures the longest train
		 * has passed to turn off the siren, open the gate and get blocked for the normal mode to continue
        */


        xSemaphoreTake(xBinaryTrainSensor1Semaphore, portMAX_DELAY);
        printText("Train is crossing now. \n\r");
        vTaskSuspend(xNormalNorthSouthHandle);
        vTaskSuspend(xNormalEastWestHandle);
        vTaskSuspend(xTaskPedestriansHandle);
        StopAllJunctions();
		CloseTrainGate();
		TurnOnSiren();
		GPIO_PORTE_IM_R |= SENSOR2 ;		 // Enable interrupt (Unmask)
		//Timer3A_DelayMs(tSafety_in_ms);	 // Duration ensuring passage of longest train
        vTaskDelay(TRAIN_PERIOD_TICKS);
		while(!TrainCrossed);						 // Loop won't be broken unless flag of SENSOR2 is raised
		TrainCrossed = false;						 // Clearing flag of SENSOR2
		TurnOffSiren();
		OpenTrainGate();
		GPIO_PORTE_IM_R &= (~(SENSOR2)) ;		 // Disable interrupt (mask)
		printText("Train crossed. \n\r");
		vTaskResume(xNormalNorthSouthHandle);
		vTaskResume(xNormalEastWestHandle);
		vTaskResume(xTaskPedestriansHandle);
    }
}
	
inline void StopAllJunctions(void) 
{
    GPIO_PORTB_DATA_R &= ~(NORTH_GREEN | SOUTH_GREEN | EAST_GREEN | WEST_GREEN);	// Stop the "Go Mode"
    GPIO_PORTB_DATA_R |= (NORTH_RED | SOUTH_RED | EAST_RED | WEST_RED);						// Start the "Stop Mode"
}

inline void CloseTrainGate(void) 	 
{	
    GPIO_PORTA_DATA_R |= SERVO;    			// Turn Servo gate LED on
}

inline void OpenTrainGate(void) 	 
{
    GPIO_PORTA_DATA_R &= ~SERVO;    		// Turn Servo gate LED off
}

inline void TurnOnSiren(void)      
{
    GPIO_PORTA_DATA_R |= BUZZER;				// Turn Buzzer on
}

inline void TurnOffSiren(void)     
{
    GPIO_PORTA_DATA_R &= ~BUZZER;			                 	// Turn Buzzer off
}

void TrainSensorsHandler(void)		 			                // PortE ISR
{
    if((GPIO_PORTE_RIS_R & SENSOR1)== SENSOR1)					// Interrupt at Pin E1 (SENSOR1)
    {
        GPIO_PORTE_ICR_R |= SENSOR1;                            // Clear Interrupt Flag
        GPIO_PORTE_ICR_R |= SENSOR2;
        printText("Train reached sensor 1. \n\r");
        portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR( xBinaryTrainSensor1Semaphore, &xHigherPriorityTaskWoken );
		portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );	    // Force Context Switch
	}

    if((GPIO_PORTE_RIS_R & SENSOR2)== SENSOR2)				    // Interrupt at Pin E2 (SENSOR2)
	{
        GPIO_PORTE_ICR_R |= SENSOR2;                            // Clear Interrupt Flag
        GPIO_PORTE_ICR_R |= SENSOR1;
        printText("Train reached sensor 2. \n\r");
        TrainCrossed = true;									// Raise SENSOR2 flag - Train has crossed

	}
}

#endif
