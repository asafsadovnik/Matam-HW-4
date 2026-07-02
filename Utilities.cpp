#include "Utilities.h"
#include <sstream>
#include <iostream>

std::vector<std::string> Utilities::parseCommand(const std::string &line)
{
    std::vector<std::string> args;
    std::stringstream ss(line);
    std::string arg;

    while (ss >> arg)
    {
        args.push_back(arg);
    }

    return args;
}

std::vector<std::string> Utilities::split(const std::string &path)
{
    std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string item;

    while (std::getline(ss, item, '/'))
    {
        if (!item.empty())
            parts.push_back(item);
    }
    return parts;
}

std::string Utilities::FileNotFoundMsg()
{
    return "File not found";
}

std::string Utilities::BrokenLinkMsg()
{
    return "Broken symbolic link";
}

std::string Utilities::TypeErrorMsg()
{
    return "File type mismatch";
}

std::string Utilities::commandErrorMsg()
{
    return "Invalid command or arguments";
}

std::string Utilities::DirectoryNotEmptyMsg()
{
    return "Directory not empty";
}

std::string Utilities::HostFileErrorMsg()
{
    return "Could not open host file";
}

std::vector<std::string> Utilities::readLinesFromStream(std::ifstream& in)
{
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line))
        lines.push_back(line);
    return lines;
}

void Utilities::writeLinesToStream(std::ofstream& out, const std::vector<std::string>& lines)
{
    for (const auto& line : lines)
        out << line << "\n";
}

void Utilities::printPrompt()
{
    std::cout << "fileSystem cmd> " << std::endl;
}

void Utilities::printActionExecuted(const std::string &actionDescription)
{
    std::cout << "--- Action: " << actionDescription << " executed ---" << std::endl;
}

void Utilities::printError(const std::string &errorMsg)
{
    std::cout << "Error: " << errorMsg << std::endl;
}

void Utilities::printTypeError()
{
    std::cout << "Error: " << TypeErrorMsg() << std::endl;
}

void Utilities::ListFiles(const std::vector<std::shared_ptr<File>> &files)
{
    for (const auto& file : files)
    {
        std::cout << " - " << file->getName() << std::endl;
    }
}

void Utilities::printFileContent(const std::vector<std::string>& content)
{
    for (const auto& line : content)
    {
        std::cout << line << std::endl;
    }
}

std::string Utilities::joinArgs(std::vector<std::string>::const_iterator it,
                                std::vector<std::string>::const_iterator end)
{
    std::string result;
    for (; it != end; ++it)
    {
        if (!result.empty())
            result += " ";
        result += *it;
    }
    return result;
}
