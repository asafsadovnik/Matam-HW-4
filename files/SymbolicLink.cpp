#include "SymbolicLink.h"
#include "Utilities.h"
#include "FileSystem.h"
// Add Action!!

File *SymbolicLink::getTargetFile() const {
    return FileSystem::getInstance().getFile(target_path);
}

std::unique_ptr<Action> SymbolicLink::CreateReadAction(ReadRequest &request) const {

    switch (request.command) {
        case CommandType::LIST:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        case CommandType::READ:
            File* targetFile = getTargetFile();
            if (targetFile == nullptr) {
                return std::make_unique<ErrorAction>(Utilities::BrokenLinkMsg());
            }
                return targetFile->CreateReadAction(request);
    }
}

std::unique_ptr<Action> SymbolicLink::CreateWriteAction(WriteRequest &request) const {

    switch (request.command) {
        case CommandType::WRITE:

        case CommandType::CREATE:

        case CommandType::DELETE:

        default:
            return nullptr;
    }
}

std::unique_ptr<Action> SymbolicLink::CreateSearchAction(SearchRequest &request) const {
    File* targetFile = getTargetFile();
    if (targetFile == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::BrokenLinkMsg());
    }
    return targetFile->CreateSearchAction(request);
}


