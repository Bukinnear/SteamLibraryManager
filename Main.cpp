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
    // library id
};

void print_header();
bool save_settings();
bool load_settings();
void run_setup();
void scan_library(std::filesystem::directory_entry dir);
std::filesystem::directory_entry apps_directory(std::filesystem::directory_entry dir);
void print_sub_directories(std::filesystem::directory_entry dir);

std::vector<std::filesystem::directory_entry> libraryfilepaths;

int main()
{
    print_header();

    if (!load_settings())
    {
        run_setup();
        save_settings();
    }

    print_sub_directories(apps_directory(libraryfilepaths[0]));

    std::cout << std::endl
              << "finished" << std::endl;
              
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
    std::ofstream savefile("config.txt", std::ios::out);

    for (auto library : libraryfilepaths)
    {
        savefile << library.path().string();
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
        if (std::filesystem::exists(line))
        {
            libraryfilepaths.push_back(std::filesystem::directory_entry(line));
        }
    }

    configfile.close();

    return true;
}

void run_setup()
{
    while (libraryfilepaths.empty())
    {
        std::cout << std::endl << "There are no Steam libraries set up." << std::endl << "Please enter a valid filepath:" << std::endl;

        char inputbuffer[256];

        std::cin.getline(inputbuffer, sizeof inputbuffer);
        std::cout << inputbuffer << std::endl;

        if (!std::filesystem::exists(inputbuffer))
        {
            std::cout << "path is invalid, or could not be accessed." << std::endl;
            continue;
        }

        libraryfilepaths.push_back(std::filesystem::directory_entry(inputbuffer));
    }
}

void scan_library(std::filesystem::directory_entry dir)
{
    for (auto &p : std::filesystem::directory_iterator(dir))
    {
        std::cout << p << std::endl;
        // dl.push_back(p);
    }
}

std::filesystem::directory_entry apps_directory(std::filesystem::directory_entry dir)
{
    return std::filesystem::directory_entry(dir.path().string().append("\\steamapps\\common"));
}

void print_sub_directories(std::filesystem::directory_entry dir)
{
    std::cout << std::endl << "-------------------------------------------\nListing all folders found in library " << dir.path().string() << std::endl << "-------------------------------------------" << std::endl << std::endl;
    {
        int index = 1;
        std::string spacer = ".     ";

        for (auto &p : std::filesystem::directory_iterator(dir))
        {
            if (index == 10)
            {
                spacer = ".    ";
            }
            else if (index == 100)
            {
                spacer = ".   ";
            }

            std::cout << index << spacer << p.path().filename().string() << std::endl;
            index++;
        }
    }
}