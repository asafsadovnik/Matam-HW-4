//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class CreateAction : public Action {
private:
    std::string& fileName;
    std::string& targetPath;
public:
    CreateAction(const std::string& type, const std::string& dirPath, const std::string& fileName, const std::string& targetPath = "");
    ~CreateAction() override = default;
    void execute() override;
};