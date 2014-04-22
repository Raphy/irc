/*
** cmd_ping.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 21:46:12 2014 raphael defreitas
*/

#include	<string.h>

#include	"channel.h"
#include	"client.h"
#include	"cmd.h"
#include	"defs.h"
#include	"list.h"
#include	"protocol.h"
#include	"srv.h"

static t_bool	check_tokens(t_srv *srv, t_client *client, char **tokens)
{
  size_t	len;

  len = 0;
  if (!tokens[1])
    {
      client_out(client, ":%s %d * * :Not enough parameters\r\n",
		 srv->hostname, ERR_NEEDMOREPARAMS);
      return (TRUE);
    }
  if (tokens[2])
    len = strlen(tokens[2]);
  if (!tokens[2] || len <= 0)
    {
      client_out(client, ":%s %d * :No text to send\r\n",
		 srv->hostname, ERR_NOTEXTTOSEND);
      return (TRUE);
    }
  return (FALSE);
}

static void	chan_msg(t_channel *channel, t_client *client, const char *msg)
{
  t_iterator	iterator;
  t_client	*dest;

  iterator_ctor(&iterator, &channel->clients, IT_DATA);
  while ((dest = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      if (dest != client)
	client_out(dest, ":%s!%s@%s PRIVMSG %s :%s\r\n", client->nickname,
		   client->name, client->server, channel->name, msg);
    }
}

static void	user_msg(t_srv *srv, t_client *client, const char *nick,
			 const char *msg)
{
  t_client	*dest;

  dest = list_find(&srv->clients, &client_find_by_nick, nick, IT_DATA);
  if (dest && dest != client)
    client_out(dest, ":%s!%s@%s PRIVMSG %s :%s\r\n", client->nickname,
	       client->name, client->server, dest->nickname, msg);
}

t_bool		cmd_privmsg(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;
  t_channel	*channel;

  if (strcmp(tokens[0], "PRIVMSG") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (check_tokens(srv, client, tokens))
    return (TRUE);
  channel = list_find(&client->channels, &channel_find_by_name, tokens[1],
		      IT_DATA);
  if (channel)
    chan_msg(channel, client, tokens[2]);
  else
    user_msg(srv, client, tokens[1], tokens[2]);
  return (TRUE);
}
