//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class WriteAction : public Action {
private:
    std::string fileName;
    std::string& text;
public:
    WriteAction(const std::string& type, const std::string& dirPath, const std::string& fileName, const std::string& text);
    ~WriteAction() override = default;
    void execute() override;
};