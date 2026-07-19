#include "TextFile.h"
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

std::unique_ptr<Action> TextFile::CreateReadAction(ReadRequest& request) const {
    switch (request.command) {
        case CommandType::READ:
            return std::make_unique<ReadAction>(request);
        case CommandType::LIST:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        default:
            return nullptr;
    }
}

std::unique_ptr<Action> TextFile::CreateWriteAction(WriteRequest &request) const {
    switch (request.command) {
        case CommandType::WRITE:
            return std::make_unique<WriteAction>(request);
        case CommandType::CREATE:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        case CommandType::DELETE:
            return std::make_unique<DeleteAction>(request);
        default:
            return nullptr;
    }
}

std::unique_ptr<Action> TextFile::CreateSearchAction(SearchRequest &request) const {
    return std::make_unique<SearchAction>(request);
}

void TextFile::WriteContent(const std::string &content) {
    fileContent.push_back(content);
}

const std::vector<std::string> &TextFile::ReadContent() const {
    return fileContent;
}





