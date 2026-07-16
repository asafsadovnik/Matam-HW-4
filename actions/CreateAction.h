//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class CreateAction : public Action {
public:
    CreateAction(const std::string& type, const std::string& dirPath, const std::string& name, const std::string& targetPath = "");
    ~CreateAction() override = default;
    void execute() override;
};