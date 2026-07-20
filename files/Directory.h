#pragma once
#include "File.h"
#include "Utilities.h"
#include <string>
#include <vector>
#include <memory>

class Directory : public File
{
public:
    Directory(const std::string& name , Directory* parent) : File(name , parent) {}
    virtual ~Directory() = default;

    virtual std::unique_ptr<Action> CreateReadAction(ReadRequest& request) const override;
    virtual std::unique_ptr<Action> CreateWriteAction(WriteRequest& request) const override;
    virtual std::unique_ptr<Action> CreateSearchAction(SearchRequest& request) const override;
    virtual std::unique_ptr<Action> CreateImportAction(WriteRequest& request) const override;
    virtual std::unique_ptr<Action> CreateExportAction(WriteRequest& request) const override;

    void  addChild(std::shared_ptr<File> newFile);
    void removeChild(const std::string& fileName);
    File* getChild(const std::string& fileName) const;
    const std::vector<std::shared_ptr<File>>& getChildes() const
    { return directoryChildren; }


private:
    std::vector<std::shared_ptr<File>> directoryChildren;
};