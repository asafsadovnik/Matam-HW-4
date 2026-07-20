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

    File* parentFile = fs.getFile(this->dirPath); //get parent file
    if (parentFile == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg());
    }
    Directory* parentDir = dynamic_cast<Directory*>(parentFile); //make sure its dir
    if (parentDir == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg());
    }

    File* deleteTarget = parentDir->getChild(this->fileName); //get file
    if (deleteTarget == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg()); //check if file exists
    }

    Directory* dir = dynamic_cast<Directory*>(deleteTarget); //try dynamic convertion to Dir

    if (dir != nullptr && !dir->getChildes().empty()) { //if its dir that is not empty, dont delete
        throw std::runtime_error(Utilities::DirectoryNotEmptyMsg());
    }

    if (parentDir != nullptr) {
        parentDir->removeChild(this->fileName);
    }
}



