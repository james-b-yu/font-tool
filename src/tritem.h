#pragma once

#include <string>
#include <wx/treectrl.h>
#include <wx/wx.h>

class TreeItem {
  public:
	wxTreeItemId id;
	std::string  name;
	TreeItem(wxTreeItemId id, std::string name);
};