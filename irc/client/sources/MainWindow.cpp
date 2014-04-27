//
// MainWindow.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:36:57 2014 raphael defreitas
// Last update Sun Apr 27 02:21:12 2014 raphael defreitas
//

#include	<stdlib.h>
#include	<cstring>
#include	<glibmm/threads.h>
#include	<gtkmm/notebook.h>
#include	<gtkmm/widget.h>
#include	<iostream>
#include	<map>
#include	<string>

#include	"ChannelTab.h"
#include	"GeneralTab.h"
#include	"ITab.h"
#include	"MainWindow.h"
#include	"NetworkWorker.h"
#include	"utils.h"
#include	"protocol.h"

MainWindow::MainWindow() :
  m_nickname(), m_response_handler(this)
{
  set_title("myirc - Raphy & Bart");
  set_default_size(800, 600);
  add(m_notebook);

  m_worker.dispatcher().connect(sigc::mem_fun(*this, &MainWindow::dispatch));

  m_command_handlers["/raw"] = &MainWindow::commandRaw;
  m_command_handlers["/server"] = &MainWindow::commandConnect;
  m_command_handlers["/join"] = &MainWindow::commandJoin;
  m_command_handlers["/nick"] = &MainWindow::commandNick;
  m_command_handlers["/part"] = &MainWindow::commandPart;
  m_command_handlers["/msg"] = &MainWindow::commandMsg;
  m_command_handlers["/users"] = &MainWindow::commandUsers;

  m_nickname = "Newbie1337";
  
}

MainWindow::~MainWindow()
{
  try
    {
      //m_worker.stop();
    }
  catch(Glib::Threads::Thread::Exit& ex)
    {}
}

void MainWindow::addTab(ITab *tab)
{
  tab->signal_command_sent().connect(sigc::mem_fun(*this, &MainWindow::onCommandSent));
  m_tabs[tab->getTitle()] = tab;
  m_notebook.append_page(*tab->getWidget(), tab->getTitle());
  m_notebook.show_all();
}

ITab* MainWindow::getTab(const std::string& title)
{
  std::map<std::string, ITab*>::iterator it = m_tabs.find(title);
  if (it == m_tabs.end())
    return (NULL);
  return it->second;
}

NetworkWorker& MainWindow::worker()
{
  return m_worker;
}

ITab* MainWindow::getCurrentTab()
{
  Gtk::Widget* widget = m_notebook.get_nth_page(m_notebook.get_current_page());
  if (widget)
    {
      std::map<std::string, ITab*>::iterator it;
      bool done = false;
      for (it = m_tabs.begin(); !done && it != m_tabs.end(); ++it)
	if (it->second->getWidget() == widget)
	  return it->second;
    }
  return (NULL);
}

void MainWindow::log(const std::string& str)
{
  ITab* tab = getCurrentTab();
  if (tab)
    tab->appendText(str);
}

void MainWindow::dispatch()
{
  if (!m_worker.getData().empty())
    {
      while (!m_worker.getData().empty())
	{
	  std::string data = m_worker.getData().front();
	  m_worker.getData().pop();
	  onCommandReceived(data);
	}
    }
}

void MainWindow::commandConnectUsage()
{
  log("Usage: /server <host> [port]");
}

void MainWindow::commandJoinUsage()
{
  log("Usage: /join <channel>");
}

void MainWindow::commandNickUsage()
{
  log("Usage: /nick <nickname>");
}

bool MainWindow::commandNick(const std::string& cmd, const std::string& args)
{
  if (cmd != "/nick")
    return false;
  char **tokens = strtoarr(args.c_str(), " ");
  if (tokens)
    {
      if (!tokens[0])
	{
	  commandNickUsage();
	  return true;
	}
	  m_nickname = tokens[0];
	  m_worker.putOut("NICK %s\r\n", tokens[0]);
      free(tokens);
    }
  return true;
}

bool MainWindow::commandMsg(const std::string& cmd, const std::string& args)
{
  if (cmd != "/msg")
    return false;
  std::string args2(args);
  std::string to;
  std::string msg;
  size_t pos = args2.find(" ");
  if (pos != std::string::npos)
    {
      to = args2.substr(0, pos);
      args2 = args2.substr(pos + 1);
    }
  if (!args2.empty())
    {
      GeneralTab* tab = new GeneralTab(to);
      addTab(tab);
      m_worker.putOut("PRIVMSG %s :%s\r\n", to.c_str(), args2.c_str());
    }
  return true;
}

bool MainWindow::commandJoin(const std::string& cmd, const std::string& args)
{
  if (cmd != "/join")
    return false;
  
  char **tokens = strtoarr(args.c_str(), " ");
  if (!tokens[0])
    {
      this->commandJoinUsage();
      free(tokens);
      return true;
    }
  m_worker.putOut("JOIN %s\r\n", tokens[0]);
  free(tokens);
  
  return true;
}

bool MainWindow::commandRaw(const std::string& cmd, const std::string& args)
{
  if (cmd != "/raw")
    return false;

  if (args != "")
    m_worker.putOut("%s\r\n", args.c_str());

  return true;
}

bool MainWindow::commandPart(const std::string& cmd, const std::string& args)
{
  if (cmd != "/part")
    return false;
  if (getCurrentTab()->getTitle()[0] != '#')
    return true;
  m_worker.putOut("PART %s", getCurrentTab()->getTitle().c_str());
  if (!args.empty())
    m_worker.putOut(" :%s", args.c_str());
  m_worker.putOut("\r\n");
  return true;
}

bool MainWindow::commandUsers(const std::string& cmd, const std::string& args)
{
  if (cmd != "/users")
    return false;
  ITab* tab = getCurrentTab();
  if (tab)
    {
      if (tab->getTitle() != "General" && tab->getTitle()[0] == '#')
	{
	  m_worker.putOut("NAMES %s\r\n", tab->getTitle().c_str());
	  ((ChannelTab*)tab)->clearUsers();
	}
    }
  return true;
}

bool MainWindow::commandConnect(const std::string& cmd, const std::string& args)
{
  if (cmd != "/server")
    return false;
  
  char **tokens = strtoarr(args.c_str(), " ");
  if (!tokens[0])
    {
      this->commandConnectUsage();
      free(tokens);
      return true;
    }

  if (!m_worker.connect(tokens[0], tokens[1] ? atoi(tokens[1]) : 6667, m_nickname))
    log("Impossible to connect to the server");

  free(tokens);
  return true;
}

void MainWindow::onCommandSent(const std::string& fcmd)
{
  std::map<std::string, CommandHandler>::iterator it;
  size_t pos = fcmd.find(" ");
  std::string cmd = pos == std::string::npos ? fcmd : fcmd.substr(0, pos);
  std::string args = pos == std::string::npos ? "" : fcmd.substr(pos + 1);

  bool done = false;
  for (it = m_command_handlers.begin(); !done && it != m_command_handlers.end(); ++it) {
    if ((this->*(it->second))(cmd, args))
      done = true;
  }
  if (!done && fcmd[0] == '/')
    log("The command « " + cmd + " » not exists");
  else if (!done && fcmd[0] != '/')
    {
      ITab* tab = getCurrentTab();
      if (tab && tab->getTitle() != "General")
	{
	  m_worker.putOut("PRIVMSG %s :%s\r\n", tab->getTitle().c_str(), fcmd.c_str());
	  tab->appendText("<" + m_nickname + "> " + fcmd);
	}
    }
    
}

void MainWindow::onCommandReceived(const std::string& fcmd)
{
  m_response_handler.handle(fcmd);
}
