//
// main.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:36:42 2014 raphael defreitas
// Last update Fri Apr 25 11:48:41 2014 raphael defreitas
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
  Gtk::Main	app(Gtk::Main(argc, argv));
  MainWindow	main_window;
  GeneralTab	*general_tab = new GeneralTab("General");
  NetworkWorker	network_worker;
  t_network	net;

  network_ctor(&net);

  main_window.addTab(general_tab);
  main_window.show_all();

  network_worker.dispatcher().connect(sigc::ptr_fun(&dispatch));
  network_worker.dispatcher().connect(sigc::mem_fun(main_window, &MainWindow::dispatch));

  /*
    network_worker.signal_data_received().connect(sigc::ptr_fun(&data_recv));
    network_worker.signal_data_received().connect(sigc::mem_fun(general_tab, &GeneralTab::appendText));
  */
  
  network_worker.start();
  Gtk::Main::run(main_window);
  return (EXIT_SUCCESS);
}
