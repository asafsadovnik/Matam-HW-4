#pragma once
#include "File.h"
#include <string>
#include <memory>

class Action; // Forward declaration

class SymbolicLink : public File {

public:

    SymbolicLink(const std::string& name , Directory* parent ,
        const std::string targetPath) : File(name , parent) , target_path(targetPath) {}
    virtual ~SymbolicLink () override = default;

    File* getTargetFile() const;

    std::unique_ptr<Action> CreateReadAction(ReadRequest &request) const override;
    std::unique_ptr<Action> CreateWriteAction(WriteRequest &request) const override;
    std::unique_ptr<Action> CreateSearchAction(SearchRequest &request) const override;
    virtual std::unique_ptr<Action> CreateImportAction(WriteRequest& request) const override;
    virtual std::unique_ptr<Action> CreateExportAction(WriteRequest& request) const override;

private:
    std::string target_path;
};