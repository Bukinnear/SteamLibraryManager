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

    const bool isValidDirectory() const;
    const std::string getFolderName() const;
    const std::string getFolderPath() const;
protected:
    std::experimental::filesystem::directory_entry RootDirectory;
};