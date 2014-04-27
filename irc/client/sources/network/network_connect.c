/*
** network_connect.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 13:40:41 2014 raphael defreitas
** Last update Sat Apr 26 18:29:02 2014 raphael defreitas
*/

#include	<netdb.h>

#include	"defs.h"
#include	"network.h"
#include	"socket.h"

int		network_connect(t_network *this, const char *h, int p)
{
  t_hostent	*hi;

  if ((this->server = socket_new()) &&
      socket_ctor(this->server, AF_INET, SOCK_STREAM, 0) == RET_SUCCESS &&
      (hi = gethostbyname(h)) &&
      socket_connect(this->server, *(in_addr_t *)hi->h_addr_list[0], p) ==
      RET_FAILURE)
    return (RET_FAILURE);
  this->disconnected = FALSE;
  return (RET_SUCCESS);
}
