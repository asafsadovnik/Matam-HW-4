//
// Created by asafi on 16/07/2026.
//
#pragma once
#include "Action.h"


class DeleteAction : public Action {
private:
    std::string fileName;
public:
    DeleteAction(const WriteRequest&);
    ~DeleteAction() override = default;
    void execute() const override;
};