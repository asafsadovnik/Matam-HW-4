//
// Created by asafi on 16/07/2026.
//

#include "Action.h"
#include "../Utilities.h"
#include "TextFile.h"
#include "File.h"
#include "FileSystem.h"


Action::Action(const std::string& fileType, const std::string& dirPath) : fileType(fileType), dirPath(dirPath) {}

std::shared_ptr<TextFile> Action::resolveSymLink(const std::shared_ptr<SymbolicLink>& link) const {
    FileSystem& fs = FileSystem::getInstance();
    std::shared_ptr<File> targetFile = fs.getFile(link->getTargetPath(), ""); //get the file that symlink points to

    if (targetFile == nullptr) {return nullptr;}

    return std::dynamic_pointer_cast<TextFile>(targetFile); //dynamic cast to text file: returns nullptr if not textfile
}

