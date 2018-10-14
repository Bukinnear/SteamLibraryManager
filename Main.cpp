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

namespace fs = std::filesystem;

// cl /EHsc Main.cpp /nologo /std:c++latest

// commands:
// 1. List all games in a specific library (by size)
// 2. List all games in specific library (aphabetical)
// 3. List all installed games
// 4. Change settings
//      1. Add a library location
//      2. Remove a library location
 
int main()
{
    print_header();

    if (!load_settings())
    {
        run_setup();
        save_settings();
    }

    
    std::cout << std::endl << "finished" << std::endl;
              
    // std::cout << "\n\nThe program will now exit.\n\nPress any key to continue..." << std::endl;
    // getch();

    return 0;
}

void print_header()
{
    std::cout << std::endl << "-------------------------------------------\n-                                         -\n-          Steam Library Manager          -\n-                                         -\n-------------------------------------------" << std::endl;
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