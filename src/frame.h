#pragma once

#include "finfo.h"
#include "tbb/concurrent_vector.h"
#include "trayicon.h"
#include "tritem.h"
#include "tritemdata.h"
#include <boost/container/vector.hpp>
#include <boost/filesystem.hpp>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <wx/statline.h>
#include <wx/treectrl.h>
#include <wx/wx.h>

class Frame : public wxFrame {
  private:
	// scaling factor for current display
	double scalingFactor;
	// window display
	wxPanel *     panel;      // main panel (for white bg)
	wxBoxSizer *  topSizer;   // main sizer which contains everything
	wxBoxSizer *  addButtons; // sizer which contains buttons
	wxBoxSizer *  statuses;
	wxButton *    addFontFilesButton;   // button to add font files
	wxButton *    removeAllFontsButton; // remove all fonts
	wxButton *    addFontFoldersButton; // button to add font folders
	wxStaticText *statusText1;
	wxStaticText *statusText2;
	wxStaticText *statusText3;
	wxStaticLine *errorLine;
	bool          errorHidden = true;

	wxButton *   removeSelectedButton;
	wxCheckBox * recursiveSearch; // whether recursion is enabled
	wxTreeCtrl * fontTree;        // display of loaded fonts
	wxTreeItemId fontTreeRoot;
	wxTreeItemId fontTreeFailed;
	wxTreeItemId fontTreeFolders;
	wxTreeItemId fontTreeFiles;
	unsigned int padding = 8;

	// keeping track of fonts
	tbb::concurrent_vector<FontInfo>           queue;
	tbb::concurrent_vector<FontInfo>           succeededFontFiles; // only fonts which were successfully added
	tbb::concurrent_vector<FontInfo>           oldSucceededFontFiles;
	tbb::concurrent_vector<FontInfo>           failedFontFiles; // failed font files
	tbb::concurrent_vector<FontInfo>           oldFailedFontFiles;
	tbb::concurrent_vector<unsigned long long> removeList;

	// for asyncronous loading of fonts
	std::mutex              m;
	std::condition_variable cv;
	unsigned long long      processCount = 0;
	void                    waitForCompletion(bool reset, bool loadArgs);

	// for bootup
	const std::string databasePath = "fonts";
	std::ifstream     savedFromFile;
	std::ofstream     saveToFile;

	unsigned long long oldSuccessfulSize = 0;
	unsigned long long oldFailedSize     = 0;

	template <class T>
	bool addToRemoveQueue(tbb::concurrent_vector<T> &list, T item);
	template <class T>
	void processRemoveQueue(tbb::concurrent_vector<T> &list);
	template <class T>
	bool isInVector(tbb::concurrent_vector<T> &list, T item);
	bool isFontFile(boost::filesystem::path path);
	void addToTree();

	tbb::concurrent_vector<TreeItem>       folders;
	tbb::concurrent_vector<TreeItemData *> treeItemDataObjects;

	void addFontsFromFile();
	void addFontsFromArgs();

	void addFontFileAsync(std::string path);
	void addFontFolderAsync(std::string dirPath, std::string folderName);
	void addFontFromInfoAsync(FontInfo currentFont);

	bool addFont(FontInfo &font);

	void handleDroppedFiles(wxDropFilesEvent &evt);
	void removeAllFontsWithButton(wxCommandEvent &evt);
	bool removeFont(FontInfo &font);
	void closeOnceDone();
	void destroyOnceDone(wxCommandEvent &evt);
	void save();

	void handleSelectionChanged(wxTreeEvent &evt);

	void removeSelected(wxCommandEvent &evt);
	void handleTreeItem(wxTreeItemId id, bool removeToo = true);

	std::string status;
	std::string readyMessage;

	void                     updateStatus();
	void                     updateStatus(std::string newStatus);
	void                     hide(wxIconizeEvent &evt);
	void                     treePopupMenu(wxMouseEvent &evt);
	void                     openSelected(wxCommandEvent &evt);
	void                     treeActivated(wxTreeEvent &evt);
	void                     enableControls();
	void                     disableControls();
	void                     getTreeItemTooltip(wxTreeEvent &evt);
	void                     onKey(wxKeyEvent &evt);
	void                     treeMotion(wxMouseEvent &evt);
	wxArrayTreeItemIds       getChildren(const wxTreeItemId &parent);
	std::string              programmePath;
	std::vector<std::string> startupFiles;

	bool changed  = false;
	bool hideTray = false;

	void updateTest(wxCommandEvent &evt);
	bool shouldEnableRemove();

	TrayIcon *trayIcon;
	DECLARE_EVENT_TABLE();

  public:
	void onClose(wxCloseEvent &evt);
	void showAbout(wxCommandEvent &evt);

	void addFontFilesFromDialog(wxCommandEvent &evt);
	void addFontFoldersFromDialog(wxCommandEvent &evt);
	void addFontsFromArgs(std::vector<std::string> args);

	bool busy;
	bool updateAvailable = false;
	bool updated         = false;
	bool supressUpdates  = false;

	Frame(wxString name, std::string programmePath, std::vector<std::string> opts, std::vector<std::string> argFiles);
	~Frame();
};
