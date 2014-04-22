/*
** cmd_ping.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 09:01:18 2014 raphael defreitas
*/

#include	<string.h>

#include	"client.h"
#include	"cmd.h"
#include	"defs.h"

t_bool		cmd_ping(__attribute__((__unused__)) t_cmd *cmd,
			 t_client *client, char **tokens)
{
  if (strcmp(tokens[0], "PING") != 0)
    return (FALSE);
  if (tokens[1])
    client_out(client, "PONG :%s\r\n", tokens[1]);
  else
    client_out(client, "PONG\r\n");
  return (TRUE);
}
