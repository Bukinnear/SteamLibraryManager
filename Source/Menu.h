#pragma once
#include <iostream>
#include <string>

class Menu
{
public:
	Menu();
	virtual int Activate();
	void OutputMenuItem(const int index, const std::string_view item, const std::string_view size) const;

private:

};