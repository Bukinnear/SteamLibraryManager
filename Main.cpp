#include <conio.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

//cl /EHsc Main.cpp /nologo /std:c++latest

// commands
// 1. List all games in a specific library (by size)
// 2. List all games in specific library (aphabetical)
// 3. List all installed games
// 4. Change settings
//      1. Add a library location
//      2. Remove a library location

struct app_details
{
    // name
    // number
    // filepath
    // library id <- this will require error checking
};

void print_header();
bool load_settings();
bool save_settings();
void run_setup();
void scan_directory(std::string s);

std::filesystem::directory_entry libraryfilepath;
std::filesystem::directory_entry libraryapps;

int main()
{    
    print_header();

    if (!load_settings())
    {
        run_setup();
        save_settings();
    }  

    std::cout << "-------------------------------------------\nListing all folders found in library " << libraryfilepath.path().string() << std::endl << "-------------------------------------------" << std::endl << std::endl;
    {
        int index = 1;
        for (auto &p : std::filesystem::directory_iterator(libraryapps))
        {
            std::cout << p.path().filename().string() << std::endl;
            index++;
        }
    }
    
    std::cout << std::endl << "finished" << std::endl;

    // std::cout << "Press any key to continue..." << std::endl;    
    // getch();

    return 0;
}

void print_header()
{
    std::cout << std::endl << "-------------------------------------------\n-                                         -\n-          Steam Library Manager          -\n-                                         -\n-------------------------------------------" << std::endl << std::endl;
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
        if (std::filesystem::exists(line))
        {
            libraryfilepath.assign(line);
            libraryapps.assign( libraryfilepath.path().string().append("\\steamapps\\common"));
            // std::cout << "library path is: " << libraryfilepath << std::endl;
        }
    }

    return true;
}

bool save_settings()
{    
    std::ofstream savefile("config.txt", std::ios::out);
    savefile << libraryfilepath.path().string();
    savefile.close();

    if (savefile.fail() == 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void run_setup()
{
    while (!libraryfilepath.exists())
    {
        std::cout << std::endl << "Library filepath is invalid." << std::endl << "Please enter a valid filepath:" << std::endl;        

        char inputbuffer[256];

        std::cin.getline(inputbuffer, sizeof inputbuffer);        
        std::cout << inputbuffer << std::endl;

        if (!std::filesystem::exists(inputbuffer))
        {
            std::cout << "path could not be found." << std::endl;
            continue;
        }
        
        libraryfilepath.assign(inputbuffer);
    }    
}

void scan_directory (std::filesystem::directory_entry dir)
{
    for (auto &p : std::filesystem::directory_iterator(dir))
    {
        std::cout << p << std::endl;
        // dl.push_back(p);
    }
}