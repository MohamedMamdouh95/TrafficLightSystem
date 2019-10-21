/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        High level led management functions
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

#define LED_NUM     8                   /* Number of user LEDs                */
const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };
extern char SelectorOneSecondandHalfSecond;
extern unsigned char led_value;
TrafficLightState State = RED_GREEN;
/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(unsigned int num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(unsigned int num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
	led_value = value;
}


void EnableTrafficLightForPedestrian(void)
{
	State = RED_FLASHING_GREEN;
	LED_On(ROAD_RED);
	LED_Off(ROAD_GREEN);
	LED_Off(ROAD_YELLOW);
	
	LED_On(PEDESTRIAN_GREEN);
	LED_Off(PEDESTRIAN_RED);
	LPC_TIM1->TC = 0x00;
	disable_timer(2);
	disable_timer(1);
	init_timer(1,FIFTEEN_SECONDS);
	init_timer(2,2*HALF_SECOND);
	SelectorOneSecondandHalfSecond = 1;
	enable_timer(2);
	enable_timer(1);
}
	
void LED_Toggle(unsigned int value)
{
	  LPC_GPIO2->FIOPIN ^= 1<<value;
		led_value = LPC_GPIO2->FIOPIN;

}