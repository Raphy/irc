/*
** srv_treat_client.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 04:49:15 2014 raphael defreitas
** Last update Mon Apr 21 21:38:22 2014 raphael defreitas
*/

#define		_BSD_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>

#include	"channel.h"
#include	"client.h"
#include	"defs.h"
#include	"list.h"
#include	"srv.h"
#include	"utils.h"

static void	disconnect(t_client *client)
{
  t_channel	*channel;
  t_iterator	iterator;
  t_item	*item;

  iterator_ctor(&iterator, &client->channels, IT_DATA);
  while ((channel = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      if ((item = list_find(&channel->clients, &client_find_by_ptr, client,
			    IT_ITEM)))
	list_unlink(&channel->clients, item);
    }
}

void		srv_treat_client(t_srv *this, t_item *item, t_client *client)
{
  char		**commands;
  int		i;

  if (client->has_data_in)
    {
      if ((commands = strtoarr(client->buf_in, "\r\n")))
	{
	  i = 0;
	  while (commands[i])
	    srv_cmd(this, client, commands[i++]);
	  free(commands);
	}
      client->has_data_in = FALSE;
      client->buf_in[0] = 0;
    }
  if (!client->authenticated && client->name && client->nickname)
    srv_auth(this, client);
  if (client->disconnected)
    {
      srv_log(client, "Disconnected");
      disconnect(client);
      client_delete(list_unlink(&this->clients, item));
    }
}
