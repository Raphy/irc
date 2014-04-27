/*
** network_set_fds.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 13:47:18 2014 raphael defreitas
** Last update Sat Apr 26 15:43:16 2014 raphael defreitas
*/

#include	<sys/select.h>

#include	"network.h"
#include	"socket.h"

void		network_set_fds(t_network *this)
{
  FD_ZERO(&this->read_fds);
  FD_ZERO(&this->write_fds);
  if (this->server)
    {
      FD_SET(socket_fd(this->server), &this->read_fds);
      if (this->has_data_out)
	FD_SET(socket_fd(this->server), &this->write_fds);
    }
}
