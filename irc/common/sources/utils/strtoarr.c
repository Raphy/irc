/*
** strtoarr.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/common/sources/utils
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sat Apr 19 17:08:34 2014 raphael defreitas
** Last update Mon Apr 21 19:48:01 2014 raphael defreitas
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

static void	fill(char **arr, char *cpy, const char *del)
{
  char		*token;
  int		i;

  i = 0;
  token = strtok(cpy, del);
  while (token)
    {
      arr[i] = token;
      i++;
      token = strtok(NULL, del);
    }
  arr[i] = NULL;
}

static int	get_size(const char *cmd, const char *del)
{
  int		size;
  char		*cpy;
  char		*token;

  size = 0;
  if ((cpy = strdup(cmd)) == NULL)
    return (-1);
  token = strtok(cpy, del);
  while (token)
    {
      size++;
      token = strtok(NULL, del);
    }
  free(cpy);
  return (size);
}

char		**strtoarr(const char *cmd, const char *del)
{
  char		*cpy;
  int		s;
  char		**arr;

  if ((s = get_size(cmd, del)) == -1)
    return (NULL);
  arr = calloc(1, (s + 1) * sizeof(char *) + (strlen(cmd) + 8) * sizeof(char));
  if (arr == NULL)
    return (NULL);
  cpy = ((char *)(arr) + (s + 1) * sizeof(char *));
  strcpy(cpy, cmd);
  cpy[strlen(cpy)] = 0;
  fill(arr, cpy, del);
  return (arr);
}
