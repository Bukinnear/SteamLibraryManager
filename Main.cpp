#include <conio.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
//cl /EHsc Main.cpp /nologo /std:c++latest

std::vector<std::filesystem::directory_entry> dl;

bool load_settings();
void run_setup();
void scan_directory(std::string s);

int main()
{    

    if (!load_settings())
    {
        run_setup();
    }
    
    scan_directory("c:/");
    

    for (auto &p : dl)
    {
        std::cout << p.path().filename() << std::endl;
    }

    std::cout << "Press any key to continue..." << std::endl;    
    getch();

    return 0;
}

bool load_settings()
{
    // check for valid settings file
    return false;
}

void run_setup()
{
    // create new valid settings file
}

void scan_directory (std::string directory)
{
    for (auto &p : std::filesystem::directory_iterator(directory))
    {
        dl.push_back(p);        
    }
}