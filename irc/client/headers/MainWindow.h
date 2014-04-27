/*
** MainWindow.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Wed Apr 23 18:36:34 2014 raphael defreitas
** Last update Sun Apr 27 01:41:40 2014 raphael defreitas
*/

#ifndef		MAIN_WINDOW_H_
# define	MAIN_WINDOW_H_

# include	<gtkmm/notebook.h>
# include	<gtkmm/widget.h>
# include	<gtkmm/window.h>
# include	<map>
# include	<string>

# include	"ITab.h"
# include	"NetworkWorker.h"
# include	"ResponseHandler.h"

class MainWindow : public Gtk::Window
{
 public:
  MainWindow();
  ~MainWindow();
  
  void addTab(ITab *tab);
  ITab *getTab(const std::string& title);
  ITab *getCurrentTab();

  void log(const std::string& str);
  NetworkWorker& worker();
  
  void onCommandSent(const std::string& command);
  void onCommandReceived(const std::string& command);

  typedef bool (MainWindow::*CommandHandler)(const std::string&, const std::string&);
 private:
  void dispatch();

  NetworkWorker m_worker;
  std::map<std::string, ITab*> m_tabs;
  Gtk::Notebook m_notebook;

  std::string m_nickname;

  ResponseHandler m_response_handler;

  std::map<std::string, CommandHandler> m_command_handlers;
  void commandRawUsage();
  void commandConnectUsage();
  void commandJoinUsage();
  void commandNickUsage();
  bool commandRaw(const std::string& command, const std::string& args);
  bool commandConnect(const std::string& command, const std::string& args);
  bool commandJoin(const std::string& command, const std::string& args);  
  bool commandNick(const std::string& command, const std::string& args);  
  bool commandMsg(const std::string& command, const std::string& args);  
  bool commandPart(const std::string& command, const std::string& args);  
  bool commandList(const std::string& command, const std::string& args);  
  bool commandUsers(const std::string& command, const std::string& args);  
};

#endif /* !MAIN_WINDOW_H_ */
