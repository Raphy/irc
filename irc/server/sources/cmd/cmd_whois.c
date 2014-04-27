/*
** cmd_whois.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Tue Apr 22 06:00:32 2014 raphael defreitas
*/

#include	<string.h>

#include	"channel.h"
#include	"client.h"
#include	"cmd.h"
#include	"defs.h"
#include	"list.h"
#include	"protocol.h"
#include	"srv.h"

t_bool		cmd_whois(t_cmd *cmd, t_client *client, char **tokens)
{
  t_srv		*srv;
  t_client	*user;

  if (strcmp(tokens[0], "WHOIS") != 0)
    return (FALSE);
  srv = (t_srv *)cmd->data;
  if (!tokens[1])
    return (TRUE);
  user = list_find(&srv->clients, &client_find_by_nick, tokens[1],
		   IT_DATA);
  if (user)
    {
      client_out(client, ":%s %03d %s %s %s %s %s :%s\r\n", srv->hostname,
		 RPL_WHOISUSER, client->nickname, user->nickname, user->name,
		 socket_ip(client_socket(user)), user->server, user->real_name);

    }
  return (TRUE);
}
