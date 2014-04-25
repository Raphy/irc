//
// NetworkWorker.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Thu Apr 24 13:23:39 2014 raphael defreitas
// Last update Fri Apr 25 18:49:47 2014 raphael defreitas
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
  m_thread(NULL)
{
  network_ctor(&m_network);
}

NetworkWorker::~NetworkWorker()
{
  network_dtor(&m_network);
}

void NetworkWorker::start()
{
  if (!m_thread)
    m_thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &NetworkWorker::run));
}

void NetworkWorker::stop()
{
  {    
    Glib::Threads::Mutex::Lock lock(m_mutex);    
    m_stop = true;
  }
  throw Glib::Threads::Thread::Exit();
}

bool NetworkWorker::connect(const std::string& host, int port)
{
  if (m_thread)
    return true;
  /*putOut("NICK newbie%d\r\nUSER myIrc Dom %s :myirc of Raphy & Bart\r\n",
    rand() % 1000, host.c_str());*/
  if (network_connect(&m_network, host.c_str(), port) == RET_FAILURE)
    return false;
  this->start();
  return true;
}

Glib::Dispatcher& NetworkWorker::dispatcher()
{
  return m_dispatcher;
}

bool NetworkWorker::stopped() const
{
  return m_stop;
}

void NetworkWorker::run()
{
  while (true)
    {
      {
	Glib::Threads::Mutex::Lock lock(m_mutex);
	if (m_stop)
	  break;
	network_set_fds(&m_network);
	m_network.tv.tv_sec = 3;
	m_network.tv.tv_usec = 0;	
      }
      std::cout << "Select.." << std::endl;
      network_select(&m_network);
      {
	Glib::Threads::Mutex::Lock lock(m_mutex);
	network_recv(&m_network);
	network_send(&m_network);
	m_stop = m_network.disconnected;
      }
      m_dispatcher.emit();
    }
}

bool NetworkWorker::hasInData()
{
  return strstr(m_network.buf_in, "\r\n") != NULL;
}

std::string* NetworkWorker::getInData()
{
  std::string* data = new std::string(m_network.buf_in);
  m_network.buf_in[0] = 0;
  return data;
}

void NetworkWorker::putOut(const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  network_put_out(&m_network, format, ap);
  va_end(ap);
}
