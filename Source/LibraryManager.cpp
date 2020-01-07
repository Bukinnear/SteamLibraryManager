#include "LibraryManager.h"

LibraryManager::LibraryManager() 
{ PopulateLibraries(); }

void LibraryManager::PopulateLibraries()
{
	libraryList = finder.FindLibraryPaths();
}

void LibraryManager::Sort(bool bySize)
{
	if (bySize)
	{
		std::sort(
			libraryList.begin(), 
			libraryList.end(), 
			[](std::shared_ptr<Library> lhs, std::shared_ptr<Library> rhs)
			{
				return lhs->Size() < rhs->Size();
			}
		);
	}
	else
	{
		std::sort(
			libraryList.begin(),
			libraryList.end(),
			[](std::shared_ptr<Library> lhs, std::shared_ptr<Library> rhs)
			{
				return lhs->Path() < rhs->Path();				
			}
		);
	}
}

void LibraryManager::PrintLibraries() const
{
	int index = 0;
	for (auto iter = libraryList.begin(); iter != libraryList.end(); iter++)
	{
		index++;
		std::shared_ptr<Library> lib = *iter;

		std::cout << "  " << index << ": \'" << lib->Path() << "\' : " << lib->Size() << "\n";
	}
}

const std::shared_ptr<Library> LibraryManager::At(int pos) const
{
	std::shared_ptr<Library> returnVal;

	if (pos < libraryList.size())
	{
		try
		{ returnVal = libraryList.at(pos); }
		catch (const std::exception&)
		{ }
	}

	if (returnVal)
	{ return returnVal; }
	else
	{ return nullptr; }
}
