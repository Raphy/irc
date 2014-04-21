/*
** client_in_handle.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 03:46:02 2014 raphael defreitas
** Last update Sat Apr 19 05:27:39 2014 raphael defreitas
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>

#include	"client.h"
#include	"defs.h"

void		client_in_handle(t_client *this)
{
  int		rlen;
  char		*tmp;
  size_t	buf_len;

  this->has_data_in = TRUE;
  buf_len = strlen(this->buf_in);
  tmp = this->buf_in + buf_len;
  if ((rlen = socket_read(this->socket, tmp, this->buf_in_size - buf_len)) > 0)
    {
      this->buf_in[buf_len + rlen] = 0;
      buf_len = strlen(this->buf_in);
      if (this->buf_in_size - buf_len < BUF_SIZE)
	{
	  this->buf_in_size += BUF_SIZE;
	  this->buf_in = realloc(this->buf_in, this->buf_in_size + 1);
	  if (this->buf_in == NULL)
	    this->disconnected = TRUE;
	}
      if (this->buf_in[buf_len - 2] != '\r' &&
	  this->buf_in[buf_len - 1] != '\n')
	this->has_data_in = FALSE;
    }
  else
    this->disconnected = TRUE;
}
