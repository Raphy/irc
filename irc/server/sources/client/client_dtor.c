/*
** clien_dtor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 03:41:24 2014 raphael defreitas
** Last update Mon Apr 21 01:15:18 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"client.h"
#include	"socket.h"

void		client_dtor(t_client *this)
{
  if (this->buf_out)
    free(this->buf_out);
  if (this->buf_in)
    free(this->buf_in);
  if (this->nickname)
    free(this->nickname);
  if (this->name)
    free(this->name);
  if (this->host)
    free(this->host);
  if (this->server)
    free(this->server);
  if (this->real_name)
    free(this->real_name);
  list_dtor(&this->channels);
  socket_delete(this->socket);
}
