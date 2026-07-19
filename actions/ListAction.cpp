//
// Created by asafi on 16/07/2026.
//

#include "ListAction.h"
#include "FileSystem.h"
#include "Directory.h"

ListAction::ListAction(const ReadRequest& request) : Action(request), fileName(request.FileName) {}

void ListAction::execute() const {
    FileSystem& fs = FileSystem::getInstance(); //access the filesystem
    File* targetFile = fs.getFile(this->dirPath); //get specific file to list

    if (targetFile == nullptr) {//check if file exists
        throw std::runtime_error(Utilities::FileNotFoundMsg());
    }

    SymbolicLink* symLink = dynamic_cast<SymbolicLink*>(targetFile); //dynamic cast to symlink
    if (symLink != nullptr) {
        if (this->resolveSymLink(symLink) == nullptr) { //check if link broken
            throw std::runtime_error(Utilities::BrokenLinkMsg());
        }
        throw std::runtime_error(Utilities::TypeErrorMsg()); //return error cant list symlink
    }

    Directory* dirToList = dynamic_cast<Directory*>(targetFile); //dynamic cast to dir

    if (dirToList == nullptr) {
        throw std::runtime_error(Utilities::TypeErrorMsg());
    }

    Utilities::ListFiles(dirToList->getChildes());
}

