#include "SymbolicLink.h"
#include "Utilities.h"
#include "FileSystem.h"
#include "Action.h"
#include "CreateAction.h"
#include "DeleteAction.h"
#include "ExportAction.h"
#include "HelpAction.h"
#include "ImportAction.h"
#include "ListAction.h"
#include "ReadAction.h"
#include "SearchAction.h"
#include "WriteAction.h"
#include "ErrorAction.h"

File *SymbolicLink::getTargetFile() const {
    return FileSystem::getInstance().getFile(target_path);
}

std::unique_ptr<Action> SymbolicLink::CreateReadAction(ReadRequest &request) const {

    switch (request.command) {
        case CommandType::LIST:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        case CommandType::READ: {
            File* targetFile = getTargetFile();
            if (targetFile == nullptr) {
                return std::make_unique<ErrorAction>(Utilities::BrokenLinkMsg());
            }
            return targetFile->CreateReadAction(request);
        }
        default:
            return nullptr;
    }
}

std::unique_ptr<Action> SymbolicLink::CreateWriteAction(WriteRequest &request) const {
    switch (request.command) {
        case CommandType::DELETE:
            return std::make_unique<DeleteAction>(request);
        case CommandType::WRITE:
            {
            File* targetFile = getTargetFile();
            if (targetFile == nullptr) {
                return std::make_unique<ErrorAction>(Utilities::BrokenLinkMsg());
            }
            return targetFile->CreateWriteAction(request);
            }
        case CommandType::CREATE: {
            File* targetFile = getTargetFile();
            if (targetFile == nullptr) {
                return std::make_unique<ErrorAction>(Utilities::BrokenLinkMsg());
            }
            return targetFile->CreateWriteAction(request);
            }
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


