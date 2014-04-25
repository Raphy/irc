/*
** network_dtor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 11:50:37 2014 raphael defreitas
** Last update Fri Apr 25 11:51:33 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"network.h"
#include	"socket.h"

void		network_dtor(t_network *this)
{
  if (this->server)
    socket_delete(this->server);
  free(this->in_buffer);
  free(this->out_buffer);
}
