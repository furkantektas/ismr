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
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>

/*
 * error - wrapper for perror
 */
void error(char *msg) {
	perror(msg);
	/*pthread_exit(0);*/
}

int isValidPort(int port) {
    return (port > 1024 ) && (port < 65535);
}

int isValidIpAddress(char *ipAddress) {
    struct sockaddr_in sa;
    return (inet_pton(AF_INET, ipAddress, &(sa.sin_addr)) != 0);
}

void usage(void) {
	printf("Invalid arguments\nUsage: ./sendip CLIENTIPADDR PORTNO\n");
}

int isValidArguments(int argc, char** argv) {
	return (argc == 3 && isValidIpAddress(argv[1]) &&  isValidPort(atoi(argv[2])));
}

int main(int argc, char** argv) {
	int sockfd,n;
	struct sockaddr_in serveraddr;
	struct hostent *server;
	char errBuf[LINE_MAX];
	char msg[BUFSIZ];
	struct ifreq ifr;

	if(!isValidArguments(argc,argv)) {
		usage();
		return -1;
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	/* I want to get an IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;

	/* I want IP address attached to "wlan0" */
	strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);

	ioctl(sockfd, SIOCGIFADDR, &ifr);
	close(sockfd);

	/* Copying IP address */
	strcpy(msg,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	
	/* socket: create the socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	
	/* gethostbyname: get the server's DNS entry */
	server = gethostbyname(argv[1]);
	if (server == NULL ) {
		memset(errBuf,0,LINE_MAX);
		sprintf(errBuf,"ERROR, no such host as %s\n", argv[1]);
		error(errBuf);
	}

	/* build the server's Internet address */
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	memcpy(&serveraddr.sin_addr.s_addr,server->h_addr, server->h_length);
	serveraddr.sin_port = htons(atoi(argv[2]));

	/* connect: create a connection with the server */
	if (connect(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
		/*error("ERROR connecting");*/
		return  -1;
	}

	n = write(sockfd, msg, BUFSIZ);
		/* TODO: 0 RETURN ET */
	if (n < 0)
		error("ERROR writing to socket");
	return 1;
	close(sockfd);

	return 0;

}
