#pragma once
#include "Library.h"

namespace fs = std::experimental::filesystem;

Library::Library(const char * Path) : LibraryFolder(Path)
{
    CommonDirectory = fs::directory_entry(RootDirectory.path().string() + "\\steamapps\\common");
    BuildLibraryList();
}

Library::Library(std::string Path) : LibraryFolder(Path)
{
    CommonDirectory = fs::directory_entry(RootDirectory.path().string() + "\\steamapps\\common");
    BuildLibraryList();
}

void Library::BuildLibraryList()
{
    for (auto p : fs::directory_iterator(CommonDirectory.path()))
    {
        LibraryFolder s = LibraryFolder(p.path().string());
        FolderList.insert(s);
    }
}

const std::set<LibraryFolder, Compare> * const Library::GetLibraryList() const
{
    return & FolderList;
}

const bool Library::ContainsFolder(std::string input) const
{
    auto a = FolderList.find(input);

    if (a == FolderList.begin())
    {
        return false;
    }
    else
    {
        return true;
    }    
}

