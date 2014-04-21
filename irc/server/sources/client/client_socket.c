/*
** client_socket.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 03:53:02 2014 raphael defreitas
** Last update Sat Apr 19 03:53:37 2014 raphael defreitas
*/

#include	"client.h"
#include	"socket.h"

t_socket	*client_socket(t_client *this)
{
  return (this->socket);
}
