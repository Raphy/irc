//
// ResponseHandler.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Apr 26 17:17:51 2014 raphael defreitas
// Last update Sun Apr 27 02:51:10 2014 raphael defreitas
//

#include	<cstdlib>
#include	<iostream>

#include	"ChannelTab.h"
#include	"GeneralTab.h"
#include	"ResponseHandler.h"
#include	"MainWindow.h"
#include	"protocol.h"

ResponseHandler::ResponseHandler(MainWindow* caller) :
  m_caller(caller)
{
  m_handlers["JOIN"] = &ResponseHandler::responseJoin;
  m_handlers["PART"] = &ResponseHandler::responsePart;
  m_handlers["PING"] = &ResponseHandler::responsePing;
  m_handlers["PRIVMSG"] = &ResponseHandler::responsePrivMsg;
  m_handlers["QUIT"] = &ResponseHandler::responseQuit;
  m_handlers["NICK"] = &ResponseHandler::responseNick;
  m_handlers["001"] = &ResponseHandler::response001;
  m_handlers["353"] = &ResponseHandler::response353;
  m_handlers["372"] = &ResponseHandler::response372;
  m_handlers["375"] = &ResponseHandler::response375;
  m_handlers["376"] = &ResponseHandler::response376;
}

ResponseHandler::~ResponseHandler()
{

}

bool ResponseHandler::responseJoin(int size, char **tokens)
{
  if (size != 3)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "JOIN")
    return false;
  std::string who(tokens[0] + 1);
  std::string channel(tokens[2]);
  size_t pos = who.find("!");
  if (pos != std::string::npos)
    who = who.substr(0, pos);
  ITab* tab = NULL;
  if (!(tab = m_caller->getTab(channel)))
    {
      if ((tab = new ChannelTab(channel)))
	m_caller->addTab(tab);
    }
  if (tab)
    tab->appendText(who + " has joined the channel.");
  return true;
}

bool ResponseHandler::responsePart(int size, char **tokens)
{
  if (size < 3)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "PART")
    return false;
  std::string who(tokens[0] + 1);
  std::string channel(tokens[2]);
  std::string reason(tokens[3] ? tokens[3] : "Leaving");
  size_t pos = who.find("!");
  if (pos != std::string::npos)
    who = who.substr(0, pos);
  ITab* tab = NULL;
  if ((tab = m_caller->getTab(channel)))
    tab->appendText(who + " has left the channel. (" + reason + ")");
  return true;
}

bool ResponseHandler::responseNick(int size, char **tokens)
{
  if (size != 3)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "NICK")
    return false;
  std::string who(tokens[0] + 1);
  std::string nick(tokens[2]);
  size_t pos = who.find("!");
  if (pos != std::string::npos)
    who = who.substr(0, pos);
  m_caller->log(who + " has is now knwon as " + nick);
  return true;
}

bool ResponseHandler::responsePing(int size, char **tokens)
{
  if (size < 1)
    return false;
  std::string cmd(tokens[0]);
  if (cmd != "PING")
    return false;
  m_caller->worker().putOut("PONG ");
  for (int i = 1; tokens[i]; i++)
    m_caller->worker().putOut("%s ", tokens[i]);
  m_caller->worker().putOut("\r\n");
  return true;
}

bool ResponseHandler::responsePrivMsg(int size, char **tokens)
{
  if (size != 4)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "PRIVMSG")
    return false;
  std::string who(tokens[0] + 1);
  std::string from(tokens[2]);
  std::string msg(tokens[3]);
  size_t pos = who.find("!");
  if (pos != std::string::npos)
    who = who.substr(0, pos);
  ITab* tab = NULL;
  if (!(tab = m_caller->getTab(from[0] == '#' ? from : who)))
    {
      if (from[0] == '#' && (tab = new ChannelTab(from)))
	m_caller->addTab(tab);
      else if ((tab = new GeneralTab(who)))
	m_caller->addTab(tab);

    }
  if (tab)
    tab->appendText("<" + who + "> " + msg);
  return true;
}

bool ResponseHandler::responseQuit(int size, char **tokens)
{
  if (size < 2)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "QUIT")
    return false;
  std::string who(tokens[0] + 1);
  std::string reason(tokens[2] ? tokens[2] : "Quit");
  size_t pos = who.find("!");
  if (pos != std::string::npos)
    who = who.substr(0, pos);
  ITab* tab = NULL;
  if ((tab = m_caller->getTab(who)))
    tab->appendText(who + " has quit (Reason: " + reason + ")");
  /* Todo: Notify each channel ... */
  m_caller->log(who + " has quit (" + reason + ")");
  return true;
}

bool ResponseHandler::response001(int size, char **tokens)
{
  if (size != 4)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "001")
    return false;
  m_hostname = tokens[0];
  return true;
}

bool ResponseHandler::response353(int size, char **tokens)
{
  if (size != 6)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "353")
    return false;
  std::string users(tokens[5]);
  std::string channel(tokens[4]);
  ITab* tab = NULL;
  if ((tab = m_caller->getTab(channel)))
    {
      ChannelTab *ct = (ChannelTab*)tab;      
      size_t pos = std::string::npos;      
      while ((pos = users.find(" ")) && pos != std::string::npos)
	{
	  std::string user = users.substr(0, pos);
	  users = users.substr(pos + 1);
	  ct->addUser(user);
	}
      ct->addUser(users);
    }
  return true;
}

bool ResponseHandler::response372(int size, char **tokens)
{
  if (size != 4)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "372")
    return false;
  std::string motd(tokens[3]);
  ITab* general_tab = m_caller->getTab("General");
  general_tab->appendText(motd);
  return true;
}

bool ResponseHandler::response375(int size, char **tokens)
{
  if (size != 4)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "375")
    return false;
  std::string motd(tokens[3]);
  ITab* general_tab = m_caller->getTab("General");
  general_tab->appendText(motd);
  return true;
}

bool ResponseHandler::response376(int size, char **tokens)
{
  if (size != 4)
    return false;
  std::string cmd(tokens[1]);
  if (cmd != "376")
    return false;
  std::string motd(tokens[3]);
  ITab* general_tab = m_caller->getTab("General");
  general_tab->appendText(motd);
  return true;
}


void ResponseHandler::handle(const std::string& response)
{
  char **tokens = protocol_parse(response.c_str());
  if (tokens)
    {
      int size = 0;
      for (size = 0; tokens[size]; size++)
	std::cout << "[" << tokens[size] << "] ";
      std::cout << " - size: " << size << std::endl;
      std::map<std::string, Handler>::iterator it;
      bool done = false;
      for (it = m_handlers.begin(); !done && it != m_handlers.end(); ++it) {
	if ((this->*(it->second))(size, tokens))
	  done = true;
      }
      free(tokens);
    }
}
