#pragma once
#include <conio.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <exception>
#include "Main.h"
#include "Library.h"
#include "Menu.h"
#include "Output.h"

namespace fs = std::filesystem;

// cl /EHsc Main.cpp Library.cpp Menu.cpp Output.cpp /nologo /std:c++latest
// cd C:\Code\SteamLibraryManager
 
int main()
{
    output::print_header();

    if (!load_settings())
    {
        run_setup();
        save_settings();
    }

    menu menu(&libraries);

    /**     
     * showProgramHeader();
     * 
     * loop
     * {     
        * try
        * {
            * selectedLibrary = menu.MakeLibrarySelection();
            * 
            * loop
            * {
                * 
            * }
        * }
        * catch (BackSelected)
        * {
            * break;
        * }
    * }
     * */

    std::cout << std::endl << "finished" << std::endl;
              
    // std::cout << "\n\nThe program will now exit.\n\nPress any key to continue..." << std::endl;
    // getch();

    return 0;
}

bool save_settings()
{
    fs::remove("config.txt");
    std::ofstream savefile("config.txt", std::ios::out);

    for (auto lib : libraries)
    {
        savefile << lib.path();
    }

    if (savefile.fail() == 0)
    {
        savefile.close();
        return true;
    }
    else
    {
        savefile.close();
        return false;
    }
}

bool load_settings()
{
    std::ifstream configfile("config.txt");
    if (!configfile.is_open())
    {        
        return false;
    }

    char line[256];

    while (configfile.getline(line, sizeof line))
    {        
        try
        {
            libraries.push_back(library(std::string(line)));
        }
        catch (InvalidLibrary e)
        {
            std::cout << "Error loading folder from config file:\n" << line << std::endl;
            std::cout << std::endl << e.what() << std::endl << std::endl;            
        }
        catch (...)
        {
            std::cout << "An error occurred while loading libraries from the configuration file. Check your library entries are valid" << std::endl;
        }
    }
    
    configfile.close();

    if (libraries.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void run_setup()
{
    while (libraries.empty())
    {
        std::cout << std::endl << "There are no Steam libraries set up." << std::endl << "Please enter a valid filepath (directory must contain steamapps subfolder):" << std::endl;

        char input_buffer[256];

        std::cin.getline(input_buffer, sizeof input_buffer);

        try 
        {
            libraries.push_back(library(std::string(input_buffer)));
        }
        catch (...)
        {
            std::cout << "An error occurred adding the specified path to libraries. Path may not be valid." << std::endl;
        }
    }
}


/*
int main(int argc, char const *argv[])
{ 
    if (!configFileExists())
    {
        runFirstSetup();
    }
     return 0;
} 

bool configFileExists()
{    
    return fs::exists("config.txt");
}

int runFirstSetup()
{
    std::vector<fs::directory_entry> allDrives = getAllDrivePaths();

    for (auto i : allDrives)   
    {
        std::cout << i.path().string() << "\n";
        auto dirIterator = fs::recursive_directory_iterator(i);

        for (auto p : dirIterator)
        {
            auto status = fs::status(p.path());

            std::cout << p.path().string() << "\n";
                        
            // https://stackoverflow.com/questions/11755422/c-how-to-retrieve-a-file-permission-and-ownership-via-win32-api
        }
    }
    
    return 0;
}

std::vector<std::filesystem::directory_entry> getAllDrivePaths()
{
    // All of this copied wholecloth from here:
    // https://stackoverflow.com/questions/18572944/getlogicaldrivestrings-and-char-where-am-i-doing-wrongly

    typedef wchar_t* LPWSTR, *PWSTR;

    std::vector<std::filesystem::directory_entry> returnVar;

    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};

    // use the correct variation:
    //https://stackoverflow.com/questions/20611865/argument-of-type-char-is-incompatible-with-parameter-of-type-lpwstr
    DWORD dwResult = GetLogicalDriveStringsA(dwSize, szLogicalDrives); 

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        char* szSingleDrive = szLogicalDrives;
        while(*szSingleDrive)
        {            
            if (fs::exists(szSingleDrive))
            {
                // printf("Drive: %s\n", szSingleDrive);
                returnVar.push_back(fs::directory_entry(szSingleDrive));
            }

            // get the next drive
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
    }
    return returnVar;
}
*/