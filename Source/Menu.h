#pragma once
#include <iostream>
#include <string>
#include <map>

class Menu
{
public:
	Menu();
	virtual int Activate();
	void OutputMenuItem(const int index, const std::string_view item, const std::string_view size) const;
	std::string TruncateSize(uint64_t size);

private:
	const static int targetLength = 75;
	const static int targetLength_Size = 100;
	const static int wrapSpaces = 7;

	const static std::map<int, std::string> byteSize;
};