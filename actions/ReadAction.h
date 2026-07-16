//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"

class ReadAction : public Action {
private:
    std::string fileName;
public:
    ReadAction(const std::string& fileType, const std::string& dirPath, const std::string& fileName);
    ~ReadAction() override = default;
    void execute() override;
};


