/*
 io.c
 @author justin zeng (whackatre)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "io.h"

void raw_message(char* format, ...)
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

void send_user(char* usr)
{
	raw_message("USER %s * * :%s", usr, usr);
}

void send_nick(char* nick)
{
	raw_message("NICK %s", nick);
}

void join_chan(char* chan)
{
	raw_message("JOIN %s\n", chan);
}

void set_mode(char* chan, char* mode)
{
	raw_message("MODE %s %s", chan, mode);
}

void set_mode_usr(char* chan, char* mode, char* user)
{
	raw_message("MODE %s %s %s", chan, mode, user);
}

void whois(char* nick)
{
	raw_message("WHOIS %s", nick);
}
