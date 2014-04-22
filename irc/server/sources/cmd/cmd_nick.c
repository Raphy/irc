/*
** cmd_nick.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 18:21:23 2014 raphael defreitas
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"channel.h"
#include	"client.h"
#include	"cmd.h"
#include	"defs.h"
#include	"list.h"
#include	"protocol.h"
#include	"srv.h"

static t_bool	nickname_used(t_srv *srv, const char *nickname)
{
  t_client	*client;
  t_iterator	iterator;

  iterator_ctor(&iterator, &srv->clients, IT_DATA);
  while ((client = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      if (client->nickname && strcmp(client->nickname, nickname) == 0)
	return (TRUE);
    }
  return (FALSE);
}

static void	warn(t_client *client, const char *nickname)
{
  t_channel	*channel;
  t_client	*dest;
  t_iterator	chan_it;
  t_iterator	client_it;

  iterator_ctor(&chan_it, &client->channels, IT_DATA);
  while ((channel = iterator_current(&chan_it)))
    {
      iterator_next(&chan_it);
      iterator_ctor(&client_it, &channel->clients, IT_DATA);
      while ((dest = iterator_current(&client_it)))
	{
	  iterator_next(&client_it);
	  client_out(dest, ":%s!%s@%s NICK :%s\r\n", client->nickname,
		     client->name, client->server, nickname);
	}
    }
}

t_bool		cmd_nick(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;

  if (strcmp(tokens[0], "NICK") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (tokens[1])
    {
      if (nickname_used(srv, tokens[1]))
	{
	  client_out(client, ":%s %d :Nickname is already in use\r\n",
		     srv->hostname, ERR_NONICKNAMEGIVEN, client->name);
	  return (TRUE);
	}
      warn(client, tokens[1]);
      if (client->nickname)
	free(client->nickname);
      client->nickname = strdup(tokens[1]);
      return (TRUE);
    }
  client_out(client, ":%s %d :No nickname given\r\n",
	     srv->hostname, ERR_NONICKNAMEGIVEN, client->name);
  return (TRUE);
}
