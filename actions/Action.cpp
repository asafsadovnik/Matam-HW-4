//
// Created by asafi on 16/07/2026.
//

#include "Action.h"
#include "../Utilities.h"
#include "TextFile.h"
#include "SymbolicLink.h"
#include "File.h"
#include "FileSystem.h"


Action::Action(const BasicRequest& request) : dirPath(request.DirPath) {}

TextFile* Action::resolveSymLink(const SymbolicLink* link) const {
    File* targetFile = link->getTargetFile(); //get the file that symlink points to
    if (targetFile == nullptr) {return nullptr;}
    return dynamic_cast<TextFile*>(targetFile); //dynamic cast to text file: returns nullptr if not textfile
}

