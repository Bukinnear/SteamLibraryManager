#pragma once
#include "LibraryFolder.h"
#include <string>
#include <set>

class Library : public LibraryFolder
{
    public:
    Library(const char * Path);
    Library(std::string Path);
    const std::set<LibraryFolder*> * GetLibraryList();
    protected:
    private:
    std::set<LibraryFolder*> * FolderList;
    void BuildLibraryList();
};