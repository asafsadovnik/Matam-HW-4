//
// Created by asafi on 16/07/2026.
//

#include "Action.h"
#include "../Utilities.h"
#include "TextFile.h"
#include "File.h"
#include "FileSystem.h"


Action::Action(const std::string& fileType, const std::string& dirPath) : fileType(fileType), dirPath(dirPath) {}

