#include "Menu_LibrariesList.h"

Menu_LibrariesList::Menu_LibrariesList() 
{
	manager.Sort();
}

int Menu_LibrariesList::Activate()
{
	std::cout << "Outputting all discovered libraries:\n----------\n";
	
	manager.PrintLibraries();

	std::string userInput;

	std::cout << "\nPlease make a selection by entering a corresponding number: ";
	std::cin >> userInput;
	int selection = std::stoi(userInput) - 1;

	auto selectedLib = manager.At(selection);

	Menu_GamesList gamesList(selectedLib);
	gamesList.Activate();

	return 0;
}