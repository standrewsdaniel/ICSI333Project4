/*

~~~~~~~~~~~~~~~~~~~~~~~~Project 4 Group Source Code File~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ICSI 333 Spring 2022 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Authors:
	Daniel Najafi
	Daniel St Andrews
	Andrew Carv

Purpose:
	Use C language to write a simple web server using information about networking,
threading, and file system calls.

Changelog:
-Created 4/23/22

Methods:



*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#define PORT_NUM 18000
#define SA struct sockaddr
#define MAXLINE 100

int fd;

int main(int argc, char* argv[]) {

	//Variables used for printing messages to screen in regards to
	//	program status.
	char* message1 = "HTTP/1.0";
	char* message2 = "Content-Length:";
	char* requestMgs = "GET";
	int contLen = 0;
	int success = 200;
	int noFile = 404;
	char* buffer[BUFSIZ];

	//Server variables for sockets
	int listenfd, connfd, n;
	struct sockaddr_in servaddr;
	uint8_t buf[MAXLINE+1];
	uint8_t recvline[MAXLINE+1];

/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|                                     |
|			Check File Input          |
|                                     |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
	//Verify there are enough arguments
	if (argc <= 1) {
		printf("Not enough arguments! Exiting...\n");
		fflush(stdout);
		exit(1);
	}
	else {
		//Has enough arguments, open file for reading.
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			printf("%s", argv[1]);
			printf("404 File Not Found.");
			fflush(stdout);
			exit(1);
		}
		else {


/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|                                     |
|			Socket / Server           |
|                                     |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

			//Creat the socket
			if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
				printf("Error creating the socket!");
				fflush(stdout);
				exit(1);
			}

			bzero(&servaddr, sizeof(servaddr));

			//Sets the family of the socket to internet
			servaddr.sin_family = AF_INET;

			//Sets it so that socket will accept any connection
			servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

			//This indicates port the server is going to run on
			servaddr.sin_port = htons(PORT_NUM);

			//Bind the socket for listening so it can accept info
			if((bind(listenfd, (SA*)&servaddr, sizeof(servaddr))) < 0){
				printf("Binding to socket error! Exiting...");
				fflush(stdout);
				exit(1);
			}

			if((listen(listenfd, 10)) < 0){
				printf("Listening error");
				exit(1);
			}

			for( ; ;){

				struct sockaddr_in addr;
				socklen_t addr_len;

				printf("Waiting for a connection on port %d\n", PORT_NUM);
				fflush(stdout);

				connfd = accept(listenfd, (SA*)NULL, NULL);

				memset(recvline, 0, MAXLINE);

				while((n = read(connfd, recvline, MAXLINE-1)) > 0){
					
					printf("%s", recvline);

					if(recvline[n-1] == '\n'){
						break;
					}
				}
				memset(recvline, 0, MAXLINE);

				if(n < 0){
					printf("Error reading, Negative bytes error!");
					exit(1);
				}

				snprintf((char*)buf, sizeof(buf), "HTTP/1.1 200 OK\r\n\r\nFILE CONTENTS");

				write(connfd, (char*)buf, strlen((char*)buf));
				close(connfd);


			}


			printf("Hit else path for successful file open");
			//File opened successfully, read into buffer and store or print.
			read(fd, buffer, BUFSIZ);
			//This is where instead of writing to screen it can
			// be stored and then sent to the server / client.
			//write(STDOUT_FILENO, buf, BUFSIZ);











		}

	}

}