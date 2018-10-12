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

std::filesystem::directory_entry libraryfilepath;

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

    run_setup();
    save_settings();

    std::cout << "Press any key to continue..." << std::endl;    
    // getch();

    return 0;
}

bool load_settings()
{
    // check for valid settings file
    return false;
}

bool save_settings()
{    
    std::ofstream savefile("config.txt", std::ios::out);
    savefile << libraryfilepath.path().string();

    return savefile.fail();
}

void run_setup()
{
    while (!libraryfilepath.exists())
    {
        char buffer[256];        

        std::cout << "Please enter a valid filepath:" << std::endl;
        std::cin >> buffer;
        libraryfilepath.replace_filename(buffer);

        // std::cout << libraryfilepath << std::endl;
    }
}

void scan_directory (std::string directory)
{
    for (auto &p : std::filesystem::directory_iterator(directory))
    {
        // dl.push_back(p);        
    }
}