#pragma once
#include "LibraryFolder.h"

namespace fs = std::experimental::filesystem;

LibraryFolder::LibraryFolder(const char * Path)
{
    RootDirectory = fs::directory_entry(Path);
}

LibraryFolder::LibraryFolder(std::string Path)
{
    RootDirectory = fs::directory_entry(Path);
}

bool LibraryFolder::operator==(const LibraryFolder & rhs) const
{
    return getFolderPath() == rhs.getFolderPath(); 
}

bool LibraryFolder::operator==(const std::string & rhs) const
{
    std::string compare = rhs;
    for (;;)
    {
        if (compare.rfind(" "))
        {
            compare.pop_back();
        }
        else
        {
            break;
        }        
    }
    return this->getFolderPath() == compare || this->getFolderName() == compare;
}

const bool LibraryFolder::IsValidDirectory() const
{
    return (fs::exists(RootDirectory) && fs::is_directory(RootDirectory));
}

const std::string LibraryFolder::GetFolderName() const
{
    return RootDirectory.path().filename().string();
}

const std::string LibraryFolder::GetFolderPath() const
{
    return RootDirectory.path().string();
}