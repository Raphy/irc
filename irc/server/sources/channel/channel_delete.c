/*
** channel_delete.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/channel
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 00:32:53 2014 raphael defreitas
** Last update Mon Apr 21 00:33:40 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"channel.h"

void		channel_delete(t_channel *this)
{
  channel_dtor(this);
  free(this);
}
