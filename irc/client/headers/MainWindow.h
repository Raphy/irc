/*
** MainWindow.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
** 
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
** 
** Started on  Wed Apr 23 18:36:34 2014 raphael defreitas
** Last update Fri Apr 25 10:21:11 2014 raphael defreitas
*/

#ifndef		MAIN_WINDOW_H_
# define	MAIN_WINDOW_H_

# include	<gtkmm/notebook.h>
# include	<gtkmm/widget.h>
# include	<gtkmm/window.h>
# include	<glibmm/threads.h>
# include	<map>
# include	<string>

# include	"ITab.h"

class MainWindow : public Gtk::Window
{
 public:
  MainWindow();
  ~MainWindow();
  
  void addTab(ITab *tab);

  void dispatch();

 private:
  std::map<std::string, ITab*> m_tabs;
  Gtk::Notebook m_notebook;
};

#endif /* !MAIN_WINDOW_H_ */
