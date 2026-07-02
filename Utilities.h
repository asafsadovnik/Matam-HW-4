#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "File.h"

class Utilities
{
public:
    /**
     * @brief Parses a command line string into individual arguments
     *
     * @param line The command line string to parse
     * @return std::vector<std::string> Vector of parsed arguments separated by whitespace
     *
     * @note Does not throw exceptions
     */
    static std::vector<std::string> parseCommand(const std::string &line);

    /**
     * @brief Splits a file path into its component parts
     *
     * @param path The file path string to split
     * @return std::vector<std::string> Vector of path components separated by '/' (empty components are skipped)
     *
     * @note Does not throw exceptions
     */
    static std::vector<std::string> split(const std::string &path);

    /**
     * @brief Generates an error message for a file not found scenario
     *
     * @return std::string The error message
     *
     * @note Does not throw exceptions
     */
    static std::string FileNotFoundMsg();

    static std::string BrokenLinkMsg();

    static std::string TypeErrorMsg();

    static std::string commandErrorMsg();

    static std::string DirectoryNotEmptyMsg();

    static std::string HostFileErrorMsg();

    /**
     * @brief Reads all lines from an input stream (e.g. a host file)
     *
     * @param in An open input stream
     * @return std::vector<std::string> The lines read from the stream
     */
    static std::vector<std::string> readLinesFromStream(std::ifstream& in);

    /**
     * @brief Writes each line to an output stream (e.g. a host file)
     *
     * @param out An open output stream
     * @param lines The lines to write, one per line
     */
    static void writeLinesToStream(std::ofstream& out, const std::vector<std::string>& lines);

    /**
     * @brief Prints the file system command prompt
     *
     * @note Does not throw exceptions
     */
    static void printPrompt();

    /**
     * @brief Prints an action execution confirmation message
     *
     * @param actionDescription The description of the action that was executed
     *
     * @note Does not throw exceptions
     */
    static void printActionExecuted(const std::string &actionDescription);

    /**
     * @brief Prints an error message
     *
     * @param errorMsg The error message to print
     *
     * @note Does not throw exceptions
     */
    static void printError(const std::string &errorMsg);

    /**
     * @brief Prints the type error message
     *
     * @note Does not throw exceptions
     */
    static void printTypeError();

    static void ListFiles(const std::vector<std::shared_ptr<File>>& files);

    static void printFileContent(const std::vector<std::string>& content);

    /**
     * @brief Joins all strings from [it, end) into a single space-separated string
     *
     * @param it   Iterator to the first element to join
     * @param end  Past-the-end iterator
     * @return std::string The joined string
     */
    static std::string joinArgs(std::vector<std::string>::const_iterator it,
                                std::vector<std::string>::const_iterator end);
};
