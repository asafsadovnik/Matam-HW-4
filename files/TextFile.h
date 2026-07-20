#pragma once
#include "File.h"
#include <string>
#include <vector>
#include <memory>

// ─────────────────────────────────────────────────────────────────────────────
// TextFile — a WORKED EXAMPLE of a concrete File (a leaf in the tree).
//
// This header is given to you as a reference so you can see how a concrete File
// looks: it stores its own data, implements getName/getParent, and builds the
// Actions for the operations it supports.
//
// Use this as a model to design your own Directory and SymbolicLink classes.
// You still have to implement TextFile's methods in TextFile.cpp.
// ─────────────────────────────────────────────────────────────────────────────
class TextFile : public File
{
public:
    TextFile(const std::string& name, Directory* parent) : File(name , parent) {}
    ~TextFile() override = default;

    virtual std::unique_ptr<Action> CreateReadAction(ReadRequest& request) const override;
    virtual std::unique_ptr<Action> CreateWriteAction(WriteRequest& request) const override;
    virtual std::unique_ptr<Action> CreateSearchAction(SearchRequest& request) const override;
    virtual std::unique_ptr<Action> CreateImportAction(WriteRequest& request) const override;
    virtual std::unique_ptr<Action> CreateExportAction(WriteRequest& request) const override;

    // TextFile-specific content API
    virtual void WriteContent(const std::string& content);          // append one line
    virtual const std::vector<std::string>& ReadContent() const;    // all lines


private:
    std::vector<std::string> fileContent;
};

