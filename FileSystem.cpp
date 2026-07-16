#include "FileSystem.h"
#include "Utilities.h"
#include "Action.h"
#include "HelpAction.h"
#include "Directory.h"
#include "TextFile.h"
#include "SymbolicLink.h"
// TODO: include the headers of the files/actions you implement
//       (Directory.h, TextFile.h, SymbolicLink.h, FileFactory.h, your actions, ...)
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>


FileSystem::FileSystem()
{
    rootDirectory = std::make_shared<Directory>("/", nullptr);
}

FileSystem::~FileSystem() = default;

FileSystem& FileSystem::getInstance()
{
    static FileSystem instance;
    return instance;
}

File* FileSystem::getFile(const std::string& path) const {
    if (path == "/") {
        return rootDirectory.get();
    }

    std::vector<std::string> pathParts = Utilities::split(path);
    File* currentFile = rootDirectory.get();
    for (std::string& part : pathParts) {
        if (part.empty()) continue;
        Directory* currentDir = dynamic_cast<Directory *>(currentFile);
        if (!currentDir) {
            return nullptr;
        }
        currentFile = currentDir->getChild(part);
        if (!currentFile) {
            return nullptr;
        }
}
    return currentFile;
}


std::unique_ptr<Action> FileSystem::handleHelp()
{
    return std::make_unique<HelpAction>();
}

// TODO: implement the remaining command handlers (create, list, read, write,
//       delete, search, import, export). Each one should validate its
//       arguments, locate the relevant file/directory, build the matching
//       request, and return the Action produced by the file's Create*Action.

// ── Main CLI loop ─────────────────────────────────────────────────────────────

void FileSystem::run()
{
    std::string line;
    while (true)
    {
        Utilities::printPrompt();
        if (!std::getline(std::cin, line))
            break;

        auto args = Utilities::parseCommand(line);
        if (args.empty())
            continue;

        const std::string& cmd = args[0];

        try
        {
            std::unique_ptr<Action> action;

            if (cmd == "exit")
            {
                break;
            }
            else if (cmd == "help")
            {
                action = handleHelp();
            }
            // TODO: add the other commands here, e.g.:
            else
            {
                throw std::runtime_error(Utilities::commandErrorMsg());
            }

            if (action)
            {
                action->execute();
                Utilities::printActionExecuted(cmd);
                // TODO: record executed commands in `history` (help/history are
                //       usually NOT recorded).
            }
        }
        catch (const std::exception& e)
        {
            Utilities::printError(e.what());
        }
    }
}
