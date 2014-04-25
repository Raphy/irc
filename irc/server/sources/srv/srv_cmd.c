/*
** srv_cmd.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 16:31:18 2014 raphael defreitas
** Last update Tue Apr 22 06:04:50 2014 raphael defreitas
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"client.h"
#include	"protocol.h"
#include	"srv.h"
#include	"utils.h"

void		srv_cmd(t_srv *this, t_client *client, const char *cmd)
{
  char		**tokens;
  int		i;
  int		j;

  srv_log(client, "IN: %s", cmd);
  if ((tokens = protocol_parse(cmd)))
    {
      j = 0;
      while (tokens[j])
	printf("%s[%s]%s", j == 0 ? "Tokens: " : "", tokens[j++],
	       tokens[j] ? " " : "\n");
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
