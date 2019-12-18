#pragma once
#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::experimental::filesystem;

class LibraryFolder
{
 public:
    LibraryFolder(const char * Path);
    LibraryFolder(std::string Path);

    bool operator==(const LibraryFolder &) const;

    const bool IsValidDirectory() const;
    const std::string GetFolderName() const;
    const std::string GetFolderPath() const;
    const int GetFolderSize() const;
    
protected:
    fs::directory_entry RootDirectory;
    double FolderSize = 0;

    void CalculateFolderSize();

private:
};