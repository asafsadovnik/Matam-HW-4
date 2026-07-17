#pragma once
#include <memory>
#include <string>
#include "TextFile.h"
#include "SymbolicLink.h"




//declaration of different actions: each ctor takes arguments based on requirements


class Action { //virtual class Action
protected:
    std::string fileType;
    std::string dirPath;

    std::shared_ptr<TextFile> resolveSymLink(const std::shared_ptr<SymbolicLink>& link) const; //check if symlink good & return textfile

public:
    Action(const std::string& fileType, const std::string& dirPath);
    virtual void execute() const = 0;
    virtual ~Action() = default;
};

