#include "Menu_GamesList.h"

Menu_GamesList::Menu_GamesList(std::shared_ptr<Library> in_SelectedLibrary) : selectedLibrary(in_SelectedLibrary)
{
	// SORT HERE
}

int Menu_GamesList::Activate()
{
	std::cout << "\n";
	if (selectedLibrary->ScanningRequired())
		selectedLibrary->ScanFolders();

	int index = 1;
	for (auto game : selectedLibrary->FolderList())
	{
		auto a = TruncateSize(game->Size());
		OutputMenuItem(index, game->Name(), a);
		index++;
	}

	std::string userInput;
	std::cout << "\nPlease make a selection by entering a corresponding number: ";
	std::cin >> userInput;

	return 0;
}