//
// Created by asafi on 16/07/2026.
//

#include "CreateAction.h"
#include "File.h"
#include "Directory.h"
#include "TextFile.h"
#include "SymbolicLink.h"
#include "FileSystem.h"

CreateAction::CreateAction(const WriteRequest& request) : Action(request), fileName(request.FileName), fileType(request.type), targetPath(request.TargetPath){}

void CreateAction::execute() const {
    FileSystem& fs = FileSystem::getInstance(); // get parentDir for creation
    File* targetFolder = fs.getFile(this->dirPath);
    Directory* parentDir = dynamic_cast<Directory*>(targetFolder);

    if (parentDir == nullptr) {//check if actually Dir
        throw std::runtime_error(Utilities::FileNotFoundMsg());
    }
    if (parentDir->getChild(this->fileName) != nullptr) {//check if file exists
        throw std::runtime_error(Utilities::commandErrorMsg());
    }

    if (this->fileType == "textfile") {
        std::shared_ptr<TextFile> newFile = std::make_shared<TextFile>(this->fileName, parentDir);
        parentDir->addChild(newFile);
    }
    else if (this->fileType == "directory") {
        std::shared_ptr<Directory> newFile = std::make_shared<Directory>(this->fileName, parentDir);
        parentDir->addChild(newFile);
    }
    else if (this->fileType == "symlink") {
        File* symTarget = fs.getFile(this->targetPath);
        if (symTarget == nullptr || dynamic_cast<TextFile*>(symTarget) == nullptr) { //check if symlink pointing to valid txt file
            throw std::runtime_error(Utilities::TypeErrorMsg());
        }
        std::shared_ptr<SymbolicLink> newFile = std::make_shared<SymbolicLink>(this->fileName, parentDir, this->targetPath);
        parentDir->addChild(newFile);
    }
}
