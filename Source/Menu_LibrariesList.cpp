#include "Menu_LibrariesList.h"

Menu_LibrariesList::Menu_LibrariesList() 
{
	manager.Sort();
}

int Menu_LibrariesList::Activate()
{
	std::cout << "Outputting all discovered libraries:\n----------\n";
	
	PrintLibraries(manager.List());

	std::string userInput;

	std::cout << "\nPlease make a selection by entering a corresponding number: ";
	std::cin >> userInput;
	int selection = std::stoi(userInput) - 1;

	auto selectedLib = manager.At(selection);

	Menu_GamesList gamesList(selectedLib);
	gamesList.Activate();

	return 0;
}

void Menu_LibrariesList::PrintLibraries(const std::vector<std::shared_ptr<Library>> list) const
{
	int index = 1;
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		std::shared_ptr<Library> lib = *iter;

		std::string first = "\'" + lib->Path() + "\'";
		std::string second = std::to_string(lib->Size());
		
		OutputMenuItem(index, first, second);
		index++;
	}
}
