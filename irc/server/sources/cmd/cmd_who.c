/*
** cmd_ping.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Tue Apr 22 06:00:41 2014 raphael defreitas
*/

#include	<string.h>

#include	"channel.h"
#include	"client.h"
#include	"cmd.h"
#include	"defs.h"
#include	"list.h"
#include	"protocol.h"
#include	"srv.h"

static void	who_chan(t_srv *srv, t_channel *channel, t_client *client)
{
  t_iterator	iterator;
  t_client	*user;

  iterator_ctor(&iterator, &channel->clients, IT_DATA);
  while ((user = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      client_out(client, ":%s %03d %s %s %s %s %s %s H :0 %s\r\n",
		 srv->hostname, RPL_WHOREPLY, client->nickname, channel->name,
		 user->name, socket_ip(client_socket(user)), user->server,
		 user->nickname, user->real_name);
    }
  client_out(client, ":%s %03d :End of /WHO list.\r\n", srv->hostname,
	     RPL_ENDOFWHO);
}

t_bool		cmd_who(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;
  t_channel	*channel;

  if (strcmp(tokens[0], "WHO") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (!tokens[1])
    return (TRUE);
  channel = list_find(&client->channels, &channel_find_by_name, tokens[1],
		      IT_DATA);
  if (channel)
    who_chan(srv, channel, client);
  return (TRUE);
}
