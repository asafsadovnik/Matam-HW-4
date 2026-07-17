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



std::unique_ptr<Action> Directory::CreateReadAction(ReadRequest& request) const  {
    switch (request.command) {
        case CommandType::READ:
            return std::make_unique<PrintChildsAction>(this);
        case CommandType::LIST:
            return std::make_unique<PrintChildsAction>(this);
        default:
            return nullptr;
    }

}

std::unique_ptr<Action> Directory::CreateWriteAction(WriteRequest &request) const {
    switch (request.command) {
        case CommandType::WRITE:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        case CommandType::CREATE:
            return std::make_unique<NewDirAction>(this, request.type, request.FileName);
        case CommandType::DELETE:
            return std::make_unique<DeleteAction>(this, request.FileName);
        default:
            return nullptr;
    }
}

std::unique_ptr<Action> Directory::CreateSearchAction(SearchRequest &request) const {
        return std::make_unique<SearchLineAction>(this , request.word);
}
void Directory::addChild(std::shared_ptr<File> newFile) {
    directoryChildren.push_back(newFile);
}

void Directory::removeChild(std::string &fileName) {
    for (auto it = directoryChildren.begin() ; it != directoryChildren.end() ;
        it++) {
        if ((*it)->getName() == fileName) {
            directoryChildren.erase(it);
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

const std::vector<std::shared_ptr<File>>& getChildes() const
{ return directoryChild; }


