#pragma once
#define HW4_2526B_HISTORYACTION_H
#include "Action.h"
#include "Utilities.h"
#include <vector>
#include <string>

class HistoryAction : public Action {
private:
    const std::vector<std::string>& historyRef;

public:
    HistoryAction(const std::vector<std::string>& history) : historyRef(history) {}

    void execute() const override {
        Utilities::printFileContent(historyRef);
    }
};
