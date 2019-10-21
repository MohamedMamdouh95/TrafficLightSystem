#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "../timer/timer.h"
//True Delay Numbers
#define FIFTEEN_SECONDS	0x165A0BC0
#define FIVE_SECONDS	  0x07735940
#define HALF_SECOND			0x00BEBC20

//#define FIFTEEN_SECONDS	0x005A0BC0
//#define FIVE_SECONDS	  0x00015940
//#define HALF_SECOND			0x00000C20

typedef enum
{
	RED_GREEN,
	RED_FLASHING_GREEN,
	GREEN_RED,
	YELLOW_RED,
	WAIT_FOR_REQUEST
}TrafficLightState;




void EnableTrafficLightForPedestrian(void);
void EnableTrafficLighForRoad(void);



#endif
