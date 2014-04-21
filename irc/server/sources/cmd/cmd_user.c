/*
** cmd_user.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 22:06:36 2014 raphael defreitas
** Last update Mon Apr 21 05:05:36 2014 raphael defreitas
*/

#define		_GNU_SOURCE
#include	<stdlib.h>
#include	<string.h>

#include	"client.h"
#include	"cmd.h"
#include	"defs.h"

t_bool		cmd_user(t_cmd *cmd, t_client *client, char **tokens)
{
  if (strcmp(tokens[0], "USER") != 0)
    return (FALSE);
  if (tokens[1] && tokens[2] && tokens[3] && tokens[4])
    {
      if (client->name)
	free(client->name);
      client->name = strdup(tokens[1]);
      if (client->host)
	free(client->host);
      client->host = strdup(tokens[2]);
      if (client->server)
	free(client->server);
      client->server = strdup(tokens[3]);
      if (client->real_name)
	free(client->real_name);
      client->real_name = strdup(tokens[4]);
      return (TRUE);
    }
  return (TRUE);
}
