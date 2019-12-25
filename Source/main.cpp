#pragma once
#include "Main.h"

/*
cl /EHsc Main.cpp Test.cpp  /nologo /std:c++latest
cd C:\Code\SteamLibraryManager
*/

int main(int argc, char const *argv[])
{
	for (;;)
	{
		LibraryFinder var;

		std::wstring substr = L"Test";
		std::wstring key = L"Computer\\HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Valve\\Steam";
		auto test = var.RegGetString(HKEY_LOCAL_MACHINE, substr, key);

		//Library test(MainLibPath);
		/*
		char FolderPath[255];
		std::cout << "Enter a path: ";
		std::cin.getline(FolderPath, sizeof(FolderPath));

		/*
		Code from "Library"
		std::cout <<"\r\n";
		for (auto a : GameList)
		{
			std::string tabs;
			int length = 48 - a->GetName().length();
			int num = length/8;
			if (length % 8 > 0 ) { num++; }
			for (int i = 0; i < num; i++)
			{
				tabs += "\t";
			}

			std::cout << a->GetName() << tabs << a->GetSize()/1024/1024 << " MB\r\n";
		}
		*/                
	}
	return 0;
}