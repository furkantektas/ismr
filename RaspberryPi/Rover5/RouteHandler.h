#ifndef ROUTE_HANDLER_H
#define ROUTE_HANDLER_H

#include "Common.h"
#include "pwm.h"

const double wheelArea = 188.4 ; //mm 
const int wheelGear = 330;
const int ninety_degree_turn= 420;
const int metreToMmetre = 1000;

class RouteHandler
{
public:
	RouteHandler(PWM* object);
	void handler(Data_t data);
	

private:
	PWM* object;
	void moveRight(Route *route);
	void moveLeft(Route *route);
	void moveForward(Route *route);
	void moveBackward(Route* route);
};

#endif