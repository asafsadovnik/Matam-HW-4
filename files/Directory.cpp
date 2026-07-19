#include "Directory.h"
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



std::unique_ptr<Action> Directory::CreateReadAction(ReadRequest& request) const  {
    switch (request.command) {
        case CommandType::READ:
            return std::make_unique<ListAction>(request);
        case CommandType::LIST:
            return std::make_unique<ListAction>(request);
        default:
            return nullptr;
    }

}

std::unique_ptr<Action> Directory::CreateWriteAction(WriteRequest &request) const {
    switch (request.command) {
        case CommandType::WRITE:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        case CommandType::CREATE:
            return std::make_unique<CreateAction>(request);
        case CommandType::DELETE:
            return std::make_unique<DeleteAction>(request);
        default:
            return nullptr;
    }
}

std::unique_ptr<Action> Directory::CreateSearchAction(SearchRequest &request) const {
        return std::make_unique<SearchAction>(request);
}
void Directory::addChild(std::shared_ptr<File> newFile) {
    directoryChildren.push_back(newFile);
}

void Directory::removeChild(const std::string &fileName) {
    for (auto it = directoryChildren.begin() ; it != directoryChildren.end() ;
        it++) {
        if ((*it)->getName() == fileName) {
            directoryChildren.erase(it);
            break;
        }
    }
}

File* Directory::getChild(const std::string& fileName) const {
    for (const auto& child : directoryChildren){
        if (child->getName() == fileName) {
            return child.get();
        }
    }
    return nullptr;
}



