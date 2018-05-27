#pragma once

#include "frame.h"
#include <wx/ipc.h>
#include <wx/snglinst.h>
#include <wx/wx.h>

class Connection : public wxConnection {
  protected:
	bool OnExec(const wxString &topic, const wxString &data);
};

class Server : public wxServer {
  public:
	wxConnectionBase *OnAcceptConnection(const wxString &topic);
};

class App : public wxApp {
  private:
	Frame *                  frame;
	wxSingleInstanceChecker *m_checker;
	Server *                 m_server;
	wxLocale                 m_locale;

  public:
	virtual bool OnInit();
	virtual int  OnExit();
};