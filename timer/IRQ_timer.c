/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"
extern TrafficLightState State;
extern short AD_current;
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
char SelectorOneSecondandHalfSecond = 0;
uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

void TIMER0_IRQHandler (void)
{
	static int ticks=0;
	static short temp =1;
	if(State == MAINTENANCE)
	{
		temp = (AD_current*7/0xFFF)+1;
	}
	/* DAC management */	
	LPC_DAC->DACR = ((SinTable[ticks])/temp)<<6;
	ticks++;
	if(ticks==45) ticks=0;

	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	if(State == RED_GREEN)
	{
		LED_On(ROAD_RED);
		LED_Off(ROAD_GREEN);
		LED_Off(ROAD_YELLOW);
		
		LED_On(PEDESTRIAN_GREEN);
		LED_Off(PEDESTRIAN_RED);
		
		State = RED_FLASHING_GREEN;
		LPC_TIM1->TC = 0x00;
		
		init_timer(1,FIFTEEN_SECONDS);
		init_timer(2,2*HALF_SECOND);
		SelectorOneSecondandHalfSecond = 1;
		enable_timer(2);
		enable_timer(1);
	}
	else if(State == RED_FLASHING_GREEN)
	{
		SelectorOneSecondandHalfSecond = 0;
		init_timer(2,HALF_SECOND);
		enable_timer(2);
		LED_On(ROAD_RED);
		LED_Off(ROAD_GREEN);
		LED_Off(ROAD_YELLOW);
		State = GREEN_RED;
		LPC_TIM1->TC = 0x00;
		init_timer(1,FIVE_SECONDS);
		enable_timer(1);
	}
	else if(State == GREEN_RED)
	{
		disable_timer(2);
		disable_timer(0);
		LED_Off(ROAD_RED);
		LED_Off(ROAD_YELLOW);
		LED_Off(PEDESTRIAN_GREEN);
		
		LED_On(ROAD_GREEN);
		LED_On(PEDESTRIAN_RED);
		State = WAIT_FOR_REQUEST;
	}
	else if(State == YELLOW_RED)
	{
		LED_Off(ROAD_GREEN);
		LED_Off(ROAD_RED);
		LED_On(ROAD_YELLOW);
		
		LED_On(PEDESTRIAN_RED);
		LED_Off(PEDESTRIAN_GREEN);
		
		State = RED_GREEN;
		LPC_TIM1->TC = 0x00;
		init_timer(1,FIVE_SECONDS);
		enable_timer(1);
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	static char flag =0 ;
	static char flag1 =0 ;
	//hello++;
	if(State == MAINTENANCE)
	{
		
		LED_Off(ROAD_GREEN);
		LED_Off(ROAD_RED);
		LED_Off(PEDESTRIAN_GREEN);
		LED_Toggle(PEDESTRIAN_RED);
		LED_Toggle(ROAD_YELLOW);
		if(flag1==0)
		{
			enable_timer(0);
			flag1 = 1;
		}
		else
		{
			disable_timer(0);
			flag1 = 0;
		}
		init_timer(2,2*HALF_SECOND);
		enable_timer(2);
	}
		
	if(SelectorOneSecondandHalfSecond == 0) //one Second timer
	{
		
		if(flag==0)
		{
			enable_timer(0);
			flag = 1;
		}
		else
		{
			disable_timer(0);
			flag = 0;
		}
		LED_Toggle(PEDESTRIAN_GREEN);
	}
	else
	{
			if(flag==0)
		{
			enable_timer(0);
			flag = 1;
		}
		else
		{
			disable_timer(0);
			flag = 0;
		}
	}
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}



/******************************************************************************
**                            End Of File
******************************************************************************/
