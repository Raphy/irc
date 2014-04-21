/*
** cmd_dtor.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/cmd
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 23:23:42 2014 raphael defreitas
** Last update Sat Apr 19 23:24:01 2014 raphael defreitas
*/

#include	<stdlib.h>

#include	"cmd.h"

void		cmd_delete(t_cmd *this)
{
  free(this);
}
