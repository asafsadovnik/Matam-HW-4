//
// Created by asafi on 16/07/2026.
//

#include "SearchAction.h"
#include "FileSystem.h"
#include "Directory.h"
#include "SymbolicLink.h"
#include "TextFile.h"

SearchAction::SearchAction(const SearchRequest& request) : Action(request), fileName(request.FileName), text(request.word) {}

void SearchAction::execute() const {
    FileSystem& fs = FileSystem::getInstance(); //access the filesystem
    File* targetFile = fs.getFile(this->dirPath + "/" + this->fileName); //get specific file to search

    if (targetFile == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg());//check if file exists
    }

    TextFile* textfile = dynamic_cast<TextFile*>(targetFile); //try dynamic convertion to text
    Directory* dir = dynamic_cast<Directory*>(targetFile); //try dynamic convertion to Dir
    SymbolicLink* symLink = dynamic_cast<SymbolicLink*>(targetFile); //try dynamic convertion to symLink

    if (symLink != nullptr) { //check symlink first. if broken then error if not then look at textfile
        if ((textfile = this->resolveSymLink(symLink)) == nullptr ) {
            throw std::runtime_error(Utilities::BrokenLinkMsg());
        }
    }

    if (textfile != nullptr) {
        std::vector<std::string> linesToPrint;
        for (const std::string& currentLine : textfile->ReadContent()) {
            if (currentLine.find(this->text) != std::string::npos) {//check if match
                linesToPrint.push_back(currentLine); //if so add to vector
            }
        }
    }
    else if (dir != nullptr) {
        std::vector<std::string> pathsToPrint;
        for (const std::string& currentFile : dir)
    }

}