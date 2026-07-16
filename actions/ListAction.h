//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class ListAction : public Action {
public:
    ListAction(std::string& dirPath);
    ~ListAction() override = default;
    void execute() override;
};