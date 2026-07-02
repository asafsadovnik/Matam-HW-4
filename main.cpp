#include "FileSystem.h"

void program_runner()
{
    FileSystem::getInstance().run();
}

int main()
{
    program_runner();
    return 0;
}
