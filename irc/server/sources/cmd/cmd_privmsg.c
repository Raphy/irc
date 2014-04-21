/*
** cmd_ping.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 05:14:53 2014 raphael defreitas
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
  /* Todo: Check if the user is in the channel */
  if (tokens[2])
    {
      if (tokens[2][0] == ':')
	tokens[2]++;
      len = strlen(tokens[2]);
    }
  if (!tokens[2] || len <= 0)
    {
      client_out(client, ":%s %d * :No text to send\r\n",
		 srv->hostname, ERR_NOTEXTTOSEND);
      return (TRUE);
    }
  return (FALSE);
}

static void	send_msg(t_client *dest, t_client *client, char **tokens)
{
  int		i;

  client_out(dest, ":%s!%s@%s PRIVMSG %s :", client->nickname,
	     client->name, client->server, tokens[1]);
  i = 2;
  while (tokens[i])
    client_out(dest, "%s ", tokens[i++]);
  client_out(dest, "\r\n");
}

t_bool		cmd_privmsg(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;
  t_channel	*channel;
  t_iterator	iterator;
  t_client	*dest;

  if (strcmp(tokens[0], "PRIVMSG") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (check_tokens(srv, client, tokens))
    return (TRUE);
  channel = list_find(&client->channels, &channel_find_by_name, tokens[1],
		      IT_DATA);
  if (channel)
    {
      iterator_ctor(&iterator, &channel->clients, IT_DATA);
      while ((dest = iterator_current(&iterator)))
	{
	  iterator_next(&iterator);
	  if (dest != client)
	    send_msg(dest, client, tokens);
	}
    }
  return (TRUE);
}
