/*
** network_send.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 13:50:34 2014 raphael defreitas
** Last update Fri Apr 25 18:51:44 2014 raphael defreitas
*/

#include	<string.h>
#include	<sys/select.h>

#include	"defs.h"
#include	"network.h"
#include	"socket.h"

void		network_send(t_network *this)
{
  if (this->has_data_out && FD_ISSET(socket_fd(this->server), &this->write_fds))
    {
      socket_write(this->server, this->buf_out, strlen(this->buf_out));
      this->buf_out[0] = 0;
      this->has_data_out = FALSE;
    }
}
