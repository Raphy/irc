/*
** network_ctor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources/network
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Fri Apr 25 11:46:09 2014 raphael defreitas
** Last update Sat Apr 26 18:27:30 2014 raphael defreitas
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
  this->buf_in = NULL;
  this->buf_out = NULL;
  this->has_data_in = FALSE;
  this->has_data_out = FALSE;
  this->disconnected = TRUE;
  if (!(this->buf_in = calloc(SOCK_BUF_LEN, sizeof(char))) ||
      !(this->buf_out = calloc(SOCK_BUF_LEN, sizeof(char))))
    return (RET_FAILURE);
  this->buf_in_size = SOCK_BUF_LEN;
  this->buf_out_size = SOCK_BUF_LEN;
  return (RET_SUCCESS);
}
