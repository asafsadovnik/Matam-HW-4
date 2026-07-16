//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class DeleteAction : public Action {
public:
    DeleteAction(const std::string& dirPath, std::string& filename);
    ~DeleteAction() override = default;
    void execute() override;
};