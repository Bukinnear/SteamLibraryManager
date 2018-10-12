#include <conio.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
//cl /EHsc Main.cpp /nologo /std:c++latest

std::vector<std::filesystem::directory_entry> dl;

bool load_settings();
bool save_settings();
void run_setup();
void scan_directory(std::string s);

std::filesystem::directory_entry library_filepath;

int main()
{    

    // if (!load_settings())
    // {
    //     run_setup();
    // }
    
    // scan_directory("c:/");
    
    // for (auto &p : dl)
    // {
    //     std::cout << p.path().filename() << std::endl;
    // }

    std::cout << "Press any key to continue..." << std::endl;    
    getch();

    return 0;
}

bool load_settings()
{
    // check for valid settings file
    return false;
}

bool save_settings()
{
    // save settings to file
    return true;
}

void run_setup()
{
    while (!library_filepath.exists())
    {
        char buffer[256];        

        std::cout << "Please enter a valid filepath:" << std::endl;
        std::cin >> buffer;
        library_filepath.replace_filename(buffer);

        std::cout << library_filepath << std::endl;
    }
}

void scan_directory (std::string directory)
{
    for (auto &p : std::filesystem::directory_iterator(directory))
    {
        // dl.push_back(p);        
    }
}