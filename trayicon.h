#pragma once

#include <wx/taskbar.h>
#include <wx/wx.h>

class TrayIcon : public wxTaskBarIcon {
  private:
	wxFrame *window;
	void     addFontFiles(wxCommandEvent &evt);
	void     addFontFolders(wxCommandEvent &evt);
	void     showWindow(wxTaskBarIconEvent &evt);
	void     showWindowCommand(wxCommandEvent &evt);
	void     showAbout(wxCommandEvent &evt);
	void     closeFrame(wxCommandEvent &evt);
	void     abort(wxCommandEvent &evt);
	void     update(wxCommandEvent &evt);

  public:
	TrayIcon(wxFrame *window);
	virtual wxMenu *CreatePopupMenu();
	DECLARE_EVENT_TABLE();
};