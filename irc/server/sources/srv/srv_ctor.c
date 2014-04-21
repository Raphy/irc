/*
** srv_ctor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 18 22:52:32 2014 raphael defreitas
** Last update Mon Apr 21 01:12:53 2014 raphael defreitas
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/select.h>
#include	<time.h>
#include	<unistd.h>

#include	"channel.h"
#include	"client.h"
#include	"cmd.h"
#include	"defs.h"
#include	"socket.h"
#include	"srv.h"

static int	init_socket(t_socket *sock, int port)
{
  if (socket_ctor(sock, AF_INET, SOCK_STREAM, 0) == RET_FAILURE)
    {
      perror("error: socket creation");
      return (RET_FAILURE);
    }
  if (socket_bind(sock, INADDR_ANY, port))
    {
      perror("error: socket bind");
      return (RET_FAILURE);
    }
  if (socket_listen(sock, 42) == RET_FAILURE)
    {
      perror("error: socket listen");
      return (RET_FAILURE);
    }
  return (RET_SUCCESS);
}

static void	init_cmd_handlers(t_srv *this)
{
  int		c;

  c = 0;
  this->cmd_handlers[c++] = cmd_new(this, &cmd_nick);
  this->cmd_handlers[c++] = cmd_new(this, &cmd_user);
  this->cmd_handlers[c++] = cmd_new(this, &cmd_ping);
  this->cmd_handlers[c++] = cmd_new(this, &cmd_pong);
  this->cmd_handlers[c++] = cmd_new(this, &cmd_join);
  this->cmd_handlers[c++] = cmd_new(this, &cmd_privmsg);
  this->cmd_handlers[c] = NULL;
}

int		srv_ctor(t_srv *this, int port)
{
  time_t	now;

  strcpy(this->hostname, "Unknown");
  now = time(NULL);
  strftime (this->created, 128, "%a %b %d %Y at %H:%M:%S %Z", localtime(&now));
  init_cmd_handlers(this);
  if (init_socket(&this->socket, port) == RET_FAILURE ||
      gethostname(this->hostname, 1024) == -1)
    {
      socket_dtor(&this->socket);
      return (RET_FAILURE);
    }
  list_ctor(&this->clients, &client_delete);
  list_ctor(&this->channels, &channel_delete);
  FD_ZERO(&this->read_fds);
  FD_ZERO(&this->write_fds);
  return (RET_SUCCESS);
}
