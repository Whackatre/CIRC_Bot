/*
 ircbot.h
 @author justin zeng (whackatre)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define BUFF_SIZE 512

/*
 the write buffer.
 */
char wbuffer[BUFF_SIZE];

/*
 the read buffer.
 */
char rbuffer[BUFF_SIZE];

/*
 the socket.
 */
int sockfd;

/*
 flushes the write buffer,
 sending it to the irc server.
 */
void sM(char* format, ...);
