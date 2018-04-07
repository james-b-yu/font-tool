#include "tritemdata.h"

TreeItemData::TreeItemData(std::string path, bool folder, bool error, std::string folderPath)
    : path(path)
    , folder(folder)
    , error(error)
    , folderPath(folderPath) {
}