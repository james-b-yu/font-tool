#include "main.h"
#include "locale.cpp"
#include <boost/filesystem.hpp>
#include <regex>
#include <thread>
#include <vector>

bool App::OnInit() {
	SetProcessDPIAware();
#if LANG == 0
	wxPuts("English: " + std::to_string(m_locale.Init(wxLANGUAGE_ENGLISH_UK)));
#elif LANG == 1
	wxPuts("Deutsch: " + std::to_string(m_locale.Init(wxLANGUAGE_GERMAN)));
#endif

	bool                     doNotRaise = false; // only used if there is an existing process
	std::vector<std::string> options;
	std::vector<std::string> argFiles;

	// a console if the programme is being started from the command line

	if (argc > 1) {
		AttachConsole(ATTACH_PARENT_PROCESS); // if in release, a console will not appear. This line is needed to attach to

		for (int i = 1; i < argc; i++) {                  // start iterating from index 1 as index 0 is the executable path
			const std::string &c = argv[i].ToStdString(); // get a reference to the current element being handled

			// check whether the user is requesting help, and whether to raise an existing instance
			if ((c == "--help" ||
			     std::regex_match(c.begin(), c.end(),
			                      std::regex("^-\\w*h\\w*$")))) { // if requesting for help, display help and exit
				std::string helpText = CMD_USAGE " " + boost::filesystem::path(argv[0].ToStdString()).filename().string() +
				                       " " CMD_SYNTAX + "\n" + CMD_HELP + "\n";

				DWORD nw;
				// WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), helpText.c_str(), helpText.length(), &nw, NULL);
				// FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				wxLogMessage("%s", wxString::FromUTF8(helpText.c_str()));
				return false;
			} else if (std::regex_match(c.begin(), c.end(),
			                            std::regex("^-\\w+$"))) { // if a short-hand version of an argument (like -d, -nd, -sn)
				std::string body = c.substr(1);
				for (char c : body)
					options.push_back(std::string("-") + c);
			} else if (std::regex_match(c.begin(), c.end(),
			                            std::regex("^--\\w[-|\\w]+$"))) { // if a long-hand version like --supress-updates
				options.push_back(c);
			} else
				argFiles.push_back(c);

			if (c == "-d" || c == "--do-not-show" || c == "--hidden") { // save whether it is hidden or not
				doNotRaise = true;
			}
		}
	}

	// prevent more than one instance from running
	m_checker = new wxSingleInstanceChecker;
	if (m_checker->IsAnotherRunning()) {
		if (!doNotRaise) { // raise it if "-d" is not specified
			wxClient *        client = new wxClient;
			wxConnectionBase *base   = client->MakeConnection("localhost", "/tmp/socket", "raise");
			base->Execute("raise");
			delete base;
			delete client;
		}

		// tell the existing instance to load the files specified in the arguments
		wxClient *        clientAdd = new wxClient;
		wxConnectionBase *baseAdd   = clientAdd->MakeConnection("localhost", "/tmp/socket", "addToList");

		for (auto i : argFiles)
			baseAdd->Execute(i);

		delete baseAdd;
		delete clientAdd;

		wxClient *        clientPush = new wxClient;
		wxConnectionBase *basePush   = clientPush->MakeConnection("localhost", "/tmp/socket", "push");

		basePush->Execute("push");

		delete basePush;
		delete clientPush;

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
	frame = new Frame(wxString::FromUTF8(NAME), argv.GetArguments()[0].ToStdString(), options, argFiles);
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

std::vector<std::string> Connection::filesToBeAdded = std::vector<std::string>();

bool Connection::OnExec(const wxString &topic, const wxString &data) {
	if (topic.compare("raise") == 0 && data.compare("raise") == 0) {
		((wxFrame *) wxTheApp->GetTopWindow())->Show();
		((wxFrame *) wxTheApp->GetTopWindow())->Restore();
		((wxFrame *) wxTheApp->GetTopWindow())->Raise();
		((wxFrame *) wxTheApp->GetTopWindow())->Show();
		((wxFrame *) wxTheApp->GetTopWindow())->Restore();
		((wxFrame *) wxTheApp->GetTopWindow())->Raise();
	} else if (topic.compare("addToList") == 0) {
		wxPuts("add" + data);
		filesToBeAdded.push_back(data.ToStdString());
	} else if (topic.compare("push") == 0) {
		wxPuts(std::to_string(filesToBeAdded.size()));
		((Frame *) wxTheApp->GetTopWindow())->addFontsFromArgs(filesToBeAdded);
		filesToBeAdded.clear();
	}

	return true;
}

wxConnectionBase *Server::OnAcceptConnection(const wxString &topic) {
	return new Connection;
}
