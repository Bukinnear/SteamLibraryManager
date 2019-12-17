#pragma once
#include "LibraryFolder.h"

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
    return GetFolderPath() == rhs.GetFolderPath(); 
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

const float LibraryFolder::GetFolderSize() const
{
    return FolderSize;
}