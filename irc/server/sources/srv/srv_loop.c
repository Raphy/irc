/*
** srv_loop.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sat Apr 19 01:05:18 2014 raphael defreitas
** Last update Sun Apr 27 18:08:51 2014 Barthelemy Delemotte
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/select.h>
#include	<sys/time.h>

#include	"channel.h"
#include	"client.h"
#include	"defs.h"
#include	"list.h"
#include	"socket.h"
#include	"srv.h"

static void	set_fds(t_srv *this)
{
  t_iterator	iterator;
  t_client	*client;

  FD_ZERO(&this->read_fds);
  FD_ZERO(&this->write_fds);
  this->nfds = socket_fd(&this->socket);
  FD_SET(socket_fd(&this->socket), &this->read_fds);
  iterator_ctor(&iterator, &this->clients, IT_DATA);
  while ((client = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      FD_SET(socket_fd(client_socket(client)), &this->read_fds);
      if (client->has_data_out)
	{
	  FD_SET(socket_fd(client_socket(client)), &this->write_fds);
	}
    }
}

static void	select_treat_clients(t_srv *this)
{
  t_iterator	iterator;
  t_item	*item;
  t_client	*client;

  iterator_ctor(&iterator, &this->clients, IT_ITEM);
  while ((item = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      if ((client = (t_client *)item_data(item)))
	{
	  if (FD_ISSET(socket_fd(client_socket(client)), &this->write_fds))
	    client_out_handle(client);
	  if (FD_ISSET(socket_fd(client_socket(client)), &this->read_fds))
	    {
	      client_in_handle(client);
	      srv_treat_client(this, item, client);
	    }
	}
    }
}

static void	select_new_client(t_srv *this)
{
  t_socket	*client_socket;
  t_client	*client;

  if (FD_ISSET(socket_fd(&this->socket), &this->read_fds))
    {
      if ((client_socket = socket_accept(&this->socket)))
	{
	  if ((client = client_new(client_socket)))
	    {
	      srv_log(client, "Connected");
	      list_enqueue(&this->clients, client);
	      this->nfds = MAX(this->nfds, socket_fd(client_socket));
	      FD_SET(socket_fd(client_socket), &this->read_fds);
	    }
	  else
	    socket_delete(client_socket);
	}
    }
}

static void		disp_info(t_srv *this)
{
  t_iterator		iterator;
  t_client		*client;
  t_channel		*channel;

  printf("#################### SERVER INFORMATION ####################\n");
  printf("#%lu clients: ", list_length(&this->clients));
  iterator_ctor(&iterator, &this->clients, IT_DATA);
  while ((client = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      printf("[%s!%s@%s] ", client->nickname, client->name, client->server);
    }
  printf("\n#%lu channels: ", list_length(&this->channels));
  iterator_ctor(&iterator, &this->channels, IT_DATA);
  while ((channel = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      printf("[%s|%lu users] ", channel->name, list_length(&channel->clients));
    }
  printf("\n############################################################\n");
}

void			srv_loop(t_srv *this)
{
  struct timeval	tv;
  int			ret;

  tv.tv_sec = this->timeout;
  tv.tv_usec = 0;
  printf("+--------------------------------------------------------------+\n");
  printf("|                       RAPHY IRC SERVER                       |\n");
  printf("+--------------------------------------------------------------+\n");
  printf("Hostname: %s\tTimeout: %d\n", this->hostname, this->timeout);
  set_fds(this);
  while ((ret = select(FD_SETSIZE, &this->read_fds,
		       &this->write_fds, NULL, &tv)) >= 0)
    {
      if (ret == 0)
	{
	  srv_ping_pong(this);
	  tv.tv_sec = this->timeout;
	  tv.tv_usec = 0;
	  disp_info(this);
	}
      select_treat_clients(this);
      select_new_client(this);
      set_fds(this);
    }
}
