/*
** socket.h for liboskcet in /home/raphy/Epitech/Libraries/libsocket/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Mon Apr 14 16:45:01 2014 raphael defreitas
** Last update Sat Apr 19 21:13:09 2014 raphael defreitas
*/

#ifndef		SOCKET_H_
# define	SOCKET_H_

# include	<sys/socket.h>
# include	<netinet/in.h>
# include	<arpa/inet.h>

# ifndef	RET_ERROR
#  define	RET_ERROR	-1
# endif /* !RET_ERROR */

# ifndef	RET_SUCCESS
#  define	RET_SUCCESS	0
# endif /* !RET_SUCCESS */

# ifndef	RET_FAILURE
#  define	RET_FAILURE	1
# endif /* !RET_FAILURE */

# ifndef	SOCK_BUF_LEN
#  define	SOCK_BUF_LEN	2048
# endif /* !SOCK_BUF_LEN */

/*
** +--------+
** | Socket |
** +--------+
*/
typedef	struct	sockaddr_in	t_sockaddr_in;

typedef	struct
{
  int		fd;
  int		domain;
  socklen_t	addr_len;
  t_sockaddr_in	addr;
}		t_socket;

int		socket_ctor(t_socket *this, int domain, int type, int protocol);
void		socket_dtor(t_socket *this);

t_socket	*socket_new(void);
void		socket_delete(t_socket *this);

int		socket_fd(t_socket *this);
const char	*socket_ip(t_socket *this);

int		socket_connect(t_socket *this, in_addr_t address, int port);

int		socket_bind(t_socket *this, in_addr_t address, int port);
int		socket_listen(t_socket *this, int queue_size);
t_socket	*socket_accept(t_socket *this);

int		socket_write(t_socket *this, const void *buf, size_t len);
int		socket_read(t_socket *this, void *buf, size_t len);

#endif /* !SOCKET_H_*/
