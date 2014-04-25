/*
** network_recv.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 13:49:00 2014 raphael defreitas
** Last update Fri Apr 25 18:50:34 2014 raphael defreitas
*/

#include	<stdlib.h>
#include	<string.h>
#include	<sys/select.h>

#include	"defs.h"
#include	"network.h"
#include	"socket.h"

void		network_recv(t_network *this)
{
  int		rlen;
  char		*tmp;
  size_t	buf_len;

  if (FD_ISSET(socket_fd(this->server), &this->read_fds))
    {
      this->has_data_in = TRUE;
      buf_len = strlen(this->buf_in);
      tmp = this->buf_in + buf_len;
      if ((rlen = socket_read(this->server, tmp, this->buf_in_size - buf_len)) > 0)
    {
      this->buf_in[buf_len + rlen] = 0;
      buf_len = strlen(this->buf_in);
      if (this->buf_in_size - buf_len < SOCK_BUF_LEN)
        {
          this->buf_in_size += SOCK_BUF_LEN;
          this->buf_in = realloc(this->buf_in, this->buf_in_size + 1);
          if (this->buf_in == NULL)
            this->disconnected = TRUE;
        }
      if (buf_len < 3 || (this->buf_in[buf_len - 2] != '\r' &&
			  this->buf_in[buf_len - 1] != '\n'))
        this->has_data_in = FALSE;
    }
      else
	this->disconnected = TRUE;
    }
}
