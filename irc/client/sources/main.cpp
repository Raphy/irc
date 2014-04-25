//
// main.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:36:42 2014 raphael defreitas
// Last update Fri Apr 25 14:38:41 2014 raphael defreitas
//

#include	<cstdlib>
#include	<gtkmm/main.h>
#include	<iostream>
#include	<sigc++/sigc++.h>
#include	<string>

#include	"ChannelTab.h"
#include	"GeneralTab.h"
#include	"MainWindow.h"
#include	"NetworkWorker.h"
#include	"network.h"
#include	"utils.h"

void		dispatch()
{
  //std::cout << "Dispatch" << std::endl;
}

int		main(int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
  MainWindow main_window;
  GeneralTab *general_tab = new GeneralTab("General");

  general_tab->signal_command_sent().connect(sigc::mem_fun(main_window, &MainWindow::onCommandSent));
  main_window.addTab(general_tab);
  main_window.show_all();

  app->run(main_window);

  return (EXIT_SUCCESS);
}
