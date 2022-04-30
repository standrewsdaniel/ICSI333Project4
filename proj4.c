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
#include<sys/dir.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>


#define PORT_NUM 8000
#define SA struct sockaddr

int fd;

int main(int argc, char* argv[]) {

	char* message1 = "HTTP/1.0";
	char* message2 = "Content-Length:";
	char* requestMgs = "GET";
	int contLen = 0;
	int success = 200;
	int noFile = 404;
	char* buf[BUFSIZ];

	if (argc <= 1) {
		printf("Not enough arguments! Exiting...\n");
		fflush(stdout);
		exit(1);
	}
	else {
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			printf("%s", argv[1]);
			printf("Error opening file! Exiting...");
			fflush(stdout);
			exit(1);
		}
		else{
			read(fd, buf, BUFSIZ);
			//This is where instead of writing to screen it can
			// be stored and then sent to the server / client.
			write(STDOUT_FILENO, buf, BUFSIZ);
		}

	}




}