/*
** network_select.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 13:45:12 2014 raphael defreitas
** Last update Fri Apr 25 18:48:22 2014 raphael defreitas
*/

#include	<stdlib.h>
#include	<sys/select.h>

#include	"network.h"

int			network_select(t_network *this)
{
  int			ret;

  printf("select\n");
  ret = select(FD_SETSIZE, &this->read_fds, &this->write_fds, NULL, &this->tv);
  if (ret == RET_ERROR)
    return (ret);
  return (ret);
}
