/*
** cmd_part.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Sun Apr 27 21:57:19 2014 raphael defreitas
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

static void	warn(t_client *client, t_channel *channel, const char *reason)
{
  t_client	*to;
  t_iterator	iterator;

  iterator_ctor(&iterator, &channel->clients, IT_DATA);
  while ((to = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      client_out(to, ":%s!%s@%s PART %s :%s\r\n", client->nickname,
		 client->name, client->server, channel->name,
		 reason ? reason : "Leaving");
    }
}

t_bool		cmd_part(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;
  t_channel	*channel;

  if (strcmp(tokens[0], "PART") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (tokens[1])
    if ((channel = list_find(&client->channels, &channel_find_by_name,
			     tokens[1], IT_DATA)))
      warn(client, channel, tokens[2]);
  return (TRUE);
}
