#pragma once
#include <filesystem>
#include <string>

class library
{
    private:
    std::filesystem::directory_entry library_path;    
    std::filesystem::directory_entry apps_directory;
    bool is_valid_library(std::filesystem::directory_entry dir);

    public:
    library(std::string filepath);
    std::string path();
    void print_sub_directories();
};

struct InvalidLibrary : public std::exception
{
    const char * what () const throw ()
    {
        return "Invalid Library Exception:\nFilepath either does not exist, or does not contain steamapps.";
    }
};