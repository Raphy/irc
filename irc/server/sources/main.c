/*
** main.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/myirc/server/sources
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Wed Apr 16 14:27:13 2014 raphael defreitas
** Last update Sat Apr 26 14:02:24 2014 raphael defreitas
*/

#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>

#include	"srv.h"

t_srv		g_srv;

static void	signal_handler(int signum)
{
  if (signum == SIGINT)
    {
      printf("\nClosing the server...\n");
      srv_dtor(&g_srv);
      exit(EXIT_SUCCESS);
    }
  signal(SIGINT, &signal_handler);
}

int		main(int argc, char **argv)
{
  if (srv_ctor(&g_srv,
	       argc > 1 ? atoi(argv[1]) : 6667,
	       argc > 2 ? atoi(argv[2]) : 300) == RET_FAILURE)
    {
      srv_dtor(&g_srv);
      return (EXIT_FAILURE);
    }
  signal_handler(-1);
  srv_loop(&g_srv);
  srv_dtor(&g_srv);
  return (EXIT_FAILURE);
}
