/*
** network_recv.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 13:49:00 2014 raphael defreitas
** Last update Sun Apr 27 21:59:20 2014 raphael defreitas
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
  size_t	bl;

  if (FD_ISSET(socket_fd(this->server), &this->read_fds))
    {
      this->has_data_in = TRUE;
      bl = strlen(this->buf_in);
      tmp = this->buf_in + bl;
      if ((rlen = socket_read(this->server, tmp, this->buf_in_size - bl)) > 0)
	{
	  this->buf_in[bl + rlen] = 0;
	  bl = strlen(this->buf_in);
	  if (this->buf_in_size - bl < SOCK_BUF_LEN)
	    {
	      this->buf_in_size += SOCK_BUF_LEN;
	      this->buf_in = realloc(this->buf_in, this->buf_in_size + 1);
	      if (this->buf_in == NULL)
		this->disconnected = TRUE;
	    }
	  this->has_data_in = TRUE;
	}
      else
	this->disconnected = TRUE;
    }
}
