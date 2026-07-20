#pragma once
#include "Action.h"
#include "Utilities.h"
#include <string>

class ErrorAction : public Action {
private:
    std::string errorMsg;
public:
    ErrorAction(const std::string& msg) : Action(BasicRequest()), errorMsg(msg) {}

    void execute() const override {
        Utilities::printError(errorMsg);
    }
};