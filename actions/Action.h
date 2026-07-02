#pragma once
#include <string>

class Action
{
public:
    virtual ~Action() = default;

    /**
     * @brief Executes the action
     */
    virtual void execute() const = 0;
};
