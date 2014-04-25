/*
** NetworkWorker.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Thu Apr 24 13:19:15 2014 raphael defreitas
** Last update Fri Apr 25 10:40:12 2014 raphael defreitas
*/

#ifndef		NETWORKWORKER_H_
# define	NETWORKWORKER_H_

# include	<sigc++/sigc++.h>
# include	<glibmm/dispatcher.h>
# include	<glibmm/threads.h>
# include	<string>

# include	"network.h"

class NetworkWorker
{
 public:
  NetworkWorker();
  ~NetworkWorker();

  void start();
  void stop();

  Glib::Dispatcher& dispatcher();

 private:
  void run();

  sigc::signal<void, Glib::ustring&> m_signal_data_received;

  Glib::Threads::Thread* m_thread;
  Glib::Threads::Mutex m_mutex;
  Glib::Dispatcher m_dispatcher;

  t_network m_network;
  bool m_stop;
};

#endif /* !NETWORKWORKER_H_*/
