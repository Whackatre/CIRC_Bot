/*
 io.h
 @author justin zeng (whackatre)
 */

#include <stdlib.h>
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
void send_message(char* format, ...);

/*
 sends the username to the server.
 */
void send_user(char* usr);

/*
 sends the desired nickname to the server.
 */
void send_nick(char* nick);
