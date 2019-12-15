#pragma once
#include <filesystem>
#include <iostream>
#include "LibraryFolder.h"

namespace fs = std::experimental::filesystem;

LibraryFolder::LibraryFolder(const char * Path)
{
    RootDirectory = new fs::directory_entry(Path);
}

LibraryFolder::LibraryFolder(std::string Path)
{
    RootDirectory = new fs::directory_entry(Path);
}

bool LibraryFolder::isValidDirectory()
{    
    return (fs::exists(*RootDirectory) && fs::is_directory(*RootDirectory));
}

std::string LibraryFolder::getFolderName()
{
    return RootDirectory->path().filename().string();
}

std::string LibraryFolder::getFolderPath()
{
    return RootDirectory->path().string();
}