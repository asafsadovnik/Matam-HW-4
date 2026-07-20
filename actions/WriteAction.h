//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class WriteAction : public Action {
private:
    std::string fileName;
    std::vector<std::string> content;
public:
    WriteAction(const WriteRequest&);
    ~WriteAction() override = default;
    void execute() const override;
};