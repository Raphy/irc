//
// NetworkWorker.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Thu Apr 24 13:23:39 2014 raphael defreitas
// Last update Fri Apr 25 10:43:57 2014 raphael defreitas
//

#include	<cstdlib>
#include	<glibmm/timer.h>
#include	<glibmm/threads.h>
#include	<iostream>
#include	<sigc++/sigc++.h>

#include	"network.h"
#include	"NetworkWorker.h"

NetworkWorker::NetworkWorker() :
  m_thread(NULL), m_stop(false)
{
  //network_ctor(&m_network);
}

NetworkWorker::~NetworkWorker()
{
  stop();
  //network_dtor(&m_network);
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

  if (m_thread)
    m_thread->join();
}

Glib::Dispatcher& NetworkWorker::dispatcher()
{
  return m_dispatcher;
}

void NetworkWorker::run()
{
  while (true)
    {
      {
	Glib::Threads::Mutex::Lock lock(m_mutex);
	if (m_stop)
	  break;
      }
      Glib::usleep(5000);
      //std::cout << "Thread" << std::endl;
      Glib::ustring* str = new Glib::ustring("MyData");
      m_dispatcher.emit();
    }
}
