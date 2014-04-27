/*
** ResponseHandler.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sat Apr 26 17:19:30 2014 raphael defreitas
** Last update Sun Apr 27 00:59:10 2014 raphael defreitas
*/

#ifndef		RESPONSEHANDLER_H_
# define	RESPONSEHANDLER_H_

# include	<string>
# include	<map>

class MainWindow;

class ResponseHandler
{
 public:
  ResponseHandler(MainWindow* caller);
  ~ResponseHandler();
 
  void handle(const std::string& response);
  typedef bool (ResponseHandler::*Handler)(int, char **);
 private:
  MainWindow* m_caller;
  std::string m_hostname;  
  bool responseJoin(int size, char **tokens);
  bool responsePart(int size, char **tokens);
  bool responseNick(int size, char **tokens);
  bool responsePing(int size, char **tokens);
  bool responsePrivMsg(int size, char **tokens);
  bool responseQuit(int size, char **tokens);
  bool response001(int size, char **tokens);
  bool response353(int size, char **tokens);
  bool response372(int size, char **tokens);
  bool response375(int size, char **tokens);
  bool response376(int size, char **tokens);
  std::map<std::string, Handler> m_handlers;
};

#endif /* !RESPONSEHANDLER_H_*/
