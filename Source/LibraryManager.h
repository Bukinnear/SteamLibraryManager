#pragma once
#include "LibraryFinder.h"

class LibraryManager
{
public:
	LibraryManager();
	void PopulateLibraries();

protected:
	std::set<fs::directory_entry> libraryList;

	LibraryFinder finder = LibraryFinder();

private:

};
