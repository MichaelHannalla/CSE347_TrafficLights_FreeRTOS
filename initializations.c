#include "initializations.h"

inline void Timers_Init(void)
{

	SYSCTL_RCGCTIMER_R |= (TIMER0 | TIMER1 | TIMER2 | TIMER3); 	//Clock Enabled for Timers 0,1,2,3
 	TIMER0_CTL_R = NO_PINS;                                     //Disable Timer While Configuring
	TIMER1_CTL_R = NO_PINS;
	TIMER2_CTL_R = NO_PINS;
	TIMER3_CTL_R = NO_PINS;
	
	TIMER0_CFG_R = BIT_MODE_32;                                 //Configure Timer0 as 32 Bit Mode
	TIMER1_CFG_R = BIT_MODE_32;
	TIMER2_CFG_R = BIT_MODE_32;
	TIMER3_CFG_R = BIT_MODE_32;
	
	TIMER0_TAMR_R = (0x22);                                     //Periodic with Match Interrupt Enable
	TIMER1_TAMR_R = (0x22);
	TIMER2_TAMR_R = (0x22);
	TIMER3_TAMR_R = (0x22);
	
	TIMER0_CTL_R |= (0x03);                                     //Enable Timer
	TIMER1_CTL_R |= (0x03);
	TIMER2_CTL_R |= (0x03);
	TIMER3_CTL_R |= (0x03);
	
}
inline void PortE_Init(void)
{

	SYSCTL_RCGC2_R |= PORT_E;                                 //Enable Clock for PortE
	GPIO_PORTE_LOCK_R  = GPIO_LOCK_KEY;
	GPIO_PORTE_CR_R    = ALL_PINS;
	GPIO_PORTE_AMSEL_R = NO_PINS;
	GPIO_PORTE_PCTL_R  = NO_PINS;
	GPIO_PORTE_DIR_R &= ~(SENSOR1 | SENSOR2 | RESET);           //Assign Pins 1,2,5 as Inputs
	GPIO_PORTE_PUR_R |= (SENSOR1 | SENSOR2 | RESET);            //Enable Pulling Up
	GPIO_PORTE_DEN_R |= (SENSOR1 | SENSOR2 | RESET);            //Enable Pins 1,2,5
}

inline void PortB_Init(void)
{

	SYSCTL_RCGC2_R   |= PORT_B;                                  //Enable Clock for PortB
	GPIO_PORTB_DIR_R |= ALL_PINS;      		                     //Assign All Pins as Outputs
	GPIO_PORTB_DEN_R |= ALL_PINS;                                //Enable All Pins
}

inline void PortA_Init(void){
	
	SYSCTL_RCGC2_R      |= PORT_A;                                //Enable Clock for PortA
	GPIO_PORTA_LOCK_R    =  GPIO_LOCK_KEY;
	GPIO_PORTA_CR_R     |=  (ALL_PINS & (~0x3U));
	//GPIO_PORTA_AMSEL_R = SERVO;                                 //Enable PIN_A2 as Analogue
	//GPIO_PORTA_PCTL_R  = NO_PINS;
	GPIO_PORTA_DIR_R    |= (SERVO | BUZZER);                      //Set Pins A2 and A3 as Outputs
	GPIO_PORTA_DIR_R    &= ~(PEDESTRIAN_PBS_OR_EMERGENCY);        //Set Pin A4 as Input
	GPIO_PORTA_PUR_R    |= (PEDESTRIAN_PBS_OR_EMERGENCY);         //Enable Pulling Up On Pin A4
	GPIO_PORTA_DEN_R    |= (SERVO | BUZZER | PEDESTRIAN_PBS_OR_EMERGENCY);
} 

