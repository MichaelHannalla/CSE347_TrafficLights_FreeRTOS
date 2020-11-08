/*
Michael Samy Hannalla Tofiles - 16P8202
CSE318 - Microcontrollers
Lab Assignment 7 - Serial UART
UART.h File
*/

#ifndef UART_H
#define UART_H

#include "stdint.h"
#include "stdio.h"
#include "string.h"

extern void UART_Init(void);
extern void PORTA_InitForUART(void);
extern void UART_outChar(uint8_t); 
extern uint8_t UART_inChar(void);
extern void printText(char*);

#endif

