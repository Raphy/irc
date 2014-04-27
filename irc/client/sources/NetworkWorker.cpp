//
// NetworkWorker.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Thu Apr 24 13:23:39 2014 raphael defreitas
// Last update Sun Apr 27 00:11:14 2014 raphael defreitas
//

#include	<cstdarg>
#include	<cstdlib>
#include	<cstring>
#include	<glibmm/timer.h>
#include	<glibmm/threads.h>
#include	<iostream>
#include	<sigc++/sigc++.h>

#include	"network.h"
#include	"NetworkWorker.h"
#include	"utils.h"

NetworkWorker::NetworkWorker() :
  m_thread(NULL), m_stop(true)
{
  network_ctor(&m_network);
  m_stop = false;
}

NetworkWorker::~NetworkWorker()
{
  network_dtor(&m_network);
}

void NetworkWorker::start()
{
  if (!m_thread)
    {
      m_stop = false;
      m_thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &NetworkWorker::run));
    }
}

bool NetworkWorker::connect(const std::string& host, int port, const std::string& nick)
{
  {
    Glib::Threads::Mutex::Lock lock(m_mutex);
    if (!m_network.disconnected || network_connect(&m_network, host.c_str(), port) == RET_FAILURE)
      return false;
    this->start();
  }
  putOut("NICK %s\r\nUSER %s %s %s :myirc of Raphy & Bart\r\n",
	 nick.c_str(), nick.c_str(), nick.c_str(), host.c_str());    
  return true;
}

Glib::Dispatcher& NetworkWorker::dispatcher()
{
  {
    Glib::Threads::Mutex::Lock lock(m_mutex);
    return m_dispatcher;
  }
}

void NetworkWorker::run()
{
  while (true)
    {
      {
	Glib::Threads::Mutex::Lock lock(m_mutex);
	if (m_network.disconnected)
	  break;
	network_set_fds(&m_network);
	m_network.tv.tv_sec = 1;
	m_network.tv.tv_usec = 0;	
      }
      network_select(&m_network);
      {
	Glib::Threads::Mutex::Lock lock(m_mutex);
	network_recv(&m_network);
	network_send(&m_network);
	m_stop = m_network.disconnected;
	if (m_network.has_data_in)
	  {
	    std::string data(m_network.buf_in);
	    m_network.buf_in[0] = 0;
	    m_network.has_data_in = FALSE;
	    int pos;
	    while ((pos = data.find("\r\n")) != std::string::npos)
	      {
		m_in_data.push(data.substr(0, pos));
		data = data.substr(pos + 2);
	      }
	    strcpy(m_network.buf_in, data.c_str());
	    strcat(m_network.buf_in, "\0");
	    if (strlen(m_network.buf_in) > 0)
	      m_network.has_data_in = TRUE;
	  }	
      }
      {
	Glib::Threads::Mutex::Lock lock(m_mutex);
	m_dispatcher.emit();
      }
    }
}

void NetworkWorker::putOut(const char* format, ...)
{
  {
    Glib::Threads::Mutex::Lock lock(m_mutex);
    va_list ap;
    va_start(ap, format);
    network_put_out(&m_network, format, ap);
    va_end(ap);
  }
}

std::queue<std::string>& NetworkWorker::getData()
{
  {
    Glib::Threads::Mutex::Lock lock(m_mutex);
    return m_in_data;
  }
}
