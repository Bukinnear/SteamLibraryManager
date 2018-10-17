#pragma once
#include <filesystem>
#include <string>
#include <map>

struct app {
    std::filesystem::directory_entry path;
    int id;
    float size;

    bool operator <(app a) 
    { 
        return size > a.size;
    }
};// sort_by_id;

struct InvalidLibrary : public std::exception
{
    const char * what () const throw ()
    {
        return "Invalid Library Exception:\nFilepath either does not exist, or does not contain steamapps.";
    }
};

class library
{
    private:
    std::filesystem::directory_entry library_path;    
    std::filesystem::directory_entry apps_directory;
    std::filesystem::directory_entry app_ids_directory;
    std::vector<app> apps;
    // std::map<std::filesystem::directory_entry, int> app_ids;
    // std::map<std::filesystem::directory_entry, int> app_sizes;
    bool is_valid_library(std::filesystem::directory_entry dir);
    void scan_library_apps();

    

    public:
    library(std::string filepath);
    std::string path();
    void print_sub_directories(bool sort_by_size);
};

