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
/*
bool operator==(const LibraryFolder & lhs, const LibraryFolder & rhs)
{
    return true; //(lhs.RootDirectory->path().filename().string() == rhs.RootDirectory->path().filename().string());
}
/*
bool operator != (const LibraryFolder & lhs, const LibraryFolder & rhs)
{
    return false; (lhs.RootDirectory->path().filename().string() != rhs.RootDirectory->path().filename().string());
}
*/
const bool LibraryFolder::isValidDirectory()
{
    return (fs::exists(*RootDirectory) && fs::is_directory(*RootDirectory));
}

const std::string LibraryFolder::getFolderName()
{
    return RootDirectory->path().filename().string();
}

const std::string LibraryFolder::getFolderPath()
{
    return RootDirectory->path().string();
}