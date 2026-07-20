//
// Created by asafi on 16/07/2026.
//

#include "ExportAction.h"
#include "FileSystem.h"
#include "Utilities.h"
#include "TextFile.h"
#include "Directory.h"
#include "SymbolicLink.h"
#include <ostream>

ExportAction::ExportAction(WriteRequest& request) : fileName(request.FileName), targetPath(request.TargetPath) {}

void ExportAction::execute() const {
    FileSystem& fs = FileSystem::getInstance();
    File* targetFile = fs.getFile(this->dirPath + "/" + this->fileName);

    if (targetFile == nullptr) {
        throw std::runtime_error(Utilities::FileNotFoundMsg());
    }

    TextFile* text = dynamic_cast<TextFile*>(targetFile);
    SymbolicLink* symLink = dynamic_cast<SymbolicLink*>(targetFile);
    Directory* dir = dynamic_cast<Directory*>(targetFile);

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
        std::ofstream hostFile(this->targetPath); //open stream
        if (!hostFile.is_open()) {//check correct open
            throw std::runtime_error(Utilities::FileNotFoundMsg());
        }
        Utilities::writeLinesToStream(hostFile, text->ReadContent());
        hostFile.close(); //close stream
    }
}