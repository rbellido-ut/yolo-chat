/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		chat_client.cpp - A simple TCP chat client program.
--
--	PROGRAM:		chat_client
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:			February 2, 2008
--
--	REVISIONS:		(Date and Description)
--				January 2005
--				Modified the read loop to use fgets.
--				While loop is based on the buffer length

--				March 25, 2013
--				tcp_clnt.c is modified to work as a chat client [from milliways]
--
--
--	DESIGNERS:		Aman Abdulla
--
--	PROGRAMMERS:		Aman Abdulla
--						Ronald Bellido
--
--	NOTES:
--	The program will establish a TCP connection to a user specifed server.
-- The server can be specified using a fully qualified domain name or and
--	IP address. After the connection has been established the user will be
-- prompted for date. The date string is then sent to the server and the
-- response (echo) back from the server is displayed.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <cstdio>
#include "globals.h"

#define SERVER_TCP_PORT		7000	// Default port
#define BUFLEN			255  	// Buffer length

using namespace std;

void * handle_recv_thread(void* args);

typedef struct {
    int socket;
    bool log;
} holder, *PHOLDER;

int main (int argc, char **argv)
{
	int sd, port;
	struct hostent	*hp;
	struct sockaddr_in server;
	char  *host, sbuf[BUFLEN], **pptr;
	char str[16];
	bool log = false;
	pthread_t recv_thread_handle;

	holder *hold = (holder*) malloc(sizeof(holder));
	hold->log = false;
	hold->socket = -1;

	switch(argc)
	{
		case 2:
			host =	argv[1];	// Host name
			port =	SERVER_TCP_PORT;
		break;
		case 3:
			host =	argv[1];
			port =	atoi(argv[2]);	// User specified port
		break;
		case 4:
		    host = argv[1];
		    port = atoi(argv[2]);
		    hold->log = true; 
		break;
		default:
			cerr << "Usage: " << argv[0] << " host [port] [log]" << endl;
			exit(1);
	}

	// Create the socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Cannot create socket");
		exit(1);
	}
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL)
	{
		cerr << "Unknown server address" << endl;
		exit(1);
	}
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	// Connecting to the server
	if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		cerr << "Can't connect to server" << endl;
		perror("connect");
		exit(1);
	}
	cout << "Connected: 	Server Name: " << hp->h_name << endl;
	pptr = hp->h_addr_list;
	cout << "\t\tIP Address: " << inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)) << endl;
	
	hold->socket = sd;

	pthread_create(&recv_thread_handle, 0, handle_recv_thread, (void*) hold);

	//TODO: if received command: 'quit' or SIGINT, then break the loop
	while (1)
	{
		//Get user's message
		cout << ">> ";
		fgets (sbuf, BUFLEN, stdin);
        
		// Transmit data through the socket
		send (sd, sbuf, BUFLEN, 0);		
	}

	cout << "Disconnecting...Goodbye!" << endl;
	close (sd);
	free(hold);
	return (0);
}

/*------------------------------------------------------------------------------------------------------------------
 -- FUNCTION: handle_recv_thread
 --
 -- DATE: March 25, 2013
 --
 -- REVISIONS: March 25, 2013
 --
 -- DESIGNER: Ronald Belllido
 --
 -- PROGRAMMER: Ronald Bellido
 --
 -- INTERFACE: handle_recv_thread
 --
 -- RETURNS: void*
 --
 -- NOTES:
Thread to handle any received messages
----------------------------------------------------------------------------------------------------------------------*/
void * handle_recv_thread(void* args)
{
	//printf("Receive:\n");
    holder *h = (holder*) args;
	int bytes_to_read = BUFLEN;
	char *bp, rbuf[BUFLEN];
	bp = rbuf;
	
	FILE * logfile = fopen("log.txt", "w+");

	while (1)
	{
		//client makes repeated calls to recv until no more data is expected to arrive.
		int n = 0;
		while ((n = recv (h->socket, bp, bytes_to_read, 0)) < BUFLEN)
		{
			bp += n;
			bytes_to_read -= n;
		}
		
        if (h->log)
            fprintf(logfile, "%s",rbuf);
            
		cout << rbuf << endl;
		//fflush(stdout);
	}
	
	fclose(logfile);
}
