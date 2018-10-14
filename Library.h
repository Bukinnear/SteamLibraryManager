#pragma once
#include <filesystem>
#include <string>
#include <map>

class library
{
    private:
    std::filesystem::directory_entry library_path;    
    std::filesystem::directory_entry apps_directory;
    std::filesystem::directory_entry app_ids_directory;
    std::map<std::filesystem::directory_entry, int> app_ids;
    bool is_valid_library(std::filesystem::directory_entry dir);
    void find_app_ids();

    public:
    library(std::string filepath);
    std::string path();
    void print_sub_directories(bool sort_by_size);
};

struct InvalidLibrary : public std::exception
{
    const char * what () const throw ()
    {
        return "Invalid Library Exception:\nFilepath either does not exist, or does not contain steamapps.";
    }
};