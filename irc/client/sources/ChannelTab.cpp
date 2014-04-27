//
// ChannelTab.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:37:33 2014 raphael defreitas
// Last update Sun Apr 27 02:30:43 2014 raphael defreitas
//

#include	<iostream>
#include	<string>

#include	"ChannelTab.h"

ChannelTab::ChannelTab(const std::string& title) :
  m_title(title), m_send_button("Send")
{
  m_users_container.add(m_users_box);
  pack_start(m_chat_container);
  pack_end(m_users_container);
  m_text_view_container.add(m_text_view);
  m_chat_container.pack_start(m_text_view_container);
  m_chat_container.pack_end(m_cmd_container, false, false);
  m_cmd_container.pack_start(m_cmd_entry);
  m_cmd_container.pack_end(m_send_button, false, false);

  m_text_view.set_editable(false);
  m_text_view.set_wrap_mode(Gtk::WRAP_WORD);
  
  m_cmd_entry.signal_key_release_event().connect(sigc::mem_fun(*this, &ChannelTab::onKeyReleased));
  this->m_send_button.signal_clicked().connect(sigc::mem_fun(*this, &ChannelTab::sendMessage));
}

ChannelTab::~ChannelTab()
{

}

void ChannelTab::addUser(const std::string& user)
{
  m_users[user] = new Gtk::Label(user);
  m_users_box.append(*m_users[user]);
  m_users_box.show_all();
}

void ChannelTab::deleteUser(const std::string& user)
{
  if (m_users.find(user) != m_users.end())
    {
      m_users.erase(user);
    }
}

void ChannelTab::clearUsers()
{
  Gtk::ListBoxRow* row;
  int i = 0;
  while ((row = m_users_box.get_row_at_index(i)))
    {
      row->remove();
      m_users_box.remove(*row);
      i++;
    }
}

void ChannelTab::appendText(const std::string& text)
{
  std::string final_text = text + "\n";
  Glib::RefPtr<Gtk::TextBuffer> buffer = m_text_view.get_buffer();
  Gtk::TextBuffer::iterator it = buffer->end();
  buffer->insert(it, final_text);  
  Glib::RefPtr<Gtk::Adjustment> adj = m_text_view.get_vadjustment();
  adj->set_value(adj->get_upper() - adj->get_page_size());
}

Gtk::Widget* ChannelTab::getWidget()
{
  return this;
}

sigc::signal<void, const std::string&>& ChannelTab::signal_command_sent()
{
  return m_signal_command_sent;
}

const std::string& ChannelTab::getTitle() const
{
  return m_title;
}

void ChannelTab::sendMessage()
{
  if (m_cmd_entry.get_text().length() > 0)
    {
      m_signal_command_sent.emit(m_cmd_entry.get_text());
      m_cmd_entry.set_text("");
    }
}

bool ChannelTab::onKeyReleased(GdkEventKey* event)
{
  if (event->keyval == 65293 || event->keyval == 65421)
    {
      this->sendMessage();
      return true;
    }
  return false;
}
