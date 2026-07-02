#include "HelpAction.h"
#include <iostream>

const std::string HelpAction::HELP_MSG = "  help                 - Show this help message";
const std::string HelpAction::EXIT_MSG = "  exit                 - Exit the shell";
const std::string HelpAction::LIST_MSG = "  list [DirPath]          - List files in directory at [DirPath]";
const std::string HelpAction::CREATE_MSG = "  create [type] [DirPath] [name] - Create a new file or directory or symbolic link of [type] at [DirPath] with [name]";
const std::string HelpAction::READ_MSG = "  read [DirPath] [FileName]       - Read and display contents of file [DirPath/FileName].";
const std::string HelpAction::DELETE_MSG = "  delete [DirPath] [FileName]     - Delete the file [DirPath/FileName].";
const std::string HelpAction::WRITE_MSG = "  write [DirPath] [FileName] [word1] [word2] [word3] ...      - Write to the file [word1 word2 word3 ...] to the end of [DirPath/FileName].";
const std::string HelpAction::SEARCH_MSG =
    R"(  search [DirPath] [FileName] [word]  - Search for [word] in files under [DirPath/FileName]
                                       If [FileName] is a file, print the lines that contain [word].
                                       If [FileName] is a symbolic link, follow the link and print the lines that contain [word].
                                       If [FileName] is a directory, print the TextFiles (and nested TextFiles) that contain [word] (Symbolic Links not included).)";
const std::string HelpAction::HISTORY_MSG = "  history              - Show the list of executed actions in order";
const std::string HelpAction::IMPORT_MSG = "  import [HostPath] [DirPath] [FileName]  - Append the content of the host file [HostPath] to the TextFile [DirPath/FileName]";
const std::string HelpAction::EXPORT_MSG = "  export [DirPath] [FileName] [HostPath]  - Write the content of the TextFile [DirPath/FileName] to the host file [HostPath]";

void HelpAction::execute() const
{
    std::cout << "Available commands:\n"
              << HELP_MSG << "\n"
              << EXIT_MSG << "\n"
              << LIST_MSG << "\n"
              << CREATE_MSG << "\n"
              << READ_MSG << "\n"
              << DELETE_MSG << "\n"
              << WRITE_MSG << "\n"
              << SEARCH_MSG << "\n"
              << HISTORY_MSG << "\n"
              << IMPORT_MSG << "\n"
              << EXPORT_MSG << "\n";
}
