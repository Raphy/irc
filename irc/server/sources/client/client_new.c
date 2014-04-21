/*
** client_new.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 03:43:41 2014 raphael defreitas
** Last update Sat Apr 19 03:45:11 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"client.h"
#include	"defs.h"
#include	"socket.h"

t_client	*client_new(t_socket *socket)
{
  t_client	*this;

  if ((this = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  if (client_ctor(this, socket) == RET_FAILURE)
    {
      client_delete(this);
      return (NULL);
    }
  return (this);
}
