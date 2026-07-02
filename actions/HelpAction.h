#pragma once
#include "Action.h"
#include <string>

class HelpAction : public Action
{
public:
    static const std::string HELP_MSG;
    static const std::string EXIT_MSG;
    static const std::string LIST_MSG;
    static const std::string CREATE_MSG;
    static const std::string READ_MSG;
    static const std::string DELETE_MSG;
    static const std::string WRITE_MSG;
    static const std::string SEARCH_MSG;
    static const std::string HISTORY_MSG;
    static const std::string IMPORT_MSG;
    static const std::string EXPORT_MSG;

    HelpAction() = default;
    void execute() const override;
};
