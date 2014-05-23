#include "Route.h"
#include <iostream>
#include <cmath>

using namespace std;

Data_t calculateRoute(Coordinate& current,Coordinate& next){
	Data_t data;
	data=findRouteControl(current,next);
	return data;
}

Coordinate getCoordinate(string coor){
	
	if(!coor.compare("z23")){
		return Z23;
	}else if(!coor.compare("z02")){
		return Z02;
	}else if(!coor.compare("z04")){
		return Z04;
	}else if(!coor.compare("z05")){
		return Z05;
	}else if(!coor.compare("z06")){
		return Z06;
	}else if(!coor.compare("z10")){
		return Z10;
	}else if(!coor.compare("z11")){
		return Z11;
	}else if(!coor.compare("z12")){
		return Z12;
	}else if(!coor.compare("z20")){
		return Z20;
	}else if(!coor.compare("z23")){
		return Z23;
	}else if(!coor.compare("baslangic0")){
		return BASLANGIC0;
	}else if(!coor.compare("kantin")){
		return KANTIN;
	}else if(!coor.compare("genellab")){
		return GENEL_LAB;
	}else if(!coor.compare("baslangic1")){
		return BASLANGIC1;
	}else if(!coor.compare("n101")){
		return N101;
	}else if(!coor.compare("n102")){
		return N102;
	}else if(!coor.compare("n109")){
		return N109;
	}else if(!coor.compare("n122")){
		return N122;
	}else if(!coor.compare("n120")){
		return N120;
	}else if(!coor.compare("n118")){
		return N118;
	}else if(!coor.compare("n108")){
		return N108;
	}else if(!coor.compare("n103")){
		return N103;
	}else if(!coor.compare("n104")){
		return N104;
	}else if(!coor.compare("n119")){
		return N119;
	}else if(!coor.compare("n121")){
		return N121;
	}else if(!coor.compare("n123")){
		return N123;
	}else if(!coor.compare("baslangic2")){
		return BASLANGIC2;
	}else if(!coor.compare("n253")){
		return N253;
	}else if(!coor.compare("n252")){
		return N252;
	}else if(!coor.compare("n251")){
		return N251;
	}else if(!coor.compare("n254")){
		return N254;
	}else if(!coor.compare("n255")){
		return N255;
	}else if(!coor.compare("n240")){
		return N240;
	}else if(!coor.compare("n248")){
		return N248;
	}else if(!coor.compare("n243")){
		return N243;
	}else if(!coor.compare("n244")){
		return N244;
	}else if(!coor.compare("n242")){
		return N242;
	}else if(!coor.compare("n241")){
		return N241;
	}else if(!coor.compare("n230")){
		return N230;
	}else if(!coor.compare("n234")){
		return N234;
	}else if(!coor.compare("n235")){
		return N235;
	}else if(!coor.compare("n239")){
		return N239;
	}else if(!coor.compare("n233")){
		return N233;
	}else if(!coor.compare("n232")){
		return N232;
	}else if(!coor.compare("n237")){
		return N237;
	}else if(!coor.compare("n238")){
		return N238;
	}else if(!coor.compare("n201")){
		return N201;
	}else if(!coor.compare("n202")){
		return N202;
	}else if(!coor.compare("n203")){
		return N203;
	}else if(!coor.compare("n204")){
		return N204;
	}else if(!coor.compare("n205")){
		return N205;
	}else if(!coor.compare("n206")){
		return N206;
	}else if(!coor.compare("n207")){
		return N207;
	}else if(!coor.compare("n208")){
		return N208;
	}else if(!coor.compare("n212")){
		return N212;
	}else if(!coor.compare("n213")){
		return N213;
	}else if(!coor.compare("n214")){
		return N214;
	}else if(!coor.compare("n215")){
		return N215;
	}else if(!coor.compare("n216")){
		return N216;
	}else if(!coor.compare("n218")){
		return N218;
	}else if(!coor.compare("n219")){
		return N219;
	}else if(!coor.compare("n220")){
		return N220;
	}else if(!coor.compare("n221")){
		return N221;
	}else if(!coor.compare("n225")){
		return N225;
	}else if(!coor.compare("n226")){
		return N226;
	}else if(!coor.compare("n229")){
		return N229;
	}
}

void addData(Data_t *data,Direction direct,double step){
	Route route;
	route.way=direct;
	route.step=step;
	addData(data,route);
}

void addData(Data_t *data,Route route){
	data->route[data->size]=route;
	data->size++;
}

void addData(Data_t *data,const Data_t *next){
	for(int i=0;i<next->size;++i){
		data->route[data->size]=next->route[i];
		data->size++;
	}
}

