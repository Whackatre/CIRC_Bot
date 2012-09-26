/*
 ircbot.c
 @author justin zeng (whackatre)
 
 huge thanks to:
	http://3ethicalhackers.com/showthread.php?tid=1007
	https://bbs.archlinux.org/viewtopic.php?id=64254

 reference:
	http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdarg.h>
#include "ircbot.h"

#define HOST_NAME "irc.rizon.net"
#define PORT "6667"
#define CHANNEL "#skyrealm"
#define USER "wcircbot"
#define NICK "`whac_"

/*
 the main entry point.
 */
int main(int argc, char* argv[])
{
	struct hostent* server;
	struct addrinfo hints, *res;
	int recv_sts;

	printf("====================\n");
	printf("IRC Bot by Whackatre\n");
	printf("====================\n");
	printf("Host: %s\n", HOST_NAME);
	printf("Port: %s\n", PORT);
	printf("Chan: %s\n", CHANNEL);

	/*
	 sets networking details.
	 */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(HOST_NAME, PORT, &hints, &res);

	server = gethostbyname(HOST_NAME);
	if (server == NULL)
	{
		printf("Error resolving host!\n");
		return EXIT_FAILURE;
	}

	/*
	 opens the socket.
	 */
	sockfd = socket(res->ai_family, res->ai_socktype, 0);
	if (sockfd < 0)
	{
		printf("Error opening socket!\n");
		return EXIT_FAILURE;
	}

	/*
	 connects to the server.
	 */
	connect(sockfd, res->ai_addr, res->ai_addrlen);
	printf("Connected successfully!\n");

	/*
	 sends USER and NICk details.
	 */
	sM("USER %s * * :%s", USER, USER);
	sM("NICK %s", NICK);
	printf("Sent USER and NICK details..\n");

	/*
	 the main loop.
	 */
	while (recv_sts = recv(sockfd, rbuffer, sizeof(rbuffer), 0))
	{
		if (recv_sts < 1)
			break;
		printf("%s", rbuffer);

		/*
		 command handling here, etc.
		 */
		if (strstr(rbuffer, "001"))
		{
			sM("JOIN %s", CHANNEL);
			memset(wbuffer, 0, BUFF_SIZE);
		}
		if (strstr(rbuffer, "PING"))
		{
			char* tok = strtok(rbuffer, "PING ");
			sM("PONG %s", tok);
			memset(wbuffer, 0, BUFF_SIZE);
		}
		if (strstr(rbuffer, "rofl"))
		{
			sM("PRIVMSG " CHANNEL " :what's so funny?.");
			memset(wbuffer, 0, BUFF_SIZE);
		}
		if (strstr(rbuffer, "quit"))
		{
			sM("PRIVMSG " CHANNEL " :bye guys.");
			memset(wbuffer, 0, BUFF_SIZE);
			break;
		}
		/* "cleans" the read buffer. */
		memset(rbuffer, 0, BUFF_SIZE);
	}
	freeaddrinfo(res);
	return EXIT_SUCCESS;
}

/*
 sends a msg to the server.
 */
void sM(char* format, ...)
{
	/* varargs */
	va_list ap;
	va_start(ap, format);
	vsnprintf(wbuffer, BUFF_SIZE, format, ap);
	va_end(ap);

	strcat(wbuffer, "\r\n"); /* flushes the stream */
	printf("<< %s", wbuffer); /* simply prints out all output */
	write(sockfd, wbuffer, strlen(wbuffer)); /* writes the buffer */
}
