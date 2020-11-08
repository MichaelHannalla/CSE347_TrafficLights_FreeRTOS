

#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "stack_macros.h"

#define PORT_A    0x01
#define PORT_B    0x02
#define PORT_E    0x10

#define TIMER0           0x01
#define TIMER1           0x02
#define TIMER2           0x04
#define TIMER3           0x08
#define BIT_MODE_32      0x00

#define SOUTH_RED        0x01                        //PIN_B0
#define SOUTH_GREEN      0x02                        //PIN_B1
#define NORTH_RED        0x04                        //PIN_B2
#define NORTH_GREEN      0x08                        //PIN_B3
#define EAST_RED         0x10                        //PIN_B4
#define EAST_GREEN       0x20                        //PIN_B5
#define WEST_RED         0x40                        //PIN_B6
#define WEST_GREEN       0x80                        //PIN_B7

#define SENSOR1                         0x02         //PIN_E1
#define SENSOR2                         0x04         //PIN_E2
#define RESET                           0x20         //PIN_E5

#define PEDESTRIAN_PBS_OR_EMERGENCY     0x10         //PIN_A4
#define SERVO            0x04                        //PIN_A2
#define BUZZER           0x08                        //PIN_A3

#define ALL_PINS  0xFF
#define NO_PINS   0x00

#define PORTA_IRQ  (1U)
#define PORTE_IRQ  (1U<<4)


inline void PortE_Init(void);
inline void PortB_Init(void);
inline void PortA_Init(void);
inline void InitializePORTAInterrupt (void);
inline void InitializePORTEInterrupt (void);
inline void Timers_Init(void);
inline void Timer0A_DelayMs(int ttime);
inline void Timer1A_DelayMs(int ttime);
inline void Timer2A_DelayMs(int ttime);
inline void Timer3A_DelayMs(int ttime);
