/*
** channel_find_by_name.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/channel
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 00:34:28 2014 raphael defreitas
** Last update Mon Apr 21 00:35:09 2014 raphael defreitas
*/

#include	<string.h>

#include	"channel.h"

int		channel_find_by_name(t_channel *channel, const char *name)
{
  return (strcmp(channel->name, name));
}
