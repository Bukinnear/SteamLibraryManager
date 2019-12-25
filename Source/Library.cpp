#pragma once
#include "Library.h"

Library::Library(std::string Path) : LibraryFolder(Path)
{
	SteamAppsDir = fs::directory_entry(Path + "\\steamapps");
	CommonDir = fs::directory_entry(Path + "\\steamapps\\Common");

	if (IsValidLibrary())
	{ GameList = BuildLibraryList(); }
	else
	{ std::cout << "\r\nERROR:\r\nLibrary at path \'" << RootDirectory.path().string() << "\' is not a valid library. Could not locat steamapps\\common.\r\n"; }
}

const std::vector<std::shared_ptr<Game>> Library::BuildLibraryList() const
{
	std::vector<std::shared_ptr<Game>> ReturnVec;
	if (!IsValidLibrary()) { return ReturnVec; }

	std::unordered_map<std::string, AppManifest> ManifestList = AllManifests();
	for (auto GameFolder : fs::directory_iterator(CommonDir))
	{
		try 
		{ 
			auto Manifest = ManifestList.at(GameFolder.path().filename().string());
			if (Manifest.IsValid())
			{
				std::shared_ptr<Game> NewGame = std::make_shared<Game>(SteamAppsDir, Manifest);
				ReturnVec.push_back(NewGame);
			}
		}
		catch(const std::exception& e) 
		{ 
			std::cout << "\r\nALERT:\r\nThere is no appmanifest file for: " << GameFolder.path().string() << "\r\nWe will continue, but scanning the folder size will take longer.\r\n\r\n"; 
			std::shared_ptr<Game> NewGame = std::make_shared<Game>(SteamAppsDir, GameFolder);
			ReturnVec.push_back(NewGame);
		}
	}	
	return ReturnVec;
}

const std::unordered_map<std::string, AppManifest> Library::AllManifests() const
{
	std::unordered_map<std::string, AppManifest> ReturnMap;

	for (auto f : fs::directory_iterator(SteamAppsDir))
	{
		auto Filename = f.path().filename().string().find("appmanifest_");
		auto NotCorrect = f.path().filename().string().npos;

		if (!fs::is_regular_file(f) || Filename == NotCorrect) { continue; }

		AppManifest Manifest = AppManifest::ReadFromFile(f.path().string());
		if (Manifest.IsValid()) 
		{ 
			ReturnMap.insert({Manifest.installdir, Manifest}); 
		}
	}
	return ReturnMap;
}

const bool Library::IsValidLibrary() const
{
	return CommonDir.exists() && CommonDir.is_directory();
}