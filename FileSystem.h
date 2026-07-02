#pragma once
#include "Action.h"
#include "File.h"
#include <memory>
#include <string>
#include <vector>


// ─────────────────────────────────────────────────────────────────────────────
// FileSystem — the Singleton front-end for the whole virtual FS.
//
// It owns the root directory, parses each command line, builds the right Action
// and executes it. Only `help` and `exit` are wired for you; the rest of the
// commands (create, list, read, write, delete, search, import, export, history)
// are YOUR job.
// ─────────────────────────────────────────────────────────────────────────────
class FileSystem
{
    // Singleton - private constructor
    FileSystem();

    // Delete copy constructor and assignment operator
    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;

    // ── Command handlers ─────────────────────────────────────────────────────
    // Provided example:
    std::unique_ptr<Action> handleHelp();

    // TODO: add the handlers for the remaining commands, e.g.:

public:
    ~FileSystem();

    // Singleton instance getter
    static FileSystem& getInstance();

    void run(); // interactive shell

};
