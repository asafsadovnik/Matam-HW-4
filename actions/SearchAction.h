//
// Created by asafi on 16/07/2026.
//
#pragma once

#include "Action.h"

class SearchAction : public Action {
private:
    std::string fileName;
    std::string text;
    void helperRecursive(File* fileToCheck, const std::string& wordToSearch, std::vector<std::string>& linesToPrint) const;
public:
    SearchAction(const SearchRequest&);
    ~SearchAction() override = default;
    void execute() const override;
};