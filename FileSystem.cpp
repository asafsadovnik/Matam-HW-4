#include "FileSystem.h"
#include "Utilities.h"
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
#include "ErrorAction.h"
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
// A method that gets a path to a file (string) and return it's ptr (if exists)
File* FileSystem::getFile(const std::string& path) const {
    if (path == "/") { // If path is "/" return the root
        return rootDirectory.get();
    }

    // Split the path to parts. Run a loop from the root Directory -
    // on each iteration - find the next part in the current directory. if
    // is not exist return null_ptr. If exist - get into the directory and do another
    // iteration on the next part.
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
// A method that gets a ptr to a file and return the path to the file (only parents)
std::string FileSystem::getFilePath(File* file) const {
    if (file == nullptr) { // If file is not exist
        return ("File was not founded");
    }

    std::string currentPath = ""; // Create a string that will contain the path
    File* currentFile = file->getParent();

    while (currentFile->getParent() != nullptr && currentFile != nullptr) {
        currentPath = "/" + currentFile->getName() + currentPath;
        currentFile = currentFile->getParent();
    }
    // If the file is the root or one of its children - return "/", else return the path
    return currentPath.empty() ? "/" : currentPath ;
}

bool FileSystem::isBrokenLynk(SymbolicLink* link) {
    if (link == nullptr) {
        return true;
    }

    std::string targetPath = getFilePath(link);

    File* targetFile = getFile(targetPath);

    if (targetFile == nullptr) {
        return true;
    }

    if (targetFile->isDirectory()) {
        return true;
    }

    return false;
}

// ── handles ─────────────────────────────────────────────────────────────

std::unique_ptr<Action> FileSystem::handleHelp()
{
    return std::make_unique<HelpAction>();
}

std::unique_ptr<Action> FileSystem::handleRead(const std::vector<std::string> &args) {
    if (args.size() != 3) {
        return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
    }
    std::string dirPath = args[1];
    std::string fileName = args[2];

    File* file = getFile(dirPath);

    if (file == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    Directory* dir = dynamic_cast<Directory *>(file);
    if (dir == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    File* targetFile = dir->getChild(fileName);
    if (targetFile == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    ReadRequest request;
    request.DirPath = dirPath;
    request.FileName = fileName;
    request.command = CommandType::READ;
    return targetFile->CreateReadAction(request);
}

std::unique_ptr<Action> FileSystem::handleList(const std::vector<std::string> &args) {
    if (args.size() != 2) {
        return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
    }
    std::string dirPath = args[1];

    File* file = getFile(dirPath);

    if (file == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    SymbolicLink* symLink = dynamic_cast<SymbolicLink *>(file);
    if (symLink != nullptr) {
        if (isBrokenLynk(symLink)) {
            return std::make_unique<ErrorAction>(Utilities::BrokenLinkMsg());
        }
        return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
    }

    if (!file->isDirectory()) {
        return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
    }

    ReadRequest request;
    request.DirPath = dirPath;
    request.FileName = "";
    request.command = CommandType::LIST;
    return file->CreateReadAction(request);
}

std::unique_ptr<Action> FileSystem::handleWrite(const std::vector<std::string> &args) {
    if (args.size() < 3) {
        return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
    }
    std::string dirPath = args[1];
    std::string fileName = args[2];

    File* file = getFile(dirPath);

    if (file == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    Directory* dir = dynamic_cast<Directory *>(file);
    if (dir == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    File* targetFile = dir->getChild(fileName);
    if (targetFile == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    std::string newLine = Utilities::joinArgs(args.begin() + 3 , args.end());

    WriteRequest request;
    request.DirPath = dirPath;
    request.FileName = fileName;
    request.command = CommandType::WRITE;
    request.Content.push_back(newLine);
    return targetFile->CreateWriteAction(request);
}

std::unique_ptr<Action> FileSystem::handleCreate(const std::vector<std::string> &args) {
    if (args. size() < 4) {
        return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
    }

    std::string type = args[1];
    std::string dirPath = args[2];
    std::string fileName = args[3];

    if (type == "symlink") {
        if (args.size() != 5) {
            return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
        }
    } else if (type == "textfile" || type == "directory") {
        if (args.size() != 4) {
            return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
            }
        }
    else {
        return std::make_unique<ErrorAction>(Utilities::TypeErrorMsg());
    }

    File* file = getFile(dirPath);
    if (file == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    Directory* dir = dynamic_cast<Directory *>(file);
    if (dir == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    WriteRequest request;
    request.type = type;
    request.DirPath = dirPath;
    request.FileName = fileName;
    request.command = CommandType::CREATE;

    if (type == "symlink") {
        request.TargetPath = args[4];
    }

    return dir->CreateWriteAction(request);
}

std::unique_ptr<Action> FileSystem::handleDelete(const std::vector<std::string> &args) {
    if (args.size() != 3) {
        return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
    }
    std::string dirPath = args[1];
    std::string fileName = args[2];

    File* file = getFile(dirPath);
    if (file == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }
    Directory* dir = dynamic_cast<Directory *>(file);
    if (dir == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    File* targetFile = dir->getChild(fileName);
    if (targetFile == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    WriteRequest request;
    request.FileName = fileName;
    request.DirPath = dirPath;
    request.command = CommandType::DELETE;

    return targetFile->CreateWriteAction(request);
}

std::unique_ptr<Action> FileSystem::handleSearch(const std::vector<std::string> &args) {
    if (args.size() != 3) {
        return std::make_unique<ErrorAction>(Utilities::commandErrorMsg());
    }

    std::string dirPath = args[1];
    std::string word = args[2];

    File* file = getFile(dirPath);
    if (file == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    Directory* dir = dynamic_cast<Directory *>(file);
    if (dir == nullptr) {
        return std::make_unique<ErrorAction>(Utilities::FileNotFoundMsg());
    }

    SearchRequest request;
    request.DirPath = dirPath;
    request.word = word;
    request.FileName = "";

    return dir->CreateSearchAction(request);
}

void FileSystem::handleHistory(const std::vector<std::string> &args) {
    if (args.size() != 1) {
        throw std::runtime_error(Utilities::commandErrorMsg());
    }

    Utilities::printFileContent(SuccsCmndHistory);
}


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
            else if (cmd == "create")
            {
                action = handleCreate(args);
            }
            else if (cmd == "delete")
            {
                action = handleDelete(args);
            }
            else if (cmd == "list")
            {
                action = handleList(args);
            }
            else if (cmd == "read")
            {
                action = handleRead(args);
            }
            else if (cmd == "write")
            {
                action = handleWrite(args);
            }
            else if (cmd == "search")
            {
                action = handleSearch(args);
            }
            else if (cmd == "history")
            {
                handleHistory(args);
            }
            else
            {
                throw std::runtime_error(Utilities::commandErrorMsg());
            }

            if (action)
            {
                action->execute();
                Utilities::printActionExecuted(cmd);

                if (cmd != "help") {
                    SuccsCmndHistory.push_back(line);
                }
            } else if (cmd == "history") {
                handleHistory(args);
                Utilities::printActionExecuted(cmd);
                SuccsCmndHistory.push_back(line);
            }
        }
        catch (const std::exception& e)
        {
            Utilities::printError(e.what());
        }
    }
}
