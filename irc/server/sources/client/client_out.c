/*
** client_out.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sun Apr 20 00:24:46 2014 raphael defreitas
** Last update Mon Apr 21 06:31:10 2014 raphael defreitas
*/

#define		_GNU_SOURCE
#include	<stdarg.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"client.h"
#include	"defs.h"

void		client_out(t_client *this, const char *format, ...)
{
  va_list	ap;
  size_t	ret;
  size_t	len;
  char		*tmp;

  va_start(ap, format);
  len = strlen(this->buf_out);
  tmp = this->buf_out + len;
  while ((ret = vsnprintf(tmp, this->buf_out_size - len - 1, format, ap)) >
	 this->buf_out_size - len - 1)
    {
      this->buf_out_size += BUF_SIZE;
      this->buf_out = realloc(this->buf_out, this->buf_out_size + 1);
      if (this->buf_out == NULL)
	this->disconnected = TRUE;
      va_end(ap);
      va_start(ap, format);
    }
  va_end(ap);
  this->has_data_out = TRUE;
}
