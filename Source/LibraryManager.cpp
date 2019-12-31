#include "LibraryManager.h"

LibraryManager::LibraryManager()
{
}

void LibraryManager::PopulateLibraries()
{
	libraryList = finder.FindLibraryPaths();
}