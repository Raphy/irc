/*
** client.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sat Apr 19 03:36:40 2014 raphael defreitas
** Last update Mon Apr 21 18:43:07 2014 raphael defreitas
*/

#ifndef		CLIENT_H_
# define	CLIENT_H_

# include	<sys/types.h>

# include	"defs.h"
# include	"list.h"
# include	"socket.h"

# ifndef	BUF_SIZE
#  define	BUF_SIZE	4096
# endif /* !BUF_SIZE */

typedef	struct
{
  t_socket	*socket;
  char		*buf_out;
  size_t	buf_out_size;
  t_bool	has_data_out;
  char		*buf_in;
  size_t	buf_in_size;
  t_bool	has_data_in;
  t_bool	disconnected;
  char		*name;
  char		*host;
  char		*server;
  char		*real_name;
  char		*nickname;
  t_bool	authenticated;
  t_bool	pinged;
  char		ping_val[33];
  t_bool	ponged;
  t_list	channels;
}		t_client;

t_client	*client_new(t_socket *socket);
void		client_delete(t_client *this);

int		client_ctor(t_client *this, t_socket *socket);
void		client_dtor(t_client *this);

int		client_find_by_ptr(t_client *client1, t_client *client2);
int		client_find_by_nick(t_client *client1, const char *nick);

t_socket	*client_socket(t_client *this);

void		client_in_handle(t_client *this);
void		client_out_handle(t_client *this);
void		client_out(t_client *this, const char *format, ...);

#endif /* !CLIENT_H_*/
