//
// Created by asafi on 16/07/2026.
//

#include "DeleteAction.h"
#include "FileSystem.h"
#include "TextFile.h"
#include "Directory.h"
#include "SymbolicLink.h"

DeleteAction::DeleteAction(const WriteRequest& request) : Action(request), fileName(request.FileName){}

void DeleteAction::execute() const {
    FileSystem& fs = FileSystem::getInstance();
    File* deleteTarget = fs.getFile(this->dirPath + "/" + this->fileName); //get file
    if (deleteTarget == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg()); //check if file exists
    }

    Directory* dir = dynamic_cast<Directory*>(deleteTarget); //try dynamic convertion to Dir

    if (dir != nullptr && !dir->getChildes().empty()) { //if its dir that is not empty, dont delete
        throw std::runtime_error(Utilities::DirectoryNotEmptyMsg());
    }
    Directory* parentDir = deleteTarget->getParent();
    if (parentDir != nullptr) {
        parentDir->removeChild(this->fileName);
    }
}



