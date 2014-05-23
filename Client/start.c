#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define STREAMPORT "8090"
#define DRIVERPORT "4546"
#define AUGMENTATIONPORT "7578"

#define STREAMURL "http://%s:%s"
#define STARTERSCRIPT "%s %s %s %s"
#define STARTERSCRIPTFILE "./starterScript.sh"


void generateStreamUrl(char* url,const char* ip) {
	sprintf(url,STREAMURL,ip,STREAMPORT);	
}

void generateStarterScript(char* cmd,const char* ip) {
	char url[BUFSIZ];
	generateStreamUrl(url,ip);	
	sprintf(cmd,STARTERSCRIPT,url,AUGMENTATIONPORT,ip,DRIVERPORT);
}

/*
 * error - wrapper for perror
 */
void error(char *msg) {
	perror(msg);
	/*pthread_exit(0);*/
}

int isValidIpAddress(char *ipAddress) {
    struct sockaddr_in sa;
    return (inet_pton(AF_INET, ipAddress, &(sa.sin_addr)) != 0);
}

int isValidPort(int port) {
    return (port > 1024 ) && (port < 65535);
}

void usage(void) {
	printf("Invalid arguments\nUsage: ./server PORTNO\n");
}

int isValidArguments(int argc, char** argv) {
	return (argc == 2 &&  isValidPort(atoi(argv[1])));
}

void runExec(const char* cmd,char* url,char* ip) {
	if(execl(cmd,cmd,url,AUGMENTATIONPORT,ip,DRIVERPORT,(char *)0) == -1)
		error("Could not execute: ");
}

void runExecutables(char* ip) {
	char url[BUFSIZ];
	printf("Opening Video Stream, that may take a while..\n");
	generateStreamUrl(url,ip);
	runExec(STARTERSCRIPTFILE,url,ip);
}

int main(int argc, char** argv) {
	int parentfd; /* parent socket */
	int childfd; /* child socket */
	int clientlen; /* byte size of client's address */
	struct sockaddr_in serveraddr; /* server's addr */
	struct sockaddr_in clientaddr; /* client addr */
	struct hostent *hostp; /* client host info */
	char buf[BUFSIZ]; /* message buffer */
	char *hostaddrp; /* dotted decimal host addr string */
	int optval; /* flag value for setsockopt */
	int n; /* message byte size */
	socklen_t sockLen;
	int usPort = atoi(argv[1]);

	strcpy(buf,"10.1.96.189");
	runExecutables(buf);
	return 0;
	/*
	 * socket: create the parent socket
	 */
	 parentfd = socket(AF_INET, SOCK_STREAM, 0);
	 if (parentfd < 0)
	 	error("ERROR opening socket");

	/* setsockopt: Handy debugging trick that lets
	 * us rerun the server immediately after we kill it;
	 * otherwise we have to wait about 20 secs.
	 * Eliminates "ERROR on binding: Address already in use" error.
	 */
	 optval = 1;
	 setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &optval,
	 	sizeof(int));

	/*
	 * build the server's Internet address
	 */
	 memset(&serveraddr, 0, sizeof(serveraddr));

	/* this is an Internet address */
	 serveraddr.sin_family = AF_INET;

	/* let the system figure out our IP address */
	 serveraddr.sin_addr.s_addr = htonl(INADDR_ANY );

	/* this is the port we will listen on */
	 if(usPort)
	 	serveraddr.sin_port = htons(usPort);
	 else
	 	serveraddr.sin_port = 0;

	/*
	 * bind: associate the parent socket with a port
	 */
	 if (bind(parentfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
	 	error("ERROR on binding");

	/* if port is not defined, get the port from socket */
	 if(!usPort) {
	 	sockLen = sizeof(serveraddr);
	 	if(getsockname(parentfd, (struct sockaddr *)&serveraddr, &sockLen) == 0 &&
	 		serveraddr.sin_family == AF_INET &&
	 		sockLen == sizeof(serveraddr)) {
	 		usPort = ntohs(serveraddr.sin_port);
	 }
	 else
	 	error("Cannot open a port");
	}

	printf("Waiting for Rover's IP. If rover is already boot up, execute `sh /home/pi/init.sh`.\n");
	/*
	 * listen: make this socket ready to accept connection requests
	 */
	if (listen(parentfd, 5) < 0) /* allow MAXCONNSIZE requests to queue up */
	 error("ERROR on listen");

	/*
	 * main loop: wait for a connection request, echo input line,
	 * then close connection.
	 */
	 clientlen = sizeof(clientaddr);
	 while (1) {

		/*
		* accept: wait for a connection request
		*/
		childfd = accept(parentfd, (struct sockaddr *) &clientaddr,
			(socklen_t *) &clientlen);
		if (childfd < 0)
			error("ERROR on accept");

		/*
		* gethostbyaddr: determine who sent the message
		*/
		hostp = gethostbyaddr((const char *) &clientaddr.sin_addr.s_addr,
			sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		if (hostp == NULL )
			error("ERROR on gethostbyaddr");

		hostaddrp = (char*) inet_ntoa(clientaddr.sin_addr);
		if (hostaddrp == NULL )
			error("ERROR on inet_ntoa\n");

		#ifndef NDEBUG
		printf("Client %s(%s) established connection to server\n",
			hostp->h_name, hostaddrp);
		#endif
		/*
		* read: read input string from the client
		*/
		memset(buf, 0, BUFSIZ);
		n = read(childfd, buf, sizeof(char)*BUFSIZ);

		if (n < 0)
			error("ERROR reading from socket");



		#ifndef NDEBUG
		printf("server received %d bytes: %s\n", n, buf);
		#endif


		close(childfd);
		if(isValidIpAddress(buf)) {
			printf("Rover's IP Address: `%s`\n",(char*)buf);
			runExecutables(buf);
			return 0;
		} else {
			printf("Invalid IP address. Please execute `sh /home/pi/init.sh` on the Rover.\n");
		}
	}
	return 0;

}