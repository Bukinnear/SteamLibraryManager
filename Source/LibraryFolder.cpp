#pragma once
#include "LibraryFolder.h"

LibraryFolder::LibraryFolder(std::string Path) : RootDirectory(Path) {}

bool LibraryFolder::operator==(const LibraryFolder & rhs) const
{
    return GetFolderPath() == rhs.GetFolderPath(); 
}

bool LibraryFolder::operator<(const LibraryFolder & rhs) const
{
    return GetFolderSize() < rhs.GetFolderSize(); 
}

bool LibraryFolder::operator>(const LibraryFolder & rhs) const
{
    return GetFolderSize() > rhs.GetFolderSize(); 
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

const uint64_t LibraryFolder::GetFolderSize() const
{
    return FolderSize; 
}

const void LibraryFolder::RefreshFolderSize()
{
    if (!IsValidDirectory() || fs::is_empty(RootDirectory)) { FolderSize = 0; }
    
    uint64_t Size = 0;

    for (auto & p : fs::recursive_directory_iterator(RootDirectory))
    {
        if (fs::is_directory(p) || fs::is_empty(p)) 
        {
            continue; 
        }
        try
        {
            Size += (fs::file_size(p));
        }
        catch(const std::exception& e)
        {
            std::cerr << "\r\nSomething went wrong while getting the file size of \'" << p.path() << "\':\r\n" << e.what() << '\r\n';
        }
    }
    FolderSize = Size;
}