/*
** srv_cmd.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 16:31:18 2014 raphael defreitas
** Last update Sun Apr 20 04:32:22 2014 raphael defreitas
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"client.h"
#include	"srv.h"
#include	"utils.h"

void		srv_cmd(t_srv *this, t_client *client, const char *cmd)
{
  char		**tokens;
  int		i;

  srv_log(client, "Request: %s", cmd);
  if ((tokens = strtoarr(cmd, " ")))
    {
      i = 0;
      while (this->cmd_handlers[i] &&
	     !this->cmd_handlers[i]->handler(this->cmd_handlers[i],
					     client, tokens))
	i++;
      if (this->cmd_handlers[i] == NULL)
	srv_log(client, "Unknown command « %s »", tokens[0]);
      free(tokens);
    }
}
