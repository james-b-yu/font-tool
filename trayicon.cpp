#include "trayicon.h"
#include "frame.h"
#include "icon.xpm"
#include "locale.cpp"
#include <wx/settings.h>

BEGIN_EVENT_TABLE(TrayIcon, wxTaskBarIcon)
EVT_TASKBAR_LEFT_DOWN(TrayIcon::showWindow)
END_EVENT_TABLE()

TrayIcon::TrayIcon(wxFrame *window)
    : wxTaskBarIcon()
    , window(window) {
	SetIcon(icon_xpm);

	Connect(wxID_HOME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::showWindowCommand));
	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::showAbout));
	Connect(wxID_FILE1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::addFontFiles));
	Connect(wxID_FILE2, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::addFontFolders));
	Connect(wxID_FILE3, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::update));
	Connect(wxID_CLOSE_FRAME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::closeFrame));
	Connect(wxID_ABORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::abort));
}

void TrayIcon::showWindow(wxTaskBarIconEvent &evt) {
	evt.Skip();
	if (window) {
		if (!window->IsShownOnScreen()) {
			window->Raise();
			window->Restore();
			window->Show();
		} else {
			window->Show(false);
		}
	}
}

wxMenu *TrayIcon::CreatePopupMenu() {
	wxMenu *    menu  = new wxMenu();
	wxMenuItem *title = new wxMenuItem(menu, wxID_HOME);

	if (window) {
		if (((Frame *) window)->busy)
			title->SetItemLabel(wxString::FromUTF8(BUSY_NAME));
		else if (((Frame *) window)->updatePending)
			title->SetItemLabel(UPDATE_AVAILABLE_NAME);
		else
			title->SetItemLabel(wxString::FromUTF8(NAME));

		wxFont font = window->GetFont();
		font.SetWeight(wxFONTWEIGHT_BOLD);
		title->SetFont(font);
	}

	menu->Append(title);
	menu->Append(new wxMenuItem(menu, wxID_SEPARATOR));
	menu->Append(wxID_ABOUT, wxString::FromUTF8(INFORMATION));

	if (window && !((Frame *) window)->busy) {
		menu->Append(wxID_FILE1, wxString::FromUTF8(A_FONT_FILES));
		menu->Append(wxID_FILE2, wxString::FromUTF8(A_FONT_FOLDERS));
		menu->Append(wxID_CLOSE_FRAME, wxString::FromUTF8(CLOSE));

		if (!((Frame *) window)->updatePending)
			menu->Append(wxID_FILE3, wxString::FromUTF8(UPDATE));
	} else {
		menu->Append(wxID_ABORT, wxString::FromUTF8(DESTROY));
	}

	return menu;
}

void TrayIcon::abort(wxCommandEvent &evt) {
	evt.Skip();
	if (window) {
		window->Destroy();
	}
}

void TrayIcon::showWindowCommand(wxCommandEvent &evt) {
	if (window) {
		window->Show();
		window->Restore();
		window->Raise();
		window->Show();
		window->Restore();
		window->Raise();
	}
}

void TrayIcon::addFontFiles(wxCommandEvent &evt) {
	if (window) {
		window->Disable();
		((Frame *) window)->addFontFilesFromDialog(evt);
	}
}

void TrayIcon::addFontFolders(wxCommandEvent &evt) {
	if (window) {
		window->Disable();
		((Frame *) window)->addFontFoldersFromDialog(evt);
	}
}

void TrayIcon::closeFrame(wxCommandEvent &evt) {
	if (window) {
		wxCloseEvent clevt;
		((Frame *) window)->onClose(clevt);
	}
}

void TrayIcon::showAbout(wxCommandEvent &evt) {
	if (window) {
		((Frame *) window)->showAbout(evt);
	}
}

void TrayIcon::update(wxCommandEvent &evt) {
	if (window) {
		// ((Frame *) window)->updateApplication();
		wxPostEvent(window, wxCommandEvent(UPDATE_APPLICATION));
	}
}