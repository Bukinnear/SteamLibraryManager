#pragma once
#include "LibraryFolder.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <set>

struct Compare
{
    using is_transparent = void;

    bool operator()(const LibraryFolder & lhs, const LibraryFolder & rhs) const
    {
        return lhs.GetFolderPath() < rhs.GetFolderPath();
    }

    bool operator()(const LibraryFolder & lhs, const std::string & rhs)
    {
        return lhs.GetFolderPath() < rhs;
    }

    bool operator()(const std::string & lhs, const LibraryFolder & rhs)
    {
        return lhs < rhs.GetFolderPath();
    }    

    bool operator()(const LibraryFolder & lhs, const float & rhs)
    {
        return lhs.GetFolderSize() < rhs;
    }

    bool operator()(const float & lhs, const LibraryFolder & rhs)
    {
        return lhs < rhs.GetFolderSize();
    }
};

class Library : public LibraryFolder
{
    public:
    Library(const char * Path);
    Library(std::string Path); 

    const std::set<LibraryFolder, Compare> * const GetLibraryList() const;
    const bool ContainsFolder(std::string) const;

    protected:
    fs::directory_entry CommonDirectory;
    std::set<LibraryFolder, Compare> FolderList;
    void BuildLibraryList();
    
    private:
};