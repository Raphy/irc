/*
** srv_ping_pong.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sun Apr 20 03:12:26 2014 raphael defreitas
** Last update Sun Apr 20 03:53:48 2014 raphael defreitas
*/

#include	<stdlib.h>
#include	<time.h>

#include	"client.h"
#include	"list.h"
#include	"srv.h"

static void	ping(t_client *client)
{
  time_t	now;

  now = time(NULL);
  strftime (client->ping_val, 32, "%s", localtime(&now));
  client_out(client, "PING %s\r\n", client->ping_val);
  client->pinged = TRUE;
}

void		srv_ping_pong(t_srv *this)
{
  t_client	*client;
  t_iterator	iterator;

  srv_log(NULL, "Processing to ping-pong...");
  iterator_ctor(&iterator, &this->clients, IT_DATA);
  while ((client = iterator_current(&iterator)))
    {
      iterator_next(&iterator);
      if (client->pinged && client->ponged)
	{
	  client->pinged = FALSE;
	  client->ping_val[0] = 0;
	  client->ponged = FALSE;
	}
      else if (!client->pinged && !client->ponged)
	ping(client);
      else if (client->pinged && !client->ponged)
	{
	  client_out(client, "ERROR :Closing link: %s (Ping timeout: %d " \
		     "seconds)\r\n", socket_ip(client_socket(client)), 120);
	  client->disconnected = TRUE;
	}
    }
}
