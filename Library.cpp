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
                std::string a;
                std::string b;

                int id = 0;
                fs::directory_entry path;

                while (!id_file.eof())
                {
                    id_file >> a >> b;
                    // std::cout << a << std::endl;

                    std::cout << a << " : " << b << std::endl;

                    if (a == "\"appid\"")
                    {
                        b.erase(0, 1);
                        b.erase(b.length()-1, 1);  
                        id = stoi(b);                                         
                    }
                    if (a == "\"installdir\n")
                    {
                        b.erase(0, 1);
                        b.erase(b.length()-1, 1); 
                        path.assign(b);
                    } 
                }     
                std::cout << a << " : " << b << std::endl;
                if (id != 0 && path != "")
                {
                    // std::cout << "test2" << std::endl;
                    app_ids.insert_or_assign(path, id);
                }                          
            }
            id_file.close();
        }
    }
    // std::cout << app_ids.size() << std::endl;
    for (auto p : app_ids)
    {
        // std::cout << "test3" << std::endl;
        std::cout << p.first << " : " << p.second << std::endl;
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