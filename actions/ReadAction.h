//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"

class ReadAction : public Action {
private:
    std::string fileName;
public:
    ReadAction(const ReadRequest& request);
    ~ReadAction() override = default;
    void execute() const override;
};


