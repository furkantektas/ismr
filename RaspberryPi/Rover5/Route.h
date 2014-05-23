#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include "Common.h"

enum YON{NORTH,SOUTH,WEST=3,EAST};

struct  Coordinate
{
	double x;
	double y;
	YON yon;
	int kat;
	int kapiYon;
};

const Coordinate BASLANGIC0 ={0.0,0.0,WEST,0,0};
const Coordinate Z23 = {-9.2,3.22,EAST,0,0};
const Coordinate Z20 = {-9.2,13.3,EAST,0,0};
const Coordinate Z12 = {-9.2,25.3,EAST,0,0};
const Coordinate Z10 = {-11.5,28.0,EAST,0,0};
const Coordinate Z05 = {-11.5,30.3,SOUTH,0,0};
const Coordinate Z04 = {-2.76,30.3,SOUTH,0,0};
const Coordinate Z02 = {3.24,30.3,SOUTH,0,0};
const Coordinate ROBOTIK = {11.5,30.3,SOUTH,0,0};
const Coordinate Z06 = {11.5,25.5,WEST,0,0};
const Coordinate Z11 = {9.2,24.8,WEST,0,0};
const Coordinate GENEL_LAB = {9.2,12.8,WEST,0,0};
const Coordinate KANTIN = {9.2,1.8,WEST,0,0};

/*1.kat*/
const Coordinate BASLANGIC1 ={0.0,0.0,WEST,1,0};
const Coordinate N123 = {-9.2,2.3,EAST,1,0};
const Coordinate N121 = {-9.2,6.8,EAST,1,0};
const Coordinate N119 = {-9.2,11.4,EAST,1,0};
const Coordinate N109 = {-9.2,23.4,EAST,1,0};
const Coordinate N104 = {-9.2,30.3,EAST,1,0};
const Coordinate N103 = {-5,30.3,SOUTH,1,0};
const Coordinate N102 = {1.4,30.3,SOUTH,1,0};
const Coordinate N101 = {9.2,30.3,WEST,1,0};
const Coordinate N108 = {9.2,23.58,WEST,1,0};
const Coordinate N118 = {9.2,11.58,WEST,1,0};
const Coordinate N120 = {9.2,6.48,WEST,1,0};
const Coordinate N122 = {9.2,1.38,WEST,1,0};
const Coordinate N24 = {9.2,-4.0,WEST,1,0};


/*2.kat*/
const Coordinate BASLANGIC2 ={0.0,0.0,WEST,2,0};
const Coordinate N254 = {-3.22,0,NORTH,2,0};
const Coordinate N255 = {-7.5,0,NORTH,2,0};
const Coordinate N248 = {-11.6,0,NORTH,2,0};
const Coordinate N208 = {-11.6,2.66,NORTH,2,0};
const Coordinate N243 = {-9.2,6.8,EAST,2,0};
const Coordinate N244 = {-9.2,6.8,EAST,2,1};
const Coordinate N239 = {-9.2,10.02,EAST,2,0};
const Coordinate N240 = {-9.2,10.02,EAST,2,1};
const Coordinate N235 = {-9.2,12.78,EAST,2,0};
const Coordinate N234 = {-9.2,12.78,EAST,2,1};
const Coordinate N230 = {-9.2,16.0,EAST,2,1};
const Coordinate N226 = {-9.2,18.76,EAST,2,1};
const Coordinate N221 = {-9.2,20.14,EAST,2,0};
const Coordinate N220 = {-9.2,21.52,EAST,2,1};
const Coordinate N216 = {-9.2,23.36,EAST,2,0};
const Coordinate N215 = {-9.2,24.74,EAST,2,1};
const Coordinate N212 = {-11.5,27.5,EAST,2,0};
const Coordinate N207 = {-11.5,30.3,SOUTH,2,0};
const Coordinate N206 = {-9.68,30.3,SOUTH,2,0};
const Coordinate N205 = {-5.54,30.3,SOUTH,2,0};
const Coordinate N204 = {-1.4,30.3,SOUTH,2,0};
const Coordinate N203 = {2.74,30.3,SOUTH,2,0};
const Coordinate N202 = {6.88,30.3,SOUTH,2,0};
const Coordinate N201 = {9.2,30.3,WEST,2,0};
const Coordinate N214 = {9.2,24.8,WEST,2,-1};
const Coordinate N213 = {9.2,23.4,WEST,2,0};
const Coordinate N219 = {9.2,21.58,WEST,2,-1};
const Coordinate N218 = {9.2,20.2,WEST,2,0};
const Coordinate N225 = {9.2,18.4,WEST,2,-1};
const Coordinate N229 = {9.2,15.64,WEST,2,-1};
const Coordinate N233 = {9.2,12.88,WEST,2,-1};
const Coordinate N232 = {9.2,12.88,WEST,2,0};
const Coordinate N237 = {9.2,9.66,WEST,2,0};
const Coordinate N238 = {9.2,9.66,WEST,2,-1};
const Coordinate N241 = {9.2,6.9,WEST,2,0};
const Coordinate N242 = {9.2,6.9,WEST,2,-1};
const Coordinate N251 = {9.2,0.0,NORTH,2,0};
const Coordinate N252 = {5.04,0.0,NORTH,2,0};
const Coordinate N253 = {0.9,0.0,NORTH,2,0};

const double WEST_NORTH_LIMIT=9.2;
const double EAST_NORTH_LIMIT=-9.2;
const double WEST_SOUTH_LIMIT=11.5;
const double EAST_SOUTH_LIMIT=-11.5;
const double SOUTH_LIMIT=30.3;
const double NORTH_LIMIT=0.0;
const double EXCEPTION_CLASS_Y=28.0;
const double EXCEPTION_CLASS_EAST_X=-11.5;
const double EXCEPTION_CLASS_WEST_X=11.5;
const double EXCEPTION_CLASS_K1_WESTY=-4.5;



Data_t findRoute(Coordinate current,Coordinate next);
Route findDirection(YON current,YON next);
void addData(Data_t *data,Direction direct,double step);
void addData(Data_t *data,Route route);
void addData(Data_t *data,const Data_t *next);
Data_t calculateRoute(Coordinate& current,Coordinate& next);
void kat_three_kontrol(Data_t* data,Coordinate current);
Data_t findRouteControl(Coordinate& current,Coordinate& next);
Coordinate getCoordinate(std::string coor);

#endif