#pragma once
#include "Main.h"
#include <string>
#include <iostream>
#include "LibraryFolder.h"

/*
cl /EHsc Main.cpp Test.cpp  /nologo /std:c++latest
cd C:\Code\SteamLibraryManager
*/

int main(int argc, char const *argv[])
{
    for (;;)
    {
        char FolderPath[255];
        std::cout << "Enter a path: ";
        std::cin.getline(FolderPath, sizeof(FolderPath));

        LibraryFolder * folder = new LibraryFolder(FolderPath);

        auto Output = ("This folder is valid: " + std::string(folder->isValidDirectory() ? "True" : "False"));

        std::cout << Output << "\r\n\r\n";
    }
    return 0;
}