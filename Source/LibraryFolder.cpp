#pragma once
#include "LibraryFolder.h"

LibraryFolder::LibraryFolder(const char * Path)
{
    RootDirectory = fs::directory_entry(Path);
    CalculateFolderSize();
}

LibraryFolder::LibraryFolder(std::string Path)
{
    RootDirectory = fs::directory_entry(Path);
    CalculateFolderSize();
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

const uintmax_t LibraryFolder::GetFolderSize() const
{
    return FolderSize;
}

void LibraryFolder::CalculateFolderSize()
{
    if (!IsValidDirectory() || fs::is_empty(RootDirectory)) { return; }
    
    uintmax_t size = 0;


    for (auto & p : fs::recursive_directory_iterator(RootDirectory))
    {
        if (fs::is_directory(p) || fs::is_empty(p)) 
        {
            continue; 
        }
        try
        {
            size += (fs::file_size(p));
            std::cout << size << "\r\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << "\r\nSomething went wrong while getting the file size of \'" << p.path() << "\'\r\n" << e.what() << '\r\n';
        }
    }
    FolderSize = size;
    std::cout << "Foldersize: " <<  FolderSize << "\r\n";
}