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
		
		/*
		total length = x
		y = 1 + index + 3 + Path() 
		z = 3 + Size() OR Size() (on a new line)

		x = y + z

		// if the path + extra > than the required length
		if (y > x)
		{ 
			// find out how many lines it takes up
			// TODO: find a way to only retrieve whole numbers, do ints allow this, or will they round up?
			int number_of_lines = y / x

			// if adding the size would be too much
			if (((y + z) / x) > number_of_lines)
			{
				// Put size at the end of a new line
				y += "\n" + ((x - z) + z) spaces + "\' : " + lib->Size() + "\n"
			}
			else
			{
				// Add y + z into one
				y += "\' : " + lib->Size() + "\n"
			}

		}

		*/
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
