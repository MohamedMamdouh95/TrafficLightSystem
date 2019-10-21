/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern TrafficLightState State;

int down=0;

void RIT_IRQHandler (void)
{					
	static int select=0;
	static int i=0;	
	static int ticks=0;
	
	/* button management */
	if(down!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* KEY1 pressed */
			down++;				
			switch(down){
				case 2:
					if(State != MAINTENANCE)
					{
						enable_timer(0);
					}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			disable_timer(0);
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
		
	/* joystick management */
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	/* Right Joytick Select pressed */
		select++;
		switch(select){
			case 1:
				if(State ==RED_FLASHING_GREEN)
				{
						State = MAINTENANCE;
						disable_timer(1);
						NVIC_DisableIRQ(EINT0_IRQn);
						init_timer(2,2*HALF_SECOND);
						enable_timer(2);
				}
			
				break;
			default:
				break;
		}
	}
	else{
			select=0;
	}
		
	
			
	/* joystick management */
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	/*Left Joytick Select pressed */
		select++;
		switch(select){
			case 1:
				if(State == MAINTENANCE)
				{
					disable_timer(0);
					disable_timer(1);
					disable_timer(2);
					EnableTrafficLightForPedestrian();
				}
			NVIC_EnableIRQ(EINT0_IRQn);
			
				break;
			default:
				break;
		}
	}
	else{
			select=0;
	}

	/* ADC management */
	ADC_start_conversion();		
			
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
