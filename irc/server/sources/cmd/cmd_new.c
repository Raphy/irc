/*
** cmd_new.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 23:21:27 2014 raphael defreitas
** Last update Sat Apr 19 23:22:52 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"cmd.h"

t_cmd		*cmd_new(void *data, t_bool (*handler)())
{
  t_cmd		*this;

  if ((this = calloc(1, sizeof(t_cmd))) == NULL)
    return (NULL);
  this->data = data;
  this->handler = handler;
  return (this);
}
