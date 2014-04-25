//
// MainWindow.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:36:57 2014 raphael defreitas
// Last update Fri Apr 25 15:33:50 2014 raphael defreitas
//

#include	<cstring>
#include	<glibmm/threads.h>
#include	<gtkmm/notebook.h>
#include	<gtkmm/widget.h>
#include	<iostream>
#include	<map>
#include	<string>

#include	"ITab.h"
#include	"MainWindow.h"
#include	"NetworkWorker.h"
#include	"utils.h"

MainWindow::MainWindow()
{
  set_title("myirc - Raphy & Bart");
  set_default_size(800, 600);
  add(m_notebook);

  m_worker.dispatcher().connect(sigc::mem_fun(*this, &MainWindow::dispatch));
}

MainWindow::~MainWindow()
{
  try
    {
      m_worker.stop();
    }
  catch(Glib::Threads::Thread::Exit& ex)
    {}
}

void MainWindow::addTab(ITab *tab)
{
  m_tabs[tab->getTitle()] = tab;
  m_notebook.append_page(*tab->getWidget(), tab->getTitle());
}

void MainWindow::dispatch()
{
  if (m_worker.hasInData())
    {
      std::string* data = m_worker.getInData();
      m_tabs.begin()->second->appendText(*data);
      delete data;
    }
}

void MainWindow::onCommandSent(const std::string& command)
{
  m_tabs.begin()->second->appendText(command);
  char **arr = strtoarr(command.c_str(), " ");
  std::cout << "Tokens: ";
  for (int i = 0; arr[i]; i++)
    std::cout << "[" << arr[i] << "] ";
  std::cout << std::endl;

  if (arr[0])
    {
      if (strcmp(arr[0], "/connect") == 0)
	{
	  if (arr[1])
	    {
	      if (!m_worker.connect(arr[1], arr[2] ? atoi(arr[1]) : 6667))
		std::cout << "echec" << std::endl;
	    }
	  return ;
	}
    }
  m_worker.putOut("%s\r\n", command.c_str());
}

