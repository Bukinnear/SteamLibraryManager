#pragma once
#include "Library.h"

namespace fs = std::experimental::filesystem;

Library::Library(const char * Path) : LibraryFolder(Path)
{
    BuildLibraryList();
}

Library::Library(std::string Path) : LibraryFolder(Path)
{
    BuildLibraryList();
}

void Library::BuildLibraryList()
{
    for (auto p : fs::directory_iterator(RootDirectory.path()))
    {
        LibraryFolder * s = new LibraryFolder(p.path().string());
        FolderList.insert(s);
    }
}

const std::set<LibraryFolder*> * const Library::GetLibraryList() const
{
    return & FolderList;
}