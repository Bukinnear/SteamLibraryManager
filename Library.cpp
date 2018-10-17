#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "Library.h"

namespace fs = std::filesystem;

library::library(std::string filepath)
{
    if (fs::exists(filepath) && is_valid_library(fs::directory_entry(filepath)))
    {
        library_path = fs::directory_entry(filepath);
        apps_directory.assign(library_path.path().string().append("\\steamapps\\common"));
        app_ids_directory.assign(library_path.path().string().append("\\steamapps"));
        scan_library_apps();
    }
    else
    {
        throw InvalidLibrary();
    }
}

bool library::is_valid_library(fs::directory_entry dir)
{
    for (auto p : fs::directory_iterator(dir))
    {
        if (fs::directory_entry(p).path().filename().string() == "steamapps")
        {
            return true;
        }
    }
    return false;
}

void library::scan_library_apps()
{
    for (auto p : fs::directory_iterator(app_ids_directory))
    {
        std::string s = p.path().filename().string();
        if (s.find(".acf") != std::string::npos)
        {
            std::ifstream id_file(p);
            if (!id_file.is_open())
            {
                std::cout << "Warning: could not open " << p << std::endl;
            }
            else 
            {
                // this part is kinda dirty
                app thisapp;

                char id_buffer[256];
                char name_buffer[256];
                char size_buffer[256];

                // set place 24
                id_file.seekg(24);

                // get id
                id_file.get(id_buffer, sizeof id_buffer, '\"');

                // skip to the line with the directory name
                for (int i = 0; i < 4; i++)
                {                    
                    id_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
                // skip to the actual name
                for (int i = 0; i < 3; i++)
                {
                    id_file.ignore(std::numeric_limits<std::streamsize>::max(), '\"');
                }

                // get name
                id_file.get(name_buffer, sizeof name_buffer, '\"');

                // skip to the line with the directory size
                for (int i = 0; i < 3; i++)
                {                    
                    id_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
                // skip to the actual size
                for (int i = 0; i < 3; i++)
                {
                    id_file.ignore(std::numeric_limits<std::streamsize>::max(), '\"');
                }

                // get size
                id_file.get(size_buffer, sizeof size_buffer, '\"');                
                
                thisapp.id = std::stoi(id_buffer);

                std::string n = apps_directory.path().string() + "\\" + std::string(name_buffer);
                thisapp.path.assign(n);  

                try
                {
                    // size in GB
                    double_t s = std::stoull(size_buffer);
                    thisapp.size = s / 1024 / 1024 / 1024;
                }
                catch(...)
                {
                    std::cout << std::endl << "ERROR\nFailed to convert the size of" << p.path().filename() << " - the file size is probably bigger than the data type. We're gonna need a bigger boat..." << std::endl << std::endl;
                }                

                if (thisapp.path.path().string() != "" && thisapp.id != 0)
                {
                    apps.push_back(thisapp);
                }
                else
                {
                    std::cout << "\nERROR\nThere was a problem scanning the file:\n" << p.path() << std::endl << std::endl;
                }
            }
            id_file.close();
        }
    }
}

std::string library::path()
{
    return library_path.path().string();
}

void library::print_sub_directories(bool sort_by_size)
{
    std::cout << std::endl << "-------------------------------------------\nListing all folders found in library " << apps_directory.path().string() << std::endl << "-------------------------------------------" << std::endl << std::endl;
    if (sort_by_size)
    {

    }
    else
    {
        int index = 1;
        std::string spacer = ".     ";

        for (auto &p : apps)
        {
            if (index == 10)
            {
                spacer = ".    ";
            }
            else if (index == 100)
            {
                spacer = ".   ";
            }

            std::cout << index << spacer << p.path.path().filename().string() << std::endl;
            index++;
        }
    }
}