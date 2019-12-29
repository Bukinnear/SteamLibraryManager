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
		auto a = var.FindLibraryPaths();

		std::vector<Library> test;
		for (fs::directory_entry b : a)
		{
			test.push_back(Library(b));
		}

		for (auto b : test)
		{
			
			b.ListFolders();
		}
		/*
		Library test(MainLibPath);
		test.ScanFolders();
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