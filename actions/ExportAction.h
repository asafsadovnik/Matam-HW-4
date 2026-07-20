//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"

class ExportAction : public Action {
private:
    std::string fileName;
    std::string targetPath;

public:
    ExportAction(WriteRequest&);
    void execute() const override;
};