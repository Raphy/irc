/*
** srv_log.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 16:44:04 2014 raphael defreitas
** Last update Mon Apr 21 05:16:44 2014 raphael defreitas
*/

#include	<stdarg.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#include	"client.h"
#include	"socket.h"

void		srv_log(t_client *client, char *format, ...)
{
  time_t	now;
  char		date[25];
  va_list	ap;

  now = time(NULL);
  strftime (date, 25, "%d/%m/%Y %H:%M:%S", localtime(&now));
  printf("%s - ", date);
  if (client)
    printf("%s - %d - %s > ", socket_ip(client_socket(client)),
	   socket_fd(client_socket(client)), client->name);
  else
    printf("SERVER > ");
  va_start(ap, format);
  vprintf(format, ap);
  va_end(ap);
  printf("\n");
}
