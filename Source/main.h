#pragma once
#include "LibraryFolder.h"
#include "Library.h"
#include "ManifestReader.h"
#include "Test.h"

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>

const char * MainLibPath = "C:\\Program Files (x86)\\Steam";

const char * ExampleGameFolder = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Borderlands 2";

// Don't Starve Together
const std::string manifest = "E:\\SteamLibrary\\SteamApps\\appmanifest_322330.acf";

/*
#include "Library.h"    
#include <exception>    // Exceptions
#include <filesystem>   // File manipulation
#include <iostream>     // User input/output
#include <memory>       // Smart pointers
#include <conio.h>      // Windows I/O api
#include <windows.h>    // Windows file API
#include <string>


struct back : public std::exception
{
    const char * what () const throw ()
    {
        return "Back was selected";
    }
};

bool configFileExists();
int runFirstSetup();
std::vector<std::filesystem::directory_entry> getAllDrivePaths();


library getValidLibrary();
*/