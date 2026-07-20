//
// Created by asafi on 16/07/2026.
//

#include "ImportAction.h"
#include "FileSystem.h"
#include "Utilities.h"
#include "TextFile.h"
#include "Directory.h"
#include "SymbolicLink.h"
#include <fstream>


    ImportAction::ImportAction(WriteRequest& request) : fileName(request.FileName), targetPath(request.TargetPath) {}


    void ImportAction::execute() const {
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
            std::ifstream hostFile(this->targetPath); //open stream
            if (!hostFile.is_open()) {//check correct open
                throw std::runtime_error(Utilities::FileNotFoundMsg());
            }
            std::vector<std::string> linesToImport = Utilities::readLinesFromStream(hostFile); //read lines from file
            for (const std::string& line : linesToImport) {
                text->WriteContent(line);
            }
            hostFile.close(); //close stream
        }
    }