//
// GeneralTab.cpp for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/client/sources
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed Apr 23 18:37:33 2014 raphael defreitas
// Last update Fri Apr 25 14:14:40 2014 raphael defreitas
//

#include	<gdk/gdk.h>
#include	<gtkmm/widget.h>
#include	<iostream>
#include	<string>

#include	"GeneralTab.h"
#include	"MainWindow.h"

GeneralTab::GeneralTab(const std::string& title) :
  m_title(title), m_send_button("Send")
{  
  pack_start(m_text_view_container, true, true);
  pack_end(m_cmd_container, false, false);
  m_text_view_container.add(m_text_view);
  m_cmd_container.pack_start(m_cmd_entry);
  m_cmd_container.pack_end(m_send_button, false, false);

  m_text_view.set_editable(false);
  m_text_view.set_wrap_mode(Gtk::WRAP_WORD);

  m_cmd_entry.signal_key_release_event().connect(sigc::mem_fun(*this, &GeneralTab::onKeyReleased));
  this->m_send_button.signal_clicked().connect(sigc::mem_fun(*this, &GeneralTab::sendMessage));
}

GeneralTab::~GeneralTab()
{
  
}

void GeneralTab::appendText(const std::string& text)
{
  std::string final_text = text + "\n";
  Glib::RefPtr<Gtk::TextBuffer> buffer = m_text_view.get_buffer();
  Gtk::TextBuffer::iterator it = buffer->end();
  buffer->insert(it, final_text);  
  Glib::RefPtr<Gtk::Adjustment> adj = m_text_view.get_vadjustment();
  adj->set_value(adj->get_upper() - adj->get_page_size());
}

Gtk::Widget* GeneralTab::getWidget()
{
  return this;
}

sigc::signal<void, const std::string&>& GeneralTab::signal_command_sent()
{
  return m_signal_command_sent;
}

const std::string& GeneralTab::getTitle() const
{
  return m_title;
}

void GeneralTab::sendMessage()
{
  if (m_cmd_entry.get_text().length() > 0)
    {
      //appendText(m_cmd_entry.get_text());
      m_signal_command_sent.emit(m_cmd_entry.get_text());
      m_cmd_entry.set_text("");
    }
}

bool GeneralTab::onKeyReleased(GdkEventKey* event)
{
  if (event->keyval == 65293 || event->keyval == 65421)
    {
      this->sendMessage();
      return true;
    }
  return false;
}
