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
private:
    std::shared_ptr<Directory> rootDirectory;
    std::vector<std::string> SuccsCmndHistory;
    // ─── Singleton constrainers ──────────────────────────────────────────────
    FileSystem();
    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(const FileSystem&) = delete;

    // ── Command handlers ─────────────────────────────────────────────────────
    std::unique_ptr<Action> handleHelp();
    std::unique_ptr<Action> handleRead(const std::vector<std::string>& args);
    std::unique_ptr<Action> handleList(const std::vector<std::string>& args);
    std::unique_ptr<Action> handleWrite(const std::vector<std::string>& args);
    std::unique_ptr<Action> handleCreate(const std::vector<std::string>& args);
    std::unique_ptr<Action> handleDelete(const std::vector<std::string>& args);
    std::unique_ptr<Action> handleSearch(const std::vector<std::string>& args);
    void handleHistory(const std::vector<std::string>& args);

public:
    ~FileSystem();

    // Singleton instance getter
    static FileSystem& getInstance();

    void run(); // interactive shell

    File* getFile(const std::string& path) const;

    Directory* getRoot() const { return rootDirectory.get(); }

}
