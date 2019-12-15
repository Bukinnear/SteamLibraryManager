#pragma once
#include <filesystem>
#include <string>

class LibraryFolder
{
 public:
    LibraryFolder(const char * Path);
    LibraryFolder(std::string Path);
    bool isValidDirectory();
    std::string getFolderName();
    std::string getFolderPath();
private:
    std::experimental::filesystem::directory_entry * RootDirectory;
};