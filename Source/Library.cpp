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

const bool Library::IsValidLibrary() const
{
	return CommonDir.exists() && CommonDir.is_directory();
}

const std::vector<std::shared_ptr<Game>> Library::BuildLibraryList() const
{
	std::vector<std::shared_ptr<Game>> ReturnVec;
	if (!IsValidLibrary()) { return ReturnVec; }

	UMapPtr_str_app ManifestList = AllManifests();
	std::set<std::string> FoldersToManuallyScan;

	for (auto GameFolder : fs::directory_iterator(CommonDir))
	{
		auto FindResult = ManifestList->find(GameFolder.path().filename().string());
		if (FindResult != ManifestList->end())
		{
			AppManifest Manifest = FindResult->second;
			if (Manifest.IsValid())
			{
				std::shared_ptr<Game> NewGame = std::make_shared<Game>(SteamAppsDir, Manifest);
				ReturnVec.push_back(NewGame);
			}
		}
		else
		{ 			
			std::shared_ptr<Game> NewGame = std::make_shared<Game>(SteamAppsDir, GameFolder);
			ReturnVec.push_back(NewGame);
		}
	}	
	return ReturnVec;
}

const UMapPtr_str_app Library::AllManifests() const
{
	UMapPtr_str_app ReturnMap(new std::unordered_map<std::string, AppManifest>);

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
