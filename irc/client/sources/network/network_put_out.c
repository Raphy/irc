/*
** network_put_out.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 15:18:43 2014 raphael defreitas
** Last update Sun Apr 27 00:13:51 2014 raphael defreitas
*/

#define		_GNU_SOURCE
#include	<stdarg.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"network.h"
#include	"socket.h"

void		network_put_out(t_network *this, const char *format, va_list ap)
{
  size_t	ret;
  size_t	len;
  char		*tmp;

  len = strlen(this->buf_out);
  tmp = this->buf_out + len;
  while ((ret = vsnprintf(tmp, this->buf_out_size - len - 1, format, ap)) >
	 this->buf_out_size - len - 1)
    {
      this->buf_out_size += SOCK_BUF_LEN;
      this->buf_out = realloc(this->buf_out, this->buf_out_size + 1);
      if (this->buf_out == NULL)
	this->disconnected = TRUE;
    }
  this->has_data_out = TRUE;
}
