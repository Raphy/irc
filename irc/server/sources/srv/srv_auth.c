/*
** srv_auth.c for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/sources/srv
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Sun Apr 20 02:32:49 2014 raphael defreitas
** Last update Mon Apr 21 03:48:54 2014 raphael defreitas
*/

#include	"client.h"
#include	"defs.h"
#include	"protocol.h"
#include	"srv.h"

static void	connection(t_srv *this, t_client *client)
{
  client_out(client, ":%s %d %s: Welcome to the Internet Relay Network " \
	     "%s!%s@%s\r\n", this->hostname, RPL_WELCOME, client->nickname,
	     client->nickname, client->name, socket_ip(client_socket(client)));
  client_out(client, ":%s %d %s: Your host is %s, running version 1.0\r\n",
	     this->hostname, RPL_YOURHOST, client->nickname, this->hostname);
  client_out(client, ":%s %d %s: This server was created %s\r\n",
	     this->hostname, RPL_CREATED, client->nickname, this->created);
  client_out(client, ":%s %d %s: %s 1.0 DOQRSZaghilopswz CFILMPQSbcefgijklmn" \
	     "opqrstvz bkloveqjfI\r\n", this->hostname, RPL_MYINFO,
	     client->nickname, this->hostname);
}

static void	motd(t_srv *this, t_client *client)
{
  client_out(client, ":%s %d %s: %s Message of the day -\r\n", this->hostname,
	     RPL_MOTDSTART, client->nickname, this->hostname);
  client_out(client, ":%s %d %s:- Profitez ;)\r\n", this->hostname,
	     RPL_MOTD, client->nickname);
  client_out(client, ":%s %d %s: End of /MOTD command.\r\n", this->hostname,
	     RPL_ENDOFMOTD, client->nickname);
}

void		srv_auth(t_srv *this, t_client *client)
{
  connection(this, client);
  motd(this, client);
  client->authenticated = TRUE;
}
