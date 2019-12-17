#pragma once
#include <filesystem>
#include <string>
#include <iostream>

class LibraryFolder
{
 public:
    LibraryFolder(const char * Path);
    LibraryFolder(std::string Path);
    bool operator==(const LibraryFolder &) const;
    bool operator==(const std::string &) const;

    const bool IsValidDirectory() const;
    const std::string GetFolderName() const;
    const std::string GetFolderPath() const;
protected:
    std::experimental::filesystem::directory_entry RootDirectory;
};