/*
** channel_new.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/channel
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 00:25:51 2014 raphael defreitas
** Last update Mon Apr 21 00:27:45 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"channel.h"
#include	"defs.h"

t_channel	*channel_new(const char *name)
{
  t_channel	*this;

  if ((this = malloc(sizeof(t_channel))) == NULL)
    return (NULL);
  if (channel_ctor(this, name) == RET_FAILURE)
    {
      channel_delete(this);
      return (NULL);
    }
  return (this);
}
