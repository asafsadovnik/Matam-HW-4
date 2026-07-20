//
// Created by asafi on 16/07/2026.
//

#include "SearchAction.h"
#include "FileSystem.h"
#include "Directory.h"
#include "SymbolicLink.h"
#include "TextFile.h"

SearchAction::SearchAction(const SearchRequest& request) : Action(request), fileName(request.FileName), text(request.word) {}


void SearchAction::helperRecursive(File* fileToCheck, const std::string& wordToSearch, std::vector<std::string>& linesToPrint) const {
    if (fileToCheck == nullptr) {return;} //empty dir so stop

    Directory* dirToCheck = dynamic_cast<Directory*>(fileToCheck);//try dynamic convertion to dir
    TextFile* textToCheck = dynamic_cast<TextFile*>(fileToCheck);//try dynamic convertion to text

    if (dirToCheck != nullptr) {
        for (std::shared_ptr<File> file : dirToCheck->getChildes()) { //check inside each dir recursivly
            helperRecursive(file.get(), wordToSearch, linesToPrint);
        }
    }
    else if (textToCheck != nullptr) {
        //if its text then check if substring exists
        for (const std::string& currentLine : textToCheck->ReadContent()) {
            if (currentLine.find(wordToSearch) != std::string::npos) {//check if match
                FileSystem& fs = FileSystem::getInstance();
                linesToPrint.push_back(fs.getFilePath(textToCheck)); //if so add to vector;
                break; //we found a substring so stop checking
            }
        }
    }
}

void SearchAction::execute() const {
    FileSystem& fs = FileSystem::getInstance(); //access the filesystem
    File* targetFile = fs.getFile(this->dirPath + "/" + this->fileName); //get specific file to search

    if (targetFile == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg());//check if file exists
    }

    Directory* dirToCheck = dynamic_cast<Directory*>(targetFile);//try dynamic convertion to dir
    TextFile* textToCheck = dynamic_cast<TextFile*>(targetFile);//try dynamic convertion to text
    SymbolicLink* symLink = dynamic_cast<SymbolicLink*>(targetFile); //try dynamic convertion to symLink


    if (symLink != nullptr) { //if its symlink, check then look at text
        textToCheck = this->resolveSymLink(symLink);
        if (textToCheck == nullptr) {
            throw std::runtime_error(Utilities::BrokenLinkMsg());
        }
    }
    if (dirToCheck != nullptr) {
        std::vector<std::string> pathsToPrint;
        helperRecursive(dirToCheck, this->text, pathsToPrint);
        Utilities::printFileContent(pathsToPrint);
    }
    else if (textToCheck != nullptr) {//if its text then check if substring exists
        std::vector<std::string> linesToPrint;
        for (const std::string& currentLine : textToCheck->ReadContent()) {
            if (currentLine.find(this->text) != std::string::npos) {//check if match
                linesToPrint.push_back(currentLine); //if so add to vector;
            }
        }
        Utilities::printFileContent(linesToPrint);
    }
}