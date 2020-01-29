#include "Menu.h"

Menu::Menu() { }

int Menu::Activate()
{
	return 0;
}

void Menu::OutputMenuItem(const int index, const std::string_view item, const std::string_view size) const
{
	int targetLength = 108;
	std::string first("  " + std::to_string(index) + ": " + std::string(item));
	
	if (first.length() < targetLength)
	{
		targetLength -= first.length();
	}
	else
	{
		first += "\n";
	}

	std::string spacer;


	for (int i = 0; i < (targetLength / 8); i++)
	{
		spacer += "\t";
	}

	std::cout << "  " << index << ": " << item << spacer << " : " << size << "\n";
}
