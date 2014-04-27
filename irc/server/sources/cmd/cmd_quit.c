/*
** cmd_nick.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 08:54:20 2014 raphael defreitas
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

static void	warn(t_client *client, const char *reason)
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
	  client_out(dest, ":%s!%s@%s QUIT :%s\r\n", client->nickname,
		     client->name, client->server, reason ? reason : "Quit");
	}
    }
}

t_bool		cmd_quit(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;

  if (strcmp(tokens[0], "QUIT") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (tokens[1])
    tokens[1]++;
  warn(client, tokens[1]);
  client->disconnected = TRUE;
  return (TRUE);
}