inline void InitializePORTAInterrupt (void)
{
	NVIC_EN0_R       |= PORTA_IRQ;				         		// Enable NVIC
	GPIO_PORTA_IS_R  &= ~( PEDESTRIAN_PBS_OR_EMERGENCY );	    // edge not level
	GPIO_PORTA_IBE_R &= ~( PEDESTRIAN_PBS_OR_EMERGENCY );	    // single edge
	GPIO_PORTA_IEV_R &= ~( PEDESTRIAN_PBS_OR_EMERGENCY );	    // Falling edge
	GPIO_PORTA_ICR_R |= ( PEDESTRIAN_PBS_OR_EMERGENCY );	    // Clear interrupt flag
	GPIO_PORTA_IM_R  |= ( PEDESTRIAN_PBS_OR_EMERGENCY );		// Enable interrupt (unmasked)
	
}

inline void InitializePORTEInterrupt (void)
{
	NVIC_EN0_R |= PORTE_IRQ;	   			                   			  // Enable NVIC
	GPIO_PORTE_IS_R &= ~( SENSOR1 | SENSOR2 );	                // edge not level
	GPIO_PORTE_IBE_R &= ~( SENSOR1 | SENSOR2 );	                // single edge
	GPIO_PORTE_IEV_R &= ~( SENSOR1 | SENSOR2 );	                // Falling edge
	GPIO_PORTE_ICR_R |= ( SENSOR1 | SENSOR2 );	                // Clear interrupt flag
	//	GPIO_PORTE_IM_R |= ( SENSOR1 | SENSOR2 );	             	// Enable interrupt (unmasked)
	GPIO_PORTE_IM_R |= SENSOR1;	 																// Enable interrupt (unmasked)
}	

inline void Timer0A_DelayMs(int ttime)
{
    TIMER0_CTL_R = NO_PINS;                                     //Disable Timer before initialization
    TIMER0_TAILR_R = 16000 * ttime - 1;  
    TIMER0_TAMATCHR_R = 0x7F;
    TIMER0_ICR_R = 0x11;                                        //Clear the TimerA timeout flag and MATCH flag
    TIMER0_CTL_R |= 0x03;                                       //Enable Timer A after initialization
    while ((TIMER0_RIS_R & 0x1) == 0);                          //Wait for TimerA timeout flag to set
}

inline void Timer1A_DelayMs(int ttime)
{
    TIMER1_CTL_R = NO_PINS;                                     //Disable Timer before initialization
    TIMER1_TAILR_R = 16000 * ttime - 1;  
    TIMER1_TAMATCHR_R = 0x7F;
    TIMER1_ICR_R = 0x11;                                        //Clear the TimerA timeout flag and MATCH flag
    TIMER1_CTL_R |= 0x03;                                       //Enable Timer A after initialization
    while ((TIMER1_RIS_R & 0x1) == 0) ;                         //Wait for TimerA timeout flag to set
}

inline void Timer2A_DelayMs(int ttime)
{
    TIMER2_CTL_R = NO_PINS;                                    //Disable Timer before initialization
    TIMER2_TAILR_R = 16000 * ttime - 1;  
    TIMER2_TAMATCHR_R = 0x7F;
    TIMER2_ICR_R = 0x11;                                       //Clear the TimerA timeout flag and MATCH flag
    TIMER2_CTL_R |= 0x03;                                      //Enable Timer A after initialization
    while ((TIMER2_RIS_R & 0x1) == 0) ;                        //Wait for TimerA timeout flag to set
}

inline void Timer3A_DelayMs(int ttime)
{
    TIMER3_CTL_R = NO_PINS;                                    //Disable Timer before initialization
    TIMER3_TAILR_R = 16000 * ttime - 1;  
    TIMER3_TAMATCHR_R = 0x7F;
    TIMER3_ICR_R = 0x11;                                       //Clear the TimerA timeout flag and MATCH flag
    TIMER3_CTL_R |= 0x03;                                      //Enable Timer A after initialization
    while ((TIMER3_RIS_R & 0x1) == 0) ;                        //Wait for TimerA timeout flag to set
}
