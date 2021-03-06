/*
** cmd.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/server/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sat Apr 19 22:03:18 2014 raphael defreitas
** Last update Sun Apr 27 21:50:16 2014 raphael defreitas
*/

#ifndef		CMD_H_
# define	CMD_H_

# include	"defs.h"
# include	"client.h"

# define	CMD_NBR		11

typedef	struct
{
  void		*data;
  t_bool	(*handler)();
}		t_cmd;

t_cmd		*cmd_new(void *data, t_bool (*handler)());
void		cmd_delete(t_cmd *this);

t_bool		cmd_user(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_nick(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_ping(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_pong(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_join(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_privmsg(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_quit(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_who(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_whois(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_part(t_cmd *this, t_client *client, char **tokens);
t_bool		cmd_names(t_cmd *this, t_client *client, char **tokens);

#endif /* !CMD_H_*/
