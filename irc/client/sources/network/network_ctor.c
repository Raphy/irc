/*
** network_ctor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 11:46:09 2014 raphael defreitas
** Last update Fri Apr 25 11:53:21 2014 raphael defreitas
*/

#include	<stdlib.h>
#include	<sys/select.h>

#include	"defs.h"
#include	"network.h"
#include	"socket.h"

int		network_ctor(t_network *this)
{
  this->server = NULL;
  FD_ZERO(&this->read_fds);
  FD_ZERO(&this->write_fds);
  this->in_buffer = NULL;
  this->out_buffer = NULL;
  this->has_in_data = FALSE;
  this->has_out_data = FALSE;
  if (!(this->server = socket_new()) ||
      !(this->in_buffer = calloc(SOCK_BUF_LEN, sizeof(char))) ||
      !(this->out_buffer = calloc(SOCK_BUF_LEN, sizeof(char))))
    return (RET_FAILURE);
  return (RET_SUCCESS);
}
