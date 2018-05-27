#pragma once

#include "tbb/concurrent_vector.h"
#include <wx/treectrl.h>
#include <wx/wx.h>

class TreeItemData : public wxTreeItemData {
  protected:
	wxString _name;
	int      _type;

  public:
	bool        folder;
	bool        error;
	std::string path;
	std::string folderPath;

	TreeItemData(std::string path, bool folder, bool error, std::string folderPath = "");
};