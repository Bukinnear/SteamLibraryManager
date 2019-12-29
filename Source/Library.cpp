#pragma once
#include "Library.h"

Library::Library(std::string Path) : LibraryFolder(Path)
{
	steamAppsDir = fs::directory_entry(Path + "\\steamapps");
	commonDir = fs::directory_entry(Path + "\\steamapps\\Common");

	if (IsValidLibrary())
	{ BuildLibraryList(); }
	else
	{ std::cout << "\r\nERROR:\r\nLibrary at path \'" << RootDirectory.path().string() << "\' is not a valid library. Could not locat steamapps\\common.\r\n"; }
}

const bool Library::ScanningRequired() const
{
	return !foldersToManuallyScan.empty();
}

void Library::ScanFolders()
{
	for (auto folder : foldersToManuallyScan)
	{
		std::cout << "Scanning: " << folder->FolderName() << " ... ";
		folder->RefreshSize();
		std::cout << "Done\n";
	}
}

const bool Library::IsValidLibrary() const
{
	return commonDir.exists() && commonDir.is_directory();
}

void Library::BuildLibraryList()
{
	gameList.clear();
	foldersToManuallyScan.clear();

	if (!IsValidLibrary()) { return; }

	UMapPtr_str_app manifestList = AllManifests();

	for (auto gameFolder : fs::directory_iterator(commonDir))
	{
		auto findResult = manifestList->find(gameFolder.path().filename().string());
		if (findResult != manifestList->end())
		{
			AppManifest manifest = findResult->second;
			if (manifest.IsValid())
			{
				std::shared_ptr<Game> newGame = std::make_shared<Game>(steamAppsDir, manifest);
				gameList.push_back(newGame);
			}
		}
		else
		{ 
			std::shared_ptr<Game> newGame = std::make_shared<Game>(steamAppsDir, gameFolder);
			gameList.push_back(newGame);
			foldersToManuallyScan.push_back(newGame);
		}
	}
}

const UMapPtr_str_app Library::AllManifests() const
{
	UMapPtr_str_app returnMap(new std::unordered_map<std::string, AppManifest>);

	for (auto filepath : fs::directory_iterator(steamAppsDir))
	{
		auto filename = filepath.path().filename().string();

		auto isAppManifest = filename.find("appmanifest_");
		auto notCorrect = filename.npos;

		if (!fs::is_regular_file(filepath) || isAppManifest == notCorrect) { continue; }

		AppManifest manifest = AppManifest::ReadFromFile(filepath.path().string());
		if (manifest.IsValid()) 
		{ 
			returnMap->insert({manifest.installdir, manifest});
		}
	}
	return returnMap;
}
