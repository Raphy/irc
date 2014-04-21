/*
** main.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/myirc/server/sources
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Wed Apr 16 14:27:13 2014 raphael defreitas
** Last update Sun Apr 20 03:55:11 2014 raphael defreitas
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

static void	print_usage(FILE *file, char *progname)
{
  fprintf(file, "Usage: %s <port>\n", progname);
}

int		main(int argc, char **argv)
{
  if (argc < 2)
    {
      print_usage(stderr, argv[0]);
      return (EXIT_FAILURE);
    }
  if (srv_ctor(&g_srv, atoi(argv[1])) == RET_FAILURE)
    {
      srv_dtor(&g_srv);
      return (EXIT_FAILURE);
    }
  signal_handler(-1);
  srv_loop(&g_srv);
  srv_dtor(&g_srv);
  return (EXIT_FAILURE);
}
