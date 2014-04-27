/*
** network.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Fri Apr 25 00:35:59 2014 raphael defreitas
** Last update Sun Apr 27 22:00:17 2014 raphael defreitas
*/

#ifndef		NETWORK_H_
# define	NETWORK_H_

# include	<glib.h>

G_BEGIN_DECLS

# include	<sys/select.h>
# include	<time.h>

# include	"defs.h"
# include	"socket.h"

  typedef	struct
  {
    t_socket	*server;
    fd_set	read_fds;
    fd_set	write_fds;
    char	*buf_in;
    size_t	buf_in_size;
    t_bool	has_data_in;
    char	*buf_out;
    size_t	buf_out_size;
    t_bool	has_data_out;
    t_bool	disconnected;
    struct timeval tv;
  }		t_network;

int		network_ctor(t_network *);
void		network_dtor(t_network *);

int		network_connect(t_network *, const char *, int);
void		network_set_fds(t_network *);
int		network_select(t_network *);

void		network_recv(t_network *);
void		network_send(t_network *);
void		network_put_out(t_network *, const char *, va_list);

G_END_DECLS

#endif /* !NETWORK_H_*/
