#include "RouteHandler.h"
#include "Route.h"
#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

void getData(int sockfd , void* data);
void task();

int main(){
	task();
	return 0;
}

void getData(int sockfd , void* data) {
	if ( (read(sockfd,data,sizeof(Data_t) ) < 0 ) )
		cout<<"ERROR reading from socket"<<endl;
}

void task( )
{
	int sockfd, newsockfd, portno = atoi( "4546" ), clilen;
	struct sockaddr_in serv_addr, cli_addr;
	Data_t data;
	int i;

	bzero((char *) &data, sizeof(Data_t));


	cout<< "using port #" << portno <<endl;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		cout<<"ERROR opening socket";
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons( portno );
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		cout<<"ERROR on binding"<<endl;
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	//--- infinite wait on a connection ---
	while ( 1 ) {
		cout<<"waiting for new client...\n";
		if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
			cout<<"ERROR on accept";

		cout<<"opened new communication with client\n" ;

		// waiting for the route
		getData( newsockfd ,&data);
		for(int i=0;i<data.size;++i){
			Route route=data.route[i];
			
			switch(route.way){
				case FORWARD:
				cout<<route.step<<" meter(s) forward"<<endl;
				break;

				case BACK:
				cout<<route.step<<" meter(s) back"<<endl;
				break;


				case RIGHT:
				cout<<route.step<<" meter(s) rigth"<<endl;
				break;


				case LEFT:
				cout<<route.step<<" meter(s) left"<<endl;
				break;
			}
		}
		PWM pwm;
		RouteHandler handler(&pwm);
		handler.handler(data);
		close( newsockfd );
	}
	close(sockfd);
}
