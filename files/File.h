#pragma once
#include "Action.h"
#include <string>
#include <memory>
#include <vector>

/*
Forward declarations of classes used in the request structs and File interface.
you need to include the actual headers in the .cpp files where you implement the methods.
feel free to add more forward declarations if you need them or change existing ones.
*/

// ─────────────────────────────────────────────────────────────────────────────
// Request structs
//
// Each command is described by a "request" that carries the data an Action
// needs to run. It is YOUR job to decide which fields each request needs
// (pointers to files, content, parent directory, flags, paths, ...).
//
// Tip: think about what information each Create*Action must hand to its Action.
// ─────────────────────────────────────────────────────────────────────────────

struct ReadRequest
{
    // TODO: add the fields your read actions need.
};

struct WriteRequest
{
    // TODO: add the fields your write/create/delete actions need.
};

struct SearchRequest
{
    // TODO: add the fields your search actions need.
};


// ─────────────────────────────────────────────────────────────────────────────
// File: the abstract component of the file-system tree.
//
// Every node in the tree (Directory, TextFile, SymbolicLink) is a File.
// Each concrete subtype is responsible for building the Action that performs
// a given operation on it (a "factory method" per operation).
//
// This is a pure interface: it is up to YOU to decide the data members and
// constructors of your concrete files.
// ─────────────────────────────────────────────────────────────────────────────
class File
{
public:
    virtual ~File() = default;

    std::string getName() const;

    // Each concrete File builds the Action appropriate for its own type.
    virtual std::unique_ptr<Action> CreateReadAction(ReadRequest& request) const = 0;
    virtual std::unique_ptr<Action> CreateWriteAction(WriteRequest& request) const = 0;
    virtual std::unique_ptr<Action> CreateSearchAction(SearchRequest& request) const = 0;

    // Hint: you will likely need Create*Action methods for import/export as well.
};
