#include "TextFile.h"
// Add Actions (#include "[name of Action]")

std::unique_ptr<Action> TextFile::CreateReadAction(ReadRequest& request) const {
    switch (request.command) {
        case CommandType::READ:
            return std::make_unique<PrintLinesAction>(this);
        case CommandType::LIST:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        default:
            return nullptr;
    }
}

std::unique_ptr<Action> TextFile::CreateWriteAction(WriteRequest &request) const {
    switch (request.command) {
        case CommandType::WRITE:
            return std::make_unique<AddLinesAction>(this, request.Content);
        case CommandType::CREATE:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        case CommandType::DELETE:
            return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
        default:
            return nullptr;
    }
}

std::unique_ptr<Action> TextFile::CreateSearchAction(SearchRequest &request) const {
    return std::make_unique<SearchWordAction>(this , request.word);
}

void TextFile::WriteContent(const std::string &content) {
    fileContent.push_back(content);
}

const std::vector<std::string> &TextFile::ReadContent() const {
    return fileContent;
}





