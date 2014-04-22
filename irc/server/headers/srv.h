/*
** srv.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Fri Apr 18 22:40:52 2014 raphael defreitas
** Last update Mon Apr 21 20:28:17 2014 raphael defreitas
*/

#ifndef		SRV_H_
# define	SRV_H_

# include	<sys/select.h>

# include	"client.h"
# include	"cmd.h"
# include	"list.h"
# include	"socket.h"

typedef	struct
{
  t_socket	socket;
  fd_set	read_fds;
  fd_set	write_fds;
  t_list	clients;
  int		nfds;
  char		hostname[1025];
  char		created[128];
  t_cmd		*cmd_handlers[CMD_NBR + 1];
  t_list	channels;
  int		timeout;
}		t_srv;

int		srv_ctor(t_srv *this, int port, int timeout);
void		srv_dtor(t_srv *this);

void		srv_log(t_client *client, char *format, ...);

void		srv_loop(t_srv *this);
void		srv_treat_client(t_srv *this, t_item *item, t_client *client);
void		srv_cmd(t_srv *this, t_client *client, const char *cmd);
void		srv_auth(t_srv *this, t_client *client);
void		srv_ping_pong(t_srv *this);

#endif /* !SRV_H_*/
