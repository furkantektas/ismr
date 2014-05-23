#include "Route.h"
#include <iostream>




Data_t calculateRoute(Coordinate& current,Coordinate& next){
	
	//cout<<Z23.yon<<endl<<Z23.y<<endl;
	
	Data_t data;
	data=findRouteControl(current,next);
	
	
	/*for (int i = 0; i < data.size; ++i)
	{
		Route route=data.route[i];
		cout<<route.way<<" "<<route.step<<endl;

	}*/
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
		return BASLANGIC2;
	}else if(!coor.compare("n101")){
		return N101;
	}else if(!coor.compare("n102")){
		return N102;
	}else if(!coor.compare("n109")){
		return N109;
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
			//current=BASLANGIC0;
		}else if(current.kat==1){
			nextData=findRoute(current,BASLANGIC1);
			//current=BASLANGIC1;
		}else{
			nextData=findRoute(current,BASLANGIC2);
			//current=BASLANGIC2;
		}
		/*
		if(nextData.size!=0)
			addData(&data,&nextData);
		*/
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
			//cout<<BASLANGIC1.y-current.y<<" metre ilerle"<<endl;
			current.y=BASLANGIC1.y;
			addData(&data,FORWARD,distance);
		}

		
		/*Eðer giriþteki yolda ise*/
		if(current.y==NORTH_LIMIT){
			/*Gideceði sýnýf güney kýsýmdaki sýnýflardan ise*/
			if(next.yon==SOUTH){
				double west_distance=abs(WEST_NORTH_LIMIT - current.x) + SOUTH_LIMIT + abs(WEST_NORTH_LIMIT - next.x);
				double east_distance=abs(EAST_NORTH_LIMIT - current.x) + SOUTH_LIMIT + abs(EAST_NORTH_LIMIT - next.x);

				/*Mesafesi kýsa olan yolu seçer*/
				if(west_distance<=east_distance){
					
					if(current.x!=WEST_NORTH_LIMIT){
						
						route=findDirection(current.yon,WEST);
						if(route.way!=EMPTY)
							addData(&data,route);
						distance=abs(current.x - WEST_NORTH_LIMIT);
						//cout<<distance<<" metre ilerle"<<endl;
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
						//cout<<distance<<" metre ilerle"<<endl;
						current.x=EAST_NORTH_LIMIT;
						addData(&data,FORWARD,distance);
					}
						
				}
				route=findDirection(current.yon,SOUTH);
				current.yon=SOUTH;
				if(route.way!=EMPTY)
					addData(&data,route);
				//cout<<SOUTH_LIMIT<<" metre ilerle "<<endl;
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
					//cout<<abs(0.0 - current.x)<<" metre ilerle"<<endl;
					
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
				//cout<<distance<< " metre ilerle"<<endl;
				current.y=next.y;
				addData(&data,FORWARD,distance);
				if(next.y==EXCEPTION_CLASS_Y){
					route=findDirection(current.yon,WEST);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=WEST;
					distance=abs(current.x-next.x);
					//cout<<distance<<" metre ilerle"<<endl;
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
				//cout<<distance<< " metre ilerle"<<endl;
				current.y=next.y;
				addData(&data,FORWARD,distance);
				if(next.y==EXCEPTION_CLASS_Y){
					route=findDirection(current.yon,EAST);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=EAST;
					distance=abs(current.x-next.x);
					//cout<<distance<<" metre ilerle"<<endl;
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
				
					//cout<<abs(distance)<<" metre ilerle"<<endl;
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
						//cout<<distance<<" metre ilerle"<<endl;
						current.x=next.x;
						addData(&data,FORWARD,distance);
					}
					route=findDirection(current.yon,NORTH);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=NORTH;
					distance=abs(next.y-current.y);
					//cout<<distance<<" metre ilerle"<<endl;
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
						//cout<<distance<<" metre ilerle"<<endl;
						current.x=next.x;
					}
					route=findDirection(current.yon,NORTH);
					if(route.way!=EMPTY)
						addData(&data,route);
					current.yon=NORTH;
					distance=abs(next.y-current.y);
					//cout<<distance<<" metre ilerle"<<endl;
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
				//cout<<distance<<" metre ilerle"<<endl;
				current.y=SOUTH_LIMIT;
				addData(&data,FORWARD,distance);
			}else if(current.yon==EAST){
				route=findDirection(current.yon,WEST);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=WEST;

				distance=abs(EAST_NORTH_LIMIT-EXCEPTION_CLASS_EAST_X);
				//cout<<distance<<" metre geri gel"<<endl;
				current.x=EAST_NORTH_LIMIT;
				addData(&data,FORWARD,distance);

				route=findDirection(current.yon,EAST);
				if(route.way!=EMPTY)
					addData(&data,route);
				current.yon=EAST;
			}else if(current.yon==WEST){
				distance=abs(WEST_NORTH_LIMIT-EXCEPTION_CLASS_WEST_X);
				//cout<<distance<<" metre geri gel"<<endl;
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

				//cout<<abs(distance)<<" metre ilerle"<<endl;
				current.y=next.y;
				addData(&data,FORWARD,abs(distance));


				/*
				route=findDirection(current.yon,next.yon);
				if(route.way!=EMPTY)
					addData(&data,route);

				break;
				*/
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
					//cout<<distance<<" metre ilerle"<<endl;
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
						//cout<<abs(north_distance)<<" metre ilerle"<<endl;
						current.y=NORTH_LIMIT;
						addData(&data,FORWARD,abs(north_distance));
					}else{
						route=findDirection(current.yon,SOUTH);
						current.yon=SOUTH;
						if(route.way!=EMPTY)
							addData(&data,route);
						//cout<<abs(south_distance)<<" metre ilerle"<<endl;
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
		//cout<<"180 derece donus yap"<<endl;
		route.way=RIGHT;
		route.step=180;
	}else{
		if(difference==-3 || difference==4 || difference==2){
			//cout<<"90 derece saga donus yap"<<endl;
			route.way=RIGHT;
			route.step=90;
		}else if(difference==3 || difference==-2 || difference==-4){
			//cout<<"90 derece sola donus yap"<<endl;
			route.way=LEFT;
			route.step=90;
		}
		
	}
	return route;
}
