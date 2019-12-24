#pragma once
#include "Library.h"

namespace fs = std::experimental::filesystem;

Library::Library(std::string Path) : LibraryFolder(Path)
{
	SteamAppsDir = fs::directory_entry(Path + "\\steamapps");
	CommonDir = fs::directory_entry(Path + "\\steamapps\\Common");
	GameList = BuildLibraryList();
}

const std::vector<std::shared_ptr<Game>> Library::BuildLibraryList() const
{
	std::vector<std::shared_ptr<Game>> ReturnVec;

	auto Manifests = GetAllManifests();
	for (auto a : fs::directory_iterator(CommonDir))
	{
		try { auto b = Manifests->at(a.path().filename().string()); }
		catch(const std::exception& e) 
		{ std::cout << "\r\nALERT:\r\nThere is no appmanifest file for: " << a.path().string() << "\r\n\r\nWe will continue, but scanning the folder size will take longer.\r\n"; }
		
		
	}
	
	return ReturnVec;
}

const std::unique_ptr<std::unordered_map<std::string, AppManifest>> Library::GetAllManifests() const
{
	std::unique_ptr<std::unordered_map<std::string, AppManifest>> ReturnMap(new std::unordered_map<std::string, AppManifest>);

	for (auto f : fs::directory_iterator(SteamAppsDir))
	{
		auto Filename = f.path().filename().string().find("appmanifest_");
		auto NotCorrect = f.path().filename().string().npos;

		if (!fs::is_regular_file(f) || Filename == NotCorrect) { continue; }

		AppManifest Manifest = AppManifest::ReadFromFile(f.path().string());
		if (Manifest.IsValid()) 
		{ 
			ReturnMap->insert({Manifest.installdir, Manifest}); 
		}
	}
	return ReturnMap;
}

/*
Library::Library(const char * Path) : LibraryFolder(Path)
{
	SteamAppsDir = fs::directory_entry(RootDirectory.path().string() + "\\steamapps");
	BuildLibraryList();
}

const std::set<LibraryFolder, Compare> * const Library::GetLibraryList() const
{
	return & FolderList;
}

void Library::BuildLibraryList()
{
	for (auto p : fs::directory_iterator(SteamAppsDir.path()))
	{
		LibraryFolder s = LibraryFolder(p.path().string());
		FolderList.insert(s);
	}
}

const bool Library::ContainsFolder(std::string input) const
{
	auto a = FolderList.find(input);

	if (a == FolderList.begin())
	{
		return false;
	}
	else
	{
		return true;
	}    
}
*/