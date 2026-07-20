#pragma once
#include <memory>
#include <string>
#include "TextFile.h"
#include "SymbolicLink.h"




//declaration of different actions: each ctor takes arguments based on requirements


class Action { //virtual class Action
protected:
    std::string dirPath;

    TextFile* resolveSymLink(const SymbolicLink* link) const; //check if symlink good & return textfile

public:
    Action() = default;
    Action(const BasicRequest&);
    virtual void execute() const = 0;
    virtual ~Action() = default;
};

