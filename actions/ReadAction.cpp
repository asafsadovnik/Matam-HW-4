//
// Created by asafi on 16/07/2026.
//

#include "ReadAction.h"
#include "FileSystem.h"
#include "TextFile.h"
#include "Utilities.h"

ReadAction::ReadAction(const std::string& fileType, const std::string& dirPath, const std::string& fileName) : Action(fileType, dirPath), fileName(fileName){}

void ReadAction::execute() {
    FileSystem& fs = FileSystem::getInstance(); //access the filesystem
    std::shared_ptr<File> targetFile = fs.getFile(this -> dirPath, this -> fileName); //get specific file to read
    if (targetFile == nullptr) {
        Utilities::printError(Utilities::FileNotFoundMsg()); //check if file exists
    }

    std::shared_ptr<TextFile> textfile = std::dynamic_pointer_cast<TextFile>(targetFile); //try dynamic convertion to text
    std::shared_ptr<Directory> dir = std::dynamic_pointer_cast<Directory>(targetFile); //try dynamic convertion to Dir
}