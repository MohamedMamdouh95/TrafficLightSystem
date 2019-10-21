																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_led, funct_led .c files
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "../timer/timer.h"

/* lib_led */
void LED_init(void);
void LED_deinit(void);

/* funct_led */
void LED_On (unsigned int num);
void LED_Off (unsigned int num);
void LED_Out(unsigned int value);

void LED_Toggle(unsigned int value);

//True Delay Numbers
#define FIFTEEN_SECONDS	0x165A0BC0
#define FIVE_SECONDS	  0x07735940
#define HALF_SECOND			0x00BEBC20

#define PEDESTRIAN_RED		7
#define PEDESTRIAN_GREEN	6

#define ROAD_RED			5
#define	ROAD_YELLOW		4
#define ROAD_GREEN		3	

//#define FIFTEEN_SECONDS	0x005A0BC0
//#define FIVE_SECONDS	  0x00015940
//#define HALF_SECOND			0x00000C20

typedef enum
{
	RED_GREEN,
	RED_FLASHING_GREEN,
	GREEN_RED,
	YELLOW_RED,
	WAIT_FOR_REQUEST,
	MAINTENANCE
}TrafficLightState;



void EnableTrafficLightForPedestrian(void);
