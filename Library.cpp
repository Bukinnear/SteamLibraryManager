#pragma once
#include <iostream>
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

std::string library::path()
{
    return library_path.path().string();
}

void library::print_sub_directories()
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