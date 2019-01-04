#pragma once
#include <filesystem>
#include <string>
#include <map>

struct app {
    std::filesystem::directory_entry path;
    std::filesystem::directory_entry manifest_path;
    int id;
    float size;

    bool operator <(app a) 
    { 
        return size > a.size;
    }
};

struct InvalidLibrary : public std::exception
{
    const char * what () const throw ()
    {
        return "Invalid Library Exception:\nFilepath either does not exist, or does not contain steamapps.";
    }
};


bool sort_apps_aphabetically (const app a, const app b); 

class library
{
    private:
    std::filesystem::directory_entry library_path;    
    std::filesystem::directory_entry apps_directory;
    std::filesystem::directory_entry app_ids_directory;
    std::vector<app> apps;
    bool is_valid_library(std::filesystem::directory_entry dir);
    void catalogue_library_apps();   

    public:
    library(std::string filepath);
    std::string path();
    void print_all_apps(int* index, bool sort_by_size = true);
    app get_app(int index);
};

