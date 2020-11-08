/*
 * Normal.h
 *
 *  Created on: Apr 13, 2020
 *      Author: Haidy Sorial Samy | Michael Samy Hannalla
 */

#ifndef NORMAL_H_
#define NORMAL_H_

#include "initializations.h"
#include <stdint.h>
#include "FreeRTOSConfig.h"
#include "UART.h"

#define NS_PRI              2
#define EW_PRI              1

#define NS_PERIOD_TICKS   (uint32_t)(((float)5000 / 1000) * configTICK_RATE_HZ) //5000 milliseconds
#define EW_PERIOD_TICKS   (uint32_t)(((float)2500 / 1000) * configTICK_RATE_HZ) //2500 milliseconds

#define NS_PERIOD_MS   5000 //5000 milliseconds
#define EW_PERIOD_MS   2500 //2500 milliseconds

void vNormalNorthSouth(void *pvParameters);
void vNormalEastWest(void *pvParameters);

inline void StartNorthSouth(void);
inline void StopNorthSouth(void);
inline void StartEastWest(void);
inline void StopEastWest(void);

xTaskHandle xNormalNorthSouthHandle;
xTaskHandle xNormalEastWestHandle;
xSemaphoreHandle xMutex;

#endif /* NORMAL_H_ */
