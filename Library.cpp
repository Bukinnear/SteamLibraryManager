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
        find_app_ids();
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

void library::find_app_ids()
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
                int id = 0;
                fs::directory_entry name;

                char id_buffer[256];
                char name_buffer[256];

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

                id = std::stoi(id_buffer);

                std::string n = apps_directory.path().string() + "\\" + std::string(name_buffer);
                name.assign(n);    

                if (name.path().string() != "" && id != 0)
                {
                    app_ids.insert_or_assign(name, id);
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
    {
        int index = 1;
        std::string spacer = ".     ";

        for (auto &p : fs::directory_iterator(apps_directory))
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