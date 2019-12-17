#pragma once
#include "LibraryFolder.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <set>

class Library : public LibraryFolder
{
    public:
    Library(const char * Path);
    Library(std::string Path);
    const std::set<LibraryFolder*> * const GetLibraryList() const;
    protected:
    std::set<LibraryFolder*> FolderList;
    void BuildLibraryList();
    private:
};