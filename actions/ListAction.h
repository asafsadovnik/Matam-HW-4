//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"
#include "File.h"


class ListAction : public Action {
private:
    std::string fileName;

public:
    ListAction(const ReadRequest&);
    ~ListAction() override = default;
    void execute() const override;
};