Data_t findRouteControl(Coordinate& current,Coordinate& next){
	Data_t data;

	if(current.kat!=next.kat){
		Data_t nextData;
		if(current.kat==0){
			nextData=findRoute(current,BASLANGIC0);
		}else if(current.kat==1){
			nextData=findRoute(current,BASLANGIC1);
		}else{
			nextData=findRoute(current,BASLANGIC2);
		}

		Route route;
		
		route.way=KATDEGISTIR;
		route.step=next.kat;

		addData(&nextData,route);
		if(next.kat==0){
			current=BASLANGIC0;
		}else if(next.kat==1)
			current=BASLANGIC1;
		else
			current=BASLANGIC2;

		return nextData;
	}else{
		data=findRoute(current,next);
		current=next;
		return data;
	}
}

Data_t findRoute(Coordinate current,Coordinate next)
{
	Data_t data;
	data.size=0;
	Route route;
	double distance;

	
	if(current.x == next.x && current.y==next.y && current.kat==next.kat && current.yon==next.yon){
		return data;
	}
	while(true){
		
		if(current.x==next.x && current.y==next.y && next.kat==current.kat && next.yon!=current.yon){
			route=findDirection(current.yon,next.yon);
			if(route.way!=EMPTY)
				addData(&data,route);
			current.yon=next.yon;
			break;
		}

		if(next.y==NORTH_LIMIT && next.x!=NORTH_LIMIT && current.y==NORTH_LIMIT){
			if(next.x > current.x){
				route=findDirection(current.yon,WEST);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=WEST;
			}else if(next.x < current.x){
				route=findDirection(current.yon,EAST);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=EAST;
			}
			distance=abs(current.x - next.x);
			if(distance>0)
				addData(&data,FORWARD,distance);
			current.x=next.x;
		}

		if(current.y==EXCEPTION_CLASS_K1_WESTY){
			route=findDirection(current.yon,SOUTH);
			if(route.way!=EMPTY)
				addData(&data,route);
			current.yon=SOUTH;
			distance=BASLANGIC1.y-current.y;
			current.y=BASLANGIC1.y;
			addData(&data,FORWARD,distance);
		}

		
		/* Eger giristeki yolda ise*/
		if(current.y==NORTH_LIMIT){
			/*Gidecegi sinif guney kisimdaki siniflardan ise*/
			if(next.yon==SOUTH){
				double west_distance=abs(WEST_NORTH_LIMIT - current.x) + SOUTH_LIMIT + abs(WEST_NORTH_LIMIT - next.x);
				double east_distance=abs(EAST_NORTH_LIMIT - current.x) + SOUTH_LIMIT + abs(EAST_NORTH_LIMIT - next.x);

				/*Mesafesi kisa olan yolu secer*/
				if(west_distance<=east_distance){
					
					if(current.x!=WEST_NORTH_LIMIT){
						
						route=findDirection(current.yon,WEST);
						if(route.way!=EMPTY)
							addData(&data,route);
						distance=abs(current.x - WEST_NORTH_LIMIT);
						
						current.x=WEST_NORTH_LIMIT;
						if(distance>0)
							addData(&data,FORWARD,distance);
					}

					
				}else{
					if(current.x!=EAST_NORTH_LIMIT){
						
						route=findDirection(current.yon,EAST);
						if(route.way!=EMPTY)
							addData(&data,route);
						current.yon=EAST;
						distance=abs(current.x - EAST_NORTH_LIMIT);
						current.x=EAST_NORTH_LIMIT;
						addData(&data,FORWARD,distance);
					}
						
				}
				route=findDirection(current.yon,SOUTH);
				current.yon=SOUTH;
				if(route.way!=EMPTY)
					addData(&data,route);
				current.y=SOUTH_LIMIT;
				addData(&data,FORWARD,SOUTH_LIMIT);
			
			}else if(next.yon==WEST){
				if(next.x==0.0){
					if(current.x < 0){
						route=findDirection(current.yon,WEST);
						current.yon=WEST;
					}else if(current.x > 0){
						route=findDirection(current.yon,EAST);
						current.yon=EAST;
					}
					
					if(route.way!=EMPTY)
						addData(&data,route);
					distance=abs(0.0 - current.x);
					
					current.x=0.0;
					addData(&data,FORWARD,distance);

					route=findDirection(current.yon,next.yon);
						current.yon=next.yon;

					if(route.way!=EMPTY)
						addData(&data,route);
					break;
				}

				if(current.x!=WEST_NORTH_LIMIT){
					route=findDirection(current.yon,WEST);
					if(route.way!=EMPTY)
						addData(&data,route);
					distance=abs(WEST_NORTH_LIMIT - current.x);
					//cout<<distance<<" metre ilerle"<<endl;
					current.yon=WEST;
					current.x=WEST_NORTH_LIMIT;
					addData(&data,FORWARD,distance);
				}
				 
				route=findDirection(current.yon,SOUTH);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=SOUTH;
				distance=abs(next.y-current.y);
				current.y=next.y;
				addData(&data,FORWARD,distance);
				if(next.y==EXCEPTION_CLASS_Y){
					route=findDirection(current.yon,WEST);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=WEST;
					distance=abs(current.x-next.x);

					addData(&data,FORWARD,distance);
				}
				
				current.x=next.x;
				route=findDirection(current.yon,next.yon);
				current.yon=next.yon;
				if(route.way!=EMPTY)
					addData(&data,route);
				break;
			}else if(next.yon==EAST){
				if(current.x!=EAST_NORTH_LIMIT){
					route=findDirection(current.yon,EAST);
					if(route.way!=EMPTY)
						addData(&data,route);
					distance=abs(EAST_NORTH_LIMIT - current.x);
					//cout<<distance<<" metre ilerle"<<endl;
					current.yon=EAST;
					current.x=EAST_NORTH_LIMIT;
					addData(&data,FORWARD,distance);
				}
				route=findDirection(current.yon,SOUTH);
				current.yon=SOUTH;
				if(route.way!=EMPTY)
					addData(&data,route);
				distance=abs(next.y-current.y);

				current.y=next.y;
				addData(&data,FORWARD,distance);
				if(next.y==EXCEPTION_CLASS_Y){
					route=findDirection(current.yon,EAST);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=EAST;
					distance=abs(current.x-next.x);

					addData(&data,FORWARD,distance);
				}
				
				current.x=next.x;
				route=findDirection(current.yon,next.yon);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=next.yon;
				break;
			}
		}
		if(current.y==SOUTH_LIMIT){
			if(next.y==NORTH_LIMIT){
				double distance1=abs(current.x - WEST_NORTH_LIMIT);
				double distance2=abs(current.x - EAST_NORTH_LIMIT);

				if(distance1>=distance2){
					route=findDirection(current.yon,EAST);
					current.yon=EAST;
					if(route.way!=EMPTY)
						addData(&data,route);

					if(distance2!=0)
						addData(&data,FORWARD,distance2);
					current.x=EAST_NORTH_LIMIT;
				}else{
					route=findDirection(current.yon,WEST);
					current.yon=WEST;
					if(route.way!=EMPTY)
						addData(&data,route);
					if(distance1!=0)
						addData(&data,FORWARD,distance1);
					
					current.x=WEST_NORTH_LIMIT;
				}
				route=findDirection(current.yon,NORTH);
				current.yon=NORTH;
				if(route.way!=EMPTY)
					addData(&data,route);
				addData(&data,FORWARD,SOUTH_LIMIT);
				current.y=NORTH_LIMIT;
				

				
			}else{
				if(next.y==SOUTH_LIMIT){
					distance=current.x-next.x;

					if(distance>0.0){
						route=findDirection(current.yon,EAST);
						current.yon=EAST;
					}else if(distance<0.0){
						route=findDirection(current.yon,WEST);
						current.yon=WEST;
					}else{
						route=findDirection(current.yon,next.yon);
						if(route.way!=EMPTY)
							addData(&data,route);
						break;
					}
					if(route.way!=EMPTY)
						addData(&data,route);

					current.x=next.x;
					addData(&data,FORWARD,abs(distance));
					route=findDirection(current.yon,next.yon);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=next.yon;
					break;
				}else if(next.yon==WEST){
				
					if(next.x!=current.x){
					
						if(next.x<current.x){
							route=findDirection(current.yon,EAST);
							current.yon=EAST;
						}else{
							route=findDirection(current.yon,WEST);
							current.yon=WEST;
						}
						if(route.way!=EMPTY)
							addData(&data,route);
						distance=abs(next.x-current.x);

						current.x=next.x;
						addData(&data,FORWARD,distance);
					}
					route=findDirection(current.yon,NORTH);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=NORTH;
					distance=abs(next.y-current.y);

					current.y=next.y;
					addData(&data,FORWARD,distance);
					route=findDirection(current.yon,WEST);
					if(route.way!=EMPTY)
						addData(&data,route);
					break;
			
				}else if(next.yon==EAST){
				
					if(next.x!=current.x){
						if(next.x>current.x){
							route=findDirection(current.yon,WEST);
							current.yon=WEST;
						}else{
							route=findDirection(current.yon,EAST);
							current.yon=EAST;
						}
						if(route.way!=EMPTY)
							addData(&data,route);

						distance=abs(next.x-current.x);
						if(distance>0)
							addData(&data,FORWARD,distance);

						current.x=next.x;
					}
					route=findDirection(current.yon,NORTH);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=NORTH;
					distance=abs(next.y-current.y);

					current.y=next.y;
					addData(&data,FORWARD,distance);
					route=findDirection(current.yon,EAST);
					if(route.way!=EMPTY)
						addData(&data,route);
					break;
			
				}
			}
		}
		if(current.x==EXCEPTION_CLASS_EAST_X || current.x==EXCEPTION_CLASS_WEST_X){
			
			if(next.yon==SOUTH){
				route=findDirection(current.yon,SOUTH);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=SOUTH;
				distance=abs(SOUTH_LIMIT-current.y);

				current.y=SOUTH_LIMIT;
				addData(&data,FORWARD,distance);
			}else if(current.yon==EAST){
				route=findDirection(current.yon,WEST);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=WEST;

				distance=abs(EAST_NORTH_LIMIT-EXCEPTION_CLASS_EAST_X);

				current.x=EAST_NORTH_LIMIT;
				addData(&data,FORWARD,distance);

				route=findDirection(current.yon,EAST);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=EAST;
			}else if(current.yon==WEST){
				distance=abs(WEST_NORTH_LIMIT-EXCEPTION_CLASS_WEST_X);

				current.x=WEST_NORTH_LIMIT;
				addData(&data,BACK,distance);
			}	
		}
		
		if(current.y!=SOUTH_LIMIT && current.y!=NORTH_LIMIT ){
			
			if(current.yon==next.yon){
				distance=next.y-current.y;
				if(distance>0){
					route=findDirection(current.yon,SOUTH);
					current.yon=SOUTH;
				}else{
					route=findDirection(current.yon,NORTH);
					current.yon=NORTH;
				}
				if(route.way!=EMPTY)
					addData(&data,route);


				current.y=next.y;
				addData(&data,FORWARD,abs(distance));

			}else{
				if(next.x==0.0 && next.y==0.0){
					route=findDirection(current.yon,NORTH);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=NORTH;
					distance=abs(current.y - NORTH_LIMIT );
					if(distance > 0)
						addData(&data,FORWARD,distance);
					current.y=NORTH_LIMIT;

					if(current.x<0){
						route=findDirection(current.yon,WEST);
						if(route.way!=EMPTY)
							addData(&data,route);
						current.yon=WEST;
					}else{
						route=findDirection(current.yon,EAST);
						if(route.way!=EMPTY)
							addData(&data,route);
						current.yon=EAST;
					}

					distance=abs(current.x - NORTH_LIMIT );
					if(distance > 0)
						addData(&data,FORWARD,distance);
					current.x=NORTH_LIMIT;

					break;
				}
				if(next.yon==SOUTH){
					route=findDirection(current.yon,SOUTH);
					current.yon=SOUTH;
					if(route.way!=EMPTY)
						addData(&data,route);
					distance=abs(SOUTH_LIMIT-current.y);

					current.y=SOUTH_LIMIT;
					addData(&data,FORWARD,distance);
				}else{

					double north_distance=abs(NORTH_LIMIT-current.y);
					double south_distance=abs(SOUTH_LIMIT-current.y);
					
					if(north_distance<=south_distance){
						route=findDirection(current.yon,NORTH);
						current.yon=NORTH;
						if(route.way!=EMPTY)
							addData(&data,route);

						current.y=NORTH_LIMIT;
						addData(&data,FORWARD,abs(north_distance));
					}else{
						route=findDirection(current.yon,SOUTH);
						current.yon=SOUTH;
						if(route.way!=EMPTY)
							addData(&data,route);

						current.y=SOUTH_LIMIT;
						addData(&data,FORWARD,abs(south_distance));
					}
				}
			}
		}
		
	}

	kat_three_kontrol(&data,next);
	return data;

}

bool operator==(Coordinate& right,Coordinate& left){

	if(right.x == left.x && right.y==left.y && right.kat==left.kat && right.kapiYon ==left.kapiYon && right.yon==left.yon)
		return true;
	return false;
}

void kat_three_kontrol(Data_t* data,Coordinate current){
	
	if(current.kapiYon==1){
		Route route={LEFT,90};
		data->route[data->size-1]=route;
	}else if(current.kapiYon==-1){
		Route route={RIGHT,90};
		data->route[data->size-1]=route;
	}
}

Route findDirection(YON current,YON next){

	int difference=current-next;
	Route route;
	route.way=EMPTY;

	if(abs(difference)==1){

		route.way=RIGHT;
		route.step=180;
	}else{
		if(difference==-3 || difference==4 || difference==2){
			route.way=RIGHT;
			route.step=90;
		}else if(difference==3 || difference==-2 || difference==-4){
			route.way=LEFT;
			route.step=90;
		}
		
	}
	return route;
}