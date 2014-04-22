/*
** cmd_ping.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 21:56:47 2014 raphael defreitas
*/

#include	<string.h>

#include	"channel.h"
#include	"client.h"
#include	"cmd.h"
#include	"defs.h"
#include	"list.h"
#include	"protocol.h"
#include	"srv.h"

static void	respond(t_srv *srv, t_client *client, t_channel *channel)
{
  t_client	*other;
  t_iterator	iterator;

  if (channel->topic)
    client_out(client, ":%s %d %s %s :%s\r\n", srv->hostname, RPL_TOPIC,
	       client->nickname, channel->name, channel->topic);
  client_out(client, ":%s %d %s = %s :", srv->hostname,
	     RPL_NAMREPLY, client->nickname, channel->name);
  iterator_ctor(&iterator, &channel->clients, IT_DATA);
  while ((other = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      client_out(client, "%s%s", other->nickname,
		 iterator_current(&iterator) ? " " : "");
    }
  client_out(client, "\r\n");
  client_out(client, ":%s %d %s %s :End of /NAMES list.\r\n",
	     srv->hostname, RPL_ENDOFNAMES, client->nickname, channel->name);
}

static void	warn(t_client *client, t_channel *channel)
{
  t_iterator	iterator;
  t_client	*dest;

  iterator_ctor(&iterator, &channel->clients, IT_DATA);
  while ((dest = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      client_out(dest, ":%s!%s@%s JOIN %s\r\n", client->nickname,
		 client->name, client->server, channel->name);
    }
}

t_bool		cmd_join(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;
  t_channel	*channel;

  if (strcmp(tokens[0], "JOIN") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (!tokens[1])
    {
      client_out(client, ":%s %d %s JOIN :Not enough parameters\r\n",
		 srv->hostname, ERR_NEEDMOREPARAMS, client->nickname);
      return (TRUE);
    }
  if ((channel = list_find(&srv->channels, &channel_find_by_name, tokens[1],
			   IT_DATA)) == NULL)
    if ((channel = channel_new(tokens[1])))
      list_enqueue(&srv->channels, channel);
  if (!list_find(&client->channels, &channel_find_by_name, tokens[1], 0) &&
      !list_find(&channel->clients, &client_find_by_ptr, client, 0))
    {
      list_enqueue(&channel->clients, client);
      list_enqueue(&client->channels, channel);
      warn(client, channel);
      respond(srv, client, channel);
    }
  return (TRUE);
}
