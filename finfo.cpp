#include "finfo.h"

FontInfo::FontInfo(std::string path, std::string folderPath, std::string folder)
    : folder(folder)
    , path(path)
    , fileName(boost::filesystem::path(path).filename().string())
    , folderPath(folderPath) {
	// wxPuts("Folder: " + folder + " Path: " + path + " fileName: " + fileName);
	// this->path.replace(this->path.begin(), this->path.end(), "\\", "/");
	// this->folderPath.replace(this->path.begin(), this->path.end(), "\\", "/");
}

bool FontInfo::operator==(FontInfo &comp) {
	try {
		// wxPuts("comp: " + comp.path);
		// wxPuts("this: " + path);
		return comp.path == path;
	} catch (...) {
		return true;
	}
}