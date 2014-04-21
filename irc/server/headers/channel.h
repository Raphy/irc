/*
** channel.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Mon Apr 21 00:21:30 2014 raphael defreitas
** Last update Mon Apr 21 00:30:30 2014 raphael defreitas
*/

#ifndef		CHANNEL_H_
# define	CHANNEL_H_

# include	"list.h"

typedef	struct
{
  char		*name;
  t_list	clients;
  char		*topic;
}		t_channel;

t_channel	*channel_new(const char *name);
void		channel_delete(t_channel *this);

int		channel_ctor(t_channel *this, const char *name);
void		channel_dtor(t_channel *this);

int		channel_find_by_name(t_channel *channel, const char *name);

#endif /* !CHANNEL_H_*/
