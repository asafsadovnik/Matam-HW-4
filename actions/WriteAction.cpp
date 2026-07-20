//
// Created by asafi on 16/07/2026.
//

#include "WriteAction.h"
#include "Directory.h"
#include "SymbolicLink.h"
#include "TextFile.h"
#include "FileSystem.h"

WriteAction::WriteAction(const WriteRequest& request) : Action(request), fileName(request.FileName), content(request.Content) {}

void WriteAction::execute() const {
    FileSystem& fs = FileSystem::getInstance(); //access the filesystem
    File* targetFile = fs.getFile(this->dirPath + "/" + this->fileName); //get specific file to write

    if (targetFile == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg());//check if file exists
    }
    Directory* dir = dynamic_cast<Directory*>(targetFile);//try dynamic convertion to dir
    TextFile* text = dynamic_cast<TextFile*>(targetFile);//try dynamic convertion to text
    SymbolicLink* symLink = dynamic_cast<SymbolicLink*>(targetFile); //try dynamic convertion to symLink

    if (dir != nullptr) {
        throw std::runtime_error(Utilities::TypeErrorMsg());
    }
    if (symLink != nullptr) {
        text = this->resolveSymLink(symLink);
        if (text == nullptr) {
            throw std::runtime_error(Utilities::BrokenLinkMsg());
        }
    }
    if (text != nullptr) {
        text->WriteContent(this->content[0]);
    }
}
