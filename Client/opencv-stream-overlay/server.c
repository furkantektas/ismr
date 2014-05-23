#include "server.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

void error(const char *msg ) {
	perror(  msg );
	exit(1);
}

void getData(int sockfd , void* data) {
	if ( (read(sockfd,data,sizeof(char)*BUFSIZ ) < 0 ) )
		error("ERROR reading from socket");
}

void* task(const char ip[], int port, void *(*fnCallBack)(void *))
{
	int sockfd, newsockfd, portno = PORTNO, clilen;
	struct sockaddr_in serv_addr, cli_addr;
	char data[BUFSIZ];
	int i;
	void* returnVal;
	bzero((char *) &data, sizeof(char)*BUFSIZ);


	printf( "using port #%d\n", portno );
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons( portno );
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	//rota
	//size
	 //--- infinite wait on a connection ---
	while ( 1 ) {
		printf( "waiting for new client...\n" );
		if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
			error("ERROR on accept");
		printf( "opened new communication with client\n" );
		
		 //---- wait for a number from client ---
		getData( newsockfd ,&data);
		returnVal = fnCallBack(data);
		//printf("%s",data);
		
		close( newsockfd );
	}
		
	close(sockfd);
	return returnVal;
}
