/*
** cmd_ping.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Sun Apr 27 02:49:35 2014 raphael defreitas
*/

#include	<string.h>

#include	"channel.h"
#include	"client.h"
#include	"cmd.h"
#include	"defs.h"
#include	"list.h"
#include	"protocol.h"
#include	"srv.h"

static void	send_users(t_srv *srv, t_client *client, t_channel *channel)
{
  t_iterator	iterator;
  t_client	*user;

  client_out(client, ":%s 353 %s [=] :", srv->hostname, client->nickname);
  iterator_ctor(&iterator, &channel->clients, IT_DATA);
  while ((user = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      client_out(client, "%s%s", user->nickname,
		 iterator_current(&iterator) ? " " : "\r\n");
    }
  client_out(client, ":%s 366 %s :End of /NAMES list.\r\n", srv->hostname);
}

t_bool		cmd_names(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;
  t_channel	*channel;

  if (strcmp(tokens[0], "NAMES") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (!tokens[1])
    return (FALSE);
  channel = list_find(&client->channels, &channel_find_by_name, tokens[1],
		      IT_DATA);
  if (channel)
    send_users(srv, client, channel);
  return (TRUE);
}
