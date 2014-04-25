/*
** ChannelTab.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Wed Apr 23 18:36:26 2014 raphael defreitas
** Last update Thu Apr 24 13:11:02 2014 raphael defreitas
*/

#ifndef		CHANNELTAB_H_
# define	CHANNELTAB_H_

# include	<gdk/gdk.h>
# include	<gtkmm/box.h>
# include	<gtkmm/button.h>
# include	<gtkmm/entry.h>
# include	<gtkmm/textview.h>
# include	<gtkmm/scrolledwindow.h>

class ChannelTab : public Gtk::HBox
{
 public:
  ChannelTab();
  ~ChannelTab();

  void appendText(const Glib::ustring& text);

 private:
  bool onKeyReleased(GdkEventKey* event);
  void sendMessage();

  Gtk::Button m_useless;
  Gtk::VBox m_chat_container;
  Gtk::ScrolledWindow m_text_view_container;
  Gtk::TextView m_text_view;
  Gtk::HBox m_cmd_container;
  Gtk::Entry m_cmd_entry;
  Gtk::Button m_send_button;
};

#endif /* !GENERALTAB_H_*/
