//
// Created by asafi on 16/07/2026.
//

#include "ReadAction.h"
#include "FileSystem.h"
#include "TextFile.h"
#include "Directory.h"
#include "Utilities.h"

ReadAction::ReadAction(const ReadRequest& request) : Action(request), fileName(request.FileName) {}

void ReadAction::execute() const {
    FileSystem& fs = FileSystem::getInstance(); //access the filesystem
    File* targetFile = fs.getFile(this->dirPath + "/" + this->fileName); //get specific file to read
    if (targetFile == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg());//check if file exists
    }

    TextFile* textfile = dynamic_cast<TextFile*>(targetFile); //try dynamic convertion to text
    Directory* dir = dynamic_cast<Directory*>(targetFile); //try dynamic convertion to Dir
    SymbolicLink* symLink = dynamic_cast<SymbolicLink*>(targetFile); //try dynamic convertion to symLink

    if (textfile != nullptr) { //if its text then print content
        Utilities::printFileContent(textfile->ReadContent());
    }
    else if (dir != nullptr) { //if its dir then print kids
        Utilities::ListFiles(dir->getChildes());
    }
    else if (symLink != nullptr) {//if its symlink then read the link text file content
        TextFile* resolvedFile = this->resolveSymLink(symLink); //check if symlink is valid
        if (resolvedFile != nullptr) {
            Utilities::printFileContent(resolvedFile->ReadContent());

        } else {throw std::runtime_error(Utilities::BrokenLinkMsg());}
    }

}