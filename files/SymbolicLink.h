#pragma once
#include "File.h"
#include "Utilities.h"
#include <string>
#include <vector>
#include <memory>

class SymbolicLink : public File {

public:
    SymbolicLink(const std::string& name , Directory* parent ,
        const std::string targetPath) : File(name , parent) , target_path(targetPath) {}
    virtual ~SymbolicLink () override = default;

    std::unique_ptr<Action> CreateReadAction(ReadRequest &request) const override;
    std::unique_ptr<Action> CreateWriteAction(WriteRequest &request) const override;
    std::unique_ptr<Action> CreateSearchAction(SearchRequest &request) const override;

private:
    std::string target_path;

    File* getTargetFile() const;
};