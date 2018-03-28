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
	// SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetIcon(icon_xpm);
}

void TrayIcon::showWindow(wxTaskBarIconEvent &evt) {
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
	wxMenuItem *title = new wxMenuItem(menu, wxID_HOME, wxString::FromUTF8(BUSY));

	if (window && !((Frame *) window)->busy) {
		title->SetItemLabel(wxString::FromUTF8(NAME));
	}

	if (window) {
		wxFont font = window->GetFont();
		font.SetWeight(wxFONTWEIGHT_BOLD);
		title->SetFont(font);
	}

	menu->Append(title);
	menu->Append(new wxMenuItem(menu, wxID_SEPARATOR));
	menu->Append(wxID_ABOUT, wxString::FromUTF8(INFORMATION));

	Bind(wxEVT_COMMAND_MENU_SELECTED, &TrayIcon::showWindowCommand, this, wxID_HOME);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &TrayIcon::showAbout, this, wxID_ABOUT);

	if (window && !((Frame *) window)->busy) {
		menu->Append(wxID_FILE1, wxString::FromUTF8(A_FONT_FILES));
		menu->Append(wxID_FILE2, wxString::FromUTF8(A_FONT_FOLDERS));
		menu->Append(wxID_FILE3, wxString::FromUTF8(UPDATE));
		menu->Append(wxID_CLOSE_FRAME, wxString::FromUTF8(CLOSE));

		Bind(wxEVT_COMMAND_MENU_SELECTED, &TrayIcon::addFontFiles, this, wxID_FILE1);
		Bind(wxEVT_COMMAND_MENU_SELECTED, &TrayIcon::addFontFolders, this, wxID_FILE2);
		Bind(wxEVT_COMMAND_MENU_SELECTED, &TrayIcon::closeFrame, this, wxID_CLOSE_FRAME);
		Bind(wxEVT_COMMAND_MENU_SELECTED, &TrayIcon::update, this, wxID_FILE3);
	} else {
		menu->Append(wxID_ABORT, wxString::FromUTF8(DESTROY));
		Bind(wxEVT_COMMAND_MENU_SELECTED, &TrayIcon::abort, this, wxID_ABORT);
	}

	return menu;
}

void TrayIcon::abort(wxCommandEvent &evt) {
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
		std::thread([&]() { ((Frame *) window)->updateApplication(); }).detach();
	}
}