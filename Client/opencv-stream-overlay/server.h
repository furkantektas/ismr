#ifndef SERVER_H_
#define SERVER_H_

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


#define LOCALHOST "127.0.0.1"
#define PORTNO 7578
		
/*
 * error - wrapper for perror
 */
void error(const char *msg);
		
void getData(int sockfd , void* data);

void* task(const char ip[], int port, void *(*fnCallBack)(void *));
		
#endif