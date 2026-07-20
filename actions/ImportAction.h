//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class ImportAction : public Action {
private:
    std::string fileName;
    std::string targetPath;

public:
    ImportAction(WriteRequest&);
    void execute() const override;
};