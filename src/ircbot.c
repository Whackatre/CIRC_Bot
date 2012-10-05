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

#include "io.h"
#include "utils.h"

#define HOST_NAME "irc.gyrat.in"
#define PORT "6667"
#define CHANNEL "#skyrealm"
#define USER "circbot"
#define NICK "`circ_"

#define WHAC ":whac!whac@skyrealm.net"

/*
 the main entry point.
 */
int main(int argc, char* argv[])
{
	struct hostent* server;
	struct addrinfo hints, *res;
	char** args;
	size_t count = 0;
	int recv_sts;
	int str_it;

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
	send_user(USER);
	send_nick(NICK);
	printf("Sent USER and NICK details..\n");

	/*
	 the main loop.
	 */
	while (recv_sts = recv(sockfd, rbuffer, sizeof(rbuffer), 0))
	{
		int i, j = 0;
		if (recv_sts < 1)
			break;
		printf("%s", rbuffer);

		char channel[64];
		char user[64];
		strcpy(user, "");
		strcpy(channel, "");

		args = str_split(rbuffer, " ", &count);
		/*
		for (i = 0; i < count; i++)
		{
			printf("[%d]: %s\n", i, args[i]);
		}
		*/

		strcpy(user, args[0]);
		strcpy(channel, args[2]);

		/*
		 testing.
		 */
		if (!starts_with(channel, "#"))
		{
			strcpy(channel, "NOT_A_CHAN");
		}

		/*
		 command handling here, etc.
		 */
		if (strstr(rbuffer, "001"))
		{
			// raw_message("JOIN %s", CHANNEL);
			join_chan(CHANNEL);
			join_chan("#helix"); // testing
			memset(wbuffer, 0, BUFF_SIZE);
		}
		if (strstr(rbuffer, "PING"))
		{
			char* tok = strtok(rbuffer, "PING ");
			raw_message("PONG %s", tok);
			memset(wbuffer, 0, BUFF_SIZE);
		}
		if (strstr(rbuffer, "rofl"))
		{
			raw_message("PRIVMSG " CHANNEL " :what's so funny?");
			memset(wbuffer, 0, BUFF_SIZE);
		}
		if (strstr(rbuffer, "-rand"))
		{
			int gen = rand_int(0, 100);
			raw_message("PRIVMSG " CHANNEL " :%d", gen);
			memset(wbuffer, 0, BUFF_SIZE);
		}
		if (strstr(rbuffer, "-genstr"))
		{
			char* gen = rand_str(8);
			raw_message("PRIVMSG " CHANNEL " :%s", gen);
			memset(wbuffer, 0, BUFF_SIZE);
			free(gen);
		}
		if (strstr(rbuffer, "-chan"))
		{
			char* chname = join("PRIVMSG ", channel);
			chname = join(chname, " :I am talking to ");
			chname = join(chname, channel);
			raw_message(chname);
			memset(wbuffer, 0, BUFF_SIZE);
			free(chname);
		}
		if (strstr(rbuffer, "-quit") && strstr(user, WHAC))
		{
			raw_message("PRIVMSG " CHANNEL " :bye guys. :(");
			memset(wbuffer, 0, BUFF_SIZE);
			break;
		}
		/*
		 "cleans" the read buffer.
		 */
		memset(rbuffer, 0, BUFF_SIZE);
		for (str_it = 0; str_it < count; str_it++)
		{
			free(args[str_it]);
		}
		free(args);
	}
	for (str_it = 0; str_it < count; str_it++)
	{
		free(args[str_it]);
	}
	free(args);
	freeaddrinfo(res);
	return EXIT_SUCCESS;
}
