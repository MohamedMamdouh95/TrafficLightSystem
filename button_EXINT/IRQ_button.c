#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"

extern TrafficLightState State;

extern int down;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	if(State == WAIT_FOR_REQUEST)
	{
		State = YELLOW_RED;
		LPC_TIM1->TC = 0x00;
		init_timer(1,FIVE_SECONDS);
		enable_timer(1);
	}
	else if(State == GREEN_RED)
	{
			EnableTrafficLightForPedestrian();
	}
	else if(State == YELLOW_RED)
	{
		//NOTHING HERE	
	}
	else if(State == RED_GREEN)
	{
		//Nothing
	}
	else if(State == MAINTENANCE)
	{
		//Nothing
	}
	else
	{
		EnableTrafficLightForPedestrian();
	}
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	down=1;
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	if(State == WAIT_FOR_REQUEST)
	{
		State = YELLOW_RED;
		LPC_TIM1->TC = 0x00;
		init_timer(1,FIVE_SECONDS);
		enable_timer(1);
	}
	else if(State == GREEN_RED)
	{
			EnableTrafficLightForPedestrian();
	}
	else if(State == YELLOW_RED)
	{
		//NOTHING HERE	
	}
	else if(State == RED_GREEN)
	{
		//Nothing
	}
	else if(State == MAINTENANCE)
	{
		//Nothing
	}
	else
	{
		EnableTrafficLightForPedestrian();
	}
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	if(State == WAIT_FOR_REQUEST)
	{
		State = YELLOW_RED;
		LPC_TIM1->TC = 0x00;
		init_timer(1,FIVE_SECONDS);
		enable_timer(1);
	}
	else if(State == GREEN_RED)
	{
			EnableTrafficLightForPedestrian();
	}
	else if(State == YELLOW_RED)
	{
		//NOTHING HERE	
	}
	else if(State == RED_GREEN)
	{
		//Nothing
	}
	else if(State == MAINTENANCE)
	{
		//Nothing
	}
	else
	{
		EnableTrafficLightForPedestrian();
	}
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


