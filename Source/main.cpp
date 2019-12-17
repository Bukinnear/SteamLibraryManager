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
        auto library = Library(MainLibGamePath);
        std::cout << library.ContainsFolder("Forager");
        //std::cout << "Library contains Forager: " << library.ContainsFolder("Forager");

        /*
        char FolderPath[255];
        std::cout << "Enter a path: ";
        std::cin.getline(FolderPath, sizeof(FolderPath));
        */                
    }
    return 0;
}