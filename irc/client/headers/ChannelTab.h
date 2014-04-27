/*
** ChannelTab.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Wed Apr 23 18:36:26 2014 raphael defreitas
** Last update Sun Apr 27 02:17:15 2014 raphael defreitas
*/

#ifndef		CHANNELTAB_H_
# define	CHANNELTAB_H_

# include	<gdk/gdk.h>
# include	<gtkmm/box.h>
# include	<gtkmm/button.h>
# include	<gtkmm/entry.h>
# include	<gtkmm/label.h>
# include	<gtkmm/listbox.h>
# include	<gtkmm/listboxrow.h>
# include	<gtkmm/textview.h>
# include	<gtkmm/scrolledwindow.h>
# include	<string>
# include	<map>

# include	"ITab.h"

class ChannelTab : public Gtk::HBox, public ITab
{
 public:
  ChannelTab(const std::string& title);
  ~ChannelTab();

  void appendText(const std::string& text);

  Gtk::Widget* getWidget();
  const std::string& getTitle() const;
  sigc::signal<void, const std::string&>& signal_command_sent();
  
  void addUser(const std::string& user);
  void deleteUser(const std::string& user);
  void clearUsers();

 private:
  bool onKeyReleased(GdkEventKey* event);
  void sendMessage();

  std::string m_title;

  Gtk::ListBox m_users_box;
  Gtk::ScrolledWindow m_users_container;
  Gtk::VBox m_chat_container;
  Gtk::ScrolledWindow m_text_view_container;
  Gtk::TextView m_text_view;
  Gtk::HBox m_cmd_container;
  Gtk::Entry m_cmd_entry;
  Gtk::Button m_send_button;

  sigc::signal<void, const std::string&> m_signal_command_sent;
  std::map<std::string, Gtk::Label*> m_users;
};


#endif /* !GENERALTAB_H_*/
