#include "Menu.h"

Menu::Menu() { }

const std::map<int, std::string> Menu::byteSize = {
	{0, "B"},
	{1, "KB"},
	{2, "MB"},
	{3, "GB"},
	{4, "TB"},
	{5, "PB"},
	{6, "Too Big!"}
};

int Menu::Activate()
{
	return 0;
}

void Menu::OutputMenuItem(const int index, const std::string_view item, const std::string_view size) const
{
	// The string we want to output before the spacer and size
	std::string ourString("  " + std::to_string(index) + ": " + std::string(item));

	// Current and previous location in the string. These are 0-indexed.
	int currentPoint;
	int lastPoint = 0;

	if (ourString.length() > targetLength)
		currentPoint = targetLength - 1;
	else
		currentPoint = int(ourString.length()) - 1;	

	// While our current point is not at the end of the string
	while (ourString.length() - 1 > currentPoint)
	{
		// find the location of the slash closest to the end of our current line
		std::string currentLine = ourString.substr(lastPoint, targetLength);
		int closestSlash = int(currentLine.rfind("\\", currentPoint)) + lastPoint + 1;
				
		if (closestSlash == 0)
			// set the closest slash to be the end of the current line
			closestSlash = currentPoint;			

		// add a new line after the slash
		ourString.insert(closestSlash, "\n");

		// Add spaces to the beginning of the line
		for (int i = 1; i != wrapSpaces; i++)
		{
			ourString.insert(closestSlash + 1, " ");
		}

		// Move the last point, and account for the new line character
		lastPoint = currentPoint + 1;

		// Place the current point after the newline & spaces
		currentPoint += 1 + wrapSpaces;

		// if the difference between our last location and the end of the string is greater than the line limit,
		if ((ourString.length() - lastPoint + 1) > targetLength)
		{
			// Move our current position to the end of a new line's worth of characters.		
			currentPoint += targetLength;
		}
		else
			// Else, make our current position the end of the string.
			currentPoint = int(ourString.length() - 1);
	}

	std::string spacer = "";

	// Do things here
	int lineLength = currentPoint - lastPoint + 1;
	int spacerLength = targetLength_Size - lineLength;

	int numberOfTabs = spacerLength / 8;
	int numberOfSpaces = spacerLength % 8;

	for (; numberOfSpaces > 0; numberOfSpaces--)
		spacer.append(" ");

	for (; numberOfTabs > 0; numberOfTabs--)
		spacer.append("\t");

	std::cout << ourString << spacer << ": " << size << "\n";
}

std::string Menu::TruncateSize(uint64_t size)
{	
	uint64_t tempSize = size;
	int index = 0;

	do 
	{
		tempSize /= 1024;
		if (tempSize > 0)
		{
			size = tempSize;
			index++;
		}
	} while (tempSize > 0 && index < 6);

	return std::string(std::to_string(size) + byteSize.at(index));
}
