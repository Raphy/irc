/*
** client_ctor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 03:38:45 2014 raphael defreitas
** Last update Mon Apr 21 01:09:15 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"client.h"
#include	"defs.h"
#include	"list.h"
#include	"socket.h"

static void	default_values(t_client *this)
{
  this->name = NULL;
  this->host = NULL;
  this->server = NULL;
  this->real_name = NULL;
  this->nickname = NULL;
  this->authenticated = FALSE;
  this->pinged = FALSE;
  this->ponged = FALSE;
  this->ping_val[0] = 0;
}

int		client_ctor(t_client *this, t_socket *socket)
{
  default_values(this);
  this->socket = socket;
  if ((this->buf_in = malloc((BUF_SIZE + 1) * sizeof(char))) == NULL ||
      (this->buf_out = malloc((BUF_SIZE + 1) * sizeof(char))) == NULL)
    return (RET_FAILURE);
  list_ctor(&this->channels, NULL);
  this->buf_in[0] = 0;
  this->buf_out[0] = 0;
  this->buf_in_size = BUF_SIZE;
  this->buf_out_size = BUF_SIZE;
  this->has_data_in = FALSE;
  this->has_data_out = FALSE;
  this->disconnected = FALSE;
  return (RET_SUCCESS);
}
