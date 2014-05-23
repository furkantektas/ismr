#ifndef SIMULATION_H
#define SIMULATION_H


#include <irrlicht/irrlicht.h>
#include "Route.h"
#include <irrlicht/ICursorControl.h>
#include <thread>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>



class Simulation{

	public:	

		Simulation(int argc, char* argv2[]){
			if(argc != 3){
				printf("\n/.model IP PORT\n\n");
				exit(0);
			}

			argv = argv2 ;
		}

		void initializeAndRun();

	private:
		char** argv;


};


#endif