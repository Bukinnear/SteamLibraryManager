#pragma once

#include "Menu.h"
#include "Library.h"

class Menu_GamesList : Menu
{
public:
	Menu_GamesList(std::shared_ptr<Library> in_SelectedLibrary);
	int Activate() override;

private:
	std::shared_ptr<Library> selectedLibrary;
};