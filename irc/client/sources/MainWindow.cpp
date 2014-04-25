//
// MainWindow.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:36:57 2014 raphael defreitas
// Last update Fri Apr 25 10:36:37 2014 raphael defreitas
//

#include	<gtkmm/notebook.h>
#include	<gtkmm/widget.h>
#include	<iostream>
#include	<map>
#include	<string>

#include	"ITab.h"
#include	"MainWindow.h"

MainWindow::MainWindow()
{
  set_title("myirc - Raphy & Bart");
  set_default_size(800, 600);
  add(m_notebook);
}

MainWindow::~MainWindow()
{
  
}

void MainWindow::addTab(ITab *tab)
{
  m_tabs[tab->getTitle()] = tab;
  m_notebook.append_page(*tab->getWidget(), tab->getTitle());
}

void MainWindow::dispatch()
{
  //m_tabs.begin()->second->appendText("Dispatch");
}
