#pragma once
#include "Main.h"
#include "LibraryFolder.h"
#include "Library.h"
#include <string>
#include <iostream>

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

        Library * folder = new Library(FolderPath);

        //auto Output = ("This folder is valid: " + std::string(folder->isValidDirectory() ? "True" : "False") + "\r\nThe Path is: " + std::string(folder->getFolderPath()) + "\r\nThe Name is: " + folder->getFolderName());

        //std::cout << Output << "\r\n\r\n";
    }
    return 0;
}