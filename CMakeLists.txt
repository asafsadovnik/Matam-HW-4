cmake_minimum_required(VERSION 4.0)
project(HW4_2526B)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(actions)
include_directories(files)

add_executable(HW4_2526B
        actions/Action.h
        actions/HelpAction.cpp
        actions/HelpAction.h
        files/File.h
        files/TextFile.h
        FileSystem.cpp
        FileSystem.h
        main.cpp
        Utilities.cpp
        Utilities.h
        files/SymbolicLink.cpp
        actions/Action.cpp
        files/TextFile.cpp)
