#include "Menu_GamesList.h"

Menu_GamesList::Menu_GamesList(std::shared_ptr<Library> in_SelectedLibrary) : selectedLibrary(in_SelectedLibrary)
{
}

int Menu_GamesList::Activate()
{
	if (selectedLibrary->ScanningRequired())
	{ selectedLibrary->ScanFolders(); }

	selectedLibrary->ListFolders();

	std::string userInput;
	std::cout << "\nPlease make a selection by entering a corresponding number: ";
	std::cin >> userInput;
	return 0;
}
