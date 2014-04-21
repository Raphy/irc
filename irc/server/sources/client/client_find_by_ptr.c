/*
** client_find_by_ptr.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 01:17:35 2014 raphael defreitas
** Last update Mon Apr 21 01:18:44 2014 raphael defreitas
*/

#include	"client.h"

int		client_find_by_ptr(t_client *client1, t_client *client2)
{
  if (client1 == client2)
    return (0);
  return (client1 > client2 ? 1 : -1);
}
