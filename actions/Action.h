#pragma once
#include <string>



//declaration of different actions: each ctor takes arguments based on requirements


class Action { //virtual class Action
protected:
    std::string fileType;
    std::string dirPath;
public:
    Action(const std::string& fileType, const std::string& dirPath);
    virtual void execute() const = 0;
    virtual ~Action() = default;
};

