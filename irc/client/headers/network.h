/*
** network.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Fri Apr 25 00:35:59 2014 raphael defreitas
** Last update Fri Apr 25 11:19:05 2014 raphael defreitas
*/

#ifndef		NETWORK_H_
# define	NETWORK_H_


# ifdef		_cplusplus
extern "C" {
# endif /* !_cplusplus */

# include	<sys/select.h>

# include	"defs.h"
# include	"socket.h"
  
  typedef	struct
  {
    t_socket	*server;
    fd_set	read_fds;
    fd_set	write_fds;
    char	*in_buffer;
    t_bool	has_in_data;
    char	*out_buffer;
    t_bool	has_out_data;
  }		t_network;

int		network_ctor(t_network *);
void		network_dtor(t_network *);

int		network_connect(t_network *, const char *, int);
int		network_select(t_network *);

void		network_recv(t_network *);
void		network_send(t_network *);

# ifdef		_cplusplus
}
# endif /* !_cplusplus */

#endif /* !NETWORK_H_*/
