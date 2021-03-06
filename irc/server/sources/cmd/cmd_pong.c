/*
** cmd_nick.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 09:00:18 2014 raphael defreitas
*/

#include	<string.h>

#include	"client.h"
#include	"cmd.h"
#include	"defs.h"

t_bool		cmd_pong(__attribute__((__unused__)) t_cmd *cmd,
			 t_client *client, char **tokens)
{
  if (strcmp(tokens[0], "PONG") != 0)
    return (FALSE);
  if (!client->pinged)
    client->disconnected = TRUE;
  if ((tokens[1] == NULL && client->ping_val[0] != 0) ||
      strcmp(tokens[1], client->ping_val) != 0)
    client->disconnected = TRUE;
  client->ponged = TRUE;
  return (TRUE);
}
