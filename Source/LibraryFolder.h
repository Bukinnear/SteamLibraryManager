#pragma once
#include <filesystem>
#include <string>

class LibraryFolder
{
 public:
    LibraryFolder(std::string Path);
    bool isValidDirectory();
    bool isValidLibrary();
    std::string getFolderName();
    std::string getFolderPath();
private:
    std::experimental::filesystem::directory_entry * RootDirectory;
};