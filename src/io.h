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
void raw_message(char* format, ...);

/*
 sends the username to the server.
 */
void send_user(char* usr);

/*
 sends the desired nickname to the server.
 */
void send_nick(char* nick);

/*
 joins a channel.
 */
void join_chan(char* chan);

/*
 sets a mode.
 */
void set_mode(char* chan, char* mode);

/*
 sets a mode to a user.
 */
void set_mode_usr(char* chan, char* mode, char* user);

/*
 performs a whois on a nick.
 */
void whois(char* nick);
