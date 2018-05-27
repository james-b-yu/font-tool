#include "main.h"
#include "locale.cpp"
#include <boost/filesystem.hpp>
#include <thread>
#include <vector>

bool App::OnInit() {
	bool startHidden = false;

	// check whether the user is requesting help, and whether to raise an existing instance
	for (int i = 0; i < argc; i++) {
		const wxString &c = argv[i];

		if ((c.ToStdString() == "--help" || c.ToStdString() == "-h" || c.ToStdString() == "--h") &&
		    AttachConsole(ATTACH_PARENT_PROCESS)) { // if requesting for help, display help and exit
			std::string helpText = CMD_USAGE " " + boost::filesystem::path(argv[0].ToStdString()).filename().string() +
			                       " " CMD_SYNTAX + "\n" + CMD_HELP + "\n";

			DWORD nw;
			WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), helpText.c_str(), helpText.length(), &nw, NULL);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			return false;
		} else if (c == "-d" || c == "--do-not-show" || c == "--hidden") { // save whether it is hidden or not
			startHidden = true;
		}
	}

	SetProcessDPIAware();
#if LANG == 0
	wxPuts("English: " + std::to_string(m_locale.Init(wxLANGUAGE_ENGLISH_UK)));
#elif LANG == 1
	wxPuts("Deutsch: " + std::to_string(m_locale.Init(wxLANGUAGE_GERMAN)));
#endif

	// prevent more than one instance from running
	m_checker = new wxSingleInstanceChecker;
	if (m_checker->IsAnotherRunning()) {
		if (!startHidden) { // raise it if "-d" is not specified
			wxClient *        client = new wxClient;
			wxConnectionBase *base   = client->MakeConnection("localhost", "/tmp/socket", "topic");
			base->Execute("raise");
			delete base;
			delete client;
		}

		delete m_checker;
		m_checker = nullptr;
		return false;
	}

	auto path = boost::filesystem::path(argv[0].ToStdString()).parent_path().string();
	SetCurrentDirectoryA(
	    path.c_str()); // make sure that the programme runs in its own parent directory (so fonts folder is not jumbled)
	wxPuts(path);

	// remove old version of the file (for updates)
	if (boost::filesystem::is_regular_file(argv[0].ToStdString() + ".old")) {
		boost::filesystem::remove(argv[0].ToStdString() + ".old");
	}

	// create a frame
	frame = new Frame(wxString::FromUTF8(NAME), argv.GetArguments());
	// frame->SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));

	// start new IPC server
	m_server = new Server;
	m_server->Create("/tmp/socket");

	// set frame to be top window
	SetTopWindow(frame);

	return true;
}

int App::OnExit() {
	delete m_server;
	delete m_checker;
	return true;
}

// macro to run app in entry point

#ifndef NDEBUG
IMPLEMENT_APP_CONSOLE(App);
#else
IMPLEMENT_APP(App);
#endif

bool Connection::OnExec(const wxString &topic, const wxString &data) {
	if (topic.compare("topic") == 0 && data.compare("raise") == 0) {
		((wxFrame *) wxTheApp->GetTopWindow())->Show();
		((wxFrame *) wxTheApp->GetTopWindow())->Restore();
		((wxFrame *) wxTheApp->GetTopWindow())->Raise();
		((wxFrame *) wxTheApp->GetTopWindow())->Show();
		((wxFrame *) wxTheApp->GetTopWindow())->Restore();
		((wxFrame *) wxTheApp->GetTopWindow())->Raise();
	}

	return true;
}

wxConnectionBase *Server::OnAcceptConnection(const wxString &topic) {
	return new Connection;
}
