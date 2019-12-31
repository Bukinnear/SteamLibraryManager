#pragma once
#include "Main.h"

int main(int argc, char const *argv[])
{
	for (;;)
	{
		std::string buffer;

		std::cout << "Please enter the number of the Library you wish to manipulate: ";
		std::cin >> buffer;

		for (auto character : buffer)
		{
			if (!std::isdigit(character))
			{
				std::cout << "\nThat is not a valid number.\n\n";

				// clear the cin buffer to avoid retaining the error 
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		std::cout << "\n" << buffer << "\n\n";
	}
	return 0;
}