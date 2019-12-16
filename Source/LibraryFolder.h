#pragma once
#include <filesystem>
#include <string>

class LibraryFolder
{
 public:
    LibraryFolder(const char * Path);
    LibraryFolder(std::string Path);
    friend bool operator==(const LibraryFolder &, const LibraryFolder &) { return true; };
    //friend bool operator == (const LibraryFolder &, const LibraryFolder &);
    //friend bool operator!= (const LibraryFolder &, const LibraryFolder &);

    const bool isValidDirectory();
    const std::string getFolderName();
    const std::string getFolderPath();
protected:
    std::experimental::filesystem::directory_entry * RootDirectory;
};