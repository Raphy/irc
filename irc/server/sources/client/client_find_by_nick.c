/*
** client_find_by_nick.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 01:17:35 2014 raphael defreitas
** Last update Mon Apr 21 18:44:04 2014 raphael defreitas
*/

#include	<string.h>

#include	"client.h"

int		client_find_by_nick(t_client *client, const char *nick)
{
  return (strcmp(client->nickname, nick));
}
