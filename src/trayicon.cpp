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
	if (window && !((Frame *) window)->supressUpdates)
		Connect(wxID_FILE3, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::update));
	Connect(wxID_CLOSE_FRAME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::closeFrame));
	Connect(wxID_ABORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TrayIcon::abort));
}

void TrayIcon::showWindow(wxTaskBarIconEvent &evt) {
	evt.Skip();
	if (window) {
		// if (!window->IsShownOnScreen()) {
		window->Raise();
		window->Restore();
		window->Show();
		// } else {
		// 	window->Show(false);
		// }
	}
}

wxMenu *TrayIcon::CreatePopupMenu() {
	wxMenu *    menu  = new wxMenu();
	wxMenuItem *title = new wxMenuItem(menu, wxID_HOME);

	wxFont font = window->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	title->SetFont(font);

	if (window) {
		if (((Frame *) window)->busy)
			title->SetItemLabel(wxString::FromUTF8(BUSY_NAME));
		else if (((Frame *) window)->updateAvailable)
			title->SetItemLabel(wxString::FromUTF8(UPDATE_AVAILABLE_NAME));
		else
			title->SetItemLabel(wxString::FromUTF8(NAME));
	}

	menu->Append(title);
	menu->Append(new wxMenuItem(menu, wxID_SEPARATOR));
	menu->Append(wxID_ABOUT, wxString::FromUTF8(INFORMATION));

	if (window && !((Frame *) window)->busy) {
		// if an update is available, display the update item at the bottom
		if (((Frame *) window)->updateAvailable) {
			menu->Append(wxID_FILE1, wxString::FromUTF8(A_FONT_FILES));
			menu->Append(wxID_FILE2, wxString::FromUTF8(A_FONT_FOLDERS));
			menu->Append(wxID_CLOSE_FRAME, wxString::FromUTF8(CLOSE));
		}

		// if the application is not already updated, display the update menu item
		if (!((Frame *) window)->updated && !((Frame *) window)->supressUpdates) {
			wxMenuItem *updateMenu = new wxMenuItem(menu, wxID_FILE3, UPDATE);
			// if an update is available, make the update item bold
			if (((Frame *) window)->updateAvailable)
				updateMenu->SetFont(font);

			menu->Append(updateMenu);
		}

		// if an update is not available, display the update item below the about item
		if (!((Frame *) window)->updateAvailable) {
			menu->Append(wxID_FILE1, wxString::FromUTF8(A_FONT_FILES));
			menu->Append(wxID_FILE2, wxString::FromUTF8(A_FONT_FOLDERS));
			menu->Append(wxID_CLOSE_FRAME, wxString::FromUTF8(CLOSE));
		}
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
		window->Raise();
		window->Restore();
		window->Show();
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
		window->Show();
		window->Restore();
		window->Raise();
		window->Show();
		window->Restore();
		window->Raise();

		wxPostEvent(window, wxCommandEvent(UPDATE_APPLICATION));
	}
}