#include "TrafficLight.h"
#include "../led/led.h"
#include "lpc17xx.h"

TrafficLightState State = RED_GREEN;

void EnableTrafficLighForRoad(void)
{
	LED_On(ROAD_GREEN);
	
	LED_Off(ROAD_RED);
	LED_Off(ROAD_YELLOW);
	
	LED_On(PEDESTRIAN_RED);
	LED_Off(PEDESTRIAN_GREEN);
}
	
void EnableTrafficLightForPedestrian(void)
{
	State = RED_FLASHING_GREEN;
	LED_On(ROAD_RED);
	LED_Off(ROAD_GREEN);
	LED_Off(ROAD_YELLOW);
	
	LED_On(PEDESTRIAN_GREEN);
	LED_Off(PEDESTRIAN_RED);
	LPC_TIM0->TC = 0x00;
	disable_timer(2);
	init_timer(1,0,FIFTEEN_SECONDS);
	enable_timer(1);
	
	
}
	
