/*
** ITab.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Fri Apr 25 10:21:24 2014 raphael defreitas
** Last update Fri Apr 25 10:34:24 2014 raphael defreitas
*/

#ifndef		ITAB_H_
# define	ITAB_H_

# include	<gtkmm/widget.h>
# include	<string>

class ITab
{
 public:
  virtual ~ITab() {};

  virtual Gtk::Widget* getWidget() = 0;
  virtual const std::string& getTitle() const = 0;
  virtual void appendText(const std::string& str) = 0;
};

#endif /* !ITAB_H_*/
