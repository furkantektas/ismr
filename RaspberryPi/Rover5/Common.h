#ifndef COMMON_H
#define COMMON_H

enum Direction {FORWARD,BACK,RIGHT,LEFT,EMPTY,KATDEGISTIR};

struct Route
{
	Direction way;
	double step;
};

struct Data_t{
	Route route[20];
	int size;
};

#endif