/*
** client_delete.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/client
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 03:45:21 2014 raphael defreitas
** Last update Sat Apr 19 03:45:48 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"client.h"

void		client_delete(t_client *this)
{
  client_dtor(this);
  free(this);
}
