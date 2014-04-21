/*
** channel_dtor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/channel
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 00:31:35 2014 raphael defreitas
** Last update Mon Apr 21 00:32:46 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"channel.h"
#include	"list.h"

void		channel_dtor(t_channel *this)
{
  if (this->name)
    free(this->name);
  if (this->topic)
    free(this->topic);
  list_dtor(&this->clients);
}
