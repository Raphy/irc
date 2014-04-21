/*
** client_out_handle.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 04:40:04 2014 raphael defreitas
** Last update Sun Apr 20 04:34:31 2014 raphael defreitas
*/

#include	<string.h>

#include	"client.h"
#include	"defs.h"
#include	"socket.h"
#include	"srv.h"

void		client_out_handle(t_client *this)
{
  size_t	len;

  len = strlen(this->buf_out);
  if (len > 0)
    {
      srv_log(this, "Response: %s", this->buf_out);
      if (socket_write(this->socket, this->buf_out, len) > -1)
	{
	  this->has_data_out = FALSE;
	  this->buf_out[0] = 0;
	}
    }
}
