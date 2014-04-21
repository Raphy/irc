/*
** srv_dtor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 00:53:19 2014 raphael defreitas
** Last update Mon Apr 21 00:50:22 2014 raphael defreitas
*/

#include	"cmd.h"
#include	"list.h"
#include	"socket.h"
#include	"srv.h"

void		srv_dtor(t_srv *this)
{
  int		i;

  i = 0;
  while (i < CMD_NBR)
    {
      cmd_delete(this->cmd_handlers[i]);
      i++;
    }
  socket_dtor(&this->socket);
  list_dtor(&this->clients);
  list_dtor(&this->channels);
}
