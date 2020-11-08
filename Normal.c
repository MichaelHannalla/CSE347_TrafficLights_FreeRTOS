/*
 * Normal.c
 *
 *  Created on: Apr 13, 2020
 *      Author: Michael Samy Hannalla | Haidy Sorial Samy
 */

#ifndef NORMAL_C_
#define NORMAL_C_

#include "Normal.h"

void vNormalNorthSouth(void *pvParameters)
{
    for(;;)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        printText("In normal mode, north south direction. \n\r");
        /* The task starts by suspending traffic flow in other direction, then starts in its direction,
         * awaits then for the specified time period then gets blocked.
         */
        StopEastWest();
        StartNorthSouth();
        //Timer0A_DelayMs(NS_PERIOD_MS);   /* Stay still */
        vTaskDelay(NS_PERIOD_TICKS);
        xSemaphoreGive(xMutex);
        StopNorthSouth();
        vTaskDelay(EW_PERIOD_TICKS);     /* Get blocked by duration of other task */
    }
}

void vNormalEastWest(void *pvParameters)
{
    for(;;)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        printText("In normal mode, east west direction. \n\r");
        /* The tasks starts by suspending traffic flow in other direction, then starts in its direction,
        * awaits then for the specified time period then gets blocked.
        */
        StopNorthSouth();
        StartEastWest();
        //Timer0A_DelayMs(EW_PERIOD_MS);  /* Stay still */
        vTaskDelay(EW_PERIOD_TICKS);
        xSemaphoreGive(xMutex);
        StopEastWest();
        vTaskDelay(NS_PERIOD_TICKS);    /* Get blocked by duration of other task */
    }
}

inline void StartNorthSouth()
{
    // Start North-South Flow
    GPIO_PORTB_DATA_R |= (NORTH_GREEN | SOUTH_GREEN);
    GPIO_PORTB_DATA_R &= ~(NORTH_RED | SOUTH_RED);
}

inline void StopNorthSouth()
{
    // Stop North-South Flow
    GPIO_PORTB_DATA_R &= ~(NORTH_GREEN | SOUTH_GREEN);
    GPIO_PORTB_DATA_R |= (NORTH_RED | SOUTH_RED);
}

inline void StartEastWest()
{
    // Start East-West Flow
    GPIO_PORTB_DATA_R |= (EAST_GREEN | WEST_GREEN);
    GPIO_PORTB_DATA_R &= ~(EAST_RED | WEST_RED);
}

inline void StopEastWest()
{
    // Stop East-West Flow
    GPIO_PORTB_DATA_R &= ~(EAST_GREEN | WEST_GREEN);
    GPIO_PORTB_DATA_R |= (EAST_RED | WEST_RED);
}

#endif /* NORMAL_H_ */
