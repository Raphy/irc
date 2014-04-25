//
// ChannelTab.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:37:33 2014 raphael defreitas
// Last update Thu Apr 24 13:11:33 2014 raphael defreitas
//

#include	<ChannelTab.h>

ChannelTab::ChannelTab() :
  m_useless("Users"), m_send_button("Send")
{
  pack_start(m_chat_container);
  pack_end(m_useless);
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

void ChannelTab::appendText(const Glib::ustring& text)
{
  std::string final_text = text + "\n";
  Glib::RefPtr<Gtk::TextBuffer> buffer = m_text_view.get_buffer();
  Gtk::TextBuffer::iterator it = buffer->end();
  buffer->insert(it, final_text);  
  Glib::RefPtr<Gtk::Adjustment> adj = m_text_view.get_vadjustment();
  adj->set_value(adj->get_upper() - adj->get_page_size());
}

void ChannelTab::sendMessage()
{
  if (m_cmd_entry.get_text().length() > 0)
    {
      appendText(m_cmd_entry.get_text());
      m_cmd_entry.set_text("");
    }
}

bool ChannelTab::onKeyReleased(GdkEventKey* event)
{
  if (event->keyval == 65293)
    {
      this->sendMessage();
      return true;
    }
  return false;
}
