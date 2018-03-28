#include <boost/filesystem.hpp>
#include <string>
#include <wx/wx.h>

class FontInfo {
  public:
	std::string folder;
	std::string path;
	std::string fileName;
	std::string folderPath;

	FontInfo(std::string path, std::string folderPath = "", std::string folder = "");
	bool operator==(FontInfo &comp);
};