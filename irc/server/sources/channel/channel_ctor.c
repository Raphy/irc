/*
** channel_ctor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/channel
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 00:28:29 2014 raphael defreitas
** Last update Mon Apr 21 00:31:24 2014 raphael defreitas
*/

#define		_GNU_SOURCE
#include	<stdlib.h>
#include	<string.h>

#include	"channel.h"
#include	"defs.h"
#include	"list.h"

int		channel_ctor(t_channel *this, const char *name)
{
  this->topic = NULL;
  list_ctor(&this->clients, NULL);
  if ((this->name = strdup(name)) == NULL)
    return (RET_FAILURE);
  return (RET_SUCCESS);
}
