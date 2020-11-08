/*
Michael Samy Hannalla Tofiles - 16P8202
CSE318 - Microcontrollers
Lab Assignment 7 - Serial UART
UART.c File
*/

#include "tm4c123gh6pm.h"
#include "UART.h"


#ifndef UART_C
#define UART_C

void PORTA_InitForUART(void)
{
  // INITIALIZING PORTA WITH NEEDED FUNCTIONALITIES
  
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // Inializing PORTA with Clock Gating Control
  
  // Wait for stabilization
  while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R0) == SYSCTL_RCGCGPIO_R0));   
  
  GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;       // Unlocking CR Register with Magic Code
  GPIO_PORTA_CR_R = 0x0000000FFU; 
  
  GPIO_PORTA_DEN_R = 0x3U;                // Digital Enabling  
  
  GPIO_PORTA_AFSEL_R |= 0x3U;
  GPIO_PORTA_PCTL_R  |= 0x11U;              // Configuring pins A0 and A1 for UART
}

void UART_Init(void)
{ 
  SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;  
  
  // Wait for stabilization
  while(!((SYSCTL_RCGCUART_R & SYSCTL_RCGCUART_R0) == SYSCTL_RCGCUART_R0)); 
  
  UART0_CTL_R &= ~(0x1U);                  // Clearing UART0EN bit to disable UART0
  
  PORTA_InitForUART();                     
  
  UART0_IBRD_R = 104;                      // For 9600 BAUD RATE
  UART0_FBRD_R = 11;                       // For 9600 BAUD RATE
  UART0_LCRH_R = 0x60U;
  UART0_CC_R = 0x0U;                       // Clock source is system clock
  
  UART0_CTL_R |= 0x301U;                   // Setting UART0EN bit to enable UART0
}

uint8_t UART_inChar(void)
{
  char recievedChar;
  while((UART0_FR_R & 0x10) != 0);          // Wait until the Rx buffer isn't empty  
  recievedChar = UART0_DR_R;                // Read the UART data register
  return recievedChar;
}

void UART_outChar(uint8_t transmittedChar)
{
  while((UART0_FR_R & 0x20) != 0);          // Wait until Tx buffer not full 
  UART0_DR_R = transmittedChar;   
}

void printText(char* textToPrint)
{
    int i;
    for (i=0 ; i< strlen(textToPrint) ; i++)
    {
        UART_outChar(textToPrint[i]);
    }
}

#endif
