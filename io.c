/*
 io.c
 @author justin zeng (whackatre)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "io.h"

void send_message(char* format, ...)
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
	send_message("USER %s * * :%s", usr, usr);
}

void send_nick(char* nick)
{
	send_message("NICK %s", nick);
}
