#pragma once
#include <wx/wx.h>

class TreeEventData : public wxObject {
  public:
	wxMouseEvent msEvent;
	TreeEventData(const wxMouseEvent &evt);
};