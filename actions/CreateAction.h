//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class CreateAction : public Action {
private:
    std::string fileName;
    std::string fileType;
    std::string targetPath;
public:
    CreateAction(const WriteRequest&);
    ~CreateAction() override = default;
    void execute() const override;
};