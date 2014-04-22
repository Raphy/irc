/*
** protocol_parse.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/common/sources/protocol
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Mon Apr 21 18:56:42 2014 raphael defreitas
** Last update Mon Apr 21 21:47:58 2014 raphael defreitas
*/

#include	<ctype.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

static size_t	get_size(const char *cmd)
{
  int		i;
  size_t	size;
  char		end;

  i = 0;
  size = 0;
  while (cmd[i] && cmd[i] == ' ')
    i++;
  while (cmd[i])
    {
      while (cmd[i] && cmd[i] != ' ' && cmd[i] != ':')
	i++;
      if (cmd[i] == ':')
	{
	  end = cmd[i + 1] && !isprint(cmd[i + 1]) ? cmd[i + 1] : '\0';
	  if (size == 0)
	    end = ' ';
	  while (cmd[i] != end)
	    i++;
	}
      size++;
      while (cmd[i] && cmd[i] == ' ')
	i++;
    }
  return (size);
}

static void	fill_trail(char **tokens, char *cmd, int *i, size_t size)
{
  char		end;

  (*i)++;
  end = cmd[*i] && !isprint(cmd[*i]) ? cmd[*i] : '\0';
  if (size == 0)
    end = ' ';
  if (cmd[*i] && !isprint(cmd[*i]))
    (*i)++;
  tokens[size] = cmd + *i;
  while (cmd[*i] && cmd[*i] != end)
    (*i)++;
  if (cmd[*i] && !isprint(cmd[*i]))
    cmd[(*i)++] = 0;
}

static void	fill(char **tokens, char *cmd)
{
  int		i;
  size_t	size;

  i = 0;
  size = 0;
  while (cmd[i] && cmd[i] == ' ')
    cmd[i++] = 0;
  while (cmd[i])
    {
      tokens[size] = cmd + i;
      if (cmd[i] == ':')
	fill_trail(tokens, cmd, &i, size);
      while (cmd[i] && cmd[i] != ' ')
	i++;
      size++;
      while (cmd[i] && cmd[i] == ' ')
	cmd[i++] = 0;
    }
  tokens[size] = NULL;
}

char		**protocol_parse(const char *cmd)
{
  char		**tokens;
  size_t	size;
  size_t	len;
  char		*cpy;

  if (!cmd)
    return (NULL);
  size = get_size(cmd);
  len = strlen(cmd);
  tokens = malloc((size + 1) * sizeof(char *) + (len + 1) * sizeof(char));
  if (!tokens)
    return (NULL);
  cpy = ((char *)(tokens) + (size + 1) * sizeof(char *));
  strcpy(cpy, cmd);
  fill(tokens, cpy);
  return (tokens);
}
