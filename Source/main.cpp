#pragma once
#include "Main.h"

/*
cl /EHsc Main.cpp Test.cpp  /nologo /std:c++latest
cd C:\Code\SteamLibraryManager
*/

int main(int argc, char const *argv[])
{
    for (;;)
    {
        //auto library = Library(MainLibPath);
        auto Folder = LibraryFolder(ExampleGameFolder);
        std::cout << "Game size in GB: " << Folder.GetFolderSize() / 1024 /1024;

        /*
        char FolderPath[255];
        std::cout << "Enter a path: ";
        std::cin.getline(FolderPath, sizeof(FolderPath));
        */                
    }
    return 0;
}