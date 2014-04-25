/*
** GeneralTab.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Wed Apr 23 18:36:26 2014 raphael defreitas
** Last update Fri Apr 25 14:04:58 2014 raphael defreitas
*/

#ifndef		GENERALTAB_H_
# define	GENERALTAB_H_

# include	<gdk/gdk.h>
# include	<glibmm/threads.h>
# include	<gtkmm/box.h>
# include	<gtkmm/button.h>
# include	<gtkmm/entry.h>
# include	<gtkmm/scrolledwindow.h>
# include	<gtkmm/textview.h>
# include	<sigc++/sigc++.h>
# include	<string>

# include	"ITab.h"

class GeneralTab : public Gtk::VBox, public ITab
{
 public:
  GeneralTab(const std::string& title);
  ~GeneralTab();

  void appendText(const std::string& text);

  Gtk::Widget* getWidget();
  const std::string& getTitle() const;
  sigc::signal<void, const std::string&>& signal_command_sent();

 private:
  bool onKeyReleased(GdkEventKey* event);
  void sendMessage();

  std::string m_title;

  Gtk::TextView m_text_view;
  Gtk::ScrolledWindow m_text_view_container;
  Gtk::HBox m_cmd_container;
  Gtk::Entry m_cmd_entry;
  Gtk::Button m_send_button;

  sigc::signal<void, const std::string&> m_signal_command_sent;
};

#endif /* !GENERALTAB_H_*/
