//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class DeleteAction : public Action {
private:
    std::string& fileName;
public:
    DeleteAction(const std::string& fileType, const std::string& dirPath, std::string& filename);
    ~DeleteAction() override = default;
    void execute() override;
};