//
// Created by asafi on 16/07/2026.
//
#pragma once

#include "Action.h"

class SearchAction : public Action {
private:
    std::string& fileName;
    std::string& text;
public:
    SearchAction(const std::string& type, const std::string& dirPath, const std::string& fileName, const std::string& text);
    ~SearchAction() override = default;
    void execute() override;
};