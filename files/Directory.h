#pragma once
#include "File.h"
#include "Utilities.h"
#include <string>
#include <vector>
#include <memory>
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

class Directory : public File
{
public:
    Directory(const std::string& name , Directory* parent) : File(name , parent) {}
    virtual ~Directory() = default;

    virtual std::unique_ptr<Action> CreateReadAction(ReadRequest& request) const override;
    virtual std::unique_ptr<Action> CreateWriteAction(WriteRequest& request) const override;
    virtual std::unique_ptr<Action> CreateSearchAction(SearchRequest& request) const override;

    void  addChild(std::shared_ptr<File> newFile);
    void removeChild(std::string& fileName);
    File* getChild(const std::string& fileName) const;
    const std::vector<std::shared_ptr<File>>& getChildes() const
    { return directoryChildren; }


private:
    std::vector<std::shared_ptr<File>> directoryChildren;
};