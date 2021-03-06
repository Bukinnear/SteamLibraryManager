#pragma once
#include <set>
#include "Menu.h"
#include "LibraryManager.h"
#include "Menu_GamesList.h"

class Menu_LibrariesList : Menu
{
public:
	Menu_LibrariesList();
	int Activate() override;

private:
	LibraryManager manager;

	void PrintLibraries(const std::vector<std::shared_ptr<Library>> list) const;

};