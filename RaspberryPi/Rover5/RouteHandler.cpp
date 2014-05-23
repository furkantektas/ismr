#include "RouteHandler.h"
#include <iostream>

RouteHandler::RouteHandler(PWM* object)
{
	this->object=object;
}

void RouteHandler::handler(Data_t data){

	this->object->resetEncoder();

	for(int i=0;i<data.size;++i){
		Route routeInstr= data.route[i];
		
		switch (routeInstr.way)
		{
		case FORWARD:
			this->moveForward(&routeInstr);
			break;
		case BACK:
			this->moveBackward(&routeInstr);
			break;
		case RIGHT:
			this->moveRight(&routeInstr);
			break;
		case LEFT:
			this->moveLeft(&routeInstr);
			break;
		default:
			break;
		}
		sleep(2);
		this->object->resetEncoder();
	}

}

void RouteHandler::moveForward(Route* route){
	double mm_step = (double)route->step * metreToMmetre;
	int step=(int)mm_step / wheelArea * wheelGear ;
	
	while(object->getTotalDistance1() < step && object ->getTotalDistance2() < step )
     	this->object->forward();

	object->stop();
}

void RouteHandler::moveBackward(Route* route){
	double mm_step = (double)route->step * metreToMmetre;
	int step=(int)mm_step / wheelArea * wheelGear * -1 ;
	
	while(object->getTotalDistance1() > step && object ->getTotalDistance2() > step)
		this->object->backward();

	object->stop();
}

void RouteHandler::moveLeft(Route* route){
	int degree= (int)route->step / 90;
	int step= degree * ninety_degree_turn;

	while(object->getTotalDistance1() > (-1 * step) && object ->getTotalDistance2() < step)
		this->object->left();
	
	object->stop();
}

void RouteHandler::moveRight(Route* route){
	int degree= (int)route->step / 90;
	int step= degree * ninety_degree_turn;

	while(object->getTotalDistance1() < step && object ->getTotalDistance2() > (-1*step))
		this->object->right();

	object->stop();
}