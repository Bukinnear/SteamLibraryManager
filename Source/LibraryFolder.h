#pragma once
#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::experimental::filesystem;

class LibraryFolder
{
 public:
    LibraryFolder(std::string Path);

    bool operator==(const LibraryFolder &) const;
    bool operator<(const LibraryFolder &) const;
    bool operator>(const LibraryFolder &) const;

    const bool IsValidDirectory() const;
    const std::string GetFolderName() const;
    const std::string GetFolderPath() const;
    const uint64_t GetFolderSize() const;
    const void RefreshFolderSize();
    
protected:
    fs::directory_entry RootDirectory;
    uint64_t FolderSize = 0;


private:

};