//
// Created by asafi on 16/07/2026.
//
#pragma once

#include "Action.h"


class SearchAction : public Action {
public:
    SearchAction(const std::string& type, const std::string& dirPath, const std::string& name, const std::string& text);
    ~SearchAction() override = default;
    void execute() override;
};