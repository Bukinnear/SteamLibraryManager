#pragma once
#include "LibraryFinder.h"

class LibraryManager
{
public:
	LibraryManager();
	void PopulateLibraries();
	void Sort(bool bySize = false);
	void PrintLibraries() const;
	const std::shared_ptr<Library> At(int) const;

protected:
	std::vector<std::shared_ptr<Library>> libraryList;
	LibraryFinder finder = LibraryFinder();

private:

};
